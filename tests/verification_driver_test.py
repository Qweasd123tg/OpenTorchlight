#!/usr/bin/env python3
"""Negative acceptance tests for the test driver (never execute original inputs)."""
import importlib.util
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('ot_check', ROOT / 'tools/check.py')
check = importlib.util.module_from_spec(spec)
spec.loader.exec_module(check)

class Driver(unittest.TestCase):
    def test_default_and_positional_directory_keep_integration_explicit(self):
        for argv, expected in [([], {'core'}), (['--core'], {'core'}),
                               (['/external/game'], {'core', 'assets', 'reference'}),
                               (['--render'], {'render'}), (['--desktop'], {'desktop'}),
                               (['/external/game', '--render'], {'core', 'assets', 'reference', 'render'}),
                               (['--all'], set(check.GROUPS))]:
            with self.subTest(argv=argv):
                groups = check.requested_groups(check.parser().parse_args(argv))
                self.assertEqual(groups, expected)
                self.assertIn('-DTORCHLIGHT_ENABLE_RENDER=' +
                              ('ON' if groups & {'render', 'desktop'} else 'OFF'),
                              check.adapter_options(groups))
                self.assertIn('-DTORCHLIGHT_ENABLE_DESKTOP=' +
                              ('ON' if 'desktop' in groups else 'OFF'), check.adapter_options(groups))

    def test_recovery_requires_complete_inputs_and_does_not_configure_partial_chain(self):
        args = check.parser().parse_args(['--recover'])
        self.assertEqual(check.requested_groups(args), {'core', 'assets', 'reference'})
        with tempfile.TemporaryDirectory() as folder:
            base = Path(folder)
            result = subprocess.run([sys.executable, str(ROOT / 'tools/check.py'), '--recover',
                '--assets', str(base / 'absent'), '--report', str(base / 'report.json'),
                '--build-dir', str(base / 'never-built')], capture_output=True, text=True, timeout=15)
            self.assertNotEqual(result.returncode, 0)
            report = json.loads((base / 'report.json').read_text())
            self.assertTrue(report['recovery_requested'])
            self.assertTrue(all(report['groups'][g]['status'] == 'NOT RUN' for g in ('core', 'assets', 'reference')))
            self.assertEqual(report['assessment']['original_status_promotions'], 0)
            self.assertFalse((base / 'never-built/CMakeCache.txt').exists())

    def test_repeatable_named_selection(self):
        args = check.parser().parse_args(['--test', 'layout', '--test', 'binding'])
        self.assertEqual(args.test, ['layout', 'binding'])
        self.assertIsNone(args.changed)
        self.assertIsNone(args.since_report)

    def test_recovery_domain_summary_keeps_failed_skipped_missing_and_unknown_checks(self):
        report = {'plan_only': False, 'recovery': {'required_tests': [
            'original_attack_speed_comparison', 'original_economy_comparison',
            'original_population', 'new_uncategorized_check']}, 'groups': {
                'reference': {'tests': [{'name': 'original_attack_speed_comparison', 'status': 'FAILED', 'seconds': '1'},
                                       {'name': 'original_economy_comparison', 'status': 'NOT RUN', 'seconds': '0'}]},
                'other_group': {'tests': [{'name': 'original_attack_speed_comparison', 'status': 'PASSED', 'seconds': '1'}]}}}
        result = check.recovery_domain_results(report)
        self.assertEqual(result['combat_skills']['status'], 'FAILED')
        self.assertEqual(result['inventory_loot_economy']['status'], 'NOT RUN')
        self.assertEqual(result['world_generation']['status'], 'NOT RUN')
        self.assertEqual(result['other_cpu_contracts']['status'], 'NOT RUN')
        self.assertEqual(sum(len(v['tests']) for v in result.values()), 4)

    def test_evidence_roles_are_independent_of_name_and_green_status(self):
        for labels, expected in [(['core'], 'unit-regression'),
                                 (['assets'], 'resource-contract'),
                                 (['core', 'render'], 'integration-regression'),
                                 (['desktop'], 'integration-regression'),
                                 (['reference'], 'bounded-reference-comparison')]:
            test = {'name': 'original_everything_complete', 'properties': [
                {'name': 'LABELS', 'value': labels}]}
            self.assertEqual(check.evidence_role(test), expected)
    def test_required_inputs_are_not_green(self):
        for argument in ('--assets', '--reference'):
            with self.subTest(argument=argument), tempfile.TemporaryDirectory() as folder:
                base = Path(folder)
                report = base / 'report.json'
                result = subprocess.run([sys.executable, str(ROOT / 'tools/check.py'), argument,
                                         str(base / 'absent'), '--report', str(report),
                                         '--build-dir', str(base / 'never-built')],
                                        capture_output=True, text=True, timeout=15)
                self.assertNotEqual(result.returncode, 0, result.stdout)
                data = json.loads(report.read_text())
                self.assertEqual(data['groups'][argument[2:]]['status'], 'NOT RUN')
                self.assertEqual(data['assessment']['original_status_promotions'], 0)
                self.assertFalse((base / 'never-built/CMakeCache.txt').exists())
                self.assertIn('NOT RUN', result.stdout)

    def test_missing_render_desktop_are_not_green(self):
        for argument in ('--render','--desktop'):
            with self.subTest(argument=argument), tempfile.TemporaryDirectory() as folder:
                base=Path(folder);report=base/'report.json'
                process=subprocess.run([sys.executable,str(ROOT/'tools/check.py'),argument,
                    '--game-dir',str(base/'absent'),'--report',str(report),
                    '--build-dir',str(base/'never-built')],capture_output=True,text=True,timeout=15)
                self.assertNotEqual(process.returncode,0)
                self.assertEqual(json.loads(report.read_text())['groups'][argument[2:]]['status'],'NOT RUN')
                self.assertFalse((base/'never-built/CMakeCache.txt').exists())

    def test_coverage_join_never_promotes(self):
        coverage_spec=importlib.util.spec_from_file_location('coverage_map',ROOT/'tools/coverage_map.py')
        coverage=importlib.util.module_from_spec(coverage_spec);coverage_spec.loader.exec_module(coverage)
        with tempfile.TemporaryDirectory() as folder:
            report=Path(folder)/'run.json'
            value={'schema':1,'kind':'verification-run','groups':{
                group:{'requested':True,'status':'PASSED' if group in ('core','assets') else 'NOT RUN'}
                for group in check.GROUPS}}
            report.write_text(json.dumps(value))
            joined=coverage.verification_summary(report)
            self.assertEqual(joined['original_status_promotions'],0)
            self.assertEqual(joined['groups']['reference']['status'],'NOT RUN')
            value['groups'].pop('desktop');report.write_text(json.dumps(value))
            with self.assertRaises(ValueError):coverage.verification_summary(report)

    def test_skipped_ctest_is_not_passed(self):
        with tempfile.TemporaryDirectory() as folder:
            p = Path(folder) / 'result.xml'
            cases = [('<testsuite><testcase name="ok" status="run"/></testsuite>', 0, 'PASSED'),
                     ('<testsuite><testcase name="no" status="notrun"><skipped/></testcase></testsuite>', 0, 'NOT RUN'),
                     ('<testsuite><testcase name="bad"><failure/></testcase></testsuite>', 8, 'FAILED'),
                     ('<testsuite/>', 0, 'NOT RUN'), ('broken', 0, 'FAILED')]
            for xml, code, expected in cases:
                p.write_text(xml)
                self.assertEqual(check.summarize_junit(p, code)['status'], expected)
            p.unlink()
            self.assertNotEqual(check.summarize_junit(p, 1)['status'], 'PASSED')

if __name__ == '__main__': unittest.main()
