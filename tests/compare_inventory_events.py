#!/usr/bin/env python3
"""Unchanged inventory mapper/tab machine code with explicit CEGUI call adapters.

Not a CEGUI runtime/unwinding or complete createMenus/updateLayout comparison.
"""
from __future__ import annotations
import argparse
import ctypes as c
import hashlib
import json
from pathlib import Path
import platform
import random
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from original import Original
from automation_state import validate_output, write_json
from native_typed_reference import Memory

MAPPER, CLICK = 0xB4F1B0, 0xB4F570


class NativeInventory(Memory):
    def __init__(self, original):
        super().__init__()
        try:
            self.owners, self.trace, self.errors = [], [], []
            self.put(MAPPER, original.read(MAPPER, 0x3B2))
            self.put(CLICK, original.read(CLICK, 0x451))
            self.put(0xFE4840, original.read(0xFE4840, 8))
            self.put(0xFEF75C, original.read(0xFEF75C, 16))
            cf = c.CFUNCTYPE

            def allocate(size):
                buf = c.create_string_buffer(size)
                self.owners.append(buf)
                return c.addressof(buf)

            def check_key(key, expected):
                length = c.c_uint64.from_address(key).value
                got = ''.join(chr(c.c_uint32.from_address(key + 0x28 + 4*i).value)
                              for i in range(min(length, 32)))
                if got != expected:
                    self.errors.append(('key', got, expected))

            def present(window, key):
                check_key(key, 'onClick')
                self.trace.append(['present', self.windows[window]])
                return self.properties[window] is not None

            def get(out, window, key):
                check_key(key, 'onClick')
                self.trace.append(['get', self.windows[window]])
                c.c_uint64.from_address(out).value = len(self.properties[window])
                return out

            def subscribe(out, eventset, event, subscriber):
                slot = c.c_void_p.from_address(subscriber).value
                words = struct.unpack('<4Q', c.string_at(slot, 32))
                if event != 0x14247E0 or words != (0xFEFCD0, 0x59, 0, self.menu_address):
                    self.errors.append(('subscriber', event, words))
                self.trace.append(['subscribe', self.windows[eventset - 0x38]])
                # Explicit null connection fixture; ref-count/destructor ownership open.
                c.memset(out, 0, 16)

            def selected(window, value):
                self.trace.append(['selected', window - 1, bool(value)])

            def visible(window, value):
                self.trace.append(['visible', window - 4, bool(value)])

            def restore(window, key, value):
                check_key(key, 'UnselectedImage')
                index = window - 1
                if value != self.menu_address + 0x91B0 + 0xB0*index:
                    self.errors.append(('saved-image', value))
                # The flag write occurs before setProperty, not in the callback.
                self.trace.append(['alert', index,
                                   bool(c.c_ubyte.from_address(self.menu_address+0x91A8+index).value)])
                self.trace.append(['restore', index])

            self.callback(0x5558F8, cf(None, c.c_void_p, c.c_size_t), lambda p,n: None)
            self.callback(0x555FE8, cf(None, c.c_void_p), lambda p: None)
            self.callback(0x553E18, cf(c.c_bool, c.c_void_p, c.c_void_p), present)
            self.callback(0x554418, cf(c.c_void_p, c.c_void_p, c.c_void_p, c.c_void_p), get)
            self.callback(0x552D68, cf(c.c_void_p, c.c_size_t), allocate)
            self.callback(0x554B78, cf(None, c.c_void_p), lambda p: None)
            self.callback(0x20000100, cf(None, c.c_void_p, c.c_void_p, c.c_void_p, c.c_void_p), subscribe)
            self.callback(0x554DC8, cf(None, c.c_size_t, c.c_bool), selected)
            self.callback(0x554718, cf(None, c.c_size_t, c.c_bool), visible)
            self.callback(0x5532D8, cf(None, c.c_size_t, c.c_void_p, c.c_void_p), restore)
            self.callback(0x20000200, cf(None, c.c_void_p), lambda p: self.trace.append(['update']))
            self.protect()
            self.map = cf(None, c.c_void_p, c.c_void_p)(MAPPER)
            self.click = cf(c.c_uint64, c.c_void_p, c.c_int)(CLICK)
        except BaseException:
            self.close()
            raise

    def reset(self):
        self.owners, self.trace, self.errors = [], [], []
        menu = c.create_string_buffer(0x9400)
        self.owners.append(menu)
        self.menu_address = c.addressof(menu)
        return menu

    def mapping(self, rows):
        self.reset()
        vtable = (c.c_void_p * 3)(0, 0, 0x20000100)
        nodes = [c.create_string_buffer(0x1E0) for _ in rows]
        addresses = [c.addressof(n) for n in nodes]
        self.windows = {p:i for i,p in enumerate(addresses)}
        self.properties = {p:rows[i][1] for i,p in enumerate(addresses)}
        for i, node in enumerate(nodes):
            children = [addresses[j] for j,r in enumerate(rows) if r[0] == i]
            array = (c.c_void_p * max(1, len(children)))(*children)
            self.owners.append(array)
            struct.pack_into('<Q', node, 0x38, c.addressof(vtable))
            struct.pack_into('<QQ', node, 0x78, c.addressof(array), c.addressof(array)+8*len(children))
        for i, row in enumerate(rows):
            if row[0] == -1:
                self.map(self.menu_address, addresses[i])
        if self.errors:
            raise AssertionError(self.errors)
        return self.trace[:]

    def tab(self, opened, command):
        menu = self.reset()
        vtable = (c.c_void_p * 10)(*([0]*9 + [0x20000200]))
        struct.pack_into('<Q', menu, 0, c.addressof(vtable))
        menu[0x60] = bytes([opened])
        for i in range(3):
            struct.pack_into('<Q', menu, 0x9120+8*i, i+1)
            struct.pack_into('<Q', menu, 0x9108+8*i, i+4)
            menu[0x91A8+i] = b'\1'
        result = self.click(self.menu_address, command)
        if result != 1 or self.errors:
            raise AssertionError((result, self.errors))
        return self.trace[:]


