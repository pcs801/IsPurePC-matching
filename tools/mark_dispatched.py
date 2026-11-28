#!/usr/bin/env python3
"""Record dispatched addresses so pick_fresh never hands the same one twice."""
import json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    p = os.path.join(ROOT, "build", "_dispatched.json")
    try:
        have = set(json.load(open(p)))
    except (OSError, ValueError):
        have = set()
    n = 0
    for a in sys.argv[1:]:
        key = "0x" + a.upper().replace("0X", "")
        if key not in have:
            have.add(key)
            n += 1
    out = sorted(have)
    with open(p, "w", encoding="utf-8", newline="\n") as f:
        json.dump(out, f)
    print("added", n, "total", len(out))


if __name__ == "__main__":
    main()
