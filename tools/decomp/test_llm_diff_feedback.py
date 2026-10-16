"""Bounded diagnostic previews retain complete, addressable diff artifacts."""
import hashlib
import json
from pathlib import Path
import re
import tempfile
import unittest
from unittest.mock import Mock, patch

import llm_loop


class InstructionDiffFeedback(unittest.TestCase):
    def feedback(self, root, mine, theirs, round_no=0):
        loop = llm_loop.Loop.__new__(llm_loop.Loop)
        loop.work = root / "attempt"
        loop.round_no = round_no
        loop.tu = {"name": "Probe.cpp"}
        loop.original = Mock()
        loop.original.normalized.return_value = theirs
        with patch.object(llm_loop.objdiff, "compile_for_diff", return_value=("unused.o", [])), \
                patch.object(llm_loop.objdiff, "object_functions",
                             return_value={"probe": {"norm": mine}}):
            return loop.instruction_diff(root / "Probe.cpp", {"address": "0x123", "names": ["probe"]})

    def test_late_hunk_is_retained_and_indexed_beyond_preview(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            mine = [f"instruction {i}" for i in range(400)]
            theirs = mine[:]
            for i in range(5, 390, 12):
                theirs[i] = f"changed {i}"
            feedback = self.feedback(root, mine, theirs)
            directory = root / "attempt/instruction-diffs"
            artifact = next(directory.glob("*.diff"))
            index = json.loads(next(directory.glob("*.json")).read_text())
            lines = artifact.read_text().splitlines()
            self.assertIn("changed 389", artifact.read_text())
            self.assertNotIn("changed 389", feedback)
            self.assertGreater(index["hunks"][-1]["start_line"], 80)
            self.assertEqual(len(lines), index["line_count"])
            self.assertEqual(hashlib.sha256(artifact.read_bytes()).hexdigest(), index["sha256"])
            self.assertIn(f"80/{len(lines)} original lines; {len(lines) - 80} lines not shown", feedback)
            pages = [self.feedback(root, mine, theirs, round_no=i)
                     for i in range((len(lines) + 79) // 80)]
            self.assertTrue(any("changed 389" in page for page in pages))
            self.assertEqual(feedback, self.feedback(root, mine, theirs,
                                                    round_no=len(pages)))
            for hunk in index["hunks"]:
                self.assertEqual(hunk["header"], lines[hunk["start_line"] - 1])
                self.assertLessEqual(hunk["start_line"], hunk["end_line"])
            self.feedback(root, mine, ["another revision"])
            self.assertTrue(artifact.exists())
            self.assertEqual(2, len(list(directory.glob("*.diff"))))

    def test_long_operand_is_not_allowed_to_expand_preview(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            operand = "x" * 20000 + "LAST_OPERAND_CHUNK"
            feedback = self.feedback(root, [operand], ["replacement"])
            self.assertLess(len(feedback), 10000)
            self.assertNotIn(operand, feedback)
            self.assertIn(operand, next((root / "attempt/instruction-diffs").glob("*.diff")).read_text())
            page_count = int(re.match(r"Diff page 1/(\d+):", feedback).group(1))
            self.assertGreater(page_count, 1)
            pages = [self.feedback(root, [operand], ["replacement"], round_no=i)
                     for i in range(page_count)]
            self.assertTrue(any("LAST_OPERAND_CHUNK" in page for page in pages))
            self.assertTrue(any("+replacement" in page for page in pages))
            for page in pages:
                # Four metadata lines are outside the bounded diff payload.
                payload = page.split("\n", 4)[4]
                self.assertLessEqual(len(payload), 8192)
                self.assertLessEqual(len(payload.splitlines()), 80)
            self.assertEqual(feedback, self.feedback(root, [operand], ["replacement"],
                                                    round_no=page_count))

    def test_page_metadata_and_payload_still_fail_closed_at_outer_prompt_budget(self):
        with tempfile.TemporaryDirectory() as tmp:
            feedback = self.feedback(Path(tmp), ["x" * 20000], ["replacement"])
            for session in (None, "existing-session"):
                with self.subTest(session=session):
                    loop = llm_loop.Loop.__new__(llm_loop.Loop)
                    loop.switch_after = 2
                    loop.max_prompt_chars = 64
                    model = Mock()
                    loop.models = [model]
                    loop.prompt_for = Mock(return_value="complete original packet")
                    item = {"f": {"address": "0x123"}, "tries": 0, "model": 0,
                            "session": session, "feedback": feedback,
                            "code": "int probe() { return 1; }"}
                    self.assertEqual(("0x123", "", session), loop.ask(item, round_no=2))
                    model.ask.assert_not_called()
                    self.assertEqual(feedback, item["feedback"])
                    self.assertIn("no code/feedback was truncated", item["blocked_reason"])

    def test_equal_functions_have_empty_diff_and_index(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            feedback = self.feedback(root, ["ret"], ["ret"])
            index = json.loads(next((root / "attempt/instruction-diffs").glob("*.json")).read_text())
            self.assertEqual([], index["hunks"])
            self.assertEqual(0, index["line_count"])
            self.assertIn("0/0 original lines; 0 lines not shown", feedback)


if __name__ == "__main__":
    unittest.main()
