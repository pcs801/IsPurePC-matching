#!/usr/bin/env python
"""Compare compiled .o .text bytes against baserom slices, with relocation awareness."""
import struct, os, json, glob, sys

ROOT = r"E:/ONE PIECE/S/IsPurePC-matching"
BASEROM = ROOT + "/baserom/SLPM_665.70"
# .text: addr 0x00100000, file offset 0x1000
TEXT_ADDR = 0x00100000
TEXT_OFF = 0x1000

FUNCS = {
 "00102078": (0x00102078, 8),
 "00105fb0": (0x00105FB0, 8),
 "001075d0": (0x001075D0, 8),
 "0010bb88": (0x0010BB88, 12),
 "0010c110": (0x0010C110, 8),
 "00110598": (0x00110598, 20),
 "00112588": (0x00112588, 12),
 "00112ab8": (0x00112AB8, 12),
 "00113480": (0x00113480, 12),
 "00123788": (0x00123788, 12),
 "0017f4e8": (0x0017F4E8, 28),
}

def read_elf32(path):
    data = open(path, "rb").read()
    assert data[:4] == b"\x7fELF"
    e_shoff = struct.unpack_from("<I", data, 0x20)[0]
    e_shentsize = struct.unpack_from("<H", data, 0x2E)[0]
    e_shnum = struct.unpack_from("<H", data, 0x30)[0]
    e_shstrndx = struct.unpack_from("<H", data, 0x32)[0]
    shstr = e_shoff + e_shstrndx * e_shentsize
    shstr_off = struct.unpack_from("<I", data, shstr + 0x10)[0]
    shstr_size = struct.unpack_from("<I", data, shstr + 0x14)[0]
    strtab = data[shstr_off:shstr_off + shstr_size]
    secs = {}
    for i in range(e_shnum):
        o = e_shoff + i * e_shentsize
        name_off, typ, flags, addr, off, size = struct.unpack_from("<IIIIII", data, o)
        link, info = struct.unpack_from("<II", data, o + 0x18)
        end = strtab.find(b"\x00", name_off)
        name = strtab[name_off:end].decode()
        secs[name] = dict(type=typ, addr=addr, off=off, size=size, link=link, info=info)
    return data, secs

def text_bytes(obj):
    data, secs = read_elf32(obj)
    t = secs.get(".text")
    if not t:
        return b"", 0, []
    raw = data[t["off"]:t["off"] + t["size"]]
    relocs = []
    for name, s in secs.items():
        if s["type"] == 9:  # SHT_REL
            for k in range(0, s["size"], 8):
                r_off, r_info = struct.unpack_from("<II", data, s["off"] + k)
                relocs.append((r_off, r_info >> 8, r_info & 0xFF))
    return raw, t["size"], relocs

def main():
    base = open(BASEROM, "rb").read()
    rows = []
    for key, (addr, size) in sorted(FUNCS.items()):
        off = TEXT_OFF + (addr - TEXT_ADDR)
        orig = base[off:off + size]
        line = {"func": key, "addr": "0x%08X" % addr, "size": size}
        for G in (0, 8):
            obj = ROOT + "/build/" + os.environ.get("SPIKE_DIR", "spike") + "/%s.G%d.o" % (key, G)
            if not os.path.exists(obj):
                line["G%d" % G] = "no-obj"
                continue
            comp, tsize, relocs = text_bytes(obj)
            if comp == orig:
                line["G%d" % G] = "MATCH"
            else:
                # reloc-aware: mask low16 where a reloc targets the word
                rel_offs = {r[0] // 4 for r in relocs}
                ok = True
                if len(comp) != len(orig):
                    ok = False
                else:
                    for i in range(0, len(comp), 4):
                        a = comp[i:i+4]; b = orig[i:i+4]
                        if a == b:
                            continue
                        if (i // 4) in rel_offs:
                            wa = int.from_bytes(a, "little")
                            wb = int.from_bytes(b, "little")
                            if (wa & 0xFFFF0000) == (wb & 0xFFFF0000):
                                continue
                            # mask low 16 only for hi/lo/idx
                        ok = False
                        break
                line["G%d" % G] = "MATCH(reloc)" if ok else "diff"
                if not ok:
                    n = sum(1 for i in range(0, min(len(comp), len(orig)), 4) if comp[i:i+4] != orig[i:i+4])
                    line["G%d_words" % G] = n
                    line["G%d_len" % G] = "%d/%d" % (len(comp), len(orig))
                    line["G%d_rel" % G] = len(relocs)
        rows.append(line)
    print("%-10s %-10s %5s %-14s %-14s" % ("func", "addr", "size", "G0", "G8"))
    for r in rows:
        print("%-10s %-10s %5d %-14s %-14s %s" % (
            r["func"], r["addr"], r["size"], r["G0"], r["G8"],
            (" " + str({k: v for k, v in r.items() if k.startswith("G0_")})) if "G0_words" in r or "G0_len" in r else ""))
    json.dump(rows, open(ROOT + "/build/" + os.environ.get("SPIKE_DIR", "spike") + "/match_result.json", "w"), indent=1)

main()
