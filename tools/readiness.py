#!/usr/bin/env python3
"""Secondary smoke/compatibility report, NOT code-first completion/readiness.

Stdlib only, offline, no inferred completion percentages or stage promotions.
Historical/unknown-source reports remain visible but cannot prove current work.
"""
from __future__ import annotations

import argparse
from collections import Counter
import json
from pathlib import Path

from automation_state import source_snapshot, validate_output, write_json
from transfer_contract import completion

ROOT = Path(__file__).resolve().parents[1]


def validate_manifest(root: Path, data: dict) -> None:
    if data.get("schema") != 1 or not isinstance(data.get("capabilities"), list):
        raise ValueError("Unsupported capability manifest")
    ids = set()
    for item in data["capabilities"]:
        if item["id"] in ids or item["stage"] not in {"partial", "prototype", "open", "complete"}:
            raise ValueError("Duplicate capability or invalid stage: " + item["id"])
        ids.add(item["id"])
        for key in ("title", "boundary", "code", "evidence", "tests", "blockers"):
            if key not in item:
                raise ValueError(f"Missing {key}: {item['id']}")
        for value in item["code"] + item["evidence"]:
            path = (root / value).resolve()
            if not path.is_relative_to(root.resolve()) or not path.is_file():
                raise ValueError(f"Missing/local source reference required: {value}")
        if item["stage"] == "complete" and (item["blockers"] or not item["tests"]):
            raise ValueError("Complete capability needs tests and no blockers: " + item["id"])


def build_report(root: Path, manifest: dict, reports: list[tuple[str, dict]], current: dict) -> dict:
    validate_manifest(root, manifest)
    observations = {}
    report_states = []
    # Timestamp orders repeated reports of the same source. File mtime is not proof.
    for name, report in sorted(reports, key=lambda pair: pair[1].get("finished_at", "")):
        if report.get("kind") != "verification-run" or report.get("schema") != 1:
            raise ValueError("Not a verification report: " + name)
        source = report.get("source", {})
        freshness = ("UNKNOWN" if not source.get("sha256") else
                     "CURRENT" if source["sha256"] == current["sha256"] and
                     report.get("source_consistent") is True else "STALE")
        if report.get("plan_only"):
            freshness = "PLAN ONLY"
        report_states.append({"path": name, "freshness": freshness,
                              "finished_at": report.get("finished_at"),
                              "inputs": report.get("inputs", {})})
        for group in report.get("groups", {}).values():
            for test in group.get("tests", []):
                item = {"status": test["status"], "freshness": freshness, "report": name}
                previous = observations.get(test["name"])
                # Never let a historical report displace current-source evidence.
                if freshness == "CURRENT" or previous is None or previous["freshness"] != "CURRENT":
                    observations[test["name"]] = item
    capabilities = []
    for item in manifest["capabilities"]:
        tests = {name: observations.get(name, {"status": "NOT RUN", "freshness": "MISSING"})
                 for name in item["tests"]}
        verified = bool(tests) and all(t["status"] == "PASSED" and t["freshness"] == "CURRENT"
                                      for t in tests.values())
        failed = any(t["status"] == "FAILED" and t["freshness"] == "CURRENT" for t in tests.values())
        capabilities.append({**item, "verification": "PASSED" if verified else "FAILED" if failed else "NOT VERIFIED",
                             "test_results": tests,
                             "release_ready": item["stage"] == "complete" and verified and not item["blockers"]})
    transfer = root / "research/function-transfer.json"
    functions = json.loads(transfer.read_text())["functions"] if transfer.is_file() else {}
    stages = {stage: sum(f.get("stages", {}).get(stage) is True for f in functions.values())
              for stage in ("analyzed", "ported", "wired", "compared")}
    hashes: dict = {}
    accepted = Counter(completion(f, root, hashes)["status"] for f in functions.values())
    return {"schema": 1, "kind": "readiness-report", "source_sha256": current["sha256"],
            "meaning": "Secondary capability smoke/compatibility only; use work_frontier for code-first acceptance",
            "scope_complete": manifest.get("scope_complete", False),
            "release_ready": False,
            "release_readiness": "NOT ASSESSED: capability checks cannot establish original-function fidelity",
            "capability_scope_ready": manifest.get("scope_complete") is True and bool(capabilities) and
                             all(c["release_ready"] for c in capabilities),
            "capabilities": capabilities, "reports": report_states,
            "stage_counts": dict(Counter(c["stage"] for c in capabilities)),
            "function_registry": {"entries": len(functions), "stages": stages,
                                  "whole_function_completion": dict(sorted(accepted.items())),
                                  "meaning": "Tracked entries only, not all functions or game completion"}}


def markdown(report: dict) -> str:
    lines = ["# OpenTorchlight: вторичные smoke/compatibility-проверки", "",
             "Этот отчёт не оценивает готовность восстановления оригинала или выпуска.",
             "Основной code-first отчёт: `python3 tools/work_frontier.py` (UI scope по умолчанию).", "",
             "Статусы границ заданы в проверяемом реестре; скрипт не восстанавливает поведение и не повышает стадии.",
             "PASSED ниже относится только к перечисленным тестам на текущем исходном коде, не ко всей подсистеме.", "",
             "| Возможность | Граница | Проверки текущего кода |", "|---|---|---|"]
    for item in report["capabilities"]:
        lines.append(f"| {item['title']} | {item['stage']} | {item['verification']} |")
    for item in report["capabilities"]:
        lines += ["", "## " + item["title"], "", item["boundary"], "", "Открыто:", ""]
        lines += ["- " + text for text in item["blockers"]] or ["- Нет записанных блокеров."]
        if item["test_results"]:
            lines += ["", "Проверки:", ""]
            lines += [f"- `{name}`: {result['status']} / {result['freshness']}"
                      for name, result in item["test_results"].items()]
    lines += ["", "## Источники результатов", ""]
    lines += [f"- `{r['path']}`: {r['freshness']}" for r in report["reports"]] or ["- Отчёты не переданы."]
    return "\n".join(lines) + "\n"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--manifest", type=Path, default=ROOT / "research/capabilities.json")
    parser.add_argument("--report", type=Path, action="append", default=[])
    parser.add_argument("--json", type=Path)
    parser.add_argument("--markdown", type=Path)
    args = parser.parse_args()
    try:
        if args.json and args.markdown and args.json.resolve() == args.markdown.resolve():
            raise ValueError("--json and --markdown must name different files")
        for output in (args.json, args.markdown):
            if output:
                validate_output(ROOT, output, [args.manifest, *args.report])
        manifest = json.loads(args.manifest.read_text())
        reports = [(str(path), json.loads(path.read_text())) for path in args.report]
        result = build_report(ROOT, manifest, reports, source_snapshot(ROOT))
        if args.json:
            write_json(args.json, result)
        if args.markdown:
            args.markdown.parent.mkdir(parents=True, exist_ok=True)
            args.markdown.write_text(markdown(result), encoding="utf-8")
        if not args.json and not args.markdown:
            print(markdown(result), end="")
        else:
            print(f"Secondary capability report: {len(result['capabilities'])}; code-first release readiness NOT ASSESSED")
    except (OSError, ValueError, KeyError, TypeError) as exc:
        parser.exit(2, f"readiness: {exc}\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
