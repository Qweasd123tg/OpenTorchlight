#!/usr/bin/env python3
import argparse
import ctypes as c
import math
import os
from pathlib import Path
import random
import struct
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from original import Original


class OriginalRandom:
    def __init__(self, original):
        self.libc = c.CDLL(None, use_errno=True)
        self.libc.mmap.argtypes = [c.c_void_p, c.c_size_t, c.c_int, c.c_int, c.c_int, c.c_long]
        self.libc.mmap.restype = c.c_void_p
        self.libc.mprotect.argtypes = [c.c_void_p, c.c_size_t, c.c_int]
        self.libc.munmap.argtypes = [c.c_void_p, c.c_size_t]
        self.regions = []
        definitions = [
            ("UTILITIES::randomBetween(float, float)", 0xC92A70, 0x97),
            ("UTILITIES::randomIntegerBetween(int, int)", 0xC92B10, 0x3D),
            ("UTILITIES::setSeed(int)", 0xC92C70, 0x33),
            ("UTILITIES::randomBetweenVolatile(float, float)", 0xC92B50, 0x97),
        ]
        for name, address, size in definitions:
            symbol = original.symbol(name)
            if (symbol.address, symbol.size) != (address, size):
                raise ValueError(f"Original function layout changed: {name}")
        try:
            for address in (0x972000, 0xC8A000, 0xC92000, 0x14EC000, 0xFA4000,
                            0xFA8000, 0xFC8000):
                result = self.libc.mmap(address, 4096, 3, 0x100000 | 0x20 | 0x02, -1, 0)
                if result == c.c_void_p(-1).value:
                    error = c.get_errno()
                    raise OSError(error, os.strerror(error))
                if result != address:
                    self.libc.munmap(result, 4096)
                    raise RuntimeError("Kernel did not honor MAP_FIXED_NOREPLACE")
                self.regions.append(address)
            c.memmove(0xC92A70, original.read(0xC92A70, 0x234), 0x234)
            c.memmove(0x972980, original.read(0x972980, 0x1FB), 0x1FB)
            c.memmove(0xC8AA10, original.read(0xC8AA10, 0x100), 0x100)
            c.memmove(0xFA47FC, original.read(0xFA47FC, 0x18), 0x18)
            c.memmove(0xFA86F4, original.read(0xFA86F4, 0x2C), 0x2C)
            c.memmove(0xFC8170, original.read(0xFC8170, 8), 8)
            c.memmove(0xFC89BC, original.read(0xFC89BC, 4), 4)
            self.seed = c.CFUNCTYPE(None, c.c_int32)(0xC92C70)
            self.integer = c.CFUNCTYPE(c.c_int32, c.c_int32, c.c_int32)(0xC92B10)
            self.between = c.CFUNCTYPE(c.c_float, c.c_float, c.c_float)(0xC92A70)
            self.between_volatile = c.CFUNCTYPE(c.c_float, c.c_float, c.c_float)(0xC92B50)
            self.get_random = c.CFUNCTYPE(c.c_int32, c.c_void_p)(0xC8AA10)
            self.intersects = c.CFUNCTYPE(c.c_bool, c.c_void_p, c.c_void_p, c.c_void_p)(
                0x972980
            )
            for address in (0x972000, 0xC8A000, 0xC92000):
                if self.libc.mprotect(address, 4096, 5) != 0:
                    raise OSError(c.get_errno(), os.strerror(c.get_errno()))
            for address in (0xFA4000, 0xFA8000, 0xFC8000):
                if self.libc.mprotect(address, 4096, 1) != 0:
                    raise OSError(c.get_errno(), os.strerror(c.get_errno()))
        except BaseException:
            self.close()
            raise

    def state(self):
        return c.c_uint64.from_address(0x14ECAF0).value

    def seed_volatile_state(self, state):
        # Owned reference image's input state, not setSeedVolatile(0)'s clock.
        c.c_uint64.from_address(0x14ECAF8).value = state

    def volatile_state(self):
        return c.c_uint64.from_address(0x14ECAF8).value

    def weighted_index(self, weights):
        choices = (c.c_int32 * len(weights))(*range(len(weights)))
        odds = (c.c_float * len(weights))(*weights)
        total = c.c_float(0.0)
        for weight in weights:
            total = c.c_float(total.value + c.c_float(weight).value)
        normalized = (c.c_float * len(weights))(
            *(c.c_float(c.c_float(weight).value / total.value).value for weight in weights)
        )
        instance = c.create_string_buffer(0x68)
        struct.pack_into("<QII", instance, 0x10, c.addressof(choices), len(weights), len(weights))
        struct.pack_into("<QII", instance, 0x28, c.addressof(odds), len(weights), len(weights))
        struct.pack_into("<QII", instance, 0x40, c.addressof(normalized), len(weights), len(weights))
        struct.pack_into("<I", instance, 0x58, 0)
        struct.pack_into("<f", instance, 0x5C, 1.0)
        struct.pack_into("<B", instance, 0x60, 0)
        return self.get_random(c.addressof(instance))

    def chunks_intersect(self, tile, width_basis, height_basis,
                         left_width, left_height, left_x, left_y, left_z,
                         right_width, right_height, right_x, right_y, right_z):
        left_type = c.create_string_buffer(0x58)
        right_type = c.create_string_buffer(0x58)
        struct.pack_into("<ii", left_type, 0x14, left_width, left_height)
        struct.pack_into("<ii", right_type, 0x14, right_width, right_height)
        types = (c.c_void_p * 2)(c.addressof(left_type), c.addressof(right_type))
        template = c.create_string_buffer(0x98)
        struct.pack_into("<QII", template, 0x10, c.addressof(types), 2, 2)
        struct.pack_into("<fff", template, 0x88, tile, width_basis, height_basis)
        left = c.create_string_buffer(0x48)
        right = c.create_string_buffer(0x48)
        struct.pack_into("<I", left, 0x10, 0)
        struct.pack_into("<fff", left, 0x20, left_x, left_y, left_z)
        struct.pack_into("<I", right, 0x10, 1)
        struct.pack_into("<fff", right, 0x20, right_x, right_y, right_z)
        existing = (c.c_void_p * 1)(c.addressof(right))
        existing_vector = c.create_string_buffer(24)
        struct.pack_into("<QQQ", existing_vector, 0, c.addressof(existing),
                         c.addressof(existing) + c.sizeof(c.c_void_p),
                         c.addressof(existing) + c.sizeof(c.c_void_p))
        return bool(self.intersects(c.addressof(template), c.addressof(left),
                                    c.addressof(existing_vector)))

    def close(self):
        for address in reversed(self.regions):
            self.libc.munmap(address, 4096)
        self.regions.clear()


