"""Range proof across a store: exact operands, CFG dominance, immutable storage."""
import unittest
from types import SimpleNamespace
import objdiff


class GuardStoreTest(unittest.TestCase):
    def base(self):
        return [(0x100, 'test', '%rdi,%rdi'), (0x103, 'je', '114'),
                (0x105, 'cmp', '$0x5,%eax'),
                (0x108, 'mov', '%eax,0x5c(%rbx)'),
                (0x10b, 'jbe', '118'), (0x114, 'ret', ''),
                (0x118, 'mov', '%eax,%eax'),
                (0x11b, 'jmp', '*0x1000(,%rax,8)')]

    def check(self, rows):
        return objdiff.Normalizer.table_size(len(rows) - 1, rows, '%rax', allow_guard_stores=True)

    def test_default_remains_fail_closed(self):
        self.assertIsNone(objdiff.Normalizer.table_size(7, self.base(), '%rax'))

    def test_original_store_shape(self):
        self.assertEqual(6, self.check(self.base()))

    def test_guard_kinds(self):
        for jump, count in [('jbe', 6), ('jb', 5), ('ja', 6), ('jae', 5)]:
            rows = self.base()
            if jump in ('ja', 'jae'):
                rows[4] = (0x10b, jump, '114')
                rows.insert(5, (0x10e, 'jmp', '118'))
            else:
                rows[4] = (0x10b, jump, '118')
            self.assertEqual(count, self.check(rows), jump)

    def test_reject_nonstores_and_unhandled_operands(self):
        cases = [('mov', '%ecx,%eax'), ('mov', '%cl,%al'), ('mov', '%cx,%ax'),
                 ('mov', '%rcx,%rax'), ('mov', '0x5c(%rbx),%eax'),
                 ('movl', '$0x1,0x5c(%rbx)'), ('add', '%eax,0x5c(%rbx)'),
                 ('test', '%eax,%eax'), ('call', '200'), ('push', '%rax'),
                 ('movq', '%eax,0x5c(%rbx)'), ('movl', '%rax,0x5c(%rbx)'),
                 ('mov', '%eax,0x5c(%ebx)'), ('mov', '%eax,0x5c(%rip)'),
                 ('mov', '%eax,%fs:0x5c(%rbx)'), ('mov', '%eax,0x5c(%rbx,%rcx,4)'),
                 ('lock mov', '%eax,0x5c(%rbx)'), ('mov', '%eax,0x1000'),
                 ('mov', '%xmm0,0x5c(%rbx)'), ('mov', '%eax,0x5c(%rbx),%eax')]
        for op, args in cases:
            rows = self.base(); rows[3] = (0x108, op, args)
            self.assertIsNone(self.check(rows), (op, args))

    def test_partial_index_write_after_guard(self):
        for reg in ('%al', '%ax', '%ah'):
            rows = self.base(); rows[6] = (0x118, 'mov', '%cl,' + reg)
            self.assertIsNone(self.check(rows), reg)

    def test_alternate_entry_and_outside_reentry(self):
        for index, replacement in [(1, (0x103, 'je', '108')),
                                   (1, (0x103, 'je', '118')),
                                   (5, (0x114, 'jmp', '118'))]:
            rows = self.base(); rows[index] = replacement
            self.assertIsNone(self.check(rows))

    def test_signed_guard_and_unbounded_count(self):
        rows = self.base(); rows[4] = (0x10b, 'jle', '118')
        self.assertIsNone(self.check(rows))
        rows = self.base(); rows[2] = (0x105, 'cmp', '$0xffffffff,%eax')
        self.assertIsNone(self.check(rows))

    def test_upper_bits_must_be_proven(self):
        rows = self.base(); rows[6] = (0x118, 'nop', '')
        self.assertIsNone(self.check(rows))

    def test_jump_table_requires_immutable_evidence_and_all_entries(self):
        rows = self.base(); n = objdiff.Normalizer()
        n.labels = {row[0]: i for i, row in enumerate(rows)}
        for evidence, entries, accepted in [(None, [0x114] * 6, False),
                                           (lambda c: False, [0x114] * 6, False),
                                           (lambda c: c == 6, [0x114] * 6, True),
                                           (lambda c: True, [0x114] * 5, False),
                                           (lambda c: True, [0x114] * 5 + [0x999], False)]:
            n.unverified = []
            token = n.jump_table(7, entries, '%rax', 0x100, 0x122,
                                 [r[0] for r in rows], rows, guard_store_safe=evidence)
            self.assertEqual(not accepted, bool(n.unverified), token)

    def test_readonly_object_sections(self):
        section = SimpleNamespace(flags=2, size=48)
        self.assertTrue(objdiff.Normalizer.readonly_section(section, 0, 48))
        for flags, start, size in [(3, 0, 48), (0, 0, 48), (2, -1, 8),
                                   (2, 0, 49), (2, 0, 0)]:
            section.flags = flags
            self.assertFalse(objdiff.Normalizer.readonly_section(section, start, size))
        section.flags = 2
        self.assertFalse(objdiff.Normalizer.readonly_section(section, 0, 48, executable=True))
        section.flags = 6
        self.assertTrue(objdiff.Normalizer.readonly_section(section, 0, 48, executable=True))

    def test_original_loaded_permissions(self):
        n = objdiff.OriginalSide.__new__(objdiff.OriginalSide)
        section = SimpleNamespace(addr=0x1000, flags=6, size=0x100)
        segment = (1, 5, 0, 0x1000, 0, 0x100, 0x100, 0x1000)
        n.image = SimpleNamespace(section_at=lambda addr: section, segments=[segment], data=bytes(0x1000))
        self.assertTrue(n.immutable_loaded_range(0x1000, 48, executable=True))
        for segments in [[], [(1, 5, 0, 0x1000, 0, 0x100, 0x20, 0x1000)],
                         [(1, 5, 0x1000, 0x1000, 0, 0x100, 0x100, 0x1000)],
                         [(1, 5, 1, 0x1000, 0, 0x100, 0x100, 0x1000)],
                         [(1, 7, 0, 0x1000, 0, 0x100, 0x100, 0x1000)],
                         [(1, 5, 0, 0x1000, 0, 16, 0x100, 0x1000)],
                         [segment, (1, 6, 0, 0x1020, 0, 0x100, 0x100, 0x1000)],
                         [segment, (1, 6, 0, 0x1100, 0, 0x100, 0x100, 0x1000)],
                         [(1, 4, 0, 0x1000, 0, 0x100, 0x100, 0x1000)]]:
            n.image.segments = segments
            self.assertFalse(n.immutable_loaded_range(0x1000, 48, executable=True))
        n.image.segments = [segment]; section.flags = 7
        self.assertFalse(n.immutable_loaded_range(0x1000, 48, executable=True))


if __name__ == '__main__':
    unittest.main()
