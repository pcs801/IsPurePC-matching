#!/usr/bin/env python
"""Convert legacy function index into symbols, resizing overlaps away.

Sizes from the legacy index overlap each other (they were produced by a
separate analysis pass).  splat refuses to disassemble overlapping symbols,
so every function size is recomputed as (next function address - address).
"""
import csv, os, collections

OLD = r"E:/ONE PIECE/S/IsPurePC"
ROOT = r"E:/ONE PIECE/S/IsPurePC-matching"
idx = OLD + "/reports/all_functions/_index.tsv"
TEXT_END = 0x00100000 + 1124764  # .text vram end

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

# drop exact duplicate addresses, keep first
seen_addr = set()
uniq = []
for addr, size, name in rows:
    if addr in seen_addr:
        continue
    seen_addr.add(addr)
    uniq.append((addr, size, name))
rows = uniq

# dedupe names
seen_name = collections.Counter()
out = []
dups = []
for addr, size, name in rows:
    seen_name[name] += 1
    if seen_name[name] == 1:
        out.append([addr, size, name])
    else:
        newname = "%s_dup%d" % (name, seen_name[name])
        dups.append((name, newname, addr))
        out.append([addr, size, newname])

# resize: next address - address (last one runs to .text end)
resized = 0
for i, row in enumerate(out):
    nxt = out[i + 1][0] if i + 1 < len(out) else TEXT_END
    new_size = nxt - row[0]
    if new_size != row[1]:
        resized += 1
    row[1] = new_size

# splat degenerates catastrophically if any function is smaller than 2
# instructions (4/8 bytes): it treats every following symbol as a
# mid-function label (alabel) and stops disassembling.  Merge those
# fragments into the preceding function instead of dropping them.
merged = []
for row in out:
    if row[1] < 8 and merged:
        merged[-1][1] += row[1]
        continue
    merged.append(row)
out = merged

os.makedirs(ROOT + "/config", exist_ok=True)
with open(ROOT + "/config/symbols.csv", "w", newline="", encoding="utf-8") as f:
    w = csv.writer(f)
    w.writerow(["address", "size", "name"])
    for addr, size, name in out:
        w.writerow(["0x%08X" % addr, size, name])

with open(ROOT + "/config/symbol_addrs.txt", "w", encoding="utf-8") as f:
    f.write("// Auto-generated; sizes = next_symbol_addr - addr (overlap-free)\n")
    for addr, size, name in out:
        f.write("%s = 0x%08X; // type:func size:0x%X\n" % (name, addr, size))

print("symbols:", len(out), "resized:", resized, "renamed dups:", len(dups))
print("addr range: 0x%08X .. 0x%08X" % (out[0][0], out[-1][0]))
