#!/usr/bin/env python
"""Emit --defsym=<name>=<addr> for every undefined symbol of an object.

spimdisasm names data symbols after their address (D_00123456), so the
definition list can be generated mechanically.  Used to feed ee-ld.
"""
import struct
import sys


def main():
    path = sys.argv[1] if len(sys.argv) > 1 else "out.o"
    out = sys.argv[2] if len(sys.argv) > 2 else "defsym.args"
    data = open(path, "rb").read()
    e_shoff = struct.unpack_from("<I", data, 0x20)[0]
    e_shentsize = struct.unpack_from("<H", data, 0x2E)[0]
    e_shnum = struct.unpack_from("<H", data, 0x30)[0]
    e_shstrndx = struct.unpack_from("<H", data, 0x32)[0]
    shstr_o = e_shoff + e_shstrndx * e_shentsize
    so = struct.unpack_from("<I", data, shstr_o + 0x10)[0]
    ss = struct.unpack_from("<I", data, shstr_o + 0x14)[0]
    strtab = data[so:so + ss]
    secs = {}
    for i in range(e_shnum):
        o = e_shoff + i * e_shentsize
        name_off, typ, flags, addr, off, size = struct.unpack_from("<IIIIII", data, o)
        end = strtab.find(b"\x00", name_off)
        secs[strtab[name_off:end].decode()] = dict(off=off, size=size)
    sym = secs[".symtab"]
    st = secs[".strtab"]
    args = []
    for i in range(sym["size"] // 16):
        o = sym["off"] + i * 16
        name_off, value, size, info, other, shndx = struct.unpack_from("<IIIBBH", data, o)
        end = data.find(b"\x00", st["off"] + name_off)
        name = data[st["off"] + name_off:end].decode()
        if shndx != 0 or not name or "_" not in name:
            continue
        hexpart = name.split("_", 1)[1].split(".")[0]
        try:
            addr = int(hexpart, 16)
        except ValueError:
            continue
        args.append("--defsym=%s=0x%X" % (name, addr))
    open(out, "w").write("\n".join(args))
    print("defsym entries:", len(args))


if __name__ == "__main__":
    main()
