#!/usr/bin/env python3
"""claims.py - atomic claim/lease ledger for the M2.2 triage queue.

Model (rac4-inspired, local-only variant)
  build/queue.json  immutable ordered work list produced by triage.py
  build/claims.json mutable ledger (one record per function address)

All mutations happen under an exclusive lock file (O_CREAT|O_EXCL), so two
concurrent workers can never be handed the same function.  A claim is a lease:
if a worker dies the lease expires after --lease seconds and another worker may
reclaim that function; the previous claim is kept in "history".

Commands
  claim-next --owner W [--tier easy] [--limit 1] [--stride 1] [--lease 900]
  claim      --owner W --addr 0x00102078 [--lease 900]
  release    --owner W --addr 0x00102078
  complete   --owner W --addr 0x00102078 --result MATCH --attempts 3
             [--source src/functions/00102078.c] [--note TEXT]
  status     [--tier easy] [--limit 20] [--json]
  stats      [--json]
  check
  reset      --yes

Addresses are stored in the canonical queue form "0x%08X".
"""
import argparse
import contextlib
import hashlib
import json
import os
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
QUEUE = os.path.join(ROOT, "build", "queue.json")
CLAIMS = os.path.join(ROOT, "build", "claims.json")
LOCK = os.path.join(ROOT, "build", ".claims.lock")
LEASE_DEFAULT = 900
RESULTS = ("MATCH", "MISS", "UNSUPPORTED", "ERROR")


def canon(addr):
    if isinstance(addr, int):
        return "0x%08X" % addr
    s = str(addr).strip()
    return "0x%08X" % int(s, 16)


def sha1_file(path):
    h = hashlib.sha1()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


