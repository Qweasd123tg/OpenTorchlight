#!/usr/bin/env python3
"""One command for the decomp track: database, matching, in-process shadow tests.

    python3 tools/decomp/check.py            # all three stages
    python3 tools/decomp/check.py --no-game  # skip the hybrid self-test

The hybrid self-test runs the original executable headless (no display, offscreen
SDL) and exits before the game's main; it never opens a window or touches saves.
Exit status is non-zero when compilation, linking or a self-test fails. DIFF
results are progress, not failures.
"""
from __future__ import annotations

import argparse
from collections import Counter
import json
from pathlib import Path
import re
import subprocess
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import elfimage  # noqa: E402
import objdiff  # noqa: E402

ROOT = elfdb.ROOT
WRITTEN = ("function", "ctor", "dtor", "static")


def ensure_db():
    path = elfdb.DEFAULT_OUT / "elfdb.json"
    stale = not path.exists() or any(p.stat().st_mtime > path.stat().st_mtime
                                     for p in (Path(elfdb.__file__), Path(elfimage.__file__)))
    if stale:
        subprocess.run([sys.executable, str(Path(elfdb.__file__))], check=True)
    db = elfdb.load_db()
    if db["original_elf_sha256"] != elfimage.ORIGINAL_SHA256:
        raise SystemExit("database built from a different ELF")
    if db["link_order_inversions"]:
        raise SystemExit(f"TU partition inconsistent: {db['link_order_inversions']} link-order inversions")
    return db


def shadow_covered(db):
    """Original addresses named by TL_ORIGINAL in the self-tests (what they compare)."""
    names = set()
    for test in (ROOT / "decomp" / "hybrid" / "tests").glob("*.cpp"):
        names.update(re.findall(r'TL_ORIGINAL\([^;]*?"(_Z\w+)"\)', test.read_text(), re.S))
    return {address for address, f in db["functions"].items() if names & set(f["names"])}


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--no-game", action="store_true")
    parser.add_argument("--json", type=Path, default=ROOT / "build-decomp" / "progress.json")
    args = parser.parse_args()

    db = ensure_db()
    game_tus = {t["id"] for t in db["tus"] if t["kind"] == "game"}
    total = [f for f in db["functions"].values() if f["tu"] in game_tus and f["kind"] in WRITTEN]
    total_bytes = sum(f["size"] for f in total)

    sources = sorted((ROOT / "decomp" / "src").rglob("*.cpp"))
    original = objdiff.Original(db=db)
    units = [objdiff.compare_source(s, original) for s in sources]
    status = Counter()
    matched = {}
    for unit in units:
        objdiff.report(unit)
        for row in unit["functions"]:
            if row["status"] == "EXTRA" or row.get("weak"):
                continue
            status[row["status"]] += 1
            if row["status"] == "MATCH":
                matched[row["address"]] = row["original_size"]
    print(f"\nmatching: {len(matched)} of {len(total)} game functions "
          f"({sum(matched.values())} of {total_bytes} bytes); by status {dict(status)}")

    selftest = None
    accepted = dict(matched)
    if not args.no_game:
        selftest = subprocess.run([sys.executable, str(ROOT / "tools" / "decomp" / "hybrid.py"), "selftest"]).returncode
        print(f"hybrid self-test: {'PASS' if selftest == 0 else 'FAIL'}")
        if selftest == 0:
            covered = shadow_covered(db)
            for unit in units:
                for row in unit["functions"]:
                    if row["status"] == "DIFF" and row["address"] in covered:
                        accepted[row["address"]] = row["original_size"]
            shadow = sorted(set(accepted) - set(matched))
            print(f"accepted: {len(accepted)} of {len(total)} game functions "
                  f"({sum(accepted.values())} bytes); {len(shadow)} of them by self-test")

    args.json.parent.mkdir(parents=True, exist_ok=True)
    args.json.write_text(json.dumps({
        "schema": 1, "original_elf_sha256": db["original_elf_sha256"],
        "game_functions": len(total), "game_bytes": total_bytes,
        "matched_functions": len(matched), "matched_bytes": sum(matched.values()),
        "accepted_functions": len(accepted), "accepted_bytes": sum(accepted.values()),
        "status": dict(status), "hybrid_selftest": selftest, "units": units,
    }, indent=1))
    return 1 if selftest not in (None, 0) else 0


if __name__ == "__main__":
    sys.exit(main())
