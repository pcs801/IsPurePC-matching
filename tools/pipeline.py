#!/usr/bin/env python3
"""pipeline.py - M2.6 revision-3: deterministic prepare/verify only.

prepare  build sandbox + evidence card per function, register todo overrides,
         write build/m26-batch-N/card.json (the subagent prompt payload).
verify   batch-compile the candidates the subagents wrote, match_kit byte check,
         promote hits to matched, produce instruction diffs, write bookkeeping.

No model or CLI invocation here: C is written by one DSH subagent per function.

Usage
  python tools/pipeline.py prepare --batch 1 --limit 20
  python tools/pipeline.py verify  --batch 1
  python tools/pipeline.py status
"""
import argparse
import hashlib
import json
import os
import re
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import claims as C          # noqa: E402
import match_kit as MK      # noqa: E402
import triage               # noqa: E402
import llm_match as LM      # noqa: E402

QUEUE = os.path.join(ROOT, "build", "queue.json")
STATE = os.path.join(ROOT, "build", "m26-pipeline-state.json")
TYPES = os.path.join(ROOT, "config", "types.json")
SRC_DIR = os.path.join(ROOT, "src", "functions")
SANDBOX = os.path.join(ROOT, "build", "sandbox")
KNOWN_HARD = os.path.join(ROOT, "build", "m26-known-hard.json")
STALL = os.path.join(ROOT, "docs", "m2-6-stall.md")
OVERRIDES = os.path.join(ROOT, "config", "overrides.json")
MAX_ATTEMPTS = 60


def load_queue():
    return json.load(open(QUEUE, encoding="utf-8"))


def load_state():
    if os.path.exists(STATE):
        return json.load(open(STATE, encoding="utf-8"))
    return {"schema": 1, "batch_no": 0, "processed": [], "tokens_total": 0,
            "gate_history": [], "stalled": False, "current": None,
            "created": time.strftime("%Y-%m-%dT%H:%M:%S%z")}


def save_state(s):
    tmp = STATE + ".tmp"
    json.dump(s, open(tmp, "w", newline="\n", encoding="utf-8"),
              indent=1, ensure_ascii=False)
    os.replace(tmp, STATE)


def claims_doc():
    return json.load(open(os.path.join(ROOT, "build", "claims.json"),
                          encoding="utf-8"))["claims"]


def load_types():
    try:
        return json.load(open(TYPES, encoding="utf-8"))
    except (OSError, ValueError):
        return {"structs": {}}


def field_offsets(text):
    out = set()
    for m in re.finditer(r"0x([0-9A-Fa-f]{1,4})\(\$", text):
        v = int(m.group(1), 16)
        if 0 < v <= 0x1000:
            out.add(v)
    return out


def _offset_of(field):
    oh = field.get("offset_hint")
    if oh is None:
        return None
    if isinstance(oh, int):
        return oh
    m = re.search(r"0x([0-9A-Fa-f]+)", str(oh))
    return int(m.group(1), 16) if m else None


def related_structs(types, body, limit=2):
    offs = set()
    for _a, _w, _mn, ops in body:
        offs |= field_offsets(ops)
    structs = types.get("structs", {}) or {}
    if isinstance(structs, list):
        structs = {st.get("name", "?"): st for st in structs}
    scored = []
    for name, st in structs.items():
        hits = [f for f in (st.get("fields") or []) if _offset_of(f) in offs]
        if hits:
            scored.append((len(hits), name, st, hits))
    scored.sort(key=lambda x: (-x[0], x[1]))
    if scored:
        return [(name, st, hits) for _c, name, st, hits in scored[:limit]]
    top = sorted(structs.items(), key=lambda kv: -len(kv[1].get("fields") or []))[:limit]
    return [(name, st, []) for name, st in top]


