#!/usr/bin/env python3
import contextlib
import io
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import check
import evidence
import mutate


class EvidenceTests(unittest.TestCase):
    def test_file_addition_content_and_context_invalidate(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            header = root / "Value.h"
            header.write_text("first")
            paths = lambda: evidence.directory_inputs("headers", root)
            baseline = evidence.digest_paths(paths(), {"flags": ["-O2"]})
            self.assertEqual(baseline, evidence.digest_paths(paths(), {"flags": ["-O2"]}))
            header.write_text("second")
            self.assertNotEqual(baseline, evidence.digest_paths(paths(), {"flags": ["-O2"]}))
            header.write_text("first")
            self.assertNotEqual(baseline, evidence.digest_paths(paths(), {"flags": ["-O0"]}))
            (root / "New.h").write_text("new include shadow")
            self.assertNotEqual(baseline, evidence.digest_paths(paths(), {"flags": ["-O2"]}))
            header.unlink()
            self.assertNotEqual(baseline, evidence.digest_paths(paths(), {"flags": ["-O2"]}))

    def test_complete_object_and_input_identity_required(self):
        entry = {"evidence": evidence.tested("object", "inputs", {"hand": False})}
        self.assertTrue(evidence.current(entry, "object", "inputs"))
        self.assertFalse(evidence.current(entry, "different data or EH relocations", "inputs"))
        self.assertFalse(evidence.current(entry, "object", "different observer or linked helper"))
        self.assertFalse(evidence.current({"code": "same instructions"}, "object", "inputs"))
        entry["evidence"]["schema"] = 0
        self.assertFalse(evidence.current(entry, "object", "inputs"))

    def record_case(self, result, build=None):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            accepted = root / "autotests.json"
            accepted.write_text("{}")
            f = {"address": "0x1", "demangled": "Unit::probe()"}
            builds = {"0x1": build or {"code": "instructions", "object_digest": "object"}}
            with patch.object(mutate, "ROOT", root), patch.object(mutate, "ACCEPTED", accepted), \
                    patch.object(mutate, "compiled_evidence", return_value=builds), \
                    patch.object(evidence, "input_digest", return_value="inputs"), \
                    contextlib.redirect_stdout(io.StringIO()):
                mutate.record({}, [f], {"0x1": result})
            return json.loads(accepted.read_text())

    def result(self):
        return {"strong": True, "killed": 9, "tried": 10, "code_at_test": "instructions",
                "evidence": evidence.tested("object", "inputs", {"hand": False})}

    def test_record_cannot_stamp_old_result_with_new_code(self):
        legacy = {"strong": True, "killed": 9, "tried": 10, "code_at_test": "old instructions"}
        self.assertEqual({}, self.record_case(legacy))
        result = self.result()
        self.assertEqual({}, self.record_case(result, {"code": "new instructions", "object_digest": "new object"}))
        # Same instructions with new data/EH is stale too.
        self.assertEqual({}, self.record_case(result, {"code": "instructions", "object_digest": "new data"}))
        result["evidence"]["inputs_digest"] = "old observer"
        self.assertEqual({}, self.record_case(result))

    def test_record_positive_control_and_hand_rejection(self):
        result = self.result()
        saved = self.record_case(result)["0x1"]
        self.assertEqual(result["evidence"], saved["evidence"])
        self.assertEqual("instructions", saved["code"])
        result["evidence"]["parameters"]["hand"] = True
        self.assertEqual({}, self.record_case(result))

    def test_observer_incompleteness_never_kills_mutant(self):
        parsed = mutate.stats(["stats auto_1 same 24 both-failed 0 different 0 incomplete 1"])
        self.assertEqual("error", mutate.generated_outcome(parsed["auto_1"]))
        self.assertEqual("error", mutate.generated_outcome((0, 30, 0, 0)))
        self.assertEqual("survived", mutate.generated_outcome((20, 0, 0, 0)))
        self.assertEqual("killed", mutate.generated_outcome((0, 0, 1, 0)))

    def test_check_rejects_legacy_and_changed_inputs(self):
        f = {"address": "0x1"}
        db = {"functions": {"0x1": f}}
        diff = {"0x1": {"code": "instructions", "object_digest": "object"}}
        entry = {"name": "probe", "code": "instructions"}
        class Generator:
            def write(self, wanted):
                return wanted, {}
        with patch.object(mutate, "load_accepted", return_value={"0x1": entry}), \
                patch.object(check.autotest, "Generator", Generator), \
                patch.object(evidence, "input_digest", return_value="inputs"), \
                contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual([], check.generated_tests(db, diff))
            entry["evidence"] = evidence.tested("object", "inputs", {"hand": False})
            self.assertEqual(["0x1"], check.generated_tests(db, diff))
            entry["evidence"]["inputs_digest"] = "old linked helper"
            self.assertEqual([], check.generated_tests(db, diff))

    def test_batch_failure_is_retried_before_attributing_kills(self):
        # A hidden call edge was absent from the symbol graph. The pair fails,
        # but only helper's mutation fails when each is tested independently.
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            src = root / "src"
            src.mkdir()
            source = src / "unit.cpp"
            source.write_text("int Unit::caller() { return 1; }\nint Unit::helper() { return 1; }\n")
            functions = [{"address": "0x1", "demangled": "Unit::caller()", "params": "", "tu": 1, "names": ["caller"]},
                         {"address": "0x2", "demangled": "Unit::helper()", "params": "", "tu": 1, "names": ["helper"]}]
            db = {"functions": {f["address"]: f for f in functions}, "tus": [{"id": 1, "name": "unit.cpp"}]}
            rounds = []
            class Generator:
                def __init__(self):
                    self.db = db
                def write(self, wanted):
                    return wanted, {}
            def build_and_test(current_src, tests, names, out):
                if out.name == "base":
                    return {"auto_1": (24, 0, 0, 0), "auto_2": (24, 0, 0, 0)}, []
                names = sorted(names)
                rounds.append(names)
                killed = len(names) > 1 or names == ["auto_2"]
                return {name: (0, 0, 1, 0) if killed else (24, 0, 0, 0) for name in names}, []
            def points(text, masked, start, end):
                at = text.index("1", start, end)
                return [(at, at + 1, "2")]
            def probe(source, text, mutant, baseline, slot):
                mutant.affected = set(mutant.target["names"])
                return True
            builds = {f["address"]: {"code": "instructions", "object_digest": "object"} for f in functions}
            with patch.object(mutate, "ROOT", root), patch.object(mutate, "SRC", src), \
                    patch.object(mutate, "WORK", root / "work"), patch.object(mutate, "RESULT", root / "mutation.json"), \
                    patch.object(mutate, "ACCEPTED", root / "autotests.json"), \
                    patch.object(mutate.toolchain, "CC_CACHE", root / "cache"), \
                    patch.object(mutate.autotest, "OUT", root / "autotests"), \
                    patch.object(mutate.autotest, "Generator", Generator), \
                    patch.object(mutate.autotest, "diff_functions", return_value=functions), \
                    patch.object(mutate, "compiled_evidence", return_value=builds), \
                    patch.object(evidence, "input_digest", return_value="inputs"), \
                    patch.object(mutate, "build_and_test", side_effect=build_and_test), \
                    patch.object(mutate, "mutation_points", side_effect=points), \
                    patch.object(mutate, "probe", side_effect=probe), \
                    patch("sys.argv", ["mutate.py", "--max", "1"]), \
                    contextlib.redirect_stdout(io.StringIO()):
                mutate.main()
            results = json.loads((root / "mutation.json").read_text())
            self.assertEqual([["auto_1", "auto_2"], ["auto_1"], ["auto_2"]], rounds)
            self.assertFalse(results["0x1"]["strong"])
            self.assertEqual(0, results["0x1"]["killed"])
            self.assertTrue(results["0x2"]["strong"])
            self.assertTrue(results["0x2"]["mutants"][0]["isolated"])


if __name__ == "__main__":
    unittest.main()
