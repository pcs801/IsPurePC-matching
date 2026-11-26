#!/usr/bin/env python3
"""triage.py - classify every function into a difficulty tier, emit build/queue.json.

Inputs
  config/symbols.csv        addr,size,name for all functions
  asm/1000.s                splat disassembly (address, word, mnemonic, operands)
  config/build_config.json  per-function -G policy (g_map)

Output
  build/queue.json          ordered queue; each entry carries the fields the
                            matcher and claims.py need (addr, size, core, g).

Tier policy (M2.2; see docs/m2-2-batch.md)
  easy    leaf (no calls/tail-jumps), straight-line (no branches), no FPU,
          no syscall/cop2, only scalar integer instructions, core size 4..64
          and size == core (no trailing alignment padding).
  medium  leaf, no FPU/syscall, scalar only, core <= 160 (padding allowed and
          flagged); also easy-shaped functions that carry alignment padding.
  hard    everything else.

Why alignment padding matters: build.py requires len(compiled .text) == the
symbol size.  Some baserom functions are followed by trailing nops that C
cannot reproduce, so a padded function can never pass the byte gate.  They are
downgraded to medium with flags=["padding"] instead of being silently dropped.

This module is also imported by tools/auto_match.py for parse_symbols/parse_asm.
"""
import argparse
import bisect
import csv
import hashlib
import json
import os
import re
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SYMBOLS = os.path.join(ROOT, "config", "symbols.csv")
ASM = os.path.join(ROOT, "asm", "1000.s")
BUILD_CONFIG = os.path.join(ROOT, "config", "build_config.json")
OUT = os.path.join(ROOT, "build", "queue.json")

TIER_ORDER = {"easy": 0, "medium": 1, "hard": 2}

# An instruction stream with any of these is never "easy".
BRANCH_OPS = {
    "beq", "bne", "beqz", "bnez", "bgez", "bgezal", "blez", "bgtz", "bltz",
    "bltzal", "bnel", "bgtzl", "blezl", "beql", "bgezall", "bltzall",
    "bc0f", "bc0t", "bc1f", "bc1t", "bc2f", "bc2t",
}
JUMP_OPS = {"j", "jal", "jalr", "jr", "b", "bal"}
FPU_OPS = {
    "lwc1", "swc1", "ldc1", "sdc1", "mtc1", "mfc1", "ctc1", "cfc1",
    "mfhi1", "mflo1", "mthi1", "mtlo1", "madd1", "maddu1", "mfsa", "mtsa",
    "mtsah", "mfsah", "lqc2", "sqc2", "cop1", "cop2", "cfc2", "ctc2",
}
SYSCALL_OPS = {"syscall", "break"}
# Scalar integer ops the C matcher understands.  Anything else is "not scalar
# core" and is pushed out of the easy tier (packed/unaligned/128-bit/FPU/...).
CORE_OPS = {
    "nop", "move", "li", "la", "lui", "ori", "andi", "xori", "addiu",
    "daddiu", "addu", "daddu", "subu", "dsubu", "addi", "dadd", "and", "or",
    "xor", "nor", "sll", "srl", "sra", "dsll", "dsrl", "dsra", "dsll32",
    "dsrl32", "dsra32", "sllv", "srlv", "srav", "slt", "slti", "sltu",
    "sltiu", "mult", "multu", "div", "divu", "mflo", "mfhi", "movn", "movz",
    "negu", "neg", "lb", "lbu", "lh", "lhu", "lw", "lwu", "ld", "ll",
    "sb", "sh", "sw", "sd", "sc", "lwl", "lwr", "swl", "swr", "jr", "nop",
}
SIG_LEN = 12

INSN_RE = re.compile(
    r"/\*\s*([0-9A-Fa-f]+)\s+([0-9A-Fa-f]{8})\s+([0-9A-Fa-f]{8})\s*\*/\s*(.*)")


def sha1_file(path):
    h = hashlib.sha1()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def parse_symbols(path=SYMBOLS):
    rows = []
    with open(path, newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f):
            rows.append({"addr": int(r["address"], 16), "size": int(r["size"]),
                         "name": r["name"]})
    rows.sort(key=lambda r: r["addr"])
    return rows


