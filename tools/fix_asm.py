#!/usr/bin/env python3
"""Assemble splat output with ee-as 2.10, rewriting unsupported instructions as .word.

ee-as 2.10 does not accept the R5900 MMI mnemonics that spimdisasm emits
(padduw/daddu/mult ...), nor several modern gas pseudo-ops.  This tool loops:

  assemble -> collect "1000.s:LINE: Error:" -> replace that line with
  .word 0x<raw word from the trailing comment, byte-swapped> -> repeat

Byte fidelity is preserved because the comment carries the original word.

Run inside WSL (ee-gcc lives at /opt/ee).
Usage: python3 fix_asm.py <workdir> <asm_filename>
"""
import os
import re
import subprocess
import sys

AS = "/opt/ee/bin/ee-as"


def main():
    workdir = sys.argv[1] if len(sys.argv) > 1 else "/root/work/asmtest"
    fname = sys.argv[2] if len(sys.argv) > 2 else "1000.s"
    os.chdir(workdir)
    path = os.path.join(workdir, fname)
    lines = open(path).read().split("\n")
    args = [AS, "-EL", "-mips3", "-I.", "-o", "out.o", fname]

    for iteration in range(40):
        p = subprocess.run(args, capture_output=True, text=True)
        bad = set()
        for m in re.finditer(re.escape(fname) + r":(\d+): Error:", p.stderr):
            bad.add(int(m.group(1)))
        if not bad:
            print("clean after", iteration, "iterations; rc =", p.returncode)
            tail = p.stderr.strip()
            if tail:
                print(tail[-800:])
            return 0
        fixed = 0
        for ln in bad:
            line = lines[ln - 1]
            m = re.search(r"/\* [0-9A-Fa-f]+ [0-9A-Fa-f]+ ([0-9A-Fa-f]{8}) \*/", line)
            if not m:
                continue
            val = bytes.fromhex(m.group(1))[::-1].hex()
            indent = line[: len(line) - len(line.lstrip())]
            lines[ln - 1] = indent + ".word 0x" + val
            fixed += 1
        if fixed == 0:
            print("no fixable lines left;", len(bad), "errors remain")
            print(p.stderr[:2000])
            return 1
        open(path, "w").write("\n".join(lines))
        print("iteration", iteration, "errors", len(bad), "rewritten", fixed)
    print("gave up after 40 iterations")
    return 1


if __name__ == "__main__":
    sys.exit(main())
