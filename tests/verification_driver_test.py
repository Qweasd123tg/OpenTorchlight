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
