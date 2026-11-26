#!/usr/bin/env python
"""Pick shortest leaf functions with no FPU and no calls from the function index."""
import json, sys, io, re

OLD = r"E:/ONE PIECE/S/IsPurePC"
idx_path = OLD + "/reports/all_functions/_index.tsv"
dis_path = OLD + "/artifacts/data/analysis/disasm_text.txt"

funcs = []
with open(idx_path, encoding="utf-8", errors="replace") as f:
    for line in f:
        p = line.rstrip("\n").split("\t")
        if len(p) < 3: continue
        try: a = int(p[0], 16)
        except ValueError: continue
        try: size = int(p[1])
        except ValueError: continue
        funcs.append((a, size, p[2]))

# word per address
words = {}
with open(dis_path, encoding="utf-8", errors="replace") as f:
    for line in f:
        p = line.split()
        if len(p) < 2: continue
        try:
            a = int(p[0], 16)
            w = int.from_bytes(bytes.fromhex(p[1]), 'little')
        except ValueError: continue
        words[a] = (w, line.rstrip("\n"))

def classify(a, size):
    end = a + size
    seq = []
    x = a
    while x < end:
        if x not in words:
            return None, "missing_word"
        w, text = words[x]
        seq.append((x, w, text))
        x += 4
    nj = len(seq) - size//4
    if nj != 0: return None, "gap"
    return seq, ""

def has_call(seq):
    for a, w, t in seq:
        op = w >> 26
        funct = w & 0x3F
        if op == 3: return "jal"
        if op == 0 and funct == 9: return "jalr"
        if op == 0 and funct == 8:  # jr — allow only jr $ra
            rs = (w >> 21) & 0x1F
            if rs != 31: return "jr_nonra"
    return ""

def has_fpu(seq):
    for a, w, t in seq:
        op = w >> 26
        if op == 0x11: return "cop1"
        if ".byte" in t:  # unknown encoding: be conservative
            return "unknown_byte"
    return ""

def is_excluded(name):
    lname = name.lower()
    return lname.startswith("entry") or "sdk" in lname

cands = []
for a, size, name in funcs:
    if size >= 64 or size < 8: continue
    if size % 4: continue
    if is_excluded(name): continue
    seq, err = classify(a, size)
    if err: continue
    c = has_call(seq)
    if c: continue
    fp = has_fpu(seq)
    if fp: continue
    cands.append((size, a, name, len(seq)))

cands.sort()
print("total funcs:", len(funcs), "candidates:", len(cands))
for size, a, name, n in cands[:60]:
    print("%08x %3d %2d %s" % (a, size, n, name))
