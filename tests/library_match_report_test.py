#!/usr/bin/env python3
"""Pure report-contract tests: no original process, Ghidra, screenshots or network."""
import copy
import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import library_match_report as pilot


def score(address, name, similarity):
    return {"address": address, "name": name, "similarity": similarity, "significance": 2.0}


def row(scores, status="ok"):
    return {"address": "0x00001000", "scores": scores, "bsim_status": status,
            "fid": None, "fid_full_matches": [], "fid_specific_matches": []}


class LibraryMatchReportTest(unittest.TestCase):
    def test_unique_retrieval_is_not_completion(self):
        result = pilot.summarize_row(row([score("0x20", "wanted", .8), score("0x30", "other", .7)]), "wanted")
        self.assertEqual(result["outcome"], "expected_unique_top")
        self.assertEqual(result["expected_rank"], 1)
        self.assertFalse(result["fid_available"])

    def test_equal_scores_remain_ambiguous(self):
        result = pilot.summarize_row(row([score("0x20", "other", 1.), score("0x30", "wanted", 1.)]), "wanted")
        self.assertEqual(result["outcome"], "expected_in_top_tie")
        self.assertEqual(result["top_tie_count"], 2)
        self.assertEqual(result["expected_rank"], 1)

    def test_wrong_top_does_not_hide_expected_rank(self):
        result = pilot.summarize_row(row([score("0x20", "other", 1.), score("0x30", "wanted", .9)]), "wanted")
        self.assertEqual(result["outcome"], "different_top_candidate")
        self.assertEqual(result["expected_rank"], 2)

    def test_unavailable_signatures_and_missing_labels_are_explicit(self):
        self.assertEqual(pilot.summarize_row(row([], "empty"), "wanted")["outcome"], "unavailable_query")
        result = pilot.summarize_row(row([score("0x20", "other", 1.)]), "wanted")
        self.assertEqual(result["outcome"], "expected_candidate_unavailable")
        self.assertIsNone(result["expected_rank"])

    def fixture(self, directory):
        root = Path(directory)
        targets, candidate_path, query_path = (root / p for p in ("targets.tsv", "candidate.json", "query.json"))
        targets.write_text("address\tsymbol\n0x00001000\twanted\n")
        common = {"schema": 1, "ghidra_version": "test", "language": "x86:LE:64:default",
                  "compiler_spec": "gcc", "weights_sha256": "a" * 64, "signature_settings": 73,
                  "script_elapsed_seconds": .01}
        candidate = dict(common, elf_sha256="b" * 64,
                         functions=[{"address": "0x20", "name": "wanted", "bsim_status": "ok"}])
        candidate_path.write_text(json.dumps(candidate))
        query = dict(common, elf_sha256=pilot.ORIGINAL_SHA,
                     candidate_elf_sha256=candidate["elf_sha256"], candidate_count=1,
                     candidate_export_sha256=pilot.digest(candidate_path), targets_sha256=pilot.digest(targets),
                     functions=[row([score("0x20", "wanted", .9)])])
        query_path.write_text(json.dumps(query))
        return targets, candidate_path, query_path, query

    def test_complete_report_and_stale_candidate_gate(self):
        with tempfile.TemporaryDirectory() as temp:
            targets, candidate, query, _ = self.fixture(temp)
            result = pilot.build_report(query, candidate, targets, None)
            self.assertEqual(result["outcomes"], {"expected_unique_top": 1})
            self.assertFalse(result["completion_statuses_changed"])
            candidate.write_text(candidate.read_text() + "\n")
            with self.assertRaisesRegex(ValueError, "Candidate export"):
                pilot.build_report(query, candidate, targets, None)

    def test_identity_target_and_comparison_gates(self):
        with tempfile.TemporaryDirectory() as temp:
            targets, candidate, query_path, query = self.fixture(temp)
            changes = [("elf_sha256", "bad", "pinned ELF"), ("targets_sha256", "bad", "target list"),
                       ("weights_sha256", "bad", "settings"), ("candidate_count", 0, "count")]
            for key, value, message in changes:
                with self.subTest(key=key):
                    edited = dict(query, **{key: value})
                    query_path.write_text(json.dumps(edited))
                    with self.assertRaisesRegex(ValueError, message):
                        pilot.build_report(query_path, candidate, targets, None)
            edited = copy.deepcopy(query)
            edited["functions"][0]["scores"] = []
            query_path.write_text(json.dumps(edited))
            with self.assertRaisesRegex(ValueError, "Incomplete"):
                pilot.build_report(query_path, candidate, targets, None)

    def test_known_tail_requires_incoming_and_outgoing_evidence(self):
        with tempfile.TemporaryDirectory() as temp:
            directory = Path(temp)
            target, caller, site = "0x00d04610", "0x00a0adc0", "0x00a0ae8c"
            packets = {
                "manifest.json": {"original_elf_sha256": pilot.ORIGINAL_SHA, "functions": [
                    {"address": target, "json": "target.json", "status": "exported"},
                    {"address": caller, "json": "caller.json", "status": "exported"}]},
                "target.json": {"address": target, "original_elf_sha256": pilot.ORIGINAL_SHA,
                    "incoming_entry_references_including_data": [
                        {"from": site, "owner": caller, "type": "UNCONDITIONAL_JUMP"},
                        {"from": "0x20", "owner": None, "type": "DATA"}]},
                "caller.json": {"address": caller, "original_elf_sha256": pilot.ORIGINAL_SHA,
                    "instructions": [{"address": site, "mnemonic": "JMP", "text": "JMP " + target,
                                      "references": [{"to": target}]}]},
            }
            for name, value in packets.items():
                (directory / name).write_text(json.dumps(value))
            self.assertEqual(pilot.check_tail_reference(directory)["recorded_incoming_count"], 2)
            packets["caller.json"]["instructions"][0]["mnemonic"] = "CALL"
            (directory / "caller.json").write_text(json.dumps(packets["caller.json"]))
            with self.assertRaisesRegex(ValueError, "tail edge"):
                pilot.check_tail_reference(directory)


if __name__ == "__main__":
    unittest.main()
