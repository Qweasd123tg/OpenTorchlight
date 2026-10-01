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
import re
import subprocess
import sys

from asm_family_cluster import instructions
from automation_state import source_snapshot, validate_output, write_json
from function_package import FunctionPackageBuilder, render_markdown
from transfer_contract import completion
from check_selection import dependency_index, make_plan, properties
from check import summarize_junit

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


def contract_test_plan(root: Path, document: dict, build: Path) -> dict:
    """Map explicitly recorded contract tests to the existing CTest/Ninja graph."""
    files = set()
    for packet in document["functions"]:
        for record in (packet.get("registry"), packet.get("transfer")):
            files.update(re.findall(r"tests/[\w./-]+\.(?:cpp|cc|cxx|c|py)\b",
                                    (record or {}).get("tests", "")))
    discovery = subprocess.run(["ctest", "--test-dir", str(build), "--show-only=json-v1"],
                               capture_output=True, text=True, check=True)
    tests = json.loads(discovery.stdout)["tests"]
    index = dependency_index(root, build, tests)
    matched = {name for name, entry in index.items() if files.intersection(entry["inputs"])}
    integration = {test["name"] for test in tests
                   if set(properties(test).get("LABELS", [])) & {"render", "desktop", "ui-integration"}}
    safe = matched - integration
    plan = make_plan(tests, {"core", "assets", "reference"}, None, index,
                     requested_tests=sorted(safe))
    matched_files = {path for name in matched for path in files.intersection(index[name]["inputs"])}
    selected = plan["tests"]
    return {"meaning": "Plan only for recorded bounded contracts; no tests executed, no complete regression or semantic closure inferred.",
            "ctest_discovery_sha256": hashlib.sha256(discovery.stdout.encode()).hexdigest(),
            "recorded_files": sorted(files), "unmapped_files": sorted(files - matched_files),
            "excluded_integration_tests": sorted(matched & integration), "selection": plan,
            "build_command": (["cmake", "--build", str(build)] +
                              ([] if plan["build_all"] else ["--target", *plan["build_targets"]])) if selected else None,
            "test_command": (["ctest", "--test-dir", str(build), "--output-on-failure", "-R",
                              "^(" + "|".join(re.escape(name) for name in selected) + ")$"]) if selected else None}


def run_contract_checks(root: Path, plan: dict, out: Path, jobs: int) -> dict:
    """Execute the generated bounded plan with existing result/identity rules."""
    before = source_snapshot(root)
    result = {"status": "NOT RUN", "meaning": "Bounded recorded-contract checks only; no function completion promotion.",
              "source_before": before["sha256"], "selected_tests": plan["selection"]["tests"]}
    junit = out / "checks.xml"
    with (out / "checks.log").open("w", encoding="utf-8") as log:
        try:
            if plan["build_command"] and plan["test_command"]:
                build = subprocess.run([*plan["build_command"], "--parallel", str(jobs)],
                                       stdout=log, stderr=subprocess.STDOUT, timeout=600)
                result["build_returncode"] = build.returncode
                if build.returncode:
                    result.update(status="FAILED", reason="Build failed; inspect checks.log")
                else:
                    check = subprocess.run([*plan["test_command"], "--no-tests=error", "--output-junit", str(junit)],
                                           stdout=log, stderr=subprocess.STDOUT, timeout=600)
                    result.update(summarize_junit(junit, check.returncode))
                    if {item["name"] for item in result["tests"]} != set(result["selected_tests"]):
                        result.update(status="FAILED", reason="CTest result names differ from the generated selection")
            else:
                result["reason"] = "No registered contract checks selected"
        except (OSError, subprocess.TimeoutExpired) as exc:
            result.update(status="FAILED", reason=str(exc))
    after = source_snapshot(root)
    result.update(source_after=after["sha256"], source_consistent=before["sha256"] == after["sha256"])
    if not result["source_consistent"]:
        result.update(status="FAILED", reason="Source inputs changed during verification")
    write_json(out / "checks.json", result)
    return result


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
    ap.add_argument("--build-dir", type=Path, help="optional existing CTest/Ninja build; emit a recorded-contract test plan without configuring or running it")
    ap.add_argument("--check", action="store_true", help="also build and execute the generated CPU/resource/reference contract plan")
    ap.add_argument("--jobs", type=int, default=2)
    args = ap.parse_args()
    if not 1 <= args.max_members <= 64 or not 1 <= args.max_representatives <= 64:
        ap.error("member/representative budgets must be in 1..64")
    if args.check and not args.build_dir:
        ap.error("--check requires --build-dir")
    if not 1 <= args.jobs <= 128:
        ap.error("--jobs must be in 1..128")
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
        if args.build_dir:
            # Checks must include every member's recorded contracts, even when
            # only structural representatives receive the larger evidence cards.
            test_document = {"functions": [
                {"registry": builder.coverage.get(member["address"][2:]),
                 "transfer": builder.transfers.get(member["address"][2:])}
                for cluster in data["clusters"] for member in cluster["members"]]}
            test_plan = contract_test_plan(ROOT, test_document, args.build_dir.resolve())
            write_json(out / "test-plan.json", test_plan)
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
                                        ("tools/prepare_family_packet.py", "tools/asm_family_cluster.py", "tools/check_selection.py", "tools/check.py", "tools/automation_state.py",
                                         "tools/transfer_contract.py", "research/ui-contour.json")},
                   "meaning": "Batching hint; every member delta, field/call contract and sink still needs review."}
        write_json(out / "summary.json", summary)
        entry = [f"# Start here: {args.method}", "",
                 f"Scope: {args.scope}; {data['members']} members; {len(representatives)} structural representatives.",
                 "No function was accepted or promoted by this script.", "",
                 "Local library source candidates and version evidence are included in the representative cards.",
                 *(["Recorded CPU/resource/reference checks and build commands: test-plan.json (plan only)."] if args.build_dir else []),
                 *(["Explicit --check results: checks.json, checks.log and checks.xml."] if args.check else []),
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
        if args.check:
            checked = run_contract_checks(ROOT, test_plan, out, args.jobs)
            print(f"recorded contract checks: {checked['status']}; see {out / 'checks.json'}")
            if checked["status"] != "PASSED":
                return 1
        return 0
    except (OSError, ValueError, subprocess.CalledProcessError) as exc:
        ap.exit(2, f"family packet: {exc}\n")


if __name__ == "__main__":
    raise SystemExit(main())
