#!/usr/bin/env python3
"""llm_match.py - evidence cards + LLM-generated C + match_kit byte verification.

M2.3 changes the generator: instead of auto_match.py's hand-written translator,
each function is described by a compact evidence card (disassembly, raw bytes,
ABI/compiler hints, previous-round byte diffs) and an LLM is asked for ordinary C.
Every returned candidate is compiled with ee-gcc 2.96 inside WSL and compared
byte-for-byte after relocation; only exact matches are kept.

LLM backend: Anthropic Messages API.  Credentials are resolved in this order:
  1. CLI flags (--api-url / --api-key / --model / --session)
  2. config/llm.local.json (gitignored)
  3. the user's Claude Code settings (~/.claude/settings.json "env")
  4. LLM_BASE_URL / LLM_API_KEY / LLM_MODEL environment variables

Padding policy: 157 of the 195 medium functions end in alignment nops that C
cannot reproduce.  For those the gate compares the compiled body with the first
core bytes and requires len(compiled) == core; such hits are recorded as
MATCH_CORE and are NOT spliced into config/overrides.json (that gate stays
byte-exact), so make check is unaffected.

Usage
  python tools/llm_match.py --tier medium --limit 195 --batch-size 6 --rounds 2 \
         --owner m23-llm --sample systematic
  python tools/llm_match.py --addr 0x001B4908 --dry-run     # print evidence card
  python tools/llm_match.py --addr 0x001B4908 --rounds 1    # one function test

No CHEAT: candidates are ordinary C (no asm/.word/volatile/goto/attributes);
everything that does not compile to the original bytes is discarded.
"""
import argparse
import json
import os
import re
import subprocess
import sys
import time
import urllib.error
import urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)

import build as B          # noqa: E402
import claims as C         # noqa: E402
import match_kit as MK     # noqa: E402
import triage              # noqa: E402

QUEUE = os.path.join(ROOT, "build", "queue.json")
OVERRIDES = os.path.join(ROOT, "config", "overrides.json")
LEDGER = os.path.join(ROOT, "progress", "ledger.tsv")
SRC_DIR = os.path.join(ROOT, "src", "functions")
RESULTS = os.path.join(ROOT, "build", "m2-3-llm-results.json")
PADDED_JSON = os.path.join(ROOT, "build", "m2-3-llm-padded.json")
EVIDENCE_DIR = os.path.join(ROOT, "build", "llm-evidence")
LLM_LOCAL = os.path.join(ROOT, "config", "llm.local.json")

GP_BASE = 0x002779F0
TEXT_ADDR = B.TEXT_ADDR
TEXT_OFF = B.TEXT_OFF
BASEROM = B.BASEROM
DEFAULT_MODEL = "deepseek-v4.1-flash"
MAX_CANDIDATES = 2
_BASEROM = None


class LlmError(Exception):
    pass


# ---------------------------------------------------------------- LLM transport
def _claude_env():
    path = os.path.expanduser("~/.claude/settings.json")
    try:
        with open(path, encoding="utf-8") as f:
            doc = json.load(f)
        env = doc.get("env", {})
        return env if isinstance(env, dict) else {}
    except (OSError, ValueError):
        return {}


def resolve_llm_cfg(args):
    env = _claude_env()
    cfg = {
        "base_url": os.environ.get("LLM_BASE_URL") or env.get("ANTHROPIC_BASE_URL") or "",
        "api_key": os.environ.get("LLM_API_KEY") or env.get("ANTHROPIC_AUTH_TOKEN") or "",
        "model": os.environ.get("LLM_MODEL") or env.get("ANTHROPIC_MODEL") or DEFAULT_MODEL,
        "session": "",
    }
    hdr = env.get("ANTHROPIC_CUSTOM_HEADERS", "")
    m = re.search(r"x-opencode-session\s*:\s*([A-Za-z0-9._-]+)", hdr or "", re.I)
    if m:
        cfg["session"] = m.group(1)
    if os.path.exists(LLM_LOCAL):
        try:
            with open(LLM_LOCAL, encoding="utf-8") as f:
                local = json.load(f)
            for k in ("base_url", "api_key", "model", "session"):
                if local.get(k):
                    cfg[k] = local[k]
        except (OSError, ValueError) as exc:
            print("warn: ignoring %s (%s)" % (LLM_LOCAL, exc))
    for key, val in (("base_url", args.api_url), ("api_key", args.api_key),
                     ("model", args.model), ("session", args.session)):
        if val:
            cfg[key] = val
    cfg["base_url"] = (cfg["base_url"] or "https://api.anthropic.com").rstrip("/")
    cfg["thinking"] = getattr(args, "thinking", "auto")
    cfg["thinking_budget"] = int(getattr(args, "thinking_budget", 3000))
    cfg["stream"] = getattr(args, "stream", "on")
    return cfg


