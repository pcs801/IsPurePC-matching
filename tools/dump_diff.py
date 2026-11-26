#!/usr/bin/env python
"""Disassemble baserom slice vs compiled .o .text for the failing samples."""
import struct, sys
from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32, CS_MODE_LITTLE_ENDIAN

ROOT = r"E:/ONE PIECE/S/IsPurePC-matching"
BASEROM = ROOT + "/baserom/SLPM_665.70"
TEXT_ADDR, TEXT_OFF = 0x00100000, 0x1000

def elf_text(path):
    data = open(path, "rb").read()
    e_shoff = struct.unpack_from("<I", data, 0x20)[0]
    e_shentsize = struct.unpack_from("<H", data, 0x2E)[0]
    e_shnum = struct.unpack_from("<H", data, 0x30)[0]
    e_shstrndx = struct.unpack_from("<H", data, 0x32)[0]
    shstr = e_shoff + e_shstrndx * e_shentsize
    shstr_off = struct.unpack_from("<I", data, shstr + 0x10)[0]
    shstr_size = struct.unpack_from("<I", data, shstr + 0x14)[0]
    strtab = data[shstr_off:shstr_off + shstr_size]
    for i in range(e_shnum):
        o = e_shoff + i * e_shentsize
        name_off, typ, flags, addr, off, size = struct.unpack_from("<IIIIII", data, o)
        end = strtab.find(b"\x00", name_off)
        if strtab[name_off:end] == b".text":
            return data[off:off + size]
    return b""

def dis(bs, addr):
    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32 + CS_MODE_LITTLE_ENDIAN)
    out = []
    for ins in md.disasm(bs, addr):
        out.append("  %08x  %-8s %s" % (ins.address, ins.mnemonic, ins.op_str))
    return "\n".join(out)

funcs = {"0010bb88": (0x0010BB88, 12), "00112588": (0x00112588, 12), "00112ab8": (0x00112AB8, 12)}
base = open(BASEROM, "rb").read()
for key, (addr, size) in funcs.items():
    off = TEXT_OFF + (addr - TEXT_ADDR)
    print("=" * 60)
    print(key, "ORIGINAL")
    print(dis(base[off:off + size], addr))
    for G in (0, 8):
        print("  -- compiled G%d --" % G)
        print(dis(elf_text(ROOT + "/build/spike/%s.G%d.o" % (key, G)), 0))
