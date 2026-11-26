import struct, re
ROOT = r"E:/ONE PIECE/S/IsPurePC-matching"
exec(open(ROOT + "/tools/reloc_resolver.py").read().split("def main()")[0])
data, secs, syms = parse_elf(ROOT + "/build/splat/1000.o")
t = secs[".text"]; text_idx = t["idx"]
asm_expr = load_asm_expressions(ROOT + "/asm/1000.s")
rel = secs[".rel.text"]
relocs = []
for k in range(0, rel["size"], 8):
    r_off, r_info = struct.unpack_from("<II", data, rel["off"] + k)
    relocs.append((r_off, r_info >> 8, r_info & 0xFF))
relocs.sort()
orphans = {}
i = 0
while i < len(relocs):
    off, sym_i, rtype = relocs[i]
    if rtype == 5:
        j = i + 1
        while j < len(relocs) and relocs[j][2] == 5 and relocs[j][1] == sym_i:
            j += 1
        if not (j < len(relocs) and relocs[j][2] == 6 and relocs[j][1] == sym_i):
            vram = 0x100000 + off
            addr, use_addend = sym_addr(syms[sym_i], text_idx, asm_expr, vram)
            if addr is not None:
                orphans["%08X" % vram] = ((addr + 0x8000) >> 16) & 0xFFFF
        i = j
    else:
        i += 1
print("orphans to literalize:", len(orphans))

lines = open(ROOT + "/asm/1000.s", encoding="utf-8", errors="replace").read().split("\n")
pat = re.compile(r"/\* [0-9A-Fa-f]+ ([0-9A-Fa-f]{8}) [0-9A-Fa-f]{8} \*/")
changed = 0
for idx, line in enumerate(lines):
    m = pat.search(line)
    if not m:
        continue
    key = m.group(1).upper()
    if key not in orphans:
        continue
    hi = orphans[key]
    new, n = re.subn(r"%hi\([^)]*\)", "0x%04X" % hi, line)
    if n:
        lines[idx] = new
        changed += 1
print("lines rewritten:", changed)
open(ROOT + "/asm/1000.ld.s", "w", encoding="utf-8").write("\n".join(lines))
