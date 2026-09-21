#!/usr/bin/env python3
"""Fail when the function registry no longer reflects the port.

Two checks, no ELF execution:
  1. Unbounded @0xADDR references are a warning-only burn-down list.
  2. research/function-transfer.json must be schema-valid; any compared=true
     entry needs a non-empty comparison, and every transfer address must be a
     known symbol and have a boundary entry once analyzed/ported/compared.
"""
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path
from transfer_contract import completion

ROOT = Path(__file__).resolve().parents[1]
REF_RE = re.compile(r"@0x([0-9a-fA-F]{4,16})\b")
SYMBOL_RE = re.compile(r"^([0-9a-fA-F]+) (?:([0-9a-fA-F]+) )?([TtWw]) (.+)$")


def known_functions() -> set[str]:
    known: set[str] = set()
    for line in (ROOT / "research/original-symbols.txt").read_text(
        encoding="utf-8", errors="replace"
    ).splitlines():
        match = SYMBOL_RE.match(line)
        if match:
            known.add(f"{int(match[1], 16):08x}")
    return known


def boundary_addresses() -> set[str]:
    data = json.loads((ROOT / "research/coverage-boundaries.json").read_text(encoding="utf-8"))
    found: set[str] = set()
    for entry in data.get("boundaries", []):
        for address in entry.get("addresses", []):
            found.add(f"{int(address, 16):08x}")
    return found


def port_references() -> dict[str, list[str]]:
    refs: dict[str, list[str]] = {}
    for base in (ROOT / "src", ROOT / "include", ROOT / "tests"):
        if not base.is_dir():
            continue
        for path in sorted(base.rglob("*")):
            if not path.is_file() or path.suffix not in {".cpp", ".hpp", ".h", ".py"}:
                continue
            try:
                text = path.read_text(encoding="utf-8", errors="replace")
            except OSError:
                continue
            for match in REF_RE.finditer(text):
                addr = f"{int(match[1], 16):08x}"
                refs.setdefault(addr, []).append(str(path.relative_to(ROOT)))
    return refs


def check_transfer(known: set[str], boundaries: set[str]) -> list[str]:
    errors: list[str] = []
    path = ROOT / "research/function-transfer.json"
    if not path.is_file():
        return ["research/function-transfer.json is absent"]
    data = json.loads(path.read_text(encoding="utf-8"))
    if data.get("schema") != 1:
        errors.append("function-transfer.json: schema must be 1")
    if data.get("original_elf_sha256") != "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b":
        errors.append("function-transfer.json: wrong original ELF SHA-256")
    functions = data.get("functions", {})
    if not isinstance(functions, dict):
        return errors + ["function-transfer.json: functions must be an object"]
    hashes: dict = {}
    for raw, entry in sorted(functions.items()):
        try:
            addr = f"{int(raw, 16):08x}"
        except ValueError:
            errors.append(f"transfer {raw}: bad address")
            continue
        if addr not in known:
            errors.append(f"transfer {raw}: unknown original address")
        stages = entry.get("stages", {})
        for stage in ("analyzed", "ported", "wired", "compared"):
            if type(stages.get(stage)) is not bool:
                errors.append(f"transfer {raw}: stage {stage} must be true/false")
        if stages.get("compared") and not entry.get("comparison"):
            errors.append(f"transfer {raw}: compared=true requires a comparison")
        if any(stages.get(s) for s in ("analyzed", "ported", "compared")) and addr not in boundaries:
            errors.append(f"transfer {raw}: active transfer needs a coverage-boundaries entry")
        accepted = completion(entry, ROOT, hashes)
        if accepted["status"] in {"invalid", "stale"}:
            errors.extend(f"transfer {raw}: {error}" for error in accepted["errors"])
    return errors


def main() -> int:
    global ROOT
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=ROOT)
    args = parser.parse_args()
    ROOT = args.root.resolve()

    known = known_functions()
    boundaries = boundary_addresses()
    refs = port_references()
    errors: list[str] = []
    warnings: list[str] = []

    entry_drift = sorted(a for a in refs if a in known and a not in boundaries)
    site_cites = sorted(a for a in refs if a not in known and a not in boundaries)
    if site_cites:
        warnings.append("port cites interior call sites/constants without a containing-function "
                        "boundary yet (per-packet work, not a separate entry):")
        for addr in site_cites[:20]:
            warnings.append(f"  0x{addr}: {', '.join(sorted(set(refs[addr]))[:3])}")
        if len(site_cites) > 20:
            warnings.append(f"  ... and {len(site_cites) - 20} more site/constant cites")
    if entry_drift:
        warnings.append("port cites original game-function entries without a reviewed "
                        "coverage-boundaries entry (burn-down list, code-first packets first):")
        for addr in entry_drift:
            warnings.append(f"  0x{addr}: {', '.join(sorted(set(refs[addr]))[:4])}")

    errors.extend(check_transfer(known, boundaries))

    # Coverage outputs must be fresh; stale TSV re-creates the same drift.
    import subprocess
    check = subprocess.run(["python3", str(ROOT / "tools/coverage_map.py"),
                            "--check", "--root", str(ROOT)],
                           capture_output=True, text=True)
    if check.returncode:
        errors.append("coverage stale: run tools/coverage_map.py --root . "
                      f"({(check.stdout + check.stderr).strip()[:300]})")

    if errors:
        print("REGISTRY SYNC FAILED")
        for line in errors:
            print(f"- {line}")
        for line in warnings:
            print(f"warning: {line}")
        return 1
    for line in warnings:
        print(f"warning: {line}")
    print(f"Registry sync ok: {len(boundaries)} bounded addresses, "
          f"{len(refs)} cited addresses, transfer entries validated.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