def same_shape_src(entry, limit=3):
    cands = []
    try:
        names = sorted(os.listdir(SRC_DIR))
    except OSError:
        return []
    for n in names:
        if not n.endswith(".c"):
            continue
        try:
            addr = int(n[:-2], 16)
        except ValueError:
            continue
        try:
            data = open(os.path.join(SRC_DIR, n), encoding="utf-8",
                        errors="replace").read()
        except OSError:
            continue
        if "FUN_" not in data:
            continue
        cands.append((abs(len(data) - entry["size"]), addr, n, data))
    cands.sort(key=lambda x: (x[0], x[1]))
    return [(n, d) for _s, _a, n, d in cands[:limit]]


_SEM = None


def _sem_index():
    global _SEM
    if _SEM is None:
        try:
            _SEM = json.load(open(os.path.join(ROOT, "build", "m26-semantic.json"),
                                  encoding="utf-8"))["functions"]
        except (OSError, ValueError):
            _SEM = {}
    return _SEM


def _sem_note(addr_i):
    p = os.path.join(ROOT, "build", "m26-semantics", "%08x.md" % addr_i)
    if not os.path.exists(p):
        return ""
    return open(p, encoding="utf-8", errors="replace").read()[:1200]


def _fn_summary(hexaddr, idx):
    rec = idx.get(hexaddr)
    if not rec:
        return None
    out = {"addr": rec.get("addr"), "name": rec.get("name"), "size": rec.get("size"),
           "matched": bool(rec.get("matched")), "features": rec.get("features", [])}
    src = rec.get("source") or ""
    if src and os.path.exists(os.path.join(ROOT, src)):
        out["source_head"] = open(os.path.join(ROOT, src), encoding="utf-8",
                                  errors="replace").read()[:1200]
    note = _sem_note(int(hexaddr, 16))
    if note:
        out["semantic"] = note
    return out


def build_card(entry, body):
    card = {
        "addr": entry["addr"], "addr_i": entry["addr_i"],
        "name": "FUN_%08x" % entry["addr_i"],
        "size": entry["size"], "core": entry["core"],
        "padding": entry["padding"], "tier": entry["tier"], "cls": entry["cls"],
        "flags": entry.get("flags") or [], "sig": entry.get("sig", ""),
        "g": entry.get("g") or ["0"],
        "disassembly": ["0x%08X  %-8s %s" % (a, mn, ops) for a, _w, mn, ops in body],
        "bytes": LM.words_hex(LM.original_bytes(entry["addr_i"], entry["core"])),
        "abi": "leaf args $a0-$a3, return $v0, $ra, $gp=0x002779F0",
        "structs": [], "same_shape_sources": [],
    }
    for name, st, hits in related_structs(load_types(), body):
        card["structs"].append({
            "name": name, "file": st.get("file", ""),
            "fields": [{"name": f.get("name"), "type": f.get("type"),
                        "offset_hint": f.get("offset_hint")} for f in hits[:8]],
        })
    for n, d in same_shape_src(entry):
        card["same_shape_sources"].append({"file": n, "code": d.strip()[:2000]})
    idx = _sem_index()
    rec = idx.get("%08x" % entry["addr_i"], {})
    card["callees"] = [x for x in (_fn_summary(c, idx) for c in rec.get("callees", [])) if x][:8]
    card["callers"] = [x for x in (_fn_summary(c, idx) for c in rec.get("callers", [])) if x][:8]
    mine = set(rec.get("features", []))
    rel = []
    for k, v in idx.items():
        if k == "%08x" % entry["addr_i"] or not v.get("matched"):
            continue
        score = len(mine & set(v.get("features", [])))
        if score:
            rel.append((score, k))
    rel.sort(reverse=True)
    card["related_matched"] = [x for x in (_fn_summary(k, idx) for _s, k in rel[:3]) if x]
    note = _sem_note(entry["addr_i"])
    if note:
        card["semantic"] = note
    return card


