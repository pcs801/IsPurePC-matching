#!/usr/bin/env python3
"""m26_queue.py - build build/m26-queue.json: the 3,743 remaining functions
ordered easy-first, per docs/m2-6-decision.md.

Order groups
  1. no branches, calls <= 1, size <= 64
  2. branches <= 3, calls <= 3, size <= 128
  3. everything else
  4. special instructions (likely / unaligned / FPU / syscall / unsupported) last

Exclusion: functions already in config/overrides.json (223 matched).
Core-only matches (padded ledger) are NOT excluded here: the decision document
counts 3,966 - 223 = 3,743; the worker skips them by claims at run time.

Usage: python tools/m26_queue.py
"""
import json
import os
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
QUEUE = os.path.join(ROOT, "build", "queue.json")
OVERRIDES = os.path.join(ROOT, "config", "overrides.json")
OUT = os.path.join(ROOT, "build", "m26-queue.json")


def group_of(e):
    unsup = e.get("unsupported") or []
    special = (e.get("fpu") or e.get("syscall") or unsup
               or any("likely" in str(x) for x in (e.get("flags") or []))
               or any(x in ("ldl", "ldr", "sdl", "sdr") for x in unsup))
    if special:
        return 4
    if e.get("branches", 0) == 0 and e.get("calls", 0) <= 1 and e.get("size", 0) <= 64:
        return 1
    if e.get("branches", 0) <= 3 and e.get("calls", 0) <= 3 and e.get("size", 0) <= 128:
        return 2
    return 3


def main():
    q = json.load(open(QUEUE, encoding="utf-8"))
    ov = json.load(open(OVERRIDES, encoding="utf-8"))
    excluded = {int(str(f["addr"]), 16) for f in ov.get("functions", [])
                if f.get("status") == "matched"}
    entries = [e for e in q["entries"] if e["addr_i"] not in excluded]
    rows = []
    for e in entries:
        rows.append({
            "addr": e["addr"], "addr_i": e["addr_i"], "name": e["name"],
            "size": e["size"], "core": e["core"], "padding": e["padding"],
            "tier": e["tier"], "cls": e["cls"], "g": e["g"],
            "branches": e["branches"], "calls": e["calls"],
            "fpu": e["fpu"], "syscall": e["syscall"],
            "unsupported": e.get("unsupported") or [],
            "flags": e.get("flags") or [], "sig": e.get("sig", ""),
            "score": e.get("score", 0), "group": group_of(e),
        })
    rows.sort(key=lambda r: (r["group"], r["score"], r["addr_i"]))
    counts = {}
    for r in rows:
        counts[str(r["group"])] = counts.get(str(r["group"]), 0) + 1
    doc = {
        "schema": 1,
        "generated": time.strftime("%Y-%m-%dT%H:%M:%S%z"),
        "policy": "easy-first groups 1..4; excluded overrides; 3,743 = 3,966-223",
        "source": "build/queue.json + config/overrides.json",
        "total": len(rows),
        "groups": counts,
        "entries": rows,
    }
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    with open(OUT, "w", newline="\n", encoding="utf-8") as f:
        json.dump(doc, f, indent=1, ensure_ascii=False)
        f.write("\n")
    print("m26 queue:", len(rows), "groups", counts)
    print("first 3:", [(r["addr"], r["group"], r["size"]) for r in rows[:3]])


if __name__ == "__main__":
    main()
