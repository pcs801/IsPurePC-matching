#!/usr/bin/env python3
"""Reclassify addresses that were reported as failed tasks.

asm-only (C cannot emit the instructions) goes to build/m26-asm-native.json so
it is exported as assembly and removed from the C queue; codegen-only losses and
truncated symbols go to build/m26-known-hard.json.
"""
import json, os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NEW_ASM = {
    "0x001E3FA8": "sq 128-bit store; C has no 128-bit scalar",
    "0x001DD010": "DMA FIFO copy uses lq/sq; C cannot emit them",
}
NEW_HARD = {
    "0x001FAC30": "truncated symbol: no epilogue in its 24 bytes",
    "0x00209140": "codegen: divisor allocated v0 vs v1, 6 words",
    "0x001F6858": "codegen: t0=0x2000 hoisted above sd ra, 2 words",
}


def main():
    p = os.path.join(ROOT, "build", "m26-asm-native.json")
    d = json.load(open(p, encoding="utf-8"))
    have = {a.lower() for a in d["addrs"]}
    added = []
    for a, why in NEW_ASM.items():
        if a.lower() not in have:
            d["addrs"].append(a)
            added.append((a, why))
    d["addrs"].sort(key=lambda x: int(x, 16))
    with open(p, "w", encoding="utf-8", newline="\n") as f:
        json.dump(d, f, indent=2, ensure_ascii=False)
        f.write("\n")
    print("asm-native added", len(added), [a for a, _ in added], "total", len(d["addrs"]))

    kp = os.path.join(ROOT, "build", "m26-known-hard.json")
    k = json.load(open(kp, encoding="utf-8"))
    khave = {e["addr"].lower() for e in k["functions"]}
    syms = {}
    for line in open(os.path.join(ROOT, "config", "symbols.csv"), encoding="utf-8").read().splitlines()[1:]:
        parts = line.split(",")
        if len(parts) >= 2:
            try:
                syms[int(parts[0], 16)] = int(parts[1])
            except ValueError:
                pass
    n = 0
    for a, why in NEW_HARD.items():
        if a.lower() in khave:
            continue
        k["functions"].append({"addr": a, "size": syms.get(int(a, 16), 0),
                               "flags": [], "attempts": 0, "note": "known-hard: " + why})
        n += 1
    k["functions"].sort(key=lambda e: int(e["addr"], 16))
    with open(kp, "w", encoding="utf-8", newline="\n") as f:
        json.dump(k, f, indent=2, ensure_ascii=False)
        f.write("\n")
    print("known-hard added", n, "total", len(k["functions"]))


if __name__ == "__main__":
    main()
