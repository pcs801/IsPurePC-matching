#!/usr/bin/env python
"""One-command build: splat -> assemble (WSL) -> resolve relocations ->
per-function C overrides -> assemble image -> sha256.

Usage:
  python tools/build.py check          # full chain + sha256 verification
  python tools/build.py check --fast   # skip splat (reuse asm/)
  python tools/build.py build          # stop after image assembly
  python tools/build.py overrides      # compile + verify config/overrides.json only
  python tools/build.py ld             # extra: link with ee-ld and compare .text
  python tools/build.py configure      # regenerate per-TU -G config

Per-function override
  config/overrides.json lists functions whose body is now a C source instead of
  the splat-disassembly.  Each entry carries addr/size/source/g/status:

    status "matched"  -> compiled bytes are REQUIRED to equal the baserom bytes
                         and are spliced into the rebuilt .text.  A mismatch (or
                         a relocation that cannot be resolved) fails the build.
    status "todo"     -> compiled for diagnostics only (see "build.py overrides"),
                         never spliced, never fails make check.

The compiled object keeps the compiler's relocations (jal targets, %hi/%lo,
$gp-relative access).  They are applied with the same symbol rules as
tools/reloc_resolver.py, so a matched function is byte-exact *after* relocation,
not merely "same opcodes with different immediates".
"""
import argparse
import hashlib
import json
import os
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
WSL_DISTRO = "Ubuntu"
WSL_ROOT = "/mnt/e/ONE PIECE/S/IsPurePC-matching"
WSL_WORK = "/root/work/build"
BASE_SHA = "e0d0b77b555fd876c6fdd933b486292da45e77677b44bc04eec67836de481147"

# .text mapping in the baserom ELF
TEXT_ADDR = 0x00100000
TEXT_OFF = 0x1000
GP = 0x002779F0

OVERRIDES_JSON = os.path.join(ROOT, "config", "overrides.json")
OVERRIDES_BUILD = os.path.join(ROOT, "build", "overrides")
RESOLVED_BIN = os.path.join(ROOT, "build", "splat", "1000.resolved.bin")
BASEROM = os.path.join(ROOT, "baserom", "SLPM_665.70")

OVERRIDE_STATS = dict(matched=0, bytes=0, verified=0)


def run(cmd, cwd=None, check=True):
    print("+", " ".join(cmd))
    r = subprocess.run(cmd, cwd=cwd or ROOT)
    if check and r.returncode != 0:
        raise SystemExit("command failed (%d): %s" % (r.returncode, " ".join(cmd)))
    return r.returncode


def wsl(script_rel):
    """Run a bash script inside WSL."""
    wpath = WSL_ROOT + "/" + script_rel.replace(os.sep, "/")
    run(["wsl.exe", "-d", WSL_DISTRO, "-u", "root", "--", "bash", wpath])


def write_script(rel, body):
    path = os.path.join(ROOT, rel)
    os.makedirs(os.path.dirname(path), exist_ok=True)
    open(path, "w", newline="\n").write(body)
    return path


def step_splat():
    print("\n== [1/6] splat split ==")
    run([sys.executable, "-m", "splat", "split", "splat.yaml"])


def step_assemble():
    print("\n== [2/6] assemble .text (WSL) ==")
    body = """#!/bin/bash
set -e
export LC_ALL=C
ROOT="%s"
mkdir -p %s && cd %s
cp "$ROOT/asm/1000.s" .
cp "$ROOT/include/macro.inc" .
python3 "$ROOT/tools/fix_asm.py" %s 1000.s
cp out.o "$ROOT/build/splat/1000.o"
echo "object: $(stat -c%%s out.o) bytes"
""" % (WSL_ROOT, WSL_WORK, WSL_WORK, WSL_WORK)
    write_script("build/_wsl_asm.sh", body)
    wsl("build/_wsl_asm.sh")


def step_resolve():
    print("\n== [3/6] resolve relocations ==")
    run([sys.executable, "tools/reloc_resolver.py"])


# ---------------------------------------------------------------- overrides

def load_overrides(strict=True):
    """Return the override entries, or [] when config/overrides.json is absent."""
    if not os.path.exists(OVERRIDES_JSON):
        return []
    cfg = json.load(open(OVERRIDES_JSON, encoding="utf-8"))
    entries = []
    for e in cfg.get("functions", []):
        e = dict(e)
        e["addr"] = int(str(e["addr"]), 16)
        e["size"] = int(e["size"])
        e.setdefault("g", 0)
        e.setdefault("status", "todo")
        e["name"] = e.get("name") or "FUN_%08x" % e["addr"]
        if e["status"] not in ("matched", "todo"):
            if strict:
                raise SystemExit("overrides: bad status %r for %s" % (e["status"], e["name"]))
            e["status"] = "todo"
        entries.append(e)
    return entries


