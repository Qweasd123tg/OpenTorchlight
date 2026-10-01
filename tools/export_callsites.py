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
import json
import os
from pathlib import Path
import re
import subprocess
import tempfile

from automation_state import validate_output, write_json
from original import Original, SUPPORTED_SHA256

ROOT = Path(__file__).resolve().parents[1]
FIELDS = ("caller_address", "caller_symbol", "callsite_address", "callee_address", "callee_symbol", "mnemonic")


def digest(path: Path) -> str:
    result = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            result.update(chunk)
    return result.hexdigest()


def reusable_cache(path: Path, identity: dict) -> dict | None:
    """Reuse only an intact index made with these exact inputs and exporter."""
    try:
        metadata = json.loads(Path(str(path) + ".meta.json").read_text(encoding="utf-8"))
        if (not isinstance(metadata, dict) or metadata.get("schema") != 1
                or metadata.get("kind") != "direct-callsites"
                or any(metadata.get(key) != value for key, value in identity.items())
                or not isinstance(metadata.get("direct_calls"), int) or metadata["direct_calls"] <= 0
                or not isinstance(metadata.get("indirect_calls"), list)
                or metadata.get("tsv_sha256") != digest(path)):
            return None
        with path.open(encoding="utf-8") as stream:
            if stream.readline().rstrip("\r\n") != "\t".join(FIELDS):
                return None
        return metadata
    except (OSError, ValueError):
        return None


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
    parser.add_argument("--reuse", action="store_true", help="reuse intact cached output only when ELF, exporter and objdump identities match")
    args = parser.parse_args()
    metadata = Path(str(args.out) + ".meta.json")
    try:
        for path in (args.out, metadata):
            validate_output(ROOT, path, [args.original.resolve().parent])
        original_sha = digest(args.original)
        if original_sha != SUPPORTED_SHA256:
            raise ValueError(f"Unsupported original build: {original_sha}")
        env = {**os.environ, "LC_ALL": "C"}
        identity = {"original_elf_sha256": original_sha,
                    "tool": subprocess.check_output(["objdump", "--version"], text=True, env=env).splitlines()[0],
                    "generator_inputs": {path: digest(ROOT / path) for path in
                                         ("tools/export_callsites.py", "tools/original.py")}}
        cached = reusable_cache(args.out, identity) if args.reuse else None
        if cached is not None:
            print(f"callsite cache HIT: {cached['direct_calls']} direct sites; {args.out}")
            return 0
        original = Original(args.original)  # Exact supported SHA-256 gate before decoding.
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
        write_json(metadata, {"schema": 1, "kind": "direct-callsites", **identity,
                   "tsv_sha256": digest(args.out), "direct_calls": len(rows),
                   "boundary": "Symbol-bounded direct CALL instructions only; address order, not runtime order. No branch predicates, indirect/virtual resolution or tail-call index.",
                   **unresolved})
        print(f"{len(rows)} direct sites; {len(unresolved['indirect_calls'])} indirect; "
              f"{unresolved['unattributed_calls']} unattributed. {args.out}")
    except (OSError, ValueError, subprocess.SubprocessError) as exc:
        parser.exit(2, f"callsites: {exc}\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
