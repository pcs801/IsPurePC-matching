#!/usr/bin/env python3
"""auto_match.py - claim triage-queue functions, synthesize C candidates, compile
them with ee-gcc 2.96 in WSL and keep only byte-exact matches.

Pipeline per batch
  1. claims.claim_next(tier=easy, stride, limit)  -> functions no one else owns
  2. translate the splat disassembly into a small C AST (registers -> expressions)
  3. emit several C variants (pointer/type/return/statement-order/-G)
  4. match_kit.compile_batch (one WSL call) + relocation-aware byte compare
  5. on MATCH: write src/functions/<addr>.c, register config/overrides.json
     (status=matched), append progress/ledger.tsv, complete the claim
     otherwise: complete the claim with MISS / UNSUPPORTED and keep the evidence
  6. after every batch: make progress (gen_report + dashboard + upload)

No CHEAT: the generated C is ordinary C (no asm, no .word, no volatile, no goto);
everything that does not compile to the original bytes is discarded.
"""
import argparse
import itertools
import json
import os
import re
import subprocess
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import triage            # noqa: E402
import claims as C       # noqa: E402
import match_kit as MK   # noqa: E402

QUEUE = os.path.join(ROOT, "build", "queue.json")
OVERRIDES = os.path.join(ROOT, "config", "overrides.json")
LEDGER = os.path.join(ROOT, "progress", "ledger.tsv")
SRC_DIR = os.path.join(ROOT, "src", "functions")
RESULTS = os.path.join(ROOT, "build", "m2-2-results.json")
GP_BASE = 0x002779F0
MAX_CAND = 24
WAVE1 = 6

# ---------------------------------------------------------------- expression IR
TY = {1: ("signed char", "unsigned char"), 2: ("short", "unsigned short"),
      4: ("int", "unsigned int"), 8: ("long long", "unsigned long long")}
LOAD_TY = {"lb": (1, False), "lbu": (1, True), "lh": (2, False),
           "lhu": (2, True), "lw": (4, False), "lwu": (4, True),
           "ld": (8, False), "ll": (4, False)}
STORE_TY = {"sb": 1, "sh": 2, "sw": 4, "sd": 8, "sc": 4}
REG_RE = re.compile(r"^\$([a-z0-9]+)$")
MEM_RE = re.compile(r"^(.*)\(\$([a-z0-9]+)\)$")
SYM_PREFIX = ("FUN_", "func_", "D_", "jtbl_", "L_")


class Unsupported(Exception):
    pass


def const(n):
    return ("const", n)


def as_int(node):
    if node[0] == "const":
        return node[1]
    return None


def mk(op, a, b):
    """Build a binary node, folding constants and neutral elements."""
    av, bv = as_int(a), as_int(b)
    if av is not None and bv is not None:
        v = None
        if op == "add":
            v = av + bv
        elif op == "sub":
            v = av - bv
        elif op == "and":
            v = av & bv
        elif op == "or":
            v = av | bv
        elif op == "xor":
            v = av ^ bv
        elif op == "mul":
            v = av * bv
        elif op in ("shl", "shr", "sar") and 0 <= bv <= 63:
            v = {"shl": av << bv,
                 "shr": (av & 0xFFFFFFFF) >> bv,
                 "sar": av >> bv}[op]
        elif op in ("lt", "lti"):
            v = int(av < bv)
        elif op in ("ltu", "ltiu"):
            v = int((av & 0xFFFFFFFF) < (bv & 0xFFFFFFFF))
        if v is not None:
            return const(v)
    if op in ("add", "or", "xor"):
        if av == 0:
            return b
        if bv == 0:
            return a
    if op in ("shl", "shr", "sar", "sub") and bv == 0:
        return a
    return ("bin", op, a, b)


def sign16(v):
    v &= 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


def sym_addr(name):
    for p in SYM_PREFIX:
        if name.startswith(p):
            head = name[len(p):].split(".")[0].split("+")[0]
            try:
                return int(head, 16)
            except ValueError:
                return None
    return None


def parse_value(tok):
    t = tok.strip()
    if t.startswith("%hi(") and t.endswith(")"):
        name = t[4:-1]
        a = sym_addr(name)
        if a is None:
            raise Unsupported("symbol %s" % name)
        return ("sym_hi", a, name)
    if t.startswith("%lo(") and t.endswith(")"):
        name = t[4:-1]
        a = sym_addr(name)
        if a is None:
            raise Unsupported("symbol %s" % name)
        return ("sym_lo", a, name)
    if t.startswith("(") and t.endswith(")"):
        m = re.match(r"^(0x[0-9A-Fa-f]+)\s*(>>|&)\s*(0x[0-9A-Fa-f]+|\d+)$", t[1:-1])
        if m:
            v = int(m.group(1), 16)
            k = int(m.group(3), 0)
            return ("const", (v >> k) if m.group(2) == ">>" else (v & k))
    try:
        return ("const", int(t, 0))
    except ValueError:
        raise Unsupported("immediate %r" % tok)


def split_ops(text):
    if not text:
        return []
    return [x.strip() for x in text.split(",")]


