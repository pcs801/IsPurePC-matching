import re, struct

ROOT = r"E:/ONE PIECE/S/IsPurePC-matching"
TEXT_VRAM = 0x00100000


def parse_elf(path):
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
        link, info, align, entsize = struct.unpack_from("<IIII", data, o + 0x18)
        end = strtab.find(b"\x00", name_off)
        secs[strtab[name_off:end].decode()] = dict(
            idx=i, type=typ, off=off, size=size, link=link, entsize=entsize)
    sym = secs[".symtab"]
    st = secs[".strtab"]
    syms = []
    for i in range(sym["size"] // 16):
        o = sym["off"] + i * 16
        name_off, value, size, info, other, shndx = struct.unpack_from("<IIIBBH", data, o)
        end = data.find(b"\x00", st["off"] + name_off)
        syms.append(dict(name=data[st["off"] + name_off:end].decode(),
                         value=value, size=size, shndx=shndx, info=info))
    return data, secs, syms


def load_asm_expressions(path):
    """vram hex -> raw operand text, for %hi/%lo expression recovery."""
    out = {}
    pat = re.compile(r"/\* [0-9A-Fa-f]+ ([0-9A-Fa-f]{8}) [0-9A-Fa-f]{8} \*/\s+\S+\s+(.*)$")
    for line in open(path, encoding="utf-8", errors="replace"):
        m = pat.search(line)
        if m:
            out[m.group(1).upper()] = m.group(2)
    return out


EXPR_NUM = re.compile(r"^(?:D_|FUN_|func_|D_)?([0-9A-Fa-f]{1,8})(?:\s*\+\s*(0x[0-9A-Fa-f]+|\d+))?$")


def parse_expr(text):
    text = text.strip()
    m = EXPR_NUM.match(text)
    if not m:
        return None
    val = int(m.group(1), 16)
    if m.group(2):
        val += int(m.group(2), 0)
    return val


def sym_addr(sym, text_idx, asm_expr, vram):
    """Return (address, uses_instruction_addend).

    A section symbol recovered from the asm expression already carries the
    full address, so the instruction immediate is not an addend any more.
    """
    if sym["shndx"] == text_idx and sym["name"]:
        return TEXT_VRAM + sym["value"], True
    if sym["shndx"] == 0:
        name = sym["name"]
        for pref in ("FUN_", "D_", "func_"):
            if name.startswith(pref):
                try:
                    return int(name[len(pref):].split(".")[0], 16), True
                except ValueError:
                    pass
        return None
    # section symbol (empty name): recover the address from the asm expression
    operands = asm_expr.get("%08X" % vram)
    if operands:
        for marker in ("%hi(", "%lo(", "%gp_rel("):
            idx = operands.find(marker)
            if idx != -1:
                inner = operands[idx + len(marker):]
                inner = inner[:inner.find(")")]
                v = parse_expr(inner)
                if v is not None:
                    return v, False
    return TEXT_VRAM + sym["value"], True


def resolve(obj_path, asm_path):
    data, secs, syms = parse_elf(obj_path)
    t = secs[".text"]
    text = bytearray(data[t["off"]:t["off"] + t["size"]])
    text_idx = t["idx"]
    asm_expr = load_asm_expressions(asm_path)
    rel = secs[".rel.text"]
    relocs = []
    for k in range(0, rel["size"], 8):
        r_off, r_info = struct.unpack_from("<II", data, rel["off"] + k)
        relocs.append((r_off, r_info >> 8, r_info & 0xFF))
    relocs.sort()

    applied = {4: 0, 5: 0, 6: 0}
    unresolved = 0
    i = 0
    while i < len(relocs):
        off, sym_i, rtype = relocs[i]
        sym = syms[sym_i]
        vram = TEXT_VRAM + off
        addr, use_addend = sym_addr(sym, text_idx, asm_expr, vram)
        if addr is None:
            unresolved += 1
            i += 1
            continue
        if rtype == 4:
            w = int.from_bytes(text[off:off + 4], "little")
            a = (w & 0x03FFFFFF) << 2
            v = (addr + a) >> 2
            w = (w & 0xFC000000) | (v & 0x03FFFFFF)
            text[off:off + 4] = w.to_bytes(4, "little")
            applied[4] += 1
            i += 1
        elif rtype == 5:
            his = [off]
            j = i + 1
            while j < len(relocs) and relocs[j][2] == 5 and relocs[j][1] == sym_i:
                his.append(relocs[j][0])
                j += 1
            if j < len(relocs) and relocs[j][2] == 6 and relocs[j][1] == sym_i:
                lo_off = relocs[j][0]
                lo_w = int.from_bytes(text[lo_off:lo_off + 4], "little")
                a = lo_w & 0xFFFF
                if use_addend:
                    if a & 0x8000:
                        a -= 0x10000
                else:
                    a = 0
                v = addr + a
                hi = ((v + 0x8000) >> 16) & 0xFFFF
                lo = v & 0xFFFF
                for h in his:
                    hw = int.from_bytes(text[h:h + 4], "little")
                    hw = (hw & 0xFFFF0000) | hi
                    text[h:h + 4] = hw.to_bytes(4, "little")
                lo_w = (lo_w & 0xFFFF0000) | lo
                text[lo_off:lo_off + 4] = lo_w.to_bytes(4, "little")
                applied[5] += len(his)
                applied[6] += 1
                i = j + 1
            else:
                hw = int.from_bytes(text[off:off + 4], "little")
                a = hw & 0xFFFF
                if use_addend:
                    if a & 0x8000:
                        a -= 0x10000
                else:
                    a = 0
                v = addr + a
                hi = ((v + 0x8000) >> 16) & 0xFFFF
                hw = (hw & 0xFFFF0000) | hi
                text[off:off + 4] = hw.to_bytes(4, "little")
                applied[5] += 1
                i += 1
        else:
            i += 1
    return bytes(text), dict(applied=applied, unresolved=unresolved, total=len(relocs))


def main():
    resolved, stats = resolve(ROOT + "/build/splat/1000.o", ROOT + "/asm/1000.s")
    base = open(ROOT + "/baserom/SLPM_665.70", "rb").read()
    orig = base[0x1000:0x1000 + 1124764]
    diffs = [i for i in range(len(orig)) if resolved[i] != orig[i]]
    print("stats:", stats)
    print("diff bytes:", len(diffs), "diff words:", len({(i // 4) * 4 for i in diffs}))
    if diffs:
        print("first:", [(hex(i), hex(resolved[i]), hex(orig[i])) for i in diffs[:10]])
    open(ROOT + "/build/splat/1000.resolved.bin", "wb").write(resolved)


if __name__ == "__main__":
    main()
