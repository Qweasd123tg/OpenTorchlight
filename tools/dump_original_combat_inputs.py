#!/usr/bin/env python3
"""Read only the missing ordinary-combat constants/path from the pinned original ELF.

This does not execute the game, write the installation, or export whole functions.
A matching SHA is mandatory. Results are evidence for review, not automatic runtime overrides.
"""
from __future__ import annotations
import argparse
import hashlib
import json
import math
from pathlib import Path
import struct
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tests'))
from verify_original_entry_dispatch import ELF_SHA256, virtual_bytes

FLOATS = {
    'speed_one': 0xFA47FC,
    'percentage_divisor': 0xFA483C,
    'minimum_attack_speed': 0xFA86E8,
    'innate_attack_range_default': 0xFCE4F8,
    'innate_strike_range_default': 0xFA4810,
    'melee_vertical_cutoff': 0xFCE4C4,
    'ai_flag_one_speed_multiplier': 0xFCE498,
}


def extract(image: bytes) -> dict:
    digest = hashlib.sha256(image).hexdigest()
    if digest != ELF_SHA256:
        raise ValueError(f'ELF SHA-256 mismatch: {digest}')
    constants = {}
    for name, address in FLOATS.items():
        raw = virtual_bytes(image, address, 4)
        value = struct.unpack('<f', raw)[0]
        if not math.isfinite(value):
            raise ValueError(f'Nonfinite constant at 0x{address:x}')
        constants[name] = {'address': hex(address), 'bytes_le': raw.hex(), 'float32': value}
    address = 0xFF82C8
    data = bytearray()
    for index in range(512):
        raw = virtual_bytes(image, address + 4 * index, 4)
        if raw == b'\0' * 4:
            break
        data.extend(raw)
    else:
        raise ValueError('Effect catalog path exceeds bounded UTF-32 read')
    path = data.decode('utf-32-le', errors='strict')
    if not path:
        raise ValueError('Empty effect catalog path')
    return {'elf_sha256': digest, 'mode': 'read-only static data, no execution',
            'constants': constants,
            'effect_catalog_path': {'address': hex(address), 'utf32le_text': path}}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--original', type=Path, required=True)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    try:
        if args.output and (args.output.resolve() == args.original.resolve() or
                            (args.output.exists() and args.original.samefile(args.output))):
            raise ValueError('output must not overwrite ELF')
        result = extract(args.original.read_bytes())
        rendered = json.dumps(result, ensure_ascii=False, indent=2, allow_nan=False) + '\n'
        if args.output:
            args.output.write_text(rendered, encoding='utf-8')
        else:
            print(rendered, end='')
    except (OSError, ValueError, UnicodeError, struct.error) as error:
        parser.exit(1, f'FAIL: {error}\n')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
