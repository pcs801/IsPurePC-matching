#!/usr/bin/env python3
"""tu_batch.py - 20 functions per batch, organized by inferred TU.

prepare  pick up to --limit unmatched functions walking TUs in address order
         (at most --max-per-tu per TU), build a per-TU card + sandboxes, register
         todo overrides, write build/m26-tu-batch-N/meta.json listing the TUs.
verify   batch-compile every selected function, match_kit check, promote hits,
         write build/m26-batch-N.json and run make progress.

No model calls: each TU gets one DSH subagent in the session.

Usage
  python tools/tu_batch.py prepare --limit 20
  python tools/tu_batch.py verify --batch 6
"""
import argparse
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
import pipeline as P        # noqa: E402

TU_FILE = os.path.join(ROOT, "config", "tu_inferred.json")
QUEUE = os.path.join(ROOT, "build", "queue.json")
WORK = os.path.join(ROOT, "build", "m26-tu")
OVERRIDES = os.path.join(ROOT, "config", "overrides.json")
MAX_ATTEMPTS = 60


def slug(name):
    return name.replace("/", "_")


def load_groups():
    return json.load(open(TU_FILE, encoding="utf-8"))["groups"]


def claims_doc():
    return json.load(open(os.path.join(ROOT, "build", "claims.json"),
                          encoding="utf-8"))["claims"]


def queue_index():
    return {e["addr_i"]: e for e in json.load(open(QUEUE, encoding="utf-8"))["entries"]}


def next_batch_no():
    mx = 0
    for n in os.listdir(os.path.join(ROOT, "build")):
        m = re.match(r"m26-batch-(\d+)\.json$", n)
        if m:
            mx = max(mx, int(m.group(1)))
    return mx + 1


def build_tu_dir(g, addrs, index, byfn, ablate=False):
    d = os.path.join(WORK, slug(g["name"]))
    os.makedirs(d, exist_ok=True)
    cards = []
    for a in addrs:
        e = index[a]
        card = P.build_card(e, byfn.get(a, []))
        card["sandbox"] = os.path.join(ROOT, "build", "sandbox", "%08x" % a).replace("\\", "/")
        card["candidate_path"] = "src/functions/%08x.c" % a
        if ablate:
            card.pop("callees", None)
            card.pop("callers", None)
            card.pop("related_matched", None)
            card.pop("semantic", None)
        cards.append(card)
        P.ensure_override(e, card["candidate_path"], (e.get("g") or ["0"])[0])
        src_abs = os.path.join(ROOT, card["candidate_path"])
        if not os.path.exists(src_abs):
            open(src_abs, "w", newline="\n", encoding="utf-8").write(
                "// FUNCTION: SLPM %s placeholder (TU worker will replace)\n"
                "void FUN_%08x(void) { }\n" % (e["addr"], a))
    matched = []
    cd = claims_doc()
    for a in g["addrs"]:
        rec = cd.get("0x%08X" % a, {})
        if rec.get("result") == "MATCH" and rec.get("source"):
            p = os.path.join(ROOT, rec["source"])
            if os.path.exists(p):
                try:
                    matched.append({"file": rec["source"],
                                    "code": open(p, encoding="utf-8", errors="replace").read()[:3000]})
                except OSError:
                    pass
    structs = {}
    for card in cards:
        for s in card.get("structs", []):
            structs.setdefault(s["name"], s)
    tu_card = {
        "schema": 1, "tu": g["name"], "start": g["start"], "end": g["end"],
        "header_hint": {"structs": list(structs.values())[:8],
                        "note": "declare these structs in the TU header if needed"},
        "functions": cards,
        "matched_sources": matched[:6],
        "instructions": (
            "开工前先读 build/sandbox/<addr>/attempts.md 与 build/m26-miss/<addr>.md（若存在），"
        "避开里面已试过的写法。参考 card.callers / card.callees / card.related_matched（含已匹配源码"
        "与 semantic 语义笔记）理解调用契约。按 functions 的地址顺序逐个匹配。每写一版用 "
            "python tools/pipeline.py check-one --addr <addr> 验证；"
            "MATCH 后把最终源码追加到本目录 matched.md，再继续下一个。"
            "后面的函数优先参考 matched.md 里已命中的写法。每函数最多 60 次且最多 20 分钟（先到先停；check-one 会强制计时，超预算直接拒绝编译）；超预算就记 best+last_diff 为 MISS 转下一个；每完成一个函数立即追加 result.json 一条；"
            "禁止 volatile/goto/asm/.word/__attribute__/#include。全部做完写本目录 "
            "result.json：{\"tu\":\"...\",\"functions\":[{\"addr\",\"result\",\"attempts\",\"g\",\"last_diff\"}]}。"
        ),
    }
    json.dump(tu_card, open(os.path.join(d, "card.json"), "w", newline="\n",
                            encoding="utf-8"), indent=1, ensure_ascii=False)
    open(os.path.join(d, "prompt.txt"), "w", newline="\n", encoding="utf-8").write(
        "你是 PS2 MIPS 字节匹配 worker，负责一个 TU 的 %d 个待匹配函数。\n"
        "工作目录：%s\nTU：%s\n证据卡：%s/card.json。先读它。\n"
        "按 card.functions 地址顺序逐个做：写普通 C 到 candidate_path；"
        "运行 python tools/pipeline.py check-one --addr <addr>；MATCH 后追加到 %s/matched.md；"
        "每函数最多 60 次且最多 20 分钟（先到先停），超预算就记 MISS 转下一个、不要死磕；每完成一个函数立即追加 %s/result.json 一条；禁止 volatile/goto/asm/.word/__attribute__/#include；"
        "全部做完后确认 result.json 已含每个函数一条记录。\n"
        % (len(cards), ROOT, g["name"], d, d, d))
    return d, cards


