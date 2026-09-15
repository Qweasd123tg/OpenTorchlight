#!/usr/bin/env python3
"""Compare two isolated, unchanged x86-64 slices with the portable scalar timer.

Default input: bytes decoded from pinned targeted ASM exports, NOT the ELF.
--original instead reads and SHA-checks the external ELF without modifying it.
Only scalar subtraction/rearming is executed, not attackAI, updateAI, OGRE or a game.
The synthetic ABI wrapper preserves RBX. No game calls/constants are substituted.
"""
from __future__ import annotations

import argparse
import ctypes
import hashlib
import itertools
import mmap
import platform
import random
import re
import struct
import subprocess
from pathlib import Path

from verify_original_entry_dispatch import ELF_SHA256, virtual_bytes

SLICES = (
    ('8dfd80-ai-cooldown.asm', 0x8E00E6, 0x8E013D,
     '6624c2dd8aaa7d0e6d5924dece5d0bfb27330ad5a721ce8ceee630db82077717'),
    ('8e3a40-ai-cooldown-tick.asm', 0x8E3A5B, 0x8E3A6F,
     '0ab42a682cf76ea1fb7c71e277af01786834f87498db043bedd948a58ba4509e'),
)


def bits(value: float) -> int:
    return struct.unpack('<I', struct.pack('<f', value))[0]


def f32(value: float) -> float:
    return struct.unpack('<f', struct.pack('<f', value))[0]


def asm_bytes(path: Path, start: int, end: int) -> bytes:
    result = bytearray()
    expected_address = start
    for line in path.read_text(encoding='utf-8').splitlines():
        match = re.match(r'^\s*([0-9a-f]+):\s*((?:[0-9a-f]{2}\s+)+)', line)
        if not match:
            continue
        address = int(match[1], 16)
        if start <= address < end:
            if address != expected_address:
                raise ValueError(f'Non-contiguous slice at 0x{address:x} in {path}')
            raw = bytes.fromhex(match[2])
            result += raw
            expected_address += len(raw)
    if expected_address != end:
        raise ValueError(f'Missing bytes at 0x{expected_address:x} in {path}')
    return bytes(result)


class Executable:
    def __init__(self, code: bytes) -> None:
        self.memory = mmap.mmap(-1, len(code), prot=mmap.PROT_READ | mmap.PROT_WRITE)
        self.memory.write(code)
        self.address = ctypes.addressof(ctypes.c_char.from_buffer(self.memory))
        libc = ctypes.CDLL(None, use_errno=True)
        protect = libc.mprotect
        protect.argtypes = (ctypes.c_void_p, ctypes.c_size_t, ctypes.c_int)
        protect.restype = ctypes.c_int
        if protect(self.address, len(code), mmap.PROT_READ | mmap.PROT_EXEC) != 0:
            self.memory.close()
            raise OSError(ctypes.get_errno(), 'mprotect executable scalar slice')

    def close(self) -> None:
        self.memory.close()


