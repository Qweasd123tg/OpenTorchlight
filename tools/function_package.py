#!/usr/bin/env python3
"""Build deterministic code-first research packets from reviewed inputs.

No ELF execution, ABI/field inference, or transfer-stage promotion is done.
Markdown remains the default; ``--format json`` emits the same structured
packet. Repeat ``--address`` for an explicit batch of 1..64 function starts.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import io
import json
import re
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable

ROOT = Path(__file__).resolve().parents[1]
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))
from automation_state import validate_output
from transfer_contract import completion

ELF_PATH = "/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64"
ELF_SHA = "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"
MAX_BATCH = 64
MAX_HITS = 60
CALLSITE_FIELDS = ("caller_address", "caller_symbol", "callsite_address",
                   "callee_address", "callee_symbol", "mnemonic")
SYMBOL_RE = re.compile(r"^([0-9a-fA-F]+) (?:([0-9a-fA-F]+) )?([TtWw]) (.+)$")


class AddressError(ValueError):
    """An address cannot be used as a function-package start."""


def normalize(address: str) -> str:
    raw = address.strip().lower()
    if raw.startswith("0x"):
        raw = raw[2:]
    if not raw or not re.fullmatch(r"[0-9a-f]+", raw):
        raise AddressError(f"invalid hexadecimal address: {address!r}")
    value = int(raw, 16)
    if value > 0xFFFFFFFFFFFFFFFF:
        raise AddressError(f"address is outside the supported range: {address!r}")
    return f"{value:08x}"


def _key(row: dict[str, str], fields: tuple[str, ...]) -> tuple[int, ...]:
    return tuple(int(row.get(field) or "0", 16) for field in fields)


@dataclass(frozen=True)
class SearchFile:
    path: str
    lines: tuple[str, ...]


class FunctionPackageBuilder:
    """Single-load index shared by all addresses in a batch."""

    def __init__(self, root: Path = ROOT, callsites_path: Path | None = None):
        self.root = root.resolve()
        self._fingerprints: dict[str, dict[str, object]] = {}
        self.input_paths: list[Path] = []
        self._corpora: dict[str, tuple[SearchFile, ...]] = {}
        self.callsites_path = (callsites_path.resolve() if callsites_path else
                               self.root / "research/original-callsites.tsv")
        self.callsites_metadata: dict | None = None
        self.indirect_calls: dict[str, list[dict]] = {}
        self._read_bytes("tools/function_package.py")
        self._optional_text("tools/transfer_contract.py")
        self.completion_hashes: dict = {}
        self.symbols = self._load_symbols()
        self.coverage = self._load_coverage()
        self.transfers = self._load_transfers()
        self.callgraph_in, self.callgraph_out = self._load_callgraph()
        self.callsite_in, self.callsite_out, self.have_callsites = self._load_callsites()

    def _read_bytes(self, relative: str) -> bytes:
        path = self.root / relative
        data = path.read_bytes()
        self.input_paths.append(path.resolve())
        self._fingerprints[relative] = {
            "sha256": hashlib.sha256(data).hexdigest(), "bytes": len(data)
        }
        return data

    def _read_external(self, path: Path, label: str) -> bytes:
        data = path.read_bytes()
        self.input_paths.append(path.resolve())
        self._fingerprints[label] = {
            "sha256": hashlib.sha256(data).hexdigest(), "bytes": len(data)
        }
        return data

    def _read_text(self, relative: str) -> str:
        return self._read_bytes(relative).decode("utf-8", errors="replace")

    def _optional_text(self, relative: str) -> str | None:
        return self._read_text(relative) if (self.root / relative).is_file() else None

    @staticmethod
    def _rows(text: str) -> Iterable[dict[str, str]]:
        return csv.DictReader(io.StringIO(text), delimiter="\t")

    def _load_symbols(self) -> dict[str, dict[str, object]]:
        result: dict[str, dict[str, object]] = {}
        for line in self._read_text("research/original-symbols.txt").splitlines():
            match = SYMBOL_RE.match(line)
            if not match:
                continue
            address = f"{int(match[1], 16):08x}"
            size = int(match[2], 16) if match[2] else 0
            row = result.setdefault(address, {"aliases": [], "size": 0})
            aliases = row["aliases"]
            assert isinstance(aliases, list)
            aliases.append(match[4])
            row["size"] = max(int(row["size"]), size)
        return result

    def _load_coverage(self) -> dict[str, dict[str, str]]:
        result: dict[str, dict[str, str]] = {}
        for row in self._rows(self._read_text("research/coverage.tsv")):
            raw = row.get("address", "")
            if not raw or raw.startswith("port:"):
                continue
            try:
                result.setdefault(normalize(raw), dict(row))
            except AddressError:
                pass
        return result

    def _load_transfers(self) -> dict[str, dict]:
        text = self._optional_text("research/function-transfer.json")
        if text is None:
            return {}
        result: dict[str, dict] = {}
        for raw, entry in json.loads(text).get("functions", {}).items():
            try:
                result[normalize(raw)] = entry
            except AddressError:
                pass
        return result

    def _load_callgraph(self) -> tuple[dict[str, list[dict]], dict[str, list[dict]]]:
        incoming: dict[str, list[dict]] = {}
        outgoing: dict[str, list[dict]] = {}
        for raw in self._rows(self._read_text("research/original-callgraph.tsv")):
            row = dict(raw)
            source, target = normalize(row["caller_address"]), normalize(row["callee_address"])
            outgoing.setdefault(source, []).append(row)
            incoming.setdefault(target, []).append(row)
        for rows in outgoing.values():
            rows.sort(key=lambda row: _key(row, ("callee_address", "caller_address")))
        for rows in incoming.values():
            rows.sort(key=lambda row: _key(row, ("caller_address", "callee_address")))
        return incoming, outgoing

    def _load_callsites(self) -> tuple[dict[str, list[dict]], dict[str, list[dict]], bool]:
        path = self.callsites_path
        if not path.is_file():
            return {}, {}, False
        try:
            relative = path.relative_to(self.root).as_posix()
        except ValueError:
            relative = "external:original-callsites.tsv"
        data = self._read_external(path, relative)
        text = data.decode("utf-8", errors="replace")
        sidecar = Path(str(path) + ".meta.json")
        if sidecar.is_file():
            metadata = json.loads(self._read_external(
                sidecar, (relative + ".meta.json")
            ).decode("utf-8"))
            if metadata.get("kind") != "direct-callsites":
                raise ValueError("callsite sidecar kind must be direct-callsites")
            if metadata.get("original_elf_sha256") != ELF_SHA:
                raise ValueError("callsite sidecar original_elf_sha256 does not match the supported ELF")
            actual = hashlib.sha256(data).hexdigest()
            if metadata.get("tsv_sha256") != actual:
                raise ValueError("callsite sidecar tsv_sha256 does not match the TSV")
            self.callsites_metadata = metadata
            for item in metadata.get("indirect_calls", []):
                if not isinstance(item, dict) or "caller_address" not in item:
                    raise ValueError("callsite sidecar has an invalid indirect_calls entry")
                self.indirect_calls.setdefault(normalize(item["caller_address"]), []).append(item)
            for rows in self.indirect_calls.values():
                rows.sort(key=lambda row: _key(row, ("callsite_address",)))
        incoming: dict[str, list[dict]] = {}
        outgoing: dict[str, list[dict]] = {}
        reader = csv.DictReader(io.StringIO(text), delimiter="\t")
        if tuple(reader.fieldnames or ()) != CALLSITE_FIELDS:
            raise ValueError(f"callsite TSV schema must be exactly: {', '.join(CALLSITE_FIELDS)}")
        for raw in reader:
            row = dict(raw)
            try:
                source = normalize(row["caller_address"])
                target = normalize(row["callee_address"])
                normalize(row["callsite_address"])
            except (AddressError, TypeError) as exc:
                raise ValueError(f"invalid callsite TSV row: {row}") from exc
            # Keep every site. Sorting below is static instruction-address order,
            # never a claim about runtime execution order or branch conditions.
            outgoing.setdefault(source, []).append(row)
            incoming.setdefault(target, []).append(row)
        for rows in outgoing.values():
            rows.sort(key=lambda row: _key(row, ("callsite_address", "callee_address")))
        for rows in incoming.values():
            rows.sort(key=lambda row: _key(row, ("caller_address", "callsite_address")))
        return incoming, outgoing, True

    def resolve_address(self, requested: str) -> str:
        address = normalize(requested)
        if address in self.symbols:
            return address
        value = int(address, 16)
        for start, row in sorted(self.symbols.items(), key=lambda item: int(item[0], 16)):
            size = int(row["size"])
            if size and int(start, 16) < value < int(start, 16) + size:
                raise AddressError(f"interior address 0x{address}; function starts at 0x{start}")
        raise AddressError(f"unknown function address: 0x{address}")

    def resolve_symbol(self, query: str) -> str:
        matches = [address for address, row in self.symbols.items()
                   if query in ";".join(row["aliases"])]
        if len(matches) != 1:
            raise AddressError(f"symbol matches {len(matches)} addresses, refine query: {matches[:10]}")
        return matches[0]

    def _load_corpus(self, name: str, directories: tuple[str, ...],
                     suffixes: frozenset[str]) -> tuple[SearchFile, ...]:
        if name in self._corpora:
            return self._corpora[name]
        files: list[SearchFile] = []
        for directory in directories:
            base = self.root / directory
            if not base.is_dir():
                continue
            for path in sorted(base.rglob("*")):
                if path.is_file() and path.suffix.lower() in suffixes:
                    relative = path.relative_to(self.root).as_posix()
                    files.append(SearchFile(relative, tuple(self._read_text(relative).splitlines())))
        self._corpora[name] = tuple(files)
        return self._corpora[name]

    def _search(self, name: str, directories: tuple[str, ...],
                suffixes: frozenset[str], patterns: tuple[str, ...]) -> dict:
        hits: list[dict[str, object]] = []
        total = 0
        for source in self._load_corpus(name, directories, suffixes):
            for number, line in enumerate(source.lines, 1):
                if any(pattern in line for pattern in patterns):
                    total += 1
                    if len(hits) < MAX_HITS:
                        hits.append({"path": source.path, "line": number, "text": line.strip()[:220]})
        return {"hits": hits, "total_hits": total, "truncated": total > len(hits)}

    @staticmethod
    def _known_references(registry: dict | None, transfer: dict | None) -> list[str]:
        values: list[str] = []
        fields = ("evidence", "implementation", "tests", "comparison")
        for row in (registry, transfer):
            if not row:
                continue
            for field in fields:
                value = row.get(field)
                if isinstance(value, str):
                    for part in value.split(";"):
                        part = part.strip()
                        if part and part not in values:
                            values.append(part)
        return values

    def packet(self, requested: str) -> dict:
        address = self.resolve_address(requested)
        symbol = self.symbols[address]
        aliases = list(symbol["aliases"])
        registry, transfer = self.coverage.get(address), self.transfers.get(address)
        short = address.lstrip("0") or "0"
        patterns = tuple(dict.fromkeys((f"0x{address}", f"0x{short}", f"00{address}", address, *aliases[:3])))
        evidence = {
            "decompilation": self._search("decompilation", ("research/decompiled-core", "research/decompiled"),
                                           frozenset({".c", ".cpp", ".txt"}), patterns),
            "disassembly": self._search("disassembly", ("research/disassembly",),
                                        frozenset({".asm", ".txt", ".md"}), patterns),
            "port_references": self._search("port", ("src", "include", "tests"),
                                             frozenset({".c", ".cpp", ".hpp", ".h", ".py"}), patterns),
        }
        unresolved: list[dict[str, str]] = []
        if registry is None:
            unresolved.append({"code": "coverage_row_missing", "detail": "Regenerate/review coverage.tsv."})
        elif registry.get("status") == "unseen" or registry.get("boundary", "").startswith("No reviewed"):
            unresolved.append({"code": "reviewed_boundary_missing", "detail": "No reviewed function boundary is recorded."})
        if transfer is None:
            unresolved.append({"code": "transfer_entry_missing", "detail": "No function-transfer entry exists."})
        else:
            stages = transfer.get("stages", {})
            for stage in ("analyzed", "ported", "wired", "compared"):
                if stages.get(stage) is not True:
                    unresolved.append({"code": f"stage_{stage}_open", "detail": f"Transfer stage {stage} is not true."})
        if not self.have_callsites:
            unresolved.append({"code": "callsites_index_missing",
                               "detail": "Order, conditions and repeat counts are unavailable from the set-only callgraph."})
        for kind in ("decompilation", "disassembly"):
            if evidence[kind]["total_hits"] == 0:
                unresolved.append({"code": f"{kind}_evidence_missing",
                                   "detail": f"No {kind} navigation hit was found."})
        indirect = list(self.indirect_calls.get(address, []))
        accepted = completion(transfer, self.root, self.completion_hashes)
        if accepted["status"] != "reviewed_full":
            unresolved.append({"code": "whole_function_" + accepted["status"],
                               "detail": "; ".join(accepted["open_items"] + accepted["errors"]) or
                               "Legacy stage flags do not establish whole-function completion."})
        record = (transfer or {}).get("completion")
        inputs = record.get("inputs", {}) if isinstance(record, dict) else {}
        for path in inputs if isinstance(inputs, dict) else {}:
            candidate = self.root / path
            if (not Path(path).is_absolute() and ".." not in Path(path).parts and
                    candidate.is_file() and not candidate.is_symlink() and candidate.resolve().is_relative_to(self.root)):
                self._read_bytes(path)
        if indirect:
            unresolved.append({"code": "indirect_calls_unresolved",
                               "detail": f"{len(indirect)} indirect/virtual call site(s) remain for this caller."})
        if self.callsites_metadata:
            source = {key: self.callsites_metadata.get(key) for key in (
                "kind", "original_elf_sha256", "tsv_sha256", "direct_calls", "tool",
                "boundary", "unattributed_calls", "bounded_function_symbols"
            ) if key in self.callsites_metadata}
        else:
            source = None
        return {
            "address": "0x" + address, "aliases": aliases, "size_bytes": int(symbol["size"]),
            "registry": registry, "transfer": transfer, "completion": accepted,
            "callgraph": {"completeness": "resolved_direct_edge_set_only",
                          "incoming": list(self.callgraph_in.get(address, [])),
                          "outgoing": list(self.callgraph_out.get(address, []))},
            "callsites": {"available": self.have_callsites,
                          "completeness": ("direct_sites_in_static_instruction_address_order; runtime_order_branch_conditions_and_virtual_targets_unresolved"
                                           if self.have_callsites else "absent"),
                          "warning": (None if self.have_callsites else
                                      (f"requested callsite index is absent: {self.callsites_path}"
                                       if self.callsites_path != self.root / "research/original-callsites.tsv"
                                       else "research/original-callsites.tsv is absent; export a bounded index first")),
                          "source": source,
                          "unresolved_indirect_calls_for_caller": indirect,
                          "incoming": list(self.callsite_in.get(address, [])),
                          "outgoing": list(self.callsite_out.get(address, []))},
            "known_references": self._known_references(registry, transfer),
            "evidence_hits": evidence, "unresolved_work": unresolved,
        }

    def document(self, addresses: list[str]) -> dict:
        if not 1 <= len(addresses) <= MAX_BATCH:
            raise AddressError(f"batch must contain 1..{MAX_BATCH} explicit addresses")
        packets = [self.packet(address) for address in addresses]
        inputs = [{"path": path, **meta} for path, meta in sorted(self._fingerprints.items())]
        digest = hashlib.sha256()
        for item in inputs:
            digest.update(item["path"].encode())
            digest.update(b"\0")
            digest.update(str(item["sha256"]).encode("ascii"))
            digest.update(b"\n")
        return {"schema": 1, "generator": "tools/function_package.py",
                "limits": {"max_explicit_addresses": MAX_BATCH, "max_hits_per_evidence_kind": MAX_HITS},
                "original_elf": {"path": ELF_PATH, "sha256": ELF_SHA},
                "source_fingerprint": {"algorithm": "sha256(path\\0content_sha256\\n)",
                                       "sha256": digest.hexdigest(), "inputs": inputs},
                "functions": packets}


def validate_destinations(root: Path, builder: FunctionPackageBuilder,
                          destinations: Iterable[Path]) -> None:
    """Reject output paths that overlap source, ELF, or any packet input."""
    protected = [Path(ELF_PATH), *builder.input_paths]
    for destination in destinations:
        validate_output(root, destination, protected)


def _hit_lines(section: dict) -> list[str]:
    lines = [f"  - {hit['path']}:{hit['line']}:{hit['text']}" for hit in section["hits"]]
    if not lines:
        lines = ["  - none"]
    if section["truncated"]:
        lines.append(f"  - ... {section['total_hits'] - len(section['hits'])} more hits omitted")
    return lines


def render_markdown(document: dict) -> str:
    lines: list[str] = []
    fingerprint = document["source_fingerprint"]
    for packet in document["functions"]:
        if lines:
            lines += ["", "---", ""]
        lines += [f"# Function package {packet['address']}", "",
                  f"ELF SHA-256 `{document['original_elf']['sha256']}`.",
                  f"Packet input fingerprint `{fingerprint['sha256']}` ({len(fingerprint['inputs'])} files).", "",
                  f"Aliases: {'; '.join(packet['aliases'])}",
                  f"Size: 0x{packet['size_bytes']:x} ({packet['size_bytes']} bytes).", ""]
        row = packet["registry"]
        if row:
            lines += ["## Registry (coverage.tsv)",
                      f"- status `{row['status']}` subsystem `{row['subsystem']}` in={row['incoming']} out={row['outgoing']} priority={row['priority']}",
                      f"- boundary: {row['boundary']}", f"- evidence: {row['evidence']}",
                      f"- implementation: {row['implementation']}", f"- tests: {row['tests']}",
                      f"- comparison: {row['comparison']}", ""]
        else:
            lines += ["## Registry", "No coverage.tsv row (regenerate coverage).", ""]
        transfer = packet["transfer"]
        accepted = packet["completion"]
        lines += ["## Whole-function acceptance (not legacy stages)",
                  f"- status: `{accepted['status']}`", "- Full closure is an explicit reviewed claim, not inferred from four true stages."]
        lines += [f"- open: {item}" for item in accepted["open_items"] + accepted["errors"]]
        lines.append("")
        if transfer is None:
            lines += ["## Transfer stages", "No entry in research/function-transfer.json.", ""]
        else:
            stages = transfer.get("stages", {})
            lines += ["## Transfer stages (analyzed/ported/wired/compared)",
                      f"- analyzed={stages.get('analyzed')} ported={stages.get('ported')} wired={stages.get('wired')} compared={stages.get('compared')}",
                      f"- notes: {transfer.get('notes', '')}", f"- evidence: {transfer.get('evidence', '')}", ""]
        graph = packet["callgraph"]
        lines += ["## Callgraph (resolved direct edges only)",
                  f"- outgoing {len(graph['outgoing'])}, incoming {len(graph['incoming'])}"]
        for edge in graph["outgoing"][:40]:
            lines.append(f"  - out {edge['caller_address']} -> {edge['callee_address']} {edge['callee_symbol']}")
        for edge in graph["incoming"][:40]:
            lines.append(f"  - in {edge['caller_address']} {edge['caller_symbol']} -> {edge['callee_address']}")
        lines.append("")
        sites = packet["callsites"]
        if sites["available"]:
            lines += ["## Call sites (static instruction-address order; repeats preserved)",
                      f"- outgoing sites {len(sites['outgoing'])}, incoming sites {len(sites['incoming'])}"]
            if sites["source"] and sites["source"].get("boundary"):
                lines.append(f"- exporter boundary: {sites['source']['boundary']}")
            for edge in sites["outgoing"][:60]:
                lines.append(f"  - out site={edge['callsite_address']} -> {edge['callee_address']} {edge['callee_symbol']} [{edge.get('mnemonic', '')}]")
            for edge in sites["incoming"][:60]:
                lines.append(f"  - in {edge['caller_address']} {edge['caller_symbol']} site={edge['callsite_address']}")
            indirect = sites["unresolved_indirect_calls_for_caller"]
            if indirect:
                lines.append(f"- unresolved indirect/virtual sites for this caller: {len(indirect)}")
                for edge in indirect[:60]:
                    lines.append(f"  - indirect site={edge['callsite_address']} operand={edge.get('operand', '')}")
        else:
            lines += ["## Call sites", "WARNING: " + sites["warning"] +
                      ". Order, branches and repeat counts are NOT recoverable from the set-only callgraph."]
        lines += ["", "## Decompilation hits (navigation only, verify against ASM)", ""]
        lines += _hit_lines(packet["evidence_hits"]["decompilation"])
        lines += ["", "## Disassembly hits", ""] + _hit_lines(packet["evidence_hits"]["disassembly"])
        lines += ["", "## Port references", ""] + _hit_lines(packet["evidence_hits"]["port_references"])
        lines += ["", "## Machine-readable unresolved work", ""]
        lines += ([f"- `{item['code']}`: {item['detail']}" for item in packet["unresolved_work"]]
                  or ["- none recorded"])
        lines += ["", "## Next step for this function",
                  "1. Read the full decompilation + ASM for every branch.",
                  "2. List field writes, error paths and all call sites with conditions.",
                  "3. Update research/function-transfer.json stages with evidence; do not invent ABI, field meanings or branch purposes.", ""]
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--address", action="append", help="exact function start; repeat for a 1..64 batch")
    group.add_argument("--symbol", help="unique substring (single-function mode)")
    parser.add_argument("--format", choices=("markdown", "json"), default="markdown")
    parser.add_argument("--out", type=Path)
    parser.add_argument("--json-out", type=Path,
                        help="also write structured JSON while keeping markdown output")
    parser.add_argument("--callsites", type=Path,
                        help="read-only external/ignored direct-callsites TSV override")
    args = parser.parse_args()
    try:
        builder = FunctionPackageBuilder(callsites_path=args.callsites)
        if args.address and len(args.address) > MAX_BATCH:
            raise AddressError(f"batch must contain 1..{MAX_BATCH} explicit addresses")
        addresses = ([builder.resolve_address(address) for address in args.address]
                     if args.address else [builder.resolve_symbol(args.symbol)])
        document = builder.document(addresses)
        destinations = [path for path in (args.out, args.json_out) if path]
        if len({path.resolve() for path in destinations}) != len(destinations):
            raise ValueError("--json-out and --out must name different files")
        validate_destinations(ROOT, builder, destinations)
    except (AddressError, OSError, ValueError, json.JSONDecodeError) as exc:
        parser.error(str(exc))
    json_text = json.dumps(document, indent=2, ensure_ascii=False, sort_keys=True) + "\n"
    if args.json_out:
        args.json_out.parent.mkdir(parents=True, exist_ok=True)
        args.json_out.write_text(json_text, encoding="utf-8")
    text = json_text if args.format == "json" else render_markdown(document)
    if args.out:
        args.out.parent.mkdir(parents=True, exist_ok=True)
        args.out.write_text(text, encoding="utf-8")
        suffix = f" and {args.json_out}" if args.json_out else ""
        print(f"Wrote {args.out}{suffix} ({len(document['functions'])} function packet(s))")
    else:
        print(text, end="" if text.endswith("\n") else "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