def ensure_override(entry, src_rel, g):
    data = {"functions": []}
    if os.path.exists(OVERRIDES):
        try:
            data = json.load(open(OVERRIDES, encoding="utf-8"))
        except ValueError:
            pass
    existing = [f for f in data.get("functions", [])
                if int(str(f["addr"]), 16) == entry["addr_i"]]
    funcs = [f for f in data.get("functions", [])
             if int(str(f["addr"]), 16) != entry["addr_i"]]
    keep_matched = bool(existing and existing[0].get("status") == "matched")
    funcs.append({"addr": entry["addr"], "size": entry["size"],
                  "name": "FUN_%08x" % entry["addr_i"], "source": src_rel,
                  "g": int(g),
                  "status": "matched" if keep_matched else "todo",
                  "note": existing[0].get("note") if keep_matched else "M2.6 pipeline todo"})
    funcs.sort(key=lambda f: int(str(f["addr"]), 16))
    data["functions"] = funcs
    json.dump(data, open(OVERRIDES, "w", newline="\n", encoding="utf-8"),
              indent=2, ensure_ascii=False)


def take_pending(state, limit):
    q = load_queue()
    cd = claims_doc()
    done = set(state.get("processed", []))
    work = []
    for e in q["entries"]:
        if e["addr"] in done:
            continue
        if cd.get(C.canon(e["addr"]), {}).get("result") == "MATCH":
            state["processed"].append(e["addr"])
            continue
        work.append(e)
        if len(work) >= limit:
            break
    return work


def cmd_prepare(args):
    state = load_state()
    byfn = triage.parse_asm(symbols=triage.parse_symbols())
    entries = take_pending(state, args.limit)
    if not entries:
        print("nothing to prepare")
        save_state(state)
        return 0
    claimed = []
    for e in entries:
        try:
            C.claim_one("m26-pipeline", e["addr"], lease=7200)
            claimed.append(e)
        except SystemExit as exc:
            print("  skip", e["addr"], exc)
    entries = claimed
    if not entries:
        save_state(state)
        return 0
    batch_no = state.get("batch_no", 0) + 1
    bdir = os.path.join(ROOT, "build", "m26-batch-%d" % batch_no)
    os.makedirs(bdir, exist_ok=True)
    cards = []
    for e in entries:
        sd = os.path.join(SANDBOX, "%08x" % e["addr_i"])
        os.makedirs(sd, exist_ok=True)
        card = build_card(e, byfn.get(e["addr_i"], []))
        card["sandbox"] = sd.replace("\\", "/")
        card["candidate_path"] = "src/functions/%08x.c" % e["addr_i"]
        card["verify_command"] = "C:/msys64/usr/bin/make.exe overrides"
        card["max_attempts"] = MAX_ATTEMPTS
        card["instructions"] = (
            "Read this card. Write ordinary C to candidate_path (function "
            "FUN_<addr>). Run verify_command and find the line for your address; "
            "Before writing, read build/sandbox/<addr>/attempts.md and build/m26-miss/<addr>.md "
            "if they exist; do not repeat tried variants. "
            "If it is not MATCH, read the diff, fix the C, repeat. Max %d attempts. "
            "No asm/.word/volatile/goto/__attribute__/#include. Do not touch other "
            "functions or run make check." % MAX_ATTEMPTS)
        json.dump(card, open(os.path.join(sd, "card.json"), "w", newline="\n",
                             encoding="utf-8"), indent=1, ensure_ascii=False)
        with open(os.path.join(sd, "notes.md"), "w", newline="\n",
                  encoding="utf-8") as f:
            f.write("# sandbox %s\n\n- card: %s/card.json\n- candidate: %s\n"
                    "- verify: %s\n" % (e["addr"], sd, card["candidate_path"],
                                        card["verify_command"]))
        src_abs = os.path.join(ROOT, card["candidate_path"])
        if not os.path.exists(src_abs):
            os.makedirs(os.path.dirname(src_abs), exist_ok=True)
            with open(src_abs, "w", newline="\n", encoding="utf-8") as f:
                f.write("// FUNCTION: SLPM %s placeholder (worker will replace)\n"
                        "void FUN_%08x(void) { }\n" % (e["addr"], e["addr_i"]))
        ensure_override(e, card["candidate_path"], (e.get("g") or ["0"])[0])
        cards.append(card)
    batch_card = {"schema": 1, "batch": batch_no, "rounds": args.rounds,
                  "max_attempts": MAX_ATTEMPTS, "functions": cards}
    json.dump(batch_card, open(os.path.join(bdir, "card.json"), "w", newline="\n",
                               encoding="utf-8"), indent=1, ensure_ascii=False)
    state["current"] = {"batch": batch_no, "addrs": [e["addr"] for e in entries],
                        "started": time.time(), "card": os.path.join(bdir, "card.json")}
    state["batch_no"] = batch_no
    save_state(state)
    print("prepared batch %d: %d functions" % (batch_no, len(entries)))
    print("batch card:", os.path.join(bdir, "card.json"))
    print("sandboxes:", ", ".join(c["sandbox"] for c in cards[:3]), "...")
    return 0


