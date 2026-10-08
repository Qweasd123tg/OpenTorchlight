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
#include <vector>
#include <map>
namespace Left { struct Item { int value; }; typedef Item Alias; }
namespace Right { struct Item { long value; }; }
struct Owner { struct Nested { unsigned long value; }; Left::Alias* item; };
Left::Alias left;
Right::Item right;
Owner::Nested nested;
Owner owner;
struct Containers { std::vector<Left::Alias> values; std::map<long long, Left::Alias*> lookup; } containers;
std::vector<double> unrelated;
struct Matrix { union { float rows[4][4]; float flat[16]; }; } matrix;
std::vector<Left::Alias>::iterator iterator;
void iterator_parameter(std::vector<Left::Alias>::iterator);
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

    def test_anonymous_union_and_value_parameter_layouts_are_exact(self):
        classes = types_export.header_classes(self.dies)
        matrix = classes['Matrix']
        union = classes[matrix['fields'][0]['type']]
        self.assertEqual('union', union['kind'])
        self.assertEqual(64, union['size'])
        self.assertEqual([0, 0], [f['offset'] for f in union['fields']])
        self.assertEqual(['float[4][4]', 'float[16]'], [f['type'] for f in union['fields']])
        iterator = next(v for k, v in classes.items() if k.startswith('__gnu_cxx::__normal_iterator<Left::Item*'))
        self.assertEqual(8, iterator['size'])
        self.assertEqual('Left::Item*', iterator['fields'][0]['type'])

    def test_materialization_uses_original_game_value_parameters_only(self):
        dies = copy.deepcopy(self.dies)
        name = next(types_export.qualified_name(dies, ref) for ref, d in dies.items()
                    if d['tag'] in ('DW_TAG_class_type', 'DW_TAG_structure_type')
                    and types_export.qualified_name(dies, ref).startswith('__gnu_cxx::__normal_iterator<Left::Item*'))
        for ref, d in dies.items():
            if types_export.qualified_name(dies, ref) == name:
                d['attrs']['DW_AT_declaration'] = True
        db = {'tus': [{'id': 1, 'kind': 'game'}, {'id': 2, 'kind': 'library'}],
              'functions': {'value': {'tu': 1, 'params': name},
                            'reference': {'tu': 1, 'params': name + ' const&'},
                            'private': {'tu': 2, 'params': '__gnu_cxx::__normal_iterator<Private*, std::vector<Private> >'}}}
        self.assertEqual([name], types_export.materialized_iterators(dies, db))
        db['functions'].pop('value')
        self.assertEqual([], types_export.materialized_iterators(dies, db))

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

    def test_pinned_containers_export_exact_private_base_and_typedef_closure(self):
        classes = types_export.header_classes(self.dies)
        seen = set()
        fields = []
        def flatten(name, offset=0):
            self.assertIn(name, classes, name)
            seen.add(name)
            entry = classes[name]
            self.assertNotIn('layout_errors', entry)
            for base in entry['bases']:
                self.assertIsNotNone(base['offset'])
                flatten(base['name'], offset + base['offset'])
            for field in entry['fields']:
                value = field['type']
                if value in classes:
                    flatten(value, offset + field['offset'])
                else:
                    fields.append((field['name'], offset + field['offset'], value, field['size']))
        vector = classes['Containers']['fields'][0]
        flatten(vector['type'])
        self.assertEqual(vector['size'], classes[vector['type']]['size'])
        self.assertEqual(fields, [('_M_start', 0, 'Left::Item*', 8),
                                  ('_M_finish', 8, 'Left::Item*', 8),
                                  ('_M_end_of_storage', 16, 'Left::Item*', 8)])
        self.assertTrue(any('::_Vector_impl' in name for name in seen))
        fields[:] = []
        lookup = classes['Containers']['fields'][1]
        flatten(lookup['type'])
        self.assertEqual(lookup['size'], classes[lookup['type']]['size'])
        self.assertEqual([(n, o, s) for n, o, _, s in fields],
                         [('_M_color', 8, 4), ('_M_parent', 16, 8), ('_M_left', 24, 8),
                          ('_M_right', 32, 8), ('_M_node_count', 40, 8)])
        self.assertTrue(any('::_Rb_tree_impl' in name for name in seen))
        self.assertFalse(any(name.startswith('std::vector<double,') for name in classes))

    def test_missing_member_offset_and_bitfields_remain_blockers(self):
        dies = copy.deepcopy(self.dies)
        ref = next(ref for ref in dies if types_export.qualified_name(dies, ref) == 'Left::Item'
                   and dies[ref]['tag'] == 'DW_TAG_structure_type'
                   and not dies[ref]['attrs'].get('DW_AT_declaration'))
        member = next(dies[c] for c in dies[ref]['children'] if dies[c]['tag'] == 'DW_TAG_member')
        member['attrs'].pop('DW_AT_data_member_location')
        self.assertIn('layout_errors', types_export.header_classes(dies)['Left::Item'])
        member['attrs']['DW_AT_data_member_location'] = 0
        member['attrs']['DW_AT_bit_size'] = 3
        self.assertIn('layout_errors', types_export.header_classes(dies)['Left::Item'])

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
