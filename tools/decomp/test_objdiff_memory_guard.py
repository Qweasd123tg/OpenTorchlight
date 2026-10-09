"""Fail-closed tests for a checked memory value reloaded into a table index."""
import unittest
import objdiff


class MemoryGuardTest(unittest.TestCase):
    def base(self):
        return [(0x100, 'test', '%rdi,%rdi'),
                (0x103, 'je', '110 <f+0x10>'),
                (0x105, 'cmpl', '$0x5,0x64(%rdi)'),
                (0x109, 'jbe', '118 <f+0x18>'),
                (0x110, 'ret', ''),
                (0x111, 'nop', ''),
                (0x118, 'mov', '0x64(%rdi),%eax'),
                (0x11b, 'jmp', '*0x1000(,%rax,8)')]

    def check(self, rows):
        return objdiff.Normalizer.memory_table_size(len(rows) - 1, rows, '%rax')

    def test_guarded_zero_extended_load(self):
        self.assertEqual(6, self.check(self.base()))

    def test_exclusive_upper_bound(self):
        rows = self.base(); rows[3] = (0x109, 'jb', '118 <f+0x18>')
        self.assertEqual(5, self.check(rows))

    def test_64_bit_guard_and_load(self):
        rows = self.base(); rows[2] = (0x105, 'cmpq', '$0x5,0x64(%rdi)')
        rows[6] = (0x118, 'mov', '0x64(%rdi),%rax')
        self.assertEqual(6, self.check(rows))

    def test_different_cell(self):
        rows = self.base(); rows[6] = (0x118, 'mov', '0x68(%rdi),%eax')
        self.assertIsNone(self.check(rows))

    def test_width_mismatch(self):
        rows = self.base(); rows[6] = (0x118, 'mov', '0x64(%rdi),%rax')
        self.assertIsNone(self.check(rows))

    def test_signed_guard(self):
        rows = self.base(); rows[3] = (0x109, 'jle', '118 <f+0x18>')
        self.assertIsNone(self.check(rows))

    def test_entry_bypasses_guard(self):
        rows = self.base(); rows[1] = (0x103, 'je', '118 <f+0x18>')
        self.assertIsNone(self.check(rows))

    def test_outside_edge_reenters(self):
        rows = self.base(); rows[4] = (0x110, 'jmp', '118 <f+0x18>')
        self.assertIsNone(self.check(rows))

    def test_intervening_write_or_call_or_base_change(self):
        for op, arg in [('movl', '$0x100,0x64(%rdi)'), ('call', '200 <other>'), ('mov', '%rsi,%rdi')]:
            rows = self.base(); rows.insert(-1, (0x11a, op, arg))
            self.assertIsNone(self.check(rows), (op, arg))

    def test_unbounded_size(self):
        rows = self.base(); rows[2] = (0x105, 'cmpl', '$0xffffffff,0x64(%rdi)')
        self.assertIsNone(self.check(rows))

    def test_unverified_entry_remains_blocked(self):
        rows = self.base()
        normalizer = objdiff.Normalizer()
        normalizer.labels = {row[0]: i for i, row in enumerate(rows)}
        normalizer.unverified = []
        token = normalizer.jump_table(7, [0x110] * 5 + [0x999], '%rax', 0x100, 0x11e,
                                      [row[0] for row in rows], rows)
        self.assertIn('unverified', token)
        self.assertTrue(normalizer.unverified)


if __name__ == '__main__':
    unittest.main()
