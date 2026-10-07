"""Cosmetic DIFF scores are optional; exact checks and object identity are not."""
from pathlib import Path
import tempfile
import unittest
from unittest.mock import Mock, patch

import objdiff


def without_score(result):
    return dict(result, functions=[{key: value for key, value in row.items() if key != "score"}
                                   for row in result["functions"]])


class OptionalScores(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.source = Path(temporary.name) / "Probe.cpp"
        self.source.write_text("int probe() { return 1; }\n")
        self.function = dict(address="0x1000", mangled="probe", names=["probe"],
                             demangled="probe()", size=4, tu=1, kind="function")
        self.original = Mock()
        self.original.db = dict(functions={"0x1000": self.function},
                                tus=[dict(id=1, name="Probe.cpp")])
        self.original.function.return_value = self.function
        self.original.normalized.return_value = ["mov $1,%eax", "ret"]
        self.original.metadata_reasons.return_value = []
        self.original.frames.personalities.return_value = []
        self.original.unknown_references.return_value = []
        self.mine = dict(size=4, bind=1, norm=["mov $1,%eax", "ret"],
                         metadata_reasons=[], personalities=[])
        self.payload = b"complete code + data + EH + relocations"

        def compile_object(source, directory, extra=(), quiet=False):
            path = Path(directory) / "unit.o"
            path.write_bytes(self.payload)
            return path, set()

        self.compile = Mock(side_effect=compile_object)
        for name, value in (("compile_for_diff", self.compile),
                            ("object_functions", Mock(side_effect=lambda *args: {"probe": self.mine}))):
            context = patch.object(objdiff, name, value)
            context.start()
            self.addCleanup(context.stop)

    def compare(self, **options):
        return objdiff.compare_source(self.source, self.original, quiet=True, **options)

    def test_default_preserves_diagnostic_scores(self):
        self.mine["norm"][0] = "mov $2,%eax"
        self.assertEqual(self.compare(), self.compare(scores=True))
        self.assertIn("score", self.compare()["functions"][0])

    def test_no_scores_never_calls_similarity_matcher(self):
        self.mine["norm"][0] = "mov $2,%eax"
        with patch.object(objdiff.difflib, "SequenceMatcher", side_effect=AssertionError("cosmetic metric")):
            result = self.compare(scores=False)
        self.assertEqual("DIFF", result["functions"][0]["status"])
        self.assertNotIn("score", result["functions"][0])

    def test_exact_match_remains_match_and_keeps_score_one(self):
        result = self.compare(scores=False)
        self.assertEqual("MATCH", result["functions"][0]["status"])
        self.assertEqual(1.0, result["functions"][0]["score"])

    def test_identical_instructions_with_unverified_data_remain_diff(self):
        self.mine["metadata_reasons"] = ["unterminated or unclassified literal"]
        row = self.compare(scores=False)["functions"][0]
        self.assertEqual("DIFF", row["status"])
        self.assertEqual(self.mine["metadata_reasons"], row["metadata_reasons"])

    def test_identical_instructions_with_eh_or_personality_uncertainty_remain_diff(self):
        self.original.metadata_reasons.return_value = ["unverified LSDA"]
        self.mine["personalities"] = ["different personality"]
        row = self.compare(scores=False)["functions"][0]
        self.assertEqual("DIFF", row["status"])
        self.assertEqual(["unverified LSDA", "EH personality differs"], row["metadata_reasons"])

    def test_unknown_refs_full_object_identity_and_every_other_field_preserved(self):
        self.mine["norm"][0] = "mov $2,%eax"
        self.original.unknown_references.return_value = ["invented"]
        self.original.known_overloads.return_value = ["real(int)"]
        before, after = self.compare(), self.compare(scores=False)
        self.assertEqual(without_score(before), without_score(after))
        self.assertTrue(after["object_digest"])
        self.assertEqual([dict(name="invented", known=["real(int)"])], after["unknown"])

    def test_identity_only_keeps_complete_bytes_and_unknown_refs_without_analysis(self):
        self.original.unknown_references.return_value = ["invented"]
        self.original.known_overloads.return_value = ["real(int)"]
        compared = self.compare()
        with patch.object(objdiff, "object_functions", side_effect=AssertionError("unneeded analysis")):
            identity = objdiff.compiled_identity(self.source, self.original, quiet=True)
        self.assertEqual({key: compared[key] for key in ("object_digest", "unknown")}, identity)
        self.payload += b"changed data/EH, unchanged instructions"
        changed = objdiff.compiled_identity(self.source, self.original, quiet=True)
        self.assertNotEqual(identity["object_digest"], changed["object_digest"])


if __name__ == "__main__":
    unittest.main()
