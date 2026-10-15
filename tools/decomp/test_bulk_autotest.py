import unittest

import bulk_autotest


class SelectionTest(unittest.TestCase):
    def test_only_unaccepted_strong_written_game_diff(self):
        fs = {hex(i): {'address': hex(i), 'tu': 1, 'kind': 'function'} for i in range(1, 8)}
        fs['0x5']['tu'] = 2
        fs['0x6']['kind'] = 'compiler'
        db = {'tus': [{'id': 1, 'kind': 'game'}, {'id': 2, 'kind': 'library'}], 'functions': fs}
        rows = [{'address': a, 'status': 'DIFF', 'weak': False} for a in fs]
        rows[1]['weak'] = True
        rows[2]['status'] = 'MATCH'
        rows[3]['status'] = 'MISSING'
        progress = {'units': [{'functions': rows}], 'comparison_evidence': {'0x7': {}}}
        self.assertEqual([f['address'] for f in bulk_autotest.select(db, progress)], ['0x1'])
        with self.assertRaises(ValueError):
            bulk_autotest.select(db, progress, ['0x2'])


class ClassificationTest(unittest.TestCase):
    def lines(self, completed=20, different=0, incomplete=0, passed=True):
        return [f'    coverage auto_123 0x123 completed {completed} different {different} incomplete {incomplete}',
                f'tlhybrid: auto_123 {"PASS (0)" if passed else "FAIL (1)"}']

    def test_acceptance_threshold_is_only_a_diagnostic_probe(self):
        self.assertEqual(bulk_autotest.classify('0x123', self.lines(), True)['status'], 'PASSED_PROBE')
        padded = self.lines()
        padded[-1] = 'tlhybrid: auto_123                         PASS (0)'
        self.assertEqual(bulk_autotest.classify('0x123', padded, True)['status'], 'PASSED_PROBE')
        self.assertEqual(bulk_autotest.classify('0x123', self.lines(19), True)['status'], 'TOO_FEW_NORMAL_PAIRS')

    def test_matching_crashes_do_not_pass(self):
        self.assertEqual(bulk_autotest.classify('0x123', self.lines(0), True)['status'], 'TOO_FEW_NORMAL_PAIRS')
        self.assertEqual(bulk_autotest.classify('0x123', self.lines(200, incomplete=1), True)['status'], 'INCOMPLETE')

    def test_failure_inventory_and_input_guards(self):
        self.assertEqual(bulk_autotest.classify('0x123', self.lines(different=1), True)['status'], 'DIFFERENT')
        self.assertEqual(bulk_autotest.classify('0x123', self.lines(passed=False), True)['status'], 'FAILED_FIXTURE')
        self.assertEqual(bulk_autotest.classify('0x123', self.lines(), False)['status'], 'INVALID_RUN')
        self.assertEqual(bulk_autotest.classify('0x123', self.lines() * 2, True)['status'], 'MISSING_COVERAGE')
        self.assertEqual(bulk_autotest.classify('0x124', self.lines(), True)['status'], 'MISSING_COVERAGE')


if __name__ == '__main__':
    unittest.main()
