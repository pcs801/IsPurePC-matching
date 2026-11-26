#!/usr/bin/env python3
"""Generate config/units.json — one unit per function, so progress is visible.

Each unit carries `addrs` (its function address), so gen_report maps exactly.
Name shape: tu/<g>/<addr> keeps the -G grouping in the folder tree.
"""
import csv, json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

def load_symbols():
    rows = []
    with open(os.path.join(ROOT, "config", "symbols.csv"), newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f):
            rows.append({"addr": int(r["address"], 16), "size": int(r["size"]), "name": r["name"]})
    return rows

def load_ranges():
    p = os.path.join(ROOT, "config", "tu_g.json")
    if not os.path.exists(p):
        return []
    with open(p, encoding="utf-8") as f:
        data = json.load(f)
    return [(int(r["start"], 16), int(r["end"], 16), r.get("g", 8)) for r in data.get("ranges", [])]

def g_label(addr, ranges):
    for a, b, g in ranges:
        if a <= addr < b:
            return "g%d" % g
    return "g0"

def main():
    syms = load_symbols()
    ranges = load_ranges()
    units = []
    for s in syms:
        units.append({
            "name": "tu/%s/%08x" % (g_label(s["addr"], ranges), s["addr"]),
            "start": s["addr"],
            "end": s["addr"] + s["size"],
            "functions": 1,
            "addrs": [s["addr"]],
            "confidence": "function",
        })
    out = {"note": "one unit per function (visibility)", "source": "functions", "units": units}
    dest = os.path.join(ROOT, "config", "units.json")
    with open(dest, "w", encoding="utf-8") as f:
        json.dump(out, f, indent=1)
    print("units:", len(units))

if __name__ == "__main__":
    main()
