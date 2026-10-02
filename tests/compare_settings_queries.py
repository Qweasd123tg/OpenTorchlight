#!/usr/bin/env python3
"""Compare generated GetInt/default double-click with unchanged whole bodies.

Settings/vector owners are initialized synthetic buffers with observed guards.
The default method's this/enum/name operands are unused in its complete body;
opaque pointer fixtures do not construct a wstring or establish its ABI.
No settings registration, constructors, callbacks, original game or UI is run.
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
from automation_state import validate_output, write_json
from original import Original
from native_typed_reference import Memory

GET_INT = 0xC6E440
DEFAULT_DOUBLE_CLICK = 0xB05E80
ENTRIES = ((GET_INT, 32), (DEFAULT_DOUBLE_CLICK, 6))
U32_MASK = 0xFFFFFFFF
GUARD_BYTES = 16
SETTINGS_BYTES = 0x80
OPAQUE_BYTES = 0x100


def accepted_sources(original):
    sources, bodies = [], []
    for address, size in ENTRIES:
        symbols = {symbol for symbol in original.symbols
                   if symbol.address == address and symbol.size and symbol.kind in 'TtWw'}
        if len(symbols) != 1 or next(iter(symbols)).size != size:
            raise ValueError(f'original whole symbol size/identity drifted: {address:#x}')
        symbol = next(iter(symbols))
        body = original.read(address, size)
        path = ROOT / 'research/lifted-ui' / f'{address:08x}.json'
        raw = path.read_bytes()
        data = json.loads(raw)
        body_hash = hashlib.sha256(body).hexdigest()
        if (data.get('schema') != 2 or data.get('original_elf_sha256') != original.sha256 or
                int(data['address'], 16) != address or data.get('original_symbol_size') != size or
                data.get('original_symbol_body_sha256') != body_hash):
            raise ValueError(f'accepted source/whole symbol differs: {address:#x}')
        instructions = data.get('instructions')
        if not isinstance(instructions, list) or not instructions:
            raise ValueError(f'accepted raw instructions absent: {address:#x}')
        covered, instruction_hash = set(), hashlib.sha256()
        for row in instructions:
            start, encoded = int(row['address'], 16), bytes.fromhex(row['bytes'])
            if not encoded or start < address or start + len(encoded) > address + size:
                raise ValueError(f'accepted instruction outside complete body: {row["address"]}')
            span = set(range(start, start + len(encoded)))
            if covered & span or original.read(start, len(encoded)) != encoded:
                raise ValueError(f'accepted instruction overlap/byte drift: {row["address"]}')
            covered |= span
            instruction_hash.update(row['address'].encode())
            instruction_hash.update(encoded)
        if covered != set(range(address, address + size)):
            raise ValueError(f'accepted whole executable body has missing bytes: {address:#x}')
        if instruction_hash.hexdigest() != data.get('address_and_instruction_bytes_sha256'):
            raise ValueError(f'accepted instruction hash differs: {address:#x}')
        sources.append(dict(path=str(path.relative_to(ROOT)), sha256=hashlib.sha256(raw).hexdigest()))
        bodies.append(dict(address=hex(address), symbol=symbol.name, size=size, sha256=body_hash))
    return sources, bodies


class Native(Memory):
    def __init__(self, original):
        super().__init__()
        try:
            for address, size in ENTRIES:
                self.put(address, original.read(address, size))
            self.protect()
            self.get = c.CFUNCTYPE(c.c_uint32, c.c_void_p, c.c_uint32)(GET_INT)
            self.default = c.CFUNCTYPE(c.c_uint32, c.c_void_p, c.c_uint32, c.c_void_p)(DEFAULT_DOUBLE_CLICK)
        except BaseException:
            self.close()
            raise

    def property(self, values, index, rng):
        vector_raw = bytearray(rng.randbytes(2 * GUARD_BYTES + 4 * len(values)))
        for i, bits in enumerate(values):
            struct.pack_into('<I', vector_raw, GUARD_BYTES + 4 * i, bits)
        vector = c.create_string_buffer(bytes(vector_raw), len(vector_raw))
        owner_raw = bytearray(rng.randbytes(2 * GUARD_BYTES + SETTINGS_BYTES))
        begin = c.addressof(vector) + GUARD_BYTES
        # GetInt's separate int-vector fields, not GetFloat's +0x58/+0x60.
        struct.pack_into('<QQ', owner_raw, GUARD_BYTES + 0x40, begin, begin + 4 * len(values))
        owner = c.create_string_buffer(bytes(owner_raw), len(owner_raw))
        before = bytes(owner), bytes(vector)
        answer = self.get(c.addressof(owner) + GUARD_BYTES, index)
        if before != (bytes(owner), bytes(vector)):
            raise AssertionError(f'original GetInt changed full owner/vector/guards: count={len(values)}, index={index}')
        expected_bits = values[index] if index < len(values) else U32_MASK
        if answer != expected_bits:
            raise AssertionError('original GetInt differs from recovered load/fallback contract')
        return int(answer)

    def double_click(self, function, pointer_mode, rng):
        owner = c.create_string_buffer(rng.randbytes(2 * GUARD_BYTES + OPAQUE_BYTES),
                                       2 * GUARD_BYTES + OPAQUE_BYTES)
        name = c.create_string_buffer(rng.randbytes(2 * GUARD_BYTES + OPAQUE_BYTES),
                                      2 * GUARD_BYTES + OPAQUE_BYTES)
        before = bytes(owner), bytes(name)
        operands = ((c.addressof(owner) + GUARD_BYTES, c.addressof(name) + GUARD_BYTES),
                    (None, None), (1, 0xFFFFFFFFFFFFFFFF))
        this_pointer, name_pointer = operands[pointer_mode]
        answer = self.default(this_pointer, function, name_pointer)
        if before != (bytes(owner), bytes(name)):
            raise AssertionError('original default double-click changed opaque argument buffers/guards')
        if answer != 1:
            raise AssertionError('original whole default double-click does not return EAX=1')
        return int(answer)


def cases():
    rng = random.Random(GET_INT)
    edges = [0, 1, 2, 0x7FFFFFFE, 0x7FFFFFFF, 0x80000000,
             0x80000001, 0xFFFFFFFE, 0xFFFFFFFF, 0x12345678, 0xAAAAAAAA, 0x55555555]
    properties = []
    for count in (0, 1, 2, 3, 7, 17, 32, 64):
        values = [edges[i % len(edges)] for i in range(count)]
        indices = {0, 1, 2, max(0, count - 1), count, count + 1,
                   0x7FFFFFFF, 0x80000000, 0xFFFFFFFF} | set(range(count))
        properties += [(values, index, 'count_and_index_edges') for index in sorted(indices)]
    properties += [([bits], index, 'int32_bit_edges') for bits in edges
                   for index in (0, 1, 0xFFFFFFFF)]
    for i in range(2048):
        values = [rng.getrandbits(32) for _ in range(rng.randrange(65))]
        index = (rng.randrange(len(values) + 1) if i % 2 else rng.getrandbits(32))
        properties.append((values, index, 'random_int32_bits'))
    functions = (0, 1, 2, 14, 17, 18, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF)
    functions += tuple(rng.getrandbits(32) for _ in range(64))
    defaults = [(function, mode) for function in functions for mode in range(3)]
    return properties, defaults


def compare(original, probe):
    sources, bodies = accepted_sources(original)
    properties, defaults = cases()
    payload, expected, labels = [], [], []
    rng = random.Random(DEFAULT_DOUBLE_CLICK)
    native = Native(original)
    try:
        for values, index, kind in properties:
            payload.append('g ' + str(len(values)) + ' ' + str(index) + ' ' +
                           ' '.join(map(str, values)) + '\n')
            expected.append(native.property(values, index, rng))
            labels.append(dict(operation='GetInt', count=len(values), index=index,
                               values_bits=[hex(bits) for bits in values], kind=kind))
        for function, mode in defaults:
            payload.append('d\n')
            expected.append(native.double_click(function, mode, rng))
            labels.append(dict(operation='default_double_click', function_bits=hex(function),
                               ignored_pointer_mode=mode))
        result = subprocess.run([str(probe.resolve())], input=''.join(payload),
                                text=True, capture_output=True, check=True, timeout=60)
        actual = [int(line) for line in result.stdout.splitlines()]
        if len(actual) != len(expected) or any(not 0 <= bits <= U32_MASK for bits in actual):
            raise ValueError('production probe count or raw uint32 output domain differs')
        mismatches = [dict(case=i, **labels[i], original_bits=hex(want), production_bits=hex(got))
                      for i, (want, got) in enumerate(zip(expected, actual)) if want != got]
        return dict(schema=1, kind='original-settings-queries-comparison',
                    status='FAIL' if mismatches else 'PASS', cases=len(expected),
                    property_cases=len(properties), default_double_click_cases=len(defaults),
                    in_range_property_cases=sum(index < len(values) for values, index, _ in properties),
                    fallback_property_cases=sum(index >= len(values) for values, index, _ in properties),
                    mismatch_count=len(mismatches), mismatches=mismatches,
                    whole_original_bodies=bodies, original_elf_sha256=original.sha256,
                    accepted_instruction_inputs=sources,
                    observed_buffers=dict(settings_owner_bytes=SETTINGS_BYTES,
                                          settings_guards_bytes=2 * GUARD_BYTES,
                                          vector_element_width=4, vector_guards_bytes=2 * GUARD_BYTES,
                                          default_opaque_arguments_bytes=2 * OPAQUE_BYTES,
                                          default_argument_guards_bytes=4 * GUARD_BYTES,
                                          observation='every initialized fixture byte after each call'),
                    scope=__doc__, original_status_promotions=0, game_executed=False,
                    original_modified=False)
    finally:
        native.close()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('original', 'probe', 'output'):
        parser.add_argument('--' + name, type=Path, required=True)
    args = parser.parse_args()
    if platform.system() != 'Linux' or platform.machine() != 'x86_64':
        return 77
    validate_output(ROOT, args.output, [args.original, args.probe])
    report = compare(Original(args.original), args.probe)
    write_json(args.output, report)
    print(f'{report["status"]}: {report["cases"]} cases '
          f'({report["property_cases"]} GetInt, {report["default_double_click_cases"]} default double-click), '
          f'{report["mismatch_count"]} raw-bit mismatches; complete guarded fixtures unchanged')
    return 0 if report['status'] == 'PASS' else 1


if __name__ == '__main__':
    raise SystemExit(main())