def llm_call(cfg, system, user, max_tokens=12000, timeout=240, retries=2, quiet=False):
    """Streaming Anthropic Messages call; stream=true avoids long-read timeouts."""
    url = cfg["base_url"] + "/v1/messages"
    payload = {
        "model": cfg["model"],
        "max_tokens": max_tokens,
        "system": system,
        "messages": [{"role": "user", "content": user}],
        "stream": True,
    }
    if cfg.get("thinking") == "off":
        payload["thinking"] = {"type": "disabled"}
    else:
        payload["thinking"] = {"type": "enabled",
                               "budget_tokens": int(cfg.get("thinking_budget", 3000))}
    if cfg.get("stream") == "off":
        payload.pop("stream", None)
    headers = {
        "content-type": "application/json",
        "anthropic-version": "2023-06-01",
        "user-agent": "llm_match/1.0 (IsPurePC M2.3)",
    }
    if cfg["api_key"]:
        headers["x-api-key"] = cfg["api_key"]
        headers["authorization"] = "Bearer " + cfg["api_key"]
    if cfg["session"]:
        headers["x-opencode-session"] = cfg["session"]
    last = None
    for attempt in range(1, retries + 1):
        try:
            req = urllib.request.Request(url, data=json.dumps(payload).encode("utf-8"),
                                         headers=headers, method="POST")
            if cfg.get("stream") == "off":
                with urllib.request.urlopen(req, timeout=timeout) as resp:
                    doc = json.loads(resp.read().decode("utf-8"))
                texts = [b.get("text", "") for b in doc.get("content", [])
                         if b.get("type") == "text"]
                text = "\n".join(t for t in texts if t).strip()
                if not text:
                    raise LlmError("empty text content")
                return {"text": text, "usage": doc.get("usage", {}),
                        "stop": doc.get("stop_reason")}
            parts = []
            usage = {}
            stop = None
            with urllib.request.urlopen(req, timeout=timeout) as resp:
                for raw in resp:
                    line = raw.decode("utf-8", "replace").strip()
                    if not line.startswith("data:"):
                        continue
                    data = line[5:].strip()
                    if not data or data == "[DONE]":
                        continue
                    try:
                        ev = json.loads(data)
                    except ValueError:
                        continue
                    etype = ev.get("type")
                    if etype == "content_block_delta":
                        delta = ev.get("delta") or {}
                        if delta.get("type") == "text_delta":
                            parts.append(delta.get("text", ""))
                    elif etype == "message_start":
                        usage.update((ev.get("message") or {}).get("usage") or {})
                    elif etype == "message_delta":
                        usage.update(ev.get("usage") or {})
                        stop = (ev.get("delta") or {}).get("stop_reason", stop)
                    elif etype == "error":
                        raise LlmError("stream error: %s" % (ev.get("error"),))
            text = "".join(parts).strip()
            if not text:
                raise LlmError("empty streamed text")
            return {"text": text, "usage": usage, "stop": stop}
        except urllib.error.HTTPError as exc:
            try:
                body = exc.read().decode("utf-8", "replace")[:600]
            except Exception:
                body = ""
            last = "HTTP %s: %s" % (exc.code, body.replace("\n", " "))
        except Exception as exc:  # network / timeout / malformed json
            last = "%s: %s" % (type(exc).__name__, exc)
        if attempt < retries:
            delay = 2.0 * attempt
            if not quiet:
                print("  llm retry %d/%d in %.0fs (%s)" % (attempt, retries - 1, delay, last))
            time.sleep(delay)
    raise LlmError(last or "unknown LLM error")


def parse_reply(text):
    """Extract the JSON object from an LLM reply (tolerates code fences / prose)."""
    t = text.strip()
    fence = chr(96) * 3
    parts = []
    if fence in t:
        parts += re.findall(re.escape(fence) + r"(?:json)?\s*(.*?)" + re.escape(fence),
                            t, re.S)
    parts.append(t)
    start, end = t.find("{"), t.rfind("}")
    if 0 <= start < end:
        parts.append(t[start:end + 1])
    for blob in parts:
        blob = blob.strip()
        if not blob:
            continue
        try:
            doc = json.loads(blob)
        except ValueError:
            continue
        if isinstance(doc, dict):
            return doc
    raise LlmError("reply is not valid JSON: %r" % t[:200])


# ---------------------------------------------------------------- evidence cards
def baserom():
    global _BASEROM
    if _BASEROM is None:
        with open(BASEROM, "rb") as f:
            _BASEROM = f.read()
    return _BASEROM


def original_bytes(addr_i, size):
    off = TEXT_OFF + (addr_i - TEXT_ADDR)
    return baserom()[off:off + size]


def words_hex(data):
    return " ".join(data[i:i + 4][::-1].hex() for i in range(0, len(data), 4))


def sym_addr(name):
    for p in ("FUN_", "func_", "D_", "jtbl_", "L_"):
        if name.startswith(p):
            head = name[len(p):].split(".")[0].split("+")[0]
            try:
                return int(head, 16)
            except ValueError:
                return None
    if name.startswith(".L"):
        try:
            return int(name[2:], 16)
        except ValueError:
            return None
    return None


