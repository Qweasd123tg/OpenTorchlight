"""Finite pipeline tests: no original ELF, Ghidra, provider or game needed."""
import json
import io
from contextlib import nullcontext, redirect_stdout
from pathlib import Path
from types import SimpleNamespace
import tempfile
import unittest
from unittest.mock import Mock, patch

import llm_loop
import publication


def function(address, name="CProbe::work()", tu=1, size=12, kind="function", names=None):
    return {"address": address, "demangled": name, "tu": tu, "size": size,
            "kind": kind, "names": names or ["symbol_" + address], "scope": "CProbe"}


class Selection(unittest.TestCase):
    def db(self):
        funcs = [function("0x10"), function("0x2", "CProbe::early()"),
                 function("0x30", names=["alias"]), function("0x40", "CProbe::huge()", size=5000),
                 function("0x50", "COther::work()", tu=2),
                 function("0x60", "CProbe::~CProbe()", kind="dtor", names=["_ZN6CProbeD0Ev"])]
        return {"tus": [{"id": 1, "name": "Probe.cpp", "kind": "game"},
                        {"id": 2, "name": "Vendor.cpp", "kind": "library"}],
                "functions": {f["address"]: f for f in funcs}}

    def test_numeric_order_and_finite_defaults(self):
        _, funcs = llm_loop.select_functions(self.db(), "Probe.cpp", limit=1)
        self.assertEqual(["0x2"], [f["address"] for f in funcs])

    def test_repeatable_aliases_canonicalize_one_source_definition(self):
        _, funcs = llm_loop.select_functions(self.db(), "Probe.cpp", ["alias", "0X30", "0x10"])
        self.assertEqual(["0x10"], [f["address"] for f in funcs])

    def test_auto_excludes_existing_before_limit_so_next_batch_progresses(self):
        _, first = llm_loop.select_functions(self.db(), "Probe.cpp", limit=1)
        _, second = llm_loop.select_functions(self.db(), "Probe.cpp", limit=1,
                                             excluded={first[0]["address"]})
        self.assertEqual(["0x10"], [f["address"] for f in second])

    def test_explicit_thunk_alias_maps_to_main_and_closure_keeps_thunk(self):
        db = self.db()
        db["functions"]["0x99"] = function("0x99", "non-virtual thunk to CProbe::work()", names=["thunk-symbol"])
        _, funcs = llm_loop.select_functions(db, "Probe.cpp", ["thunk-symbol"])
        self.assertEqual(["0x10"], [f["address"] for f in funcs])
        self.assertIn("0x99", llm_loop.definitions.closure(funcs[0], db))
        _, auto = llm_loop.select_functions(db, "Probe.cpp")
        self.assertNotIn("0x99", {f["address"] for f in auto})

    def test_foreign_deleting_large_unknown_and_over_limit_fail_closed(self):
        for address in ["0x50", "0x60", "0x40", "absent"]:
            with self.subTest(address=address), self.assertRaises(ValueError):
                llm_loop.select_functions(self.db(), "Probe.cpp", [address])
        with self.assertRaises(ValueError):
            llm_loop.select_functions(self.db(), "Probe.cpp", ["0x2", "0x10"], limit=1)
        with self.assertRaises(ValueError):
                llm_loop.select_functions(self.db(), "Vendor.cpp")