def parse_asm(path=ASM, symbols=None):
    """Return {func_addr: [(addr, word, mnemonic, operands), ...]}."""
    if symbols is None:
        symbols = parse_symbols()
    starts = [s["addr"] for s in symbols]
    by_fn = {}
    cur = None
    with open(path, encoding="utf-8", errors="replace") as f:
        for line in f:
            m = INSN_RE.search(line)
            if not m:
                continue
            addr = int(m.group(2), 16)
            word = int(m.group(3), 16)
            parts = m.group(4).strip().split(None, 1)
            mn = parts[0] if parts else ""
            ops = parts[1].strip() if len(parts) > 1 else ""
            i = bisect.bisect_right(starts, addr) - 1
            if i < 0:
                continue
            cur = starts[i]
            by_fn.setdefault(cur, []).append((addr, word, mn, ops))
    return by_fn


def load_g_map(path=BUILD_CONFIG):
    """addr -> (class, [g values]) from configure.py output."""
    if not os.path.exists(path):
        return {}
    cfg = json.load(open(path, encoding="utf-8"))
    out = {}
    for e in cfg.get("g_map", []):
        try:
            addr = int(str(e["addr"]), 16)
        except (KeyError, ValueError):
            continue
        g = e.get("g", "0")
        if g == "try-both":
            gs = ["0", "8"]
        elif g == "either":
            gs = ["0"]
        elif g in ("0", "8"):
            gs = [g]
        else:
            try:
                gs = [str(int(g))]
            except ValueError:
                gs = ["0"]
        out[addr] = (e.get("cls", "unknown"), gs)
    return out


def core_size(body, size):
    """Bytes of actual code; trailing nops after jr's delay slot are padding."""
    last = -1
    for i, (_a, _w, mn, ops) in enumerate(body):
        if mn == "jr" and ops.replace(" ", "") == "$ra":
            last = i
    if last < 0:
        return size, 0
    end = (last + 2) * 4
    if end > size:
        return size, 0
    return end, size - end


def classify(addr, size, name, body, cls, gs):
    mns = [x[2] for x in body]
    calls = 0
    for i, (_a, _w, mn, ops) in enumerate(body):
        if mn in ("jal", "jalr", "b", "bal"):
            calls += 1
        elif mn == "j":
            calls += 1
        elif mn == "jr" and ops.replace(" ", "") != "$ra":
            calls += 1
        elif mn in ("jalx",):
            calls += 1
    branches = sum(1 for mn in mns if mn in BRANCH_OPS)
    returns = sum(1 for (_a, _w, mn, ops) in body
                  if mn == "jr" and ops.replace(" ", "") == "$ra")
    fpu = any(mn in FPU_OPS or ("." in mn and not mn.startswith("."))
              for mn in mns)
    syscall = any(mn in SYSCALL_OPS for mn in mns)
    unsupported = sorted({mn for mn in mns
                          if mn not in CORE_OPS and mn not in BRANCH_OPS
                          and mn not in JUMP_OPS and mn not in FPU_OPS
                          and mn not in SYSCALL_OPS})
    core, padding = core_size(body, size)
    leaf = calls == 0
    straight = branches == 0
    gp = any("$gp" in ops for (_a, _w, _mn, ops) in body)
    flags = []
    if not leaf:
        flags.append("calls")
    if returns > 1:
        flags.append("multi-return")
    if not straight:
        flags.append("branch")
    if fpu:
        flags.append("fpu")
    if syscall:
        flags.append("syscall")
    if unsupported:
        flags.append("non-scalar:" + ",".join(unsupported))
    if padding:
        flags.append("padding")
    if gp:
        flags.append("gp")
    if not body:
        flags.append("no-disasm")

    if not body:
        tier, reason = "hard", "no disassembly"
    elif not leaf:
        tier, reason = "hard", "has calls/tail-jumps"
    elif returns > 1:
        tier, reason = "hard", "multiple return points"
    elif fpu or syscall:
        tier, reason = "hard", "fpu/syscall"
    elif unsupported:
        tier, reason = "hard", "non-scalar instructions"
    elif not straight:
        tier = "medium" if core <= 96 and not fpu else "hard"
        reason = "has branches"
    elif padding:
        tier, reason = "medium", "alignment padding not reproducible from C"
    elif core <= 64:
        tier, reason = "easy", ""
    elif core <= 160:
        tier, reason = "medium", "larger straight-line body"
    else:
        tier, reason = "hard", "large body"

    # Lower score = tried earlier.  Size dominates; single-easy-idiom
    # functions (2 instructions) come first inside the same size.
    score = core
    if not straight:
        score += 200
    if not leaf:
        score += 400
    if padding:
        score += 50
    score += min(len(unsupported), 4) * 25
    return {
        "addr": "0x%08X" % addr,
        "addr_i": addr,
        "name": name,
        "size": size,
        "core": core,
        "padding": padding,
        "cls": cls,
        "g": gs,
        "tier": tier,
        "score": score,
        "ins": len(body),
        "leaf": leaf,
        "straight": straight,
        "fpu": fpu,
        "syscall": syscall,
        "gp": gp,
        "calls": calls,
        "branches": branches,
        "unsupported": unsupported,
        "flags": flags,
        "sig": " ; ".join(mns[:SIG_LEN]),
        "reason": reason,
    }


