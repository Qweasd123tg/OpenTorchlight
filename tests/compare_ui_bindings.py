#!/usr/bin/env python3
"""Execute unchanged mapToFunctions with explicit library adapters, not a game.

CEGUI property/string, old-ABI std::string and C-locale StringUpper calls are
fixture adapters. Native traversal, guards, lookup and userData writes execute
unchanged. C++ unwinding/library fidelity is NOT established by this harness.
"""
from __future__ import annotations
import argparse
import ctypes as c
import hashlib
import json
from pathlib import Path
import platform
import random
import struct
import subprocess
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from original import Original
from audit_original import recover_commands
from automation_state import validate_output, write_json
from native_typed_reference import Memory

ROOT = Path(__file__).resolve().parents[1]
ADDRESS = 0xA980E0


class NativeBindings(Memory):
    def __init__(self, original):
        super().__init__()
        try:
            self.original = original
            self.commands, _ = recover_commands(original)
            self.owners = []
            self.temporary = []
            self.strings = {}
            self.properties = {}
            self.events = []
            self.put(ADDRESS, original.read(ADDRESS, 0x374))
            self.put(0xFE4840, original.read(0xFE4840, 8))
            table = [self.old_string(row["name"].encode(), self.owners) for row in self.commands]
            self.put(0x14B7DC0, struct.pack("<97Q", *table))
            cf = c.CFUNCTYPE

            def string(destination, raw):
                self.cegui_string(destination, c.string_at(raw))

            def present(window, key):
                self.events.append(("present", self.windows[window]))
                return self.properties[window] is not None

            def get(destination, window, key):
                self.events.append(("get", self.windows[window]))
                self.cegui_string(destination, self.properties[window])
                return destination

            def utf8(source):
                buf = c.create_string_buffer(self.strings[source])
                self.temporary.append(buf)
                return c.addressof(buf)

            def std_string(destination, raw, allocator):
                c.c_void_p.from_address(destination).value = self.old_string(c.string_at(raw), self.temporary)

            def uppercase(destination, source):
                raw = c.string_at(c.c_void_p.from_address(source).value)
                # Explicit C-locale fixture, NOT execution of StringUpper.
                c.c_void_p.from_address(destination).value = self.old_string(raw.upper(), self.temporary)
                return destination

            self.callback(0x899620, cf(None, c.c_void_p, c.c_void_p), string)
            self.callback(0x553E18, cf(c.c_bool, c.c_void_p, c.c_void_p), present)
            self.callback(0x554418, cf(c.c_void_p, c.c_void_p, c.c_void_p, c.c_void_p), get)
            self.callback(0x556378, cf(c.c_void_p, c.c_void_p), utf8)
            self.callback(0x5562F8, cf(None, c.c_void_p, c.c_void_p, c.c_void_p), std_string)
            self.callback(0xC8E0E0, cf(c.c_void_p, c.c_void_p, c.c_void_p), uppercase)
            self.callback(0x555FE8, cf(None, c.c_void_p), lambda p: self.strings.pop(p, None))
            self.callback(0x5557D8, cf(None, c.c_void_p, c.c_void_p), lambda p, a: None)
            self.protect()
            self.invoke = cf(None, c.c_void_p, c.c_void_p)(ADDRESS)
        except BaseException:
            self.close()
            raise

    @staticmethod
    def old_string(raw, owners):
        buf = c.create_string_buffer(24 + len(raw) + 1)
        struct.pack_into("<QQi", buf, 0, len(raw), len(raw), 0)
        c.memmove(c.addressof(buf) + 24, raw, len(raw))
        owners.append(buf)
        return c.addressof(buf) + 24

    def cegui_string(self, destination, raw):
        self.strings[destination] = raw
        c.c_uint64.from_address(destination).value = len(raw)

    def run(self, rows):
        self.temporary = []
        self.strings = {}
        self.events = []
        gameui = c.create_string_buffer(0x1920)
        base = c.addressof(gameui) + 0x1790
        for i in range(97):
            struct.pack_into("<i", gameui, 0x1790 + 4 * i, i)
        nodes = [c.create_string_buffer(0x1E0) for _ in rows]
        addresses = [c.addressof(node) for node in nodes]
        self.windows = {address: i for i, address in enumerate(addresses)}
        self.properties = {address: rows[i][2] for i, address in enumerate(addresses)}
        for i, (parent, prior, prop) in enumerate(rows):
            children = [addresses[k] for k, row in enumerate(rows) if row[0] == i]
            array = (c.c_void_p * max(1, len(children)))(*children)
            self.temporary.append(array)
            struct.pack_into("<QQ", nodes[i], 0x78, c.addressof(array), c.addressof(array) + 8 * len(children))
            struct.pack_into("<Q", nodes[i], 0x1D8, base + 4 * prior if prior >= 0 else 0)
        for i, row in enumerate(rows):
            if row[0] == -1:
                self.invoke(c.addressof(gameui), addresses[i])
        result = []
        for node in nodes:
            pointer = struct.unpack_from("<Q", node, 0x1D8)[0]
            if pointer and not (base <= pointer < base + 388 and (pointer - base) % 4 == 0):
                raise AssertionError("native returned an unexpected pointer")
            result.append((pointer - base) // 4 if pointer else -1)
        return result, self.events[:]


def cases(commands):
    for row in commands:
        raw = row["name"].encode()
        for value in (raw, raw.lower(), raw + b"\0ignored", raw + b" "):
            yield [(-1, 7, value)]
    yield [(-1, 7, None), (-1, 14, b""), (-1, 15, b"\0"), (-1, -1, b"unknown")]
    rng = random.Random(0xA980E0)
    values = [None, b"", b"\0guiPause", b"guiSelect1", b"gUiPaUsE", b"unknown", b"NONE", b"\xc3\xa9"]
    for _ in range(80):
        yield [(rng.randrange(-1, i) if i else -1, rng.randrange(-1, 97), rng.choice(values)) for i in range(24)]


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--original", type=Path, required=True)
    ap.add_argument("--probe", type=Path)
    ap.add_argument("--output", type=Path, required=True)
    args = ap.parse_args()
    validate_output(ROOT, args.output, [args.original, *([args.probe] if args.probe else [])])
    if platform.machine() != "x86_64":
        return 77
    original = Original(args.original)
    native = NativeBindings(original)
    try:
        tests = list(cases(native.commands))
        expected = [native.run(rows) for rows in tests]
        # Minimal sanity is against explicit original command IDs, not a copy of lookup.
        if expected[0][0] != [0] or native.run([
                (-1, 7, None), (-1, 7, b"unknown"), (-1, 7, b"\0")])[0] != [96, 7, 7]:
            raise AssertionError("native sanity check failed")
        if args.probe:
            lines = []
            for rows in tests:
                lines.append(str(len(rows)))
                lines.extend(f"{parent} {prior} {'_' if prop is None else prop.hex() or '-'}" for parent, prior, prop in rows)
            output = subprocess.check_output([str(args.probe)], input="\n".join(lines) + "\n", text=True)
            observed = [json.loads(line) for line in output.splitlines()]
            if len(observed) != len(expected):
                raise AssertionError(f"port returned {len(observed)} cases; expected {len(expected)}")
            for i, (got, (bindings, events)) in enumerate(zip(observed, expected)):
                if got != {"bindings": bindings, "events": [list(event) for event in events]}:
                    raise AssertionError(f"original/port divergence case {i}: {got!r} != {(bindings, events)!r}")
        write_json(args.output, {"elf_sha256": original.sha256, "address": hex(ADDRESS),
            "body_sha256": hashlib.sha256(original.read(ADDRESS, 0x374)).hexdigest(),
            "cases": len(tests), "nodes": sum(map(len, tests)), "compared_with_port": bool(args.probe),
            "commands": native.commands,
            "boundary": "Unchanged mapToFunctions, synthetic CEGUI/std::string/uppercase adapters; no original exception unwinding or library fidelity claim."})
        print(f"ui bindings: {len(tests)} trees, {sum(map(len, tests))} nodes; native property order and binding pointers" + (" match port" if args.probe else " (native-only)"))
    finally:
        native.close()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
