"""Final publication checks all emitted variants, not just the requested body."""
from contextlib import nullcontext
import json
from pathlib import Path
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

import hybrid
import objdiff
import publication
import toolchain


def row(address, status="MATCH", weak=False, name=None):
    return {"address": address, "status": status, "weak": weak,
            "name": name or "function_" + address}


class Definitions(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory(prefix="publication-definitions-", dir="/tmp/opencode")
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        for name in ("src", "include", "hybrid/tests"):
            (self.root / "decomp" / name).mkdir(parents=True)
        for name in ("A.cpp", "B.cpp"):
            (self.root / "decomp/src" / name).write_text("baseline")
        (self.root / "decomp/hybrid/tests/Control.cpp").write_text("control")
        (self.root / "decomp/config.json").write_text("{}")
        self.stage = publication.Stage(self.root)
        self.db = {"classes": {"CUnit": {}}, "original_elf_sha256": "0" * 64,
                   "functions": {a: {"names": [n], "kind": k} for a, n, k in (
                       ("0x100", "keep", "function"),
                       ("0x200", "_ZN5CUnitC1Ev", "ctor"),
                       ("0x201", "_ZN5CUnitC2Ev", "ctor"),
                       ("0x202", "_ZN5CUnitD0Ev", "dtor"),
                       ("0x203", "_ZN5CUnitD1Ev", "dtor"),
                       ("0x300", "_GLOBAL__I_keep", "compiler"))}}
        self.before = {"A.cpp": [row("0x100")], "B.cpp": []}
        self.after = {name: list(rows) for name, rows in self.before.items()}
        self.report = ["tlhybrid: control PASS (0)"]
        self.old_object, self.new_object = "old-object", "old-object"
        self.built_tests = []
        for target, attribute, value in (
                (publication.Stage, "_input_digest", lambda *_: "fixture-inputs"),
                (publication.Stage, "_verify_published_objects", lambda *_: None),
                (publication.Stage, "activate", lambda stage: nullcontext(stage)),
                (objdiff, "Original", lambda: SimpleNamespace(db=self.db)),
                (objdiff, "compare_source", self.compare),
                (toolchain, "parallel_map", lambda fn, items: [fn(p) for p in items]),
                (hybrid, "build", self.build),
                (hybrid, "selftest", lambda *_: (0, self.report))):
            mocked = patch.object(target, attribute, value)
            mocked.start()
            self.addCleanup(mocked.stop)

    def compare(self, source, *_args, **_kwargs):
        staged = source.is_relative_to(self.stage.path)
        return {"source": str(source), "tu": source.name,
                "functions": (self.after if staged else self.before)[source.name],
                "object_digest": self.new_object if staged else self.old_object, "unknown": []}

    def build(self, **kwargs):
        self.built_tests = kwargs["tests"]
        return Path("blob"), Path("loader")

    def validate(self):
        return self.stage.validate(baseline_covered=())

    def coverage(self, address="0x200"):
        return ["tlhybrid: auto_200 PASS (0)",
                "    coverage auto_200 " + address + " completed 100 different 0 incomplete 0"]

    def generated_fixture(self):
        path = self.stage.path / "build-decomp/hybrid/autotests/auto_200.cpp"
        path.parent.mkdir(parents=True)
        path.write_text("generated comparison")
        return path

    def test_new_strong_or_weak_diff_in_either_tu_is_rejected(self):
        for owner in ("A.cpp", "B.cpp"):
            for weak in (False, True):
                with self.subTest(owner=owner, weak=weak):
                    self.after = {n: list(rows) for n, rows in self.before.items()}
                    self.after[owner] += [row("0x200"), row("0x201", "DIFF", weak)]
                    with self.assertRaisesRegex(RuntimeError, "new definition lacks MATCH"):
                        self.validate()
                    self.assertIsNone(self.stage.validated)

    def test_one_variant_receipt_does_not_cover_another(self):
        for address in ("0x201", "0x202", "0x203"):
            with self.subTest(address=address):
                self.after["B.cpp"] = [row("0x200", "DIFF"), row(address, "DIFF", True)]
                self.report = self.coverage()
                with self.assertRaisesRegex(RuntimeError, "new definition lacks MATCH.*" + address):
                    self.validate()

    def test_all_new_variants_matching_are_allowed(self):
        self.after["B.cpp"] = [row(a, weak=True) for a in ("0x200", "0x201", "0x202", "0x203")]
        self.validate()

    def test_existing_weak_match_cannot_disappear_or_change(self):
        self.before["A.cpp"] = [row("0x100", weak=True)]
        self.after["A.cpp"] = []
        with self.assertRaisesRegex(RuntimeError, "definition disappeared"):
            self.validate()
        self.after["A.cpp"] = [row("0x100", "DIFF", weak=True)]
        with self.assertRaisesRegex(RuntimeError, "previous MATCH lost"):
            self.validate()

    def test_existing_weak_unknown_diff_requires_unchanged_object(self):
        self.before["A.cpp"] = [row("0x100", "DIFF", weak=True)]
        self.after["A.cpp"] = list(self.before["A.cpp"])
        self.validate()
        self.new_object = "changed-object"
        with self.assertRaisesRegex(RuntimeError, "existing DIFF changed"):
            self.validate()

    def test_duplicate_rows_cannot_hide_diff_behind_match(self):
        self.after["B.cpp"] = [row("0x200", "DIFF", True), row("0x200")]
        with self.assertRaisesRegex(RuntimeError, "new definition lacks MATCH"):
            self.validate()

    def test_new_definition_in_another_tu_cannot_reuse_unchanged_baseline_diff(self):
        self.before["A.cpp"] = [row("0x100", "DIFF")]
        self.after["A.cpp"] = list(self.before["A.cpp"])
        self.after["B.cpp"] = [row("0x100", "DIFF", True)]
        with self.assertRaisesRegex(RuntimeError, "new definition lacks MATCH"):
            self.validate()

    def test_compiler_originals_are_excluded_consistently_with_hybrid(self):
        self.before["A.cpp"] += [row("0x300", "DIFF")]
        self.after["B.cpp"] = [row("0x300", "DIFF", True)]
        self.validate()

    def test_extra_helpers_are_narrowly_allowed(self):
        for name in ("_GLOBAL__I_keep", "__tcf_10",
                     "_Z41__static_initialization_and_destruction_0ii.clone.0",
                     "_ZNSt6vectorIiSaIiEE9push_backERKi", "_ZN9__gnu_cxx12__normal_iteratorIPiEppEv"):
            self.after["B.cpp"] = [{"name": name, "status": "EXTRA"}]
            self.validate()

    def test_invented_defined_game_member_and_plain_extra_are_rejected(self):
        for name, error in (("_ZN5CUnit8inventedEv", "invented game definition"),
                            ("injected_helper", "unsupported extra definition"),
                            ("_ZSt8inventedv", "unsupported extra definition")):
            self.after["B.cpp"] = [{"name": name, "status": "EXTRA"}]
            with self.assertRaisesRegex(RuntimeError, error):
                self.validate()

    def test_existing_nonallowlisted_extra_is_preserved_only_with_same_object(self):
        extra = {"name": "legacy_helper", "status": "EXTRA"}
        self.before["B.cpp"] = [extra]
        self.after["B.cpp"] = [extra]
        self.validate()
        self.new_object = "changed-object"
        with self.assertRaisesRegex(RuntimeError, "unsupported extra definition"):
            self.validate()

    def test_publish_runs_definition_gate_again(self):
        self.after["B.cpp"] = [row("0x200")]
        self.validate()
        self.stage.final_units[1]["functions"] = [row("0x200", "DIFF", True)]
        with self.assertRaisesRegex(RuntimeError, "new definition lacks MATCH"):
            self.stage.publish()

    def test_generated_fixture_has_fresh_coverage_and_is_in_final_build(self):
        fixture = self.generated_fixture()
        self.after["B.cpp"] = [row("0x200", "DIFF", True)]
        self.report = self.coverage()
        self.validate()
        self.assertIn(fixture, self.built_tests)
        self.assertEqual({"0x200"}, self.stage.covered)
        self.stage.publish()

    def test_old_stats_or_failed_fixture_are_not_coverage(self):
        self.generated_fixture()
        self.after["B.cpp"] = [row("0x200", "DIFF")]
        for report in (["tlhybrid: auto_200 PASS (0)",
                        "    stats auto_200 same 100 both-failed 0 different 0 incomplete 0"],
                       [self.coverage()[1]],
                       [self.coverage()[0], self.coverage()[1].replace("incomplete 0", "incomplete 1")]):
            self.report = report
            with self.assertRaisesRegex(RuntimeError, "new definition lacks MATCH"):
                self.validate()

    def test_generated_fixture_mutation_during_validation_is_rejected(self):
        fixture = self.generated_fixture()
        def mutate(*_):
            fixture.write_text("untested replacement")
            return 0, self.report
        with patch.object(hybrid, "selftest", side_effect=mutate):
            with self.assertRaisesRegex(RuntimeError, "fixtures changed during validation"):
                self.validate()

    def test_generated_fixture_mutation_after_validation_is_rejected(self):
        fixture = self.generated_fixture()
        self.validate()
        fixture.write_text("untested replacement")
        with self.assertRaisesRegex(RuntimeError, "fixtures changed after validation"):
            self.stage.publish()

    def test_generated_fixture_mutation_during_publish_rolls_back(self):
        fixture = self.generated_fixture()
        target = self.stage.path / "decomp/src/B.cpp"
        target.write_text("candidate")
        self.after["B.cpp"] = [row("0x200")]
        self.validate()
        before = publication.tree_state(self.root)
        with patch.object(self.stage, "_verify_published_objects",
                          side_effect=lambda: fixture.write_text("untested replacement")):
            with self.assertRaisesRegex(RuntimeError, "fixtures changed during publication"):
                self.stage.publish()
        self.assertEqual(before, publication.tree_state(self.root))

    def test_resume_loses_validation_and_rejects_root_or_path_mismatch(self):
        self.validate()
        resumed = publication.Stage.resume(self.stage.path, self.root)
        self.assertIsNone(resumed.validated)
        self.assertIsNone(resumed.validated_inputs)
        with self.assertRaisesRegex(RuntimeError, "root mismatch"):
            publication.Stage.resume(self.stage.path, self.root / "other")
        outside = self.root / "outside"
        outside.mkdir()
        (outside / "stage.json").write_bytes((self.stage.path / "stage.json").read_bytes())
        with self.assertRaisesRegex(RuntimeError, "must be inside"):
            publication.Stage.resume(outside)

    def test_resume_rejects_baseline_traversal(self):
        path = self.stage.path / "stage.json"
        data = json.loads(path.read_text())
        data["baseline"]["decomp/../../victim"] = "0" * 64
        path.write_text(json.dumps(data))
        with self.assertRaisesRegex(RuntimeError, "invalid saved Stage baseline"):
            publication.Stage.resume(self.stage.path)


if __name__ == "__main__":
    unittest.main()
