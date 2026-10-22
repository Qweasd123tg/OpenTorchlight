"""Original-only imported consumer proofs, with fail-closed def-use boundaries."""
import unittest
from unittest.mock import patch
import objdiff_eh
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

class ForwardLifetimeTest(WideUseTest):
    def side(self, raw=None):
        side = super().side(raw)
        side.frames = objdiff_eh.Frames([])
        side.image.plt.update({0x555100: '_ZdlPv', 0x555200: '_Unwind_Resume'})
        return side

    def forward_rows(self):
        return [[0x100, 'call', '555999 <unrelated>'],
                [0x105, 'mov', '$0xff0000,%esi'],
                [0x10a, 'movq', '$0x0,0x10(%rbx)'],
                [0x112, 'mov', '%rbx,%rdi'],
                [0x115, 'call', '555000 <wstring@plt>'],
                [0x11a, 'mov', '0x10(%rbx),%rax'],
                [0x11e, 'xor', '%edx,%edx'],
                [0x120, 'mov', '%rbp,%rsi'],
                [0x123, 'ret', '']]

    def proof(self, side=None, rows=None):
        return (side or self.side()).wide_literal_use(1, rows or self.forward_rows(), 0x100, 0x124)

    def test_forward_proves_only_executed_operand(self):
        proof = self.proof()
        self.assertEqual(proof['model'], 'original-operand-forward-lifetime-v1')
        self.assertEqual(proof['normal_kill'], 0x120)
        # Unrelated control flow / entry bypassing this operand does not type it.
        rows = self.forward_rows(); rows[0] = [0x100, 'jne', '112 <interior>']
        self.assertIsNotNone(self.proof(rows=rows))
        side = self.side(); side.func_start[0x112] = 'separate_entry'
        self.assertIsNotNone(self.proof(side=side))

    def test_forward_rejects_preconsumer_observation_or_escape(self):
        for op, args in [('mov', '%rsi,%r12'), ('movq', '%rsi,(%rsp)'),
                         ('cmp', '%rsi,%rdi'), ('mov', '%al,%sil'),
                         ('lea', '(%rsi),%rdx'), ('call', '555100 <delete>'),
                         ('jne', '115 <consumer>'), ('lodsq',''),
                         ('syscall',''), ('rep movsq','')]:
            rows = self.forward_rows(); rows[2] = [0x10a,op,args]
            with self.subTest(op=op,args=args): self.assertIsNone(self.proof(rows=rows))

    def test_forward_rejects_observation_before_full_kill_or_return(self):
        for op,args in [('mov', '%rsi,%rax'), ('mov', '(%rsi),%rax'),
                        ('mov', '%ax,%si'), ('add', '$0x1,%rsi')]:
            rows=self.forward_rows(); rows[5]=[0x11a,op,args]
            with self.subTest(op=op,args=args): self.assertIsNone(self.proof(rows=rows))
        rows=self.forward_rows();rows[7]=[0x120,'mov','%si,%ax']
        self.assertIsNone(self.proof(rows=rows))
        for op,args in [('mov','%eax,%esi'),('xor','%esi,%esi'),('lea','(%rbx),%rsi')]:
            rows=self.forward_rows();rows[7]=[0x120,op,args]
            self.assertIsNotNone(self.proof(rows=rows))

    def test_forward_rejects_wrong_consumer_and_bad_frames(self):
        side=self.side();side.image.plt[0x555000]='_ZN5SceneC1EPKw'
        self.assertIsNone(self.proof(side=side))
        side=self.side();side.frames=objdiff_eh.Frames([],error='malformed')
        self.assertIsNone(self.proof(side=side))

    def cleanup_case(self):
        side=self.side()
        rows=self.forward_rows()+[[0x124,'mov','%rax,%rbx'],
             [0x127,'test','%rdi,%rdi'],[0x12a,'je','134 <resume>'],
             [0x12c,'call','555100 <delete@plt>'],
             [0x131,'mov','%rbx,%rdi'],[0x134,'call','555200 <resume@plt>']]
        eh={'kind':'gcc447-cleanup-v1','rows':[(0x15,5,0x24,0)]}
        return side,rows,eh

    def test_forward_cleanup_no_rsi_read(self):
        side,rows,eh=self.cleanup_case()
        with patch.object(side,'_literal_eh',return_value=eh):
            proof=side.wide_literal_use(1,rows,0x100,0x139)
        self.assertEqual(proof['cleanup'][0]['entry'],0x124)
        self.assertTrue(proof['cleanup'][0]['calls'])

    def test_forward_cleanup_rejects_alias_unknown_call_and_target(self):
        for op,args in [('mov','%rsi,%r12'),('mov','(%rsi),%rax'),
                        ('mov','%ax,%si'),('call','555333 <unknown>'),
                        ('call','*%rax'),('jmp','999999 <outside>'),('lodsq','')]:
            side,rows,eh=self.cleanup_case();rows[-1]=[0x134,op,args]
            with patch.object(side,'_literal_eh',return_value=eh):
                with self.subTest(op=op,args=args):
                    self.assertIsNone(side.wide_literal_use(1,rows,0x100,0x139))

    def test_forward_full_payload_and_no_global_override(self):
        tokens=[]
        for raw in ['AX\0'.encode('utf-32le'),'AY\0'.encode('utf-32le')]:
            side=self.side(raw);tokens.append(side.normalize(self.forward_rows(),0x100,0x124)[1])
            self.assertEqual(len(side.literal_proofs),1)
            self.assertIn('unverified-data:',side.name_at(0xff0000,'mov',True))
        self.assertNotEqual(*tokens)
        side=self.side(b'A\0\0\0');side.normalize(self.forward_rows(),0x100,0x124)
        self.assertFalse(side.literal_proofs)

if __name__=='__main__': unittest.main()
