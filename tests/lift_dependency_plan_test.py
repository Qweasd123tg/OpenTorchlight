#!/usr/bin/env python3
"""Dependency frontier contracts: synthetic reports, no game or ledger writes."""
from __future__ import annotations

import copy
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from lift_dependency_plan import build_dependency_plan, dependency_plan_markdown
from screen_function_lifts import closure_groups


def address(value):
    return f'0x{value:08x}'


def edge(target, site, kind='direct_call'):
    return {'kind': kind, 'target': address(target) if target is not None else None,
            'instruction': address(site), 'pcode_index': 3}


def row(entry, *dependencies, selected=False, status='verified', supported=True):
    return {'address': address(entry), 'selected_residual': selected, 'raw_status': status,
            'local_structural_candidate': supported, 'dependencies': list(dependencies),
            'structural_reasons': [] if supported else [{'kind': 'unsupported_opcode',
                'context': address(entry), 'detail': 'FLOAT_ADD'}]}


def report(*rows):
    rows = list(rows)
    closure_groups(rows)
    return {'schema': 1, 'kind': 'raw-function-lift-screening', 'functions': rows,
            'original_status_promotions': 0}


def symbols(*entries):
    return {f'{e:08x}': {'aliases': [f'Func{e:x}'], 'size': 16} for e in entries}


