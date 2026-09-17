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

GROUPS = ("core", "assets", "reference", "render", "desktop")


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
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_suffix(path.suffix + ".tmp")
    temporary.write_text(json.dumps(report, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    temporary.replace(path)
    print("\nGROUP       STATUS       PASS / FAIL / SKIP    REASON")
    for group in GROUPS:
        item = report["groups"][group]
        print(f"{group:11} {item['status']:12} {item.get('passed',0):4} / {item.get('failed',0):4} / "
              f"{item.get('skipped',0):4}    {item.get('reason','')}")
    print(f"Report: {path}")


def parser() -> argparse.ArgumentParser:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("directory", nargs="?", type=Path,
                   help="backward-compatible full check: directory with pak.zip and original ELF")
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
    p.add_argument("--jobs", type=int, default=int(os.environ.get("TORCHLIGHT_BUILD_JOBS", "2")))
    return p


def main(argv: list[str] | None = None) -> int:
    args = parser().parse_args(argv)
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
    full = args.all or args.directory is not None
    if game is None and original is not None:
        game = original.parent
    if original is None and full and game is not None:
        original = game / "Torchlight.bin.x86_64"
    game = game.resolve() if game is not None else None
    original = original.resolve() if original is not None else None
    selected = set(GROUPS) if full else {g for g in GROUPS if bool(getattr(args, g if g != "core" else "core"))}
    if not selected:
        selected = {"core"}
    # Reports/builds must never overwrite a read-only external input or project source.
    inputs = [p for p in (game / "pak.zip" if game else None, original) if p is not None]
    if output in inputs or output == Path(__file__).resolve() or build in inputs:
        parser().error("output collides with a read-only input")
    report = {"schema": 1, "kind": "verification-run", "groups": {}, "inputs": {},
              "evidence": {"core": "authored fixtures and bounded export comparisons",
                           "assets": "resource-derived; not ELF parity",
                           "reference": "pinned original comparisons",
                           "render": "actual GL; self snapshots are regression only",
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
                         "-DTORCHLIGHT_ENABLE_DESKTOP=" + ("ON" if "desktop" in selected else "OFF"),
                         "-DTORCHLIGHT_ENABLE_RENDER=" + ("ON" if selected & {"core", "render", "desktop"} else "OFF"),
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
                    phase = "build"
                    code = run(["cmake", "--build", str(build), "--parallel", str(args.jobs)], phase)
            if code:
                for group in runnable:
                    report["groups"][group].update(status="FAILED", reason=f"{phase} failed: exit {code}")
            else:
                for group in GROUPS:
                    if group not in runnable:
                        continue
                    xml = log_dir / (group + ".xml")
                    xml.unlink(missing_ok=True)  # Never reuse a previous green result.
                    began = time.monotonic()
                    code = run(["ctest", "--test-dir", str(build), "-L", "^" + group + "$",
                                "--output-on-failure", "--no-tests=error", "--output-junit", str(xml),
                                "--parallel", str(args.jobs)], group)
                    result = summarize_junit(xml, code)
                    # Empty group is unavailable, not a behavioral test failure.
                    if not result["tests"]:
                        result["status"] = "NOT RUN"
                        result["reason"] = "No tests registered: required dependency or harness unavailable"
                    result.update(requested=True, seconds=round(time.monotonic() - began, 3))
                    report["groups"][group] = result
    except (OSError, ValueError) as exc:
        for group in runnable:
            if report["groups"][group]["status"] == "NOT RUN":
                report["groups"][group].update(status="FAILED", reason=str(exc))
    write_report(report, output)
    return 0 if all(report["groups"][g]["status"] == "PASSED" for g in selected) else 1


if __name__ == "__main__":
    raise SystemExit(main())
