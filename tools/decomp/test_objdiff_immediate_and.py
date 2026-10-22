"""Immediate AND is forward-only independence, never a raw kill or predicate."""
import unittest
from unittest.mock import patch

import objdiff
import test_objdiff_literal_use as literal_tests


class ImmediateAndTest(unittest.TestCase):
    registers = ('eax', 'ebx', 'ecx', 'edx', 'edi') + tuple('r%dd' % n for n in range(8, 16))

    def setUp(self):
        self.side = literal_tests.ForwardLifetimeTest().side()

    def rows(self, op='and', args='$0x1,%r12d'):
        return [[0x100, 'mov', '$0xff0000,%esi'],
                [0x105, op, args],
                [0x10a, 'call', '555000 <ctor>'],
                [0x10f, 'mov', '%rbx,%rsi'], [0x112, 'ret', '']]

    def proof(self, rows):
        return self.side.wide_literal_use(0, rows, 0x100, rows[-1][0] + 5)

    def accepts(self, op, args):
        return self.side._forward_independent_and(op, args)

    def test_all_eligible_registers_unsigned_imm32_boundaries(self):
        for reg in self.registers:
            for immediate in ('0', '1', '7fffffff', '80000000', 'ffffffff', '00000001'):
                args = '$0x%s,%%%s' % (immediate, reg)
                with self.subTest(args=args):
                    self.assertTrue(self.accepts('and', args))
                    self.assertIsNotNone(self.proof(self.rows(args=args)))

    def test_reject_excluded_families_widths_and_registers(self):
        for reg in ('rsi', 'esi', 'si', 'sil', 'rsp', 'esp', 'sp', 'spl',
                    'rbp', 'ebp', 'bp', 'bpl', 'rax', 'ax', 'al', 'ah',
                    'r12', 'r12w', 'r12b', 'r16d', 'r08d', 'xmm0', 'rip', 'eip'):
            args = '$0x1,%' + reg
            with self.subTest(args=args):
                self.assertFalse(self.accepts('and', args))
                self.assertIsNone(self.proof(self.rows(args=args)))

    def test_reject_memory_register_source_and_malformed_operands(self):
        for args in ('$0x1,(%rax)', '$0x1,0x8(%rsp)', '$0x1,%fs:0x8(%rax)',
                     '$0x1,(%rax,%rcx,4)', '$0x1,0xff0000', '%cl,%r12d',
                     '%eax,%r12d', '0x1,%r12d', '$1,%r12d', '$-0x1,%r12d',
                     '$0x100000000,%r12d', '$0xffffffffffffffff,%r12d',
                     '$0x,%r12d', '$0xGG,%r12d', '$0X1,%r12d',
                     '$0x1, %r12d', '$0x1,%r12d ', '$0x1,%%r12d',
                     '$0x1,%r12d # extra', '$0x1,%r12d,%eax', '', '%r12d'):
            with self.subTest(args=args):
                self.assertFalse(self.accepts('and', args))
                self.assertIsNone(self.proof(self.rows(args=args)))

    def test_reject_prefixes_suffixes_other_operations_in_new_helper(self):
        for op in ('andl', 'andq', 'andw', 'andb', 'lock and', 'rep and',
                   'data16 and', 'addr32 and', 'rex.W and', 'AND', 'and ',
                   'shr', 'sar', 'shl', 'rol', 'ror', 'andn', 'test'):
            with self.subTest(op=op):
                self.assertFalse(self.accepts(op, '$0x1,%r12d'))
        for op in ('andl', 'andq', 'andw', 'andb', 'lock and', 'rep and', 'addr32 and'):
            self.assertIsNone(self.proof(self.rows(op=op)))

    def test_raw_observation_and_alias_creation_reject_before_and_after_and(self):
        forbidden = [('mov', '%rsi,%r12'), ('mov', '%esi,%r12d'),
                     ('mov', '%si,%r12w'), ('mov', '%sil,%r12b'),
                     ('mov', '%rsi,(%rsp)'), ('mov', '%rsi,0x8(%rbp)'),
                     ('mov', '%rsi,(%rax)'), ('lea', '(%rsi),%r12'),
                     ('mov', '(%rsi),%eax'), ('push', '%rsi'),
                     ('xchg', '%rsi,%rax'), ('lodsq', ''), ('rep movsq', ''),
                     ('syscall', ''), ('cmp', '%rsi,%rdi'), ('test', '%esi,%esi'),
                     ('mov', '%al,%sil'), ('mov', '%ax,%si'),
                     ('add', '$0x1,%rsi'), ('and', '$0x0,%esi')]
        for op, args in forbidden:
            for position in (1, 2):
                rows = self.rows(); rows.insert(position, [0, op, args])
                for i, row in enumerate(rows): row[0] = 0x100 + i * 5
                with self.subTest(op=op, args=args, position=position):
                    self.assertIsNone(self.proof(rows))

    def test_forward_transfers_and_nonconsumer_calls_still_reject(self):
        for op, args in [('jne', '10a <ctor>'), ('jmp', '10a <ctor>'), ('ret', ''),
                         ('call', '555100 <delete>'), ('call', '*%rax')]:
            rows = self.rows(); rows.insert(2, [0x108, op, args])
            self.assertIsNone(self.proof(rows))
        self.side.image.plt[0x555000] = '_ZN5SceneC1EPKw'
        self.assertIsNone(self.proof(self.rows()))
        self.side.image.plt = {}
        self.side.func_start[0x555000] = self.side.WSTRING_CTOR
        self.assertIsNone(self.proof(self.rows()))

    def test_normal_and_cleanup_gates_not_widened(self):
        self.assertFalse(self.side._literal_independent_instruction('and', '$0x1,%r12d'))
        rows = self.rows(); rows[3][1:] = ['and', '$0x1,%r12d']
        self.assertIsNone(self.proof(rows))
        rows = self.rows() + [[0x120, 'and', '$0x1,%r12d'],
                              [0x125, 'call', '555200 <resume>']]
        eh = {'kind': 'gcc447-cleanup-v1', 'rows': [(10, 5, 32, 0)]}
        with patch.object(self.side, '_literal_eh', return_value=eh):
            self.assertIsNone(self.proof(rows))
        self.assertFalse(self.side._rsi_kill('and', '$0x0,%esi'))

    def test_normal_raw_observer_and_partial_kill_still_reject(self):
        for op, args in [('mov', '%rsi,%rax'), ('mov', '(%rsi),%rax'),
                         ('mov', '%rsi,(%rsp)'), ('mov', '%ax,%si'),
                         ('and', '$0x0,%esi')]:
            rows = self.rows(); rows[3][1:] = [op, args]
            self.assertIsNone(self.proof(rows))

    def test_exception_lifetime_required(self):
        rows = self.rows() + [[0x120, 'mov', '%rbx,%rsi'],
                              [0x125, 'call', '555200 <resume>']]
        eh = {'kind': 'gcc447-cleanup-v1', 'rows': [(10, 5, 32, 0)]}
        with patch.object(self.side, '_literal_eh', return_value=eh):
            self.assertIsNotNone(self.proof(rows))
            rows[-2][1:] = ['mov', '%rsi,%rax']
            self.assertIsNone(self.proof(rows))
        with patch.object(self.side, '_literal_eh', return_value=None):
            self.assertIsNone(self.proof(self.rows()))

    def test_unsafe_normal_and_exception_branches_not_pruned(self):
        for exceptional in (False, True):
            rows = self.rows()
            fork = [[0x120, 'je', '130 <unsafe>'], [0x125, 'mov', '%rbx,%rsi'],
                    [0x12a, 'ret', ''], [0x130, 'mov', '%rsi,%rax'], [0x135, 'ret', '']]
            if exceptional:
                fork[2][1:] = ['call', '555200 <resume>']
                fork[-1][1:] = ['call', '555200 <resume>']
                rows += fork
                eh = {'kind': 'gcc447-cleanup-v1', 'rows': [(10, 5, 32, 0)]}
            else:
                rows = rows[:3] + [[0x10f, 'jmp', '120 <fork>']] + fork
                eh = {'kind': 'no-lsda', 'rows': []}
            with self.subTest(exceptional=exceptional), patch.object(self.side, '_literal_eh', return_value=eh):
                self.assertIsNone(self.proof(rows))
                rows[-2][1:] = ['mov', '%rbx,%rsi']
                self.assertIsNotNone(self.proof(rows))

    def test_compare_consumer_and_full_payload_remain_bound(self):
        self.side.image.plt[0x555000] = self.side.WSTRING_COMPARE
        self.assertIsNotNone(self.proof(self.rows()))
        tokens = []
        for text in ('AX\0', 'AY\0'):
            side = literal_tests.ForwardLifetimeTest().side(text.encode('utf-32le'))
            tokens.append(side.normalize(self.rows(), 0x100, 0x117)[0])
        self.assertNotEqual(tokens[0], tokens[1])
        for raw in (b'A\0\0\0', b'A\0\0'):
            side = literal_tests.ForwardLifetimeTest().side(raw)
            side.normalize(self.rows(), 0x100, 0x117)
            self.assertTrue(side.unverified)


if __name__ == '__main__':
    unittest.main()
