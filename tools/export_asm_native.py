#!/usr/bin/env python3
"""Export per-function assembly for C-unreachable (asm-native) functions.

Those functions contain instructions ee-gcc cannot emit from C (syscall, sync,
ei, cop0 moves, lq/sq). They are byte-exact by construction: the original
assembly IS the function. We publish one small .s per function so the progress
viewer can show real code instead of "no file defines it".

Two sources: the splat block (when the symbol is a real function boundary) and,
for symbols splat folded into a neighbour, the instruction lines sliced by
address from asm/1000.s.
"""
import csv, json, os, re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ASM = os.path.join(ROOT, "asm", "1000.s")
OUT = os.path.join(ROOT, "asm", "nonmatching")
PAT = re.compile(r"/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s*\*/")
HEADER = ("/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.\n"
          "   Byte-exact by construction - this is the original assembly. */\n")


def load_sizes():
    out = {}
    with open(os.path.join(ROOT, "config", "symbols.csv"), newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f):
            out[int(r["address"], 16)] = int(r["size"])
    return out


def main():
    addrs = [int(a, 16) for a in json.load(open(os.path.join(
        ROOT, "build", "m26-asm-native.json"), encoding="utf-8"))["addrs"]]
    sizes = load_sizes()
    text = open(ASM, encoding="utf-8", errors="replace").read().splitlines()
    blocks, by_addr = {}, {}
    writing, buf = None, []
    for line in text:
        m = re.match(r"^nonmatching\s+(FUN_[0-9a-f]{8}),", line)
        if m and writing is None:
            writing = m.group(1)
            buf = [line]
            continue
        if writing is not None:
            buf.append(line)
            if line.startswith("endlabel " + writing):
                blocks[writing] = "".join(buf)
                writing, buf = None, []
            continue
        mm = PAT.search(line)
        if mm:
            by_addr[int(mm.group(1), 16)] = line
    os.makedirs(OUT, exist_ok=True)
    n_block = n_slice = n_miss = 0
    for a in sorted(addrs):
        name = "FUN_%08x" % a
        body = blocks.get(name)
        if body:
            n_block += 1
        else:
            size = sizes.get(a)
            if not size:
                n_miss += 1
                print("no size", name)
                continue
            rows = [by_addr.get(a + i) for i in range(0, size, 4)]
            rows = [r if r is not None else "    /* gap at %08X */" % (a + i)
                    for i, r in enumerate(rows)]
            body = "nonmatching %s, 0x%X\n\nglabel %s\n%s\nendlabel %s\n" % (
                name, size, name, "\n".join(rows), name)
            n_slice += 1
        with open(os.path.join(OUT, "%08x.s" % a), "w", encoding="utf-8", newline="\n") as g:
            g.write(HEADER + body)
    print("blocks", n_block, "sliced", n_slice, "nosize", n_miss, "total", len(addrs))


if __name__ == "__main__":
    main()
