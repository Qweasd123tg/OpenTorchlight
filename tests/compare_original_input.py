#!/usr/bin/env python3
"""Compare recovered C++ with isolated original x86-64 input functions.

Only the fingerprint-checked, inspected input functions are mapped. The game,
its dynamic loader, constructors, renderer and saves are never started.
MAP_FIXED_NOREPLACE refuses to overwrite existing mappings. Code is RX after
copying; original state is held in separate RW memory. CKeyManager::keyEvent
uses a controlled SDL_GetKeyboardState stub that returns a real byte array;
its original state-transition code is executed unchanged. Run in its own process.
"""

import argparse
import ctypes as c
import os
from pathlib import Path
import platform
import random
import struct
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from original import Original


class Point(c.Structure):
    _fields_ = [("x", c.c_int64), ("y", c.c_int64)]


FUNCTIONS = {
    "update_cursor": ("UpdateCursorPos(long, long)", 0xF63210, 15, None, [c.c_int64, c.c_int64]),
    "get_cursor": ("GetCursorPos(POINT*)", 0xF63220, 24, c.c_int, [c.POINTER(Point)]),
    "set_cursor": ("SetCursorPos(int, int)", 0xF63240, 3, c.c_int, [c.c_int32, c.c_int32]),
    "update_key": ("UpdateKeyState(unsigned int, bool)", 0xF63250, 10, None, [c.c_uint32, c.c_bool]),
    "get_async_key": ("GetAsyncKeyState(unsigned int)", 0xF63260, 18, c.c_int16, [c.c_uint32]),
    "get_key": ("GetKeyState(unsigned int)", 0xF63280, 18, c.c_int16, [c.c_uint32]),
    "clear_keys": ("ClearKeyState()", 0xF632B0, 19, None, []),
}

FRAME_FUNCTIONS = {
    "frame_pressed": ("CKeyManager::keyPressed(unsigned int)", 0x91A670, 0xB, c.c_bool, [c.c_uint32]),
    "frame_held": ("CKeyManager::keyHeld(unsigned int)", 0x91A680, 0x1B, c.c_bool, [c.c_uint32]),
    "frame_released": ("CKeyManager::keyReleased(unsigned int)", 0x91A6A0, 0xE, c.c_bool, [c.c_uint32]),
    "frame_capture": ("CKeyManager::capture()", 0x91A980, 0x119, None, []),
    "frame_flush_all": ("CKeyManager::flushAll()", 0x91AAA0, 0x84, None, []),
    "frame_flush": ("CKeyManager::flush()", 0x91AB30, 0x5B, None, []),
    "frame_event": ("CKeyManager::keyEvent(unsigned int, unsigned int)", 0x91AB90, 0x7E, None,
                    [c.c_uint32, c.c_uint32]),
}

MOUSE_FUNCTIONS = {
    "mouse_event": ("CMouseManager::mouseEvent(unsigned int, unsigned int)", 0x91AC90, 0x85, None,
                    [c.c_uint32, c.c_uint32]),
    "mouse_pressed": ("CMouseManager::buttonPressed(EMouseButton)", 0x91AD20, 0xC, c.c_bool, [c.c_int]),
    "mouse_held": ("CMouseManager::buttonHeld(EMouseButton)", 0x91AD30, 0x19, c.c_bool, [c.c_int]),
    "mouse_double": ("CMouseManager::buttonDoubleClick(EMouseButton)", 0x91AD50, 0xC, c.c_bool, [c.c_int]),
    "mouse_virtual": ("CMouseManager::virtualMousePosition(float, float, float, float)", 0x91AD60,
                      0x35, c.POINTER(Point), [c.c_float] * 4),
    "mouse_capture": ("CMouseManager::capture()", 0x91AE10, 0x57, None, []),
    "mouse_flush_all": ("CMouseManager::flushAll()", 0x91AE70, 0x26, None, []),
    "mouse_flush": ("CMouseManager::flush()", 0x91AEA0, 0x1C, None, []),
    "mouse_update": ("CMouseManager::update(void*)", 0x91AEC0, 0x9, None, [c.c_void_p]),
}