def attempted_addrs():
    """Addresses already attempted in any batch (MATCH or MISS) plus known-hard."""
    out = set()
    import glob
    for fp in glob.glob(os.path.join(ROOT, "build", "m26-batch-*.json")):
        try:
            d = json.load(open(fp, encoding="utf-8"))
            for r in d.get("rows", []):
                out.add(r.get("addr"))
        except (OSError, ValueError):
            pass
    try:
        kh = json.load(open(os.path.join(ROOT, "build", "m26-known-hard.json"),
                            encoding="utf-8"))
        for r in kh.get("functions", []):
            out.add(r.get("addr"))
    except (OSError, ValueError):
        pass
    return out


def cmd_prepare(args):
    groups = sorted(load_groups(), key=lambda g: g["start"])
    cd = claims_doc()
    index = queue_index()
    attempted = attempted_addrs() if not args.retry else set()
    byfn = triage.parse_asm(symbols=triage.parse_symbols())
    batch_no = next_batch_no()
    chosen = []
    total = 0
    if args.addrs:
        for a in [int(x, 16) for x in args.addrs.split(",") if x.strip()]:
            g = next((gg for gg in groups if a in gg["addrs"]), None)
            if not g or any(gg is g for gg, _ in chosen):
                continue
            rem = [x for x in g["addrs"]
                   if cd.get("0x%08X" % x, {}).get("result") != "MATCH"
                   and x in index]
            if not rem:
                continue
            take = [a] + [x for x in rem if x != a][:max(0, args.max_per_tu - 1)]
            take = [x for x in take if x in index]
            chosen.append((g, take))
            total += len(take)
    for g in groups:
        if any(gg is g for gg, _ in chosen):
            continue
        rem = [a for a in g["addrs"]
               if cd.get("0x%08X" % a, {}).get("result") != "MATCH"
               and "0x%08X" % a not in attempted and a in index]
        if not rem:
            continue
        take = rem[:args.max_per_tu]
        if total + len(take) > args.limit:
            take = take[:args.limit - total]
        if not take:
            break
        chosen.append((g, take))
        total += len(take)
        if total >= args.limit:
            break
    bdir = os.path.join(ROOT, "build", "m26-tu-batch-%d" % batch_no)
    os.makedirs(bdir, exist_ok=True)
    metas = []
    ablate_set = set()
    for i, (g, take) in enumerate(chosen):
        abl = bool(args.ablate and i % 2 == 0)
        if abl:
            ablate_set.add(g["name"])
        d, cards = build_tu_dir(g, take, index, byfn, ablate=abl)
        metas.append({"tu": g["name"], "dir": d.replace("\\", "/"),
                      "addrs": [index[a]["addr"] for a in take],
                      "functions": len(take), "ablate": abl})
        print("TU", g["name"], "functions", len(take))
    meta = {"schema": 1, "batch": batch_no, "total": total, "tus": metas,
            "ablate_tus": sorted(ablate_set),
            "created": time.strftime("%Y-%m-%dT%H:%M:%S%z")}
    json.dump(meta, open(os.path.join(bdir, "meta.json"), "w", newline="\n",
                         encoding="utf-8"), indent=1, ensure_ascii=False)
    print("batch", batch_no, "prepared:", total, "functions in", len(metas), "TUs")
    print("meta:", os.path.join(bdir, "meta.json"))
    return 0