def collect_globals(body):
    """Addresses/symbols referenced through %hi/%lo or $gp."""
    out = []
    seen = set()

    def add(addr, name, how):
        key = addr
        if key in seen:
            return
        seen.add(key)
        out.append((addr, name, how))

    for _a, _w, _mn, ops in body:
        for m in re.finditer(r"(-?0x[0-9A-Fa-f]+)\(\$gp\)", ops):
            raw = int(m.group(1), 0)
            off = raw - 0x10000 if raw & 0x8000 and raw > 0 else raw
            addr = (GP_BASE + off) & 0xFFFFFFFF
            add(addr, "D_%08X" % addr, "$gp%+d" % off)
        for m in re.finditer(r"\((0x[0-9A-Fa-f]+)\s*>>\s*16\)", ops):
            addr = int(m.group(1), 16)
            add(addr, "D_%08X" % addr, "absolute")
        for m in re.finditer(r"%hi\(([^)]+)\)", ops):
            name = m.group(1).strip()
            addr = sym_addr(name)
            if addr is not None:
                add(addr, name, "%hi")
        for m in re.finditer(r"%lo\(([^)]+)\)", ops):
            name = m.group(1).strip()
            addr = sym_addr(name)
            if addr is not None:
                add(addr, name, "%lo")
        for m in re.finditer(r"\.L([0-9A-Fa-f]{6,})", ops):
            try:
                addr = int(m.group(1), 16)
            except ValueError:
                continue
            add(addr, "L_%08X" % addr, "branch target")
    return out


def evidence_card(entry, body, history=None, note=None):
    addr = entry["addr"]
    addr_i = entry["addr_i"]
    size = entry["size"]
    core = entry["core"]
    padding = size - core
    gs = entry.get("g") or ["0"]
    lines = []
    lines.append("### FUNCTION %s" % addr)
    lines.append("size=%d core=%d trailing_padding=%d tier=%s cls=%s flags=%s"
                 % (size, core, padding, entry.get("tier"), entry.get("cls"),
                    ",".join(entry.get("flags") or []) or "none"))
    lines.append("allowed -G: %s   (G0: all globals via %%hi/%%lo; G8: globals <=8B via $gp)"
                 % " / ".join("-G" + str(g) for g in gs))
    lines.append("mnemonic sequence (triage sig): %s" % entry.get("sig", ""))
    if note:
        lines.append("note: %s" % note)
    lines.append("ABI: leaf function, args $a0-$a3, return $v0, return address $ra, "
                 "$gp=0x%08X; must compile to exactly %d byte(s)."
                 % (GP_BASE, core))
    if padding:
        lines.append("PADDING: the last %d byte(s) of the original are 4-byte alignment nops; "
                     "do NOT reproduce them. Your compiled .text must be exactly %d bytes."
                     % (padding, core))
    globs = collect_globals(body)
    if globs:
        lines.append("globals / symbols referenced:")
        for a, name, how in globs:
            kind = "branch" if how == "branch target" else "data"
            lines.append("  %s  %s  (%s, %s)" % (name, "0x%08X" % a, how, kind))
    else:
        lines.append("globals / symbols referenced: none")
    lines.append("DISASSEMBLY (MIPS III; the instruction after jr/branch is its delay slot "
                 "and still executes):")
    for a, w, mn, ops in body:
        mark = ""
        if mn in ("jr", "jalr"):
            mark = "   <-- return"
        lines.append("  %08X  %-8s %s%s" % (a, mn, ops, mark))
    lines.append("ORIGINAL BYTES (memory order, 4-byte words):")
    lines.append("  " + words_hex(original_bytes(addr_i, core)))
    if history:
        lines.append("PREVIOUS LLM ATTEMPTS (byte comparison after relocation):")
        for i, h in enumerate(history[-6:], 1):
            lines.append("  attempt %d: candidate g=%s -> %s"
                         % (i, h.get("g"), h.get("summary")))
            if h.get("disasm"):
                for dl in h["disasm"].splitlines()[:24]:
                    lines.append("      " + dl)
            if h.get("compile_error"):
                lines.append("    COMPILE ERROR: " + h["compile_error"][:600].replace("\n", " | "))
    return "\n".join(lines)


SYSTEM_PROMPT = """You are an expert reverse engineer of PlayStation 2 (Emotion Engine, MIPS III) binaries.
Task: given one function's exact original machine code, write ordinary C that the ORIGINAL
compiler (ee-gcc 2.96-ee-001003-1, flags: -O2 -mips3 -G<n>) compiles back to EXACTLY the same
bytes after relocation.

HARD RULES
- Emit standalone C function definitions named FUN_<8 lowercase hex digits>, matching each card's address.
- Ordinary C only: no inline asm, no .word, no volatile, no goto, no labels, no __attribute__,
  no #include. You may declare extern globals/functions and typedefs.
- The compiled .text must have exactly the byte length stated on the card (core bytes).
  Trailing alignment nops of the original are NOT part of the C function.
- Respect the ABI: $a0-$a3 arguments, $v0 return value, $ra return address, $gp = 0x002779F0.
  A leaf function has no stack frame or prologue.
- Globals are reached either through %hi/%lo pairs (absolute D_XXXXXXXX addresses, declare
  extern with the type implied by load/store width and signedness) or, with -G8, through
  $gp-relative offsets for objects of 8 bytes or less. The card lists the allowed -G values;
  emit "g": <value> for every candidate.
- Use ONLY the symbolic names printed on the card for globals and branch targets. NEVER write
  a numeric absolute address in C (for example 0x00281501): declare the named symbol as
  extern and access it through that name. Numeric address literals make gcc 2.96 allocate
  $at for the address, which does not match the original register choice.
- The instruction after jr $ra is the delay slot and executes before returning; arrange the
  last statement so gcc schedules that instruction into the slot (usually the final store,
  or the load feeding the return value).
- Match instruction selection and operand order. gcc 2.96 reorders, folds constants and
  allocates registers aggressively; use the simplest natural expression that produces the
  observed instructions, and do not introduce temporaries unless the disassembly requires them.
- Reconstruct branches with if / else / early return. A branch delay slot instruction is the
  one printed after the branch instruction and is part of the taken/not-taken path like the
  compiler scheduled it. Splat labels such as .L001B4918 denote absolute target addresses.
- Width/signedness matters: lb/lbu/lh/lhu/lw/lwu/ld and sb/sh/sw/sd imply the pointed-to type;
  slt/slti are signed, sltu/sltiu unsigned. Use casts only when the disassembly forces them.
- If the function returns a 64-bit value, use long long / unsigned long long as appropriate.

OUTPUT: strict JSON only, no markdown fences, no prose:
{"functions":[{"addr":"0x001B4908","candidates":[{"g":0,"code":"extern ...; int FUN_001b4908(int *p) { ... }","why":"short reason"}]}]}
Give 1-2 genuinely different candidates when possible (different return type, type width,
statement order, or symbol form), not duplicates. Every candidate must be a complete
definition (extern declarations + the function itself)."""

