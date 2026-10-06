#!/usr/bin/env python3
"""ghidra_cpp.py rewrites: literals survive exactly, NaN guards go only where provably redundant."""
import unittest
from unittest.mock import patch

import ghidra_cpp


class LiteralTest(unittest.TestCase):
    def inline(self, literal):
        text = ("\n    std::wstring::wstring((wstring *)&local_58, " + literal + ", &local_59);"
                "\n    std::wstring local_58;\n    consume((wstring *)&local_58);")
        return ghidra_cpp.inline_temp_strings(text)

    def test_literals_are_kept_byte_for_byte(self):
        for literal in [r'L"media\\resources.dat"', r'L"media\\levelsets\\"', r'L"line\nnext"',
                        r'L"quote\"here"', 'L"simple"', r'"\1\g<0>"']:
            self.assertIn(f"consume({literal});", self.inline(literal), literal)


class NanTest(unittest.TestCase):
    def tidy(self, text):
        return ghidra_cpp.tidy_expressions(text, proven_nan_operands=True)

    def test_redundant_guards_go(self):
        self.assertEqual(self.tidy("if (!NAN(a) && a == b) {"), "if (a == b) {")
        self.assertEqual(self.tidy("if ((!NAN(a) && !NAN(b)) && a < b) {"), "if (a < b) {")
        self.assertEqual(self.tidy("if (a <= b && !NAN(a)) {"), "if (a <= b) {")
        self.assertEqual(self.tidy("x = !NAN(f) && f >= 0.5;"), "x = f >= 0.5;")
        self.assertEqual(self.tidy("if (!NAN(p->x) && p->x < y) {"), "if (p->x < y) {")
        self.assertEqual(self.tidy("if (!NAN(b) && a < -b) {"), "if (a < -b) {")

    def test_guards_that_change_meaning_stay(self):
        for text in ["if (!NAN(x) && enabled) {", "if (!NAN(a) && !(a < b)) {", "if (!NAN(a) && a != b) {",
                     "if (!NAN(c) && a < b) {", "if (NAN(a) || a < b) {"]:
            self.assertEqual(self.tidy(text), text)

    def test_guard_on_a_name_inside_an_operand_stays(self):
        # x and p->x are different values: NaN in x with a number in p->x changes the result.
        for text in ["if (!NAN(x) && p->x < y) {", "if (!NAN(x) && y < p->x) {", "if (p->x < y && !NAN(x)) {",
                     "if (!NAN(x) && a[x] < y) {", "if (!NAN(x) && x * 2 < y) {", "if (!NAN(x) && s.x < y) {"]:
            self.assertEqual(self.tidy(text), text)


class HiddenReturnTest(unittest.TestCase):
    draft = (
        "\nwstring * __thiscall\nCUnit::getStats(wstring *__return_storage_ptr__,CUnit *this,CSkill *param_3,int param_4)\n"
        "\n{\n  allocator local_29 [9];\n  \n  if (param_3 == (CSkill *)0x0) {\n"
        "    std::wstring::wstring((wstring *)__return_storage_ptr__,L\"\",local_29);\n  }\n  else {\n"
        "    CSkill::getLevelStats(__return_storage_ptr__,param_3,param_4);\n  }\n"
        "  return __return_storage_ptr__;\n}\n")

    def test_function_returning_through_the_hidden_pointer(self):
        f = {"demangled": "CUnit::getStats(CSkill*, int)", "params": "CSkill*, int", "kind": "function"}
        with patch.object(ghidra_cpp, "returned_by_pointer", return_value={"CSkill::getLevelStats"}):
            out = ghidra_cpp.convert(self.draft, {("CSkill", "getLevelStats")}, f)
        self.assertIn("std::wstring CUnit::getStats(CSkill* param_1, int param_2)", out)
        self.assertIn('return L"";', out)
        self.assertIn("return param_1->CSkill::getLevelStats(param_2);", out)
        self.assertNotIn("__return_storage_ptr__", out)
        self.assertIn("allocator local_29", out)  # no lifetime proof for dropping it

    def test_call_of_such_a_function_assigns_its_result(self):
        with patch.object(ghidra_cpp, "returned_by_pointer", return_value={"CUnit::getName"}):
            out = ghidra_cpp.hidden_return_calls("\n  CUnit::getName(&local_40,pUnit);\n  CUnit::other(&local_48,pUnit);")
        self.assertIn("local_40 = CUnit::getName(pUnit);", out)
        self.assertIn("CUnit::other(&local_48,pUnit);", out)

    def test_reference_parameters_take_the_object(self):
        signatures = {"addSkill": [["std::wstring const&", "bool"]], "use": [["Foo*"], ["Foo&"]]}
        self.assertEqual(ghidra_cpp.reference_arguments("addSkill(&m_sName, false)", signatures),
                         "addSkill(m_sName, false)")
        self.assertEqual(ghidra_cpp.reference_arguments("use(&x)", signatures), "use(&x)")


