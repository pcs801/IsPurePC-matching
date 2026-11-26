import sys, struct
sys.path.insert(0, r"E:/ONE PIECE/S/IsPurePC-matching/tools")
import build as B
from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS64, CS_MODE_LITTLE_ENDIAN

addr = int(sys.argv[1], 16)
size = int(sys.argv[2])
core = int(sys.argv[3]) if len(sys.argv) > 3 else size
G = 8
obj = r"E:/ONE PIECE/S/IsPurePC-matching/build/candidates/check_%x/one.G%d.o" % (addr, G)
text, stats = B.resolve_object_text(obj)
base = open(B.BASEROM, "rb").read()
off = B.TEXT_OFF + (addr - B.TEXT_ADDR)
orig = base[off:off+size][:core]
md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS64 + CS_MODE_LITTLE_ENDIAN)
def dis(bs):
    return [(i.address, i.mnemonic, i.op_str) for i in md.disasm(bs, addr)]
a = dis(orig); b = dis(text)
print("orig insns %d, compiled insns %d, compiled bytes %d/%d" % (len(a), len(b), len(text), core))
if stats["unresolved"]: print("UNRESOLVED:", stats["unresolved"][:5])
n = max(len(a), len(b))
only = sys.argv[4] if len(sys.argv) > 4 else None
for i in range(n):
    x = a[i] if i < len(a) else None
    y = b[i] if i < len(b) else None
    if x and y and (x[1], x[2]) == (y[1], y[2]):
        continue
    if only == "first":
        print("first diff idx %d: want %s %s | got %s %s" % (i, x[1] if x else "-", x[2] if x else "", y[1] if y else "-", y[2] if y else ""))
        break
    print("--- idx %d" % i)
    print("  want %s %s" % (x[1], x[2]) if x else "  want -")
    print("  got  %s %s" % (y[1], y[2]) if y else "  got -")