def build_queue():
    symbols = parse_symbols()
    by_fn = parse_asm(symbols=symbols)
    gmap = load_g_map()
    entries = []
    for s in symbols:
        addr, size, name = s["addr"], s["size"], s["name"]
        cls, gs = gmap.get(addr, ("local", ["0"]))
        entries.append(classify(addr, size, name, by_fn.get(addr, []), cls, gs))
    entries.sort(key=lambda e: (TIER_ORDER.get(e["tier"], 9), e["score"],
                                e["addr_i"]))
    for i, e in enumerate(entries):
        e["rank"] = i + 1
    return entries


def summarize(entries):
    by_tier = {}
    for e in entries:
        by_tier.setdefault(e["tier"], []).append(e)
    stats = {"total": len(entries)}
    for t in ("easy", "medium", "hard"):
        rows = by_tier.get(t, [])
        sizes = {}
        for e in rows:
            sizes[e["core"]] = sizes.get(e["core"], 0) + 1
        stats[t] = {
            "count": len(rows),
            "sizes": dict(sorted(sizes.items())),
            "padded": sum(1 for e in rows if e["padding"]),
            "with_calls": sum(1 for e in rows if not e["leaf"]),
            "with_branch": sum(1 for e in rows if not e["straight"]),
            "fpu": sum(1 for e in rows if e["fpu"]),
            "gp": sum(1 for e in rows if e["gp"]),
        }
    stats["easy_addrs"] = [e["addr"] for e in by_tier.get("easy", [])]
    return stats


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--out", default=OUT)
    ap.add_argument("--quiet", action="store_true")
    args = ap.parse_args(argv)
    t0 = time.time()
    entries = build_queue()
    stats = summarize(entries)
    doc = {
        "schema": 1,
        "project": "IsPurePC-Matching",
        "generated": time.strftime("%Y-%m-%dT%H:%M:%S%z"),
        "source": {
            "symbols": os.path.relpath(SYMBOLS, ROOT),
            "symbols_sha1": sha1_file(SYMBOLS),
            "asm": os.path.relpath(ASM, ROOT),
            "asm_sha1": sha1_file(ASM),
        },
        "policy": {
            "easy": "leaf, straight-line, scalar-integer only, core 4..64 bytes, no padding",
            "medium": "leaf scalar straight-line <=160 core, or easy body with padding/branches",
            "hard": "everything else (calls, fpu, syscall, non-scalar, large)",
            "score": "core + 50*padding + 200*branch + 400*calls + 25*unsupported",
            "order": "tier, score, addr ascending",
        },
        "stats": stats,
        "entries": entries,
    }
    os.makedirs(os.path.dirname(args.out), exist_ok=True)
    with open(args.out, "w", newline="\n", encoding="utf-8") as f:
        json.dump(doc, f, indent=1, ensure_ascii=False)
        f.write("\n")
    if not args.quiet:
        print("queue -> %s (%d functions, %.1fs)" % (
            os.path.relpath(args.out, ROOT), len(entries), time.time() - t0))
        for t in ("easy", "medium", "hard"):
            s = stats[t]
            sz = ", ".join("%dB:%d" % (k, v) for k, v in s["sizes"].items())
            print("  %-6s %4d   padded=%-3d calls=%-4d branch=%-3d fpu=%-3d gp=%-3d  [%s]" % (
                t, s["count"], s["padded"], s["with_calls"], s["with_branch"],
                s["fpu"], s["gp"], sz))
        print("easy addrs (first 20):", " ".join(stats["easy_addrs"][:20]))
    return 0


if __name__ == "__main__":
    sys.exit(main())
