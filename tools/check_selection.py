"""Conservative CTest selection using Ninja's existing build dependency graph.

No source-language guessing. Headers, build rules, Python/shared helpers,
unknown files or missing graph information widen to all requested tests.
Only C/C++ translation units known to Ninja may narrow the test set.
"""
from __future__ import annotations

from pathlib import Path
import shlex
import subprocess


def properties(test: dict) -> dict:
    return {p["name"]: p["value"] for p in test.get("properties", [])}


def eligible_tests(tests: list[dict], groups: set[str]) -> list[dict]:
    return [t for t in tests if groups.intersection(properties(t).get("LABELS", []))]


def close_fixtures(tests: list[dict], names: set[str]) -> set[str]:
    """Include DEPENDS and fixture setup/cleanup even across group labels."""
    by_name = {t["name"]: t for t in tests}
    names = set(names)
    while True:
        before = set(names)
        required = set()
        for name in before:
            if name not in by_name:
                raise ValueError(f"Unknown dependent CTest test: {name}")
            props = properties(by_name[name])
            names.update(props.get("DEPENDS", []))
            required.update(props.get("FIXTURES_REQUIRED", []))
        for test in tests:
            props = properties(test)
            if required.intersection(props.get("FIXTURES_SETUP", []) +
                                     props.get("FIXTURES_CLEANUP", [])):
                names.add(test["name"])
        if before == names:
            return names


def command_output(build: Path, *args: str) -> str:
    result = subprocess.run(["ninja", "-C", str(build), "-t", *args],
                            capture_output=True, text=True)
    if result.returncode:
        raise ValueError("Ninja dependency query failed: " + result.stderr.strip())
    return result.stdout


def dependency_index(root: Path, build: Path, tests: list[dict]) -> dict:
    # Target names may contain spaces. Split only the final ': rule' delimiter.
    targets = {line.rsplit(": ", 1)[0] for line in
               command_output(build, "targets", "all").splitlines() if ": " in line}
    absolute = {(build / target).resolve(): target for target in targets}
    cache = {}
    index = {}
    for test in tests:
        dependencies, needed = set(), set()
        workdir = Path(properties(test).get("WORKING_DIRECTORY", str(build)))
        for argument in test.get("command", []):
            if argument.startswith("-"):
                continue
            path = (workdir / argument).resolve()
            if path.is_relative_to(root):
                dependencies.add(str(path.relative_to(root)))
            target = absolute.get(path)
            if target is None:
                continue
            needed.add(target)
            if target not in cache:
                inputs = set()
                # Ninja inputs emits shell-escaped paths by default, one per line.
                for line in command_output(build, "inputs", target).splitlines():
                    tokens = shlex.split(line)
                    if len(tokens) != 1:
                        raise ValueError("Unparseable Ninja input: " + line)
                    item = (build / tokens[0]).resolve()
                    if item.is_relative_to(root):
                        inputs.add(str(item.relative_to(root)))
                cache[target] = inputs
            dependencies.update(cache[target])
        index[test["name"]] = {"inputs": dependencies, "targets": needed,
                               # Scripts can hide runtime/build dependencies.
                               "opaque": not needed or any(a.endswith(".py") for a in test.get("command", []))}
    return index


def make_plan(tests: list[dict], groups: set[str], changes: list[str] | None,
              index: dict | None, graph_error: str = "", *,
              requested_tests: list[str] | None = None) -> dict:
    eligible = eligible_tests(tests, groups)
    reasons = []
    selected = {t["name"] for t in eligible}
    full = changes is None
    if requested_tests is not None:
        if changes is not None:
            raise ValueError("Named tests and changed-source selection are mutually exclusive")
        unknown = set(requested_tests) - selected
        if unknown:
            raise ValueError("Tests absent from requested groups: " + ", ".join(sorted(unknown)))
        selected = set(requested_tests)
        full = False
    elif changes is not None:
        if not changes:
            selected = set()
        elif not index:
            full = True
            reasons.append(graph_error or "Dependency graph unavailable")
        else:
            for path in changes:
                if Path(path).suffix not in {".c", ".cc", ".cpp", ".cxx"}:
                    reasons.append(f"Conservative fallback for header/script/data/build/unknown input: {path}")
                elif not any(path in entry["inputs"] for entry in index.values()):
                    reasons.append(f"No registered dependency for changed source: {path}")
            full = bool(reasons)
            if not full:
                selected = {t["name"] for t in eligible
                            if index[t["name"]]["opaque"] or
                            set(changes).intersection(index[t["name"]]["inputs"])}
    selected = close_fixtures(tests, selected)
    require_explicit_integration(tests, selected, groups)
    # Opaque scripts may launch tools not present in their CTest argv. Build all
    # in that case; never run a stale helper because target inference missed it.
    build_all = full or bool(selected) and (not index or any(index[n]["opaque"] for n in selected))
    if requested_tests is not None and build_all:
        reasons.append(graph_error or "Build dependencies are incomplete/opaque; build configured targets, execute only named tests")
    targets = sorted({target for n in selected for target in (index or {}).get(n, {}).get("targets", [])})
    return {"mode": "named" if requested_tests is not None else
                    "full" if changes is None else "fallback-full" if full else "affected",
            "changed_files": changes, "tests": sorted(selected),
            "registered_in_requested_groups": len(eligible), "reasons": reasons,
            "build_all": bool(build_all), "build_targets": targets,
            "not_a_full_gate": requested_tests is not None or changes is not None and not full}


def require_explicit_integration(tests: list[dict], names: set[str], groups: set[str]) -> None:
    """Also guard fixture closure and accidentally dual-labelled legacy tests."""
    for test in tests:
        if test["name"] not in names:
            continue
        labels = set(properties(test).get("LABELS", []))
        needed = labels & {"render", "desktop"}
        if "ui-integration" in labels and not needed:
            needed = {"render"}
        if needed and not needed.intersection(groups):
            raise ValueError(f"Integration test {test['name']} requires explicit " +
                             "/".join("--" + group for group in sorted(needed)))
