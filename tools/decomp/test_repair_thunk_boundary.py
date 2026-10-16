"""The external cycle must enforce the thunk pin after actual comparison."""
from contextlib import nullcontext
import json
from pathlib import Path
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

import candidate


class RepairComparisonBoundary(unittest.TestCase):
    def compare(self, thunk):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            path = root / 'attempt'
            for base in (root, path):
                (base / 'decomp/src').mkdir(parents=True)
                (base / 'decomp/src/Probe.cpp').write_text('int CProbe::work() { return 1; }\n')
            packet = path / 'build-decomp/llm-loop/Probe.cpp'
            packet.mkdir(parents=True)
            pinned = {'address': '0x3', 'name': '_ZThn16_N6CProbe4workEv', 'code': '0' * 16}
            (packet / 'checkpoint.json').write_text(json.dumps({'repair': {'protected_thunks': [pinned]}}))
            cycle = SimpleNamespace(stage=SimpleNamespace(root=root, path=path, activate=nullcontext),
                                    spec={'tu': 'Probe.cpp', 'addresses': ['0x2']},
                                    state={'phases': {'compare': {}}}, _artifact=lambda *args: {})
            rows = [{'address': '0x2', 'name': '_ZN6CProbe4workEv', 'status': 'DIFF', 'weak': False}]
            if thunk is not None:
                rows.append(dict(pinned, status='MATCH', weak=False, **thunk))
            with patch.object(candidate.objdiff, 'Original'), \
                    patch.object(candidate.objdiff, 'compare_source', return_value={'functions': rows, 'unknown': []}):
                candidate.Cycle._compare(cycle)

    def test_unchanged_thunk_keeps_unaccepted_body_eligible(self):
        self.compare({})

    def test_missing_or_changed_thunk_rejects_before_tests_or_gate(self):
        for thunk in (None, {'code': 'f' * 16}):
            with self.subTest(thunk=thunk), self.assertRaisesRegex(RuntimeError, 'protected MATCH adjustment thunk'):
                self.compare(thunk)


if __name__ == '__main__':
    unittest.main()
