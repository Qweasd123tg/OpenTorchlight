#!/usr/bin/env python3
"""Reviewed codegen must reject unsupported contracts, drift and stale outputs."""
import copy
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import generate_recovered as recovered


class RecoveryCodegen(unittest.TestCase):
    def setUp(self):
        self.manifest = json.loads((ROOT / "research/recovery-contracts.json").read_text())

    def rehash(self, value):
        value["content_sha256"] = recovered.content_hash({k: v for k, v in value.items() if k != "content_sha256"})

    def test_snapshot_pins_bodies_scalar_boundaries_and_all_commands(self):
        generated = recovered.generate(self.manifest)
        self.assertEqual(len(self.manifest["source_functions"]), 17)
        self.assertEqual(len(self.manifest["scalar_spans"]), 8)
        self.assertEqual(len(self.manifest["ui_commands"]), 97)
        self.assertIn('"GUIEXITGAME"', generated["ui_bindings.hpp"])
        self.assertIn('"NONE"', generated["ui_bindings.hpp"])
        self.assertIn("UINT64_C(0xfffffffffffff)", generated["mwc_float.hpp"])

    def test_numeric_constants_and_scalar_scope_cannot_be_changed_by_rehashing(self):
        for edit in (lambda x: x["numeric_constants"]["numeric_hundred"].update(bytes_le="00007a44"),
                     lambda x: x["numeric_constants"]["numeric_hundred"].update(address="0x0"),
                     lambda x: x["scalar_spans"][0].update(scope="whole-function"),
                     lambda x: x["scalar_spans"][0].update(body_sha256="0" * 64)):
            changed = copy.deepcopy(self.manifest)
            edit(changed)
            self.rehash(changed)
            with self.assertRaises(ValueError):
                recovered.generate(changed)

    def test_unknown_recipes_bodies_and_changed_widths_require_review(self):
        for field, value in (("recipes", ["guess_from_similar_shape"]),
                             ("source_functions", [])):
            changed = copy.deepcopy(self.manifest)
            changed[field] = value
            self.rehash(changed)
            with self.assertRaises(ValueError):
                recovered.generate(changed)
        changed = copy.deepcopy(self.manifest)
        changed["mwc_operands"]["fraction_mask"] = "0xfffffffffff"  # old 44-bit bug
        self.rehash(changed)
        with self.assertRaisesRegex(ValueError, "operand/width"):
            recovered.generate(changed)

    def test_snapshot_drift_missing_ids_and_cpp_injection_are_rejected(self):
        changed = copy.deepcopy(self.manifest)
        changed["ui_commands"][0]["name"] = "changed"
        with self.assertRaisesRegex(ValueError, "content hash"):
            recovered.generate(changed)
        for edit in (lambda x: x["ui_commands"].pop(),
                     lambda x: x["ui_commands"][0].update(id=10),
                     lambda x: x["ui_commands"][0].update(name='GUI"; BAD')):
            changed = copy.deepcopy(self.manifest)
            edit(changed)
            self.rehash(changed)
            with self.assertRaises(ValueError):
                recovered.generate(changed)

    def test_generation_reuse_and_failed_check_never_leaves_green_report(self):
        with tempfile.TemporaryDirectory() as folder:
            out = Path(folder) / "include"
            report = Path(folder) / "generation.json"
            command = [sys.executable, str(ROOT / "tools/generate_recovered.py"),
                       "--out-dir", str(out), "--report", str(report)]
            subprocess.run(command, check=True, capture_output=True)
            mtimes = {p.name: p.stat().st_mtime_ns for p in out.iterdir()}
            subprocess.run(command, check=True, capture_output=True)
            self.assertEqual(mtimes, {p.name: p.stat().st_mtime_ns for p in out.iterdir()})
            self.assertEqual(json.loads(report.read_text())["changed_outputs"], [])
            header = out / "mwc_float.hpp"
            header.write_text(header.read_text().replace("0xfffffffffffff", "0xfffffffffff"))
            result = subprocess.run([*command, "--check"], capture_output=True, text=True)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn("stale/missing", result.stderr)
            self.assertEqual(json.loads(report.read_text())["status"], "FAILED")
            self.assertIn("0xfffffffffff", header.read_text())  # check did not auto-fix unknown drift
            subprocess.run(command, check=True, capture_output=True)
            self.assertEqual(json.loads(report.read_text())["changed_outputs"], ["mwc_float.hpp"])


if __name__ == "__main__":
    unittest.main()
