#!/usr/bin/env python3
"""Execute unchanged setGraphDamage/setGraphAC from the fingerprinted ELF.

Graph/string-manager queries are controlled callbacks; the numeric functions and
stores are original instructions. This is not full item generation/retirement.
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
from compare_character_stats import Native as Mapping, bits, f32
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from original import Original

class Native(Mapping):
    def __init__(self, original):
        self.libc = c.CDLL(None, use_errno=True)
        self.libc.mmap.argtypes = [c.c_void_p, c.c_size_t, c.c_int, c.c_int, c.c_int, c.c_long]
        self.libc.mmap.restype = c.c_void_p
        self.libc.mprotect.argtypes = [c.c_void_p, c.c_size_t, c.c_int]
        self.libc.munmap.argtypes = [c.c_void_p, c.c_size_t]
        self.pages, self.callbacks, self.evidence = set(), [], []
        self.actor = c.create_string_buffer(0x500)
        self.graph = c.create_string_buffer(8)
        self.graph_value = 0.
        self.libm = c.CDLL('libm.so.6')
        try:
            for name, addr, size in [('CEquipment::setGraphDamage(unsigned int)', 0x87dfa0, 0x114),
                                     ('CEquipment::setGraphAC(unsigned int)', 0x87e0c0, 0x10c)]:
                symbol = original.symbol(name)
                if (symbol.address, symbol.size) != (addr, size):
                    raise ValueError('Unexpected symbol: ' + name)
                code = original.read(addr, size)
                self.put(addr, code)
                self.evidence.append({'symbol': name, 'address': hex(addr), 'size': size,
                                      'sha256': hashlib.sha256(code).hexdigest()})
            self.put(0xfa483c, original.read(0xfa483c, 4))
            @c.CFUNCTYPE(None, c.c_void_p, c.c_void_p, c.c_void_p)
            def string(out, _text, _allocator):
                c.c_uint64.from_address(out).value = 0x1424540 + 0x18
            @c.CFUNCTYPE(c.c_void_p)
            def singleton(): return c.addressof(self.graph)
            @c.CFUNCTYPE(c.c_void_p, c.c_void_p, c.c_void_p)
            def get_graph(_manager, _name): return c.addressof(self.graph)
            @c.CFUNCTYPE(c.c_float, c.c_void_p, c.c_float, c.c_uint32)
            def value(_graph, _level, _index): return self.graph_value
            for address, callback in [(0x555e58, string), (0xa51d40, singleton),
                                       (0xa51fa0, get_graph), (0xc78310, value)]:
                self.callbacks.append(callback)
                self.jump(address, c.cast(callback, c.c_void_p).value)
            self.jump(0x553678, c.cast(self.libm.ceilf, c.c_void_p).value)
            for page in self.pages:
                if self.libc.mprotect(page, 4096, 1 if page == 0xfa4000 else 5):
                    raise OSError(c.get_errno(), 'mprotect')
            self.damage = c.CFUNCTYPE(None, c.c_void_p, c.c_uint32)(0x87dfa0)
            self.armor = c.CFUNCTYPE(None, c.c_void_p, c.c_uint32)(0x87e0c0)
        except BaseException:
            self.close()
            raise


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
    rng = random.Random(0x87dfa0)
    cases = [(f32(base), pct, count) for base in (0, .01, 1, 3, 7, 21, 50, 100, 9999)
             for pct in (0, 1, 7, 30, 57, 100, 101, 110, 300) for count in (0, 1, 4, 5, 6, 10)]
    cases += [(f32(rng.uniform(0, 10000)), rng.randrange(2000), rng.randrange(11)) for _ in range(12000)]
    inputs, expected = [], []
    try:
        for graph, percent, count in cases:
            native.graph_value = graph
            struct.pack_into('<i', native.actor, 0x274, 19)
            struct.pack_into('<i', native.actor, 0x28c, count)
            for op, function, offsets in [(0, native.damage, (0x330, 0x334, 0x340)),
                                           (1, native.armor, (0x338, 0x33c))]:
                function(c.addressof(native.actor), percent)
                values = [struct.unpack_from('<i', native.actor, offset)[0] for offset in offsets]
                if len(set(values)) != 1: raise AssertionError(('original stores differ', values))
                inputs.append(f'{op} {bits(graph)} {percent} {count}\n')
                expected.append(values[0])
        run = subprocess.run([str(args.probe.resolve())], input=''.join(inputs), text=True,
                             capture_output=True, check=True, timeout=60)
        rows = [tuple(map(int, line.split())) for line in run.stdout.splitlines()]
        actual = [row[0] for row in rows]
        old = [row[1] for row in rows]
        if actual != expected:
            i = next((i for i, pair in enumerate(zip(actual, expected)) if pair[0] != pair[1]), None)
            raise AssertionError({'case': i, 'input': inputs[i] if i is not None else None,
                                  'expected': expected[i] if i is not None else len(expected),
                                  'actual': actual[i] if i is not None else len(actual)})
        differences = [{'input': line.strip(), 'original': e, 'previous_formula': o}
                       for line, e, o in zip(inputs, expected, old) if e != o]
        report = {'original_sha256': original.sha256, 'functions': native.evidence,
                  'comparisons': len(expected), 'damage_cases': len(cases), 'armor_cases': len(cases),
                  'passed': True, 'previous_formula_disagreements': len(differences),
                  'examples': differences[:4],
                  'rounding_examples': [d for d in differences if d['original'] > 0][:16],
                  'rounding_disagreements': sum(d['original'] > 0 for d in differences),
                  'scope': 'Unchanged numeric functions and stores; evaluated graph value/string manager stubbed. No constructors, RNG, full item generation, retirement or requirement lifecycle.',
                  'domain': 'Finite binary32 graph values, nonnegative heirloom count, final result fits int32. uint32 percentage input.'}
        if args.output:
            args.output.parent.mkdir(parents=True, exist_ok=True)
            args.output.write_text(json.dumps(report, indent=2) + '\n')
        print(json.dumps(report, indent=2))
    finally:
        native.close()
    return 0
if __name__ == '__main__': raise SystemExit(main())
