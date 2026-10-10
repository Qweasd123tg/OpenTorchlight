"""Standalone C++98 Detour storage regression. No game process is launched.

Run with the configured original compiler:
    python3 -m unittest discover -s tools/decomp -p test_detour_storage.py -v

As in test_capture_narrow_text, pinned GCC compiles the C++ code; the host
C++ driver only links the resulting object against the available libc.
"""
from pathlib import Path
import subprocess
import tempfile
import unittest

import toolchain

ROOT = Path(__file__).resolve().parents[2]
HEADER = ROOT / "decomp/hybrid/tests/Detour.h"
FIXTURE = Path(__file__).with_name("fixtures") / "DetourStorage.cpp"
WRAPS = ("mmap", "munmap", "mprotect", "malloc", "calloc", "realloc", "free")


class DetourStorage(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temporary = tempfile.TemporaryDirectory(prefix="detour-storage-")
        cls.addClassCleanup(cls.temporary.cleanup)
        cls.folder = Path(cls.temporary.name)
        cls.header = HEADER.read_text()
        cls.executable = cls.compile_fixture("detour-storage", cls.header)

    @classmethod
    def compile_fixture(cls, name, header):
        folder = cls.folder / name
        folder.mkdir()
        (folder / "Detour.h").write_text(header)
        obj = folder / "proof.o"
        toolchain.compile_source(
            FIXTURE, obj,
            ["-std=gnu++98", "-Wall", "-Wextra", "-Werror", "-I", str(folder)],
            cache=False, quiet=True,
        )
        executable = folder / "proof"
        subprocess.run(
            ["c++", "-no-pie", str(obj), "-o", str(executable), "-ldl"]
            + ["-Wl,--wrap=" + symbol for symbol in WRAPS],
            check=True, capture_output=True, text=True,
        )
        return executable

    def run_fixture(self, executable, *arguments):
        return subprocess.run(
            [str(executable), *map(str, arguments)],
            capture_output=True, text=True, timeout=60,
        )

    def test_old_boundary_and_substantially_larger_sets(self):
        for count in (63, 64, 65, 4097):
            with self.subTest(sites=count):
                result = self.run_fixture(self.executable, count)
                self.assertEqual(0, result.returncode, result.stdout + result.stderr)
                self.assertIn("PASS requested growth control", result.stdout)

    def test_coverage_allocator_isolation_and_failure_paths(self):
        result = self.run_fixture(self.executable)
        self.assertEqual(0, result.returncode, result.stdout + result.stderr)
        self.assertIn("PASS all requested Detour capacity controls", result.stdout)

    def test_semantic_mutations_cannot_pass(self):
        changes = {
            "silent-storage-failure": (
                "fail(StorageFailure, at);", "(void)at; // deliberately omit failure"
            ),
            "missing-linked-address": (
                "if (!failed() && linked != original)", "if (false && linked != original)"
            ),
            "forward-restoration": (
                "m_last->patches[m_last->count - 1]", "m_last->patches[0]"
            ),
            "skip-restored-protection": (
                "if (!writable(p.at, p.protection))", "if (false)"
            ),
        }
        for name, (before, after) in changes.items():
            with self.subTest(mutation=name):
                self.assertEqual(1, self.header.count(before), "Mutation anchor changed; update the control explicitly")
                executable = self.compile_fixture(name, self.header.replace(before, after))
                result = self.run_fixture(executable)
                self.assertEqual(1, result.returncode, result.stdout + result.stderr)
                self.assertIn("FAIL:", result.stderr)

    def test_failed_restore_cannot_be_ignored(self):
        before = "fail(ProtectionFailure, p.at);\n                    std::abort();"
        self.assertEqual(2, self.header.count(before))
        mutant = self.header.replace(before, "fail(ProtectionFailure, p.at);\n                    return;", 1)
        executable = self.compile_fixture("ignored-restore-failure", mutant)
        result = self.run_fixture(executable)
        self.assertEqual(1, result.returncode, result.stdout + result.stderr)
        self.assertIn("failed restoration must abort before any following statement", result.stderr)

    def test_owning_set_is_not_copyable(self):
        for name, operation in (
            ("construction", "detour::Set b(a);"),
            ("assignment", "detour::Set b; b = a;"),
        ):
            with self.subTest(operation=name):
                source = self.folder / (name + ".cpp")
                source.write_text('#include "Detour.h"\nvoid copy_set() { detour::Set a; ' + operation + ' }\n')
                with self.assertRaises(SystemExit) as failure:
                    toolchain.compile_source(
                        source, self.folder / (name + ".o"),
                        ["-std=gnu++98", "-I", str(self.folder / "detour-storage")],
                        cache=False, quiet=True,
                    )
                self.assertIn("private", str(failure.exception))


if __name__ == "__main__":
    unittest.main()