def parse_mem(tok):
    m = MEM_RE.match(tok.strip())
    if not m:
        raise Unsupported("memory operand %r" % tok)
    off_txt, base = m.group(1).strip(), m.group(2)
    off = 0
    sym = None
    if off_txt:
        v = parse_value(off_txt)
        if v[0] == "const":
            off = v[1]
        elif v[0] == "sym_lo":
            sym = v
            off = 0
        else:
            raise Unsupported("memory offset %r" % off_txt)
    return base, off, sym


def strip_reg(tok):
    m = REG_RE.match(tok.strip())
    if not m:
        raise Unsupported("register %r" % tok)
    return m.group(1)


# ---------------------------------------------------------------- translation
def translate(body):
    regs = {("a%d" % i): ("param", i) for i in range(4)}
    stores = []
    reads = []          # (insn_index, set(reg names))
    writes = []         # (insn_index, reg)
    pending_mul = None
    pending_div = None
    ended = False
    uses64 = False

    def get(reg, idx):
        reads.append((idx, reg))
        if reg == "zero":
            return const(0)
        if reg in ("ra", "sp", "fp", "gp", "at", "k0", "k1"):
            raise Unsupported("reads $%s" % reg)
        if reg not in regs:
            raise Unsupported("reads uninitialised $%s" % reg)
        return regs[reg]

    def put(reg, node, idx):
        regs[reg] = node
        writes.append((idx, reg))

    for idx, (_a, _w, mn, ops) in enumerate(body):
        o = split_ops(ops)
        if mn in ("nop",):
            continue
        if mn == "jr":
            if strip_reg(o[0]) != "ra":
                raise Unsupported("tail jump")
            ended = True
            continue
        if mn in ("syscall", "break", "cache", "sync", "sync.p", "eret"):
            raise Unsupported(mn)
        if mn == "lui":
            dst = strip_reg(o[0])
            v = parse_value(o[1])
            if v[0] == "sym_hi":
                put(dst, v, idx)
            elif v[0] == "const":
                put(dst, const((v[1] << 16) & 0xFFFFFFFFFFFFFFFF
                               if v[1] < 0 else v[1] << 16), idx)
            else:
                raise Unsupported("lui %s" % o[1])
            continue
        if mn in ("addiu", "daddiu", "addi", "dadd"):
            dst = strip_reg(o[0])
            base = get(strip_reg(o[1]), idx)
            v = parse_value(o[2])
            if v[0] == "const":
                imm = v[1]
                if mn != "dadd":
                    imm = sign16(imm) if imm > 0x7FFF else imm
                put(dst, mk("add", base, const(imm)), idx)
            elif v[0] == "sym_lo" and base[0] == "sym_hi":
                put(dst, ("sym", v[1], v[2]), idx)
            elif v[0] == "sym_lo":
                put(dst, mk("add", base, ("sym", v[1], v[2])), idx)
            else:
                raise Unsupported("addiu %r" % o[2])
            continue
        if mn == "ori":
            dst = strip_reg(o[0])
            base = get(strip_reg(o[1]), idx)
            v = parse_value(o[2])
            put(dst, mk("or", base, const(v[1] & 0xFFFF)), idx)
            continue
        if mn == "andi":
            dst = strip_reg(o[0])
            base = get(strip_reg(o[1]), idx)
            v = parse_value(o[2])
            put(dst, mk("and", base, const(v[1] & 0xFFFF)), idx)
            continue
        if mn == "xori":
            dst = strip_reg(o[0])
            base = get(strip_reg(o[1]), idx)
            v = parse_value(o[2])
            put(dst, mk("xor", base, const(v[1] & 0xFFFF)), idx)
            continue
        if mn in ("addu", "daddu", "subu", "dsubu", "and", "or", "xor",
                  "nor", "slt", "sltu", "negu", "neg", "move"):
            dst = strip_reg(o[0])
            if mn in ("negu", "neg"):
                put(dst, mk("sub", const(0), get(strip_reg(o[1]), idx)), idx)
                continue
            a = get(strip_reg(o[1]), idx)
            b = const(0) if len(o) < 3 else get(strip_reg(o[2]), idx)
            op = {"addu": "add", "daddu": "add", "subu": "sub", "dsubu": "sub",
                  "and": "and", "or": "or", "xor": "xor", "nor": "nor",
                  "slt": "lt", "sltu": "ltu", "move": "add"}[mn]
            uses64 |= mn.startswith("d")
            put(dst, mk(op, a, b), idx)
            continue
        if mn in ("slti", "sltiu"):
            dst = strip_reg(o[0])
            a = get(strip_reg(o[1]), idx)
            v = parse_value(o[2])
            put(dst, mk("lti" if mn == "slti" else "ltiu", a, const(v[1])), idx)
            continue
        if mn in ("sll", "srl", "sra", "dsll", "dsrl", "dsra",
                  "dsll32", "dsrl32", "dsra32"):
            dst = strip_reg(o[0])
            a = get(strip_reg(o[1]), idx)
            sh = parse_value(o[2])[1]
            if mn.endswith("32"):
                sh += 32
                uses64 = True
            m = {"sll": "shl", "srl": "shr", "sra": "sar", "dsll": "shl",
                 "dsrl": "shr", "dsra": "sar"}.get(mn.rstrip("32")) 
            if m is None:
                m = "shl" if "sll" in mn else ("shr" if "srl" in mn else "sar")
            put(dst, mk(m, a, const(sh)), idx)
            continue
        if mn in ("sllv", "srlv", "srav"):
            dst = strip_reg(o[0])
            a = get(strip_reg(o[1]), idx)
            b = get(strip_reg(o[2]), idx)
            put(dst, mk({"sllv": "shl", "srlv": "shr", "srav": "sar"}[mn], a, b), idx)
            continue
        if mn in ("mult", "multu"):
            if len(o) == 3:
                dst = strip_reg(o[0])
                a = get(strip_reg(o[1]), idx)
                b = get(strip_reg(o[2]), idx)
                put(dst, mk("mul", a, b), idx)
            else:
                pending_mul = (get(strip_reg(o[0]), idx), get(strip_reg(o[1]), idx))
            continue
        if mn in ("div", "divu"):
            if len(o) == 3:
                a = get(strip_reg(o[1]), idx)
                b = get(strip_reg(o[2]), idx)
                pending_div = (a, b, "divu" in mn)
            else:
                pending_div = (get(strip_reg(o[0]), idx), get(strip_reg(o[1]), idx), mn == "divu")
            continue
        if mn in ("mflo", "mfhi"):
            dst = strip_reg(o[0])
            if pending_div:
                a, b, _u = pending_div
                put(dst, mk("div" if mn == "mflo" else "mod", a, b), idx)
            elif pending_mul:
                a, b = pending_mul
                put(dst, mk("div" if mn == "mflo" else "mod", a, b), idx)
            else:
                raise Unsupported("mflo without div")
            continue
        if mn in ("movn", "movz"):
            dst = strip_reg(o[0])
            a = get(strip_reg(o[1]), idx)
            cond = get(strip_reg(o[2]), idx)
            old = regs.get(dst, const(0))
            put(dst, ("sel", a, old, cond, "nz" if mn == "movn" else "z"), idx)
            continue
        if mn in LOAD_TY:
            dst = strip_reg(o[0])
            base, off, sym = parse_mem(o[1])
            addr = build_addr(base, off, sym, idx, get)
            w, signed = LOAD_TY[mn]
            uses64 |= mn == "ld"
            put(dst, ("load", (w, signed), addr), idx)
            continue
        if mn in STORE_TY:
            base, off, sym = parse_mem(o[1])
            addr = build_addr(base, off, sym, idx, get)
            val = get(strip_reg(o[0]), idx)
            w = STORE_TY[mn]
            uses64 |= mn == "sd"
            stores.append({"addr": addr, "ty": (w, False), "val": val, "idx": idx})
            continue
        raise Unsupported(mn)

    if not ended:
        raise Unsupported("no jr $ra")
    # return value: last write to v0 that no later instruction reads
    last_v0 = None
    for wi, reg in writes:
        if reg == "v0":
            last_v0 = wi
    ret = None
    if last_v0 is not None:
        later_read = any(i > last_v0 and reg == "v0" for i, reg in reads)
        if not later_read:
            ret = regs.get("v0")
    params = collect_params(stores, regs, ret)
    return {"stores": stores, "ret": ret, "params": params, "uses64": uses64}


