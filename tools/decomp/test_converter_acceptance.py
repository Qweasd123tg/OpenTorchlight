"""Archived converter defects exercised through conversion and C++98 behavior."""
import shutil
import json
import subprocess
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import ghidra_cpp
import headers


def function(scope, method, params="", cv="", kind="function"):
    qualified = f"{scope}::{method}" if scope else method
    return {"scope": scope, "method": method, "qualified": qualified, "params": params,
            "cv": cv, "kind": kind, "tu": 1, "address": qualified + params + cv,
            "demangled": f"{qualified}({params})" + (" " + cv if cv else "")}


class ConverterRegressionTest(unittest.TestCase):
    def execute(self, source):
        compiler = shutil.which("g++")
        if not compiler:
            self.skipTest("g++ unavailable for synthetic C++98 behavior probe")
        with tempfile.TemporaryDirectory(prefix="otl-converter-") as tmp:
            cpp, exe = Path(tmp) / "probe.cpp", Path(tmp) / "probe"
            cpp.write_text(source)
            result = subprocess.run([compiler, "-std=c++98", "-O2", str(cpp), "-o", str(exe)],
                                    text=True, capture_output=True)
            self.assertEqual(result.returncode, 0, result.stderr + "\n" + source)
            return subprocess.check_output([str(exe)], text=True)

    def test_direct_base_call_does_not_dispatch_to_derived(self):
        raw = "int __thiscall CWrapper::probe(CWrapper *this,CBase *param_1)\n{\n return CBase::step(param_1);\n}\n"
        converted = ghidra_cpp.convert(raw, {("CBase", "step")}, function("CWrapper", "probe", "CBase*"))
        self.assertIn("param_1->CBase::step()", converted)
        source = ("#include <cstdio>\nstruct CBase { virtual int step() { return 11; } };\n"
                  "struct CDerived : CBase { int step() { return 22; } };\n"
                  "struct CWrapper { int probe(CBase*); };\n" + converted +
                  "int main() { CDerived d; CWrapper w; std::printf(\"%d\", w.probe(&d)); }\n")
        self.assertEqual(self.execute(source), "11")

    def test_direct_namespace_and_this_calls_keep_qualification(self):
        methods = {("one::CBase", "step")}
        self.assertEqual(ghidra_cpp.call_rewrite("one::CBase::step(this, 2)", methods),
                         "one::CBase::step(2)")
        self.assertEqual(ghidra_cpp.call_rewrite("one::CBase::step(&value, 2)", methods),
                         "value.one::CBase::step(2)")
        self.assertEqual(ghidra_cpp.call_rewrite("two::CBase::step((one::CBase *)value, 2)", methods),
                         "two::CBase::step((one::CBase *)value, 2)")
        self.assertEqual(ghidra_cpp.call_rewrite("one::CBase::step((one::CBase *)value, 2)", methods),
                         "((one::CBase *)value)->one::CBase::step(2)")

    def test_numeric_bool_comparison_retains_normalized_value(self):
        source = ghidra_cpp.convert("int normalize(int x)\n{\n return x != false;\n}\n", set())
        self.assertIn("x != false", source)
        self.assertEqual(self.execute("#include <cstdio>\n" + source +
                                     "int main() { std::printf(\"%d %d %d\", normalize(-3), normalize(0), normalize(2)); }"),
                         "1 0 1")

    def test_full_conversion_preserves_lexical_contents(self):
        literal = r'"byte ulong undefined4 CBase::step(this) /* } */ \\"'
        # The quotation, type names, calls and comment delimiters inside a
        # literal must survive every pass, including indentation.
        source = "const char *message(void)\n{\n // byte CBase::step(this) {\n return " + literal + ";\n}\n"
        converted = ghidra_cpp.convert(source, {("CBase", "step")})
        self.assertIn(literal, converted)
        self.assertIn("// byte CBase::step(this) {", converted)
        self.assertEqual(self.execute("#include <cstdio>\n" + converted +
                                     "int main() { std::printf(\"%s\", message()); }"),
                         'byte ulong undefined4 CBase::step(this) /* } */ \\')

    def test_escaped_characters_and_wide_literals_are_unchanged(self):
        source = "int f(void)\n{\n /* byte undefined4 } */\n const wchar_t *p = L\"byte\";\n return '\\0' == 'b';\n}\n"
        converted = ghidra_cpp.convert(source, set())
        for token in ["/* byte undefined4 } */", 'L"byte"', "'\\0'", "'b'"]:
            self.assertIn(token, converted)

    def test_cv_definition_and_declaration_compile_together(self):
        f = function("CProbe", "get", cv="const volatile")
        generator = headers.Gen.__new__(headers.Gen)
        generator.resolve = lambda ctype, deps: ctype
        generator.ghidra_return = lambda f: "int"
        generator.prototypes = {f["address"]: {"static": False}}
        decl = generator.method_decl(f, "CProbe", {})
        converted = ghidra_cpp.convert("int __thiscall CProbe::get(CProbe *this)\n{\n return this->x;\n}\n", set(), f)
        self.assertIn("get() const volatile", decl)
        self.assertIn("get() const volatile", converted)
        self.assertEqual(self.execute("#include <cstdio>\nstruct CProbe { int x; " + decl + " };\n" + converted +
                                     "int main() { CProbe p; p.x = 7; std::printf(\"%d\", p.get()); }"), "7")

    def test_unsafe_lifetime_and_receiver_cleanups_are_opt_in(self):
        source = ("void CProbe::run(CProbe *this)\n{\n Object local_obj;\n local_unused = 3;\n"
                  " if (local_s != &_S_empty_rep_storage) {\n destroy(local_s);\n }\n"
                  " helper(this, 2);\n this->_vptr = saved;\n ~CBase();\n"
                  " if (!NAN(value) && value < limit) { consume(value); }\n}\n")
        converted = ghidra_cpp.convert(source, set())
        for token in ["Object local_obj;", "local_unused = 3;", "destroy(local_s)", "helper(this, 2)",
                      "_vptr = saved", "~CBase()", "!NAN(value)"]:
            self.assertIn(token, converted)

    def test_short_name_and_arity_do_not_choose_unrelated_overload(self):
        fs = [function("one", "use", "Value&"), function("two", "use", "Value*"),
              function("one", "pick", "EKind"), function("one", "pick", "int")]
        signatures = ghidra_cpp.signatures_of({"functions": {f["address"]: f for f in fs}})
        self.assertNotIn("use", signatures)
        self.assertEqual(ghidra_cpp.reference_arguments("one::use(&x); two::use(&x); use(&x);", signatures),
                         "one::use(x); two::use(&x); use(&x);")
        self.assertEqual(ghidra_cpp.enum_arguments("one::pick(1)", signatures, {"EKind": {1: "Chosen"}}),
                         "one::pick(1)")

    def test_sret_effects_and_overwrites_do_not_turn_into_early_return(self):
        raw = ("wstring * __thiscall CProbe::get(wstring *__return_storage_ptr__,CProbe *this)\n{\n"
               " std::wstring::wstring((wstring *)__return_storage_ptr__,L\"value\",local_alloc);\n"
               " EFFECT\n return __return_storage_ptr__;\n}\n")
        f = function("CProbe", "get")
        for effect in ["cleanup();", "std::wstring::wstring((wstring *)__return_storage_ptr__,L\"second\",local_alloc);"]:
            converted = ghidra_cpp.convert(raw.replace("EFFECT", effect), set(), f)
            self.assertIn("cleanup();" if effect.startswith("cleanup") else 'L"second"', converted)
            self.assertIn("__return_storage_ptr__", converted)
            self.assertNotIn('return L"value";', converted)