@contextlib.contextmanager
def locked(timeout=30.0):
    os.makedirs(os.path.dirname(LOCK), exist_ok=True)
    t0 = time.time()
    fd = None
    while True:
        try:
            fd = os.open(LOCK, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
            os.write(fd, ("%d %s" % (os.getpid(), time.strftime("%H:%M:%S"))).encode())
            break
        except FileExistsError:
            try:
                age = time.time() - os.path.getmtime(LOCK)
            except OSError:
                age = 0.0
            if age > 120:
                try:
                    os.remove(LOCK)
                except OSError:
                    pass
                continue
            if time.time() - t0 > timeout:
                raise SystemExit("claims: lock timeout (stale %s?)" % LOCK)
            time.sleep(0.02)
        except PermissionError:
            time.sleep(0.05)
    try:
        yield
    finally:
        if fd is not None:
            try:
                os.close(fd)
            except OSError:
                pass
        try:
            os.remove(LOCK)
        except OSError:
            pass


def load_queue():
    if not os.path.exists(QUEUE):
        raise SystemExit("claims: %s missing - run tools/triage.py first" % QUEUE)
    with open(QUEUE, encoding="utf-8") as f:
        return json.load(f)


def queue_index(doc):
    return {canon(e["addr"]): e for e in doc["entries"]}


def _new_doc(qdoc):
    return {
        "schema": 1,
        "queue_sha1": sha1_file(QUEUE),
        "created": time.strftime("%Y-%m-%dT%H:%M:%S%z"),
        "next_seq": 1,
        "claims": {},
        "history": [],
    }


def load_claims(qdoc=None):
    if not os.path.exists(CLAIMS):
        if qdoc is None:
            qdoc = load_queue()
        return _new_doc(qdoc)
    with open(CLAIMS, encoding="utf-8") as f:
        doc = json.load(f)
    doc.setdefault("claims", {})
    doc.setdefault("history", [])
    doc.setdefault("next_seq", 1)
    return doc


def save_claims(doc):
    tmp = CLAIMS + ".tmp"
    with open(tmp, "w", newline="\n", encoding="utf-8") as f:
        json.dump(doc, f, indent=1, ensure_ascii=False)
        f.write("\n")
    os.replace(tmp, CLAIMS)


def _active(rec, now):
    return rec.get("status") == "claimed" and rec.get("lease_until", 0) > now


def eligible(qdoc, cdoc, tier=None, max_core=None):
    """Queue entries that are free (never claimed, or lease expired)."""
    now = time.time()
    out = []
    for e in qdoc["entries"]:
        if tier and e.get("tier") != tier:
            continue
        if max_core and e.get("core", e.get("size", 0)) > int(max_core):
            continue
        rec = cdoc["claims"].get(canon(e["addr"]))
        if rec and rec.get("status") == "done":
            continue
        if rec and _active(rec, now):
            continue
        out.append(e)
    return out


def claim_entry(cdoc, entry, owner, lease, note=None):
    now = time.time()
    key = canon(entry["addr"])
    old = cdoc["claims"].get(key)
    rec = {
        "seq": cdoc["next_seq"],
        "addr": key,
        "tier": entry.get("tier"),
        "owner": owner,
        "status": "claimed",
        "claimed_at": now,
        "claimed_time": time.strftime("%H:%M:%S"),
        "lease_until": now + lease,
        "attempts": 0,
        "result": None,
        "note": note or "",
        "source": "",
    }
    cdoc["next_seq"] += 1
    if old:
        hist = dict(old)
        hist["replaced_by"] = rec["seq"]
        cdoc["history"].append(hist)
        rec["retries"] = old.get("retries", 0) + 1
    cdoc["claims"][key] = rec
    return rec


def claim_next(owner, tier=None, limit=1, stride=1, lease=LEASE_DEFAULT,
               max_core=None):
    with locked():
        qdoc = load_queue()
        cdoc = load_claims(qdoc)
        free = eligible(qdoc, cdoc, tier=tier, max_core=max_core)
        picks = free[::max(1, int(stride))][:max(0, int(limit))]
        recs = [claim_entry(cdoc, e, owner, lease) for e in picks]
        if recs:
            save_claims(cdoc)
        return recs, len(free)


def claim_one(owner, addr, lease=LEASE_DEFAULT):
    key = canon(addr)
    with locked():
        qdoc = load_queue()
        idx = queue_index(qdoc)
        if key not in idx:
            raise SystemExit("claims: %s not in queue" % key)
        cdoc = load_claims(qdoc)
        rec = cdoc["claims"].get(key)
        if rec and _active(rec, time.time()) and rec.get("owner") != owner:
            raise SystemExit("claims: %s already leased to %s until %s" % (
                key, rec.get("owner"), time.strftime("%H:%M:%S", time.localtime(rec["lease_until"]))))
        out = claim_entry(cdoc, idx[key], owner, lease)
        save_claims(cdoc)
        return out


def release(owner, addr):
    key = canon(addr)
    with locked():
        qdoc = load_queue()
        cdoc = load_claims(qdoc)
        rec = cdoc["claims"].get(key)
        if not rec:
            raise SystemExit("claims: %s is not claimed" % key)
        if rec.get("owner") != owner:
            raise SystemExit("claims: %s owned by %s, not %s" % (key, rec.get("owner"), owner))
        if rec.get("status") == "done":
            raise SystemExit("claims: %s already completed (%s)" % (key, rec.get("result")))
        rec["status"] = "released"
        rec["released_at"] = time.strftime("%H:%M:%S")
        cdoc["history"].append(rec)
        del cdoc["claims"][key]
        save_claims(cdoc)
        return rec


def complete(owner, addr, result, attempts, note="", source="", force=False):
    key = canon(addr)
    result = result.upper()
    if result not in RESULTS:
        raise SystemExit("claims: result must be one of %s" % (RESULTS,))
    with locked():
        qdoc = load_queue()
        cdoc = load_claims(qdoc)
        rec = cdoc["claims"].get(key)
        if not rec:
            raise SystemExit("claims: %s is not claimed" % key)
        if rec.get("owner") != owner and not force:
            raise SystemExit("claims: %s owned by %s, not %s" % (key, rec.get("owner"), owner))
        rec.update(status="done", result=result, attempts=int(attempts),
                   note=note, source=source,
                   completed_at=time.time(),
                   completed_time=time.strftime("%H:%M:%S"),
                   lease_until=0)
        save_claims(cdoc)
        return rec


def summarize(qdoc, cdoc):
    rows = list(cdoc["claims"].values())
    done = [r for r in rows if r.get("status") == "done"]
    active = [r for r in rows if _active(r, time.time())]
    by_result = {}
    for r in done:
        by_result[r.get("result")] = by_result.get(r.get("result"), 0) + 1
    attempted = [r for r in done if r.get("attempts", 0) > 0]
    avg = (sum(r["attempts"] for r in attempted) / len(attempted)) if attempted else 0.0
    return {
        "queue_total": len(qdoc["entries"]),
        "claimed_total": len(rows),
        "done": len(done),
        "active": len(active),
        "by_result": by_result,
        "avg_attempts": round(avg, 2),
        "attempts_sum": sum(r["attempts"] for r in attempted),
        "matched": by_result.get("MATCH", 0),
        "match_rate": round(by_result.get("MATCH", 0) / len(done), 4) if done else 0.0,
        "done_addrs": [r["addr"] for r in done],
    }


def cmd_status(args):
    qdoc = load_queue()
    cdoc = load_claims(qdoc)
    idx = queue_index(qdoc)
    s = summarize(qdoc, cdoc)
    if args.json:
        print(json.dumps(s, indent=1))
        return 0
    print("queue: %d functions   claimed: %d   done: %d   active leases: %d" % (
        s["queue_total"], s["claimed_total"], s["done"], s["active"]))
    print("results:", s["by_result"], " avg attempts: %.2f" % s["avg_attempts"])
    rows = sorted(cdoc["claims"].values(), key=lambda r: r["seq"])
    if args.tier:
        rows = [r for r in rows if idx.get(r["addr"], {}).get("tier") == args.tier]
    show = rows[-args.limit:] if args.limit else rows
    for r in show:
        e = idx.get(r["addr"], {})
        print("  %4d %s %-8s %-6s %-8s attempts=%-2d %s %s" % (
            r["seq"], r["addr"], e.get("tier", "?"), r.get("status"),
            r.get("result") or "-", r.get("attempts", 0),
            os.path.basename(r.get("source") or ""), r.get("note", "")))
    return 0


def cmd_claim_next(args):
    recs, free = claim_next(args.owner, tier=args.tier, limit=args.limit,
                            stride=args.stride, lease=args.lease,
                            max_core=args.max_core)
    if args.json:
        print(json.dumps({"claimed": recs, "free_before": free}, indent=1))
    else:
        for r in recs:
            print("claimed %s by %s (seq %d, %d free)" % (r["addr"], r["owner"], r["seq"], free))
        if not recs:
            print("no free entries (tier=%s, %d free)" % (args.tier, free))
    return 0 if recs else 3


def cmd_claim(args):
    r = claim_one(args.owner, args.addr, lease=args.lease)
    print(json.dumps(r, indent=1))
    return 0


def cmd_complete(args):
    r = complete(args.owner, args.addr, args.result, args.attempts,
                 note=args.note, source=args.source, force=args.force)
    print("completed %s %s attempts=%d" % (r["addr"], r["result"], r["attempts"]))
    return 0


def cmd_check(args):
    qdoc = load_queue()
    cdoc = load_claims(qdoc)
    idx = queue_index(qdoc)
    problems = []
    if cdoc.get("queue_sha1") and cdoc["queue_sha1"] != sha1_file(QUEUE):
        problems.append("queue.json changed since the ledger was created "
                        "(queue_sha1 mismatch)")
    seen = {}
    for key, rec in cdoc["claims"].items():
        if key not in idx:
            problems.append("%s claimed but not in queue" % key)
        if rec.get("status") == "done" and rec.get("result") not in RESULTS:
            problems.append("%s bad result %r" % (key, rec.get("result")))
        if rec.get("status") == "claimed" and rec.get("lease_until", 0) < time.time():
            problems.append("%s lease expired at %s" % (
                key, time.strftime("%H:%M:%S", time.localtime(rec.get("lease_until", 0)))))
        if seen.get(key):
            problems.append("%s duplicated" % key)
        seen[key] = True
    if problems:
        for p in problems:
            print("PROBLEM:", p)
        return 1
    print("claims: OK (%d records, %d done)" % (
        len(cdoc["claims"]), sum(1 for r in cdoc["claims"].values() if r.get("status") == "done")))
    return 0


def cmd_reset(args):
    if not args.yes:
        raise SystemExit("claims: reset needs --yes")
    with locked():
        if os.path.exists(CLAIMS):
            os.remove(CLAIMS)
    print("claims: ledger removed (build/queue.json untouched)")
    return 0


def build_parser():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)

    p = sub.add_parser("claim-next")
    p.add_argument("--owner", required=True)
    p.add_argument("--tier", default=None)
    p.add_argument("--limit", type=int, default=1)
    p.add_argument("--stride", type=int, default=1)
    p.add_argument("--lease", type=int, default=LEASE_DEFAULT)
    p.add_argument("--max-core", type=int, default=None)
    p.add_argument("--json", action="store_true")
    p.set_defaults(func=cmd_claim_next)

    p = sub.add_parser("claim")
    p.add_argument("--owner", required=True)
    p.add_argument("--addr", required=True)
    p.add_argument("--lease", type=int, default=LEASE_DEFAULT)
    p.set_defaults(func=cmd_claim)

    p = sub.add_parser("release")
    p.add_argument("--owner", required=True)
    p.add_argument("--addr", required=True)
    p.set_defaults(func=lambda a: (release(a.owner, a.addr), 0)[1])

    p = sub.add_parser("complete")
    p.add_argument("--owner", required=True)
    p.add_argument("--addr", required=True)
    p.add_argument("--result", required=True)
    p.add_argument("--attempts", type=int, required=True)
    p.add_argument("--note", default="")
    p.add_argument("--source", default="")
    p.add_argument("--force", action="store_true")
    p.set_defaults(func=cmd_complete)

    p = sub.add_parser("status")
    p.add_argument("--tier", default=None)
    p.add_argument("--limit", type=int, default=20)
    p.add_argument("--json", action="store_true")
    p.set_defaults(func=cmd_status)

    p = sub.add_parser("stats")
    p.add_argument("--json", action="store_true")
    p.set_defaults(func=lambda a: (print(json.dumps(summarize(load_queue(), load_claims()), indent=1)), 0)[1])

    p = sub.add_parser("check")
    p.set_defaults(func=cmd_check)

    p = sub.add_parser("reset")
    p.add_argument("--yes", action="store_true")
    p.set_defaults(func=cmd_reset)
    return ap


def main(argv=None):
    args = build_parser().parse_args(argv)
    return args.func(args) or 0


if __name__ == "__main__":
    sys.exit(main())
