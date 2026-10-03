#!/usr/bin/env python3
"""Parallel decomp work: one git worktree and branch per worker.

    python3 tools/decomp/parallel.py new ai AIFlagManager.cpp AISkillManager.cpp
    python3 tools/decomp/parallel.py list
    python3 tools/decomp/parallel.py merge ai      # merge decomp/ai into the current branch
    python3 tools/decomp/parallel.py drop ai       # remove the worktree and branch

Worktrees live under /tmp/opencode/decomp-wt/<slug> (no spaces, so tools and
LD_PRELOAD work directly). Each gets a copy of build-decomp/db and its own
hybrid runtime directory; the GCC toolchain cache is shared read-only.
"""
from __future__ import annotations

import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402

ROOT = elfdb.ROOT
BASE = Path(os.environ.get("OTL_DECOMP_WORKTREES", "/tmp/opencode/decomp-wt"))


def git(*args, cwd=ROOT, check=True):
    return subprocess.run(["git", *args], cwd=cwd, check=check, capture_output=True, text=True)


def new(slug, tus):
    path = BASE / slug
    if path.exists():
        raise SystemExit(f"{path} exists")
    BASE.mkdir(parents=True, exist_ok=True)
    git("worktree", "add", "-b", f"decomp/{slug}", str(path), "HEAD")
    # Copy after checkout so the database is newer than the tool sources.
    shutil.copytree(ROOT / "build-decomp" / "db", path / "build-decomp" / "db")
    (path / "build-decomp" / "WORKER.json").write_text(json.dumps({"slug": slug, "tus": tus}, indent=1))
    for tu in tus:
        subprocess.run([sys.executable, str(path / "tools" / "decomp" / "scaffold.py"), tu], cwd=path, check=True,
                       capture_output=True)
    print(path)


def listing():
    for line in git("worktree", "list", "--porcelain").stdout.split("\n\n"):
        fields = dict(l.split(" ", 1) for l in line.splitlines() if " " in l)
        wt = fields.get("worktree", "")
        if not wt.startswith(str(BASE)):
            continue
        branch = fields.get("branch", "").replace("refs/heads/", "")
        ahead = git("rev-list", "--count", f"HEAD..{branch}").stdout.strip()
        dirty = git("status", "--short", cwd=wt).stdout.count("\n")
        meta = Path(wt) / "build-decomp" / "WORKER.json"
        tus = json.loads(meta.read_text())["tus"] if meta.exists() else []
        print(f"{branch:28} commits ahead {ahead:>3}  uncommitted {dirty:>3}  {' '.join(tus)}")


def merge(slug):
    branch = f"decomp/{slug}"
    result = git("merge", "--no-ff", "--no-edit", branch, check=False)
    print(result.stdout + result.stderr)
    if result.returncode:
        raise SystemExit(f"merge of {branch} stopped on conflicts; resolve, then commit")


def drop(slug):
    git("worktree", "remove", "--force", str(BASE / slug))
    git("branch", "-D", f"decomp/{slug}", check=False)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    p = sub.add_parser("new")
    p.add_argument("slug")
    p.add_argument("tus", nargs="+")
    sub.add_parser("list")
    for name in ("merge", "drop"):
        sub.add_parser(name).add_argument("slug")
    args = parser.parse_args()
    if args.command == "new":
        new(args.slug, args.tus)
    elif args.command == "list":
        listing()
    elif args.command == "merge":
        merge(args.slug)
    else:
        drop(args.slug)


if __name__ == "__main__":
    main()
