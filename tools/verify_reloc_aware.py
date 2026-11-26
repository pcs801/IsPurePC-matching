import struct
ROOT = r"E:/ONE PIECE/S/IsPurePC-matching"

def sections(path):
    data = open(path, "rb").read()
    e_shoff = struct.unpack_from("<I", data, 0x20)[0]
    e_shentsize = struct.unpack_from("<H", data, 0x2E)[0]
    e_shnum = struct.unpack_from("<H", data, 0x30)[0]
    e_shstrndx = struct.unpack_from("<H", data, 0x32)[0]
    shstr = e_shoff + e_shstrndx * e_shentsize
    shstr_off = struct.unpack_from("<I", data, shstr + 0x10)[0]
    shstr_size = struct.unpack_from("<I", data, shstr + 0x14)[0]
    strtab = data[shstr_off:shstr_off + shstr_size]
    out = {}
    for i in range(e_shnum):
        o = e_shoff + i * e_shentsize
        name_off, typ, flags, addr, off, size = struct.unpack_from("<IIIIII", data, o)
        end = strtab.find(b"\x00", name_off)
        name = strtab[name_off:end].decode()
        out[name] = dict(type=typ, addr=addr, off=off, size=size)
    return data, out

data, secs = sections(ROOT + "/build/splat/1000.o")
t = secs[".text"]
obj = data[t["off"]:t["off"] + t["size"]]
base = open(ROOT + "/baserom/SLPM_665.70", "rb").read()
orig = base[0x1000:0x1000 + 1124764]

rel = secs[".rel.text"]
relocs = {}
for k in range(0, rel["size"], 8):
    r_off, r_info = struct.unpack_from("<II", data, rel["off"] + k)
    rtype = r_info & 0xFF
    relocs[r_off] = rtype

print("relocations:", len(relocs), "of", len(obj) // 4, "words")

# relocation type masks (low bits that get patched)
# R_MIPS_16=1, R_MIPS_32=2, R_MIPS_26=4, R_MIPS_HI16=5, R_MIPS_LO16=6, R_MIPS_GPREL16=7 ...
MASKS = {1: 0x0000FFFF, 2: 0xFFFFFFFF, 4: 0x03FFFFFF, 5: 0x0000FFFF,
         6: 0x0000FFFF, 7: 0x0000FFFF, 8: 0x0000FFFF, 9: 0x0000FFFF,
         10: 0x0000FFFF, 11: 0x0000FFFF, 12: 0x0000FFFF, 13: 0x0000FFFF}

bad = []
covered = 0
for off, rtype in relocs.items():
    mask = MASKS.get(rtype, 0x0000FFFF)
    w_obj = int.from_bytes(obj[off:off+4], "little")
    w_org = int.from_bytes(orig[off:off+4], "little")
    if (w_obj & ~mask & 0xFFFFFFFF) != (w_org & ~mask & 0xFFFFFFFF):
        bad.append((off, rtype, hex(w_obj), hex(w_org)))

# bytes not covered by any reloc
reloc_bytes = set()
for off in relocs:
    for i in range(4):
        reloc_bytes.add(off + i)
uncovered_diffs = [i for i in range(len(obj)) if obj[i] != orig[i] and i not in reloc_bytes]
print("reloc words with opcode/reg mismatch:", len(bad))
print("byte diffs outside relocations:", len(uncovered_diffs))
if uncovered_diffs:
    print("sample:", [(hex(i), hex(obj[i]), hex(orig[i])) for i in uncovered_diffs[:10]])
if bad:
    print("sample bad:", bad[:5])
