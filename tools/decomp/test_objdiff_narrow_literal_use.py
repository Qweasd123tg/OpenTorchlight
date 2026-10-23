"""Per-use narrow imported-constructor proof; no address-wide typing."""
import unittest
from unittest.mock import patch
import objdiff
import test_objdiff_literal_use as wide_tests


class NarrowUseTest(unittest.TestCase):
    def fixture(self, raw=b'1\0\0\0\0\0\0\0'):
        helper = wide_tests.ForwardLifetimeTest()
        side = helper.side(raw)
        side.image.plt[0x555000] = side.STRING_CTOR
        rows = helper.forward_rows()
        rows[2] = [0x10a, 'mulss', '%xmm1,%xmm0']
        return side, rows

    def normalized(self, raw):
        side, rows = self.fixture(raw)
        return side, side.normalize(rows, 0x100, 0x124)

    def test_narrow_payload_and_provenance(self):
        side, rows = self.normalized(b'AB\0tail')
        self.assertIn('lit:w1:n2:4142', rows[1])
        proof = side.literal_proofs[0]
        self.assertEqual((proof['width'], proof['size'], proof['end']), (1, 3, 0xff0003))
        self.assertEqual(proof['callee'], side.STRING_CTOR)
        self.assertFalse(side.unverified)

    def test_before_nul_matters_after_nul_does_not(self):
        a = self.normalized(b'AB\0tail')[1]
        self.assertNotEqual(a, self.normalized(b'AC\0tail')[1])
        self.assertEqual(a, self.normalized(b'AB\0other')[1])

    def test_same_address_wide_and_unproven_are_not_overridden(self):
        side, rows = self.fixture('AB\0'.encode('utf-32le'))
        narrow = side.normalize(rows, 0x100, 0x124)[1]
        side.image.plt[0x555000] = side.WSTRING_CTOR
        wide = side.normalize(rows, 0x100, 0x124)[1]
        self.assertIn('lit:w1:n1:41', narrow)
        self.assertIn('lit:w4:n2:4100000042000000', wide)
        self.assertIn('unverified-data:', side.name_at(0xff0000, 'mov', True))
        # Bytes ignored by the narrow use remain observable at a wide use.
        other, otherrows = self.fixture('AC\0'.encode('utf-32le'))
        self.assertEqual(narrow, other.normalize(otherrows, 0x100, 0x124)[1])
        other.image.plt[0x555000] = other.WSTRING_CTOR
        self.assertNotEqual(wide, other.normalize(otherrows, 0x100, 0x124)[1])

    def test_wrong_import_alias_and_postcall_reads(self):
        for name in ('_ZNSsC2EPKcRKSaIcE', '_ZN5SceneC1EPKc', ''):
            side, rows = self.fixture(); side.image.plt[0x555000] = name
            self.assertIsNone(side.wide_literal_use(1, rows, 0x100, 0x124))
        for index in (2, 5):
            for op, args in [('mov','%rsi,%r12'), ('mov','(%rsi),%rax'),
                             ('mov','%sil,%al'), ('mov','%rsi,(%rsp)')]:
                side, rows = self.fixture(); rows[index][1:] = [op, args]
                self.assertIsNone(side.wide_literal_use(1, rows, 0x100, 0x124))

    def test_cleanup_and_legacy_prefix_cannot_bypass_lifetime(self):
        helper = wide_tests.ForwardLifetimeTest()
        for args in ('%rsi,%r12', '(%rsi),%rax', '%sil,%al'):
            side, rows, eh = helper.cleanup_case()
            side.image.plt[0x555000] = side.STRING_CTOR
            rows[-1][1:] = ['mov', args]
            with patch.object(side, '_literal_eh', return_value=eh):
                self.assertIsNone(side.wide_literal_use(1, rows, 0x100, 0x139))
        side, _ = self.fixture(); rows = helper.insns()
        rows[-1][1:] = ['mov', '%rsi,%rax']; rows.append([0x118, 'ret', ''])
        self.assertIsNone(side.wide_literal_use(1, rows, 0x100, 0x119))

    def test_rip_scalar_effects_and_complete_forward_path(self):
        side, rows = self.fixture()
        rows[2:3] = [[0x10a, 'movss', '0x100(%rip),%xmm1        # 20b <constant>'],
                     [0x10b, 'mulss', '%xmm1,%xmm0'],
                     [0x10c, 'mulss', '0x104(%rip),%xmm0'],
                     [0x10d, 'movss', '%xmm0,0x108(%rip)']]
        self.assertIsNotNone(side.wide_literal_use(1, rows, 0x100, 0x124))
        effect = objdiff.OriginalSide._literal_independent_instruction
        self.assertTrue(effect('movss', '%xmm0,0x108(%rip)'))
        self.assertTrue(effect('movss', '0x108(%rip),%xmm0'))
        for args in ('%eax,0x108(%rip)', '0x108(%rip),%eax',
                     '0x108(%rip),0x100(%rip)', '0x108(%rip,%rax,4),%xmm0'):
            self.assertFalse(effect('movss', args))
        self.assertFalse(effect('rep movss', '0x108(%rip),%xmm0'))
        for tail in (' # arbitrary', ' # 123 <x> junk', ' # 123', ' # 123 <x>\nmov'):
            self.assertFalse(effect('mulss', '0x108(%rip),%xmm0'+tail))
        self.assertTrue(effect('mulss', '0x108(%rip),%xmm0 # 123 <constant>'))

    def test_invalid_width_address_and_unterminated(self):
        side, rows = self.fixture()
        proof = side.wide_literal_use(1, rows, 0x100, 0x124)
        side.literal_proofs = []; side.unverified = []
        for width in (None, True, 0, 2, 8, '1'):
            self.assertIn('unverified-data:', side.name_at(0xff0000, 'mov', True,
                          dict(proof, width=width)))
        self.assertIn('unverified-data:', side.name_at(0xff0000, 'mov', True,
                      dict(proof, literal=0xff0001)))
        side, rows = self.normalized(b'no terminator')
        self.assertTrue(side.unverified); self.assertFalse(side.literal_proofs)

    def test_mulss_exact_effect_forms(self):
        effect = objdiff.OriginalSide._literal_independent_instruction
        for args in ('%xmm0,%xmm15', '(%rax),%xmm1', '-0x4(%rbx),%xmm2', '0x10(%rip),%xmm0'):
            self.assertTrue(effect('mulss', args))
        for args in ('(%rsi),%xmm0','(%rdx),%xmm0','%eax,%xmm0',
                     '%xmm0,%eax','%xmm0,(%rax)','(%eax),%xmm0',
                     '%xmm16,%xmm0','%xmm0,%xmm16','%xmm0',
                     '(%rax,%rcx,4),%xmm0','%fs:(%rax),%xmm0',
                     '*%rax,%xmm0','$0x1,%xmm0'):
            self.assertFalse(effect('mulss', args), args)
        for op in ('rep mulss','lock mulss','mulssl','vmulss','data16 mulss'):
            self.assertFalse(effect(op, '%xmm0,%xmm1'))
        self.assertFalse(effect('mulss', '(%rbx),%xmm0', blocked=("b",)))


if __name__ == '__main__': unittest.main()
