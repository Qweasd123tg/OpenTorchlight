"""Regressions for interrupted attempts, stale claims, table holes and include shadowing."""
import json
import os
from pathlib import Path
import subprocess
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

import candidate
import check
import ghidra_cpp
import hybrid
import llm_loop
import mutate
import name_tables
import parallel
import publication
import toolchain


class Publication(unittest.TestCase):
    def setUp(self):
        self.enterContext(patch.object(publication.Stage, "_input_digest", return_value="synthetic-inputs"))
        self.enterContext(patch.object(publication.Stage, "_verify_published_objects", return_value=None))
    def fixture(self, folder):
        root = Path(folder)
        (root / "decomp/src").mkdir(parents=True)
        (root / "decomp/include").mkdir()
        (root / "decomp/src/Unit.cpp").write_text("old source")
        (root / "decomp/include/Unit.h").write_text("old header")
        return root

    def test_rejection_and_interruption_leave_live_source_and_headers_unchanged(self):
        with tempfile.TemporaryDirectory() as folder:
            root = self.fixture(folder)
            baseline = publication.tree_state(root)
            stage = publication.Stage(root)
            (stage.path / "decomp/src/Unit.cpp").write_text("rejected candidate")
            (stage.path / "decomp/include/Unit.h").write_text("rejected layout")
            with self.assertRaisesRegex(RuntimeError, "requires validation"):
                stage.publish()
            self.assertEqual(baseline, publication.tree_state(root))
            with stage.activate():
                self.assertEqual(stage.path, llm_loop.ROOT)
                self.assertIn(str(stage.path / "decomp/include"),
                              toolchain.include_args(Path("/compiler"), {"include": ["decomp/include"]}))
            self.assertNotEqual(stage.path, llm_loop.ROOT)

    def test_changed_final_tree_and_concurrent_editor_block_publication(self):
        with tempfile.TemporaryDirectory() as folder:
            root = self.fixture(folder)
            stage = publication.Stage(root)
            stage.validated = publication.tree_state(stage.path)
            stage.validated_inputs = "synthetic-inputs"
            (stage.path / "decomp/include/Unit.h").write_text("changed after tests")
            with self.assertRaisesRegex(RuntimeError, "requires validation"):
                stage.publish()
            stage.validated = publication.tree_state(stage.path)
            stage.validated_inputs = "synthetic-inputs"
            (root / "decomp/src/Unit.cpp").write_text("another editor")
            with self.assertRaisesRegex(RuntimeError, "changed during"):
                stage.publish()
            self.assertEqual("another editor", (root / "decomp/src/Unit.cpp").read_text())

    def test_partial_write_failure_rolls_back_both_files(self):
        with tempfile.TemporaryDirectory() as folder:
            root = self.fixture(folder)
            baseline = publication.tree_state(root)
            stage = publication.Stage(root)
            for path in (stage.path / "decomp/src/Unit.cpp", stage.path / "decomp/include/Unit.h"):
                path.write_text("validated new content")
            stage.validated = publication.tree_state(stage.path)
            stage.validated_inputs = "synthetic-inputs"
            replace = stage._replace
            count = 0
            def fail_once(name, data):
                nonlocal count
                count += 1
                if count == 2:
                    raise OSError("injected interrupted publication")
                return replace(name, data)
            with patch.object(stage, "_replace", side_effect=fail_once), self.assertRaises(OSError):
                stage.publish()
            self.assertEqual(baseline, publication.tree_state(root))


class CompilerCache(unittest.TestCase):
    def test_new_higher_priority_header_changes_real_object_and_warm_hit(self):
        with tempfile.TemporaryDirectory(prefix="otl-cache-shadow-") as folder:
            root = Path(folder)
            high, low = root / "high", root / "low"
            high.mkdir(); low.mkdir()
            (low / "Shadow.h").write_text("#define VALUE 7\n")
            source = root / "Probe.cpp"
            source.write_text('#include "Shadow.h"\nint value() { return VALUE; }\n')
            flags = ["-I", str(high), "-I", str(low), "-std=gnu++98"]
            with patch.object(toolchain, "CC_CACHE", root / "cache"), patch.dict(os.environ, {}, clear=False):
                os.environ.pop("OTL_NO_CC_CACHE", None)
                a = toolchain.compile_source(source, root / "a.o", flags).read_bytes()
                b = toolchain.compile_source(source, root / "b.o", flags).read_bytes()
                self.assertEqual(a, b)
                (high / "Shadow.h").write_text("#define VALUE 99\n")
                c = toolchain.compile_source(source, root / "c.o", flags).read_bytes()
                cold = toolchain.compile_source(source, root / "cold.o", flags, cache=False).read_bytes()
                self.assertNotEqual(a, c)
                self.assertEqual(cold, c)
                (high / "Shadow.h").unlink()
                self.assertEqual(a, toolchain.compile_source(source, root / "d.o", flags).read_bytes())

    def test_runtime_pairs_cannot_overwrite_another_active_attempt(self):
        with tempfile.TemporaryDirectory(prefix="otl-runtime-pairs-") as folder:
            root = Path(folder)
            blob, loader = root / "blob.elf", root / "loader.so"
            blob.write_bytes(b"first blob"); loader.write_bytes(b"loader")
            with patch.object(toolchain, "cache_dir", return_value=root / "cache"):
                first = hybrid.stage_runtime(blob, loader)
                blob.write_bytes(b"second blob")
                second = hybrid.stage_runtime(blob, loader)
                self.assertNotEqual(first[0], second[0])
                self.assertEqual(b"first blob", first[0].read_bytes())
                self.assertEqual(b"second blob", second[0].read_bytes())
                self.assertEqual(second, hybrid.stage_runtime(blob, loader))


