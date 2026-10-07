from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import check


class Prepare(unittest.TestCase):
    def test_existing_types_do_not_start_exporter(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "build-decomp").mkdir()
            (root / "build-decomp/types.json").write_text("{}")
            with patch.object(check, "ROOT", root), patch.object(check.subprocess, "run") as run:
                check.ensure_types()
                run.assert_not_called()

    def test_fresh_worktree_exports_before_fingerprinting(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            def export(*args, **kwargs):
                (root / "build-decomp").mkdir(exist_ok=True)
                (root / "build-decomp/types.json").write_text("{}")
            with patch.object(check, "ROOT", root), patch.object(check.subprocess, "run", side_effect=export) as run:
                check.ensure_types()
                self.assertTrue(run.call_args.kwargs["check"])
                self.assertTrue(run.call_args.args[0][1].endswith("tools/decomp/types_export.py"))

    def test_exporter_without_output_is_not_ready(self):
        with tempfile.TemporaryDirectory() as tmp:
            with patch.object(check, "ROOT", Path(tmp)), patch.object(check.subprocess, "run"):
                with self.assertRaisesRegex(SystemExit, "did not create"):
                    check.ensure_types()


if __name__ == "__main__":
    unittest.main()
