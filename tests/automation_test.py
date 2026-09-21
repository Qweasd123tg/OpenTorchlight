#!/usr/bin/env python3
"""Portable negative/positive acceptance for deterministic automation."""
from __future__ import annotations

import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from automation_state import changed_paths, snapshot_changes, source_snapshot, validate_output
from check_selection import close_fixtures, dependency_index, make_plan
from export_callsites import parse_calls
from original import Symbol
from readiness import build_report, validate_manifest


def test_entry(name, labels=("core",), **props):
    return {"name": name, "properties": [{"name": k, "value": v} for k, v in {"LABELS": list(labels), **props}.items()]}


class Automation(unittest.TestCase):
    def repo(self, root):
        subprocess.run(["git", "init", "-q", str(root)], check=True)
        (root / "a.cpp").write_text("old")
        (root / ".gitignore").write_text("/build/\n")
        subprocess.run(["git", "-C", str(root), "add", "."], check=True)
        subprocess.run(["git", "-C", str(root), "-c", "user.name=Test", "-c", "user.email=test@example.invalid",
                        "commit", "-qm", "fixture"], check=True)

    def test_snapshot_dirty_untracked_deleted_ignored(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d); self.repo(root)
            before = source_snapshot(root)
            self.assertEqual(before, source_snapshot(root))
            (root / "build").mkdir(); (root / "build/result.json").write_text("generated")
            self.assertEqual(before, source_snapshot(root))
            (root / "a.cpp").write_text("dirty")
            (root / "new.cpp").write_text("untracked")
            self.assertNotEqual(before["sha256"], source_snapshot(root)["sha256"])
            self.assertEqual(changed_paths(root, "HEAD"), ["a.cpp", "new.cpp"])
            self.assertEqual(snapshot_changes(before, source_snapshot(root)), ["a.cpp", "new.cpp"])
            (root / "a.cpp").unlink()
            self.assertEqual(source_snapshot(root)["files"]["a.cpp"], {"kind": "missing"})
            with self.assertRaises(ValueError): changed_paths(root, "--bad-option")
            with self.assertRaises(ValueError): validate_output(root, root / "a.cpp")
            with self.assertRaises(ValueError): validate_output(root, root)
            validate_output(root, root / "build/result.json")
            with self.assertRaises(ValueError): validate_output(root, root / "build/original", [root / "build"])

    def test_symlink_identity_never_reads_external_target(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d); self.repo(root)
            (root / "link").symlink_to("/nonexistent/private/input")
            self.assertEqual(source_snapshot(root)["files"]["link"]["kind"], "symlink")

    def test_selection_fail_closed(self):
        tests = [test_entry("a"), test_entry("b"), test_entry("resource", ("assets",))]
        index = {n: {"inputs": {f"{n}.cpp"}, "targets": {n}, "opaque": False} for n in ("a", "b", "resource")}
        plan = make_plan(tests, {"core"}, ["a.cpp"], index)
        self.assertEqual(plan["tests"], ["a"])
        self.assertEqual(plan["build_targets"], ["a"])
        self.assertTrue(plan["not_a_full_gate"])
        for files in (["unknown.cpp"], ["a.hpp"], ["CMakeLists.txt"], ["helper.py"], ["deleted.cpp"]):
            with self.subTest(files=files):
                plan = make_plan(tests, {"core"}, files, index)
                self.assertEqual(plan["tests"], ["a", "b"])
                self.assertEqual(plan["mode"], "fallback-full")
        self.assertEqual(make_plan(tests, {"core"}, ["a.cpp"], None)["mode"], "fallback-full")
        self.assertEqual(make_plan(tests, {"core"}, [], index)["tests"], [])

    def test_fixture_dependency_closure(self):
        tests = [test_entry("use", FIXTURES_REQUIRED=["state"], DEPENDS=["other"]),
                 test_entry("setup", ("assets",), FIXTURES_SETUP=["state"]),
                 test_entry("cleanup", FIXTURES_CLEANUP=["state"]), test_entry("other")]
        self.assertEqual(close_fixtures(tests, {"use"}), {"use", "setup", "cleanup", "other"})
        with self.assertRaises(ValueError): close_fixtures(tests, {"missing"})

    def test_named_contract_selection_is_exact_and_partial(self):
        tests = [test_entry("layout", FIXTURES_REQUIRED=["data"]),
                 test_entry("setup", FIXTURES_SETUP=["data"]), test_entry("unrelated"),
                 test_entry("clicks", ("render", "ui-integration"))]
        index = {t["name"]: {"inputs": set(), "targets": {t["name"]}, "opaque": False} for t in tests}
        plan = make_plan(tests, {"core"}, None, index, requested_tests=["layout", "layout"])
        self.assertEqual(plan["tests"], ["layout", "setup"])
        self.assertEqual(plan["build_targets"], ["layout", "setup"])
        self.assertEqual(plan["mode"], "named")
        self.assertFalse(plan["build_all"])
        self.assertTrue(plan["not_a_full_gate"])
        for name in ("typo", "clicks"):
            with self.assertRaises(ValueError):
                make_plan(tests, {"core"}, None, index, requested_tests=[name])
        with self.assertRaises(ValueError):
            make_plan(tests, {"core"}, ["a.cpp"], index, requested_tests=["layout"])

    def test_integration_cannot_enter_core_via_fixtures_or_dual_labels(self):
        for prop in ({"DEPENDS": ["ui"]}, {"FIXTURES_REQUIRED": ["screen"]}):
            tests = [test_entry("contract", **prop),
                     test_entry("ui", ("render", "ui-integration"), FIXTURES_SETUP=["screen"])]
            with self.assertRaisesRegex(ValueError, "requires explicit --render"):
                make_plan(tests, {"core"}, None, None)
            self.assertEqual(make_plan(tests, {"core", "render"}, None, None)["tests"], ["contract", "ui"])
        for labels in (("core", "render"), ("core", "desktop"), ("core", "ui-integration")):
            with self.assertRaisesRegex(ValueError, "requires explicit"):
                make_plan([test_entry("ui", labels)], {"core"}, None, None)

    def test_real_ninja_graph_with_spaces_and_generated_input(self):
        with tempfile.TemporaryDirectory(prefix="ot graph ") as d:
            root = Path(d); build = root / "build"; build.mkdir()
            (root / "a.cpp").write_text("input")
            (build / "build.ninja").write_text("rule copy\n  command = cp $in $out\nbuild probe: copy ../a.cpp\n")
            test = test_entry("probe"); test["command"] = [str(build / "probe")]
            index = dependency_index(root, build, [test])
            self.assertIn("a.cpp", index["probe"]["inputs"])
            self.assertEqual(index["probe"]["targets"], {"probe"})

    def test_driver_end_to_end_baseline_selection_and_plan(self):
        with tempfile.TemporaryDirectory(prefix="ot driver ") as d:
            root = Path(d); self.repo(root)
            (root / "tools").mkdir()
            for name in ("check.py", "check_selection.py", "automation_state.py"):
                shutil.copyfile(ROOT / "tools" / name, root / "tools" / name)
            (root / ".gitignore").write_text("/build/\n__pycache__/\n")
            (root / "a.cpp").write_text("int main() { return 0; }\n")
            (root / "b.cpp").write_text("int main() { return 0; }\n")
            (root / "CMakeLists.txt").write_text(
                "cmake_minimum_required(VERSION 3.16)\nproject(Selection LANGUAGES CXX)\n"
                "enable_testing()\nadd_executable(a a.cpp)\nadd_executable(b b.cpp)\n"
                "add_test(NAME a COMMAND ${CMAKE_COMMAND} -E env $<TARGET_FILE:a>)\n"
                "add_test(NAME b COMMAND b)\n"
                "set_tests_properties(a b PROPERTIES LABELS core)\n"
                "if(TORCHLIGHT_ENABLE_RENDER OR TORCHLIGHT_ENABLE_DESKTOP)\n"
                "  message(FATAL_ERROR \"core selected graphics\")\nendif()\n"
                "add_test(NAME ui_clicks COMMAND ${CMAKE_COMMAND} -E false)\n"
                "set_tests_properties(ui_clicks PROPERTIES LABELS \"render;ui-integration\")\n")
            command = [sys.executable, str(root / "tools/check.py"), "--core", "--build-dir", str(root / "build")]
            def run(name, *args):
                output = root / "build" / (name + ".json")
                result = subprocess.run([*command, "--report", str(output), *args],
                                        text=True, capture_output=True, timeout=35)
                self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                return json.loads(output.read_text())
            named = run("named", "--test", "a")
            self.assertEqual(named["selection"]["tests"], ["a"])
            self.assertEqual(named["selection"]["build_targets"], ["a"])
            self.assertTrue(named["selection"]["not_a_full_gate"])
            self.assertEqual(named["groups"]["core"]["passed"], 1)
            self.assertFalse(named["selection"]["build_all"])
            self.assertFalse((root / "build/b").exists())
            baseline = run("baseline")
            self.assertEqual(baseline["groups"]["core"]["passed"], 2)
            self.assertTrue(baseline["source_consistent"])
            options = ("--since-report", str(root / "build/baseline.json"))
            plan = run("plan", *options, "--plan")
            self.assertEqual(plan["selection"]["tests"], [])
            self.assertEqual(plan["groups"]["core"]["status"], "PLANNED")
            noop = run("noop", *options)
            self.assertEqual(noop["groups"]["core"]["status"], "NOT AFFECTED")
            (root / "a.cpp").write_text("int main() { return 0; } // modified\n")
            selected = run("affected", *options)
            self.assertEqual(selected["selection"]["tests"], ["a"])
            self.assertEqual(selected["selection"]["build_targets"], ["a"])
            self.assertFalse(selected["selection"]["build_all"])
            self.assertEqual(selected["groups"]["core"]["passed"], 1)
            (root / "unknown.py").write_text("# unknown dependency\n")
            fallback = run("fallback", *options)
            self.assertEqual(fallback["selection"]["mode"], "fallback-full")
            self.assertEqual(fallback["groups"]["core"]["passed"], 2)
            # A partial run cannot become a new full baseline.
            wider = run("partial-baseline", "--since-report", str(root / "build/affected.json"))
            self.assertEqual(wider["selection"]["mode"], "fallback-full")

    def manifest(self):
        return {"schema": 1, "scope_complete": False, "capabilities": [{"id": "sample", "title": "Sample",
                "stage": "partial", "boundary": "Slice only", "code": [], "evidence": [], "tests": ["a"],
                "blockers": ["Other branches"]}]}

    def report(self, sha="now", status="PASSED", **values):
        return {"schema": 1, "kind": "verification-run", "source": {"sha256": sha},
                "source_consistent": True, "groups": {"core": {"tests": [{"name": "a", "status": status}]}}, **values}

    def test_readiness_never_promotes_partial_or_old_evidence(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            for report, expected in [(self.report(), "PASSED"), (self.report("old"), "NOT VERIFIED"),
                                      (self.report(status="FAILED"), "FAILED"),
                                      (self.report(plan_only=True), "NOT VERIFIED"),
                                      (self.report(source_consistent=False), "NOT VERIFIED")]:
                result = build_report(root, self.manifest(), [("run", report)], {"sha256": "now"})
                self.assertFalse(result["release_ready"])
                self.assertEqual(result["capabilities"][0]["stage"], "partial")
                self.assertEqual(result["capabilities"][0]["verification"], expected)
            old = self.report(); old.pop("source")
            result = build_report(root, self.manifest(), [("old", old)], {"sha256": "now"})
            self.assertEqual(result["reports"][0]["freshness"], "UNKNOWN")

    def test_readiness_latest_failure_wins_and_missing_is_visible(self):
        with tempfile.TemporaryDirectory() as d:
            reports = [("pass", self.report(finished_at="2026-01-01")),
                       ("fail", self.report(status="FAILED", finished_at="2026-01-02"))]
            root = Path(d)
            result = build_report(root, self.manifest(), list(reversed(reports)), {"sha256": "now"})
            self.assertEqual(result["capabilities"][0]["verification"], "FAILED")
            self.assertEqual(build_report(root, self.manifest(), [], {"sha256": "now"})["capabilities"][0]["verification"], "NOT VERIFIED")
            manifest = self.manifest(); manifest["capabilities"][0]["stage"] = "complete"
            with self.assertRaises(ValueError): validate_manifest(root, manifest)

    def test_direct_calls_repeats_indirect_bounds_aliases(self):
        symbols = [Symbol(0x100, 0x20, "T", "caller"), Symbol(0x100, 0x10, "T", "alias"),
                   Symbol(0x200, 0x10, "T", "target")]
        lines = [" 100: call 200 <target>", " 105: callq 200 <target>", " 10a: call *%rax",
                 " 10d: call *0x200(%rip) # 200 <target>", " 110: jmp 200 <target>",
                 " 120: call 200 <target>", " 115: call 300 <external@plt>"]
        rows, metadata = parse_calls(lines, symbols)
        self.assertEqual([r["callsite_address"] for r in rows], ["00000100", "00000105", "00000115"])
        self.assertEqual(rows[0]["caller_symbol"], "caller")
        self.assertEqual(len(metadata["indirect_calls"]), 2)
        self.assertEqual(metadata["unattributed_calls"], 1)

    def test_export_rejects_wrong_original_before_output(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d); game = root / "game"; game.mkdir()
            binary = game / "Torchlight.bin.x86_64"; binary.write_bytes(b"not supported")
            output = root / "calls.tsv"
            result = subprocess.run([sys.executable, str(ROOT / "tools/export_callsites.py"),
                                     "--original", str(binary), "--out", str(output)],
                                    text=True, capture_output=True, timeout=10)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn("Unsupported original build", result.stderr)
            self.assertFalse(output.exists())
            self.assertEqual(binary.read_bytes(), b"not supported")

    def test_project_capability_manifest(self):
        validate_manifest(ROOT, json.loads((ROOT / "research/capabilities.json").read_text()))


if __name__ == "__main__":
    unittest.main()
