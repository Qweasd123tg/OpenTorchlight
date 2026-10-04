#!/usr/bin/env python3
"""C++98 regression for exact return ABI in generated differential tests."""
from pathlib import Path
import subprocess
import tempfile
import unittest

import autotest
import toolchain


class ReturnTypes(unittest.TestCase):
    def test_exact_types_and_reference_value(self):
        cases = [
            ("ref", [], False, False, "int&"),
            ("ref", [], False, True, "const int&"),
            ("overload", ["int"], False, False, "float"),
            ("overload", ["float"], False, False, "int*"),
            ("nothing", [], False, False, "void"),
            ("staticRef", [], True, False, "int&"),
        ]
        text = """
#include <cstdio>
struct Fixture {
    int x;
    int& ref() { return x; }
    const int& ref() const { return x; }
    float overload(int) { return 1.0f; }
    int* overload(float) { return &x; }
    void nothing() {}
    static int& staticRef() { static int x=17; return x; }
};
template<class A, class B> struct Same { enum { value=0 }; };
template<class A> struct Same<A,A> { enum { value=1 }; };
int& original(Fixture* f) { return f->x; }
"""
        for i, (method, params, static, const, wanted) in enumerate(cases):
            declarations, prelude = autotest.return_type_lookup("Fixture", method, params, static, const)
            text += f"namespace case{i} {{\n" + "\n".join(declarations + prelude)
            text += f"\ntypedef char exact[Same<Result,{wanted}>::value ? 1 : -1];\n}}\n"
        text += """
int main() {
    Fixture f = {17};
    typedef case0::Result (*Fn)(Fixture*);
    Fn call = &original;
    int& result=call(&f);
    if (&result!=&f.x || result!=17) return 1;
    result=23;
    return f.x==23 ? 0 : 2;
}
"""
        with tempfile.TemporaryDirectory(prefix="otl-return-test-") as folder:
            source = Path(folder)/"returns.cpp"
            obj = Path(folder)/"returns.o"
            binary = Path(folder)/"returns"
            source.write_text(text)
            # Compile with the original compiler, then link the C-only probe.
            toolchain.compile_source(source, obj, ["-std=gnu++98"])
            subprocess.run(["c++", "-no-pie", str(obj), "-o", str(binary)], check=True)
            subprocess.run([str(binary)], check=True)


if __name__ == "__main__":
    unittest.main()
