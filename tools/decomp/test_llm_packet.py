#!/usr/bin/env python3
"""llm_packet: what the model is given for one function, and what it is not."""
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import llm_packet  # noqa: E402

RUN_CORE = """#ifndef RUNCORE_H
#define RUNCORE_H
#include "GenTypes.h"
class CRunCore
{
public:
    CRunCore();
    virtual ~CRunCore();
    virtual void update(float delta);
    virtual int getSlots() const;
    void applyDamage(int amount, bool critical);
    int m_iSlots;
private:
    TArrayList<int> m_damage;
};
#endif
"""
RUN_STATE = """#ifndef RUNSTATE_H
#define RUNSTATE_H
class CRunState
{
public:
    void enter();
private:
    int m_iPhase;
};
#endif
"""
IDIOMS = "# GCC 4.4 x86-64 code of Torchlight (C++98)\n\nThe ASM is the truth.\n"


def func(cls="CRunCore", method="applyDamage", address="0x401000", **extra):
    return {"address": address, "size": 64, "demangled": f"{cls}::{method}(int, bool)" if cls
            else method, "mangled": "_ZN9CRunCore11applyDamageEib", "scope": cls, "method": method,
            "kind": "function", **extra}


class Fixture:
    """A root with two headers, one scaffold ASM packet and no ELF."""

    def __init__(self, root):
        self.root = root
        inc = root / "decomp" / "include"
        inc.mkdir(parents=True)
        (inc / "RunCore.h").write_text(RUN_CORE)
        (inc / "RunState.h").write_text(RUN_STATE)
        self.asm_dir = root / "build-decomp" / "scaffold" / "RunCore.cpp" / "asm"
        self.asm_dir.mkdir(parents=True)
        self.asm_file = self.asm_dir / "0x401000_CRunCore_applyDamage_ib.s"
        self.asm_file.write_text("   401000:\tpush   %rbp\n   401004:\tmov    %rsp,%rbp\n"
                                 "   401009:\tret\n")

    def drop_asm(self):
        self.asm_file.unlink()