class RecoveredRandom:
    def __init__(self, path):
        self.library = c.CDLL(str(path.resolve()))
        self.seed = self.library.recovered_random_seed
        self.seed.restype = c.c_bool
        self.seed.argtypes = [c.c_uint32]
        self.integer = self.library.recovered_random_integer_between
        self.integer.restype = c.c_int32
        self.integer.argtypes = [c.c_int32, c.c_int32]
        self.between = self.library.recovered_random_between
        self.between.restype = c.c_float
        self.between.argtypes = [c.c_float, c.c_float]
        self.weighted_index = self.library.recovered_weighted_index
        self.weighted_index.restype = c.c_size_t
        self.weighted_index.argtypes = [c.POINTER(c.c_float), c.c_size_t]
        self.state = self.library.recovered_random_state
        self.state.restype = c.c_uint64
        self.state.argtypes = []
        self.seed_volatile_state = self.library.recovered_volatile_seed
        self.seed_volatile_state.restype = None
        self.seed_volatile_state.argtypes = [c.c_uint64]
        self.between_volatile = self.library.recovered_volatile_between
        self.between_volatile.restype = c.c_float
        self.between_volatile.argtypes = [c.c_float, c.c_float]
        self.volatile_state = self.library.recovered_volatile_state
        self.volatile_state.restype = c.c_uint64
        self.volatile_state.argtypes = []
        self.ui_channel_gain = self.library.recovered_ui_channel_gain
        self.ui_channel_gain.restype = c.c_float
        self.ui_channel_gain.argtypes = [c.c_float, c.c_float]
        self.chunks_intersect = self.library.recovered_chunks_intersect
        self.chunks_intersect.restype = c.c_bool
        self.chunks_intersect.argtypes = [
            c.c_float, c.c_float, c.c_float,
            c.c_int32, c.c_int32, c.c_float, c.c_float, c.c_float,
            c.c_int32, c.c_int32, c.c_float, c.c_float, c.c_float,
        ]


def float_bits(value):
    return struct.pack("<f", value)


