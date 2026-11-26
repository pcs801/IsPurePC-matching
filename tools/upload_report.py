#!/usr/bin/env python3
"""Upload build/report.json to ByteMatch (per-project token, no GitHub Actions)."""
import json, os, subprocess, sys, urllib.request

def main():
    token   = os.environ.get("BYTEMATCH_TOKEN")
    owner   = os.environ.get("BYTEMATCH_OWNER")
    repo    = os.environ.get("BYTEMATCH_REPO")
    version = os.environ.get("BYTEMATCH_VERSION", "SLPM_665.70")
    host    = os.environ.get("BYTEMATCH_HOST", "https://bytematch.dev").rstrip("/")
    if not (token and owner and repo):
        print("set BYTEMATCH_TOKEN / BYTEMATCH_OWNER / BYTEMATCH_REPO", file=sys.stderr)
        return 2
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    path = os.path.join(root, "build", "report.json")
    body = open(path, "rb").read()
    try:
        commit = subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=root).decode().strip()
    except Exception:
        commit = "0" * 40
    url = f"{host}/api/v1/projects/{owner}/{repo}/reports?version={version}&commit={commit}"
    req = urllib.request.Request(url, data=body, method="POST")
    req.add_header("Authorization", "Bearer " + token)
    req.add_header("Content-Type", "application/json")
    try:
        with urllib.request.urlopen(req, timeout=60) as r:
            print(r.status, r.read().decode()[:500])
    except urllib.error.HTTPError as e:
        print("HTTP", e.code, e.read().decode()[:800], file=sys.stderr)
        return 1
    return 0

if __name__ == "__main__":
    sys.exit(main())
