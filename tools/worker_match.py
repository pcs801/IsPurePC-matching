#!/usr/bin/env python3
"""worker_match.py - M2.6 per-function LLM worker.

One function, one sandbox: build/sandbox/<addr>/ holds the evidence card, each
round's candidate C, the LLM reply and the diff.  Pipeline per function:
evidence card -> LLM (1-2 candidates) -> match_kit relocation-aware byte check ->
diff fed back into the next round.  Up to 60 attempts per function.

Batch runner: 80 functions per batch; after each batch it writes
build/m26-batch-N.json, appends the ledger on hits, and runs make progress.

Three safety nets (docs/m2-6-decision.md):
  1. hit-rate gate: 3 consecutive batches with hit rate < 10% -> write
     docs/m2-6-stall.md and stop.
  2. token caps: 100M per batch, 5.0B total.
  3. stop-loss: 60 attempts per function -> known-hard, never blocks the queue.

State: build/m26-state.json (resume across runs; processed addresses, batch
number, token totals, gate history).

Usage
  python tools/worker_match.py --limit 80
  python tools/worker_match.py --resume --limit 0
  python tools/worker_match.py --dry-run
"""
import argparse
import json
import os
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

import claims as C          # noqa: E402
import match_kit as MK      # noqa: E402
import triage               # noqa: E402
import llm_match as LM      # noqa: E402

M26_QUEUE = os.path.join(ROOT, "build", "m26-queue.json")
STATE_FILE = os.path.join(ROOT, "build", "m26-state.json")
SANDBOX = os.path.join(ROOT, "build", "sandbox")
KNOWN_HARD = os.path.join(ROOT, "build", "m26-known-hard.json")
STALL_DOC = os.path.join(ROOT, "docs", "m2-6-stall.md")
BATCH_BUDGET = 100_000_000
TOTAL_BUDGET = 5_000_000_000
MAX_CAND = 2


class FnState:
    def __init__(self, entry, body):
        self.entry = entry
        self.body = body
        self.history = []
        self.attempts = 0
        self.patience = 0
        self.hit = None
        self.tokens_in = 0
        self.tokens_out = 0
        self.rounds = 0
        self.note = ""
        self.result = None
        self.source = ""
        self.started = time.time()
        self.sandbox = os.path.join(SANDBOX, "%08x" % entry["addr_i"])
        os.makedirs(self.sandbox, exist_ok=True)

    def add_usage(self, usage):
        self.tokens_in += int(usage.get("input_tokens", 0) or 0)
        self.tokens_out += int(usage.get("output_tokens", 0) or 0)


def load_state():
    if os.path.exists(STATE_FILE):
        with open(STATE_FILE, encoding="utf-8") as f:
            return json.load(f)
    return {"schema": 1, "created": time.strftime("%Y-%m-%dT%H:%M:%S%z"),
            "batch_no": 0, "processed": [], "known_hard": [],
            "tokens_total": 0, "gate_history": [], "stalled": False}


def save_state(state):
    tmp = STATE_FILE + ".tmp"
    with open(tmp, "w", newline="\n", encoding="utf-8") as f:
        json.dump(state, f, indent=1, ensure_ascii=False)
        f.write("\n")
    os.replace(tmp, STATE_FILE)


def write_known_hard(entry, attempts, note):
    doc = {"schema": 1, "functions": []}
    if os.path.exists(KNOWN_HARD):
        try:
            with open(KNOWN_HARD, encoding="utf-8") as f:
                doc = json.load(f)
        except ValueError:
            pass
    rows = [r for r in doc.get("functions", []) if r.get("addr") != entry["addr"]]
    rows.append({"addr": entry["addr"], "size": entry["size"],
                 "flags": entry.get("flags"), "attempts": attempts,
                 "note": note[:300]})
    rows.sort(key=lambda r: int(r["addr"], 16))
    doc["functions"] = rows
    with open(KNOWN_HARD, "w", newline="\n", encoding="utf-8") as f:
        json.dump(doc, f, indent=1, ensure_ascii=False)
        f.write("\n")


