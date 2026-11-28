#!/usr/bin/env python3
"""Pick fresh small functions: unmatched, not excluded, no existing candidate.

Round-25 rules (see build/m26-optimizer/ledger.md):
  1. exhausted families (0x001B8xxx, 0x001C7xxx) are skipped by default;
     preferred windows 0x001C9xxx-0x001Dxxxx and 0x0020xxxx-0x0021xxxx rank first;
  2. addresses classified D/X/P in build/m26-nearmiss-pool.json are excluded;
     class A (length equal + 1-3 differing words) is kept but ranked last: it is
     not a pure regalloc wall - several A entries were recovered by rewriting the
     call form, so they stay dispatchable at low priority;
  3. ordering: size, then cls (local < ambiguous < needs_G8), then family rank,
     then single-valued g, then address.
Usage: python tools/pick_fresh.py [limit] [maxsize] [--allow-exhausted] [--include-nearmiss]
"""
import json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# families with 30+ recent hits -> nothing new to learn there
EXHAUSTED = [(0x001B8000, 0x001B8FFF), (0x001C7000, 0x001C7FFF)]
# windows we want to open next
PREFERRED = [(0x001C9000, 0x001DFFFF), (0x00200000, 0x0021FFFF)]
# near-miss pool classes that must not be dispatched again
POOL_SKIP = {"D", "X", "P"}
CLS_RANK = {"local": 0, "ambiguous": 1, "needs_G8": 2}


def load(p):
    with open(os.path.join(ROOT, p), encoding="utf-8") as f:
        return json.load(f)


def load_opt(p, key=None):
    try:
        d = load(p)
    except (OSError, ValueError):
        return None
    return d.get(key) if key else d


def in_ranges(a, ranges):
    return any(lo <= a <= hi for lo, hi in ranges)


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    flags = {a for a in sys.argv[1:] if a.startswith("--")}
    limit = int(args[0]) if args else 20
    maxsize = int(args[1]) if len(args) > 1 else 96
    allow_exhausted = "--allow-exhausted" in flags
    include_nearmiss = "--include-nearmiss" in flags

    q = load("build/m26-queue.json")["entries"]
    kh = {int(e["addr"], 16) for e in load("build/m26-known-hard.json")["functions"]}
    an = {int(a, 16) for a in load("build/m26-asm-native.json")["addrs"]}
    ov = load("config/overrides.json")["functions"]
    matched = {int(f["addr"], 16) for f in ov
               if f.get("status") == "matched" or f.get("kind") in ("full", "core")}
    src = set(os.listdir(os.path.join(ROOT, "src", "functions")))
    try:
        disp = set(json.load(open(os.path.join(ROOT, "build", "_dispatched.json"))))
    except (OSError, ValueError):
        disp = set()
    pool = load_opt("build/m26-nearmiss-pool.json", "entries") or []
    pool_cls = {int(e["addr"], 16): e.get("cls") for e in pool if e.get("addr")}

    kept, skipped = [], {"pool": 0, "family": 0}
    for e in q:
        a = int(e["addr"], 16)
        if a in matched or a in kh or a in an:
            continue
        if "%08x.c" % a in src:
            continue
        if e["addr"] in disp or "%08x" % a in disp:
            continue
        if e.get("syscall") or e.get("unsupported"):
            continue
        if e["size"] > maxsize:
            continue
        if not include_nearmiss and pool_cls.get(a) in POOL_SKIP:
            skipped["pool"] += 1
            continue
        if not allow_exhausted and in_ranges(a, EXHAUSTED):
            skipped["family"] += 1
            continue
        e = dict(e)
        e["_fam_rank"] = 0 if in_ranges(a, PREFERRED) else 1
        e["_g_len"] = len(e.get("g") or [])
        kept.append(e)

    kept.sort(key=lambda e: (e["size"], CLS_RANK.get(e.get("cls"), 3),
                             1 if pool_cls.get(int(e["addr"], 16)) == "A" else 0,
                             e["_fam_rank"], e["_g_len"], e["addr_i"]))
    print("candidates", len(kept), "| skipped pool:", skipped["pool"],
          "family:", skipped["family"])
    out = [{"addr": e["addr"], "size": e["size"], "sig": e["sig"], "g": e["g"],
            "group": e.get("group"), "cls": e["cls"],
            "family": "0x%08X" % (int(e["addr"], 16) & 0xFFFFF000),
            "preferred": e["_fam_rank"] == 0, "g_len": e["_g_len"],
            "pool_cls": pool_cls.get(int(e["addr"], 16))} for e in kept[:limit]]
    print(json.dumps(out, ensure_ascii=False))
    return out


if __name__ == "__main__":
    main()
