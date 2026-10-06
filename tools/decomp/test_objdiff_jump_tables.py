#!/usr/bin/env python3
"""Real ELF/ET_REL switch comparisons, including the revision-review examples."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import threading
import unittest
from unittest.mock import patch

import elfimage
import objdiff
import objdiff_eh
import toolchain


TEMPLATE = '''.text
.globl probe
.type probe,@function
probe:
 .cfi_startproc
 GUARD
 COPY
 EXTRA
 jmp *.Ltable(,INDEX,8)
.Lzero:
 movl $11,%eax
 ret
.Lone:
 movl $22,%eax
 ret
.Ltwo:
 movl $33,%eax
 ret
.Ldefault:
 movl $-1,%eax
 ret
 .cfi_endproc
.size probe,.-probe
.section .rodata
.p2align 3
.Ltable:
 .quad .Lzero
 .quad TARGET
.data
.globl saved_flag
.type saved_flag,@object
.size saved_flag,1
saved_flag: .byte 0
.section .note.GNU-stack,"",@progbits
'''


def assembly(target='.Lone', guard='cmpl $1,%edi\n ja .Ldefault',
             copy='movl %edi,%edi', extra='', index='%rdi'):
    text = TEMPLATE
    for marker, replacement in (('GUARD', guard), ('COPY', copy), ('EXTRA', extra),
                                ('INDEX', index), ('TARGET', target)):
        text = text.replace(marker, replacement)
    return text


def original_for(binary):
    image = elfimage.load(binary, require_original=False)
    functions = {}
    for symbol in image.symbols:
        if symbol.type == elfimage.STT_FUNC and symbol.defined and symbol.size:
            address = hex(symbol.value)
            functions[address] = {'address': address, 'size': symbol.size, 'mangled': symbol.name,
                                  'names': [symbol.name], 'bind': ['global'], 'demangled': symbol.name,
                                  'tu': 0, 'kind': 'function'}
    globals_ = [{'name': s.name, 'address': hex(s.value), 'bind': 'global', 'file': 'Probe.cpp'}
                for s in image.symbols if s.type == elfimage.STT_OBJECT and s.defined]
    original = objdiff.Original.__new__(objdiff.Original)
    original.db = {'functions': functions, 'classes': {}, 'globals': globals_, 'tus': []}
    original.image = image
    original.side = objdiff.OriginalSide(image, original.db)
    original.frames = objdiff_eh.inspect(image)
    original._lock = threading.RLock()
    original.by_name = {f['mangled']: [f] for f in functions.values()}
    return original


@unittest.skipUnless(shutil.which('g++') and shutil.which('gcc'), 'requires native x86-64 compiler/linker')
class JumpTableTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(prefix='otl-jump-tables-')
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        cache = patch.object(objdiff, 'NORM_CACHE', self.root / 'normalized.pickle')
        cache.start()
        self.addCleanup(cache.stop)
        self.source = self.root / 'Probe.cpp'
        self.source.write_text('// assembly fixture supplied at the compiler boundary\n')
        self.driver = self.root / 'driver.cpp'
        self.driver.write_text('extern "C" int probe(unsigned,unsigned);\n'
                               'extern "C" int outside_A(unsigned,unsigned) { return 22; }\n'
                               'extern "C" int outside_B(unsigned,unsigned) { return 33; }\n'
                               'int main() { return probe(1,0); }\n')

    def assemble(self, text, stem):
        path, obj = self.root / (stem + '.s'), self.root / (stem + '.o')
        path.write_text(text)
        if (toolchain.cache_dir() / 'gcc447' / '.complete.json').exists():
            toolchain.assemble(path, obj)
        else:
            subprocess.run(['gcc', '-c', str(path), '-o', str(obj)], check=True, capture_output=True)
        return obj

    def link(self, obj, stem):
        binary = self.root / stem
        subprocess.run(['g++', '-no-pie', str(obj), str(self.driver), '-o', str(binary)],
                       check=True, capture_output=True)
        return binary

    def compare(self, obj, original):
        # Only compilation is supplied: parser, normalizers and MATCH decision are real.
        with patch.object(objdiff, 'compile_for_diff', return_value=(obj, set())):
            result = objdiff.compare_source(self.source, original, quiet=True)
        return next(row for row in result['functions'] if row['name'] == 'probe')

    def pair(self, left, right, execute=True):
        reference = self.assemble(left, 'left')
        candidate = self.assemble(right, 'right')
        reference_binary = self.link(reference, 'reference')
        candidate_binary = self.link(candidate, 'candidate')
        original = original_for(reference_binary)
        identical, changed = self.compare(reference, original), self.compare(candidate, original)
        if execute:
            self.assertEqual(subprocess.run([str(reference_binary)]).returncode, 22)
            self.assertEqual(subprocess.run([str(candidate_binary)]).returncode, 33)
        return identical, changed

    def test_external_function_entry_is_compared(self):
        identical, changed = self.pair(assembly('outside_A'), assembly('outside_B'))
        self.assertEqual(identical['status'], 'MATCH')
        self.assertEqual(changed['status'], 'DIFF')

    def test_external_different_section_is_compared(self):
        helpers = ('.section .text.helpers,"ax",@progbits\n'
                   '.globl helper_A\n.type helper_A,@function\nhelper_A: movl $22,%eax\n ret\n.size helper_A,.-helper_A\n'
                   '.globl helper_B\n.type helper_B,@function\nhelper_B: movl $33,%eax\n ret\n.size helper_B,.-helper_B\n')
        identical, changed = self.pair(assembly('helper_A') + helpers, assembly('helper_B') + helpers)
        self.assertEqual(identical['status'], 'MATCH')
        self.assertEqual(changed['status'], 'DIFF')

    def test_unrelated_cmp_does_not_shrink_table(self):
        extra = 'cmpl $0,%esi\n sete %al\n movb %al,saved_flag(%rip)'
        identical, changed = self.pair(assembly(extra=extra), assembly('.Ltwo', extra=extra))
        self.assertEqual(identical['status'], 'MATCH')
        self.assertEqual(changed['status'], 'DIFF')

    def test_internal_targets_and_copied_index(self):
        for copy, index in (('movl %edi,%edi', '%rdi'), ('movl %edi,%eax', '%rax')):
            identical, changed = self.pair(assembly(copy=copy, index=index),
                                           assembly('.Ltwo', copy=copy, index=index))
            self.assertEqual(identical['status'], 'MATCH')
            self.assertEqual(changed['status'], 'DIFF')

    def test_taken_in_range_guard_is_supported(self):
        guard = 'cmpl $1,%edi\n jbe .Linside\n jmp .Ldefault\n.Linside:'
        identical, changed = self.pair(assembly(guard=guard), assembly('.Ltwo', guard=guard))
        self.assertEqual(identical['status'], 'MATCH')
        self.assertEqual(changed['status'], 'DIFF')

    def assert_unverified(self, text, fragment):
        identical, _ = self.pair(text, text, execute=False)
        self.assertEqual(identical['status'], 'DIFF')
        self.assertTrue(any(fragment in reason for reason in identical.get('metadata_reasons', [])), identical)

    def test_unknown_range_or_index_fails_closed(self):
        for options in ({'guard': 'cmpl $0,%esi\n ja .Ldefault'},
                        {'extra': 'movl $0,%edi'}, {'copy': ''}):
            with self.subTest(options=options):
                self.assert_unverified(assembly(**options), 'index range unverified')

    def test_external_guard_continuation_cannot_prove_a_prefix(self):
        guard = 'cmpl $0,%edi\n ja trampoline'
        helper = ('.text\n.globl trampoline\n.type trampoline,@function\n'
                  'trampoline: jmp .Ldispatch\n.size trampoline,.-trampoline\n')
        left = assembly(guard=guard, extra='.Ldispatch:') + helper
        right = assembly('.Ltwo', guard=guard, extra='.Ldispatch:') + helper
        identical, changed = self.pair(left, right)
        self.assertEqual(identical['status'], 'DIFF')
        self.assertEqual(changed['status'], 'DIFF')
        self.assertIn('jump table index range unverified', identical['metadata_reasons'])

    def test_guard_default_tail_jump_continuation_is_unverified(self):
        text = assembly(guard='cmpl $0,%edi\n ja .Lescape', extra='.Ldispatch:')
        text = text.replace(' .cfi_endproc', '.Lescape: jmp trampoline\n .cfi_endproc')
        text += ('.text\n.globl trampoline\n.type trampoline,@function\n'
                 'trampoline: jmp .Ldispatch\n.size trampoline,.-trampoline\n')
        self.assert_unverified(text, 'index range unverified')

    def test_segment_prefixed_instruction_is_not_alignment_padding(self):
        left = assembly(extra='.byte 0x2e\n movl $1,%edi')
        right = assembly(extra='.byte 0x2e\n movl $0,%edi')
        reference = self.assemble(left, 'left')
        candidate = self.assemble(right, 'right')
        original = original_for(self.link(reference, 'reference'))
        row = self.compare(candidate, original)
        self.assertEqual(row['status'], 'DIFF')
        self.assertIn('jump table index range unverified', row['metadata_reasons'])
        norm = objdiff.object_functions(candidate)['probe']['norm']
        self.assertTrue(any(n.startswith('cs mov') for n in norm), norm)
        self.assertTrue(objdiff.Normalizer.padding('data16 cs', 'nopw 0x0(%rax,%rax,1)'))

    def test_guard_cannot_be_bypassed(self):
        text = assembly(extra='.Ldispatch:').replace(' cmpl $1,%edi',
                                                    ' testl %esi,%esi\n jne .Ldispatch\n cmpl $1,%edi')
        self.assert_unverified(text, 'index range unverified')

    def test_missing_truncated_and_non_instruction_targets_fail_closed(self):
        for text in (assembly('0'), assembly('.Lone+1'),
                     assembly(guard='cmpl $2,%edi\n ja .Ldefault')):
            with self.subTest(text=text):
                self.assert_unverified(text, 'target unverified')

    def test_unknown_external_does_not_hide_later_differences(self):
        left = assembly('outside_A').replace('.quad outside_A', '.quad outside_A\n .quad .Lone')
        right = assembly('outside_A').replace('.quad outside_A', '.quad outside_A\n .quad .Ltwo')
        left = left.replace('cmpl $1,%edi', 'cmpl $2,%edi')
        right = right.replace('cmpl $1,%edi', 'cmpl $2,%edi')
        reference, candidate = self.assemble(left, 'left'), self.assemble(right, 'right')
        original = original_for(self.link(reference, 'reference'))
        # Deliberately unavailable external identity, as in the review's minimal DB.
        original.side.func_start = {a: n for a, n in original.side.func_start.items() if n == 'probe'}
        original.by_name = {'probe': original.by_name['probe']}
        row = self.compare(candidate, original)
        self.assertEqual(row['status'], 'DIFF')
        self.assertIn('jump table entry 1 target unverified', row['metadata_reasons'])
        norms = objdiff.object_functions(candidate)['probe']['norm']
        token = next(n for n in norms if '[table:' in n)
        self.assertEqual(len(token.split('[table:', 1)[1].split(']', 1)[0].split(',')), 3)


@unittest.skipUnless((toolchain.cache_dir() / 'gcc447' / '.complete.json').exists() and shutil.which('g++'),
                     'requires pinned GCC 4.4.7')
class PinnedSwitchTest(unittest.TestCase):
    setUp = JumpTableTest.setUp
    link = JumpTableTest.link

    def test_actual_pinned_cpp_compile_and_complete_switch(self):
        text = ('extern "C" int sink(int); extern "C" int probe(unsigned x,unsigned) { '
                'switch(x) { case 0: return sink(11); case 1: return sink(22); '
                'case 2: return sink(33); case 3: return sink(44); case 4: return sink(55); '
                'case 5: return sink(66); default: return -1; } }')
        self.source.write_text(text)
        directory = self.root / 'compile'
        directory.mkdir()
        obj, _ = objdiff.compile_for_diff(self.source, directory, quiet=True)
        self.driver.write_text('extern "C" int probe(unsigned,unsigned); extern "C" int sink(int x) { return x; } '
                               'int main() { return probe(1,0); }')
        original = original_for(self.link(obj, 'reference'))
        norm = objdiff.object_functions(obj)['probe']['norm']
        self.assertTrue(any('[table:' in row for row in norm), norm)
        row = next(row for row in objdiff.compare_source(self.source, original, quiet=True)['functions']
                   if row['name'] == 'probe')
        self.assertEqual(row['status'], 'MATCH', row)
        # Alter one slot through source; this invokes the actual pinned compiler again.
        self.source.write_text(text.replace('sink(22)', 'sink(23)'))
        changed = next(row for row in objdiff.compare_source(self.source, original, quiet=True)['functions']
                       if row['name'] == 'probe')
        self.assertEqual(changed['status'], 'DIFF')


if __name__ == '__main__':
    unittest.main()
