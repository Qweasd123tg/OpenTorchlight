"""Execute the inspected camera controller with a bounded, headless fixture.

No game startup, rendering, input, saves, or main(). The full controller's
instructions are unchanged. Only dependency entrypoints are supplied below.
The fixture covers normal gameplay, no level/collisions, no shake, yaw=0.
"""

import ctypes as c
import os
import platform
import struct

from original import Original


class Vec3(c.Structure):
    _fields_ = [("x", c.c_float), ("y", c.c_float), ("z", c.c_float)]


class OriginalCamera:
    def __init__(self, path):
        if platform.machine() != "x86_64" or os.sysconf("SC_PAGE_SIZE") != 4096:
            raise RuntimeError("Original camera comparison requires Linux x86-64 / 4K pages")
        self.original = Original(path)
        self.regions = []
        self.libc = c.CDLL(None, use_errno=True)
        self.libm = c.CDLL("libm.so.6")
        self.libc.mmap.argtypes = [c.c_void_p, c.c_size_t, c.c_int, c.c_int, c.c_int, c.c_long]
        self.libc.mmap.restype = c.c_void_p
        self.libc.mprotect.argtypes = [c.c_void_p, c.c_size_t, c.c_int]
        self.libc.munmap.argtypes = [c.c_void_p, c.c_size_t]
        self.callbacks = []
        self.master = c.create_string_buffer(0x98)
        self.player = c.create_string_buffer(0x3910)
        self.players = (c.c_void_p * 1)(c.addressof(self.player))
        self.resources = c.create_string_buffer(0x38)
        struct.pack_into("<QI", self.resources, 0x28, c.addressof(self.players), 1)
        struct.pack_into("<Q", self.master, 0x90, 0x1234)
        self.controller = c.create_string_buffer(0x90)
        self.netbook = False
        self.position = None
        self.look_at = None
        self.unexpected_calls = []
        try:
            code = (0x553000, 0x554000, 0x556000, 0xA54000, 0xC6E000,
                    0xC7A000, 0xCEA000, 0xCEB000)
            constants = (0xFA4000, 0xFA8000, 0xFC6000, 0xFCE000, 0xFD1000,
                         0xFF6000, 0x1423000, 0x1424000)
            for address in code + constants + (0x14F6000, 0x150B000):
                self._map(address)
            functions = (
                ("CCameraControl::updateGameCamera(float, CResourceManager*, Ogre::Vector3, ECAMERA_STATES)",
                 0xCEA050, 0x11D7),
                ("MATH::matrixRotationY(Ogre::Matrix4&, float)", 0xC7A2A0, 0x98),
            )
            for name, address, size in functions:
                symbol = self.original.symbol(name)
                if (symbol.address, symbol.size) != (address, size):
                    raise ValueError("Unsupported camera function layout: " + name)
                c.memmove(address, self.original.read(address, size), size)
            for address in constants:
                if address < 0x1423000:
                    c.memmove(address, self.original.read(address, 4096), 4096)
            # ELF copy relocations in .bss normally populated from OgreMain.
            identity = struct.pack("<16f", 1, 0, 0, 0, 0, 1, 0, 0,
                                   0, 0, 1, 0, 0, 0, 0, 1)
            c.memmove(0x1423FC0, identity, len(identity))
            c.memmove(0x1424B34, struct.pack("<3f", 0, 1, 0), 12)
            # C++ guard initialized; no global constructors from the executable run.
            c.c_uint64.from_address(0x14F6EA8).value = 1
            for identifier, address in enumerate((0x150B4D8, 0x150B4B4, 0x150B4A8), 1):
                c.c_uint32.from_address(address).value = identifier
            self._jump(0x553118, self.libm.sincosf)
            self._jump(0x5549F8, self.libm.powf)
            self._jump(0xA54490, c.CFUNCTYPE(c.c_void_p)(lambda: c.addressof(self.master)))
            self._jump(0xC6E440, c.CFUNCTYPE(c.c_int, c.c_void_p, c.c_uint32)(self._setting))
            self._jump(0x5560F8, c.CFUNCTYPE(None, c.c_void_p, c.POINTER(Vec3))(self._position))
            self._jump(0x556358, c.CFUNCTYPE(None, c.c_void_p, c.POINTER(Vec3))(self._look_at))
            for address in code:
                self._protect(address, 5)
            for address in constants:
                self._protect(address, 1)
            self.update = c.CFUNCTYPE(None, c.c_void_p, c.c_float, c.c_void_p,
                                     Vec3, c.c_int)(0xCEA050)
            self.rotation_y = c.CFUNCTYPE(None, c.POINTER(c.c_float), c.c_float)(0xC7A2A0)
        except BaseException:
            self.close()
            raise

    def _map(self, address):
        result = self.libc.mmap(address, 4096, 3, 0x100000 | 0x20 | 0x02, -1, 0)
        if result == c.c_void_p(-1).value:
            raise OSError(c.get_errno(), os.strerror(c.get_errno()))
        if result != address:
            self.libc.munmap(result, 4096)
            raise RuntimeError("Kernel did not honor MAP_FIXED_NOREPLACE")
        self.regions.append(address)

    def _protect(self, address, protection):
        if self.libc.mprotect(address, 4096, protection) != 0:
            raise OSError(c.get_errno(), os.strerror(c.get_errno()))

    def _jump(self, address, callback):
        self.callbacks.append(callback)
        trampoline = b"\x48\xb8" + struct.pack("<Q", c.cast(callback, c.c_void_p).value) + b"\xff\xe0"
        c.memmove(address, trampoline, len(trampoline))

    def _setting(self, instance, key):
        if instance != 0x1234 or key not in (1, 2, 3):
            self.unexpected_calls.append(("setting", instance, key))
        return int(self.netbook) if key == 1 else 0

    def _position(self, camera, value):
        if camera != 0x5678:
            self.unexpected_calls.append(("camera", camera))
        self.position = [value.contents.x, value.contents.y, value.contents.z]

    def _look_at(self, camera, value):
        if camera != 0x5678:
            self.unexpected_calls.append(("look_at", camera))
        self.look_at = [value.contents.x, value.contents.y, value.contents.z]

    def sample(self, target, dolly=28.5, netbook=True, multiplier=1.0,
               previous_offset=None, dt=1 / 60):
        c.memset(c.addressof(self.controller), 0, len(self.controller))
        struct.pack_into("<Q", self.controller, 0x10, 0x5678)
        struct.pack_into("<f", self.controller, 0x38, dolly)
        struct.pack_into("<f", self.controller, 0x8C, multiplier)
        if previous_offset is not None:
            struct.pack_into("<fff", self.controller, 0x3C, *previous_offset)
        self.netbook = netbook
        self.position = self.look_at = None
        self.unexpected_calls.clear()
        c.c_uint8.from_address(0x14F6EA0).value = 0
        self.update(self.controller, dt, self.resources, Vec3(*target), 0)
        if self.position is None or self.look_at is None or self.unexpected_calls:
            raise RuntimeError("Original camera left its fixture contract: " + repr(self.unexpected_calls))
        return {"position": self.position, "target": self.look_at}

    def close(self):
        for address in reversed(self.regions):
            self.libc.munmap(address, 4096)
        self.regions.clear()

    def __enter__(self):
        return self

    def __exit__(self, *_):
        self.close()