def build_addr(base, off, sym, idx, get):
    if base == "gp":
        if sym is not None:
            raise Unsupported("gp + %lo")
        a = GP_BASE + off
        return ("sym", a, "D_%08X" % a)
    b = get(base, idx)
    node = b
    if off:
        node = mk("add", node, const(off))
    if sym is not None:
        node = mk("add", node, ("sym", sym[1], sym[2]))
    return node


def collect_params(stores, regs, ret):
    out = set()

    def walk(n):
        if not isinstance(n, tuple):
            return
        if n and n[0] == "param":
            out.add(n[1])
            return
        if n and n[0] == "sym":
            return
        for x in n[1:]:
            if isinstance(x, tuple):
                walk(x)

    for s in stores:
        walk(s["addr"])
        walk(s["val"])
    if ret is not None:
        walk(ret)
    return out


# ---------------------------------------------------------------- address split
def flatten_add(node, out):
    if node[0] == "bin" and node[1] == "add":
        flatten_add(node[2], out)
        flatten_add(node[3], out)
    else:
        out.append(node)


def split_addr(node):
    terms = []
    flatten_add(node, terms)
    off = 0
    syms = []
    others = []
    for t in terms:
        if t[0] == "const":
            off += t[1]
        elif t[0] == "sym":
            syms.append(t)
        elif t[0] == "param":
            others.append(t)
        elif t[0] == "load":
            others.append(t)
        elif t[0] == "bin":
            others.append(t)
        else:
            raise Unsupported("address term %r" % (t,))
    if len(syms) > 1:
        raise Unsupported("two symbol bases")
    if syms and others and any(o[0] == "load" for o in others):
        raise Unsupported("symbol + load base")
    return {"sym": syms[0] if syms else None, "off": off, "index": others}


# ---------------------------------------------------------------- C rendering
def tys(w, signed):
    return TY[w][0 if not signed else 1]


def is_ptr_param(node):
    return node[0] == "param"


