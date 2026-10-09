"""Compile-only vtable and RTTI checks for newly introduced partial classes.

MATCH of a destructor's instructions alone does not check the contents of its
vtable. Require the entire original slot list, the RTTI link and base metadata.
This narrow validator supports one public non-virtual base at offset zero.
"""
import hashlib
import json
from pathlib import Path
import struct

import elfimage
import toolchain


def check_object(obj, cls, original):
    name = cls['name']
    encoded = str(len(name)) + name
    if '::' in name:
        raise ValueError('vtable check only supports unscoped class names')
    original_class = original.db['classes'][name]
    bases = original_class['bases']
    if len(bases) != 1 or bases[0] != {'class': cls['base'], 'external': True, 'offset': 0, 'public': True, 'virtual': False}:
        raise ValueError('original RTTI base is outside the supported layout')
    original_table = original.db['vtables'][name]
    if len(original_table['groups']) != 1 or original_table['groups'][0]['offset_to_top'] != 0:
        raise ValueError('multiple or adjusted vtable group is unsupported')
    def symbol(mangled):
        rows = [s for s in obj.symbols if s.defined and s.name == mangled]
        if len(rows) != 1:
            raise ValueError('missing/ambiguous emitted metadata: ' + mangled)
        return rows[0]
    table = symbol('_ZTV' + encoded)
    if table.size != original_table['size']:
        raise ValueError('vtable size differs from original')
    data = obj.section_bytes(table.shndx)[table.value:table.value + table.size]
    if len(data) != table.size or any(data):
        raise ValueError('nonzero or truncated unrelocated vtable bytes')
    relocs = {r.offset - table.value: r for r in obj.relocs.get(table.shndx, [])
              if table.value <= r.offset < table.value + table.size}
    slots = original_table['groups'][0]['slots']
    if set(relocs) != {8} | {16 + 8 * i for i in range(len(slots))}:
        raise ValueError('vtable relocation shape differs')
    if any(r.type != elfimage.R_X86_64_64 or r.addend for r in relocs.values()):
        raise ValueError('unsupported vtable relocation')
    if relocs[8].symbol.name != '_ZTI' + encoded:
        raise ValueError('vtable refers to the wrong RTTI')
    checked_slots = []
    for i, expected in enumerate(slots):
        mangled = relocs[16 + 8 * i].symbol.name
        f = original.function(mangled)
        address = f['address'] if f else mangled
        if address != expected:
            raise ValueError('vtable method slot differs: ' + mangled)
        checked_slots.append({'index': i, 'symbol': mangled, 'original': address})
    rtti = symbol('_ZTI' + encoded)
    if rtti.size != 24:
        raise ValueError('single-base RTTI size differs')
    refs = {r.offset - rtti.value: r for r in obj.relocs.get(rtti.shndx, [])
            if rtti.value <= r.offset < rtti.value + rtti.size}
    expected_names = {0: '_ZTVN10__cxxabiv120__si_class_type_infoE', 8: '_ZTS' + encoded,
                      16: '_ZTI' + str(len(cls['base'])) + cls['base']}
    if set(refs) != set(expected_names):
        raise ValueError('RTTI relocation shape differs')
    for offset, mangled in expected_names.items():
        r = refs[offset]
        if r.type != elfimage.R_X86_64_64 or r.symbol.name != mangled or r.addend != (16 if offset == 0 else 0):
            raise ValueError('RTTI class/base link differs')
    type_name = symbol('_ZTS' + encoded)
    spelling = obj.section_bytes(type_name.shndx)[type_name.value:type_name.value + type_name.size]
    if spelling != encoded.encode() + b'\0':
        raise ValueError('RTTI class name differs')
    return {'class': name, 'status': 'PASS', 'vtable_bytes': table.size, 'slots': checked_slots,
            'base': cls['base'], 'base_offset': 0, 'rtti_bytes': rtti.size}


def verify(original, manifest, candidates, output):
    output = Path(output); output.mkdir(parents=True, exist_ok=True)
    result = []
    for cls in manifest['classes']:
        if not cls.get('new_header'):
            continue
        # The reviewed first member witness belongs to this class's own TU.
        witness = cls['members'][0]['witnesses'][0]
        f = original.db['functions'][witness['function']]
        tu = next(t['name'] for t in original.db['tus'] if t['id'] == f['tu'])
        source = Path(candidates) / tu
        if not source.is_file():
            raise ValueError('new class has no accepted complete TU for vtable checking')
        path = output / (tu + '.o')
        toolchain.compile_source(source.resolve(), path.resolve(), quiet=True)
        row = check_object(elfimage.load_object(path), cls, original)
        row['object_sha256'] = hashlib.sha256(path.read_bytes()).hexdigest()
        result.append(row)
    (output / 'vtable-check.json').write_text(json.dumps(result, indent=2) + '\n')
    return result