def cmd_verify(args):
    bdir = os.path.join(ROOT, "build", "m26-tu-batch-%d" % args.batch)
    meta = json.load(open(os.path.join(bdir, "meta.json"), encoding="utf-8"))
    index = queue_index()
    byfn = triage.parse_asm(symbols=triage.parse_symbols())
    entries = [index[int(a, 16)] for t in meta["tus"] for a in t["addrs"] if int(a, 16) in index]
    items, slot = [], {}
    for e in entries:
        src_abs = os.path.join(ROOT, "src", "functions", "%08x.c" % e["addr_i"])
        if not os.path.exists(src_abs):
            continue
        code = open(src_abs, encoding="utf-8", errors="replace").read()
        if "FUN_%08x" % e["addr_i"] not in code:
            continue
        if LM.sanitize_candidate(code, e["addr_i"]):
            continue
        for gi, g in enumerate(e.get("g") or ["0"]):
            key = "%x_%d" % (e["addr_i"], gi)
            items.append({"key": key, "src": code, "g": int(g)})
            slot[key] = (e, int(g))
    objs = MK.compile_batch(items, "tub_%d" % args.batch, verbose=False) if items else {}
    dis = LM.disasm_objects({k: v for k, v in objs.items() if v}, "tub_%d" % args.batch)
    hits = 0
    core_hits = 0
    rows = []
    for e in entries:
        r = {"ok": False, "summary": "no candidate", "compiled_len": 0,
             "want_len": e["core"] if e["core"] < e["size"] else e["size"]}
        hit_g = int((e.get("g") or ["0"])[0])
        for gi, g in enumerate(e.get("g") or ["0"]):
            key = "%x_%d" % (e["addr_i"], gi)
            if objs.get(key):
                rr = LM.verify(objs[key], e)
                if rr.get("ok"):
                    r = rr; hit_g = int(g); break
                if r.get("compiled_len") == 0:
                    r = rr
        if r.get("ok"):
            core_only = e["core"] < e["size"]
            src_rel = "src/functions/%08x.c" % e["addr_i"]
            note = "M2.6 TU-batch %d: %s" % (
                args.batch, ("core %d/%d" % (e["core"], e["size"])) if core_only
                else ("%d bytes" % e["size"]))
            if core_only:
                core_hits += 1
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
                C.complete("m26-tub", e["addr"], "MATCH", MAX_ATTEMPTS, note=note, source=src_rel)
            except SystemExit:
                pass
            hits += 1
            rows.append({"addr": e["addr"], "result": "MATCH", "source": src_rel})
            print("  %s MATCH" % e["addr"])
        else:
            diff = "compiled %s/%s: %s" % (r.get("compiled_len"), r.get("want_len"),
                                           r.get("summary", ""))
            try:
                C.complete("m26-tub", e["addr"], "MISS", MAX_ATTEMPTS, note=diff[:300])
            except SystemExit:
                pass
            P._archive_miss(e["addr_i"], diff)
            rows.append({"addr": e["addr"], "result": "MISS", "diff": diff[:300]})
            print("  %s MISS  %s" % (e["addr"], diff[:70]))
    tested = len(entries)
    rate = hits / float(tested) if tested else 0.0
    doc = {"schema": 1, "phase": "M2.6-pipeline", "batch": args.batch,
           "mode": "tu", "functions": tested, "hits": hits, "core_only_hits": core_hits,
           "miss": tested - hits,
           "hit_rate": round(rate, 4),
           "generated": time.strftime("%Y-%m-%dT%H:%M:%S%z"), "rows": rows}
    json.dump(doc, open(os.path.join(ROOT, "build", "m26-batch-%d.json" % args.batch),
                        "w", newline="\n", encoding="utf-8"), indent=1, ensure_ascii=False)
    json.dump(doc, open(os.path.join(bdir, "verify.json"), "w", newline="\n",
                        encoding="utf-8"), indent=1, ensure_ascii=False)
    print("batch %d (TU mode): %d/%d hits (%.1f%%)" % (args.batch, hits, tested, rate * 100))
    try:
        import subprocess
        exe = "C:/msys64/usr/bin/make.exe"
        if not os.path.exists(exe):
            exe = "make"
        subprocess.run([exe, "progress"], cwd=ROOT, capture_output=True, text=True,
                       encoding="utf-8", errors="replace", timeout=180)
    except Exception:
        pass
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("prepare")
    p.add_argument("--limit", type=int, default=20)
    p.add_argument("--max-per-tu", type=int, default=3)
    p.add_argument("--addrs", default="",
                   help="priority addresses (comma separated), placed first")
    p.add_argument("--ablate", action="store_true",
                   help="A/B: half the TUs get no semantic context")
    p.add_argument("--retry", action="store_true",
                   help="re-include already attempted (MISS) functions")
    p.set_defaults(func=cmd_prepare)
    v = sub.add_parser("verify")
    v.add_argument("--batch", type=int, required=True)
    v.set_defaults(func=cmd_verify)
    args = ap.parse_args(argv)
    return args.func(args)


if __name__ == "__main__":
    sys.exit(main())