def param_roles(info):
    """param index -> {"direct": set(width,), "ptr": set(width,)}"""
    roles = {}

    def note(i, role, w):
        if not w:
            return
        roles.setdefault(i, {"direct": set(), "ptr": set()})
        roles[i][role].add(w)

    def walk_access(addr, w):
        s = split_addr(addr)
        for o in s["index"]:
            if o[0] == "param":
                note(o[1], "direct", w)
            elif o[0] == "load":
                inner = split_addr(o[2])
                pi = next((x[1] for x in inner["index"] if x[0] == "param"), None)
                if pi is not None and inner["sym"] is None:
                    note(pi, "ptr", w)
                else:
                    walk_access(o[2], w)

    for st in info["stores"]:
        walk_access(st["addr"], st["ty"][0])
    if info["ret"] is not None and info["ret"][0] == "load":
        walk_access(info["ret"][2], info["ret"][1][0])
    return roles


def ptr_decl(roles, pi, mode, signed):
    r = roles.get(pi, {"direct": set(), "ptr": set()})
    if r["ptr"] and not r["direct"]:
        w = max(r["ptr"])
        return tys(w, signed) + " **"
    if r["direct"]:
        w = max(r["direct"])
        return tys(w, signed) + " *"
    return "int *"


def render_expr(node, ctx, mode="natural"):
    k = node[0]
    if k == "const":
        return str(node[1])
    if k == "param":
        return ctx["params"][node[1]]
    if k == "sym":
        return "(char*)%s" % node[2]
    if k == "load":
        return emit_mem(node[2], node[1], ctx, mode, load=True)
    if k == "bin":
        op, a, b = node[1], node[2], node[3]
        A = render_expr(a, ctx, mode)
        B = render_expr(b, ctx, mode)
        c = {
            "add": "%s + %s", "sub": "%s - %s", "and": "%s & %s", "or": "%s | %s",
            "xor": "%s ^ %s", "mul": "%s * %s", "div": "%s / %s", "mod": "%s %% %s",
            "lt": "%s < %s", "ltu": "(unsigned)%s < (unsigned)%s",
            "lti": "%s < %s", "ltiu": "(unsigned)%s < (unsigned)%s",
            "shl": "%s << %s", "shr": "(unsigned)%s >> %s", "sar": "%s >> %s",
        }[op]
        return "(" + (c % (A, B)) + ")"
    if k == "sel":
        a, old, cond, how = node[1], node[2], node[3], node[4]
        cond_s = render_expr(cond, ctx, mode)
        test = "%s != 0" % cond_s if how == "nz" else "%s == 0" % cond_s
        return "((%s) ? %s : %s)" % (test, render_expr(a, ctx, mode),
                                     render_expr(old, ctx, mode))
    if k == "sym_hi":
        raise Unsupported("unresolved %hi")
    raise Unsupported("expr %r" % (k,))


def add_extern(ctx, name, decl):
    old = ctx["externs"].get(name)
    if old and old != decl:
        raise Unsupported("conflicting externs for %s" % name)
    ctx["externs"][name] = decl


