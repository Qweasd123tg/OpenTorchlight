#!/usr/bin/env python3
"""Compare recovered path-grid primitives with original machine code."""

import argparse
import ctypes as c
import os
from pathlib import Path
import random
import struct
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from original import Original


FUNCTIONS = {
    "tile_index": ("CAstarPathfinder::tileIndex(unsigned int, unsigned int)", 0x592240, 0x08),
    "tile_free": ("CAstarPathfinder::tileFree(unsigned int, unsigned int, ENodeDirection)",
                  0x592250, 0x44),
    "node_x": ("CAstarPathfinder::getNodeX()", 0x5922B0, 0x24),
    "node_z": ("CAstarPathfinder::getNodeY()", 0x5922E0, 0x24),
}


def float_bits(value):
    return struct.pack("<f", value)


class OriginalPathRules:
    def __init__(self, original):
        self.libc = c.CDLL(None, use_errno=True)
        self.libc.mmap.argtypes = [c.c_void_p, c.c_size_t, c.c_int, c.c_int, c.c_int, c.c_long]
        self.libc.mmap.restype = c.c_void_p
        self.libc.mprotect.argtypes = [c.c_void_p, c.c_size_t, c.c_int]
        self.libc.munmap.argtypes = [c.c_void_p, c.c_size_t]
        self.address = 0x592000
        self.constant_address = 0xFA4000
        self.object = c.create_string_buffer(0x70)
        self.node = c.create_string_buffer(0x68)
        if os.sysconf("SC_PAGE_SIZE") != 4096:
            raise RuntimeError("Path comparison requires a 4096-byte host page")
        result = self.libc.mmap(self.address, 4096, 3, 0x100000 | 0x20 | 0x02, -1, 0)
        if result == c.c_void_p(-1).value:
            error = c.get_errno()
            raise OSError(error, os.strerror(error))
        if result != self.address:
            self.libc.munmap(result, 4096)
            raise RuntimeError("Kernel did not honor MAP_FIXED_NOREPLACE")
        constant_result = self.libc.mmap(
            self.constant_address, 4096, 3, 0x100000 | 0x20 | 0x02, -1, 0)
        if constant_result == c.c_void_p(-1).value:
            error = c.get_errno()
            self.libc.munmap(self.address, 4096)
            self.address = 0
            raise OSError(error, os.strerror(error))
        if constant_result != self.constant_address:
            self.libc.munmap(constant_result, 4096)
            self.libc.munmap(self.address, 4096)
            self.address = 0
            raise RuntimeError("Kernel did not honor MAP_FIXED_NOREPLACE for constants")
        try:
            for name, (symbol_name, address, size) in FUNCTIONS.items():
                symbol = original.symbol(symbol_name)
                if (symbol.address, symbol.size) != (address, size):
                    raise ValueError(f"Original {name} layout changed")
                c.memmove(address, original.read(address, size), size)
            c.memmove(0xFA4810, original.read(0xFA4810, 4), 4)
            if self.libc.mprotect(self.address, 4096, 5) != 0:
                error = c.get_errno()
                raise OSError(error, os.strerror(error))
            if self.libc.mprotect(self.constant_address, 4096, 1) != 0:
                error = c.get_errno()
                raise OSError(error, os.strerror(error))
            self.tile_index = c.CFUNCTYPE(c.c_uint32, c.c_void_p, c.c_uint32, c.c_uint32)(0x592240)
            self.tile_free = c.CFUNCTYPE(c.c_bool, c.c_void_p, c.c_uint32, c.c_uint32,
                                         c.c_int)(0x592250)
            self.node_x = c.CFUNCTYPE(c.c_float, c.c_void_p)(0x5922B0)
            self.node_z = c.CFUNCTYPE(c.c_float, c.c_void_p)(0x5922E0)
        except BaseException:
            self.close()
            raise

    def configure(self, width, height, primary, secondary, primary_only):
        rows_primary = (c.POINTER(c.c_int16) * width)()
        rows_secondary = (c.POINTER(c.c_int16) * width)()
        for x in range(width):
            rows_primary[x] = c.cast(c.byref(primary, x * height * 2), c.POINTER(c.c_int16))
            rows_secondary[x] = c.cast(c.byref(secondary, x * height * 2), c.POINTER(c.c_int16))
        self.rows_primary = rows_primary
        self.rows_secondary = rows_secondary
        c.c_uint32.from_buffer(self.object, 0x3C).value = height
        c.c_uint32.from_buffer(self.object, 0x40).value = width
        c.c_void_p.from_buffer(self.object, 0x50).value = c.addressof(rows_primary)
        c.c_void_p.from_buffer(self.object, 0x58).value = c.addressof(rows_secondary)
        c.c_uint8.from_buffer(self.object, 0x69).value = primary_only

    def configure_node(self, coordinate_x, coordinate_z, cell_size, origin_x, origin_z):
        c.c_void_p.from_buffer(self.object, 0x28).value = c.addressof(self.node)
        c.c_uint32.from_buffer(self.node, 0x0C).value = coordinate_x
        c.c_uint32.from_buffer(self.node, 0x10).value = coordinate_z
        c.c_float.from_buffer(self.object, 0x44).value = cell_size
        c.c_float.from_buffer(self.object, 0x60).value = origin_x
        c.c_float.from_buffer(self.object, 0x64).value = origin_z

    def close(self):
        if getattr(self, "address", 0):
            self.libc.munmap(self.address, 4096)
            self.address = 0
        if getattr(self, "constant_address", 0):
            self.libc.munmap(self.constant_address, 4096)
            self.constant_address = 0