def compare(probe: Path, start_code: bytes, update_code: bytes) -> int:
    # Synthetic ABI adapter: push rbx; mov rbx,rdi; [unchanged slice]; pop rbx; ret.
    start = Executable(bytes.fromhex('53 48 89 fb') + start_code + bytes.fromhex('5b c3'))
    update = Executable(update_code + b'\xc3')
    try:
        arm = ctypes.CFUNCTYPE(None, ctypes.c_void_p)(start.address)
        tick = ctypes.CFUNCTYPE(None, ctypes.c_void_p, ctypes.c_float)(update.address)
        monster = ctypes.create_string_buffer(0x900)
        weapon = ctypes.create_string_buffer(0x420)
        remaining_field = ctypes.c_float.from_buffer(monster, 0x7E8)
        unit_field = ctypes.c_float.from_buffer(monster, 0x7EC)
        weapon_field = ctypes.c_float.from_buffer(weapon, 0x408)
        weapon_pointer = ctypes.c_void_p.from_buffer(monster, 0x498)

        # Normal finite float32 inputs, plus signed zero and exact boundaries.
        values = [-1000., -2., -1., -0.5, -0.0, 0.0, 0.0625, 0.5, 1., 2., 1000.]
        cases = [(1, a, b, c, has) for a, b, c, has in
                 itertools.product(values, values, values, (0, 1))]
        cases += [(0, a, b, 0., 0) for a, b in itertools.product(
            values, [0., 0.0625, 0.1, 0.5, 1., 2., 10.])]
        rng = random.Random(0x8DFD80)
        for _ in range(20000):
            cases.append((1, f32(rng.uniform(-1000, 1000)), f32(rng.uniform(-10, 10)),
                          f32(rng.uniform(-10, 10)), rng.randrange(2)))
            cases.append((0, f32(rng.uniform(-1000, 1000)), f32(rng.uniform(0, 10)), 0., 0))
        expected: list[int] = []
        inputs: list[str] = []
        for operation, remaining, unit_or_dt, equipment, has_equipment in cases:
            remaining_field.value = remaining
            if operation == 0:
                tick(ctypes.addressof(monster), unit_or_dt)
            else:
                unit_field.value = unit_or_dt
                weapon_field.value = equipment
                weapon_pointer.value = ctypes.addressof(weapon) if has_equipment else None
                arm(ctypes.addressof(monster))
            expected.append(bits(remaining_field.value))
            inputs.append(f'{operation} {bits(remaining)} {bits(unit_or_dt)} '
                          f'{bits(equipment)} {has_equipment}\n')
        result = subprocess.run([str(probe.resolve())], input=''.join(inputs),
                                text=True, capture_output=True, timeout=30, check=True)
        actual = [int(line) for line in result.stdout.splitlines()]
        if len(actual) != len(expected):
            raise ValueError(f'Probe returned {len(actual)} results, expected {len(expected)}')
        for index, (left, right) in enumerate(zip(expected, actual)):
            if left != right:
                raise ValueError(f'Case {index}, {cases[index]}: original slice=0x{left:08x}, '
                                 f'portable=0x{right:08x}')
        return len(cases)
    finally:
        update.close()
        start.close()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    source = parser.add_mutually_exclusive_group()
    source.add_argument('--original', type=Path)
    source.add_argument('--disassembly-dir', type=Path,
                        default=Path(__file__).resolve().parents[1] / 'research/disassembly')
    parser.add_argument('--probe', required=True, type=Path)
    args = parser.parse_args()
    if platform.system() != 'Linux' or platform.machine() not in ('x86_64', 'AMD64'):
        print('SKIP: unchanged instruction slices require Linux x86-64')
        return 77
    try:
        image = args.original.read_bytes() if args.original else None
        if image is not None:
            actual_hash = hashlib.sha256(image).hexdigest()
            if actual_hash != ELF_SHA256:
                raise ValueError(f'Original ELF SHA-256 mismatch: {actual_hash}')
            # Both producers reference the same UTF-32 resource key.
            key = 'AI_ATTACKCOOLDOWN\0'.encode('utf-32-le')
            if virtual_bytes(image, 0xFCF8A0, len(key)) != key:
                raise ValueError('Original shared cooldown resource key mismatch')
        code = []
        for name, low, high, digest in SLICES:
            raw = (virtual_bytes(image, low, high - low) if image is not None else
                   asm_bytes(args.disassembly_dir / name, low, high))
            if hashlib.sha256(raw).hexdigest() != digest:
                raise ValueError(f'Instruction-slice SHA-256 mismatch: {name}')
            code.append(raw)
        count = compare(args.probe, code[0], code[1])
    except (OSError, ValueError, struct.error, subprocess.SubprocessError) as error:
        if isinstance(error, subprocess.CalledProcessError) and error.stderr:
            print(error.stderr, end='')
        parser.exit(1, f'FAIL: {error}\n')
    source_name = 'SHA-checked ELF slices' if image is not None else 'pinned ASM-export slices (ELF not loaded)'
    print(f'PASS: {count} bit-exact float32 comparisons against {source_name}')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
