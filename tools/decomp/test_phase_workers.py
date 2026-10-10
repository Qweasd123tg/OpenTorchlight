"""Per-phase concurrency changes scheduling only, not ordering or error propagation."""
import ast
import os
from pathlib import Path
import threading
import unittest
from unittest.mock import patch
import toolchain

class PhaseWorkers(unittest.TestCase):
    def setUp(self):
        clean = patch.dict(os.environ, {"OTL_JOBS": "4"}, clear=True)
        clean.start(); self.addCleanup(clean.stop)

    def test_legacy_fallback_unchanged(self):
        for phase in toolchain.PHASE_JOB_ENV:
            self.assertEqual(toolchain.phase_jobs(phase), toolchain.jobs())
        with patch.dict(os.environ, {}, clear=True), patch.object(toolchain.os, "cpu_count", return_value=9):
            self.assertEqual(toolchain.jobs(), 5)
            self.assertEqual(toolchain.phase_jobs("build"), 5)

    def test_independent_phase_overrides(self):
        with patch.dict(os.environ, {"OTL_COMPARE_JOBS":"2", "OTL_BUILD_JOBS":"6", "OTL_SELFTEST_JOBS":"8"}):
            self.assertEqual([toolchain.phase_jobs(p) for p in ("compare","build","selftest")], [2,6,8])
            self.assertEqual(toolchain.jobs(), 4)

    def test_partial_override_does_not_change_other_phases(self):
        for phase, variable in toolchain.PHASE_JOB_ENV.items():
            with patch.dict(os.environ, {variable:"6"}):
                for other in toolchain.PHASE_JOB_ENV:
                    self.assertEqual(toolchain.phase_jobs(other), 6 if phase == other else 4)

    def test_empty_override_falls_back(self):
        for phase, variable in toolchain.PHASE_JOB_ENV.items():
            with patch.dict(os.environ, {variable:""}):
                self.assertEqual(toolchain.phase_jobs(phase), 4)

    def test_bad_override_is_not_silently_accepted(self):
        for phase, variable in toolchain.PHASE_JOB_ENV.items():
            for value in ("0", "-1", "many", "1.5"):
                with self.subTest(phase=phase, value=value), patch.dict(os.environ, {variable:value}):
                    with self.assertRaises(ValueError): toolchain.phase_jobs(phase)

    def test_unknown_phase_fails_before_work(self):
        with self.assertRaises(ValueError): toolchain.parallel_map(lambda x:x, [], phase="unknown")

    def test_default_serial_path_preserves_order(self):
        with patch.dict(os.environ, {"OTL_JOBS":"1"}), patch.object(toolchain,"ThreadPoolExecutor") as executor:
            self.assertEqual(toolchain.parallel_map(lambda x:x*x, [3,1,2]), [9,1,4])
            executor.assert_not_called()

    def test_override_is_bounded_and_preserves_result_order(self):
        barrier = threading.Barrier(3)
        lock = threading.Lock()
        state = {"active":0,"peak":0}
        def work(x):
            with lock:
                state["active"] += 1
                state["peak"] = max(state["peak"],state["active"])
            try:
                if x < 3: barrier.wait(timeout=5)
                return x*x
            finally:
                with lock: state["active"] -= 1
        with patch.dict(os.environ, {"OTL_JOBS":"1","OTL_BUILD_JOBS":"3"}):
            self.assertEqual(toolchain.parallel_map(work, range(12), phase="build"), [x*x for x in range(12)])
        self.assertEqual(state, {"active":0,"peak":3})

    def test_system_exit_propagates_after_other_work_finishes(self):
        completed = []
        def work(x):
            if x == 0: raise SystemExit(9)
            completed.append(x)
            return x
        with patch.dict(os.environ, {"OTL_SELFTEST_JOBS":"3"}):
            with self.assertRaises(SystemExit) as raised:
                toolchain.parallel_map(work, range(8), phase="selftest")
        self.assertEqual(raised.exception.code, 9)
        self.assertEqual(sorted(completed), list(range(1,8)))

    def test_all_core_call_sites_are_routed(self):
        expected = {"standalone.py":["build"], "check.py":["compare"], "hybrid.py":["build","selftest"],
                    "publication.py":["compare","compare","compare"]}
        for name, phases in expected.items():
            tree=ast.parse(Path(toolchain.__file__).with_name(name).read_text())
            calls=[node for node in ast.walk(tree) if isinstance(node,ast.Call) and isinstance(node.func,ast.Attribute) and node.func.attr=="parallel_map"]
            actual=[next(k.value.value for k in call.keywords if k.arg=="phase") for call in calls]
            self.assertEqual(sorted(actual), sorted(phases))

if __name__ == "__main__": unittest.main()
