"""No original/compiled program is executed by these optimizer tests."""
import copy
import json
import os
from pathlib import Path
import random
from tempfile import TemporaryDirectory
import unittest
from unittest.mock import patch

import llm_definitions as definitions
import smallmatch
import smallmatch_plan as plan
from smallmatch_trial_cache import TrialMemo, StaticInputs


def function(address='0x100', name='C::f', tu=1, **kw):
    return {'address': address, 'qualified': name, 'demangled': name + '()',
            'tu': tu, 'tu_name': 'C.cpp', 'params': '', 'cv': '', 'kind': 'function', **kw}


class DefinitionIndexTests(unittest.TestCase):
    def setUp(self):
        self.a = function()
        self.db = {'functions': {'0x100': self.a, '0x120': function('0x120'),
                  '0x130': function('0x130', 'non-virtual thunk to C::f'),
                  '0x200': function('0x200', tu=2), '0x140': function('0x140', kind='compiler')}}
        self.index = definitions.DefinitionIndex(self.db)

    def test_closure_exactly_preserves_aliases_tu_and_compiler_exclusion(self):
        self.assertEqual(definitions.closure(self.a, self.db), self.index.closure(self.a))
        self.assertEqual({'0x100', '0x120', '0x130'}, self.index.closure(self.a))

    def test_returned_set_does_not_mutate_index(self):
        self.index.closure(self.a).clear()
        self.assertEqual(3, len(self.index.closure(self.a)))

    def test_new_snapshot_after_database_change(self):
        self.db['functions']['0x150'] = function('0x150')
        self.assertNotIn('0x150', self.index.closure(self.a))
        self.assertIn('0x150', definitions.DefinitionIndex(self.db).closure(self.a))

    def test_input_objects_not_retained_or_modified(self):
        before = copy.deepcopy(self.db)
        definitions.DefinitionIndex(self.db)
        self.assertEqual(before, self.db)
        self.db['functions']['0x120']['tu'] = 99
        self.assertIn('0x120', self.index.closure(self.a))

    def test_weak_target_cannot_accept_strong_sibling(self):
        unit = {'functions': [{'address': '0x100', 'weak': True, 'status': 'MATCH'},
                              {'address': '0x120', 'status': 'MATCH'}]}
        self.assertEqual('compile-error', self.index.verdict(self.a, unit)[0])

    def test_one_bad_sibling_blocks_all(self):
        unit = {'functions': [{'address': '0x120', 'status': 'DIFF'}, {'address': '0x100', 'status': 'MATCH'}]}
        self.assertEqual(definitions.verdict(self.a, unit, self.db), self.index.verdict(self.a, unit))
        self.assertEqual('DIFF', self.index.verdict(self.a, unit)[0])

    def test_irrelevant_incomplete_row_is_ignored_like_legacy(self):
        unit = {'functions': [{'address': '0x999'}, {'address': '0x100', 'status': 'MATCH'}]}
        self.assertEqual(definitions.verdict(self.a, unit, self.db), self.index.verdict(self.a, unit))

    def test_no_status_receipts_cached(self):
        unit = {'functions': [{'address': '0x100', 'status': 'MATCH'}]}
        self.assertEqual('MATCH', self.index.verdict(self.a, unit)[0])
        unit['functions'][0]['status'] = 'DIFF'
        self.assertEqual('DIFF', self.index.verdict(self.a, unit)[0])

    def test_randomized_legacy_equivalence(self):
        rng = random.Random(731)
        for _ in range(500):
            unit = {'functions': [{'address': rng.choice(['0x100', '0x120', '0x130', '0x200', '0x999']),
                    'weak': rng.choice([False, False, True]),
                    'status': rng.choice(['MATCH', 'DIFF', 'MISSING', 'EXTRA', 'BLOCKED'])}
                    for _ in range(rng.randrange(20))]}
            targets = list(self.db['functions'].values())
            expected = [definitions.verdict(f, unit, self.db) for f in targets]
            self.assertEqual(expected, self.index.verdicts(targets, unit))

    def test_zero_targets(self):
        self.assertEqual([], self.index.verdicts([], {'functions': []}))


