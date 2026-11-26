#!/usr/bin/env python
"""Dump disassembly for candidate leaf functions (sorted by size)."""
import sys

OLD = r"E:/ONE PIECE/S/IsPurePC"
idx = OLD + "/reports/all_functions/_index.tsv"
dis = OLD + "/artifacts/data/analysis/disasm_text.txt"

lo = int(sys.argv[1]) if len(sys.argv) > 1 else 8
hi = int(sys.argv[2]) if len(sys.argv) > 2 else 64
limit = int(sys.argv[3]) if len(sys.argv) > 3 else 12

funcs = []
with open(idx, encoding="utf-8", errors="replace") as f:
    for line in f:
        p = line.rstrip("\n").split("\t")
        if len(p) < 3: continue
        try:
            funcs.append((int(p[0], 16), int(p[1]), p[2]))
        except ValueError:
            continue

lines = {}
addrs = set()
with open(dis, encoding="utf-8", errors="replace") as f:
    for line in f:
        p = line.split()
        if len(p) < 2: continue
        try:
            addrs.add(int(p[0], 16))
        except ValueError:
            continue
        lines[int(p[0], 16)] = line.rstrip("\n")

def leaf_ok(a, size):
    end = a + size
    x = a
    while x < end:
        if x not in lines: return False, "missing"
        w = int.from_bytes(bytes.fromhex(lines[x].split()[1]), 'little')
        op = w >> 26
        fn = w & 0x3F
        if op == 3 or (op == 0 and fn == 9): return False, "call"
        if op == 0x11: return False, "fpu"
        if ".byte" in lines[x]: return False, "byte"
        x += 4
    return True, ""

cands = []
for a, size, name in funcs:
    if not (lo <= size <= hi): continue
    if size % 4: continue
    if name.lower().startswith("entry"): continue
    ok, why = leaf_ok(a, size)
    if ok:
        cands.append((size, a, name))

cands.sort()
print("candidates in [%d,%d]: %d" % (lo, hi, len(cands)))
for size, a, name in cands[:limit]:
    print("=" * 70)
    print("%s  addr=0x%08X  size=%d" % (name, a, size))
    for x in range(a, a + size, 4):
        print("  " + lines[x])
