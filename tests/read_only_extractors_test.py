#!/usr/bin/env python3
"""Test source-write protection and bounded readers using ONLY authored inputs.
This does not pretend that a synthetic file has the pinned original ELF hash.
"""
from __future__ import annotations
import importlib.util
import os
from pathlib import Path
import subprocess
import sys
import tempfile
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
checks = 0


def require(condition: bool, message: str) -> None:
    global checks
    checks += 1
    if not condition:
        raise AssertionError(message)


def main() -> None:
    scripts = [ROOT/'tools/dump_original_combat_inputs.py',
               ROOT/'tools/dump_original_gameplay_inputs.py']
    with tempfile.TemporaryDirectory() as temp:
        directory = Path(temp)
        original = directory/'authored-not-an-elf'
        data = b'Authored negative test; never an original executable.\0'
        original.write_bytes(data)
        symlink = directory/'link'
        symlink.symlink_to(original)
        hardlink = directory/'hardlink'
        os.link(original, hardlink)
        for script in scripts:
            for target in (original, symlink, hardlink):
                result = subprocess.run([sys.executable, str(script), '--original', str(original),
                    '--output', str(target)], capture_output=True, text=True, timeout=10)
                require(result.returncode != 0 and 'must not overwrite ELF' in result.stderr,
                        'same source through direct/symbolic/hard link was not rejected')
                require(original.read_bytes() == data, 'source was overwritten')
            target = directory/'new-output.json'
            result = subprocess.run([sys.executable, str(script), '--original', str(original),
                '--output', str(target)], capture_output=True, text=True, timeout=10)
            require(result.returncode != 0 and 'SHA-256 mismatch' in result.stderr,
                    'unpinned source accepted')
            require(not target.exists() and original.read_bytes() == data,
                    'hash rejection modified input/output')

    spec = importlib.util.spec_from_file_location('gameplay_dump', scripts[1])
    if spec is None or spec.loader is None:
        raise RuntimeError('cannot import bounded reader')
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    def read(data: bytes, address: int, size: int) -> bytes:
        if address < 0 or address + size > len(data):
            raise ValueError('outside authored virtual segment')
        return data[address:address + size]
    with patch.object(module, 'virtual_bytes', read):
        require(module.wide_string('MANA\0'.encode('utf-32-le'), 0) == 'MANA', 'UTF32 decode')
        for bad in (b'\0'*4, b'\xff\xff\xff\xff\0\0\0\0', b'\x41\0',
                    ('A'*256).encode('utf-32-le')):
            rejected = False
            try:
                module.wide_string(bad, 0)
            except (ValueError, UnicodeError):
                rejected = True
            require(rejected, 'empty/invalid/truncated/unbounded string accepted')
    print(f'PASS: {checks} read-only extractor assertions; synthetic files only, no original execution')


if __name__ == '__main__':
    main()