def write_stall(batch_no, rate, history):
    lines = [
        "# M2.6 命中率门禁触发（stall）",
        "",
        "> 时间：%s" % time.strftime("%Y-%m-%d %H:%M:%S"),
        "> 规则：连续 3 批命中率 < 10% → 自动暂停（docs/m2-6-decision.md 保险 1）",
        "",
        "## 最近 3 批",
        "",
        "| 批 | 命中/处理 | 命中率 | token |",
        "|---|---|---|---|",
    ]
    for h in history[-3:]:
        lines.append("| %s | %d/%d | %.1f%% | %d |" % (
            h.get("batch"), h.get("hits", 0), h.get("tested", 0),
            h.get("rate", 0) * 100, h.get("tokens", 0)))
    lines += ["", "## 处理建议", "",
              "1. 先审查最近 3 批的 known-hard 与证据卡（build/sandbox/）；",
              "2. 若提示词/模型确实无效，停止全量，回到程序化生成器；",
              "3. 修复后删除 build/m26-state.json 的 gate_history 再 resume。",
              ""]
    os.makedirs(os.path.dirname(STALL_DOC), exist_ok=True)
    with open(STALL_DOC, "w", newline="\n", encoding="utf-8") as f:
        f.write("\n".join(lines) + "\n")


def extract_candidates(doc, entry):
    out = []
    for item in doc.get("functions", []):
        try:
            if int(str(item.get("addr", "")), 16) != entry["addr_i"]:
                continue
        except ValueError:
            continue
        raw = item.get("candidates", [])
        if isinstance(raw, (str, dict)):
            raw = [raw]
        for c in raw[:MAX_CAND]:
            if isinstance(c, str):
                code, g = c, None
            elif isinstance(c, dict):
                code, g = c.get("code", ""), c.get("g")
            else:
                continue
            if not isinstance(code, str) or "FUN_" not in code:
                continue
            if LM.sanitize_candidate(code, entry["addr_i"]):
                continue
            if g is None:
                g = (entry.get("g") or ["0"])[0]
            try:
                g = int(g)
            except (TypeError, ValueError):
                g = int((entry.get("g") or ["0"])[0])
            out.append({"code": code, "g": g})
    return out


def save_round_sandbox(fn, round_no, reply_text, cands, r, first):
    d = fn.sandbox
    try:
        with open(os.path.join(d, "card.txt"), "w", newline="\n", encoding="utf-8") as f:
            f.write(LM.evidence_card(fn.entry, fn.body, history=fn.history[-6:]))
        with open(os.path.join(d, "round-%02d-reply.json" % round_no), "w", newline="\n",
                  encoding="utf-8") as f:
            f.write(reply_text[:200000])
        for ci, c in enumerate(cands):
            with open(os.path.join(d, "round-%02d-cand-%d.c" % (round_no, ci)), "w",
                      newline="\n", encoding="utf-8") as f:
                f.write(c["code"])
        with open(os.path.join(d, "round-%02d-diff.txt" % round_no), "w", newline="\n",
                  encoding="utf-8") as f:
            f.write("%s\n" % (first or r.get("summary", "")))
    except OSError:
        pass


def write_back(fn, cand, g, attempts, core_only):
    entry = fn.entry
    src_rel = LM.write_source(entry, cand["code"], "worker_match M2.6 attempts=%d" % attempts)
    note = "M2.6 worker: %s%s" % (
        ("core %d/%d" % (entry["core"], entry["size"])) if core_only else ("%d bytes" % entry["size"]),
        "" if core_only else "; g=%d" % g)
    if core_only:
        LM.record_padded(entry, src_rel, note, g)
    else:
        LM.update_overrides(entry, src_rel, note, g)
    LM.append_ledger(entry, g, attempts, note)
    try:
        C.complete("m26-worker", entry["addr"], "MATCH", attempts, note=note, source=src_rel)
    except SystemExit as exc:
        print("  claim complete failed", entry["addr"], exc)
    fn.result = "MATCH_CORE" if core_only else "MATCH"
    fn.source = src_rel
    return fn.result


