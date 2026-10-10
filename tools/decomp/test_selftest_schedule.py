"""Scheduling changes only dispatch order; every process/report stays independent."""
import contextlib
from concurrent.futures import ThreadPoolExecutor
import json
import math
import os
from pathlib import Path
import subprocess
import tempfile
import threading
import time
from types import SimpleNamespace
import unittest
from unittest.mock import patch

import hybrid
import selftest_schedule as schedule


def output(names, *, failed=()):
    lines = []
    for name in names:
        count = int(name in failed)
        lines += [f"tlhybrid: begin {name}", f"tlhybrid: timing {name} 0.010 seconds",
                  f"tlhybrid: {name:<48} {'FAIL' if count else 'PASS'} ({count})"]
    lines += [f"tlhybrid: {len(names)} tests, {sum(name in failed for name in names)} failed"]
    return SimpleNamespace(returncode=int(bool(failed)), stderr="\n".join(lines))


class Fixture(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory(prefix="otl-shard-schedule-")
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        (self.root / "decomp/hybrid/tests").mkdir(parents=True)
        (self.root / "decomp/include").mkdir(parents=True)
        self.fixture = self.root / "decomp/hybrid/tests/Test.cpp"
        self.fixture.write_text("fixture v1")
        self.header = self.root / "decomp/include/Test.h"
        self.header.write_text("header v1")
        self.blob = self.root / "blob.elf"
        self.blob.write_bytes(b"fake linked test artifact")
        self.names = ["t" + str(index) for index in range(7)]
        self.environment = patch.dict(os.environ, {"OTL_DECOMP_CACHE": str(self.root / "cache"),
                                                   "OTL_SELFTEST_JOBS": "3"}, clear=True)
        self.environment.start()
        self.addCleanup(self.environment.stop)
        self.mock_inventory = patch.object(schedule, "inventory", return_value=self.names)
        self.mock_inventory.start()
        self.addCleanup(self.mock_inventory.stop)
        self.path = self.write_profile([1, 2, 3, 4, 8, 6, 7])

    def write_profile(self, costs):
        digest = schedule.fixture_digest(self.root)
        artifact = schedule.artifact_fingerprints(self.blob)[0]
        path = schedule.profile_path(self.names, digest, artifact)
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(json.dumps(schedule._profile(self.names, digest, artifact, costs)))
        return path

    def plan(self, **kwargs):
        return schedule.plan(self.blob, self.root, kwargs.pop("only", None), 3, **kwargs)


class Prediction(Fixture):
    def test_longest_first_tie_breaks_by_index_without_changing_modulo(self):
        predicted = self.plan()
        self.assertEqual([12, 10, 9], predicted["predicted_seconds"])
        self.assertEqual([0, 1, 2], predicted["order"])
        self.write_profile([1, 20, 30, 4, 8, 6, 7])
        self.assertEqual([2, 1, 0], self.plan()["order"])
        self.assertEqual(self.names, self.plan()["selected"])
        self.write_profile([1] * 7)
        self.assertEqual([0, 1, 2], self.plan()["order"])

    def test_selected_inventory_uses_exact_prefix_and_selected_modulo(self):
        predicted = self.plan(only="t2,t6,")
        self.assertEqual(["t2", "t6"], predicted["selected"])
        self.assertEqual([3, 7, 0], predicted["predicted_seconds"])
        self.assertEqual([1, 0, 2], predicted["order"])
        self.assertEqual([], self.plan(only=",")["selected"])
        self.assertEqual([0, 1, 2], self.plan(only="absent")["order"])

    def test_changed_unknown_removed_and_reordered_tests_fall_back(self):
        for names in [self.names + ["new_test"], self.names[:-1], list(reversed(self.names)),
                      ["replacement"] + self.names[1:]]:
            with self.subTest(names=names), patch.object(schedule, "inventory", return_value=names):
                result = self.plan(timing_path=self.path)
                self.assertEqual("index", result["method"])
                self.assertEqual([0, 1, 2], result["order"])

    def test_changed_source_and_header_fall_back_even_with_restored_mtime(self):
        for path in [self.fixture, self.header]:
            before, metadata = path.read_text(), path.stat()
            path.write_text(before.replace("v1", "v2"))
            os.utime(path, ns=(metadata.st_atime_ns, metadata.st_mtime_ns))
            self.assertEqual("index", self.plan(timing_path=self.path)["method"])
            path.write_text(before)

    def test_cross_checkout_key_has_no_absolute_paths(self):
        import shutil
        other = self.root / "second_checkout"
        shutil.copytree(self.root / "decomp", other / "decomp")
        (other / "blob.elf").write_bytes(self.blob.read_bytes())
        result = schedule.plan(other / "blob.elf", other, None, 3)
        self.assertEqual("longest-predicted-first", result["method"])
        self.assertEqual(self.plan()["profile_key"], result["profile_key"])

    def test_corrupt_missing_stale_or_incomplete_profile_falls_back(self):
        original = self.path.read_text()
        profile = json.loads(original)
        cases = ["{", "[]", '{"schema":1,"schema":1}', "null", "[" * 1500 + "]" * 1500]
        for field, value in [("schema", True), ("schema", 2), ("inventory", []),
                             ("fixture_sha256", "stale"), ("key", "stale"),
                             ("seconds", [1]), ("seconds", "bad")]:
            cases.append(json.dumps({**profile, field: value}))
        for bad in [float("nan"), float("inf"), -1, True, None, "3"]:
            cases.append(json.dumps({**profile, "seconds": [bad] + profile["seconds"][1:]}))
        for text in cases:
            with self.subTest(text=text):
                self.path.write_text(text)
                self.assertEqual("index", self.plan()["method"])
        self.path.unlink()
        self.assertEqual("index", self.plan()["method"])
        self.path.write_text(original)

    def test_legacy_blob_change_with_same_inventory_falls_back(self):
        self.blob.write_bytes(b"same names but changed custom or generated tests")
        self.assertEqual("index", self.plan()["method"])

    def test_built_test_fingerprint_covers_custom_generated_tests_but_not_production(self):
        obj = self.root / "test_Custom.o"
        obj.write_bytes(b"custom fixture v1")
        schedule.write_inputs(self.blob, [obj])
        self.path = self.write_profile([1, 20, 30, 4, 8, 6, 7])
        self.assertEqual("test-objects", self.plan()["artifact"]["kind"])
        self.blob.write_bytes(b"production changed, same tests")
        schedule.write_inputs(self.blob, [obj])
        self.assertEqual("longest-predicted-first", self.plan()["method"])
        obj.write_bytes(b"custom fixture v2")
        schedule.write_inputs(self.blob, [obj])
        self.assertEqual("index", self.plan()["method"])

    def test_stale_corrupt_missing_test_sidecars_and_changed_objects_use_whole_blob(self):
        obj = self.root / "test_Custom.o"
        obj.write_bytes(b"fixture")
        schedule.write_inputs(self.blob, [obj])
        self.path = self.write_profile([1, 20, 30, 4, 8, 6, 7])
        metadata = self.root / "selftest-inputs.json"
        original = metadata.read_text()
        for bad in ["null", "{", "[]", original.replace('test_Custom.o', '../test_Custom.o'),
                    original.replace('"schema": 1', '"schema": true')]:
            metadata.write_text(bad)
            self.assertEqual("blob", self.plan()["artifact"]["kind"])
        metadata.write_text(original)
        obj.write_bytes(b"changed fixture")
        self.assertEqual("blob", self.plan()["artifact"]["kind"])
        obj.unlink()
        self.assertEqual("blob", self.plan()["artifact"]["kind"])


    def test_finite_cost_corruption_and_unknown_profile_fields_fall_back(self):
        profile = json.loads(self.path.read_text())
        profile["seconds"][0] += 1
        self.path.write_text(json.dumps(profile))
        self.assertEqual("index", self.plan()["method"])
        profile["sha256"] = schedule._profile_hash(profile)
        profile["runtime_pass"] = True
        self.path.write_text(json.dumps(profile))
        self.assertEqual("index", self.plan()["method"])


    def test_explicit_baseline_order_remains_fresh(self):
        self.write_profile([1, 20, 30, 4, 8, 6, 7])
        with patch.dict(os.environ, {"OTL_SELFTEST_ORDER": "index"}):
            self.assertEqual([0, 1, 2], self.plan()["order"])
            self.assertEqual(self.names, self.plan()["selected"])

    def test_unreadable_blob_deterministically_falls_back(self):
        with patch.object(schedule, "inventory", side_effect=ValueError("malformed ELF")):
            self.assertEqual([0, 1, 2], self.plan()["order"])
            self.assertIsNone(self.plan()["selected"])


class Completion(Fixture):
    def test_out_of_order_results_restored_before_strict_parser(self):
        values = [output(self.names[index::3]) for index in range(3)]
        rows = [(2, values[2]), (0, values[0]), (1, values[1])]
        ordered = schedule.ordered_results(rows, 3)
        self.assertEqual(values, ordered)
        schedule.validate_inventory(ordered, self.names)
        code, report = hybrid._selftest_report(ordered)
        self.assertEqual(0, code)
        self.assertEqual("tlhybrid: 7 tests, 0 failed", report[-1])

    def test_missing_duplicate_and_invalid_shard_results_fail_closed(self):
        value = output([])
        for rows in [[(0, value)], [(0, value), (0, value), (2, value)],
                     [(0, value), (1, value), (3, value)],
                     [(0, value), (True, value), (2, value)]]:
            with self.subTest(rows=rows), self.assertRaises(ValueError):
                schedule.ordered_results(rows, 3)

    def test_inventory_missing_duplicate_changed_or_extra_rows_fail_closed(self):
        for altered in [["t0", "t3"], ["t0", "t3", "t3"], ["new", "t3", "t6"],
                        ["t6", "t3", "t0"], ["t0", "t3", "t6", "extra"]]:
            rows = [output(altered)] + [output(self.names[index::3]) for index in (1, 2)]
            with self.subTest(altered=altered), self.assertRaises(ValueError):
                schedule.validate_inventory(rows, self.names)
        for replace in [lambda text: text + "\ntlhybrid: 3 tests, 0 failed",
                        lambda text: text.replace("tlhybrid: timing t3 0.010 seconds\n", ""),
                        lambda text: text.replace("PASS (0)", "PASS (1)")]:
            rows = [output(self.names[index::3]) for index in range(3)]
            rows[0].stderr = replace(rows[0].stderr)
            with self.assertRaises(ValueError):
                schedule.validate_inventory(rows, self.names)

    def test_failed_tests_and_wrong_process_exit_still_reject_success(self):
        rows = [output(self.names[index::3], failed=("t3",) if index == 0 else ()) for index in range(3)]
        schedule.validate_inventory(rows, self.names)
        self.assertEqual(1, hybrid._selftest_report(rows)[0])
        rows[0].returncode = 0
        self.assertEqual(2, hybrid._selftest_report(rows)[0])

    def test_atomic_hints_contain_no_acceptance_status_and_work_at_root(self):
        plan = self.plan()
        rows = [output(self.names[index::3]) for index in range(3)]
        with ThreadPoolExecutor(max_workers=5) as pool:
            list(pool.map(lambda _: schedule.save_costs(plan, rows), range(20)))
        data = json.loads(self.path.read_text())
        self.assertEqual({"schema", "key", "inventory", "fixture_sha256", "artifact", "seconds", "sha256"}, set(data))
        self.assertEqual([0.01] * len(self.names), data["seconds"])
        self.assertEqual("longest-predicted-first", self.plan()["method"])
        self.assertEqual([self.path], list(self.path.parent.iterdir()))

    def test_filtered_or_incomplete_runs_cannot_write_complete_hints(self):
        before = self.path.read_bytes()
        plan = self.plan(only="t2,t6")
        schedule.save_costs(plan, [output(["t2"]), output(["t6"]), output([])])
        self.assertEqual(before, self.path.read_bytes())
        with self.assertRaises(ValueError):
            schedule.save_costs(self.plan(), [output(["t0"]), output([]), output([])])
        self.assertEqual(before, self.path.read_bytes())

    def test_seed_checks_exact_legacy_report_order_and_saves_durations_only(self):
        rows = [output(self.names[index::3]) for index in range(3)]
        code, report = hybrid._selftest_report(rows)
        source = self.root / "old-report.json"
        source.write_text(json.dumps({"code": code, "report": report}))
        target = schedule.seed(self.blob, self.root, source, 3)
        self.assertEqual(self.path, target)
        self.assertEqual([0.01] * 7, json.loads(target.read_text())["seconds"])
        # A wrong old shard count or missing/duplicated current test is rejected.
        for count in (2, 4):
            with self.assertRaises(ValueError):
                schedule.seed(self.blob, self.root, source, count)
        source.write_text(json.dumps({"code": 0, "report": report[:-2] + report[-1:]}))
        with self.assertRaises(ValueError):
            schedule.seed(self.blob, self.root, source, 3)

    def test_seed_accepts_complete_root_log_but_rejects_two_loader_reports(self):
        rows = [output(self.names[index::3]) for index in range(3)]
        _, report = hybrid._selftest_report(rows)
        source = self.root / "root.log"
        source.write_text("compiler diagnostics\n" + "\n".join(report) + "\nhybrid self-test: PASS\n")
        self.assertEqual(self.path, schedule.seed(self.blob, self.root, source, 3))
        source.write_text("\n".join(report + report))
        with self.assertRaises(ValueError):
            schedule.seed(self.blob, self.root, source, 3)


class Dispatch(Fixture):
    def exercise(self, *, timeout=None, exception=None, only=None, bad_rows=False):
        self.write_profile([1, 20, 30, 4, 8, 6, 7])
        dispatched, finished, environments = [], [], []
        state = {"active": 0, "peak": 0}
        lock, semaphore = threading.Lock(), threading.Semaphore(2)
        @contextlib.contextmanager
        def slot(pool):
            self.assertEqual("selftest", pool)
            with semaphore:
                yield
        def run(*args, **kwargs):
            index = int(kwargs["env"]["TLHYBRID_SHARD"].split("/")[0])
            self.assertEqual(120, kwargs["timeout"])
            with lock:
                dispatched.append(index)
                environments.append(kwargs["env"])
                state["active"] += 1
                state["peak"] = max(state["peak"], state["active"])
            try:
                time.sleep((3 - index) * 0.01)
                if index == timeout:
                    raise subprocess.TimeoutExpired("fake", kwargs["timeout"], stderr=b"partial stderr")
                if index == exception:
                    raise OSError("fake process launch failed")
                names = self.names
                if only:
                    names = [name for name in names if name.startswith(tuple(only.split(",")))]
                return output(names[index::3])
            finally:
                with lock:
                    finished.append(index)
                    state["active"] -= 1
        evidence = []
        real_parallel = hybrid.toolchain.parallel_map
        def parallel(fn, indices, **kwargs):
            indices = list(indices)
            evidence.append(indices)
            rows = real_parallel(fn, indices, **kwargs)
            return rows[:-1] if bad_rows else rows
        with patch.object(hybrid, "ROOT", self.root), \
                patch.object(hybrid, "game_env", return_value=(self.root, {"TLHYBRID_FILTER": "inherited"})), \
                patch.object(hybrid.resource_slots, "slot", side_effect=slot), \
                patch.object(hybrid.subprocess, "run", side_effect=run), \
                patch.object(hybrid.toolchain, "parallel_map", side_effect=parallel):
            result = hybrid.selftest(self.blob, self.root / "loader.so", only=only, shards=3)
        return result, dispatched, finished, environments, state, evidence

    def test_real_executor_reorders_dispatch_retains_index_reports_and_slot_limit(self):
        result, dispatched, finished, envs, state, plans = self.exercise()
        self.assertEqual([[2, 1, 0]], plans)
        self.assertEqual([0, 1, 2], sorted(dispatched))
        self.assertEqual([2, 1, 0], finished)
        self.assertLessEqual(state["peak"], 2)
        self.assertEqual(0, result[0])
        begins = [line for line in result[1] if line.startswith("tlhybrid: begin ")]
        self.assertEqual(["tlhybrid: begin " + name for i in range(3) for name in self.names[i::3]], begins)
        self.assertTrue(all("TLHYBRID_FILTER" not in env for env in envs))
        evidence = json.loads((self.root / "selftest-timing.json").read_text())
        self.assertEqual({"environment", "schedule", "execute", "parse"}, set(evidence["phases"]))
        self.assertEqual(3, len(evidence["shards"]))
        for row in evidence["shards"]:
            stamps = [row[field] for field in ("enqueued", "dispatched", "slot_acquired", "process_started", "ended")]
            self.assertEqual(sorted(stamps), stamps)
            self.assertAlmostEqual(row["ended"] - row["process_started"], row["elapsed"])
            self.assertEqual(0, row["returncode"])

    def test_timeout_executes_other_shards_and_retains_diagnostic(self):
        result, dispatched, _, _, _, _ = self.exercise(timeout=1)
        self.assertEqual(2, result[0])
        self.assertEqual([0, 1, 2], sorted(dispatched))
        self.assertIn("timeout after 120 seconds", "\n".join(result[1]))
        evidence = json.loads((self.root / "selftest-timing.json").read_text())
        self.assertEqual(120, evidence["shards"][1]["timeout"])
        self.assertEqual(2, evidence["shards"][1]["returncode"])

    def test_missing_results_cannot_return_success(self):
        self.assertEqual(2, self.exercise(bad_rows=True)[0][0])

    def test_spawn_error_propagates_after_other_shards_finish_with_evidence(self):
        with self.assertRaisesRegex(OSError, "fake process launch failed"):
            self.exercise(exception=1)
        evidence = json.loads((self.root / "selftest-timing.json").read_text())
        self.assertTrue(all(row["ended"] is not None for row in evidence["shards"]))
        self.assertIn("OSError", evidence["shards"][1]["error"])

    def test_exactly_sixty_shards_even_with_fewer_selected_tests(self):
        evidence, indices = [], []
        def run(*args, **kwargs):
            index, count = map(int, kwargs["env"]["TLHYBRID_SHARD"].split("/"))
            self.assertEqual(60, count)
            indices.append(index)
            return output(self.names[index::count])
        with patch.object(hybrid, "ROOT", self.root), \
                patch.object(hybrid, "game_env", return_value=(self.root, {})), \
                patch.object(hybrid.resource_slots, "slot", side_effect=lambda _: contextlib.nullcontext()), \
                patch.object(hybrid.subprocess, "run", side_effect=run), \
                patch.object(schedule, "write_timing", side_effect=lambda blob, row: evidence.append(row)):
            result = hybrid.selftest(self.blob, None, shards=60)
        self.assertEqual(0, result[0])
        self.assertEqual(list(range(60)), sorted(indices))
        self.assertEqual(60, len(evidence[0]["shards"]))
        self.assertEqual("tlhybrid: 7 tests, 0 failed", result[1][-1])

    def test_diagnostic_write_failures_do_not_change_fresh_verdict(self):
        import io
        with patch.object(schedule, "_atomic_json", side_effect=OSError("disk full")), \
                contextlib.redirect_stderr(io.StringIO()) as errors:
            result, *_ = self.exercise()
        self.assertEqual(0, result[0])
        self.assertIn("disk full", errors.getvalue())


    def test_broken_stderr_and_diagnostic_disk_error_preserve_primary_exception(self):
        import sys
        primary = RuntimeError("original selftest setup failure")
        with patch.object(hybrid, "_selftest", side_effect=primary), \
                patch.object(schedule, "_atomic_json", side_effect=OSError("disk full")), \
                patch.object(sys.stderr, "write", side_effect=OSError("broken stderr")):
            with self.assertRaises(RuntimeError) as caught:
                hybrid.selftest(self.blob, None, shards=3)
            self.assertIs(primary, caught.exception)
            schedule.write_inputs(self.blob, [])  # Optional build diagnostics also cannot raise.


    def test_slot_wait_does_not_consume_process_timeout(self):
        result, *_ = self.exercise()
        self.assertEqual(0, result[0])
        evidence = json.loads((self.root / "selftest-timing.json").read_text())
        self.assertGreater(max(row["slot_wait_elapsed"] for row in evidence["shards"]), 0.005)


if __name__ == "__main__":
    unittest.main()
