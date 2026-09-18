#!/usr/bin/env python3
"""One-command packet for batch reverse engineering of a repeated method family.

It combines:
  * the repository family/stage matrix,
  * exact/near normalized ASM clusters from the pinned original ELF,
  * full original ASM for one representative of each exact-shape cluster,
  * the existing function_package evidence for those representatives,
  * a ready-to-send agent prompt.

No statuses are changed and no game code is generated.  The packet is meant to
turn "analyse 23 close handlers" into "analyse 13 structural representatives,
then review explicit member deltas".
"""
from __future__ import annotations

import argparse
import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def run(cmd: list[str]) -> None:
    subprocess.run(cmd, check=True)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("method")
    ap.add_argument("--elf", type=Path, required=True)
    ap.add_argument("--out", type=Path, required=True)
    ap.add_argument("--class-regex", default="^C")
    ap.add_argument("--near", type=float, default=0.90)
    args = ap.parse_args()
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    family_md = out / "FAMILY.md"
    clusters_md = out / "ASM_CLUSTERS.md"
    clusters_json = out / "clusters.json"
    run([sys.executable, str(ROOT / "tools/family_package.py"), args.method,
         "--class-regex", args.class_regex, "--out", str(family_md)])
    run([sys.executable, str(ROOT / "tools/asm_family_cluster.py"), args.method,
         "--elf", str(args.elf), "--class-regex", args.class_regex,
         "--near", str(args.near), "--out", str(clusters_md), "--json", str(clusters_json)])
    data = json.loads(clusters_json.read_text(encoding="utf-8"))
    reps = []
    repdir = out / "representatives"
    repdir.mkdir(exist_ok=True)
    for cluster in data["clusters"]:
        rep = cluster["members"][0]
        reps.append(rep)
        addr = rep["address"]
        package = repdir / (addr + "-package.md")
        run([sys.executable, str(ROOT / "tools/function_package.py"), "--address", addr,
             "--out", str(package)])
        # Full ASM slice from the pinned ELF. Address/size are resolved from nm table by objdump
        # through a tiny local lookup to avoid relying on research/batch working files.
        symbols = (ROOT / "research/original-symbols.txt").read_text(encoding="utf-8", errors="replace")
        start = int(addr, 16)
        size = 0
        for line in symbols.splitlines():
            parts = line.split(maxsplit=3)
            if len(parts) == 4 and int(parts[0], 16) == start:
                try: size = max(size, int(parts[1], 16))
                except ValueError: pass
        if size:
            asm = subprocess.run(["objdump", "-d", "--start-address=" + str(start),
                                  "--stop-address=" + str(start + size), str(args.elf)],
                                 check=True, capture_output=True, text=True).stdout
            (repdir / (addr + ".asm")).write_text(asm, encoding="utf-8")
    prompt = out / "PROMPT.txt"
    prompt.write_text(
        "You are porting one original Torchlight method family. Work from the supplied original ASM and existing repository evidence; do not invent missing behavior.\n\n"
        f"TARGET FAMILY: {args.method}\n"
        f"MEMBERS: {data['members']}\n"
        f"EXACT NORMALIZED SHAPE CLUSTERS: {len(data['clusters'])}\n\n"
        "Workflow:\n"
        "1. Read FAMILY.md and ASM_CLUSTERS.md.\n"
        "2. Analyse each representative in representatives/ completely (early exits, field writes, constants, callees, side effects, errors).\n"
        "3. For every other member in its cluster, verify the delta: constants, field offsets, call targets, callers and resources. Exact normalized shape is NOT proof of semantic equivalence.\n"
        "4. Build one shared implementation only for genuinely common semantics; encode proven member deltas as profile/data. Split exceptions.\n"
        "5. Reuse existing port implementations/evidence before writing code.\n"
        "6. Wire a real caller/scenario before marking the family ported/wired.\n"
        "7. Update function-transfer stages only for what was actually established.\n"
        "8. Report unresolved indirect calls or missing decompilation instead of guessing.\n",
        encoding="utf-8")
    summary = {
        "method": args.method,
        "members": data["members"],
        "exact_clusters": len(data["clusters"]),
        "representatives": reps,
        "representative_reduction": data["members"] - len(data["clusters"]),
    }
    (out / "summary.json").write_text(json.dumps(summary, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(f"packet {out}: {data['members']} members -> {len(data['clusters'])} structural representatives")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
