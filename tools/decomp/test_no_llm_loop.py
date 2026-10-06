import json
from pathlib import Path
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

import candidate
import elfimage
import llm_loop
import no_llm_loop
import objdiff
import publication
import toolchain


class Providers(unittest.TestCase):
    def test_cached_failures_do_not_starve_the_remaining_queue(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            tus = [{"id": i, "name": n + "Descriptor.cpp", "kind": "game"} for i, n in enumerate("ABCDE")]
            with patch.object(no_llm_loop.elfdb, "ROOT", root), \
                    patch.object(no_llm_loop.elfdb, "load_db", return_value={"tus": tus}), \
                    patch.object(no_llm_loop.evidence, "input_digest", return_value="inputs"), \
                    patch.object(no_llm_loop.publication, "Stage", return_value=SimpleNamespace(path=root)), \
                    patch.object(no_llm_loop, "provide", side_effect=RuntimeError("unsupported ABI")) as provider:
                first = no_llm_loop.run([], "descriptor", limit=3)
                second = no_llm_loop.run([], "descriptor", limit=3)
                third = no_llm_loop.run([], "descriptor", limit=3)
            self.assertEqual(3, first["attempted"])
            self.assertEqual(2, second["attempted"])
            self.assertEqual(3, second["cached_failures"])
            self.assertEqual(0, third["attempted"])
            self.assertEqual(5, third["cached_failures"])
            self.assertEqual([t["name"] for t in tus], [c.args[1]["name"] for c in provider.call_args_list])

    def test_generated_property_belongs_to_tu_as_a_strong_definition(self):
        with tempfile.TemporaryDirectory(prefix="otl-property-provider-") as folder:
            root = Path(folder)
            (root / "decomp/src").mkdir(parents=True)
            (root / "decomp/include").mkdir()
            source = root / "decomp/src/ProbeDescriptor.cpp"
            source.write_text('#include "ProbeDescriptor.h"\n')
            header = root / "decomp/include/ProbeDescriptor.h"
            header.write_text('''class CProbeDescriptor {
public:
    static int Get_value(int object)
    { return object + 7; }
};
''')
            f = {"address": "0x1", "tu": 1, "scope": "CProbeDescriptor", "method": "Get_value",
                 "params": "int", "demangled": "CProbeDescriptor::Get_value(int)", "cv": ""}
            with patch.object(llm_loop.Model, "ask", side_effect=AssertionError("model call forbidden")):
                self.assertEqual(1, no_llm_loop.outline_properties(SimpleNamespace(path=root),
                                  {"id": 1, "name": source.name}, "CProbeDescriptor", {"functions": {"0x1": f}}))
            self.assertIn("static int Get_value(int object);", header.read_text())
            self.assertIn("int CProbeDescriptor::Get_value(int object)", source.read_text())
            output = toolchain.compile_source(source, root / "probe.o", ["-I", str(header.parent)], cache=False)
            rows = objdiff.object_functions(output)
            self.assertEqual(elfimage.STB_GLOBAL, rows["_ZN16CProbeDescriptor9Get_valueEi"]["bind"])

    def test_repeated_unsupported_job_is_not_regenerated_or_sent_to_a_model(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            tu = {"id": 1, "name": "ProbeDescriptor.cpp", "kind": "game"}
            with patch.object(no_llm_loop.elfdb, "ROOT", root), \
                    patch.object(no_llm_loop.elfdb, "load_db", return_value={"tus": [tu]}), \
                    patch.object(no_llm_loop.evidence, "input_digest", return_value="inputs"), \
                    patch.object(no_llm_loop.publication, "Stage", return_value=SimpleNamespace(path=root)), \
                    patch.object(no_llm_loop, "provide", side_effect=RuntimeError("unsupported ABI")) as provider, \
                    patch.object(llm_loop.Model, "__init__", side_effect=AssertionError("no models")):
                a = no_llm_loop.run([], "descriptor")
                b = no_llm_loop.run([], "descriptor")
                self.assertEqual("BLOCKED", a["results"][0]["status"])
                self.assertTrue(b["results"][0]["cached_failure"])
                self.assertEqual(1, provider.call_count)

    def test_existing_diff_body_cannot_be_relabelled_as_preserved(self):
        with tempfile.TemporaryDirectory() as folder:
            a, b = Path(folder) / "a.cpp", Path(folder) / "b.cpp"
            a.write_text("int C::f() { return 1; }\n")
            b.write_text("int C::f() { return 2; }\n")
            row = {"address": "0x1", "status": "DIFF", "code": "same", "object_digest": "full-object",
                   "metadata_reasons": ["unknown EH"]}
            f = {"demangled": "C::f()", "params": "", "cv": ""}
            self.assertFalse(candidate.preserve_existing(a, b, {"0x1": row}, [row], {"functions": {"0x1": f}}))
            b.write_text(a.read_text() + "int C::g() { return 3; }\n")
            self.assertTrue(candidate.preserve_existing(a, b, {"0x1": row}, [row], {"functions": {"0x1": f}}))


if __name__ == "__main__":
    unittest.main()
