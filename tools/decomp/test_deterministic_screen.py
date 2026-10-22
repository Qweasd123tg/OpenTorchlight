import copy
import builtins
import os
import json
from pathlib import Path
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

import deterministic_screen as d


def row(name, address, status='DIFF'):
    return {'name': name, 'address': address, 'status': status, 'object_digest': 'obj', 'code': 'code'}


def result(rows):
    return {'functions': rows, 'unknown': [], 'object_digest': 'obj', 'tu': 'X.cpp', 'source': 'decomp/src/X.cpp'}


class Orchestration(unittest.TestCase):
    def setUp(self):
        self.baseline = result([row('old', '0x1', 'MATCH'), row('new', '0x2'), row('alias', '0x2')])
        self.screen = result([row('new', '0x2', 'MATCH'), row('alias', '0x2', 'MATCH')])
        self.selection = {('new', '0x2'), ('alias', '0x2')}
        self.full = result([self.baseline['functions'][0]] + self.screen['functions'])

    def test_screen_is_never_acceptance_and_aliases_deduplicate(self):
        r = d.assess(self.baseline, self.screen, self.selection)
        self.assertTrue(r['screening_only'])
        self.assertFalse(r['validated_comparator_report'])
        self.assertFalse(r['promotion_authorized'])
        self.assertEqual(r['canonical_new_addresses'], ['0x2'])
        self.assertEqual(r['canonical_candidates'], [{'address': '0x2', 'category': 'strict-match-only', 'historically_tested': False, 'countable_historical_gain': False}])

    def test_full_report_keeps_all_rows_and_still_never_promotes(self):
        r = d.assess(self.baseline, self.screen, self.selection, self.full)
        self.assertTrue(r['validated_comparator_report'])
        self.assertFalse(r['promotion_authorized'])
        self.assertEqual(r['functions'], self.full['functions'])

    def test_existing_matching_alias_is_not_new_gain(self):
        self.baseline['functions'][2]['status'] = 'MATCH'
        self.assertEqual(d.assess(self.baseline, self.screen, self.selection)['canonical_new_addresses'], [])

    def test_unknown_reference_changes_reject(self):
        for target in ('screen', 'full'):
            s, f = copy.deepcopy(self.screen), copy.deepcopy(self.full)
            (s if target == 'screen' else f)['unknown'] = [{'name': 'unknown'}]
            with self.assertRaises(d.GateError): d.assess(self.baseline, s, self.selection, f)

    def test_all_prior_match_fields_must_be_preserved(self):
        for field, value in [('status', 'DIFF'), ('code', 'other'), ('metadata_reasons', ['unverified']), ('object_digest', 'other')]:
            f = copy.deepcopy(self.full); f['functions'][0][field] = value
            with self.assertRaises(d.GateError): d.assess(self.baseline, self.screen, self.selection, f)

    def test_missing_extra_duplicate_and_address_changed_rows_reject(self):
        fs = [self.full['functions'][:-1], self.full['functions'] + [row('extra', '0x4')], self.full['functions'] * 2]
        changed = copy.deepcopy(self.full['functions']); changed[-1]['address'] = '0xff'; fs.append(changed)
        for rows in fs:
            with self.assertRaises(d.GateError): d.assess(self.baseline, self.screen, self.selection, result(rows))

    def test_selected_output_incomplete_extra_and_diff_full_reject(self):
        for rows in (self.screen['functions'][:-1], self.screen['functions'] + [row('extra', '0x4')]):
            with self.assertRaises(d.GateError): d.assess(self.baseline, result(rows), self.selection)
        f = copy.deepcopy(self.full); f['functions'][1]['status'] = 'DIFF'
        with self.assertRaises(d.GateError): d.assess(self.baseline, self.screen, self.selection, f)

    def test_source_and_tu_drift_rejects_screen_and_full(self):
        for which in ('screen', 'full'):
            for field, value in [('source', 'decomp/src/other.cpp'), ('tu', 'other.cpp')]:
                screen, full = copy.deepcopy(self.screen), copy.deepcopy(self.full)
                (screen if which == 'screen' else full)[field] = value
                with self.assertRaises(d.GateError):d.assess(self.baseline, screen, self.selection, full)

    def test_unselected_diff_row_cannot_have_wrong_object(self):
        baseline = copy.deepcopy(self.baseline); baseline['functions'].append(row('neighbor', '0x3'))
        full = copy.deepcopy(self.full); full['functions'].append(row('neighbor', '0x3'))
        full['functions'][-1]['object_digest'] = 'wrong'
        with self.assertRaises(d.GateError):d.assess(baseline, self.screen, self.selection, full)

    def test_object_identity_changes_reject(self):
        s = copy.deepcopy(self.screen); s['object_digest'] = 'different'
        with self.assertRaises(d.GateError): d.assess(self.baseline, s, self.selection)

    def test_verifier_patches_restore_even_after_exception(self):
        real = lambda *a, **kw: {'new': {'norm': []}, 'other': {'norm': []}}
        module = SimpleNamespace(compile_for_diff=object(), _load_norm_cache=object(), object_functions=real)
        originals = vars(module).copy()
        with self.assertRaises(RuntimeError):
            with d.exact_object(module, '/object', ['local'], {('new', '0x2')}) as captured:
                self.assertEqual(module.compile_for_diff(), ('/object', {'local'}))
                self.assertEqual(set(module.object_functions()), {'new'})
                self.assertEqual(set(captured), {'new', 'other'})
                raise RuntimeError('test')
        self.assertEqual(vars(module), originals)