class Packet(unittest.TestCase):
    def build(self, root, f=None, headers=None, **kwargs):
        headers = {"CRunCore": "RunCore.h", "CRunState": "RunState.h"} if headers is None else headers
        options = {"draft": "int CRunCore::applyDamage(int amount, bool critical)\n{\n}\n",
                   "idioms": IDIOMS}
        options.update(kwargs)
        return llm_packet.build_prompt(f or func(), root=root, tu="RunCore.cpp", headers=headers,
                                       **options)

    # -- what goes in --------------------------------------------------------

    def test_only_the_owning_class_header_is_sent_whole(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            Fixture(root)
            prompt = self.build(root)
        for line in RUN_CORE.splitlines():
            self.assertIn(line, prompt)  # fields, virtuals and declarations are not cut
        self.assertIn("virtual int getSlots() const;", prompt)
        self.assertIn("    TArrayList<int> m_damage;\n};\n#endif", prompt)
        self.assertNotIn("CRunState", prompt.split("Write the C++98 definition")[0].replace(
            "Other headers of this TU, by name only, if you need them: RunState.h", ""))

    def test_other_headers_are_named_without_their_contents(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            Fixture(root)
            prompt = self.build(root)
        self.assertIn("RunState.h", prompt)
        self.assertNotIn("m_iPhase", prompt)

    def test_free_function_gets_every_mapped_header(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            Fixture(root)
            prompt = self.build(root, func(cls="", method="startGame", address="0x402000"),
                                headers={"CRunCore": "RunCore.h", "CRunState": "RunState.h"})
        self.assertIn("Headers of this TU, whole", prompt)
        self.assertIn("m_iPhase", prompt)
        self.assertIn("virtual int getSlots() const;", prompt)

    def test_nested_scope_selects_the_outermost_class(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            Fixture(root)
            f = func(scope="CRunCore::Inner")
            self.assertEqual(llm_packet.header_names(f, {"CRunCore": "RunCore.h", "CRunCore::Inner":
                                                         "Inner.h"}), ["RunCore.h"])
            prompt = self.build(root, f, headers={"CRunCore": "RunCore.h", "CRunCore::Inner": "Inner.h"})
        self.assertIn("virtual int getSlots() const;", prompt)
        self.assertNotIn("Inner.h", prompt.replace("Other headers of this TU, by name only, "
                                                    "if you need them: Inner.h", ""))

    def test_header_mapping_may_hold_several_names(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            Fixture(root)
            prompt = self.build(root, headers={"CRunCore": ["RunCore.h", "RunState.h"]})
        self.assertIn("m_iPhase", prompt)

    def test_missing_header_is_reported_not_silently_skipped(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            Fixture(root)
            prompt = self.build(root, headers={"CRunCore": "Missing.h"})
        self.assertIn("Missing.h", prompt)
        self.assertIn("not in decomp/include yet", prompt)

    # -- ASM and draft fallbacks -------------------------------------------

    def test_packet_asm_is_used_and_objdump_is_not_run(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            fixture = Fixture(root)
            with patch.object(llm_packet.scaffold, "disassemble",
                              side_effect=AssertionError("objdump must not run")) as dump:
                prompt = self.build(root)
        dump.assert_not_called()
        self.assertIn("\tpush   %rbp", prompt)
        self.assertIn("Original machine code (objdump of 0x401000)", prompt)

    def test_without_packet_asm_only_the_function_range_is_disassembled(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            fixture = Fixture(root)
            fixture.drop_asm()
            with patch.object(llm_packet.scaffold, "disassemble",
                              return_value="   401000:\tret\n") as dump:
                prompt = self.build(root)
        dump.assert_called_once()
        self.assertIn("\tret", prompt)

    def test_ambiguous_packet_falls_back_to_objdump(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            fixture = Fixture(root)
            (fixture.asm_dir / "0x401000_CRunCore_applyDamage_ib_copy.s").write_text("x")
            with patch.object(llm_packet.scaffold, "disassemble", return_value="   401000:\tnop\n") as dump:
                self.build(root)
        dump.assert_called_once()

    def test_absent_asm_and_draft_keep_the_packet_usable(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            fixture = Fixture(root)
            fixture.drop_asm()
            with patch.object(llm_packet.scaffold, "disassemble", side_effect=FileNotFoundError("no elf")), \
                    patch.object(llm_packet.elfdb, "default_elf",
                                 side_effect=AssertionError("default_elf must not be needed")):
                prompt = self.build(root, draft="")
        self.assertIn(llm_packet.NO_ASM, prompt)
        self.assertIn(llm_packet.NO_DRAFT, prompt)

    def test_stale_draft_note_is_carried(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            Fixture(root)
            prompt = self.build(root, stale_note="; STALE, made before these changes: field names")
        self.assertIn("types and temporaries may be wrong; STALE, made before these changes: field names",
                      prompt)

    # -- the task itself -----------------------------------------------------

    def test_exact_symbol_and_the_return_type_caveat(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            Fixture(root)
            prompt = self.build(root, func(vslots=[{"class": "CRunCore", "slot": 2}]))
        self.assertIn("Write the C++98 definition of `CRunCore::applyDamage(int, bool)`.", prompt)
        self.assertIn("`_ZN9CRunCore11applyDamageEib` at 0x401000", prompt)
        self.assertIn("Vtable slots of the original: CRunCore[2].", prompt)
        self.assertIn("encodes neither the return type nor `static`", prompt)

    def test_prefix_is_stable_for_every_function_of_a_class(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            fixture = Fixture(root)
            first = self.build(root)
            second = self.build(root, func(method="update", address="0x401100",
                                          demangled="CRunCore::update(float)"))
        cut = len(IDIOMS) + len(RUN_CORE) + 60
        self.assertEqual(first[:cut], second[:cut])
        self.assertIn(llm_packet.RULES.split(":")[0], first)
        for rule in ("C++98", "add no #include", "exactly one fenced", "never bind a symbol with an "
                       "__asm__ label", "never leave a stub"):
            self.assertIn(rule, first)

    # -- budget --------------------------------------------------------------

    def test_examples_are_dropped_first_and_the_mandatory_part_survives(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            fixture = Fixture(root)
            bare = self.build(root)
            full = self.build(root, examples="DRAFT AND SOURCE EXAMPLE " * 200)
            self.assertIn("for the style and the idioms", full)
            limited = self.build(root, examples="DRAFT AND SOURCE EXAMPLE " * 200,
                                 max_chars=len(bare) + 500)
        self.assertNotIn("for the style and the idioms", limited)
        self.assertIn(llm_packet.RULES, limited)
        self.assertIn("\tpush   %rbp", limited)  # the ASM is not the thing that gets cut

    def test_mandatory_part_over_the_budget_raises_with_sizes(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            Fixture(root)
            with self.assertRaises(ValueError) as error:
                self.build(root, max_chars=200, examples="irrelevant")
        message = str(error.exception)
        self.assertIn("CRunCore::applyDamage(int, bool)", message)
        for part in ("idioms", "headers", "ASM", "draft"):
            self.assertIn(part, message)

    # -- unsafe input --------------------------------------------------------

    def test_headers_must_stay_inside_decomp_include(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            Fixture(root)
            (root / "decomp" / "include" / "evil.h").write_text("secret")
            for name in ("../include/evil.h", "/etc/passwd", "sub/RunCore.h", "..", ".hidden.h"):
                with self.subTest(name=name), self.assertRaises(ValueError):
                    self.build(root, headers={"CRunCore": name})
            with self.assertRaises(ValueError):
                self.build(root, headers={"CRunCore": ""})

    def test_tu_name_must_be_a_plain_name(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            Fixture(root)
            with patch.object(llm_packet, "asm_of", return_value="nop"):
                for tu in ("../other/RunCore.cpp", "build/RunCore.cpp", "/tmp/RunCore.cpp"):
                    with self.subTest(tu=tu), self.assertRaises(ValueError):
                        llm_packet.build_prompt(func(), root=root, tu=tu,
                                                headers={"CRunCore": "RunCore.h"}, draft="", idioms=IDIOMS)

    def test_address_must_be_nonzero_hex(self):
        self.assertEqual(llm_packet.address_of({"address": "401000"}), "0x401000")
        self.assertEqual(llm_packet.address_of({"address": "0X401000"}), "0x401000")
        self.assertEqual(llm_packet.address_of({"address": 0x401000}), "0x401000")
        for bad in ("0x0", 0, "", "zzz", None):
            with self.subTest(address=bad), self.assertRaises(ValueError):
                llm_packet.address_of({"address": bad})

    # -- what it must not read ----------------------------------------------

    def test_only_headers_and_the_packet_asm_are_read(self):
        reads = []
        original_text, original_bytes = Path.read_text, Path.read_bytes

        def record_text(self, *args, **kwargs):
            reads.append(str(self))
            return original_text(self, *args, **kwargs)

        def record_bytes(self, *args, **kwargs):
            reads.append(str(self))
            return original_bytes(self, *args, **kwargs)

        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            Fixture(root)
            (root / "build-decomp" / "types.json").write_text("{ not json at all")
            (root / "build-decomp" / "insns.pickle").write_bytes(b"\x80\x04 not a pickle")
            with patch.object(Path, "read_text", record_text), patch.object(Path, "read_bytes", record_bytes), \
                    patch.object(elfdb, "load_db", side_effect=AssertionError("no database")), \
                    patch.object(llm_packet.scaffold, "disassemble",
                                 side_effect=AssertionError("no objdump")):
                self.build(root)
        self.assertTrue(reads)
        for name in reads:
            self.assertTrue(name.endswith("RunCore.h") or name.endswith(".s"), name)


if __name__ == "__main__":
    unittest.main()