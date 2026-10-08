"""A packet may borrow only this attempt's current completed Ghidra body."""
import hashlib
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import ghidra_draft
import llm_loop
import type_inputs


class AttemptDrafts(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name) / "attempt"
        self.folder = self.root / "build-decomp/drafts/Unit.cpp"
        (self.folder / "raw").mkdir(parents=True)
        self.raw = self.folder / "raw/0x10.c"
        self.raw.write_text("void original_draft() {}\n")
        (self.root / "decomp/include").mkdir(parents=True)
        (self.root / "decomp/include/Unit.h").write_text("struct Unit { int field; };")
        (self.root / "decomp/config.json").write_text("{}")
        self.compiler = Path(temporary.name) / "cache/gcc447"
        self.compiler.mkdir(parents=True)
        self.elf = Path(temporary.name) / "original"
        self.elf.write_bytes(b"original ELF")
        for context in [patch.object(type_inputs.toolchain, "cache_dir", return_value=self.compiler.parent),
                        patch.object(type_inputs.elfdb, "default_elf", return_value=self.elf),
                        patch.dict(type_inputs.os.environ, {}, clear=True)]:
            context.start()
            self.addCleanup(context.stop)
        self.types = {"classes": {}, "prototypes": {}, "vtables": {}}
        self.types["source_inputs"] = type_inputs.capture(self.root)
        (self.root / "build-decomp/types.json").write_text(json.dumps(self.types))
        self.receipt = {"schema": ghidra_draft.DRAFT_SCHEMA, "elf": "original",
                        "tools": ghidra_draft.tools_digest(),
                        "types_fingerprint": ghidra_draft.types_fingerprint(self.types),
                        "exports": {"0x10": {"status": "COMPLETE",
                                              "raw_sha256": hashlib.sha256(self.raw.read_bytes()).hexdigest()}}}
        self.save()
        self.loop = llm_loop.Loop.__new__(llm_loop.Loop)
        self.loop.tu = {"name": "Unit.cpp"}
        self.loop.db = {"original_elf_sha256": "original", "tus": [{"id": 1, "name": "Unit.cpp"}],
                        "functions": {"0x10": {"tu": 1}, "0x20": {"tu": 1}}}
        self.loop.methods, self.loop.signatures, self.loop.enums = {}, {}, {}
        for context in [patch.object(llm_loop, "ROOT", self.root),
                        patch.object(ghidra_draft, "OUT", Path(temporary.name) / "other-checkout"),
                        patch.object(ghidra_draft, "export_types", side_effect=AssertionError("live export forbidden"))]:
            context.start()
            self.addCleanup(context.stop)

    def save(self):
        (self.folder / "inputs.json").write_text(json.dumps(self.receipt))

    def draft(self):
        with patch.object(llm_loop.ghidra_cpp, "convert", return_value="converted definition") as converter:
            result = self.loop.draft({"address": "0x10"})
        return result, converter.called

    def test_fresh_selected_body_uses_attempt_not_live_and_needs_no_whole_tu_export(self):
        self.assertEqual(("converted definition", True), self.draft())

    def test_unversioned_raw_is_not_sent_as_a_model_draft(self):
        (self.folder / "inputs.json").unlink()
        text, converted = self.draft()
        self.assertFalse(converted)
        self.assertIn("no inputs.json", text)
        self.assertNotIn("original_draft", text)

    def test_failed_receipt_never_reuses_a_leftover_body(self):
        for status in ("TYPE_ERROR", "TIMEOUT", "NO_BODY"):
            with self.subTest(status=status):
                self.receipt["exports"]["0x10"]["status"] = status
                self.save()
                text, converted = self.draft()
                self.assertFalse(converted)
                self.assertIn(status, text)
                self.assertNotIn("original_draft", text)

    def test_changed_body_or_type_snapshot_is_not_sent(self):
        self.raw.write_text("void changed_draft() {}\n")
        self.assertFalse(self.draft()[1])
        self.raw.write_text("void original_draft() {}\n")
        (self.root / "build-decomp/types.json").write_text(json.dumps({**self.types, "classes": {"Changed": {}}}))
        text, converted = self.draft()
        self.assertFalse(converted)
        self.assertIn("type/layout/vtable/prototype inputs changed", text)

    def test_changed_header_cannot_reuse_a_matching_old_types_and_receipt_pair(self):
        (self.root / "decomp/include/Unit.h").write_text("struct Unit { long field; };")
        text, converted = self.draft()
        self.assertFalse(converted)
        self.assertIn("type snapshot inputs", text)

    def test_missing_attempt_types_cannot_borrow_the_live_snapshot(self):
        (self.root / "build-decomp/types.json").unlink()
        text, converted = self.draft()
        self.assertFalse(converted)
        self.assertIn("types snapshot", text)


if __name__ == "__main__":
    unittest.main()
