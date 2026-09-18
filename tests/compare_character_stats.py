#!/usr/bin/env python3
"""Bounded original character-stat oracle, not a whole-character simulation.

Loads unchanged, fingerprint-checked functions from a user-supplied Linux ELF.
Only getEffectValue is stubbed with evaluated test inputs; ceilf uses host libm.
No loader, constructors, game, resources or effect lifecycle is executed.
Linux x86-64; use a PIE Python host to avoid the original address range.
"""
from __future__ import annotations
import argparse
import ctypes as c
import hashlib
import json
import os
from pathlib import Path
import platform
import random
import struct
import subprocess
import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from original import Original

FUNCTIONS = {
    'walking': ('CCharacter::walkingSpeed()', 0x815a20, 0xa6),
    'running': ('CCharacter::runningSpeed()', 0x815ad0, 0xa6),
    'defense': ('CCharacter::defense()', 0x814530, 0x85),
    'armor': ('CCharacter::armorBonus()', 0x8145c0, 0xae),
    'ac': ('CCharacter::AC()', 0x814670, 0x61),
}
def bits(v): return struct.unpack('<I', struct.pack('<f', v))[0]
def f32(v): return struct.unpack('<f', struct.pack('<f', v))[0]

class Native:
    def __init__(self, original):
        self.libc = c.CDLL(None, use_errno=True)
        self.libc.mmap.argtypes = [c.c_void_p, c.c_size_t, c.c_int, c.c_int, c.c_int, c.c_long]
        self.libc.mmap.restype = c.c_void_p
        self.libc.mprotect.argtypes = [c.c_void_p, c.c_size_t, c.c_int]
        self.libc.munmap.argtypes = [c.c_void_p, c.c_size_t]
        self.pages = set()
        self.values = {}
        self.actor = c.create_string_buffer(0x700)
        self.inventory = c.create_string_buffer(0x40)
        self.owner = c.create_string_buffer(0x700)
        self.callbacks = []
        self.libm = c.CDLL('libm.so.6')
        self.evidence = []
        try:
            for name, addr, size in FUNCTIONS.values():
                symbol = original.symbol(name)
                if (symbol.address, symbol.size) != (addr, size):
                    raise ValueError('Unexpected symbol: ' + name)
                code = original.read(addr, size)
                self.put(addr, code)
                self.evidence.append({'symbol': name, 'address': hex(addr), 'size': size,
                                      'sha256': hashlib.sha256(code).hexdigest()})
            for addr, size in ((0xfa47f8, 8), (0xfa483c, 4)):
                self.put(addr, original.read(addr, size))
            @c.CFUNCTYPE(c.c_float, c.c_void_p, c.c_uint32, c.c_uint32)
            def effect(actor, kind, damage):
                return self.values.get((actor == c.addressof(self.owner), kind, damage), 0.)
            self.callbacks.append(effect)
            self.jump(0x8137e0, c.cast(effect, c.c_void_p).value)
            self.jump(0x553678, c.cast(self.libm.ceilf, c.c_void_p).value)
            for page in self.pages:
                if self.libc.mprotect(page, 4096, 1 if page == 0xfa4000 else 5):
                    raise OSError(c.get_errno(), 'mprotect')
            self.running = c.CFUNCTYPE(c.c_float, c.c_void_p)(0x815ad0)
            self.walking = c.CFUNCTYPE(c.c_float, c.c_void_p)(0x815a20)
            self.defense = c.CFUNCTYPE(c.c_int32, c.c_void_p)(0x814530)
            self.ac = c.CFUNCTYPE(c.c_int32, c.c_void_p)(0x814670)
            struct.pack_into('<Q', self.actor, 0x490, c.addressof(self.inventory))
        except BaseException:
            self.close()
            raise
    def put(self, addr, data):
        for page in range(addr & ~4095, ((addr + len(data) - 1) & ~4095) + 4096, 4096):
            if page in self.pages: continue
            got = self.libc.mmap(page, 4096, 3, 0x100000 | 0x20 | 2, -1, 0)
            if got == c.c_void_p(-1).value: raise OSError(c.get_errno(), 'MAP_FIXED_NOREPLACE failed; use PIE host')
            if got != page:
                self.libc.munmap(got, 4096)
                raise RuntimeError('MAP_FIXED_NOREPLACE not honored')
            self.pages.add(page)
        c.memmove(addr, data, len(data))
    def jump(self, addr, target): self.put(addr, b'\x48\xb8' + struct.pack('<Q', target) + b'\xff\xe0')
    def close(self):
        for page in self.pages: self.libc.munmap(page, 4096)
        self.pages.clear()

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--original', type=Path, required=True)
    p.add_argument('--probe', type=Path, required=True)
    p.add_argument('--output', type=Path)
    args = p.parse_args()
    if platform.system() != 'Linux' or platform.machine() not in ('x86_64', 'AMD64') or os.sysconf('SC_PAGE_SIZE') != 4096:
        return 77
    original = Original(args.original)
    native = Native(original)
    inputs, expected, groups = [], [], {}
    rng = random.Random(0x815ad0)
    def append(group, text, value):
        inputs.append(text + '\n'); expected.append(value); groups[group] = groups.get(group, 0) + 1
    try:
        movement = [(f32(b), f32(pct), f32(r)) for b in (0, .01, 2.5, 6, 8.4, 1000)
                    for pct in (-250, -100, -99.999, -50, -0.001, 0, 0.1, 25, 50, 200)
                    for r in (-20, 0, .01, 50, 99.999, 100, 150)]
        movement += [(f32(rng.uniform(0, 1000)), f32(rng.uniform(-250, 250)), f32(rng.uniform(-50, 150))) for _ in range(4000)]
        for base, pct, resist in movement:
            native.values = {(False, 0x15, 7): pct, (False, 0x8c, 7): resist}
            struct.pack_into('<ff', native.actor, 0x28c, base, base)
            for name, function in (('walking', native.walking), ('running', native.running)):
                append(name, f'0 {bits(base)} {bits(pct)} {bits(resist)}', bits(function(c.addressof(native.actor))))
        defense_cases = [(base, f32(pct), f32(all_pct), f32(flat)) for base in (-5, 0, 1, 7, 20, 101, 9999)
                         for pct in (-120, -.001, 0, 25, 100) for all_pct in (0, 25)
                         for flat in (-1.1, 0, .01, 1.1)]
        defense_cases += [(rng.randrange(100000), f32(rng.uniform(-100, 250)), f32(rng.uniform(-100, 250)),
                           f32(rng.uniform(-100, 100))) for _ in range(6000)]
        for base, pct, all_pct, flat in defense_cases:
            native.values = {(False, 0x11, 7): pct, (False, 0x11, 6): all_pct, (False, 2, 7): flat}
            struct.pack_into('<i', native.actor, 0x430, base)
            append('defense', f'1 {base} {bits(pct)} {bits(all_pct)} {bits(flat)}', native.defense(c.addressof(native.actor)))
        armor_cases = [(base, defense, f32(pct), f32(flat), f32(degrade), f32(owner))
                       for base in (0, 1, 7, 20, 101, 9999) for defense in (-10, 0, 1, 99)
                       for pct in (-100, 0, 50) for flat in (0, 20.1)
                       for degrade in (0, 20.1) for owner in (0, 50)]
        armor_cases += [(rng.randrange(100000), rng.randrange(-50, 1000), f32(rng.uniform(-120, 250)),
                         f32(rng.uniform(-100, 100)), f32(rng.uniform(-10, 1000)), f32(rng.uniform(-50, 100))) for _ in range(6000)]
        for base, defense, pct, flat, degrade, owner in armor_cases:
            native.values = {(False, 0x17, 7): pct, (False, 8, 7): flat,
                             (False, 0x42, 7): degrade, (True, 0x61, 7): owner}
            # Independently exercise the actor+inventory sum and nullable master path.
            gear = rng.randrange(base + 1)
            struct.pack_into('<i', native.actor, 0x424, base - gear)
            struct.pack_into('<i', native.inventory, 0x10, gear)
            struct.pack_into('<i', native.actor, 0x430, defense)
            struct.pack_into('<Q', native.actor, 0x640, c.addressof(native.owner) if owner != 0 else 0)
            append('physical_AC', f'2 {base} {defense} {bits(pct)} {bits(flat)} {bits(degrade)} {bits(owner)}', native.ac(c.addressof(native.actor)))
        result = subprocess.run([str(args.probe.resolve())], input=''.join(inputs), text=True, capture_output=True, check=True, timeout=60)
        actual = list(map(int, result.stdout.split()))
        if actual != expected:
            i = next((i for i, pair in enumerate(zip(actual, expected)) if pair[0] != pair[1]), None)
            raise AssertionError({'case': i, 'input': inputs[i] if i is not None else None,
                                  'expected': expected[i] if i is not None else len(expected),
                                  'actual': actual[i] if i is not None else len(actual)})
        report = {'original_sha256': original.sha256, 'functions': native.evidence,
                  'comparisons': len(expected), 'groups': groups, 'passed': True,
                  'scope': 'Unchanged bounded original functions, controlled evaluated effects/objects, host ceilf. No effect lifecycle, elemental defense, UI, AI or constructed original character.',
                  'domain': 'Finite binary32 inputs; integer intermediates fit int32. NaN/infinity and integer overflow excluded.'}
        if args.output:
            args.output.parent.mkdir(parents=True, exist_ok=True)
            args.output.write_text(json.dumps(report, indent=2) + '\n')
        print(json.dumps(report, indent=2))
    finally:
        native.close()
    return 0
if __name__ == '__main__': raise SystemExit(main())
