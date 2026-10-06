#!/usr/bin/env python3
"""Reproduce cross-TU prototype cache invalidation without the ELF or GCC.

Usage: python3 probe_draft_invalidation.py /path/to/OpenTorchlight
Uses only temporary files. It does not modify project code or call an LLM.
A 'fresh' result after changing the callee confirms the tested limitation;
it is not an integration test of Ghidra or the original game.
"""
from __future__ import annotations
import argparse
import importlib
import json
import sys
import tempfile
from pathlib import Path
from unittest.mock import patch


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('repo', type=Path)
    args = parser.parse_args()
    tools = args.repo.resolve() / 'tools' / 'decomp'
    if not (tools / 'ghidra_draft.py').is_file():
        parser.error('tools/decomp/ghidra_draft.py was not found under repo')
    sys.path.insert(0, str(tools))
    module = importlib.import_module('ghidra_draft')
    original = {
        '0x1000': {'name': 'A::caller()', 'ret': 'int'},
        '0x2000': {'name': 'B::callee()', 'ret': 'int'},
    }
    db = {
        'original_elf_sha256': 'synthetic-input-not-a-game-binary',
        'tus': [{'id': 1, 'name': 'A.cpp'}, {'id': 2, 'name': 'B.cpp'}],
        'functions': {'0x1000': {'tu': 1}, '0x2000': {'tu': 2}},
    }
    # A's existing draft is assumed to call B::callee. The current metadata
    # only fingerprints its own methods, not the called prototype.
    with tempfile.TemporaryDirectory(prefix='otl-invalidation-probe-') as tmp:
        folder = Path(tmp)
        (folder / 'A.cpp').mkdir()
        metadata = {
            'elf': db['original_elf_sha256'], 'tools': module.tools_digest(),
            'prototypes': module.prototype_digest(original, ['0x1000']),
            'classes': {},
        }
        (folder / 'A.cpp' / 'inputs.json').write_text(json.dumps(metadata))
        results = {}
        for label, prototypes in [
            ('unchanged', original),
            ('callee_return_changed', {**original, '0x2000': {'name': 'B::callee()', 'ret': 'float'}}),
            ('own_return_changed', {**original, '0x1000': {'name': 'A::caller()', 'ret': 'float'}}),
        ]:
            with patch.object(module, 'OUT', folder), patch.object(module, '_prototypes', return_value=prototypes):
                state, reasons = module.draft_state('A.cpp', db=db, types={})
                results[label] = {'state': state, 'reasons': reasons}
        print(json.dumps(results, indent=2))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
