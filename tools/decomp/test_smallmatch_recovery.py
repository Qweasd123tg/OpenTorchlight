"""Fail-closed checks for the type-evidence and post-pruning acceptance gates."""
import copy
import hashlib
import json
from pathlib import Path
from tempfile import TemporaryDirectory
from types import SimpleNamespace as NS
import unittest
from unittest.mock import patch

import smallmatch_layouts as layouts
import smallmatch_recovery as recovery
import smallmatch_vtables as vtables


TREE = 'std::_Rb_tree<int, std::pair<int const, float>, std::_Select1st<std::pair<int const, float> >, std::less<int>, std::allocator<std::pair<int const, float> > >'


class ContainerEvidenceTest(unittest.TestCase):
    def test_tree_destruction_does_not_claim_map(self):
        row = layouts.container_type(TREE + '::_M_erase(node*)')
        self.assertEqual('map_or_multimap', row['representation'])
        self.assertEqual('std::map<int, float>', row['type'])

    def test_unique_insertion_is_distinguished(self):
        row = layouts.container_type(TREE + '::_M_insert_unique(value const&)')
        self.assertEqual('unique_map', row['representation'])

    def test_custom_comparator_is_not_replaced_by_default(self):
        self.assertIsNone(layouts.container_type(TREE.replace('std::less<int>', 'std::greater<int>') + '::_M_erase(node*)'))

    def test_nested_template_type_survives(self):
        symbol = 'TArrayList<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > >::~TArrayList()'
        self.assertIn('basic_string<wchar_t', layouts.container_type(symbol)['type'])

    def instructions(self):
        return [(0x100, 'push', '%rbx'), (0x101, 'mov', '%rdi,%rbx'),
                (0x104, 'lea', '0x18(%rbx),%rdi'), (0x108, 'mov', '%rax,%rbp'),
                (0x10b, 'call', '200 <TArrayList<int>::~TArrayList()>'),
                (0x110, 'pop', '%rbx'), (0x111, 'ret', '')]

    def test_saved_this_and_terminal_restore(self):
        rows = self.instructions()
        self.assertEqual({'%rbx'}, layouts.stable_this_registers(rows))
        self.assertEqual((0x18, 0x104), layouts.receiver_offset(rows, 4, {'%rbx'}))

    def test_partial_write_invalidates_this_alias(self):
        rows = self.instructions(); rows.insert(2, (0x103, 'mov', '%eax,%ebx'))
        self.assertFalse(layouts.stable_this_registers(rows))

    def test_overwritten_receiver_is_not_old_lea(self):
        rows = self.instructions(); rows[3] = (0x108, 'mov', '%rsi,%rdi')
        self.assertIsNone(layouts.receiver_offset(rows, 4, {'%rbx'}))

    def test_call_boundary_invalidates_receiver(self):
        rows = self.instructions(); rows[3] = (0x108, 'call', '300 <other>')
        self.assertIsNone(layouts.receiver_offset(rows, 4, {'%rbx'}))

    def test_branch_before_this_anchor_is_not_trusted(self):
        rows = self.instructions(); rows.insert(1, (0x100, 'je', '108 <f+8>'))
        self.assertFalse(layouts.stable_this_registers(rows))

    def test_jump_into_call_bypasses_receiver_definition(self):
        rows = self.instructions(); rows.insert(2, (0x103, 'je', '10b <f+11>'))
        self.assertIsNone(layouts.receiver_offset(rows, 5, {'%rbx'}))

    def test_indirect_continuation_cannot_prove_receiver(self):
        rows = self.instructions(); rows.append((0x120, 'jmp', '*%rax'))
        self.assertIsNone(layouts.receiver_offset(rows, 4, {'%rbx'}))

    def test_restored_register_jumping_back_is_not_this(self):
        rows = self.instructions(); rows[-1] = (0x111, 'jmp', '104 <f+4>')
        self.assertFalse(layouts.stable_this_registers(rows))


class ManifestBoundaryTest(unittest.TestCase):
    def setUp(self):
        self.tmp = TemporaryDirectory(); self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name) / 'root'; self.kit = Path(self.tmp.name) / 'kit'
        for base in (self.root / 'decomp/include', self.kit / 'project/decomp/include',
                     self.kit / 'reference', self.kit / 'original'):
            base.mkdir(parents=True)
        (self.kit / 'original/Torchlight.bin.x86_64').write_bytes(b'not executable fixture')
        (self.kit / 'reference/elfdb.json').write_text('{"functions":{}}')
        (self.kit / 'targets.json').write_text('[]')
        (self.kit / 'project/decomp/include/C.h').write_text('old')
        (self.root / 'decomp/include/C.h').write_text('new')
        self.manifest = {'schema': 1, 'base_commit': '824e3d3a33242c9ea775ca8a5ff36e87d6fd23ee',
                         'original_elf_sha256': layouts.digest(self.kit / 'original/Torchlight.bin.x86_64'),
                         'headers': [{'path': 'C.h', 'before_sha256': layouts.digest(self.kit / 'project/decomp/include/C.h'),
                                      'after_sha256': layouts.digest(self.root / 'decomp/include/C.h')}], 'classes': []}

    def test_reviewed_hash_boundary(self):
        self.assertTrue(layouts.validate_manifest(self.kit, self.root, self.manifest))
        (self.root / 'decomp/include/C.h').write_text('unreviewed change')
        with self.assertRaisesRegex(ValueError, 'reviewed content'):
            layouts.validate_manifest(self.kit, self.root, self.manifest)

    def test_unlisted_nested_header_is_rejected(self):
        p = self.root / 'decomp/include/nested/x.inc'; p.parent.mkdir(); p.write_text('extra')
        with self.assertRaisesRegex(ValueError, 'absent from'):
            layouts.validate_manifest(self.kit, self.root, self.manifest)

    def test_changed_original_is_rejected(self):
        (self.kit / 'original/Torchlight.bin.x86_64').write_bytes(b'changed')
        with self.assertRaisesRegex(ValueError, 'original ELF'):
            layouts.validate_manifest(self.kit, self.root, self.manifest)

    def test_receiver_evidence_is_required(self):
        self.manifest['classes'] = [{'name': 'C', 'header': 'C.h', 'size': 24, 'provenance': 'review',
            'members': [{'offset': 0, 'size': 24, 'type': 'TArrayList<int>', 'evidence_type': 'TArrayList<int>',
                         'name': 'items', 'witnesses': [{'function': '0x100', 'call_instruction': '0x108', 'assembly_sha256': 'x'}]}]}]
        with self.assertRaisesRegex(ValueError, 'does not reproduce'):
            layouts.validate_manifest(self.kit, self.root, self.manifest)