def run_group(cfg, group, args, batch_no, batch_tokens):
    pending = [fn for fn in group if not fn.hit]
    round_no = 0
    while pending and round_no < args.max_attempts:
        send = [fn for fn in pending
                if fn.attempts < args.max_attempts and fn.patience < args.patience]
        if not send:
            break
        round_no += 1
        cards = [LM.evidence_card(fn.entry, fn.body, history=fn.history[-6:]) for fn in send]
        user = (LM.USER_INSTRUCTIONS % len(send) + "\n\n" + "\n\n".join(cards))
        try:
            reply = LM.llm_call(cfg, LM.SYSTEM_PROMPT, user,
                                max_tokens=args.max_tokens, timeout=args.timeout)
        except Exception as exc:
            for fn in send:
                fn.patience += 1
                fn.note = "llm error: %s" % str(exc)[:200]
            print("  llm error in group: %s" % str(exc)[:120])
            continue
        usage = reply.get("usage", {})
        for fn in send:
            fn.add_usage(usage)
        batch_tokens[0] += int(usage.get("input_tokens", 0) or 0) + int(usage.get("output_tokens", 0) or 0)
        try:
            doc = LM.parse_reply(reply["text"])
        except Exception:
            doc = {"functions": []}
        items, slot = [], {}
        round_cands = {}
        for fn in send:
            fn.attempts += 1
            fn.rounds = round_no
            cands = extract_candidates(doc, fn.entry)
            round_cands[fn.entry["addr"]] = cands
            if not cands:
                fn.patience += 1
                fn.history.append({"round": round_no, "g": None,
                                   "summary": "no usable candidate"})
                continue
            for ci, c in enumerate(cands):
                gs = [c["g"]] + [int(g) for g in (fn.entry.get("g") or ["0"]) if int(g) != c["g"]]
                for g in gs:
                    key = "%x_%d_%d_%d" % (fn.entry["addr_i"], round_no, ci, g)
                    items.append({"key": key, "src": c["code"], "g": g})
                    slot[key] = (fn, ci, g, c)
        if items:
            tag = "m26_%d_%02d" % (batch_no, round_no)
            objs = MK.compile_batch(items, tag, verbose=False)
            for key, (fn, ci, g, c) in slot.items():
                obj = objs.get(key)
                if not obj:
                    continue
                r = LM.verify(obj, fn.entry)
                if r["ok"]:
                    if not fn.hit:
                        core_only = fn.entry["core"] < fn.entry["size"]
                        fn.hit = {"cand": c, "g": g, "core_only": core_only, "r": r}
                        save_round_sandbox(fn, round_no, reply["text"],
                                           round_cands[fn.entry["addr"]], r, None)
                        write_back(fn, c, g, fn.attempts, core_only)
                        print("    %s %3dB MATCH r%d g=%d" % (
                            fn.entry["addr"], fn.entry["size"], round_no, g))
                    break
            for fn in send:
                if fn.hit:
                    continue
                # record the closest diff for this round
                shown = None
                for key, (f2, ci, g, c) in slot.items():
                    if f2 is fn:
                        rr = LM.verify(objs.get(key), fn.entry) if objs.get(key) else None
                        if rr and shown is None:
                            shown = rr.get("summary")
                        break
                fn.history.append({"round": round_no, "g": None,
                                   "summary": shown or "no object"})
                fn.patience += 1
                save_round_sandbox(fn, round_no, reply["text"],
                                   round_cands.get(fn.entry["addr"], []), {}, shown)
        pending = [fn for fn in pending if not fn.hit]
    return round_no


