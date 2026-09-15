#!/usr/bin/env python3
"""Verify the three property-node dispatch entries missing from text-only ASM.

The ELF is read-only and must be the version recorded in AGENTS/research.
This is a static data check, not an execution of loadRoomLayout or the game.
"""
from __future__ import annotations

import argparse
import hashlib
import struct
from pathlib import Path

ELF_SHA256 = "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"
TABLE_ADDRESS = 0xFD6AD0
EXPECTED = {1: 0x960AD8, 4: 0x9609C0, 5: 0x960910}


def virtual_bytes(image: bytes, address: int, count: int) -> bytes:
    if len(image) < 64 or image[:6] != b"\x7fELF\x02\x01":
        raise ValueError("Expected a little-endian ELF64 file")
    if struct.unpack_from("<H", image, 18)[0] != 62:
        raise ValueError("Expected ELF machine x86-64")
    phoff = struct.unpack_from("<Q", image, 32)[0]
    phsize, phcount = struct.unpack_from("<HH", image, 54)
    if phsize < 56 or phoff + phsize * phcount > len(image):
        raise ValueError("Invalid ELF program-header table")
    for index in range(phcount):
        fields = struct.unpack_from("<IIQQQQQQ", image, phoff + index * phsize)
        kind, _, offset, virtual, _, filesz, _, _ = fields
        if kind != 1 or address < virtual or address + count > virtual + filesz:
            continue
        start = offset + address - virtual
        if start + count > len(image):
            raise ValueError("ELF load segment extends past the file")
        return image[start : start + count]
    raise ValueError(f"No file-backed ELF segment covers 0x{address:x}")


def verify_dispatch(image: bytes) -> None:
    for node_type, expected in EXPECTED.items():
        actual = struct.unpack("<Q", virtual_bytes(image, TABLE_ADDRESS + 8 * node_type, 8))[0]
        if actual != expected:
            raise ValueError(
                f"TYPE {node_type}: jump-table target 0x{actual:x}, expected 0x{expected:x}; "
                "recheck the inferred property-node mapping before relying on the fallback"
            )


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original", type=Path, required=True)
    args = parser.parse_args()
    try:
        image = args.original.read_bytes()
        actual_hash = hashlib.sha256(image).hexdigest()
        if actual_hash != ELF_SHA256:
            raise ValueError(f"Original ELF SHA-256 mismatch: {actual_hash}")
        verify_dispatch(image)
    except (OSError, ValueError, struct.error) as error:
        parser.exit(1, f"FAIL: {error}\n")
    print("PASS: original Player Start / Entrance / Exit jump-table entries match")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
