#!/usr/bin/env python3
"""Compare generated production writers with unchanged whole original bodies.

The raw UI buffer is explicit synthetic state, never an original game object.
Every byte is observed after request and clear; constructors and game update
timing are not implied. Accepted compiler inputs are verified against the ELF.
"""
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

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from automation_state import validate_output, write_json
from original import Original
from native_typed_reference import Memory

ENTRIES = ((0xA828F0, 13), (0xA82900, 21))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--probe", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if platform.system() != "Linux" or platform.machine() != "x86_64":
        return 77
    validate_output(ROOT, args.output, [args.original, args.probe])
    original = Original(args.original)
    bodies = []
    memory = Memory()
    try:
        for address, size in ENTRIES:
            symbol = next(s for s in original.symbols if s.address == address and s.size)
            if symbol.size != size:
                raise ValueError(f"original writer size drifted: {address:#x}")
            body = original.read(address, size)
            memory.put(address, body)
            bodies.append(dict(address=hex(address), size=size,
                               sha256=hashlib.sha256(body).hexdigest()))
        memory.protect()
        request = c.CFUNCTYPE(None, c.c_void_p, c.c_uint32, c.c_uint32)(ENTRIES[0][0])
        clear = c.CFUNCTYPE(None, c.c_void_p)(ENTRIES[1][0])
        # Accepted compiler inputs are executable evidence, not decompiler text.
        sources = []
        for path in sorted((ROOT / "research/lifted-ui").glob("0*.json")):
            data = json.loads(path.read_text())
            if data["original_elf_sha256"] != original.sha256:
                raise ValueError("accepted p-code ELF differs from original")
            address = int(data["address"], 16)
            symbol = next(s for s in original.symbols if s.address == address and s.size)
            if (data["original_symbol_size"] != symbol.size or
                    hashlib.sha256(original.read(address, symbol.size)).hexdigest() !=
                    data["original_symbol_body_sha256"]):
                raise ValueError(f"accepted whole symbol body drifted: {address:#x}")
            for row in data["instructions"]:
                body = bytes.fromhex(row["bytes"])
                if body != original.read(int(row["address"], 16), len(body)):
                    raise ValueError(f"accepted instruction drifted: {row['address']}")
            sources.append(dict(path=str(path.relative_to(ROOT)),
                                sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
        if original.read(0xFA47F8, 4) != bytes(4):
            raise ValueError("Continue binary32 zero literal drifted")
        edges = (0, 1, 2, 3, 6, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF)
        cases = [(0x12345678, 0xABCDEF01, state, menu) for state in edges for menu in edges]
        rng = random.Random(0xA828F0)
        cases += [tuple(rng.getrandbits(32) for _ in range(4)) for _ in range(2048)]
        expected = []
        for initial_state, initial_menu, state, menu in cases:
            raw = bytearray(rng.randbytes(0x1920))
            struct.pack_into("<II", raw, 0x1914, initial_state, initial_menu)
            buffer = c.create_string_buffer(bytes(raw), len(raw))
            request(c.addressof(buffer), state, menu)
            after = bytearray(raw)
            struct.pack_into("<II", after, 0x1914, state, menu)
            if bytes(buffer) != bytes(after):
                raise AssertionError("request mutated bytes outside the two u32 fields")
            result = list(struct.unpack_from("<II", buffer, 0x1914))
            clear(c.addressof(buffer))
            struct.pack_into("<II", after, 0x1914, 6, 6)
            if bytes(buffer) != bytes(after):
                raise AssertionError("clear mutated bytes outside the two u32 fields")
            result += struct.unpack_from("<II", buffer, 0x1914)
            expected.append(tuple(result))
        payload = "".join(" ".join(map(str, case)) + "\n" for case in cases)
        result = subprocess.run([str(args.probe.resolve())], input=payload, text=True,
                                capture_output=True, check=True, timeout=60)
        actual = [tuple(map(int, row.split())) for row in result.stdout.splitlines()]
        if actual != expected:
            raise AssertionError("generated production request/clear differs from original")
        write_json(args.output, dict(status="PASS", cases=len(cases),
            whole_original_bodies=bodies, original_elf_sha256=original.sha256,
            accepted_instruction_inputs=sources, full_observed_buffer_bytes=0x1920,
            scope="Two whole writer bodies; explicit raw buffers and all u32 bit domains. No game update timing, original constructor or GUI."))
        print(f"generated UI request/clear: {len(cases)} cases, 2 unchanged whole bodies, all buffer bytes")
        return 0
    finally:
        memory.close()


if __name__ == "__main__":
    raise SystemExit(main())
