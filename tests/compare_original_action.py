#!/usr/bin/env python3
"""Compare recovered pointer movement with isolated original machine code."""

import argparse
import ctypes as c
import math
import os
from pathlib import Path
import platform
import random
import struct
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from original import Original


MOVE = ("CGameClient::moveToMouse(bool)", 0x57A900, 0xE3)
DEPENDENCIES = (
    ("CGameClient::findWorldLocation(Ogre::Vector3&, bool)", 0x579E90),
    ("CPositionableObject::getPosition(bool)", 0x9E7080),
    ("CCharacter::setDestination(CLevel&, float, float)", 0x82AC30),
)


class Vector3(c.Structure):
    _fields_ = [("x", c.c_float), ("y", c.c_float), ("z", c.c_float)]


class StubState(c.Structure):
    _fields_ = [
        ("projection_result", c.c_uint8),
        ("projection_mode", c.c_uint8),
        ("current_position", c.c_uint8),
        ("reserved", c.c_uint8),
        ("projected", Vector3),
        ("actor", Vector3),
        ("find_calls", c.c_uint32),
        ("position_calls", c.c_uint32),
        ("destination_calls", c.c_uint32),
        ("padding", c.c_uint32),
        ("actor_pointer", c.c_uint64),
        ("level_pointer", c.c_uint64),
        ("destination_x", c.c_float),
        ("destination_z", c.c_float),
    ]


class ActionResult(c.Structure):
    _fields_ = [
        ("find_calls", c.c_uint32),
        ("position_calls", c.c_uint32),
        ("destination_calls", c.c_uint32),
        ("projection_mode", c.c_uint32),
        ("current_position", c.c_uint32),
        ("moved", c.c_uint32),
        ("cooldown", c.c_float),
        ("destination_x", c.c_float),
        ("destination_z", c.c_float),
    ]


def movabs_rax(address):
    return b"\x48\xb8" + struct.pack("<Q", address)


class OriginalPointerMovement:
    def __init__(self, original):
        self.libc = c.CDLL(None, use_errno=True)
        self.libc.mmap.argtypes = [c.c_void_p, c.c_size_t, c.c_int, c.c_int, c.c_int, c.c_long]
        self.libc.mmap.restype = c.c_void_p
        self.libc.mprotect.argtypes = [c.c_void_p, c.c_size_t, c.c_int]
        self.libc.munmap.argtypes = [c.c_void_p, c.c_size_t]
        self.regions = []
        self.state = StubState()
        self.client = c.create_string_buffer(0x100)
        self.actor = c.create_string_buffer(0x300)
        self.level = c.create_string_buffer(8)

        if os.sysconf("SC_PAGE_SIZE") != 4096:
            raise RuntimeError("This original-code comparison requires a 4096-byte host page")
        symbol = original.symbol(MOVE[0])
        if (symbol.address, symbol.size) != MOVE[1:]:
            raise ValueError("Original moveToMouse layout changed")
        for name, address in DEPENDENCIES:
            if original.symbol(name).address != address:
                raise ValueError(f"Original dependency moved: {name}")

        try:
            pages = (0x57A000, 0x579000, 0x9E7000, 0x82A000)
            for address in pages:
                result = self.libc.mmap(address, 4096, 3, 0x100000 | 0x20 | 0x02, -1, 0)
                if result == c.c_void_p(-1).value:
                    error = c.get_errno()
                    raise OSError(error, os.strerror(error))
                if result != address:
                    self.libc.munmap(result, 4096)
                    raise RuntimeError("Kernel did not honor MAP_FIXED_NOREPLACE")
                self.regions.append(address)

            c.memmove(MOVE[1], original.read(MOVE[1], MOVE[2]), MOVE[2])
            state = c.addressof(self.state)
            find_stub = (movabs_rax(state) + b"\xff\x40\x1c\x88\x50\x01\x48\x8b\x48\x04"
                         b"\x48\x89\x0e\x8b\x48\x0c\x89\x4e\x08\x0f\xb6\x00\xc3")
            position_stub = (movabs_rax(state) + b"\xff\x40\x20\x40\x88\x70\x02"
                             b"\xf3\x0f\x7e\x40\x10\xf3\x0f\x10\x48\x18\xc3")
            destination_stub = (movabs_rax(state) + b"\xff\x40\x24\x48\x89\x78\x30"
                                b"\x48\x89\x70\x38\xf3\x0f\x11\x40\x40"
                                b"\xf3\x0f\x11\x48\x44\xc3")
            for address, code in ((0x579E90, find_stub), (0x9E7080, position_stub),
                                  (0x82AC30, destination_stub)):
                c.memmove(address, code, len(code))
            for address in pages:
                if self.libc.mprotect(address, 4096, 5) != 0:
                    error = c.get_errno()
                    raise OSError(error, os.strerror(error))
            self.function = c.CFUNCTYPE(None, c.c_void_p, c.c_bool)(MOVE[1])
        except BaseException:
            self.close()
            raise

    def run(self, projection_result, projected, actor, legacy_argument, projection_mode, cooldown):
        c.memset(c.addressof(self.state), 0, c.sizeof(self.state))
        self.state.projection_result = projection_result
        self.state.projected = Vector3(*projected)
        self.state.actor = Vector3(*actor)
        c.memset(c.addressof(self.client), 0, c.sizeof(self.client))
        c.memset(c.addressof(self.actor), 0, c.sizeof(self.actor))
        c.c_void_p.from_buffer(self.client, 0x58).value = c.addressof(self.actor)
        c.c_void_p.from_buffer(self.client, 0x70).value = c.addressof(self.level)
        c.c_float.from_buffer(self.client, 0x80).value = cooldown
        c.c_uint8.from_buffer(self.actor, 0x266).value = projection_mode
        self.function(c.addressof(self.client), legacy_argument)
        result = ActionResult()
        result.find_calls = self.state.find_calls
        result.position_calls = self.state.position_calls
        result.destination_calls = self.state.destination_calls
        result.projection_mode = self.state.projection_mode
        result.current_position = self.state.current_position
        result.moved = self.state.destination_calls != 0
        result.cooldown = c.c_float.from_buffer(self.client, 0x80).value
        result.destination_x = self.state.destination_x
        result.destination_z = self.state.destination_z
        if result.destination_calls:
            if self.state.actor_pointer != c.addressof(self.actor):
                raise AssertionError("original setDestination received the wrong actor")
            if self.state.level_pointer != c.addressof(self.level):
                raise AssertionError("original setDestination received the wrong level")
        return result

    def close(self):
        for address in reversed(self.regions):
            self.libc.munmap(address, 4096)
        self.regions.clear()


