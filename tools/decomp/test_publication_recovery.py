"""Publication recovers process exits and revalidates complete staged inputs."""
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

import hybrid
import objdiff
import publication
import toolchain

_REAL_VERIFY_PUBLISHED = publication.Stage._verify_published_objects
FIXTURE_DB = {"original_elf_sha256": "0" * 64, "functions": {"0x100": {}, "0x200": {}}}


def fixture(folder):
    root = Path(folder)
    for name in ("src", "include", "hybrid/tests"):
        (root / "decomp" / name).mkdir(parents=True, exist_ok=True)
    for name, data in {"src/A.cpp": "old A", "src/B.cpp": "old B",
                       "include/Shared.h": "7", "hybrid/tests/Control.cpp": "old test",
                       "hybrid/Runtime.h": "old runtime", "config.json": "{}",
                       "autotests.json": "{}"}.items():
        (root / "decomp" / name).write_text(data)
    return root


class SyntheticStage(unittest.TestCase):
    def setUp(self):
        digest = patch.object(publication.Stage, "_input_digest", return_value="fixture-inputs")
        digest.start()
        self.addCleanup(digest.stop)
        objects = patch.object(publication.Stage, "_verify_published_objects", return_value=None)
        objects.start()
        self.addCleanup(objects.stop)

    def mark(self, stage):
        stage.validated = publication.tree_state(stage.path)
        stage.validated_inputs = "fixture-inputs"


