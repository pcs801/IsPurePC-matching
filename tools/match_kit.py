#!/usr/bin/env python3
"""match_kit.py - compile C candidates inside WSL and byte-compare with baserom.

This is the standalone compile/verify primitive behind build.py's override step,
exposed so the M2.2 batch runner can test many candidates cheaply:

  * one WSL invocation compiles every candidate of a batch
  * each object's .text is relocation-resolved with tools/build.py's resolver
    (same symbols, gp=0x002779F0) and compared word-for-word to the baserom

CLI
  python tools/match_kit.py one --src build/x.c --addr 0x00102078 --size 8 --g 0
  python tools/match_kit.py batch --manifest build/cands.json
"""
import argparse
import json
import os
import subprocess
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build as B  # noqa: E402  (build.py is import-safe)

CAND_ROOT = os.path.join(ROOT, "build", "candidates")
BASEROM = os.path.join(ROOT, "baserom", "SLPM_665.70")
TEXT_ADDR = B.TEXT_ADDR
TEXT_OFF = B.TEXT_OFF


def _obj_path(tag, key, g):
    return os.path.join(CAND_ROOT, tag, "%s.G%d.o" % (key, int(g)))


def _tick_compile(items, objs):
    """Append one line per compiled object to build/compile-tick.log."""
    try:
        import hashlib
        import re as _re
        import time as _time
        log = os.path.join(ROOT, "build", "compile-tick.log")
        with open(log, "a", encoding="utf-8") as f:
            for it in items:
                m = _re.match(r"([0-9a-fA-F]+)", str(it.get("key", "")))
                if not m:
                    continue
                addr = int(m.group(1), 16)
                op = objs.get(it["key"])
                sha = ""
                if op and os.path.exists(op):
                    sha = hashlib.sha1(open(op, "rb").read()).hexdigest()[:12]
                f.write("%.0f %08x %s %s\n" % (_time.time(), addr, it["key"], sha))
    except OSError:
        pass


def compile_batch(items, tag, verbose=True):
    """items: [{"key","src","g"}] -> {key: object path or None}."""
    if not items:
        return {}
    work = os.path.join(CAND_ROOT, tag)
    os.makedirs(work, exist_ok=True)
    for it in items:
        with open(os.path.join(work, it["key"] + ".c"), "w", newline="\n",
                  encoding="utf-8") as f:
            f.write(it["src"])
    script = [
        "#!/bin/bash",
        "export LC_ALL=C",
        'ROOT="%s"' % B.WSL_ROOT,
        'D="$ROOT/build/candidates/%s"' % tag,
        "mkdir -p \"$D\"",
        "cd /root/work || exit 1",
        'rm -rf "cand_%s" && mkdir "cand_%s" && cd "cand_%s"' % (tag, tag, tag),
    ]
    for it in items:
        key = it["key"]
        g = int(it["g"])
        obj = "%s.G%d.o" % (key, g)
        script += [
            'cp "$D/%s.c" .' % key,
            ('CC="%s"; if $CC -O2 -mips3 -G%d -c %s.c -o %s 2>%s.err; then '
             'cp %s "$D/%s"; else echo "FAIL %s"; fi; '
             'if [ -f %s.err ]; then cp %s.err "$D/"; fi') % (
                 it.get("cc") or "/opt/ee/bin/ee-gcc", g, key, obj, key, obj, obj, key, key, key),
        ]
    script += ['echo COMPILE_DONE', 'exit 0']
    sh = os.path.join(ROOT, "build", "_wsl_match_%s.sh" % tag)
    with open(sh, "w", newline="\n", encoding="utf-8") as f:
        f.write("\n".join(script) + "\n")
    t0 = time.time()
    r = subprocess.run(["wsl.exe", "-d", B.WSL_DISTRO, "-u", "root", "--",
                        "bash", B.WSL_ROOT + "/build/_wsl_match_%s.sh" % tag],
                       cwd=ROOT)
    if r.returncode != 0:
        print("match_kit: WSL compile script failed (%d)" % r.returncode,
              file=sys.stderr)
    out = {}
    for it in items:
        path = _obj_path(tag, it["key"], it["g"])
        out[it["key"]] = path if os.path.exists(path) else None
    if verbose:
        missing = [k for k, v in out.items() if not v]
        print("  compile: %d candidates, %d objects, %.1fs%s" % (
            len(items), len(out) - len(missing), time.time() - t0,
            ("  FAILED: " + ",".join(missing[:6])) if missing else ""))
    _tick_compile(items, out)
    return out


