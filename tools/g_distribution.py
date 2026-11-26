#!/usr/bin/env python
"""-G distribution survey.

Static scan: classify every function by how it reaches globals.
  - gp-relative access  => the TU had small-data enabled (-G8 and up)
  - lui+lw/sw absolute  => the global was NOT in small data (-G0, or symbol too big)
  - neither             => G-agnostic

Outputs build/g-distribution.json plus a console summary.
"""
import json, os, collections

OLD = r"E:/ONE PIECE/S/IsPurePC"
ROOT = r"E:/ONE PIECE/S/IsPurePC-matching"
idx_path = OLD + "/reports/all_functions/_index.tsv"
dis_path = OLD + "/artifacts/data/analysis/disasm_text.txt"

LOADS = {0x20: "lb", 0x21: "lh", 0x23: "lw", 0x24: "lbu", 0x25: "lhu",
         0x27: "lwu", 0x31: "lwc1", 0x37: "ld", 0x3D: "ldc1"}
STORES = {0x28: "sb", 0x29: "sh", 0x2B: "sw", 0x38: "swc1", 0x39: "swc1",
          0x3F: "sd", 0x3E: "sdc1"}
GP = 28

# index
funcs = []
with open(idx_path, encoding="utf-8", errors="replace") as f:
    for line in f:
        p = line.rstrip("\n").split("\t")
        if len(p) < 3: continue
        try:
            funcs.append((int(p[0], 16), int(p[1]), p[2]))
        except ValueError:
            continue
funcs.sort()

# disasm
words = {}
with open(dis_path, encoding="utf-8", errors="replace") as f:
    for line in f:
        p = line.split()
        if len(p) < 2: continue
        try:
            a = int(p[0], 16)
            w = int.from_bytes(bytes.fromhex(p[1]), "little")
        except ValueError:
            continue
        words[a] = (w, line.rstrip("\n"))

def analyze(a, size):
    end = a + size
    x = a
    gp_load = gp_store = 0
    lui_regs = {}
    lui_global = 0
    fpu = 0
    unknown = 0
    gp_offsets = []
    calls = 0
    first_lui = {}
    while x < end:
        if x not in words:
            return None
        w, t = words[x]
        op = w >> 26
        rs = (w >> 21) & 0x1F
        rt = (w >> 16) & 0x1F
        imm = w & 0xFFFF
        if ".byte" in t:
            unknown += 1
        if op == 0x11:
            fpu += 1
        if op in LOADS or op in STORES:
            if rs == GP:
                if op in LOADS:
                    gp_load += 1
                else:
                    gp_store += 1
                if imm & 0x8000:
                    gp_offsets.append(imm - 0x10000)
                else:
                    gp_offsets.append(imm)
            else:
                if rs in lui_regs:
                    lui_global += 1
                    del lui_regs[rs]
        elif op == 0x0F:  # lui
            lui_regs[rt] = x
            first_lui[rt] = imm
        elif op == 3 or (op == 0 and (w & 0x3F) == 9):
            calls += 1
        elif op == 9 or op == 0x0D:  # addiu / ori
            if rs == GP:
                gp_offsets.append(imm - 0x10000 if imm & 0x8000 else imm)
            else:
                if rs in lui_regs:
                    lui_global += 1
                    del lui_regs[rs]
        x += 4
    return dict(gp_load=gp_load, gp_store=gp_store, gp_total=gp_load + gp_store,
                gp_offsets=gp_offsets, lui_global=lui_global, fpu=fpu,
                unknown=unknown, calls=calls)

rows = []
for a, size, name in funcs:
    r = analyze(a, size)
    if r is None:
        rows.append(dict(addr=a, size=size, name=name, status="gap"))
        continue
    if r["gp_total"] > 0:
        cls = "needs_G8"
    elif r["lui_global"] > 0:
        cls = "ambiguous"
    else:
        cls = "local"
    cand = size < 64 and r["calls"] == 0 and r["fpu"] == 0 and r["unknown"] == 0
    rows.append(dict(addr=a, size=size, name=name, status="ok", cls=cls,
                     leaf=(r["calls"] == 0), candidate=cand,
                     **{k: v for k, v in r.items() if k != "gp_offsets"},
                     gp_offsets=r["gp_offsets"][:6]))

# summary
cnt = collections.Counter(r["cls"] for r in rows if r.get("status") == "ok")
leaf_rows = [r for r in rows if r.get("status") == "ok" and r.get("leaf")]
cand_rows = [r for r in rows if r.get("status") == "ok" and r.get("candidate")]
cand_cnt = collections.Counter(r["cls"] for r in cand_rows)
leaf_cnt = collections.Counter(r["cls"] for r in leaf_rows)
all_offs = [o for r in rows if r.get("status") == "ok" for o in r["gp_offsets"]]

os.makedirs(ROOT + "/build", exist_ok=True)
json.dump(dict(total=len(funcs), ok=sum(1 for r in rows if r.get("status") == "ok"),
               gap=sum(1 for r in rows if r.get("status") == "gap"),
               classes=dict(cnt), leaf_total=len(leaf_rows), leaf_classes=dict(leaf_cnt),
               candidate_total=len(cand_rows), candidate_classes=dict(cand_cnt),
               gp_offset_min=min(all_offs) if all_offs else None,
               gp_offset_max=max(all_offs) if all_offs else None,
               rows=rows), open(ROOT + "/build/g-distribution.json", "w"), indent=1)

print("total funcs:", len(funcs))
print("parsed ok:", sum(1 for r in rows if r.get("status") == "ok"),
      " gap:", sum(1 for r in rows if r.get("status") == "gap"))
print("ALL   :", dict(cnt))
print("LEAF  :", len(leaf_rows), dict(leaf_cnt))
print("CAND  :", len(cand_rows), dict(cand_cnt))
print("gp offsets: min=%s max=%s" % (min(all_offs) if all_offs else None, max(all_offs) if all_offs else None))
print()
with open(ROOT + "/build/g-distribution.csv", "w", encoding="utf-8") as f:
    f.write("addr,size,name,class,leaf,candidate,gp_load,gp_store,lui_global,fpu,calls\n")
    for r in rows:
        if r.get("status") != "ok":
            continue
        f.write("0x%08X,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d\n" % (
            r["addr"], r["size"], r["name"], r["cls"], 1 if r["leaf"] else 0, 1 if r.get("candidate") else 0,
            r.get("gp_load", 0), r.get("gp_store", 0), r.get("lui_global", 0),
            r.get("fpu", 0), r.get("calls", 0)))
print("addr windows with gp-access (16KB buckets):")
bucket = collections.defaultdict(lambda: collections.Counter())
for r in rows:
    if r.get("status") != "ok": continue
    b = r["addr"] >> 14
    bucket[b][r["cls"]] += 1
for b in sorted(bucket):
    c = bucket[b]
    print("  0x%06X-0x%06X  needs_G8=%3d ambiguous=%3d local=%3d" % (
        b << 14, (b << 14) + 0x3FFF, c["needs_G8"], c["ambiguous"], c["local"]))
