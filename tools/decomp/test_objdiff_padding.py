"""Only actual padding may disappear, including after objdump's prefix tokens."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
from unittest.mock import patch

import elfimage
import objdiff


class Padding(unittest.TestCase):
    def test_recognized_padding(self):
        for mnemonic, operands in [("nop", ""), ("nopl", "0x0(%rax)"),
                                    ("xchg", "%ax,%ax"), ("cs", "nopw 0x0(%rax,%rax,1)"),
                                    ("data16", "cs nopw 0x0(%rax,%rax,1)"),
                                    ("data16", "data16 cs nopw 0x0(%rax,%rax,1)")]:
            with self.subTest(mnemonic=mnemonic, operands=operands):
                self.assertTrue(objdiff.Normalizer.padding(mnemonic, operands))

    def test_prefix_does_not_erase_instruction(self):
        for mnemonic, operands in [("cs", "add $0x1,%eax"), ("data16", "add $0x1,%ax"),
                                    ("cs", "mov (%rax),%eax"), ("data16", ""),
                                    ("cs", "jmp 0x1000"), ("xchg", "%eax,%ebx")]:
            with self.subTest(mnemonic=mnemonic, operands=operands):
                self.assertFalse(objdiff.Normalizer.padding(mnemonic, operands))

    def test_nontrivial_trailing_exchange_is_retained(self):
        class TextSide(objdiff.Normalizer):
            def token(self, k, address, nxt, mnemonic, operands, *args):
                return mnemonic + " " + operands
        self.assertEqual(["xchg %eax,%ebx"],
                         TextSide().normalize([(0, "xchg", "%eax,%ebx")], 0, 1))

    def test_labels_ignore_only_real_padding(self):
        class TextSide(objdiff.Normalizer):
            def token(self, k, address, nxt, mnemonic, operands, start, end, offsets, insns):
                if mnemonic == "jmp":
                    return "jmp " + self.branch(k, int(operands, 16), start, end, offsets)
                return mnemonic + " " + operands
        side = TextSide()
        result = side.normalize([(0, "jmp", "0x2"), (1, "cs", "nopw 0x0(%rax)"),
                                 (2, "cs", "add $0x1,%eax"), (3, "ret", "")], 0, 4)
        self.assertEqual(["jmp L1", "cs add $0x1,%eax", "ret "], result)


@unittest.skipUnless(shutil.which("gcc") and shutil.which("g++") and shutil.which("objdump"),
                     "requires host assembler/compiler and objdump")
class NativeComparison(unittest.TestCase):
    def compare(self, first, second):
        with tempfile.TemporaryDirectory(prefix="otl-padding-") as folder:
            root = Path(folder)
            objects, binaries = [], []
            driver = root / "main.cpp"
            driver.write_text('extern "C" int probe(); int main() { return probe(); }\n')
            for index, body in enumerate((first, second)):
                source, obj, binary = root / (str(index) + ".s"), root / (str(index) + ".o"), root / str(index)
                source.write_text('.text\n.globl probe\n.type probe,@function\nprobe:\n' + body +
                                  '\n.size probe,.-probe\n.section .note.GNU-stack,"",@progbits\n')
                subprocess.run(["gcc", "-c", str(source), "-o", str(obj)], check=True, capture_output=True)
                subprocess.run(["g++", "-no-pie", str(obj), str(driver), "-o", str(binary)], check=True, capture_output=True)
                objects.append(obj); binaries.append(binary)
            image = elfimage.load(binaries[0], require_original=False)
            symbol = next(s for s in image.symbols if s.name == "probe")
            address = hex(symbol.value)
            function = {"address": address, "mangled": "probe", "names": ["probe"], "demangled": "probe()",
                        "size": symbol.size, "tu": 1, "scope": "", "method": "probe", "kind": "function", "bind": ["global"]}
            db = {"functions": {address: function}, "globals": [], "classes": {},
                  "tus": [{"id": 1, "name": "Probe.cpp", "kind": "game"}]}
            source = root / "Probe.cpp"; source.write_text("// preassembled synthetic fixture\n")
            with patch.object(elfimage, "ORIGINAL_SHA256", image.sha256):
                original = objdiff.Original(db=db, elf=binaries[0])
            with patch.object(objdiff, "NORM_CACHE", root / "cache.pickle"), \
                    patch.object(objdiff, "compile_for_diff", return_value=(objects[1], set())):
                result = objdiff.compare_source(source, original, quiet=True)
            row = next(r for r in result["functions"] if r.get("address") == address)
            return row["status"], [subprocess.run([str(p)], check=False).returncode for p in binaries]

    def test_prefixed_arithmetic_differs(self):
        for prefix in ("0x2e", "0x66"):
            with self.subTest(prefix=prefix):
                a = "movl $11,%eax\n.byte " + prefix + "\naddl $1,%eax\nret"
                b = a.replace("$1,%eax", "$2,%eax")
                self.assertEqual(("DIFF", [12, 13]), self.compare(a, b))

    def test_real_prefixed_nop_remains_padding(self):
        self.assertEqual(("MATCH", [11, 11]), self.compare("movl $11,%eax\nnop\nret",
                         "movl $11,%eax\n.byte 0x66,0x90\nret"))


if __name__ == "__main__":
    unittest.main()
