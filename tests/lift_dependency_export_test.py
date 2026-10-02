#!/usr/bin/env python3
"""Explicit dependency selection and graph reuse, without Ghidra/game execution."""
from __future__ import annotations

import copy
from contextlib import redirect_stderr, redirect_stdout
import hashlib
import io
import json
from pathlib import Path
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest import mock

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import screen_function_lifts as screening
from original import Symbol
from transfer_contract import REVIEW_AREAS, STAGES


class ExplicitDependencySelectionTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='lift-dependency-export-', dir='/tmp')
        self.root = Path(self.temp.name)
        for directory in ('research', 'tools', 'src', 'tests'):
            (self.root / directory).mkdir()
        self.write('tools/function_package.py', '# fixture index reader identity\n')
        self.write('research/original-symbols.txt',
                   '00001000 00000002 T CMainMenu::first()\n'
                   '00002000 00000002 W Ogre::Vector3::normalise()\n'
                   '00003000 00000002 T CMainMenu::accepted()\n'
                   '00004000 00000002 t COutsideContour::dependency()\n'
                   '00005000 T CMainMenu::unsized()\n')
        self.write('research/coverage.tsv', 'address\tsymbol\tsubsystem\tstatus\n'
                   '0x00001000\tCMainMenu::first()\tfrontend\tpartial\n'
                   '0x00002000\tOgre::Vector3::normalise()\tother\tpartial\n'
                   '0x00003000\tCMainMenu::accepted()\tfrontend\tclosed\n')
        self.write('research/original-callgraph.tsv',
                   'caller_address\tcaller_symbol\tcallee_address\tcallee_symbol\n')
        self.write('research/ui-contour.json', json.dumps({
            'original_elf_sha256': screening.ELF_SHA,
            'entry_addresses': [], 'class_prefixes': ['CMainMenu']}))
        self.write('src/accepted.cpp', '// fixture production\n')
        self.write('tests/accepted.cpp', '// fixture comparison\n')
        pins = {relative: screening.digest(self.root / relative)
                for relative in ('src/accepted.cpp', 'tests/accepted.cpp')}
        self.write('research/function-transfer.json', json.dumps({'functions': {
            '0x3000': {'stages': {stage: True for stage in STAGES}, 'completion': {
                'status': 'full', 'open_items': [], 'inputs': pins,
                'review': {area: 'fixture explicit whole-contract review' for area in REVIEW_AREAS}}}}}))
        self.targets = self.root / 'targets.txt'

    def tearDown(self):
        self.temp.cleanup()

    def write(self, relative, value):
        (self.root / relative).write_text(value, encoding='utf-8')

    def select(self, text, limit=4):
        self.targets.write_text(text, encoding='utf-8')
        return screening.select_explicit(self.root, self.targets, limit)

    def test_dependency_export_retains_full_nonmanual_and_unregistered_symbols(self):
        residual, _ = screening.select(self.root, 'all', 4)
        self.assertEqual([row['address'] for row in residual['selected']], ['0x00001000'])
        exclusions = {row['address']: row['screening_status'] for row in residual['excluded']}
        self.assertEqual(exclusions['0x00002000'], 'excluded_nonmanual_route')
        self.assertEqual(exclusions['0x00003000'], 'excluded_reviewed_full')

        selected, builder = self.select('0x2000\n0x3000\n0x4000\n')
        self.assertEqual({row['address'] for row in selected['selected']},
                         {'0x00002000', '0x00003000', '0x00004000'})
        self.assertEqual(selected['offset'], 0)
        self.assertEqual(builder.root, self.root.resolve())
        symbols = {row['address']: row['symbol'] for row in selected['selected']}
        self.assertEqual(symbols['0x00004000'], 'COutsideContour::dependency()')
        for row in selected['selected']:
            self.assertEqual(row['size'], 2)
            self.assertFalse(row['selected_residual'])
            self.assertEqual(row['role'], 'dependency_export')

    def test_canonical_spellings_and_comments_remain_one_bounded_batch(self):
        selected, _ = self.select('# exact missing dependencies\n\n0X2000\n00004000\n', limit=2)
        self.assertEqual({row['address'] for row in selected['selected']},
                         {'0x00002000', '0x00004000'})

    def test_duplicate_addresses_are_rejected_after_normalization(self):
        for text in ('0x2000\n0x2000\n', '2000\n00002000\n', '0X2000\n0x2000\n'):
            with self.subTest(text=text), self.assertRaises(ValueError):
                self.select(text)

    def test_interior_missing_and_unsized_entries_are_not_substituted(self):
        for address in ('0x2001', '0x6000', '0x5000'):
            with self.subTest(address=address), self.assertRaises(ValueError):
                self.select(address + '\n')

    def test_conflicting_index_alias_sizes_are_rejected(self):
        path = self.root / 'research/original-symbols.txt'
        path.write_text(path.read_text() + '00002000 00000003 T AliasAtSameEntry()\n')
        with self.assertRaises(ValueError):
            self.select('0x2000\n')

    def test_identical_index_alias_sizes_keep_one_exact_entry(self):
        path = self.root / 'research/original-symbols.txt'
        path.write_text(path.read_text() + '00002000 00000002 T AliasAtSameEntry()\n')
        selected, _ = self.select('0x2000\n')
        self.assertEqual(len(selected['selected']), 1)
        self.assertEqual(selected['selected'][0]['size'], 2)

    def test_empty_and_malformed_targets_are_rejected(self):
        for text in ('', '\n # no targets\n', '-1\n', '0x10000000000000000\n',
                     '0xGG\n', '0x2000 0x4000\n', '../0x2000\n'):
            with self.subTest(text=text), self.assertRaises(ValueError):
                self.select(text)

    def test_batch_limit_is_enforced_without_silent_truncation(self):
        with self.assertRaises(ValueError):
            self.select('0x2000\n0x3000\n0x4000\n', limit=2)
        for limit in (0, 1025):
            with self.subTest(limit=limit), self.assertRaises(ValueError):
                self.select('0x2000\n', limit=limit)

    def test_selection_preserves_sources_and_target_bytes(self):
        self.targets.write_text('0x2000\n0x3000\n0x4000\n', encoding='utf-8')
        before = {str(path.relative_to(self.root)): path.read_bytes()
                  for path in self.root.rglob('*') if path.is_file()}
        screening.select_explicit(self.root, self.targets, 4)
        after = {str(path.relative_to(self.root)): path.read_bytes()
                 for path in self.root.rglob('*') if path.is_file()}
        self.assertEqual(before, after)

    def prepare_cli_inputs(self):
        for name in ('screen_function_lifts.py', 'lift_pcode.py', 'lift_dependency_plan.py', 'ghidra_runtime.py',
                     'auto_triage.py', 'original.py', 'automation_state.py',
                     'transfer_contract.py', 'setup_ghidra.py', 'ghidra/ExportLiftBatch.java'):
            path = self.root / 'tools' / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text('# fixture CLI input identity\n')
        self.targets.write_text('0x2000\n0x4000\n', encoding='utf-8')

    def test_cli_dry_selection_hashes_targets_without_opening_original_or_ghidra(self):
        self.prepare_cli_inputs()
        before = {str(path.relative_to(self.root)): path.read_bytes()
                  for path in self.root.rglob('*') if path.is_file()}
        with tempfile.TemporaryDirectory(prefix='lift-dependency-cli-', dir='/tmp') as directory:
            output = Path(directory) / 'fresh'
            argv = ['screen_function_lifts.py', '--targets-file', str(self.targets),
                    '--limit', '2', '--output', str(output)]
            with mock.patch.object(screening, 'ROOT', self.root), mock.patch.object(sys, 'argv', argv), \
                 mock.patch.object(screening, 'Original') as original, \
                 mock.patch.object(screening, 'verify_installation') as ghidra, redirect_stdout(io.StringIO()):
                self.assertEqual(screening.main(), 0)
            original.assert_not_called()
            ghidra.assert_not_called()
            report = json.loads((output / 'report.json').read_text())
            self.assertEqual(report['status'], 'SCREENED')
            self.assertTrue(report['source_consistent'])
            self.assertFalse(report['original_elf']['verified_this_run'])
            self.assertEqual(report['input_sha256'][str(self.targets.resolve())], screening.digest(self.targets))
            self.assertEqual((output / 'targets.txt').read_text(), '0x00002000\n0x00004000\n')
            self.assertEqual(report['counts']['selected'], 2)
            self.assertTrue(all(row['selected_for_screen'] and not row['selected_residual']
                                for row in report['functions']))
            self.assertEqual(report['original_status_promotions'], 0)
            self.assertEqual({str(path.relative_to(self.root)): path.read_bytes()
                              for path in self.root.rglob('*') if path.is_file()}, before)

    def test_cli_preserves_existing_evidence_directory(self):
        self.prepare_cli_inputs()
        with tempfile.TemporaryDirectory(prefix='lift-dependency-cli-', dir='/tmp') as directory:
            output = Path(directory) / 'existing'
            output.mkdir()
            evidence = output / 'report.json'
            evidence.write_text('accepted prior evidence\n')
            argv = ['screen_function_lifts.py', '--targets-file', str(self.targets),
                    '--limit', '2', '--output', str(output)]
            with mock.patch.object(screening, 'ROOT', self.root), mock.patch.object(sys, 'argv', argv), \
                 redirect_stderr(io.StringIO()), self.assertRaises(SystemExit) as rejected:
                screening.main()
            self.assertEqual(rejected.exception.code, 2)
            self.assertEqual(evidence.read_text(), 'accepted prior evidence\n')