class SourceMaskTests(unittest.TestCase):
    def test_same_mtime_changed_bytes_refresh_parse(self):
        with TemporaryDirectory() as temp:
            g = object.__new__(smallmatch.Generator); g.root = Path(temp); g._source_masks = {}
            folder = g.root / 'decomp/src'; folder.mkdir(parents=True)
            path = folder / 'C.cpp'; path.write_text('void C::f() {}\n')
            f = function(tu_name='C.cpp')
            stat = path.stat()
            self.assertTrue(g.prior_definition(f))
            path.write_text('void C::g() {}\n'); os.utime(path, ns=(stat.st_atime_ns, stat.st_mtime_ns))
            self.assertFalse(g.prior_definition(f))
            path.unlink()
            self.assertFalse(g.prior_definition(f))

    def test_mask_is_computed_once_for_unchanged_text(self):
        with TemporaryDirectory() as temp:
            g = object.__new__(smallmatch.Generator); g.root = Path(temp); g._source_masks = {}
            folder = g.root / 'decomp/src'; folder.mkdir(parents=True)
            (folder / 'C.cpp').write_text('void C::f() {}\n')
            with patch.object(smallmatch.mutate, 'mask', wraps=smallmatch.mutate.mask) as mask:
                for _ in range(20): g.prior_definition(function(tu_name='C.cpp'))
                self.assertEqual(1, mask.call_count)


class TrialMemoTests(unittest.TestCase):
    def setUp(self):
        self.tmp = TemporaryDirectory(); self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name); self.calls = 0; self.token = 'snapshot-1'; self.error = False
        self.memo = TrialMemo(self.evaluate, self.render, lambda: self.token)

    def render(self, rows):
        return '\n'.join(r['source'] for r in rows)

    def evaluate(self, rows, phase, address):
        self.calls += 1
        path = self.root / ('trial-' + str(self.calls) + '.cpp'); path.write_text(self.render(rows))
        result = {'_trial_source': str(path), 'object_digest': 'complete-object-fixture',
                  'functions': [{'address': '0x100', 'status': 'DIFF'}]}
        if self.error: result['error'] = 'temporary compiler error'
        return result

    def trial(self, source='void C::f() {}', memo=None):
        return (memo or self.memo)([{'source': source}], 'retry', '0x100')

    def test_exact_repeat_reuses_original_source_receipt(self):
        a, b = self.trial(), self.trial()
        self.assertEqual(1, self.calls); self.assertEqual(a, b)
        self.assertEqual(1, self.memo.stats['hits'])

    def test_any_other_definition_change_invalidates(self):
        self.trial(); self.trial('void C::f() {}\nvoid C::other() {}')
        self.assertEqual(2, self.calls)

    def test_input_token_change_requires_new_comparison(self):
        self.trial(); self.token = 'changed-header-toolchain-or-config'; self.trial()
        self.assertEqual(2, self.calls)

    def test_missing_input_fingerprint_disables_cache(self):
        self.token = None; self.trial(); self.trial()
        self.assertEqual(2, self.calls)

    def test_cached_result_cannot_be_mutated(self):
        a = self.trial(); a['functions'][0]['status'] = 'MATCH'
        self.assertEqual('DIFF', self.trial()['functions'][0]['status'])

    def test_deleted_source_is_not_a_valid_receipt(self):
        a = self.trial(); Path(a['_trial_source']).unlink(); self.trial()
        self.assertEqual(2, self.calls)

    def test_modified_source_is_not_a_valid_receipt(self):
        a = self.trial(); Path(a['_trial_source']).write_text('changed'); self.trial()
        self.assertEqual(2, self.calls)

    def test_clock_or_path_macros_bypass(self):
        for macro in ('__DATE__', '__TIME__', '__FILE__', '__BASE_FILE__', '__TIMESTAMP__'):
            before = self.calls; self.trial(macro); self.trial(macro)
            self.assertEqual(before + 2, self.calls)

    def test_compiler_errors_are_retried(self):
        self.error = True; self.trial(); self.trial()
        self.assertEqual(2, self.calls); self.assertEqual(2, self.memo.stats['errors_not_cached'])

    def test_input_change_during_comparison_aborts(self):
        def changing(*args):
            result = self.evaluate(*args); self.token = 'new'; return result
        memo = TrialMemo(changing, self.render, lambda: self.token)
        with self.assertRaisesRegex(RuntimeError, 'changed'):
            self.trial(memo=memo)

    def test_eviction_is_bounded(self):
        memo = TrialMemo(self.evaluate, self.render, lambda: self.token, max_entries=1)
        self.trial('a', memo); self.trial('b', memo); self.trial('a', memo)
        self.assertEqual(3, self.calls); self.assertEqual(2, memo.stats['evictions'])

    def test_no_cache_across_instances(self):
        self.trial(); other = TrialMemo(self.evaluate, self.render, lambda: self.token)
        self.trial(memo=other); self.assertEqual(2, self.calls)

    def test_full_project_verifier_does_not_use_trial_cache(self):
        path = Path(__file__).with_name('smallmatch_verify.py')
        self.assertNotIn('TrialMemo', path.read_text())


