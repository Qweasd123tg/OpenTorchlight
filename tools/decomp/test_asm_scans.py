"""Cheap ASM filters must not change symbol or constructor rewriting."""
import unittest

import hybrid
import objdiff


class AssemblyScans(unittest.TestCase):
    def test_redirects_only_declared_data_and_keeps_instructions(self):
        text = (".type value, @object\nvalue:\n\t.quad 0\n"
                ".type function, @function\nfunction:\n\tmovq value, %rax\n")
        expected = text.replace("value:\n", ".Ltlhybrid_dead_0:\n") + "\t.set\tvalue, 0x4000\n"
        self.assertEqual((expected, ["value"]), hybrid.rewrite_assembly(text, {"value": 0x4000, "function": 8}, True))

    def test_gnu_unique_data_reuses_original_storage_identity(self):
        # GCC emits this for UTF-16 basic_string's empty representation. A second
        # blob-owned copy makes the original reserve() free non-heap storage.
        text = ('.weak empty_rep\n.section .bss.empty_rep,"awG",@nobits,empty_rep,comdat\n'
                '.type empty_rep, @gnu_unique_object\n.size empty_rep, 32\n'
                'empty_rep:\n.zero 32\n.text\nmovq $empty_rep+24, %rax\n')
        expected = text.replace('empty_rep:\n', '.Ltlhybrid_dead_0:\n') + '\t.set\tempty_rep, 0x1426440\n'
        self.assertEqual((expected, ['empty_rep']), hybrid.rewrite_assembly(
            text, {'empty_rep': 0x1426440}, False))

    def test_object_type_prefix_is_not_a_data_declaration(self):
        text = '.type lookalike, @gnu_unique_object_suffix\nlookalike:\n.zero 8\n'
        self.assertEqual((text, []), hybrid.rewrite_assembly(text, {'lookalike': 16}, False))

    def test_common_data_and_prefix_lookalikes(self):
        text = "\t.comm value,8\n\u2003.lcomm local,16\n.commlook value,8\n.typelook ghost, @object\nghost:\n"
        expected = ".commlook value,8\n.typelook ghost, @object\nghost:\n\t.set\tlocal, 0x8000\n\t.set\tvalue, 0x4000\n"
        self.assertEqual((expected, ["local", "value"]), hybrid.rewrite_assembly(
            text, {"value": 0x4000, "local": 0x8000, "ghost": 16}, True))

    def test_constructor_section_stack_and_previous_are_preserved(self):
        text = (".section .ctors,\"aw\",@progbits\n\t.quad ctor\n\t.quadlook keep\n"
                ".pushsection .text\n\t.quad keep\n.popsection\n\t.quad ctor2\n"
                ".previous\n\t.quad keep2\n")
        expected = text.replace("\t.quad ctor\n", "").replace("\t.quad ctor2\n", "")
        self.assertEqual((expected, []), hybrid.rewrite_assembly(text, {}, True))
        self.assertEqual((text, []), hybrid.rewrite_assembly(text, {}, False))

    def test_labels_must_still_match_the_full_original_pattern(self):
        text = ".type value, @object\n value:\nvalue: # comment\nvalue:\t\n"
        expected = text.replace("value:\t\n", ".Ltlhybrid_dead_0:\n") + "\t.set\tvalue, 0x4000\n"
        self.assertEqual((expected, ["value"]), hybrid.rewrite_assembly(text, {"value": 0x4000}, False))

    def test_globalization_retains_declared_weak_local_and_unicode_names(self):
        text = (".globl known\n.weak weak\nknown:\nweak:\n\u2003.local local\n.locality ignored\n"
                "local:\t\n_with_é:\n.label:\n indented:\ncomment: # retain\n\tmovq %rdi,%rax\n")
        expected = text.replace("\u2003.local local\n", "\t.globl\tlocal\n")
        expected = expected.replace("local:\t\n", "\t.globl\tlocal\nlocal:\t\n")
        expected = expected.replace("_with_é:\n", "\t.globl\t_with_é\n_with_é:\n")
        self.assertEqual((expected, {"local", "_with_é"}), objdiff.globalize_locals(text))

    def test_empty_and_unterminated_inputs_keep_output_termination(self):
        self.assertEqual(("\n", set()), objdiff.globalize_locals(""))
        self.assertEqual(("\n", []), hybrid.rewrite_assembly("", {}, False))
        self.assertEqual(("\t.globl\tname\nname:\n", {"name"}), objdiff.globalize_locals("name:"))


if __name__ == "__main__":
    unittest.main()
