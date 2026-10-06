#!/usr/bin/env python3
"""Complete literal identity, bounded section reads and numeric-load semantics."""
import unittest
from types import SimpleNamespace
import objdiff

class LiteralRelocationTest(unittest.TestCase):
    def token(self, relocation_type, relocation_offset, operands, literal):
        side = objdiff.ObjectSide.__new__(objdiff.ObjectSide)
        side.relocs = [SimpleNamespace(offset=relocation_offset, type=relocation_type,
                                      symbol=SimpleNamespace(name=".LC0"), addend=0)]
        side.reloc_offsets = [relocation_offset]
        side.target_name = lambda symbol, offset, mnemonic, address_operand=False: literal
        return side.token(0, 0, 7, "mov", operands, 0, 7, [0], [])

    def test_immediate_backslashes(self):
        for literal in [r'lit:"media\particles\scripts"', r'lit:"media\resources.dat"',
                        r'lit:"translations\translation.dat"', r'lit:"\1\g<name>"']:
            self.assertEqual(self.token(next(iter(objdiff.ABSOLUTE)),3,"$0x0,%edi",literal),
                             f"mov $[{literal}],%edi")

    def test_rip_relative_backslashes(self):
        literal = r'lit:"media\particles\images"'
        self.assertEqual(self.token(next(iter(objdiff.PC_RELATIVE)),3,"0x0(%rip),%rax",literal),
                         f"mov [{literal}](%rip),%rax")

    def test_absolute_memory_backslashes(self):
        literal = r'lit:"media\resources.dat"'
        self.assertEqual(self.token(next(iter(objdiff.ABSOLUTE)),2,"0x0(%rax),%rcx",literal),
                         f"mov [{literal}](%rax),%rcx")

class FullLiteralTest(unittest.TestCase):
    def test_full_identity_after_old_limits(self):
        for length in (79, 80, 81, 255, 256, 300):
            a = objdiff.literal_token(b"A" * length + b"X\0", 1)
            b = objdiff.literal_token(b"A" * length + b"Y\0", 1)
            self.assertNotEqual(a, b)
            self.assertNotEqual(objdiff.code_digest([a]), objdiff.code_digest([b]))
            self.assertIn(f"n{length + 1}:", a)

    def test_width_and_empty_literals(self):
        self.assertNotEqual(objdiff.literal_token(b"A\0", 1),
                            objdiff.literal_token(b"A\0\0\0\0\0\0\0", 4))
        self.assertNotEqual(objdiff.literal_token(b"\0", 1), objdiff.literal_token(b"\0" * 4, 4))
        self.assertEqual(objdiff.literal_token(b"\0garbage", 1), "lit:w1:n0:")
        self.assertEqual(objdiff.literal_token(b"\0" * 4 + b"garbage", 4), "lit:w4:n0:")

    def test_unterminated_or_ambiguous_data_is_not_a_prefix_token(self):
        for raw, width in [(b"A" * 300, 1), (b"A\0\0\0", 4), (b"", 1),
                           (b"A\0\0\0\0\0\0\0", None), (b"\0" * 4, None)]:
            with self.assertRaises(objdiff.UnverifiedData):
                objdiff.literal_token(raw, width)

    def test_representation_and_length_are_unambiguous(self):
        self.assertNotEqual(objdiff.literal_token(b'A"\\n\0', 1), objdiff.literal_token(b'A"\n\0', 1))
        self.assertNotEqual(objdiff.literal_token(b"a\0", 1), objdiff.literal_token(b"aa\0", 1))
        self.assertEqual(objdiff.literal_token(b"\xc3\xa9\0", 1), "lit:w1:n2:c3a9")

    def side(self, data, name=".rodata.str1.1", declared_size=None):
        section = SimpleNamespace(index=1, name=name, size=len(data) if declared_size is None else declared_size)
        obj = SimpleNamespace(symbols=[], sections=[None, section], section_bytes=lambda _: data)
        side = objdiff.ObjectSide(obj)
        symbol = SimpleNamespace(name=".LC0", defined=True, shndx=1, value=0, type=0)
        return side, symbol

    def test_object_reads_stay_within_section(self):
        side, symbol = self.side(b"tail\0")
        self.assertEqual(side.target_name(symbol, 0, "mov", True), "lit:w1:n4:7461696c")
        self.assertEqual(side.target_name(symbol, 4, "mov", True), "lit:w1:n0:")
        for offset in (-1, 5, 6):
            side.target_name(symbol, offset, "mov", True)
            self.assertTrue(side.unverified)
        side, symbol = self.side(b"short\0", declared_size=20)
        side.target_name(symbol, 0, "mov", True)
        self.assertTrue(side.unverified)

    def test_nearby_numeric_constants_are_not_literals(self):
        side, symbol = self.side(b"A\0\0\0" + b"long string\0", ".rodata")
        self.assertEqual(side.target_name(symbol, 0, "mov"), "const:41000000")
        self.assertEqual(side.target_name(symbol, 0, "movsd"), "const:410000006c6f6e67")
        side, symbol = self.side(b"\0\0\0", ".rodata")
        side.target_name(symbol, 0, "mov")
        self.assertIn("truncated", side.unverified[0])

    def test_numeric_access_width_is_preserved(self):
        for mnemonic, operands, width in [("mov", "0x0(%rip),%rax", 8),
                                           ("mov", "0x0(%rip),%ax", 2),
                                           ("mov", "0x0(%rip),%al", 1),
                                           ("movzbl", "0x0(%rip),%eax", 1),
                                           ("movzwl", "0x0(%rip),%eax", 2),
                                           ("movsd", "0x0(%rip),%xmm0", 8),
                                           ("movss", "0x0(%rip),%xmm0", 4),
                                           ("cmpb", "$0x1,0x0(%rip)", 1)]:
            self.assertEqual(objdiff.const_size(objdiff.memory_mnemonic(mnemonic, operands)), width)

    def test_named_symbol_resolution_retains_name_and_addend(self):
        side, _ = self.side(b"ignored\0")
        symbol = SimpleNamespace(name="global_object", defined=True, shndx=1, value=0, type=1)
        side.resolve = lambda name: 0x1000 if name == symbol.name else None
        side.name_at = lambda address, mnemonic, address_operand=False: f"global_object+{address - 0x1000:#x}"
        self.assertEqual(side.target_name(symbol, 8, "mov"), "global_object+0x8")

    def test_original_section_tail_is_read_without_crossing_boundary(self):
        section = SimpleNamespace(name=".rodata", addr=0x1000, size=5)
        requests = []
        def read(address, size):
            requests.append((address, size))
            if address < section.addr or address + size > section.addr + section.size:
                raise ValueError("out of section")
            return b"tail\0"[address - section.addr:address - section.addr + size]
        side = objdiff.OriginalSide.__new__(objdiff.OriginalSide)
        side.func_start = {}; side.image = SimpleNamespace(plt={}, section_at=lambda _: section, read=read)
        side.obj_starts = []; side.objects = []; side.exact = {}
        self.assertEqual(side.name_at(0x1000, "mov", True), "lit:w1:n4:7461696c")
        self.assertEqual(requests, [(0x1000, 5)])


if __name__ == "__main__":
    unittest.main()
