#!/usr/bin/env python
"""Convert the legacy function index into config/symbols.csv + symbol_addrs.txt."""
import csv, os

OLD = r"E:/ONE PIECE/S/IsPurePC"
ROOT = r"E:/ONE PIECE/S/IsPurePC-matching"
idx = OLD + "/reports/all_functions/_index.tsv"

rows = []
with open(idx, encoding="utf-8", errors="replace") as f:
    for line in f:
        p = line.rstrip("\n").split("\t")
        if len(p) < 3:
            continue
        try:
            addr = int(p[0], 16)
            size = int(p[1])
        except ValueError:
            continue
        rows.append((addr, size, p[2]))

rows.sort()
os.makedirs(ROOT + "/config", exist_ok=True)
with open(ROOT + "/config/symbols.csv", "w", newline="", encoding="utf-8") as f:
    w = csv.writer(f)
    w.writerow(["address", "size", "name"])
    for addr, size, name in rows:
        w.writerow([f"0x{addr:08X}", size, name])

with open(ROOT + "/config/symbol_addrs.txt", "w", encoding="utf-8") as f:
    f.write("// Auto-generated from IsPurePC/reports/all_functions/_index.tsv\n")
    for addr, size, name in rows:
        f.write(f"{name} = 0x{addr:08X}; // type:func size:0x{size:X}\n")

print("wrote", len(rows), "symbols")
print("first:", rows[0], "last:", rows[-1])