def mapping_cases():
    values = [None, b'', b'guiSelect1', b'unknown', b'\0', b' ']
    yield [(-1,v) for v in values]
    rng = random.Random(MAPPER)
    for _ in range(80):
        yield [(rng.randrange(-1,i) if i else -1,rng.choice(values)) for i in range(24)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--original', type=Path, required=True)
    p.add_argument('--probe', type=Path)
    p.add_argument('--output', type=Path, required=True)
    a = p.parse_args()
    validate_output(ROOT, a.output, [a.original, *([a.probe] if a.probe else [])])
    if platform.machine() != 'x86_64': return 77
    original = Original(a.original)
    native = NativeInventory(original)
    try:
        trees = list(mapping_cases())
        tab_cases = [(opened,command) for opened in (0,1) for command in range(-1,98)]
        expected = [native.mapping(rows) for rows in trees]
        expected += [native.tab(*row) for row in tab_cases]
        if native.tab(0,14) or len(native.tab(1,14)) != 9:
            raise AssertionError('native sanity failed')
        if a.probe:
            lines = []
            for rows in trees:
                lines.append(f'map {len(rows)}')
                lines += [f'{parent} {"_" if prop is None else prop.hex() or "-"}' for parent,prop in rows]
            lines += [f'tab {opened} {command}' for opened,command in tab_cases]
            out = subprocess.check_output([str(a.probe),'--probe'],input='\n'.join(lines)+'\n',text=True)
            observed = [json.loads(line) for line in out.splitlines()]
            if len(observed) != len(expected): raise AssertionError('case count differs')
            for i,(got,want) in enumerate(zip(observed,expected)):
                if got != want: raise AssertionError(f'case {i}: {got!r} != {want!r}')
        write_json(a.output, {'elf_sha256':original.sha256,'mapping_trees':len(trees),
                   'mapping_nodes':sum(map(len,trees)), 'tab_cases':len(tab_cases),
                   'compared_with_port': bool(a.probe),
                   'bodies': {hex(addr):hashlib.sha256(original.read(addr,size)).hexdigest()
                              for addr,size in [(MAPPER,0x3B2),(CLICK,0x451)]},
                   'boundary':'Unchanged bodies; synthetic CEGUI/property/subscription/updateLayout calls. No native exceptions, library ownership or full layout update.'})
        print(f'PASS: {len(trees)} trees, {len(tab_cases)} tab cases; compared={bool(a.probe)}')
        return 0
    finally:
        native.close()

if __name__ == '__main__': raise SystemExit(main())