class IdentityGates(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.w = self.root / 'work'
        def file(name, text='x'):
            p = self.root / name; p.parent.mkdir(parents=True, exist_ok=True); p.write_text(text)
            return str(p)
        def entry(path):return {'path': path, 'sha256': d.sha(path)}
        def write(name, value):return file(name, json.dumps(value))
        roles = {'source': file('work/decomp/src/X.cpp'), 'object': file('unit.o'), 'database': file('db.json'),
                 'elf': file('original.elf'), 'library': file('lib/lib64/libOgreMain-1.6.5.so'),
                 'owners': write('work/decomp/owners.json', {'tus': {'X.cpp': 'owner'}}),
                 'config': write('work/decomp/config.json', {'compiler': 'pinned'}), 'objdump': file('bin/objdump')}
        self.m = {'schema': 1, 'scope': 'exact-object-single-tu', 'worktree': str(self.w), 'tu': 'X.cpp', 'owner': 'owner',
                  'inputs': {r: entry(p) for r, p in roles.items()},
                  'selected': [{'name': 'new', 'address': '0x2'}]}
        for group, path in [('tool_files', 'work/tools/decomp/objdiff.py'), ('dependencies', 'work/decomp/include/X.h'),
                            ('compiler_files', 'compiler'), ('baseline_tool_files', 'old-tools/objdiff.py'), ('provenance', 'review.json')]:
            p = file(path); self.m[group] = {p: d.sha(p)}
        common = {r: e['sha256'] for r, e in self.m['inputs'].items()}
        common.update(dependencies=self.m['dependencies'], compiler_files=self.m['compiler_files'])
        self.m['binding'] = entry(write('binding.json', {'schema': 1, 'common_identity': common, 'compiler_config': {'compiler': 'pinned'}, 'globalized': []}))
        baseline = result([row('new', '0x2')]); baseline['object_digest'] = common['object']; baseline['functions'][0]['object_digest'] = common['object']
        self.m['baseline_result'] = entry(write('baseline.json', baseline))
        self.m['baseline_receipt'] = entry(write('receipt.json', {'scope': 'full-tu', 'common_identity': common, 'result_sha256': self.m['baseline_result']['sha256'],
            'tool_files': self.m['baseline_tool_files'], 'row_keys': [['new', '0x2']]}))
        self.path = self.root / 'manifest.json'
        self.save()

    def save(self):self.path.write_text(json.dumps(self.m)); self.digest = d.sha(self.path)
    def validate(self):return d.validate_manifest(self.path, self.digest)

    def test_exact_reviewed_manifest_passes(self):self.validate()
    def test_manifest_not_auto_trusted(self):
        with self.assertRaises(d.GateError):d.validate_manifest(self.path, 'wrong')
    def test_changed_every_input_group_rejects(self):
        paths = [e['path'] for e in self.m['inputs'].values()]
        paths += [p for g in ('tool_files', 'dependencies', 'compiler_files', 'baseline_tool_files', 'provenance') for p in self.m[g]]
        paths += [self.m[r]['path'] for r in ('binding', 'baseline_result', 'baseline_receipt')]
        for p in paths:
            old = Path(p).read_bytes(); Path(p).write_bytes(old + b'changed')
            with self.assertRaises(d.GateError):self.validate()
            Path(p).write_bytes(old)
    def test_omitted_dependency_or_new_tool_rejects(self):
        for path in (self.w / 'decomp/include/new.h', self.w / 'tools/decomp/new.py'):
            path.write_text('new')
            with self.assertRaises(d.GateError):self.validate()
            path.unlink()
    def test_current_hashes_cannot_relabel_binding(self):
        p = Path(self.m['inputs']['source']['path']); p.write_text('changed')
        self.m['inputs']['source']['sha256'] = d.sha(p); self.save()
        with self.assertRaises(d.GateError):self.validate()
    def test_owner_mismatch_rejects(self):
        self.m['owner'] = 'other'; self.save()
        with self.assertRaises(d.GateError):self.validate()
    def test_binding_cannot_overwrite_source_identity(self):
        source = Path(self.m['inputs']['source']['path'])
        source.write_bytes(Path(self.m['binding']['path']).read_bytes())
        self.m['binding'] = {'path': str(source), 'sha256': d.sha(source)}
        self.save()
        with self.assertRaises(d.GateError):self.validate()

    def test_receipts_cannot_collide_even_with_equal_bytes(self):
        self.m['baseline_receipt'] = dict(self.m['binding']); self.save()
        with self.assertRaises(d.GateError):self.validate()

    def test_group_alias_cannot_hide_conflicting_digest(self):
        source = self.m['inputs']['source']['path']
        self.m['provenance'][str(Path(source).parent / '..' / 'src' / 'X.cpp')] = 'conflict'
        self.save()
        with self.assertRaises(d.GateError):self.validate()

    def test_midrun_mutation_prevents_output(self):
        output = self.root / 'report.json'
        def mutate(*args):
            Path(self.m['inputs']['source']['path']).write_text('changed during run')
            return {'validated_comparator_report': False}
        argv = ['driver', '--manifest', str(self.path), '--manifest-sha256', self.digest, '--output', str(output)]
        with patch.object(d.sys, 'argv', argv), patch.object(d, 'run', side_effect=mutate):
            with self.assertRaises(d.GateError):d.main()
        self.assertFalse(output.exists())

    def test_existing_or_worktree_output_refused_before_run(self):
        existing = self.root / 'report.json'; existing.write_text('preserve')
        for output in (existing, self.w / 'report.json', self.path):
            argv = ['driver', '--manifest', str(self.path), '--manifest-sha256', self.digest, '--output', str(output)]
            with patch.object(d.sys, 'argv', argv), patch.object(d, 'run') as run:
                with self.assertRaises(d.GateError):d.main()
                run.assert_not_called()
        self.assertEqual(existing.read_text(), 'preserve')

    def test_address_mismatch_rejects(self):
        self.m['selected'][0]['address'] = '0x99'; self.save()
        with self.assertRaises(d.GateError):self.validate()



class RunLifecycle(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(); self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        def file(name, text='x'):
            path = self.root / name; path.parent.mkdir(parents=True, exist_ok=True); path.write_text(text)
            return path
        library = file('game/lib64/libOgreMain-1.6.5.so')
        tool = file('work/tools/decomp/objdiff.py')
        objdump = file('bin/objdump'); objdump.chmod(0o755)
        db = file('db.json', '{}'); source = file('work/decomp/src/X.cpp'); obj = file('unit.o')
        self.m = {'worktree': str(self.root / 'work'), 'tool_files': {str(tool): d.sha(tool)},
                  'selected': [{'name': 'new', 'address': '0x2'}], 'inputs': {}}
        for name, path in [('library', library), ('objdump', objdump), ('database', db), ('source', source), ('object', obj), ('elf', file('original.elf'))]:
            self.m['inputs'][name] = {'path': str(path), 'sha256': d.sha(path)}
        self.baseline = result([row('old', '0x1', 'MATCH'), row('new', '0x2')])
        self.originals = []
        def original(**kwargs):
            value = SimpleNamespace(_norm_cache={}); self.originals.append(value); return value
        def compile_forbidden(*args, **kwargs):raise AssertionError('compilation forbidden')
        def objects(*args, **kwargs):return {name: {'norm': [name], 'metadata_reasons': [], 'personalities': set()} for name in ('old', 'new')}
        self.module = SimpleNamespace(__file__=str(tool), OGRE_LITERAL_SHA256=d.sha(library),
                                      literal_library_path=lambda: library, Original=original,
                                      compile_for_diff=compile_forbidden, _load_norm_cache=lambda: {'forbidden': True}, object_functions=objects)
        def compare(source, original, **kwargs):
            self.assertEqual(self.module.compile_for_diff()[0], str(obj))
            self.assertEqual(self.module._load_norm_cache(), {})
            records = self.module.object_functions()
            rows = [row(name, '0x1' if name == 'old' else '0x2', 'MATCH') for name in sorted(records)]
            original._norm_cache = {'elf:' + r['address']: {'norm': [r['name']], 'metadata_reasons': [], 'literal_proofs': ['proof']} for r in rows}
            return result(rows)
        self.module.compare_source = compare

    def execute(self, full=True, which=None):
        real_import = builtins.__import__
        def imported(name, *args, **kwargs):
            return self.module if name == 'objdiff' else real_import(name, *args, **kwargs)
        with patch('builtins.__import__', side_effect=imported), patch.object(d.sys, 'path', list(d.sys.path)), patch.dict(os.environ):
            if which is not None:
                with patch.object(d.shutil, 'which', return_value=which):return d.run(self.m, self.baseline, {'globalized': []}, full)
            return d.run(self.m, self.baseline, {'globalized': []}, full)

    def test_gain_triggers_exactly_two_cold_originals_and_complete_evidence(self):
        report = self.execute()
        self.assertEqual(len(self.originals), 2)
        self.assertIsNot(self.originals[0], self.originals[1])
        self.assertTrue(report['validated_comparator_report'])
        self.assertEqual(len(report['functions']), 2)
        self.assertEqual(set(report['screen_evidence']['original_functions']), {'elf:0x2'})
        self.assertEqual(set(report['screen_evidence']['object_functions']), {'old', 'new'})
        self.assertEqual(set(report['full_evidence']['original_functions']), {'elf:0x1', 'elf:0x2'})
        self.assertEqual(report['full_evidence']['original_functions']['elf:0x2']['literal_proofs'], ['proof'])

    def test_no_gain_does_not_trigger_full_or_validate(self):
        self.baseline['functions'][1]['status'] = 'MATCH'
        report = self.execute()
        self.assertEqual(len(self.originals), 1)
        self.assertFalse(report['validated_comparator_report'])
        self.assertTrue(report['screening_only'])
        self.assertNotIn('full_evidence', report)

    def test_without_opt_in_gain_is_screen_only(self):
        report = self.execute(False)
        self.assertEqual(len(self.originals), 1)
        self.assertFalse(report['validated_comparator_report'])

    def test_actual_objdump_path_mismatch_rejects_before_comparison(self):
        with self.assertRaises(d.GateError):self.execute(which='/different/objdump')
        self.assertEqual(self.originals, [])

if __name__ == '__main__':unittest.main()