class OriginalInput:
    def __init__(self, original):
        self.libc = c.CDLL(None, use_errno=True)
        self.libc.mmap.argtypes = [c.c_void_p, c.c_size_t, c.c_int, c.c_int, c.c_int, c.c_long]
        self.libc.mmap.restype = c.c_void_p
        self.libc.mprotect.argtypes = [c.c_void_p, c.c_size_t, c.c_int]
        self.libc.munmap.argtypes = [c.c_void_p, c.c_size_t]
        self.regions = []
        self.keyboard = (c.c_uint8 * 512)()
        self.frame_memory = c.create_string_buffer(0xD20)
        self.mouse_memory = c.create_string_buffer(0x58)
        if os.sysconf("SC_PAGE_SIZE") != 4096:
            raise RuntimeError("This original-code comparison requires a 4096-byte host page")
        definitions = list(FUNCTIONS.values()) + list(FRAME_FUNCTIONS.values()) + list(MOUSE_FUNCTIONS.values())
        for name, address, size, _, _ in definitions:
            symbol = original.symbol(name)
            if (symbol.address, symbol.size) != (address, size):
                raise ValueError(f"Original function layout changed: {name}")
        for name, address, size in [("keyStates", 0x154DE00, 256),
                                     ("MouseX", 0x154DF00, 8), ("MouseY", 0x154DF08, 8)]:
            symbol = original.symbol(name)
            if (symbol.address, symbol.size) != (address, size):
                raise ValueError(f"Original state layout changed: {name}")
        try:
            for address in (0xF63000, 0x154D000, 0x91A000, 0x556000, 0xFD4000):
                result = self.libc.mmap(address, 4096, 3, 0x100000 | 0x20 | 0x02, -1, 0)
                if result == c.c_void_p(-1).value:
                    error = c.get_errno()
                    raise OSError(error, os.strerror(error))
                if result != address:
                    self.libc.munmap(result, 4096)
                    raise RuntimeError("Kernel did not honor MAP_FIXED_NOREPLACE")
                self.regions.append(address)
            for key, (_, address, size, result, arguments) in FUNCTIONS.items():
                c.memmove(address, original.read(address, size), size)
                setattr(self, key, c.CFUNCTYPE(result, *arguments)(address))
            for definitions, memory in ((FRAME_FUNCTIONS, self.frame_memory),
                                         (MOUSE_FUNCTIONS, self.mouse_memory)):
                for key, (_, address, size, result, arguments) in definitions.items():
                    c.memmove(address, original.read(address, size), size)
                    function = c.CFUNCTYPE(result, c.c_void_p, *arguments)(address)
                    def bound(*args, _function=function, _memory=memory):
                        return _function(c.addressof(_memory), *args)
                    setattr(self, key, bound)
            # Read-only dispatch table referenced by original mouseEvent.
            c.memmove(0xFD48A8, original.read(0xFD48A8, 80), 80)
            # movabs keyboard_buffer, %rax; ret. Only SDL's external query is stubbed.
            stub = b"\x48\xb8" + struct.pack("<Q", c.addressof(self.keyboard)) + b"\xc3"
            c.memmove(0x5563A8, stub, len(stub))
            for address in (0xF63000, 0x91A000, 0x556000):
                if self.libc.mprotect(address, 4096, 5) != 0:
                    error = c.get_errno()
                    raise OSError(error, os.strerror(error))
            if self.libc.mprotect(0xFD4000, 4096, 1) != 0:
                error = c.get_errno()
                raise OSError(error, os.strerror(error))
        except BaseException:
            self.close()
            raise

    def close(self):
        for address in reversed(self.regions):
            self.libc.munmap(address, 4096)
        self.regions.clear()

    def frame_caps(self):
        return bool(c.c_uint8.from_buffer(self.frame_memory, 0x10).value)

    def mouse_wheel(self):
        return c.c_int32.from_buffer(self.mouse_memory, 0x48).value

    def mouse_position(self):
        point = Point.from_buffer(self.mouse_memory, 0x28)
        return point.x, point.y


class RecoveredInput:
    def __init__(self, path):
        self.library = c.CDLL(str(path.resolve()))
        for key, (_, _, _, result, arguments) in FUNCTIONS.items():
            function = getattr(self.library, "recovered_" + key)
            function.restype = c.c_bool if key == "update_key" else result
            function.argtypes = arguments
            setattr(self, key, function)
        for key, (_, _, _, result, arguments) in FRAME_FUNCTIONS.items():
            function = getattr(self.library, "recovered_" + key)
            function.restype = result
            function.argtypes = arguments + ([c.c_bool] if key == "frame_event" else [])
            setattr(self, key, function)
        self.frame_caps = self.library.recovered_frame_caps
        self.frame_caps.restype = c.c_bool
        self.frame_caps.argtypes = []
        for key, (_, _, _, result, arguments) in MOUSE_FUNCTIONS.items():
            function = getattr(self.library, "recovered_" + key)
            function.restype = result
            function.argtypes = arguments
            setattr(self, key, function)
        self.mouse_wheel = self.library.recovered_mouse_wheel
        self.mouse_wheel.restype = c.c_int32
        self.mouse_wheel.argtypes = []
        self._mouse_position = self.library.recovered_mouse_position
        self._mouse_position.restype = None
        self._mouse_position.argtypes = [c.POINTER(Point)]

    def mouse_position(self):
        point = Point()
        self._mouse_position(c.byref(point))
        return point.x, point.y


