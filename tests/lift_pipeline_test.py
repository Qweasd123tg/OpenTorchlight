#!/usr/bin/env python3
"""Bounded command orchestration contracts; no Ghidra, model or game calls."""
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
from lift_dependency_plan import build_dependency_plan
from run_lift_pipeline import PipelineOptions, run_pipeline
from screen_function_lifts import closure_groups


def address(value):
    return f'0x{value:08x}'


def edge(target, site, kind='direct_call'):
    return {'kind': kind, 'target': address(target) if target is not None else None,
            'instruction': address(site), 'pcode_index': 1}


def row(entry, *dependencies, selected=False, status='verified', supported=True):
    return {'address': address(entry), 'selected_residual': selected, 'raw_status': status,
            'dependencies': list(dependencies), 'local_structural_candidate': supported,
            'structural_reasons': [] if supported else [{'kind': 'unsupported_opcode',
                                                        'context': address(entry), 'detail': 'FLOAT_ADD'}]}


class ChildScreens:
    """Publish synthetic screen evidence from explicit sequential expectations."""
    def __init__(self, *screens, change_source=None, fail_at=None):
        self.screens, self.calls = list(screens), []
        self.change_source, self.fail_at = change_source, fail_at

    def __call__(self, command, log):
        self.calls.append(command)
        log.write_text('synthetic child invocation\n')
        if self.change_source:
            self.change_source(len(self.calls))
        if self.fail_at == len(self.calls):
            return 2
        rows = copy.deepcopy(self.screens[len(self.calls) - 1])
        closure_groups(rows)
        selected = [{'address': r['address']} for r in rows if r['selected_residual']]
        if '--targets-file' in command:
            selected = [{'address': a} for a in Path(command[command.index('--targets-file') + 1]).read_text().splitlines()]
        report = {'schema': 1, 'kind': 'raw-function-lift-screening', 'status': 'SCREENED',
                  'source_consistent': True, 'original_status_promotions': 0,
                  'game_executed': False, 'original_modified': False,
                  'selection': {'selected': selected}, 'functions': rows}
        symbols = {f'{i:08x}': {'symbol': f'Func{i:x}', 'size': 1} for i in range(0x1000, 0x7000)}
        plan = build_dependency_plan(report, symbols)
        child_output = Path(command[command.index('--output') + 1])
        child_output.mkdir()
        if '--export' in command:
            (child_output / 'raw').mkdir()
        report_path = child_output / 'report.json'
        report_path.write_text(json.dumps(report))
        plan.update(status='SCREENED', source_consistent=True,
                    report_sha256=hashlib.sha256(report_path.read_bytes()).hexdigest())
        (child_output / 'dependency-plan.json').write_text(json.dumps(plan))
        return 0


class PreparedScreens:
    def __init__(self, *screens, fail_prepare=False, change_on_prepare=None, status='PREPARED'):
        self.screen = ChildScreens(*screens)
        self.calls = []
        self.fail_prepare = fail_prepare
        self.change_on_prepare = change_on_prepare
        self.status = status

    def __call__(self, command, log):
        self.calls.append(command)
        if Path(command[1]).name != 'prepare_lift_project.py':
            return self.screen(command, log)
        log.write_text('synthetic bounded preparation\n')
        if self.change_on_prepare:
            self.change_on_prepare()
        if self.fail_prepare:
            return 2
        child_output = Path(command[command.index('--output') + 1])
        child_output.mkdir()
        report = {'schema': 1, 'kind': 'bounded-lift-project-preparation', 'status': self.status,
                  'source_consistent': True, 'original_status_promotions': 0,
                  'original_modified': False, 'game_executed': False,
                  'analysis_requested': False, 'decompiler_requested': False,
                  'project_database_modified': True,
                  'requested_targets': Path(command[command.index('--targets-file') + 1]).read_text().splitlines()}
        (child_output / 'report.json').write_text(json.dumps(report))
        return 0


class LiftPipelineTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.base = Path(self.temp.name)
        self.raw = self.base / 'existing'
        self.raw.mkdir()
        self.source = {'sha256': 'unchanged'}

    def options(self, **changes):
        values = dict(output=self.base / 'pipeline', limit=4, max_rounds=2,
                      max_functions=16, raw_dirs=(self.raw,),
                      original=self.base / 'original-input' / 'original.bin',
                      home=self.base / 'tool', analysis_root=self.base / 'project')
        values.update(changes)
        return PipelineOptions(**values)

    def run_pipeline(self, child, root_selector=None, **options):
        return run_pipeline(self.options(**options), child, snapshotter=lambda _: dict(self.source),
                            root_selector=root_selector)

    def test_reuse_export_rejoin_sequentially_without_reexporting_verified(self):
        initial = [row(0x1000, edge(0x2000, 0x1001), selected=True)]
        exported = [row(0x2000)]
        joined = initial + exported
        child = ChildScreens(initial, exported, joined)
        result = self.run_pipeline(child)
        self.assertEqual(result['stop_reason'], 'closure_collected')
        self.assertEqual(result['counts']['export_functions'], 1)
        self.assertEqual(result['counts']['dependency_rounds'], 1)
        self.assertEqual([c['role'] for c in result['commands']],
                         ['root_reuse', 'dependency_export', 'root_rejoin'])
        self.assertNotIn('--export', child.calls[0])
        self.assertIn('--targets-file', child.calls[1])
        self.assertEqual(result['attempted_targets'], [address(0x2000)])
        self.assertEqual(child.calls[2].count('--raw-dir'), 2)
        self.assertTrue((self.base / 'pipeline' / 'SUMMARY.md').is_file())

    def test_blocked_roots_do_not_block_independent_or_shared_healthy_targets(self):
        initial = [row(0x1000, edge(0x3000, 0x1001), edge(None, 0x1002, 'indirect_call'), selected=True),
                   row(0x2000, edge(0x3000, 0x2001), selected=True)]
        exported = [row(0x3000)]
        child = ChildScreens(initial, exported, initial + exported)
        result = self.run_pipeline(child)
        self.assertEqual(result['counts']['export_functions'], 1)
        self.assertEqual(result['blocked_roots'], [address(0x1000)])
        self.assertEqual(result['stop_reason'], 'unresolved_blockers')

    def test_fully_blocked_root_does_not_spend_on_other_missing_targets(self):
        child = ChildScreens([row(0x1000, edge(0x2000, 0x1001), selected=True, supported=False)])
        result = self.run_pipeline(child)
        self.assertEqual(result['stop_reason'], 'unresolved_blockers')
        self.assertEqual(result['counts']['export_functions'], 0)
        self.assertEqual(len(child.calls), 1)

    def test_missing_function_requires_review_and_is_never_retried(self):
        initial = [row(0x1000, edge(0x2000, 0x1001), selected=True)]
        failed = [row(0x2000, status='missing_function', supported=False)]
        child = ChildScreens(initial, failed, initial + failed)
        result = self.run_pipeline(child)
        self.assertEqual(result['stop_reason'], 'retry_review_required')
        self.assertEqual(result['retry_roots'], [address(0x1000)])
        self.assertEqual(result['counts']['export_functions'], 1)
        self.assertEqual(len(child.calls), 3)
        self.assertTrue(all('--retry-failed' not in c for c in child.calls))

    def test_round_budget_keeps_the_new_uncollected_frontier(self):
        initial = [row(0x1000, edge(0x2000, 0x1001), selected=True)]
        dependency = [row(0x2000, edge(0x3000, 0x2001))]
        child = ChildScreens(initial, dependency, initial + dependency)
        result = self.run_pipeline(child, max_rounds=1)
        self.assertEqual(result['stop_reason'], 'round_budget')
        self.assertEqual(result['counts']['remaining_targets'], 1)
        self.assertEqual(result['attempted_targets'], [address(0x2000)])

    def test_function_budget_truncates_frontier_and_rejoins_completed_work(self):
        initial = [row(0x1000, edge(0x2000, 0x1001), edge(0x3000, 0x1002), selected=True)]
        exported = [row(0x2000)]
        child = ChildScreens(initial, exported, initial + exported)
        result = self.run_pipeline(child, max_functions=1)
        self.assertEqual(result['stop_reason'], 'function_budget')
        self.assertEqual(result['counts']['export_functions'], 1)
        self.assertEqual(result['counts']['remaining_targets'], 1)

    def test_root_exports_count_toward_budget(self):
        initial = [row(0x1000, edge(0x2000, 0x1001), selected=True)]
        child = ChildScreens(initial)
        result = self.run_pipeline(child, raw_dirs=(), export_roots=True, limit=1, max_functions=1)
        self.assertEqual(result['stop_reason'], 'function_budget')
        self.assertEqual(result['counts']['export_functions'], 1)
        self.assertEqual(result['attempted_targets'], [address(0x1000)])

    def test_optional_root_preparation_precedes_export_and_uses_bounded_default(self):
        child = PreparedScreens([row(0x1000, selected=True)])
        result = self.run_pipeline(child, root_selector=lambda *_: ['0x1000'],
                                   raw_dirs=(), export_roots=True, prepare_project=True,
                                   analysis_root=None, limit=1)
        self.assertEqual([c['role'] for c in result['commands']], ['project_prepare', 'root_export'])
        self.assertEqual(result['stop_reason'], 'closure_collected')
        self.assertTrue(result['project_database_modified'])
        self.assertFalse(result['original_modified'])
        self.assertEqual(len(child.calls), 2)
        for command in child.calls:
            self.assertEqual(command[command.index('--analysis-root') + 1], str(ROOT / 'build-ghidra-lift'))
        targets = Path(child.calls[0][child.calls[0].index('--targets-file') + 1]).read_text()
        self.assertEqual(targets, address(0x1000) + '\n')

    def test_reuse_prepares_only_new_dependency_batches(self):
        initial = [row(0x1000, edge(0x2000, 0x1001), selected=True)]
        exported = [row(0x2000)]
        child = PreparedScreens(initial, exported, initial + exported)
        result = self.run_pipeline(child, prepare_project=True)
        self.assertEqual([c['role'] for c in result['commands']],
                         ['root_reuse', 'project_prepare', 'dependency_export', 'root_rejoin'])
        self.assertEqual(result['commands'][1]['targets'], [address(0x2000)])
        self.assertEqual(result['counts']['export_functions'], 1)

    def test_default_saved_project_path_stays_read_only_without_preparation(self):
        child = ChildScreens([row(0x1000, selected=True)])
        result = self.run_pipeline(child, analysis_root=None)
        self.assertFalse(result['prepare_project'])
        self.assertFalse(result['project_database_modified'])
        self.assertEqual(child.calls[0][child.calls[0].index('--analysis-root') + 1], str(ROOT / 'build-ghidra'))
        self.assertEqual([c['role'] for c in result['commands']], ['root_reuse'])

    def test_preparation_failure_stops_before_export(self):
        child = PreparedScreens(fail_prepare=True)
        result = self.run_pipeline(child, root_selector=lambda *_: ['0x1000'],
                                   raw_dirs=(), export_roots=True, prepare_project=True, limit=1)
        self.assertEqual(result['stop_reason'], 'child_failed')
        self.assertEqual(result['counts']['export_functions'], 0)
        self.assertTrue(result['project_preparation_unconfirmed'])
        self.assertEqual(len(child.calls), 1)
        self.assertTrue(all('--export' not in c for c in child.calls))

    def test_stale_preparation_or_source_change_never_reaches_export(self):
        for stale in (False, True):
            with self.subTest(stale=stale):
                self.source['sha256'] = 'unchanged'
                child = PreparedScreens(status='STALE' if stale else 'PREPARED',
                                        change_on_prepare=None if stale else
                                        lambda: self.source.update(sha256='changed'))
                result = self.run_pipeline(child, root_selector=lambda *_: ['0x1000'],
                                           output=self.base / f'prepare-{stale}', raw_dirs=(),
                                           export_roots=True, prepare_project=True, limit=1)
                self.assertEqual(result['stop_reason'], 'invalid_evidence' if stale else 'source_changed')
                self.assertEqual(len(child.calls), 1)

    def test_1025_targets_export_as_sequential_1024_and_one_batches(self):
        entries = range(0x2000, 0x2000 + 1025)
        initial = [row(0x1000, *(edge(e, 0x1001) for e in entries), selected=True)]
        first = [row(e) for e in range(0x2000, 0x2400)]
        second = [row(0x2400)]
        child = ChildScreens(initial, first, second, initial + first + second)
        result = self.run_pipeline(child, max_functions=1025)
        commands = [c for c in result['commands'] if c['role'] == 'dependency_export']
        self.assertEqual([len(c['targets']) for c in commands], [1024, 1])
        self.assertEqual(result['counts']['export_functions'], 1025)
        self.assertEqual(result['stop_reason'], 'closure_collected')

    def test_no_progress_does_not_export_the_same_target_again(self):
        initial = [row(0x1000, edge(0x2000, 0x1001), selected=True)]
        child = ChildScreens(initial, [row(0x2000)], initial)
        result = self.run_pipeline(child)
        self.assertEqual(result['stop_reason'], 'no_new_targets')
        self.assertEqual(len(child.calls), 3)
        self.assertEqual(result['counts']['export_functions'], 1)

    def test_tampered_plan_and_malformed_frontier_fail_with_preserved_audit(self):
        initial = [row(0x1000, edge(0x2000, 0x1001), selected=True)]
        for field, value in (('report_sha256', 'mismatch'), ('targets', [None])):
            with self.subTest(field=field):
                child = ChildScreens(initial)
                def tamper(command, log):
                    code = child(command, log)
                    path = Path(command[command.index('--output') + 1]) / 'dependency-plan.json'
                    plan = json.loads(path.read_text())
                    plan[field] = value
                    path.write_text(json.dumps(plan))
                    return code
                result = self.run_pipeline(tamper, output=self.base / field)
                self.assertEqual(result['status'], 'FAILED')
                self.assertEqual(result['stop_reason'], 'invalid_evidence')
                self.assertTrue((self.base / field / 'pipeline.json').is_file())

    def test_source_change_after_child_stops_before_dependency_exports(self):
        initial = [row(0x1000, edge(0x2000, 0x1001), selected=True)]
        child = ChildScreens(initial, change_source=lambda _: self.source.update(sha256='changed'))
        result = self.run_pipeline(child)
        self.assertEqual(result['stop_reason'], 'source_changed')
        self.assertEqual(result['status'], 'STALE')
        self.assertFalse(result['source_consistent'])
        self.assertEqual(len(child.calls), 1)

    def test_failed_child_preserves_log_and_audit_without_claiming_collection(self):
        child = ChildScreens([], fail_at=1)
        result = self.run_pipeline(child)
        self.assertEqual(result['status'], 'FAILED')
        self.assertEqual(result['stop_reason'], 'child_failed')
        self.assertEqual(result['original_status_promotions'], 0)
        self.assertFalse(result['game_executed'])
        self.assertEqual(json.loads((self.base / 'pipeline' / 'pipeline.json').read_text()), result)

    def test_empty_residual_selection_does_not_claim_collection(self):
        result = self.run_pipeline(ChildScreens([row(0x2000)]))
        self.assertEqual(result['stop_reason'], 'no_roots_selected')
        self.assertEqual(result['status'], 'STOPPED')

    def test_fresh_output_and_explicit_bounded_options(self):
        for changes in ({'max_rounds': 0}, {'max_rounds': 17}, {'max_functions': 4097},
                        {'limit': 1025}, {'raw_dirs': (), 'export_roots': False},
                        {'export_roots': True}, {'raw_dirs': (), 'export_roots': True,
                         'limit': 4, 'max_functions': 3}):
            with self.subTest(changes=changes), self.assertRaises(ValueError):
                self.run_pipeline(ChildScreens([]), **changes)
        existing = self.base / 'pipeline'
        existing.mkdir()
        with self.assertRaises(ValueError):
            self.run_pipeline(ChildScreens([]))


if __name__ == '__main__':
    unittest.main()
