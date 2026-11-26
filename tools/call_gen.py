#!/usr/bin/env python3
"""call_gen.py - straight-line functions that call other functions (hard c1+b0 /
c2-3+b0).  auto_match.py rejects jal/j; this generator translates them into
extern declarations plus ordinary calls, then byte-verifies with match_kit.

Supported shapes
  * tail call:      j FUN_xxx   (+ delay-slot argument setup)  -> return FUN_xxx(args);
  * direct call:    jal FUN_xxx (+ delay-slot argument setup)  -> v0 = FUN_xxx(args); ...
  * mixed with the same scalar/global expression IR as auto_match.

Usage
  python tools/call_gen.py --addr 0x001F3A60 --dry-run
  python tools/call_gen.py --set call702 --limit 702
"""
import argparse
import json
import os
import re
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import build as B          # noqa: E402
import claims as C         # noqa: E402
import match_kit as MK     # noqa: E402
import triage              # noqa: E402
import auto_match as AM    # noqa: E402
import llm_match as LM     # noqa: E402

QUEUE = os.path.join(ROOT, "build", "queue.json")
SETS = os.path.join(ROOT, "build", "m2-5-sets.json")
RESULTS = os.path.join(ROOT, "build", "m2-5-call-results.json")
MAX_CAND = 12


class Unsupported(Exception):
    pass


def regname(tok):
    tok = tok.strip()
    if not tok.startswith("$"):
        raise Unsupported("register %r" % tok)
    return tok[1:]


def call_target(tok):
    m = re.match(r"^(?:func_|FUN_)([0-9A-Fa-f]{6,8})", tok.strip())
    if not m:
        return None
    return int(m.group(1), 16)


def parse_imm(tok):
    v = AM.parse_value(tok)
    if v[0] != "const":
        raise Unsupported("immediate %r" % tok)
    return v[1]


