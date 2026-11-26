#!/usr/bin/env python3
"""Generate an objdiff-compatible report.json for ByteMatch from local data.

Sources:
  config/symbols.csv    address,size,name  (3,967 functions)
  config/overrides.json functions[].status == "matched"
Output:
  build/report.json     measures + units (pseudo-modules by 0x20000 address buckets)
"""
import csv, json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUCKET = 0x20000

def load_symbols():
    rows = []
    with open(os.path.join(ROOT, "config", "symbols.csv"), newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f):
            rows.append({"addr": int(r["address"], 16), "size": int(r["size"]), "name": r["name"]})
    return rows

def load_matched():
    p = os.path.join(ROOT, "config", "overrides.json")
    with open(p, encoding="utf-8") as f:
        data = json.load(f)
    return {int(fn["addr"], 16) for fn in data.get("functions", []) if fn.get("status") == "matched"}

def pct(a, b):
    return (a / b * 100.0) if b else 0.0

def main():
    syms = load_symbols()
    matched = load_matched()
    total_code = sum(s["size"] for s in syms)
    matched_code = sum(s["size"] for s in syms if s["addr"] in matched)
    total_functions = len(syms)
    matched_functions = sum(1 for s in syms if s["addr"] in matched)

    units = {}
    for s in syms:
        b = s["addr"] // BUCKET
        u = units.setdefault(b, {"name": "text/%08x" % (b * BUCKET), "functions": []})
        ok = s["addr"] in matched
        u["functions"].append({
            "name": s["name"], "size": s["size"],
            "match_percent": 100.0 if ok else 0.0,
            "fuzzy_match_percent": 100.0 if ok else 0.0,
        })

    unit_list = []
    for b in sorted(units):
        u = units[b]
        t = sum(f["size"] for f in u["functions"])
        mc = sum(f["size"] for f in u["functions"] if f["match_percent"] == 100.0)
        mf = sum(1 for f in u["functions"] if f["match_percent"] == 100.0)
        unit_list.append({
            "name": u["name"],
            "measures": {
                "total_code": t, "matched_code": mc, "matched_code_percent": pct(mc, t),
                "total_functions": len(u["functions"]), "matched_functions": mf,
                "matched_functions_percent": pct(mf, len(u["functions"])),
                "complete_code": mc, "complete_code_percent": pct(mc, t),
                "total_data": 0, "matched_data": 0, "matched_data_percent": 0.0,
                "complete_data": 0, "complete_data_percent": 0.0,
            },
            "functions": u["functions"],
        })

    measures = {
        "fuzzy_match_percent": pct(matched_code, total_code),
        "total_code": total_code, "matched_code": matched_code,
        "matched_code_percent": pct(matched_code, total_code),
        "total_data": 0, "matched_data": 0, "matched_data_percent": 0.0,
        "total_functions": total_functions, "matched_functions": matched_functions,
        "matched_functions_percent": pct(matched_functions, total_functions),
        "complete_code": matched_code, "complete_code_percent": pct(matched_code, total_code),
        "complete_data": 0, "complete_data_percent": 0.0,
        "total_units": len(unit_list),
        "complete_units": sum(1 for u in unit_list
                              if u["measures"]["total_code"] > 0
                              and u["measures"]["matched_code"] == u["measures"]["total_code"]),
    }
    dest = os.path.join(ROOT, "build", "report.json")
    os.makedirs(os.path.dirname(dest), exist_ok=True)
    with open(dest, "w", encoding="utf-8") as f:
        json.dump({"measures": measures, "units": unit_list}, f, indent=2)
    print("wrote", dest)
    for k, v in measures.items():
        print("  %-26s %s" % (k, v))

if __name__ == "__main__":
    main()
