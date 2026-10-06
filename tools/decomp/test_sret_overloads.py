"""Real convert() must not choose another overload by removing an ABI argument."""
from contextlib import contextmanager
import json
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch

import ghidra_cpp
import toolchain


def function(address, qualified, params="", cv=""):
    return {"address": address, "qualified": qualified, "params": params, "cv": cv,
            "kind": "function", "demangled": qualified + "(" + params + ")" + (" " + cv if cv else "")}


def prototype(f, sret=True, member=False):
    return {"name": f["demangled"], "sret": sret, "trusted": True, "variadic": False,
            "member": member, "static": False, "ret": "Result" if sret else "void",
            "params": [{"type": p, "size": 8} for p in ghidra_cpp.split_args(f["params"])]}


class HiddenOverloads(unittest.TestCase):
    @contextmanager
    def inputs(self, functions, protos):
        with tempfile.TemporaryDirectory(prefix="otl-sret-") as tmp:
            root = Path(tmp)
            (root / "build-decomp").mkdir()
            (root / "build-decomp/types.json").write_text(json.dumps({"prototypes": protos}))
            signatures = ghidra_cpp.signatures_of({"functions": {f["address"]: f for f in functions}})
            with patch.object(ghidra_cpp, "ROOT", root):
                yield signatures

    def execute(self, source):
        with tempfile.TemporaryDirectory(prefix="otl-sret-execution-") as tmp:
            cpp, obj, exe = Path(tmp) / "probe.cpp", Path(tmp) / "probe.o", Path(tmp) / "probe"
            cpp.write_text(source)
            toolchain.compile_source(cpp, obj, ["-std=gnu++98"], cache=False)
            subprocess.run(["g++", "-no-pie", str(obj), "-o", str(exe)], check=True, capture_output=True)
            return subprocess.check_output([str(exe)], text=True)

    def test_scalar_overload_retains_storage_argument_and_behavior(self):
        aggregate = function("0x1", "N::choose", "int")
        scalar = function("0x2", "N::choose", "Result*, int")
        raw = "int probe(int x)\n{\n Result local_result;\n N::choose(&local_result, x);\n return local_result.value;\n}\n"
        with self.inputs([aggregate, scalar], {"0x1": prototype(aggregate), "0x2": prototype(scalar, False)}) as signatures:
            converted = ghidra_cpp.convert(raw, set(), signatures=signatures)
        self.assertIn("N::choose(&local_result, x);", converted)
        declarations = ("#include <cstdio>\nstruct Result { int value; Result():value(0) {} ~Result() {} };\n"
                        "namespace N { Result choose(int) { Result r; r.value=22; return r; }\n"
                        "void choose(Result* r,int) { r->value=11; } }\n")
        main = 'int main() { std::printf("%d", probe(3)); }\n'
        self.assertEqual(self.execute(declarations + raw + main), "11")
        self.assertEqual(self.execute(declarations + converted + main), "11")
        # The formerly emitted C++ is valid but chooses the other function.
        bad = raw.replace("N::choose(&local_result, x)", "local_result = N::choose(x)")
        self.assertEqual(self.execute(declarations + bad + main), "22")

    def test_forwarding_does_not_choose_another_overload(self):
        aggregate = function("0x1", "N::choose", "int")
        scalar = function("0x2", "N::choose", "Result*, int")
        raw = ("Result *probe(Result *__return_storage_ptr__,int param_2)\n{\n"
               " N::choose(__return_storage_ptr__,param_2);\n return __return_storage_ptr__;\n}\n")
        with self.inputs([aggregate, scalar], {"0x1": prototype(aggregate), "0x2": prototype(scalar, False)}) as signatures:
            converted = ghidra_cpp.convert(raw, set(), signatures=signatures)
        self.assertIn("N::choose(__return_storage_ptr__,param_2);", converted)
        self.assertIn("Result *probe", converted)
        self.assertNotIn("return N::choose", converted)

    def test_missing_prototype_and_cv_overload_are_not_ignored(self):
        f = function("0x1", "C::choose", "int")
        for other in [function("0x2", "C::choose", "Result*, int"), function("0x2", "C::choose", "int", "const")]:
            with self.inputs([f, other], {"0x1": prototype(f, member=True)}) as signatures:
                raw = "void probe(C *p)\n{\n C::choose(&local_result,p,1);\n}\n"
                converted = ghidra_cpp.convert(raw, {("C", "choose")}, signatures=signatures)
                self.assertIn("C::choose(&local_result,p,1);", converted)
                self.assertNotIn("local_result.C::choose", converted)

    def test_ambiguous_calls_stay_opaque_to_reference_and_receiver_rewrites(self):
        f = function("0x1", "C::choose", "int&")
        other = function("0x2", "C::choose", "Result&, int&")
        with self.inputs([f, other], {"0x1": prototype(f, member=True)}) as signatures:
            raw = "void probe(C *p)\n{\n C::choose(&local_result,p,&x);\n}\n"
            converted = ghidra_cpp.convert(raw, {("C", "choose")}, signatures=signatures)
            self.assertIn("C::choose(&local_result,p,&x);", converted)

    def test_unique_target_still_reconstructs_and_executes(self):
        f = function("0x1", "N::choose", "int")
        raw = "int probe(int x)\n{\n Result local_result;\n N::choose(&local_result,x);\n return local_result.value;\n}\n"
        with self.inputs([f], {"0x1": prototype(f)}) as signatures:
            converted = ghidra_cpp.convert(raw, set(), signatures=signatures)
        self.assertIn("local_result = N::choose(x);", converted)
        declarations = ("#include <cstdio>\nstruct Result { int value; Result():value(0) {} ~Result() {} };\n"
                        "namespace N { Result choose(int) { Result r; r.value=22; return r; } }\n")
        self.assertEqual(self.execute(declarations + converted + 'int main() { std::printf("%d",probe(3)); }'), "22")

    def test_unknown_identity_or_bad_arity_keeps_the_call(self):
        f = function("0x1", "C::choose", "int")
        raw = "void probe(C *p)\n{\n C::choose(&local_result,p);\n}\n"
        with self.inputs([f], {"0x1": prototype(f, member=True)}) as signatures:
            self.assertIn("C::choose(&local_result,p);", ghidra_cpp.convert(raw, {("C", "choose")}, signatures=signatures))
            self.assertIn("C::choose(&local_result,p);", ghidra_cpp.convert(raw, {("C", "choose")}))


if __name__ == "__main__":
    unittest.main()