def skipped_match(entry, claims_doc):
    rec = claims_doc.get(C.canon(entry["addr"]), {})
    return rec.get("result") == "MATCH"


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--limit", type=int, default=80,
                    help="functions to process this run (0 = all)")
    ap.add_argument("--batch-size", type=int, default=80)
    ap.add_argument("--group-size", type=int, default=4)
    ap.add_argument("--max-attempts", type=int, default=60)
    ap.add_argument("--patience", type=int, default=8,
                    help="give up after N consecutive rounds without a match")
    ap.add_argument("--max-tokens", type=int, default=6000)
    ap.add_argument("--timeout", type=int, default=60)
    ap.add_argument("--stream", default="on", choices=["on", "off"])
    ap.add_argument("--thinking", default="off", choices=["off", "auto"])
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--reset-state", action="store_true")
    args = ap.parse_args(argv)

    if args.reset_state and os.path.exists(STATE_FILE):
        os.remove(STATE_FILE)
    if not os.path.exists(M26_QUEUE):
        raise SystemExit("run tools/m26_queue.py first")
    q = json.load(open(M26_QUEUE, encoding="utf-8"))
    entries = q["entries"]
    if args.dry_run:
        print("queue", len(entries), "groups", q["groups"])
        for e in entries[:10]:
            print(" ", e["addr"], "g%d" % e["group"], e["size"], e["cls"])
        return 0

    class A:
        api_url = None
        api_key = None
        model = None
        session = None
        thinking = args.thinking
        thinking_budget = 3000
        stream = args.stream
    cfg = LM.resolve_llm_cfg(A())
    print("worker llm:", cfg["base_url"], cfg["model"], "thinking", cfg["thinking"])
    byfn = triage.parse_asm(symbols=triage.parse_symbols())
    state = load_state()
    cdoc = json.load(open(os.path.join(ROOT, "build", "claims.json"), encoding="utf-8"))
    processed = set(state.get("processed", []))
    print("state: batch_no=%d processed=%d tokens=%.1fM"
          % (state["batch_no"], len(processed), state["tokens_total"] / 1e6))

    work = []
    for e in entries:
        if e["addr"] in processed:
            continue
        if skipped_match(e, cdoc["claims"]):
            state["processed"].append(e["addr"])
            continue
        work.append(e)
        if args.limit and len(work) >= args.limit:
            break
    if not work:
        print("nothing to do")
        save_state(state)
        return 0
    print("this run: %d function(s)" % len(work))

    total_t0 = time.time()
    index = 0
    while index < len(work):
        state["batch_no"] += 1
        batch_no = state["batch_no"]
        batch = work[index:index + args.batch_size]
        index += len(batch)
        print("\n== batch %d: %d function(s) ==" % (batch_no, len(batch)))
        fn_states = []
        claimed = []
        for e in batch:
            fn = FnState(e, byfn.get(e["addr_i"], []))
            fn_states.append(fn)
            try:
                C.claim_one("m26-worker", e["addr"], lease=7200)
                claimed.append(fn)
            except SystemExit as exc:
                fn.result = "SKIP"
                fn.note = str(exc)[:200]
        batch_tokens = [0]
        batch_t0 = time.time()
        groups = [claimed[i:i + args.group_size]
                  for i in range(0, len(claimed), args.group_size)]
        for gi, group in enumerate(groups):
            if batch_tokens[0] >= BATCH_BUDGET:
                print("  batch token cap reached; stopping this batch")
                break
            if state["tokens_total"] + batch_tokens[0] >= TOTAL_BUDGET:
                print("  total token budget reached")
                break
            run_group(cfg, group, args, batch_no, batch_tokens)
            print("  group %d/%d done, tokens %.1fM"
                  % (gi + 1, len(groups), batch_tokens[0] / 1e6))
        # finalize batch
        rows = []
        hits = core = miss = skip = known = 0
        for fn in fn_states:
            if fn.hit:
                rows.append({"addr": fn.entry["addr"], "result": fn.result,
                             "attempts": fn.attempts, "rounds": fn.rounds,
                             "tokens_in": fn.tokens_in, "tokens_out": fn.tokens_out,
                             "source": fn.source})
                if fn.result == "MATCH_CORE":
                    core += 1
                else:
                    hits += 1
            elif fn.result == "SKIP":
                skip += 1
                rows.append({"addr": fn.entry["addr"], "result": "SKIP",
                             "note": fn.note})
            else:
                known_hard = (fn.attempts >= args.max_attempts
                              or fn.patience >= args.patience)
                note = ("known-hard: attempts=%d patience=%d %s"
                        % (fn.attempts, fn.patience, fn.note))
                try:
                    C.complete("m26-worker", fn.entry["addr"], "MISS",
                               fn.attempts, note=note[:300])
                except SystemExit:
                    pass
                if known_hard:
                    write_known_hard(fn.entry, fn.attempts, note)
                    known += 1
                    result = "KNOWN_HARD"
                else:
                    result = "MISS"
                miss += 1
                rows.append({"addr": fn.entry["addr"], "result": result,
                             "attempts": fn.attempts, "rounds": fn.rounds,
                             "tokens_in": fn.tokens_in, "tokens_out": fn.tokens_out,
                             "note": note[:200]})
        tested = hits + core + miss
        rate = (hits + core) / float(tested) if tested else 0.0
        batch_doc = {
            "schema": 1, "phase": "M2.6", "batch": batch_no,
            "generated": time.strftime("%Y-%m-%dT%H:%M:%S%z"),
            "functions": len(fn_states), "tested": tested,
            "hits": hits + core, "byte_exact": hits, "core_only": core,
            "miss": miss, "known_hard": known, "skipped": skip,
            "hit_rate": round(rate, 4),
            "tokens_in": sum(fn.tokens_in for fn in fn_states),
            "tokens_out": sum(fn.tokens_out for fn in fn_states),
            "elapsed_sec": round(time.time() - batch_t0, 1),
            "rows": rows,
        }
        path = os.path.join(ROOT, "build", "m26-batch-%d.json" % batch_no)
        with open(path, "w", newline="\n", encoding="utf-8") as f:
            json.dump(batch_doc, f, indent=1, ensure_ascii=False)
            f.write("\n")
        state["tokens_total"] += batch_tokens[0]
        state["processed"].extend(fn.entry["addr"] for fn in fn_states if fn.result != "SKIP"
                                  or True)
        state["gate_history"].append({"batch": batch_no, "hits": hits + core,
                                      "tested": tested, "rate": rate,
                                      "tokens": batch_tokens[0]})
        save_state(state)
        print("batch %d done: %d/%d hits (%.1f%%), %d known-hard, %.1fM tokens, %.0fs"
              % (batch_no, hits + core, tested, rate * 100, known,
                 batch_tokens[0] / 1e6, time.time() - batch_t0))
        try:
            import subprocess
            exe = "C:/msys64/usr/bin/make.exe"
            if not os.path.exists(exe):
                exe = "make"
            subprocess.run([exe, "progress"], cwd=ROOT, capture_output=True,
                           text=True, encoding="utf-8", errors="replace", timeout=180)
        except Exception as exc:
            print("  make progress failed:", exc)
        # safety net 1: 3 consecutive low-hit batches
        hist = state["gate_history"][-3:]
        if len(hist) == 3 and all(h["tested"] > 0 and h["rate"] < 0.10 for h in hist):
            write_stall(batch_no, rate, state["gate_history"])
            state["stalled"] = True
            save_state(state)
            print("STALL: 3 consecutive batches <10%; wrote docs/m2-6-stall.md")
            return 2
        if state["tokens_total"] >= TOTAL_BUDGET:
            print("total token budget reached; stopping")
            return 3

    print("\nworker run done: %d function(s), %.1fM tokens, %.0fs"
          % (len(work), state["tokens_total"] / 1e6, time.time() - total_t0))
    return 0


if __name__ == "__main__":
    sys.exit(main())
