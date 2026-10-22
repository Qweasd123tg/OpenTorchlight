"""Exact imported compare and finite forward normal-return lifetime proofs."""
import unittest
from unittest.mock import patch
import objdiff
import test_objdiff_literal_use as literal_tests


class CompareLifetimeTest(unittest.TestCase):
    def setUp(self):
        self.fixture = literal_tests.ForwardLifetimeTest()
        self.side = self.fixture.side()
        self.side.image.plt[0x555000] = self.side.WSTRING_COMPARE

    def rows(self):
        return [[0x100,'mov','$0xff0000,%esi'],
                [0x105,'call','555000 <compare@plt>'],
                [0x10a,'test','%eax,%eax'],
                [0x10c,'je','120 <return>'],
                [0x10e,'mov','$0x0,%esi'],
                [0x113,'call','555999 <unknown after full kill>'],
                [0x118,'ret',''],[0x120,'ret','']]

    def proof(self, rows=None):
        return self.side.wide_literal_use(0, rows or self.rows(), 0x100, 0x121)

    def test_branch_kill_or_abi_return(self):
        proof = self.proof()
        self.assertEqual(proof['callee'], self.side.WSTRING_COMPARE)
        self.assertEqual(proof['normal']['kills'], [0x10e])
        self.assertEqual(proof['normal']['returns'], [0x120])
        self.assertNotIn(0x113, proof['normal']['visited'])

    def test_all_branches_checked(self):
        for slot in (4, 7):
            rows=self.rows();rows[slot][1:]=['mov','%rsi,%rax']
            self.assertIsNone(self.proof(rows))

    def test_loops_indirect_midinstruction_and_external_branches_reject(self):
        for target in ['10a <loop>','10c <self>','101 <middle>','999 <outside>','*%rax']:
            rows=self.rows();rows[3][2]=target
            self.assertIsNone(self.proof(rows))

    def test_implicit_partial_alias_escape_reject(self):
        for op,args in [('lodsq',''),('syscall',''),('rep movsq',''),
                        ('mov','%ax,%si'),('mov','%al,%sil'),('mov','%rsi,%rbx'),
                        ('mov','%rsi,(%rax)'),('test','%rsi,%rsi'),('call','*%rax'),
                        ('call','555999 <unknown>')]:
            rows=self.rows();rows[2][1:]=[op,args]
            with self.subTest(op=op,args=args):self.assertIsNone(self.proof(rows))

    def test_known_call_may_preserve_then_return(self):
        rows=self.rows();rows[2][1:]=['call','555100 <delete>']
        self.assertTrue(self.proof(rows)['normal']['calls'])
        rows[-1][1:]=['mov','%rsi,%rax']
        self.assertIsNone(self.proof(rows))

    def test_callee_kill_not_promoted_to_unconditional_caller_kill(self):
        rows=self.rows();rows[2][1:]=['call','555999 <nullable wrapper>']
        with patch.object(self.side,'_nonobserving_callee',return_value={'effect':'may-preserve-not-observe','kills':[123]}):
            self.assertIsNotNone(self.proof(rows))
            rows[-1][1:]=['mov','%rsi,%rax']
            self.assertIsNone(self.proof(rows))

    def test_compare_exact_import_only(self):
        for name in ['',self.side.WSTRING_COMPARE+'X','_ZNKSs7compareEPKc']:
            self.side.image.plt[0x555000]=name
            self.assertIsNone(self.proof())
        self.side.image.plt={};self.side.func_start[0x555000]=self.side.WSTRING_COMPARE
        self.assertIsNone(self.proof())

    def test_compare_payload_complete_and_site_local(self):
        tokens=[]
        for raw in ['AX\0'.encode('utf-32le'),'AY\0'.encode('utf-32le')]:
            self.side=self.fixture.side(raw)
            self.side.image.plt[0x555000]=self.side.WSTRING_COMPARE
            tokens.append(self.side.normalize(self.rows(),0x100,0x121)[0])
            self.assertEqual(self.side.literal_proofs[0]['size'],12)
            self.assertIn('unverified-data:',self.side.name_at(0xff0000,'mov',True))
        self.assertNotEqual(*tokens)
        self.side=self.fixture.side(b'A\0\0\0');self.side.image.plt[0x555000]=self.side.WSTRING_COMPARE
        self.side.normalize(self.rows(),0x100,0x121)
        self.assertFalse(self.side.literal_proofs)

    def test_no_preconsumer_copy_or_alternate_path(self):
        for op,args in [('mov','%rsi,%rax'),('mov','%rsi,(%rsp)'),('je','105 <consumer>'),('call','555100 <delete>')]:
            rows=self.rows();rows.insert(1,[0x103,op,args])
            self.assertIsNone(self.proof(rows))

    def test_normal_call_eh_continuation_independent(self):
        rows=self.rows();rows[2][1:]=['call','555100 <delete>']
        rows += [[0x130,'mov','%rax,%rdi'],[0x133,'call','555200 <resume>']]
        eh={'kind':'gcc447-cleanup-v1','rows':[(0xa,1,0x30,0)]}
        with patch.object(self.side,'_literal_eh',return_value=eh):
            self.assertTrue(self.proof(rows)['normal']['cleanup'])
            rows[-2][1:]=['mov','%rsi,%rax']
            self.assertIsNone(self.proof(rows))

    def test_consumer_eh_and_malformed_eh(self):
        rows=self.rows()+[[0x130,'mov','%rsi,%rax'],[0x133,'call','555200 <resume>']]
        eh={'kind':'gcc447-cleanup-v1','rows':[(5,5,0x30,0)]}
        with patch.object(self.side,'_literal_eh',return_value=eh):self.assertIsNone(self.proof(rows))
        with patch.object(self.side,'_literal_eh',return_value=None):self.assertIsNone(self.proof())

    def test_missing_return_and_unknown_import_not_inferred(self):
        rows=self.rows();rows[-1][1:]=['nop','']
        self.assertIsNone(self.proof(rows))
        self.side.image.plt[0x555300]='_ZNSbIwSt11char_traitsIwESaIwEED1Ev'
        rows=self.rows();rows[2][1:]=['call','555300 <wstring dtor not yet supported>']
        self.assertIsNone(self.proof(rows))


if __name__=='__main__': unittest.main()
