#!/usr/bin/env python3
import hashlib
import json
import tempfile
import threading
import unittest
from pathlib import Path
from unittest import mock

import ghidra_draft


class DraftReceipts(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.out = self.root / 'drafts'
        (self.out / 'A.cpp' / 'raw').mkdir(parents=True)
        self.patch = mock.patch.object(ghidra_draft, 'OUT', self.out)
        self.patch.start()
        self.addCleanup(self.patch.stop)
        self.db = {'original_elf_sha256': 'elf',
                   'tus': [{'id': 1, 'name': 'A.cpp'}, {'id': 2, 'name': 'B.cpp'}],
                   'functions': {'0x10': {'tu': 1}, '0x20': {'tu': 2}, '0x30': {'tu': 2}}}
        self.types = {'classes': {'Derived': {'bases': ['Base']}, 'Base': {'fields': ['int']}},
                      'prototypes': {'0x10': 'void A::run()', '0x20': 'int B::get()'},
                      'vtables': {'Base': ['get']}}
        self.raw = self.out / 'A.cpp' / 'raw' / '0x10.c'
        self.raw.write_text('void run() { return; }\n')
        self.receipt = {'schema': ghidra_draft.DRAFT_SCHEMA, 'elf': 'elf',
                        'tools': ghidra_draft.tools_digest(),
                        'types_fingerprint': ghidra_draft.types_fingerprint(self.types),
                        'exports': {'0x10': {'status': 'COMPLETE',
                                              'raw_sha256': hashlib.sha256(self.raw.read_bytes()).hexdigest()}}}
        self.save()

    def save(self):
        (self.out / 'A.cpp' / 'inputs.json').write_text(json.dumps(self.receipt))

    def state(self):
        return ghidra_draft.draft_state('A.cpp', self.db, self.types)[0]

    def test_complete_unchanged_receipt_is_fresh(self):
        self.assertEqual(self.state(), 'fresh')

    def test_partial_job_is_fresh_only_for_its_requested_addresses(self):
        self.db['functions']['0x11'] = {'tu': 1}
        self.assertEqual('stale', self.state())
        self.assertEqual('fresh', ghidra_draft.draft_state('A.cpp', self.db, self.types, addresses=['0x10'])[0])
        with self.assertRaises(ValueError):
            ghidra_draft.draft_state('A.cpp', self.db, self.types, addresses=['0x20'])

    def test_transitive_base_field_vtable_and_callee_changes_invalidate(self):
        for key, mutation in [('classes', {'Base': {'fields': ['long']}}),
                              ('vtables', {'Base': ['other']}),
                              ('prototypes', {'0x20': 'long B::get()'})]:
            with self.subTest(key=key):
                before = self.types[key]
                self.types[key] = mutation
                self.assertEqual(self.state(), 'stale')
                self.types[key] = before
        self.assertEqual(self.state(), 'fresh')

    def test_failed_missing_changed_and_legacy_drafts_are_stale(self):
        for status in ('TIMEOUT', 'TYPE_ERROR', 'NO_BODY'):
            self.receipt['exports']['0x10']['status'] = status
            self.save()
            self.assertEqual(self.state(), 'stale')
        self.receipt['exports']['0x10']['status'] = 'COMPLETE'
        self.save()
        self.raw.write_text('// no function\n')
        self.assertEqual(self.state(), 'stale')
        self.raw.unlink()
        self.assertEqual(self.state(), 'stale')
        self.receipt.pop('schema')
        self.save()
        self.assertEqual(self.state(), 'stale')

    def test_added_function_requires_completed_export(self):
        self.db['functions']['0x11'] = {'tu': 1}
        self.assertEqual(self.state(), 'stale')

    def test_direct_callees_still_in_shaping_set(self):
        insns = {'0x10': [(0x10, 'call', '20', 'B::get'), (0x15, 'jmp', '12', '')]}
        self.assertEqual(ghidra_draft.shaping_functions(self.db, 1, insns), {'0x10', '0x20'})

    def test_export_refreshes_every_api_call_and_existing_file(self):
        path = self.root / 'build-decomp' / 'types.json'
        path.parent.mkdir()
        path.write_text('{"classes":{"Old":{}}}')
        def export(*args, **kwargs):
            path.write_text(json.dumps({'classes': {'Current': {'generation': runner.call_count}}}))
        with mock.patch.object(ghidra_draft, 'ROOT', self.root), \
                mock.patch.object(ghidra_draft.subprocess, 'run', side_effect=export) as runner:
            self.assertEqual(ghidra_draft._types()['Current']['generation'], 1)
            self.assertEqual(ghidra_draft._types()['Current']['generation'], 2)

    def test_unique_jobs_and_project_lock_exclusion(self):
        base = self.root / 'work'
        (base / 'jobs').mkdir(parents=True)
        first = ghidra_draft.job_dir(base, 'drafts')
        second = ghidra_draft.job_dir(base, 'drafts')
        self.assertNotEqual(first, second)
        attempted, entered = threading.Event(), threading.Event()
        def contender():
            attempted.set()
            with ghidra_draft.file_lock(base / 'project.lock'):
                entered.set()
        with ghidra_draft.file_lock(base / 'project.lock'):
            worker = threading.Thread(target=contender)
            worker.start()
            self.assertTrue(attempted.wait(2))
            self.assertFalse(entered.wait(.05))
        worker.join(2)
        self.assertFalse(worker.is_alive())
        self.assertTrue(entered.is_set())

    def test_comment_only_complete_record_rejected(self):
        self.raw.write_text('// no function\n')
        self.raw.with_name('0x10.status.json').write_text('{"status":"COMPLETE"}')
        self.assertEqual(ghidra_draft.read_export(self.raw.parent, '0x10')['status'], 'NO_BODY')

    def test_timeout_retry_only_and_preserves_other_exports(self):
        jobs = self.root / 'work' / 'jobs'
        jobs.mkdir(parents=True)
        self.db['functions'] = {
            a: {'tu': 1, 'kind': 'function', 'address': a} for a in ('0x10', '0x11', '0x12')}
        calls = []
        def run(args, log_name, **kwargs):
            marker = args.index('DecompDrafts.java')
            target_file, out = Path(args[marker + 2]), Path(args[marker + 3])
            calls.append((target_file.read_text().splitlines(), args[marker + 4]))
            out.mkdir()
            for address in calls[-1][0]:
                status = 'TIMEOUT' if address == '0x10' and len(calls) == 1 else \
                    'TYPE_ERROR' if address == '0x12' else 'COMPLETE'
                (out / f'{address}.status.json').write_text(json.dumps({'status': status}))
                if status == 'COMPLETE':
                    (out / f'{address}.c').write_text('void function() {}\n')
            return mock.Mock(returncode=0)
        # Script copy uses the real repository; all mutable artifacts stay in this temp tree.
        with mock.patch.object(ghidra_draft.elfdb, 'load_db', return_value=self.db), \
                mock.patch.object(ghidra_draft, 'export_types', return_value=self.types), \
                mock.patch.object(ghidra_draft, 'workspace', return_value=jobs.parent), \
                mock.patch.object(ghidra_draft, 'headless', side_effect=run):
            self.assertEqual(ghidra_draft.drafts(['A.cpp'], timeout=3, retries=1), 1)
        self.assertEqual(calls, [(['0x10', '0x11', '0x12'], '3'), (['0x10'], '6')])
        receipt = json.loads((self.out / 'A.cpp' / 'inputs.json').read_text())
        self.assertEqual(receipt['exports']['0x10']['status'], 'COMPLETE')
        self.assertEqual(receipt['exports']['0x12']['status'], 'TYPE_ERROR')
        self.assertFalse((self.out / 'A.cpp' / 'raw' / '0x12.c').exists())
        self.assertEqual(self.state(), 'stale')


if __name__ == '__main__':
    unittest.main()
