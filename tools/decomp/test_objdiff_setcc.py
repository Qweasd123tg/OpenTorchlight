"""SETcc nonobservation is byte-local, never a raw-pointer kill or predicate."""
import unittest
from unittest.mock import patch
import objdiff
import test_objdiff_literal_use as literal_tests

class SetccTest(unittest.TestCase):
    conditions = ('a ae b be c e g ge l le na nae nb nbe nc ne ng nge nl nle no np ns nz o p pe po s z').split()
    def setUp(self):
        self.side=literal_tests.ForwardLifetimeTest().side()
    def rows(self, op='setne', args='%al'):
        return [[0x100,'mov','$0xff0000,%esi'],[0x105,'call','555000 <ctor>'],
                [0x10a,'test','%eax,%eax'],[0x10c,op,args],[0x10f,'ret','']]
    def proof(self,rows):return self.side.wide_literal_use(0,rows,0x100,rows[-1][0]+1)
    def test_exact_conditions_byte_registers(self):
        for cc in self.conditions:
            for reg in ('al','ah','bl','bh','cl','ch','dl','dh','dil','bpl','r8b','r15b'):
                with self.subTest(cc=cc,reg=reg):
                    self.assertTrue(self.side._literal_independent_instruction('set'+cc,'%'+reg))
        for cc in self.conditions:
            self.assertIsNotNone(self.proof(self.rows('set'+cc)))
    def test_all_blocked_alias_families_reject(self):
        for reg,family in [('al','a'),('ah','a'),('bl','b'),('bh','b'),('cl','c'),('ch','c'),
                           ('dl','d'),('dh','d'),('sil','si'),('dil','di'),('bpl','bp'),('r8b','8'),('r15b','15')]:
            for cc in self.conditions:
                self.assertFalse(self.side._literal_independent_instruction('set'+cc,'%'+reg,blocked={family}))
    def test_malformed_memory_prefixes_widths_reject(self):
        for op,args in [('setne','%eax'),('sete','%rax'),('sete','%ax'),('sete','%xmm0'),
                        ('sete','(%rax)'),('sete','(%rsi)'),('sete','%fs:0x8(%rax)'),
                        ('sete','%al,%bl'),('sete','%al # extra'),('sete','%r16b'),
                        ('sete','%spl'),('sete','%%al'),('sete','%al '),('sete','%r08b'),('sete',''),('setfoo','%al'),('setneb','%al'),
                        ('lock sete','%al'),('rep sete','%al'),('addr32 sete','%al'),('set','%al')]:
            with self.subTest(op=op,args=args):
                self.assertFalse(self.side._literal_independent_instruction(op,args))
    def test_partial_byte_write_is_not_pointer_kill(self):
        self.assertFalse(self.side._rsi_kill('sete','%sil'))
        self.assertIsNone(self.proof(self.rows('sete','%sil')))
        rows=self.rows();rows.insert(-1,[0x10e,'mov','%rsi,%rax'])
        self.assertIsNone(self.proof(rows))
    def test_public_compare_normal_and_exception_paths(self):
        self.side.image.plt[0x555000]=self.side.WSTRING_COMPARE
        self.assertIsNotNone(self.proof(self.rows('sete')))
        rows=self.rows();rows += [[0x120,'setne','%al'],[0x123,'call','555200 <resume>']]
        eh={'kind':'gcc447-cleanup-v1','rows':[(5,5,32,0)]}
        with patch.object(self.side,'_literal_eh',return_value=eh):
            self.assertIsNotNone(self.proof(rows))
            rows[-2][2]='%sil'
            self.assertIsNone(self.proof(rows))
    def test_setcc_does_not_prune_unsafe_branch(self):
        rows=self.rows();rows[-1:]=[[0x10f,'je','120 <unsafe>'],[0x112,'ret',''],
                                  [0x120,'mov','%rsi,%rax'],[0x123,'ret','']]
        self.assertIsNone(self.proof(rows))

if __name__=='__main__':unittest.main()
