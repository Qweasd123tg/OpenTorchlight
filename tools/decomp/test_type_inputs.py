import json
from pathlib import Path
import shutil
import tempfile
import unittest
from unittest.mock import patch

import type_inputs


class TypeInputs(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.base = Path(temporary.name)
        self.root = self.base / "live"
        self.compiler = self.base / "cache/gcc447"
        self.compiler.mkdir(parents=True)
        (self.compiler / "stddef.h").write_text("typedef unsigned long size_t;")
        (self.root / "decomp/include").mkdir(parents=True)
        (self.root / "decomp/include/Owner.h").write_text("struct Owner { int field; };")
        (self.root / "sdk").mkdir()
        (self.root / "sdk/Dependency.h").write_text("struct Dependency { long value; };")
        (self.root / "decomp/config.json").write_text(json.dumps(
            {"include": ["decomp/include"], "system_include": ["sdk"]}))
        (self.root / "build-decomp/include-gen").mkdir(parents=True)
        (self.root / "build-decomp/include-gen/Generated.h").write_text("struct Generated {};")
        self.elf = self.base / "original"
        self.elf.write_bytes(b"original ELF input")
        for context in [patch.object(type_inputs.toolchain, "cache_dir", return_value=self.compiler.parent),
                        patch.object(type_inputs.elfdb, "default_elf", return_value=self.elf),
                        patch.dict(type_inputs.os.environ, {}, clear=True)]:
            context.start()
            self.addCleanup(context.stop)

    def test_stage_copy_keeps_identity_with_the_same_fallback_search_mode(self):
        expected = type_inputs.capture(self.root)
        stage = self.base / "stage"
        shutil.copytree(self.root, stage)
        self.assertEqual(expected, type_inputs.capture(stage))
        with patch.dict(type_inputs.os.environ, {"OTL_EXTRA_INCLUDE": str(self.root / "build-decomp/include-gen")}):
            expected_fallback = type_inputs.capture(self.root)
        self.assertNotEqual(expected, expected_fallback)
        with patch.dict(type_inputs.os.environ, {"OTL_INCLUDE_ROOT": str(stage),
                                               "OTL_EXTRA_INCLUDE": str(stage / "build-decomp/include-gen")}):
            self.assertEqual(expected_fallback, type_inputs.capture(stage))

    def test_enabling_a_generated_header_that_shadows_sdk_changes_identity(self):
        generated = self.root / "build-decomp/include-gen/Dependency.h"
        generated.write_text("struct Dependency { char value; };")
        stamp = {"source_inputs": type_inputs.capture(self.root)}
        with patch.dict(type_inputs.os.environ, {"OTL_EXTRA_INCLUDE": str(generated.parent)}):
            self.assertFalse(type_inputs.current(stamp, self.root))

    def test_changed_header_sdk_compiler_elf_or_config_invalidates_snapshot(self):
        for path in [self.root / "decomp/include/Owner.h", self.root / "sdk/Dependency.h",
                     self.compiler / "stddef.h", self.elf, self.root / "decomp/config.json"]:
            with self.subTest(path=path):
                original = path.read_bytes()
                types = {"source_inputs": type_inputs.capture(self.root)}
                path.write_bytes(original + b" ")
                self.assertFalse(type_inputs.current(types, self.root))
                path.write_bytes(original)
                self.assertTrue(type_inputs.current(types, self.root))

    def test_added_and_deleted_header_invalidate(self):
        stamp = {"source_inputs": type_inputs.capture(self.root)}
        path = self.root / "sdk/New.h"
        path.write_text("struct New {};")
        self.assertFalse(type_inputs.current(stamp, self.root))
        path.unlink()
        self.assertTrue(type_inputs.current(stamp, self.root))
        (self.root / "decomp/include/Owner.h").unlink()
        self.assertFalse(type_inputs.current(stamp, self.root))

    def test_unversioned_snapshot_rejected_and_capture_does_not_write(self):
        self.assertFalse(type_inputs.current({"classes": {}}, self.root))
        before = {str(p): p.read_bytes() for p in self.base.rglob("*") if p.is_file()}
        type_inputs.capture(self.root)
        after = {str(p): p.read_bytes() for p in self.base.rglob("*") if p.is_file()}
        self.assertEqual(before, after)


if __name__ == "__main__":
    unittest.main()