def compare(old, new):
    checks = 0

    def equal(actual, expected, description):
        nonlocal checks
        checks += 1
        if actual != expected:
            raise AssertionError(f"{description}: recovered={actual}, original={expected}")

    def check_key(key):
        equal(new.get_key(key), old.get_key(key), f"key {key}")
        equal(new.get_async_key(key), old.get_async_key(key), f"async key {key}")

    def check_cursor():
        a, b = Point(-123, -456), Point(-123, -456)
        equal(new.get_cursor(c.byref(a)), old.get_cursor(c.byref(b)), "cursor result")
        equal((a.x, a.y), (b.x, b.y), "cursor coordinates")

    def check_all():
        for key in range(256):
            check_key(key)
        check_cursor()

    check_all()
    # Every valid key, including mouse and modifier virtual keys; repeated
    # reads catch accidental Windows-style consumed-edge semantics.
    for down in (True, False, True):
        for key in range(256):
            old.update_key(key, down)
            equal(new.update_key(key, down), True, "valid key accepted")
            check_key(key)
            check_key(key)
        check_all()
    for x, y in [(0, 0), (-1, -1), (2340, 1080), (-2**63, 2**63 - 1), (2**40, -2**40)]:
        old.update_cursor(x, y)
        new.update_cursor(x, y)
        check_cursor()
        equal(new.set_cursor(100, 200), old.set_cursor(100, 200), "SetCursorPos result")
        check_cursor()
        old.clear_keys()
        new.clear_keys()
        check_all()

    # Randomized interleavings test state interaction, clearing and persistence.
    generator = random.Random(0x544F5243)
    for step in range(20000):
        action = generator.randrange(5)
        key = generator.randrange(256)
        if action <= 1:
            down = bool(generator.getrandbits(1))
            old.update_key(key, down)
            equal(new.update_key(key, down), True, "valid random key accepted")
        elif action == 2:
            x, y = (generator.randrange(-2**40, 2**40) for _ in range(2))
            old.update_cursor(x, y)
            new.update_cursor(x, y)
        elif action == 3:
            x, y = (generator.randrange(-2**31, 2**31) for _ in range(2))
            equal(new.set_cursor(x, y), old.set_cursor(x, y), "random SetCursorPos result")
        else:
            old.clear_keys()
            new.clear_keys()
        check_key(key)
        check_cursor()
        if step % 127 == 0:
            check_all()

    # Defined safety extension: original is never called with invalid indexes.
    for invalid in (256, 65535, 2**32 - 1):
        equal(new.update_key(invalid, True), False, "invalid key rejected")
        equal(new.get_key(invalid), 0, "invalid key reads released")
        equal(new.get_async_key(invalid), 0, "invalid async key reads released")
    check_all()
    return checks


def compare_frames(old, new):
    checks = 0

    def equal(actual, expected, description):
        nonlocal checks
        checks += 1
        if actual != expected:
            raise AssertionError(f"{description}: recovered={actual}, original={expected}")

    def check_key(key):
        for name in ("frame_pressed", "frame_held", "frame_released"):
            equal(getattr(new, name)(key), getattr(old, name)(key), f"{name}({key})")
        equal(new.frame_caps(), old.frame_caps(), "physical caps key flag")

    def check_all():
        for key in range(512):
            check_key(key)

    def event(message, key, caps=False):
        old.keyboard[57] = caps
        old.frame_event(message, key)
        new.frame_event(message, key, caps)

    def action(name):
        getattr(old, name)()
        getattr(new, name)()

    # Zero test storage and an initial capture avoid relying on the original
    # constructor's unpublished/uninitialized frame snapshots.
    action("frame_capture")
    check_all()
    for key in range(512):
        for message in (0x101, 0x100, 0x100, 0x101, 0x104, 0x105):
            event(message, key)
            check_key(key)
        action("frame_capture")
        check_key(key)
        # Both edges can coexist. Held includes pressed, even after release.
        equal(new.frame_pressed(key), True, "press within frame")
        equal(new.frame_released(key), True, "release within frame")
        equal(new.frame_held(key), True, "quick tap is held for one frame")
        action("frame_capture")
        check_key(key)
        equal(new.frame_held(key), False, "quick tap expires next frame")

    # flush and flushAll affect pending state, not the published snapshot.
    event(0x100, 65, True)
    action("frame_capture")
    action("frame_flush_all")
    check_key(65)
    equal(new.frame_held(65), True, "flushAll retains published state")
    action("frame_capture")
    check_key(65)
    equal(new.frame_held(65), False, "capture publishes flushAll")

    generator = random.Random(0x4B455953)
    messages = (0x100, 0x101, 0x104, 0x105, 0x102, 0, 0xFFFFFFFF)
    for step in range(15000):
        choice = generator.randrange(6)
        key = generator.randrange(512)
        if choice < 3:
            event(generator.choice(messages), key, bool(generator.getrandbits(1)))
        else:
            action(("frame_capture", "frame_flush", "frame_flush_all")[choice - 3])
        check_key(key)
        if step % 101 == 0:
            check_all()
    for invalid in (512, 65535, 2**32 - 1):
        new.frame_event(0x100, invalid, False)
        event(0, 0, False)  # Same physical Caps query; no original out-of-bounds call.
        for name in ("frame_pressed", "frame_held", "frame_released"):
            equal(getattr(new, name)(invalid), False, "invalid key rejected")
    action("frame_capture")
    check_all()
    return checks


