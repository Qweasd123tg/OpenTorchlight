#!/usr/bin/env python3
"""Read-only, model-free direct call-site index using GNU nm/objdump.

This is NOT Ghidra function/CFG analysis: callers are bounded by ELF symbols,
only literal direct CALL targets are resolved, address order is not execution
order. Indirect calls and unknown callers remain explicit in the sidecar.
No game execution, full decompilation, guessed types or original asset copies.
"""
from __future__ import annotations

import argparse
import bisect
import csv
import hashlib
import os
from pathlib import Path
import re
import subprocess
import tempfile

from automation_state import validate_output, write_json
from original import Original

ROOT = Path(__file__).resolve().parents[1]
FIELDS = ("caller_address", "caller_symbol", "callsite_address", "callee_address", "callee_symbol", "mnemonic")


def symbol_index(symbols) -> tuple[list[int], dict]:
    entries = {}
    for symbol in symbols:
        if symbol.kind not in "TtWw" or not symbol.size:
            continue
        previous = entries.get(symbol.address)
        if previous is None or (-symbol.size, symbol.name) < (-previous.size, previous.name):
            entries[symbol.address] = symbol
    return sorted(entries), entries


def parse_calls(lines, symbols) -> tuple[list[dict], dict]:
    starts, entries = symbol_index(symbols)
    rows, indirect = [], []
    unattributed = 0
    for line in lines:
        match = re.match(r"\s*([0-9a-fA-F]+):\s+(callq?)\s+(.+?)\s*$", line)
        if not match:
            continue
        address, mnemonic, operand = int(match[1], 16), match[2], match[3]
        index = bisect.bisect_right(starts, address) - 1
        caller = entries[starts[index]] if index >= 0 else None
        if caller is None or address >= caller.address + caller.size:
            unattributed += 1
            continue
        target = re.fullmatch(r"([0-9a-fA-F]+)(?:\s+<(.+)>)?", operand)
        base = {"caller_address": f"{caller.address:08x}", "caller_symbol": caller.name,
                "callsite_address": f"{address:08x}"}
        if not target:
            indirect.append({**base, "operand": operand})
            continue
        callee = int(target[1], 16)
        rows.append({**base, "callee_address": f"{callee:08x}",
                     "callee_symbol": entries[callee].name if callee in entries else target[2] or "<unresolved>",
                     "mnemonic": mnemonic.upper()})
    rows.sort(key=lambda r: (r["caller_address"], r["callsite_address"], r["callee_address"]))
    return rows, {"indirect_calls": indirect, "unattributed_calls": unattributed,
                  "bounded_function_symbols": len(entries)}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--out", type=Path, required=True,
                        help="ignored build/cache path or external output; sidecar is <out>.meta.json")
    args = parser.parse_args()
    metadata = Path(str(args.out) + ".meta.json")
    try:
        for path in (args.out, metadata):
            validate_output(ROOT, path, [args.original.resolve().parent])
        original = Original(args.original)  # Exact supported SHA-256 gate before decoding.
        env = {**os.environ, "LC_ALL": "C"}
        # No full disassembly file is retained; only call-site metadata is exported.
        with tempfile.TemporaryFile(mode="w+") as errors:
            with subprocess.Popen(["objdump", "-d", "-w", "-C", "--no-show-raw-insn", str(original.path)],
                                  stdout=subprocess.PIPE, stderr=errors, text=True, env=env) as child:
                rows, unresolved = parse_calls(child.stdout, original.symbols)
                if child.wait():
                    errors.seek(0)
                    raise ValueError("objdump failed: " + errors.read())
        if not rows:
            raise ValueError("No direct calls decoded; refusing an empty index")
        args.out.parent.mkdir(parents=True, exist_ok=True)
        with tempfile.NamedTemporaryFile(mode="w", encoding="utf-8", newline="", dir=args.out.parent,
                                         prefix=args.out.name + ".", delete=False) as stream:
            temporary = Path(stream.name)
            writer = csv.DictWriter(stream, fieldnames=FIELDS, delimiter="\t", lineterminator="\n")
            writer.writeheader()
            writer.writerows(rows)
        temporary.replace(args.out)
        write_json(metadata, {"schema": 1, "kind": "direct-callsites", "original_elf_sha256": original.sha256,
                   "tsv_sha256": hashlib.sha256(args.out.read_bytes()).hexdigest(), "direct_calls": len(rows),
                   "tool": subprocess.check_output(["objdump", "--version"], text=True, env=env).splitlines()[0],
                   "boundary": "Symbol-bounded direct CALL instructions only; address order, not runtime order. No branch predicates, indirect/virtual resolution or tail-call index.",
                   **unresolved})
        print(f"{len(rows)} direct sites; {len(unresolved['indirect_calls'])} indirect; "
              f"{unresolved['unattributed_calls']} unattributed. {args.out}")
    except (OSError, ValueError, subprocess.SubprocessError) as exc:
        parser.exit(2, f"callsites: {exc}\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