class InputFingerprint(unittest.TestCase):
    def test_mutable_instruction_caches_are_not_checkpoint_inputs(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            database = root / "build-decomp/db"
            database.mkdir(parents=True)
            (database / "elfdb.json").write_text("symbols")
            (database / "insns.pickle").write_bytes(b"instruction cache")
            (database / "orig-normalized.pickle").write_bytes(b"normalization cache")
            elf = root / "original"
            elf.write_bytes(b"ELF")
            with patch.object(llm_loop.elfdb, "default_elf", return_value=elf):
                before = llm_loop.packet_inputs(root)
                (database / "insns.pickle").write_bytes(b"new instruction cache")
                (database / "orig-normalized.pickle").write_bytes(b"new normalization cache")
                self.assertEqual(before, llm_loop.packet_inputs(root))
                (database / "elfdb.json").write_text("changed symbols")
                self.assertNotEqual(before, llm_loop.packet_inputs(root))


class Pipeline(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / "decomp/src").mkdir(parents=True)
        (self.root / "decomp/include").mkdir()
        self.root_patch = patch.object(llm_loop, "ROOT", self.root)
        self.root_patch.start()
        self.addCleanup(self.root_patch.stop)
        self.inputs_patch = patch.object(llm_loop, "packet_inputs", return_value={"elf": "mock-elf"})
        self.inputs_patch.start()
        self.addCleanup(self.inputs_patch.stop)
        self.loop = loop = llm_loop.Loop.__new__(llm_loop.Loop)
        loop.tu = {"name": "Probe.cpp"}
        loop.funcs = [function("0x2")]
        loop.classes = ["CProbe"]
        loop.work = self.root / "build-decomp/llm-loop/Probe.cpp"
        loop.work.mkdir(parents=True)
        loop.source = self.root / "decomp/src/Probe.cpp"
        loop.models, loop.model_names = [], list(llm_loop.MODELS)
        loop.model_timeout, loop.model_retries = 17, 1
        loop.max_prompt_chars = 24000
        loop.allowed_headers = set()
        loop.db = {"functions": {"0x2": loop.funcs[0]}}
        loop.original = Mock()
        loop.rounds, loop.round_no, loop.switch_after, loop.jobs = 2, 0, 2, 16
        loop.settings = {"selected": loop.funcs, "models": loop.model_names}
        loop.prepare_only, loop.no_autotest, loop.attempt_resume = False, True, False
        loop.accepted, loop.status, loop.pending, loop.by_model = {}, {}, {}, {}
        loop.existing = ""
        loop.header = Mock(side_effect=lambda: setattr(loop, "headers", {"CProbe": "Probe.h"}))
        loop.prompt_for = Mock(return_value="known inputs")
        loop.unit = Mock(side_effect=lambda *args: "\n".join(loop.accepted.values()))
        loop.finish = Mock(return_value=True)
        loop.test = Mock(side_effect=AssertionError("game forbidden"))
        self.model = Mock(model=loop.model_names[0], sent=0, received=0, last_error="timeout")
        self.model.ask.return_value = ("", "session")
        self.model_patch = patch.object(llm_loop, "Model", return_value=self.model)
        self.model_class = self.model_patch.start()
        self.addCleanup(self.model_patch.stop)

    def result(self):
        return json.loads((self.loop.work / "result.json").read_text())

    def test_prepare_creates_prompts_checkpoint_without_model_compile_or_game(self):
        self.loop.prepare_only = True
        self.loop.compile = Mock(side_effect=AssertionError("compile forbidden"))
        self.loop.run()
        self.model_class.assert_not_called()
        self.loop.finish.assert_not_called()
        self.assertEqual("known inputs", (self.loop.work / "prompts/0x2.md").read_text())
        self.assertTrue((self.loop.work / "checkpoint.json").exists())
        self.assertTrue(self.result()["prepared"])

    def test_constructor_keeps_existing_attempt_work_and_is_model_lazy(self):
        sentinel = self.loop.work / "sentinel"
        sentinel.write_text("keep")
        with patch.object(llm_loop.elfdb, "load_db", return_value=Selection().db()), \
                patch.object(llm_loop.examples, "load", return_value=[]), \
                patch.object(llm_loop.objdiff, "Original"), \
                patch.object(llm_loop.ghidra_cpp, "known_methods", return_value={}), \
                patch.object(llm_loop.ghidra_cpp, "signatures_of", return_value={}), \
                patch.object(llm_loop.ghidra_cpp, "parse_enums", return_value={}), \
                patch("ghidra_draft.draft_state", return_value=("fresh", [])), \
                patch.dict("os.environ", {}, clear=False):
            loop = llm_loop.Loop("Probe.cpp", list(llm_loop.MODELS), 2, addresses=["alias"],
                                 prepare_only=True)
        self.assertEqual(["0x10"], [f["address"] for f in loop.funcs])
        self.assertEqual("keep", sentinel.read_text())
        self.model_class.assert_not_called()

    def test_constructor_compares_original_before_header_and_limits_missing(self):
        self.loop.source.write_text("original TU")
        with patch.object(llm_loop.elfdb, "load_db", return_value=Selection().db()), \
                patch.object(llm_loop.examples, "load", return_value=[]), \
                patch.object(llm_loop.objdiff, "Original"), \
                patch.object(llm_loop.objdiff, "compare_source", return_value={"functions": [
                    {"address": "0x2", "status": "MATCH"}]}), \
                patch.object(llm_loop.ghidra_cpp, "known_methods", return_value={}), \
                patch.object(llm_loop.ghidra_cpp, "signatures_of", return_value={}), \
                patch.object(llm_loop.ghidra_cpp, "parse_enums", return_value={}), \
                patch("ghidra_draft.draft_state", return_value=("fresh", [])), \
                patch.dict("os.environ", {}, clear=False):
            loop = llm_loop.Loop("Probe.cpp", list(llm_loop.MODELS), 2, limit=1)
        self.assertEqual(["0x10"], [f["address"] for f in loop.funcs])
        self.assertEqual("original TU", loop.existing)

    def test_prepare_refuses_missing_header_without_model(self):
        with self.assertRaisesRegex(RuntimeError, "no known or generated header"):
            llm_loop.Loop.header(self.loop)
        self.model_class.assert_not_called()

    def test_no_code_is_rejected_with_reason_and_checkpoint_session(self):
        self.loop.run()
        result = self.result()
        self.assertEqual({"0x2": "rejected"}, result["status"])
        self.assertEqual("timeout", result["rejected"]["0x2"]["error"])
        self.assertEqual([], result["published"])
        self.assertFalse(self.loop.source.exists())
        checkpoint = json.loads((self.loop.work / "checkpoint.json").read_text())
        self.assertEqual("session", checkpoint["pending"]["0x2"]["session"])
        self.assertEqual(2, checkpoint["pending"]["0x2"]["tries"])
        self.model_class.assert_called_once_with(llm_loop.MODELS[0], self.loop.work, timeout=17, retries=1)

    def test_diff_is_artifact_only_with_autotest_disabled(self):
        self.model.ask.return_value = ("int CProbe::work() { return 1; }", "session")
        self.loop.compile = Mock(return_value=("DIFF", "instructions differ"))
        self.loop.run()
        self.loop.test.assert_not_called()
        self.assertFalse(self.loop.source.exists())
        self.assertTrue((self.loop.work / "rejected/0x2.cpp").exists())
        self.assertEqual({}, self.result()["diagnostics"])

    def test_match_is_diagnostic_not_implicit_publication(self):
        self.model.ask.return_value = ("int CProbe::work() { return 1; }", "session")
        self.loop.compile = Mock(return_value=("MATCH", ""))
        self.loop.run()
        self.assertEqual({"0x2": "MATCH"}, self.result()["diagnostics"])
        self.assertEqual([], self.result()["published"])
        self.loop.finish.assert_called_once()
        checkpoint = json.loads((self.loop.work / "checkpoint.json").read_text())
        self.assertEqual("session", checkpoint["items"]["0x2"]["session"])
        self.assertEqual(1, checkpoint["items"]["0x2"]["tries"])

    def test_prepare_resume_keeps_work_and_checks_all_inputs(self):
        self.loop.prepare_only = True
        self.loop.run()
        sentinel = self.loop.work / "sentinel"
        sentinel.write_text("keep")
        self.loop.attempt_resume = True
        self.loop.run()
        self.assertEqual("keep", sentinel.read_text())
        self.loop.settings = {"models": ["paid"]}
        with self.assertRaisesRegex(RuntimeError, "checkpoint inputs/settings changed"):
            self.loop.restore()

    def test_checkpoint_rejects_changed_source_and_external_inputs(self):
        self.loop.prepare_only = True
        self.loop.run()
        with patch.object(llm_loop, "packet_inputs", return_value={"elf": "different"}):
            with self.assertRaises(RuntimeError):
                self.loop.restore()
        (self.root / "decomp/include/Probe.h").write_text("changed")
        with self.assertRaises(RuntimeError):
            self.loop.restore()

    def test_restored_extra_definition_is_rejected_before_compilation(self):
        self.loop.prepare_only = True
        self.loop.run()
        path = self.loop.work / "checkpoint.json"
        data = json.loads(path.read_text())
        data["accepted"]["0x2"] = "int CProbe::work() { return 1; }\nint evil() { return 0; }"
        data["status"]["0x2"] = "MATCH"
        llm_loop.atomic_json(path, data)
        with patch.object(llm_loop.objdiff, "compare_source") as compare:
            with self.assertRaisesRegex(RuntimeError, "invalid restored definition"):
                self.loop.restore()
        compare.assert_not_called()

    def test_restored_candidate_requires_fresh_match_not_status_string(self):
        self.model.ask.return_value = ("int CProbe::work() { return 1; }", "session")
        self.loop.compile = Mock(return_value=("MATCH", ""))
        self.loop.run()
        unit = {"functions": [{"address": "0x2", "status": "DIFF"}]}
        with patch.object(llm_loop.objdiff, "compare_source", return_value=unit):
            with self.assertRaisesRegex(RuntimeError, "not freshly MATCH"):
                self.loop.restore()

    def test_unaccepted_status_tamper_does_not_bypass_scheduling(self):
        self.loop.prepare_only = True
        self.loop.run()
        path = self.loop.work / "checkpoint.json"
        data = json.loads(path.read_text())
        data["status"]["0x2"] = "MATCH"
        llm_loop.atomic_json(path, data)
        self.loop.restore()
        self.assertNotIn("0x2", self.loop.status)
        self.assertIn("0x2", self.loop.pending)

    def test_invalid_checkpoint_item_identity_and_model_fail_closed(self):
        self.loop.prepare_only = True
        self.loop.run()
        path = self.loop.work / "checkpoint.json"
        original = json.loads(path.read_text())
        for field, value in [("model", 99), ("tries", -1), ("f", function("0xff"))]:
            data = json.loads(json.dumps(original))
            data["items"]["0x2"][field] = value
            llm_loop.atomic_json(path, data)
            with self.subTest(field=field), self.assertRaisesRegex(RuntimeError, "item identity"):
                self.loop.restore()

    def test_declared_methods_do_not_construct_header_generator(self):
        self.loop.funcs[0]["method"] = "work"
        (self.root / "decomp/include/Probe.h").write_text(
            "class CProbe\n{\npublic:\n    int work();\n};\n")
        with patch.object(llm_loop.headers, "Gen", side_effect=AssertionError("unnecessary generation")):
            self.assertEqual([], self.loop.complete_hand_header("CProbe", "Probe.h"))

    def test_missing_method_declaration_blocks_without_model_calls(self):
        self.loop.funcs[0]["method"] = "work"
        (self.root / "decomp/include/Probe.h").write_text("class CProbe\n{\npublic:\n    int old();\n};\n")
        self.loop.run()
        self.assertEqual({"0x2": "blocked"}, self.result()["status"])
        self.assertIn("signature is absent", self.result()["blocked"]["0x2"])
        self.model_class.assert_not_called()

    def test_blocked_item_is_not_logged_as_accepted(self):
        self.loop.funcs.append(function("0x3", "CProbe::other()"))
        self.loop.declaration_error = Mock(side_effect=lambda f: "missing declaration" if f["address"] == "0x2" else None)
        self.model.ask.return_value = ("int CProbe::other() { return 1; }", "session")
        self.loop.compile = Mock(return_value=("MATCH", ""))
        output = io.StringIO()
        with redirect_stdout(output):
            self.loop.run()
        self.assertIn("accepted 1 of 2 (1 MATCH); pending 0; blocked 1", output.getvalue())
        self.assertNotIn("accepted 2 of 2", output.getvalue())

    def context_packet(self):
        self.loop.prompt_for = llm_loop.Loop.prompt_for.__get__(self.loop)
        self.loop.examples, self.loop.stale_note = [], ""
        self.loop.original.image = SimpleNamespace(symbols=[], dynsyms=[], relocs={},
                                                   section_at=lambda address: None)
        self.loop.db["tus"] = [{"id": 1, "name": "Probe.cpp", "kind": "game"}]
        (self.root / "decomp/include/Probe.h").write_text(
            "class CProbe\n{\npublic:\n    int work();\n    int other();\n};\n")
        prompts = self.root / "tools/decomp/prompts"
        prompts.mkdir(parents=True)
        (prompts / "idioms.md").write_text("C++98; ASM is authoritative.\n")

    def test_context_index_and_exact_asm_are_prepared_once_not_each_round(self):
        self.context_packet()
        self.loop.prepare_only = True
        self.loop.funcs.append(function("0x3", "CProbe::other()"))
        with patch.object(llm_loop, "ContextIndex", wraps=llm_loop.ContextIndex) as index, \
                patch("llm_packet.asm_of", return_value="2: ret\n3: ret") as asm:
            self.loop.run()
            one = self.loop.prompt_for(self.loop.funcs[0])
            self.assertEqual(one, self.loop.prompt_for(self.loop.funcs[0]))
        self.assertEqual(1, index.call_count)
        self.assertIs(index.call_args.kwargs["image"], self.loop.original.image)
        self.assertEqual(2, asm.call_count)
        self.model_class.assert_not_called()

    def test_real_packet_preparation_missing_dependency_blocks_before_model(self):
        self.context_packet()
        self.loop.db["tus"].append({"id": 2, "name": "Dependency.cpp", "kind": "game"})
        callee = dict(function("0x20", "CUnknown::value()", tu=2), scope="CUnknown", method="value")
        self.loop.db["functions"]["0x20"] = callee
        with patch("llm_packet.asm_of", return_value="2: call 20\n7: ret"):
            self.loop.run()
        self.assertEqual({"0x2": "blocked"}, self.result()["status"])
        self.assertIn("No existing declaration of direct callee", self.result()["blocked"]["0x2"])
        self.model_class.assert_not_called()

    def test_real_packet_automatically_supplies_known_dependency_and_data(self):
        self.context_packet()
        self.loop.prepare_only = True
        self.loop.db["tus"].append({"id": 2, "name": "Dependency.cpp", "kind": "game"})
        callee = dict(function("0x20", "CCallee::value()", tu=2), scope="CCallee", method="value")
        self.loop.db["functions"]["0x20"] = callee
        self.loop.db["globals"] = [{"address": "0x6000", "name": "gBalance", "size": 4, "bind": "global"}]
        (self.root / "decomp/include/Callee.h").write_text("class CCallee { public: int value(); int balance; };\n")
        (self.root / "decomp/include/Variables.h").write_text("extern int gBalance;\nextern int unrelated;\n")
        with patch("llm_packet.asm_of", return_value="2: call 20\n7: mov 0x6000,%eax\nb: ret"):
            self.loop.run()
        prompt = (self.loop.work / "prompts/0x2.md").read_text()
        self.assertIn("class CCallee { public: int value(); int balance; };", prompt)
        self.assertIn("extern int gBalance;", prompt)
        self.assertNotIn("extern int unrelated;", prompt)
        self.assertEqual({}, self.result()["blocked"])
        self.model_class.assert_not_called()

    def test_over_budget_repair_blocks_instead_of_sending_partial_feedback(self):
        self.loop.max_prompt_chars = 64
        self.model.ask.return_value = ("int CProbe::work() { return 1; }", "session")
        self.loop.compile = Mock(return_value=("compile-error", "full diagnostic " * 100))
        self.loop.run()
        self.assertEqual({"0x2": "blocked"}, self.result()["status"])
        self.assertIn("no code/feedback was truncated", self.result()["blocked"]["0x2"])
        self.model.ask.assert_called_once()

    def test_unit_preserves_macros_conditional_includes_and_original_bytes(self):
        self.loop.existing = '#define FLAG 1\r\n#if FLAG\r\n#include "Probe.h"\r\n#endif\r\n// original\r\n'
        self.loop.headers = {"CProbe": "Probe.h"}
        (self.root / "decomp/include/Probe.h").write_text("class CProbe {};\n")
        text = llm_loop.Loop.unit(self.loop, ["int CProbe::work() { return 1; }"])
        self.assertTrue(text.startswith(self.loop.existing))
        self.assertEqual(1, text.count('#include "Probe.h"'))
        self.assertNotIn('EmptyStrings.h', text)
        self.assertNotIn('GenGlobals.h', text)

    def test_compile_gate_refuses_injected_directives_and_sibling_before_compiler(self):
        for code in ['#include "evil.h"\nint CProbe::work() { return 1; }',
                     'int CProbe::work() { return 1; }\nint evil() { return 0; }']:
            with patch.object(llm_loop.objdiff, "compare_source") as compare:
                status, detail = llm_loop.Loop.compile(self.loop, self.loop.funcs[0], code)
            self.assertEqual("compile-error", status)
            self.assertTrue(detail)
            compare.assert_not_called()

    def test_final_promotion_checks_every_emitted_variant(self):
        self.loop.source.write_text("accepted TU")
        self.loop.accepted = {"0x2": "int CProbe::work() { return 1; }"}
        self.loop.status = {"0x2": "MATCH"}
        self.loop.db["functions"]["0x3"] = function("0x3", "non-virtual thunk to CProbe::work()")
        before = {"functions": [{"address": "0x2", "status": "MATCH"}, {"address": "0x3", "status": "MATCH"}]}
        after = {"functions": [{"address": "0x2", "status": "MATCH"}, {"address": "0x3", "status": "DIFF"}]}
        self.loop.compare = Mock(side_effect=[before, after])
        with patch.object(llm_loop.promote, "promote", return_value=[]):
            self.assertFalse(llm_loop.Loop.finish(self.loop))

    def test_existing_compile_failure_never_starts_fresh(self):
        self.loop.source.write_text("user definition")
        self.loop.compare = Mock(side_effect=SystemExit("compile error"))
        with self.assertRaisesRegex(RuntimeError, "preserved unchanged"):
            self.loop.keep_existing()
        self.assertEqual("user definition", self.loop.source.read_text())

    def test_existing_source_is_preserved_without_resume_flag(self):
        self.loop.source.write_text("user definition")
        self.loop.compare = Mock(return_value={"functions": [{"address": "0x2", "status": "DIFF"}]})
        self.loop.run()
        self.model.ask.assert_not_called()
        self.assertEqual("user definition", self.loop.source.read_text())
        self.assertEqual(["0x2"], self.result()["existing"])

    def main_stage(self, options):
        stage = Mock(path=self.root, baseline=publication.tree_state(self.root))
        stage.activate.side_effect = lambda: nullcontext(stage)
        stage.publish.return_value = ["decomp/src/Probe.cpp"]
        with patch("sys.argv", ["llm_loop.py", "Probe.cpp"] + options), \
                patch.object(llm_loop.elfdb, "load_db", return_value=Selection().db()), \
                patch("parallel.owned_by_others", return_value=None), \
                patch.object(publication, "Stage", return_value=stage), \
                patch.object(llm_loop, "Loop", return_value=self.loop):
            llm_loop.main()
        return stage

    def test_cli_defaults_never_validate_or_publish(self):
        stage = self.main_stage([])
        stage.validate.assert_not_called()
        stage.publish.assert_not_called()

    def test_cli_publish_calls_existing_stage_safeguards_once(self):
        self.model.ask.return_value = ("int CProbe::work() { return 1; }", "session")
        self.loop.compile = Mock(return_value=("MATCH", ""))
        stage = self.main_stage(["--publish"])
        stage.validate.assert_called_once_with()
        stage.publish.assert_called_once_with()
        self.assertEqual(["decomp/src/Probe.cpp"], self.result()["published"])

    def test_cli_refuses_publish_with_no_code(self):
        with self.assertRaisesRegex(RuntimeError, "no accepted candidates"):
            self.main_stage(["--publish"])

    def test_cli_refuses_unintended_config_delta_before_validation(self):
        self.model.ask.return_value = ("int CProbe::work() { return 1; }", "session")
        self.loop.compile = Mock(return_value=("MATCH", ""))
        def polluted_finish():
            (self.root / "decomp/config.json").write_text("injected config")
            return True
        self.loop.finish.side_effect = polluted_finish
        with self.assertRaisesRegex(RuntimeError, "unexpected attempt delta: decomp/config.json"):
            self.main_stage(["--publish"])

    def test_unexpected_test_failure_still_removes_unsupported_source(self):
        self.loop.no_autotest = False
        self.model.ask.return_value = ("unsupported candidate", "session")
        self.loop.compile = Mock(return_value=("DIFF", "diff"))
        def failed_test(*args):
            self.loop.source.write_text("unsupported candidate")
            raise RuntimeError("test interrupted")
        self.loop.test.side_effect = failed_test
        with self.assertRaisesRegex(RuntimeError, "test interrupted"):
            self.loop.run()
        self.assertFalse(self.loop.source.exists())


if __name__ == "__main__":
    unittest.main()
