#!/usr/bin/env python3
"""branch_gen.py - structured control-flow templates for medium branch functions.

The straight-line translator in auto_match.py cannot express branches.  This
generator recognises the shapes that dominate the medium branch tier and renders
ordinary C candidates for them:

  * if / else      one conditional branch + its delay slot + a short fallthrough
                   block (early return, conditional store, conditional increment)
  * loop           backward branch (while / do-while skeleton)
  * switch         a beq/bne chain or a jr jump-table guard (best effort)

Candidates are compiled with ee-gcc 2.96 in WSL and byte-compared with the same
relocation-aware core gate used by llm_match.py.

Usage
  python tools/branch_gen.py --addr 0x001B4908 --dry-run
  python tools/branch_gen.py --tier medium --branch --limit 65
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
RESULTS = os.path.join(ROOT, "build", "m2-4-branch-results.json")
MAX_CAND = 24

BRANCHES = {"beq": "eq", "bne": "ne", "beqz": "eqz", "bnez": "nez",
            "blez": "lez", "bgtz": "gtz", "bltz": "ltz", "bgez": "gez"}
LIKELY = {k + "l": v for k, v in BRANCHES.items()}


class Unsupported(Exception):
    pass


def is_branch(mn):
    return mn in BRANCHES or mn in LIKELY


def regname(tok):
    tok = tok.strip()
    if not tok.startswith("$"):
        raise Unsupported("register %r" % tok)
    return tok[1:]


def parse_imm(tok):
    v = AM.parse_value(tok)
    if v[0] != "const":
        raise Unsupported("immediate %r" % tok)
    return v[1]


class Block:
    """Straight-line slice translator (subset of auto_match.translate)."""

    def __init__(self, signed=True, init_regs=None):
        self.signed = signed
        self.regs = dict(init_regs or {})
        self.stores = []
        self.v0 = self.regs.get("v0")

    def get(self, reg):
        if reg == "zero":
            return AM.const(0)
        if reg == "gp":
            raise Unsupported("$gp as value")
        if reg in ("a0", "a1", "a2", "a3"):
            return ("param", int(reg[1]))
        if reg not in self.regs:
            raise Unsupported("uninitialised $%s" % reg)
        return self.regs[reg]

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

    def run(self, insns):
        for _a, _w, mn, ops in insns:
            o = AM.split_ops(ops)
            if mn == "nop":
                continue
            if mn in ("j", "b"):
                raise Unsupported("jump")
            if mn == "jr":
                if regname(o[0]) != "ra":
                    raise Unsupported("tail jump")
                self.ret = True
                continue
            if mn == "lui":
                dst = regname(o[0])
                v = AM.parse_value(o[1])
                if v[0] == "sym_hi":
                    self.put(dst, v)
                elif v[0] == "const":
                    self.put(dst, AM.const((v[1] << 16) & 0xFFFFFFFF))
                else:
                    raise Unsupported("lui %r" % (o[1],))
                continue
            if mn in ("addiu", "daddiu"):
                dst = regname(o[0])
                base = self.get(regname(o[1]))
                v = AM.parse_value(o[2])
                if v[0] == "const":
                    imm = AM.sign16(v[1]) if v[1] > 0x7FFF else v[1]
                    self.put(dst, AM.mk("add", base, AM.const(imm)))
                elif v[0] == "sym_lo":
                    self.put(dst, ("sym", v[1], v[2]) if base[0] == "sym_hi"
                             else AM.mk("add", base, ("sym", v[1], v[2])))
                else:
                    raise Unsupported("addiu %r" % (o[2],))
                continue
            if mn == "ori":
                dst = regname(o[0])
                self.put(dst, AM.mk("or", self.get(regname(o[1])),
                                    AM.const(parse_imm(o[2]) & 0xFFFF)))
                continue
            if mn == "andi":
                dst = regname(o[0])
                self.put(dst, AM.mk("and", self.get(regname(o[1])),
                                    AM.const(parse_imm(o[2]) & 0xFFFF)))
                continue
            if mn == "xori":
                dst = regname(o[0])
                self.put(dst, AM.mk("xor", self.get(regname(o[1])),
                                    AM.const(parse_imm(o[2]) & 0xFFFF)))
                continue
            if mn in ("addu", "daddu", "subu", "and", "or", "xor", "move"):
                dst = regname(o[0])
                a = self.get(regname(o[1]))
                b = self.get(regname(o[2])) if len(o) > 2 else AM.const(0)
                op = {"addu": "add", "daddu": "add", "subu": "sub", "and": "and",
                      "or": "or", "xor": "xor", "move": "add"}[mn]
                self.put(dst, AM.mk(op, a, b))
                continue
            if mn in ("sll", "srl", "sra"):
                dst = regname(o[0])
                sh = parse_imm(o[2])
                self.put(dst, AM.mk({"sll": "shl", "srl": "shr", "sra": "sar"}[mn],
                                    self.get(regname(o[1])), AM.const(sh)))
                continue
            if mn in ("slti", "sltiu"):
                dst = regname(o[0])
                self.put(dst, AM.mk("lti" if mn == "slti" else "ltiu",
                                    self.get(regname(o[1])), AM.const(parse_imm(o[2]))))
                continue
            if mn in ("movn", "movz"):
                dst = regname(o[0])
                self.put(dst, ("sel", self.get(regname(o[1])), AM.const(0),
                               self.get(regname(o[2])),
                               "nz" if mn == "movn" else "z"))
                continue
            if mn in AM.LOAD_TY:
                dst = regname(o[0])
                base, off, sym = AM.parse_mem(o[1])
                w, signed = AM.LOAD_TY[mn]
                self.put(dst, ("load", (w, signed), self.addr(base, off, sym)))
                continue
            if mn in AM.STORE_TY:
                base, off, sym = AM.parse_mem(o[1])
                self.stores.append({"addr": self.addr(base, off, sym),
                                    "ty": (AM.STORE_TY[mn], False),
                                    "val": self.get(regname(o[0]))})
                continue
            raise Unsupported(mn)


def param_roles(insns):
    ro = {}
    for _a, _w, mn, ops in insns:
        if mn in AM.LOAD_TY or mn in AM.STORE_TY:
            try:
                parts = AM.split_ops(ops)
                base, _off, _sym = AM.parse_mem(parts[1] if mn in AM.LOAD_TY else parts[1])
            except Unsupported:
                continue
            if base in ("a0", "a1", "a2", "a3"):
                w = AM.LOAD_TY[mn][0] if mn in AM.LOAD_TY else AM.STORE_TY[mn]
                ro.setdefault(int(base[1]), set()).add(w)
    return ro


def build_ctx(entry, insns, mode, signed):
    ro = param_roles(insns)
    seen = set()
    for _a, _w, _mn, ops in insns:
        for m in re.finditer(r"\$a([0-3])", ops):
            seen.add(int(m.group(1)))
    nparam = max([max(ro) if ro else -1] + list(seen)) + 1
    names = ["p", "a", "b", "c"]
    ctx = {"params": {i: names[i] for i in range(nparam)}, "decls": {},
           "externs": {}, "mode": mode, "signed": signed}
    for i in range(nparam):
        w = max(ro.get(i) or {4})
        ctx["decls"][i] = AM.TY[w][0 if signed else 1] + " *"
    return ctx


def render_cond(kind, lhs, rhs, ctx):
    A = AM.render_expr(lhs, ctx, ctx["mode"])
    table = {"eqz": "%s == 0", "nez": "%s != 0", "lez": "%s <= 0",
             "gtz": "%s > 0", "ltz": "%s < 0", "gez": "%s >= 0"}
    if kind in table:
        return table[kind] % A
    B = AM.render_expr(rhs, ctx, ctx["mode"])
    return ("%s == %s" if kind == "eq" else "%s != %s") % (A, B)


def parse_cond(mn, ops, pre):
    kind = BRANCHES.get(mn) or LIKELY.get(mn)
    lhs = pre.get(regname(ops[0]))
    if kind in ("eqz", "nez", "lez", "gtz", "ltz", "gez"):
        return kind, lhs, AM.const(0)
    second = ops[1].strip()
    if second.startswith("$"):
        rhs = pre.get(regname(second))
    else:
        try:
            rhs = AM.const(parse_imm(second))
        except Unsupported:
            return None
    return kind, lhs, rhs


def stmts_of(blk, ctx):
    return [AM.emit_mem(st["addr"], st["ty"], ctx, ctx["mode"], load=False,
                        val=AM.render_expr(st["val"], ctx, ctx["mode"]))
            for st in blk.stores]


def render_all(entry, insns, branch_idx, mode, signed):
    branch = insns[branch_idx]
    mn, ops = branch[2], AM.split_ops(branch[3])
    m = re.search(r"\.L([0-9A-Fa-f]+)", branch[3])
    if not m:
        return []
    target = int(m.group(1), 16)
    if branch_idx + 1 >= len(insns):
        return []
    delay = [insns[branch_idx + 1]]
    a_start = branch_idx + 2
    a_end = None
    for i in range(a_start, len(insns)):
        if insns[i][0] >= target:
            a_end = i
            break
    if a_end is None:
        return []
    A_ins = insns[a_start:a_end]
    B_ins = insns[a_end:]
    if any(is_branch(x[2]) for x in A_ins) or any(is_branch(x[2]) for x in B_ins):
        return []
    ctx = build_ctx(entry, insns, mode, signed)
    try:
        pre = Block(signed)
        pre.run(insns[:branch_idx])
        cond = parse_cond(mn, ops, pre)
        if cond is None:
            return []
        dly = Block(signed, pre.regs)
        dly.run(delay)
        a = Block(signed, dly.regs)
        a.run(A_ins)
        b = Block(signed, dly.regs)
        b.run(B_ins)
    except Unsupported:
        return []
    pre_stmts, delay_stmts = stmts_of(pre, ctx), stmts_of(dly, ctx)
    a_stmts, b_stmts = stmts_of(a, ctx), stmts_of(b, ctx)
    b_ret_node = b.v0 if b.v0 is not None else dly.v0
    a_ret_node = a.v0 if a.v0 is not None else b_ret_node
    if a_ret_node is None and b_ret_node is None:
        return []
    cond_s = render_cond(cond[0], cond[1], cond[2], ctx)
    a_ret = AM.render_expr(a_ret_node, ctx, mode) if a_ret_node is not None else None
    b_ret = AM.render_expr(b_ret_node, ctx, mode) if b_ret_node is not None else None
    heads = []
    for i in sorted(ctx["params"]):
        dt = ctx["decls"].get(i, "int *")
        heads.append(dt + ("" if dt.endswith("*") else " ") + ctx["params"][i])
    out = []
    for ret_type in ("int", "void", "unsigned int", "char", "unsigned char"):
        for inv in (False, True):
            C_ = cond_s if not inv else "!(%s)" % cond_s
            bodies = []
            # T1: both paths return
            if b_ret is not None and a_ret is not None:
                t = []
                t += ["    " + s for s in pre_stmts]
                t += ["    " + s for s in delay_stmts]
                t.append("    if (%s) {" % C_)
                t += ["        " + s for s in b_stmts]
                t.append("        return %s;" % b_ret)
                t.append("    }")
                t += ["    " + s for s in a_stmts]
                t.append("    return %s;" % a_ret)
                bodies.append(t)
                # T3: ternary (no stores on either path)
                if not a_stmts and not b_stmts:
                    t = ["    " + s for s in pre_stmts + delay_stmts]
                    t.append("    return (%s) ? %s : %s;" % (C_, b_ret, a_ret))
                    bodies.append(t)
            # T2: guard the fallthrough block, single return
            if b_ret is not None and (a_stmts or a_ret is not None):
                t = ["    " + s for s in pre_stmts + delay_stmts]
                t.append("    if (!(%s)) {" % C_)
                t += ["        " + s for s in a_stmts]
                if a_ret is not None:
                    t.append("        return %s;" % a_ret)
                t.append("    }")
                t.append("    return %s;" % b_ret)
                bodies.append(t)
            # T4: conditional store, return the delay-slot value
            if not a_ret and a_stmts and b_ret is not None:
                t = ["    " + s for s in pre_stmts + delay_stmts]
                t.append("    if (!(%s)) {" % C_)
                t += ["        " + s for s in a_stmts]
                t.append("    }")
                t.append("    return %s;" % b_ret)
                bodies.append(t)
            for body in bodies:
                head = "%s FUN_%08x(%s) {" % (
                    ret_type, entry["addr_i"], ", ".join(heads) if heads else "void")
                outs = [head] + body + ["}"]
                externs = sorted(ctx["externs"].values())
                if externs:
                    outs = externs + [""] + outs
                out.append("\n".join(outs) + "\n")
    return out


def render_loop(entry, insns, branch_idx, mode, signed):
    """Backward branch -> while / do-while / infinite-loop-with-break templates."""
    branch = insns[branch_idx]
    m = re.search(r"\.L([0-9A-Fa-f]+)", branch[3])
    if not m:
        return []
    target = int(m.group(1), 16)
    if target >= branch[0]:
        return []
    body = [x for x in insns if target <= x[0] < branch[0]]
    pre = [x for x in insns if x[0] < target]
    delay = [x for x in insns if x[0] == branch[0] + 4]
    tail = [x for x in insns if x[0] > branch[0] + 4]
    if not body:
        return []
    if any(is_branch(x[2]) for x in pre + body + tail):
        return []
    mn, ops = branch[2], AM.split_ops(branch[3])
    if mn not in BRANCHES:
        return []
    ctx = build_ctx(entry, insns, mode, signed)
    try:
        p = Block(signed)
        p.run(pre)
        b = Block(signed, p.regs)
        b.run(body)
        cond = parse_cond(mn, ops, b)
        if cond is None:
            return []
        d = Block(signed, b.regs)
        d.run(delay)
        t = Block(signed, d.regs)
        t.run(tail)
    except Unsupported:
        return []
    body_stmts = stmts_of(b, ctx) + stmts_of(d, ctx)
    pre_stmts = stmts_of(p, ctx)
    cond_s = render_cond(cond[0], cond[1], cond[2], ctx)
    ret_node = t.v0 if t.v0 is not None else d.v0
    ret_s = AM.render_expr(ret_node, ctx, mode) if ret_node is not None else None
    heads = []
    for i in sorted(ctx["params"]):
        dt = ctx["decls"].get(i, "int *")
        heads.append(dt + ("" if dt.endswith("*") else " ") + ctx["params"][i])
    outs = []
    for ret_type in ("int", "void", "unsigned int", "char", "unsigned char"):
        for inv in (False, True):
            CS = cond_s if not inv else "!(%s)" % cond_s
            for shape in ("do", "while", "for"):
                t = ["    " + s for s in pre_stmts]
                if shape == "do":
                    t.append("    do {")
                    t += ["        " + s for s in body_stmts]
                    t.append("    } while (%s);" % CS)
                elif shape == "while":
                    t.append("    while (%s) {" % CS)
                    t += ["        " + s for s in body_stmts]
                    t.append("    }")
                else:
                    t.append("    for (;;) {")
                    t.append("        if (!(%s)) break;" % CS)
                    t += ["        " + s for s in body_stmts]
                    t.append("    }")
                if ret_s is not None:
                    t.append("    return %s;" % ret_s)
                head = "%s FUN_%08x(%s) {" % (
                    ret_type, entry["addr_i"], ", ".join(heads) if heads else "void")
                externs = sorted(ctx["externs"].values())
                outs.append("\n".join((externs + [""] if externs else []) + [head] + t + ["}"]) + "\n")
    return outs


def render_switch(entry, insns, mode, signed):
    """Multi-branch beq/bne chain -> switch(x) / if-else chain candidates."""
    bidx = [i for i, x in enumerate(insns) if is_branch(x[2])]
    if len(bidx) < 2:
        return []
    first = insns[bidx[0]]
    pre_ins = [x for x in insns if x[0] < first[0]]
    reg = None
    cases = []
    for i in bidx:
        mn = insns[i][2]
        if mn not in ("beq", "bne"):
            return []
        ops = AM.split_ops(insns[i][3])
        r1 = regname(ops[0])
        if reg is None:
            reg = r1
        elif r1 != reg:
            return []
        second = ops[1].strip()
        if second.startswith("$"):
            return []
        try:
            c = parse_imm(second)
        except Unsupported:
            return []
        m = re.search(r"\.L([0-9A-Fa-f]+)", insns[i][3])
        if not m:
            return []
        cases.append((mn, c, int(m.group(1), 16), i))
    if len(cases) < 2:
        return []
    ctx = build_ctx(entry, insns, mode, signed)
    try:
        pre = Block(signed)
        pre.run(pre_ins)
        expr = pre.get(reg)
    except Unsupported:
        return []
    # translate each case block up to its jr (or the next case target)
    targets = sorted(set(c[2] for c in cases))
    blocks = {}
    for mn, c, target, i in cases:
        idx = next(k for k, x in enumerate(insns) if x[0] == target)
        stop = len(insns)
        for t2 in targets:
            if t2 > target:
                stop = min(stop, next(k for k, x in enumerate(insns) if x[0] == t2))
        block_ins = insns[idx:stop]
        if any(is_branch(x[2]) for x in block_ins):
            continue
        try:
            b = Block(signed, pre.regs)
            b.run(block_ins)
        except Unsupported:
            continue
        blocks[target] = b
    if not blocks:
        return []
    expr_s = AM.render_expr(expr, ctx, mode)
    heads = []
    for i in sorted(ctx["params"]):
        dt = ctx["decls"].get(i, "int *")
        heads.append(dt + ("" if dt.endswith("*") else " ") + ctx["params"][i])
    outs = []
    for ret_type in ("int", "void", "unsigned int"):
        # switch form
        body = ["    switch (%s) {" % expr_s]
        for mn, c, target, i in cases:
            if target not in blocks:
                continue
            b = blocks[target]
            case_val = c if mn == "beq" else c
            body.append("        case %d:" % case_val)
            for st in b.stores:
                body.append("            " + AM.emit_mem(st["addr"], st["ty"], ctx, mode,
                                                         load=False,
                                                         val=AM.render_expr(st["val"], ctx, mode)))
            if b.v0 is not None:
                body.append("            return %s;" % AM.render_expr(b.v0, ctx, mode))
            else:
                body.append("            break;")
        body.append("        default: break;")
        body.append("    }")
        vals = [AM.render_expr(b.v0, ctx, mode) for b in blocks.values()
                if b.v0 is not None]
        if vals:
            body.append("    return %s;" % vals[0])
        head = "%s FUN_%08x(%s) {" % (ret_type, entry["addr_i"],
                                      ", ".join(heads) if heads else "void")
        externs = sorted(ctx["externs"].values())
        outs.append("\n".join((externs + [""] if externs else []) + [head] + body + ["}"]) + "\n")
        # if-else chain form
        body = []
        for k, (mn, c, target, i) in enumerate(cases):
            if target not in blocks:
                continue
            b = blocks[target]
            test = ("%s == %d" if mn == "beq" else "%s != %d") % (expr_s, c)
            body.append("    %s (%s) {" % ("if" if k == 0 else "else if", test))
            for st in b.stores:
                body.append("        " + AM.emit_mem(st["addr"], st["ty"], ctx, mode,
                                                     load=False,
                                                     val=AM.render_expr(st["val"], ctx, mode)))
            if b.v0 is not None:
                body.append("        return %s;" % AM.render_expr(b.v0, ctx, mode))
            body.append("    }")
        if vals:
            body.append("    return %s;" % vals[0])
        head = "%s FUN_%08x(%s) {" % (ret_type, entry["addr_i"],
                                      ", ".join(heads) if heads else "void")
        outs.append("\n".join((externs + [""] if externs else []) + [head] + body + ["}"]) + "\n")
    return outs


def render_likely(entry, insns, branch_idx, mode, signed):
    """Likely branch: delay slot executes only when the branch is taken; the
    fallthrough block skips it.  Emit if/else over the two paths."""
    branch = insns[branch_idx]
    mn = branch[2]
    if mn not in LIKELY:
        return []
    m = re.search(r"\.L([0-9A-Fa-f]+)", branch[3])
    if not m:
        return []
    target = int(m.group(1), 16)
    if branch_idx + 1 >= len(insns):
        return []
    delay = [insns[branch_idx + 1]]
    tgt_idx = next((i for i, x in enumerate(insns) if x[0] >= target), len(insns))
    ft = insns[branch_idx + 2:tgt_idx]
    then = insns[tgt_idx:]
    pre = insns[:branch_idx]
    ctx = build_ctx(entry, insns, mode, signed)
    try:
        p = Block(signed)
        p.run(pre)
        cond = parse_cond(mn, AM.split_ops(branch[3]), p)
        if cond is None:
            return []
        d = Block(signed, p.regs)
        d.run(delay)
        th = Block(signed, d.regs)
        th.run(then)
        el = Block(signed, p.regs)
        el.run(ft)
    except Unsupported:
        return []
    pre_stmts = stmts_of(p, ctx)
    then_stmts = stmts_of(d, ctx) + stmts_of(th, ctx)
    else_stmts = stmts_of(el, ctx)
    cond_s = render_cond(cond[0], cond[1], cond[2], ctx)
    then_ret = th.v0
    else_ret = el.v0
    heads = []
    for i in sorted(ctx["params"]):
        dt = ctx["decls"].get(i, "int *")
        heads.append(dt + ("" if dt.endswith("*") else " ") + ctx["params"][i])
    outs = []
    for ret_type in ("void", "int", "unsigned int"):
        for inv in (False, True):
            CS = cond_s if not inv else "!(%s)" % cond_s
            t = ["    " + st for st in pre_stmts]
            t.append("    if (%s) {" % CS)
            t += ["        " + st for st in then_stmts]
            if then_ret is not None:
                t.append("        return %s;" % AM.render_expr(then_ret, ctx, mode))
            t.append("    } else {")
            t += ["        " + st for st in else_stmts]
            if else_ret is not None:
                t.append("        return %s;" % AM.render_expr(else_ret, ctx, mode))
            t.append("    }")
            head = "%s FUN_%08x(%s) {" % (ret_type, entry["addr_i"],
                                          ", ".join(heads) if heads else "void")
            externs = sorted(ctx["externs"].values())
            outs.append("\n".join((externs + [""] if externs else []) + [head] + t + ["}"]) + "\n")
    return outs


def generate(entry, insns):
    cands, seen = [], set()
    bidx = [i for i, x in enumerate(insns) if is_branch(x[2])]
    if len(bidx) == 0:
        return []
    if len(bidx) == 1 and insns[bidx[0]][2] in LIKELY:
        for mode in ("natural", "cast"):
            for signed in (True, False):
                try:
                    srcs = render_likely(entry, insns, bidx[0], mode, signed)
                except Exception:
                    srcs = []
                for src in srcs:
                    if src in seen:
                        continue
                    seen.add(src)
                    cands.append({"src": src, "g": int((entry.get("g") or ["0"])[0]),
                                  "variant": "%s/%s/likely" % (mode, "s" if signed else "u")})
                    if len(cands) >= MAX_CAND:
                        return cands
        return cands
    if len(bidx) >= 2:
        for mode in ("natural", "cast"):
            for signed in (True, False):
                try:
                    srcs = render_switch(entry, insns, mode, signed)
                except Exception:
                    srcs = []
                for src in srcs:
                    if src in seen:
                        continue
                    seen.add(src)
                    cands.append({"src": src, "g": int((entry.get("g") or ["0"])[0]),
                                  "variant": "%s/%s/switch" % (mode, "s" if signed else "u")})
                    if len(cands) >= MAX_CAND:
                        return cands
        return cands
    bi = bidx[0]
    m = re.search(r"\.L([0-9A-Fa-f]+)", insns[bi][3])
    if not m:
        return []
    target = int(m.group(1), 16)
    backward = target < insns[bi][0]
    for mode in ("natural", "cast"):
        for signed in (True, False):
            try:
                srcs = (render_loop(entry, insns, bi, mode, signed) if backward
                        else render_all(entry, insns, bi, mode, signed))
            except Exception:
                srcs = []
            for src in srcs:
                if src in seen:
                    continue
                seen.add(src)
                cands.append({"src": src, "g": int((entry.get("g") or ["0"])[0]),
                              "variant": "%s/%s" % (mode, "s" if signed else "u")})
                if len(cands) >= MAX_CAND:
                    return cands
    return cands


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--addr", action="append", default=None)
    ap.add_argument("--tier", default="medium")
    ap.add_argument("--branch", action="store_true")
    ap.add_argument("--set", default=None, help="address list from build/m2-5-sets.json")
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--owner", default="m24-branch")
    ap.add_argument("--tag-prefix", default="m24b")
    ap.add_argument("--quiet", action="store_true")
    ap.add_argument("--no-claim", action="store_true",
                    help="verify without touching the claims ledger")
    ap.add_argument("--no-write", action="store_true",
                    help="verify and record only; do not write src/overrides/claims")
    args = ap.parse_args(argv)

    q = json.load(open(QUEUE, encoding="utf-8"))
    idx = {"0x%08X" % e["addr_i"]: e for e in q["entries"]}
    byfn = triage.parse_asm(symbols=triage.parse_symbols())
    cdoc = json.load(open(os.path.join(ROOT, "build", "claims.json"), encoding="utf-8"))

    if args.addr:
        targets = [idx["0x%08X" % int(a, 16)] for a in args.addr]
    elif args.set:
        sets = json.load(open(os.path.join(ROOT, "build", "m2-5-sets.json"), encoding="utf-8"))
        targets = [idx[a] for a in sets.get(args.set, []) if a in idx]
        targets = [e for e in targets
                   if cdoc["claims"].get("0x%08X" % e["addr_i"], {}).get("result") != "MATCH"]
    else:
        targets = [e for e in q["entries"] if e["tier"] == args.tier]
        if args.branch:
            targets = [e for e in targets if "branch" in (e["flags"] or [])]
        targets = [e for e in targets
                   if cdoc["claims"].get("0x%08X" % e["addr_i"], {}).get("result") != "MATCH"]
        if args.limit:
            targets = targets[:args.limit]
    if args.dry_run:
        for e in targets[:8]:
            insns = byfn.get(e["addr_i"], [])
            cands = generate(e, insns)
            print("=== %s size=%d core=%d flags=%s" % (e["addr"], e["size"],
                                                       e["core"], e["flags"]))
            if not cands:
                print("  no candidate")
            for i, c in enumerate(cands[:3]):
                print("--- candidate %d (%s)" % (i + 1, c["variant"]))
                print(c["src"])
        return 0
    if not targets:
        print("nothing to do")
        return 0

    claimed = []
    for e in targets:
        if args.no_claim:
            claimed.append(e)
            continue
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
        insns = byfn.get(e["addr_i"], [])
        try:
            cands = generate(e, insns)
            note = "no candidate" if not cands else ""
        except Exception as exc:
            cands, note = [], "generator error: %s" % exc
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
            if args.no_write:
                d = os.path.join(ROOT, "build", "m2-4-branch-src")
                os.makedirs(d, exist_ok=True)
                src_rel = "build/m2-4-branch-src/%08x.c" % e["addr_i"]
                open(os.path.join(ROOT, src_rel), "w", newline="\n",
                     encoding="utf-8").write(c["src"])
                result = "MATCH_CORE" if core_only else "MATCH"
                n_hit += 1
                print("  %s %3dB %-24s %s  %s" % (e["addr"], e["size"], e["sig"],
                                                   result, c["variant"]))
                rows.append({"addr": e["addr"], "size": e["size"], "core": e["core"],
                             "flags": e["flags"], "sig": e["sig"], "result": result,
                             "attempts": attempts, "variant": c["variant"],
                             "g": c["g"], "source": src_rel,
                             "note": "verified, not written (no-write)"})
                continue
            src_rel = LM.write_source(e, c["src"], "branch_gen %s" % c["variant"])
            note2 = "M2.4 branch: %s%s" % (
                ("core %d/%d" % (e["core"], e["size"])) if core_only else ("%d bytes" % e["size"]),
                "" if core_only else "; g=%d" % c["g"])
            if core_only:
                LM.record_padded(e, src_rel, note2, c["g"])
            else:
                LM.update_overrides(e, src_rel, note2, c["g"])
            LM.append_ledger(e, c["g"], attempts, note2)
            C.complete(args.owner, e["addr"], "MATCH", attempts, note=note2, source=src_rel)
            n_hit += 1
            result = "MATCH_CORE" if core_only else "MATCH"
            print("  %s %3dB %-24s MATCH  %s" % (e["addr"], e["size"], e["sig"], c["variant"]))
        else:
            why = note or first or "no byte-exact candidate"
            if not args.no_write:
                C.complete(args.owner, e["addr"], "MISS", attempts, note=str(why)[:300])
            result = "MISS"
            print("  %s %3dB %-24s MISS   %s" % (e["addr"], e["size"], e["sig"],
                                                 str(why)[:70]))
        rows.append({"addr": e["addr"], "size": e["size"], "core": e["core"],
                     "flags": e["flags"], "sig": e["sig"], "result": result,
                     "attempts": attempts, "note": str(note or first or "")[:300]})

    doc = {"schema": 1, "phase": "M2.4-branch", "tier": args.tier,
           "generated": time.strftime("%Y-%m-%dT%H:%M:%S%z"),
           "tested": len(rows), "hits": n_hit,
           "hit_rate": round(n_hit / float(len(rows)), 4) if rows else 0,
           "elapsed_sec": round(time.time() - t0, 1), "functions": rows}
    with open(RESULTS, "w", newline="\n", encoding="utf-8") as f:
        json.dump(doc, f, indent=1, ensure_ascii=False)
        f.write("\n")
    print("branch_gen done: %d/%d = %.1f%%, %.1fs"
          % (n_hit, len(rows), 100.0 * n_hit / len(rows) if rows else 0,
             time.time() - t0))
    return 0


if __name__ == "__main__":
    sys.exit(main())