class TArrayListTest(unittest.TestCase):
    def test_element_address_with_the_capacity_check(self):
        for draft in [
                "\n    if (uVar2 < (this->m_Objects).m_nCapacity) {\n      ppCVar1 = (this->m_Objects).m_pData + uVar2;\n"
                "    }\n    else {\n      ppCVar1 = (this->m_Objects).m_pData;\n    }",
                "\n    if (uVar5 < (this->m_Groups).m_nCapacity) {\n"
                "      ppCVar1 = (string *)((ulong)uVar5 * 8 + (long)(this->m_Groups).m_pData);\n    }\n    else {\n"
                "      ppCVar1 = (this->m_Groups).m_pData;\n    }".replace("m_Groups", "m_Objects").replace("uVar5", "uVar2"),
                "\n    ppCVar1 = (this->m_Objects).m_pData;\n    \n    if (uVar2 < (this->m_Objects).m_nCapacity) {\n"
                "      ppCVar1 = (this->m_Objects).m_pData + uVar2;\n    }"]:
            self.assertEqual(ghidra_cpp.tarraylist_access(draft), "\n    ppCVar1 = &this->m_Objects[uVar2];")

    def test_element_value_and_return(self):
        self.assertEqual(ghidra_cpp.tarraylist_access(
            "\n  if (param_3 < (this->m_Flags).m_nCapacity) {\n    return (this->m_Flags).m_pData[param_3];\n  }\n"
            "  return *(this->m_Flags).m_pData;"), "\n  return this->m_Flags[param_3];")
        self.assertEqual(ghidra_cpp.tarraylist_access(
            "\n  if (i < local_f8.m_List.m_nCapacity) {\n    v = local_f8.m_List.m_pData[i];\n  }\n  else {\n"
            "    v = *local_f8.m_List.m_pData;\n  }"), "\n  v = local_f8.m_List[i];")

    def test_other_shapes_stay(self):
        for draft in [
                # a different index in the element than in the check
                "\n  if (i < (this->m_A).m_nCapacity) {\n    p = (this->m_A).m_pData + j;\n  }\n  else {\n"
                "    p = (this->m_A).m_pData;\n  }",
                # a different list in the fallback
                "\n  if (i < (this->m_A).m_nCapacity) {\n    p = (this->m_A).m_pData + i;\n  }\n  else {\n"
                "    p = (this->m_B).m_pData;\n  }",
                # a precomputed offset: not checked against the index
                "\n  p = (this->m_A).m_pData;\n  if (i < (this->m_A).m_nCapacity) {\n"
                "    p = (C **)(lVar9 + (long)(this->m_A).m_pData);\n  }"]:
            self.assertEqual(ghidra_cpp.tarraylist_access(draft), draft)

    def test_count_reads_become_size(self):
        self.assertEqual(ghidra_cpp.tarraylist_count("while (uVar2 < (this->m_Objects).m_nCount) {"),
                         "while (uVar2 < this->m_Objects.size()) {")
        self.assertEqual(ghidra_cpp.tarraylist_count("if (local_f8.m_List.m_nCount != 0) {"),
                         "if (local_f8.m_List.size() != 0) {")
        for write in ["(this->m_A).m_nCount = 0;", "(this->m_A).m_nCount = uVar1 - 1;", "p = &(this->m_A).m_nCount;",
                      "(this->m_A).m_nCount++;", "--(this->m_A).m_nCount;"]:
            self.assertEqual(ghidra_cpp.tarraylist_count(write), write)


if __name__ == "__main__":
    unittest.main()
