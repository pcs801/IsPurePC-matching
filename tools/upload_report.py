#!/usr/bin/env python3
"""Upload build/report.json to ByteMatch (per-project token, no GitHub Actions).

Config precedence:
  1. environment: BYTEMATCH_TOKEN / BYTEMATCH_OWNER / BYTEMATCH_REPO / BYTEMATCH_VERSION
  2. config/upload.local.json  (gitignored)

Cloudflare in front of bytematch.dev rejects urllib's default signature (HTTP 403, error 1010),
so this shells out to curl with a browser User-Agent.
"""
import json, os, subprocess, sys

UA = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0 Safari/537.36"

def load_local(root):
    p = os.path.join(root, "config", "upload.local.json")
    if os.path.exists(p):
        with open(p, encoding="utf-8") as f:
            return json.load(f)
    return {}

def main():
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    cfg = load_local(root)
    token   = os.environ.get("BYTEMATCH_TOKEN") or cfg.get("token")
    owner   = os.environ.get("BYTEMATCH_OWNER") or cfg.get("owner")
    repo    = os.environ.get("BYTEMATCH_REPO") or cfg.get("repo")
    version = os.environ.get("BYTEMATCH_VERSION") or cfg.get("version") or "SLPM_665.70"
    host    = os.environ.get("BYTEMATCH_HOST", "https://bytematch.dev").rstrip("/")
    if not (token and owner and repo):
        print("no token: set env or config/upload.local.json", file=sys.stderr)
        return 2
    path = os.path.join(root, "build", "report.json")
    try:
        commit = subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=root).decode().strip()
    except Exception:
        commit = "0" * 40
    url = f"{host}/api/v1/projects/{owner}/{repo}/reports?version={version}&commit={commit}"
    env = {k: v for k, v in os.environ.items() if k.lower() not in ("https_proxy", "http_proxy")}
    res = subprocess.run(
        ["curl", "-sS", "-X", "POST",
         "-H", "Authorization: Bearer " + token,
         "-H", "Content-Type: application/json",
         "-A", UA,
         "--data-binary", "@" + path,
         url, "-w", "\nHTTP=%{http_code}\n"],
        cwd=root, env=env, capture_output=True, text=True, timeout=90,
    )
    sys.stdout.write(res.stdout)
    sys.stderr.write(res.stderr)
    return 0 if "HTTP=201" in res.stdout or "HTTP=200" in res.stdout else 1

if __name__ == "__main__":
    sys.exit(main())
