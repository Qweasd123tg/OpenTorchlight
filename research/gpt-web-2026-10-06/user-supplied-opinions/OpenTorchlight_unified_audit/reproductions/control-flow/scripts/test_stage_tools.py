#!/usr/bin/env python3
"""Small self-tests for the read-only archive tools, not game validation."""
import json
import unittest
from pathlib import Path
from archive_census import mask_text
from effect_regions import analyze, parse_insn, target


def fixture(lines, size=0x40):
    insns = {}
    for line in lines.strip().splitlines():
        parsed = parse_insn(line)
        assert parsed is not None, line
        a, op, args = parsed
        insns[a] = {'op': op, 'args': args}
    return {'address': 0x100, 'size': size, 'name': 'synthetic',
            'insns': insns, 'sources': {'synthetic fixture'}}


class ParsingTests(unittest.TestCase):
    def test_intel_bytes(self):
        self.assertEqual(parse_insn('  100: 48 85 c0 test rax,rax'),
                         (0x100, 'test', 'rax,rax'))

    def test_att_no_bytes(self):
        self.assertEqual(parse_insn('100:\tcallq 200 <helper>'),
                         (0x100, 'callq', '200 <helper>'))

    def test_continuation_bytes(self):
        self.assertIsNone(parse_insn('100: 00 00 00'))

    def test_targets(self):
        self.assertEqual(target('0x234 <name>'), 0x234)
        self.assertIsNone(target('*%rax'))

    def test_mask_literal_and_comments(self):
        s = '"goto fake;"; // goto c;\n/* goto b; */ goto real;\n'
        masked = mask_text(s)
        self.assertEqual(len(masked), len(s))
        self.assertEqual(masked.count('\n'), s.count('\n'))
        self.assertEqual(masked.count('goto'), 1)


class RegionTests(unittest.TestCase):
    def test_diamond(self):
        r = analyze(fixture('''
100: cmp eax,0
103: je 110
105: call 200 <left>
10a: jmp 120
110: call 300 <right>
120: ret
'''))
        self.assertEqual(r['normal_flow_blocks'], 4)
        self.assertEqual(r['region_count'], 1)
        self.assertEqual(r['normal_flow_regions'][0]['merge'], '0x120')
        self.assertEqual(r['normal_flow_regions'][0]['calls'], 2)
        self.assertEqual({tuple(x['guard_blocks']) for x in r['call_sites']},
                         {('0x100',)})

    def test_loop(self):
        r = analyze(fixture('''
100: mov eax,0
103: jmp 110
110: cmp eax,10
113: jge 130
115: call 200 <body>
11a: add eax,1
11d: jmp 110
130: ret
'''))
        self.assertEqual(r['loop_back_edges'], 1)
        self.assertEqual(len(r['unresolved_transfers']), 0)
        self.assertIn('0x110', r['call_sites'][0]['guard_blocks'])

    def test_indirect_is_unknown(self):
        r = analyze(fixture('''
100: test eax,eax
102: je 110
104: jmp *%rax
110: ret
'''))
        self.assertEqual(r['unresolved_transfers'][0]['kind'], 'indirect jump')

    def test_missing_entry_skipped(self):
        f=fixture('110: ret')
        self.assertIn('skip', analyze(f))

    def test_no_exit_skipped(self):
        f=fixture('100: jmp 100')
        self.assertEqual(analyze(f)['skip'], 'no normal exit in modeled graph')

    def test_missing_branch_target_flagged(self):
        r=analyze(fixture('100: jmp 110'))
        self.assertEqual(r['unresolved_transfers'][0]['kind'],
                         'missing internal jump target')

    def test_tail_call_is_exit(self):
        r=analyze(fixture('100: jmp 900 <external>'))
        self.assertEqual(r['region_count'], 0)
        self.assertEqual(r['unresolved_transfers'], [])


if __name__ == '__main__':
    unittest.main(verbosity=2)
