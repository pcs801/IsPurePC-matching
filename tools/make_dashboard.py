#!/usr/bin/env python3
"""Generate a self-contained progress dashboard from build/report.json."""
import json, os, html
from datetime import datetime

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

def fmt_bytes(n):
    for u in ("B", "KB", "MB"):
        if n < 1024 or u == "MB":
            return f"{n:.1f} {u}" if u != "B" else f"{n} B"
        n /= 1024

def main():
    with open(os.path.join(ROOT, "build", "report.json"), encoding="utf-8") as f:
        rep = json.load(f)
    m = rep["measures"]
    units = rep.get("units", [])
    funcs = []
    for u in units:
        for fn in u.get("functions", []):
            funcs.append((u["name"], fn))
    matched = [x for x in funcs if x[1].get("match_percent", 0) >= 100.0]
    pct = m["matched_code_percent"]
    rows = "".join(
        f'<tr class="{"ok" if fn.get("match_percent",0)>=100 else ""}">'
        f'<td>{html.escape(fn["name"])}</td><td>{fn["size"]}</td>'
        f'<td>{fn.get("match_percent",0):.0f}%</td></tr>'
        for _, fn in funcs[:400]
    )
    grid = "".join(
        f'<div class="cell" title="{html.escape(u["name"])}">'
        f'<div class="cell-bar"><i style="width:{u["measures"]["matched_code_percent"]:.3f}%"></i></div>'
        f'<span>{u["measures"]["matched_code_percent"]:.2f}%</span></div>'
        for u in units
    )
    doc = f"""<!doctype html>
<html lang="zh"><meta charset="utf-8"><title>IsPurePC-Matching 进度</title>
<style>
body{{margin:0;background:#0b0f17;color:#e6edf3;font:14px/1.6 -apple-system,Segoe UI,sans-serif}}
.wrap{{max-width:1040px;margin:0 auto;padding:32px 24px}}
h1{{font-size:22px;margin:0 0 4px}} .sub{{color:#8b949e;margin-bottom:24px}}
.big{{font-size:44px;font-weight:700;color:#3fb950}}
.bar{{height:10px;background:#161b22;border-radius:5px;overflow:hidden;margin:12px 0}}
.bar i{{display:block;height:100%;background:#3fb950;width:{pct:.4f}%}}
.stats{{display:flex;gap:28px;flex-wrap:wrap;margin:18px 0 28px}}
.stat b{{display:block;font-size:20px}} .stat span{{color:#8b949e;font-size:12px}}
.grid{{display:grid;grid-template-columns:repeat(auto-fill,minmax(150px,1fr));gap:10px;margin:12px 0 28px}}
.cell{{background:#161b22;border:1px solid #21262d;border-radius:8px;padding:10px}}
.cell-bar{{height:6px;background:#0d1117;border-radius:3px;overflow:hidden;margin-bottom:6px}}
.cell-bar i{{display:block;height:100%;background:#3fb950}}
table{{width:100%;border-collapse:collapse;font-size:12px}}
th,td{{text-align:left;padding:5px 8px;border-bottom:1px solid #21262d}}
tr.ok{{color:#3fb950}} th{{color:#8b949e;font-weight:500}}
</style>
<div class="wrap">
<h1>IsPurePC-Matching</h1>
<div class="sub">PS2《I's Pure》SLPM-66570 · 字节级 matching decompilation · 更新于 {datetime.now():%Y-%m-%d %H:%M}</div>
<div class="big">{pct:.3f}%</div>
<div class="bar"><i></i></div>
<div class="stats">
<div class="stat"><b>{m['matched_code']:,} / {m['total_code']:,}</b><span>已匹配字节</span></div>
<div class="stat"><b>{m['matched_functions']} / {m['total_functions']}</b><span>已匹配函数</span></div>
<div class="stat"><b>{m['complete_units']} / {m['total_units']}</b><span>完成单元</span></div>
</div>
<h3>单元</h3>
<div class="grid">{grid}</div>
<h3>函数（前 400 个）</h3>
<table><tr><th>名称</th><th>大小</th><th>匹配</th></tr>{rows}</table>
</div></html>"""
    dest = os.path.join(ROOT, "docs", "progress.html")
    with open(dest, "w", encoding="utf-8") as f:
        f.write(doc)
    print("wrote", dest)

if __name__ == "__main__":
    main()
