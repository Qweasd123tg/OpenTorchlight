"""Offline callback declaration identity regressions. No compiler or game."""
import re
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import ghidra_cpp
import headers
import llm_loop
import test_llm_context
import test_llm_loop_headers


CALLBACK = "void (*)(CUnit*, int)"
PARAMS = CALLBACK + ", bool (*)(void*, const CUnit&)"
DECL = "void work(" + PARAMS + ")"


def identity(params=PARAMS, cv="", static=False):
    return (tuple(ghidra_cpp.parameter_key(p)
                  for p in ghidra_cpp.split_args(params)), cv, static)


class CallbackDeclarations(unittest.TestCase):
    def test_exact_two_callbacks_and_method_cv_static(self):
        self.assertEqual(headers.declared_signatures(DECL + ";", "work"), {identity()})
        self.assertEqual(headers.declared_signatures("static " + DECL + ";", "work"), {identity(static=True)})
        self.assertEqual(headers.declared_signatures(DECL + " volatile const;", "work"), {identity(cv="const volatile")})
        self.assertEqual(headers.declared_signatures("virtual " + DECL + " const = 0;", "work"), {identity(cv="const")})

    def test_exact_return_arguments_order_ptr_ref_and_const(self):
        for wrong in (PARAMS.replace("void (*)", "int (*)", 1),
                      PARAMS.replace("CUnit*, int", "CUnit*"),
                      PARAMS.replace("CUnit*, int", "int, CUnit*"),
                      PARAMS.replace("CUnit*, int", "CUnit*, float"),
                      PARAMS.replace("CUnit*", "CUnit&", 1),
                      PARAMS.replace("CUnit*", "const CUnit*", 1),
                      PARAMS.replace("const CUnit&", "CUnit&")):
            with self.subTest(wrong=wrong):
                self.assertNotIn(identity(), headers.declared_signatures("void work(" + wrong + ");", "work"))

    def test_distinct_same_name_overloads_not_suppressed(self):
        text = "void work(int); " + DECL + "; void work(" + CALLBACK + ");"
        self.assertEqual(headers.declared_signatures(text, "work"), {identity("int"), identity(), identity(CALLBACK)})

    def test_only_unnamed_free_function_pointers(self):
        for unsupported in ("void (*callback)(int)", "void (*)(void (*)(int))",
                            "void (CUnit::*)(int)", "void (*[2])(int)",
                            "void (**)(int)", "void (&)(int)", "void (* const)(int)",
                            "void (__cdecl *)(int)", "void (*)(int) __attribute__((cdecl))",
                            "void (*)(int named)", "void (*)(int, ...)",
                            "void (*)(int[2])", "void (*)(std::vector<int>)",
                            "void (*)(int,,float)", "void (*)(int,)", "void (*)(void, int)",
                            "void (*)(int&&)", "void (*)(int&*)", "void (*)(int) = 0"):
            with self.subTest(unsupported=unsupported):
                self.assertEqual(headers.declared_signatures("void work(" + unsupported + ");", "work"), set())
        self.assertNotIn(identity(CALLBACK), headers.declared_signatures("void work(CallbackAlias);", "work"))

    def test_malformed_declarations_fail_closed(self):
        for declaration in ("void work(" + CALLBACK + ",);", "void work(," + CALLBACK + ");",
                            "void work(" + CALLBACK + ", void);", DECL + " const const;",
                            DECL + " = other;", DECL + " = 0junk;", DECL + ") ;",
                            DECL[:-1] + ";", DECL + " noexcept;", DECL + " = 0",
                            "int field = " + DECL + ";"):
            with self.subTest(declaration=declaration):
                self.assertEqual(headers.declared_signatures(declaration, "work"), set())

    def test_comments_fields_nested_classes_namespaces_and_bodies(self):
        for text in ("// " + DECL + ";\n", "/* " + DECL + "; */",
                     'const char* text = "' + DECL + ';";',
                     "void (*work)(" + CALLBACK + ");",
                     "struct Inner { " + DECL + "; };",
                     "namespace Other { " + DECL + "; }",
                     "void other() { " + DECL + "; }", DECL + " { }"):
            with self.subTest(text=text):
                self.assertEqual(headers.declared_signatures(text, "work"), set())
        self.assertEqual(headers.declared_signatures("void other() {} " + DECL + ";", "work"), {identity()})

    def test_empty_callback_arguments_are_exact_not_conflated(self):
        self.assertEqual(headers.declared_signatures("void work(void (*)());", "work"), {identity("void (*)()")})
        self.assertEqual(headers.declared_signatures("void work(void (*)(void));", "work"), {identity("void (*)(void)")})

    def test_callee_context_uses_exact_callback_identity(self):
        case = test_llm_context.PacketContextTests()
        case.setUp()
        self.addCleanup(case.doCleanups)
        for params, cv, missing in ((PARAMS, "", False), (CALLBACK, "", True),
                                    (PARAMS.replace("bool (*)", "int (*)"), "", True),
                                    (PARAMS, "const", True)):
            with self.subTest(params=params, cv=cv):
                result = case.overload_case(DECL + ";", params, cv, method="work")
                self.assertEqual(bool(result.gaps), missing)

    def test_word_boundaries_never_collapse_distinct_callback_types(self):
        case = test_llm_context.PacketContextTests()
        case.setUp()
        self.addCleanup(case.doCleanups)
        check = test_llm_loop_headers.DeclarationReadiness().check
        for first, second in (("unsigned int", "unsignedint"),
                              ("const CUnit*", "constCUnit*"),
                              ("long long", "longlong"),
                              ("volatile CUnit&", "volatileCUnit&")):
            for declared, expected in ((first, second), (second, first)):
                for pattern in ("void (*)(%s)", "%s (*)(int)"):
                    params, wrong = pattern % declared, pattern % expected
                    declaration = "void work(" + params + ");"
                    with self.subTest(params=params, wrong=wrong):
                        self.assertNotEqual(identity(params), identity(wrong))
                        self.assertTrue(case.overload_case(declaration, wrong, method="work").gaps)
                        self.assertFalse(case.overload_case(declaration, params, method="work").gaps)
                        files = {"Unit.h": "class CUnit\n{\npublic:\n" + declaration + "\n};\n"}
                        self.assertIsNotNone(check(files, "CUnit", "work", wrong))
                        self.assertIsNone(check(files, "CUnit", "work", params))

    def test_class_and_reopened_namespace_readiness(self):
        check = test_llm_loop_headers.DeclarationReadiness().check
        self.assertIsNone(check({"Unit.h": "class CUnit\n{\npublic:\n" + DECL + ";\n};\n"},
                                "CUnit", "work", PARAMS))
        files = {"Globals.h": "namespace API { extern int count; }",
                 "Api.h": "namespace API { " + DECL + "; }"}
        self.assertIsNone(check(files, "API", "work", PARAMS))
        self.assertIsNotNone(check(files, "API", "work", CALLBACK))

    def test_complete_header_does_not_duplicate_but_keeps_overload(self):
        header = "class CUnit\n{\npublic:\n" + DECL + ";\n};\n"
        exact = {**test_llm_loop_headers.func("CUnit", "work"), "params": PARAMS, "cv": ""}
        added, text = test_llm_loop_headers.CompleteHandHeader().complete(header, [exact], {})
        self.assertEqual((added, text), ([], header))
        other = {**exact, "params": "int"}
        added, text = test_llm_loop_headers.CompleteHandHeader().complete(header, [exact, other], {"work": ("void work(int);", set())})
        self.assertEqual(added, ["void work(int);"])
        self.assertEqual(text.count(DECL + ";"), 1)

    def test_namespace_generation_skips_only_exact_identity(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "Api.h").write_text("namespace API { " + DECL + "; }")
            exact = dict(scope="API", method="work", qualified="API::work", params=PARAMS,
                         cv="", static=False, tu=1, kind="function")
            gen = headers.Gen.__new__(headers.Gen)
            gen.db = {"tus": [{"id": 1, "kind": "game"}]}
            gen.funcs = {"0x1": exact, "0x2": {**exact, "params": "int"}}
            gen.game_classes, gen.hand = set(), {}
            gen.resolve = lambda text, deps: text
            gen.ghidra_return = lambda function: "void"
            with patch.object(headers, "INCLUDE", root):
                output = gen.namespaces_header()
            self.assertNotIn("(*)", output)
            self.assertIn("void work(int);", output)

    def test_trial_generation_skips_exact_and_preserves_overload(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            include = root / "decomp/include"
            include.mkdir(parents=True)
            original = "class CUnit\n{\npublic:\n" + DECL + ";\n};\n"
            (include / "Unit.h").write_text(original)
            exact = dict(scope="CUnit", method="work", qualified="CUnit::work", params=PARAMS,
                         cv="", static=False, address="0x1")
            gen = headers.Gen.__new__(headers.Gen)
            gen.db = {"classes": {"CUnit": {"methods": ["0x1", "0x2"]}}}
            gen.funcs = {"0x1": exact, "0x2": {**exact, "address": "0x2", "params": "int"}}
            gen.prototypes = {a: {"static": False} for a in gen.funcs}
            gen.game_classes, gen.hand = {"CUnit"}, {"CUnit": "Unit.h"}
            gen.hand_templates, gen.hand_enums = set(), {}
            gen.method_decl = lambda function, cls, deps: "void work(" + function["params"] + ");"
            with patch.object(headers, "ROOT", root), patch.object(headers, "INCLUDE", include):
                self.assertEqual(gen.trial_include(), 1)
            output = (root / "build-decomp/include-trial/Unit.h").read_text()
            self.assertEqual(output.count(DECL + ";"), 1)
            self.assertIn("void work(int);", output)


if __name__ == "__main__":
    unittest.main()