class Recovery(SyntheticStage):
    def crash(self, root, point):
        program = '''
import os, sys
from pathlib import Path
sys.path.insert(0, sys.argv[1])
import publication as p
p.Stage._input_digest = lambda self: "fixture-inputs"
p.Stage._verify_published_objects = lambda self: None
stage = p.Stage(Path(sys.argv[2]))
(stage.path / "decomp/src/A.cpp").write_text("new A")
(stage.path / "decomp/include/Shared.h").write_text("99")
(stage.path / "decomp/hybrid/tests/New.cpp").write_text("new test")
(stage.path / "decomp/src/B.cpp").unlink()
stage.validated = p.tree_state(stage.path)
stage.validated_inputs = "fixture-inputs"
point = sys.argv[3]
replace = stage._replace
count = 0
def stop(name, data):
    global count
    if point == "before":
        os._exit(77)
    replace(name, data)
    count += 1
    if point == "first" or (point == "last" and count == 4):
        os._exit(77)
stage._replace = stop
write = p._write_file
def marker(path, data):
    write(path, data)
    if point == "committed" and path.name == "committed":
        os._exit(77)
p._write_file = marker
stage.publish()
'''
        result = subprocess.run([sys.executable, "-c", program, str(Path(publication.__file__).parent),
                                 str(root), point], capture_output=True, text=True, timeout=20)
        self.assertEqual(77, result.returncode, result.stderr)

    def test_reader_recovers_before_first_partial_and_last_write(self):
        for point in ("before", "first", "last"):
            with self.subTest(point=point), tempfile.TemporaryDirectory() as folder:
                root = fixture(folder)
                before = publication.tree_state(root)
                self.crash(root, point)
                self.assertTrue(publication._journal(root).exists())
                with publication.tree_lock(root):
                    self.assertEqual(before, publication.tree_state(root))
                self.assertFalse(publication._journal(root).exists())
                # A second reader sees the same recovered version.
                self.assertEqual(before, publication.Stage(root).baseline)

    def test_committed_marker_keeps_complete_new_version(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            self.crash(root, "committed")
            with publication.tree_lock(root):
                self.assertEqual("new A", (root / "decomp/src/A.cpp").read_text())
                self.assertEqual("99", (root / "decomp/include/Shared.h").read_text())
                self.assertTrue((root / "decomp/hybrid/tests/New.cpp").is_file())
                self.assertFalse((root / "decomp/src/B.cpp").exists())
            self.assertFalse(publication._journal(root).exists())

    def test_corrupt_backup_blocks_reader(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            self.crash(root, "first")
            journal = publication._journal(root)
            manifest = json.loads((journal / "manifest.json").read_text())
            backup = next(row["backup"] for row in manifest["files"] if row["backup"])
            (journal / backup).write_bytes(b"damaged")
            with self.assertRaisesRegex(RuntimeError, "damaged publication backup"):
                with publication.tree_lock(root):
                    self.fail("mixed tree exposed")


class ValidationInputs(SyntheticStage):
    def test_external_inputs_changed_after_validation_block_publication(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            stage = publication.Stage(root)
            (stage.path / "decomp/src/A.cpp").write_text("new A")
            self.mark(stage)
            before = publication.tree_state(root)
            with patch.object(stage, "_input_digest", return_value="new compiler or runtime"):
                with self.assertRaisesRegex(RuntimeError, "build inputs changed after validation"):
                    stage.publish()
            self.assertEqual(before, publication.tree_state(root))

    def test_process_exit_validation_cannot_be_restored_by_tree_stamp_alone(self):
        with tempfile.TemporaryDirectory() as folder:
            stage = publication.Stage(fixture(folder))
            stage.validated = publication.tree_state(stage.path)
            with self.assertRaisesRegex(RuntimeError, "complete build inputs"):
                stage.publish()

    def test_tests_runtime_configuration_and_registry_invalidate_validation(self):
        for name in ("hybrid/tests/Control.cpp", "hybrid/tests/New.cpp", "hybrid/Runtime.h",
                     "config.json", "autotests.json"):
            with self.subTest(name=name), tempfile.TemporaryDirectory() as folder:
                stage = publication.Stage(fixture(folder))
                self.mark(stage)
                (stage.path / "decomp" / name).write_text("changed input")
                with self.assertRaisesRegex(RuntimeError, "requires validation"):
                    stage.publish()

    def test_validated_test_and_config_changes_are_published_together(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            stage = publication.Stage(root)
            for name in ("hybrid/tests/New.cpp", "hybrid/Runtime.h", "config.json", "autotests.json"):
                (stage.path / "decomp" / name).write_text("validated input")
            self.mark(stage)
            changed = stage.publish()
            self.assertIn("decomp/hybrid/tests/New.cpp", changed)
            for name in changed:
                self.assertEqual((stage.path / name).read_bytes(), (root / name).read_bytes())

    def test_changed_tools_are_detected_and_cannot_be_published(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            (root / "tools/decomp").mkdir(parents=True)
            (root / "tools/decomp/Logic.py").write_text("old tool")
            stage = publication.Stage(root)
            (stage.path / "tools/decomp/Logic.py").write_text("new tool")
            self.mark(stage)
            with self.assertRaisesRegex(RuntimeError, "only supports decomp"):
                stage.publish()

    def test_activate_compiles_staged_configuration_and_runtime(self):
        with tempfile.TemporaryDirectory() as folder:
            stage = publication.Stage(fixture(folder))
            old = toolchain.CONFIG, hybrid.HYBRID
            with stage.activate():
                self.assertEqual(stage.path / "decomp/config.json", toolchain.CONFIG)
                self.assertEqual(stage.path / "decomp/hybrid", hybrid.HYBRID)
                self.assertEqual(stage.root / "build-decomp/shared-cc-cache", toolchain.SHARED_CC_CACHE)
            self.assertEqual(old, (toolchain.CONFIG, hybrid.HYBRID))

    def test_staged_digest_sees_actual_read_only_library_inputs(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            library = root / "third_party/sdk"
            library.mkdir(parents=True)
            header = library / "Sdk.h"
            header.write_text("library input")
            stage = publication.Stage(root)
            self.assertTrue((stage.path / "third_party").is_symlink())
            from evidence import directory_inputs
            inputs = directory_inputs("third_party", stage.path / "third_party", {".h"})
            self.assertEqual(["third_party/sdk/Sdk.h"], [name for name, _ in inputs])
            self.assertEqual(header.read_bytes(), inputs[0][1].read_bytes())
            self.assertNotIn("third_party/sdk/Sdk.h", publication.tree_state(stage.path))


class Preservation(SyntheticStage):
    def validate(self, stage, compare, covered=(), selftest=None):
        with patch.object(objdiff, "Original", return_value=SimpleNamespace(db=FIXTURE_DB)), \
                patch.object(objdiff, "compare_source", side_effect=compare), \
                patch.object(toolchain, "parallel_map", side_effect=lambda fn, items: [fn(item) for item in items]), \
                patch.object(hybrid, "build", return_value=(Path("blob"), Path("loader"))), \
                patch.object(hybrid, "selftest", side_effect=selftest,
                             return_value=(0, ["tlhybrid: control PASS (0)"])):
            return stage.validate(coverage_provider=lambda *_: set(covered))

    def test_edit_during_selftest_cannot_rebind_earlier_pass(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            stage = publication.Stage(root)
            def edit(*_args):
                (stage.path / "decomp/hybrid/tests/Control.cpp").write_text("untested new fixture")
                return 0, ["tlhybrid: control PASS (0)"]
            with self.assertRaisesRegex(RuntimeError, "validation inputs changed"):
                self.validate(stage, self.comparator(root), covered=("0x100", "0x200"), selftest=edit)
            self.assertIsNone(stage.validated)

    def test_external_edit_during_validation_invalidates_earlier_pass(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            stage = publication.Stage(root)
            with patch.object(stage, "_input_digest", side_effect=("first inputs", "changed inputs")):
                with self.assertRaisesRegex(RuntimeError, "external validation inputs changed"):
                    self.validate(stage, self.comparator(root))
            self.assertIsNone(stage.validated)

    def comparator(self, root, old_status="MATCH", same_object=False):
        def compare(source, *_args, **_kwargs):
            value = (source.parent.parent / "include/Shared.h").read_text()
            status = old_status if value == "7" else "DIFF"
            address = "0x100" if source.name == "A.cpp" else "0x200"
            return {"functions": [{"address": address, "status": status}], "unknown": [],
                    "object_digest": "same-object" if same_object else value}
        return compare

    def test_header_cannot_silently_remove_neighbour_match(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            stage = publication.Stage(root)
            (stage.path / "decomp/include/Shared.h").write_text("99")
            with self.assertRaisesRegex(RuntimeError, "previous MATCH lost"):
                self.validate(stage, self.comparator(root))
            self.assertIsNone(stage.validated)

    def test_fresh_final_behavioral_comparisons_can_restore_previous_match(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            stage = publication.Stage(root)
            (stage.path / "decomp/include/Shared.h").write_text("99")
            self.validate(stage, self.comparator(root), covered=("0x100", "0x200"))
            self.assertEqual({"0x100", "0x200"}, stage.covered)
            stage.publish()

    def test_existing_definition_cannot_disappear(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            stage = publication.Stage(root)
            (stage.path / "decomp/src/B.cpp").unlink()
            with self.assertRaisesRegex(RuntimeError, "definition disappeared"):
                self.validate(stage, self.comparator(root))

    def test_added_test_does_not_accept_or_block_unchanged_unknown_neighbour(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            stage = publication.Stage(root)
            (stage.path / "decomp/hybrid/tests/New.cpp").write_text("new actual comparison fixture")
            (stage.path / "decomp/autotests.json").write_text('{"new": "test registration"}')
            self.validate(stage, self.comparator(root, old_status="DIFF"))
            self.assertEqual(set(), stage.covered)
            self.assertTrue(all(row["status"] == "DIFF" for unit in stage.final_units for row in unit["functions"]))

    def prior_receipt(self, root, address):
        progress = root / "build-decomp/progress.json"
        progress.parent.mkdir(parents=True, exist_ok=True)
        progress.write_text(json.dumps({"comparison_evidence": {address: {
            "policy": 1, "method": "executed-call-pair", "original_elf_sha256": FIXTURE_DB["original_elf_sha256"],
            "evidence": {"schema": 1, "object_digest": "old complete object", "inputs_digest": "old complete inputs",
                         "parameters": {"fixtures": ["real_compared_fixture"]}}}}}))

    def test_previously_compared_diff_requires_fresh_receipt_after_test_changes(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            self.prior_receipt(root, "0x200")
            stage = publication.Stage(root)
            (stage.path / "decomp/hybrid/tests/New.cpp").write_text("new fixture")
            with self.assertRaisesRegex(RuntimeError, "previous behavioral acceptance lost"):
                self.validate(stage, self.comparator(root, old_status="DIFF"))
            self.assertIsNone(stage.validated)
            self.validate(stage, self.comparator(root, old_status="DIFF"), covered=("0x200",))
            self.assertEqual({"0x200"}, stage.covered)

    def test_newly_recorded_prior_receipt_is_checked_again_before_publication(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            stage = publication.Stage(root)
            (stage.path / "decomp/hybrid/tests/New.cpp").write_text("new fixture")
            self.validate(stage, self.comparator(root, old_status="DIFF"))
            self.prior_receipt(root, "0x200")
            with self.assertRaisesRegex(RuntimeError, "previous behavioral acceptance lost"):
                stage.publish()
            self.assertFalse((root / "decomp/hybrid/tests/New.cpp").exists())

    def test_unchanged_existing_diff_is_allowed(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            stage = publication.Stage(root)
            self.validate(stage, self.comparator(root, old_status="DIFF"))

    def test_equal_unknown_instructions_do_not_preserve_changed_environment(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            stage = publication.Stage(root)
            (stage.path / "decomp/include/Shared.h").write_text("99")
            with self.assertRaisesRegex(RuntimeError, "existing DIFF changed"):
                self.validate(stage, self.comparator(root, old_status="DIFF", same_object=True))


class Rebase(SyntheticStage):
    def test_attempt_can_resume_after_process_exit_and_rebase_without_generation(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            saved = publication.Stage(root)
            (saved.path / "decomp/src/B.cpp").write_text("saved candidate")
            self.mark(saved)
            (root / "decomp/src/A.cpp").write_text("fresh A")
            resumed = publication.Stage.resume(saved.path)
            self.assertIsNone(resumed.validated)
            resumed.rebase()
            self.assertEqual("saved candidate", (resumed.path / "decomp/src/B.cpp").read_text())
            self.assertEqual("fresh A", (resumed.path / "decomp/src/A.cpp").read_text())
            self.assertEqual(publication.tree_state(root), publication.Stage.resume(resumed.path).baseline)

    def test_independent_candidate_is_saved_and_revalidation_required(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            first, second = publication.Stage(root), publication.Stage(root)
            (first.path / "decomp/src/A.cpp").write_text("new A")
            (second.path / "decomp/src/B.cpp").write_text("new B")
            self.mark(first)
            self.mark(second)
            first.publish()
            with self.assertRaisesRegex(RuntimeError, "changed during"):
                second.publish()
            self.assertEqual(["decomp/src/B.cpp"], second.rebase())
            self.assertEqual("new A", (second.path / "decomp/src/A.cpp").read_text())
            self.assertEqual("new B", (second.path / "decomp/src/B.cpp").read_text())
            with self.assertRaisesRegex(RuntimeError, "requires validation"):
                second.publish()
            self.mark(second)
            self.assertEqual(["decomp/src/B.cpp"], second.publish())

    def test_conflict_rejects_without_losing_candidate(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            stage = publication.Stage(root)
            (stage.path / "decomp/src/A.cpp").write_text("candidate A")
            (root / "decomp/src/A.cpp").write_text("another A")
            with self.assertRaisesRegex(RuntimeError, "rebase conflicts"):
                stage.rebase()
            self.assertEqual("candidate A", (stage.path / "decomp/src/A.cpp").read_text())


class PublishedObjects(SyntheticStage):
    def test_verification_failure_rolls_back_before_commit_marker(self):
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            stage = publication.Stage(root)
            before = publication.tree_state(root)
            (stage.path / "decomp/src/A.cpp").write_text("new A")
            self.mark(stage)
            with patch.object(stage, "_verify_published_objects", side_effect=RuntimeError("published object differs")):
                with self.assertRaisesRegex(RuntimeError, "published object differs"):
                    stage.publish()
            self.assertEqual(before, publication.tree_state(root))
            self.assertFalse(publication._journal(root).exists())

    @unittest.skipUnless((toolchain.cache_dir() / "gcc447/.complete.json").exists(), "requires pinned GCC 4.4.7")
    def test_real_file_macro_cannot_transfer_stage_object_proof_to_live_path(self):
        """Real native object bytes; comparison decision/headless suite are fixture boundaries."""
        with tempfile.TemporaryDirectory() as folder:
            root = fixture(folder)
            (root / "decomp/config.json").write_text(json.dumps({"cflags": ["-O2"], "include": ["decomp/include"]}))
            (root / "decomp/src/A.cpp").write_text('extern "C" const char* where(){return "old";}\n')
            (root / "decomp/src/B.cpp").write_text('extern "C" int keep(){return 7;}\n')
            before = publication.tree_state(root)
            stage = publication.Stage(root)
            (stage.path / "decomp/src/A.cpp").write_text('extern "C" const char* where(){return __FILE__;}\n')
            objects = []
            def compare(source, *_args, **_kwargs):
                with tempfile.TemporaryDirectory(prefix="otl-published-object-") as work:
                    obj = toolchain.compile_source(source, Path(work) / "unit.o", quiet=True)
                    digest = toolchain.sha256(obj)
                objects.append((str(source), digest))
                return {"functions": [{"address": "0x100" if source.name == "A.cpp" else "0x200", "status": "MATCH"}],
                        "unknown": [], "object_digest": digest}
            with patch.object(objdiff, "Original", return_value=SimpleNamespace(db=FIXTURE_DB)), \
                    patch.object(objdiff, "compare_source", side_effect=compare), \
                    patch.object(toolchain, "parallel_map", side_effect=lambda fn, items: [fn(item) for item in items]), \
                    patch.object(hybrid, "build", return_value=(Path("blob"), Path("loader"))), \
                    patch.object(hybrid, "selftest", return_value=(0, ["tlhybrid: control PASS (0)"])), \
                    patch.object(stage, "_verify_published_objects", side_effect=lambda: _REAL_VERIFY_PUBLISHED(stage)):
                stage.validate(coverage_provider=lambda *_: set())
                with self.assertRaisesRegex(RuntimeError, "published object differs.*decomp/src/A.cpp"):
                    stage.publish()
            self.assertEqual(before, publication.tree_state(root))
            self.assertFalse(publication._journal(root).exists())
            stage_object = next(digest for source, digest in objects if source == str(stage.path / "decomp/src/A.cpp"))
            live_object = [digest for source, digest in objects if source == str(root / "decomp/src/A.cpp")][-1]
            self.assertNotEqual(stage_object, live_object)


if __name__ == "__main__":
    unittest.main()