class Queue(unittest.TestCase):
    def test_failed_start_returns_claim_to_queue(self):
        with tempfile.TemporaryDirectory() as folder:
            path = Path(folder) / "claims.json"
            with patch.object(parallel, "CLAIMS", path), patch.object(parallel.elfdb, "load_db", return_value={}), \
                    patch.object(parallel, "candidates", return_value=[(0, 100, "Unit.cpp", 1)]), \
                    patch.object(parallel, "new", side_effect=RuntimeError("startup failed")):
                with self.assertRaises(RuntimeError):
                    parallel.claim("worker", 1000)
                self.assertEqual({}, parallel.claims())

    def test_partial_and_large_tus_keep_remaining_functions(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            (root / "decomp/src").mkdir(parents=True)
            (root / "decomp/include").mkdir()
            (root / "decomp/src/Big.cpp").write_text("partial")
            funcs = {"0x1": {"address": "0x1", "tu": 1, "kind": "function", "size": 7},
                     "0x2": {"address": "0x2", "tu": 1, "kind": "function", "size": 80000}}
            db = {"tus": [{"id": 1, "name": "Big.cpp", "kind": "game"}], "functions": funcs, "classes": {}}
            import objdiff
            with patch.object(parallel, "ROOT", root), patch.object(parallel, "claims", return_value={}), \
                    patch.object(parallel, "owners", return_value={}), patch.object(objdiff, "Original"), \
                    patch.object(objdiff, "compare_source", return_value={"functions": [{"address": "0x1", "status": "MATCH"}]}):
                self.assertEqual([(0, 80000, "Big.cpp", 1)], parallel.candidates(db))


class Evidence(unittest.TestCase):
    def test_declared_unused_original_is_not_coverage(self):
        db = {"functions": {"0x1": {"names": ["_Z1fv"]}}}
        self.assertEqual(set(), check.shadow_covered(db, ["tlhybrid: unrelated PASS (0)"]))
        lines = ["tlhybrid: used PASS (0)", "    coverage used 0x1 completed 20 different 0 incomplete 0"]
        self.assertEqual({"0x1"}, check.shadow_covered(db, lines))
        for bad in ("different 1 incomplete 0", "different 0 incomplete 1"):
            self.assertEqual(set(), check.shadow_covered(db, [lines[0], lines[1].replace("different 0 incomplete 0", bad)]))
        self.assertEqual(set(), check.shadow_covered(db, [lines[1]]))

    def test_one_mutant_or_one_fault_class_is_not_strong(self):
        row = {"outcome": "killed", "category": "constant", "isolated": True}
        self.assertFalse(mutate.mutation_strength([row]))
        self.assertFalse(mutate.mutation_strength([row] * 10))
        self.assertTrue(mutate.mutation_strength([row, row, {**row, "category": "comparison"}]))
        self.assertFalse(mutate.mutation_strength([row, row, {**row, "category": "comparison", "isolated": False}]))

    def test_cv_selects_the_correct_mutation_body(self):
        text = "int C::f() { return 1; }\nint C::f() const { return 2; }\n"
        f = {"demangled": "C::f() const", "params": "", "cv": "const"}
        span = mutate.definition(text, mutate.mask(text), f)
        self.assertEqual("{ return 2; }", text[span[0]:span[1] + 1])

    def test_constructor_initializer_is_not_a_cv_qualifier(self):
        text = "C::C(int x) : Base(x), member(x) { run(); }\n"
        function = {"demangled": "C::C(int)", "params": "int", "kind": "ctor", "cv": ""}
        span = mutate.definition(text, mutate.mask(text), function)
        self.assertEqual("{ run(); }", text[span[0]:span[1] + 1])


class Tables(unittest.TestCase):
    def test_empty_known_width_and_non_ascii_values(self):
        table = name_tables.Tables.__new__(name_tables.Tables)
        data = b"\0" + b"\x80\0" + b"\0" + "\u0410\0".encode("utf-32le")
        table.image = SimpleNamespace(section_at=lambda a: SimpleNamespace(addr=0, size=len(data)),
                                      read=lambda a, n: data[a:a + n])
        self.assertEqual("", table.read_text(0, 1))
        self.assertEqual("\x80", table.read_text(1, 1))
        self.assertEqual("\u0410", table.read_text(4, 4))
        self.assertIsNone(table.read_text(1, 4))
        self.assertEqual("\\200", name_tables.c_literal("\x80"))

    def test_missing_slot_never_emits_shifted_array(self):
        table = name_tables.Tables.__new__(name_tables.Tables)
        with patch.object(table, "recover", return_value=({"file": "T.cpp", "demangled": "names"},
                                                        (("std::wstring", "L"), ["a", None, "c"], [1]))):
            with self.assertRaisesRegex(SystemExit, "unresolved slots"):
                table.definition("names")


class Diagnostics(unittest.TestCase):
    def test_same_compiler_failure_clusters_across_function_names_and_paths(self):
        a = "/tmp/a/T.cpp:12:4: error: local_123 was not declared"
        b = "/tmp/b/T.cpp:85:9: error: local_456 was not declared"
        self.assertEqual(candidate.failure_class(a), candidate.failure_class(b))


if __name__ == "__main__":
    unittest.main()
