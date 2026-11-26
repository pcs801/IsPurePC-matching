import sys, json, os
sys.path.insert(0, r"E:/ONE PIECE/S/IsPurePC-matching/tools")
import build as B, llm_match as LM, match_kit as MK
from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS64, CS_MODE_LITTLE_ENDIAN

addr = int(sys.argv[1], 16)
entry = {"addr_i": addr, "size": int(sys.argv[2]), "core": int(sys.argv[3])}
variants = json.load(open(sys.argv[4], encoding="utf-8"))
items = [{"key": "v%d" % i, "src": v["src"], "g": 8} for i, v in enumerate(variants)]
objs = MK.compile_batch(items, "try_%x" % addr, verbose=False)
md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS64 + CS_MODE_LITTLE_ENDIAN)
orig = LM.original_bytes(addr, entry["size"])[:entry["core"]]
def dis(bs):
    return [(i.mnemonic, i.op_str) for i in md.disasm(bs, addr)]
oa = dis(orig)
for i, v in enumerate(variants):
    r = LM.verify(objs.get("v%d" % i), entry)
    print("== %s: %s" % (v["name"], "MATCH" if r["ok"] else r["summary"]))
    if r["ok"]:
        print("   SRC:", v["src"])
        continue
    got = dis(r["compiled"]) if r.get("compiled") else []
    if sys.argv[5:] and sys.argv[5] == "all":
        for k in range(max(len(oa), len(got))):
            x = oa[k] if k < len(oa) else None
            y = got[k] if k < len(got) else None
            same = "  " if (x and y and x == y) else "**"
            print("%s %3d want %-8s %-20s got %-8s %s" % (same, k, x[0] if x else "-", x[1] if x else "", y[0] if y else "-", y[1] if y else ""))
        continue
    if sys.argv[5:] and sys.argv[5] == "full":
        n = max(len(oa), len(got))
        shown = 0
        for k in range(n):
            x = oa[k] if k < len(oa) else None
            y = got[k] if k < len(got) else None
            if x and y and x == y: continue
            print("   idx %d want %-10s %-22s got %-10s %s" % (k, x[0] if x else "-", x[1] if x else "", y[0] if y else "-", y[1] if y else ""))
            shown += 1
            if shown > 40: break
