#!/usr/bin/env python3
"""Summarize Ghidra's bounded BSim/FID pilot; never promote transfer statuses."""
from __future__ import annotations

import argparse
import csv
import hashlib
import json
from collections import Counter
from pathlib import Path

ORIGINAL_SHA = "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"
TIE_EPSILON = 1e-12


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def summarize_row(row: dict, expected: str) -> dict:
    scores = row["scores"]
    expected_scores = [s for s in scores if s["name"] == expected]
    best_expected = max(expected_scores, key=lambda s: s["similarity"], default=None)
    tied_top = [s for s in scores if abs(s["similarity"] - scores[0]["similarity"]) <= TIE_EPSILON]
    expected_is_top = any(s["name"] == expected for s in tied_top)
    # Names are used only here, after Ghidra has computed ALL candidate scores.
    rank = None if best_expected is None else 1 + sum(
        s["similarity"] > best_expected["similarity"] + TIE_EPSILON for s in scores
    )
    if row["bsim_status"] != "ok":
        outcome = "unavailable_query"
    elif not expected_scores:
        outcome = "expected_candidate_unavailable"
    elif not expected_is_top:
        outcome = "different_top_candidate"
    elif len(tied_top) != 1:
        outcome = "expected_in_top_tie"
    else:
        outcome = "expected_unique_top"
    return {
        "address": row["address"], "expected_symbol": expected,
        "bsim_status": row["bsim_status"], "outcome": outcome,
        "self_significance": row.get("self_significance"),
        "expected_rank": rank, "expected_score": best_expected,
        "top_tie_count": len(tied_top), "top_candidates": tied_top,
        "compared_candidates": len(scores),
        "fid_available": row["fid"] is not None,
        "fid_full_matches": row["fid_full_matches"],
        "fid_specific_matches": row["fid_specific_matches"],
    }


def check_tail_reference(directory: Path) -> dict:
    manifest = json.loads((directory / "manifest.json").read_text())
    if manifest["original_elf_sha256"] != ORIGINAL_SHA:
        raise ValueError("Xref manifest ELF identity mismatch")
    paths = {r["address"]: r["json"] for r in manifest["functions"] if r["status"] == "exported"}
    packets = {}
    for address in ("0x00d04610", "0x00a0adc0"):
        path = (directory / paths[address]).resolve()
        if path.parent != directory.resolve():
            raise ValueError("Xref packet path escapes export directory")
        packets[address] = json.loads(path.read_text())
        if packets[address]["original_elf_sha256"] != ORIGINAL_SHA or packets[address]["address"] != address:
            raise ValueError("Xref packet identity mismatch")
    target = packets["0x00d04610"]
    owner = packets["0x00a0adc0"]
    incoming = [r for r in target["incoming_entry_references_including_data"]
                if r["from"] == "0x00a0ae8c" and r["owner"] == owner["address"]]
    sites = [i for i in owner["instructions"] if i["address"] == "0x00a0ae8c"
             and i["mnemonic"].upper() == "JMP"
             and any(r["to"] == target["address"] for r in i["references"])]
    if not incoming or len(sites) != 1:
        raise ValueError("Known createAndFireMissile tail edge is missing")
    return {
        "target": target["address"], "caller": owner["address"],
        "site": sites[0]["address"], "instruction": sites[0]["text"],
        "incoming_types": [r["type"] for r in incoming],
        "recorded_incoming_count": len(target["incoming_entry_references_including_data"]),
        "manifest_sha256": digest(directory / "manifest.json"),
        "scope": "known tail jump and recorded entry references, not all runtime callers",
    }