class DependencyPlanTest(unittest.TestCase):
    def test_shared_dependency_roots_and_all_repeated_sites_deduplicated(self):
        data = report(row(0x1000, edge(0x3000, 0x1001), edge(0x3000, 0x1005), selected=True),
                      row(0x2000, edge(0x3000, 0x2001, 'tail_jump'), selected=True))
        plan = build_dependency_plan(data, symbols(0x3000))
        self.assertEqual(plan['batches'], [{'index': 0, 'targets': [address(0x3000)]}])
        target = plan['targets'][0]
        self.assertEqual(target['roots'], [address(0x1000), address(0x2000)])
        self.assertEqual([c['instruction'] for c in target['callers']],
                         [address(0x1001), address(0x1005), address(0x2001)])
        self.assertFalse(target['retry'])
        self.assertEqual(plan['blocked'], [])

    def test_dependency_only_helpers_ignores_nonmanual_and_reviewed_scheduling(self):
        data = report(row(0x1000, edge(0x2000, 0x1001), selected=True),
                      row(0x2000, edge(0x3000, 0x2001)), row(0x3000, status='missing_function'))
        data['functions'][1]['recommended_action'] = 'library_reuse'
        data['functions'][2]['completion_status'] = 'reviewed_full'
        index = symbols(0x2000, 0x3000)
        index['00003000'] = {'address': '0x3000', 'symbol': 'ClosedHelper', 'size': 12}
        plan = build_dependency_plan(data, index)
        self.assertEqual([v['address'] for v in plan['targets']], [address(0x3000)])
        target = plan['targets'][0]
        self.assertEqual(target['symbol'], 'ClosedHelper')
        self.assertTrue(target['retry'])
        self.assertEqual(target['export_reason'], 'retry_missing_function')
        self.assertEqual(target['callers'][0]['address'], address(0x2000))
        self.assertEqual(plan['counts']['retry_targets'], 1)

    def test_nonverified_root_has_no_fabricated_caller(self):
        plan = build_dependency_plan(report(row(0x1000, selected=True, status='missing_packet')), symbols(0x1000))
        self.assertEqual(plan['targets'][0]['callers'], [])
        self.assertFalse(plan['targets'][0]['retry'])

    def test_ambiguous_alias_sizes_do_not_create_an_export_plan(self):
        data = report(row(0x1000, edge(0x2000, 0x1001), selected=True))
        index = symbols(0x2000)
        index['00002000']['ambiguous_sizes'] = True
        plan = build_dependency_plan(data, index)
        self.assertEqual(plan['targets'], [])
        self.assertEqual(plan['counts']['blocked_kinds'], {'ambiguous_symbol_size': 1})
        self.assertEqual(plan['blocked'][0]['target'], address(0x2000))

    def test_interior_unknown_unsized_and_unsafe_targets_never_export(self):
        malformed = edge(0x3000, 0x1007)
        malformed['target'] = '../../tmp/targets'
        data = report(row(0x1000, edge(0x2001, 0x1001), edge(0x4000, 0x1002),
                          edge(0x5000, 0x1003), selected=True))
        # Unsafe strings cannot enter screen closure normalization. They still
        # fail closed at the planner boundary rather than becoming filenames.
        data['functions'][0]['dependencies'].append(malformed)
        index = symbols(0x2000, 0x5000)
        index['00005000']['size'] = 0
        plan = build_dependency_plan(data, index)
        self.assertEqual(plan['targets'], [])
        self.assertEqual(plan['counts']['blocked_kinds'],
                         {'invalid_static_target': 1, 'not_exact_sized_symbol': 3})
        interior = next(b for b in plan['blocked'] if b['target'] == address(0x2001))
        self.assertEqual(interior['containing_symbol'], address(0x2000))

    def test_cycle_and_unsupported_supplied_stay_blocked_without_reexport(self):
        data = report(row(0x1000, edge(0x2000, 0x1001), selected=True),
                      row(0x2000, edge(0x3000, 0x2001), supported=False),
                      row(0x3000, edge(0x2000, 0x3001)))
        plan = build_dependency_plan(data, symbols(0x1000, 0x2000, 0x3000))
        self.assertEqual(plan['targets'], [])
        self.assertEqual(plan['counts']['blocked_kinds'],
                         {'recursive_dependency_cycle': 1, 'unsupported_supplied': 1})
        blocker = next(b for b in plan['blocked'] if b['kind'] == 'unsupported_supplied')
        self.assertEqual(blocker['target'], address(0x2000))
        self.assertEqual(blocker['reasons'][0]['detail'], 'FLOAT_ADD')

    def test_indirect_userop_and_conditional_never_invent_export_targets(self):
        data = report(row(0x1000, edge(None, 0x1001, 'indirect_call'),
                          edge(None, 0x1002, 'userop'),
                          edge(0x2000, 0x1003, 'external_conditional_branch'), selected=True))
        # An analysis candidate on a computed edge remains unapproved.
        data['functions'][0]['dependencies'][0]['target'] = address(0x3000)
        plan = build_dependency_plan(data, symbols(0x2000, 0x3000))
        self.assertEqual(plan['targets'], [])
        self.assertEqual({b['kind'] for b in plan['blocked']},
                         {'indirect_call', 'userop', 'external_conditional_branch'})
        indirect = next(b for b in plan['blocked'] if b['kind'] == 'indirect_call')
        self.assertIsNone(indirect['target'])

    def test_1025_targets_split_deterministically_in_bounded_batches(self):
        entries = list(range(0x2000, 0x2000 + 1025))
        data = report(row(0x1000, *(edge(e, 0x1001) for e in reversed(entries)), selected=True))
        plan = build_dependency_plan(data, symbols(*entries))
        self.assertEqual([len(b['targets']) for b in plan['batches']], [1024, 1])
        self.assertEqual(plan['batches'][0]['targets'][0], address(entries[0]))
        self.assertEqual(plan['batches'][1]['targets'], [address(entries[-1])])

    def test_input_order_independence_and_no_registry_or_report_mutation(self):
        data = report(row(0x2000, edge(0x4000, 0x2001), selected=True),
                      row(0x1000, edge(0x3000, 0x1001), selected=True))
        index = symbols(0x4000, 0x3000)
        original_data, original_index = copy.deepcopy(data), copy.deepcopy(index)
        expected = build_dependency_plan(data, index, max_batch=1)
        self.assertEqual(data, original_data)
        self.assertEqual(index, original_index)
        reversed_data = copy.deepcopy(data)
        reversed_data['functions'].reverse()
        actual = build_dependency_plan(reversed_data, dict(reversed(list(index.items()))), max_batch=1)
        self.assertEqual(actual, expected)
        self.assertEqual(actual['original_status_promotions'], 0)
        self.assertFalse(actual['game_executed'])
        self.assertFalse(actual['original_modified'])
        self.assertIn('2 targets in 2 batches for 2 roots', dependency_plan_markdown(actual))

    def test_invalid_batch_and_source_identity_are_rejected(self):
        data = report(row(0x1000, selected=True))
        for limit in (0, 1025, True, 1.5):
            with self.assertRaises(ValueError):
                build_dependency_plan(data, {}, limit)
        for status in ('FAILED', 'STALE'):
            with self.assertRaises(ValueError):
                build_dependency_plan({**data, 'status': status}, {})
        with self.assertRaises(ValueError):
            build_dependency_plan(data, {'00002000': {'address': '0x2001', 'symbol': 'Wrong', 'size': 8}})


if __name__ == '__main__':
    unittest.main()