class RecoveredPointerMovement:
    def __init__(self, path):
        self.library = c.CDLL(str(path.resolve()))
        self.function = self.library.recovered_move_to_pointer
        self.function.restype = None
        self.function.argtypes = [c.c_bool, *([c.c_float] * 6), c.c_bool, c.c_bool,
                                  c.c_float, c.POINTER(ActionResult)]

    def run(self, projection_result, projected, actor, legacy_argument, projection_mode, cooldown):
        result = ActionResult()
        self.function(projection_result, *projected, *actor, legacy_argument, projection_mode,
                      cooldown, c.byref(result))
        return result


def float_bits(value):
    return struct.pack("<f", value)


def compare_case(old, new, arguments, label):
    expected = old.run(*arguments)
    actual = new.run(*arguments)
    checks = 0
    for field in ("find_calls", "position_calls", "destination_calls", "projection_mode",
                  "current_position", "moved"):
        checks += 1
        if getattr(actual, field) != getattr(expected, field):
            raise AssertionError(
                f"{label} {field}: recovered={getattr(actual, field)}, original={getattr(expected, field)}"
            )
    checks += 1
    if float_bits(actual.cooldown) != float_bits(expected.cooldown):
        raise AssertionError(f"{label} cooldown differs")
    if expected.destination_calls:
        for field in ("destination_x", "destination_z"):
            checks += 1
            if float_bits(getattr(actual, field)) != float_bits(getattr(expected, field)):
                raise AssertionError(f"{label} {field} differs")
    return checks


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--library", type=Path, required=True)
    args = parser.parse_args()
    if platform.system() != "Linux" or platform.machine() not in {"x86_64", "AMD64"}:
        print("SKIP: original machine-code comparison requires Linux x86-64")
        return 77

    original = Original(args.original)
    old = OriginalPointerMovement(original)
    new = RecoveredPointerMovement(args.library)
    checks = 0
    cases = [
        (False, (1.0, 2.0, 3.0), (4.0, 5.0, 6.0), False, False, 0.0),
        (True, (1.0, 2.0, 3.0), (1.0, 2.0, 3.0), False, True, 4.0),
        (True, (1.0, 2.0, 3.0), (4.0, 2.0, 3.0), True, False, 0.1),
        (True, (1.0, 2.0, 3.0), (1.0, 9.0, 3.0), True, True, 0.0),
        (True, (-0.0, 2.0, 3.0), (0.0, 2.0, 3.0), False, False, math.inf),
        (True, (1.0, 2.0, 3.0), (1.0, 2.0, 4.0), False, True, -math.inf),
        (True, (1.0, 2.0, 3.0), (1.0, 2.0, 4.0), True, True, math.nan),
        (True, (math.nan, 2.0, 3.0), (math.nan, 2.0, 3.0), True, False, 0.0),
    ]
    generator = random.Random(0x4D4F5645)
    for _ in range(20000):
        projected = tuple(generator.uniform(-10000.0, 10000.0) for _ in range(3))
        actor = projected if generator.randrange(5) == 0 else tuple(
            generator.uniform(-10000.0, 10000.0) for _ in range(3)
        )
        cases.append((bool(generator.getrandbits(1)), projected, actor,
                      bool(generator.getrandbits(1)), bool(generator.getrandbits(1)),
                      generator.choice((-1.0, 0.0, 0.1, 1.0))))
    try:
        for index, case in enumerate(cases):
            checks += compare_case(old, new, case, f"case {index}")
    finally:
        old.close()
    print(f"PASS: {checks} checks, 20000 randomized cases, 1 original action function")
    print(f"Original SHA256: {original.sha256}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
