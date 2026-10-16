#!/usr/bin/env python3
import tempfile
import unittest
from pathlib import Path

import llm_loop
import objdiff


class FakeGen:
    def __init__(self, decls):
        self.decls = decls

    def ghidra_return(self, f):
        return "int"

    def method_decl(self, f, cls, deps, ret=None):
        decl, forward = self.decls[f["method"]]
        deps["forward"] |= forward
        return decl


def func(cls, method, kind="function", vslots=None):
    return {"scope": cls, "method": method, "kind": kind, "vslots": vslots}


class CompleteHandHeader(unittest.TestCase):
    def complete(self, header, funcs, decls):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "decomp" / "include").mkdir(parents=True)
            (root / "decomp" / "include" / "Unit.h").write_text(header)
            old_root, old_code = llm_loop.ROOT, llm_loop.return_from_code
            llm_loop.ROOT, llm_loop.return_from_code = root, lambda f: None
            try:
                loop = llm_loop.Loop.__new__(llm_loop.Loop)
                loop.funcs, loop._decls = funcs, FakeGen(decls)
                added = loop.complete_hand_header("CUnit", "Unit.h")
            finally:
                llm_loop.ROOT, llm_loop.return_from_code = old_root, old_code
            return added, (root / "decomp" / "include" / "Unit.h").read_text()

    header = ("#ifndef UNIT_H\n#define UNIT_H\nclass CUnit\n{\npublic:\n    virtual ~CUnit();\n"
              "    int getA();\nprivate:\n    int m_iA;\n};\n#endif\n")

    def test_missing_methods_go_to_the_end_of_the_public_section(self):
        added, text = self.complete(self.header, [func("CUnit", "getA"), func("CUnit", "setTarget")],
                                    {"setTarget": ("void setTarget(CTarget*);", {"CTarget"})})
        self.assertEqual(added, ["void setTarget(CTarget*);"])
        self.assertIn("    int getA();\n    void setTarget(CTarget*);\nprivate:", text)
        self.assertIn("class CTarget;\nclass CUnit\n", text)

    def test_virtual_and_other_class_methods_are_left_alone(self):
        added, text = self.complete(self.header, [func("CUnit", "update", vslots=[3]), func("COther", "run")],
                                    {"update": ("void update();", set()), "run": ("void run();", set())})
        self.assertEqual(added, [])
        self.assertEqual(text, self.header)

    def test_existing_short_name_does_not_hide_cv_overload(self):
        function = {**func("CUnit", "getA"), "params": "", "cv": "const"}
        added, text = self.complete(self.header, [function], {"getA": ("int getA() const;", set())})
        self.assertEqual(["int getA() const;"], added)
        self.assertIn("int getA();\n    int getA() const;", text)

    def test_class_without_public_section_gets_one(self):
        header = "class CUnit\n{\n    int m_iA;\n};\n"
        added, text = self.complete(header, [func("CUnit", "getA")], {"getA": ("int getA();", set())})
        self.assertEqual(text, "class CUnit\n{\n    int m_iA;\npublic:\n    int getA();\n};\n")
        header = "struct CUnit\n{\n    int m_iA;\n};\n"
        added, text = self.complete(header, [func("CUnit", "getA")], {"getA": ("int getA();", set())})
        self.assertEqual(text, "struct CUnit\n{\n    int m_iA;\n    int getA();\n};\n")
        header = "class CUnit\n{\nprivate:\n    int m_iA;\n};\n"
        added, text = self.complete(header, [func("CUnit", "getA")], {"getA": ("int getA();", set())})
        self.assertIn("    int m_iA;\npublic:\n    int getA();\n};", text)


