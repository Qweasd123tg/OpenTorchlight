#!/usr/bin/env python3
"""Bounded CCharacter::setLevel XP scalar comparison; NOT a whole-game or RNG test.
Executes the unchanged targeted-export bytes (or SHA-checked ELF with --original).
Only a stack-alignment adapter is needed; the scalar has no external call.
"""
from __future__ import annotations
import argparse
import ctypes
import hashlib
import platform
import random
import struct
import subprocess
from pathlib import Path
from compare_ai_cooldown import Executable, asm_bytes, bits, f32
from verify_original_entry_dispatch import ELF_SHA256, virtual_bytes

ROOT = Path(__file__).resolve().parents[1]
START, END = 0x83ecea, 0x83ecfd
DIGEST = '9aa637a7d502a86db7be6307a21f2cb588a72d00f70589f62c297e308f782c35'
# trunc((g/100)*g) stays nonnegative and inside int32 for g <= sqrt(int32_max*100).
MAX_GRAPH = 463408.0


def compare(probe: Path, image: bytes | None) -> int:
    raw = (virtual_bytes(image, START, END-START) if image is not None else
           asm_bytes(ROOT/'research/disassembly/83ead0-character-set-level-xp.asm', START, END))
    if hashlib.sha256(raw).hexdigest() != DIGEST:
        raise ValueError('monster XP scalar export digest mismatch')
    low = 0x550000
    window = bytearray(0xfa4900-low)
    def write(address: int, data: bytes) -> None:
        offset = address-low
        if offset < 0 or offset+len(data) > len(window):
            raise ValueError('monster XP sparse-map bounds')
        window[offset:offset+len(data)] = data
    write(START, raw)
    write(END, bytes.fromhex('5d c3'))  # restore wrapper push rbp; return
    write(0xfa483c, struct.pack('<f', 100))
    executable = Executable(bytes(window))
    wrapper = None
    try:
        # CFUNCTYPE supplies the graph value in xmm0; the scalar returns eax.
        wrapper = Executable(b'\x55\x48\xb8'+struct.pack('<Q', executable.address+START-low)+b'\xff\xe0')
        fn = ctypes.CFUNCTYPE(ctypes.c_int32, ctypes.c_float)(wrapper.address)
        rng = random.Random(START)
        grid = [0., 0.01, 0.1, 1., 10., 100., 110., 150., 200.9, 300.9, 1000.,
                65535., 463407.9, MAX_GRAPH]
        cases = [(value,) for value in grid]
        cases += [(f32(rng.uniform(0, MAX_GRAPH)),) for _ in range(20000)]
        # Explicit ULP neighbours around truncation boundaries and the valid edge.
        for target in [1., 100., 1000., 65536., 262144., MAX_GRAPH]:
            for delta in [-1, 0, 1]:
                x = struct.unpack('<f', struct.pack('<I', bits(target)+delta))[0]
                if 0 <= x <= MAX_GRAPH:
                    cases.append((x,))
        expected = [fn(f32(x)) for (x,) in cases]
        if min(expected) < 0:
            raise ValueError('comparison accidentally entered invalid conversion domain')
        requests = ''.join(f'{bits(x)}\n' for (x,) in cases)
        result = subprocess.run([str(probe.resolve())], input=requests, text=True,
                                capture_output=True, check=True, timeout=30)
        actual = [int(line) for line in result.stdout.splitlines()]
        if len(actual) != len(expected):
            raise ValueError('wrong monster XP probe result count')
        for i, (a, b) in enumerate(zip(actual, expected)):
            if a != b:
                raise ValueError(f'case {i}: g={cases[i][0]!r}, portable={a}, original scalar={b}')
        return len(cases)
    finally:
        if wrapper:
            wrapper.close()
        executable.close()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--probe', required=True, type=Path)
    parser.add_argument('--original', type=Path)
    args = parser.parse_args()
    if platform.system() != 'Linux' or platform.machine() not in ('x86_64', 'AMD64'):
        print('SKIP: bounded instruction adapter requires Linux x86-64')
        return 77
    try:
        image = args.original.read_bytes() if args.original else None
        if image is not None:
            if hashlib.sha256(image).hexdigest() != ELF_SHA256:
                raise ValueError('ELF SHA mismatch')
            if virtual_bytes(image, 0xfa483c, 4) != struct.pack('<f', 100):
                raise ValueError('ELF percentage divisor mismatch')
        count = compare(args.probe, image)
        print(f'PASS: {count} monster XP scalar cases; unchanged instructions; '+
              ('SHA-checked ELF' if image is not None else 'targeted exports, NOT original asset/runtime validation'))
        return 0
    except (ValueError, OSError, subprocess.SubprocessError) as error:
        parser.exit(1, f'FAIL: {error}\n')

if __name__ == '__main__':
    raise SystemExit(main())