def cmd_verify(args):
    state = load_state()
    cur = state.get("current")
    if not cur:
        print("no current batch")
        return 1
    batch_no = cur["batch"]
    index = {e["addr_i"]: e for e in load_queue()["entries"]}
    entries = [index[int(a, 16)] for a in cur["addrs"]]
    byfn = triage.parse_asm(symbols=triage.parse_symbols())
    items, slot = [], {}
    for e in entries:
        src_abs = os.path.join(ROOT, "src", "functions", "%08x.c" % e["addr_i"])
        if not os.path.exists(src_abs):
            continue
        try:
            code = open(src_abs, encoding="utf-8", errors="replace").read()
        except OSError:
            continue
        if "FUN_%08x" % e["addr_i"] not in code:
            continue
        if LM.sanitize_candidate(code, e["addr_i"]):
            continue
        key = "%x_00" % e["addr_i"]
        items.append({"key": key, "src": code,
                      "g": int((e.get("g") or ["0"])[0])})
        slot[key] = e
    objs = MK.compile_batch(items, "m26v_%d" % batch_no, verbose=False) if items else {}
    dis = LM.disasm_objects({k: v for k, v in objs.items() if v},
                            "m26v_%d" % batch_no)
    hits = 0
    rows = []
    for e in entries:
        key = "%x_00" % e["addr_i"]
        obj = objs.get(key)
        r = LM.verify(obj, e) if obj else {"ok": False, "summary": "no candidate",
                                           "compiled_len": 0,
                                           "want_len": e["core"] if e["core"] < e["size"] else e["size"]}
        if r.get("ok"):
            core_only = e["core"] < e["size"]
            src_rel = "src/functions/%08x.c" % e["addr_i"]
            note = "M2.6 pipeline: %s%s" % (
                ("core %d/%d" % (e["core"], e["size"])) if core_only else ("%d bytes" % e["size"]),
                "" if core_only else "; g=%d" % int((e.get("g") or ["0"])[0]))
            if core_only:
                LM.record_padded(e, src_rel, note, int((e.get("g") or ["0"])[0]))
            else:
                data = json.load(open(OVERRIDES, encoding="utf-8"))
                for f in data["functions"]:
                    if int(str(f["addr"]), 16) == e["addr_i"]:
                        f["status"] = "matched"
                        f["note"] = note
                json.dump(data, open(OVERRIDES, "w", newline="\n", encoding="utf-8"),
                          indent=2, ensure_ascii=False)
            LM.append_ledger(e, int((e.get("g") or ["0"])[0]), MAX_ATTEMPTS, note)
            try:
                C.complete("m26-pipeline", e["addr"], "MATCH", MAX_ATTEMPTS,
                           note=note, source=src_rel)
            except SystemExit:
                pass
            hits += 1
            rows.append({"addr": e["addr"], "result": "MATCH", "source": src_rel})
            print("  %s MATCH" % e["addr"])
        else:
            diff = "compiled %s/%s: %s" % (r.get("compiled_len"),
                                           r.get("want_len"), r.get("summary", ""))
            sd = os.path.join(SANDBOX, "%08x" % e["addr_i"])
            os.makedirs(sd, exist_ok=True)
            got_lines = (dis.get(key, "") or "").splitlines()
            body = byfn.get(e["addr_i"], [])
            dl = [diff]
            for i, (_a, _w, mn, ops) in enumerate(body[:10]):
                dl.append("want: %-8s %s" % (mn, ops))
                if i < len(got_lines):
                    dl.append("got : %s" % got_lines[i].strip())
            open(os.path.join(sd, "diff.txt"), "w", newline="\n",
                 encoding="utf-8").write("\n".join(dl) + "\n")
            try:
                C.complete("m26-pipeline", e["addr"], "MISS", MAX_ATTEMPTS,
                           note=diff[:300])
            except SystemExit:
                pass
            _archive_miss(e["addr_i"], diff)
            rows.append({"addr": e["addr"], "result": "MISS", "diff": diff[:300]})
            print("  %s MISS  %s" % (e["addr"], diff[:70]))
    # no usable candidate for missing sources
    missing = [e["addr"] for e in entries
               if not os.path.exists(os.path.join(ROOT, "src", "functions",
                                                  "%08x.c" % e["addr_i"]))]
    tested = len(entries)
    rate = hits / float(tested) if tested else 0.0
    doc = {"schema": 1, "phase": "M2.6-pipeline", "batch": batch_no,
           "generated": time.strftime("%Y-%m-%dT%H:%M:%S%z"),
           "functions": tested, "hits": hits, "miss": tested - hits,
           "hit_rate": round(rate, 4), "missing_source": len(missing),
           "elapsed_sec": round(time.time() - cur.get("started", time.time()), 1),
           "max_attempts": MAX_ATTEMPTS, "rows": rows}
    json.dump(doc, open(os.path.join(ROOT, "build", "m26-batch-%d.json" % batch_no),
                        "w", newline="\n", encoding="utf-8"),
              indent=1, ensure_ascii=False)
    state["processed"].extend(e["addr"] for e in entries)
    state["gate_history"].append({"batch": batch_no, "hits": hits,
                                  "tested": tested, "rate": rate, "tokens": 0})
    state["current"] = None
    save_state(state)
    print("batch %d: %d/%d hits (%.1f%%), %d missing source, %.0fs"
          % (batch_no, hits, tested, rate * 100, len(missing), doc["elapsed_sec"]))
    try:
        import subprocess
        exe = "C:/msys64/usr/bin/make.exe"
        if not os.path.exists(exe):
            exe = "make"
        subprocess.run([exe, "progress"], cwd=ROOT, capture_output=True, text=True,
                       encoding="utf-8", errors="replace", timeout=180)
    except Exception:
        pass
    hist = state["gate_history"][-3:]
    if len(hist) == 3 and all(h["tested"] > 0 and h["rate"] < 0.10 for h in hist):
        lines = ["# M2.6 命中率门禁触发", "", "连续 3 批命中率 < 10%：", ""]
        for h in hist:
            lines.append("- batch %s: %d/%d (%.1f%%)" % (h["batch"], h["hits"],
                                                         h["tested"], h["rate"] * 100))
        lines += ["", "处理建议：审查 build/sandbox/ 的证据卡与 diff；修正后删除 "
                  "build/m26-pipeline-state.json 的 gate_history 再 resume。", ""]
        os.makedirs(os.path.dirname(STALL), exist_ok=True)
        open(STALL, "w", newline="\n", encoding="utf-8").write("\n".join(lines) + "\n")
        state["stalled"] = True
        save_state(state)
        print("STALL: wrote docs/m2-6-stall.md")
        return 2
    return 0


