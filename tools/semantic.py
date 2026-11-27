#!/usr/bin/env python3
"""semantic.py - call graph + instruction-shape features + short semantic cards.

Reads build/queue.json, config/overrides.json, asm via triage.parse_asm and
writes build/m26-semantic.json:
  { "functions": { "<08x>": {name,size,callers,callees,features,source,matched} } }

No model calls; explainer notes are stored separately in build/m26-semantics/.
"""
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import triage  # noqa: E402

QUEUE = os.path.join(ROOT, "build", "queue.json")
OVERRIDES = os.path.join(ROOT, "config", "overrides.json")
OUT = os.path.join(ROOT, "build", "m26-semantic.json")


def features_of(body):
    mns = [x[2] for x in body]
    ops = " ".join(x[3] for x in body)
    f = []
    if mns.count("jal"):
        f.append("calls:%d" % mns.count("jal"))
    if "jr" in mns and any("$v0" in x[3] for x in body if x[2] == "jr"):
        f.append("switch-jump")
    if any(x[2] in ("lwl", "lwr", "swl", "swr", "ldl", "ldr", "sdl", "sdr") for x in body):
        f.append("unaligned")
    if any(x[2].startswith("c1") or x[2].startswith("swc1") or x[2].startswith("lwc1") for x in body):
        f.append("fpu")
    if any(x[2] in ("mult", "multu", "div", "divu", "madd", "maddu", "mtlo", "mthi") for x in body):
        f.append("muldiv")
    if "andi" in mns and ("sll" in mns or "srl" in mns):
        f.append("bitmap")
    if any(x[2] == "lui" and "%hi" in x[3] for x in body):
        f.append("abs-addr")
    if any("(%gp)" in x[3] or ",0(gp)" in x[3] or "gp)" in x[3] for x in body):
        f.append("gp")
    if any(x[2] == "beql" or x[2] == "bnel" or x[2] == "bnel" for x in body):
        f.append("likely-branch")
    if "syscall" in mns:
        f.append("syscall")
    if "move" in mns and any("$sp" in x[3] for x in body if x[2] == "move"):
        f.append("stack-frame")
    return f


def main():
    q = json.load(open(QUEUE, encoding="utf-8"))
    ov = json.load(open(OVERRIDES, encoding="utf-8"))
    matched = {int(str(f["addr"]), 16): f.get("source", "") for f in ov.get("functions", [])
               if f.get("status") == "matched"}
    syms = triage.parse_symbols()
    by_fn = triage.parse_asm(symbols=syms)
    name_to_addr = {}
    for s in syms:
        name_to_addr[s["name"]] = s["addr"]
    funcs = {}
    for e in q["entries"]:
        ai = e["addr_i"]
        body = by_fn.get(ai, [])
        callees = []
        for (_a, _w, mn, ops) in body:
            if mn not in ("jal", "j"):
                continue
            tgt = None
            m = re.search(r"(FUN_[0-9a-fA-F]{8})", ops)
            if m:
                tgt = int(m.group(1)[4:], 16)
            elif "jal" in mn:
                m2 = re.match(r"\s*([A-Za-z_][A-Za-z0-9_]*)", ops)
                if m2 and m2.group(1) in name_to_addr:
                    tgt = name_to_addr[m2.group(1)]
                elif m2 and re.search(r"[0-9a-fA-F]{6,}", m2.group(1)):
                    tgt = int(re.search(r"([0-9a-fA-F]{6,})", m2.group(1)).group(1), 16)
            if tgt and tgt != ai and 0x100000 <= tgt < 0x300000:
                if tgt not in callees:
                    callees.append(tgt)
        funcs["%08x" % ai] = {
            "addr": e["addr"], "name": e.get("name"), "size": e.get("size"),
            "matched": ai in matched, "source": matched.get(ai, ""),
            "features": features_of(body), "callees": ["%08x" % c for c in callees],
        }
    for ai, rec in funcs.items():
        rec["callers"] = []
    for ai, rec in funcs.items():
        for c in rec["callees"]:
            if c in funcs:
                funcs[c]["callers"].append(ai)
    json.dump({"schema": 1, "functions": funcs}, open(OUT, "w", newline="\n",
              encoding="utf-8"), indent=0, ensure_ascii=False)
    n_matched = sum(1 for r in funcs.values() if r["matched"])
    print("semantic index:", len(funcs), "functions,", n_matched, "matched")


if __name__ == "__main__":
    main()