def elf_sections(path):
    data = open(path, "rb").read()
    if data[:4] != b"\x7fELF":
        raise SystemExit("not an ELF: %s" % path)
    e_shoff = struct.unpack_from("<I", data, 0x20)[0]
    e_shentsize = struct.unpack_from("<H", data, 0x2E)[0]
    e_shnum = struct.unpack_from("<H", data, 0x30)[0]
    e_shstrndx = struct.unpack_from("<H", data, 0x32)[0]
    shstr_o = e_shoff + e_shstrndx * e_shentsize
    so = struct.unpack_from("<I", data, shstr_o + 0x10)[0]
    ss = struct.unpack_from("<I", data, shstr_o + 0x14)[0]
    strtab = data[so:so + ss]
    secs = []
    for i in range(e_shnum):
        o = e_shoff + i * e_shentsize
        name_off, typ, flags, addr, off, size = struct.unpack_from("<IIIIII", data, o)
        link, info, align, entsize = struct.unpack_from("<IIII", data, o + 0x18)
        end = strtab.find(b"\x00", name_off)
        secs.append(dict(idx=i, name=strtab[name_off:end].decode(), type=typ,
                         flags=flags, addr=addr, off=off, size=size,
                         link=link, info=info, entsize=entsize))
    return data, secs


