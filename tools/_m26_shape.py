import sys, re, difflib
sys.path.insert(0, "tools")
import build as B
from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32, CS_MODE_LITTLE_ENDIAN

def dis(bs, addr):
    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32 + CS_MODE_LITTLE_ENDIAN)
    md.skipdata = True
    return [("%s %s" % (i.mnemonic, i.op_str)).strip() for i in md.disasm(bs, addr)]

def norm(s):
    s = re.sub(r"\$(s[0-8]|s8|t[0-9]|a[0-3]|v[0-9]|k[01]|at)", "$R", s)
    s = s.replace("$fp", "$R").replace("$ra", "$R")
    return s

addr = int(sys.argv[1], 16); size = int(sys.argv[2]); obj = sys.argv[3]
data = open("baserom/SLPM_665.70", "rb").read()
off = B.TEXT_OFF + (addr - B.TEXT_ADDR)
orig = data[off:off + size]
text, stats = B.resolve_object_text(obj)
a = [norm(x) for x in dis(orig, addr)]
b = [norm(x) for x in dis(text, addr)]
sm = difflib.SequenceMatcher(None, a, b)
print("shape diff (normalised):")
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == "equal":
        continue
    print("  @%d %s" % (i1, tag))
    for x in a[i1:i2]:
        print("    O  " + x)
    for y in b[j1:j2]:
        print("    C  " + y)
print("orig=%d compiled=%d words" % (len(a), len(b)))