class ClosurePruningTest(unittest.TestCase):
    def setUp(self):
        self.f = {'address': '0x100', 'qualified': 'C::~C', 'demangled': 'C::~C()', 'params': '', 'cv': '', 'tu': 1, 'kind': 'dtor'}
        self.db = {'functions': {'0x100': self.f, '0x120': {**self.f, 'address': '0x120'}}}
        self.rows = [{'address': '0x100'}]

    def test_deleting_match_does_not_accept_different_main_destructor(self):
        comparison = {'functions': [{'address': '0x100', 'status': 'DIFF'}, {'address': '0x120', 'status': 'MATCH'}]}
        keep, rejected = recovery.next_survivors(self.rows, comparison, {'0x100': self.f}, self.db)
        self.assertFalse(keep); self.assertEqual('DIFF', rejected[0]['status'])

    def test_a_former_match_is_rechecked_after_context_changes(self):
        comparison = {'functions': [{'address': '0x100', 'status': 'MATCH'}, {'address': '0x120', 'status': 'MATCH'}]}
        keep, _ = recovery.next_survivors(self.rows, comparison, {'0x100': self.f}, self.db)
        comparison['functions'][0]['status'] = 'DIFF'
        keep, rejected = recovery.next_survivors(keep, comparison, {'0x100': self.f}, self.db)
        self.assertFalse(keep); self.assertEqual(1, len(rejected))


class VtableBoundaryTest(unittest.TestCase):
    def fixture(self):
        cls = {'name': 'C', 'base': 'B'}
        symbols = [NS(name='_ZTV1C', defined=True, size=32, shndx=1, value=0),
                   NS(name='_ZTI1C', defined=True, size=24, shndx=2, value=0),
                   NS(name='_ZTS1C', defined=True, size=3, shndx=3, value=0)]
        def ref(offset, name, addend=0):
            return NS(offset=offset, type=1, addend=addend, symbol=NS(name=name))
        obj = NS(symbols=symbols, section_bytes=lambda index: {1: bytes(32), 2: bytes(24), 3: b'1C\0'}[index],
                 relocs={1: [ref(8, '_ZTI1C'), ref(16, 'd1'), ref(24, 'd0')],
                         2: [ref(0, '_ZTVN10__cxxabiv120__si_class_type_infoE', 16), ref(8, '_ZTS1C'), ref(16, '_ZTI1B')]})
        original = NS(db={'classes': {'C': {'bases': [{'class': 'B', 'external': True, 'offset': 0, 'public': True, 'virtual': False}]}},
                          'vtables': {'C': {'size': 32, 'groups': [{'offset_to_top': 0, 'slots': ['0x100', '0x120']}]}}},
                      function=lambda name: {'address': {'d1': '0x100', 'd0': '0x120', 'wrong': '0x140'}[name]})
        return obj, cls, original

    def test_complete_original_vtable(self):
        self.assertEqual('PASS', vtables.check_object(*self.fixture())['status'])

    def test_reordered_destructors_are_rejected(self):
        obj, cls, original = self.fixture(); obj.relocs[1][1].symbol.name = 'd0'
        with self.assertRaisesRegex(ValueError, 'slot differs'): vtables.check_object(obj, cls, original)

    def test_extra_virtual_slot_is_rejected(self):
        obj, cls, original = self.fixture(); obj.symbols[0].size = 40
        with self.assertRaisesRegex(ValueError, 'size differs'): vtables.check_object(obj, cls, original)

    def test_wrong_rtti_base_is_rejected(self):
        obj, cls, original = self.fixture(); obj.relocs[2][2].symbol.name = '_ZTI1D'
        with self.assertRaisesRegex(ValueError, 'class/base link'): vtables.check_object(obj, cls, original)

    def test_adjusted_slot_pointer_is_rejected(self):
        obj, cls, original = self.fixture(); obj.relocs[1][1].addend = 8
        with self.assertRaisesRegex(ValueError, 'unsupported vtable relocation'): vtables.check_object(obj, cls, original)


if __name__ == '__main__':
    unittest.main()
