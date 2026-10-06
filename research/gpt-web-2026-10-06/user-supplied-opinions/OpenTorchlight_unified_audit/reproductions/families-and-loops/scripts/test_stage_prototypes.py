#!/usr/bin/env python3
"""Synthetic regression tests. These are not original-game equivalence tests."""
from __future__ import annotations
import json
import unittest
import family_deltas as fd
import member_alignment as ma
import loop_obligations as lo

class TokenTests(unittest.TestCase):
    def key(self, text, holes=False):
        return fd.canonical(fd.body_tokens(text)[0], holes)[0]
    def test_comments_do_not_affect_key(self):
        self.assertEqual(self.key('int f(){return 1;}'), self.key('int f(){/* } */return 1;// {\n}'))
    def test_string_braces_are_not_syntax(self):
        body, _ = fd.body_tokens('char* f(){return "}{";} int other;')
        self.assertEqual([v for _,v in body], ['{','return','"}{"',';','}'])
    def test_string_contents_preserved_in_exact_mode(self):
        self.assertNotEqual(self.key('void f(){g("byte");}'), self.key('void f(){g("unsigned char");}'))
    def test_local_alpha_rename(self):
        self.assertEqual(self.key('int f(){int iVar1; iVar1=3; return iVar1;}'),self.key('int f(){int iVar9; iVar9=3; return iVar9;}'))
    def test_label_alpha_rename(self):
        self.assertEqual(self.key('void f(){goto LAB_12; LAB_12:return;}'), self.key('void f(){goto LAB_90; LAB_90:return;}'))
    def test_original_identifier_cannot_collide_with_placeholder(self):
        self.assertNotEqual(self.key('int f(){return LOCAL0;}'), self.key('int f(){return iVar9;}'))
    def test_operator_difference_not_parameterized(self):
        self.assertNotEqual(self.key('int f(){return x+7;}',True), self.key('int f(){return x-7;}',True))
    def test_literal_identity_is_preserved(self):
        self.assertNotEqual(self.key('int f(){return x+7+7;}',True),self.key('int f(){return x+8+9;}',True))
    def test_literal_delta_retained(self):
        a,ab=fd.canonical(fd.body_tokens('int f(){return x+7;}')[0],True)
        b,bb=fd.canonical(fd.body_tokens('int f(){return x+8;}')[0],True)
        self.assertEqual(a,b);self.assertEqual(ab['@NUMBER:0'],'7');self.assertEqual(bb['@NUMBER:0'],'8')
    def test_call_identity_is_preserved(self):
        self.assertNotEqual(self.key('void f(){read();read();}',True), self.key('void f(){read();write();}',True))
    def test_signature_is_intentionally_not_in_key(self):
        self.assertEqual(self.key('int f(int x){return x;}',True), self.key('long f(long x){return x;}',True))
    def test_missing_body_rejected(self):
        self.assertEqual(fd.body_tokens('int f();'),([],[]))
    def test_only_direct_this_offsets_extracted(self):
        ts=fd.tokens('{ x=*(this+0x10); y=*(other+0x20); z=this[24]; }')
        self.assertEqual(sorted(ma.direct_this_offsets(ts).values()),[16,24])
    def test_string_with_fake_offset_not_extracted(self):
        self.assertEqual(ma.direct_this_offsets(fd.tokens('{ print("this+0x10"); }')), {})

class InvariantTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        try: cls.solver=lo.SMT()
        except RuntimeError as e: raise unittest.SkipTest(str(e))
    def test_all_ten_explicit_obligations(self):
        for name,expected,asserts,_ in lo.OBLIGATIONS:
            with self.subTest(obligation=name):
                result=self.solver.check(lo.PRE+asserts+'\n(check-sat)\n')
                self.assertEqual(result.splitlines()[0],expected)

if __name__=='__main__':unittest.main(verbosity=2)
