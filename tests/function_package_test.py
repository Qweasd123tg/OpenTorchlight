#!/usr/bin/env python3
"""Focused tests for deterministic, bounded function-package automation."""
from __future__ import annotations

import hashlib
import importlib.util
import json
import sys
import tempfile
import unittest
from pathlib import Path

MODULE_PATH = Path(__file__).resolve().parents[1] / "tools/function_package.py"
SPEC = importlib.util.spec_from_file_location("function_package", MODULE_PATH)
assert SPEC and SPEC.loader
function_package = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = function_package
SPEC.loader.exec_module(function_package)


class FunctionPackageTest(unittest.TestCase):
    def setUp(self) -> None:
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        for directory in (
            "research/decompiled-core", "research/decompiled", "research/disassembly",
            "src", "include", "tests",
        ):
            (self.root / directory).mkdir(parents=True, exist_ok=True)
        self.write("tools/function_package.py", "# fixture generator identity\n")
        self.write("research/original-symbols.txt", "00001000 00000020 T FuncA\n00002000 00000010 T FuncB\n")
        self.write(
            "research/coverage.tsv",
            "address\tsymbol\tsubsystem\tstatus\tincoming\toutgoing\troot_distance\tpriority\tboundary\tevidence\timplementation\ttests\tcomparison\taliases\n"
            "0x00001000\tFuncA\tcombat\tpartial\t1\t1\t1\t9\treviewed\tresearch/evidence.md\tsrc/a.cpp\ttests/a.cpp\toriginal-vs-port\tFuncA\n",
        )
        self.write(
            "research/function-transfer.json",
            json.dumps({"functions": {"0x00001000": {
                "stages": {"analyzed": True, "ported": False, "wired": False, "compared": False},
                "evidence": "research/evidence.md", "implementation": "src/a.cpp", "notes": "bounded",
            }}}),
        )
        self.write(
            "research/original-callgraph.tsv",
            "caller_address\tcaller_symbol\tcallee_address\tcallee_symbol\n"
            "0x00001000\tFuncA\t0x00002000\tFuncB\n"
            "0x00002000\tFuncB\t0x00001000\tFuncA\n",
        )
        self.write("research/decompiled/a.c", "// FuncA 0x00001000\n")
        self.write("research/disassembly/a.asm", "; 0x00001000 FuncA\n")
        self.write("src/a.cpp", "// original 0x00001000 FuncA\n")

    def tearDown(self) -> None:
        self.temp.cleanup()

    def write(self, relative: str, text: str) -> None:
        path = self.root / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")

    def external_callsites(self, metadata_changes: dict | None = None) -> Path:
        path = self.root / "cache/calls.tsv"
        self.write(
            "cache/calls.tsv",
            "caller_address\tcaller_symbol\tcallsite_address\tcallee_address\tcallee_symbol\tmnemonic\n"
            "0x1000\tFuncA\t0x1004\t0x2000\tFuncB\tCALL\n",
        )
        metadata = {
            "schema": 1, "kind": "direct-callsites",
            "original_elf_sha256": function_package.ELF_SHA,
            "tsv_sha256": hashlib.sha256(path.read_bytes()).hexdigest(),
            "boundary": "Direct calls only; static address order, not runtime order.",
            "direct_calls": 1, "unattributed_calls": 2,
            "indirect_calls": [
                {"caller_address": "00001000", "caller_symbol": "FuncA",
                 "callsite_address": "00001008", "operand": "*%eax"},
                {"caller_address": "00002000", "caller_symbol": "FuncB",
                 "callsite_address": "00002008", "operand": "*%edx"},
            ],
        }
        metadata.update(metadata_changes or {})
        self.write("cache/calls.tsv.meta.json", json.dumps(metadata))
        return path

    def snapshot(self) -> dict[str, tuple[int, str]]:
        result = {}
        for path in sorted(self.root.rglob("*")):
            if path.is_file():
                data = path.read_bytes()
                result[path.relative_to(self.root).as_posix()] = (
                    path.stat().st_mtime_ns, hashlib.sha256(data).hexdigest()
                )
        return result

    def test_rejects_invalid_interior_and_unknown_addresses(self) -> None:
        builder = function_package.FunctionPackageBuilder(self.root)
        with self.assertRaisesRegex(function_package.AddressError, "invalid hexadecimal"):
            builder.resolve_address("not-an-address")
        with self.assertRaisesRegex(function_package.AddressError, "interior address"):
            builder.resolve_address("0x1001")
        with self.assertRaisesRegex(function_package.AddressError, "unknown function"):
            builder.resolve_address("0x3000")

    def test_batch_limit_is_checked_before_packet_work(self) -> None:
        builder = function_package.FunctionPackageBuilder(self.root)
        with self.assertRaisesRegex(function_package.AddressError, "1..64"):
            builder.document([])
        with self.assertRaisesRegex(function_package.AddressError, "1..64"):
            builder.document(["0x1000"] * 65)
        document = builder.document(["0x1000"] * 64)
        self.assertEqual(64, len(document["functions"]))

    def test_absent_callsites_is_explicit_and_machine_readable(self) -> None:
        packet = function_package.FunctionPackageBuilder(self.root).document(["0x1000"])["functions"][0]
        self.assertFalse(packet["callsites"]["available"])
        self.assertIn("original-callsites.tsv is absent", packet["callsites"]["warning"])
        self.assertIn("callsites_index_missing", [item["code"] for item in packet["unresolved_work"]])
        self.assertEqual(["research/evidence.md", "src/a.cpp", "tests/a.cpp", "original-vs-port"],
                         packet["known_references"])

    def test_callsites_keep_repeats_and_instruction_order(self) -> None:
        self.write(
            "research/original-callsites.tsv",
            "caller_address\tcaller_symbol\tcallsite_address\tcallee_address\tcallee_symbol\tmnemonic\n"
            "0x1000\tFuncA\t0x1008\t0x2000\tFuncB\tCALL\n"
            "0x1000\tFuncA\t0x1004\t0x2000\tFuncB\tCALL\n"
            "0x1000\tFuncA\t0x1008\t0x2000\tFuncB\tCALL\n",
        )
        packet = function_package.FunctionPackageBuilder(self.root).document(["0x1000"])["functions"][0]
        sites = packet["callsites"]["outgoing"]
        self.assertEqual(["0x1004", "0x1008", "0x1008"],
                         [row["callsite_address"] for row in sites])

    def test_external_callsites_validates_sidecar_and_filters_indirect_calls(self) -> None:
        path = self.external_callsites()
        packet = function_package.FunctionPackageBuilder(
            self.root, callsites_path=path
        ).document(["0x1000"])["functions"][0]
        self.assertEqual("direct-callsites", packet["callsites"]["source"]["kind"])
        indirect = packet["callsites"]["unresolved_indirect_calls_for_caller"]
        self.assertEqual(["00001000"], [row["caller_address"] for row in indirect])
        self.assertIn("indirect_calls_unresolved",
                      [item["code"] for item in packet["unresolved_work"]])

    def test_rejects_tampered_or_wrong_sidecar(self) -> None:
        cases = (
            ({"kind": "something-else"}, "kind"),
            ({"original_elf_sha256": "0" * 64}, "original_elf_sha256"),
            ({"tsv_sha256": "f" * 64}, "tsv_sha256"),
        )
        for changes, message in cases:
            with self.subTest(message=message):
                path = self.external_callsites(changes)
                with self.assertRaisesRegex(ValueError, message):
                    function_package.FunctionPackageBuilder(self.root, callsites_path=path)
        path = self.external_callsites()
        path.write_text(path.read_text(encoding="utf-8") + "# tampered\n", encoding="utf-8")
        with self.assertRaisesRegex(ValueError, "tsv_sha256"):
            function_package.FunctionPackageBuilder(self.root, callsites_path=path)

    def test_output_cannot_overwrite_source(self) -> None:
        builder = function_package.FunctionPackageBuilder(self.root)
        with self.assertRaisesRegex(ValueError, "ignored, not source"):
            function_package.validate_destinations(
                MODULE_PATH.parents[1], builder, [MODULE_PATH]
            )

    def test_output_is_stable_and_inputs_are_read_only(self) -> None:
        before = self.snapshot()
        first = function_package.FunctionPackageBuilder(self.root).document(["0x1000", "0x2000"])
        middle = self.snapshot()
        second = function_package.FunctionPackageBuilder(self.root).document(["0x1000", "0x2000"])
        after = self.snapshot()
        self.assertEqual(before, middle)
        self.assertEqual(before, after)
        self.assertEqual(
            json.dumps(first, ensure_ascii=False, sort_keys=True),
            json.dumps(second, ensure_ascii=False, sort_keys=True),
        )
        self.assertEqual(64, len(first["source_fingerprint"]["sha256"]))
        self.assertEqual(function_package.ELF_SHA, first["original_elf"]["sha256"])


if __name__ == "__main__":
    unittest.main()