class HeaderIdentityTest(unittest.TestCase):
    def generator(self, functions):
        generator = headers.Gen.__new__(headers.Gen)
        generator.funcs = {f["address"]: f for f in functions}
        generator.db = {"classes": {"CProbe": {"methods": list(generator.funcs)}},
                        "functions": generator.funcs, "tus": [{"id": 1, "kind": "game"}]}
        generator.game_classes = {"CProbe"}
        generator.hand = {"CProbe": "CProbe.h"}
        generator.hand_templates = set()
        generator.hand_enums = {}
        generator.prototypes = {f["address"]: {"static": False} for f in functions}
        generator.resolve = lambda ctype, deps: ctype
        generator.ghidra_return = lambda f: "int"
        return generator

    def test_trial_adds_missing_overload_and_cv_only_once(self):
        functions = [function("CProbe", "read", "int"), function("CProbe", "read", "long"),
                     function("CProbe", "read", "int", "const")]
        generator = self.generator(functions)
        with tempfile.TemporaryDirectory(prefix="otl-header-") as tmp:
            root, include = Path(tmp), Path(tmp) / "include"
            include.mkdir()
            (include / "CProbe.h").write_text("struct CProbe\n{\n int read(int value);\n};\n")
            with patch.object(headers, "ROOT", root), patch.object(headers, "INCLUDE", include):
                self.assertEqual(generator.trial_include(), 2)
            result = (root / "build-decomp/include-trial/CProbe.h").read_text()
            self.assertIn("int read(long);", result)
            self.assertIn("int read(int) const;", result)
            self.assertEqual(result.count("read(int value)"), 1)

    def test_unrelated_class_does_not_suppress_namespace_function(self):
        functions = [function("TOOLS", "parse", "int"), function("TOOLS", "parse", "long"),
                     function("outer::TOOLS", "parse", "int")]
        generator = self.generator(functions)
        with tempfile.TemporaryDirectory(prefix="otl-namespaces-") as tmp:
            include = Path(tmp)
            (include / "Noise.h").write_text("struct Noise { int parse(int); };\nnamespace TOOLS { int parse(int); }\n")
            with patch.object(headers, "INCLUDE", include):
                result = generator.namespaces_header()
        self.assertEqual(result.count("int parse(int);"), 1)
        self.assertIn("int parse(long);", result)
        self.assertIn("namespace outer {", result)

    def test_cv_virtual_identities_are_distinct(self):
        generator = self.generator([])
        normal = function("CProbe", "read", "int")
        qualified = function("CProbe", "read", "int", "const")
        self.assertNotEqual(generator.virtual_signature(normal), generator.virtual_signature(qualified))

    def test_dwarf_static_identity_overrides_symbol_binding_guess(self):
        f = function("CProbe", "read", "int")
        generator = self.generator([f])
        generator.prototypes = {f["address"]: {"static": True}}
        self.assertEqual(generator.method_decl(f, "CProbe", {}), "static int read(int);")

    def test_unknown_static_member_identity_is_not_guessed(self):
        f = function("CProbe", "read", "int", kind="static")
        generator = self.generator([f])
        generator.prototypes = {}
        self.assertIsNone(generator.method_decl(f, "CProbe", {}))

    def test_receiver_rewrite_uses_exact_prototype_member_fact(self):
        functions = [function("CProbe", "staticCall", "CProbe*"), function("CProbe", "memberCall"),
                     function("CProbe", "unknownCall")]
        db = {"classes": {"CProbe": {}}, "functions": {f["address"]: f for f in functions}}
        with tempfile.TemporaryDirectory(prefix="otl-prototypes-") as tmp:
            root = Path(tmp)
            (root / "build-decomp").mkdir()
            (root / "build-decomp/types.json").write_text(json.dumps({"prototypes": {
                functions[0]["address"]: {"static": True}, functions[1]["address"]: {"static": False}}}))
            with patch.object(ghidra_cpp, "ROOT", root), patch("types_export.is_class", return_value=True):
                methods = ghidra_cpp.known_methods(db)
        self.assertEqual(methods, {("CProbe", "memberCall")})
        text = "CProbe::staticCall((CProbe *)p); CProbe::memberCall(p); CProbe::unknownCall(p);"
        self.assertEqual(ghidra_cpp.call_rewrite(text, methods),
                         "CProbe::staticCall((CProbe *)p); p->CProbe::memberCall(); CProbe::unknownCall(p);")

    def test_name_only_vtable_overloads_fail_closed(self):
        first, second = function("CProbe", "read", "int"), function("CProbe", "read", "long")
        first["names"], second["names"] = ["_ZN6CProbe4readEi"], ["_ZN6CProbe4readEl"]
        functions = {f["address"]: f for f in [first, second]}
        db = {"functions": functions, "vtables": {"CProbe": {"groups": [{"slots": list(functions)}]}}}
        dump = "Vtable for CProbe\nCProbe::_ZTV6CProbe: 4u entries\n0 0\n8 (int (*)(...)) _ZTI6CProbe\n16 CProbe::read\n24 CProbe::read\n"
        self.assertIn("relocation identities", headers.vtable_mismatch(db, "CProbe", dump))


if __name__ == "__main__":
    unittest.main()
