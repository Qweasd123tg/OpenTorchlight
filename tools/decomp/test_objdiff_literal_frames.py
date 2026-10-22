import copy
import unittest
import objdiff_literal_frames as frames

CFI='''000004b0 000000000000001c 00000000 CIE "zPLR" cf=1 df=-8 ra=16
   LOC           CFA      ra
0000000000000000 rsp+8    c-8

000a6a38 0000000000000024 000a658c FDE cie=000004b0 pc=0000000000f620d0..0000000000f622d7
   LOC           CFA      rbx   rbp   r12   r13   ra
0000000000f620d0 rsp+8    u     u     u     u     c-8
0000000000f620dd rsp+8    c-40  c-32  u     u     c-8
0000000000f620eb rsp+112  c-40  c-32  c-24  c-16  c-8
0000000000f621b2 rsp+8    c-40  c-32  c-24  c-16  c-8
0000000000f621b3 rsp+112  c-40  c-32  c-24  c-16  c-8
'''

class FixedFrameTest(unittest.TestCase):
    def table(self,text=CFI):return frames.parse_cfi(text,0xf620d0,0xf622d7)
    def check(self,t):return frames.span_rules(t,0xf62131,0xf62136,-104,
                       {'rbx':-32,'rbp':-24,'r12':-16,'r13':-8})
    def test_empty_fde_inherits_recognized_cie(self):
        text=CFI[:CFI.index('000a6a38')]+"000a6a38 0000000000000014 00000000 FDE cie=000004b0 pc=0000000000f620d0..0000000000f622d7\n\n"
        t=self.table(text);self.assertIsNotNone(frames.span_rules(t,0xf620d0,0xf620d1,0,{}))
        self.assertIsNone(self.table(text.replace('rsp+8    c-8','rsp+16    c-8')))
        self.assertIsNone(self.table(text+'   LOC CFA ra\n'))
    def test_actual_rule_shape(self):self.assertIsNotNone(self.check(self.table()))
    def test_malformed_cie_and_fde(self):
        for text in [CFI.replace('cf=1','cf=2'),CFI.replace('zPLR','zPLRS'),
                     CFI.replace('pc=0000000000f620d0','pc=0000000000f620d1'),
                     CFI+CFI[CFI.index('000a6a38'):],CFI.replace('rsp+8    c-8','rsp+8    u')]:
            self.assertIsNone(self.table(text))
    def test_wrong_cfa_save_or_return_address(self):
        for a,b in [('rsp+112','rsp+104'),('c-24','c-16'),('c-8','u')]:
            self.assertIsNone(self.check(self.table(CFI.replace(a,b))))
    def test_call_interior_cfi_change(self):
        t=self.table();t['rows'].insert(3,(0xf62134,dict(t['rows'][2][1],r12='c-16')))
        self.assertIsNone(self.check(t))
    def test_missing_extra_and_duplicate_columns(self):
        for text in [CFI.replace('r12   r13','r12   r12'),CFI.replace('r13','rdi'),
                     CFI.replace('c-24  c-16','c-24')]:self.assertIsNone(self.table(text))
    def test_local_regions_exclude_private_slots(self):
        for pos,width in [(-104,8),(-72,8),(-41,1)]:
            self.assertTrue(frames.local_access(pos,width,-104,[-32,-24,-16,-8]))
        for pos,width in [(-33,8),(-16,8),(0,8),(-105,1),(-42,16)]:
            self.assertFalse(frames.local_access(pos,width,-104,[-32,-24,-16,-8]))
    def test_no_undefined_preservation(self):
        t=self.table();self.assertIsNone(frames.span_rules(t,0xf620d0,0xf620d5,0,{}))

if __name__=='__main__':unittest.main()