class DeclarationReadiness(unittest.TestCase):
    def check(self, files, scope, method, params, cv=""):
        from unittest.mock import patch
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "decomp/include").mkdir(parents=True)
            for name, body in files.items():
                (root / "decomp/include" / name).write_text(body)
            loop = llm_loop.Loop.__new__(llm_loop.Loop)
            loop.headers = {scope.split("::")[0]: next(iter(files))}
            with patch.object(llm_loop, "ROOT", root):
                return loop.declaration_error({"scope": scope, "method": method, "params": params, "cv": cv})

    def test_destructor_is_recognized_without_becoming_a_default_constructor(self):
        files = {"Unit.h": "class CUnit\n{\npublic:\n virtual ~CUnit();\n};\n"}
        self.assertIsNone(self.check(files, "CUnit", "~CUnit", ""))
        self.assertIsNotNone(self.check(files, "CUnit", "CUnit", ""))

    def test_packed_owner_keeps_its_hand_written_layout(self):
        from unittest.mock import patch
        header = ("class CBase;\nclass __attribute__((packed)) CUnit : public CBase\n"
                  "{\npublic:\n int work(int value);\n CPoint* m_head;\n};\n")
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "decomp/include").mkdir(parents=True)
            (root / "build-decomp/include-gen").mkdir(parents=True)
            path = root / "decomp/include/Unit.h"
            path.write_text(header)
            generated = root / "build-decomp/include-gen/CUnit.h"
            generated.write_text("class CUnit { void* m_unknown; };\n")
            loop = llm_loop.Loop.__new__(llm_loop.Loop)
            loop.classes, loop.funcs, loop.allowed_headers = ["CUnit"], [], set()
            with patch.object(llm_loop, "ROOT", root):
                self.assertEqual({"CUnit": ["Unit.h"]}, llm_loop.headers_by_class())
                loop.header()
                self.assertIsNone(loop.declaration_error(
                    {"scope": "CUnit", "method": "work", "params": "int", "cv": ""}))
                self.assertIsNotNone(loop.declaration_error(
                    {"scope": "CUnit", "method": "work", "params": "float", "cv": ""}))
            self.assertEqual(header, path.read_text())
            self.assertTrue(generated.exists())
            self.assertFalse(loop.allowed_headers)

    def test_constructor_and_destructor_signatures_stay_separate(self):
        files = {"Unit.h": "class CUnit\n{\npublic:\n CUnit(int);\n virtual ~CUnit();\n};\n"}
        self.assertIsNone(self.check(files, "CUnit", "CUnit", "int"))
        self.assertIsNotNone(self.check(files, "CUnit", "CUnit", ""))
        self.assertIsNone(self.check(files, "CUnit", "~CUnit", ""))
        self.assertIsNotNone(self.check(files, "CUnit", "~CUnit", "int"))

    def test_destructor_does_not_match_identifier_suffix_or_nested_class(self):
        files = {"Unit.h": "class CUnit\n{\npublic:\n virtual ~OtherCUnit();\n struct Inner { ~CUnit(); };\n};\n"}
        self.assertIsNotNone(self.check(files, "CUnit", "~CUnit", ""))

    def test_reopened_namespace_finds_exact_declaration_in_another_header(self):
        files = {"Globals.h": "namespace STRINGS { extern int counter; }",
                 "Strings.h": "namespace STRINGS { std::string upper(const std::string& text); }"}
        self.assertIsNone(self.check(files, "STRINGS", "upper", "std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&"))
        self.assertIsNotNone(self.check(files, "STRINGS", "upper", "std::wstring const&"))

    def test_nested_namespace_does_not_borrow_unrelated_or_nested_class_declaration(self):
        files = {"Names.h": "namespace A { namespace B { int work(int); struct C { int work(float); }; } } namespace Other { int work(double); }"}
        self.assertIsNone(self.check(files, "A::B", "work", "int"))
        self.assertIsNotNone(self.check(files, "A::B", "work", "float"))
        self.assertIsNotNone(self.check(files, "A::B", "work", "double"))

    def test_template_defaults_match_without_accepting_a_custom_allocator_or_wrong_cv(self):
        files = {"Unit.h": "class CUnit\n{\npublic:\n void work(const std::vector<unsigned int>& values);\n};\n"}
        self.assertIsNone(self.check(files, "CUnit", "work", "std::vector<unsigned int, std::allocator<unsigned int> > const&"))
        self.assertIsNotNone(self.check(files, "CUnit", "work", "std::vector<unsigned int, CustomAllocator<unsigned int> > const&"))
        self.assertIsNotNone(self.check(files, "CUnit", "work", "std::vector<unsigned int>&"))

    def test_map_defaults_keep_custom_comparator_and_pointer_key_const_distinct(self):
        files = {"Unit.h": "class CUnit\n{\npublic:\n void work(std::map<int*, bool>& values);\n};\n"}
        exact = "std::map<int*, bool, std::less<int*>, std::allocator<std::pair<int* const, bool> > >&"
        self.assertIsNone(self.check(files, "CUnit", "work", exact))
        self.assertIsNotNone(self.check(files, "CUnit", "work", exact.replace("std::less<int*>", "OtherLess<int*>")))
        self.assertIsNotNone(self.check(files, "CUnit", "work", exact.replace("int* const", "const int*")))
        self.assertIsNotNone(self.check(files, "CUnit", "work", exact, "const"))

    def test_nested_parameter_uses_its_declared_lexical_type(self):
        files = {"Unit.h": "struct Point;\nclass CUnit\n{\npublic:\n struct Point;\n void work(Point* value);\n};\n"}
        self.assertIsNone(self.check(files, "CUnit", "work", "CUnit::Point*"))
        self.assertIsNotNone(self.check(files, "CUnit", "work", "Point*"))
        self.assertIsNotNone(self.check(files, "CUnit", "work", "COther::Point*"))


class AsmLabels(unittest.TestCase):
    def test_labels_bound_to_mangled_names_are_refused(self):
        self.assertTrue(llm_loop.ASM_LABEL.search('extern "C" void f(C*) __asm__("_ZN1C1fEv");'))
        self.assertTrue(llm_loop.ASM_LABEL.search('void f() asm ("_ZN1C1fEv");'))
        self.assertFalse(llm_loop.ASM_LABEL.search('__asm__ volatile ("pause");'))


class UnknownMembers(unittest.TestCase):
    db = {"classes": {"CUnit": {}, "Ogre": {}},
          "functions": {"0x1": {"scope": "CUnit", "method": "get", "demangled": "CUnit::get(int)"}}}

    def test_members_of_game_classes_absent_from_the_original(self):
        names = {"_ZN5CUnit3getEi"}
        found = objdiff.unknown_members(self.db, names, ["_ZN5CUnit3getEi", "_ZNK5CUnit3getEi",
                                                         "_ZN4Ogre4Math4SqrtEf", "memcpy"])
        self.assertEqual(found, ["_ZNK5CUnit3getEi"])
        self.assertEqual(objdiff.known_overloads(self.db, "_ZNK5CUnit3getEi"), ["CUnit::get(int)"])


if __name__ == "__main__":
    unittest.main()
