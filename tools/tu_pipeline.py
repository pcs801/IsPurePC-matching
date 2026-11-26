#!/usr/bin/env python3
"""tu_pipeline.py - M2.6 TU-level pipeline.

One translation unit, one subagent.  The card is per-TU: all functions in the
unit with their disassembly/bytes, related structs from config/types.json, and
the sources of functions already matched in this unit.  The subagent walks the
unit in address order, writes C for each function, uses check-one to verify, and
appends each matched source to matched.md so later functions can follow the same
style.

Deterministic commands only (no model calls):
  prepare --tu <name>          build the TU card + sandboxes + todo overrides
  verify  --tu <name>          batch-compile the unit, match_kit check, bookkeep

Usage
  python tools/tu_pipeline.py prepare --limit 3
  python tools/tu_pipeline.py verify --tu tu/00117760
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
QUEUE = os.path.join(ROOT, "build", "m26-queue.json")
STATE = os.path.join(ROOT, "build", "m26-tu-state.json")
WORK = os.path.join(ROOT, "build", "m26-tu")
OVERRIDES = os.path.join(ROOT, "config", "overrides.json")
MAX_ATTEMPTS = 60


def load_state():
    if os.path.exists(STATE):
        return json.load(open(STATE, encoding="utf-8"))
    return {"schema": 1, "tu_done": [], "created": time.strftime("%Y-%m-%dT%H:%M:%S%z")}


def save_state(s):
    tmp = STATE + ".tmp"
    json.dump(s, open(tmp, "w", newline="\n", encoding="utf-8"), indent=1, ensure_ascii=False)
    os.replace(tmp, STATE)


def slug(name):
    return name.replace("/", "_")


def load_groups():
    return json.load(open(TU_FILE, encoding="utf-8"))["groups"]


def claims_doc():
    return json.load(open(os.path.join(ROOT, "build", "claims.json"),
                          encoding="utf-8"))["claims"]


def cmd_prepare(args):
    groups = load_groups()
    cd = claims_doc()
    index = {}
    for e in json.load(open(QUEUE, encoding="utf-8"))["entries"]:
        index[e["addr_i"]] = e
    state = load_state()
    picked = []
    if args.tu:
        metas = [g for g in groups if g["name"] == args.tu]
    else:
        metas = []
        for g in groups:
            if g["name"] in state.get("tu_done", []):
                continue
            rem = [a for a in g["addrs"] if cd.get("0x%08X" % a, {}).get("result") != "MATCH"]
            if args.min_rem <= len(rem) <= args.max_rem:
                metas.append(g)
        metas.sort(key=lambda g: (len([a for a in g["addrs"]
                                       if cd.get("0x%08X" % a, {}).get("result") != "MATCH"]),
                                  g["start"]))
        metas = metas[:args.limit]
    byfn = triage.parse_asm(symbols=triage.parse_symbols())
    for g in metas:
        rem = [a for a in g["addrs"] if cd.get("0x%08X" % a, {}).get("result") != "MATCH"]
        rem = [a for a in rem if a in index]
        if not rem:
            continue
        sl = slug(g["name"])
        d = os.path.join(WORK, sl)
        os.makedirs(d, exist_ok=True)
        cards = []
        for a in rem:
            e = index[a]
            body = byfn.get(a, [])
            card = P.build_card(e, body)
            card["sandbox"] = os.path.join(ROOT, "build", "sandbox", "%08x" % a).replace("\\", "/")
            card["candidate_path"] = "src/functions/%08x.c" % a
            cards.append(card)
            P.ensure_override(e, card["candidate_path"],
                              (e.get("g") or ["0"])[0])
            src_abs = os.path.join(ROOT, card["candidate_path"])
            if not os.path.exists(src_abs):
                open(src_abs, "w", newline="\n", encoding="utf-8").write(
                    "// FUNCTION: SLPM %s placeholder (TU worker will replace)\n"
                    "void FUN_%08x(void) { }\n" % (e["addr"], a))
        # already matched functions in this unit: source context
        matched = []
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
            "confidence": g.get("confidence"),
            "header_hint": {"structs": list(structs.values())[:8],
                            "note": "declare these structs in the TU header if needed"},
            "functions": cards,
            "matched_sources": matched[:6],
            "instructions": (
                "按 functions 的地址顺序逐个匹配。每写一版用 "
                "python tools/pipeline.py check-one --addr <addr> 验证；"
                "MATCH 后把最终源码追加到本目录 matched.md，再继续下一个。"
                "后面的函数优先参考 matched.md 里已命中的写法（类型、语句顺序、"
                "extern D_ 符号、延迟槽安排）。每函数最多 60 次，禁止 volatile/goto/"
                "asm/.word/__attribute__/#include。全部做完后把每函数结果写入本目录 "
                "result.json：{\"tu\":\"...\",\"functions\":[{\"addr\",\"result\",\"attempts\",\"g\",\"last_diff\"}]}。"
            ),
        }
        json.dump(tu_card, open(os.path.join(d, "card.json"), "w", newline="\n",
                                encoding="utf-8"), indent=1, ensure_ascii=False)
        open(os.path.join(d, "prompt.txt"), "w", newline="\n", encoding="utf-8").write(
            "你是 PS2 MIPS 字节匹配 worker，负责一个翻译单元（TU）。\n"
            "工作目录：%s\nTU：%s（%d 个待匹配函数）\n"
            "证据卡：%s/card.json（按 TU 生成：函数反汇编/字节、types.json 相关结构体、"
            "本 TU 已匹配源码）。先读它。\n"
            "按 card.functions 的地址顺序逐个做：\n"
            "1. 写普通 C 到 card.functions[i].candidate_path，函数名 FUN_<addr>；\n"
            "2. 运行 python tools/pipeline.py check-one --addr <addr>，MATCH 即过；MISS 看第一处指令差异继续改；\n"
            "3. 每命中一个，把最终源码追加到 %s/matched.md，后面的函数参考它；\n"
            "4. 每函数最多 60 次；禁止 volatile/goto/asm/.word/__attribute__/#include；\n"
            "5. 全部做完写 %s/result.json（每函数 addr/result/attempts/g/last_diff）。\n"
            % (ROOT, g["name"], len(rem), d, d, d))
        state.setdefault("prepared", []).append(g["name"])
        print("prepared", g["name"], "unmatched", len(rem), "dir", d)
    save_state(state)
    return 0


def cmd_verify(args):
    state = load_state()
    groups = load_groups()
    metas = [g for g in groups if g["name"] == args.tu]
    if not metas:
        print("unknown TU", args.tu)
        return 1
    g = metas[0]
    cd = claims_doc()
    index = {}
    for e in json.load(open(QUEUE, encoding="utf-8"))["entries"]:
        index[e["addr_i"]] = e
    rem = [a for a in g["addrs"] if cd.get("0x%08X" % a, {}).get("result") != "MATCH"]
    rem = [a for a in rem if a in index]
    byfn = triage.parse_asm(symbols=triage.parse_symbols())
    items, slot = [], {}
    for a in rem:
        src_abs = os.path.join(ROOT, "src", "functions", "%08x.c" % a)
        if not os.path.exists(src_abs):
            continue
        code = open(src_abs, encoding="utf-8", errors="replace").read()
        if "FUN_%08x" % a not in code:
            continue
        if LM.sanitize_candidate(code, a):
            continue
        key = "%x_00" % a
        items.append({"key": key, "src": code, "g": int((index[a].get("g") or ["0"])[0])})
        slot[key] = a
    objs = MK.compile_batch(items, "tu_%s" % slug(g["name"]), verbose=False) if items else {}
    dis = LM.disasm_objects({k: v for k, v in objs.items() if v}, "tu_%s" % slug(g["name"]))
    hits = 0
    rows = []
    for a in rem:
        e = index[a]
        obj = objs.get("%x_00" % a)
        r = LM.verify(obj, e) if obj else {"ok": False, "summary": "no candidate",
                                           "compiled_len": 0,
                                           "want_len": e["core"] if e["core"] < e["size"] else e["size"]}
        if r.get("ok"):
            core_only = e["core"] < e["size"]
            src_rel = "src/functions/%08x.c" % a
            note = "M2.6 TU %s: %s" % (g["name"], ("core %d/%d" % (e["core"], e["size"]))
                                       if core_only else ("%d bytes" % e["size"]))
            if core_only:
                LM.record_padded(e, src_rel, note, int((e["g"] or ["0"])[0]))
            else:
                data = json.load(open(OVERRIDES, encoding="utf-8"))
                for f in data["functions"]:
                    if int(str(f["addr"]), 16) == a:
                        f["status"] = "matched"
                        f["note"] = note
                json.dump(data, open(OVERRIDES, "w", newline="\n", encoding="utf-8"),
                          indent=2, ensure_ascii=False)
            LM.append_ledger(e, int((e["g"] or ["0"])[0]), MAX_ATTEMPTS, note)
            try:
                C.complete("m26-tu", e["addr"], "MATCH", MAX_ATTEMPTS, note=note, source=src_rel)
            except SystemExit:
                pass
            hits += 1
            rows.append({"addr": e["addr"], "result": "MATCH", "source": src_rel})
            print("  %s MATCH" % e["addr"])
        else:
            diff = "compiled %s/%s: %s" % (r.get("compiled_len"), r.get("want_len"),
                                           r.get("summary", ""))
            try:
                C.complete("m26-tu", e["addr"], "MISS", MAX_ATTEMPTS, note=diff[:300])
            except SystemExit:
                pass
            rows.append({"addr": e["addr"], "result": "MISS", "diff": diff[:300]})
            print("  %s MISS  %s" % (e["addr"], diff[:70]))
    tested = len(rem)
    rate = hits / float(tested) if tested else 0.0
    doc = {"schema": 1, "phase": "M2.6-tu", "tu": g["name"],
           "generated": time.strftime("%Y-%m-%dT%H:%M:%S%z"),
           "functions": tested, "hits": hits, "miss": tested - hits,
           "hit_rate": round(rate, 4), "rows": rows}
    d = os.path.join(WORK, slug(g["name"]))
    os.makedirs(d, exist_ok=True)
    json.dump(doc, open(os.path.join(d, "verify.json"), "w", newline="\n",
                        encoding="utf-8"), indent=1, ensure_ascii=False)
    json.dump(doc, open(os.path.join(ROOT, "build", "m26-tu-%s.json" % slug(g["name"])),
                        "w", newline="\n", encoding="utf-8"), indent=1, ensure_ascii=False)
    state.setdefault("tu_done", []).append(g["name"])
    save_state(state)
    print("TU %s: %d/%d hits (%.1f%%)" % (g["name"], hits, tested, rate * 100))
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
    p.add_argument("--tu", default=None)
    p.add_argument("--limit", type=int, default=3)
    p.add_argument("--min-rem", type=int, default=1)
    p.add_argument("--max-rem", type=int, default=3)
    p.set_defaults(func=cmd_prepare)
    v = sub.add_parser("verify")
    v.add_argument("--tu", required=True)
    v.set_defaults(func=cmd_verify)
    s = sub.add_parser("status")
    s.set_defaults(func=lambda a: print(json.dumps(load_state(), ensure_ascii=False, indent=1)))
    args = ap.parse_args(argv)
    return args.func(args)


if __name__ == "__main__":
    sys.exit(main())
