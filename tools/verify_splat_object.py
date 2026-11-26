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
print("sections:", {k: hex(v["size"]) for k, v in secs.items() if v["size"]})
t = secs[".text"]
obj_text = data[t["off"]:t["off"] + t["size"]]

base = open(ROOT + "/baserom/SLPM_665.70", "rb").read()
orig = base[0x1000:0x1000 + 1124764]
print("obj .text size:", len(obj_text), "orig .text size:", len(orig))
n = min(len(obj_text), len(orig))
diff = [i for i in range(n) if obj_text[i] != orig[i]]
print("differing bytes:", len(diff), "of", n)
if diff:
    print("first diffs:", [(hex(i), hex(obj_text[i]), hex(orig[i])) for i in diff[:10]])
# symbol table check
symtab = secs.get(".symtab")
print("symtab size:", hex(symtab["size"]) if symtab else None)
if symtab:
    strtab = secs.get(".strtab")
    n_syms = symtab["size"] // 16
    print("symbols:", n_syms)
