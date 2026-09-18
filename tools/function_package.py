#!/usr/bin/env python3
"""Build a code-first function package: everything needed to transfer one
original function without re-collecting evidence by hand.

Bundle contents per function address:
  - registry row (research/coverage.tsv) + boundary annotation
  - transfer stages (research/function-transfer.json), if present
  - direct callgraph edges (research/original-callgraph.tsv), incoming/outgoing
  - call-site edges (research/original-callsites.tsv), if exported; otherwise
    an explicit warning that order/multiplicity is unavailable
  - decompilation hits (research/decompiled-core/*.c, research/decompiled/*.c)
  - disassembly hits (research/disassembly/*.asm)
  - port references (src/, include/, tests/ mentioning the address or symbol)
  - ELF strings inside the function bounds (from original-symbols.txt sizes)

No ELF execution. No promotions. Read-only inputs, markdown to stdout or file.
"""
from __future__ import annotations

import argparse
import csv
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ELF_SHA = "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"

SYMBOL_RE = re.compile(r"^([0-9a-fA-F]+) (?:([0-9a-fA-F]+) )?([TtWw]) (.+)$")


def normalize(address: str) -> str:
    address = address.strip().lower()
    if address.startswith("0x"):
        address = address[2:]
    return f"{int(address, 16):08x}"


def load_symbols() -> dict[str, dict]:
    functions: dict[str, dict] = {}
    for line in (ROOT / "research/original-symbols.txt").read_text(
        encoding="utf-8", errors="replace"
    ).splitlines():
        match = SYMBOL_RE.match(line)
        if not match:
            continue
        addr = f"{int(match[1], 16):08x}"
        size = int(match[2], 16) if match[2] else 0
        row = functions.setdefault(addr, {"aliases": [], "size": 0})
        row["aliases"].append(match[4])
        row["size"] = max(row["size"], size)
    return functions


def load_callgraph() -> tuple[list[dict], list[dict], dict, dict]:
    path = ROOT / "research/original-callgraph.tsv"
    incoming: dict[str, list[dict]] = {}
    outgoing: dict[str, list[dict]] = {}
    with path.open(newline="", encoding="utf-8") as stream:
        for row in csv.DictReader(stream, delimiter="\t"):
            source = f"{int(row['caller_address'], 16):08x}"
            target = f"{int(row['callee_address'], 16):08x}"
            outgoing.setdefault(source, []).append(row)
            incoming.setdefault(target, []).append(row)
    return [], [], incoming, outgoing


def load_callsites(addr: str) -> tuple[list[dict], list[dict], bool]:
    path = ROOT / "research/original-callsites.tsv"
    if not path.is_file():
        return [], [], False
    incoming: list[dict] = []
    outgoing: list[dict] = []
    with path.open(newline="", encoding="utf-8") as stream:
        for row in csv.DictReader(stream, delimiter="\t"):
            source = f"{int(row['caller_address'], 16):08x}"
            target = f"{int(row['callee_address'], 16):08x}"
            if source == addr:
                outgoing.append(row)
            if target == addr:
                incoming.append(row)
    outgoing.sort(key=lambda r: (r["callsite_address"], r["callee_address"]))
    incoming.sort(key=lambda r: (r["caller_address"], r["callsite_address"]))
    return incoming, outgoing, True


def coverage_row(addr: str) -> dict | None:
    with (ROOT / "research/coverage.tsv").open(newline="", encoding="utf-8") as stream:
        for row in csv.DictReader(stream, delimiter="\t"):
            if row["address"].startswith("port:"):
                continue
            if f"{int(row['address'], 16):08x}" == addr:
                return row
    return None


def transfer_entry(addr: str) -> dict | None:
    path = ROOT / "research/function-transfer.json"
    if not path.is_file():
        return None
    data = json.loads(path.read_text(encoding="utf-8"))
    return data.get("functions", {}).get("0x" + addr)