def compare_mouse(old, new):
    checks = 0

    def equal(actual, expected, description):
        nonlocal checks
        checks += 1
        if actual != expected:
            raise AssertionError(f"{description}: recovered={actual}, original={expected}")

    def check_all():
        for button in range(3):
            for name in ("mouse_pressed", "mouse_held", "mouse_double"):
                equal(getattr(new, name)(button), getattr(old, name)(button), f"{name}({button})")
        equal(new.mouse_wheel(), old.mouse_wheel(), "wheel delta")
        equal(new.mouse_position(), old.mouse_position(), "mouse position")

    def action(name, *args):
        getattr(old, name)(*args)
        getattr(new, name)(*args)

    check_all()
    for button in range(3):
        for message in (0x202, 0x201, 0x201, 0x202, 0x203):
            action("mouse_event", message + button * 3, 0)
            check_all()
        action("mouse_capture")
        check_all()
        equal(new.mouse_held(button), True, "quick mouse tap held within frame")
        equal(new.mouse_double(button), button != 2, "middle double click ignored")
        action("mouse_capture")
        check_all()
        equal(new.mouse_held(button), False, "mouse tap expires")

    # Accumulation wraps at 32 bits in the original, including signed wheel deltas.
    for _ in range(70000):
        action("mouse_event", 0x20A, 0x7FFF0000)
    action("mouse_capture")
    check_all()
    for delta in (0xFFFF0000, 0x80000000, 0x0001FFFF, 0):
        action("mouse_event", 0x20A, delta)
    action("mouse_capture")
    check_all()

    generator = random.Random(0x4D4F5553)
    for _ in range(8000):
        choice = generator.randrange(6)
        if choice < 3:
            action("mouse_event", generator.choice(tuple(range(0x200, 0x20C)) + (0, 0xFFFFFFFF)),
                   generator.getrandbits(32))
        else:
            action(("mouse_capture", "mouse_flush", "mouse_flush_all")[choice - 3])
        check_all()

    dimensions = [(2160, 1440, 1024, 768), (2340, 1080, 1560, 720),
                  (0, 0, 0, 0), (0, 1, 1, -1), (1, 1, 1, 1),
                  (float("inf"), float("nan"), 1, 1)]
    points = [(0, 0), (-1, 1), (1170, 540), (-2**63, 2**63 - 1),
              (2**31 - 1, -(2**31)), (2**40, -(2**40))]
    for _ in range(1000):
        points.append((generator.randrange(-10000, 10000), generator.randrange(-10000, 10000)))
    for x, y in points:
        action("update_cursor", x, y)
        action("mouse_update", None)
        check_all()
        for size in dimensions:
            a = old.mouse_virtual(*size).contents
            b = new.mouse_virtual(*size).contents
            equal((b.x, b.y), (a.x, a.y), f"virtual coordinates {x},{y} / {size}")
    for invalid in (-1, 3, 65535):
        for name in ("mouse_pressed", "mouse_held", "mouse_double"):
            equal(getattr(new, name)(invalid), False, "invalid mouse button rejected")
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
    new = RecoveredInput(args.library)
    old = OriginalInput(original)
    try:
        checks = compare(old, new)
        frame_checks = compare_frames(old, new)
        mouse_checks = compare_mouse(old, new)
    finally:
        old.close()
    print(f"PASS: {checks} checks, 20000 randomized operations, 7 original state functions")
    print(f"PASS: {frame_checks} checks, 15000 randomized operations, 7 original frame functions")
    print(f"PASS: {mouse_checks} checks, 8000 randomized operations, 9 original mouse functions")
    print(f"Original SHA256: {original.sha256}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