USER_INSTRUCTIONS = """Compile targets are checked by byte-for-byte comparison after relocation.
Write the best 1-2 ordinary C candidates for EACH function below, following the system rules.
Return strict JSON covering all %d function(s), keyed by the exact addresses shown."""


# ---------------------------------------------------------------- compile/verify
def compile_objects(items, tag, quiet=False):
    """items: [{"key","src","g"}] -> {key: obj path or None}."""
    return MK.compile_batch(items, tag, verbose=not quiet)


def read_compile_error(tag, key):
    p = os.path.join(MK.CAND_ROOT, tag, key + ".err")
    if os.path.exists(p):
        try:
            with open(p, encoding="utf-8", errors="replace") as f:
                return f.read().strip()
        except OSError:
            return ""
    return ""


def disasm_objects(objs, tag):
    """Batch-disassemble compiled objects inside WSL -> {key: text}."""
    if not objs:
        return {}
    work = MK.CAND_ROOT
    script = [
        "#!/bin/bash",
        "export LC_ALL=C",
        'D="%s"' % (B.WSL_ROOT + "/build/candidates/" + tag),
        'for f in "$D"/*.G*.o; do',
        '  [ -f "$f" ] || continue',
        '  b=$(basename "$f" .o)',
        '  /opt/ee-ld/bin/mips-ps2-decompals-objdump -d "$f" > "$D/$b.dis" 2>&1 || true',
        "done",
        "echo OBJDUMP_DONE",
    ]
    path = os.path.join(ROOT, "build", "_wsl_objdump_%s.sh" % tag)
    with open(path, "w", newline="\n", encoding="utf-8") as f:
        f.write("\n".join(script) + "\n")
    wpath = B.WSL_ROOT + "/build/_wsl_objdump_%s.sh" % tag
    try:
        subprocess.run(["wsl.exe", "-d", B.WSL_DISTRO, "-u", "root", "--", "bash", wpath],
                       cwd=ROOT, capture_output=True, text=True, encoding="utf-8",
                       errors="replace", timeout=120)
    except (OSError, subprocess.SubprocessError):
        pass
    out = {}
    for key in objs:
        p = os.path.join(work, tag, key + ".dis")
        if not os.path.exists(p):
            continue
        try:
            with open(p, encoding="utf-8", errors="replace") as f:
                lines = []
                for line in f:
                    m = re.match(r"^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(.*)$", line)
                    if m:
                        lines.append("  %s  %s" % (m.group(2), m.group(3).strip()))
                out[key] = "\n".join(lines)
        except OSError:
            pass
    return out


def verify(obj, entry):
    """Byte-exact verification; padding functions compare only the core bytes."""
    addr_i = entry["addr_i"]
    size = entry["size"]
    core = entry["core"]
    want_len = core if core < size else size
    if not obj or not os.path.exists(obj):
        return {"ok": False, "reason": "no-object", "compiled_len": 0,
                "want_len": want_len, "summary": "no object produced",
                "diffs": [], "ndiff": 0, "unresolved": []}
    try:
        text, stats = B.resolve_object_text(obj, entry["addr_i"])
    except SystemExit as exc:
        return {"ok": False, "reason": "elf:%s" % exc, "compiled_len": 0,
                "want_len": want_len, "summary": "ELF/resolve error: %s" % exc,
                "diffs": [], "ndiff": 0, "unresolved": []}
    orig = original_bytes(addr_i, size)[:want_len]
    diffs, ndiff = B.word_diff(text, orig)
    ok = len(text) == want_len and not diffs and not stats["unresolved"]
    first = diffs[0] if diffs else None
    if ok:
        summary = "MATCH (%d bytes)" % want_len
    else:
        parts = ["compiled %d/%d bytes" % (len(text), want_len)]
        if first:
            if first[0] == "len":
                parts.append("length differs")
            else:
                parts.append("word %s: got %s want %s" % (first[0], first[1], first[2]))
        if ndiff:
            parts.append("%d differing word(s)" % ndiff)
        if stats["unresolved"]:
            parts.append("unresolved reloc: %s" % ", ".join(stats["unresolved"][:3]))
        summary = "; ".join(parts)
    return {"ok": ok, "reason": summary, "compiled_len": len(text),
            "want_len": want_len, "summary": summary, "diffs": diffs,
            "ndiff": ndiff, "unresolved": stats["unresolved"],
            "compiled": text}