class RecoveredPathRules:
    def __init__(self, path):
        self.library = c.CDLL(str(path.resolve()))
        self.tile_index = self.library.recovered_path_tile_index
        self.tile_index.restype = c.c_uint32
        self.tile_index.argtypes = [c.c_uint32, c.c_uint32, c.c_uint32]
        self.tile_free = self.library.recovered_path_tile_free
        self.tile_free.restype = c.c_bool
        self.tile_free.argtypes = [c.c_uint32, c.c_uint32, c.POINTER(c.c_int16),
                                   c.POINTER(c.c_int16), c.c_bool, c.c_uint32, c.c_uint32]
        self.node_center = self.library.recovered_path_node_center
        self.node_center.restype = c.c_float
        self.node_center.argtypes = [c.c_uint32, c.c_float, c.c_float]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--original", required=True, type=Path)
    parser.add_argument("--library", required=True, type=Path)
    args = parser.parse_args()
    original = Original(args.original)
    try:
        old = OriginalPathRules(original)
    except (OSError, RuntimeError) as error:
        print(f"SKIP: original pathfinder code cannot be mapped: {error}")
        return 77
    new = RecoveredPathRules(args.library)
    generator = random.Random(0x50415448)
    checks = 0
    try:
        for _ in range(80):
            width = generator.randrange(1, 48)
            height = generator.randrange(1, 48)
            values = width * height
            primary = (c.c_int16 * values)(*(generator.randrange(-2, 3) for _ in range(values)))
            secondary = (c.c_int16 * values)(*(generator.randrange(-2, 3) for _ in range(values)))
            primary_only = bool(generator.getrandbits(1))
            old.configure(width, height, primary, secondary, primary_only)
            for _ in range(400):
                x = generator.randrange(0, width + 3)
                z = generator.randrange(0, height + 3)
                if new.tile_index(width, x, z) != old.tile_index(c.byref(old.object), x, z):
                    raise AssertionError("tileIndex differs")
                actual = new.tile_free(width, height, primary, secondary, primary_only, x, z)
                expected = old.tile_free(c.byref(old.object), x, z, generator.randrange(0, 9))
                if actual != expected:
                    raise AssertionError("tileFree differs")
                checks += 2
        for _ in range(20000):
            x = generator.randrange(0, 100000)
            z = generator.randrange(0, 100000)
            cell_size = c.c_float(generator.uniform(0.01, 20.0)).value
            origin_x = c.c_float(generator.uniform(-10000.0, 10000.0)).value
            origin_z = c.c_float(generator.uniform(-10000.0, 10000.0)).value
            old.configure_node(x, z, cell_size, origin_x, origin_z)
            if float_bits(new.node_center(x, cell_size, origin_x)) != float_bits(
                    old.node_x(c.byref(old.object))):
                raise AssertionError("getNodeX differs")
            if float_bits(new.node_center(z, cell_size, origin_z)) != float_bits(
                    old.node_z(c.byref(old.object))):
                raise AssertionError("getNodeY differs")
            checks += 2
    finally:
        old.close()
    print(f"PASS: {checks} path-grid comparisons match the original")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
