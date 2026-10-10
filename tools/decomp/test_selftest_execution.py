#!/usr/bin/env python3
"""No acceptance from an empty, filtered or interrupted self-test process."""
import contextlib
import io
from pathlib import Path
import shutil
import subprocess
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

import hybrid
import llm_loop
import mutate


@unittest.skipUnless(shutil.which("cc"), "requires host C compiler")
class NativeDispatch(unittest.TestCase):
    def test_real_loader_selection_and_empty_shards(self):
        source = r'''
#define __libc_start_main research_unused_start
#include "loader.c"
#undef __libc_start_main
static int calls;
static int pass_case(const tlhybrid_host *host) { (void)host; calls++; return 0; }
static int fail_case(const tlhybrid_host *host) { (void)host; calls++; return 1; }
int main(int argc, char **argv) {
    if (argc != 3) return 9;
    tlhybrid_test tests[2] = {{"control_pass", pass_case}, {"control_fail", fail_case}};
    Elf64_Ehdr eh = {0}; Elf64_Shdr sh = {0}; struct blob b = {0};
    eh.e_shnum = 1; sh.sh_name = 1; sh.sh_addr = (uintptr_t)tests; sh.sh_size = sizeof(tests);
    b.eh = &eh; b.sh = &sh; b.shstr = "\0.tlhybrid.tests\0";
    if (*argv[1]) setenv("TLHYBRID_FILTER", argv[1], 1); else unsetenv("TLHYBRID_FILTER");
    if (*argv[2]) setenv("TLHYBRID_SHARD", argv[2], 1); else unsetenv("TLHYBRID_SHARD");
    int code = run_tests(&b);
    printf("%d %d\n", code, calls);
    return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="otl-dispatch-test-") as folder:
            src, binary = Path(folder) / "probe.c", Path(folder) / "probe"
            src.write_text(source)
            subprocess.run(["cc", "-std=gnu11", "-O0", "-I", str(hybrid.HYBRID),
                            str(src), "-ldl", "-o", str(binary)], check=True, capture_output=True)
            for only, shard, expected in [("missing_case", "", "2 0"), ("control_pass", "", "0 1"),
                                          ("control_fail", "", "1 1"), ("", "", "1 2"),
                                          ("control_pass", "3/4", "0 0"), ("", "0/2", "0 1")]:
                with self.subTest(only=only, shard=shard):
                    result = subprocess.run([str(binary), only, shard], check=True, capture_output=True, text=True)
                    self.assertEqual(expected, result.stdout.strip())


class ProcessGate(unittest.TestCase):
    def exercise(self, results, only=None):
        environments = []
        def environment(blob, loader, extra, headless):
            self.assertTrue(headless)
            return Path("/tmp"), {"TLHYBRID_FILTER": "inherited", **extra}
        def run(*args, **kwargs):
            environments.append(kwargs["env"])
            return results[len(environments) - 1]
        with patch.object(hybrid, "game_env", side_effect=environment), \
                patch.object(hybrid.toolchain, "parallel_map", side_effect=lambda fn, rows, **kwargs: [fn(row) for row in rows]), \
                patch.object(hybrid.subprocess, "run", side_effect=run):
            outcome = hybrid.selftest(None, None, only=only, shards=len(results))
        return outcome, environments

    def result(self, code=0, ran=1, failed=0, extra=""):
        return SimpleNamespace(returncode=code, stderr=extra + f"tlhybrid: {ran} tests, {failed} failed\n")

    def test_full_run_removes_ambient_filter_and_explicit_filter_survives(self):
        outcome, environments = self.exercise([self.result()])
        self.assertEqual(0, outcome[0])
        self.assertNotIn("TLHYBRID_FILTER", environments[0])
        outcome, environments = self.exercise([self.result()], only="requested")
        self.assertEqual("requested", environments[0]["TLHYBRID_FILTER"])

    def test_aggregate_requires_at_least_one_executed_test(self):
        self.assertNotEqual(0, self.exercise([self.result(ran=0)])[0][0])
        outcome, _ = self.exercise([self.result(), self.result(ran=0)])
        self.assertEqual(0, outcome[0])
        self.assertIn("tlhybrid: 1 tests, 0 failed", outcome[1])

    def test_crash_or_inconsistent_exit_cannot_use_positive_statistics(self):
        for code in (-11, 1, 97):
            with self.subTest(code=code):
                outcome, _ = self.exercise([self.result(code=code, extra="    stats auto_1 same 30 both-failed 0 different 0\n")])
                self.assertEqual(2, outcome[0])
        outcome, _ = self.exercise([SimpleNamespace(returncode=0, stderr="    stats auto_1 same 30 both-failed 0 different 0\n")])
        self.assertEqual(2, outcome[0])
        self.assertEqual(2, self.exercise([self.result(failed=1)])[0][0])

    def test_complete_failed_test_is_a_valid_mutation_verdict(self):
        outcome, _ = self.exercise([self.result(code=1, failed=1)])
        self.assertEqual(1, outcome[0])

    def test_negative_shard_count_is_not_an_empty_success(self):
        with self.assertRaises(ValueError):
            hybrid.selftest(None, None, shards=-1)

    def test_mutation_discards_incomplete_process_and_timeout(self):
        report = ["    stats auto_1 same 30 both-failed 0 different 0 incomplete 0"]
        with patch.object(mutate.hybrid, "build", return_value=(None, None)), \
                patch.object(mutate.hybrid, "selftest", return_value=(2, report)):
            self.assertEqual(({}, []), mutate.build_and_test(None, [], ["auto_1"], Path("/tmp")))
        with patch.object(mutate.hybrid, "build", return_value=(None, None)), \
                patch.object(mutate.hybrid, "selftest", side_effect=subprocess.TimeoutExpired("probe", 1)):
            self.assertEqual(({}, []), mutate.build_and_test(None, [], ["auto_1"], Path("/tmp")))


class CandidateGate(unittest.TestCase):
    def exercise(self, code=0, different=0, incomplete=0):
        with tempfile.TemporaryDirectory(prefix="otl-candidate-gate-") as folder:
            root = Path(folder)
            function = {"address": "0x100", "demangled": "CProbe::f()"}
            loop = llm_loop.Loop.__new__(llm_loop.Loop)
            loop.source, loop.work, loop.rounds = root / "Probe.cpp", root, 5
            loop.accepted, loop.status, loop.original = {}, {}, None
            loop.unit = lambda extra=(): "\n".join(extra) + "\n"
            pending = {"0x100": {"f": function, "code": "int f(){return 7;}"}}
            report = [f"    stats auto_100 same 20 both-failed 0 different {different} incomplete {incomplete}"]
            generator = SimpleNamespace(write=lambda _: ([function], {}))
            with patch.object(llm_loop.autotest, "Generator", return_value=generator), \
                    patch.object(llm_loop.autotest, "OUT", root), \
                    patch.object(llm_loop.objdiff, "compare_source", return_value={}), \
                    patch.object(llm_loop.hybrid, "build", return_value=(None, None)), \
                    patch.object(llm_loop.hybrid, "selftest", return_value=(code, report)), \
                    contextlib.redirect_stdout(io.StringIO()):
                loop.test(pending, {"0x100": "fixture difference"}, 1)
            return bool(loop.accepted)

    def test_complete_success_is_accepted(self):
        self.assertTrue(self.exercise())

    def test_failed_process_incomplete_or_different_capture_is_rejected(self):
        self.assertFalse(self.exercise(code=97))
        self.assertFalse(self.exercise(code=-11))
        self.assertFalse(self.exercise(different=1))
        self.assertFalse(self.exercise(incomplete=1))


if __name__ == "__main__":
    unittest.main()
