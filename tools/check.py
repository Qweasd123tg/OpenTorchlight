#!/usr/bin/env python3
"""Run dependency-separated OpenTorchlight checks; skipped required tests are NOT RUN.

This is port-native verification infrastructure, not an original-game algorithm.
The JSON report distinguishes asset compatibility, regression and ELF evidence.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import time
import xml.etree.ElementTree as ET
from datetime import datetime, timezone

sys.path.insert(0, str(Path(__file__).resolve().parent))
from automation_state import changed_paths, snapshot_changes, source_snapshot, validate_output, write_json
from check_selection import close_fixtures, command_output, dependency_index, make_plan, properties

GROUPS = ("core", "assets", "reference", "render", "desktop")


def requested_groups(args: argparse.Namespace) -> set[str]:
    if args.recover:
        return {"core", "assets", "reference"}
    if args.all:
        return set(GROUPS)
    selected = {g for g in GROUPS if bool(getattr(args, g))}
    if args.directory is not None:
        selected.update(("core", "assets", "reference"))
    return selected or {"core"}


def adapter_options(groups: set[str]) -> list[str]:
    return ["-DTORCHLIGHT_ENABLE_DESKTOP=" + ("ON" if "desktop" in groups else "OFF"),
            "-DTORCHLIGHT_ENABLE_RENDER=" + ("ON" if groups & {"render", "desktop"} else "OFF")]


def evidence_role(test: dict) -> str:
    """Describe what was executed independently of its PASS/FAIL result."""
    labels = set(properties(test).get("LABELS", []))
    if "reference" in labels:
        return "bounded-reference-comparison"
    if labels & {"render", "desktop"}:
        return "integration-regression"
    if "assets" in labels:
        return "resource-contract"
    return "unit-regression"


def summarize_junit(path: Path, returncode: int) -> dict:
    """CTest can return zero despite SKIP_RETURN_CODE. Never turn that into PASS."""
    if not path.is_file():
        return {"status": "FAILED" if returncode else "NOT RUN", "passed": 0,
                "failed": 0, "skipped": 0, "tests": [], "reason": "No CTest result file"}
    try:
        root = ET.parse(path).getroot()
        tests = []
        for test in root.iter("testcase"):
            skipped = test.find("skipped") is not None or test.get("status") in ("notrun", "disabled")
            failed = test.find("failure") is not None or test.find("error") is not None
            status = "NOT RUN" if skipped else "FAILED" if failed else "PASSED"
            tests.append({"name": test.get("name", ""), "status": status,
                          "seconds": test.get("time", "0")})
        passed = sum(t["status"] == "PASSED" for t in tests)
        failed = sum(t["status"] == "FAILED" for t in tests)
        skipped = sum(t["status"] == "NOT RUN" for t in tests)
        status = "FAILED" if failed or returncode else "NOT RUN" if skipped or not tests else "PASSED"
        return {"status": status, "passed": passed, "failed": failed,
                "skipped": skipped, "tests": tests,
                "reason": "One or more required tests did not execute" if skipped else
                          "No registered tests for this group" if not tests else ""}
    except (OSError, ET.ParseError, ValueError) as exc:
        return {"status": "FAILED", "passed": 0, "failed": 0, "skipped": 0,
                "tests": [], "reason": f"Invalid CTest result: {exc}"}


def digest(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def write_report(report: dict, path: Path) -> None:
    write_json(path, report)
    print("\nGROUP       STATUS       PASS / FAIL / SKIP    REASON")
    for group in GROUPS:
        item = report["groups"][group]
        print(f"{group:11} {item['status']:12} {item.get('passed',0):4} / {item.get('failed',0):4} / "
              f"{item.get('skipped',0):4}    {item.get('reason','')}")
    print(f"Report: {path}")
    print("Results validate the recorded test boundaries; function completion is recorded in function-transfer.json.")


def parser() -> argparse.ArgumentParser:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("directory", nargs="?", type=Path,
                   help="core/assets/reference inputs; UI integration selected separately")
    p.add_argument("--portable", "--core", dest="core", action="store_true")
    p.add_argument("--assets", type=Path, metavar="DIR")
    p.add_argument("--reference", type=Path, metavar="ELF")
    p.add_argument("--reference-python", type=Path, metavar="EXECUTABLE",
                   help="optional PIE Python for original fixed-address comparison probes")
    p.add_argument("--render", action="store_true")
    p.add_argument("--desktop", action="store_true")
    p.add_argument("--all", action="store_true", help="require all five groups")
    p.add_argument("--game-dir", type=Path, help="resource input without selecting the assets group")
    p.add_argument("--build-dir", type=Path)
    p.add_argument("--report", type=Path)
    selection = p.add_mutually_exclusive_group()
    selection.add_argument("--changed", nargs="?", const="HEAD", metavar="REV",
                   help="select affected tests from tracked+untracked changes vs REV (default HEAD); unknown inputs widen")
    selection.add_argument("--since-report", type=Path, metavar="JSON",
                           help="compare content against a prior full successful report, including a dirty checkout")
    selection.add_argument("--test", action="append", metavar="NAME",
                           help="run exact named contract check (repeatable), plus required fixtures")
    selection.add_argument("--recover", action="store_true",
                           help="generate reviewed production recipes, build their real consumers and run original/resource/registry gates")
    p.add_argument("--plan", action="store_true", help="configure/discover and report selection without building/running tests")
    p.add_argument("--jobs", type=int, default=int(os.environ.get("TORCHLIGHT_BUILD_JOBS", "2")))
    return p


def main(argv: list[str] | None = None) -> int:
    args = parser().parse_args(argv)
    if args.recover and (args.render or args.desktop or args.all):
        parser().error("--recover selects the reviewed CPU/resource/reference chain; integration groups are separate")
    if args.reference_python is not None and (not args.reference_python.is_file() or
                                            not os.access(args.reference_python, os.X_OK)):
        parser().error("--reference-python must be an executable file")
    if args.jobs < 1:
        parser().error("--jobs must be positive")
    root = Path(__file__).resolve().parents[1]
    build = (args.build_dir or root / "build-verification").resolve()
    output = (args.report or build / "verification.json").resolve()
    if output.suffix.lower() != ".json":
        parser().error("--report must have a .json extension")
    game = args.assets or args.game_dir or args.directory
    original = args.reference
    selected = requested_groups(args)
    if game is None and original is not None:
        game = original.parent
    if original is None and "reference" in selected and game is not None:
        original = game / "Torchlight.bin.x86_64"
    game = game.resolve() if game is not None else None
    original = original.resolve() if original is not None else None
    # Reports/builds must never overwrite a read-only external input or project source.
    inputs = [p for p in (game / "pak.zip" if game else None, original) if p is not None]
    if output in inputs or output == Path(__file__).resolve() or build in inputs:
        parser().error("output collides with a read-only input")
    try:
        protected = ([game] if game and (game / "pak.zip").is_file() else []) + (
            [original.parent] if original and original.is_file() else [])
        validate_output(root, build, protected, directory=True)
        validate_output(root, output, protected)
        before = source_snapshot(root)
        baseline, baseline_reason = None, ""
        changes = changed_paths(root, args.changed) if args.changed is not None else None
        if args.since_report is not None:
            if args.since_report.resolve() == output:
                raise ValueError("--since-report and --report must name different files")
            baseline = json.loads(args.since_report.read_text())
            if not isinstance(baseline, dict):
                raise ValueError("Baseline must be a verification report object")
            if (baseline.get("kind") != "verification-run" or baseline.get("plan_only") or
                baseline.get("source_consistent") is not True or
                baseline.get("selection", {}).get("not_a_full_gate") or
                not baseline.get("source", {}).get("files") or
                any(baseline.get("groups", {}).get(g, {}).get("status") != "PASSED" for g in selected)):
                baseline_reason = "Baseline is not a full successful gate for every requested group"
            else:
                changes = snapshot_changes(baseline["source"], before)
    except (OSError, ValueError, KeyError, TypeError) as exc:
        parser().error(str(exc))
    report = {"schema": 1, "kind": "verification-run", "groups": {}, "inputs": {},
              "started_at": datetime.now(timezone.utc).isoformat(),
              "source": before, "plan_only": args.plan,
              "baseline": str(args.since_report) if args.since_report else None,
              "recovery_requested": args.recover,
              "assessment": {"original_status_promotions": 0,
                             "function_completion_source": "research/function-transfer.json",
                             "test_counts_measure": "executed checks within their recorded boundaries"},
              "evidence": {"core": "authored fixtures and bounded export comparisons",
                           "assets": "resource-derived; not ELF parity",
                           "reference": "pinned original comparisons",
                           "render": "explicit UI/graphics integration; not original-game parity",
                           "desktop": "full window adapter; not original-game parity"}}
    for group in GROUPS:
        report["groups"][group] = {"requested": group in selected, "status": "NOT RUN",
                                  "reason": "Not requested" if group not in selected else "Not started"}
    unavailable = {}
    if "assets" in selected and (not game or not (game / "pak.zip").is_file()):
        unavailable["assets"] = "Required pak.zip is absent"
    if "reference" in selected and (not original or not original.is_file()):
        unavailable["reference"] = "Required original ELF is absent"
    if "render" in selected and (not game or not (game / "pak.zip").is_file()):
        unavailable["render"] = "Full-scene rendering requires pak.zip (--game-dir DIR)"
    if "desktop" in selected and (not game or not (game / "pak.zip").is_file()):
        unavailable["desktop"] = "Full desktop scenario requires pak.zip"
    for group, reason in unavailable.items():
        report["groups"][group]["reason"] = reason
    runnable = selected - unavailable.keys()
    if args.recover and unavailable:
        for group in runnable:
            report["groups"][group]["reason"] = "Recovery chain requires all original/resource inputs; build not attempted"
        runnable = set()
    plan = None
    try:
        for name, path in (("pak", game / "pak.zip" if game else None), ("elf", original)):
            if path and path.is_file():
                report["inputs"][name] = {"path": str(path), "sha256": digest(path)}
        if runnable:
            build.mkdir(parents=True, exist_ok=True)
            log_dir = build / "verification-logs"
            log_dir.mkdir(exist_ok=True)

            def run(command: list[str], name: str) -> int:
                print("+", " ".join(command), flush=True)
                with (log_dir / (name + ".log")).open("w", encoding="utf-8") as log:
                    child = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                             text=True, encoding="utf-8", errors="replace")
                    assert child.stdout is not None
                    for line in child.stdout:
                        log.write(line)
                        print(line, end="", flush=True)
                    return child.wait()

            # Explicitly clear absent inputs, so a previous full cache cannot leak
            # tests/resources into a later --core invocation.
            configure = ["cmake", "-S", str(root), "-B", str(build), "-G", "Ninja",
                         "-DCMAKE_BUILD_TYPE=Debug", "-DBUILD_TESTING=ON",
                         *adapter_options(selected),
                         "-DTORCHLIGHT_GAME_DIR=" + (str(game) if game else ""),
                         "-DTORCHLIGHT_ORIGINAL=" + (str(original) if original and original.is_file() else "")]
            if args.reference_python is not None:
                configure.append("-DTORCHLIGHT_REFERENCE_PYTHON=" + str(args.reference_python.resolve()))
            phase = "configure"
            code = run(configure, phase)
            if not code:
                # Preserve and expose a deliberately configured instrumentation budget.
                cache = (build / "CMakeCache.txt").read_text(encoding="utf-8")
                budget = next((line.split("=",1)[1] for line in cache.splitlines()
                               if line.startswith("TORCHLIGHT_TEST_TIMEOUT_SCALE:STRING=")), "1")
                report["test_timeout_scale"] = int(budget)
                report["reference_python"] = next((line.split("=",1)[1] for line in cache.splitlines()
                    if line.startswith("TORCHLIGHT_REFERENCE_PYTHON:FILEPATH=")), "")
                report["configuration_sha256"] = hashlib.sha256(cache.encode()).hexdigest()
                if baseline and (baseline.get("inputs") != report["inputs"] or
                                 baseline.get("configuration_sha256") != report["configuration_sha256"]):
                    baseline_reason = "Original inputs or CMake configuration differ from baseline"
                discovery = subprocess.run(["ctest", "--test-dir", str(build), "--show-only=json-v1"],
                                           capture_output=True, text=True, check=False)
                (log_dir / "discovery.json").write_text(discovery.stdout, encoding="utf-8")
                if discovery.returncode:
                    raise ValueError("CTest discovery failed: " + discovery.stderr)
                registered = json.loads(discovery.stdout).get("tests", [])
                labels = {label for test in registered for prop in test.get("properties", [])
                          if prop.get("name") == "LABELS" for label in prop.get("value", [])}
                for group in tuple(runnable):
                    if group not in labels:
                        report["groups"][group].update(status="NOT RUN", reason=
                            "No tests registered: required dependency or harness unavailable")
                        runnable.remove(group)
                if runnable:
                    index, graph_error = None, ""
                    if args.changed is not None or args.since_report is not None or args.test is not None or args.recover:
                        try:
                            index = dependency_index(root, build, registered)
                        except (OSError, ValueError) as exc:
                            graph_error = str(exc)
                    requested_tests = args.test
                    recovery = None
                    if args.recover:
                        recovery = json.loads((build / "recovery-plan.json").read_text())
                        if (recovery.get("schema") != 1 or recovery.get("kind") != "reviewed-recovery-chain"
                                or recovery.get("build_target") != "torchlight_recovery_gates"
                                or recovery.get("generated_dir") != "generated/recovered/torchlight/recovered"
                                or not isinstance(recovery.get("required_tests"), list)
                                or not 1 <= len(recovery["required_tests"]) <= 64
                                or any(not isinstance(name, str) for name in recovery["required_tests"])
                                or len(set(recovery["required_tests"])) != len(recovery["required_tests"])):
                            raise ValueError("Unsupported reviewed recovery plan")
                        target_list = command_output(build, "targets", "all")
                        if "torchlight_recovery_gates: phony" not in target_list.splitlines():
                            raise ValueError("Reviewed recovery build closure is missing from Ninja")
                        requested_tests = recovery["required_tests"]
                        report["recovery"] = recovery
                    plan = make_plan(registered, runnable, None if baseline_reason else changes, index,
                                     graph_error, requested_tests=requested_tests)
                    if recovery:
                        plan.update(build_all=False, build_targets=[recovery["build_target"]])
                        plan["reasons"] = ["Explicit CMake build closure for the reviewed recovery recipes"]
                    if baseline_reason:
                        plan.update(mode="fallback-full", changed_files=changes)
                        plan["reasons"].append(baseline_reason)
                    report["selection"] = plan
                    print(f"Selection: {plan['mode']}, {len(plan['tests'])} tests; "
                          f"{len(plan['reasons'])} fallback reasons")
                    for reason in plan["reasons"]:
                        print("  " + reason)
                    if not args.plan and plan["tests"]:
                        phase = "build"
                        if recovery:
                            phase = "recovery-generate"
                            code = run([sys.executable, str(root / "tools/generate_recovered.py"),
                                "--original", str(original), "--out-dir", str(build / recovery["generated_dir"]),
                                "--report", str(build / "recovery-generation.json")], phase)
                        command = ["cmake", "--build", str(build), "--parallel", str(args.jobs)]
                        if not plan["build_all"]:
                            command += ["--target", *plan["build_targets"]]
                        if not code:
                            phase = "build"
                            code = run(command, phase)
                        if recovery and (build / "recovery-generation.json").is_file():
                            report["recovery"]["generation"] = json.loads((build / "recovery-generation.json").read_text())
            if code:
                for group in runnable:
                    report["groups"][group].update(status="FAILED", reason=f"{phase} failed: exit {code}")
            else:
                for group in GROUPS:
                    if group not in runnable:
                        continue
                    names = sorted(t["name"] for t in registered
                                   if t["name"] in plan["tests"] and group in properties(t).get("LABELS", []))
                    names = sorted(close_fixtures(registered, set(names)))
                    report["groups"][group]["selected_tests"] = names
                    if args.plan or not names:
                        report["groups"][group].update(status="PLANNED" if args.plan else "NOT AFFECTED",
                            reason="Plan only; no tests executed" if args.plan else
                                   "No affected tests; not a full verification result")
                        continue
                    xml = log_dir / (group + ".xml")
                    xml.unlink(missing_ok=True)  # Never reuse a previous green result.
                    began = time.monotonic()
                    # Use exact names. --tests-from-file requires CTest >=3.29;
                    # escaped anchored regex does not add that newer requirement.
                    import re
                    expression = "^(" + "|".join(re.escape(name) for name in names) + ")$"
                    code = run(["ctest", "--test-dir", str(build), "-R", expression,
                                "--output-on-failure", "--no-tests=error", "--output-junit", str(xml),
                                "--parallel", str(args.jobs)], group)
                    result = summarize_junit(xml, code)
                    roles = {test["name"]: evidence_role(test) for test in registered}
                    for test in result["tests"]:
                        test["evidence_role"] = roles.get(test["name"], "unclassified")
                    actual = {test["name"] for test in result["tests"]}
                    if set(names) - actual:
                        result.update(status="FAILED", reason="Selected tests missing from CTest results")
                    # Empty group is unavailable, not a behavioral test failure.
                    if not result["tests"]:
                        result["status"] = "NOT RUN"
                        result["reason"] = "No tests registered: required dependency or harness unavailable"
                    result.update(requested=True, selected_tests=names,
                                  seconds=round(time.monotonic() - began, 3))
                    report["groups"][group] = result
    except (OSError, ValueError) as exc:
        for group in runnable:
            if report["groups"][group]["status"] == "NOT RUN":
                report["groups"][group].update(status="FAILED", reason=str(exc))
    report["finished_at"] = datetime.now(timezone.utc).isoformat()
    after = source_snapshot(root)
    report["source_consistent"] = after["sha256"] == before["sha256"]
    if not report["source_consistent"]:
        report["source_after_sha256"] = after["sha256"]
        print("Source changed during checks: results are not a current-source gate.")
    write_report(report, output)
    accepted = {"PLANNED"} if args.plan else {"PASSED", "NOT AFFECTED"}
    return 0 if report["source_consistent"] and all(
        report["groups"][g]["status"] in accepted for g in selected) else 1


if __name__ == "__main__":
    raise SystemExit(main())
