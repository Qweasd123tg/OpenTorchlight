#!/usr/bin/env python3
import json
import tempfile
import unittest
from pathlib import Path
from unittest import mock

import ghidra_draft


class CalleePrototypes(unittest.TestCase):
    def test_callee_prototype_from_another_tu_makes_drafts_stale(self):
        db = {"original_elf_sha256": "elf",
              "tus": [{"id": 1, "name": "A.cpp"}, {"id": 2, "name": "B.cpp"}],
              "functions": {"0x10": {"tu": 1}, "0x20": {"tu": 2}, "0x30": {"tu": 2}}}
        # A::run calls B::get; the jmp stays inside A::run.
        insns = {"0x10": [(0x10, "call", "20", "B::get"), (0x15, "jmp", "12", "")]}
        prototypes = {"0x10": "void A::run()", "0x20": "int B::get()", "0x30": "void B::other()"}
        with tempfile.TemporaryDirectory() as tmp:
            out = Path(tmp)
            (out / "A.cpp").mkdir()
            with mock.patch.object(ghidra_draft, "OUT", out), \
                    mock.patch.object(ghidra_draft, "tools_digest", lambda: "tools"), \
                    mock.patch.object(ghidra_draft, "_prototypes", lambda: prototypes):
                shaping = ghidra_draft.shaping_functions(db, 1, insns)
                self.assertEqual(shaping, {"0x10", "0x20"})
                (out / "A.cpp" / "inputs.json").write_text(json.dumps({
                    "elf": "elf", "tools": "tools", "classes": {},
                    "prototypes": ghidra_draft.prototype_digest(prototypes, shaping)}))

                def state():
                    return ghidra_draft.draft_state("A.cpp", db, {}, insns)[0]
                self.assertEqual(state(), "fresh")
                prototypes["0x30"] = "long B::other()"
                self.assertEqual(state(), "fresh")
                prototypes["0x20"] = "long B::get()"
                self.assertEqual(state(), "stale")


if __name__ == "__main__":
    unittest.main()
