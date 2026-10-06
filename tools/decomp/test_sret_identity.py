"""Do not apply a hidden-return ABI to a different overload with the same name."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
from unittest.mock import patch

import ghidra_cpp


class HiddenReturnIdentity(unittest.TestCase):
    draft = "void probe(void)\n{\n  C::f(&local_x,7);\n}\n"

    def transform(self, prototypes):
        with tempfile.TemporaryDirectory(prefix="otl-sret-identity-") as folder:
            root = Path(folder)
            (root / "build-decomp").mkdir()
            (root / "build-decomp/types.json").write_text(json.dumps({"prototypes": prototypes}))
            with patch.object(ghidra_cpp, "ROOT", root), patch.object(ghidra_cpp, "_SRET", None), \
                    patch.object(ghidra_cpp, "_SRET_INPUT", None):
                return ghidra_cpp.convert(self.draft, set())

    def test_single_record_preserves_existing_sret_conversion(self):
        result = self.transform({"0x1": {"name": "C::f(int)", "sret": True}})
        self.assertIn("local_x = C::f(7)", result)

    def test_mixed_overloads_keep_original_call(self):
        result = self.transform({"0x1": {"name": "C::f(int)", "sret": True},
                                 "0x2": {"name": "C::f(X*, int)", "sret": False}})
        self.assertIn("C::f(&local_x,7)", result)

    def test_multiple_sret_overloads_are_also_ambiguous(self):
        result = self.transform({"0x1": {"name": "C::f(int)", "sret": True},
                                 "0x2": {"name": "C::f(long)", "sret": True}})
        self.assertIn("C::f(&local_x,7)", result)

    def test_absent_prototypes_do_not_invent_hidden_return(self):
        self.assertIn("C::f(&local_x,7)", self.transform({}))

    @unittest.skipUnless(shutil.which("g++"), "requires host C++ compiler")
    def test_conversion_preserves_executed_overload(self):
        converted = self.transform({"0x1": {"name": "C::f(int)", "sret": True},
                                    "0x2": {"name": "C::f(X*, int)", "sret": False}})
        prefix = '''#include <cstdio>
struct X { int value; };
X local_x;
struct C {
    static void f(X* p, int) { p->value = 11; }
    static X f(int) { X x; x.value = 22; return x; }
};
'''
        suffix = 'int main() { probe(); std::printf("%d", local_x.value); }\n'
        with tempfile.TemporaryDirectory(prefix="otl-sret-behavior-") as folder:
            for name, body in (("original", self.draft), ("converted", converted)):
                source, binary = Path(folder) / (name + ".cpp"), Path(folder) / name
                source.write_text(prefix + body + suffix)
                subprocess.run(["g++", "-std=c++98", "-O2", str(source), "-o", str(binary)],
                               check=True, capture_output=True)
                self.assertEqual("11", subprocess.check_output([str(binary)], text=True))


if __name__ == "__main__":
    unittest.main()
