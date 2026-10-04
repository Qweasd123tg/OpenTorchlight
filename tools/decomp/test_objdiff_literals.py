#!/usr/bin/env python3
"""Literal relocation tokens must not be parsed as regex replacement templates."""
import unittest
from types import SimpleNamespace
import objdiff

class LiteralRelocationTest(unittest.TestCase):
    def token(self, relocation_type, relocation_offset, operands, literal):
        side = objdiff.ObjectSide.__new__(objdiff.ObjectSide)
        side.relocs = [SimpleNamespace(offset=relocation_offset, type=relocation_type,
                                      symbol=SimpleNamespace(name=".LC0"), addend=0)]
        side.reloc_offsets = [relocation_offset]
        side.target_name = lambda symbol, offset, mnemonic: literal
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

if __name__ == "__main__":
    unittest.main()
