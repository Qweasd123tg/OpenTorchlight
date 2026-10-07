import multiprocessing
import os
from pathlib import Path
import tempfile
import time
import unittest
from unittest.mock import patch

import resource_slots


def occupy(root, ready):
    with resource_slots.slot("compiler", root=root, slots=1):
        ready.set()
        time.sleep(30)


def measured(root, active, peak, guard):
    with resource_slots.slot("compiler", root=root, slots=2, timeout=10):
        with guard:
            active.value += 1
            peak.value = max(peak.value, active.value)
        time.sleep(0.1)
        with guard:
            active.value -= 1


class Slots(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        env = patch.dict(os.environ)
        env.start()
        self.addCleanup(env.stop)
        for name in resource_slots.POOLS.values():
            os.environ.pop(name, None)

    def test_exception_releases_slot(self):
        with self.assertRaisesRegex(RuntimeError, "body"):
            with resource_slots.slot("compiler", root=self.root, slots=1):
                raise RuntimeError("body")
        with resource_slots.slot("compiler", root=self.root, slots=1, timeout=0):
            pass

    def test_timeout_and_active_resize(self):
        with resource_slots.slot("compiler", root=self.root, slots=1):
            with self.assertRaisesRegex(RuntimeError, "waiting"):
                with resource_slots.slot("compiler", root=self.root, slots=1, timeout=0):
                    self.fail("second worker acquired the same slot")
            with self.assertRaisesRegex(RuntimeError, "active"):
                resource_slots.configure("compiler", 2, root=self.root)
        resource_slots.configure("compiler", 2, root=self.root)
        with resource_slots.slot("compiler", root=self.root, slots=2):
            with resource_slots.slot("compiler", root=self.root, slots=2, timeout=0):
                pass

    def test_different_capacity_cannot_bypass_limit(self):
        resource_slots.configure("compiler", 1, root=self.root)
        with self.assertRaisesRegex(ValueError, "already has"):
            with resource_slots.slot("compiler", root=self.root, slots=2):
                self.fail("inconsistent capacities permitted")

    def test_invalid_configuration(self):
        for value in (0, -1, 65):
            with self.assertRaises(ValueError):
                resource_slots.configure("compiler", value, root=self.root)
        with self.assertRaises(ValueError):
            with resource_slots.slot("../compiler", root=self.root):
                pass
        for timeout in (-1, float("nan"), float("inf")):
            with self.assertRaises(ValueError):
                with resource_slots.slot("compiler", root=self.root, timeout=timeout):
                    pass

    def test_process_crash_releases_slot(self):
        context = multiprocessing.get_context("spawn")
        ready = context.Event()
        process = context.Process(target=occupy, args=(str(self.root), ready))
        process.start()
        try:
            self.assertTrue(ready.wait(10))
            with self.assertRaises(RuntimeError):
                with resource_slots.slot("compiler", root=self.root, slots=1, timeout=0):
                    pass
        finally:
            process.terminate()
            process.join(10)
        with resource_slots.slot("compiler", root=self.root, slots=1, timeout=0):
            pass

    def test_process_concurrency_is_globally_bounded(self):
        context = multiprocessing.get_context("spawn")
        active, peak = context.Value("i", 0), context.Value("i", 0)
        guard = context.Lock()
        processes = [context.Process(target=measured, args=(str(self.root), active, peak, guard)) for _ in range(6)]
        try:
            for process in processes:
                process.start()
            for process in processes:
                process.join(15)
                self.assertEqual(0, process.exitcode)
            self.assertLessEqual(peak.value, 2)
            self.assertGreater(peak.value, 0)
            self.assertEqual(0, active.value)
        finally:
            for process in processes:
                if process.is_alive():
                    process.terminate()
                    process.join(10)


if __name__ == "__main__":
    unittest.main()