def _budget_exhausted(addr_i, limit_attempts=60, limit_min=20):
    """Hard external budget: every check-one counts; refuse after limits."""
    sd = os.path.join(SANDBOX, "%08x" % addr_i)
    os.makedirs(sd, exist_ok=True)
    p = os.path.join(sd, "budget.json")
    now = time.time()
    d = {}
    if os.path.exists(p):
        try:
            d = json.load(open(p, encoding="utf-8"))
        except ValueError:
            d = {}
    if "started" not in d:
        d["started"] = now
    d["attempts"] = int(d.get("attempts", 0)) + 1
    d["updated"] = now
    elapsed = (now - d["started"]) / 60.0
    exhausted = d["attempts"] > limit_attempts or elapsed > limit_min
    with open(p, "w", newline="\n", encoding="utf-8") as f:
        json.dump(d, f)
    print("[budget] attempt %d/%d, elapsed %.1f/%d min" % (
        d["attempts"], limit_attempts, elapsed, limit_min))
    return exhausted


def cmd_check_one(args):
    """Fast single-function check: compile one candidate, match_kit verify (~1-2s)."""
    addr_i = int(str(args.addr), 16)
    if _budget_exhausted(addr_i):
        print("BUDGET EXHAUSTED: stop this function, write its best candidate + last_diff "
              "as MISS in result.json, then move to the next function.")
        return 2
    index = {e["addr_i"]: e for e in load_queue()["entries"]}
    e = index.get(addr_i)
    if not e:
        print("unknown addr", args.addr)
        return 1
    src_abs = os.path.join(ROOT, "src", "functions", "%08x.c" % addr_i)
    if not os.path.exists(src_abs):
        print("MISS no source:", src_abs)
        return 1
    code = open(src_abs, encoding="utf-8", errors="replace").read()
    problems = LM.sanitize_candidate(code, addr_i)
    if problems:
        print("MISS rejected:", ", ".join(problems))
        return 1
    best = None
    for g in (e.get("g") or ["0"]):
        items = [{"key": "one", "src": code, "g": int(g)}]
        objs = MK.compile_batch(items, "check_%x" % addr_i, verbose=False)
        obj = objs.get("one")
        if not obj:
            continue
        rr = LM.verify(obj, e)
        if rr.get("ok"):
            best = (rr, int(g)); break
        if best is None:
            best = (rr, int(g))
    if best is None:
        print("MISS compile failed")
        return 1
    r, used_g = best
    if r.get("ok"):
        print("MATCH g=%d" % used_g)
        return 0
    _note_attempt(addr_i, code, r)
    print("MISS", r.get("summary"))
    if r.get("diffs"):
        first = r["diffs"][0]
        if isinstance(first, tuple) and len(first) >= 3:
            print("first diff at word %s: got %s want %s" % (first[0], first[1], first[2]))
        else:
            print("first diff:", first)
    return 1


