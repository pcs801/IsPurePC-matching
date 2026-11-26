import json, sys
sys.path.insert(0, "tools")
import build as B
import match_kit as MK

spec = json.load(open(sys.argv[1], encoding="utf-8"))
addr = int(spec["addr"], 16); size = spec["size"]; g = spec.get("g", 8)
items = [{"key": c["key"], "src": c["src"], "g": g} for c in spec["cands"]]
objs = MK.compile_batch(items, spec.get("tag", "try"), verbose=False)
data = open("baserom/SLPM_665.70", "rb").read()
off = B.TEXT_OFF + (addr - B.TEXT_ADDR)
orig = data[off:off + size]
out = []
for c in spec["cands"]:
    o = objs.get(c["key"])
    if not o:
        out.append((9999, c["key"], "compile fail", 0)); continue
    text, stats = B.resolve_object_text(o)
    diffs, nd = B.word_diff(text, orig)
    out.append((nd, c["key"], "len %d/%d" % (len(text), len(orig)), len(diffs)))
for nd, k, s, d in sorted(out):
    print("%-6s ndiff=%-4d %s" % (k, nd, s))