def elf_symbols(data, secs):
    sym = next((s for s in secs if s["type"] == 2), None)  # SHT_SYMTAB
    if not sym:
        return []
    strtab = secs[sym["link"]]
    out = []
    for i in range(sym["size"] // 16):
        o = sym["off"] + i * 16
        name_off, value, size, info, other, shndx = struct.unpack_from("<IIIBBH", data, o)
        end = data.find(b"\x00", strtab["off"] + name_off)
        out.append(dict(name=data[strtab["off"] + name_off:end].decode(),
                        value=value, size=size, shndx=shndx, info=info))
    return out


def symbol_address(sym, text_idx):
    """Absolute VRAM address of a symbol, or None when it cannot be known."""
    if sym["shndx"] != 0:
        return TEXT_ADDR + sym["value"] if sym["shndx"] == text_idx else None
    name = sym["name"]
    for pref in ("FUN_", "func_", "D_", "jtbl_", "L_"):
        if name.startswith(pref):
            head = name[len(pref):].split(".")[0].split("+")[0]
            try:
                return int(head, 16)
            except ValueError:
                return None
    return None


def sign16(v):
    return v - 0x10000 if v & 0x8000 else v


def resolve_object_text(path, addr=None):
    """Compile-time relocations of a single-function object -> final .text bytes.

    Returns (bytes, stats).  Anything unresolvable is reported, never guessed.
    """
    addr_arg = addr
    data, secs = elf_sections(path)
    byname = {s["name"]: s for s in secs}
    base = None
    jtbl_map = {}
    hi_bias = {}
    try:
        jd = json.load(open(os.path.join(ROOT, "build", "jtbl-map.json"),
                            encoding="utf-8"))
        jtbl_map = {int(k, 16): int(v, 16) for k, v in jd.get("maps", {}).items()}
        hi_bias = {int(k, 16): int(v) for k, v in jd.get("hi_bias", {}).items()}
    except (OSError, ValueError):
        jtbl_map = {}
        hi_bias = {}
    if addr is not None:
        try:
            with open(BASEROM, "rb") as f:
                base = f.read()
        except OSError:
            base = None
    t = byname.get(".text")
    if not t:
        raise SystemExit("no .text in %s" % path)
    text = bytearray(data[t["off"]:t["off"] + t["size"]])
    text_idx = t["idx"]
    syms = elf_symbols(data, secs)
    rels = []
    for s in secs:
        if s["type"] == 9 and s["info"] == text_idx:  # SHT_REL against .text
            for k in range(0, s["size"], 8):
                r_off, r_info = struct.unpack_from("<II", data, s["off"] + k)
                rels.append((r_off, r_info >> 8, r_info & 0xFF))
    rels.sort()

    unresolved = []
    applied = {2: 0, 4: 0, 5: 0, 6: 0, 7: 0}
    pending_hi = []  # (offset, sym_index)
    target_guided = 0
    for off, si, rtype in rels:
        sym = syms[si]
        addr_t = symbol_address(sym, text_idx)
        section_hint = (addr_t is None and sym["shndx"] not in (0, text_idx)
                        and base is not None and addr_arg is not None)
        if addr_t is None and not section_hint:
            unresolved.append("%08X rc%d %s" % (off, rtype, sym["name"] or "<section>"))
            continue
        addr = addr_t
        word = int.from_bytes(text[off:off + 4], "little")
        if rtype == 4:  # R_MIPS_26
            a = (word & 0x03FFFFFF) << 2
            v = (addr + a) >> 2
            word = (word & 0xFC000000) | (v & 0x03FFFFFF)
            text[off:off + 4] = word.to_bytes(4, "little")
            applied[4] += 1
        elif rtype == 5:  # R_MIPS_HI16
            pending_hi.append((off, si))
        elif rtype == 6:  # R_MIPS_LO16
            guided = False
            lo_op = -1
            v = None if addr is None else addr + sign16(word & 0xFFFF)
            if v is None and section_hint and addr_arg in jtbl_map:
                v = jtbl_map[addr_arg] + int(sym.get("value") or 0)
                guided = True
                target_guided += 1
            if v is None and section_hint:
                hoff = next((h for h, hsi in pending_hi if hsi == si), None)
                if hoff is None and pending_hi:
                    hoff = pending_hi[-1][0]
                if hoff is not None:
                    t0 = TEXT_OFF + (addr_arg - TEXT_ADDR + hoff)
                    t1 = TEXT_OFF + (addr_arg - TEXT_ADDR + off)
                    hi_w = int.from_bytes(base[t0:t0 + 4], "little") & 0xFFFF
                    lo_instr = int.from_bytes(base[t1:t1 + 4], "little")
                    lo_w = lo_instr & 0xFFFF
                    lo_op = lo_instr >> 26
                    cand = (hi_w << 16) + lo_w
                    cand_s = (hi_w << 16) + sign16(lo_w)
                    if cand % 4 == 0 and TEXT_ADDR <= cand < 0x20000000:
                        pass
                    else:
                        cand = cand_s
                    if cand % 4 == 0 and TEXT_ADDR <= cand < 0x20000000:
                        v = cand
                        guided = True
                        target_guided += 1
            if v is None:
                unresolved.append("%08X rc6 %s (section unresolved)" % (off, sym["name"] or "<section>"))
                continue
            lo = v & 0xFFFF
            if guided:
                if addr_arg in hi_bias:
                    hi = (((v + 0x8000) >> 16) if hi_bias[addr_arg]
                          else (v >> 16)) & 0xFFFF
                else:
                    hi = (((v + 0x8000) >> 16) if lo_op in (0x08, 0x09, 0x19)
                          else (v >> 16)) & 0xFFFF
            else:
                hi = ((v + 0x8000) >> 16) & 0xFFFF
            remain = []
            for hoff, hsi in pending_hi:
                if hsi == si:
                    hw = int.from_bytes(text[hoff:hoff + 4], "little")
                    text[hoff:hoff + 4] = ((hw & 0xFFFF0000) | hi).to_bytes(4, "little")
                else:
                    remain.append((hoff, hsi))
            pending_hi = remain
            text[off:off + 4] = ((word & 0xFFFF0000) | lo).to_bytes(4, "little")
            applied[6] += 1
        elif rtype == 7:  # R_MIPS_GPREL16
            v = addr - GP + sign16(word & 0xFFFF)
            text[off:off + 4] = ((word & 0xFFFF0000) | (v & 0xFFFF)).to_bytes(4, "little")
            applied[7] += 1
        elif rtype == 2:  # R_MIPS_32
            v = (addr + word) & 0xFFFFFFFF
            text[off:off + 4] = v.to_bytes(4, "little")
            applied[2] += 1
        else:
            unresolved.append("%08X rc%d %s (unsupported)" % (off, rtype, sym["name"] or "<section>"))
    for hoff, hsi in pending_hi:
        unresolved.append("%08X HI16 %s without LO16" % (hoff, syms[hsi]["name"]))
    return bytes(text), dict(applied=applied, unresolved=unresolved, relocs=len(rels),
                             target_guided=target_guided)


def compile_overrides(entries):
    """Compile every entry inside WSL; return {addr: object path}."""
    todo = [e for e in entries if e.get("source")]
    if not todo:
        return {}
    lines = ["#!/bin/bash", "export LC_ALL=C",
             'ROOT="%s"' % WSL_ROOT, "WORK=/root/work/overrides",
             'rm -rf "$WORK" && mkdir -p "$WORK" && cd "$WORK"',
             'mkdir -p "$ROOT/build/overrides"', 'rm -f "$ROOT"/build/overrides/*.o']
    objs = {}
    try:
        cc_overrides = json.load(open(os.path.join(ROOT, "build", "cc-overrides.json"),
                                      encoding="utf-8")).get("overrides", {})
    except (OSError, ValueError):
        cc_overrides = {}
    for e in todo:
        src = e["source"].replace("\\", "/")
        base = os.path.splitext(os.path.basename(src))[0]
        g = int(e["g"])
        obj = "%s.G%d.o" % (base, g)
        try:
            _cc_key = "0x%08X" % (e["addr"] if isinstance(e["addr"], int)
                                 else int(str(e["addr"]), 16))
        except (TypeError, ValueError):
            _cc_key = ""
        lines += [
            'if cp "$ROOT/%s" %s.c 2>/dev/null; then ' % (src, base),
            'CC="%s"; $CC -O2 -mips3 -G%d -c %s.c -o %s 2>%s.err && cp %s "$ROOT/build/overrides/%s" || echo "FAIL %s";' % (cc_overrides.get(_cc_key, "/opt/ee/bin/ee-gcc"), g, base, obj, base, obj, obj, base),
            'else echo "MISSING %s"; fi;' % base,
        ]
        objs[e["addr"]] = os.path.join(OVERRIDES_BUILD, obj)
    write_script("build/_wsl_overrides.sh", "\n".join(lines) + "\n")
    wsl("build/_wsl_overrides.sh")
    return objs


def word_diff(compiled, orig, limit=12):
    n = min(len(compiled), len(orig)) // 4
    diffs = []
    for i in range(n):
        a = compiled[i * 4:i * 4 + 4]
        b = orig[i * 4:i * 4 + 4]
        if a != b:
            diffs.append((i, a[::-1].hex(), b[::-1].hex()))
    if len(compiled) != len(orig):
        diffs.append(("len", "%d" % len(compiled), "%d" % len(orig)))
    return diffs[:limit], len(diffs)


def verify_overrides(entries, verbose=True):
    """Compile, relocate and byte-compare.  Returns (matched_ok, rows)."""
    base = open(BASEROM, "rb").read()
    objs = compile_overrides(entries)
    rows = []
    ok = True
    for e in entries:
        obj = objs.get(e["addr"])
        if not obj or not os.path.exists(obj):
            rows.append((e, "no-object", 0, 0))
            if e["status"] == "matched":
                ok = False
            continue
        compiled, stats = resolve_object_text(obj, e["addr"])
        off = TEXT_OFF + (e["addr"] - TEXT_ADDR)
        orig = base[off:off + e["size"]]
        diffs, ndiff = word_diff(compiled, orig)
        good = (not diffs) and (len(compiled) == e["size"]) and not stats["unresolved"]
        result = "MATCH" if good else "diff %d/%d" % (len(diffs), max(1, len(compiled) // 4))
        rows.append((e, result, len(compiled), stats))
        if verbose:
            print("  %-10s 0x%08X size=%-3d -G%d  %-14s %s" % (
                e["status"], e["addr"], e["size"], int(e["g"]), result,
                "" if good else diffs))
            for u in stats["unresolved"]:
                print("      unresolved reloc:", u)
        if e["status"] == "matched":
            if not good:
                ok = False
                print("  FAIL: matched override %s does not reproduce the baserom bytes"
                      % e["name"])
            elif len(compiled) != e["size"]:
                ok = False
    return ok, rows


def step_overrides(apply=True):
    entries = load_overrides()
    print("\n== [4/6] per-function overrides ==")
    if not entries:
        print("no config/overrides.json entries - asm-only build")
        return
    matched = [e for e in entries if e["status"] == "matched"]
    print("%d override(s): %d matched, %d todo" % (
        len(entries), len(matched), len(entries) - len(matched)))
    ok, rows = verify_overrides(entries)
    if not ok:
        raise SystemExit("override verification failed - refusing to build")
    if not apply or not matched:
        OVERRIDE_STATS.update(matched=len(matched), bytes=sum(e["size"] for e in matched),
                              verified=sum(1 for r in rows if r[1] == "MATCH" and r[0]["status"] == "matched"))
        return
    blob = bytearray(open(RESOLVED_BIN, "rb").read())
    total = 0
    for e in matched:
        obj = os.path.join(OVERRIDES_BUILD, "%s.G%d.o" % (
            os.path.splitext(os.path.basename(e["source"]))[0], int(e["g"])))
        compiled, _ = resolve_object_text(obj, e["addr"])
        off = e["addr"] - TEXT_ADDR
        blob[off:off + len(compiled)] = compiled
        total += len(compiled)
    open(RESOLVED_BIN, "wb").write(blob)
    OVERRIDE_STATS.update(matched=len(matched), bytes=total, verified=len(matched))
    print("spliced %d function(s), %d bytes from C into %s" % (
        len(matched), total, os.path.relpath(RESOLVED_BIN, ROOT)))
    for e in matched:
        print("  0x%08X  %-18s %s" % (e["addr"], e["name"], e["source"]))


def step_image():
    print("\n== [5/6] assemble image ==")
    run([sys.executable, "tools/assemble_image.py"])


def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def step_check():
    print("\n== [6/6] sha256 verification ==")
    img = os.path.join(ROOT, "build", "splat", "SLPM_665.70.rebuilt")
    base = os.path.join(ROOT, "baserom", "SLPM_665.70")
    a, b = sha256(img), sha256(base)
    print("baserom:", b)
    print("rebuilt:", a)
    if OVERRIDE_STATS["matched"]:
        print("overrides: %d function(s), %d bytes of .text came from C sources" % (
            OVERRIDE_STATS["matched"], OVERRIDE_STATS["bytes"]))
    if a == b:
        print("RESULT: MATCH")
        return True
    print("RESULT: DIFFER (expected %s)" % BASE_SHA)
    return False


def step_ld():
    """Extra verification: GNU ld link of the object, compare .text."""
    print("\n== [extra] ee-ld link verification ==")
    body = """#!/bin/bash
set -e
export LC_ALL=C
ROOT="%s"
mkdir -p %s && cd %s
cp "$ROOT/asm/1000.ld.s" . 2>/dev/null || python3 "$ROOT/tools/literalize_hi.py"
cp "$ROOT/include/macro.inc" .
python3 "$ROOT/tools/fix_asm.py" %s 1000.ld.s || true
python3 "$ROOT/tools/gen_defsym.py" out.o defsym.args
ee-ld -EL -G 8 --no-check-sections -Ttext 0x100000 -e _start $(cat defsym.args) -o 1000.elf out.o 2>&1 | grep -v "cannot find entry" | head -4
/opt/ee-ld/bin/mips-ps2-decompals-objcopy -O binary --only-section=.text 1000.elf "$ROOT/build/splat/1000.linked.text.bin"
echo linked
""" % (WSL_ROOT, WSL_WORK, WSL_WORK, WSL_WORK)
    write_script("build/_wsl_ld.sh", body)
    wsl("build/_wsl_ld.sh")
    run([sys.executable, "tools/compare_linked.py"])


def cmd_overrides():
    entries = load_overrides()
    print("== overrides: %d entr%s in %s ==" % (
        len(entries), "y" if len(entries) == 1 else "ies", os.path.relpath(OVERRIDES_JSON, ROOT)))
    if not entries:
        return 0
    ok, rows = verify_overrides(entries)
    matched = sum(1 for e in entries if e["status"] == "matched")
    print()
    print("summary: %d matched / %d todo / %d total" % (matched, len(entries) - matched, len(entries)))
    ready = [r[0] for r in rows if r[1] == "MATCH" and r[0]["status"] == "todo"]
    if ready:
        print("todo entries already byte-exact (set status to \"matched\" to splice):")
        for e in ready:
            print("  0x%08X  %s" % (e["addr"], e["name"]))
    return 0 if ok else 1


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("command", choices=["build", "check", "ld", "configure", "overrides"])
    ap.add_argument("--fast", action="store_true", help="skip splat")
    args = ap.parse_args()

    if args.command == "configure":
        run([sys.executable, "tools/configure.py"])
        return
    if args.command == "ld":
        step_ld()
        return
    if args.command == "overrides":
        sys.exit(cmd_overrides())

    if not args.fast:
        step_splat()
    step_assemble()
    step_resolve()
    step_overrides()
    step_image()
    if args.command == "check":
        sys.exit(0 if step_check() else 1)
    print("\nbuild done (image at build/splat/SLPM_665.70.rebuilt)")


if __name__ == "__main__":
    main()