class PlanningTests(unittest.TestCase):
    def setUp(self):
        self.targets = {'0x100': function(size=20), '0x120': function('0x120', size=30)}
        self.ledger = [{'address': '0x100', 'status': 'MATCH', 'original_size': 20},
                       {'address': '0x120', 'status': 'BLOCKED', 'original_size': 30}]
        self.summary = {'original_elf_sha256': 'ELF', 'target_count': 2, 'new_match_count': 1}

    def test_valid_history_does_not_create_new_matches(self):
        self.assertEqual({'0x100'}, plan.historical_ids(self.targets, self.ledger, self.summary, 'ELF'))

    def test_wrong_original_is_rejected(self):
        with self.assertRaises(ValueError): plan.historical_ids(self.targets, self.ledger, self.summary, 'OTHER')

    def test_partial_history_is_rejected(self):
        with self.assertRaises(ValueError): plan.historical_ids(self.targets, self.ledger[:1], self.summary, 'ELF')

    def test_duplicate_history_is_rejected(self):
        with self.assertRaises(ValueError): plan.historical_ids(self.targets, self.ledger * 2, self.summary, 'ELF')

    def test_size_change_is_rejected(self):
        self.ledger[0]['original_size'] = 99
        with self.assertRaises(ValueError): plan.historical_ids(self.targets, self.ledger, self.summary, 'ELF')

    def test_no_double_count_of_abi_aliases(self):
        db = {'functions': self.targets}
        groups = plan.definition_groups(self.targets, db, set())
        self.assertEqual(1, len(groups)); self.assertEqual(2, len(groups[0][1]))

    def test_large_sibling_is_visible_and_not_scheduled_as_small(self):
        db = {'functions': {**self.targets, '0x150': function('0x150', size=1000)}}
        groups = plan.definition_groups(self.targets, db, set())
        self.assertEqual(['0x150'], groups[0][3])

    def test_path_traversal_rejected(self):
        with TemporaryDirectory() as tmp:
            with self.assertRaises(ValueError): plan.safe_child(tmp, '../escape.asm')


class InputFingerprintTests(unittest.TestCase):
    def setUp(self):
        self.temp = TemporaryDirectory(); self.addCleanup(self.temp.cleanup)
        self.base = Path(self.temp.name)
        self.kit, self.root, self.prior, self.cc = [self.base / n for n in ('kit', 'root', 'prior', 'gcc')]
        for p in (self.kit/'original', self.kit/'reference', self.root/'decomp/include',
                  self.root/'tools/decomp', self.root/'third_party', self.prior, self.cc/'usr/bin'):
            p.mkdir(parents=True)
        for path in (self.kit/'original/Torchlight.bin.x86_64', self.kit/'targets.json',
                     self.kit/'reference/elfdb.json', self.kit/'reference/types.json',
                     self.root/'decomp/config.json', self.cc/'usr/bin/g++'):
            path.write_text('static test input, never executed')
        self.catalog = self.base/'catalog.json'; self.catalog.write_text('{}')
        self.guard = StaticInputs(self.kit, self.root, self.prior, self.catalog, self.cc, {})

    def test_identical_snapshot_is_stable(self):
        a = self.guard(); self.assertIsNotNone(a); self.assertEqual(a, self.guard())

    def test_header_addition_and_deletion_invalidate(self):
        a = self.guard(); header = self.root/'decomp/include/new.h'; header.write_text('void f();')
        b = self.guard(); self.assertNotEqual(a, b)
        header.unlink(); self.assertEqual(a, self.guard())

    def test_same_stat_header_edit_still_invalidates(self):
        header = self.root/'decomp/include/C.h'; header.write_text('int x;')
        a = self.guard(); st = header.stat(); header.write_text('int y;')
        os.utime(header, ns=(st.st_atime_ns, st.st_mtime_ns))
        self.assertNotEqual(a, self.guard())

    def test_pinned_compiler_change_invalidates(self):
        a = self.guard(); (self.cc/'usr/bin/g++').write_text('changed compiler fixture')
        self.assertNotEqual(a, self.guard())

    def test_missing_compiler_disables_reuse(self):
        (self.cc/'usr/bin/g++').unlink(); self.assertIsNone(self.guard())

    def test_environment_changes_invalidate_without_logging_values(self):
        a = self.guard()
        with patch.dict(os.environ, {'OTL_TEST_PRIVATE_MARKER': 'not-to-be-logged'}):
            b = self.guard(); self.assertNotEqual(a, b); self.assertEqual(64, len(b))

    def test_unknown_configured_include_disables_reuse(self):
        other = StaticInputs(self.kit, self.root, self.prior, self.catalog, self.cc,
                             {'include': ['missing-folder']})
        self.assertIsNone(other())

    def test_clock_macro_in_header_disables_reuse(self):
        (self.root/'decomp/include/clock.h').write_text('const char* date = __TIME__;')
        self.assertIsNone(self.guard())

    def test_original_change_invalidates(self):
        a = self.guard(); (self.kit/'original/Torchlight.bin.x86_64').write_text('other ELF')
        self.assertNotEqual(a, self.guard())


if __name__ == '__main__':
    unittest.main()
