"""Static-only pinned-GCC LSDA tests. No executable, original or fixture, is run."""
from dataclasses import replace
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
from unittest.mock import patch

import elfimage
import objdiff
import objdiff_eh as eh
import toolchain
from test_objdiff_eh import linked_original


@unittest.skipUnless((toolchain.cache_dir() / 'gcc447/.complete.json').exists(), 'pinned GCC required')
class CleanupStaticTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.tmp = tempfile.TemporaryDirectory(prefix='otl-cleanup-static-')
        cls.root = Path(cls.tmp.name)
        cls.source = cls.root / 'probe.cpp'
        cls.source.write_text('extern "C" void raise_value();\nextern "C" void cleanup();\n'
                              'struct Guard { ~Guard() { cleanup(); } };\n'
                              'extern "C" int probe() { Guard guard; raise_value(); return 7; }\n'
                              'extern "C" int plain(int x) { return x * 3; }\n')
        cls.path, cls.globalized = objdiff.compile_for_diff(cls.source, cls.root, quiet=True)
        support = cls.root / 'support.cpp'
        support.write_text('extern "C" const char fixture_rodata[] = "fixture";\n'
                           'extern "C" void raise_value() {}\nextern "C" void cleanup() {}\n'
                           'extern "C" void _Unwind_Resume(void*) {}\n'
                           'extern "C" int __gxx_personality_v0() { return 0; }\n')
        support_obj = toolchain.compile_source(support, cls.root / 'support.o', quiet=True)
        cls.linked = cls.root / 'reference'
        # This image is only an ELF metadata fixture, never executed.
        subprocess.run([str(toolchain.cache_dir() / 'gcc447/usr/bin/ld'), '-e', 'plain',
                        str(cls.path), str(support_obj), '-o', str(cls.linked)], check=True, capture_output=True,
                       env=toolchain.driver_env(toolchain.cache_dir() / 'gcc447'))
        cls.original = linked_original(cls.linked)

    @classmethod
    def tearDownClass(cls):
        cls.tmp.cleanup()

    def parts(self):
        image = elfimage.load_object(self.path)
        frames = eh.inspect(image, True)
        symbol = next(s for s in image.symbols if s.name == 'probe')
        section = image.sections[symbol.shndx]
        text = objdiff.run_objdump(['--section=' + section.name, str(self.path)])
        insns = [i for i in objdiff.parse_insns(text) if symbol.value <= i[0] < symbol.value + symbol.size]
        location = frames._lsda_index[(symbol.shndx, symbol.value, symbol.value + symbol.size)]
        return image, frames, symbol, insns, location

    def signature(self, parts):
        image, frames, symbol, insns, _ = parts
        return eh.cleanup_signature(image, frames, symbol.value, symbol.size, insns, symbol.shndx)

    def change(self, delta, value):
        parts = self.parts()
        image, frames, symbol, insns, loc = parts
        where = image.sections[loc[3]].offset + loc[4] + delta
        data = bytearray(image.data); data[where] = value; image.data = bytes(data)
        return parts

    def site_positions(self):
        image, _, _, _, loc = self.parts()
        section = image.sections[loc[3]]
        data = image.data[section.offset:section.offset + section.size]
        reader = eh.Reader(data, loc[4])
        self.assertEqual(reader.take(3), b'\xff\xff\x01')
        length_position = reader.pos - loc[4]
        length = reader.leb(); end = reader.pos + length
        positions = []
        while reader.pos < end:
            row = []
            for _ in range(4):
                position = reader.pos - loc[4]
                value = reader.leb(); row.append((position, value))
            positions.append(row)
        return length_position, positions

    def test_positive_linked_and_object(self):
        parts = self.parts(); expected = self.signature(parts)
        self.assertIsNotNone(expected)
        f = self.original.function('probe')
        self.assertEqual(expected, self.original.cleanup_eh(f))
        rows = {r['name']: r for r in objdiff.compare_source(self.source, self.original, quiet=True)['functions']}
        self.assertEqual(rows['probe']['status'], 'MATCH')
        self.assertEqual(rows['probe']['eh_verified'], 'gcc447-cleanup-v1')
        self.assertEqual(rows['plain']['status'], 'MATCH')

    def test_old_inspection_gate_is_not_disabled(self):
        image, frames, symbol, insns, _ = self.parts()
        self.assertIsNotNone(self.signature(self.parts()))
        self.assertEqual(frames.reason(symbol.value, symbol.size, symbol.shndx), 'EH LSDA equivalence unverified')

    def test_changed_landing_pad(self):
        _, positions = self.site_positions()
        pos, pad = next(row[2] for row in positions if row[2][1])
        changed = self.signature(self.change(pos, 0))
        self.assertIsNotNone(changed)
        self.assertNotEqual(changed, self.signature(self.parts()))

    def test_mutated_table_is_rejected_by_full_comparator(self):
        _, positions = self.site_positions()
        position, _ = next(row[2] for row in positions if row[2][1])
        parts = self.change(position, 0)
        changed = self.root / 'changed-lsda.o'
        changed.write_bytes(parts[0].data)
        with patch.object(objdiff, 'compile_for_diff', return_value=(changed, self.globalized)):
            rows = {r['name']: r for r in objdiff.compare_source(self.source, self.original, quiet=True)['functions']}
        self.assertEqual(rows['probe']['score'], 1.0)
        self.assertEqual(rows['probe']['status'], 'DIFF')
        self.assertIn('EH LSDA equivalence unverified', rows['probe']['metadata_reasons'])
        self.assertEqual(rows['plain']['status'], 'MATCH')

    def test_changed_valid_range(self):
        _, positions = self.site_positions()
        begin_pos, begin = positions[0][0]
        length_pos, length = positions[0][1]
        parts = self.parts(); offsets = [i[0] - parts[2].value for i in parts[3]]
        alternatives = [v for v in offsets if begin < v < begin + length]
        if not alternatives:
            # A one-instruction protected range is made empty and must fail.
            self.assertIsNone(self.signature(self.change(length_pos, 0)))
        else:
            self.assertNotEqual(self.signature(self.change(begin_pos, alternatives[0])), self.signature(parts))

    def test_non_instruction_landing_pad(self):
        _, positions = self.site_positions()
        pos, pad = next(row[2] for row in positions if row[2][1])
        parts = self.parts(); offsets = {i[0] - parts[2].value for i in parts[3]}
        invalid = next(i for i in range(1, min(parts[2].size, 128)) if i not in offsets)
        self.assertIsNone(self.signature(self.change(pos, invalid)))

    def test_nonzero_action(self):
        _, positions = self.site_positions()
        self.assertIsNone(self.signature(self.change(positions[0][3][0], 1)))

    def test_explicit_lpstart(self):
        self.assertIsNone(self.signature(self.change(0, 0)))

    def test_type_table_and_catches(self):
        self.assertIsNone(self.signature(self.change(1, 3)))

    def test_unsupported_call_site_encoding(self):
        self.assertIsNone(self.signature(self.change(2, 3)))

    def test_truncated_table(self):
        position, _ = self.site_positions()
        self.assertIsNone(self.signature(self.change(position, 127)))

    def test_empty_table(self):
        position, _ = self.site_positions()
        self.assertIsNone(self.signature(self.change(position, 0)))

    def test_missing_lsda_association(self):
        parts = list(self.parts()); parts[1] = replace(parts[1], lsdas=())
        self.assertIsNone(self.signature(parts))

    def test_wrong_function_size(self):
        image, frames, symbol, insns, _ = self.parts()
        self.assertIsNone(eh.cleanup_signature(image, frames, symbol.value, symbol.size - 1, insns, symbol.shndx))

    def test_wrong_function_start(self):
        image, frames, symbol, insns, _ = self.parts()
        self.assertIsNone(eh.cleanup_signature(image, frames, symbol.value + 1, symbol.size - 1, insns[1:], symbol.shndx))

    def test_overlapping_fde(self):
        parts = list(self.parts()); image, frames, symbol, insns, _ = parts
        entry = next(row for row in frames.ranges if row[0:3] == (symbol.shndx, symbol.value, symbol.value + symbol.size))
        parts[1] = replace(frames, ranges=frames.ranges + (entry,))
        self.assertIsNone(self.signature(parts))

    def test_unknown_personality(self):
        parts = list(self.parts()); frames = parts[1]
        parts[1] = replace(frames, ranges=tuple((*r[:4], '__other_personality') for r in frames.ranges))
        self.assertIsNone(self.signature(parts))

    def test_exception_data_relocation(self):
        parts = self.parts(); image, _, _, _, loc = parts
        reloc = next(r for rs in image.relocs.values() for r in rs)
        image.relocs[loc[3]] = [replace(reloc, offset=loc[4])]
        self.assertIsNone(self.signature(parts))

    def test_truncated_section_bytes(self):
        parts = self.parts(); image, _, _, _, loc = parts
        image.data = image.data[:image.sections[loc[3]].offset + loc[4] + 2]
        self.assertIsNone(self.signature(parts))

    def test_different_instruction_offsets(self):
        parts = list(self.parts()); rows = list(parts[3]); rows[1] = [rows[1][0] + 1, *rows[1][1:]]; parts[3] = rows
        self.assertNotEqual(self.signature(parts), self.signature(self.parts()))

    def test_real_catch_remains_blocked(self):
        source = self.root / 'catch.cpp'
        source.write_text('extern void raise_value(); int catch_probe() { try { raise_value(); return 1; } '
                          'catch (...) { return 2; } }')
        directory = self.root / 'catch'; directory.mkdir(exist_ok=True)
        path, globalized = objdiff.compile_for_diff(source, directory, quiet=True)
        row = objdiff.object_functions(path, globalized=globalized)['_Z11catch_probev']
        self.assertIsNone(row['cleanup_eh'])
        self.assertIn('EH LSDA equivalence unverified', row['metadata_reasons'])


if __name__ == '__main__':
    unittest.main()
