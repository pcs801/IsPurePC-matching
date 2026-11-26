#!/usr/bin/env python3
"""Generate an objdiff-compatible report.json for ByteMatch from local data.

Unit granularity is configurable:
  config/units.json          explicit list: {"units":[{"name","start","end"}]}
  config/tu_g.json           fallback: one unit per -G8 range, -G0 gaps bucketed
  BUCKET env / default       0x20000 bytes for the -G0 buckets
"""
import csv, json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUCKET = int(os.environ.get("UNIT_BUCKET", "0x20000"), 0)
MAXSPAN = int(os.environ.get("UNIT_MAXSPAN", "0x20000"), 0)

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

def load_units():
    """Return list of (name, start, end) ranges, or None for flat bucketing."""
    p = os.path.join(ROOT, "config", "units.json")
    if os.path.exists(p):
        with open(p, encoding="utf-8") as f:
            data = json.load(f)
        return data["units"]
    t = os.path.join(ROOT, "config", "tu_g.json")
    if os.path.exists(t):
        with open(t, encoding="utf-8") as f:
            data = json.load(f)
        return [(("game/g%d/%08x" % (r["g"], int(r["start"], 16))),
                 int(r["start"], 16), int(r["end"], 16)) for r in data.get("ranges", [])]
    return None

def expand(ranges, maxspan):
    """Split ranges wider than maxspan so no unit is a 400 KB blob."""
    out = []
    for name, a, b in ranges:
        if b - a <= maxspan:
            out.append((name, a, b))
        else:
            n = (b - a + maxspan - 1) // maxspan
            for i in range(n):
                s = a + i * maxspan
                out.append(("%s_%02d" % (name, i), s, min(b, s + maxspan)))
    return out

def assign(syms, units):
    """Map each symbol to a unit name.

    units is a list of dicts from config/units.json. When `addrs` is present it
    is authoritative (no range overlap); otherwise fall back to [start, end).
    """
    by_addr = {}
    for u in units:
        for a in u.get("addrs") or []:
            by_addr[a] = u["name"]
    if by_addr:
        return [by_addr.get(s["addr"], "game/g0/%08x" % (s["addr"] // BUCKET * BUCKET)) for s in syms]
    import bisect
    ranges = sorted((int(u["start"], 16) if isinstance(u["start"], str) else int(u["start"]),
                     int(u["end"], 16) if isinstance(u["end"], str) else int(u["end"]),
                     u["name"]) for u in units)
    starts = [r[0] for r in ranges]
    out = []
    for s in syms:
        i = bisect.bisect_right(starts, s["addr"]) - 1
        hit = None
        if i >= 0 and ranges[i][0] <= s["addr"] < ranges[i][1]:
            hit = ranges[i][2]
        out.append(hit or ("game/g0/%08x" % (s["addr"] // BUCKET * BUCKET)))
    return out

def pct(a, b):
    return (a / b * 100.0) if b else 0.0

def main():
    syms = load_symbols()
    matched = load_matched()
    names = assign(syms, load_units() or [])

    total_code = sum(s["size"] for s in syms)
    matched_code = sum(s["size"] for s in syms if s["addr"] in matched)
    total_functions = len(syms)
    matched_functions = sum(1 for s in syms if s["addr"] in matched)

    units = {}
    for s, uname in zip(syms, names):
        u = units.setdefault(uname, {"name": uname, "functions": []})
        ok = s["addr"] in matched
        u["functions"].append({
            "name": s["name"], "size": s["size"],
            "match_percent": 100.0 if ok else 0.0,
            "fuzzy_match_percent": 100.0 if ok else 0.0,
        })

    unit_list = []
    for uname in sorted(units):
        u = units[uname]
        t = sum(f["size"] for f in u["functions"])
        mc = sum(f["size"] for f in u["functions"] if f["match_percent"] == 100.0)
        mf = sum(1 for f in u["functions"] if f["match_percent"] == 100.0)
        unit_list.append({
            "name": uname,
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
    print("units:", len(unit_list))
    for u in unit_list:
        print("  %-24s %6d funcs %8d bytes %6.2f%%" % (
            u["name"], u["measures"]["total_functions"],
            u["measures"]["total_code"], u["measures"]["matched_code_percent"]))

if __name__ == "__main__":
    main()
