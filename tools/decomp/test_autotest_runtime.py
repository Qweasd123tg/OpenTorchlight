from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import autotest
import publication


class Runtime(unittest.TestCase):
    def test_runtime_does_not_remove_or_rewrite_selected_fixtures(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            fixture = root / "auto_100.cpp"
            fixture.write_text("selected comparison")
            runtime = autotest.write_runtime(root)
            self.assertIn("Outcome g_outcomes[2]", runtime.read_text())
            self.assertEqual("selected comparison", fixture.read_text())
            stamp = runtime.stat().st_mtime_ns
            self.assertEqual(runtime, autotest.write_runtime(root))
            self.assertEqual(stamp, runtime.stat().st_mtime_ns)

    def test_default_runtime_uses_current_stage_output_path(self):
        with tempfile.TemporaryDirectory() as tmp:
            with patch.object(autotest, "OUT", Path(tmp)):
                self.assertEqual(Path(tmp) / "AutoTestRuntime.cpp", autotest.write_runtime())

    def test_final_validation_prepares_runtime_before_fixture_fingerprint(self):
        with tempfile.TemporaryDirectory() as tmp:
            stage = publication.Stage.__new__(publication.Stage)
            stage.path = Path(tmp)
            def fingerprint():
                path = stage.path / "build-decomp/hybrid/autotests/AutoTestRuntime.cpp"
                self.assertTrue(path.exists())
                raise RuntimeError("stop after checking ordering")
            with patch.object(stage, "_generated_tests_state", side_effect=fingerprint):
                with self.assertRaisesRegex(RuntimeError, "checking ordering"):
                    stage.validate()


if __name__ == "__main__":
    unittest.main()