def build_report(query_path: Path, candidate_path: Path, targets_path: Path, xref_dir: Path | None) -> dict:
    query = json.loads(query_path.read_text())
    candidate = json.loads(candidate_path.read_text())
    if query["schema"] != 1 or query["elf_sha256"] != ORIGINAL_SHA:
        raise ValueError("Query schema or pinned ELF identity mismatch")
    if query["candidate_export_sha256"] != digest(candidate_path):
        raise ValueError("Candidate export is stale or different")
    if query["candidate_elf_sha256"] != candidate["elf_sha256"]:
        raise ValueError("Candidate ELF identity mismatch")
    if query["targets_sha256"] != digest(targets_path):
        raise ValueError("Preselected target list is stale or different")
    for key in ("schema", "ghidra_version", "language", "compiler_spec", "weights_sha256", "signature_settings"):
        if query[key] != candidate[key]:
            raise ValueError(f"Incompatible Ghidra settings: {key}")
    with targets_path.open() as stream:
        labels = list(csv.DictReader(stream, delimiter="\t"))
    expected = {r["address"]: r["symbol"] for r in labels}
    rows = query["functions"]
    if (len(labels) != len(expected) or len(rows) != len(expected)
            or {r["address"] for r in rows} != set(expected)):
        raise ValueError("Query entries differ from preselected targets")
    pool = {r["address"]: r for r in candidate["functions"]}
    if len(pool) != len(candidate["functions"]) or query["candidate_count"] != len(pool):
        raise ValueError("Candidate count/identity mismatch")
    valid_pool = {a for a, r in pool.items() if r["bsim_status"] == "ok"}
    for row in rows:
        scores = row["scores"]
        required = valid_pool if row["bsim_status"] == "ok" else set()
        if len(scores) != len(required) or {s["address"] for s in scores} != required:
            raise ValueError("Incomplete or duplicate candidate comparisons")
        if any(s["name"] != pool[s["address"]]["name"] for s in scores):
            raise ValueError("Candidate labels changed after scoring")
        if any(not isinstance(s["similarity"], (float, int)) or not -1e-12 <= s["similarity"] <= 1 + 1e-12 for s in scores):
            raise ValueError("Invalid similarity score")
        if any(scores[i]["similarity"] < scores[i+1]["similarity"] for i in range(len(scores)-1)):
            raise ValueError("Candidate scores not sorted")
    result_rows = [summarize_row(r, expected[r["address"]]) for r in rows]
    return {
        "schema": 1, "original_elf_sha256": ORIGINAL_SHA,
        "query_export_sha256": digest(query_path), "candidate_export_sha256": digest(candidate_path),
        "candidate_elf_sha256": candidate["elf_sha256"], "targets_sha256": digest(targets_path),
        "ghidra_version": query["ghidra_version"], "weights_sha256": query["weights_sha256"],
        "analysis_completeness": "not established by feature exports; inspect headless analysis logs",
        "signature_settings": query["signature_settings"], "candidate_count": len(pool),
        "candidate_bsim_statuses": dict(Counter(r["bsim_status"] for r in pool.values())),
        "query_count": len(rows), "outcomes": dict(Counter(r["outcome"] for r in result_rows)),
        "fid_query_available_count": sum(r["fid_available"] for r in result_rows),
        "fid_expected_specific_unique_count": sum(
            len(r["fid_specific_matches"]) == 1 and r["fid_specific_matches"][0]["name"] == r["expected_symbol"]
            for r in result_rows),
        "candidate_feature_seconds": candidate["script_elapsed_seconds"],
        "query_and_compare_seconds": query["script_elapsed_seconds"],
        "known_tail_reference": check_tail_reference(xref_dir) if xref_dir else None,
        "functions": result_rows, "completion_statuses_changed": False,
        "boundary": "symbol-label retrieval on a pinned source candidate; neither source-version proof nor semantic equivalence",
    }


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--query", type=Path, required=True)
    parser.add_argument("--candidate", type=Path, required=True)
    parser.add_argument("--targets", type=Path, default=Path(__file__).resolve().parents[1] / "research/library-match-targets.tsv")
    parser.add_argument("--xref-dir", type=Path)
    parser.add_argument("--out", type=Path, required=True)
    args = parser.parse_args()
    report = build_report(args.query, args.candidate, args.targets, args.xref_dir)
    with args.out.open("x") as stream:
        json.dump(report, stream, indent=2, ensure_ascii=False, allow_nan=False)
        stream.write("\n")
    print(json.dumps({k: v for k, v in report.items() if k != "functions"}, indent=2))


if __name__ == "__main__":
    main()
