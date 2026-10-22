"""Acyclic normal continuations and explicit standard destructor ABI contract."""
import unittest
import objdiff
from unittest.mock import patch
import test_objdiff_literal_use as literal_tests


class AcyclicLifetimeTest(unittest.TestCase):
    def setUp(self):
        self.side = literal_tests.ForwardLifetimeTest().side()
        self.eh = {'kind':'no-lsda','rows':[]}

    def rows(self):
        return [[0x100,'jmp','110 <later block>'],[0x105,'test','%eax,%eax'],
                [0x107,'je','120 <return>'],[0x109,'mov','%eax,%esi'],
                [0x110,'mov','%rbx,%rax'],[0x113,'jmp','105 <earlier block>'],
                [0x120,'ret','']]

    def proof(self, rows=None):
        return self.side._rsi_normal_dead(rows or self.rows(),0x100,0x100,self.eh)

    def test_backward_layout_not_cycle(self):
        proof=self.proof()
        self.assertEqual(proof['cfg'],'acyclic-dfs-v1')
        self.assertEqual(proof['kills'],[0x109]);self.assertEqual(proof['returns'],[0x120])

    def test_self_and_multiblock_cycles_reject(self):
        for target in ['107 <self>','110 <actual cycle>','100 <entry cycle>']:
            rows=self.rows();rows[2][2]=target
            with self.subTest(target=target):self.assertIsNone(self.proof(rows))

    def test_cycle_unreachable_after_full_kill_irrelevant(self):
        rows=self.rows();rows[4][1:]=['mov','%eax,%esi']
        rows[5][1:]=['jmp','113 <self>']
        self.assertIsNotNone(self.proof(rows))

    def test_merge_with_live_read_and_partial_kill_reject(self):
        rows=self.rows();rows[-1][1:]=['mov','%rsi,%rax'];self.assertIsNone(self.proof(rows))
        rows=self.rows();rows[3][1:]=['mov','%ax,%si'];self.assertIsNone(self.proof(rows))

    def test_shared_completed_merge_not_cycle(self):
        rows=[[0x100,'je','110 <right>'],[0x105,'jmp','120 <merge>'],
              [0x110,'jmp','120 <merge>'],[0x120,'ret','']]
        self.assertIsNotNone(self.proof(rows))
        rows[-1][1:]=['mov','%rsi,%rbx'];self.assertIsNone(self.proof(rows))

    def test_xorps_only_explicit_xmm_registers(self):
        for args in ['%xmm0,%xmm0','%xmm1,%xmm15','%xmm12,%xmm2']:
            rows=self.rows();rows[4][1:]=['xorps',args]
            self.assertIsNotNone(self.proof(rows))
        for op,args in [('xorps','(%rax),%xmm0'),('xorps','(%rsi),%xmm0'),
                        ('xorps','%eax,%xmm0'),('xorps','%xmm0,%esi'),
                        ('xorps','%xmm16,%xmm0'),('xorps','%xmm0'),
                        ('xorps','%xmm0,%xmm0,%xmm1'),('xorps','%xmm0,%xmm0 # extra'),
                        ('vxorps','%xmm0,%xmm0,%xmm0'),('movaps','%xmm0,%xmm1')]:
            with self.subTest(op=op,args=args):
                self.assertFalse(self.side._literal_independent_instruction(op,args))

    def test_xorps_between_consumer_and_integer_kill(self):
        rows=[[0x100,'mov','$0xff0000,%esi'],[0x105,'call','555000 <ctor>'],
              [0x10a,'xorps','%xmm0,%xmm0'],[0x10d,'mov','%rbx,%rsi'],[0x110,'ret','']]
        # Public entrypoint must not bypass lifetime checks via legacy prefix.
        self.assertIsNotNone(self.side.wide_literal_use(0,rows,0x100,0x111))
        rows[2][2]='(%rsi),%xmm0'
        self.assertIsNone(self.side.wide_literal_use(0,rows,0x100,0x111))

    def test_legacy_prefix_public_api_rejects_postconsumer_observation(self):
        for op,args in [('mov','%rsi,%rax'),('mov','(%rsi),%rax'),
                        ('mov','%rsi,(%rsp)'),('mov','%ax,%si'),
                        ('xorps','(%rsi),%xmm0'),('call','555999 <unknown>')]:
            rows=[[0x100,'mov','$0xff0000,%esi'],[0x105,'call','555000 <ctor>'],
                  [0x10a,op,args],[0x10d,'ret','']]
            with self.subTest(op=op,args=args):
                self.assertIsNone(self.side.wide_literal_use(0,rows,0x100,0x10e))
                self.side.normalize(rows,0x100,0x10e)
                self.assertFalse(self.side.literal_proofs)

    def test_legacy_prefix_needs_bounds_and_eh_and_validates_cleanup(self):
        rows=[[0x100,'mov','$0xff0000,%esi'],[0x105,'call','555000 <ctor>'],
              [0x10a,'ret',''],[0x110,'mov','%rsi,%rax'],[0x113,'call','555200 <resume>']]
        self.assertIsNone(self.side.wide_literal_use(0,rows))
        with patch.object(self.side,'_literal_eh',return_value=None):
            self.assertIsNone(self.side.wide_literal_use(0,rows,0x100,0x118))
        eh={'kind':'gcc447-cleanup-v1','rows':[(5,5,16,0)]}
        with patch.object(self.side,'_literal_eh',return_value=eh):
            self.assertIsNone(self.side.wide_literal_use(0,rows,0x100,0x118))

    def test_real_objdump_lock_parser_form(self):
        rows=objdiff.parse_insns("  c72e37:\tlock xadd %eax,0x10(%rdi)\n")
        self.assertEqual(rows,[[0xc72e37,'lock xadd','%eax,0x10(%rdi)']])
        self.assertTrue(self.side._literal_independent_instruction(*rows[0][1:]))

    def test_or_and_atomic_exact_independent_operands(self):
        for op,args in [('or','$0xffffffff,%eax'),('lock xadd','%eax,0x10(%rdi)'),
                        ('lock xadd','%rax,(%rbx)')]:
            rows=self.rows();rows[4][1:]=[op,args]
            with self.subTest(op=op,args=args):self.assertIsNotNone(self.proof(rows))

    def test_atomic_alias_partial_unknown_and_implicit_effects_reject(self):
        for op,args in [('or','$0x1,%sil'),('or','%rsi,%rax'),
                        ('lock xadd','%esi,(%rbx)'),('lock xadd','%eax,(%rsi)'),
                        ('lock xadd','%ax,(%rbx)'),('lock xadd','%al,(%rbx)'),
                        ('lock','cmpxchg %eax,(%rbx)'),('lock xadd','%eax,%ebx'),
                        ('lock xadd','%eax,%fs:0x10(%rbx)'),('lahf',''),('sahf',''),
                        ('pushf',''),('rep movsq',''),('adc','$0x0,%eax')]:
            rows=self.rows();rows[4][1:]=[op,args]
            with self.subTest(op=op,args=args):self.assertIsNone(self.proof(rows))

    def test_destructor_exact_import_standard_abi_not_library_bytes(self):
        self.side.image.plt[0x555300]=self.side.WSTRING_DTOR
        with patch.object(self.side,'_pinned_literal_library',side_effect=AssertionError('must not infer original DSO')):
            proof=self.side._nonobserving_callee(self.side.image,0x555300)
        self.assertEqual(proof['kind'],'standard-library-abi-no-rsi-input')
        self.assertEqual(proof['contract'],'wstring-D1-this-only-v1')
        self.assertEqual(proof['effect'],'may-preserve-not-observe')
        self.assertNotIn('body_sha256',proof)

    def test_destructor_other_specialization_and_local_name_reject(self):
        for name in [self.side.WSTRING_DTOR+'X',self.side.WSTRING_DTOR.replace('D1','D2'),'_ZNSsD1Ev']:
            self.side.image.plt[0x555300]=name
            self.assertIsNone(self.side._nonobserving_callee(self.side.image,0x555300))
        del self.side.image.plt[0x555300]
        self.side.func_start[0x555300]=self.side.WSTRING_DTOR
        self.assertIsNone(self.side._nonobserving_callee(self.side.image,0x555300))

    def test_destructor_may_preserve_caller_read_rejected(self):
        self.side.image.plt[0x555300]=self.side.WSTRING_DTOR
        rows=self.rows();rows[4][1:]=['call','555300 <dtor>']
        self.assertIsNotNone(self.proof(rows))
        rows[-1][1:]=['mov','%rsi,%rax'];self.assertIsNone(self.proof(rows))

    def test_destructor_eh_no_observation_separately(self):
        self.side.image.plt[0x555300]=self.side.WSTRING_DTOR
        rows=[[0x100,'call','555300 <dtor>'],[0x105,'ret',''],
              [0x110,'mov','%rax,%rdi'],[0x113,'call','555200 <resume>']]
        self.eh={'kind':'gcc447-cleanup-v1','rows':[(0,5,16,0)]}
        self.assertTrue(self.proof(rows)['cleanup'])
        rows[-2][1:]=['mov','%rsi,%rax'];self.assertIsNone(self.proof(rows))


if __name__=='__main__': unittest.main()
