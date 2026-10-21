"""Original-only imported consumer proofs, with fail-closed def-use boundaries."""
import unittest
from types import SimpleNamespace
import objdiff

class WideUseTest(unittest.TestCase):
    def side(self, raw=None):
        raw = raw if raw is not None else 'NOT LOADED\0'.encode('utf-32le')
        sec = SimpleNamespace(name='.rodata', addr=0xff0000, size=len(raw))
        side = objdiff.OriginalSide.__new__(objdiff.OriginalSide)
        side.func_start = {}; side.obj_starts = []; side.objects = []; side.exact = {}
        side.low = 0x400000; side.high = 0x1000000
        side.image = SimpleNamespace(plt={0x555000: side.WSTRING_CTOR},
            section_at=lambda a: sec if sec.addr <= a < sec.addr + sec.size else None,
            read=lambda a,n: raw[a-sec.addr:a-sec.addr+n])
        return side

    def insns(self):
        return [[0x100, 'push', '%rbx'], [0x101, 'mov', '$0xff0000,%esi'],
                [0x106, 'mov', '%rdi,%rbx'], [0x109, 'sub', '$0x10,%rsp'],
                [0x10d, 'lea', '0xf(%rsp),%rdx'],
                [0x112, 'call', '555000 <wstring@plt>'], [0x117, 'ret', '']]

    def test_original_consumer_proves_full_bytes(self):
        side = self.side(); result = side.normalize(self.insns(), 0x100, 0x118)
        self.assertFalse(side.unverified)
        self.assertIn('lit:w4:n10:', result[1])
        self.assertEqual(side.literal_proofs[0]['size'], 44)
        self.assertEqual(side.literal_proofs[0]['end'], 0xff002c)
        self.assertEqual(side.literal_proofs[0]['argument'], 'rsi')

    def test_reject_intervening_effects(self):
        for op,args in [('mov', '%eax,%esi'), ('mov', '%ax,%si'), ('mov', '%al,%sil'),
                        ('mov', '%rsi,%rax'), ('mov', '%rsi,(%rbx)'),
                        ('lea', '0x0(%rsi),%rax'), ('lodsq',''),
                        ('call', '555100 <other>'), ('call', '*%rax'),
                        ('jmp', '112 <sink>'), ('jne', '112 <sink>'), ('ret','')]:
            with self.subTest(op=op,args=args):
                rows=self.insns(); rows[2]=[0x106,op,args]
                self.assertIsNone(self.side().wide_literal_use(1, rows))

    def test_reject_wrong_consumer_and_non_import(self):
        for name in ['_ZNSsC1EPKcRKSaIcE', '_ZN5SceneC1EPKw', '']:
            side=self.side(); side.image.plt[0x555000]=name
            self.assertIsNone(side.wide_literal_use(1,self.insns()))
        side=self.side(); side.image.plt={}; side.func_start[0x555000]=side.WSTRING_CTOR
        self.assertIsNone(side.wide_literal_use(1,self.insns()))

    def test_reject_alternative_entry_and_prior_call(self):
        side=self.side(); side.func_start[0x10d]='alternate'
        self.assertIsNone(side.wide_literal_use(1,self.insns()))
        rows=self.insns(); rows[0]=[0x100,'call','555100 <earlier>']
        self.assertIsNone(self.side().wide_literal_use(1,rows))
        rows=self.insns(); rows.append([0x118,'jmp','10d <alternate>'])
        self.assertIsNone(self.side().wide_literal_use(1,rows))

    def test_truncated_wide_remains_unverified(self):
        for raw in [b'A\0\0\0', b'A\0\0', b'']:
            side=self.side(raw); side.normalize(self.insns(),0x100,0x118)
            if raw:
                self.assertTrue(side.unverified)
            self.assertEqual(side.literal_proofs,[])

    def test_same_address_without_proof_still_ambiguous(self):
        side=self.side(); side.normalize(self.insns(),0x100,0x118)
        self.assertIn('unverified-data:',side.name_at(0xff0000,'mov',True))
        self.assertTrue(side.unverified)

    def test_complete_payload_and_width_not_prefix(self):
        tokens=[]
        for text in ['AX\0','AY\0','\0']:
            side=self.side(text.encode('utf-32le'))
            tokens.append(side.normalize(self.insns(),0x100,0x118)[1])
        self.assertNotEqual(tokens[0],tokens[1])
        self.assertIn('lit:w4:n0:',tokens[2])
        self.assertNotIn(objdiff.literal_token(b'\0',1),tokens[2])

if __name__=='__main__': unittest.main()