def sanitize_candidate(code, addr_i):
    problems = []
    if not re.search(r"\bFUN_%08x\s*\(" % addr_i, code, re.I):
        problems.append("missing definition FUN_%08x" % addr_i)
    for pat, label in ((r"\b(__asm__|asm)\b", "inline asm"),
                       (r"\.word\b", ".word"), (r"\bvolatile\b", "volatile"),
                       (r"\bgoto\b", "goto"), (r"__attribute__", "__attribute__"),
                       (r"#\s*include", "#include")):
        if re.search(pat, code):
            problems.append(label)
    return problems


# ---------------------------------------------------------------- bookkeeping
def update_overrides(entry, source_rel, note, g):
    data = {"functions": []}
    if os.path.exists(OVERRIDES):
        try:
            with open(OVERRIDES, encoding="utf-8") as f:
                data = json.load(f)
        except ValueError:
            pass
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


def record_padded(entry, source_rel, note, g):
    data = {"schema": 1, "functions": []}
    if os.path.exists(PADDED_JSON):
        try:
            with open(PADDED_JSON, encoding="utf-8") as f:
                data = json.load(f)
        except ValueError:
            pass
    rows = [r for r in data.get("functions", [])
            if int(str(r["addr"]), 16) != entry["addr_i"]]
    rows.append({"addr": entry["addr"], "addr_i": entry["addr_i"],
                 "size": entry["size"], "core": entry["core"],
                 "source": source_rel, "g": int(g), "note": note})
    rows.sort(key=lambda r: r["addr_i"])
    data["functions"] = rows
    with open(PADDED_JSON, "w", newline="\n", encoding="utf-8") as f:
        json.dump(data, f, indent=1, ensure_ascii=False)
        f.write("\n")


def append_ledger(entry, g, attempts, note):
    header = "addr\tname\tsize\tresult\tflags\tassembler\tattempts\tnote\n"
    if not os.path.exists(LEDGER):
        with open(LEDGER, "w", newline="\n", encoding="utf-8") as f:
            f.write(header)
    with open(LEDGER, "a", newline="\n", encoding="utf-8") as f:
        f.write("%s\tFUN_%08x\t%d\tMATCH\t-O2 -mips3 -G%d\tee-gcc 2.96-ee-001003-1\t%d\t%s\n"
                % (entry["addr"], entry["addr_i"], entry["size"], int(g), attempts,
                   note.replace("\t", " ").replace("\n", " ")))


def write_source(entry, code, meta):
    os.makedirs(SRC_DIR, exist_ok=True)
    rel = "src/functions/%08x.c" % entry["addr_i"]
    abs_path = os.path.join(ROOT, rel)
    header = ("// FUNCTION: SLPM %s  size %d  core %d\n"
              "// sig: %s\n"
              "// generated by tools/llm_match.py (M2.3, %s); verified byte-exact%s\n\n"
              % (entry["addr"], entry["size"], entry["core"], entry.get("sig", ""),
                 meta, " (core bytes; trailing padding excluded)"
                 if entry["core"] < entry["size"] else ""))
    with open(abs_path, "w", newline="\n", encoding="utf-8") as f:
        f.write(header + code.strip() + "\n")
    return rel


def run_progress():
    exe = "C:/msys64/usr/bin/make.exe"
    if not os.path.exists(exe):
        exe = "make"
    try:
        r = subprocess.run([exe, "progress"], cwd=ROOT, capture_output=True, text=True,
                           encoding="utf-8", errors="replace", timeout=180)
    except (OSError, subprocess.SubprocessError):
        return
    out = (r.stdout or "") + (r.stderr or "")
    tail = "\n".join(out.strip().splitlines()[-4:])
    print("  make progress: exit=%d\n%s" % (r.returncode, tail))


# ---------------------------------------------------------------- sample selection
def select_sample(eligible, limit, mode="systematic", stride=1):
    if mode == "head":
        return eligible[:limit]
    if mode == "stride":
        return eligible[::max(1, int(stride))][:limit]
    n = min(limit, len(eligible))
    if n <= 0:
        return []
    if n >= len(eligible):
        return list(eligible)
    step = len(eligible) / float(n)
    return [eligible[min(len(eligible) - 1, int(i * step + step / 2.0))]
            for i in range(n)]


