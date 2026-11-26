#!/usr/bin/env python
"""Assemble the full ELF image from rebuilt segments and compare SHA with baserom.

Inputs
  build/splat/1000.resolved.bin   rebuilt .text (relocations resolved)
  assets/*.bin                    splat-split data segments
  baserom/SLPM_665.70             template for ELF metadata (header/phdr/shdr)
"""
import hashlib
import os
import struct

ROOT = r"E:/ONE PIECE/S/IsPurePC-matching"
BASE = ROOT + "/baserom/SLPM_665.70"
OUT = ROOT + "/build/splat/SLPM_665.70.rebuilt"

# (file, rom offset)
SEGMENTS = [
    ("assets/0.bin", 0x000000),
    ("build/splat/1000.resolved.bin", 0x001000),
    ("assets/ctors.bin", 0x11399C),
    ("assets/dtors.bin", 0x1139A4),
    ("assets/reginfo.bin", 0x1139AC),
    ("assets/data.bin", 0x113A00),
    ("assets/eh_frame.bin", 0x158D08),
    ("assets/rodata.bin", 0x158D80),
    ("assets/lit4.bin", 0x170A00),
    ("assets/sdata.bin", 0x170B80),
]

# region covered by splat-split segments (data end); metadata after it is copied
DATA_END = 0x171AB8


def main():
    base = bytearray(open(BASE, "rb").read())
    img = bytearray(base)  # template: ELF header, phdrs, shstrtab, section headers
    applied = []
    for rel, off in SEGMENTS:
        path = os.path.join(ROOT, rel)
        blob = open(path, "rb").read()
        img[off:off + len(blob)] = blob
        applied.append((rel, off, len(blob)))

    open(OUT, "wb").write(img)

    h_base = hashlib.sha256(base).hexdigest()
    h_img = hashlib.sha256(img).hexdigest()
    print("segments applied:")
    for rel, off, n in applied:
        print("  0x%06X  %-34s %6d bytes" % (off, rel, n))
    print()
    print("baserom sha256:", h_base)
    print("rebuilt sha256:", h_img)
    print("MATCH" if h_base == h_img else "DIFFER")
    if h_base != h_img:
        diffs = [i for i in range(len(base)) if base[i] != img[i]]
        print("diff bytes:", len(diffs), "first:", [(hex(i), base[i], img[i]) for i in diffs[:8]])
    # also report the game-payload hash (exclude ELF metadata tail)
    payload = bytes(img[DATA_END:])
    print("tail (metadata) identical:", bytes(base[DATA_END:]) == payload)


main()