class ActualElfTargetValidationTest(unittest.TestCase):
    def selection(self, address='0x2000', size=2):
        return {'selected': [{'address': address, 'size': size, 'symbol': 'IndexSpelling()'}]}

    def original(self, *symbols):
        class ExactSymbolFixture:
            pass
        result = ExactSymbolFixture()
        result.symbols = list(symbols)
        return result

    def builder(self):
        return SimpleNamespace(symbols={'00002000': {'size': 2}})

    def test_matching_exact_code_symbol_and_equal_sized_aliases_pass(self):
        original = self.original(Symbol(0x2000, 2, 'T', 'Function()'),
                                 Symbol(0x2000, 2, 'W', 'Alias()'))
        self.assertIsNone(screening.validate_export_targets(self.selection(), self.builder(), original))

    def test_actual_missing_interior_unsized_and_noncode_targets_are_rejected(self):
        for symbols in ((Symbol(0x2001, 2, 'T', 'Other()'),),
                        (Symbol(0x1fff, 4, 'T', 'Containing()'),),
                        (Symbol(0x2000, 0, 'T', 'Unsized()'),),
                        (Symbol(0x2000, 2, 'D', 'Data'),)):
            with self.subTest(symbols=symbols), self.assertRaises(ValueError):
                screening.validate_export_targets(self.selection(), self.builder(), self.original(*symbols))

    def test_index_size_mismatch_and_conflicting_actual_aliases_are_rejected(self):
        for symbols in ((Symbol(0x2000, 3, 'T', 'ChangedSize()'),),
                        (Symbol(0x2000, 2, 'T', 'Function()'),
                         Symbol(0x2000, 3, 'W', 'AmbiguousAlias()'))):
            with self.subTest(symbols=symbols), self.assertRaises(ValueError):
                screening.validate_export_targets(self.selection(), self.builder(), self.original(*symbols))