def cmd_budget(args):
    """Read-only external clock: attempts, elapsed, remaining (no counting)."""
    addr_i = int(str(args.addr), 16)
    sd = os.path.join(SANDBOX, "%08x" % addr_i)
    p = os.path.join(sd, "budget.json")
    if not os.path.exists(p):
        print("budget: 0/60 attempts, 0.0/20.0 min, remaining 20.0 min")
        return 0
    try:
        d = json.load(open(p, encoding="utf-8"))
    except ValueError:
        d = {}
    now = time.time()
    elapsed = (now - d.get("started", now)) / 60.0
    remaining = max(0.0, 20.0 - elapsed)
    print("budget: %d/60 attempts, %.1f/20.0 min, remaining %.1f min" % (
        int(d.get("attempts", 0)), elapsed, remaining))
    return 0


def cmd_progress(args):
    """progress --addr --json: variants/best_words/insn_ratio/converged/stalled."""
    addr_i = int(str(args.addr), 16)
    key = "%08x" % addr_i
    variants = set()
    n_ticks = 0
    p = os.path.join(ROOT, "build", "compile-tick.log")
    if os.path.exists(p):
        for line in open(p, encoding="utf-8", errors="replace"):
            parts = line.split()
            if len(parts) >= 4 and parts[1] == key:
                n_ticks += 1
                if parts[3]:
                    variants.add(parts[3])
    index = {e["addr_i"]: e for e in load_queue()["entries"]}
    e = index.get(addr_i)
    best = 10 ** 6
    ratio = 0.0
    if e:
        src = os.path.join(ROOT, "src", "functions", key + ".c")
        if os.path.exists(src):
            code = open(src, encoding="utf-8", errors="replace").read()
            if not LM.sanitize_candidate(code, addr_i):
                objs = MK.compile_batch([{"key": "p", "src": code, "g": int((e.get("g") or ["0"])[0])}], "prog_%s" % key, verbose=False)
                obj = objs.get("p")
                if obj:
                    r = LM.verify(obj, e)
                    best = len(r.get("diffs") or [])
                    want = r.get("want_len") or 1
                    ratio = round((r.get("compiled_len") or 0) / float(want), 3)
    converged = len(variants) >= 6 and best <= 15 and 0.95 <= ratio <= 1.05
    stalled = len(variants) >= 6 and best > 15
    abandoned = len(variants) < 6 and best > 15
    out = {"addr": "0x%08X" % addr_i, "variants": len(variants), "ticks": n_ticks,
           "best_words": best if best < 10 ** 6 else None, "insn_ratio": ratio,
           "converged": converged, "stalled": stalled, "abandoned": abandoned}
    print(json.dumps(out, ensure_ascii=False))
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("prepare")
    p.add_argument("--batch", type=int, default=0)
    p.add_argument("--limit", type=int, default=20)
    p.add_argument("--rounds", type=int, default=1)
    p.set_defaults(func=cmd_prepare)
    v = sub.add_parser("verify")
    v.add_argument("--batch", type=int, default=0)
    v.set_defaults(func=cmd_verify)
    b = sub.add_parser("budget")
    b.add_argument("--addr", required=True)
    b.set_defaults(func=cmd_budget)
    pr = sub.add_parser("progress")
    pr.add_argument("--addr", required=True)
    pr.add_argument("--json", action="store_true")
    pr.set_defaults(func=cmd_progress)
    c = sub.add_parser("check-one")
    c.add_argument("--addr", required=True)
    c.set_defaults(func=cmd_check_one)
    s = sub.add_parser("status")
    s.set_defaults(func=lambda a: print(json.dumps(load_state(), ensure_ascii=False, indent=1)))
    args = ap.parse_args(argv)
    return args.func(args)