def emit_mem(addr, ty, ctx, mode, load, val=None):
    w, signed = ty
    T = tys(w, signed)
    s = split_addr(addr)
    idx = s["index"]
    sym = s["sym"]
    off = s["off"]
    if sym is not None:
        name = sym[2]
        if off == 0 and not idx:
            add_extern(ctx, name, "extern %s %s;" % (T, name))
            expr = name
        else:
            add_extern(ctx, name, "extern char %s[];" % name)
            body = "(char*)%s" % name
            if off:
                body += " + %d" % off
            for o in idx:
                body += " + (%s)" % render_expr(o, ctx, mode)
            expr = "*(%s*)(%s)" % (T, body)
    else:
        base_param = next((o for o in idx if o[0] == "param"), None)
        base_load = next((o for o in idx if o[0] == "load"), None)
        rest = [o for o in idx if o is not base_param and o is not base_load]
        rest_s = " + ".join("(%s)" % render_expr(o, ctx, mode) for o in rest)
        if base_param is None and base_load is None:
            if off > 0x10000:
                name = "D_%08X" % off
                add_extern(ctx, name, "extern char %s[];" % name)
                expr = "*(%s*)((char*)%s + %s)" % (T, name, rest_s or "0")
                return expr
            raise Unsupported("address without base")
        if base_load is not None and base_param is None:
            inner = split_addr(base_load[2])
            if inner["sym"] is not None and not inner["index"] and inner["off"] == 0:
                name = inner["sym"][2]
                add_extern(ctx, name, "extern %s *%s;" % (T, name))
                if mode == "natural" and not rest and off % w == 0:
                    expr = "%s[%d]" % (name, off // w)
                else:
                    body = "(char*)%s" % name
                    if off:
                        body += " + %d" % off
                    for o in rest:
                        body += " + (%s)" % render_expr(o, ctx, mode)
                    expr = "*(%s*)(%s)" % (T, body)
            else:
                pi = next((x[1] for x in inner["index"] if x[0] == "param"), None)
                if pi is None:
                    raise Unsupported("pointer from unknown base")
                pn = ctx["params"][pi]
                body = "(char*)%s[%d]" % (pn, inner["off"] // 4)
                if off:
                    body += " + %d" % off
                for o in rest:
                    body += " + (%s)" % render_expr(o, ctx, mode)
                expr = "*(%s*)(%s)" % (T, body)
        elif base_param is not None:
            pn = ctx["params"][base_param[1]]
            decl = ctx["decls"].get(base_param[1], "")
            if mode == "natural" and "**" not in decl and not rest and off % w == 0:
                expr = "%s[%d]" % (pn, off // w)
            else:
                body = "(char*)%s" % pn
                if off:
                    body += " + %d" % off
                for o in rest:
                    body += " + (%s)" % render_expr(o, ctx, mode)
                expr = "*(%s*)(%s)" % (T, body)
        else:
            raise Unsupported("address without base")
    if load:
        return expr
    return "%s = %s;" % (expr, val)


def render_function(entry, info, order, ptr_mode, signed, ret_type, g):
    addr = entry["addr_i"]
    name = "FUN_%08x" % addr
    roles = param_roles(info)
    nparam = (max(info["params"]) + 1) if info["params"] else 0
    names = ["p", "a", "b", "c"]
    ctx = {"params": {i: names[i] for i in range(nparam)},
           "decls": {}, "externs": {}}
    decl_parts = []
    for i in range(nparam):
        if i in roles and (roles[i]["direct"] or roles[i]["ptr"]):
            dt = ptr_decl(roles, i, ptr_mode, signed == "unsigned")
        else:
            dt = "int" if signed == "int" else "unsigned int"
        ctx["decls"][i] = dt
        sep = "" if dt.endswith("*") else " "
        decl_parts.append("%s%s%s" % (dt, sep, ctx["params"][i]))
    # stores, in requested order
    body_lines = []
    for si in order:
        st = info["stores"][si]
        expr = emit_mem(st["addr"], st["ty"], ctx, ptr_mode, load=False,
                        val=render_expr(st["val"], ctx, ptr_mode))
        body_lines.append("    " + expr)
    ret_type = ret_type or ("void" if info["ret"] is None else "int")
    if info["ret"] is not None:
        body_lines.append("    return %s;" % render_expr(info["ret"], ctx, ptr_mode))
    head = [
        "// FUNCTION: SLPM 0x%08X  size %d" % (addr, entry["size"]),
        "// sig: %s" % entry.get("sig", ""),
        "// auto-generated by tools/auto_match.py (M2.2); verified byte-exact",
        "",
    ]
    for e in sorted(ctx["externs"].values()):
        head.append(e)
    if ctx["externs"]:
        head.append("")
    head.append("%s %s(%s) {" % (ret_type, name,
                                 ", ".join(decl_parts) if decl_parts else "void"))
    if not body_lines:
        head.append("}")
    else:
        head += body_lines
        head.append("}")
    return "\n".join(head) + "\n"


# ---------------------------------------------------------------- candidates
def store_orders(n):
    if n <= 1:
        return [tuple(range(n))]
    if n <= 4:
        perms = list(itertools.permutations(range(n)))
        perms.sort(key=lambda p: (sum(1 for i, x in enumerate(p) if x != i), p))
        return [tuple(range(n))] + [p for p in perms if p != tuple(range(n))][:11]
    out = [tuple(range(n)), tuple(reversed(range(n)))]
    for k in range(1, n):
        out.append(tuple(list(range(k, n)) + list(range(k))))
    return out


def generate(entry, body):
    try:
        info = translate(body)
        variants = []
        orders = store_orders(len(info["stores"]))
        gs = entry.get("g") or ["0"]
        rets = ["int"] if info["ret"] is not None else ["void"]
        if info["ret"] is not None and info["ret"][0] == "load" \
                and info["ret"][1][0] == 4:
            rets.append("unsigned int")
        if info["uses64"]:
            rets.append("long long")
        combos = []
        # most likely first: natural types, program order, queue -G
        for g in gs:
            combos.append((orders[0], "natural", "int", rets[0], g))
        for g in gs:
            combos.append((orders[0], "natural", "unsigned", rets[0], g))
        combos.append((orders[0], "natural", "int", rets[-1], gs[0]))
        combos.append((orders[0], "cast", "int", rets[0], gs[0]))
        combos.append((orders[0], "cast", "unsigned", rets[0], gs[0]))
        for o in orders[1:]:
            combos.append((o, "natural", "int", rets[0], gs[0]))
        for o in orders[:4]:
            combos.append((o, "natural", "unsigned", rets[0], gs[-1]))
            combos.append((o, "cast", "int", rets[0], gs[-1]))
        if info["uses64"]:
            for o in orders[:3]:
                combos.append((o, "natural", "long long", "long long", gs[0]))
        seen = set()
        for order, pm, sg, rt, g in combos:
            try:
                src = render_function(entry, info, order, pm, sg, rt, g)
            except Unsupported:
                continue
            if src in seen:
                continue
            seen.add(src)
            variants.append({"src": src, "g": g, "variant": "%s/%s/%s/%s" % (
                "ord" + "".join(map(str, order)), pm, sg, rt)})
            if len(variants) >= MAX_CAND:
                break
        if not variants:
            return [], "no candidate rendered"
        return variants, ""
    except Unsupported as e:
        return [], "unsupported: %s" % e


# ---------------------------------------------------------------- bookkeeping
def load_queue_index():
    with open(QUEUE, encoding="utf-8") as f:
        doc = json.load(f)
    return {C.canon(e["addr"]): e for e in doc["entries"]}


def update_overrides(entry, source_rel, note, g):
    data = json.load(open(OVERRIDES, encoding="utf-8"))
    addr_i = entry["addr_i"]
    funcs = [f for f in data.get("functions", [])
             if int(str(f["addr"]), 16) != addr_i]
    funcs.append({
        "addr": "0x%08X" % addr_i,
        "size": entry["size"],
        "name": "FUN_%08x" % addr_i,
        "source": source_rel,
        "g": int(g),
        "status": "matched",
        "note": note,
    })
    funcs.sort(key=lambda f: int(str(f["addr"]), 16))
    data["functions"] = funcs
    with open(OVERRIDES, "w", newline="\n", encoding="utf-8") as f:
        json.dump(data, f, indent=2, ensure_ascii=False)
        f.write("\n")


def append_ledger(entry, g, attempts, note):
    header = "addr\tname\tsize\tresult\tflags\tassembler\tattempts\tnote\n"
    if not os.path.exists(LEDGER):
        with open(LEDGER, "w", newline="\n", encoding="utf-8") as f:
            f.write(header)
    with open(LEDGER, "a", newline="\n", encoding="utf-8") as f:
        f.write("%s\tFUN_%08x\t%d\tMATCH\t-O2 -mips3 -G%d\tee-gcc 2.96-ee-001003-1\t%d\t%s\n" % (
            entry["addr"], entry["addr_i"], entry["size"], int(g), attempts,
            note.replace("\t", " ")))


def run_progress():
    exe = "C:/msys64/usr/bin/make.exe"
    if not os.path.exists(exe):
        exe = "make"
    t0 = time.time()
    r = subprocess.run([exe, "progress"], cwd=ROOT, capture_output=True, text=True)
    out = (r.stdout or "") + (r.stderr or "")
    tail = "\n".join(out.strip().splitlines()[-6:])
    print("  make progress: exit=%d (%.1fs)\n%s" % (r.returncode, time.time() - t0, tail))
    return r.returncode


def select_sample(eligible, limit, stride=1, mode="systematic"):
    """Pick the functions a run will work on, in the order they are claimed."""
    if mode == "head":
        return eligible[:limit]
    if mode == "stride":
        return eligible[::max(1, int(stride))][:limit]
    # systematic: evenly spaced over the difficulty-ordered tier, so the sample
    # covers every size bucket in proportion instead of only the smallest ones.
    n = min(limit, len(eligible))
    if n <= 0:
        return []
    if n == len(eligible):
        return list(eligible)
    step = len(eligible) / float(n)
    return [eligible[min(len(eligible) - 1, int(i * step + step / 2.0))]
            for i in range(n)]


def run_batch(args, batch_no, index, addrs):
    recs = []
    for a in addrs:
        try:
            recs.append(C.claim_one(args.owner, a, lease=args.lease))
        except SystemExit as exc:
            print("  skip %s: %s" % (a, exc))
    if not recs:
        print("no claimable functions in this batch")
        return None
    tag = "%s%02d" % (args.tag_prefix, batch_no)
    funcs = []
    rows = []
    for rec in recs:
        e = index[rec["addr"]]
        body = BYFN.get(e["addr_i"], [])
        cands, why = generate(e, body)
        if not cands:
            rec2 = C.complete(args.owner, e["addr"], "UNSUPPORTED", 0,
                              note=why, source="")
            rows.append({"addr": e["addr"], "name": e["name"], "tier": e["tier"],
                         "size": e["size"], "core": e["core"], "cls": e["cls"],
                         "sig": e["sig"], "result": "UNSUPPORTED", "attempts": 0,
                         "note": why, "source": "", "g": None,
                         "variant": ""})
            print("  %s %4dB %-28s UNSUPPORTED  %s" % (e["addr"], e["size"], e["sig"], why))
            continue
        funcs.append({"entry": e, "cands": cands, "tag": tag})

    def compile_wave(subset, cand_slice, wave):
        items = []
        for f in subset:
            e = f["entry"]
            for ci, c in enumerate(f["cands"][cand_slice[0]:cand_slice[1]]):
                ci_abs = cand_slice[0] + ci
                key = "%x_%02d" % (e["addr_i"], ci_abs)
                items.append({"key": key, "src": c["src"], "g": int(c["g"])})
        objs = MK.compile_batch(items, "%s_w%d" % (tag, wave),
                                verbose=not args.quiet)
        return objs

    # wave 1
    wave_funcs = [f for f in funcs]
    objs = compile_wave(wave_funcs, (0, WAVE1), 1)
    pending = []
    for f in wave_funcs:
        e = f["entry"]
        hit = None
        last_r = None
        for ci in range(min(WAVE1, len(f["cands"]))):
            key = "%x_%02d" % (e["addr_i"], ci)
            last_r = MK.verify_obj(objs.get(key), e["addr_i"], e["size"])
            if last_r["ok"]:
                hit = (ci, f["cands"][ci])
                break
        attempts = len(f["cands"][:WAVE1])
        if hit:
            f["hit"] = (hit[0] + 1, hit[1], attempts)
        else:
            f["last_r"] = last_r
            pending.append(f)

    # wave 2 for unmatched
    wave2_objs = {}
    if pending and any(len(f["cands"]) > WAVE1 for f in pending):
        wave2_objs = compile_wave([f for f in pending if len(f["cands"]) > WAVE1],
                                  (WAVE1, MAX_CAND), 2)
    for f in pending:
        e = f["entry"]
        total = min(WAVE1, len(f["cands"]))
        for ci in range(WAVE1, len(f["cands"])):
            key = "%x_%02d" % (e["addr_i"], ci)
            r = MK.verify_obj(wave2_objs.get(key), e["addr_i"], e["size"])
            total = ci + 1
            f["last_r"] = r
            if r["ok"]:
                f["hit"] = (ci + 1, f["cands"][ci])
                break
        if "hit" not in f:
            f["hit"] = None
        f["attempts"] = total
        f["first"] = f.get("last_r")

    matched = 0
    for f in funcs:
        e = f["entry"]
        key_hit = f.get("hit")
        if key_hit:
            attempts, cand, _ = key_hit
            try:
                src_rel = "src/functions/%08x.c" % e["addr_i"]
                src_abs = os.path.join(ROOT, src_rel)
                with open(src_abs, "w", newline="\n", encoding="utf-8") as fh:
                    fh.write(cand["src"])
                note = "M2.2 auto: %s; %d candidate(s)" % (
                    f["cands"][0]["variant"], attempts)
                update_overrides(e, src_rel, note, cand["g"])
                append_ledger(e, cand["g"], attempts, note)
                C.complete(args.owner, e["addr"], "MATCH", attempts,
                           note=note, source=src_rel)
                matched += 1
                row = {"addr": e["addr"], "name": e["name"], "tier": e["tier"],
                       "size": e["size"], "core": e["core"], "cls": e["cls"],
                       "sig": e["sig"], "result": "MATCH", "attempts": attempts,
                       "note": note, "source": src_rel, "g": cand["g"],
                       "variant": cand["variant"]}
                print("  %s %4dB %-28s MATCH (attempt %d, -G%s)" % (
                    e["addr"], e["size"], e["sig"], attempts, cand["g"]))
            except Exception as exc:  # keep the batch alive; claim becomes ERROR
                C.complete(args.owner, e["addr"], "ERROR", attempts,
                           note="bookkeeping: %s" % exc)
                row = {"addr": e["addr"], "name": e["name"], "tier": e["tier"],
                       "size": e["size"], "core": e["core"], "cls": e["cls"],
                       "sig": e["sig"], "result": "ERROR", "attempts": attempts,
                       "note": str(exc), "source": "", "g": cand["g"],
                       "variant": cand["variant"]}
                print("  %s ERROR %s" % (e["addr"], exc))
        else:
            attempts = f.get("attempts", 0)
            fd = f.get("first") or {}
            diff = fd.get("first_diff")
            note = fd.get("reason", "no candidate matched")
            if diff:
                note += " first=%s" % (diff,)
            C.complete(args.owner, e["addr"], "MISS", attempts, note=note)
            row = {"addr": e["addr"], "name": e["name"], "tier": e["tier"],
                   "size": e["size"], "core": e["core"], "cls": e["cls"],
                   "sig": e["sig"], "result": "MISS", "attempts": attempts,
                   "note": note, "source": "", "g": None, "variant": ""}
            print("  %s %4dB %-28s MISS after %d attempts  %s" % (
                e["addr"], e["size"], e["sig"], attempts, note[:70]))
        rows.append(row)
    return {"batch": batch_no, "tag": tag, "claimed": len(recs),
            "free_before": len(addrs), "matched": matched, "rows": rows,
            "ts": time.strftime("%Y-%m-%dT%H:%M:%S%z")}


def update_results(batch_doc):
    doc = {"schema": 1, "project": "IsPurePC-Matching", "policy": {},
           "batches": []}
    if os.path.exists(RESULTS):
        try:
            doc = json.load(open(RESULTS, encoding="utf-8"))
        except json.JSONDecodeError:
            pass
    doc["batches"].append(batch_doc)
    rows = [r for b in doc["batches"] for r in b["rows"]]
    done = [r for r in rows if r["result"] in ("MATCH", "MISS")]
    matched = [r for r in rows if r["result"] == "MATCH"]
    tried = [r for r in done if r["attempts"] > 0]
    doc["summary"] = {
        "functions": len(rows),
        "matched": len(matched),
        "miss": sum(1 for r in rows if r["result"] == "MISS"),
        "unsupported": sum(1 for r in rows if r["result"] == "UNSUPPORTED"),
        "match_rate": round(len(matched) / len(rows), 4) if rows else 0.0,
        "attempts_sum": sum(r["attempts"] for r in rows),
        "avg_attempts": round(sum(r["attempts"] for r in tried) / len(tried), 2) if tried else 0.0,
        "avg_attempts_matched": round(sum(r["attempts"] for r in matched) / len(matched), 2) if matched else 0.0,
        "by_tier": {},
        "by_size": {},
    }
    for r in rows:
        t = r["tier"]
        d = doc["summary"]["by_tier"].setdefault(t, {"n": 0, "match": 0})
        d["n"] += 1
        d["match"] += 1 if r["result"] == "MATCH" else 0
    for r in rows:
        s = str(r["size"])
        d = doc["summary"]["by_size"].setdefault(s, {"n": 0, "match": 0})
        d["n"] += 1
        d["match"] += 1 if r["result"] == "MATCH" else 0
    doc["generated"] = time.strftime("%Y-%m-%dT%H:%M:%S%z")
    with open(RESULTS, "w", newline="\n", encoding="utf-8") as f:
        json.dump(doc, f, indent=1, ensure_ascii=False)
        f.write("\n")
    return doc


def clean_m2_2():
    """Remove everything a previous M2.2 auto run wrote (idempotent reset)."""
    removed_overrides = 0
    removed_src = []
    if os.path.exists(OVERRIDES):
        data = json.load(open(OVERRIDES, encoding="utf-8"))
        keep = []
        for fn in data.get("functions", []):
            if str(fn.get("note", "")).startswith("M2.2 auto"):
                removed_overrides += 1
                src = fn.get("source", "")
                p = os.path.join(ROOT, src)
                if src and os.path.exists(p):
                    os.remove(p)
                    removed_src.append(src)
            else:
                keep.append(fn)
        data["functions"] = keep
        with open(OVERRIDES, "w", newline="\n", encoding="utf-8") as f:
            json.dump(data, f, indent=2, ensure_ascii=False)
            f.write("\n")
    removed_ledger = 0
    if os.path.exists(LEDGER):
        lines = open(LEDGER, encoding="utf-8").read().splitlines()
        keep = [ln for ln in lines if "M2.2 auto" not in ln]
        removed_ledger = len(lines) - len(keep)
        with open(LEDGER, "w", newline="\n", encoding="utf-8") as f:
            f.write("\n".join(keep) + "\n")
    for p in (RESULTS, C.CLAIMS):
        if os.path.exists(p):
            os.remove(p)
    print("cleaned: %d overrides, %d src files, %d ledger rows; results/claims removed" % (
        removed_overrides, len(removed_src), removed_ledger))
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--owner", default="m22-worker")
    ap.add_argument("--tier", default="easy")
    ap.add_argument("--limit", type=int, default=50, help="total functions")
    ap.add_argument("--batch-size", type=int, default=10)
    ap.add_argument("--stride", type=int, default=3)
    ap.add_argument("--sample", default="systematic",
                    choices=["systematic", "head", "stride"])
    ap.add_argument("--lease", type=int, default=1800)
    ap.add_argument("--tag-prefix", default="m22b")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--addr", action="append", default=None,
                    help="only these addresses (dry-run/debug)")
    ap.add_argument("--no-progress", action="store_true")
    ap.add_argument("--quiet", action="store_true")
    ap.add_argument("--clean", action="store_true",
                    help="remove a previous M2.2 auto run (overrides/src/ledger/results/claims)")
    args = ap.parse_args(argv)

    if args.clean:
        return clean_m2_2()

    global BYFN, QUEUE_DOC
    symbols = triage.parse_symbols()
    BYFN = triage.parse_asm(symbols=symbols)
    with open(QUEUE, encoding="utf-8") as f:
        QUEUE_DOC = json.load(f)
    index = load_queue_index()

    if args.addr:
        entries = [index[C.canon(a)] for a in args.addr if C.canon(a) in index]
        for e in entries:
            cands, why = generate(e, BYFN.get(e["addr_i"], []))
            print("=== %s %s size=%d core=%d sig=%s" % (
                e["addr"], e["tier"], e["size"], e["core"], e["sig"]))
            if why:
                print("  unsupported:", why)
            for i, c in enumerate(cands[:4]):
                print("--- candidate %d variant=%s g=%s" % (i + 1, c["variant"], c["g"]))
                print(c["src"])
        return 0

    batch_no = 0
    total_matched = 0
    t0 = time.time()
    remaining = args.limit
    cdoc = C.load_claims()
    eligible = C.eligible(QUEUE_DOC, cdoc, tier=args.tier)
    plan = select_sample(eligible, args.limit, args.stride, args.sample)
    print("sample: %s, %d of %d eligible (%s)" % (
        args.sample, len(plan), len(eligible), args.tier))
    while remaining > 0 and plan:
        batch_no += 1
        size = min(args.batch_size, remaining)
        chunk, plan = plan[:size], plan[size:]
        doc = run_batch(args, batch_no, index, [e["addr"] for e in chunk])
        if doc is None:
            break
        total_matched += doc["matched"]
        s = update_results(doc)["summary"]
        remaining -= doc["claimed"]
        print("batch %d: claimed=%d matched=%d | running total %d/%d (%.1f%%), "
              "avg attempts %.2f | %.1fs" % (
                  batch_no, doc["claimed"], doc["matched"], s["matched"],
                  args.limit, s["match_rate"] * 100, s["avg_attempts"],
                  time.time() - t0))
        if not args.no_progress:
            run_progress()
        if doc["claimed"] < size:
            break
    print("\nM2.2 batch done: %d matched in %.1fs" % (total_matched, time.time() - t0))
    return 0


if __name__ == "__main__":
    sys.exit(main())
