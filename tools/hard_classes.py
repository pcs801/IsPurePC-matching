#!/usr/bin/env python3
"""hard_classes.py - subdivide the hard tier (3,632 functions) by size, branch
count, FPU presence, call count, syscall and unsupported instructions.

Output: build/hard-classes.json with one-dimensional distributions, a
(calls x branches x fpu) cross table, a size x calls table, and a ranked list
of "work classes" with example addresses for the next matching campaign.

Usage:
  python tools/hard_classes.py
  python tools/hard_classes.py --tier hard --out build/hard-classes.json
"""
import argparse
import collections
import json
import os
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
QUEUE = os.path.join(ROOT, "build", "queue.json")


def bucket_size(n):
    if n <= 16:
        return "01_size_<=16"
    if n <= 32:
        return "02_size_17-32"
    if n <= 64:
        return "03_size_33-64"
    if n <= 128:
        return "04_size_65-128"
    if n <= 256:
        return "05_size_129-256"
    if n <= 512:
        return "06_size_257-512"
    if n <= 2048:
        return "07_size_513-2048"
    return "08_size_>2048"


def bucket_branches(n):
    if n == 0:
        return "b0"
    if n == 1:
        return "b1"
    if n == 2:
        return "b2"
    if n <= 5:
        return "b3-5"
    return "b6+"


def bucket_calls(n):
    if n == 0:
        return "c0"
    if n == 1:
        return "c1"
    if n <= 3:
        return "c2-3"
    if n <= 7:
        return "c4-7"
    return "c8+"


def unsupported_group(e):
    u = e.get("unsupported") or []
    if not u:
        return "none"
    if any(x in ("ldl", "ldr", "sdl", "sdr") for x in u):
        return "unaligned_ldl_ldr"
    if any(x in ("lq", "sq") for x in u):
        return "packed_lq_sq"
    if any(x.endswith("l") for x in u):
        return "likely_branch"
    if any(x in ("mult1", "div1", "madd", "maddu", "msub") for x in u):
        return "muldiv_variant"
    return "other_misc"


def summarize(entries):
    return {
        "count": len(entries),
        "bytes": sum(e["size"] for e in entries),
        "examples": [e["addr"] for e in entries[:6]],
    }


def group(entries, keyfn):
    buckets = collections.OrderedDict()
    for e in entries:
        buckets.setdefault(keyfn(e), []).append(e)
    return collections.OrderedDict(
        (k, summarize(v)) for k, v in sorted(buckets.items(), key=lambda kv: (-len(kv[1]), kv[0]))
    )


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--tier", default="hard")
    ap.add_argument("--out", default=os.path.join(ROOT, "build", "hard-classes.json"))
    args = ap.parse_args()
    with open(QUEUE, encoding="utf-8") as f:
        q = json.load(f)
    entries = [e for e in q["entries"] if e.get("tier") == args.tier]
    if not entries:
        raise SystemExit("no entries for tier %s" % args.tier)

    dims = {
        "size": group(entries, lambda e: bucket_size(e["size"])),
        "branches": group(entries, lambda e: bucket_branches(e["branches"])),
        "calls": group(entries, lambda e: bucket_calls(e["calls"])),
        "fpu": group(entries, lambda e: "fpu1" if e["fpu"] else "fpu0"),
        "syscall": group(entries, lambda e: "sys1" if e["syscall"] else "sys0"),
        "unsupported": group(entries, unsupported_group),
        "cls": group(entries, lambda e: e["cls"]),
        "padding": group(entries, lambda e: "padding" if e["padding"] else "no_padding"),
        "multi_return": group(
            entries, lambda e: "multi" if "multi-return" in (e["flags"] or []) else "single"),
    }

    cross = collections.Counter()
    for e in entries:
        cross[(bucket_calls(e["calls"]), bucket_branches(e["branches"]),
               "fpu1" if e["fpu"] else "fpu0")] += 1
    cross_rows = [
        {"calls": k[0], "branches": k[1], "fpu": k[2], "count": v}
        for k, v in sorted(cross.items(), key=lambda kv: (-kv[1], kv[0]))
    ]

    size_calls = collections.Counter()
    for e in entries:
        size_calls[(bucket_size(e["size"]), bucket_calls(e["calls"]))] += 1
    size_calls_rows = [
        {"size": k[0], "calls": k[1], "count": v}
        for k, v in sorted(size_calls.items(), key=lambda kv: (-kv[1], kv[0]))
    ]

    # practical work classes: ordered by expected difficulty (cheap first)
    def klass(e):
        parts = [bucket_calls(e["calls"]), bucket_branches(e["branches"])]
        if e["fpu"]:
            parts.append("fpu")
        if e["syscall"]:
            parts.append("syscall")
        if unsupported_group(e) != "none":
            parts.append("unsup:" + unsupported_group(e))
        if e["padding"]:
            parts.append("padding")
        return "+".join(parts)

    work = group(entries, klass)
    ranked = []
    for name, info in work.items():
        ranked.append({"class": name, **info})
    ranked.sort(key=lambda r: (-r["count"], r["class"]))

    doc = {
        "schema": 1,
        "project": "IsPurePC-Matching",
        "generated": time.strftime("%Y-%m-%dT%H:%M:%S%z"),
        "tier": args.tier,
        "total": len(entries),
        "total_bytes": sum(e["size"] for e in entries),
        "dims": dims,
        "unsupported_raw_top": [
            {"ops": list(k), "count": v}
            for k, v in collections.Counter(
                tuple(e["unsupported"]) for e in entries if e["unsupported"]).most_common(15)
        ],
        "cross_calls_branches_fpu": cross_rows,
        "cross_size_calls": size_calls_rows,
        "work_classes": ranked,
    }
    os.makedirs(os.path.dirname(args.out), exist_ok=True)
    with open(args.out, "w", newline="\n", encoding="utf-8") as f:
        json.dump(doc, f, indent=1, ensure_ascii=False)
        f.write("\n")

    print("hard tier: %d functions, %d bytes" % (len(entries), doc["total_bytes"]))
    print("size: " + ", ".join("%s=%d" % (k, v["count"]) for k, v in dims["size"].items()))
    print("branches: " + ", ".join("%s=%d" % (k, v["count"]) for k, v in dims["branches"].items()))
    print("calls: " + ", ".join("%s=%d" % (k, v["count"]) for k, v in dims["calls"].items()))
    print("fpu: %s, syscall: %s" % (
        {k: v["count"] for k, v in dims["fpu"].items()},
        {k: v["count"] for k, v in dims["syscall"].items()}))
    print("unsupported: " + ", ".join("%s=%d" % (k, v["count"])
                                      for k, v in dims["unsupported"].items()))
    print("top work classes:")
    for r in ranked[:12]:
        print("  %-42s %5d  e.g. %s" % (r["class"], r["count"], ",".join(r["examples"][:3])))
    print("wrote", os.path.relpath(args.out, ROOT))


if __name__ == "__main__":
    main()