def _archive_miss(addr_i, diff):
    sd = os.path.join(SANDBOX, "%08x" % addr_i)
    md = os.path.join(ROOT, "build", "m26-miss")
    os.makedirs(md, exist_ok=True)
    lines = ["# %08x MISS" % addr_i, "", "- best: src/functions/%08x.c" % addr_i,
             "- attempts: build/sandbox/%08x/attempts/" % addr_i, "", "## last verify", "",
             "```", diff, "```", ""]
    ap = os.path.join(sd, "attempts.md")
    if os.path.exists(ap):
        rows = open(ap, encoding="utf-8", errors="replace").read().splitlines()
        lines += ["## attempts (last 80)", ""] + rows[-80:] + [""]
    np = os.path.join(sd, "notes.md")
    if os.path.exists(np):
        lines += ["## notes", "```", open(np, encoding="utf-8", errors="replace").read()[:2000], "```"]
    with open(os.path.join(md, "%08x.md" % addr_i), "w", newline="\n", encoding="utf-8") as f:
        f.write("\n".join(lines))


def _note_attempt(addr_i, code, r):
    sd = os.path.join(SANDBOX, "%08x" % addr_i)
    os.makedirs(os.path.join(sd, "attempts"), exist_ok=True)
    h = hashlib.sha1(code.encode("utf-8", "replace")).hexdigest()[:10]
    cp = os.path.join(sd, "attempts", h + ".c")
    if not os.path.exists(cp):
        with open(cp, "w", newline="\n", encoding="utf-8") as f:
            f.write(code)
    with open(os.path.join(sd, "attempts.md"), "a", newline="\n",
              encoding="utf-8") as f:
        f.write("- %s %s %s compiled %s/%s %s\n" % (
            time.strftime("%H:%M:%S"), h, "MATCH" if r.get("ok") else "MISS",
            r.get("compiled_len"), r.get("want_len"), r.get("summary")))


if __name__ == "__main__":
    sys.exit(main())
