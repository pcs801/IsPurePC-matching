#!/usr/bin/env python3
"""semantic_eval.py - feedback loop with size/tier stratification.

Raw has_ctx vs no_ctx is confounded by size: functions with matched callees are
usually bigger. Compare inside the same size/tier bucket instead.
"""
import glob
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))


def classify(diff):
    d = (diff or "").lower()
    if "volatile" in d:
        return "volatile-class"
    if "unresolved reloc" in d or "section" in d:
        return "reloc-toolchain"
    if "length differs" in d:
        return "length/pad"
    if re.search(r"word \d+", d):
        return "sched/register"
    if "no candidate" in d or "rejected" in d:
        return "no-candidate"
    return "other"


def size_bucket(n):
    if n is None:
        return "?"
    if n <= 64:
        return "b1<=64"
    if n <= 256:
        return "b2<=256"
    if n <= 1024:
        return "b3<=1024"
    return "b4>1024"


def main():
    try:
        sem = json.load(open(os.path.join(ROOT, "build", "m26-semantic.json"),
                             encoding="utf-8"))["functions"]
    except (OSError, ValueError):
        sem = {}
    try:
        q = json.load(open(os.path.join(ROOT, "build", "queue.json"), encoding="utf-8"))["entries"]
    except (OSError, ValueError):
        q = []
    size_of = {e["addr"]: e.get("size") for e in q}
    batches = []
    for p in sorted(glob.glob(os.path.join(ROOT, "build", "m26-batch-*.json"))):
        try:
            d = json.load(open(p, encoding="utf-8"))
        except (OSError, ValueError):
            continue
        if d.get("phase") not in ("M2.6-pipeline", "M2.6") or not d.get("rows"):
            continue
        batches.append(d)
    by_addr = {}
    for d in batches:
        for r in d.get("rows", []):
            by_addr.setdefault(r.get("addr"), []).append(r)
    buckets = {}
    blockers = {}
    rows = []
    for addr, rs in by_addr.items():
        ai = int(str(addr), 16)
        rec = sem.get("%08x" % ai, {})
        refs = list(rec.get("callers", [])) + list(rec.get("callees", []))
        has_ctx = any(sem.get(x, {}).get("matched") for x in refs)
        last = rs[-1]
        ok = last.get("result") == "MATCH"
        b = "match" if ok else classify(last.get("diff"))
        blockers[b] = blockers.get(b, 0) + 1
        sb = size_bucket(size_of.get(addr))
        k = (sb, "has_ctx" if has_ctx else "no_ctx")
        buckets.setdefault(k, [0, 0])
        buckets[k][0] += 1 if ok else 0
        buckets[k][1] += 1
        rows.append({"addr": addr, "result": last.get("result"), "blocker": b,
                     "has_ctx": has_ctx, "size_bucket": sb})
    strat = {}
    for (sb, side), (h, n) in sorted(buckets.items()):
        strat.setdefault(sb, {})[side] = {"hits": h, "functions": n,
                                          "hit_rate": round(h / n, 4) if n else None}
    per_batch = [{"batch": d.get("batch"), "mode": d.get("mode", "func"),
                  "functions": d.get("functions"), "hits": d.get("hits"),
                  "hit_rate": d.get("hit_rate")} for d in batches]
    doc = {"schema": 1, "batches": per_batch, "blockers": blockers,
           "by_size_bucket": strat, "rows": rows}
    json.dump(doc, open(os.path.join(ROOT, "build", "m26-semantic-eval.json"), "w",
                        newline="\n", encoding="utf-8"), indent=1, ensure_ascii=False)
    print("batches", len(per_batch), "blockers", blockers)
    for sb in sorted(strat):
        print(sb, json.dumps(strat[sb], ensure_ascii=False))


if __name__ == "__main__":
    main()
