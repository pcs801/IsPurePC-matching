#!/usr/bin/env python3
"""program_map.py - deterministic facts for a top-down program map.

Extracts printable strings from baserom, call-graph centrality, and library-ish
symbol hints into build/m26-program-map-data.json. No model calls, no guessing.
"""
import csv
import json
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BASEROM = os.path.join(ROOT, "baserom", "SLPM_665.70")
SYMBOLS = os.path.join(ROOT, "config", "symbols.csv")
SEMANTIC = os.path.join(ROOT, "build", "m26-semantic.json")
OUT = os.path.join(ROOT, "build", "m26-program-map-data.json")


def strings_from_bin(path, minlen=6, limit=400):
    data = open(path, "rb").read()
    out = []
    for m in re.finditer(rb"[\x20-\x7e]{%d,}" % minlen, data):
        s = m.group(0).decode("ascii", "replace")
        out.append({"offset": m.start(), "s": s})
        if len(out) >= limit:
            break
    return out


def main():
    strings = strings_from_bin(BASEROM)
    rows = []
    with open(SYMBOLS, newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f):
            rows.append({"addr": int(r["address"], 16), "size": int(r["size"]),
                         "name": r["name"]})
    named = [r for r in rows if not r["name"].startswith("FUN_") and r["name"] != "entry"]
    sdk_area = [r for r in rows if 0x200000 <= r["addr"] < 0x210000]
    lib_hint = sorted({r["name"] for r in named if re.search(r"Sif|Flush|Wait|Sema|Rpc|Pad|Memcard|Gs", r["name"], re.I)})
    try:
        sem = json.load(open(SEMANTIC, encoding="utf-8"))["functions"]
    except (OSError, ValueError):
        sem = {}
    central = []
    for k, v in sem.items():
        central.append((len(v.get("callers", [])), k, v.get("name"), v.get("matched")))
    central.sort(reverse=True)
    doc = {"schema": 1,
           "binary": "baserom/SLPM_665.70",
           "strings_sample": strings[:300],
           "string_count": len(strings),
           "symbols": {"total": len(rows), "named": len(named), "sdk_area": len(sdk_area),
                       "lib_hint": lib_hint[:40]},
           "central_functions": [{"callers": c, "addr": "0x" + k.upper(),
                                  "name": n, "matched": m} for c, k, n, m in central[:40]],
           }
    json.dump(doc, open(OUT, "w", newline="\n", encoding="utf-8"),
              indent=1, ensure_ascii=False)
    print("strings", len(strings), "symbols", len(rows), "named", len(named),
          "sdk_area", len(sdk_area))
    print("lib hints", lib_hint[:12])
    print("central top5", [(c, "0x" + k.upper()) for c, k, _n, _m in central[:5]])


if __name__ == "__main__":
    main()