def raw_packet(address, target=None):
    """Synthetic raw structure only; these fixtures are not original byte evidence."""
    operation = 'BRANCH' if target is not None else 'RETURN'
    node = {'space': 'ram' if target is not None else 'register',
            'space_id': 433 if target is not None else 548,
            'offset': hex(target if target is not None else 0x288), 'size': 8, 'constant': False}
    row = {'address': screening.canonical(hex(address)), 'bytes': '90', 'fallthrough': None,
           'pcode': [{'operation': operation, 'opcode': screening.lift.OPCODES[operation],
                      'index': 0, 'inputs': [node], 'output': None}]}
    digest = hashlib.sha256(row['address'].encode() + b'\x90').hexdigest()
    return {'schema': 2, 'original_elf_sha256': screening.ELF_SHA, 'address': row['address'],
            'instructions': [row], 'body_ranges': [{'start': row['address'], 'end_inclusive': row['address']}],
            'address_and_instruction_bytes_sha256': digest}


def raw_entry(packet):
    return {'raw_status': 'verified', 'raw_sha256': hashlib.sha256(
        json.dumps(packet, sort_keys=True).encode()).hexdigest(), 'packet': packet}


class DependencyOnlyGraphTest(unittest.TestCase):
    def test_explicit_export_closes_missing_graph_without_creating_residual_work(self):
        caller, dependency = raw_packet(0x1000, 0x2000), raw_packet(0x2000)
        raw = {caller['address']: raw_entry(caller)}
        residual_selection = {'selected': [{'address': caller['address']}]}
        missing = screening.make_report(residual_selection, raw)
        self.assertEqual(missing['functions'][0]['missing_dependency_packets'], [dependency['address']])
        self.assertFalse(missing['functions'][0]['structural_closure_candidate'])

        explicit_selection = {'selected': [{'address': dependency['address'], 'symbol': 'Dependency()',
                                           'size': 1, 'selected_residual': False,
                                           'role': 'dependency_export'}]}
        dependency_raw = {dependency['address']: raw_entry(dependency)}
        explicit = screening.make_report(explicit_selection, dependency_raw)
        dep_row = explicit['functions'][0]
        self.assertTrue(dep_row['selected_for_screen'])
        self.assertFalse(dep_row['selected_residual'])
        # "selected" counts this explicit screen batch, while the row remains
        # outside the residual manual queue and carries no acceptance.
        self.assertEqual(explicit['counts']['selected'], 1)
        self.assertEqual(explicit['raw_packet_counts']['verified'], 1)
        self.assertEqual(explicit['original_status_promotions'], 0)
        self.assertFalse(dep_row['production_ready'])

        before = copy.deepcopy(dependency_raw)
        screening.merge_raw(raw, dependency_raw)
        joined = screening.make_report(residual_selection, raw)
        rows = {row['address']: row for row in joined['functions']}
        self.assertTrue(rows[caller['address']]['structural_closure_candidate'])
        self.assertTrue(rows[caller['address']]['selected_for_screen'])
        self.assertTrue(rows[caller['address']]['selected_residual'])
        self.assertFalse(rows[dependency['address']]['selected_for_screen'])
        self.assertFalse(rows[dependency['address']]['selected_residual'])
        self.assertEqual(joined['counts']['selected'], 1)
        self.assertEqual(joined['raw_packet_counts']['verified'], 2)
        self.assertFalse(rows[caller['address']]['production_ready'])
        self.assertFalse(rows[dependency['address']]['production_ready'])
        self.assertEqual(joined['original_status_promotions'], 0)
        self.assertEqual(dependency_raw, before)


if __name__ == '__main__':
    unittest.main()
