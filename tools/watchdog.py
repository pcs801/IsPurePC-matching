#!/usr/bin/env python3
"""watchdog.py - find TUs of the CURRENT batch whose workers look stuck.

Reads the newest build/m26-tu-batch-N/meta.json, then for each of its TUs checks
whether result.json was written after the batch was created. Reports idle minutes
so the captain can nudge / reassign instead of letting one function block a batch.
"""
import glob
import json
import os
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
STUCK = int(os.environ.get("STUCK_MIN", "25"))


def newest_mtime(d):
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
    return newest, newest_f


def main():
    metas = sorted(glob.glob(os.path.join(ROOT, "build", "m26-tu-batch-*", "meta.json")),
                   key=os.path.getmtime)
    if not metas:
        print("no batch meta"); return 0
    meta_path = metas[-1]
    meta = json.load(open(meta_path, encoding="utf-8"))
    created = os.path.getmtime(meta_path)
    rows = []
    for t in meta.get("tus", []):
        d = t.get("dir") or ""
        res = os.path.join(d, "result.json")
        done = os.path.exists(res) and os.path.getmtime(res) >= created
        newest, nf = newest_mtime(d) if os.path.isdir(d) else (0, "")
        mins = (time.time() - newest) / 60.0 if newest else 999
        rows.append((mins, done, t.get("tu"), (nf or "").replace(ROOT, ".")))
    rows.sort(reverse=True)
    stuck = [r for r in rows if not r[1] and r[0] >= STUCK]
    for mins, done, tu, f in rows:
        flag = "done" if done else ("STUCK" if mins >= STUCK else "ok")
        print("%-5s %6.1f min  %-22s (%s)" % (flag, mins, tu, f))
    print("batch %s: stuck %d, pending %d" % (meta.get("batch"), len(stuck),
                                              sum(1 for r in rows if not r[1])))
    return 0


if __name__ == "__main__":
    main()
