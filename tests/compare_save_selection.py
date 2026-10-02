#!/usr/bin/env python3
"""Compare three unchanged original Continue queries with the production selector.

Synthetic raw save records, vector bounds and the two manager pointers are
explicit fixture state. There are no callbacks, constructors or original game
process. Nonfinite health bits calibrate raw code only: OTC SaveStore validation
need not accept them as checkpoint input. The OTC unreadable-row guard is an
additional portable input boundary and is not attributed to the original.
"""
import argparse
import ctypes as c
import hashlib
from pathlib import Path
import platform
import random
import struct
import subprocess
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from automation_state import validate_output, write_json
from original import Original
from native_typed_reference import Memory

ENTRIES = ((0xC33490, 67), (0xC2B9C0, 12), (0xA84D30, 12))
ZERO = 0xFA47F8


def compare_case(runs, health, selected):
    menu = c.create_string_buffer(0x200)
    manager = c.create_string_buffer(0xDF0)
    ui = c.create_string_buffer(0x590)
    saves = [c.create_string_buffer(0xE8) for _ in health]
    pointers = (c.c_size_t * max(len(saves), 1))()
    for index, (save, bits) in enumerate(zip(saves, health)):
        struct.pack_into("<I", save, 0xE0, bits)
        pointers[index] = c.addressof(save)
    begin = c.addressof(pointers)
    struct.pack_into("<QQ", menu, 0x1E8, begin, begin + 8 * len(saves))
    struct.pack_into("<i", menu, 0xC8, selected)
    struct.pack_into("<Q", manager, 0xDE8, c.addressof(menu))
    struct.pack_into("<Q", ui, 0x588, c.addressof(manager))
    values = [run(c.addressof(obj)) for run, obj in zip(runs, (menu, manager, ui))]
    if len(set(values)) != 1:
        raise AssertionError(f"original wrappers disagree: {values}; count={len(health)} selected={selected}")
    return int(values[0])


def cases():
    # Covers strict >0, IEEE unordered, signed zero, positive subnormal,
    # nonselected live records and the first/past-last vector positions.
    edges = [0x00000000, 0x80000000, 0x00000001, 0x80000001,
             0x3F800000, 0xBF800000, 0x7F7FFFFF, 0xFF7FFFFF,
             0x7F800000, 0xFF800000, 0x7FC00001, 0xFFC00001]
    for value in edges:
        yield [value], 0
    for count in (0, 1, 2, 3, 7, 32, 128):
        raw = [0] * count
        if count > 1:
            raw[-1] = 0x40000000
        for selected in {0, max(count - 1, 0), count, count + 3}:
            yield raw, selected
    rng = random.Random(0xC33490)
    for _ in range(2400):
        count = rng.randrange(129)
        raw = [rng.choice(edges) if rng.randrange(3) else rng.getrandbits(32)
               for _ in range(count)]
        selected = rng.choice((0, max(count - 1, 0), count, count + 1,
                               rng.randrange(count + 2)))
        yield raw, selected


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--probe", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if platform.system() != "Linux" or platform.machine() != "x86_64":
        return 77
    root = Path(__file__).resolve().parents[1]
    validate_output(root, args.output, [args.original, args.probe])
    original = Original(args.original)
    memory = Memory()
    bodies = []
    try:
        for entry, required_size in ENTRIES:
            symbol = next(s for s in original.symbols if s.address == entry and s.size)
            if symbol.size != required_size:
                raise ValueError(f"Unexpected original size at {entry:#x}: {symbol.size}")
            body = original.read(entry, symbol.size)
            memory.put(entry, body)
            bodies.append(dict(address=hex(entry), symbol=symbol.name,
                               size=symbol.size, sha256=hashlib.sha256(body).hexdigest()))
        zero = original.read(ZERO, 4)
        if zero != bytes(4):
            raise ValueError(f"Original zero literal drifted: {zero.hex()}")
        memory.put(ZERO, zero)
        memory.protect()
        runs = tuple(c.CFUNCTYPE(c.c_bool, c.c_void_p)(entry) for entry, _ in ENTRIES)
        fixtures = list(cases())
        expected = [compare_case(runs, raw, selected) for raw, selected in fixtures]
        input_text = "".join(f"{len(raw)} {selected}" +
                             "".join(f" {bits}" for bits in raw) + "\n"
                             for raw, selected in fixtures)
        result = subprocess.run([str(args.probe.resolve())], input=input_text,
                                text=True, capture_output=True, check=True, timeout=45)
        actual = [int(line) for line in result.stdout.splitlines()]
        if len(actual) != len(expected) or actual != expected:
            bad = next((i for i, (got, want) in enumerate(zip(actual, expected))
                        if got != want), None)
            raise AssertionError(f"Continue selector differs at {bad}: "
                                 f"{fixtures[bad] if bad is not None else 'result count'}")
        write_json(args.output, dict(schema=1, kind="original-save-selection-comparison",
                                     status="PASS", original_elf_sha256=original.sha256,
                                     bodies=bodies, zero_literal=dict(address=hex(ZERO), bytes=zero.hex()),
                                     cases=len(fixtures), scope=__doc__, game_executed=False,
                                     original_status_promotions=0))
        print(f"PASS Continue selection: {len(fixtures)} cases, three unchanged original bodies")
        return 0
    finally:
        memory.close()


if __name__ == "__main__":
    raise SystemExit(main())