def grep_hits(directories: list[Path], patterns: list[str],
              suffixes: set[str] | None = None) -> list[str]:
    hits: list[str] = []
    for base in directories:
        if not base.is_dir():
            continue
        for path in sorted(base.rglob("*")):
            if not path.is_file():
                continue
            allowed = suffixes or {".c", ".cpp", ".hpp", ".h", ".py"}
            if path.suffix.lower() not in allowed:
                continue
            try:
                text = path.read_text(encoding="utf-8", errors="replace")
            except OSError:
                continue
            for number, line in enumerate(text.splitlines(), 1):
                if any(p in line for p in patterns):
                    hits.append(f"{path.relative_to(ROOT)}:{number}:{line.strip()[:220]}")
                    if len(hits) >= 60:
                        return hits
    return hits


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--address")
    group.add_argument("--symbol")
    parser.add_argument("--out", type=Path)
    args = parser.parse_args()

    symbols = load_symbols()
    if args.address:
        addr = normalize(args.address)
    else:
        matches = [a for a, row in symbols.items() if args.symbol in ";".join(row["aliases"])]
        if len(matches) != 1:
            raise SystemExit(f"symbol matches {len(matches)} addresses, refine query: {matches[:10]}")
        addr = matches[0]
    if addr not in symbols:
        raise SystemExit(f"unknown address: 0x{addr}")

    aliases = symbols[addr]["aliases"]
    size = symbols[addr]["size"]
    row = coverage_row(addr)
    transfer = transfer_entry(addr)
    _, _, incoming, outgoing = load_callgraph()
    site_in, site_out, have_sites = load_callsites(addr)

    hex_variants = {f"0x{addr}", f"0x{addr.lstrip('0') or '0'}", f"00{addr}", addr}
    patterns = list(hex_variants) + aliases[:3]

    decompiled = grep_hits([ROOT / "research/decompiled-core", ROOT / "research/decompiled"],
                           patterns, {".c", ".cpp", ".txt"})
    disassembly = grep_hits([ROOT / "research/disassembly"], patterns,
                            {".asm", ".txt", ".md"})
    port = grep_hits([ROOT / "src", ROOT / "include", ROOT / "tests"], patterns,
                     {".c", ".cpp", ".hpp", ".h", ".py"})

    lines = [f"# Function package 0x{addr}", "",
             f"ELF SHA-256 `{ELF_SHA}`.", "",
             f"Aliases: {'; '.join(aliases)}", f"Size: 0x{size:x} ({size} bytes).", ""]
    if row:
        lines += ["## Registry (coverage.tsv)",
                  f"- status `{row['status']}` subsystem `{row['subsystem']}` "
                  f"in={row['incoming']} out={row['outgoing']} priority={row['priority']}",
                  f"- boundary: {row['boundary']}", f"- evidence: {row['evidence']}",
                  f"- implementation: {row['implementation']}", f"- tests: {row['tests']}",
                  f"- comparison: {row['comparison']}", ""]
    else:
        lines += ["## Registry", "No coverage.tsv row (regenerate coverage).", ""]
    if transfer is None:
        lines += ["## Transfer stages", "No entry in research/function-transfer.json.", ""]
    else:
        stages = transfer.get("stages", {})
        lines += ["## Transfer stages (analyzed/ported/wired/compared)",
                  f"- analyzed={stages.get('analyzed')} ported={stages.get('ported')} "
                  f"wired={stages.get('wired')} compared={stages.get('compared')}",
                  f"- notes: {transfer.get('notes', '')}",
                  f"- evidence: {transfer.get('evidence', '')}", ""]
    lines += [f"## Callgraph (resolved direct edges only)",
              f"- outgoing {len(outgoing.get(addr, []))}, incoming {len(incoming.get(addr, []))}"]
    for edge in outgoing.get(addr, [])[:40]:
        lines.append(f"  - out {edge['caller_address']} -> {edge['callee_address']} {edge['callee_symbol']}")
    for edge in incoming.get(addr, [])[:40]:
        lines.append(f"  - in {edge['caller_address']} {edge['caller_symbol']} -> {edge['callee_address']}")
    lines.append("")
    if have_sites:
        lines += ["## Call sites (site+order+multiplicity)",
                  f"- outgoing sites {len(site_out)}, incoming sites {len(site_in)}"]
        for edge in site_out[:60]:
            lines.append(f"  - out site={edge['callsite_address']} -> {edge['callee_address']} "
                         f"{edge['callee_symbol']} [{edge.get('mnemonic', '')}]")
        for edge in site_in[:60]:
            lines.append(f"  - in {edge['caller_address']} {edge['caller_symbol']} "
                         f"site={edge['callsite_address']}")
    else:
        lines += ["## Call sites",
                  "WARNING: research/original-callsites.tsv is absent. Run "
                  "tools/ghidra/export_call_sites.sh. Order, branches and repeat "
                  "counts are NOT recoverable from the set-only callgraph.", ""]
    lines.append("")
    lines += ["## Decompilation hits (navigation only, verify against ASM)", ""]
    lines += [f"  - {hit}" for hit in decompiled[:40]] or ["  - none"]
    lines += ["", "## Disassembly hits", ""]
    lines += [f"  - {hit}" for hit in disassembly[:40]] or ["  - none"]
    lines += ["", "## Port references", ""]
    lines += [f"  - {hit}" for hit in port[:60]] or ["  - none"]

    reuse_tool = ROOT / "tools/reuse_inventory.py"
    reuse_scopes = ROOT / "research/reuse/scopes.json"
    if reuse_tool.is_file() and reuse_scopes.is_file():
        try:
            sys.path.insert(0, str(ROOT / "tools"))
            import reuse_inventory  # type: ignore
            reuse_text = reuse_inventory.context(
                ROOT, address="0x" + addr, aliases=aliases)
            lines += ["", reuse_text]
        except Exception as exc:  # navigation aid must never hide the core packet
            lines += ["", "## Earlier work to reuse",
                      f"Reuse index unavailable: {exc}"]

    lines += ["", "## Next step for this function",
              "1. Read the full decompilation + ASM for every branch.",
              "2. List field writes, error paths and all call sites with conditions.",
              "3. Update research/function-transfer.json stages with evidence; "
              "do not invent field meanings or branch purposes.", ""]
    text = "\n".join(lines)
    if args.out:
        args.out.write_text(text, encoding="utf-8")
        print(f"Wrote {args.out} ({len(lines)} lines)")
    else:
        print(text)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
