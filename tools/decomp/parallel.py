#!/usr/bin/env python3
"""Parallel decomp work: one git worktree and branch per worker.

    python3 tools/decomp/parallel.py queue [--limit 30]  # next TUs, dependency-ready first
    python3 tools/decomp/parallel.py claim w7 [--budget 25000]  # worktree with the next batch
    python3 tools/decomp/parallel.py new ai AIFlagManager.cpp AISkillManager.cpp
    python3 tools/decomp/parallel.py list
    python3 tools/decomp/parallel.py own dot Character.cpp player.cpp   # decomp/owners.json
    python3 tools/decomp/parallel.py merge ai      # merge decomp/ai into the current branch
    python3 tools/decomp/parallel.py drop ai       # remove the worktree and branch

Worktrees live under /tmp/opencode/decomp-wt/<slug> (no spaces, so tools and
LD_PRELOAD work directly). Each gets a copy of build-decomp/db and its own
hybrid runtime directory; the GCC toolchain cache is shared read-only.
decomp/owners.json (tracked) splits TUs between workers on different machines:
the queue skips TUs owned by anyone but $OTL_OWNER.
"""
from __future__ import annotations

import argparse
from contextlib import contextmanager
import fcntl
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402

ROOT = elfdb.ROOT
BASE = Path(os.environ.get("OTL_DECOMP_WORKTREES", "/tmp/opencode/decomp-wt"))


CLAIMS = ROOT / "build-decomp" / "claims.json"
OWNERS = ROOT / "decomp" / "owners.json"
WRITTEN = ("function", "ctor", "dtor", "static")
# Reserved for generators or special handling instead of the worker queue.
RESERVED_SUFFIX = ("binreloc.c",)


def owners():
    """TU -> owner from the tracked decomp/owners.json."""
    return json.loads(OWNERS.read_text())["tus"] if OWNERS.exists() else {}


def owned_by_others(tu, me=None):
    """Owner of `tu` when it is someone else than `me` (default $OTL_OWNER), else None."""
    me = me if me is not None else os.environ.get("OTL_OWNER", "")
    owner = owners().get(tu)
    return owner if owner and owner != me else None


def own(owner, tus):
    data = json.loads(OWNERS.read_text())
    taken = {tu: data["tus"][tu] for tu in tus if data["tus"].get(tu) not in (None, owner)}
    if taken:
        raise SystemExit("owned by others: " + ", ".join(f"{tu} ({o})" for tu, o in taken.items()))
    data["owners"].setdefault(owner, "")
    data["tus"].update({tu: owner for tu in tus})
    data["tus"] = dict(sorted(data["tus"].items(), key=lambda x: x[0].lower()))
    OWNERS.write_text(json.dumps(data, indent=1, ensure_ascii=False) + "\n")
    print(f"{owner} owns {len(tus)} more TUs; commit decomp/owners.json so the others see it")


def claims():
    return json.loads(CLAIMS.read_text()) if CLAIMS.exists() else {}


def save_claims(data):
    CLAIMS.parent.mkdir(parents=True, exist_ok=True)
    fd, temporary = tempfile.mkstemp(prefix="claims-", dir=CLAIMS.parent)
    try:
        with os.fdopen(fd, "w") as stream:
            json.dump(data, stream, indent=1)
        os.replace(temporary, CLAIMS)
    finally:
        Path(temporary).unlink(missing_ok=True)


@contextmanager
def claims_lock():
    CLAIMS.parent.mkdir(parents=True, exist_ok=True)
    with CLAIMS.with_suffix(".lock").open("a+") as stream:
        fcntl.flock(stream, fcntl.LOCK_EX)
        try:
            yield
        finally:
            fcntl.flock(stream, fcntl.LOCK_UN)


def candidates(db):
    """Open game TUs: (missing base headers, bytes, name, functions), readiest and smallest first."""
    claimed = {tu for tus in claims().values() for tu in tus}
    claimed |= {tu for tu in owners() if owned_by_others(tu)}
    headers = {p.stem for p in (ROOT / "decomp" / "include").glob("*.h")}
    by_tu = {}
    for f in db["functions"].values():
        if f["kind"] in WRITTEN:
            by_tu.setdefault(f["tu"], []).append(f)
    rows = []
    original = None
    for t in db["tus"]:
        name = t["name"]
        funcs = by_tu.get(t["id"], [])
        if (t["kind"] != "game" or not funcs or name in claimed
                or name.endswith(RESERVED_SUFFIX)):
            continue
        source = ROOT / "decomp" / "src" / name
        if source.exists():
            import objdiff
            original = original or objdiff.Original(db=db)
            try:
                unit = objdiff.compare_source(source, original, quiet=True)
                done = {r["address"] for r in unit["functions"] if r.get("address") and r["status"] == "MATCH"}
                funcs = [f for f in funcs if f["address"] not in done]
            except SystemExit:
                print(f"queue: {name} does not compile; retained for repair", file=sys.stderr)
            if not funcs:
                continue
        size = sum(f["size"] for f in funcs)
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
    with claims_lock():
        return _claim(slug, budget)


def _claim(slug, budget):
    if not re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9_-]*", slug):
        raise SystemExit("worker slug must contain only letters, digits, underscores and hyphens")
    if slug in claims():
        raise SystemExit(f"{slug} already has a claim")
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
    try:
        new(slug, batch)
    except BaseException:
        data = claims()
        data.pop(slug, None)
        save_claims(data)
        raise
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
    # All drafts, not only the batch's: regenerated headers take return types from them.
    src_build = ROOT / "build-decomp"
    for name in ("types.json", "include-gen", "drafts", "examples.json"):
        if (src_build / name).is_dir():
            shutil.copytree(src_build / name, path / "build-decomp" / name, copy_function=shutil.copy)
        elif (src_build / name).exists():
            shutil.copy(src_build / name, path / "build-decomp" / name)
    for tu in tus:
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
    with claims_lock():
        data = claims()
        if data.pop(slug, None) is not None:
            save_claims(data)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    p = sub.add_parser("new")
    p.add_argument("slug")
    p.add_argument("tus", nargs="+")
    o = sub.add_parser("own", help="record TUs in decomp/owners.json")
    o.add_argument("owner")
    o.add_argument("tus", nargs="+")
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
    elif args.command == "own":
        own(args.owner, args.tus)
    elif args.command == "list":
        listing()
    elif args.command == "merge":
        merge(args.slug)
    else:
        drop(args.slug)


if __name__ == "__main__":
    main()
