#!/usr/bin/env python3
"""Pinned GCC counterexamples: EH, literals and full object evidence identity."""
import hashlib
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import threading
import unittest
from unittest.mock import patch

import elfimage
import objdiff
import objdiff_eh
import toolchain


def linked_original(path):
    image = elfimage.load(path, require_original=False)
    functions = {}
    for symbol in image.symbols:
        if symbol.type == elfimage.STT_FUNC and symbol.defined and symbol.size:
            address = hex(symbol.value)
            functions[address] = {"address": address, "size": symbol.size, "mangled": symbol.name,
                                  "names": [symbol.name], "bind": ["global"], "demangled": symbol.name,
                                  "tu": 0, "kind": "function"}
    original = objdiff.Original.__new__(objdiff.Original)
    original.db = {"functions": functions, "classes": {}, "globals": [], "tus": []}
    original.image = image
    original.side = objdiff.OriginalSide(image, original.db)
    original.frames = objdiff_eh.inspect(image)
    original._lock = threading.RLock()
    original.by_name = {f["mangled"]: [f] for f in functions.values()}
    return original


@unittest.skipUnless((toolchain.cache_dir() / "gcc447" / ".complete.json").exists() and shutil.which("g++"),
                     "requires cached pinned GCC 4.4.7 and host linker")
class PinnedAcceptanceTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(prefix="otl-objdiff-test-")
        self.directory = Path(self.tmp.name)
        self.env = patch.dict(os.environ, {"OTL_NO_CC_CACHE": "1"})
        self.env.start()
        self.addCleanup(self.env.stop)
        self.addCleanup(self.tmp.cleanup)

    def compile(self, text, stem="unit", extra=()):
        source = self.directory / (stem + ".cpp")
        source.write_text(text)
        directory = self.directory / stem
        directory.mkdir(exist_ok=True)
        obj, globalized = objdiff.compile_for_diff(source, directory, extra=extra, quiet=True)
        return source, obj, globalized

    def link(self, obj, driver, stem="reference"):
        source = self.directory / (stem + "-driver.cpp")
        source.write_text(driver)
        binary = self.directory / stem
        subprocess.run(["g++", "-no-pie", str(obj), str(source), "-o", str(binary)],
                       check=True, capture_output=True)
        return binary

    def test_catch_type_cannot_match_and_plain_function_still_matches(self):
        def body(kind):
            return ('extern "C" void raise_value();\n'
                    'extern "C" int plain(int x) { return x * 3; }\n'
                    'extern "C" int probe() { try { raise_value(); return 0; } '
                    'catch (' + kind + ') { return 7; } }\n')
        source, obj, globalized = self.compile(body("int"))
        original_bytes = Path(obj).read_bytes()
        norm_int = objdiff.object_functions(obj, globalized=globalized)
        driver = ('extern "C" int probe(); extern "C" void raise_value() { throw 1; } '
                  'int main() { try { return probe(); } catch (...) { return 99; } }')
        binary_int = self.link(obj, driver)
        original = linked_original(binary_int)
        result_int = objdiff.compare_source(source, original, quiet=True)
        rows_int = {row["name"]: row for row in result_int["functions"]}
        self.assertEqual(rows_int["plain"]["status"], "MATCH")
        self.assertEqual(rows_int["probe"]["status"], "DIFF")
        self.assertIn("EH LSDA equivalence unverified", rows_int["probe"]["metadata_reasons"])
        self.assertEqual(result_int["object_digest"], hashlib.sha256(original_bytes).hexdigest())
        self.assertTrue(all(row["object_digest"] == result_int["object_digest"] for row in result_int["functions"]))
        self.assertEqual(subprocess.run([str(binary_int)]).returncode, 7)

        source, obj, globalized = self.compile(body("double"))
        binary_double = self.link(obj, driver, "different")
        norm_double = objdiff.object_functions(obj, globalized=globalized)
        self.assertEqual(norm_int["probe"]["norm"], norm_double["probe"]["norm"])
        self.assertNotEqual(hashlib.sha256(original_bytes).hexdigest(), hashlib.sha256(Path(obj).read_bytes()).hexdigest())
        result_double = objdiff.compare_source(source, original, quiet=True)
        rows_double = {row["name"]: row for row in result_double["functions"]}
        self.assertEqual(rows_double["plain"]["status"], "MATCH")
        self.assertEqual(rows_double["probe"]["status"], "DIFF")
        self.assertNotEqual(result_int["object_digest"], result_double["object_digest"])
        self.assertEqual(subprocess.run([str(binary_double)]).returncode, 99)

    def test_linked_and_object_long_literals_compare_completely(self):
        for length in (80, 300):
            prefix = 'extern "C" int sink(const char *); extern "C" int probe() { return sink("'
            source, obj, globalized = self.compile(prefix + "A" * length + 'X"); }')
            binary = self.link(obj, 'extern "C" int probe(); extern "C" int sink(const char *) { return 0; } '
                                   'int main() { return probe(); }', "reference" + str(length))
            original = linked_original(binary)
            initial = objdiff.compare_source(source, original, quiet=True)
            self.assertEqual(next(row for row in initial["functions"] if row["name"] == "probe")["status"], "MATCH")
            source.write_text(prefix + "A" * length + 'Y"); }')
            changed = objdiff.compare_source(source, original, quiet=True)
            self.assertEqual(next(row for row in changed["functions"] if row["name"] == "probe")["status"], "DIFF")

    def test_corrupt_unresolved_eh_fails_closed(self):
        _, path, globalized = self.compile('extern "C" int probe(int x) { return x * 3; }')
        obj = elfimage.load_object(path)
        frames = objdiff_eh.inspect(obj, relocatable=True)
        symbol = next(s for s in obj.symbols if s.name == "probe")
        self.assertIsNone(frames.reason(symbol.value, symbol.size, symbol.shndx))
        self.assertEqual(frames.personalities(symbol.value, symbol.size, symbol.shndx), ["__gxx_personality_v0"])
        frame_section = next(s for s in obj.sections if s.name == ".eh_frame")
        obj.relocs[frame_section.index] = []
        self.assertIn("unresolved", objdiff_eh.inspect(obj, True).reason(symbol.value, symbol.size, symbol.shndx))
        obj = elfimage.load_object(path)
        frame_section = next(s for s in obj.sections if s.name == ".eh_frame")
        obj.data = obj.data[:frame_section.offset + 5]
        self.assertIn("truncated", objdiff_eh.inspect(obj, True).reason(symbol.value, symbol.size, symbol.shndx))


if __name__ == "__main__":
    unittest.main()
