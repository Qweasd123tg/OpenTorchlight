#!/usr/bin/env python3
"""ghidra_cpp.py rewrites: literals survive exactly, NaN guards go only where provably redundant."""
import unittest

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
        return ghidra_cpp.tidy_expressions(text)

    def test_redundant_guards_go(self):
        self.assertEqual(self.tidy("if (!NAN(a) && a == b) {"), "if (a == b) {")
        self.assertEqual(self.tidy("if ((!NAN(a) && !NAN(b)) && a < b) {"), "if (a < b) {")
        self.assertEqual(self.tidy("if (a <= b && !NAN(a)) {"), "if (a <= b) {")
        self.assertEqual(self.tidy("x = !NAN(f) && f >= 0.5;"), "x = f >= 0.5;")

    def test_guards_that_change_meaning_stay(self):
        for text in ["if (!NAN(x) && enabled) {", "if (!NAN(a) && !(a < b)) {", "if (!NAN(a) && a != b) {",
                     "if (!NAN(c) && a < b) {", "if (NAN(a) || a < b) {"]:
            self.assertEqual(self.tidy(text), text)


if __name__ == "__main__":
    unittest.main()
