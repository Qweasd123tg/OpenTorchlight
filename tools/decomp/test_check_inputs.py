import contextlib
import io
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import check
import evidence


class InputDiagnostics(unittest.TestCase):
    def manifests(self):
        return ({"schema": 1, "files": [["decomp/src/unit.cpp", "old"]],
                 "context": {"database_digest": "old"}},
                {"schema": 1, "files": [["decomp/src/unit.cpp", "new"]],
                 "context": {"database_digest": "new"}})

    def test_unchanged_manifest_does_not_write_diagnostics(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            before, _ = self.manifests()
            with patch.object(check, "ROOT", root):
                self.assertTrue(check.unchanged_inputs(before, before, "changed inputs"))
            self.assertFalse((root / "build-decomp").exists())

    def test_initial_manifest_survives_interrupted_comparison(self):
        for no_game in (False, True):
            with self.subTest(no_game=no_game), tempfile.TemporaryDirectory() as folder:
                root = Path(folder)
                before, _ = self.manifests()
                db = {"tus": [], "functions": {}}

                def interrupted(*args, **kwargs):
                    saved = root / "build-decomp/check-inputs-before.json"
                    self.assertEqual(before, json.loads(saved.read_text()))
                    raise RuntimeError("synthetic interruption")

                argv = ["check.py"] + (["--no-game"] if no_game else [])
                with patch.object(check, "ROOT", root), patch.object(check, "ensure_db", return_value=db), \
                        patch.object(check, "ensure_types"), \
                        patch.object(check.acceptance, "load_comparisons", return_value={"0x1": {}}), \
                        patch.object(evidence, "input_manifest", return_value=before), \
                        patch.object(check.objdiff, "Original"), \
                        patch.object(check.toolchain, "parallel_map", side_effect=interrupted), \
                        patch("sys.argv", argv):
                    with self.assertRaisesRegex(RuntimeError, "synthetic interruption"):
                        check.main()
                self.assertFalse((root / "build-decomp/check-inputs-after.json").exists())

    def test_full_and_no_game_guards_save_manifests_without_accepting(self):
        for no_game in (False, True):
            with self.subTest(no_game=no_game), tempfile.TemporaryDirectory() as folder:
                root = Path(folder)
                output = root / "progress.json"
                before, after = self.manifests()
                db = {"original_elf_sha256": "original", "tus": [{"id": 1, "kind": "game"}],
                      "functions": {"0x1": {"address": "0x1", "tu": 1, "kind": "function", "size": 1}}}
                units = [{"source": "unit.cpp", "functions": [
                    {"address": "0x1", "status": "DIFF", "original_size": 1}]}]
                text = io.StringIO()
                argv = ["check.py", "--json", str(output)] + (["--no-game"] if no_game else [])
                patches = [patch.object(check, "ROOT", root), patch.object(check, "ensure_db", return_value=db),
                           patch.object(check, "ensure_types"),
                           patch.object(check.acceptance, "load_comparisons", return_value={"0x1": {}}),
                           patch.object(check.objdiff, "Original"), patch.object(check.objdiff, "save_norm_cache"),
                           patch.object(check.objdiff, "report"),
                           patch.object(check.toolchain, "parallel_map", return_value=units),
                           patch.object(check, "generated_tests", return_value=[]),
                           patch.object(check.hybrid, "TESTS", root / "tests"),
                           patch.object(check.hybrid, "build", return_value=("blob", "loader")),
                           patch.object(check.hybrid, "selftest", return_value=(0, [])),
                           patch.object(check, "shadow_covered", return_value=set()),
                           patch.object(check, "shadow_declared", return_value=set()),
                           patch.dict(check.os.environ, {"OTL_SELFTEST_SHARDS": "1"}),
                           patch("sys.argv", argv), contextlib.redirect_stdout(text)]
                with contextlib.ExitStack() as stack:
                    for item in patches:
                        stack.enter_context(item)
                    snapshot = stack.enter_context(patch.object(evidence, "input_manifest", side_effect=[before, after]))
                    accept = stack.enter_context(patch.object(check.acceptance, "comparison_bindings"))
                    self.assertEqual(2, check.main())
                    self.assertEqual(2, snapshot.call_count)
                    accept.assert_not_called()
                self.assertFalse(output.exists())
                self.assertEqual(before, json.loads((root / "build-decomp/check-inputs-before.json").read_text()))
                self.assertEqual(after, json.loads((root / "build-decomp/check-inputs-after.json").read_text()))
                self.assertIn("changed (1): decomp/src/unit.cpp", text.getvalue())
                self.assertIn("context.database_digest", text.getvalue())

    def test_failure_to_save_before_still_attempts_after_and_fails_closed(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            before, after = self.manifests()
            write_text = Path.write_text

            def write(path, *args, **kwargs):
                if "before" in path.name:
                    raise OSError("synthetic write failure")
                return write_text(path, *args, **kwargs)

            text = io.StringIO()
            with patch.object(check, "ROOT", root), patch.object(Path, "write_text", write), \
                    contextlib.redirect_stdout(text):
                self.assertFalse(check.unchanged_inputs(before, after, "changed inputs"))
            self.assertEqual(after, json.loads((root / "build-decomp/check-inputs-after.json").read_text()))
            self.assertIn("cannot save before input manifest: synthetic write failure", text.getvalue())


if __name__ == "__main__":
    unittest.main()
