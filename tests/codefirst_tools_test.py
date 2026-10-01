#!/usr/bin/env python3
"""Scope, explicit acceptance and bounded batch preparation; no game execution."""
from __future__ import annotations
import copy
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import asm_family_cluster as asm
import prepare_family_packet as family
import work_frontier
import audit_sinks
from transfer_contract import REVIEW_AREAS, STAGES, completion, in_scope, load_scope
from readiness import build_report


class CodeFirstToolsTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.write("src/sample.cpp", "implementation\n")
        self.write("tests/sample.cpp", "original comparison and regression\n")
        self.write("research/ui-contour.json", json.dumps({
            "class_prefixes": ["CInventoryMenu", "CGameUI"], "entry_addresses": ["0x3000"]}))
        self.entry = {"stages": {s: True for s in STAGES}}

    def write(self, relative, data):
        path = self.root / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(data, encoding="utf-8")
        return path

    def full(self):
        return {**self.entry, "completion": {
            "status": "full", "open_items": [],
            "review": {area: "explicit reviewer evidence for " + area for area in REVIEW_AREAS},
            "inputs": {p: hashlib.sha256((self.root / p).read_bytes()).hexdigest()
                       for p in ("src/sample.cpp", "tests/sample.cpp")}}}

    def test_four_stages_never_imply_full_acceptance(self):
        self.assertEqual(completion(self.entry, self.root)["status"], "unassessed")
        self.assertEqual(completion(None, self.root)["status"], "unassessed")

    def test_partial_requires_explicit_remaining_work(self):
        entry = {**self.entry, "completion": {"status": "partial", "open_items": ["renderer sink"]}}
        self.assertEqual(completion(entry, self.root)["status"], "partial")
        entry["completion"]["open_items"] = []
        self.assertEqual(completion(entry, self.root)["status"], "invalid")

    def test_full_claim_is_reviewed_not_automatically_proven(self):
        entry = self.full()
        before = copy.deepcopy(entry)
        result = completion(entry, self.root)
        self.assertEqual(result["status"], "reviewed_full")
        self.assertIn("not an automated semantic proof", result["meaning"])
        self.assertEqual(entry, before)

    def test_full_claim_cannot_leave_an_effect_open(self):
        entry = self.full()
        entry["completion"]["open_items"].append("OPEN animation")
        self.assertEqual(completion(entry, self.root)["status"], "invalid")

    def test_every_stage_and_review_area_is_required(self):
        for stage in STAGES:
            entry = self.full()
            entry["stages"] = {**entry["stages"], stage: False}
            self.assertEqual(completion(entry, self.root)["status"], "invalid", stage)
        for area in REVIEW_AREAS:
            entry = self.full()
            del entry["completion"]["review"][area]
            self.assertEqual(completion(entry, self.root)["status"], "invalid", area)

    def test_changed_or_missing_inputs_invalidate_acceptance(self):
        entry = self.full()
        self.write("src/sample.cpp", "changed\n")
        self.assertEqual(completion(entry, self.root)["status"], "stale")
        entry = self.full()
        entry["completion"]["inputs"]["tests/missing.cpp"] = "0" * 64
        self.assertEqual(completion(entry, self.root)["status"], "stale")

    def test_implementation_and_test_inputs_are_mandatory(self):
        for path in ("src/sample.cpp", "tests/sample.cpp"):
            entry = self.full()
            del entry["completion"]["inputs"][path]
            self.assertEqual(completion(entry, self.root)["status"], "invalid")

    def test_input_paths_and_hashes_fail_closed(self):
        for path, digest in (("../outside", "a" * 64), ("/tmp/outside", "a" * 64),
                             ("src/sample.cpp", "bad-hash")):
            entry = self.full()
            entry["completion"]["inputs"][path] = digest
            self.assertEqual(completion(entry, self.root)["status"], "invalid")
        (self.root / "src/link.cpp").symlink_to(self.root / "src/sample.cpp")
        entry = self.full()
        entry["completion"]["inputs"]["src/link.cpp"] = "a" * 64
        self.assertEqual(completion(entry, self.root)["status"], "invalid")

    def test_bad_completion_shape_is_not_promoted(self):
        for record in ([], "full", {"status": []}, {"status": "done"}, {"status": "full"}):
            self.assertEqual(completion({**self.entry, "completion": record}, self.root)["status"], "invalid")

    def test_ui_scope_includes_explicit_entries_and_thunks_not_gameplay(self):
        scope = load_scope(self.root)
        self.assertTrue(in_scope("CInventoryMenu::setOpen(bool)", "0x1000", scope))
        self.assertTrue(in_scope("non-virtual thunk to CGameUI::update()", "0x1000", scope))
        self.assertTrue(in_scope("explicit_dependency()", "0x3000", scope))
        self.assertFalse(in_scope("CSkill::startSkill()", "0x2000", scope))
        self.assertTrue(in_scope("CSkill::startSkill()", "0x2000", load_scope(self.root, "all")))

    def frontier_fixture(self):
        self.write("research/coverage.tsv",
                   "address\tsymbol\tsubsystem\tstatus\tincoming\toutgoing\tpriority\n"
                   "0x00001000\tCInventoryMenu::setOpen(bool)\titems\tpartial\t1\t1\t9\n"
                   "0x00002000\tCSkill::startSkill()\tskills\tpartial\t1\t1\t99\n")
        entries = {"0x00001000": {**self.entry, "implementation": "src/sample.cpp"},
                   "0x00002000": {**self.entry, "implementation": "src/skills.cpp"}}
        self.write("research/function-transfer.json", json.dumps({"functions": entries}))
        self.write("research/auto-triage.json", json.dumps({"total_functions": 999999}))

    def test_frontier_keeps_all_true_unreviewed_functions_in_scope_and_groups(self):
        self.frontier_fixture()
        report = work_frontier.build(self.root, None, 1)
        self.assertEqual(report["scope"]["functions"], 1)
        self.assertEqual(report["whole_function_completion"], {"unassessed": 1})
        pending = report["near_term"]["whole_function_open"]
        self.assertEqual([r["address"] for r in pending], ["0x00001000"])
        self.assertEqual(report["near_term"]["integration_groups"][0]["implementation_group"], "src/sample.cpp")
        self.assertEqual(report["auto_triage"]["total_functions"], 2)  # fresh, not stale export
        self.assertEqual(work_frontier.build(self.root, None, 1, scope_name="all")["scope"]["functions"], 2)

    def test_shape_similarity_does_not_erase_concrete_delta(self):
        left = " 1000: mov $0x1,0x10(%rax)\n 1007: call 2000 <A>\n 100c: ret\n"
        right = " 3000: mov $0x2,0x20(%rax)\n 3007: call 4000 <B>\n 300c: ret\n"
        self.assertEqual([asm.normalize_instruction(x) for x in asm.instructions(left)],
                         [asm.normalize_instruction(x) for x in asm.instructions(right)])
        delta = family.member_delta("0x1000", "0x3000", left, right)
        for value in ("$0x1", "$0x2", "0x10", "0x20", "<A>", "<B>"):
            self.assertIn(value, delta)

    def test_one_evidence_builder_per_batch(self):
        with patch.object(family, "FunctionPackageBuilder") as factory:
            factory.return_value.document.return_value = {"functions": []}
            builder, document = family.build_evidence(self.root, ["0x1000", "0x2000"])
            factory.assert_called_once_with(self.root, callsites_path=None)
            builder.document.assert_called_once_with(["0x1000", "0x2000"])

    def test_contract_plan_uses_graph_and_fixtures_and_excludes_ui_execution(self):
        def test(name, labels, **props):
            return {"name": name, "command": [], "properties": [
                {"name": "LABELS", "value": labels},
                *[{"name": key, "value": value} for key, value in props.items()]]}
        tests = [test("cpu", ["core"], FIXTURES_REQUIRED=["data"]),
                 test("data_setup", ["assets"], FIXTURES_SETUP=["data"]),
                 test("window", ["render"]), test("unrelated", ["core"])]
        index = {name: {"inputs": {"tests/sample.cpp"} if name in {"cpu", "window"} else set(),
                        "targets": {name + "_target"}, "opaque": False}
                 for name in ("cpu", "window", "data_setup", "unrelated")}
        document = {"functions": [{"registry": {"tests": "tests/sample.cpp;tests/unknown.py"}}]}
        with patch.object(family.subprocess, "run") as command, patch.object(family, "dependency_index", return_value=index):
            command.return_value.stdout = json.dumps({"tests": tests})
            plan = family.contract_test_plan(self.root, document, self.root / "build")
        self.assertEqual(plan["selection"]["tests"], ["cpu", "data_setup"])
        self.assertEqual(plan["excluded_integration_tests"], ["window"])
        self.assertEqual(plan["unmapped_files"], ["tests/unknown.py"])
        self.assertFalse(plan["selection"]["build_all"])
        self.assertEqual(plan["test_command"][-1], "^(cpu|data_setup)$")
        self.assertEqual(command.call_count, 1)  # discovery only, never build/run
        self.assertIn("--show-only=json-v1", command.call_args.args[0])

    def test_contract_plan_without_registered_tests_has_no_execution_commands(self):
        document = {"functions": [{"registry": {"tests": ""}}]}
        with patch.object(family.subprocess, "run") as command, patch.object(family, "dependency_index", return_value={}):
            command.return_value.stdout = json.dumps({"tests": []})
            plan = family.contract_test_plan(self.root, document, self.root / "build")
        self.assertEqual(plan["selection"]["tests"], [])
        self.assertIsNone(plan["build_command"])
        self.assertIsNone(plan["test_command"])

    def test_automated_checks_reject_skips_changed_sources_and_wrong_test_names(self):
        plan = {"selection": {"tests": ["cpu"]}, "build_command": ["cmake", "--build", "build"],
                "test_command": ["ctest", "--test-dir", "build"]}
        for xml, after, expected in (
                ('<testcase name="cpu"/>', "same", "PASSED"),
                ('<testcase name="cpu"><skipped/></testcase>', "same", "NOT RUN"),
                ('<testcase name="cpu"/>', "changed", "FAILED"),
                ('<testcase name="other"/>', "same", "FAILED")):
            with self.subTest(xml=xml, after=after):
                out = self.root / ("check-" + str(len(list(self.root.glob('check-*')))))
                out.mkdir()
                def run(command, **kwargs):
                    if command[0] == "ctest":
                        (out / "checks.xml").write_text("<testsuite>" + xml + "</testsuite>")
                    return subprocess.CompletedProcess(command, 0)
                with patch.object(family, "source_snapshot", side_effect=[{"sha256": "same"}, {"sha256": after}]), \
                     patch.object(family.subprocess, "run", side_effect=run):
                    result = family.run_contract_checks(self.root, plan, out, 2)
                self.assertEqual(result["status"], expected)
                self.assertEqual(json.loads((out / "checks.json").read_text())["status"], expected)

    def test_build_failure_does_not_execute_contract_tests(self):
        plan = {"selection": {"tests": ["cpu"]}, "build_command": ["cmake"], "test_command": ["ctest"]}
        out = self.root / "failed-build"
        out.mkdir()
        with patch.object(family, "source_snapshot", return_value={"sha256": "same"}), \
             patch.object(family.subprocess, "run", return_value=subprocess.CompletedProcess([], 1)) as command:
            result = family.run_contract_checks(self.root, plan, out, 2)
        self.assertEqual(result["status"], "FAILED")
        self.assertEqual(command.call_count, 1)

    def test_header_declaration_is_not_counted_as_production_consumer(self):
        self.write("include/sample.hpp", "void only_declared();\n")
        self.write("tests/sample.cpp", "only_declared();\n")
        audit_sinks.reference_index.cache_clear()
        self.assertEqual(audit_sinks.references(str(self.root), "only_declared"), set())
        self.assertEqual(audit_sinks.test_refs(str(self.root), "only_declared"), {"tests/sample.cpp"})
        self.assertEqual(audit_sinks.reference_index.cache_info().misses, 1)

    def test_family_output_cannot_replace_sources(self):
        result = subprocess.run([sys.executable, str(ROOT / "tools/prepare_family_packet.py"),
                                 "setOpen", "--elf", str(self.root / "absent-elf"),
                                 "--out", str(ROOT / "research/families")], capture_output=True, text=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("ignored, not source", result.stderr)

    def test_existing_packet_is_not_overlaid_with_stale_files(self):
        out = self.root / "packet"
        out.mkdir()
        (out / "prior.md").write_text("keep", encoding="utf-8")
        result = subprocess.run([sys.executable, str(ROOT / "tools/prepare_family_packet.py"),
                                 "setOpen", "--elf", str(self.root / "absent-elf"),
                                 "--out", str(out)], capture_output=True, text=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("new or empty", result.stderr)
        self.assertEqual((out / "prior.md").read_text(), "keep")

    def test_green_capability_manifest_never_claims_codefirst_release(self):
        manifest = {"schema": 1, "scope_complete": True, "capabilities": [{
            "id": "a", "title": "demo", "stage": "complete", "boundary": "bounded",
            "code": [], "evidence": [], "tests": ["a"], "blockers": []}]}
        result = build_report(self.root, manifest, [("run", {
            "schema": 1, "kind": "verification-run", "source": {"sha256": "same"},
            "source_consistent": True, "groups": {"core": {"tests": [{"name": "a", "status": "PASSED"}]}}
        })], {"sha256": "same"})
        self.assertTrue(result["capability_scope_ready"])
        self.assertFalse(result["release_ready"])
        self.assertIn("NOT ASSESSED", result["release_readiness"])

    def test_readiness_rejects_colliding_outputs_before_writing(self):
        path = self.root / "result.json"
        result = subprocess.run([sys.executable, str(ROOT / "tools/readiness.py"),
                                 "--json", str(path), "--markdown", str(path)],
                                capture_output=True, text=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("different files", result.stderr)
        self.assertFalse(path.exists())


if __name__ == "__main__":
    unittest.main()
