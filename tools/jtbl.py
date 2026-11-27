#!/usr/bin/env python3
"""jtbl.py - recover PS2 jump tables from the baserom ELF.

PS2 ELF is little-endian (EI_DATA=1).  Given a table VA and item count, map VA to
file offset through the program headers, read <I, and group duplicate targets.

Usage:
  python tools/jtbl.py --va 0x0026BF00 --count 59
  python tools/jtbl.py --va 0x00257FA0 --count 8
"""
import argparse
import struct

BASEROM = "baserom/SLPM_665.70"


def load_segments(path):
    data = open(path, "rb").read()
    if data[:4] != b"\x7fELF" or data[5] != 1:
        raise SystemExit("not a little-endian ELF")
    e_phoff = struct.unpack_from("<I", data, 0x1C)[0]
    e_phentsize = struct.unpack_from("<H", data, 0x2A)[0]
    e_phnum = struct.unpack_from("<H", data, 0x2C)[0]
    segs = []
    for i in range(e_phnum):
        off = e_phoff + i * e_phentsize
        p_type, p_offset, p_vaddr, _p_paddr, p_filesz = struct.unpack_from("<IIIII", data, off)
        if p_type == 1:  # PT_LOAD
            segs.append((p_vaddr, p_offset, p_filesz))
    return data, segs


def va2off(segs, va):
    for vaddr, off, filesz in segs:
        if vaddr <= va < vaddr + filesz:
            return off + (va - vaddr)
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--va", required=True, help="table virtual address, e.g. 0x0026BF00")
    ap.add_argument("--count", type=int, required=True)
    ap.add_argument("--bin", default=BASEROM)
    args = ap.parse_args()
    va = int(args.va, 16)
    data, segs = load_segments(args.bin)
    off = va2off(segs, va)
    if off is None:
        raise SystemExit("VA not in any PT_LOAD segment")
    targets = struct.unpack_from("<%dI" % args.count, data, off)
    groups = {}
    for i, t in enumerate(targets):
        groups.setdefault(t, []).append(i)
    print("table 0x%08X -> file offset 0x%X, %d items, %d distinct targets" % (
        va, off, args.count, len(groups)))
    for t, idxs in sorted(groups.items()):
        print("  0x%08X  count=%d  idx=%s" % (t, len(idxs), idxs if len(idxs) <= 12 else idxs[:12] + ["..."]))


if __name__ == "__main__":
    main()
