#!/usr/bin/env python3
"""Bounded source selection, cache ownership and headless evidence contracts.

Synthetic ELF views only; no full Ghidra analysis or original game execution.
"""
from __future__ import annotations

import copy
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import prepare_lift_project as prepare
from original import Symbol, SUPPORTED_SHA256


class FakeOriginal:
    sha256 = SUPPORTED_SHA256
    symbols = [Symbol(0x1000, 8, 'T', 'First'), Symbol(0x2000, 8, 'T', 'Second')]
    segments = [(1, 5, 0, 0x1000, 0, 0x10000000, 0x10000000, 0x1000)]

    def read(self, address, size):
        return bytes([address & 255]) * size


def functions(*entries):
    return {address: {'sizes': {size}, 'aliases': {f'Function{address:x}'}}
            for address, size in entries}


class LiftPreparationTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='lift-preparation-', dir='/tmp')
        self.directory = Path(self.temp.name)

    def tearDown(self):
        self.temp.cleanup()

    def test_function_symbols_keep_ambiguous_sizes_and_require_func_type(self):
        rows = '''
  Num:    Value          Size Type    Bind   Vis      Ndx Name
     1: 0000000000001000     8 FUNC    GLOBAL DEFAULT    1 Name
     2: 0000000000001000     8 FUNC    WEAK   DEFAULT    1 Alias
     3: 0000000000001000    16 FUNC    GLOBAL DEFAULT    1 Conflict
     4: 0000000000002000     8 OBJECT  GLOBAL DEFAULT    1 Data
     5: 0000000000003000     0 FUNC    GLOBAL DEFAULT    1 Unsized
     6: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND Import
'''
        parsed = prepare.parse_function_symbols(rows)
        self.assertEqual(parsed[0x1000]['sizes'], {8, 16})
        self.assertEqual(parsed[0x1000]['aliases'], {'Name', 'Alias', 'Conflict'})
        self.assertEqual(parsed[0x3000]['sizes'], set())
        self.assertNotIn(0x2000, parsed)
        self.assertNotIn(0, parsed)
        with self.assertRaisesRegex(ValueError, 'ambiguous exact STT_FUNC'):
            prepare.prepare_request(FakeOriginal(), [0x1000], parsed)

    def test_explicit_target_order_duplicates_and_batch_limit(self):
        path = self.directory / 'targets.txt'
        path.write_text('# exact source starts\n0x2000\n00001000\n')
        self.assertEqual(prepare.read_targets(path), [0x1000, 0x2000])
        path.write_text('0x1000\n00001000\n')
        with self.assertRaisesRegex(ValueError, 'Duplicate normalized'):
            prepare.read_targets(path)
        path.write_text(''.join(f'{n:x}\n' for n in range(1025)))
        with self.assertRaisesRegex(ValueError, '1..1024'):
            prepare.read_targets(path)
        path.write_text('# no targets\n')
        with self.assertRaisesRegex(ValueError, '1..1024'):
            prepare.read_targets(path)

    def test_exact_function_full_symbol_bytes_and_no_inferred_abi(self):
        request = prepare.prepare_request(FakeOriginal(), [0x2000, 0x1000], functions((0x1000, 8), (0x2000, 8)))
        self.assertEqual([r['address'] for r in request['entries']], ['0x00001000', '0x00002000'])
        self.assertEqual(request['selected_symbol_bytes'], 16)
        self.assertEqual(request['entries'][0]['full_symbol_sha256'], hashlib.sha256(bytes(8)).hexdigest())
        self.assertFalse(request['analysis_requested'])
        self.assertFalse(request['decompiler_requested'])
        self.assertEqual(request['original_status_promotions'], 0)
        self.assertNotIn('input_registers', json.dumps(request))
        self.assertNotIn('return_register', json.dumps(request))

    def test_interiors_unknown_unsized_and_overlapping_source_entries_rejected(self):
        for entry in (0x1001, 0x9999):
            with self.subTest(entry=entry), self.assertRaisesRegex(ValueError, 'exact STT_FUNC'):
                prepare.prepare_request(FakeOriginal(), [entry], functions((0x1000, 8)))
        original = FakeOriginal()
        original.symbols = [*original.symbols, Symbol(0x1004, 0, 'T', 'Inside')]
        with self.assertRaisesRegex(ValueError, 'another exact source entry'):
            prepare.prepare_request(original, [0x1000], functions((0x1000, 8)))
        with self.assertRaisesRegex(ValueError, 'exact STT_FUNC'):
            prepare.prepare_request(FakeOriginal(), [0x1000], {0x1000: {'sizes': set(), 'aliases': {'Unsized'}}})

    def test_function_requires_file_backed_executable_memory_and_pinned_elf(self):
        for flags, file_size in ((4, 8), (5, 7)):
            original = FakeOriginal()
            original.segments = [(1, flags, 0, 0x1000, 0, file_size, 8, 0x1000)]
            with self.subTest(flags=flags, file_size=file_size), self.assertRaisesRegex(ValueError, 'file-backed executable'):
                prepare.prepare_request(original, [0x1000], functions((0x1000, 8)))
        original = FakeOriginal()
        original.sha256 = 'f' * 64
        with self.assertRaisesRegex(ValueError, 'ELF identity'):
            prepare.prepare_request(original, [0x1000], functions((0x1000, 8)))

    def test_byte_budgets_are_explicit_and_never_truncate(self):
        original = FakeOriginal()
        original.symbols = []
        with self.assertRaisesRegex(ValueError, 'Function span'):
            prepare.prepare_request(original, [0x1000], functions((0x1000, (1 << 20) + 1)))
        entries = [(0x1000 + n * (2 << 20), 1 << 20) for n in range(9)]
        with self.assertRaisesRegex(ValueError, 'batch limit'):
            prepare.prepare_request(original, [a for a, _ in entries], functions(*entries))

    def test_owned_cache_extension_preserves_unrelated_or_partial_projects(self):
        root = self.directory / 'cache'
        self.assertEqual(prepare.project_mode(root), ('import', None))
        project = root / 'project'
        project.mkdir(parents=True)
        gpr = project / 'OpenTorchlight.gpr'
        gpr.write_text('preserve this database')
        with self.assertRaisesRegex(ValueError, 'verified owned bounded cache'):
            prepare.project_mode(root)
        (project / 'OpenTorchlight.rep').mkdir()
        marker = {'schema': 1, 'kind': 'bounded-lift-project', 'original_elf_sha256': SUPPORTED_SHA256,
                  'ghidra_version': prepare.VERSION, 'project_path': str(gpr.resolve()),
                  'analysis_requested': False, 'decompiler_requested': False}
        (root / prepare.MARKER_NAME).write_text(json.dumps(marker))
        self.assertEqual(prepare.project_mode(root), ('extend', marker))
        self.assertEqual(gpr.read_text(), 'preserve this database')
        gpr.unlink()
        with self.assertRaisesRegex(ValueError, 'Partial/unowned project'):
            prepare.project_mode(root)

    def test_command_separates_mutable_preparation_from_readonly_export(self):
        original = Path('/original/Torchlight.bin.x86_64')
        command = prepare.preparation_command(self.directory / 'tool', self.directory / 'cache',
            original, self.directory / 'request.json', self.directory / 'result.json', 'import')
        self.assertIn('-noanalysis', command)
        self.assertNotIn('-readOnly', command)
        self.assertNotIn('-overwrite', command)
        self.assertNotIn('ExportLiftBatch.java', command)
        self.assertEqual(command[command.index('-loader-applyRelocations') + 1], 'false')
        self.assertEqual(command[command.index('-loader-loadLibraries') + 1], 'false')
        self.assertEqual(command[command.index('-postScript') + 1], 'PrepareLiftEntries.java')
        extend = prepare.preparation_command(self.directory / 'tool', self.directory / 'cache',
            original, self.directory / 'request.json', self.directory / 'result.json', 'extend')
        self.assertIn('-process', extend)
        self.assertNotIn('-import', extend)
        self.assertNotIn('-overwrite', extend)

    def test_launcher_success_is_not_sufficient_evidence(self):
        request = prepare.prepare_request(FakeOriginal(), [0x1000], functions((0x1000, 8)))
        row = {**request['entries'][0], 'instructions': 1, 'instruction_bytes': 7}
        good = {'schema': 1, 'kind': 'bounded-lift-preparation-result', 'status': 'PREPARED',
                'request_sha256': 'a' * 64, 'original_elf_sha256': SUPPORTED_SHA256,
                'ghidra_version': prepare.VERSION, 'language': request['language'],
                'analysis_requested': False, 'decompiler_requested': False,
                'program_bytes_modified': False, 'game_executed': False, 'entries': [row]}
        prepare.verify_result(good, request, 'a' * 64)
        cases = []
        for field, value in (('request_sha256', 'b' * 64), ('analysis_requested', True),
                             ('program_bytes_modified', True), ('entries', [])):
            bad = copy.deepcopy(good)
            bad[field] = value
            cases.append(bad)
        bad = copy.deepcopy(good)
        bad['entries'][0]['size'] = 9
        cases.append(bad)
        bad = copy.deepcopy(good)
        bad['entries'][0]['full_symbol_sha256'] = 'c' * 64
        cases.append(bad)
        for bad in cases:
            with self.subTest(result=bad), self.assertRaises(ValueError):
                prepare.verify_result(bad, request, 'a' * 64)


if __name__ == '__main__':
    unittest.main()