def verify_obj(obj, addr, size):
    """Relocation-aware byte comparison.  Returns dict(ok, ...)."""
    if not obj or not os.path.exists(obj):
        return {"ok": False, "reason": "no-object", "diffs": [], "unresolved": [],
                "compiled_len": 0}
    try:
        data, secs = B.elf_sections(obj)
        text, stats = B.resolve_object_text(obj)
    except SystemExit as e:
        return {"ok": False, "reason": "elf:%s" % e, "diffs": [], "unresolved": [],
                "compiled_len": 0}
    with open(BASEROM, "rb") as f:
        base = f.read()
    off = TEXT_OFF + (addr - TEXT_ADDR)
    orig = base[off:off + size]
    diffs, ndiff = B.word_diff(text, orig)
    ok = (len(text) == size) and not diffs and not stats["unresolved"]
    first = diffs[0] if diffs else None
    return {
        "ok": ok,
        "reason": "match" if ok else ("diff %d word(s)" % ndiff),
        "diffs": diffs,
        "ndiff": ndiff,
        "unresolved": stats["unresolved"],
        "compiled_len": len(text),
        "expected_len": size,
        "compiled": text,
        "first_diff": first,
    }


def verify_src(src, addr, size, g, tag="one"):
    """Convenience: compile one candidate and compare."""
    items = [{"key": "cand", "src": src, "g": g}]
    objs = compile_batch(items, tag, verbose=False)
    return verify_obj(objs["cand"], addr, size)


def cmd_one(args):
    src = open(args.src, encoding="utf-8").read()
    slot = int(args.addr, 16) if isinstance(args.addr, str) else args.addr
    r = verify_src(src, slot, args.size, args.g, tag=args.tag)
    print("addr 0x%08X size=%d -G%d -> %s  (%d/%d bytes)" % (
        slot, args.size, args.g, "MATCH" if r["ok"] else r["reason"],
        r["compiled_len"], r["expected_len"]))
    if not r["ok"]:
        if r.get("first_diff"):
            print("  first diff:", r["first_diff"])
        for u in r["unresolved"][:5]:
            print("  unresolved reloc:", u)
    return 0 if r["ok"] else 1


def cmd_batch(args):
    with open(args.manifest, encoding="utf-8") as f:
        items = json.load(f)
    for it in items:
        it["g"] = int(it.get("g", 0))
    objs = compile_batch(items, args.tag or "batch")
    n_ok = 0
    for it in items:
        slot = int(it["addr"], 16) if isinstance(it["addr"], str) else it["addr"]
        r = verify_obj(objs.get(it["key"]), slot, int(it["size"]))
        n_ok += 1 if r["ok"] else 0
        print("%-16s 0x%08X %-6s %s" % (it["key"], slot, "MATCH" if r["ok"] else "-", r["reason"]))
    print("summary: %d/%d matched" % (n_ok, len(items)))
    return 0


def build_parser():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("one")
    p.add_argument("--src", required=True)
    p.add_argument("--addr", required=True)
    p.add_argument("--size", type=int, required=True)
    p.add_argument("--g", type=int, default=0)
    p.add_argument("--tag", default="one")
    p.set_defaults(func=cmd_one)
    p = sub.add_parser("batch")
    p.add_argument("--manifest", required=True)
    p.add_argument("--tag", default="batch")
    p.set_defaults(func=cmd_batch)
    return ap


if __name__ == "__main__":
    args = build_parser().parse_args()
    sys.exit(args.func(args))
