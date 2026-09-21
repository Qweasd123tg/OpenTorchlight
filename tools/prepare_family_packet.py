#!/usr/bin/env python3
"""Prepare a bounded UI family: one shared evidence index, ASM once per member.

ENTRY.md is the small entry point; full function evidence and concrete member
deltas stay in separate files. No model, game execution, status promotion or
semantic-equivalence claim. Generated packets belong in ignored build or /tmp.
"""
from __future__ import annotations

import argparse
from difflib import unified_diff
import hashlib
import json
from pathlib import Path
import subprocess
import sys

from asm_family_cluster import instructions
from automation_state import validate_output, write_json
from function_package import FunctionPackageBuilder, render_markdown
from transfer_contract import completion

ROOT = Path(__file__).resolve().parents[1]


def build_evidence(root: Path, addresses: list[str], callsites: Path | None = None) -> tuple:
    """One builder per batch, not one Python process/index scan per function."""
    builder = FunctionPackageBuilder(root, callsites_path=callsites)
    return builder, builder.document(addresses)


def member_delta(representative: str, member: str, representative_asm: str, member_asm: str) -> str:
    # Strip instruction addresses, not operand constants, offsets or callees.
    # This is a review aid; CFG/virtual targets/context still require review.
    delta = "\n".join(unified_diff(instructions(representative_asm), instructions(member_asm),
                                   fromfile=representative, tofile=member, lineterm=""))
    return (delta or "No instruction-text differences; still review callers, fields and dependencies.") + "\n"


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("method")
    ap.add_argument("--elf", type=Path, required=True)
    ap.add_argument("--out", type=Path, required=True)
    ap.add_argument("--scope", choices=("ui", "all"), default="ui")
    ap.add_argument("--class-regex", default="^C")
    ap.add_argument("--near", type=float, default=None)
    ap.add_argument("--max-members", type=int, default=64)
    ap.add_argument("--max-representatives", type=int, default=64)
    ap.add_argument("--callsites", type=Path)
    args = ap.parse_args()
    if not 1 <= args.max_members <= 64 or not 1 <= args.max_representatives <= 64:
        ap.error("member/representative budgets must be in 1..64")
    out = args.out.resolve()
    protected = [args.elf, *([args.callsites] if args.callsites else [])]
    try:
        validate_output(ROOT, out, protected, directory=True)
        if out.exists() and (not out.is_dir() or any(out.iterdir())):
            raise ValueError("packet output must be a new or empty directory; do not mix stale artifacts")
        if args.callsites and not args.callsites.is_file():
            raise ValueError(f"missing explicitly requested callsite index: {args.callsites}")
        out.mkdir(parents=True, exist_ok=True)
        command = [sys.executable, str(ROOT / "tools/asm_family_cluster.py"), args.method,
                   "--elf", str(args.elf), "--scope", args.scope, "--class-regex", args.class_regex,
                   "--max-members", str(args.max_members), "--out", str(out / "ASM_CLUSTERS.md"),
                   "--json", str(out / "clusters.json"), "--assembly-dir", str(out / "members")]
        if args.near is not None:
            command += ["--near", str(args.near)]
        subprocess.run(command, check=True)
        data = json.loads((out / "clusters.json").read_text(encoding="utf-8"))
        representatives = [cluster["members"][0] for cluster in data["clusters"]]
        if len(representatives) > args.max_representatives:
            raise ValueError(f"{len(representatives)} representatives exceed budget {args.max_representatives}; "
                             "narrow --class-regex; no full evidence packet was produced")
        builder, document = build_evidence(ROOT, [r["address"] for r in representatives], args.callsites)
        write_json(out / "functions.json", document)
        repdir, deltas = out / "representatives", out / "member-deltas"
        repdir.mkdir()
        deltas.mkdir()
        for packet in document["functions"]:
            one = {**document, "functions": [packet]}
            (repdir / (packet["address"] + ".md")).write_text(render_markdown(one), encoding="utf-8")
        matrix = [f"# Family {args.method}", "",
                  "A/P/W/C are legacy bounded stages, NOT whole-function acceptance.", "",
                  "All members' existing boundaries, callers and unresolved targets: members.json.", "",
                  "| Member | Function | A/P/W/C | Acceptance | Representative / concrete delta |",
                  "|---|---|---|---|---|"]
        hashes: dict = {}
        member_contexts = []
        for cluster in data["clusters"]:
            representative = cluster["members"][0]["address"]
            reference = (out / "members" / (representative + ".asm")).read_text(encoding="utf-8")
            for member in cluster["members"]:
                address = member["address"]
                entry = builder.transfers.get(address[2:])
                accepted = completion(entry, ROOT, hashes)
                member_contexts.append({
                    "address": address, "symbol": member["symbol"], "representative": representative,
                    "registry": builder.coverage.get(address[2:]), "transfer": entry, "completion": accepted,
                    "callgraph": {"incoming": builder.callgraph_in.get(address[2:], []),
                                  "outgoing": builder.callgraph_out.get(address[2:], [])},
                    "callsites": {"available": builder.have_callsites,
                                  "incoming": builder.callsite_in.get(address[2:], []),
                                  "outgoing": builder.callsite_out.get(address[2:], []),
                                  "unresolved_indirect": builder.indirect_calls.get(address[2:], [])},
                })
                flags = "/".join("1" if (entry or {}).get("stages", {}).get(s) is True else "0"
                                 for s in ("analyzed", "ported", "wired", "compared"))
                delta_link = f"representatives/{representative}.md"
                if address != representative:
                    concrete = (out / "members" / (address + ".asm")).read_text(encoding="utf-8")
                    delta_link = f"member-deltas/{address}.diff"
                    (out / delta_link).write_text(member_delta(representative, address, reference, concrete),
                                                 encoding="utf-8")
                matrix.append(f"| {address} | {member['symbol']} | {flags} | {accepted['status']} | "
                              f"[{representative}]({delta_link}) |")
        (out / "FAMILY.md").write_text("\n".join(matrix) + "\n", encoding="utf-8")
        write_json(out / "members.json", {"schema": 1, "functions": member_contexts,
                   "meaning": "All member contexts; static direct graph is not runtime order or complete virtual dispatch."})
        summary = {"schema": 2, "kind": "code-first-family-packet", "method": args.method,
                   "scope": args.scope, "original_elf_sha256": data["elf_sha256"],
                   "members": data["members"], "representatives": representatives,
                   "exact_clusters": len(representatives), "near_threshold": args.near,
                   "work_reduction_hint": data["members"] - len(representatives),
                   "evidence_index_loads": 1, "decoded_member_bodies": data["members"],
                   "source_fingerprint": document["source_fingerprint"]["sha256"],
                   "generator_inputs": {p: hashlib.sha256((ROOT / p).read_bytes()).hexdigest() for p in
                                        ("tools/prepare_family_packet.py", "tools/asm_family_cluster.py",
                                         "tools/transfer_contract.py", "research/ui-contour.json")},
                   "meaning": "Batching hint; every member delta, field/call contract and sink still needs review."}
        write_json(out / "summary.json", summary)
        entry = [f"# Start here: {args.method}", "",
                 f"Scope: {args.scope}; {data['members']} members; {len(representatives)} structural representatives.",
                 "No function was accepted or promoted by this script.", "",
                 "1. Read FAMILY.md for all members and existing bounded stages/acceptance.",
                 "2. Read ASM_CLUSTERS.md. Normalized shape is NOT semantic equivalence.",
                 "3. Open one representative evidence card at a time; full ASM is in members/.",
                 "4. Review every member-deltas/*.diff plus raw ASM/callers; constants and field ownership matter.",
                 "5. Reuse a shared implementation only after validating each member's differences.",
                 "6. Trace production callers, fields and consumers; compare the translation with pinned ASM/library contracts.",
                 "7. Build affected code and run narrow known-contract checks; use an original harness/trace for a concrete unresolved question.",
                 "8. UI clicks, screenshots, frame and end-to-end scenarios are separate explicitly user-requested work.",
                 "9. Record remaining work in completion.open_items; four true stages describe the reviewed boundary.", "",
                 "Representative evidence: functions.json; EVERY member's boundary/callers: members.json.",
                 "Input identities: summary.json.",
                 "Missing callsites/decompilation/indirect targets remain explicit in representative cards.", "",
                 "## Representatives", ""]
        entry += [f"- [{r['address']} {r['symbol']}](representatives/{r['address']}.md)" for r in representatives]
        (out / "ENTRY.md").write_text("\n".join(entry) + "\n", encoding="utf-8")
        print(f"packet {out}: {data['members']} members -> {len(representatives)} representatives; one evidence index load")
        return 0
    except (OSError, ValueError, subprocess.CalledProcessError) as exc:
        ap.exit(2, f"family packet: {exc}\n")


if __name__ == "__main__":
    raise SystemExit(main())
