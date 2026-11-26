#!/usr/bin/env python3
"""Export struct/class layouts from the legacy IsPurePC headers into config/types.json.

The worker's evidence card needs field names, types and offset hints; the legacy
project already reverse-engineered them (91 headers under include/ispure).
"""
import json, os, re, sys

SRC = "E:/ONE PIECE/S/IsPurePC/include/ispure"
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

RE_STRUCT = re.compile(r'^\s*(?:struct|class)\s+(\w+)\s*(?::[^{]*)?\{')
RE_FIELD = re.compile(
    r'^\s*([A-Za-z_][\w:<>,\*&\s]*?[\w>\*&])\s+([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*(?:\{.*\})?\s*(?:=[^;]*)?;\s*(?://\s*(.*))?$'
)
RE_OFF = re.compile(r'\+?0x([0-9A-Fa-f]+)')

def main():
    if not os.path.isdir(SRC):
        print("missing", SRC, file=sys.stderr)
        return 1
    types = {}
    for fn in sorted(os.listdir(SRC)):
        if not fn.endswith(".hpp"):
            continue
        path = os.path.join(SRC, fn)
        cur = None
        depth = 0
        with open(path, encoding="utf-8", errors="ignore") as f:
            for line in f:
                if cur is None:
                    m = RE_STRUCT.match(line)
                    if m:
                        cur = m.group(1)
                        depth = line.count("{") - line.count("}")
                        if cur not in types:
                            types[cur] = {"file": fn, "fields": []}
                        if depth <= 0:
                            cur = None
                    continue
                depth += line.count("{") - line.count("}")
                if depth <= 0:
                    cur = None
                    continue
                m = RE_FIELD.match(line)
                if m and m.group(2) not in ("return",):
                    comment = (m.group(4) or "").strip()
                    off = RE_OFF.search(comment)
                    types[cur]["fields"].append({
                        "type": re.sub(r"\s+", " ", m.group(1)).strip(),
                        "name": m.group(2),
                        "array": m.group(3),
                        "offset_hint": ("0x" + off.group(1)) if off else None,
                        "comment": comment[:160],
                    })
    types = {k: v for k, v in types.items() if v["fields"]}
    dest = os.path.join(ROOT, "config", "types.json")
    with open(dest, "w", encoding="utf-8") as f:
        json.dump({"source": SRC, "structs": types}, f, indent=1, ensure_ascii=False)
    print("structs:", len(types), "fields:", sum(len(v["fields"]) for v in types.values()))
    for k in list(types)[:8]:
        print("  %-28s %3d fields  (%s)" % (k, len(types[k]["fields"]), types[k]["file"]))

if __name__ == "__main__":
    sys.exit(main())
