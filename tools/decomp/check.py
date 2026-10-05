#!/usr/bin/env python3
"""One command for the decomp track: database, matching, in-process shadow tests.

    python3 tools/decomp/check.py            # all three stages
    python3 tools/decomp/check.py --no-game  # skip the hybrid self-test

Functions recorded in decomp/autotests.json (tools/decomp/mutate.py --accept)
get generated differential tests in the same run.

The hybrid self-test runs the original executable headless (no display, offscreen
SDL) and exits before the game's main; it never opens a window or touches saves.
Exit status is non-zero when compilation, linking or a self-test fails. DIFF
results are progress, not failures.
"""
from __future__ import annotations

import argparse
from collections import Counter
import json
import os
from pathlib import Path
import re
import subprocess
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import elfimage  # noqa: E402
import autotest  # noqa: E402
import hybrid  # noqa: E402
import mutate  # noqa: E402
import objdiff  # noqa: E402
import toolchain  # noqa: E402

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


def generated_tests(db, diff):
    """Generates the autotests of DIFF functions recorded by mutate.py --accept whose
    compiled code has not changed since; returns their addresses."""
    wanted = []
    for address, entry in mutate.load_accepted().items():
        f = db["functions"].get(address)
        if address not in diff or not f:
            continue
        if diff[address].get("code") != entry.get("code"):
            print(f"stale mutation check: {address} {entry['name']} compiles differently now; "
                  f"run tools/decomp/mutate.py --accept {address}")
            continue
        wanted.append(f)
    made, skipped = autotest.Generator().write(wanted)
    for address, why in skipped.items():
        print(f"generated test lost: {address}: {why}")
    return [f["address"] for f in made]


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--no-game", action="store_true")
    parser.add_argument("--json", type=Path, default=ROOT / "build-decomp" / "progress.json")
    args = parser.parse_args()

    db = ensure_db()
    game_tus = {t["id"] for t in db["tus"] if t["kind"] == "game"}
    total = [f for f in db["functions"].values() if f["tu"] in game_tus and f["kind"] in WRITTEN]
    total_bytes = sum(f["size"] for f in total)
    counted = {f["address"] for f in total}

    sources = sorted((ROOT / "decomp" / "src").rglob("*.cpp"))
    original = objdiff.Original(db=db)
    units = toolchain.parallel_map(lambda s: objdiff.compare_source(s, original), sources)
    objdiff.save_norm_cache(original)
    status = Counter()
    matched = {}
    generated_by_compiler = {}
    for unit in units:
        objdiff.report(unit)
        for row in unit["functions"]:
            if row["status"] == "EXTRA" or row.get("weak"):
                continue
            status[row["status"]] += 1
            if row["status"] == "MATCH" and row.get("address") in counted:
                matched[row["address"]] = row["original_size"]
            elif row["status"] == "MATCH":
                generated_by_compiler[row["address"]] = row["original_size"]
    print(f"\nmatching: {len(matched)} of {len(total)} game functions "
          f"({sum(matched.values())} of {total_bytes} bytes); by status {dict(status)}")
    print(f"also matching: {len(generated_by_compiler)} compiler-generated static initializers and "
          f"destructors ({sum(generated_by_compiler.values())} bytes, outside the totals)")
    unknown = [(unit["source"], ref) for unit in units for ref in unit.get("unknown", [])]
    for source, ref in unknown:
        print(f"unknown reference in {source}: {ref['name']}; the original has: "
              f"{'; '.join(ref['known']) or 'no such member'}")
    if unknown:
        print("FAIL: fix the declarations above (constness, references, parameter types) before the self-test")
        return 1

    selftest = None
    accepted = dict(matched)
    if not args.no_game:
        diff = {row["address"]: row for unit in units for row in unit["functions"]
                if row["status"] == "DIFF" and row.get("address") in counted}
        generated = generated_tests(db, diff)
        os.environ["OTL_AUTOTEST"] = "1"
        os.environ["OTL_SELFTEST_TIMEOUT"] = str(120 + 12 * len(generated))
        blob, loader = hybrid.build()
        selftest, report = hybrid.selftest(blob, loader)
        print("\n".join(report))
        print(f"hybrid self-test: {'PASS' if selftest == 0 else 'FAIL'}")
        if selftest == 0:
            covered = shadow_covered(db)
            auto = set()
            for line in report:
                m = re.match(r"\s+stats auto_(\w+) same (\d+) both-failed \d+ different (\d+)", line)
                if m and int(m.group(3)) == 0 and int(m.group(2)) >= autotest.MIN_COMPLETED:
                    auto.add(f"0x{m.group(1)}")
            for address, row in diff.items():
                if address in covered or address in auto:
                    accepted[address] = row["original_size"]
            by_hand = sum(1 for a in accepted if a not in matched and a in covered)
            print(f"accepted: {len(accepted)} of {len(total)} game functions "
                  f"({sum(accepted.values())} bytes); {by_hand} by self-test, "
                  f"{sum(1 for a in accepted if a not in matched and a not in covered)} by generated tests")

    args.json.parent.mkdir(parents=True, exist_ok=True)
    args.json.write_text(json.dumps({
        "schema": 1, "original_elf_sha256": db["original_elf_sha256"],
        "game_functions": len(total), "game_bytes": total_bytes,
        "matched_functions": len(matched), "matched_bytes": sum(matched.values()),
        "matched_static_init": len(generated_by_compiler),
        "matched_static_init_bytes": sum(generated_by_compiler.values()),
        "accepted_functions": len(accepted), "accepted_bytes": sum(accepted.values()),
        "accepted": sorted(accepted),
        "status": dict(status), "hybrid_selftest": selftest, "units": units,
    }, indent=1))
    return 1 if selftest not in (None, 0) else 0


if __name__ == "__main__":
    sys.exit(main())
