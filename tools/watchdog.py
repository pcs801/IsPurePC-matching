#!/usr/bin/env python3
"""watchdog.py - find TUs whose workers look stuck.

For every build/m26-tu/tu_* directory without result.json, report the minutes
since its newest file changed, so the captain can nudge / reassign instead of
letting one function block the batch.
"""
import glob
import os
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TU = os.path.join(ROOT, "build", "m26-tu")
STUCK = int(os.environ.get("STUCK_MIN", "25"))


def main():
    rows = []
    for d in sorted(glob.glob(os.path.join(TU, "tu_*"))):
        if os.path.exists(os.path.join(d, "result.json")):
            continue
        newest = 0
        newest_f = ""
        for root, _dirs, files in os.walk(d):
            for f in files:
                p = os.path.join(root, f)
                try:
                    m = os.path.getmtime(p)
                except OSError:
                    continue
                if m > newest:
                    newest = m
                    newest_f = p
        mins = (time.time() - newest) / 60.0 if newest else 999
        rows.append((mins, os.path.basename(d), newest_f.replace(ROOT, ".")))
    rows.sort(reverse=True)
    stuck = [r for r in rows if r[0] >= STUCK]
    for mins, tu, f in rows:
        flag = "STUCK" if mins >= STUCK else "ok"
        print("%-5s %6.1f min  %s  (%s)" % (flag, mins, tu, f))
    print("stuck", len(stuck), "pending", len(rows))
    return 0


if __name__ == "__main__":
    sys.exit(main())
