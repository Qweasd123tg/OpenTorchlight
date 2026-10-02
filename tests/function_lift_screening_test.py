#!/usr/bin/env python3
"""Mass scheduling/raw feasibility checks; synthetic contracts, no promotion."""
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
import screen_function_lifts as screening
from original import Symbol


def node(space, offset, size=8):
    return {'space': space, 'space_id': {'const': 48, 'ram': 433, 'register': 548, 'unique': 291}[space],
            'offset': hex(offset), 'size': size, 'constant': space == 'const'}


def operation(name, *inputs, output=None, index=0):
    return {'operation': name, 'opcode': screening.lift.OPCODES.get(name, 999),
            'inputs': list(inputs), 'output': output, 'index': index}


def instruction(address, *ops, fall=None):
    return {'address': screening.canonical(hex(address)), 'bytes': '90',
            'pcode': [dict(op, index=i) for i, op in enumerate(ops)],
            'fallthrough': screening.canonical(hex(fall)) if fall else None}


def packet(*rows):
    digest = hashlib.sha256()
    for row in rows:
        digest.update(row['address'].encode()); digest.update(bytes.fromhex(row['bytes']))
    return {'schema': 2, 'original_elf_sha256': screening.ELF_SHA,
            'address': rows[0]['address'], 'instructions': list(rows),
            'body_ranges': [{'start': rows[0]['address'], 'end_inclusive': rows[-1]['address']}],
            'address_and_instruction_bytes_sha256': digest.hexdigest()}


def returns(address):
    return packet(instruction(address, operation('RETURN', node('register', 0x288))))


def entry(data):
    return {'raw_status': 'verified', 'raw_sha256': 'f' * 64, 'packet': data}


def selection(*addresses):
    return {'selected': [{'address': screening.canonical(hex(a))} for a in addresses]}


class FakeOriginal:
    sha256 = screening.ELF_SHA
    symbols = [Symbol(0x1000, 2, 'T', 'FuncA')]

    def read(self, address, size):
        if 0x1000 <= address and address + size <= 0x1002:
            return b'\x90' * size
        raise ValueError('fixture not file-backed')


