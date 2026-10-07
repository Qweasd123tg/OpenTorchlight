import unittest

import llm_definitions as definitions


F = {"address": "0x10", "tu": 1, "demangled": "C::f(int)", "qualified": "C::f",
     "params": "int", "cv": "", "kind": "function"}


class Definition(unittest.TestCase):
    def test_one_definition_with_comments_and_nested_body(self):
        self.assertIsNone(definitions.single_definition(F, "// {\nint C::f(int x) { if(x) { return x; } return 0; } // ;"))

    def test_extra_definition_before_or_after_and_directives_refused(self):
        good = "int C::f(int x) { return x; }"
        for code in (good + " int C::g() {return 0;}", "int C::g() {return 0;}\n" + good,
                     "int extra;\n" + good, "#include <x>\n" + good, good + "\n#define VALUE 0"):
            self.assertIsNotNone(definitions.single_definition(F, code), code)

    def test_wrong_signature_and_incomplete_body_refused(self):
        for code in ("int C::g(int x) {return x;}", "int C::f(int x) { return x;", "int C::f(int x);",
                     "int C::f(int x) const {return x;}", "int C::f(float x) {return 1;}"):
            self.assertIsNotNone(definitions.single_definition(F, code))

    def test_constructor_initializer(self):
        ctor = {**F, "demangled": "C::C(int)", "qualified": "C::C", "kind": "ctor"}
        self.assertIsNone(definitions.single_definition(ctor, "C::C(int x) : Base(x), field(x) { run(); }"))


class Variants(unittest.TestCase):
    def setUp(self):
        self.db = {"functions": {"0x10": F,
                                "0x20": {**F, "address": "0x20", "demangled": "non-virtual thunk to C::f(int)"},
                                "0x30": {**F, "address": "0x30", "cv": "const"},
                                "0x40": {**F, "address": "0x40", "tu": 2}}}

    def unit(self, status="MATCH", weak=False):
        return {"functions": [{"address": "0x10", "status": "MATCH", "weak": False},
                              {"address": "0x20", "status": status, "weak": weak}]}

    def test_same_source_closure_does_not_merge_overloads_or_tus(self):
        self.assertEqual({"0x10", "0x20"}, definitions.closure(F, self.db))

    def test_all_emitted_variants_match(self):
        self.assertEqual("MATCH", definitions.verdict(F, self.unit(), self.db)[0])

    def test_secondary_variant_diff_blocks_primary_match_even_weak(self):
        for weak in (False, True):
            status, detail = definitions.verdict(F, self.unit("DIFF", weak), self.db)
            self.assertEqual("DIFF", status)
            self.assertIn("0x20", detail)

    def test_no_strong_target_is_not_a_transfer(self):
        unit = self.unit()
        unit["functions"][0]["weak"] = True
        self.assertEqual("compile-error", definitions.verdict(F, unit, self.db)[0])


if __name__ == "__main__":
    unittest.main()