def compare(old, new):
    checks = 0
    generator = random.Random(0x544F524348)
    for seed in (1, 2, 17, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF):
        old.seed(c.c_int32(seed).value)
        assert new.seed(seed)
        for step in range(2000):
            if step % 3:
                low = generator.randrange(-1000000, 1000000)
                high = low + generator.randrange(-10, 100000)
                actual = new.integer(low, high)
                expected = old.integer(low, high)
            else:
                low = c.c_float(generator.uniform(-1000.0, 1000.0)).value
                high = c.c_float(low + generator.uniform(-1.0, 2000.0)).value
                actual = float_bits(new.between(low, high))
                expected = float_bits(old.between(low, high))
            if actual != expected:
                raise AssertionError(
                    f"seed={seed:#x} step={step}: recovered={actual!r}, original={expected!r}")
            if new.state() != old.state():
                raise AssertionError(f"seed={seed:#x} step={step}: generator state differs")
            checks += 2
    weighted_sets = (
        (1.0,),
        (1.0, 1.0),
        (1.0, 3.0, 2.0),
        (0.0, 5.0, 0.0, 1.0),
        (1000.0, 1.0, 7.0, 25.0, 3.0),
    )
    for seed in (1, 17, 0x7FFFFFFF, 0xFFFFFFFF):
        for weights in weighted_sets:
            old.seed(c.c_int32(seed).value)
            assert new.seed(seed)
            new_weights = (c.c_float * len(weights))(*weights)
            for step in range(500):
                actual = new.weighted_index(new_weights, len(weights))
                expected = old.weighted_index(weights)
                if actual != expected:
                    raise AssertionError(
                        f"weighted seed={seed:#x} weights={weights} step={step}: "
                        f"recovered={actual}, original={expected}")
                if new.state() != old.state():
                    raise AssertionError("weighted generator state differs")
                checks += 2
    geometry_cases = [
        (4.0, 25.0, 25.0, 1, 1, 0.0, 0.0, 0.0, 1, 1, 100.0, 0.0, 0.0),
        (4.0, 25.0, 25.0, 1, 1, 0.0, 0.0, 0.0, 1, 1, 99.0, 0.0, 0.0),
        (4.0, 25.0, 25.0, 1, 1, 0.0, 0.0, 0.0, 1, 1, 0.0, 2000.1, 0.0),
        (4.0, 25.0, 25.0, 2, 3, -100.0, 7.0, 200.0,
         3, 2, 99.0, -11.0, 499.0),
    ]
    for _ in range(20000):
        tile = c.c_float(generator.uniform(1.0, 8.0)).value
        width_basis = c.c_float(generator.uniform(10.0, 40.0)).value
        height_basis = c.c_float(generator.uniform(10.0, 40.0)).value
        geometry_cases.append((
            tile, width_basis, height_basis,
            generator.randrange(1, 5), generator.randrange(1, 5),
            *(c.c_float(generator.uniform(-1000.0, 1000.0)).value for _ in range(3)),
            generator.randrange(1, 5), generator.randrange(1, 5),
            *(c.c_float(generator.uniform(-1000.0, 1000.0)).value for _ in range(3)),
        ))
    for case in geometry_cases:
        actual = bool(new.chunks_intersect(*case))
        expected = old.chunks_intersect(*case)
        if actual != expected:
            raise AssertionError(
                f"chunk intersection differs for {case}: recovered={actual}, original={expected}")
        checks += 1
    return checks


def compare_volatile(old, new):
    checks = 0
    generator = random.Random(0x564F4C4154494C45)
    special = ((-2.5, 7.25), (0.0, 1.0), (1.0, -1.0),
               (-0.0, 0.0), (0.0, -0.0), (2.0, 2.0),
               (float("nan"), 1.0), (1.0, float("nan")),
               (float("nan"), float("nan")),
               (float("inf"), float("inf")),
               (-float("inf"), float("inf")), (1.0, float("inf")))
    for seed in (0, 1, 17, 0x7FFFFFFF, 0xFFFFFFFF,
                 0x123456789ABCDEF, 0xFFFFFFFFFFFFFFFF):
        old.seed_volatile_state(seed)
        new.seed_volatile_state(seed)
        for step in range(2000):
            if step < len(special):
                low, high = special[step]
            else:
                low = c.c_float(generator.uniform(-1000.0, 1000.0)).value
                high = c.c_float(generator.uniform(-1000.0, 1000.0)).value
            actual = float_bits(new.between_volatile(low, high))
            expected = float_bits(old.between_volatile(low, high))
            if actual != expected or new.volatile_state() != old.volatile_state():
                raise AssertionError(
                    f"volatile state={seed:#x} step={step} bounds={low},{high}: "
                    f"recovered={actual.hex()}/{new.volatile_state():#x}, "
                    f"original={expected.hex()}/{old.volatile_state():#x}")
            checks += 2
    return checks


def compare_ui_gain(old, new):
    checks = 0
    for seed in (1, 17, 0x12345678, 0xFFFFFFFF):
        old.seed_volatile_state(seed)
        new.seed_volatile_state(seed)
        for step in range(500):
            volume, variation = ((0.2, 0.2), (0.9, 0.2), (0.0, 1.0), (1.0, 0.0))[step % 4]
            volume, variation = c.c_float(volume).value, c.c_float(variation).value
            # Source additive/capped gain contract, driven by original ASM RNG.
            expected = min(c.c_float(volume + old.between_volatile(0.0, variation)).value, 1.0)
            actual = new.ui_channel_gain(volume, variation)
            if float_bits(actual) != float_bits(expected) or new.volatile_state() != old.volatile_state():
                raise AssertionError(f"UI gain seed={seed:#x} step={step}: {actual} != {expected}")
            checks += 2
    return checks


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--original", required=True, type=Path)
    parser.add_argument("--library", required=True, type=Path)
    args = parser.parse_args()
    try:
        old = OriginalRandom(Original(args.original))
    except (OSError, RuntimeError) as error:
        print(f"SKIP: original random code cannot be mapped: {error}")
        return 77
    try:
        new = RecoveredRandom(args.library)
        volatile_checks = compare_volatile(old, new)
        ui_checks = compare_ui_gain(old, new)
        checks = compare(old, new)
        print(f"PASS: {volatile_checks} volatile float-bit/state comparisons match the original")
        print(f"PASS: {ui_checks} production UI gain/state comparisons use original RNG")
        print(f"PASS: {checks} randomizer and chunk-geometry comparisons match the original")
        return 0
    finally:
        old.close()


if __name__ == "__main__":
    raise SystemExit(main())