class StructuralScreeningTest(unittest.TestCase):
    def test_float_multiply_matches_emitter_sse_instruction_boundary(self):
        row = instruction(0x1000,
            operation('FLOAT_MULT', node('register', 0x1200, 4), node('register', 0x1210, 4),
                      output=node('register', 0x1200, 4)),
            operation('RETURN', node('register', 0x288)))
        row['bytes'] = 'f30f59c1'
        self.assertTrue(screening.screen_packet(packet(row))['local_structural_candidate'])
        row['bytes'] = 'd8c9'
        self.assertIn('unsupported_instruction', {
            r['kind'] for r in screening.screen_packet(packet(row))['structural_reasons']})
        row['bytes'] = 'f30f59c1'
        row['pcode'][0]['inputs'][0]['size'] = 2
        self.assertIn('width_contract', {
            r['kind'] for r in screening.screen_packet(packet(row))['structural_reasons']})

    def test_no_call_does_not_make_tail_leaf(self):
        data = packet(instruction(0x1000, operation('BRANCH', node('ram', 0x2000))))
        report = screening.make_report(selection(0x1000), {'0x00001000': entry(data)})
        row = report['functions'][0]
        self.assertTrue(row['local_structural_candidate'])
        self.assertFalse(row['structural_closure_candidate'])
        self.assertEqual(row['dependencies'][0]['kind'], 'tail_jump')
        self.assertEqual(row['missing_dependency_packets'], ['0x00002000'])
        self.assertEqual(report['original_status_promotions'], 0)
        self.assertFalse(row['production_ready'])
        self.assertEqual(row['abi_status'], 'missing_reviewed_abi')
        self.assertEqual(row['owner_status'], 'missing_production_owner_review')

    def test_direct_call_requires_return_fallthrough_and_retains_target(self):
        data = packet(instruction(0x1000, operation('CALL', node('ram', 0x2000)), fall=0x1001),
                      instruction(0x1001, operation('RETURN', node('register', 0x288))))
        result = screening.screen_packet(data)
        self.assertTrue(result['local_structural_candidate'])
        self.assertEqual(result['dependencies'][0]['kind'], 'direct_call')
        data['instructions'][0]['fallthrough'] = None
        result = screening.screen_packet(data)
        self.assertIn('call_fallthrough', {r['kind'] for r in result['structural_reasons']})
        self.assertEqual(result['dependencies'][0]['target'], '0x00002000')

    def test_indirect_unknown_opcode_and_wide_nodes_all_remain_explicit(self):
        data = packet(instruction(0x1000,
            operation('COPY', node('const', 1, 16), output=node('register', 0, 16)),
            operation('FLOAT_ADD', node('register', 0), node('register', 8), output=node('register', 16)),
            operation('CALLIND', node('register', 0)),
            operation('BRANCHIND', node('register', 8))))
        result = screening.screen_packet(data)
        kinds = {r['kind'] for r in result['structural_reasons']}
        self.assertIn('unsupported_width_space', kinds)
        self.assertIn('unsupported_opcode', kinds)
        self.assertIn('indirect_dependency', kinds)
        self.assertEqual({e['kind'] for e in result['dependencies']}, {'indirect_call', 'indirect_branch'})
        self.assertEqual(result['opcode_inventory']['FLOAT_ADD'], 1)

    def test_supported_closure_preserves_dependency_only_members(self):
        a = packet(instruction(0x1000, operation('BRANCH', node('ram', 0x2000))))
        b = returns(0x2000)
        before = copy.deepcopy(a)
        report = screening.make_report(selection(0x1000), {'0x00001000': entry(a), '0x00002000': entry(b)})
        rows = {r['address']: r for r in report['functions']}
        self.assertTrue(rows['0x00001000']['structural_closure_candidate'])
        self.assertFalse(rows['0x00002000']['selected_residual'])
        self.assertIn(['0x00001000', '0x00002000'], [g['entries'] for g in report['structural_closure_groups']])
        self.assertEqual(a, before)
        self.assertEqual(report['original_status_promotions'], 0)

    def test_reachable_cycle_blocks_caller_and_cycle_members(self):
        raw = {}
        for a, b in ((0x1000, 0x2000), (0x2000, 0x3000), (0x3000, 0x2000)):
            data = packet(instruction(a, operation('BRANCH', node('ram', b))))
            raw[data['address']] = entry(data)
        report = screening.make_report(selection(0x1000), raw)
        for row in report['functions']:
            self.assertFalse(row['structural_closure_candidate'])
            self.assertIn('recursive_dependency_cycle', {r['kind'] for r in row['closure_reasons']})

    def test_exact_abi_preflight_still_does_not_accept_owner_or_completion(self):
        data = returns(0x1000)
        abi = {'schema': 1, 'original_elf_sha256': screening.ELF_SHA, 'memory_space_id': 433,
               'functions': {'0x1000': {'return': 'void', 'input_registers':
                                       [{'offset': '0x20', 'size': 8}, {'offset': '0x288', 'size': 8}]}}}
        report = screening.make_report(selection(0x1000), {data['address']: entry(data)}, abi)
        row = report['functions'][0]
        self.assertEqual(row['abi_status'], 'explicit_abi_preflight_passed')
        self.assertFalse(row['production_ready'])
        self.assertEqual(report['original_status_promotions'], 0)
        del abi['functions']['0x1000']['input_registers']
        row = screening.make_report(selection(0x1000), {data['address']: entry(data)}, abi)['functions'][0]
        self.assertEqual(row['abi_status'], 'explicit_abi_rejected')

    def test_unique_use_before_definition_and_invalid_index(self):
        data = packet(instruction(0x1000,
            operation('COPY', node('unique', 10), output=node('register', 0)),
            operation('RETURN', node('register', 0))))
        data['instructions'][0]['pcode'][0]['index'] = 2
        result = screening.screen_packet(data)
        self.assertEqual({'opcode_index_mismatch', 'uninitialized_unique'},
                         {r['kind'] for r in result['structural_reasons']})

    def test_width_space_and_external_conditional_not_lowered(self):
        data = packet(instruction(0x1000,
            operation('CBRANCH', node('ram', 0x2000), node('register', 0, 1)),
            operation('RETURN', node('register', 0))))
        result = screening.screen_packet(data)
        self.assertIn('external_conditional_branch', {r['kind'] for r in result['structural_reasons']})
        self.assertEqual(result['dependencies'][0]['kind'], 'external_conditional_branch')
        data['instructions'][0]['pcode'][0]['inputs'][1]['space_id'] = 999
        result = screening.screen_packet(data)
        self.assertIn('unsupported_width_space', {r['kind'] for r in result['structural_reasons']})

    def test_closure_depth_bound_matches_emitter(self):
        raw = {}
        for i in range(65):
            a = 0x1000 + i
            data = returns(a) if i == 64 else packet(instruction(a, operation('BRANCH', node('ram', a + 1))))
            raw[data['address']] = entry(data)
        report = screening.make_report(selection(0x1000), raw)
        first = report['functions'][0]
        self.assertFalse(first['structural_closure_candidate'])
        self.assertEqual(first['closure_depth'], 65)
        self.assertIn('closure_depth_limit', {r['kind'] for r in first['closure_reasons']})


class RawIdentityTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='screening-raw-', dir='/tmp')
        self.root = Path(self.temp.name)
        self.data = packet(instruction(0x1000, operation('COPY', node('const', 1), output=node('register', 0)), fall=0x1001),
                           instruction(0x1001, operation('RETURN', node('register', 0))))
        self.manifest = {'schema': 2, 'original_elf_sha256': screening.ELF_SHA,
                         'ghidra_version': screening.VERSION, 'language': 'x86:LE:64:default',
                         'program_modified_by_script': False, 'game_executed': False,
                         'functions': [{'address': '0x1000', 'json': '00001000.json', 'status': 'exported'}]}
        self.write()

    def tearDown(self):
        self.temp.cleanup()

    def write(self):
        (self.root / 'manifest.json').write_text(json.dumps(self.manifest))
        (self.root / '00001000.json').write_text(json.dumps(self.data))

    def test_full_symbol_and_each_instruction_are_verified(self):
        raw, _, _ = screening.load_raw(self.root, FakeOriginal())
        verification = raw['0x00001000']['original_verification']
        self.assertEqual(verification['full_symbol_sha256'], hashlib.sha256(b'\x90\x90').hexdigest())
        self.assertEqual(verification['verified_instruction_bytes'], 2)
        self.assertEqual(verification['symbol_bytes_without_exported_instruction'], 0)

    def test_instruction_byte_and_packet_hash_tampering_rejected(self):
        self.data['instructions'][0]['bytes'] = '91'; self.write()
        with self.assertRaisesRegex(ValueError, 'differ from external original'):
            screening.load_raw(self.root, FakeOriginal())
        self.data['instructions'][0]['bytes'] = '90'
        self.data['address_and_instruction_bytes_sha256'] = 'f' * 64; self.write()
        with self.assertRaisesRegex(ValueError, 'hash mismatch'):
            screening.load_raw(self.root, FakeOriginal())

    def test_missing_manifest_entry_or_duplicate_not_skipped(self):
        self.manifest['functions'][0]['json'] = 'missing.json'; self.write()
        with self.assertRaisesRegex(ValueError, 'missing/unsafe'):
            screening.load_raw(self.root, FakeOriginal())
        self.manifest['functions'][0]['json'] = '00001000.json'
        self.manifest['functions'].append(dict(self.manifest['functions'][0], address='0x00001000')); self.write()
        with self.assertRaisesRegex(ValueError, 'Duplicate normalized'):
            screening.load_raw(self.root, FakeOriginal())

    def test_wrong_tool_or_program_identity_rejected(self):
        self.manifest['ghidra_version'] = 'old'; self.write()
        with self.assertRaisesRegex(ValueError, 'identity'):
            screening.load_raw(self.root, FakeOriginal())
        self.manifest['ghidra_version'] = screening.VERSION
        self.data['address'] = '0x1001'; self.write()
        with self.assertRaisesRegex(ValueError, 'exact-entry mismatch'):
            screening.load_raw(self.root, FakeOriginal())

    def test_gaps_in_symbol_coverage_reported_not_hidden(self):
        data = returns(0x1000)
        result = screening.validate_raw(data, FakeOriginal(), FakeOriginal.symbols[0], data['address'])
        self.assertEqual(result['symbol_bytes_without_exported_instruction'], 1)


class SelectionTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='screening-selection-', dir='/tmp')
        self.root = Path(self.temp.name)
        (self.root / 'research').mkdir()
        (self.root / 'tools').mkdir()
        self.write('tools/function_package.py', '# fixture identity\n')
        self.write('research/original-symbols.txt', '00001000 00000002 T CMainMenu::first()\n'
                   '00002000 00000002 T CGame::second()\n00003000 00000002 T CMainMenu::third()\n')
        self.write('research/coverage.tsv', 'address\tsymbol\tsubsystem\tstatus\n'
                   '0x00001000\tCMainMenu::first()\tui\tpartial\n'
                   '0x00002000\tCGame::second()\tgameplay\tpartial\n'
                   '0x00003000\tCMainMenu::third()\tui\tclosed\n')
        self.write('research/original-callgraph.tsv', 'caller_address\tcaller_symbol\tcallee_address\tcallee_symbol\n')
        self.write('research/ui-contour.json', json.dumps({'original_elf_sha256': screening.ELF_SHA,
                   'entry_addresses': [], 'class_prefixes': ['CMainMenu']}))
        self.write('research/function-transfer.json', json.dumps({'functions': {}}))

    def write(self, path, text):
        (self.root / path).write_text(text)

    def tearDown(self):
        self.temp.cleanup()

    def test_manual_scope_pagination_exclusions_and_no_ledger_mutation(self):
        before = {p: p.read_bytes() for p in self.root.rglob('*') if p.is_file()}
        ui, _ = screening.select(self.root, 'ui', 1)
        self.assertEqual([r['address'] for r in ui['selected']], ['0x00001000'])
        self.assertEqual(ui['excluded'][0]['screening_status'], 'excluded_closed')
        all_rows, _ = screening.select(self.root, 'all', 1, 1)
        self.assertEqual([r['address'] for r in all_rows['selected']], ['0x00002000'])
        self.assertEqual(all_rows['residual_manual_total'], 2)
        self.assertEqual(before, {p: p.read_bytes() for p in self.root.rglob('*') if p.is_file()})

    def test_explicit_batch_bound(self):
        for limit in (0, 1025):
            with self.assertRaisesRegex(ValueError, '1..1024'):
                screening.select(self.root, 'all', limit)

    def test_callsite_index_metadata_hash_is_enforced(self):
        text = 'caller_address\tcaller_symbol\tcallsite_address\tcallee_address\tcallee_symbol\tmnemonic\n'
        self.write('research/original-callsites.tsv', text)
        self.write('research/original-callsites.tsv.meta.json', json.dumps({
            'kind': 'direct-callsites', 'original_elf_sha256': screening.ELF_SHA, 'tsv_sha256': 'f' * 64}))
        with self.assertRaisesRegex(ValueError, 'tsv_sha256'):
            screening.select(self.root, 'all', 1)

    def test_full_claim_excluded_only_while_all_inputs_current(self):
        from transfer_contract import STAGES, REVIEW_AREAS
        for directory in ('src', 'tests'):
            (self.root / directory).mkdir()
        self.write('src/fixture.cpp', '// fixture production\n')
        self.write('tests/fixture.cpp', '// fixture comparison\n')
        pins = {p: screening.digest(self.root / p) for p in ('src/fixture.cpp', 'tests/fixture.cpp')}
        record = {'stages': {stage: True for stage in STAGES}, 'completion': {
            'status': 'full', 'open_items': [], 'inputs': pins,
            'review': {area: 'fixture explicit review' for area in REVIEW_AREAS}}}
        # Closed is a legacy coverage label. Freshness of the whole-function
        # claim must control exclusions when such a claim is present.
        coverage = self.root / 'research/coverage.tsv'
        coverage.write_text(coverage.read_text().replace('ui\tpartial', 'ui\tclosed', 1))
        self.write('research/function-transfer.json', json.dumps({'functions': {'0x1000': record}}))
        current, _ = screening.select(self.root, 'all', 2)
        self.assertEqual([r['address'] for r in current['selected']], ['0x00002000'])
        self.assertEqual(current['excluded'][0]['screening_status'], 'excluded_reviewed_full')
        self.write('src/fixture.cpp', '// modified production\n')
        stale, _ = screening.select(self.root, 'all', 2)
        self.assertEqual([r['address'] for r in stale['selected']], ['0x00001000', '0x00002000'])
        self.assertEqual(stale['selected'][0]['completion_status'], 'stale')
        record['completion']['review'].pop('original_comparison')
        self.write('research/function-transfer.json', json.dumps({'functions': {'0x1000': record}}))
        invalid, _ = screening.select(self.root, 'all', 2)
        self.assertEqual([r['address'] for r in invalid['selected']], ['0x00001000', '0x00002000'])
        self.assertEqual(invalid['selected'][0]['completion_status'], 'invalid')


class BatchUnionTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='screening-union-', dir='/tmp')
        self.root = Path(self.temp.name)

    def tearDown(self):
        self.temp.cleanup()

    def batch(self, name, packets, statuses=None):
        directory = self.root / name
        directory.mkdir()
        rows = []
        for data in packets:
            filename = data['address'][2:] + '.json'
            (directory / filename).write_text(json.dumps(data))
            rows.append({'address': data['address'], 'json': filename,
                         'status': (statuses or {}).get(data['address'], 'exported')})
        (directory / 'manifest.json').write_text(json.dumps({
            'schema': 2, 'original_elf_sha256': screening.ELF_SHA,
            'ghidra_version': screening.VERSION, 'language': 'x86:LE:64:default',
            'program_modified_by_script': False, 'game_executed': False, 'functions': rows}))
        return directory

    def original(self):
        class BatchOriginal(FakeOriginal):
            symbols = [Symbol(0x1000, 1, 'T', 'FuncA'), Symbol(0x2000, 1, 'T', 'FuncB')]

            def read(self, address, size):
                if address in (0x1000, 0x2000) and size == 1:
                    return b'\x90'
                raise ValueError('fixture not file-backed')
        return BatchOriginal()

    def test_cross_batch_closure_retains_nonselected_dependency(self):
        a = packet(instruction(0x1000, operation('BRANCH', node('ram', 0x2000))))
        b = returns(0x2000)
        left, _, _ = screening.load_raw(self.batch('left', [a]), self.original())
        right, _, _ = screening.load_raw(self.batch('right', [b]), self.original())
        separate = screening.make_report(selection(0x1000), left)['functions'][0]
        self.assertFalse(separate['structural_closure_candidate'])
        self.assertEqual(separate['missing_dependency_packets'], ['0x00002000'])
        screening.merge_raw(left, right)
        joined = screening.make_report(selection(0x1000), left)
        rows = {r['address']: r for r in joined['functions']}
        self.assertTrue(rows['0x00001000']['structural_closure_candidate'])
        self.assertEqual(rows['0x00001000']['transitive_dependencies_in_batch'], ['0x00002000'])
        self.assertFalse(rows['0x00002000']['selected_residual'])
        self.assertFalse(rows['0x00001000']['production_ready'])
        self.assertEqual(joined['original_status_promotions'], 0)
        self.assertEqual(joined['counts']['selected'], 1)
        self.assertEqual(joined['counts']['structural_closure_candidate'], 1)
        self.assertEqual(joined['raw_packet_counts']['supplied_unique_entries'], 2)
        self.assertEqual(joined['raw_packet_counts']['verified'], 2)
        self.assertEqual(joined['raw_packet_counts']['local_structural_candidate'], 2)
        self.assertEqual(joined['raw_packet_counts']['structural_closure_candidate'], 2)
        self.assertEqual(joined['raw_packet_counts']['production_ready'], 0)

    def test_identical_duplicate_reusable_but_different_raw_contract_rejected(self):
        a = returns(0x1000)
        left, _, _ = screening.load_raw(self.batch('left', [a]), self.original())
        duplicate, _, _ = screening.load_raw(self.batch('duplicate', [a]), self.original())
        first_path = left['0x00001000']['raw_path']
        screening.merge_raw(left, duplicate)
        self.assertEqual(len(left), 1)
        self.assertEqual(left['0x00001000']['raw_path'], first_path)
        # Same verified instruction bytes, different p-code: original byte
        # validation alone cannot authorize silently replacing a raw contract.
        changed = copy.deepcopy(a)
        changed['instructions'][0]['pcode'][0]['inputs'][0]['offset'] = '0x290'
        conflict, _, _ = screening.load_raw(self.batch('conflict', [changed, returns(0x2000)]), self.original())
        before = copy.deepcopy(left)
        with self.assertRaisesRegex(ValueError, 'Conflicting duplicate'):
            screening.merge_raw(left, conflict)
        self.assertEqual(left, before)

    def test_aggregate_counts_distinguish_occurrences_functions_and_selection(self):
        data = packet(instruction(0x1000,
            operation('CALLIND', node('register', 0)),
            operation('CALLIND', node('register', 8)),
            operation('RETURN', node('register', 0))))
        raw = {data['address']: entry(data), '0x00002000': entry(returns(0x2000))}
        report = screening.make_report(selection(0x2000), raw)
        counts = report['raw_packet_counts']
        self.assertEqual(counts['verified'], 2)
        self.assertEqual(counts['structural_reason_occurrences']['indirect_dependency'], 2)
        self.assertEqual(counts['structural_reason_function_counts']['indirect_dependency'], 1)
        self.assertEqual(counts['closure_reason_occurrences']['unresolved_dependency'], 2)
        self.assertEqual(counts['closure_reason_function_counts']['unresolved_dependency'], 1)
        self.assertEqual(report['counts']['selected'], 1)
        self.assertNotIn('reason:indirect_dependency', report['counts'])

    def test_identical_packet_with_conflicting_manifest_status_rejected(self):
        a = returns(0x1000)
        exported, _, _ = screening.load_raw(self.batch('exported', [a]), self.original())
        failed, _, _ = screening.load_raw(self.batch('failed', [a], {a['address']: 'missing_function'}), self.original())
        self.assertEqual(exported[a['address']]['raw_sha256'], failed[a['address']]['raw_sha256'])
        for destination, source in ((exported, failed), (failed, exported)):
            with self.assertRaisesRegex(ValueError, 'Conflicting duplicate'):
                screening.merge_raw(destination, source)


if __name__ == '__main__':
    unittest.main()
