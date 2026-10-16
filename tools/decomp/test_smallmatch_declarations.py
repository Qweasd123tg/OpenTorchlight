"""Source identity lookup is not return/static ABI inference or acceptance."""
import json
from pathlib import Path
from tempfile import TemporaryDirectory
import unittest

import smallmatch


class DeclarationTests(unittest.TestCase):
    def setUp(self):
        self.temp = TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / 'decomp/include').mkdir(parents=True)
        self.kit = self.root / 'kit'
        (self.kit / 'reference').mkdir(parents=True)
        (self.kit / 'targets.json').write_text('[]')
        (self.kit / 'reference/elfdb.json').write_text('{"functions": {}, "globals": []}')

    def declaration(self, source, parameters, cv='', scope='C', prototype=None, extra=None):
        (self.root / 'decomp/include/C.h').write_text(source)
        for name, text in (extra or {}).items():
            (self.root / 'decomp/include' / name).write_text(text)
        abi = {'trusted': True, 'static': False, 'variadic': False, 'sret': False}
        abi.update(prototype or {})
        (self.kit / 'reference/types.json').write_text(json.dumps({'classes': {}, 'prototypes': {'0x100': abi}}))
        generator = smallmatch.Generator(self.kit, self.root)
        function = {'address': '0x100', 'method': 'f', 'qualified': scope + '::f',
                    'params': parameters, 'cv': cv, 'scope': scope}
        return generator.declaration(function)

    def rejects(self, source, parameters, **kwargs):
        with self.assertRaises(smallmatch.Unsupported):
            self.declaration(source, parameters, **kwargs)

    def test_leading_comment_does_not_become_return_type(self):
        result = self.declaration('class C { public: // explanatory comment; {\n bool f(unsigned int value); };', 'unsigned int')
        self.assertEqual('bool', result['ret'])

    def test_nested_forward_declaration_is_qualified(self):
        self.declaration('class C { class D; void f(D* value); };', 'C::D*')

    def test_nested_definition_is_qualified(self):
        self.declaration('class C { struct D { int x; }; void f(D* value); };', 'C::D*')

    def test_nested_name_does_not_match_unrelated_scope(self):
        self.rejects('class C { class D; void f(D* value); };', 'Other::D*')

    def test_original_global_type_is_not_qualified_to_nested_shadow(self):
        source = 'class D {}; class C { class D; void f(D* value); };'
        self.rejects(source, 'D*')
        self.declaration(source, 'C::D*')

    def test_global_callback_alias_types_keep_their_defining_scope(self):
        source = 'class D {}; typedef int (*Callback)(D*); class C { class D; void f(Callback cb); };'
        self.declaration(source, 'int (*)(D*)')
        self.rejects(source, 'int (*)(C::D*)')

    def test_nested_type_can_shadow_global_callback_alias(self):
        self.rejects('typedef int (*Callback)(int); class C { class Callback; void f(Callback cb); };', 'int (*)(int)')

    def test_parameter_name_matching_nested_type_does_not_change_type(self):
        self.declaration('class C { class value; void f(int value); };', 'int')

    def test_innermost_type_shadows_outer(self):
        self.rejects('class C { class D; class Inner { class D; void f(D* value); }; };', 'C::D*', scope='C::Inner')
        self.declaration('class C { class D; class Inner { class D; void f(D* value); }; };', 'C::Inner::D*', scope='C::Inner')

    def test_same_method_in_different_scope_is_not_used(self):
        self.rejects('class Other { void f(int value); };', 'int')

    def test_callback_alias_matches_const_string(self):
        self.declaration('typedef unsigned int (*Callback)(const std::wstring&, void*); class C { void f(Callback cb); };',
                         'unsigned int (*)(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, void*)')

    def test_callback_constness_and_return_stay_distinct(self):
        source = 'typedef unsigned int (*Callback)(const std::wstring&, void*); class C { void f(Callback cb); };'
        self.rejects(source, 'int (*)(std::wstring const&, void*)')
        self.rejects(source, 'unsigned int (*)(std::wstring&, void*)')

    def test_callback_pointer_object_const_is_not_pointee_const(self):
        for actual, wanted in (('D* const&', 'const D*&'), ('D* const*', 'const D**')):
            source = 'typedef int (*Callback)(' + actual + '); class C { void f(Callback cb); };'
            self.rejects(source, 'int (*)(' + wanted + ')')

    def test_callback_pointer_object_cv_is_conservatively_deferred(self):
        for actual in ('D* const&', 'D* volatile&'):
            source = 'typedef int (*Callback)(' + actual + '); class C { void f(Callback cb); };'
            self.rejects(source, 'int (*)(' + actual + ')')

    def test_callback_pointee_const_still_matches(self):
        self.declaration('typedef int (*Callback)(const D*&); class C { void f(Callback cb); };', 'int (*)(const D*&)')

    def test_conflicting_aliases_fail_closed(self):
        self.rejects('typedef int (*Callback)(int); class C { void f(Callback cb); };', 'int (*)(int)',
                     extra={'Other.h': 'typedef float (*Callback)(int);'})

    def test_scoped_callback_shadow_fails_closed(self):
        self.rejects('typedef int (*Callback)(int); class C { typedef float (*Callback)(int); void f(Callback cb); };', 'int (*)(int)')

    def test_noncallback_shadow_fails_closed(self):
        self.rejects('typedef int (*Callback)(int); class C { typedef float Callback; void f(Callback cb); };', 'int (*)(int)')

    def test_pointer_to_callback_alias_not_equated(self):
        self.rejects('typedef int (*Callback)(int); class C { void f(Callback* cb); };', 'int (*)(int)')

    def test_callback_word_boundaries_preserved(self):
        self.rejects('typedef int (*Callback)(unsignedint); class C { void f(Callback cb); };', 'int (*)(unsigned int)')

    def test_nested_callback_declarators_are_not_guessed(self):
        self.rejects('typedef int (*Callback)(int (*nested)(int)); class C { void f(Callback cb); };', 'int (*)(int (*)(int))')

    def test_array_reference_exact_extent(self):
        self.declaration('class C { void f(float (&values)[6], bool use); };', 'float (&) [6], bool')
        self.rejects('class C { void f(float (&values)[6], bool use); };', 'float (&) [5], bool')

    def test_array_reference_does_not_match_pointer(self):
        self.rejects('class C { void f(float* values); };', 'float (&) [6]')

    def test_array_reference_retains_element_qualifiers(self):
        self.rejects('class C { void f(const float (&values)[6]); };', 'float (&) [6]')

    def test_unsized_expression_and_multidimensional_arrays_deferred(self):
        for array in ('[]', '[COUNT]', '[6][2]'):
            self.rejects('class C { void f(float (&values)' + array + '); };', 'float (&) [6]')

    def test_file_alias_needs_pinned_system_include(self):
        self.declaration('#include <stdio.h>\nclass C { void f(FILE* file); };', '_IO_FILE*')
        self.rejects('class C { void f(FILE* file); };', '_IO_FILE*')

    def test_file_alias_does_not_override_shadow(self):
        self.rejects('#include <stdio.h>\nclass C { typedef Other FILE; void f(FILE* file); };', '_IO_FILE*')

    def test_file_alias_does_not_expand_namespace_alias(self):
        self.rejects('#include <stdio.h>\nclass C { void f(Custom::FILE* file); };', '_IO_FILE*')

    def test_original_nominal_file_name_is_not_system_alias_expanded(self):
        self.rejects('#include <stdio.h>\nclass C { void f(_IO_FILE* file); };', 'FILE*')

    def test_commented_include_does_not_enable_file_alias(self):
        self.rejects('/*\n#include <stdio.h>\n*/\nclass C { void f(FILE* file); };', '_IO_FILE*')

    def test_map_defaults_match(self):
        full = 'std::map<unsigned int, bool, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, bool> > >&'
        self.declaration('class C { void f(std::map<unsigned int, bool>& values); };', full)

    def test_map_pointer_key_default_qualifies_pointer_object(self):
        full = 'std::map<Item*, bool, std::less<Item*>, std::allocator<std::pair<Item* const, bool> > >&'
        self.declaration('class C { void f(std::map<Item*, bool>& values); };', full)

    def test_map_pointer_key_pointee_const_is_not_default_allocator(self):
        full = 'std::map<Item*, bool, std::less<Item*>, std::allocator<std::pair<const Item*, bool> > >&'
        self.rejects('class C { void f(std::map<Item*, bool>& values); };', full)

    def test_map_template_key_with_pointer_element_can_have_prefix_const(self):
        full = 'std::map<std::vector<Item*>, bool, std::less<std::vector<Item*> >, std::allocator<std::pair<const std::vector<Item*>, bool> > >&'
        self.declaration('class C { void f(std::map<std::vector<Item*>, bool>& values); };', full)

    def test_map_comparator_allocator_and_key_const_are_preserved(self):
        source = 'class C { void f(std::map<unsigned int, bool>& values); };'
        for full in ('std::map<unsigned int, bool, std::greater<unsigned int> >&',
                     'std::map<unsigned int, bool, std::less<unsigned int>, CustomAllocator>&',
                     'std::map<unsigned int, bool, std::less<unsigned int>, std::allocator<std::pair<unsigned int, bool> > >&',
                     'std::map<unsignedint, bool>&'):
            self.rejects(source, full)

    def test_vector_defaults_still_match(self):
        self.declaration('class C { void f(std::vector<unsigned int>& values); };', 'std::vector<unsigned int, std::allocator<unsigned int> >&')

    def test_vector_custom_allocator_rejected(self):
        self.rejects('class C { void f(std::vector<unsigned int>& values); };', 'std::vector<unsigned int, CustomAllocator>&')

    def test_cv_and_overload_identity_preserved(self):
        source = 'class C { void f(int value) const; void f(float value); };'
        self.declaration(source, 'int', cv='const')
        self.rejects(source, 'int')
        self.rejects(source, 'double')

    def test_conflicting_return_declarations_are_ambiguous(self):
        self.rejects('class C { void f(int value); int f(int value); };', 'int')

    def test_static_status_must_match_exported_abi(self):
        self.rejects('class C { static void f(int value); };', 'int')
        self.declaration('class C { static void f(int value); };', 'int', prototype={'static': True})

    def test_untrusted_variadic_and_hidden_returns_remain_blocked(self):
        for prototype in ({'trusted': False}, {'variadic': True}, {'sret': True}):
            self.rejects('class C { void f(int value); };', 'int', prototype=prototype)

    def test_complex_parameter_names_are_inserted_inside_declarator(self):
        self.assertEqual('float (&value)[6]', smallmatch._named_parameter('float (&)[6]', 'value'))
        self.assertEqual('int (*cb)(int)', smallmatch._named_parameter('int (*)(int)', 'cb'))


if __name__ == '__main__':
    unittest.main()
