#!/usr/bin/env python3
"""Original-compiler DWARF regression: namespace, alias, layout conflicts and secondary groups."""
import copy
from pathlib import Path
import tempfile
import unittest

import toolchain
import types_export


class QualifiedTypes(unittest.TestCase):
    def test_unknown_span_keeps_its_width(self):
        self.assertEqual("undefined24", types_export.sane_type("unknown", 24, {"classes": {}}, {}))

    @classmethod
    def setUpClass(cls):
        cls.folder = tempfile.TemporaryDirectory(prefix='otl-type-identity-')
        source = Path(cls.folder.name) / 'identity.cpp'
        obj = source.with_suffix('.o')
        source.write_text('''
namespace Left { struct Item { int value; }; typedef Item Alias; }
namespace Right { struct Item { long value; }; }
struct Owner { struct Nested { unsigned long value; }; Left::Alias* item; };
Left::Alias left;
Right::Item right;
Owner::Nested nested;
Owner owner;
''')
        toolchain.compile_source(source, obj, ['-g', '-O0', '-fno-eliminate-unused-debug-types',
                                              '-femit-class-debug-always'], cache=False)
        cls.dies = types_export.parse_dies(obj)

    @classmethod
    def tearDownClass(cls):
        cls.folder.cleanup()

    def test_namespaces_nested_types_and_alias_targets_are_distinct(self):
        classes = types_export.header_classes(self.dies)
        self.assertIn('Left::Item', classes)
        self.assertIn('Right::Item', classes)
        self.assertIn('Owner::Nested', classes)
        self.assertEqual(classes['Left::Item']['size'], 4)
        self.assertEqual(classes['Right::Item']['size'], 8)
        self.assertEqual(classes['Owner::Nested']['fields'][0]['type'], 'long unsigned int')
        self.assertEqual(classes['Owner']['fields'][0]['type'], 'Left::Item*')
        names = {entry['name'] for entry in types_export.type_identities(self.dies).values()}
        self.assertIn('Left::Alias', names)

    def test_disagreeing_same_qualified_identity_is_quarantined(self):
        dies = copy.deepcopy(self.dies)
        ref = next(ref for ref in dies if types_export.qualified_name(dies, ref) == 'Left::Item'
                   and dies[ref]['tag'] == 'DW_TAG_structure_type'
                   and not dies[ref]['attrs'].get('DW_AT_declaration'))
        duplicate = copy.deepcopy(dies[ref])
        duplicate['attrs']['DW_AT_byte_size'] = 99
        dies[max(dies) + 1] = duplicate
        conflicts = {}
        classes = types_export.header_classes(dies, conflicts)
        self.assertNotIn('Left::Item', classes)
        self.assertEqual(len(conflicts['Left::Item']), 2)
        self.assertIn('Right::Item', classes)

    def test_typedef_cv_and_unknown_array_extent_are_preserved(self):
        dies = {1: {'tag': 'DW_TAG_base_type', 'attrs': {'DW_AT_name': 'long int', 'DW_AT_byte_size': 8},
                    'children': []},
                2: {'tag': 'DW_TAG_typedef', 'attrs': {'DW_AT_name': 'Alias', 'DW_AT_type': 1}, 'children': []},
                3: {'tag': 'DW_TAG_const_type', 'attrs': {'DW_AT_type': 2}, 'children': []},
                4: {'tag': 'DW_TAG_array_type', 'attrs': {'DW_AT_type': 3}, 'children': [5]},
                5: {'tag': 'DW_TAG_subrange_type', 'attrs': {}, 'children': []}}
        self.assertEqual(types_export.type_name(dies, 4), 'const long int[]')
        self.assertEqual(types_export.type_size(dies, 4), 0)

    def test_conflicting_prototypes_are_quarantined_and_free_functions_have_no_this(self):
        dies = {
            1: {"tag": "DW_TAG_base_type", "attrs": {"DW_AT_name": "int", "DW_AT_byte_size": 4}, "children": []},
            2: {"tag": "DW_TAG_base_type", "attrs": {"DW_AT_name": "long int", "DW_AT_byte_size": 8}, "children": []},
            3: {"tag": "DW_TAG_subprogram", "attrs": {"DW_AT_linkage_name": "_Z1fv", "DW_AT_type": 1}, "children": []}}
        db = {"functions": {"0x10": {"names": ["_Z1fv"], "demangled": "f()", "scope": ""}}, "classes": {}}
        first = types_export.prototypes(dies, db, set(), set())
        self.assertFalse(first["0x10"]["member"])
        dies[4] = {"tag": "DW_TAG_subprogram", "attrs": {"DW_AT_linkage_name": "_Z1fv", "DW_AT_type": 2},
                   "children": []}
        conflicts = {}
        self.assertEqual(types_export.prototypes(dies, db, set(), set(), conflicts), {})
        self.assertEqual(len(conflicts["0x10"]), 2)

    def test_exact_sdk_linkage_and_c_imports_without_short_name_guessing(self):
        dies = {
            1: {"tag": "DW_TAG_base_type", "attrs": {"DW_AT_name": "int", "DW_AT_byte_size": 4}, "children": []},
            2: {"tag": "DW_TAG_namespace", "attrs": {"DW_AT_name": "Ogre"}, "children": [3]},
            3: {"tag": "DW_TAG_subprogram", "attrs": {"DW_AT_name": "read", "DW_AT_linkage_name": "_ZN4Ogre4readEv",
                    "DW_AT_type": 1}, "children": [], "parent": 2},
            4: {"tag": "DW_TAG_subprogram", "attrs": {"DW_AT_name": "exact_c_import", "DW_AT_type": 1}, "children": []},
            5: {"tag": "DW_TAG_subprogram", "attrs": {"DW_AT_name": "read", "DW_AT_linkage_name": "_Z4readv",
                    "DW_AT_type": 1}, "children": []},
            6: {"tag": "DW_TAG_unspecified_parameters", "attrs": {}, "children": []}}
        db = {"imports": {"plt": {"0x10": "exact_c_import"}}, "classes": {}}
        sdk = types_export.sdk_prototypes(dies, db)
        self.assertEqual(set(sdk), {"_ZN4Ogre4readEv", "exact_c_import"})
        self.assertTrue(sdk['exact_c_import']['imported'])
        self.assertEqual(sdk['_ZN4Ogre4readEv']['abi_status'], 'SCALAR_OR_POINTER')
        dies[3]['children'] = [6]
        sdk = types_export.sdk_prototypes(dies, db)
        self.assertEqual(sdk['_ZN4Ogre4readEv']['abi_status'], 'AGGREGATE_UNVERIFIED')
        self.assertTrue(sdk['_ZN4Ogre4readEv']['variadic'])

    def test_secondary_groups_keep_targets_and_unknown_adjustment_abi(self):
        db = {'vtables': {'Owner': {'address': 0x100, 'size': 64, 'groups': [
            {'offset_to_top': 0, 'slots': ['0x10', None]},
            {'offset_to_top': -16, 'slots': ['0x20']}] }},
              'functions': {'0x10': {'demangled': 'Owner::call()'},
                            '0x20': {'demangled': 'non-virtual thunk to Owner::call()'}}}
        groups = types_export.vtable_groups(db, {'0x10': {'ret': 'void'}, '0x20': {'ret': 'void'}})['Owner']['groups']
        self.assertEqual(len(groups), 2)
        self.assertEqual(groups[0]['slots'][0]['abi_status'], 'PRIMARY_PROTOTYPE')
        self.assertEqual(groups[1]['object_vptr_offset'], 16)
        self.assertEqual(groups[1]['slots'][0]['target'], '0x20')
        self.assertEqual(groups[1]['slots'][0]['abi_status'], 'SECONDARY_UNVERIFIED')
        self.assertIsNone(groups[1]['slots'][0]['prototype'])
        self.assertIsNone(groups[0]['slots'][1]['target'])


if __name__ == '__main__':
    unittest.main()