class T:
    """Single-pass translator for one straight-line function body."""

    def __init__(self, signed=True):
        self.signed = signed
        self.regs = {"a0": ("param", 0), "a1": ("param", 1),
                     "a2": ("param", 2), "a3": ("param", 3)}
        self.stores = []
        self.calls = []      # (target_addr, [arg nodes])
        self.tail = None     # (target_addr, [arg nodes])
        self.v0 = None
        self.used_params = set()
        self.ret = False

    def get(self, reg):
        if reg == "zero":
            return AM.const(0)
        if reg == "gp":
            raise Unsupported("$gp value")
        if reg in self.regs:
            return self.regs[reg]
        raise Unsupported("uninitialised $%s" % reg)

    def put(self, reg, node):
        self.regs[reg] = node
        if reg == "v0":
            self.v0 = node

    def addr(self, base, off, sym):
        if base == "gp":
            a = (AM.GP_BASE + off) & 0xFFFFFFFF
            return ("sym", a, "D_%08X" % a)
        node = self.get(base)
        if off:
            node = AM.mk("add", node, AM.const(off))
        if sym is not None:
            if node[0] == "sym" and node[1] == sym[1]:
                return node
            node = AM.mk("add", node, ("sym", sym[1], sym[2]))
        return node

    def args(self):
        written = [i for i in range(4)
                   if ("a%d" % i) in self.regs and self.regs["a%d" % i] != ("param", i)]
        n = max(written) + 1 if written else 0
        out = []
        for i in range(n):
            out.append(self.regs.get("a%d" % i, ("param", i)))
            self.used_params.add(i)
        return out

    def run(self, insns):
        body = list(insns)
        i = 0
        while i < len(body):
            _a, _w, mn, ops = body[i]
            o = AM.split_ops(ops)
            if mn == "nop":
                i += 1
                continue
            if mn in ("jal", "j"):
                target = call_target(o[0])
                if target is None:
                    raise Unsupported("%s %r" % (mn, o[0]))
                i += 1
                # execute the delay slot first (it sets arguments)
                if i < len(body):
                    self._one(body[i])
                    i += 1
                args = self.args()
                if mn == "j":
                    self.tail = (target, args)
                    return
                self.calls.append((target, args))
                self.put("v0", ("call", target, args))
                continue
            if mn == "jr":
                if regname(o[0]) != "ra":
                    raise Unsupported("tail jump")
                self.ret = True
                i += 1
                continue
            self._one(body[i])
            i += 1
        return

    def _one(self, insn):
        _a, _w, mn, ops = insn
        o = AM.split_ops(ops)
        if mn == "nop":
            return
        if mn == "lui":
            dst = regname(o[0])
            v = AM.parse_value(o[1])
            if v[0] == "sym_hi":
                self.put(dst, v)
            elif v[0] == "const":
                self.put(dst, AM.const((v[1] << 16) & 0xFFFFFFFF))
            else:
                raise Unsupported("lui")
            return
        if mn in ("addiu", "daddiu"):
            dst = regname(o[0])
            if dst == "sp" and regname(o[1]) == "sp":
                return  # frame adjust, ignored
            base = self.get(regname(o[1]))
            v = AM.parse_value(o[2])
            if v[0] == "const":
                imm = AM.sign16(v[1]) if v[1] > 0x7FFF else v[1]
                self.put(dst, AM.mk("add", base, AM.const(imm)))
            elif v[0] == "sym_lo":
                self.put(dst, ("sym", v[1], v[2]) if base[0] == "sym_hi"
                         else AM.mk("add", base, ("sym", v[1], v[2])))
            else:
                raise Unsupported("addiu")
            return
        if mn == "ori":
            self.put(regname(o[0]), AM.mk("or", self.get(regname(o[1])),
                                          AM.const(parse_imm(o[2]) & 0xFFFF)))
            return
        if mn == "andi":
            self.put(regname(o[0]), AM.mk("and", self.get(regname(o[1])),
                                          AM.const(parse_imm(o[2]) & 0xFFFF)))
            return
        if mn == "xori":
            self.put(regname(o[0]), AM.mk("xor", self.get(regname(o[1])),
                                          AM.const(parse_imm(o[2]) & 0xFFFF)))
            return
        if mn in ("addu", "daddu", "subu", "and", "or", "xor", "move"):
            dst = regname(o[0])
            a = self.get(regname(o[1]))
            b = self.get(regname(o[2])) if len(o) > 2 else AM.const(0)
            op = {"addu": "add", "daddu": "add", "subu": "sub", "and": "and",
                  "or": "or", "xor": "xor", "move": "add"}[mn]
            self.put(dst, AM.mk(op, a, b))
            return
        if mn in ("sll", "srl", "sra"):
            self.put(regname(o[0]), AM.mk({"sll": "shl", "srl": "shr", "sra": "sar"}[mn],
                                          self.get(regname(o[1])), AM.const(parse_imm(o[2]))))
            return
        if mn in ("slti", "sltiu"):
            self.put(regname(o[0]), AM.mk("lti" if mn == "slti" else "ltiu",
                                          self.get(regname(o[1])), AM.const(parse_imm(o[2]))))
            return
        if mn in ("movn", "movz"):
            self.put(regname(o[0]), ("sel", self.get(regname(o[1])), AM.const(0),
                                     self.get(regname(o[2])),
                                     "nz" if mn == "movn" else "z"))
            return
        if mn in AM.LOAD_TY:
            dst = regname(o[0])
            base, off, sym = AM.parse_mem(o[1])
            if base == "sp":
                if dst in ("ra", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7"):
                    return  # frame restore, ignored
                raise Unsupported("local load from $sp")
            w, signed = AM.LOAD_TY[mn]
            self.put(dst, ("load", (w, signed), self.addr(base, off, sym)))
            return
        if mn in AM.STORE_TY:
            base, off, sym = AM.parse_mem(o[1])
            if base == "sp":
                return  # frame save, ignored
            self.stores.append({"addr": self.addr(base, off, sym),
                                "ty": (AM.STORE_TY[mn], False),
                                "val": self.get(regname(o[0]))})
            return
        raise Unsupported(mn)


def render(entry, insns, mode, signed, ret_type, ptr_params):
    tr = T(signed)
    tr.run(insns)
    ctx = {"params": {i: ["p", "a", "b", "c"][i] for i in range(4)},
           "decls": {}, "externs": {}, "mode": mode, "signed": signed}
    for i in range(4):
        ctx["decls"][i] = "int *" if ptr_params else "int"
    call_defs = []
    protos = {}
    for target, args in tr.calls + ([tr.tail] if tr.tail else []):
        name = "FUN_%08x" % target
        ts = ["void *" if a[0] in ("sym", "load", "param") else "int" for a in args]
        decl = "extern int %s(%s);" % (name, ", ".join(ts) if ts else "void")
        if name in protos:
            continue
        protos[name] = decl
        call_defs.append(decl)
    def expr_args(args):
        return ", ".join(AM.render_expr(a, ctx, mode) for a in args)

    def rn(node):
        if node[0] == "call":
            return "FUN_%08x(%s)" % (node[1], expr_args(node[2]))
        return AM.render_expr(node, ctx, mode)
    body = []
    for st in tr.stores:
        body.append("    " + AM.emit_mem(st["addr"], st["ty"], ctx, mode, load=False,
                                         val=AM.render_expr(st["val"], ctx, mode)))
    for target, args in tr.calls:
        body.append("    FUN_%08x(%s);" % (target, expr_args(args)))
    if tr.tail:
        target, args = tr.tail
        if ret_type == "void":
            body.append("    FUN_%08x(%s);" % (target, expr_args(args)))
            body.append("    return;")
        else:
            body.append("    return FUN_%08x(%s);" % (target, expr_args(args)))
    elif tr.v0 is not None:
        if not (tr.v0[0] == "call" and ret_type == "void"):
            body.append("    return %s;" % rn(tr.v0))
    nparam = max(tr.used_params) + 1 if tr.used_params else 0
    params = []
    for i in range(nparam):
        dt = ctx["decls"][i]
        params.append(dt + ("" if dt.endswith("*") else " ") + ctx["params"][i])
    head = "%s FUN_%08x(%s) {" % (ret_type, entry["addr_i"],
                                  ", ".join(params) if params else "void")
    defs = call_defs + [d for d in ctx["externs"].values() if d not in call_defs]
    return "\n".join(defs + ([""] if defs else []) + [head] + body + ["}"]) + "\n"


def generate(entry, insns):
    out, seen = [], set()
    for mode in ("natural", "cast"):
        for ptr in (False, True):
            for ret_type in ("int", "void", "unsigned int", "long long"):
                try:
                    src = render(entry, insns, mode, True, ret_type, ptr)
                except Exception:
                    continue
                if src in seen:
                    continue
                seen.add(src)
                out.append({"src": src, "g": int((entry.get("g") or ["0"])[0]),
                            "variant": "%s/%s/%s" % (mode, "ptr" if ptr else "int", ret_type)})
                if len(out) >= MAX_CAND:
                    return out
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--addr", action="append", default=None)
    ap.add_argument("--set", default="call702", choices=["call702", "likely", "unaligned"])
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--owner", default="m25-call")
    ap.add_argument("--tag-prefix", default="m25c")
    ap.add_argument("--quiet", action="store_true")
    args = ap.parse_args(argv)

    q = json.load(open(QUEUE, encoding="utf-8"))
    idx = {"0x%08X" % e["addr_i"]: e for e in q["entries"]}
    byfn = triage.parse_asm(symbols=triage.parse_symbols())
    sets = json.load(open(SETS, encoding="utf-8"))
    if args.addr:
        targets = [idx["0x%08X" % int(a, 16)] for a in args.addr]
    else:
        targets = [idx[a] for a in sets.get(args.set, []) if a in idx]
        if args.limit:
            targets = targets[:args.limit]
    if args.dry_run:
        for e in targets[:5]:
            cands = generate(e, byfn.get(e["addr_i"], []))
            print("=== %s size=%d flags=%s" % (e["addr"], e["size"], e["flags"]))
            if not cands:
                print("  no candidate")
            for c in cands[:2]:
                print("--- %s" % c["variant"])
                print(c["src"])
        return 0
    if not targets:
        print("nothing to do")
        return 0

    claimed = []
    for e in targets:
        try:
            C.claim_one(args.owner, e["addr"], lease=3600)
            claimed.append(e)
        except SystemExit as exc:
            print("  skip", e["addr"], exc)
    if not claimed:
        return 0

    rows, n_hit = [], 0
    t0 = time.time()
    for e in claimed:
        cands = generate(e, byfn.get(e["addr_i"], []))
        hit, attempts, first = None, 0, None
        if cands:
            tag = "%s_%x" % (args.tag_prefix, e["addr_i"])
            items, slot = [], {}
            for ci, c in enumerate(cands):
                key = "%x_%02d" % (e["addr_i"], ci)
                items.append({"key": key, "src": c["src"], "g": c["g"]})
                slot[key] = (ci, c)
            objs = MK.compile_batch(items, tag, verbose=not args.quiet)
            for key, (ci, c) in slot.items():
                attempts += 1
                if not objs.get(key):
                    continue
                r = LM.verify(objs[key], e)
                if r["ok"]:
                    hit = (ci, c, r)
                    break
                if first is None:
                    first = r["summary"]
        if hit:
            ci, c, r = hit
            core_only = e["core"] < e["size"]
            src_rel = LM.write_source(e, c["src"], "call_gen %s" % c["variant"])
            note = "M2.5 call: %s%s" % (
                ("core %d/%d" % (e["core"], e["size"])) if core_only else ("%d bytes" % e["size"]),
                "" if core_only else "; g=%d" % c["g"])
            if core_only:
                LM.record_padded(e, src_rel, note, c["g"])
            else:
                LM.update_overrides(e, src_rel, note, c["g"])
            LM.append_ledger(e, c["g"], attempts, note)
            C.complete(args.owner, e["addr"], "MATCH", attempts, note=note, source=src_rel)
            n_hit += 1
            result = "MATCH_CORE" if core_only else "MATCH"
            print("  %s %3dB MATCH  %s" % (e["addr"], e["size"], c["variant"]))
        else:
            why = first or "no candidate" if cands else "no candidate"
            C.complete(args.owner, e["addr"], "MISS", attempts, note=str(why)[:300])
            result = "MISS"
            print("  %s %3dB MISS   %s" % (e["addr"], e["size"], str(why)[:70]))
        rows.append({"addr": e["addr"], "size": e["size"], "core": e["core"],
                     "flags": e["flags"], "sig": e["sig"], "result": result,
                     "attempts": attempts, "note": str(first or "")[:300]})

    doc = {"schema": 1, "phase": "M2.5-call", "set": args.set,
           "generated": time.strftime("%Y-%m-%dT%H:%M:%S%z"),
           "tested": len(rows), "hits": n_hit,
           "hit_rate": round(n_hit / float(len(rows)), 4) if rows else 0,
           "elapsed_sec": round(time.time() - t0, 1), "functions": rows}
    with open(RESULTS, "w", newline="\n", encoding="utf-8") as f:
        json.dump(doc, f, indent=1, ensure_ascii=False)
        f.write("\n")
    print("call_gen done: %d/%d = %.1f%%, %.1fs"
          % (n_hit, len(rows), 100.0 * n_hit / len(rows) if rows else 0, time.time() - t0))
    return 0


if __name__ == "__main__":
    sys.exit(main())
