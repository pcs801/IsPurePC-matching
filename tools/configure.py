#!/usr/bin/env python
"""Generate build configuration: per-TU -G from the survey, plus toolchain paths.

Reads  build/g-distribution.csv  (addr,size,name,class,...)
Writes config/build_config.json  (toolchain + per-function G recommendation)
       config/tu_g.json          (address ranges -> -G, aggregated)
"""
import collections
import csv
import json
import os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CSV_PATH = os.path.join(ROOT, "build", "g-distribution.csv")
OUT_CFG = os.path.join(ROOT, "config", "build_config.json")
OUT_TU = os.path.join(ROOT, "config", "tu_g.json")

# tools are invoked inside WSL
CC = "/opt/ee/bin/ee-gcc"
AS = "/opt/ee/ee/bin/ee-as"
LD = "/usr/local/bin/ee-ld"
GP = 0x002779F0
BASE_FLAGS = ["-O2", "-mips3"]

GAP_LIMIT = 0x2000  # merge needs_G8 functions into one TU range if closer than this


def load_rows():
    rows = []
    with open(CSV_PATH, encoding="utf-8") as f:
        for r in csv.DictReader(f):
            rows.append(dict(
                addr=int(r["addr"], 16),
                size=int(r["size"]),
                name=r["name"],
                cls=r["class"],
                leaf=int(r["leaf"]),
                candidate=int(r["candidate"]),
            ))
    rows.sort(key=lambda x: x["addr"])
    return rows


def aggregate_ranges(rows):
    """Merge consecutive needs_G8 functions into TU-like ranges."""
    g8 = [r for r in rows if r["cls"] == "needs_G8"]
    ranges = []
    for r in g8:
        if ranges and r["addr"] - ranges[-1]["end"] <= GAP_LIMIT:
            ranges[-1]["end"] = r["addr"] + r["size"]
            ranges[-1]["count"] += 1
        else:
            ranges.append(dict(start=r["addr"], end=r["addr"] + r["size"], count=1))
    return ranges


def main():
    rows = load_rows()
    ranges = aggregate_ranges(rows)

    # per-function recommendation for the C matching loop
    g_map = []
    for r in rows:
        if r["cls"] == "needs_G8":
            rec = "8"
        elif r["cls"] == "local":
            rec = "either"
        else:
            rec = "try-both"
        g_map.append(dict(addr="0x%08X" % r["addr"], name=r["name"], cls=r["cls"], g=rec))

    cfg = dict(
        project="IsPurePC-Matching",
        root=ROOT,
        paths=dict(
            baserom="baserom/SLPM_665.70",
            splat_yaml="splat.yaml",
            asm="asm/1000.s",
            object="build/splat/1000.o",
            resolved="build/splat/1000.resolved.bin",
            image="build/splat/SLPM_665.70.rebuilt",
            symbols="config/symbol_addrs.txt",
        ),
        toolchain=dict(cc=CC, as_=AS, ld=LD, gp=GP, base_flags=BASE_FLAGS),
        wsl=dict(
            distro="Ubuntu",
            work_dir="/root/work/build",
            mount_root="/mnt/e/ONE PIECE/S/IsPurePC-matching",
        ),
        g_policy=dict(
            default="0",
            needs_g8_functions=sum(1 for r in rows if r["cls"] == "needs_G8"),
            ambiguous=sum(1 for r in rows if r["cls"] == "ambiguous"),
            local=sum(1 for r in rows if r["cls"] == "local"),
        ),
        g_map=g_map,
    )
    with open(OUT_CFG, "w", encoding="utf-8") as f:
        json.dump(cfg, f, indent=1)

    tu = dict(
        note="needs_G8 address ranges (gap<=0x%X merged); everything else -G0" % GAP_LIMIT,
        default_g=0,
        ranges=[dict(start="0x%08X" % r["start"], end="0x%08X" % r["end"],
                     count=r["count"], g=8) for r in ranges],
    )
    with open(OUT_TU, "w", encoding="utf-8") as f:
        json.dump(tu, f, indent=1)

    print("functions:", len(rows))
    print("classes:", collections.Counter(r["cls"] for r in rows))
    print("needs_G8 ranges:", len(ranges), "covering",
          sum(r["end"] - r["start"] for r in ranges), "bytes")
    print("largest ranges:")
    for r in sorted(ranges, key=lambda x: x["end"] - x["start"], reverse=True)[:5]:
        print("  0x%06X-0x%06X  %5d bytes  %d funcs" % (
            r["start"], r["end"], r["end"] - r["start"], r["count"]))
    print("wrote", os.path.relpath(OUT_CFG, ROOT), "and", os.path.relpath(OUT_TU, ROOT))


if __name__ == "__main__":
    main()
