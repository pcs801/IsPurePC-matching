ROOT = r"E:/ONE PIECE/S/IsPurePC-matching"
base = open(ROOT + "/baserom/SLPM_665.70", "rb").read()
orig = base[0x1000:0x1000 + 1124764]
linked = open(ROOT + "/build/splat/1000.linked.text.bin", "rb").read()
print("linked size:", len(linked), "orig size:", len(orig))
diffs = [i for i in range(min(len(linked), len(orig))) if linked[i] != orig[i]]
print("diff bytes:", len(diffs), "diff words:", len({(i//4)*4 for i in diffs}))
if diffs:
    print("first:", [(hex(i), hex(linked[i]), hex(orig[i])) for i in diffs[:10]])
    words = sorted({(i//4)*4 for i in diffs})
    for w in words[:6]:
        print("  off 0x%06X linked=%08x orig=%08x" % (
            w, int.from_bytes(linked[w:w+4],'little'), int.from_bytes(orig[w:w+4],'little')))
