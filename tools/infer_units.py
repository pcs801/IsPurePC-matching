#!/usr/bin/env python3
"""Infer probable translation units from the call graph and link order.

Inputs:  config/symbols.csv              address,size,name
         (legacy) functions.json          start,end,callees  (optional)
Output:  config/tu_inferred.json         groups with name/start/end/functions/confidence

Method: label propagation over call edges (weight 1) + address-adjacency edges
(weight 0.3, gap <= 0x20). Small clusters are merged into the nearest address
cluster. Confidence is "low": this is an inference, not decoded metadata.
"""
import csv, json, os, sys
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LEGACY = "E:/ONE PIECE/S/IsPurePC/artifacts/data/analysis/functions.json"

def load_symbols():
    rows = []
    with open(os.path.join(ROOT, "config", "symbols.csv"), newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f):
            rows.append({"addr": int(r["address"], 16), "size": int(r["size"]), "name": r["name"]})
    rows.sort(key=lambda x: x["addr"])
    return rows

def load_calls(syms):
    by = {s["addr"]: s for s in syms}
    edges = defaultdict(set)
    path = LEGACY
    if os.path.exists(path):
        with open(path, encoding="utf-8") as f:
            data = json.load(f)
        for fn in data:
            a = int(fn["start"])
            for c in fn.get("callees", []):
                if a in by and c in by:
                    edges[a].add(c)
                    edges[c].add(a)
    return edges

def lpa(nodes, adj, rounds=30):
    labels = {n: n for n in nodes}
    for _ in range(rounds):
        changed = 0
        for n in nodes:
            cnt = Counter(labels[m] for m in adj.get(n, ()))
            if not cnt:
                continue
            best = max(cnt.items(), key=lambda kv: (kv[1], -kv[0]))[0]
            if labels[n] != best:
                labels[n] = best
                changed += 1
        if changed == 0:
            break
    return labels

def main():
    syms = load_symbols()
    if not syms:
        print("no symbols", file=sys.stderr)
        return 1
    nodes = [s["addr"] for s in syms]
    calls = load_calls(syms)

    # only keep call edges inside a plausible TU span: long-distance calls are
    # inter-module and would otherwise collapse the graph into one blob.
    MAX_DIST = 0x4000
    adj = defaultdict(set)
    for a, bs in calls.items():
        for b in bs:
            if abs(a - b) <= MAX_DIST:
                adj[a].add(b)
                adj[b].add(a)

    labels = lpa(nodes, adj)

    # functions with no call edge: attach to the nearest labelled function by address
    import bisect
    labelled = sorted((n, labels[n]) for n in nodes if adj.get(n))
    if labelled:
        keys = [n for n, _ in labelled]
        for n in nodes:
            if adj.get(n):
                continue
            i = bisect.bisect_left(keys, n)
            if i == 0:
                labels[n] = labelled[0][1]
            elif i >= len(keys):
                labels[n] = labelled[-1][1]
            else:
                before, after = labelled[i - 1], labelled[i]
                labels[n] = before[1] if (n - before[0]) <= (after[0] - n) else after[1]
    groups = defaultdict(list)
    for s in syms:
        groups[labels[s["addr"]]].append(s)

    # merge tiny groups into the nearest address group
    big = {k: v for k, v in groups.items() if len(v) >= 3}
    small = [s for k, v in groups.items() if len(v) < 3 for s in v]
    if big and small:
        starts = sorted((min(x["addr"] for x in v), k) for k, v in big.items())
        for s in small:
            import bisect
            keys = [st for st, _ in starts]
            i = bisect.bisect_right(keys, s["addr"]) - 1
            k = starts[max(0, i)][1]
            big[k].append(s)

    out = []
    for k, v in big.items():
        v.sort(key=lambda x: x["addr"])
        out.append({
            "name": "tu/%08x" % v[0]["addr"],
            "start": v[0]["addr"],
            "end": max(x["addr"] + x["size"] for x in v),
            "functions": len(v),
            "addrs": [x["addr"] for x in v],
            "confidence": "low",
        })
    out.sort(key=lambda u: u["start"])
    dest = os.path.join(ROOT, "config", "tu_inferred.json")
    with open(dest, "w", encoding="utf-8") as f:
        json.dump({"note": "inferred by tools/infer_units.py; not decoded metadata", "groups": out}, f, indent=1)
    print("groups:", len(out), "functions:", sum(u["functions"] for u in out))
    big5 = sorted(out, key=lambda u: -u["functions"])[:5]
    for u in big5:
        print("  %-16s %5d funcs %08x-%08x" % (u["name"], u["functions"], u["start"], u["end"]))

if __name__ == "__main__":
    sys.exit(main())
