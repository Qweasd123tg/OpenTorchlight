"""A full-TU candidate cannot discard existing recovered definitions."""
import tempfile
from pathlib import Path
from unittest.mock import patch
import unittest

import candidate
import publication


class PreserveDefinitions(unittest.TestCase):
    def exercise(self, body):
        with tempfile.TemporaryDirectory(prefix="otl-preservation-") as folder:
            root = Path(folder)
            (root / "decomp/src").mkdir(parents=True)
            (root / "decomp/include").mkdir()
            live = root / "decomp/src/Unit.cpp"
            baseline = "int first() { return 1; }\nint second() { return 2; }\n"
            live.write_text(baseline)
            source = root / "candidate.cpp"
            source.write_text(body)
            db = {"tus": [{"name": "Unit.cpp", "kind": "game"}], "functions": {}}
            def compare(path, *args, **kwargs):
                text = Path(path).read_text()
                rows = [{"address": address, "status": "MATCH" if name in text else "MISSING"}
                        for address, name in [("0x1", "first"), ("0x2", "second")]]
                return {"object_digest": "fixture-object", "functions": rows, "unknown": []}
            def validate(stage):
                # Simulate a green suite which does not exercise the omitted body.
                stage.validated = publication.tree_state(stage.path)
                stage.validated_inputs = "fixture-inputs"
                stage.final_units = [{"source": str(stage.path / "decomp/src/Unit.cpp"),
                                      **compare(stage.path / "decomp/src/Unit.cpp")}]
                stage.covered, stage.report = set(), []
            with patch.object(candidate.elfdb, "load_db", return_value=db), \
                    patch.object(candidate.evidence, "input_digest", return_value="fixture-inputs"), \
                    patch.object(candidate.objdiff, "Original"), \
                    patch.object(candidate.objdiff, "compare_source", side_effect=compare), \
                    patch.object(candidate.promote, "promote"), \
                    patch.object(publication.Stage, "_verify_published_objects"), \
                    patch.object(publication.Stage, "validate", validate):
                result = candidate.evaluate("Unit.cpp", source, publish=True, root=root)
            return result, live.read_text(), baseline

    def test_missing_previous_definition_cannot_publish(self):
        result, live, baseline = self.exercise("int first() { return 1; }\n")
        self.assertFalse(result["published"])
        self.assertEqual("DIFF", result["status"])
        self.assertEqual(["0x2"], result["missing_previous"])
        self.assertEqual(baseline, live)

    def test_complete_matching_candidate_can_publish(self):
        result, live, baseline = self.exercise("int first() { return 1; }\nint second() { return 2; }\n")
        self.assertTrue(result["published"])
        self.assertEqual(baseline, live)


if __name__ == '__main__':
    unittest.main()
