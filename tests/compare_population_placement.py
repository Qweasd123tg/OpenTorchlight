#!/usr/bin/env python3
"""Native comparison for ordinary population placement sampling.

Executes the UNCHANGED original placement-sampling prefix piece by piece:
volatile radius/angle draws (UTILITIES::randomBetweenVolatile @0xC92B50 on the
real g_RandVolatile stream) plus MATH::rotateY @0xC7A400 (single sincosf call
redirected at real libc), composed exactly as CLevel::randomOpenPositionRange
@0x945770 does. Compares candidate (x, y, z) bits plus volatile RNG state
against the portable probe.

This covers the sampling mechanics only: draw order/values, single-precision
degrees-to-radians, sincosf order, candidate assembly. The surrounding map-test
loop is control flow verified under GDB against the pinned ELF, not executed
here (it needs live level structures). Section rects, no-spawn regions,
facing, formations and spawn nodes are NOT covered.
Run under a PIE Python host: fixed original pages must not collide with it.
"""
from __future__ import annotations
import argparse
import ctypes as c
import ctypes.util
import platform
import random
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from compare_ai_cooldown import bits, f32

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from original import Original
from compare_original_random import OriginalRandom

RANGE_ADDRESS = 0x945770
ROTATE_ADDRESS = 0xC7A400
ROTATE_SIZE = 0x59
VOLATILE_BETWEEN = 0xC92B50


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--probe", type=Path, required=True)
    args = parser.parse_args()
    if platform.system() != "Linux" or platform.machine() not in ("x86_64", "AMD64"):
        print("SKIP: native isolated functions require Linux x86-64")
        return 77
    original = Original(args.original)
    volatile_symbol = original.symbol("UTILITIES::randomBetweenVolatile(float, float)")
    if volatile_symbol.address != VOLATILE_BETWEEN:
        raise ValueError("Original volatile RNG layout changed")
    rotate = original.symbol("MATH::rotateY(Ogre::Vector3*, float)")
    if (rotate.address, rotate.size) != (ROTATE_ADDRESS, ROTATE_SIZE):
        raise ValueError("Original rotateY layout changed")
    if original.symbol("CLevel::randomOpenPositionRange(Ogre::Vector3 const&, float, float, bool)").address != RANGE_ADDRESS:
        raise ValueError("Original randomOpenPositionRange layout changed")

    old = OriginalRandom(original)
    libc = old.libc
    extra = []
    try:
        # 0xFA4000/0xFA8000/0xFC8000 are already mapped by OriginalRandom;
        # only borrow 0xFA8000 briefly to add one more constant byte.
        if libc.mprotect(0xFA8000, 4096, 3) != 0:
            raise OSError(c.get_errno(), "mprotect RW for constants")
        c.memmove(0xFA86D0, original.read(0xFA86D0, 4), 4)
        if libc.mprotect(0xFA8000, 4096, 1) != 0:
            raise OSError(c.get_errno(), "mprotect RO for constants")
        for address in (0xC7A000, 0x553000):
            result = libc.mmap(address, 4096, 3, 0x100000 | 0x20 | 0x02, -1, 0)
            if result == c.c_void_p(-1).value:
                raise OSError(c.get_errno(), "MAP_FIXED_NOREPLACE; use PIE Python")
            if result != address:
                libc.munmap(result, 4096)
                raise RuntimeError("kernel ignored no-replace fixed mapping")
            extra.append(address)
        c.memmove(ROTATE_ADDRESS, original.read(ROTATE_ADDRESS, ROTATE_SIZE), ROTATE_SIZE)
        libm = c.CDLL(ctypes.util.find_library("m"))
        target = c.cast(libm.sincosf, c.c_void_p).value
        stub = b"\x48\xb8" + struct.pack("<Q", target) + b"\xff\xe0"
        c.memmove(0x553118, stub, len(stub))
        for address, protection in ((0xC7A000, 5), (0x553000, 5)):
            if libc.mprotect(address, 4096, protection) != 0:
                raise OSError(c.get_errno(), "mprotect")
        # Native prefix of one scan attempt, composed from executed originals:
        # volatile radius/angle draws + native rotateY. The map-test loop
        # around it is control flow verified under GDB, not executed here.
        volatile_between = c.CFUNCTYPE(c.c_float, c.c_float, c.c_float)(VOLATILE_BETWEEN)
        rotate_y = c.CFUNCTYPE(None, c.c_void_p, c.c_float)(ROTATE_ADDRESS)
        vec = c.create_string_buffer(12)
        pi180 = struct.unpack("<f", original.read(0xFCE49C, 4))[0]
        center = c.create_string_buffer(12)
        rng = random.Random(RANGE_ADDRESS)
        cases = []
        for seed in (1, 17, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF):
            cases.append((seed, 0.0, 27.5, 0.0, 0.0, 3.0))
        for _ in range(3000):
            seed = rng.randrange(1, 2**32)
            cx = f32(rng.uniform(-500, 500))
            cz = f32(rng.uniform(-500, 500))
            span = rng.choice([(0.0, 3.0), (0.0, 3.0), (0.0, 0.0), (5.0, 5.0), (1.0, 2.0)])
            cases.append((seed, cx, 27.5, cz, span[0], span[1]))
        expected, inputs = [], []
        for seed, cx, cy, cz, minr, maxr in cases:
            struct.pack_into("<fff", center, 0, cx, cy, cz)
            # Volatile stream: the placement sampler consumes g_RandVolatile
            # @0x14ECAF8, not the main RNG. Seed/read it directly.
            c.memmove(0x14ECAF8, struct.pack("<Q", seed), 8)
            radius = volatile_between(minr, maxr)
            degrees = volatile_between(0.0, 360.0)
            angle = f32(degrees * pi180)
            struct.pack_into("<fff", vec, 0, 0.0, 0.0, radius)
            rotate_y(c.addressof(vec), angle)
            dx, _, dz = struct.unpack_from("<fff", vec, 0)
            x = f32(cx + dx)
            z = f32(cz + dz)
            state = c.c_uint64.from_address(0x14ECAF8).value
            expected.append((bits(x), bits(cy), bits(z), state))
            inputs.append(f"o {seed} {bits(cx)} {bits(cy)} {bits(cz)} {bits(minr)} {bits(maxr)}\n")
        result = subprocess.run([str(args.probe)], input="".join(inputs), text=True,
                                capture_output=True, check=True, timeout=120)
        actual = [tuple(map(int, line.split())) for line in result.stdout.splitlines()]
        if actual != expected:
            first = next((i for i, pair in enumerate(zip(actual, expected)) if pair[0] != pair[1]), None)
            raise ValueError(
                f"placement native mismatch at {first}: "
                + str((cases[first], actual[first], expected[first]) if first is not None else "count"))
        print(f"PASS: population placement {len(expected)} polar picks AND RNG states; pick only, NOT regions/sections")
        return 0
    finally:
        for address in reversed(extra):
            libc.munmap(address, 4096)
        old.close()


if __name__ == "__main__":
    raise SystemExit(main())
