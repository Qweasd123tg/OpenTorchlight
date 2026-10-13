"""Synthetic only: no compiler, original executable, model, or submitted code runs."""
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import candidate
import publication
from test_publication_recovery import fixture


class Continuation(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = fixture(self.temp.name)
        self.stage = publication.Stage(self.root)
        self.source = self.stage.path / 'decomp/src/A.cpp'
        self.source.write_text('golden candidate')
        self.spec = {'schema': 1, 'tu': 'A.cpp', 'addresses': ['0x100'],
                     'focused': ['Control.cpp'], 'regression': ['Control.cpp'],
                     'controls': [{'name': 'change', 'old': 'golden', 'new': 'mutant', 'count': 1,
                                   'test': 'compare_a', 'address': '0x100'}]}
        identity = patch.object(candidate.Cycle, '_identity', lambda c: {
            'spec': c.spec, 'tree': publication.tree_state(c.stage.path), 'inputs': 'pinned'})
        identity.start()
        self.addCleanup(identity.stop)
        self.calls = []
        self.fail_phase = None
        self.compare = patch.object(candidate.Cycle, '_compare', lambda c: self.action('compare'))
        self.compare.start()
        self.addCleanup(self.compare.stop)
        self.tests = patch.object(candidate.Cycle, '_tests', lambda c, name, fixtures, control=None: self.action(name))
        self.tests.start()
        self.addCleanup(self.tests.stop)
        self.validate = patch.object(publication.Stage, 'validate', lambda stage: self.validate_stage(stage))
        self.validate.start()
        self.addCleanup(self.validate.stop)
        self.publish = patch.object(publication.Stage, 'publish', lambda s: self.action('publish') or ['decomp/src/A.cpp'])
        self.publish.start()
        self.addCleanup(self.publish.stop)

    def action(self, name):
        self.calls.append(name)
        if self.fail_phase == name:
            raise RuntimeError('deliberate ' + name)
        if name == 'publish':
            return {}
        work = self.stage.path / 'build-decomp/candidate-cycle'
        import hashlib
        names = [name + '.json'] if name == 'compare' else [name + '.json', name + '.log']
        artifacts = {}
        for artifact in names:
            (work / artifact).write_bytes(b'{}')
            artifacts[artifact] = hashlib.sha256(b'{}').hexdigest()
        return {'artifacts': artifacts}

    def validate_stage(self, stage):
        self.calls.append('gate')
        if self.fail_phase == 'gate':
            raise RuntimeError('deliberate gate')
        stage.validated = publication.tree_state(stage.path)
        stage.validated_inputs = 'pinned'
        stage.final_objects = {}
        stage.validated_fixtures = {}
        stage.report = []
        stage.covered = {'0x100'}
        stage.final_units = []
        stage.baseline_units = []

    def cycle(self):
        return candidate.Cycle(self.stage, self.spec)

    def request(self, cycle, action='publish'):
        request = {'action': action, 'identity_sha256': cycle.state['identity_sha256']}
        if action == 'publish':
            request['inputs_digest'] = 'pinned'
        return request

    def test_batch_resume_runs_only_missing_gate_keeps_live_stage(self):
        first = self.cycle()
        self.assertEqual(first.run()['status'], 'READY_FOR_GATE')
        calls = list(self.calls)
        second = self.cycle()
        self.assertEqual(second.run(True)['status'], 'AWAITING_RELEASE')
        self.assertEqual(self.calls, calls + ['gate'])
        self.assertIs(second.stage, self.stage)
        self.assertEqual(second.release(self.request(second))['status'], 'PUBLISHED')
        self.assertEqual(self.calls.count('gate'), 1)

    def test_saved_gate_cannot_restore_validation(self):
        first = self.cycle()
        first.run(True)
        second = self.cycle()
        self.assertEqual(second.run(True)['status'], 'REVALIDATION_REQUIRED')
        with self.assertRaises(RuntimeError):
            second.release(self.request(second))
        self.assertEqual(self.calls.count('gate'), 1)

    def test_fail_closed_at_each_phase_and_restore_golden(self):
        for phase in ['compare', 'focused', 'control-change', 'regression', 'gate']:
            with self.subTest(phase=phase):
                self.fail_phase = phase
                self.calls.clear()
                work = self.stage.path / 'build-decomp/candidate-cycle'
                if (work / 'checkpoint.json').exists():
                    (work / 'checkpoint.json').unlink()
                cycle = self.cycle()
                self.assertEqual(cycle.run(True)['status'], 'STOPPED')
                self.assertEqual(self.calls[-1], phase)
                self.assertEqual(self.source.read_text(), 'golden candidate')
                before = list(self.calls)
                cycle.run(True)
                self.assertEqual(self.calls, before)

    def test_stale_source_and_spec_rejected(self):
        self.cycle().run()
        self.source.write_text('different')
        with self.assertRaisesRegex(RuntimeError, 'inputs changed'):
            self.cycle()
        self.source.write_text('golden candidate')
        self.spec['controls'][0]['new'] = 'other'
        with self.assertRaisesRegex(RuntimeError, 'specification changed'):
            self.cycle()

    def test_corrupt_checkpoint_and_artifact_rejected(self):
        cycle = self.cycle()
        cycle.path.write_text('broken')
        with self.assertRaises(ValueError):
            self.cycle()
        cycle._save()
        cycle.state['phases']['compare'] = {'status': 'PASS', 'artifacts': cycle._artifact('compare.json', {})}
        cycle._save()
        (cycle.work / 'compare.json').write_text('changed')
        with self.assertRaisesRegex(RuntimeError, 'corrupt'):
            self.cycle()

    def test_interrupt_mutation_cleanup_and_durable_recovery(self):
        cycle = self.cycle()
        with patch.object(cycle, '_tests', side_effect=KeyboardInterrupt):
            with self.assertRaises(KeyboardInterrupt):
                cycle._control(self.spec['controls'][0])
        self.assertEqual(self.source.read_text(), 'golden candidate')
        # Simulate SIGKILL after durable journal and mutant write, before finally.
        golden = self.source.read_bytes()
        cycle._artifact('golden-source.bin', golden)
        mutant = b'mutant candidate'
        import hashlib
        cycle.state['mutation'] = {'source': 'decomp/src/A.cpp', 'identity_sha256': cycle.state['identity_sha256'],
                                   'backup': 'golden-source.bin', 'golden': hashlib.sha256(golden).hexdigest(),
                                   'mutant': hashlib.sha256(mutant).hexdigest()}
        cycle._save()
        self.source.write_bytes(mutant)
        restored = self.cycle()
        self.assertEqual(self.source.read_bytes(), golden)
        self.assertNotIn('mutation', restored.state)

    def test_invalid_release_and_cancel_never_publish(self):
        cycle = self.cycle()
        cycle.run(True)
        with self.assertRaises(RuntimeError):
            cycle.release({'action': 'publish'})
        self.assertEqual(cycle.state['status'], 'AWAITING_RELEASE')
        cycle.release(self.request(cycle, 'cancel'))
        with self.assertRaises(RuntimeError):
            cycle.release(self.request(cycle))
        self.assertNotIn('publish', self.calls)

    def test_post_gate_receipt_failure_never_repeats_gate(self):
        cycle = self.cycle()
        with patch.object(cycle, '_gate_receipt', side_effect=OSError('disk full')):
            self.assertEqual(cycle.run(True)['status'], 'RECEIPT_ERROR')
        self.assertTrue(cycle.live_gate)
        cycle.persist_gate_receipt()
        self.assertEqual(cycle.state['status'], 'AWAITING_RELEASE')
        cycle.release(self.request(cycle))
        self.assertEqual(self.calls.count('gate'), 1)

    def test_changed_mutant_source_not_overwritten_on_recovery(self):
        cycle = self.cycle()
        import hashlib
        cycle._artifact('golden-source.bin', b'golden candidate')
        cycle.state['mutation'] = {'source': 'decomp/src/A.cpp', 'identity_sha256': cycle.state['identity_sha256'],
                                   'backup': 'golden-source.bin', 'golden': hashlib.sha256(b'golden candidate').hexdigest(),
                                   'mutant': hashlib.sha256(b'mutant candidate').hexdigest()}
        cycle._save()
        self.source.write_text('independent change')
        with self.assertRaisesRegex(RuntimeError, 'source changed'):
            self.cycle()
        self.assertEqual(self.source.read_text(), 'independent change')

class ComparativeOutcomes(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = fixture(self.temp.name)
        self.stage = publication.Stage(self.root)
        self.spec = {'schema': 1, 'tu': 'A.cpp', 'addresses': ['0x100'],
                     'focused': ['Control.cpp'], 'regression': ['Control.cpp'],
                     'controls': [{'name': 'change', 'old': 'old', 'new': 'new', 'count': 1,
                                   'test': 'compare_a', 'address': '0x100'}]}
        (self.stage.path / 'decomp/hybrid/tests/Control.cpp').write_text('TL_TEST(compare_a) {}')
        self.blob = self.stage.path / 'blob.so'
        self.loader = self.stage.path / 'loader.so'
        self.blob.write_bytes(b'blob')
        self.loader.write_bytes(b'loader')
        identity = patch.object(candidate.Cycle, '_identity', lambda c: {'spec': c.spec, 'fixed': True})
        identity.start()
        self.addCleanup(identity.stop)
        self.cycle = candidate.Cycle(self.stage, self.spec)
        self.cycle.state['phase'] = 'focused'
        self.cycle.state['phases']['focused'] = {'status': 'RUNNING'}
        import hybrid
        build = patch.object(hybrid, 'build', return_value=(self.blob, self.loader))
        build.start()
        self.addCleanup(build.stop)

    def check_report(self, code, report, negative=False, *, label='focused', begin=True):
        import hybrid
        if begin:
            report = ['tlhybrid: begin compare_a'] + report
        with patch.object(hybrid, 'selftest', return_value=(code, report)):
            return self.cycle._tests(label, ['Control.cpp'], self.spec['controls'][0] if negative else None)

    def test_complete_equal_original_candidate_passes(self):
        self.check_report(0, ['    coverage compare_a 0x100 completed 3 different 0 incomplete 0',
                              'tlhybrid: compare_a PASS (0)'])

    def test_only_completed_semantic_difference_kills_control(self):
        self.check_report(1, ['    coverage compare_a 0x100 completed 3 different 1 incomplete 0',
                              'tlhybrid: compare_a FAIL (1)'], True)

    def test_crash_timeout_incomplete_or_missing_comparisons_fail_closed(self):
        for code, lines in [
            (2, ['    coverage compare_a 0x100 completed 3 different 1 incomplete 0', 'tlhybrid: compare_a FAIL (1)']),
            (-11, ['tlhybrid: compare_a FAIL (1)']),
            (1, ['    coverage compare_a 0x100 completed 0 different 1 incomplete 1', 'tlhybrid: compare_a FAIL (1)']),
            (1, ['    coverage compare_a 0x100 completed 3 different 0 incomplete 0', 'tlhybrid: compare_a FAIL (1)']),
            (1, ['    coverage compare_a 0x100 completed 3 different 1 incomplete 0']),
            (0, ['tlhybrid: compare_a PASS (0)']),
        ]:
            with self.subTest(code=code, lines=lines):
                with self.assertRaisesRegex(RuntimeError, 'incomplete comparative'):
                    self.check_report(code, lines, code != 0)

    def test_unexpected_extra_test_or_failure_is_not_killed(self):
        for extra in ['tlhybrid: surprise PASS (0)', 'tlhybrid: surprise FAIL (1)']:
            with self.assertRaises(RuntimeError):
                self.check_report(1, ['    coverage compare_a 0x100 completed 3 different 1 incomplete 0',
                                      'tlhybrid: compare_a FAIL (1)', extra], True)

class InputIdentity(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = fixture(self.temp.name)
        tool = self.root / 'tools/decomp/candidate.py'
        tool.parent.mkdir(parents=True)
        tool.write_bytes(Path(candidate.__file__).read_bytes())
        self.stage = publication.Stage(self.root)
        self.spec = {'schema': 1, 'tu': 'A.cpp', 'addresses': ['0x100'],
                     'focused': ['Control.cpp'], 'regression': ['Control.cpp'],
                     'controls': [{'name': 'change', 'old': 'old', 'new': 'new', 'count': 1,
                                   'test': 'compare_a', 'address': '0x100'}]}
        self.context = {'db': 'database', 'types': 'types'}
        packet = self.stage.path / 'build-decomp/llm-loop/A.cpp'
        (packet / 'prompts').mkdir(parents=True)
        (packet / 'prompts/0x100.md').write_text('prepared original instructions')
        (packet / 'result.json').write_text(json.dumps({'prepared': True, 'blocked': {}}))
        (packet / 'checkpoint.json').write_text(json.dumps({
            'settings': {'selected': [{'address': '0x100'}]}, 'inputs': self.context,
            'tree': publication.tree_state(self.stage.path)}))
        self.packet = packet
        import llm_loop
        for stub in [patch.object(llm_loop, 'packet_inputs', side_effect=lambda p: self.context),
                     patch.object(publication.Stage, '_input_digest', return_value='external')]:
            stub.start()
            self.addCleanup(stub.stop)

    def test_real_identity_permits_source_fixture_input_then_pins_it(self):
        (self.stage.path / 'decomp/src/A.cpp').write_text('candidate')
        (self.stage.path / 'decomp/hybrid/tests/Control.cpp').write_text('test specification')
        c = candidate.Cycle(self.stage, self.spec)
        again = candidate.Cycle(self.stage, self.spec)
        self.assertEqual(c.state['identity_sha256'], again.state['identity_sha256'])
        (self.stage.path / 'decomp/src/A.cpp').write_text('different candidate')
        with self.assertRaisesRegex(RuntimeError, 'inputs changed'):
            candidate.Cycle(self.stage, self.spec)

    def test_stale_packet_context_is_rejected_even_on_first_run(self):
        self.context['types'] = 'changed'
        with self.assertRaisesRegex(RuntimeError, 'prepared context changed'):
            candidate.Cycle(self.stage, self.spec)

    def test_header_change_requires_fresh_prepare(self):
        (self.stage.path / 'decomp/include/Shared.h').write_text('new header')
        with self.assertRaisesRegex(RuntimeError, 'prepared source/header/tool'):
            candidate.Cycle(self.stage, self.spec)

    def test_staged_tool_change_rejected(self):
        (self.stage.path / 'tools/decomp/candidate.py').write_text('changed')
        with self.assertRaisesRegex(RuntimeError, 'staged tools'):
            candidate.Cycle(self.stage, self.spec)

    def test_running_implementation_change_rejected(self):
        tool = self.root / 'tools/decomp/candidate.py'
        tool.write_text('old implementation')
        self.stage = publication.Stage(self.root)
        with self.assertRaisesRegex(RuntimeError, 'loaded tools'):
            candidate.Cycle(self.stage, self.spec)

    def test_external_context_and_artifact_change_invalidate_resume(self):
        candidate.Cycle(self.stage, self.spec)
        with patch.object(publication.Stage, '_input_digest', return_value='changed external'):
            with self.assertRaisesRegex(RuntimeError, 'inputs changed'):
                candidate.Cycle(self.stage, self.spec)
        (self.packet / 'prompts/0x100.md').write_text('different prepared prompt')
        with self.assertRaisesRegex(RuntimeError, 'inputs changed'):
            candidate.Cycle(self.stage, self.spec)


class ReviewRegressions(Continuation):
    def test_checksum_rejects_changed_status_before_recovery(self):
        cycle = self.cycle()
        data = json.loads(cycle.path.read_text())
        data['status'] = 'READY_FOR_GATE'
        cycle.path.write_text(json.dumps(data))
        with self.assertRaisesRegex(RuntimeError, 'checkpoint checksum'):
            self.cycle()

    def test_pass_without_required_artifacts_is_rejected(self):
        cycle = self.cycle()
        cycle.run()
        cycle.state['phases']['focused']['artifacts'] = {}
        cycle._save()
        with self.assertRaisesRegex(RuntimeError, 'missing successful phase receipts'):
            self.cycle()

    def test_missing_preceding_phase_is_rejected(self):
        cycle = self.cycle()
        cycle.run()
        del cycle.state['phases']['focused']
        cycle._save()
        with self.assertRaisesRegex(RuntimeError, 'out-of-order'):
            self.cycle()

    def test_changed_spec_cannot_recover_into_other_tu(self):
        cycle = self.cycle()
        import hashlib
        cycle._artifact('golden-source.bin', b'golden candidate')
        cycle.state['mutation'] = {'source': 'decomp/src/A.cpp', 'identity_sha256': cycle.state['identity_sha256'],
                                   'backup': 'golden-source.bin', 'golden': hashlib.sha256(b'golden candidate').hexdigest(),
                                   'mutant': hashlib.sha256(b'mutant candidate').hexdigest()}
        cycle._save()
        self.source.write_text('mutant candidate')
        other = self.stage.path / 'decomp/src/B.cpp'
        other.write_text('mutant candidate')
        self.spec['tu'] = 'B.cpp'
        with self.assertRaisesRegex(RuntimeError, 'specification changed'):
            self.cycle()
        self.assertEqual(other.read_text(), 'mutant candidate')
        self.assertEqual(self.source.read_text(), 'mutant candidate')

    def test_concurrent_control_edit_is_not_erased(self):
        cycle = self.cycle()
        def edit(*args):
            self.source.write_text('independent correction')
            return {}
        with patch.object(cycle, '_tests', side_effect=edit):
            with self.assertRaisesRegex(RuntimeError, 'source changed during control'):
                cycle._control(self.spec['controls'][0])
        self.assertEqual(self.source.read_text(), 'independent correction')
        self.assertIn('mutation', cycle.state)

    def test_real_compiler_systemexit_returns_compact_stop(self):
        cycle = self.cycle()
        with patch.object(cycle, '_compare', side_effect=SystemExit('compiler diagnostics')):
            self.assertEqual(cycle.run(True)['status'], 'STOPPED')
        summary = cycle.summary()
        self.assertEqual(summary['phase'], 'compare')
        self.assertEqual(summary['error'], 'compiler diagnostics')
        self.assertTrue(Path(summary['evidence'][0]).is_file())
        self.assertNotIn('gate', self.calls)

    def test_publication_failure_stops_without_retry_or_gate_loss(self):
        cycle = self.cycle()
        cycle.run(True)
        with patch.object(self.stage, 'publish', side_effect=RuntimeError('publication changed input')) as publish:
            with self.assertRaisesRegex(RuntimeError, 'publication stopped'):
                cycle.release(self.request(cycle))
            self.assertEqual(cycle.state['status'], 'PUBLICATION_FAILED')
            self.assertIsNone(cycle.state['published'])
            self.assertIn('unknown', cycle.state['publication_outcome'])
            self.assertTrue(cycle.live_gate)
            self.assertEqual(cycle.run(True)['status'], 'PUBLICATION_FAILED')
            with self.assertRaises(RuntimeError):
                cycle.release(self.request(cycle))
            self.assertEqual(publish.call_count, 1)
        cycle.release(self.request(cycle, 'cancel'))
        self.assertEqual(cycle.state['status'], 'CANCELLED')

    def test_publication_configuration_failure_is_also_uncertain_and_terminal(self):
        cycle = self.cycle()
        cycle.run(True)
        with patch.object(self.stage, 'publish', side_effect=ValueError('invalid job configuration')):
            with self.assertRaisesRegex(RuntimeError, 'publication stopped'):
                cycle.release(self.request(cycle))
        self.assertEqual(cycle.run(True)['status'], 'PUBLICATION_FAILED')
        self.assertIsNone(cycle.state['published'])

    def test_release_wait_cancels_before_broken_receipt_retry(self):
        cycle = self.cycle()
        cycle.run(True)
        cycle.state['status'] = 'RECEIPT_ERROR'
        spec_path = self.root / 'spec.json'
        spec_path.write_text(json.dumps(self.spec))
        release = self.root / 'release.json'
        release.write_text(json.dumps(self.request(cycle, 'cancel')))
        import parallel
        with patch.object(candidate, 'Cycle', return_value=cycle), \
                patch.object(publication.Stage, 'resume', return_value=self.stage), \
                patch.object(parallel, 'owned_by_others', return_value=None), \
                patch.object(cycle, 'run', return_value=cycle.state), \
                patch.object(cycle, 'persist_gate_receipt', side_effect=OSError('disk full')) as persist:
            result = candidate.continue_cycle('A.cpp', self.stage.path, spec_path, True, release)
        self.assertEqual(result['status'], 'CANCELLED')
        persist.assert_not_called()


    def test_malformed_release_does_not_block_receipt_repair(self):
        cycle = self.cycle()
        cycle.run(True)
        cycle.state['status'] = 'RECEIPT_ERROR'
        spec_path = self.root / 'spec.json'
        spec_path.write_text(json.dumps(self.spec))
        release = self.root / 'release.json'
        release.write_text('malformed')
        import parallel
        import time
        import io
        def next_poll(_):
            release.write_text(json.dumps(self.request(cycle, 'cancel')))
        with patch.object(candidate, 'Cycle', return_value=cycle), \
                patch.object(publication.Stage, 'resume', return_value=self.stage), \
                patch.object(parallel, 'owned_by_others', return_value=None), \
                patch.object(cycle, 'run', return_value=cycle.state), \
                patch.object(cycle, 'persist_gate_receipt', wraps=cycle.persist_gate_receipt) as persist, \
                patch.object(time, 'sleep', side_effect=next_poll), patch('sys.stdout', new_callable=io.StringIO) as output:
            result = candidate.continue_cycle('A.cpp', self.stage.path, spec_path, True, release)
        self.assertEqual(result['status'], 'CANCELLED')
        self.assertEqual(persist.call_count, 1)
        self.assertIn('AWAITING_RELEASE', output.getvalue())

    def test_malformed_spec_types_fail_as_admission_errors(self):
        for spec in [None, [], {'unexpected': True}, dict(self.spec, tu=1),
                     dict(self.spec, addresses=[{}]), dict(self.spec, focused=[1]),
                     dict(self.spec, controls=[None]), dict(self.spec, controls='command')]:
            with self.subTest(spec=spec), self.assertRaises(ValueError):
                candidate.Cycle(self.stage, spec)

    def test_nested_fixture_not_advertised_as_canonical_input(self):
        nested = self.stage.path / 'decomp/hybrid/tests/nested/Probe.cpp'
        nested.parent.mkdir()
        nested.write_text('TL_TEST(probe) {}')
        self.spec['focused'] = ['nested/Probe.cpp']
        with self.assertRaisesRegex(ValueError, 'missing fixture'):
            self.cycle()


class CoverageReviewRegressions(ComparativeOutcomes):
    def test_contradictory_incomplete_zero_coverage_rejected(self):
        for bad in ['    coverage compare_a 0x100 completed 1 different 0 incomplete 1',
                    '    coverage compare_a 0x100 completed 1 different 1 incomplete 0',
                    '    coverage compare_a 0x100 completed 0 different 0 incomplete 0']:
            with self.assertRaises(RuntimeError):
                self.check_report(0, ['    coverage compare_a 0x100 completed 3 different 0 incomplete 0',
                                      bad, 'tlhybrid: compare_a PASS (0)'])


class FramedCoverage(ComparativeOutcomes):
    def test_positive_alias_repeats_and_child_labels_are_diagnostics(self):
        rows = ['    coverage compare_a 0x100 completed 3 different 0 incomplete 0',
                '    coverage compare_a 0x100 completed 3 different 0 incomplete 0',
                '    coverage child_lane 0x200 completed 2 different 0 incomplete 0',
                '    coverage listener accepted-controller integration (supplemental) 0x300 completed 4 different 0 incomplete 0',
                'tlhybrid: compare_a PASS (0)']
        self.check_report(0, rows)
        self.check_report(0, rows, label='regression')

    def test_supplemental_free_label_counts_are_checked(self):
        for counts in ('completed 0 different 0 incomplete 0', 'completed 4 different 1 incomplete 0',
                       'completed 4 different 0 incomplete 1'):
            with self.subTest(counts=counts), self.assertRaises(RuntimeError):
                self.check_report(0, ['    coverage compare_a 0x100 completed 3 different 0 incomplete 0',
                                      '    coverage listener accepted-controller integration (supplemental) 0x300 ' + counts,
                                      'tlhybrid: compare_a PASS (0)'], label='regression')

    def test_child_label_does_not_satisfy_focused_target(self):
        with self.assertRaises(RuntimeError):
            self.check_report(0, ['    coverage child_lane 0x100 completed 3 different 0 incomplete 0',
                                  'tlhybrid: compare_a PASS (0)'])

    def test_child_label_does_not_kill_control(self):
        with self.assertRaises(RuntimeError):
            self.check_report(1, ['    coverage child_lane 0x100 completed 3 different 1 incomplete 0',
                                  'tlhybrid: compare_a FAIL (1)'], True)

    def test_each_repeated_control_row_is_checked(self):
        for bad in ['completed 0 different 0 incomplete 0',
                    'completed 1 different 0 incomplete 1',
                    'completed 1 different 2 incomplete 0']:
            with self.subTest(bad=bad), self.assertRaises(RuntimeError):
                self.check_report(1, ['    coverage compare_a 0x100 completed 3 different 1 incomplete 0',
                                      '    coverage compare_a 0x100 ' + bad,
                                      'tlhybrid: compare_a FAIL (1)'], True)

    def test_control_witness_must_belong_to_failing_enclosing_test(self):
        fixture = self.stage.path / 'decomp/hybrid/tests/Control.cpp'
        fixture.write_text(fixture.read_text() + '\nTL_TEST(other_test) {}\n')
        report = ['tlhybrid: begin compare_a', 'tlhybrid: compare_a FAIL (1)',
                  'tlhybrid: begin other_test',
                  '    coverage compare_a 0x100 completed 3 different 1 incomplete 0',
                  'tlhybrid: other_test PASS (0)']
        with self.assertRaises(RuntimeError):
            self.check_report(1, report, True, begin=False)

    def test_invalid_framing_fails_closed(self):
        coverage = '    coverage compare_a 0x100 completed 3 different 0 incomplete 0'
        begin, end = 'tlhybrid: begin compare_a', 'tlhybrid: compare_a PASS (0)'
        for rows in [[coverage, end], [begin, coverage], [begin, begin, coverage, end],
                     [begin, coverage, end, end], [begin, coverage, end, begin, end],
                     [begin, coverage, 'tlhybrid: other PASS (0)'],
                     ['tlhybrid: begin other', coverage, 'tlhybrid: other PASS (0)'],
                     [begin, coverage, end, coverage], [begin, '    coverage malformed', end]]:
            with self.subTest(rows=rows), self.assertRaises(RuntimeError):
                self.check_report(0, rows, begin=False)


class LoaderFrameParser(unittest.TestCase):
    def test_legacy_descriptive_child_and_alias_rows_are_not_summed(self):
        report = [
            'tlhybrid: begin quest_destructor_owned_lifetime',
            '    coverage quest_destructor_owned_lifetime 0xd1a390 completed 22 different 0 incomplete 0',
            '    coverage quest_deleting_lifetime 0xd1b5c0 completed 10 different 0 incomplete 0',
            'tlhybrid: timing quest_destructor_owned_lifetime 0.223 seconds',
            'tlhybrid: quest_destructor_owned_lifetime PASS (0)',
            'tlhybrid: begin questmanager_lifecycle_destructor',
            '    coverage questmanager_lifecycle_destructor 0xd2e930 completed 72 different 0 incomplete 0',
            '    coverage questmanager_lifecycle_destructor 0xd2e930 completed 72 different 0 incomplete 0',
            'tlhybrid: questmanager_lifecycle_destructor PASS (0)']
        finished, rows = candidate._comparison_frames(report, ['quest_destructor_owned_lifetime',
                                                               'questmanager_lifecycle_destructor'])
        self.assertEqual(2, len(finished))
        self.assertEqual(4, len(rows))
        self.assertEqual(('quest_destructor_owned_lifetime', 'quest_deleting_lifetime'), rows[1][:2])
        self.assertEqual(rows[2], rows[3])
        self.assertEqual('72', rows[2][3])


class RepairCycleAdmission(unittest.TestCase):
    def setUp(self):
        from test_llm_loop_pipeline import RepairWorkflow
        self.preparation = RepairWorkflow('test_repair_prepares_without_removing_source_or_calling_model')
        self.preparation.setUp()
        self.addCleanup(self.preparation.doCleanups)
        self.checkpoint = self.preparation.prepared_checkpoint()
        self.stage = self.preparation.stage
        self.source = self.preparation.loop.source
        tests = self.stage.path / 'decomp/hybrid/tests'
        tests.mkdir(parents=True, exist_ok=True)
        (tests / 'Repair.cpp').write_text('TL_TEST(repair_probe) {}')
        self.spec = {'schema': 1, 'tu': 'Probe.cpp', 'addresses': ['0x2'],
                     'focused': ['Repair.cpp'], 'regression': ['Repair.cpp'],
                     'controls': [{'name': 'repair-control', 'old': 'return 1', 'new': 'return 3',
                                   'count': 1, 'test': 'repair_probe', 'address': '0x2'}]}
        for target, attr, value in ((candidate.elfdb, 'load_db', self.preparation.loop.db),
                                    (self.stage, '_input_digest', 'pinned')):
            patched = patch.object(target, attr, return_value=value)
            patched.start(); self.addCleanup(patched.stop)

    def test_actual_identity_accepts_repaired_body_without_building(self):
        self.source.write_text(self.source.read_text().replace('return 1', 'return 9'))
        cycle = candidate.Cycle(self.stage, self.spec)
        self.assertEqual('READY', cycle.state['status'])
        self.assertIn('checkpoint.json', cycle.state['identity']['packet'])
        self.preparation.model_class.assert_not_called()
        self.preparation.loop.compile.assert_not_called()

    def test_progress_or_protected_neighbor_change_blocks_before_cycle(self):
        original = self.source.read_text()
        self.source.write_text(original.replace('return 2', 'return 9'))
        with self.assertRaisesRegex(RuntimeError, 'outside assigned bodies'):
            candidate.Cycle(self.stage, self.spec)
        self.source.write_text(original)
        path = self.stage.root / 'build-decomp/progress.json'
        path.write_text(path.read_text() + ' ')
        with self.assertRaisesRegex(RuntimeError, 'protection inputs changed'):
            candidate.Cycle(self.stage, self.spec)

    def test_missing_or_corrupt_snapshot_does_not_downgrade_to_ordinary(self):
        import copy
        path = self.preparation.loop.work / 'checkpoint.json'
        missing = copy.deepcopy(self.checkpoint)
        missing.pop('repair');missing['settings'].pop('repair_addresses');missing['settings'].pop('repair_mode')
        corrupt = copy.deepcopy(self.checkpoint);corrupt['repair']['source_sha256'] = '0' * 64
        for value in (missing, corrupt):
            path.write_text(json.dumps(value))
            with self.assertRaises(RuntimeError): candidate.Cycle(self.stage, self.spec)


if __name__ == '__main__':
    unittest.main()