# ---------------------------------------------------------------- LLM round
def ask_llm(cfg, entries, states, round_no, args, quiet):
    """One LLM call for a batch; returns ({addr: [candidates]}, usage)."""
    cards = [evidence_card(e, states[e["addr"]]["body"],
                           history=states[e["addr"]]["history"])
             for e in entries]
    user = USER_INSTRUCTIONS % len(entries) + "\n\n" + "\n\n".join(cards)
    if round_no > 1:
        user += ("\n\nROUND %d: earlier attempts above did not match. Correct the byte-level "
                 "differences shown (length, operand order, signedness, scheduling)." % round_no)
    reply = llm_call(cfg, SYSTEM_PROMPT, user, max_tokens=args.max_tokens,
                     timeout=args.timeout, quiet=quiet)
    try:
        doc = parse_reply(reply["text"])
    except LlmError as exc:
        if not quiet:
            print("  llm JSON parse failed (%s); asking for repair" % str(exc)[:120])
        repair = llm_call(cfg, SYSTEM_PROMPT,
                          user + "\n\nYour previous reply was not valid JSON (%s). "
                          "Return ONLY the JSON object." % str(exc)[:200],
                          max_tokens=args.max_tokens, timeout=args.timeout, quiet=quiet)
        doc = parse_reply(repair["text"])
    out = {}
    for item in doc.get("functions", []):
        addr = str(item.get("addr", "")).strip().lower()
        try:
            addr_i = int(addr, 16)
            key = "0x%08X" % addr_i
        except ValueError:
            continue
        wanted = states.get(key)
        if not wanted:
            continue
        cands = []
        raw = item.get("candidates", [])
        if isinstance(raw, (str, dict)):
            raw = [raw]
        for c in raw[:MAX_CANDIDATES]:
            if isinstance(c, str):
                code, g = c, None
            elif isinstance(c, dict):
                code, g = c.get("code", ""), c.get("g")
            else:
                continue
            if not isinstance(code, str) or "FUN_" not in code:
                continue
            probs = sanitize_candidate(code, wanted["entry"]["addr_i"])
            if probs:
                if not quiet:
                    print("  reject candidate %s: %s" % (key, ",".join(probs)))
                continue
            if g is None:
                g = (wanted["entry"].get("g") or ["0"])[0]
            try:
                g = int(g)
            except (TypeError, ValueError):
                g = int((wanted["entry"].get("g") or ["0"])[0])
            cands.append({"code": code, "g": g,
                          "why": (c.get("why", "") if isinstance(c, dict) else "")})
        if cands:
            out[key] = cands
    return out, reply.get("usage", {})


def evaluate_batch(entries, candidates, states, tag, args, quiet):
    """Compile every candidate (all allowed -G values) and record the first match."""
    items = []
    slot = {}
    for e in entries:
        st = states[e["addr"]]
        cands = candidates.get(e["addr"], [])
        if not cands:
            st["note"] = st.get("note") or "LLM returned no usable candidate"
            continue
        for ci, cand in enumerate(cands):
            gs = [cand["g"]]
            for g in (e.get("g") or ["0"]):
                if int(g) not in gs:
                    gs.append(int(g))
            for g in gs:
                key = "%x_%02d_%d" % (e["addr_i"], ci, g)
                items.append({"key": key, "src": cand["code"], "g": g})
                slot[key] = (e, ci, g, cand)
    objs = {}
    if items:
        objs = compile_objects(items, tag, quiet=quiet)
    errors = {k: read_compile_error(tag, k) for k in slot if not objs.get(k)}
    dis = disasm_objects({k: v for k, v in objs.items() if v}, tag)
    results = {}
    for key, (e, ci, g, cand) in slot.items():
        st = states[e["addr"]]
        st["attempts"] += 1
        if not objs.get(key):
            r = {"ok": False, "summary": "compile failed", "compiled_len": 0,
                 "want_len": e["core"] if e["core"] < e["size"] else e["size"],
                 "diffs": [], "ndiff": 0, "unresolved": []}
        else:
            r = verify(objs[key], e)
        entry_state = {"round": st["round"], "candidate": ci, "g": g,
                       "summary": r["summary"], "disasm": dis.get(key, "")}
        if r["ok"]:
            st["hit"] = {"cand": cand, "g": g, "r": r, "round": st["round"],
                         "ci": ci}
            results[e["addr"]] = r
            break
        if errors.get(key):
            entry_state["compile_error"] = errors[key]
            st["compile_errors"] = st.get("compile_errors", 0) + 1
        if len(st["history"]) < 8:
            st["history"].append(entry_state)
    return results


# ---------------------------------------------------------------- driver
def load_queue():
    with open(QUEUE, encoding="utf-8") as f:
        return json.load(f)


def save_evidence(entry, st):
    path = os.path.join(EVIDENCE_DIR, "%08x.json" % entry["addr_i"])
    os.makedirs(EVIDENCE_DIR, exist_ok=True)
    doc = {"addr": entry["addr"], "size": entry["size"], "core": entry["core"],
           "flags": entry.get("flags"), "sig": entry.get("sig"),
           "attempts": st["attempts"], "round": st["round"],
           "history": st["history"]}
    with open(path, "w", newline="\n", encoding="utf-8") as f:
        json.dump(doc, f, indent=1, ensure_ascii=False)


def summarize(rows, entries, calls, usage, elapsed):
    n = len(rows)
    match = [r for r in rows if r["result"] == "MATCH"]
    core = [r for r in rows if r["result"] == "MATCH_CORE"]
    miss = [r for r in rows if r["result"] == "MISS"]
    return {
        "functions": n,
        "match": len(match),
        "match_core": len(core),
        "match_total": len(match) + len(core),
        "match_rate": round((len(match) + len(core)) / float(n), 4) if n else 0.0,
        "byte_exact_rate": round(len(match) / float(n), 4) if n else 0.0,
        "miss": len(miss),
        "avg_rounds": round(sum(r["rounds"] for r in rows) / float(n), 2) if n else 0.0,
        "avg_attempts": round(sum(r["attempts"] for r in rows) / float(n), 2) if n else 0.0,
        "llm_calls": calls, "elapsed_sec": round(elapsed, 1),
        "usage": usage,
        "by_size": _group(rows, "size"), "by_cls": _group(rows, "cls"),
        "by_flags": _group_flags(rows), "by_round": _group(rows, "rounds"),
    }


