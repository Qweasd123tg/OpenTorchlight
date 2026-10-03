#!/usr/bin/env python3
"""Parallel decomp work: one git worktree and branch per worker.

    python3 tools/decomp/parallel.py queue [--limit 30]  # next TUs, dependency-ready first
    python3 tools/decomp/parallel.py claim w7 [--budget 25000]  # worktree with the next batch
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
import re
import shutil
import subprocess
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402

ROOT = elfdb.ROOT
BASE = Path(os.environ.get("OTL_DECOMP_WORKTREES", "/tmp/opencode/decomp-wt"))


CLAIMS = ROOT / "build-decomp" / "claims.json"
WRITTEN = ("function", "ctor", "dtor", "static")
# Reserved for generators or special handling instead of the worker queue.
RESERVED_SUFFIX = ("Descriptor.cpp", "binreloc.c")
LARGE_TU = 60000


def claims():
    return json.loads(CLAIMS.read_text()) if CLAIMS.exists() else {}


def save_claims(data):
    CLAIMS.parent.mkdir(parents=True, exist_ok=True)
    CLAIMS.write_text(json.dumps(data, indent=1))


def candidates(db):
    """Open game TUs: (missing base headers, bytes, name, functions), readiest and smallest first."""
    claimed = {tu for tus in claims().values() for tu in tus}
    headers = {p.stem for p in (ROOT / "decomp" / "include").glob("*.h")}
    by_tu = {}
    for f in db["functions"].values():
        if f["kind"] in WRITTEN:
            by_tu.setdefault(f["tu"], []).append(f)
    rows = []
    for t in db["tus"]:
        name = t["name"]
        funcs = by_tu.get(t["id"], [])
        if (t["kind"] != "game" or not funcs or (ROOT / "decomp" / "src" / name).exists() or name in claimed
                or name.endswith(RESERVED_SUFFIX)):
            continue
        size = sum(f["size"] for f in funcs)
        if size > LARGE_TU:
            continue
        missing = set()
        for cls in {f["scope"] for f in funcs if f.get("scope")}:
            for b in db["classes"].get(cls, {}).get("bases", []):
                base = b["class"]
                if "::" not in base and base.lstrip("C") not in headers and base[1:] not in headers:
                    missing.add(base)
        rows.append((len(missing), size, name, len(funcs)))
    return sorted(rows)


def queue(limit):
    db = elfdb.load_db()
    for missing, size, name, count in candidates(db)[:limit]:
        print(f"{name:40} {count:4} functions {size:7} bytes  missing base headers: {missing}")


def claim(slug, budget):
    db = elfdb.load_db()
    rows = candidates(db)
    if not rows:
        raise SystemExit("queue is empty")
    seed = rows[0]
    stem = re.sub(r"(Descriptor|Manager|Menu|menu)?\.cpp$", "", seed[2]).lower()
    batch, total = [seed[2]], seed[1]
    # Same-family TUs first (shared headers), then the next ready ones.
    family = [r for r in rows[1:] if r[2].lower().startswith(stem[:6])]
    for r in family + [r for r in rows[1:] if r not in family]:
        if total + r[1] > budget or len(batch) >= 10:
            continue
        batch.append(r[2])
        total += r[1]
    data = claims()
    data[slug] = batch
    save_claims(data)
    new(slug, batch)
    print(f"claimed {len(batch)} TUs, {total} bytes: {' '.join(batch)}")


def git(*args, cwd=ROOT, check=True):
    return subprocess.run(["git", *args], cwd=cwd, check=check, capture_output=True, text=True)


def new(slug, tus):
    path = BASE / slug
    if path.exists():
        raise SystemExit(f"{path} exists")
    BASE.mkdir(parents=True, exist_ok=True)
    git("worktree", "add", "-b", f"decomp/{slug}", str(path), "HEAD")
    # Copy after checkout with fresh mtimes, database first, so neither the
    # database nor the instruction cache looks stale against the checkout.
    db_dir = path / "build-decomp" / "db"
    shutil.copytree(ROOT / "build-decomp" / "db", db_dir, copy_function=shutil.copy)
    for name in ("elfdb.json", "insns.pickle"):
        if (db_dir / name).exists():
            os.utime(db_dir / name)
    # Shared generated inputs: recovered types, generated headers, Ghidra drafts and trial builds.
    src_build = ROOT / "build-decomp"
    for name in ("types.json", "include-gen"):
        if (src_build / name).is_dir():
            shutil.copytree(src_build / name, path / "build-decomp" / name, copy_function=shutil.copy)
        elif (src_build / name).exists():
            shutil.copy(src_build / name, path / "build-decomp" / name)
    for tu in tus:
        if (src_build / "drafts" / tu).exists():
            shutil.copytree(src_build / "drafts" / tu, path / "build-decomp" / "drafts" / tu)
        if (src_build / "trial" / tu).exists():
            (path / "build-decomp" / "trial").mkdir(parents=True, exist_ok=True)
            shutil.copy(src_build / "trial" / tu, path / "build-decomp" / "trial" / tu)
    if (src_build / "trial" / "summary.json").exists():
        (path / "build-decomp" / "trial").mkdir(parents=True, exist_ok=True)
        shutil.copy(src_build / "trial" / "summary.json", path / "build-decomp" / "trial" / "summary.json")
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
    git("worktree", "remove", "--force", str(BASE / slug), check=False)
    git("worktree", "prune")
    git("branch", "-D", f"decomp/{slug}", check=False)
    data = claims()
    if data.pop(slug, None) is not None:
        save_claims(data)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    p = sub.add_parser("new")
    p.add_argument("slug")
    p.add_argument("tus", nargs="+")
    sub.add_parser("list")
    for name in ("merge", "drop"):
        sub.add_parser(name).add_argument("slug")
    q = sub.add_parser("queue")
    q.add_argument("--limit", type=int, default=30)
    c = sub.add_parser("claim")
    c.add_argument("slug")
    c.add_argument("--budget", type=int, default=25000)
    args = parser.parse_args()
    if args.command == "queue":
        queue(args.limit)
    elif args.command == "claim":
        claim(args.slug, args.budget)
    elif args.command == "new":
        new(args.slug, args.tus)
    elif args.command == "list":
        listing()
    elif args.command == "merge":
        merge(args.slug)
    else:
        drop(args.slug)


if __name__ == "__main__":
    main()
