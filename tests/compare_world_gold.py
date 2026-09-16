#!/usr/bin/env python3
"""Bounded CItemGold arithmetic comparison; NOT a whole-game or RNG parity test.
Executes unchanged targeted-export bytes (or SHA-checked ELF with --original).
Only a stack-alignment adapter and native libm ceilf replace the surrounding ABI.
"""
from __future__ import annotations
import argparse
import ctypes
import ctypes.util
import hashlib
import itertools
import platform
import random
import struct
import subprocess
from pathlib import Path
from compare_ai_cooldown import Executable, asm_bytes, bits, f32
from verify_original_entry_dispatch import ELF_SHA256, virtual_bytes

ROOT = Path(__file__).resolve().parents[1]
START, END = 0x8cad46, 0x8cad5b
DIGEST = '0fb86d029081f0308759b77f54b993715cd42b05c10d675fb5c5a80ad8d8fc21'


def compare(probe: Path, image: bytes | None) -> int:
    raw = (virtual_bytes(image, START, END-START) if image is not None else
           asm_bytes(ROOT/'research/disassembly/8ca940-gold-unit-init.asm', START, END))
    if hashlib.sha256(raw).hexdigest() != DIGEST:
        raise ValueError('gold scalar export digest mismatch')
    low = 0x550000
    window = bytearray(0xfa4900-low)
    def write(address: int, data: bytes) -> None:
        offset = address-low
        if offset < 0 or offset+len(data) > len(window):
            raise ValueError('gold sparse-map bounds')
        window[offset:offset+len(data)] = data
    write(START, raw)
    write(END, bytes.fromhex('5d c3'))  # restore wrapper push rbp; return
    write(0xfa483c, struct.pack('<f', 100))
    libm = ctypes.CDLL(ctypes.util.find_library('m'))
    address = ctypes.cast(libm.ceilf, ctypes.c_void_p).value
    write(0x553678, b'\x48\xb8'+struct.pack('<Q', address)+b'\xff\xe0')
    executable = Executable(bytes(window))
    wrapper = None
    try:
        # CFUNCTYPE supplies graph in xmm0, percent in xmm1. The original
        # scalar's call instruction expects rsp%16 == 0 before calling ceilf.
        wrapper = Executable(b'\x55\x48\xb8'+struct.pack('<Q', executable.address+START-low)+b'\xff\xe0')
        fn = ctypes.CFUNCTYPE(ctypes.c_int32, ctypes.c_float, ctypes.c_float)(wrapper.address)
        rng = random.Random(START)
        cases = list(itertools.product([0., .01, .1, .99999, 1., 1.00001, 19.2, 16777216., 100000000.],
                                      [0., .01, .1, 1., 12.5, 33.3, 99.999, 100., 125., 200.]))
        cases += [(f32(rng.uniform(0, 1000000)), f32(rng.uniform(0, 1000))) for _ in range(10000)]
        # Explicit ULP neighbours at ceil boundaries and near int32's valid edge.
        for target in [1., 10., 100., 1000., 16777216., 2147483520.]:
            for delta in [-1, 0, 1]:
                x = struct.unpack('<f', struct.pack('<I', bits(target)+delta))[0]
                if x < 2147483648.:
                    cases.append((x, 100.))
        expected = [fn(f32(x), f32(y)) for x, y in cases]
        if min(expected) < 0:
            raise ValueError('comparison accidentally entered invalid conversion domain')
        requests = ''.join(f'{bits(x)} {bits(y)}\n' for x, y in cases)
        result = subprocess.run([str(probe.resolve())], input=requests, text=True,
                                capture_output=True, check=True, timeout=30)
        actual = [int(line) for line in result.stdout.splitlines()]
        if len(actual) != len(expected):
            raise ValueError('wrong gold probe result count')
        for i, (a,b) in enumerate(zip(actual, expected)):
            if a != b:
                raise ValueError(f'case {i}: {cases[i]}, portable={a}, original scalar={b}')
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
        print(f'PASS: {count} gold scalar cases; unchanged instructions; native ceilf dependency; '+
              ('SHA-checked ELF' if image is not None else 'targeted exports, NOT original asset/runtime validation'))
        return 0
    except (ValueError, OSError, subprocess.SubprocessError) as error:
        parser.exit(1, f'FAIL: {error}\n')

if __name__ == '__main__':
    raise SystemExit(main())