def _group(rows, key):
    out = {}
    for r in rows:
        k = str(r.get(key))
        d = out.setdefault(k, {"n": 0, "match": 0, "match_core": 0})
        d["n"] += 1
        if r["result"] == "MATCH":
            d["match"] += 1
        elif r["result"] == "MATCH_CORE":
            d["match_core"] += 1
    return out


def _group_flags(rows):
    out = {}
    for r in rows:
        flags = r.get("flags") or []
        key = "+".join(sorted(flags)) or "none"
        d = out.setdefault(key, {"n": 0, "match": 0, "match_core": 0})
        d["n"] += 1
        if r["result"] == "MATCH":
            d["match"] += 1
        elif r["result"] == "MATCH_CORE":
            d["match_core"] += 1
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--owner", default="m23-llm")
    ap.add_argument("--tier", default="medium")
    ap.add_argument("--limit", type=int, default=195)
    ap.add_argument("--batch-size", type=int, default=6)
    ap.add_argument("--rounds", type=int, default=2, help="LLM correction rounds")
    ap.add_argument("--sample", default="systematic",
                    choices=["systematic", "head", "stride"])
    ap.add_argument("--stride", type=int, default=1)
    ap.add_argument("--lease", type=int, default=5400)
    ap.add_argument("--tag-prefix", default="m23l")
    ap.add_argument("--addr", action="append", default=None,
                    help="only these addresses (bypasses the claim queue)")
    ap.add_argument("--dry-run", action="store_true",
                    help="print evidence card(s) and exit")
    ap.add_argument("--no-progress", action="store_true")
    ap.add_argument("--quiet", action="store_true")
    ap.add_argument("--max-tokens", type=int, default=12000)
    ap.add_argument("--timeout", type=int, default=240)
    ap.add_argument("--sleep", type=float, default=1.0,
                    help="pause between LLM calls")
    ap.add_argument("--api-url", default=None)
    ap.add_argument("--api-key", default=None)
    ap.add_argument("--model", default=None)
    ap.add_argument("--session", default=None)
    ap.add_argument("--results", default=RESULTS, help="results JSON output path")
    ap.add_argument("--set", default=None,
                    help="address list from build/m2-5-sets.json")
    ap.add_argument("--stream", default="on", choices=["on", "off"],
                    help="off uses a plain (non-streamed) request; use with thinking=auto")
    ap.add_argument("--thinking", default="auto", choices=["auto", "off"],
                    help="off disables model thinking (faster, less deep)")
    ap.add_argument("--thinking-budget", type=int, default=3000,
                    help="token budget when thinking is enabled")
    args = ap.parse_args(argv)

    symbols = triage.parse_symbols()
    byfn = triage.parse_asm(symbols=symbols)
    qdoc = load_queue()
    index = {C.canon(e["addr"]): e for e in qdoc["entries"]}

    if args.addr:
        entries = [index[C.canon(a)] for a in args.addr if C.canon(a) in index]
        if args.dry_run:
            for e in entries:
                print(evidence_card(e, byfn.get(e["addr_i"], [])))
                print()
            return 0
    elif args.set:
        cdoc = C.load_claims(qdoc)
        sets = json.load(open(os.path.join(ROOT, "build", "m2-5-sets.json"), encoding="utf-8"))
        entries = [index[a] for a in sets.get(args.set, []) if a in index]
        entries = [e for e in entries
                   if cdoc["claims"].get(C.canon(e["addr"]), {}).get("result") != "MATCH"]
        if args.limit:
            entries = entries[:args.limit]
    else:
        cdoc = C.load_claims(qdoc)
        eligible = C.eligible(qdoc, cdoc, tier=args.tier)
        entries = select_sample(eligible, args.limit, args.sample, args.stride)
        print("sample: %s, %d of %d eligible (%s)"
              % (args.sample, len(entries), len(eligible), args.tier))
    if not entries:
        print("nothing to do")
        return 0

    cfg = resolve_llm_cfg(args)
    print("llm: %s  model=%s  key=%s  session=%s"
          % (cfg["base_url"], cfg["model"],
             "yes" if cfg["api_key"] else "NO", "yes" if cfg["session"] else "no"))

    os.makedirs(EVIDENCE_DIR, exist_ok=True)
    claimed = []
    for e in entries:
        if args.addr:
            claimed.append(e)
            continue
        try:
            C.claim_one(args.owner, e["addr"], lease=args.lease)
            claimed.append(e)
        except SystemExit as exc:
            print("  skip %s: %s" % (e["addr"], exc))
    entries = claimed
    if not entries:
        return 0

    states = {}
    for e in entries:
        states[e["addr"]] = {
            "entry": e, "body": byfn.get(e["addr_i"], []), "history": [],
            "round": 0, "attempts": 0, "hit": None, "note": None,
            "started": time.time(),
        }

    t0 = time.time()
    total_calls = 0
    usage_total = {"input_tokens": 0, "output_tokens": 0}
    batch_no = 0
    for round_no in range(1, args.rounds + 1):
        pending = [e for e in entries if not states[e["addr"]]["hit"]]
        if not pending:
            break
        print("\n== round %d: %d function(s) ==" % (round_no, len(pending)))
        for start in range(0, len(pending), args.batch_size):
            batch = pending[start:start + args.batch_size]
            batch_no += 1
            for e in batch:
                states[e["addr"]]["round"] = round_no
            tag = "%sr%d_b%02d" % (args.tag_prefix, round_no, batch_no)
            try:
                cands, usage = ask_llm(cfg, batch, states, round_no, args, args.quiet)
            except LlmError as exc:
                print("  batch %d: LLM failed: %s" % (batch_no, exc))
                for e in batch:
                    states[e["addr"]]["note"] = "LLM error: %s" % str(exc)[:200]
                continue
            total_calls += 1
            for k in usage_total:
                usage_total[k] += int(usage.get(k, 0) or 0)
            got = sum(1 for e in batch if e["addr"] in cands)
            evaluate_batch(batch, cands, states, tag, args, args.quiet)
            hits = sum(1 for e in batch if states[e["addr"]]["hit"])
            print("  batch %d (%s): %d/%d functions with candidates, %d hit | %.1fs"
                  % (batch_no, tag, got, len(batch), hits, time.time() - t0))
            if not args.quiet:
                for e in batch:
                    st = states[e["addr"]]
                    if st["hit"]:
                        h = st["hit"]
                        print("    %s %dB %-26s MATCH r%d g=%d %s"
                              % (e["addr"], e["size"], e["sig"], h["round"], h["g"],
                                 "(core only)" if e["core"] < e["size"] else ""))
            time.sleep(args.sleep)

    rows = []
    n_match = n_core = n_miss = 0
    for e in entries:
        st = states[e["addr"]]
        hit = st["hit"]
        if hit:
            cand = hit["cand"]
            g = hit["g"]
            core_only = e["core"] < e["size"]
            meta = "round %d, candidate %d" % (hit["round"], hit["ci"] + 1)
            src_rel = write_source(e, cand["code"], meta)
            note = "M2.3 llm: round %d cand %d; %s%s" % (
                hit["round"], hit["ci"] + 1,
                "core %d/%d bytes" % (e["core"], e["size"]) if core_only else
                "%d bytes" % e["size"],
                "" if core_only else "; g=%d" % g)
            if core_only:
                record_padded(e, src_rel, note, g)
            else:
                update_overrides(e, src_rel, note, g)
            append_ledger(e, g, st["attempts"], note)
            C.complete(args.owner, e["addr"], "MATCH", st["attempts"],
                       note=note, source=src_rel)
            result = "MATCH_CORE" if core_only else "MATCH"
            if core_only:
                n_core += 1
            else:
                n_match += 1
            row = {"addr": e["addr"], "name": e["name"], "tier": e["tier"],
                   "size": e["size"], "core": e["core"], "cls": e.get("cls"),
                   "flags": e.get("flags"), "sig": e.get("sig"),
                   "result": result, "rounds": hit["round"],
                   "attempts": st["attempts"], "g": g, "source": src_rel,
                   "note": note}
        else:
            why = st["note"] or ("no byte-exact candidate after %d round(s)" % st["round"])
            C.complete(args.owner, e["addr"], "MISS", st["attempts"], note=why[:400])
            n_miss += 1
            row = {"addr": e["addr"], "name": e["name"], "tier": e["tier"],
                   "size": e["size"], "core": e["core"], "cls": e.get("cls"),
                   "flags": e.get("flags"), "sig": e.get("sig"),
                   "result": "MISS", "rounds": st["round"],
                   "attempts": st["attempts"], "g": None, "source": "",
                   "note": why[:400]}
            save_evidence(e, st)
        rows.append(row)

    summary = summarize(rows, entries, total_calls, usage_total, time.time() - t0)
    doc = {"schema": 1, "project": "IsPurePC-Matching", "phase": "M2.3",
           "generated": time.strftime("%Y-%m-%dT%H:%M:%S%z"),
           "llm": {"base_url": cfg["base_url"], "model": cfg["model"]},
           "arguments": {"tier": args.tier, "limit": args.limit,
                         "batch_size": args.batch_size, "rounds": args.rounds,
                         "sample": args.sample},
           "summary": summary, "functions": rows}
    with open(args.results, "w", newline="\n", encoding="utf-8") as f:
        json.dump(doc, f, indent=1, ensure_ascii=False)
        f.write("\n")
    print("\nM2.3 LLM batch done: %d function(s), %d MATCH + %d MATCH_CORE = %.1f%%, "
          "%d MISS, %.1fs, %d LLM call(s)"
          % (len(rows), n_match, n_core,
             (n_match + n_core) * 100.0 / len(rows) if rows else 0.0,
             n_miss, time.time() - t0, total_calls))
    print("results: %s" % os.path.relpath(args.results, ROOT))
    if not args.no_progress:
        run_progress()
    return 0


if __name__ == "__main__":
    sys.exit(main())
