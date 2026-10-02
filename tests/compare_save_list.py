#!/usr/bin/env python3
"""Compare the two unchanged original canLoad bodies with the production query.

Explicit synthetic UI, manager and Continue buffers own the pointer chain.
Filename-vector bounds +0x218/+0x220 deliberately differ from save-state-vector
bounds +0x1e8/+0x1f0. Only bounds are read: large counts require no huge allocation.
All owner and marker-buffer bytes are observed after both original calls.
Constructors, filename contents, SVB/OTC parsing and original game are not run.
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

ENTRIES = ((0xA84D20, 12), (0xC2B700, 31))
U64_MASK = (1 << 64) - 1
MAX_COUNT = ((1 << 63) - 1) // 8


def vector_bounds(buffer, offset, marker, count):
    if not isinstance(count, int) or not 0 <= count <= MAX_COUNT:
        raise ValueError("fixture count exceeds nonnegative signed64 pointer-delta domain")
    begin = c.addressof(marker)
    delta = count * 8
    end = begin + delta
    if delta > (1 << 63) - 1 or end > U64_MASK:
        raise ValueError("fixture pointer addition would overflow uint64")
    struct.pack_into("<QQ", buffer, offset, begin, end & U64_MASK)


def compare_case(runs, count, save_count, rng):
    ui = c.create_string_buffer(rng.randbytes(0x590), 0x590)
    manager = c.create_string_buffer(rng.randbytes(0xDF0), 0xDF0)
    menu = c.create_string_buffer(rng.randbytes(0x248), 0x248)
    filename_marker = c.create_string_buffer(rng.randbytes(8), 8)
    save_marker = c.create_string_buffer(rng.randbytes(8), 8)
    vector_bounds(menu, 0x218, filename_marker, count)
    vector_bounds(menu, 0x1E8, save_marker, save_count)
    struct.pack_into("<Q", manager, 0xDE8, c.addressof(menu))
    struct.pack_into("<Q", ui, 0x588, c.addressof(manager))
    buffers = (ui, manager, menu, filename_marker, save_marker)
    before = tuple(bytes(buffer) for buffer in buffers)
    values = []
    for run, owner in zip(runs, (ui, manager)):
        values.append(int(run(c.addressof(owner))))
        if tuple(bytes(buffer) for buffer in buffers) != before:
            raise AssertionError(f"original canLoad mutated fixture state: count={count}")
    if values[0] != values[1]:
        raise AssertionError(f"original UI/manager disagree: count={count}, results={values}")
    # SETG consumes signed low32 after the original SAR64, not size_t != 0.
    low = count & 0xFFFFFFFF
    arithmetic = int(0 < low < 0x80000000)
    if values[0] != arithmetic:
        raise AssertionError(f"original signed-low32 result differs: count={count}")
    return values[0]


def cases():
    counts = list(range(257))
    anchors = (0, 1, 4, 5, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF,
               1 << 32, (1 << 32) + 1, (1 << 33) - 1,
               MAX_COUNT - 1, MAX_COUNT)
    counts += [anchor + delta for anchor in anchors for delta in range(-4, 5)
               if 0 <= anchor + delta <= MAX_COUNT]
    rng = random.Random(0xC2B700)
    for index in range(1024):
        counts.append(rng.getrandbits(32 if index % 2 else 60))
    for count in dict.fromkeys(counts):
        # Both variants differ from filename_count. A zero/nonzero save-state
        # toggle catches accidental reuse of canContinue's vector mapping.
        for save_count in ((1, 7) if count == 0 else (0, 7 if count != 7 else 9)):
            yield count, save_count


def accepted_sources(original):
    sources = []
    for address, size in ENTRIES:
        path = ROOT / "research/lifted-ui" / f"{address:08x}.json"
        data = json.loads(path.read_text())
        if data["original_elf_sha256"] != original.sha256 or int(data["address"], 16) != address:
            raise ValueError(f"accepted p-code original identity differs: {path}")
        body = original.read(address, size)
        if (data["original_symbol_size"] != size or
                data["original_symbol_body_sha256"] != hashlib.sha256(body).hexdigest()):
            raise ValueError(f"accepted whole original body differs: {address:#x}")
        for row in data["instructions"]:
            raw = bytes.fromhex(row["bytes"])
            if original.read(int(row["address"], 16), len(raw)) != raw:
                raise ValueError(f"accepted original instruction differs: {row['address']}")
        sources.append(dict(path=str(path.relative_to(ROOT)),
                            sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
    return sources


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
    sources = accepted_sources(original)
    memory = Memory()
    bodies = []
    try:
        for entry, size in ENTRIES:
            symbol = next(s for s in original.symbols if s.address == entry and s.size)
            if symbol.size != size:
                raise ValueError(f"unexpected original body size at {entry:#x}: {symbol.size}")
            body = original.read(entry, size)
            memory.put(entry, body)
            bodies.append(dict(address=hex(entry), symbol=symbol.name, size=size,
                               sha256=hashlib.sha256(body).hexdigest()))
        memory.protect()
        runs = tuple(c.CFUNCTYPE(c.c_bool, c.c_void_p)(entry) for entry, _ in ENTRIES)
        fixtures = list(cases())
        rng = random.Random(0xA84D20)
        expected = [compare_case(runs, count, save_count, rng)
                    for count, save_count in fixtures]
        payload = "".join(f"{count}\n" for count, _ in fixtures)
        result = subprocess.run([str(args.probe.resolve())], input=payload, text=True,
                                capture_output=True, check=True, timeout=45)
        actual = [int(line) for line in result.stdout.splitlines()]
        if len(actual) != len(expected) or actual != expected:
            bad = next((i for i, (got, want) in enumerate(zip(actual, expected))
                        if got != want), None)
            raise AssertionError(f"production canLoad differs at {bad}: "
                                 f"{fixtures[bad] if bad is not None else 'result count'}")
        write_json(args.output, dict(schema=1, kind="original-save-list-comparison",
            status="PASS", original_elf_sha256=original.sha256, bodies=bodies,
            accepted_instruction_inputs=sources, cases=len(fixtures),
            distinct_filename_counts=len({count for count, _ in fixtures}),
            full_observed_buffer_bytes=0x590 + 0xDF0 + 0x248 + 16,
            filename_vector_offsets=["0x218", "0x220"],
            deliberately_distinct_save_vector_offsets=["0x1e8", "0x1f0"],
            scope=__doc__, game_executed=False, original_status_promotions=0))
        print(f"PASS save-list canLoad: {len(fixtures)} cases, two unchanged whole bodies, all fixture bytes")
        return 0
    finally:
        memory.close()


if __name__ == "__main__":
    raise SystemExit(main())
