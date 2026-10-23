"""Offline regression tests: no original ELF, provider, game, Ghidra or compiler."""
from __future__ import annotations

from pathlib import Path
from tempfile import TemporaryDirectory
from types import SimpleNamespace, ModuleType
from unittest import TestCase, main, mock
import copy
import hashlib
import os
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
from llm_context import Context, ContextError, ContextIndex, compose_prompt, _float32_literal_bytes


HERE = Path(__file__).resolve().parents[2] / "build-decomp"


def section(name, address, data, *, flags=2, typ=1, entsize=0, size=None):
    return SimpleNamespace(name=name, addr=address, size=len(data) if size is None else size,
                           flags=flags, type=typ, entsize=entsize, contents=data)


class FakeImage:
    def __init__(self, *sections, file_limit=None):
        self.sections = list(sections)
        self.reads = []
        self.symbols, self.dynsyms, self.relocs = [], [], {}
        self.segments = [(1, 4, 0, s.addr, 0, len(s.contents) if file_limit is None else file_limit, s.size, 4096)
                         for s in sections if s.type != 8]

    def section_at(self, address):
        return next((s for s in self.sections if s.addr <= address < s.addr + s.size), None)

    def read(self, address, size):
        self.reads.append((address, size))
        s = self.section_at(address)
        if not s or address + size > s.addr + len(s.contents):
            raise ValueError("not file-backed")
        return s.contents[address - s.addr:address - s.addr + size]


def function(address, scope, method, *, tu=0, size=0x80, **extra):
    qualified = (scope + "::" if scope else "") + method
    params = extra.pop("params", {"getStatInt": "int", "getStatFloat": "int", "GetInt": "wchar_t const*", "gameFree": "int"}.get(method, ""))
    cv = extra.pop("cv", "")
    return dict(params=params, cv=cv, address=hex(address), size=size, scope=scope, method=method,
                qualified=qualified, demangled=qualified + "()", mangled="_fake_" + method,
                tu=tu, **extra)


def object_symbol(address, name, *, size=32, bind="global", file=None):
    return dict(address=hex(address), name=name, demangled=name, size=size, bind=bind, file=file)


class PacketContextTests(TestCase):
    def setUp(self):
        self.sdk_pins = mock.patch.dict(ContextIndex.CEGUI_HEADER_SHA256, {}, clear=True)
        self.sdk_pins.start()
        self.addCleanup(self.sdk_pins.stop)
        self.tmp = TemporaryDirectory(prefix="test-", dir=HERE)
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.include = self.root / "decomp/include"
        self.src = self.root / "decomp/src"
        self.include.mkdir(parents=True)
        self.src.mkdir(parents=True)
        self.target = function(0x1000, "CAchievement", "update", size=0x40)
        self.db = dict(tus=[dict(id=0, name="Achievement.cpp", kind="game"),
                            dict(id=1, name="SteamStats.cpp", kind="game"),
                            dict(id=2, name="Other.cpp", kind="game"),
                            dict(id=3, name="fl_draw.cxx", kind="fltk")],
                       functions={}, globals=[])
        self.write_header("Achievement.h", "class CAchievement { public: void update(); };\n")
        self.write_header("SteamStats.h", "class CSteamStats { public: int getStatInt(int); float getStatFloat(int); };\n")
        self.write_header("Unrelated.h", "class CUnrelated { public: void update(); }; // SHOULD_NOT_APPEAR\n")
        self.write_header("GameVariables.h", "#ifndef VARIABLES_H\n#define VARIABLES_H\n"
                          "// types inferred historically\nstatic unsigned char g_strStatDefines[744];\n"
                          "extern int irrelevantData;\n#endif\n")
        self.mapping = {"CAchievement": "Achievement.h", "CSteamStats": ["SteamStats.h", "SteamStats.h"],
                        "CUnrelated": "Unrelated.h"}
        self.image = FakeImage(section(".rodata", 0x5000, b"\x91" * 128),
                               section(".text", 0x1000, b"\x90" * 128, flags=6),
                               section(".data", 0x6000, b"DATA\0" * 10, flags=3),
                               section(".bss", 0x7000, b"", flags=3, typ=8, size=128))

    def write_header(self, name, text):
        (self.include / name).write_text(text)

    def add_function(self, f):
        self.db["functions"][f["address"]] = f

    def index(self, **kwargs):
        return ContextIndex(root=self.root, db=kwargs.get("db", self.db),
                            image=kwargs.get("image", self.image), headers=kwargs.get("headers", self.mapping))

    def overload_case(self, declaration, params, cv="", *, scope="CResourceManager", method="createUnit"):
        self.write_header("ResourceManager.h", "class " + scope + " { public: " + declaration + " };\n")
        self.mapping[scope] = "ResourceManager.h"
        self.add_function(function(0x2000, scope, method, tu=1, params=params, cv=cv))
        return self.index().build(self.target, "1000: call 2000")

    def test_overload_pointer_not_integer_same_name_and_arity(self):
        result = self.overload_case("CBaseUnit* createUnit(long long guid, int level, bool a, bool b);", "CDataGroup*, int, bool, bool")
        self.assertTrue(result.gaps)
        self.assertIn("ResourceManager.h", result.headers)
        self.assertNotIn("createUnit(CDataGroup*", result.text)

    def test_overload_exact_named_parameters(self):
        result = self.overload_case("CBaseUnit* createUnit(CDataGroup* group, int level, bool first, bool second);", "CDataGroup*, int, bool, bool")
        self.assertFalse(result.gaps)

    def test_overload_multiple_declarations_select_exact_one(self):
        result = self.overload_case("CBaseUnit* createUnit(long long, int, bool, bool); CBaseUnit* createUnit(CDataGroup*, int, bool, bool);", "CDataGroup*, int, bool, bool")
        self.assertFalse(result.gaps)

    def test_overload_wrong_arity(self):
        self.assertTrue(self.overload_case("void createUnit(CDataGroup*);", "CDataGroup*, int").gaps)

    def test_overload_pointer_reference_mismatch(self):
        self.assertTrue(self.overload_case("void createUnit(CDataGroup&);", "CDataGroup*").gaps)

    def test_overload_pointee_cv_mismatch(self):
        self.assertTrue(self.overload_case("void createUnit(const CDataGroup*);", "CDataGroup*").gaps)

    def test_overload_const_spelling_normalized(self):
        self.assertFalse(self.overload_case("void createUnit(const CDataGroup* group);", "CDataGroup const*").gaps)

    def test_overload_member_cv_mismatch(self):
        self.assertTrue(self.overload_case("void createUnit(int);", "int", "const").gaps)
        self.assertTrue(self.overload_case("void createUnit(int) const;", "int").gaps)

    def test_overload_member_cv_exact(self):
        self.assertFalse(self.overload_case("void createUnit(int) const volatile;", "int", "volatile const").gaps)

    def test_overload_default_value_and_pure_virtual(self):
        self.assertFalse(self.overload_case("virtual void createUnit(int level = 0, bool active = true) = 0;", "int, bool").gaps)
        self.assertTrue(self.overload_case("void createUnit(int level = 0);", "").gaps)

    def test_overload_unknown_typedef_not_assumed_equivalent(self):
        self.assertTrue(self.overload_case("void createUnit(MyInteger);", "int").gaps)

    def test_overload_function_pointer_is_unresolved(self):
        self.assertTrue(self.overload_case("void createUnit(void (*callback)(int));", "void (*)(int)").gaps)

    def test_overload_static_and_return_not_guessed_from_symbol(self):
        self.assertFalse(self.overload_case("static double createUnit(int);", "int").gaps)

    def test_overload_destructor_declaration(self):
        self.assertFalse(self.overload_case("virtual ~CResourceManager();", "", method="~CResourceManager").gaps)

    def test_overload_missing_parameter_metadata_is_unresolved(self):
        self.overload_case("void createUnit();", "")
        del self.db["functions"]["0x2000"]["params"]
        self.assertTrue(self.index().build(self.target, "1000: call 2000").gaps)

    def test_overload_tu_local_wrong_parameters(self):
        self.write_header("Achievement.h", "class CAchievement { void update(); }; class CLocal;\n")
        (self.src / "Achievement.cpp").write_text("class CLocal { public: void load(int); };\n")
        self.add_function(function(0x2000, "CLocal", "load", params="CDataGroup*"))
        self.assertTrue(self.index().build(self.target, "1000: call 2000").gaps)

    def test_standard_wstring_const_reference_db_to_typedef(self):
        full = "std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&"
        self.assertFalse(self.overload_case("void createUnit(const std::wstring& text);", full).gaps)

    def test_standard_wstring_typedef_to_full_header(self):
        full = "std::basic_string< wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >"
        self.assertFalse(self.overload_case("void createUnit(const " + full + "& text);", "std::wstring const&").gaps)

    def test_standard_narrow_string_alias_both_directions(self):
        full = "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"
        self.assertFalse(self.overload_case("void createUnit(const std::string&);", full + " const&").gaps)
        self.assertFalse(self.overload_case("void createUnit(const " + full + "&);", "std::string const&").gaps)

    def test_standard_queue_deque_defaults_both_directions(self):
        for short, full in (
            ('std::deque<int>', 'std::deque<int, std::allocator<int> >'),
            ('std::queue<int>', 'std::queue<int, std::deque<int> >'),
            ('std::queue<int>', 'std::queue<int, std::deque<int, std::allocator<int> > >'),
            ('std::queue<std::queue<int> >',
             'std::queue<std::queue<int, std::deque<int> >, std::deque<std::queue<int>, std::allocator<std::queue<int> > > >')):
            for a, b in ((short, full), (full, short)):
                with self.subTest(declared=a, expected=b):
                    self.assertFalse(self.overload_case('void createUnit(' + a + '*);', b + '*').gaps)

    def test_standard_queue_real_reader_signature(self):
        wide = 'std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >'
        params = 'std::queue<' + wide + ', std::deque<' + wide + ', std::allocator<' + wide + '> > >*, wchar_t const*, wchar_t'
        declaration = 'void ReadLineTokenize(std::queue<std::wstring>* tokens, const wchar_t* separators, wchar_t comment);'
        self.write_header('FileReader.h', '#include <queue>\n#include <string>\nclass CFileReader { public: ' + declaration + ' };')
        self.mapping['CFileReader'] = 'FileReader.h'
        self.add_function(function(0xc72c40, 'CFileReader', 'ReadLineTokenize', tu=1, params=params))
        result = self.index().build(self.target, '1000: call c72c40').require_complete()
        self.assertIn(declaration, result.text)
        self.assertIn('FileReader.h', result.headers)

    def test_standard_queue_nondefaults_are_not_erased(self):
        bad = ('std::queue<int, std::vector<int> >',
               'std::queue<int, CustomDeque<int> >',
               'std::queue<int, std::deque<int, CustomAllocator<int> > >',
               'std::queue<int, std::deque<int, std::allocator<const int> > >',
               'std::queue<int, std::deque<const int> >',
               'std::queue<int, std::deque<int*> >',
               'std::queue<int, other::deque<int> >',
               'std::queue<int, std::__debug::deque<int> >',
               'other::std::queue<int, std::deque<int> >',
               'std::__debug::queue<int, std::deque<int> >',
               'std::queue<int, std::deque<int> const>',
               'std::queue<int, std::deque<int>*>',
               'std::queue<int, std::deque<int, other::allocator<int> > >')
        for full in bad:
            with self.subTest(full=full):
                self.assertTrue(self.overload_case('void createUnit(std::queue<int>*);', full + '*').gaps)

    def test_standard_queue_preserves_cv_refs_extra_arguments(self):
        full = 'std::queue<int, std::deque<int, std::allocator<int> > >'
        for params, cv in ((full + ' const*', ''), (full + '&', ''),
                           (full + '**', ''), (full + '*, int', ''), (full + '*', 'const')):
            with self.subTest(params=params, cv=cv):
                self.assertTrue(self.overload_case('void createUnit(std::queue<int>*);', params, cv).gaps)

    def test_standard_sequence_malformed_args_fail_closed(self):
        for full in ('std::queue<>', 'std::queue<int,>', 'std::queue<int, std::deque<int>, int>',
                     'std::queue<int, std::deque<int>', 'std::queue<int, ALLOC(int)>',
                     'std::deque<int, std::allocator<int>, int>', 'std::deque<int,,>'):
            with self.subTest(full=full):
                self.assertTrue(self.overload_case('void createUnit(std::queue<int>*);', full + '*').gaps)

    def test_standard_sequence_word_boundaries_are_preserved(self):
        for kind in ('queue', 'deque'):
            for spaced, joined in (('unsigned int', 'unsignedint'), ('Foo const*', 'Fooconst*')):
                full = 'std::' + kind + '<' + joined + ', std::' + ('deque' if kind == 'queue' else 'allocator') + '<' + joined + '> >'
                self.assertTrue(self.overload_case('void createUnit(std::' + kind + '<' + spaced + '>*);', full + '*').gaps)

    def test_standard_queue_scoped_element_not_short_name_matched(self):
        self.write_header('ResourceManager.h', 'class CResourceManager { public: struct Item {}; void createUnit(std::queue<Item>*); };')
        self.mapping['CResourceManager'] = 'ResourceManager.h'
        for element, expected in (('Item', True), ('Other::Item', True), ('CResourceManager::Item', False)):
            self.add_function(function(0x2000, 'CResourceManager', 'createUnit', tu=1,
                                       params='std::queue<' + element + ', std::deque<' + element + '> >*'))
            self.assertEqual(bool(self.index().build(self.target, '1000: call 2000').gaps), expected)

    def test_standard_vector_default_allocator_both_directions(self):
        full = "std::vector<CDataGroup*, std::allocator<CDataGroup*> >*"
        self.assertFalse(self.overload_case("void createUnit(std::vector<CDataGroup*>* groups);", full).gaps)
        self.assertFalse(self.overload_case("void createUnit(" + full + " groups);",
                                           "std::vector<CDataGroup*>*").gaps)

    def test_standard_vector_real_datagroup_declaration_context(self):
        declaration = "unsigned int GetDataGroupsMatchingName(const std::wstring& name, std::vector<CDataGroup*>* groups);"
        self.write_header("DataGroup.h", "#include <string>\n#include <vector>\nclass CDataGroup { public: " + declaration + " };\n")
        self.mapping['CDataGroup'] = 'DataGroup.h'
        params = ("std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, "
                  "std::vector<CDataGroup*, std::allocator<CDataGroup*> >*")
        self.add_function(function(0xc5f910, 'CDataGroup', 'GetDataGroupsMatchingName', tu=1, params=params))
        result = self.index().build(self.target, "1000: call c5f910").require_complete()
        self.assertIn('DataGroup.h', result.headers)
        self.assertIn(declaration, result.text)  # supplied declaration is not rewritten
        self.add_function(function(0x2000, 'CMissing', 'missing', tu=1, params='int'))
        with self.assertRaises(ContextError):
            self.index().build(self.target, "1000: call c5f910\n1005: call 2000").require_complete()

    def test_standard_vector_nested_default_and_string_alias(self):
        full = 'std::vector<std::vector<int, std::allocator<int> >, std::allocator<std::vector<int, std::allocator<int> > > > const&'
        self.assertFalse(self.overload_case('void createUnit(const std::vector<std::vector<int> >&);', full).gaps)
        string = 'std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >'
        full = 'std::vector<' + string + ', std::allocator<' + string + '> > const&'
        self.assertFalse(self.overload_case('void createUnit(const std::vector<std::wstring>&);', full).gaps)

    def test_standard_vector_custom_namespace_allocator_and_element_do_not_match(self):
        for full in ('std::vector<CDataGroup*, CustomAllocator<CDataGroup*> >*',
                     'std::vector<CDataGroup*, std::allocator<const CDataGroup*> >*',
                     'std::vector<CDataGroup*, std::allocator<CDataGroup> >*',
                     'std::vector<CDataGroup*, otherstd::allocator<CDataGroup*> >*',
                     'std::vector<CDataGroup*, std::__new::allocator<CDataGroup*> >*',
                     'otherstd::vector<CDataGroup*, std::allocator<CDataGroup*> >*',
                     'custom::std::vector<CDataGroup*, std::allocator<CDataGroup*> >*',
                     'std::__debug::vector<CDataGroup*, std::allocator<CDataGroup*> >*',
                     'std::vector<const CDataGroup*, std::allocator<const CDataGroup*> >*',
                     'std::vector<CDataGroup* const, std::allocator<CDataGroup* const> >*'):
            with self.subTest(full=full):
                self.assertTrue(self.overload_case('void createUnit(std::vector<CDataGroup*>*);', full).gaps)

    def test_standard_vector_preserves_outer_qualifiers_arity_member_cv(self):
        full = 'std::vector<CDataGroup*, std::allocator<CDataGroup*> >'
        for params, cv in ((full, ''), (full + '&', ''), (full + ' const*', ''),
                           (full + '**', ''), (full + '*, int', ''), (full + '*', 'const')):
            with self.subTest(params=params, cv=cv):
                self.assertTrue(self.overload_case('void createUnit(std::vector<CDataGroup*>*);', params, cv).gaps)

    def test_standard_vector_malformed_arguments_fail_closed(self):
        for full in ('std::vector<CDataGroup*, std::allocator<CDataGroup*>*',
                     'std::vector<>*', 'std::vector<CDataGroup*,>*',
                     'std::vector<CDataGroup*,,std::allocator<CDataGroup*> >*',
                     'std::vector<CDataGroup*, std::allocator<CDataGroup*>, int>*',
                     'std::vector<CDataGroup*, ALLOC(CDataGroup*)>*'):
            with self.subTest(full=full):
                self.assertTrue(self.overload_case('void createUnit(std::vector<CDataGroup*>*);', full).gaps)

    def test_standard_vector_element_word_boundaries_survive_signature_keys(self):
        for spaced, joined in (('unsigned int', 'unsignedint'), ('Foo const*', 'Fooconst*'),
                               ('const Foo*', 'constFoo*'), ('unsigned long long', 'unsignedlonglong')):
            for header_type, callee_type in ((spaced, joined), (joined, spaced)):
                with self.subTest(header=header_type, callee=callee_type):
                    full = 'std::vector<' + callee_type + ', std::allocator<' + callee_type + '> >*'
                    self.assertTrue(self.overload_case('void createUnit(std::vector<' + header_type + '>*);', full).gaps)
        self.assertFalse(self.overload_case('void createUnit(std::vector<unsigned int>*);',
                                           'std::vector<unsigned int, std::allocator<unsigned int> >*').gaps)

    def test_standard_vector_namespace_spacing_keeps_token_boundaries(self):
        for prefix in ('std :: vector', 'std:: vector', 'std ::vector', 'std\n::\nvector'):
            with self.subTest(prefix=prefix):
                self.assertTrue(self.overload_case('void createUnit(' + prefix + '<unsigned int>*);',
                                                   'std::vector<unsignedint, std::allocator<unsignedint> >*').gaps)
                self.assertTrue(self.overload_case('void createUnit(std::vector<unsignedint>*);',
                                                   prefix + '<unsigned int, std::allocator<unsigned int> >*').gaps)
                self.assertFalse(self.overload_case('void createUnit(' + prefix + '<unsigned int>*);',
                                                    'std::vector<unsigned int, std::allocator<unsigned int> >*').gaps)
                self.assertTrue(self.overload_case('void createUnit(std::vector<unsigned int>*);',
                                                   'custom :: ' + prefix + '<unsigned int, std::allocator<unsigned int> >*').gaps)

    def test_standard_vector_token_boundaries_not_allocator_heuristics(self):
        from llm_context import _standard_vector_defaults
        for text in ('std::vector<unsigned int, std::allocator<unsignedint> >',
                     'std::vector<unsignedint, std::allocator<unsigned int> >',
                     'std::vector<T*, AliasAllocator>',
                     'custom:: std::vector<T, std::allocator<T> >'):
            with self.subTest(text=text):
                normalized = _standard_vector_defaults(text)
                self.assertIn('allocator' if 'allocator' in text else 'AliasAllocator', normalized)
        with self.assertRaises(ValueError):
            _standard_vector_defaults('std::vector<' * 40 + 'int' + '>' * 40)

    def test_standard_string_alias_inside_template(self):
        full = "std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > const&"
        self.assertFalse(self.overload_case("void createUnit(const std::vector<std::wstring>& words);", full).gaps)

    def test_standard_string_alias_does_not_hide_custom_traits_allocator_or_abi(self):
        for full in ("std::basic_string<wchar_t, CustomTraits, std::allocator<wchar_t> >",
                     "std::basic_string<wchar_t, std::char_traits<wchar_t>, CustomAllocator>",
                     "otherstd::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >",
                     "custom::std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >",
                     "std::__cxx11::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >",
                     "std::basic_string<unsigned short, std::char_traits<unsigned short>, std::allocator<unsigned short> >"):
            with self.subTest(full=full):
                self.assertTrue(self.overload_case("void createUnit(const std::wstring&);", full + " const&").gaps)

    def test_standard_string_alias_preserves_reference_and_cv_distinctions(self):
        full = "std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >"
        for params in (full + "&", full + " const*", full, full + " const&, int"):
            with self.subTest(params=params):
                self.assertTrue(self.overload_case("void createUnit(const std::wstring&);", params).gaps)

    def test_dso_registration_all_immediate_argument_permutations(self):
        import itertools
        self.dso_handle()
        values = ("$0x5000,%edx", "$0x7010,%esi", "$0x3100,%edi")
        for order in itertools.permutations(values):
            with self.subTest(order=order):
                asm = "\n".join("%x: mov %s" % (0x1000+5*i,x) for i,x in enumerate(order))
                self.index().build(self.target, asm + "\n100f: call 3000\n1014: ret").require_complete()

    def test_dso_registration_branch_into_partial_argument_setup_is_unresolved(self):
        self.dso_handle()
        for target in ("1005", "100a", "100f"):
            with self.subTest(target=target):
                asm = self.dso_handle() + "\n1015: jmp " + target
                self.assertTrue(self.index().build(self.target, asm).gaps)

    def test_dso_registration_branch_to_complete_setup_remains_valid(self):
        asm = self.dso_handle() + "\n1015: jmp 1000"
        self.index().build(self.target, asm).require_complete()

    def test_dso_registration_reordered_duplicate_argument_not_accepted(self):
        asm = self.dso_handle().replace("100a: mov $0x3100,%edi", "100a: mov $0x3100,%esi")
        self.assertTrue(self.index().build(self.target, asm).gaps)

    def test_dso_registration_reordered_nonimmediate_not_accepted(self):
        asm = self.dso_handle().replace("1005: mov $0x7010,%esi", "1005: mov %r12d,%esi")
        self.assertTrue(self.index().build(self.target, asm).gaps)

    def test_direct_callee_header_whole_not_transitive_or_all_mapped(self):
        self.add_function(function(0x2000, "CSteamStats", "getStatInt", tu=1))
        self.add_function(function(0x3000, "CUnrelated", "update", tu=2))
        result = self.index().build(self.target, "1000: callq 2000 <bogus::getStatType()>\n"
                                                "1005: retq\n2000: callq 3000 <CUnrelated::update()>",
                                    already_shown=["Achievement.h"])
        self.assertEqual(result.headers, ("SteamStats.h",))
        self.assertIn((self.include / "SteamStats.h").read_text(), result.text)
        self.assertIn("float getStatFloat(int);", result.text)
        self.assertNotIn("SHOULD_NOT_APPEAR", result.text)
        self.assertNotIn("getStatType", result.text)
        self.assertNotIn("Direct game call/tail-call 0x3000", result.text)
        self.assertFalse(result.gaps)

    def test_packed_callee_keeps_its_scope_and_exact_overload(self):
        header = ("class __attribute__((packed)) CSteamStats { public: "
                  "int getStatInt(int value); float getStatFloat(int value); };\n")
        self.write_header("SteamStats.h", header)
        callee = function(0x2000, "CSteamStats", "getStatInt", tu=1)
        self.add_function(callee)
        result = self.index().build(self.target, "1000: call 2000")
        self.assertFalse(result.gaps)
        self.assertIn(header, result.text)
        self.db["functions"]["0x2000"] = dict(callee, params="float")
        self.assertTrue(self.index().build(self.target, "1000: call 2000").gaps)

    def test_raw_bytes_asm_tail_call_and_library_exclusion(self):
        self.add_function(function(0x2000, "CSteamStats", "getStatInt", tu=1))
        self.add_function(function(0x3000, "CUnrelated", "update", tu=3))
        result = self.index().build(self.target, "1000: e8 00 00 00 00 callq 3000 <fltk>\n"
                                                "1005: e9 00 00 00 00 jmpq 2000 <tail>\n"
                                                "100a: 75 02 jne 3000 <not_a_call>")
        self.assertEqual(result.headers, ("SteamStats.h",))
        self.assertNotIn("CUnrelated", result.text)

    def test_library_instantiation_inside_game_tu_is_not_a_game_dependency(self):
        self.write_header("StdFake.h", "namespace std { void helper(); } // NOT_GAME\n")
        self.mapping["std"] = "StdFake.h"
        self.add_function(function(0x2000, "std", "helper", tu=0, kind="inline_or_template"))
        result = self.index().build(self.target, "1000: call 2000")
        self.assertEqual(result.headers, ())
        self.assertNotIn("NOT_GAME", result.text)
        self.assertFalse(result.gaps)

    def test_vtable_metadata_is_not_fabricated_as_a_cxx_variable(self):
        data = object_symbol(0x5000, "vtable for CAchievement", size=16)
        data["name"] = "_ZTV12CAchievement"
        self.db["globals"] = [data]
        result = self.index().build(self.target, "1000: mov $0x5008,%rax")
        self.assertFalse(result.gaps)
        self.assertIn("compiler/ABI metadata", result.text)
        self.assertIn("Named data 0x5008: vtable for CAchievement+0x8", result.text)

    def test_vtt_is_compiler_abi_metadata_without_a_source_global(self):
        data = object_symbol(0x5000, "VTT for std::basic_stringstream<char>", size=32)
        data['name'] = '_ZTTSt18basic_stringstreamIcSt11char_traitsIcESaIcEE'
        self.db['globals'] = [data]
        result = self.index().build(self.target, '1000: mov $0x5008,%rax')
        self.assertFalse(result.gaps)
        self.assertIn('compiler/ABI metadata', result.text)
        self.assertIn('VTT for std::basic_stringstream', result.text)

    def test_target_function_local_bss_has_identity_without_a_header_type_guess(self):
        mangled = '_ZN12CAchievement6updateEv'
        self.target['names'] = [mangled]
        raw = '_ZZ' + mangled[2:] + 'E7counter'
        data = object_symbol(0x7000, self.target['demangled'] + '::counter', size=4,
                             bind='local', file='Achievement.cpp')
        data['name'] = raw
        self.db['globals'] = [data]
        self.image.symbols = [SimpleNamespace(name=raw, value=0x7000, size=4, type=1,
                                              bind=0, defined=True, file='Achievement.cpp')]
        result = self.index().build(self.target, '1000: mov $0x7000,%rax')
        self.assertFalse(result.gaps)
        self.assertIn('SHT_NOBITS zero initialization', result.text)
        self.assertIn('C++ type is not inferred', result.text)
        self.assertFalse(self.image.reads)
        for change in ('symbol_name', 'size', 'function', 'owner', 'initialized', 'missing_elf'):
            with self.subTest(change=change):
                db = copy.deepcopy(self.db)
                image = copy.deepcopy(self.image)
                if change == 'symbol_name': image.symbols[0].name = '_ZZanother_functionE7counter'
                elif change == 'size': image.symbols[0].size = 8
                elif change == 'function': db['globals'][0]['demangled'] = 'COther::update()::counter'
                elif change == 'owner': db['globals'][0]['file'] = 'Other.cpp'
                elif change == 'initialized': image.sections[-1].type = 1
                elif change == 'missing_elf': image.symbols = []
                self.assertTrue(self.index(db=db, image=image).build(self.target, '1000: mov $0x7000,%rax').gaps)

    def local_initializer_case(self):
        mangled = '_ZN12CAchievement6updateEv'
        self.target['names'] = [mangled]
        raw = '_ZZ' + mangled[2:] + 'E6values'
        payload = bytes(range(36))
        data = object_symbol(0x5000, self.target['demangled'] + '::values', size=36,
                             bind='local', file='Achievement.cpp')
        data['name'] = raw
        self.db['globals'] = [data]
        self.image.sections[0].contents = payload + bytes(92)
        self.image.symbols = [SimpleNamespace(name=raw, value=0x5000, size=36, type=1,
                                             bind=0, defined=True, file='Achievement.cpp')]
        return payload

    def test_target_local_readonly_initializer_is_complete_not_a_type_guess(self):
        payload = self.local_initializer_case()
        result = self.index().build(self.target, '1000: mov $0x5004,%rax')
        self.assertFalse(result.gaps)
        self.assertIn('Complete initializer (36 bytes): ' + payload.hex(' '), result.text)
        self.assertIn(hashlib.sha256(payload).hexdigest(), result.text)
        self.assertIn('C++ type is not inferred', result.text)
        self.assertIn('not behavior acceptance', result.text)
        self.assertEqual(result.headers, ())
        self.assertIn((0x5000, 36), self.image.reads)

    def test_target_local_initialized_storage_requires_exact_identity_and_bounds(self):
        self.local_initializer_case()
        changes = ('symbol_name', 'elf_size', 'elf_owner', 'elf_bind', 'elf_type',
                   'elf_undefined', 'function', 'mangled_function', 'suffix_length',
                   'owner', 'global', 'missing_elf', 'writable', 'executable',
                   'nobits', 'section_truncated', 'file_truncated', 'relocation',
                   'overlap', 'zero_size', 'oversize')
        for change in changes:
            with self.subTest(change=change):
                db, image = copy.deepcopy(self.db), copy.deepcopy(self.image)
                obj, sym, sec = db['globals'][0], image.symbols[0], image.sections[0]
                if change == 'symbol_name': sym.name = '_ZZotherE6values'
                elif change == 'elf_size': sym.size = 40
                elif change == 'elf_owner': sym.file = 'Other.cpp'
                elif change == 'elf_bind': sym.bind = 1
                elif change == 'elf_type': sym.type = 2
                elif change == 'elf_undefined': sym.defined = False
                elif change == 'function': obj['demangled'] = 'COther::update()::values'
                elif change == 'mangled_function': obj['name'] = sym.name = '_ZZN6COther6updateEvE6values'
                elif change == 'suffix_length': obj['name'] = sym.name = sym.name.replace('E6values', 'E7values')
                elif change == 'owner': obj['file'] = 'Other.cpp'
                elif change == 'global': obj['bind'] = 'global'
                elif change == 'missing_elf': image.symbols = []
                elif change == 'writable': sec.flags = 3
                elif change == 'executable': sec.flags = 6
                elif change == 'nobits': sec.type = 8
                elif change == 'section_truncated': sec.size = 32
                elif change == 'file_truncated': image.segments[0] = (*image.segments[0][:5], 32, *image.segments[0][6:])
                elif change == 'relocation': image.relocs[0x5010] = SimpleNamespace(offset=0x5010, symbol='ptr', type=1)
                elif change == 'overlap': db['globals'].append(object_symbol(0x5010, 'other', size=4))
                elif change == 'zero_size': obj['size'] = sym.size = 0
                elif change == 'oversize': obj['size'] = sym.size = 8193
                result = self.index(db=db, image=image).build(self.target, '1000: mov $0x5000,%rax')
                self.assertNotIn('Complete initializer', result.text)
                if change != 'nobits':
                    self.assertTrue(result.gaps)

    def test_local_initializer_mandatory_context_is_not_truncated(self):
        self.local_initializer_case()
        with self.assertRaises(ContextError):
            self.index().build(self.target, '1000: mov $0x5000,%rax', max_chars=32)

    def imported_data(self, raw, readable, *, address=0x7000, version="GLIBCXX_3.4"):
        # Version comes from the borrowed ELF symbol, not just the DB label.
        data = object_symbol(address, readable, size=32)
        data["name"] = raw + "@@" + version
        self.db["globals"] = [data]
        self.image.symbols = [SimpleNamespace(name=raw + "@@" + version, value=address,
                                              type=1, bind=1, defined=True)]
        self.image.dynsyms = [SimpleNamespace(name=raw, value=address, type=1, bind=1, defined=True)]
        self.image.relocs = {address: SimpleNamespace(offset=address, symbol=raw, type=5)}
        return data

    def test_stdio_streams_require_exact_version_copy_pointer_and_name(self):
        for stream in ("stdin", "stdout", "stderr"):
            for change in (None, "no_copy", "version_only_in_db", "wrong_db_size", "wrong_elf_size", "local", "wrong_name"):
                with self.subTest(stream=stream, change=change):
                    data = self.imported_data(stream, stream + "@@GLIBC_2.2.5", version="GLIBC_2.2.5")
                    data["size"] = 8
                    for symbol in self.image.symbols + self.image.dynsyms:
                        symbol.size = 8
                    if change == "no_copy": self.image.relocs = {}
                    elif change == "version_only_in_db": self.image.symbols[0].name = stream
                    elif change == "wrong_db_size": data["size"] = 4
                    elif change == "wrong_elf_size": self.image.symbols[0].size = 4
                    elif change == "local": data["bind"] = "local"
                    elif change == "wrong_name": data["demangled"] = "game_stderr"
                    result = self.index().build(self.target, "1000: mov $0x7000,%rax")
                    if change is None:
                        result.require_complete()
                        self.assertIn("stdio; borrowed ELF STT_OBJECT + GLIBC_2.2.5", result.text)
                    else:
                        with self.assertRaises(ContextError): result.require_complete()

    def template_data(self, code='j'):
        ctype, address = {'j': ('unsigned int', 0x1426460), 't': ('unsigned short', 0x1426440)}[code]
        raw = '_ZNSbI%sSt11char_traitsI%sESaI%sEE4_Rep20_S_empty_rep_storageE' % (code, code, code)
        label = 'std::basic_string<%s, std::char_traits<%s>, std::allocator<%s> >::_Rep::_S_empty_rep_storage' % (ctype, ctype, ctype)
        data = object_symbol(address, label, bind='?'); data.update(name=raw, section='.bss')
        self.db['globals'] = [data]
        original = '91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b'
        self.db['original_elf_sha256'] = self.image.sha256 = original
        self.image.sections.append(section('.bss', address, b'', flags=3, typ=8, size=32))
        symbol = SimpleNamespace(name=raw, value=address, type=1, bind=10, size=32, defined=True)
        self.image.symbols = [symbol]; self.image.dynsyms = [copy.copy(symbol)]
        return data, address

    def test_pinned_unsigned_string_template_reps(self):
        for code in ('j', 't'):
            with self.subTest(code=code), mock.patch.object(ContextIndex, '_string_template_headers', return_value=True):
                data, address = self.template_data(code)
                result = self.index().build(self.target, '1000: mov $0x%x,%%rax\n1005: mov $0x%x,%%rdx' % (address, address+24))
                result.require_complete()
                self.assertEqual(result.text.count('pinned GNU-unique'), 2)
                self.assertIn('Named data', result.text)
                self.assertNotIn('Referenced data declaration', result.text)
                self.assertFalse(self.image.reads)

    def test_template_rep_evidence_fail_closed(self):
        data, address = self.template_data()
        cases = ['db_hash', 'image_hash', 'label', 'raw', 'db_address', 'db_size', 'db_bind', 'db_owner', 'db_section',
                 'elf_missing', 'dyn_missing', 'elf_duplicate', 'dyn_duplicate', 'elf_bind', 'dyn_bind',
                 'elf_size', 'dyn_size', 'elf_type', 'dyn_type', 'elf_defined', 'dyn_defined',
                 'elf_address', 'dyn_address', 'section_type', 'section_name', 'section_flags', 'section_size', 'copy']
        for change in cases:
            with self.subTest(change=change), mock.patch.object(ContextIndex, '_string_template_headers', return_value=True):
                db, image = copy.deepcopy(self.db), copy.deepcopy(self.image)
                obj = db['globals'][0]
                if change == 'db_hash': db['original_elf_sha256'] = 'wrong'
                elif change == 'image_hash': image.sha256 = 'wrong'
                elif change == 'label': obj['demangled'] = 'CGame::value'
                elif change == 'raw': obj['name'] += '_fake'
                elif change == 'db_address': obj['address'] = hex(address+1)
                elif change == 'db_size': obj['size'] = 24
                elif change == 'db_bind': obj['bind'] = 'weak'
                elif change == 'db_owner': obj['file'] = 'Achievement.cpp'
                elif change == 'db_section': obj['section'] = '.data'
                elif change == 'copy': image.relocs[address] = SimpleNamespace(offset=address, symbol=obj['name'], type=5)
                elif change.startswith('section_'):
                    attr = change.split('_',1)[1]
                    setattr(image.sections[-1], attr, {'type':1,'name':'.data','flags':7,'size':31}[attr])
                else:
                    table, attr = change.split('_',1); symbols = image.symbols if table=='elf' else image.dynsyms
                    if attr=='missing': symbols.clear()
                    elif attr=='duplicate': symbols.append(copy.copy(symbols[0]))
                    else: setattr(symbols[0], {'address':'value'}.get(attr,attr), {'bind':2,'size':24,'type':2,'defined':False,'address':address+1}[attr])
                self.assertIsNone(self.index(db=db,image=image)._string_template_data(obj))
        with mock.patch.object(ContextIndex, '_string_template_headers', return_value=False):
            self.assertIsNone(self.index()._string_template_data(data))

    def test_template_rep_header_hashes_are_required(self):
        cache=self.root/'compiler-cache'; bits=cache/'gcc447/usr/include/c++/4.4.4/bits'; bits.mkdir(parents=True)
        hashes={'basic_string.h':hashlib.sha256(b'declaration').hexdigest(), 'basic_string.tcc':hashlib.sha256(b'definition').hexdigest()}
        with mock.patch.dict(os.environ, {'OTL_DECOMP_CACHE':str(cache)}), mock.patch.object(ContextIndex,'STRING_TEMPLATE_HEADERS',hashes):
            index=self.index(); self.assertFalse(index._string_template_headers())
            (bits/'basic_string.h').write_bytes(b'declaration'); (bits/'basic_string.tcc').write_bytes(b'definition')
            self.assertTrue(index._string_template_headers())
            (bits/'basic_string.tcc').write_bytes(b'changed definition'); self.assertFalse(index._string_template_headers())

    def test_std_library_abi_data_preserves_facts_without_gap_or_declaration(self):
        raw = "_ZNSbIwSt11char_traitsIwESaIwEE4_Rep20_S_empty_rep_storageE"
        name = "std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_S_empty_rep_storage"
        self.imported_data(raw, name + "@@GLIBCXX_3.4")
        result = self.index().build(self.target, "1000: mov $0x7000,%rax\n1005: mov $0x7018,%rax")
        self.assertIs(result.require_complete(), result)
        self.assertIn("Named data 0x7000: " + name, result.text)
        self.assertIn("Named data 0x7018: " + name + "@@GLIBCXX_3.4+0x18", result.text)
        self.assertEqual(result.text.count("library-owned ABI data"), 2)
        self.assertIn("borrowed ELF STT_OBJECT + GLIBCXX_3.4 + matching R_X86_64_COPY", result.text)
        self.assertNotIn("Referenced data declaration", result.text)
        self.assertEqual(self.image.reads, [])  # copied .bss object is not a literal

    def test_actual_std_nested_and_string_alias_namespace_encodings(self):
        cases = [("_ZNSt6locale2id5_S_refcountE", "std::locale::id::_S_refcount"),
                 ("_ZNSs4_Rep20_S_empty_rep_storageE", "std::basic_string<char>::_Rep::_S_empty_rep_storage")]
        for raw, readable in cases:
            with self.subTest(raw=raw):
                self.imported_data(raw, readable)
                result = self.index().build(self.target, "1000: mov $0x7000,%rax")
                result.require_complete()
                self.assertIn("library-owned ABI data (std;", result.text)

    def test_gnu_cxx_library_data_requires_actual_borrowed_symbol_provenance(self):
        self.imported_data("_ZN9__gnu_cxx12__pool_allocIiE9_S_policyE", "__gnu_cxx::__pool_alloc<int>::_S_policy")
        result = self.index().build(self.target, "1000: mov $0x7000,%rax")
        result.require_complete()
        self.assertIn("library-owned ABI data (__gnu_cxx;", result.text)
        self.assertIn("Named data 0x7000: __gnu_cxx::", result.text)
        self.assertNotIn("Referenced data declaration", result.text)

    def test_similar_or_nested_game_names_still_block_missing_declarations(self):
        cases = [("_ZN5CGame20_S_empty_rep_storageE", "CGame::_S_empty_rep_storage@@GLIBCXX_3.4"),
                 ("_ZN8std_game7counterE", "std_game::counter@@GLIBCXX_3.4"),
                 ("_ZN14__gnu_cxx_game7counterE", "__gnu_cxx_game::counter@@GLIBCXX_3.4"),
                 ("_ZN5CGame7counterE", "CGame<std::basic_string<char> >::counter@@GLIBCXX_3.4"),
                 ("_ZN5CGame7counterE", "CGame<__gnu_cxx::allocator<int> >::counter@@GLIBCXX_3.4"),
                 ("_ZN5CGame7counterE", "std::fake_label@@GLIBCXX_3.4"),
                 ("_ZN5CGame7counterE", "__gnu_cxx::fake_label@@GLIBCXX_3.4")]
        for raw, readable in cases:
            with self.subTest(readable=readable):
                self.imported_data(raw, readable)
                result = self.index().build(self.target, "1000: mov $0x7000,%rax")
                self.assertNotIn("library-owned ABI data", result.text)
                self.assertIn("No existing header declaration", result.text)
                with self.assertRaises(ContextError):
                    result.require_complete()

    def test_library_looking_db_labels_without_elf_confirmation_still_block(self):
        self.imported_data("_ZNSt6locale2id5_S_refcountE", "std::locale::id::_S_refcount@@GLIBCXX_3.4")
        self.image.symbols, self.image.dynsyms = [], []
        result = self.index().build(self.target, "1000: mov $0x7000,%rax")
        with self.assertRaises(ContextError):
            result.require_complete()
        self.assertNotIn("library-owned ABI data", result.text)

    def test_library_data_evidence_must_agree_on_address_name_type_binding_and_copy(self):
        raw = "_ZNSt6locale2id5_S_refcountE"
        for change in ("symbol_address", "symbol_name", "symbol_type", "symbol_local", "undefined",
                       "copy_address", "copy_name", "copy_type", "no_copy", "version_only_in_db", "db_local"):
            with self.subTest(change=change):
                data = self.imported_data(raw, "std::locale::id::_S_refcount@@GLIBCXX_3.4")
                symbol, dynamic, reloc = self.image.symbols[0], self.image.dynsyms[0], self.image.relocs[0x7000]
                if change == "symbol_address":
                    symbol.value = dynamic.value = 0x7010
                elif change == "symbol_name":
                    symbol.name = dynamic.name = "_ZNSt6locale2id8_S_otherE@@GLIBCXX_3.4"
                elif change == "symbol_type":
                    symbol.type = dynamic.type = 2
                elif change == "symbol_local":
                    symbol.bind = dynamic.bind = 0
                elif change == "undefined":
                    symbol.defined = dynamic.defined = False
                elif change == "copy_address":
                    reloc.offset = 0x7010
                elif change == "copy_name":
                    reloc.symbol = "_ZN5CGame7counterE"
                elif change == "copy_type":
                    reloc.type = 6
                elif change == "no_copy":
                    self.image.relocs = {}
                elif change == "version_only_in_db":
                    symbol.name = raw
                elif change == "db_local":
                    data.update(bind="local", file="Achievement.cpp")
                result = self.index().build(self.target, "1000: mov $0x7000,%rax")
                with self.assertRaises(ContextError):
                    result.require_complete()
                self.assertNotIn("library-owned ABI data", result.text)

    def test_unversioned_game_definition_in_std_namespace_is_not_blanket_exempt(self):
        self.imported_data("_ZNSt8GameStat7counterE", "std::GameStat::counter", version="GAME_1.0")
        result = self.index().build(self.target, "1000: mov $0x7000,%rax")
        self.assertIn("No existing header declaration", result.text)
        with self.assertRaises(ContextError):
            result.require_complete()

    def test_library_data_does_not_hide_missing_ordinary_game_data_in_same_packet(self):
        self.imported_data("_ZNSs4_Rep20_S_empty_rep_storageE", "std::basic_string<char>::_Rep::_S_empty_rep_storage")
        self.db["globals"].append(object_symbol(0x6000, "gUnknownGameStat", size=4))
        result = self.index().build(self.target, "1000: mov $0x7000,%rax\n1005: mov $0x6000,%rax")
        self.assertIn("library-owned ABI data", result.text)
        self.assertEqual(len(result.gaps), 1)
        self.assertIn("gUnknownGameStat", result.gaps[0])
        with self.assertRaises(ContextError):
            result.require_complete()

    def test_indirect_annotations_do_not_choose_a_header(self):
        self.add_function(function(0x2000, "CUnrelated", "update", tu=2))
        result = self.index().build(self.target, "1000: callq *%rax <CUnrelated::update()>\n1005: retq")
        self.assertEqual(result.headers, ())
        self.assertIn("Indirect call at 0x1000", result.text)
        self.assertNotIn("SHOULD_NOT_APPEAR", result.text)

    def test_numeric_rip_target_and_indexed_interior_named_data(self):
        self.db["globals"] = [object_symbol(0x6000, "g_strStatDefines", size=744, bind="local", file="Achievement.cpp")]
        result = self.index().build(self.target, "1000: mov 0x6004(,%rax,8),%ecx\n"
                                                "1008: mov 0x5ff5(%rip),%eax # 6004 <untrusted+4>\n"
                                                "1010: retq")
        self.assertIn("g_strStatDefines+0x4", result.text)
        self.assertIn("static unsigned char g_strStatDefines[744];", result.text)
        self.assertNotIn("irrelevantData", result.text)
        self.assertNotIn("#ifndef", result.text)
        self.assertNotIn("#define", result.text)
        self.assertEqual(result.text.count("Referenced data declaration"), 1)
        self.assertEqual(result.text.count("Named data 0x6004"), 1)
        self.assertEqual(self.image.reads, [])  # writable table is not a literal
        self.assertFalse(result.gaps)

    def test_duplicate_data_symbols_and_references_are_rendered_once(self):
        data = object_symbol(0x6000, "g_strStatDefines", size=744, bind="local", file="Achievement.cpp")
        self.db["globals"] = [data, dict(data)]
        result = self.index().build(self.target, "1000: mov $0x6004,%rax\n1005: mov $0x6004,%rax")
        self.assertEqual(result.text.count("Named data 0x6004"), 1)
        self.assertEqual(result.text.count("static unsigned char g_strStatDefines[744];"), 1)

    def dso_handle(self):
        self.db["globals"] = [object_symbol(0x5000, "__dso_handle", size=0,
                                             bind="local", file="Other.cpp")]
        self.image.symbols = [SimpleNamespace(name="__dso_handle", value=0x5000,
                                              type=1, bind=0, defined=True, size=0)]
        self.image.plt = {0x3000: "__cxa_atexit"}
        return ("1000: mov $0x5000,%edx\n1005: mov $0x7010,%esi\n"
                "100a: mov $0x3100,%edi\n100f: call 3000 <untrusted_label>\n1014: ret")

    def test_dso_registration_handle_uses_elf_and_plt_not_stt_file_or_annotation(self):
        asm = self.dso_handle()
        result = self.index().build(self.target, asm).require_complete()
        self.assertIn("ELF-proven DSO destruction registration handle", result.text)
        self.assertNotIn("Referenced data declaration", result.text)
        self.assertEqual(result.headers, ())

    def test_dso_registration_handle_repeated_registrations(self):
        asm = self.dso_handle().replace("1014: ret", "1014: mov $0x5000,%edx\n"
               "1019: mov $0x7020,%esi\n101e: mov $0x3200,%edi\n1023: call 3000")
        self.index().build(self.target, asm).require_complete()

    def test_dso_registration_handle_null_object_xor_esi(self):
        asm = self.dso_handle().replace("mov $0x7010,%esi", "xor %esi,%esi")
        self.index().build(self.target, asm).require_complete()
        for invalid in ("xor %edi,%esi", "xor %edx,%edx", "xor %rsi,%rsi"):
            with self.subTest(invalid=invalid):
                with self.assertRaises(ContextError):
                    self.index().build(self.target, asm.replace("xor %esi,%esi", invalid)).require_complete()

    def test_dso_handle_does_not_exempt_additional_nonregistration_reference(self):
        asm = self.dso_handle() + "\n1015: mov $0x5000,%eax"
        with self.assertRaises(ContextError):
            self.index().build(self.target, asm).require_complete()

    def test_dso_registration_handle_requires_actual_elf_identity(self):
        for change in ("missing", "duplicate", "wrong_name", "wrong_address", "wrong_type",
                       "wrong_bind", "undefined", "nonzero_size", "writable", "executable",
                       "db_name", "db_demangled", "db_bind", "db_size"):
            with self.subTest(change=change):
                asm = self.dso_handle()
                self.image.sections[0].flags = 2
                symbol = self.image.symbols[0]
                if change == "missing": self.image.symbols = []
                elif change == "duplicate": self.image.symbols.append(copy.copy(symbol))
                elif change == "wrong_name": symbol.name = "game_handle"
                elif change == "wrong_address": symbol.value += 8
                elif change == "wrong_type": symbol.type = 2
                elif change == "wrong_bind": symbol.bind = 1
                elif change == "undefined": symbol.defined = False
                elif change == "nonzero_size": symbol.size = 8
                elif change == "writable": self.image.sections[0].flags = 3
                elif change == "executable": self.image.sections[0].flags = 6
                elif change == "db_name": self.db["globals"][0]["name"] = "game_handle"
                elif change == "db_demangled": self.db["globals"][0]["demangled"] = "game_handle"
                elif change == "db_bind": self.db["globals"][0]["bind"] = "global"
                elif change == "db_size": self.db["globals"][0]["size"] = 8
                with self.assertRaises(ContextError):
                    self.index().build(self.target, asm).require_complete()

    def test_dso_registration_handle_requires_exact_argument_and_import_sequence(self):
        for change in ("wrong_register", "wrong_second", "clobber", "indirect", "wrong_call",
                       "missing_plt", "wrong_plt", "truncated", "memory_load"):
            with self.subTest(change=change):
                asm = self.dso_handle()
                if change == "wrong_register": asm = asm.replace("%edx", "%esi")
                elif change == "wrong_second": asm = asm.replace("%esi", "%ecx")
                elif change == "clobber": asm = asm.replace("mov $0x7010,%esi", "xor %edx,%edx")
                elif change == "indirect": asm = asm.replace("call 3000 <untrusted_label>", "call *%rax <__cxa_atexit>")
                elif change == "wrong_call": asm = asm.replace("call 3000", "call 3100")
                elif change == "missing_plt": self.image.plt = {}
                elif change == "wrong_plt": self.image.plt[0x3000] = "game_exit"
                elif change == "truncated": asm = asm.split("100a:")[0]
                elif change == "memory_load": asm = asm.replace("$0x5000", "0x5000")
                with self.assertRaises(ContextError):
                    self.index().build(self.target, asm).require_complete()

    def test_dso_registration_handle_does_not_hide_ordinary_missing_data(self):
        asm = self.dso_handle() + "\n1015: mov $0x6000,%eax"
        self.db["globals"].append(object_symbol(0x6000, "gMissing"))
        result = self.index().build(self.target, asm)
        self.assertIn("ELF-proven DSO destruction registration handle", result.text)
        self.assertEqual(len(result.gaps), 1)
        self.assertIn("gMissing", result.gaps[0])

    def test_literal_initialized_string_array_keeps_complete_existing_declaration(self):
        declaration = 'static const std::string icons[] = {"melee", "ranged", "magic"};'
        self.write_header("Icons.h", declaration)
        self.db["globals"] = [object_symbol(0x6000, "icons", size=24, bind="local", file="Achievement.cpp")]
        result = self.index().build(self.target, "1000: mov $0x6008,%rax").require_complete()
        self.assertIn(declaration, result.text)
        self.assertNotIn("NUL-terminated", result.text)
        self.assertEqual(self.image.reads, [])

    def test_literal_initialized_wstring_array_in_namespace(self):
        declaration = 'const std::wstring labels[2] = {L"one", L"two",};'
        self.write_header("Labels.h", 'namespace LABELS { ' + declaration + ' }')
        self.db["globals"] = [object_symbol(0x6000, "LABELS::labels", size=16)]
        result = self.index().build(self.target, "1000: mov $0x6000,%rax").require_complete()
        self.assertIn(declaration, result.text)
        self.assertIn("namespace LABELS", result.text)

    def test_mutable_literal_string_array_keeps_initializer_and_owner_checks(self):
        declaration = 'static std::wstring labels[3] = {L"Fast", L"Box", L""};'
        self.write_header("Labels.h", declaration)
        self.db["globals"] = [object_symbol(0x6000, "labels", size=24,
                                              bind="local", file="Achievement.cpp")]
        result = self.index().build(self.target, "1000: mov $0x6008,%rax").require_complete()
        self.assertIn(declaration, result.text)
        self.assertEqual(self.image.reads, [])
        self.db["globals"][0]["file"] = "Other.cpp"
        with self.assertRaises(ContextError):
            self.index().build(self.target, "1000: mov $0x6008,%rax").require_complete()

    def test_initialized_string_array_does_not_infer_nonliteral_expressions(self):
        for initializer in ('makeName()', 'SOME_MACRO', '"one" + suffix',
                            '{"nested"}', '"one", call()', '"adjacent" "literal"', ''):
            with self.subTest(initializer=initializer):
                self.write_header("Icons.h", 'static const std::string icons[] = {' + initializer + '};')
                self.db["globals"] = [object_symbol(0x6000, "icons", size=24)]
                with self.assertRaises(ContextError):
                    self.index().build(self.target, "1000: mov $0x6000,%rax").require_complete()

    def test_initialized_string_array_inside_function_is_not_global(self):
        self.write_header("Icons.h", 'void hidden() { static const std::string icons[] = {"one"}; }')
        self.db["globals"] = [object_symbol(0x6000, "icons", size=8)]
        with self.assertRaises(ContextError):
            self.index().build(self.target, "1000: mov $0x6000,%rax").require_complete()

    def test_initialized_string_array_preserves_local_owner_guard(self):
        self.write_header("Icons.h", 'static const std::string icons[] = {"one"};')
        self.db["globals"] = [object_symbol(0x6000, "icons", size=8, bind="local", file="Other.cpp")]
        result = self.index().build(self.target, "1000: mov $0x6000,%rax")
        self.assertIn("no same-name declaration substituted", result.text)
        with self.assertRaises(ContextError): result.require_complete()

    def test_initialized_string_array_retains_ordinary_following_declarations(self):
        self.write_header("Icons.h", 'static const std::string icons[] = {"one"}; extern int other;')
        self.db["globals"] = [object_symbol(0x6000, "other", size=4)]
        result = self.index().build(self.target, "1000: mov $0x6000,%rax").require_complete()
        self.assertIn("extern int other;", result.text)
        self.assertNotIn('icons[]', result.text)

    def integer_scalar(self, declaration="static unsigned int version = 23;", value=23, signed=False):
        self.write_header("IntegerScalar.h", declaration)
        raw="_ZL7version"
        self.db["globals"]=[dict(object_symbol(0x5000,raw,size=4,bind="local",file="Achievement.cpp"),demangled="version")]
        self.image=FakeImage(section(".data",0x5000,value.to_bytes(4,"little",signed=signed),flags=3))
        self.image.symbols=[SimpleNamespace(name=raw,value=0x5000,size=4,bind=0,type=1,defined=True,file="Achievement.cpp")]
        return declaration

    def test_gameclient_integer_scalar_exact_initial_bytes_and_boundaries(self):
        for typ,value in (("int",-2147483648),("int",2147483647),("unsigned int",23),("unsigned int",4294967295)):
            with self.subTest(typ=typ,value=value):
                declaration=self.integer_scalar("static "+typ+" version = "+str(value)+";",value,typ=="int")
                result=self.index().build(self.target,"1000: mov $0x5000,%rax").require_complete()
                self.assertIn(declaration,result.text)
                self.assertNotIn("extern unsigned int",result.text)

    def test_gameclient_integer_scalar_rejects_nonliteral_or_out_of_range(self):
        for declaration in ("static unsigned int version = 23u;","static unsigned int version = 0x17;",
                "static unsigned int version = 023;","static unsigned int version = 22+1;",
                "static unsigned int version = VALUE;","static unsigned int version = -1;",
                "static unsigned int version = 4294967296;","static int version = 2147483648;",
                "static int version = -2147483649;","static int version = 23, other;",
                "static long version = 23;","static unsigned int version = "+"9"*5000+";"):
            with self.subTest(declaration=declaration[:100]):
                self.integer_scalar(declaration)
                self.assertTrue(self.index().build(self.target,"1000: mov $0x5000,%rax").gaps)

    def test_gameclient_integer_scalar_requires_exact_native_identity_and_initial_value(self):
        for change in ("bytes","db_size","elf_size","db_binding","elf_binding","elf_type","undefined",
                       "missing_symbol","elf_name","elf_address","elf_owner","db_owner","missing_owner","bss","executable","truncated"):
            with self.subTest(change=change):
                self.integer_scalar();symbol,obj,sec=self.image.symbols[0],self.db["globals"][0],self.image.sections[0]
                if change=="bytes":sec.contents=b"\0"*4
                elif change=="db_size":obj["size"]=8
                elif change=="elf_size":symbol.size=8
                elif change=="db_binding":obj["bind"]="global"
                elif change=="elf_binding":symbol.bind=1
                elif change=="elf_type":symbol.type=2
                elif change=="undefined":symbol.defined=False
                elif change=="missing_symbol":self.image.symbols=[]
                elif change=="elf_name":symbol.name="_other"
                elif change=="elf_address":symbol.value+=4
                elif change=="elf_owner":symbol.file="Other.cpp"
                elif change=="db_owner":obj["file"]="Other.cpp"
                elif change=="missing_owner":obj["file"]=None
                elif change=="bss":sec.type=8
                elif change=="executable":sec.flags=6
                elif change=="truncated":sec.size=3
                self.assertTrue(self.index().build(self.target,"1000: mov $0x5000,%rax").gaps)

    def test_gameclient_integer_scalar_does_not_hide_an_unrelated_gap(self):
        self.integer_scalar();self.add_function(function(0x3000,"CUnrelated","missing",tu=2))
        result=self.index().build(self.target,"1000: mov $0x5000,%rax\n1005: call 3000")
        self.assertTrue(result.gaps);self.assertIn("CUnrelated", ";".join(result.gaps))

    def integer_array(self, declaration=None, *, namespace=False):
        declaration = declaration or "static const int slots[5] = {4, 2, 6, 3, 5};"
        source = "namespace W { " + declaration + " }" if namespace else declaration
        self.write_header("Slots.h", source)
        raw = "_ZN1WL5slotsE" if namespace else "_ZL5slots"
        obj = dict(object_symbol(0x5000, raw, size=20, bind="local", file="Achievement.cpp"),
                   demangled="W::slots" if namespace else "slots")
        self.db["globals"] = [obj]
        data = b"".join(n.to_bytes(4, "little", signed=True) for n in (4, 2, 6, 3, 5))
        self.image = FakeImage(section(".rodata", 0x5000, data))
        self.image.symbols = [SimpleNamespace(name=raw, value=0x5000, size=20,
                                              bind=0, type=1, defined=True, file="Achievement.cpp")]
        return declaration

    def test_literal_int_array_preserves_complete_internal_declaration(self):
        declaration = self.integer_array()
        result = self.index().build(self.target, "1000: mov $0x5008,%rax").require_complete()
        self.assertIn(declaration, result.text)
        self.assertNotIn("extern", result.text)
        self.assertNotIn("NUL-terminated", result.text)

    def test_literal_int_array_namespace_and_signed_boundaries(self):
        declaration = self.integer_array("static const int slots[5] = {-2147483648, 2147483647, -1, 0, 5,};", namespace=True)
        data = b"".join(n.to_bytes(4, "little", signed=True) for n in (-2147483648, 2147483647, -1, 0, 5))
        self.image.sections[0].contents = data
        result = self.index().build(self.target, "1000: mov $0x5000,%rax").require_complete()
        self.assertIn(declaration, result.text)
        self.assertIn("namespace W", result.text)

    def test_literal_int_array_rejects_unknown_or_malformed_declarations(self):
        for declaration in (
                "static const int slots[5] = {4, 2, 6, 3};",
                "static const int slots[5] = {4, 2, 6, 3, 5, 7};",
                "static const int slots[5] = {4, 2, UNKNOWN, 3, 5};",
                "static const int slots[5] = {4, 2, call(), 3, 5};",
                "static const int slots[5] = {4, 2, 3+3, 3, 5};",
                "static const int slots[5] = {4, 2, {6}, 3, 5};",
                "static const int slots[5] = {4, 2, 06, 3, 5};",
                "static const int slots[5] = {4, 2, 0x6, 3, 5};",
                "static const int slots[5] = {4, 2, 6u, 3, 5};",
                'static const int slots[5] = {4, 2, "6", 3, 5};',
                "static const int slots[5] = {4, 2, 2147483648, 3, 5};",
                "static const int slots[5] = {4, 2, -2147483649, 3, 5};",
                "static const int slots[5] = {4, 2, " + "9" * 5000 + ", 3, 5};",
                "static const int slots[] = {4, 2, 6, 3, 5};",
                "static const int slots[SIZE] = {4, 2, 6, 3, 5};",
                "static const int slots[0] = {};",
                "static const int slots[5000] = {4, 2, 6, 3, 5};",
                "static const int slots[5] = {4, 2, 6, 3, 5}, other;",
                "static int slots[5] = {4, 2, 6, 3, 5};",
                "extern const int slots[5] = {4, 2, 6, 3, 5};",
                "static const unsigned int slots[5] = {4, 2, 6, 3, 5};",
                "static const int slots[5] = {4, 2, 6, 3, 5}"):
            with self.subTest(declaration=declaration[:100]):
                self.integer_array(declaration)
                with self.assertRaises(ContextError):
                    self.index().build(self.target, "1000: mov $0x5000,%rax").require_complete()

    def test_literal_int_array_rejects_wrong_elf_or_db_evidence(self):
        for change in ("bytes", "db_size", "elf_size", "db_binding", "elf_binding", "elf_type",
                       "undefined", "missing_symbol", "elf_name", "elf_address", "elf_owner",
                       "db_owner", "missing_owner", "writable", "executable", "bss", "truncated"):
            with self.subTest(change=change):
                self.integer_array()
                symbol, obj, sec = self.image.symbols[0], self.db["globals"][0], self.image.sections[0]
                if change == "bytes": sec.contents = b"\0" * 20
                elif change == "db_size": obj["size"] = 24
                elif change == "elf_size": symbol.size = 24
                elif change == "db_binding": obj["bind"] = "global"
                elif change == "elf_binding": symbol.bind = 1
                elif change == "elf_type": symbol.type = 2
                elif change == "undefined": symbol.defined = False
                elif change == "missing_symbol": self.image.symbols = []
                elif change == "elf_name": symbol.name = "_other"
                elif change == "elf_address": symbol.value += 4
                elif change == "elf_owner": symbol.file = "Other.cpp"
                elif change == "db_owner": obj["file"] = "Other.cpp"
                elif change == "missing_owner": obj["file"] = None
                elif change == "writable": sec.flags = 3
                elif change == "executable": sec.flags = 6
                elif change == "bss": sec.type = 8
                elif change == "truncated": sec.size = 16
                with self.assertRaises(ContextError):
                    self.index().build(self.target, "1000: mov $0x5000,%rax").require_complete()

    def test_literal_int_array_rejects_body_class_anonymous_scope(self):
        for wrapper in ("void hidden() { %s }", "class Hidden { %s };", "namespace { %s }"):
            with self.subTest(wrapper=wrapper):
                declaration = self.integer_array()
                self.write_header("Slots.h", wrapper % declaration)
                with self.assertRaises(ContextError):
                    self.index().build(self.target, "1000: mov $0x5000,%rax").require_complete()

    def scalar_array(self, scalar_type, *, namespace=False):
        self.integer_array(namespace=namespace)
        if scalar_type == "bool":
            declaration = "static const bool slots[5] = {true, false, true, true, false,};"
            data = bytes((1, 0, 1, 1, 0))
        else:
            declaration = "static const float slots[5] = {0.1f, 0.2f, 0.4f, 0.8f, -0.0f};"
            data = bytes.fromhex("cdcccc3dcdcc4c3ecdcccc3ecdcc4c3f00000080")
        self.write_header("Slots.h", "namespace W { " + declaration + " }" if namespace else declaration)
        self.db["globals"][0]["size"] = len(data)
        symbol = self.image.symbols[0]
        symbol.size = len(data)
        self.image = FakeImage(section(".rodata", 0x5000, data))
        self.image.symbols = [symbol]
        return declaration

    def test_literal_bool_and_float_arrays_preserve_source_namespace_and_interior_references(self):
        for scalar_type in ("bool", "float"):
            for namespace in (False, True):
                with self.subTest(scalar_type=scalar_type, namespace=namespace):
                    declaration = self.scalar_array(scalar_type, namespace=namespace)
                    result = self.index().build(self.target, "1000: mov $0x5004,%rax").require_complete()
                    self.assertIn(declaration, result.text)
                    self.assertNotIn("extern", result.text)
                    if namespace: self.assertIn("namespace W", result.text)

    def test_float_literal_rounding_is_exact_even_at_double_rounding_boundaries(self):
        for token, word in (
                ("0.1f", 0x3dcccccd), ("-0.0F", 0x80000000),
                ("1.000000059604644775390625f", 0x3f800000),
                ("1.000000059604644775390626f", 0x3f800001),
                ("1.000000178813934326171875f", 0x3f800002),
                ("1.0e-45f", 1), ("-1.0e-46f", 0x80000000),
                ("3.4028234e38f", 0x7f7fffff)):
            with self.subTest(token=token):
                self.assertEqual(_float32_literal_bytes(token), word.to_bytes(4, "little"))
        for token in ("1.0e39f", "1.0e999f", "nanf", "inff", "0.1", "1f", "0x1.0p0f",
                      "1.0f+0.1f", "0.1ff", "01.0f", "-" + "9" * 5000 + ".0f"):
            with self.subTest(token=token[:100]):
                self.assertIsNone(_float32_literal_bytes(token))

    def test_literal_scalar_arrays_reject_partial_nonliteral_or_unsupported_initializers(self):
        for scalar_type, values in (
                ("bool", ("true,false,true,false", "true,false,true,false,true,false",
                          "true,0,true,false,true", "true,BOOL,true,false,true",
                          "true,!false,true,false,true", "true,bool(1),true,false,true",
                          "true,{false},true,false,true", "true,true,true,true,true,,")),
                ("float", ("0.1f,0.2f,0.4f,0.8f", "0.1f,0.2f,0.4f,0.8f,0.0f,1.0f",
                           "0.1f,0.2f,0.4f,0.8f,UNKNOWN", "0.1f,0.2f,0.4f,0.8f,call()",
                           "0.1f,0.2f,0.4f,0.8f,0.0", "0.1f,0.2f,0.4f,0.8f,1.0e39f"))):
            for initializer in values:
                with self.subTest(scalar_type=scalar_type, initializer=initializer):
                    self.scalar_array(scalar_type)
                    self.write_header("Slots.h", "static const " + scalar_type + " slots[5] = {" + initializer + "};")
                    with self.assertRaises(ContextError):
                        self.index().build(self.target, "1000: mov $0x5000,%rax").require_complete()
            for wrapper in ("void hidden() { %s }", "class Hidden { %s };", "namespace { %s }",
                            "%s other;", "%s"):
                with self.subTest(scalar_type=scalar_type, wrapper=wrapper):
                    declaration = self.scalar_array(scalar_type)
                    invalid = declaration.rstrip(";") if wrapper == "%s" else declaration
                    if wrapper == "%s other;": invalid = declaration[:-1] + ","
                    self.write_header("Slots.h", wrapper % invalid)
                    with self.assertRaises(ContextError):
                        self.index().build(self.target, "1000: mov $0x5000,%rax").require_complete()

    def test_literal_scalar_arrays_require_exact_readonly_elf_identity_and_bytes(self):
        for scalar_type in ("bool", "float"):
            for change in ("bytes", "db_size", "elf_size", "db_binding", "elf_binding", "elf_type",
                           "undefined", "missing_symbol", "elf_name", "elf_address", "elf_owner",
                           "db_owner", "missing_owner", "writable", "executable", "bss", "truncated"):
                with self.subTest(scalar_type=scalar_type, change=change):
                    self.scalar_array(scalar_type)
                    symbol, obj, sec = self.image.symbols[0], self.db["globals"][0], self.image.sections[0]
                    if change == "bytes": sec.contents = b"\0" * sec.size
                    elif change == "db_size": obj["size"] += 1
                    elif change == "elf_size": symbol.size += 1
                    elif change == "db_binding": obj["bind"] = "global"
                    elif change == "elf_binding": symbol.bind = 1
                    elif change == "elf_type": symbol.type = 2
                    elif change == "undefined": symbol.defined = False
                    elif change == "missing_symbol": self.image.symbols = []
                    elif change == "elf_name": symbol.name = "_other"
                    elif change == "elf_address": symbol.value += 1
                    elif change == "elf_owner": symbol.file = "Other.cpp"
                    elif change == "db_owner": obj["file"] = "Other.cpp"
                    elif change == "missing_owner": obj["file"] = None
                    elif change == "writable": sec.flags = 3
                    elif change == "executable": sec.flags = 6
                    elif change == "bss": sec.type = 8
                    elif change == "truncated": sec.size -= 1
                    with self.assertRaises(ContextError):
                        self.index().build(self.target, "1000: mov $0x5000,%rax").require_complete()

    def test_literal_int_array_keeps_following_declaration_and_unrelated_gap(self):
        declaration = self.integer_array()
        self.write_header("Slots.h", declaration + " extern int other;")
        self.db["globals"].extend([object_symbol(0x6000, "other", size=4), object_symbol(0x7000, "missing", size=4)])
        result = self.index().build(self.target, "1000: mov $0x5000,%rax\n1005: mov $0x6000,%rax\n100a: mov $0x7000,%rax")
        self.assertIn(declaration, result.text)
        self.assertIn("extern int other;", result.text)
        self.assertEqual(len(result.gaps), 1)
        self.assertIn("missing", result.gaps[0])

    def asm_wstring(self):
        declaration='extern std::wstring gameHomePath __asm__("_ZN10LinuxUtilsL12gameHomePathE");'
        self.write_header('Paths.h','namespace LinuxUtils { '+declaration+' }')
        obj=object_symbol(0x7000,'_ZN10LinuxUtilsL12gameHomePathE',size=8,bind='local',file='Achievement.cpp')
        obj['demangled']='LinuxUtils::gameHomePath';self.db['globals']=[obj]
        self.image.symbols=[SimpleNamespace(name=obj['name'],value=0x7000,size=8,bind=0,type=1,defined=True,file='Achievement.cpp')]
        return declaration

    def test_explicit_wstring_asm_label_preserves_original_namespace_and_storage(self):
        declaration=self.asm_wstring()
        result=self.index().build(self.target,'1000: mov $0x7000,%rax').require_complete()
        self.assertIn(declaration,result.text);self.assertIn('namespace LinuxUtils',result.text)

    def test_explicit_wstring_asm_label_rejects_wrong_identity_or_storage(self):
        for change in ('alias','db_size','elf_size','db_bind','elf_bind','elf_type','undefined','owner',
                       'missing','not_bss','readonly','short','wrong_type','body','class','anonymous'):
            with self.subTest(change=change):
                declaration=self.asm_wstring();obj=self.db['globals'][0];symbol=self.image.symbols[0]
                if change=='alias':self.write_header('Paths.h','namespace LinuxUtils { '+declaration.replace('L12gameHomePathE','L12gameTempPathE')+' }')
                elif change=='db_size':obj['size']=16
                elif change=='elf_size':symbol.size=16
                elif change=='db_bind':obj['bind']='global'
                elif change=='elf_bind':symbol.bind=1
                elif change=='elf_type':symbol.type=2
                elif change=='undefined':symbol.defined=False
                elif change=='owner':obj['file']='Other.cpp'
                elif change=='missing':self.image.symbols=[]
                elif change in ('not_bss','readonly','short'):
                    sec=self.image.sections[-1]
                    if change=='not_bss':sec.type=1
                    elif change=='readonly':sec.flags=2
                    else:sec.size=4
                elif change=='wrong_type':self.write_header('Paths.h','namespace LinuxUtils { '+declaration.replace('std::wstring','int')+' }')
                else:
                    wrapper={'body':'namespace LinuxUtils { void hidden() { %s } }',
                             'class':'namespace LinuxUtils { class Hidden { %s }; }',
                             'anonymous':'namespace { %s }'}[change]
                    self.write_header('Paths.h',wrapper%declaration)
                with self.assertRaises(ContextError):self.index().build(self.target,'1000: mov $0x7000,%rax').require_complete()
    def test_string_list_literal_growth_is_existing_data_not_function(self):
        declaration = 'static TArrayList<std::wstring> names(10);'
        self.write_header("Names.h", declaration)
        self.db["globals"] = [object_symbol(0x6000, "names", size=24, bind="local", file="Achievement.cpp")]
        result = self.index().build(self.target, "1000: mov $0x6008,%rax").require_complete()
        self.assertIn(declaration, result.text)
        self.assertEqual(self.image.reads, [])
        self.db["globals"][0]["file"] = "Other.cpp"
        with self.assertRaises(ContextError):
            self.index().build(self.target, "1000: mov $0x6008,%rax").require_complete()

    def test_string_list_does_not_promote_function_macro_or_local_storage(self):
        self.db["globals"] = [object_symbol(0x6000, "names", size=24)]
        for declaration in ('TArrayList<std::wstring> names(unsigned int growth);',
                            'static TArrayList<std::wstring> names(GROWTH);',
                            'void f() { static TArrayList<std::wstring> names(10); }'):
            self.write_header("Names.h", declaration)
            with self.subTest(declaration=declaration), self.assertRaises(ContextError):
                self.index().build(self.target, "1000: mov $0x6008,%rax").require_complete()

    def sdk_header(self, name, source):
        directory = self.root / "third_party/cegui-0.6.2/include"
        directory.mkdir(parents=True, exist_ok=True)
        (directory / name).write_text(source)
        ContextIndex.CEGUI_HEADER_SHA256.setdefault(name, hashlib.sha256(source.encode()).hexdigest())

    def sdk_object(self, label, raw, size):
        self.db["globals"] = [dict(object_symbol(0x7000, raw, size=size), demangled=label)]
        self.image.sections[-1].size = 512
        self.image.symbols = [SimpleNamespace(name=raw, value=0x7000, size=size,
                                              bind=1, type=1, defined=True)]
        self.image.relocs = {0x7000: SimpleNamespace(type=5, offset=0x7000, symbol=raw)}

    def sdk_event(self):
        label, raw = "CEGUI::Window::EventMouseMove", "_ZN5CEGUI6Window14EventMouseMoveE"
        self.sdk_object(label, raw, 176)
        self.sdk_header("CEGUIWindow.h", "namespace CEGUI { class CEGUIEXPORT Window { public: static const String EventMouseMove; }; }")

    def test_sdk_event_requires_real_declaration_and_copy_identity(self):
        self.sdk_event()
        result = self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()
        self.assertIn("CEGUI0.6.2 SDK declaration static const String EventMouseMove;", result.text)
        self.assertIn("CEGUIWindow.h SHA256", result.text)
        self.assertNotIn("Referenced data declaration", result.text)

    def test_sdk_npos_has_its_own_exact_declaration_and_size(self):
        self.sdk_object("CEGUI::String::npos", "_ZN5CEGUI6String4nposE", 8)
        self.sdk_header("CEGUIString.h", "namespace CEGUI { class CEGUIEXPORT String { public: static const size_type npos; }; }")
        self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()
        self.db["globals"][0]["size"] = self.image.symbols[0].size = 4
        with self.assertRaises(ContextError): self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()

    def test_sdk_singleton_requires_template_and_actual_owner_inheritance(self):
        self.sdk_object("CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton",
                        "_ZN5CEGUI9SingletonINS_15ImagesetManagerEE12ms_SingletonE", 8)
        self.sdk_header("CEGUISingleton.h", "namespace CEGUI { template<typename T> class Singleton { protected: static T* ms_Singleton; }; }")
        self.sdk_header("CEGUIImagesetManager.h", "namespace CEGUI { class CEGUIEXPORT ImagesetManager : public Singleton<ImagesetManager> {}; }")
        self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()
        self.sdk_header("CEGUIImagesetManager.h", "namespace CEGUI { class ImagesetManager : public Singleton<OtherManager> {}; }")
        with self.assertRaises(ContextError): self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()

    def test_sdk_font_and_scheme_singletons_require_pinned_owner_and_copy(self):
        for owner in ("FontManager", "SchemeManager"):
            with self.subTest(owner=owner):
                self.sdk_object("CEGUI::Singleton<CEGUI::" + owner + ">::ms_Singleton",
                                "_ZN5CEGUI9SingletonINS_" + str(len(owner)) + owner + "EE12ms_SingletonE", 8)
                self.sdk_header("CEGUISingleton.h", "namespace CEGUI { template<typename T> class Singleton { protected: static T* ms_Singleton; }; }")
                name = "CEGUI" + owner + ".h"
                self.sdk_header(name, "namespace CEGUI { class CEGUIEXPORT " + owner + " : public Singleton<" + owner + "> {}; }")
                self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()
                self.image.relocs = {}
                with self.assertRaises(ContextError):
                    self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()

    def ogre_data_setup(self):
        raw = "_ZN4Ogre20ResourceGroupManager27DEFAULT_RESOURCE_GROUP_NAMEE"
        self.sdk_object("Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME", raw, 8)
        cache = self.root / "cache"
        sdk = cache / "gcc447/ogre-1.6.5/ogre/OgreMain/include"
        sdk.mkdir(parents=True, exist_ok=True)
        sources = {
            "OgreResourceGroupManager.h": "namespace Ogre { class _OgreExport ResourceGroupManager { OGRE_AUTO_MUTEX public: static String DEFAULT_RESOURCE_GROUP_NAME; }; }",
            "OgrePrerequisites.h": "namespace Ogre { typedef std::string _StringBase; typedef _StringBase String; }",
            "OgrePlatform.h": "// reviewed platform input\n",
            "OgreConfig.h": "// reviewed default configuration\n",
        }
        for name, value in sources.items():
            (sdk / name).write_text(value)
        configuration = self.root / "decomp/config.json"
        configuration.write_text('{"cflags":["-O2"]}')
        pins = {name: hashlib.sha256(value.encode()).hexdigest() for name, value in sources.items()}
        for patch in (mock.patch.dict(ContextIndex.OGRE_HEADER_SHA256, pins, clear=True),
                      mock.patch.object(ContextIndex, "OGRE_CONFIG_SHA256", hashlib.sha256(configuration.read_bytes()).hexdigest()),
                      mock.patch.dict(os.environ, {"OTL_DECOMP_CACHE": str(cache)})):
            patch.start(); self.addCleanup(patch.stop)
        return sdk, configuration

    def test_ogre_default_group_uses_exact_sdk_declaration_and_copy(self):
        self.ogre_data_setup()
        result = self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()
        self.assertIn("OGRE1.6.5 SDK declaration static String DEFAULT_RESOURCE_GROUP_NAME", result.text)
        self.assertNotIn("Referenced data declaration", result.text)

    def test_ogre_default_group_rejects_copy_identity_and_size_changes(self):
        self.ogre_data_setup()
        self.image.relocs = {}
        with self.assertRaises(ContextError): self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()
        self.image.relocs = {0x7000: SimpleNamespace(type=5, offset=0x7000, symbol="different")}
        with self.assertRaises(ContextError): self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()
        self.image.relocs[0x7000].symbol = self.db["globals"][0]["name"]
        self.image.symbols[0].size = self.db["globals"][0]["size"] = 4
        with self.assertRaises(ContextError): self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()

    def test_ogre_default_group_rejects_unreviewed_configuration(self):
        sdk, configuration = self.ogre_data_setup()
        configuration.write_text('{"cflags":["-DOGRE_WCHAR_T_STRINGS=1"]}')
        with self.assertRaises(ContextError): self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()

    def test_ogre_default_group_rejects_changed_header_pin(self):
        sdk, _ = self.ogre_data_setup()
        (sdk / "OgreConfig.h").write_text("#define HAVE_CONFIG_H 1\n")
        with self.assertRaises(ContextError): self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()

    def test_ogre_default_group_rejects_wrong_declaration_owner_and_type(self):
        sdk, _ = self.ogre_data_setup()
        for value in ("namespace Ogre { class Other { public: static String DEFAULT_RESOURCE_GROUP_NAME; }; }",
                      "namespace Other { class ResourceGroupManager { public: static String DEFAULT_RESOURCE_GROUP_NAME; }; }",
                      "namespace Ogre { class ResourceGroupManager { public: static int DEFAULT_RESOURCE_GROUP_NAME; }; }"):
            (sdk / "OgreResourceGroupManager.h").write_text(value)
            ContextIndex.OGRE_HEADER_SHA256["OgreResourceGroupManager.h"] = hashlib.sha256(value.encode()).hexdigest()
            with self.assertRaises(ContextError): self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()

    def test_ogre_default_group_rejects_non_bss_and_readonly_objects(self):
        self.ogre_data_setup()
        self.image.sections[-1].type = 1
        with self.assertRaises(ContextError): self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()
        self.image.sections[-1].type = 8; self.image.sections[-1].flags = 2
        with self.assertRaises(ContextError): self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()

    def test_ogre_default_group_rejects_sdk_symlink_escape(self):
        sdk, _ = self.ogre_data_setup()
        path = sdk / "OgreResourceGroupManager.h"
        outside = self.root / "outside-ogre.h"
        outside.write_bytes(path.read_bytes());path.unlink();path.symlink_to(outside)
        with self.assertRaises(ContextError): self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()


    def ogre_value_setup(self, kind="Vector3"):
        sdk, configuration = self.ogre_data_setup()
        values = {
            "OgreMath.h": "namespace Ogre { class _OgreExport Math { public: static const Real PI; static const Real TWO_PI; static const Real POS_INFINITY; static const Real fRad2Deg; static const Real fDeg2Rad; }; }",
            "OgrePrerequisites.h": "namespace Ogre { typedef float Real; typedef std::string _StringBase; typedef _StringBase String; }",
            "OgrePlatform.h": "// pinned platform\n",
            "OgreConfig.h": "#define OGRE_DOUBLE_PRECISION 0\n",
            "OgreVector3.h": "namespace Ogre { class _OgreExport Vector3 { public: Real x,y,z; static const Vector3 ZERO; static const Vector3 UNIT_Y; static const Vector3 UNIT_X; static const Vector3 UNIT_SCALE; static const Vector3 UNIT_Z; static const Vector3 NEGATIVE_UNIT_Y; }; }",
            "OgreMatrix4.h": "namespace Ogre { class _OgreExport Matrix4 { public: Real m[4][4]; static const Matrix4 IDENTITY; }; }",
            "OgreQuaternion.h": "namespace Ogre { class _OgreExport Quaternion { public: Real w,x,y,z; static const Quaternion IDENTITY; }; }",
            "OgreString.h": "namespace Ogre { class _OgreExport StringUtil { public: static const String BLANK; }; }",
            "OgreColourValue.h": "namespace Ogre { class _OgreExport ColourValue { public: Real r,g,b,a; static const ColourValue White; static const ColourValue Black; static const ColourValue ZERO; }; }",
            "OgreMovableObject.h": "namespace Ogre { class _OgreExport MovableObject { protected: static uint32 msDefaultVisibilityFlags; }; }",
            "OgreSceneManager.h": "namespace Ogre { class _OgreExport SceneManager { public: static uint32 WORLD_GEOMETRY_TYPE_MASK; }; }",
        }
        for name, value in values.items(): (sdk / name).write_text(value)
        pins = {name: hashlib.sha256(value.encode()).hexdigest() for name, value in values.items()}
        patch = mock.patch.dict(ContextIndex.OGRE_VALUE_HEADER_SHA256, pins, clear=True)
        patch.start(); self.addCleanup(patch.stop)
        identities = {
            "PI": ("Ogre::Math::PI", "_ZN4Ogre4Math2PIE", 4),
            "TwoPI": ("Ogre::Math::TWO_PI", "_ZN4Ogre4Math6TWO_PIE", 4),
            "WorldMask": ("Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK", "_ZN4Ogre12SceneManager24WORLD_GEOMETRY_TYPE_MASKE", 4),
            "UnitZ": ("Ogre::Vector3::UNIT_Z", "_ZN4Ogre7Vector36UNIT_ZE", 12),
            "Rad2Deg": ("Ogre::Math::fRad2Deg", "_ZN4Ogre4Math8fRad2DegE", 4),
            "Deg2Rad": ("Ogre::Math::fDeg2Rad", "_ZN4Ogre4Math8fDeg2RadE", 4),
            "UnitX": ("Ogre::Vector3::UNIT_X", "_ZN4Ogre7Vector36UNIT_XE", 12),
            "UnitScale": ("Ogre::Vector3::UNIT_SCALE", "_ZN4Ogre7Vector310UNIT_SCALEE", 12),
            "ColourZero": ("Ogre::ColourValue::ZERO", "_ZN4Ogre11ColourValue4ZEROE", 16),
            "UnitY": ("Ogre::Vector3::UNIT_Y", "_ZN4Ogre7Vector36UNIT_YE", 12),
            "NegativeUnitY": ("Ogre::Vector3::NEGATIVE_UNIT_Y", "_ZN4Ogre7Vector315NEGATIVE_UNIT_YE", 12),
            "Infinity": ("Ogre::Math::POS_INFINITY", "_ZN4Ogre4Math12POS_INFINITYE", 4),
            "Vector3": ("Ogre::Vector3::ZERO", "_ZN4Ogre7Vector34ZEROE", 12),
            "Matrix4": ("Ogre::Matrix4::IDENTITY", "_ZN4Ogre7Matrix48IDENTITYE", 64),
            "Quaternion": ("Ogre::Quaternion::IDENTITY", "_ZN4Ogre10Quaternion8IDENTITYE", 16),
            "StringUtil": ("Ogre::StringUtil::BLANK", "_ZN4Ogre10StringUtil5BLANKE", 8),
            "White": ("Ogre::ColourValue::White", "_ZN4Ogre11ColourValue5WhiteE", 16),
            "Black": ("Ogre::ColourValue::Black", "_ZN4Ogre11ColourValue5BlackE", 16),
            "Visibility": ("Ogre::MovableObject::msDefaultVisibilityFlags", "_ZN4Ogre13MovableObject24msDefaultVisibilityFlagsE", 4),
        }
        self.sdk_object(*identities[kind])
        return sdk, configuration

    def test_ogre_values_exact_constants_and_interior_references(self):
        for kind, size in (("PI",4),("TwoPI",4),("WorldMask",4),("Vector3",12),("Quaternion",16),("StringUtil",8),("Matrix4",64),("UnitY",12),("UnitX",12),("UnitScale",12),("ColourZero",16),("Infinity",4),("UnitZ",12),("Rad2Deg",4),("Deg2Rad",4),("White",16),("Black",16),("Visibility",4),("NegativeUnitY",12)):
            with self.subTest(kind=kind):
                self.ogre_value_setup(kind)
                for offset in range(0,size,4):
                    result=self.index().build(self.target,"1000: mov $%#x,%%rax"%(0x7000+offset)).require_complete()
                    self.assertIn("exact ELF object/COPY identity",result.text)
                    self.assertIn("pinned float/narrow-string profile",result.text)
                    self.assertNotIn("Referenced data declaration",result.text)

    def test_missile_constants_reject_metadata_mismatches(self):
        for kind in ("PI", "TwoPI", "WorldMask", "UnitY", "Infinity", "UnitZ", "Rad2Deg", "Deg2Rad", "White", "Black", "Visibility", "NegativeUnitY", "UnitX", "UnitScale", "ColourZero"):
            for change in ("no_copy", "wrong_copy", "no_symbol", "wrong_size", "wrong_db_size", "wrong_type", "wrong_label", "readonly", "short"):
                with self.subTest(kind=kind,change=change):
                    self.ogre_value_setup(kind)
                    if change=="no_copy": self.image.relocs={}
                    elif change=="wrong_copy": self.image.relocs[0x7000].symbol="wrong"
                    elif change=="no_symbol": self.image.symbols=[]
                    elif change=="wrong_size": self.image.symbols[0].size=32
                    elif change=="wrong_db_size": self.db["globals"][0]["size"]=32
                    elif change=="wrong_type": self.image.symbols[0].type=2
                    elif change=="wrong_label": self.db["globals"][0]["demangled"]="Ogre::Other::FAKE"
                    elif change=="readonly": self.image.sections[-1].flags=2
                    elif change=="short": self.image.sections[-1].size=1
                    with self.assertRaises(ContextError):self.index().build(self.target,"1000: mov $0x7000,%rax").require_complete()

    def test_missile_constants_reject_declaration_mismatches(self):
        for kind,header,owner,typ,member in (("UnitX","OgreVector3.h","Vector3","Vector3","UNIT_X"),("UnitScale","OgreVector3.h","Vector3","Vector3","UNIT_SCALE"),("ColourZero","OgreColourValue.h","ColourValue","ColourValue","ZERO"),("PI","OgreMath.h","Math","Real","PI"),("TwoPI","OgreMath.h","Math","Real","TWO_PI"),("Black","OgreColourValue.h","ColourValue","ColourValue","Black"),("NegativeUnitY","OgreVector3.h","Vector3","Vector3","NEGATIVE_UNIT_Y"),("UnitY","OgreVector3.h","Vector3","Vector3","UNIT_Y"),("Infinity","OgreMath.h","Math","Real","POS_INFINITY"),("UnitZ","OgreVector3.h","Vector3","Vector3","UNIT_Z"),("Rad2Deg","OgreMath.h","Math","Real","fRad2Deg"),("Deg2Rad","OgreMath.h","Math","Real","fDeg2Rad")):
            for declaration in ("static {typ} {member};", "static const int {member};", "static const {typ} WRONG;", "static const {typ} {member}; static const {typ} {member};"):
                with self.subTest(kind=kind,declaration=declaration):
                    sdk,_=self.ogre_value_setup(kind)
                    source="namespace Ogre { class "+owner+" { public: "+declaration.format(typ=typ,member=member)+" }; }"
                    (sdk/header).write_text(source);ContextIndex.OGRE_VALUE_HEADER_SHA256[header]=hashlib.sha256(source.encode()).hexdigest()
                    with self.assertRaises(ContextError):self.index().build(self.target,"1000: mov $0x7000,%rax").require_complete()

    def test_world_mask_rejects_declaration_mismatches(self):
        for declaration in ("static const uint32 WORLD_GEOMETRY_TYPE_MASK;", "static float WORLD_GEOMETRY_TYPE_MASK;", "static uint32 WRONG;", "static uint32 WORLD_GEOMETRY_TYPE_MASK; static uint32 WORLD_GEOMETRY_TYPE_MASK;"):
            with self.subTest(declaration=declaration):
                sdk,_=self.ogre_value_setup("WorldMask")
                source="namespace Ogre { class SceneManager { public: "+declaration+" }; }"
                (sdk/"OgreSceneManager.h").write_text(source);ContextIndex.OGRE_VALUE_HEADER_SHA256["OgreSceneManager.h"]=hashlib.sha256(source.encode()).hexdigest()
                with self.assertRaises(ContextError):self.index().build(self.target,"1000: mov $0x7000,%rax").require_complete()

    def test_ogre_values_reject_abi_and_identity_mismatches(self):
        for change in ("no_copy","wrong_copy","no_symbol","undefined","local_symbol","wrong_symbol_type","wrong_symbol_size","wrong_both_sizes","db_local","db_raw","db_label","wrong_section","readonly","short_section"):
            with self.subTest(change=change):
                self.ogre_value_setup()
                if change=="no_copy": self.image.relocs={}
                elif change=="wrong_copy": self.image.relocs[0x7000].symbol="wrong"
                elif change=="no_symbol": self.image.symbols=[]
                elif change=="undefined": self.image.symbols[0].defined=False
                elif change=="local_symbol": self.image.symbols[0].bind=0
                elif change=="wrong_symbol_type": self.image.symbols[0].type=2
                elif change=="wrong_symbol_size": self.image.symbols[0].size=16
                elif change=="wrong_both_sizes": self.image.symbols[0].size=self.db["globals"][0]["size"]=16
                elif change=="db_local": self.db["globals"][0]["bind"]="local"
                elif change=="db_raw": self.db["globals"][0]["name"]="_ZN4Ogre7Vector34FAKEE"
                elif change=="db_label": self.db["globals"][0]["demangled"]="Ogre::Vector3::FAKE"
                elif change=="wrong_section": self.image.sections[-1].type=1
                elif change=="readonly": self.image.sections[-1].flags=2
                elif change=="short_section": self.image.sections[-1].size=8
                with self.assertRaises(ContextError):self.index().build(self.target,"1000: mov $0x7000,%rax").require_complete()

    def test_ogre_matrix_reject_abi_and_identity_mismatches(self):
        for change in ("no_copy","wrong_copy","no_symbol","undefined","local_symbol","wrong_symbol_type","wrong_symbol_size","wrong_both_sizes","db_local","db_raw","db_label","wrong_section","readonly","short_section"):
            with self.subTest(change=change):
                self.ogre_value_setup("Matrix4")
                if change=="no_copy": self.image.relocs={}
                elif change=="wrong_copy": self.image.relocs[0x7000].symbol="wrong"
                elif change=="no_symbol": self.image.symbols=[]
                elif change=="undefined": self.image.symbols[0].defined=False
                elif change=="local_symbol": self.image.symbols[0].bind=0
                elif change=="wrong_symbol_type": self.image.symbols[0].type=2
                elif change=="wrong_symbol_size": self.image.symbols[0].size=32
                elif change=="wrong_both_sizes": self.image.symbols[0].size=self.db["globals"][0]["size"]=32
                elif change=="db_local": self.db["globals"][0]["bind"]="local"
                elif change=="db_raw": self.db["globals"][0]["name"]="_ZN4Ogre7Matrix44FAKEE"
                elif change=="db_label": self.db["globals"][0]["demangled"]="Ogre::Matrix4::FAKE"
                elif change=="wrong_section": self.image.sections[-1].type=1
                elif change=="readonly": self.image.sections[-1].flags=2
                elif change=="short_section": self.image.sections[-1].size=8
                with self.assertRaises(ContextError):self.index().build(self.target,"1000: mov $0x7000,%rax").require_complete()

    def test_ogre_values_reject_changed_configuration_or_header(self):
        for name in ("config","OgreConfig.h","OgrePrerequisites.h","OgrePlatform.h","OgreVector3.h","OgreQuaternion.h","OgreString.h","OgreMatrix4.h","OgreMath.h"):
            with self.subTest(name=name):
                sdk,config=self.ogre_value_setup()
                target=config if name=="config" else sdk/name
                target.write_bytes(target.read_bytes()+b"\n// changed")
                with self.assertRaises(ContextError):self.index().build(self.target,"1000: mov $0x7000,%rax").require_complete()

    def test_ogre_values_reject_wrong_type_owner_constness_duplicate_and_namespace(self):
        for declaration in (
            "namespace Ogre { class Vector3 { public: static Vector3 ZERO; }; }",
            "namespace Ogre { class Vector3 { public: static const int ZERO; }; }",
            "namespace Ogre { class Other { public: static const Vector3 ZERO; }; }",
            "namespace Other { class Vector3 { public: static const Vector3 ZERO; }; }",
            "namespace Ogre { class Vector3 { public: static const Vector3 ZERO; static const Vector3 ZERO; }; }"):
            with self.subTest(declaration=declaration):
                sdk,_=self.ogre_value_setup();(sdk/"OgreVector3.h").write_text(declaration)
                ContextIndex.OGRE_VALUE_HEADER_SHA256["OgreVector3.h"]=hashlib.sha256(declaration.encode()).hexdigest()
                with self.assertRaises(ContextError):self.index().build(self.target,"1000: mov $0x7000,%rax").require_complete()

    def test_ogre_matrix_reject_declaration_mismatches(self):
        for declaration in (
            "namespace Ogre { class Matrix4 { public: static Matrix4 IDENTITY; }; }",
            "namespace Ogre { class Matrix4 { public: static const int IDENTITY; }; }",
            "namespace Ogre { class Other { public: static const Matrix4 IDENTITY; }; }",
            "namespace Other { class Matrix4 { public: static const Matrix4 IDENTITY; }; }",
            "namespace Ogre { class Matrix4 { public: static const Matrix4 IDENTITY; static const Matrix4 IDENTITY; }; }"):
            with self.subTest(declaration=declaration):
                sdk,_=self.ogre_value_setup("Matrix4");(sdk/"OgreMatrix4.h").write_text(declaration)
                ContextIndex.OGRE_VALUE_HEADER_SHA256["OgreMatrix4.h"]=hashlib.sha256(declaration.encode()).hexdigest()
                with self.assertRaises(ContextError):self.index().build(self.target,"1000: mov $0x7000,%rax").require_complete()

    def test_ogre_values_reject_profile_changes_even_with_updated_header_pin(self):
        for name,value in (("OgreConfig.h","#define OGRE_DOUBLE_PRECISION 1\n"),("OgrePrerequisites.h","typedef double Real; typedef std::wstring _StringBase; typedef _StringBase String;")):
            sdk,_=self.ogre_value_setup();(sdk/name).write_text(value)
            ContextIndex.OGRE_VALUE_HEADER_SHA256[name]=hashlib.sha256(value.encode()).hexdigest()
            with self.assertRaises(ContextError):self.index().build(self.target,"1000: mov $0x7000,%rax").require_complete()

    def test_ogre_values_reject_symlink_escape_and_missing_header(self):
        for kind in ("escape","missing"):
            sdk,_=self.ogre_value_setup();path=sdk/"OgreVector3.h"
            outside=self.root/"outside-values.h";outside.write_bytes(path.read_bytes());path.unlink()
            if kind=="escape":path.symlink_to(outside)
            with self.assertRaises(ContextError):self.index().build(self.target,"1000: mov $0x7000,%rax").require_complete()

    def test_sdk_event_rejects_identity_and_abi_mismatches(self):
        for change in ("no_copy", "wrong_copy", "no_symbol", "undefined", "local_symbol",
                       "wrong_symbol_type", "wrong_symbol_size", "wrong_both_sizes", "db_local",
                       "db_raw", "db_label", "wrong_section", "readonly", "short_section"):
            with self.subTest(change=change):
                self.sdk_event();self.image.sections[-1].type = 8;self.image.sections[-1].flags = 3
                obj, symbol = self.db["globals"][0], self.image.symbols[0]
                if change == "no_copy": self.image.relocs = {}
                elif change == "wrong_copy": self.image.relocs[0x7000].symbol = "gameObject"
                elif change == "no_symbol": self.image.symbols = []
                elif change == "undefined": symbol.defined = False
                elif change == "local_symbol": symbol.bind = 0
                elif change == "wrong_symbol_type": symbol.type = 2
                elif change == "wrong_symbol_size": symbol.size = 8
                elif change == "wrong_both_sizes": symbol.size = obj["size"] = 8
                elif change == "db_local": obj.update(bind="local", file="Other.cpp")
                elif change == "db_raw": obj["name"] = "gameObject"
                elif change == "db_label": obj["demangled"] = "CEGUI::Window::OtherEvent"
                elif change == "wrong_section": self.image.sections[-1].type = 1
                elif change == "readonly": self.image.sections[-1].flags = 2
                elif change == "short_section": self.image.sections[-1].size = 8
                with self.assertRaises(ContextError): self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()

    def test_sdk_event_rejects_missing_or_changed_declaration(self):
        for source in ("", "namespace OTHER { class Window { static const String EventMouseMove; }; }",
                       "namespace CEGUI { class Window { static const int EventMouseMove; }; }",
                       "namespace CEGUI { class Window { const String EventMouseMove; }; }",
                       "namespace CEGUI { class Window { static String EventMouseMove; }; }",
                       "// namespace CEGUI { class Window { static const String EventMouseMove; }; }"):
            with self.subTest(source=source):
                self.sdk_event();self.sdk_header("CEGUIWindow.h", source)
                with self.assertRaises(ContextError): self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()

    def test_sdk_named_game_object_is_not_blanket_exempt(self):
        self.sdk_object("CEGUI::GameStat::counter", "_ZN5CEGUI8GameStat7counterE", 8)
        with self.assertRaises(ContextError): self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()

    def safe_pointer(self, pointee="CNode"):
        body = "template<class T> class TSafePointer { public: void setObject(T* p) { value=p; } private: T* value; };\n"
        self.write_header("SafePointer.h", body)
        pin = mock.patch.object(ContextIndex, "SAFE_POINTER_HEADER_SHA256", hashlib.sha256(body.encode()).hexdigest())
        pin.start(); self.addCleanup(pin.stop)
        self.write_header("Node.h", "class " + pointee + " { public: int value; };\n")
        self.mapping[pointee] = ["Node.h"]
        scope = "TSafePointer<" + pointee + ">"
        symbol = f"_ZN12TSafePointerI{len(pointee)}{pointee}E9setObjectEPS0_"
        f = function(0x2000, scope, "setObject", tu=1, kind="inline_or_template",
                     bind=["weak"], names=[symbol], params=pointee+"*", cv="")
        f["mangled"] = symbol
        self.add_function(f)
        self.image.symbols = [SimpleNamespace(type=2, bind=2, defined=True, value=0x2000, name=symbol, size=f["size"])]
        return f

    def test_safe_pointer_existing_template_supplies_whole_headers(self):
        self.safe_pointer()
        result = self.index().build(self.target, "1000: call 2000").require_complete()
        self.assertEqual(result.headers, ("Node.h", "SafePointer.h"))
        self.assertIn((self.include/"SafePointer.h").read_text(), result.text)
        self.assertIn("No specialization or prototype synthesized", result.text)

    def test_safe_pointer_equipment_and_character_instantiations(self):
        for cls in ("CEquipment", "CCharacter"):
            with self.subTest(cls=cls):
                self.safe_pointer(cls)
                self.index().build(self.target, "1000: call 2000").require_complete()

    def test_safe_pointer_rejects_wrong_db_identity(self):
        for change in ("strong", "ordinary", "method", "params", "cv", "mangled", "names", "qualified", "size"):
            with self.subTest(change=change):
                f=self.safe_pointer()
                if change=="strong": f["bind"]=["global"]
                elif change=="ordinary": f["kind"]="function"
                elif change=="method": f["method"]="setOther"
                elif change=="params": f["params"]="const CNode*"
                elif change=="cv": f["cv"]="const"
                elif change=="mangled": f["mangled"]="_fake"
                elif change=="names": f["names"].append("_fake")
                elif change=="qualified": f["qualified"]="Unrelated::setObject"
                elif change=="size": f["size"]+=1
                self.assertTrue(self.index().build(self.target,"1000: call 2000").gaps)

    def test_safe_pointer_requires_actual_weak_elf_function(self):
        for change in ("absent", "name", "size", "address", "binding", "type", "undefined"):
            with self.subTest(change=change):
                self.safe_pointer();symbol=self.image.symbols[0]
                if change=="absent": self.image.symbols=[]
                elif change=="name": symbol.name="_fake"
                elif change=="size": symbol.size+=1
                elif change=="address": symbol.value+=1
                elif change=="binding": symbol.bind=1
                elif change=="type": symbol.type=1
                elif change=="undefined": symbol.defined=False
                self.assertTrue(self.index().build(self.target,"1000: call 2000").gaps)

    def test_safe_pointer_changed_header_remains_gap(self):
        self.safe_pointer()
        with (self.include/"SafePointer.h").open("a") as stream: stream.write("// changed\n")
        self.assertTrue(self.index().build(self.target,"1000: call 2000").gaps)

    def test_safe_pointer_requires_unique_complete_pointee(self):
        for change in ("unmapped", "forward", "ambiguous"):
            with self.subTest(change=change):
                self.safe_pointer()
                if change=="unmapped": self.mapping.pop("CNode")
                elif change=="forward": self.write_header("Node.h","class CNode;\n")
                else:
                    self.write_header("OtherNode.h","class CNode { int other; };\n")
                    self.mapping["CNode"].append("OtherNode.h")
                self.assertTrue(self.index().build(self.target,"1000: call 2000").gaps)

    def test_safe_pointer_does_not_hide_an_unrelated_missing_callee(self):
        self.safe_pointer();self.add_function(function(0x3000,"CUnrelated","missing",tu=2))
        result=self.index().build(self.target,"1000: call 2000\n1005: call 3000")
        self.assertEqual(len(result.gaps),1)
        self.assertIn("CUnrelated::missing",result.gaps[0])

    def window_array(self):
        body = "template<class T> class TArrayList { public: ~TArrayList() { if (data) delete[] data; } T* data; };\n"
        self.write_header("TArrayList.h", body)
        pin = mock.patch.object(ContextIndex, "WINDOW_ARRAY_HEADER_SHA256", hashlib.sha256(body.encode()).hexdigest())
        pin.start(); self.addCleanup(pin.stop)
        scope = "TArrayList<CEGUI::Window*>"
        names = ["_ZN10TArrayListIPN5CEGUI6WindowEED1Ev", "_ZN10TArrayListIPN5CEGUI6WindowEED2Ev"]
        f = function(0x2000, scope, "~TArrayList", tu=1, kind="inline_or_template", bind=["weak", "weak"], names=names, params="", cv="")
        f["mangled"] = names[0]
        self.add_function(f)
        self.image.symbols = [SimpleNamespace(type=2, bind=2, defined=True, value=0x2000, name=n, size=f["size"]) for n in names]
        return f

    def test_window_array_existing_destructor_body_is_context(self):
        self.window_array()
        result = self.index().build(self.target, "1000: call 2000").require_complete()
        self.assertEqual(result.headers, ("TArrayList.h",))
        self.assertIn((self.include/"TArrayList.h").read_text(), result.text)
        self.assertIn("No specialization or prototype synthesized", result.text)

    def test_window_array_rejects_wrong_db_identity(self):
        for change in ("strong", "ordinary", "method", "params", "cv", "mangled", "names", "qualified", "size", "scope"):
            with self.subTest(change=change):
                f = self.window_array()
                if change == "strong": f["bind"] = ["global", "global"]
                elif change == "ordinary": f["kind"] = "function"
                elif change == "method": f["method"] = "clear"
                elif change == "params": f["params"] = "int"
                elif change == "cv": f["cv"] = "const"
                elif change == "mangled": f["mangled"] = "_fake"
                elif change == "names": f["names"] = ["_ZN10TArrayListIPN5CEGUI6WindowEED0Ev"]
                elif change == "qualified": f["qualified"] = "Unrelated::~Unrelated"
                elif change == "size": f["size"] += 1
                elif change == "scope": f["scope"] = "TArrayList<CNode*>"
                self.assertTrue(self.index().build(self.target,"1000: call 2000").gaps)

    def test_window_array_requires_both_actual_weak_elf_functions(self):
        for change in ("absent", "name", "size", "address", "binding", "type", "undefined"):
            with self.subTest(change=change):
                self.window_array(); symbol = self.image.symbols[1]
                if change == "absent": self.image.symbols.pop()
                elif change == "name": symbol.name = "_fake"
                elif change == "size": symbol.size += 1
                elif change == "address": symbol.value += 1
                elif change == "binding": symbol.bind = 1
                elif change == "type": symbol.type = 1
                elif change == "undefined": symbol.defined = False
                self.assertTrue(self.index().build(self.target,"1000: call 2000").gaps)

    def test_window_array_changed_header_remains_gap(self):
        self.window_array()
        with (self.include/"TArrayList.h").open("a") as out: out.write("// changed\n")
        self.assertTrue(self.index().build(self.target,"1000: call 2000").gaps)

    def test_window_array_does_not_hide_unrelated_callee(self):
        self.window_array(); self.add_function(function(0x3000,"CUnrelated","missing",tu=2))
        self.assertTrue(self.index().build(self.target,"1000: call 2000\n1005: call 3000").gaps)

    def pinned_destructor(self, variant):
        if variant == "wstring":
            f = self.window_array()
            scope = "TArrayList<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > >"
            address, size = 0x5f8e90, 155
            prefix, method = "_ZN10TArrayListISbIwSt11char_traitsIwESaIwEEE", "~TArrayList"
        elif variant in ("float", "quest_dialog", "quest_dialog_item", "quest_unit_arrays", "base_unit", "editor_object", "chunk", "level_layout", "chunk_type", "effect_stat", "data_group", "unsigned_int", "equipment_ref"):
            f = self.window_array()
            scope, address, prefix = {
                "float": ("TArrayList<float>", 0x59fb40, "_ZN10TArrayListIfE"),
                "unsigned_int": ("TArrayList<unsigned int>", 0x90da70, "_ZN10TArrayListIjE"),
                "equipment_ref": ("TArrayList<CEquipmentRef*>", 0x90da50, "_ZN10TArrayListIP13CEquipmentRefE"),
                "effect_stat": ("TArrayList<EEFFECT_STAT_MODIFIERS>", 0x7e4740, "_ZN10TArrayListI22EEFFECT_STAT_MODIFIERSE"),
                "data_group": ("TArrayList<CDataGroup*>", 0x85acd0, "_ZN10TArrayListIP10CDataGroupE"),
                "chunk": ("TArrayList<CChunk*>", 0x97cb30, "_ZN10TArrayListIP6CChunkE"),
                "level_layout": ("TArrayList<CLevelLayout*>", 0x97cb50, "_ZN10TArrayListIP12CLevelLayoutE"),
                "chunk_type": ("TArrayList<CChunkType*>", 0x97cb70, "_ZN10TArrayListIP10CChunkTypeE"),
                "editor_object": ("TArrayList<CEditorBaseObject*>", 0x740b90, "_ZN10TArrayListIP17CEditorBaseObjectE"),
                "base_unit": ("TArrayList<CBaseUnit*>", 0xd49940, "_ZN10TArrayListIP9CBaseUnitE"),
                "quest_dialog": ("TArrayList<CQuestDialog*>", 0xd1d3f0, "_ZN10TArrayListIP12CQuestDialogE"),
                "quest_dialog_item": ("TArrayList<CQuestDialogItem*>", 0xd26480, "_ZN10TArrayListIP16CQuestDialogItemE"),
                "quest_unit_arrays": ("TArrayList<TArrayList<CQuestUnitData*>*>", 0xd1d3d0, "_ZN10TArrayListIPS_IP14CQuestUnitDataEE"),
            }[variant]
            if variant == "equipment_ref":
                self.write_header("EquipmentRef.h", "class CEquipmentRef {};\n")
                self.mapping["CEquipmentRef"] = "EquipmentRef.h"
            size, method = 26, "~TArrayList"
        else:
            f = self.safe_pointer(variant)
            scope = "TSafePointer<" + variant + ">"
            address, size = {"CCharacter": (0x591b50, 47), "CPositionableObject": (0xd06790, 47), "CEquipment": (0xacbc90, 47), "CGraph": (0xcf8e70, 47), "CSkill": (0x7d5f90, 47), "CBaseUnit": (0x7d5fc0, 47), "CItem": (0x591be0, 47), "CEffectManager": (0x7d5ff0, 47)}[variant]
            prefix, method = "_ZN12TSafePointerI" + str(len(variant)) + variant + "E", "~TSafePointer"
        self.db["functions"].pop("0x2000")
        names = [prefix + "D1Ev", prefix + "D2Ev"]
        f.update(address=hex(address), size=size, scope=scope, method=method,
                 qualified=scope + "::" + method, params="", cv="", names=names, mangled=names[0])
        self.add_function(f)
        self.image.symbols = [SimpleNamespace(type=2, bind=2, defined=True, value=address, name=n, size=size) for n in names]
        return f

    def test_pinned_destructors_supply_existing_headers(self):
        for variant in ("wstring", "float", "CCharacter", "CPositionableObject", "CEquipment", "CGraph", "CSkill", "CBaseUnit", "CEffectManager", "CItem", "quest_dialog", "quest_dialog_item", "quest_unit_arrays", "base_unit", "editor_object", "chunk", "level_layout", "chunk_type", "effect_stat", "data_group", "unsigned_int", "equipment_ref"):
            with self.subTest(variant=variant):
                f = self.pinned_destructor(variant)
                result = self.index().build(self.target, "1000: call " + f["address"]).require_complete()
                expected = ("TArrayList.h",) if variant in ("wstring", "float", "quest_dialog", "quest_dialog_item", "quest_unit_arrays", "base_unit", "editor_object", "chunk", "level_layout", "chunk_type", "effect_stat", "data_group", "unsigned_int", "equipment_ref") else ("Node.h", "SafePointer.h")
                if variant == "equipment_ref":
                    expected = ("EquipmentRef.h", "TArrayList.h")
                self.assertEqual(result.headers, expected)
                self.assertIn("No specialization or prototype synthesized", result.text)

    def test_gameclient_item_destructor_rejects_identity_drift(self):
        for delta in ({"address": "0x591be1"}, {"size": 48}, {"kind": "function"},
                      {"bind": ["global"]}, {"params": "int"}, {"cv": "const"},
                      {"names": ["_ZN12TSafePointerI5CItemED0Ev"]}):
            with self.subTest(delta=delta):
                f=self.pinned_destructor("CItem")
                self.db["functions"].pop(f["address"])
                f.update(delta);self.add_function(f)
                self.assertTrue(self.index().build(self.target,"1000: call "+f["address"]).gaps)

    def test_gameclient_item_destructor_requires_both_native_aliases_and_header(self):
        for change in ("alias", "header", "pointee"):
            with self.subTest(change=change):
                f=self.pinned_destructor("CItem")
                if change=="alias":self.image.symbols.pop()
                elif change=="header":(self.include/"SafePointer.h").write_text("template<class T> class TSafePointer {};\n")
                else:(self.include/"Node.h").write_text("class CItem;\n")
                self.assertTrue(self.index().build(self.target,"1000: call "+f["address"]).gaps)

    def repository_destructor(self):
        header = Path(__file__).resolve().parents[2] / "decomp/include/TRepository.h"
        self.write_header("TRepository.h", header.read_text())
        scope = "TRepository<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > >"
        prefix = "_ZN11TRepositoryISbIwSt11char_traitsIwESaIwEEE"
        names = [prefix + "D1Ev", prefix + "D2Ev"]
        f = function(0xc629f0, scope, "~TRepository", size=178, tu=2)
        f.update(kind="inline_or_template", bind=["weak", "weak"], names=names,
                 mangled=names[0], params="", cv="")
        self.add_function(f)
        self.image.symbols = [SimpleNamespace(type=2, bind=2, defined=True,
                                             value=0xc629f0, name=n, size=178) for n in names]
        return f

    def test_repository_implicit_destructor_supplies_unchanged_whole_header(self):
        f = self.repository_destructor()
        result = self.index().build(self.target, "1000: call " + f["address"]).require_complete()
        self.assertEqual(result.headers, ("TRepository.h",))
        self.assertIn(ContextIndex.REPOSITORY_HEADER_SHA256, result.text)
        self.assertIn("No specialization or prototype synthesized", result.text)

    def test_repository_destructor_rejects_identity_and_header_drift(self):
        for delta in ({"address": "0xc629f1"}, {"size": 179}, {"kind": "function"},
                      {"bind": ["global"]}, {"method": "other"}, {"params": "int"},
                      {"names": ["_ZN11TRepositoryISbIwSt11char_traitsIwESaIwEEED0Ev"]}):
            with self.subTest(delta=delta):
                f = self.repository_destructor()
                self.add_function(dict(f, **delta))
                self.assertTrue(self.index().build(self.target, "1000: call " + delta.get("address", f["address"])).gaps)
        f = self.repository_destructor()
        (self.include / "TRepository.h").write_text("template<class T> class TRepository {};\n")
        self.assertTrue(self.index().build(self.target, "1000: call " + f["address"]).gaps)

    def test_repository_destructor_requires_both_native_aliases(self):
        f = self.repository_destructor()
        self.image.symbols.pop()
        self.assertTrue(self.index().build(self.target, "1000: call " + f["address"]).gaps)

    def test_base_unit_destructor_uses_real_pinned_header(self):
        f = self.pinned_destructor("base_unit")
        body = (Path(__file__).resolve().parents[2] / "decomp/include/TArrayList.h").read_bytes()
        digest = "d91f88adac805622a3e58081386a6b121b6b8f0d57bc4621886b9e5af591519f"
        self.assertEqual(hashlib.sha256(body).hexdigest(), digest)
        (self.include / "TArrayList.h").write_bytes(body)
        with mock.patch.object(ContextIndex, "WINDOW_ARRAY_HEADER_SHA256", digest):
            result = self.index().build(self.target, "1000: call " + f["address"]).require_complete()
        self.assertEqual(result.headers, ("TArrayList.h",))
        self.assertIn(body.decode(), result.text)
        self.assertIn("No specialization or prototype synthesized", result.text)

    def test_editor_object_destructor_uses_real_pinned_header(self):
        f = self.pinned_destructor("editor_object")
        body = (Path(__file__).resolve().parents[2] / "decomp/include/TArrayList.h").read_bytes()
        digest = "d91f88adac805622a3e58081386a6b121b6b8f0d57bc4621886b9e5af591519f"
        self.assertEqual(hashlib.sha256(body).hexdigest(), digest)
        (self.include / "TArrayList.h").write_bytes(body)
        with mock.patch.object(ContextIndex, "WINDOW_ARRAY_HEADER_SHA256", digest):
            result = self.index().build(self.target, "1000: call " + f["address"]).require_complete()
        self.assertEqual(result.headers, ("TArrayList.h",))
        self.assertIn(body.decode(), result.text)
        self.assertIn("No specialization or prototype synthesized", result.text)

    def test_level_array_destructors_use_real_pinned_header(self):
        body = (Path(__file__).resolve().parents[2] / "decomp/include/TArrayList.h").read_bytes()
        digest = "d91f88adac805622a3e58081386a6b121b6b8f0d57bc4621886b9e5af591519f"
        self.assertEqual(hashlib.sha256(body).hexdigest(), digest)
        for variant in ("chunk", "level_layout", "chunk_type", "effect_stat", "data_group", "unsigned_int", "equipment_ref"):
            with self.subTest(variant=variant):
                f = self.pinned_destructor(variant)
                (self.include / "TArrayList.h").write_bytes(body)
                with mock.patch.object(ContextIndex, "WINDOW_ARRAY_HEADER_SHA256", digest):
                    result = self.index().build(self.target, "1000: call " + f["address"]).require_complete()
                expected = ("EquipmentRef.h", "TArrayList.h") if variant == "equipment_ref" else ("TArrayList.h",)
                self.assertEqual(result.headers, expected)
                self.assertIn(body.decode(), result.text)
                self.assertIn("No specialization or prototype synthesized", result.text)

    def test_base_unit_pointer_shape_is_not_generic_template_permission(self):
        for scope, prefix in (("TArrayList<CBaseUnit const*>", "_ZN10TArrayListIPK9CBaseUnitE"),
                              ("TArrayList<CBaseUnit**>", "_ZN10TArrayListIPP9CBaseUnitE"),
                              ("TArrayList<CCharacter*>", "_ZN10TArrayListIP10CCharacterE")):
            with self.subTest(scope=scope):
                f = self.pinned_destructor("base_unit")
                names = [prefix + "D1Ev", prefix + "D2Ev"]
                f.update(scope=scope, qualified=scope + "::~TArrayList", names=names, mangled=names[0])
                for symbol, name in zip(self.image.symbols, names): symbol.name = name
                self.assertTrue(self.index().build(self.target, "1000: call " + f["address"]).gaps)
        f = self.pinned_destructor("base_unit")
        f['names'].append("_extra_alias")
        self.assertTrue(self.index().build(self.target, "1000: call " + f["address"]).gaps)

    def test_pinned_destructors_reject_db_mutations(self):
        mutations = {"kind": "function", "bind": ["global"], "method": "clear", "params": "int",
                     "cv": "const", "mangled": "_fake", "names": ["_fake"], "qualified": "Other::~Other",
                     "scope": "TArrayList<CNode*>", "size": 99, "address": "0x2222"}
        for variant in ("wstring", "float", "CCharacter", "CPositionableObject", "CEquipment", "CGraph", "CSkill", "CBaseUnit", "CEffectManager", "CItem", "quest_dialog", "quest_dialog_item", "quest_unit_arrays", "base_unit", "editor_object", "chunk", "level_layout", "chunk_type", "effect_stat", "data_group", "unsigned_int", "equipment_ref"):
            for field, value in mutations.items():
                with self.subTest(variant=variant, field=field):
                    f = self.pinned_destructor(variant); address = f["address"]
                    f[field] = value
                    self.assertTrue(self.index().build(self.target, "1000: call " + address).gaps)

    def test_pinned_destructors_require_both_weak_elf_aliases(self):
        for variant in ("wstring", "float", "CCharacter", "CPositionableObject", "CEquipment", "CGraph", "CSkill", "CBaseUnit", "CEffectManager", "CItem", "quest_dialog", "quest_dialog_item", "quest_unit_arrays", "base_unit", "editor_object", "chunk", "level_layout", "chunk_type", "effect_stat", "data_group", "unsigned_int", "equipment_ref"):
            for change in ("absent", "name", "size", "address", "binding", "type", "undefined", "D0"):
                with self.subTest(variant=variant, change=change):
                    f = self.pinned_destructor(variant); symbol = self.image.symbols[1]
                    if change == "absent": self.image.symbols.pop()
                    elif change == "name": symbol.name = "_fake"
                    elif change == "size": symbol.size += 1
                    elif change == "address": symbol.value += 1
                    elif change == "binding": symbol.bind = 1
                    elif change == "type": symbol.type = 1
                    elif change == "undefined": symbol.defined = False
                    else:
                        name = symbol.name.replace("D2Ev", "D0Ev")
                        symbol.name = name; f["names"][1] = name
                    self.assertTrue(self.index().build(self.target, "1000: call " + f["address"]).gaps)

    def test_pinned_destructors_reject_coherent_unreviewed_instantiations(self):
        for variant in ("wstring", "float", "CCharacter", "CPositionableObject", "CEquipment", "CGraph", "CSkill", "CBaseUnit", "CEffectManager", "CItem", "quest_dialog", "quest_dialog_item", "quest_unit_arrays", "base_unit", "editor_object", "chunk", "level_layout", "chunk_type", "effect_stat", "data_group", "unsigned_int", "equipment_ref"):
            with self.subTest(variant=variant):
                f = self.pinned_destructor(variant)
                if variant == "wstring":
                    scope, prefix = "TArrayList<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >", "_ZN10TArrayListISsE"
                elif variant in ("float", "quest_dialog", "quest_dialog_item", "quest_unit_arrays", "base_unit", "editor_object", "chunk", "level_layout", "chunk_type", "effect_stat", "data_group", "unsigned_int", "equipment_ref"):
                    scope, prefix = "TArrayList<CQuestUnitData*>", "_ZN10TArrayListIP14CQuestUnitDataE"
                else:
                    scope, prefix = "TSafePointer<CNode>", "_ZN12TSafePointerI5CNodeE"
                    self.write_header("Unreviewed.h", "class CNode { public: int value; };\n")
                    self.mapping["CNode"] = ["Unreviewed.h"]
                names = [prefix + "D1Ev", prefix + "D2Ev"]
                f.update(scope=scope, qualified=scope + "::" + f["method"], names=names, mangled=names[0])
                for symbol, name in zip(self.image.symbols, names): symbol.name = name
                self.assertTrue(self.index().build(self.target, "1000: call " + f["address"]).gaps)

    def test_pinned_destructors_reject_changed_template(self):
        for variant in ("wstring", "float", "CCharacter", "CPositionableObject", "CEquipment", "CGraph", "CSkill", "CBaseUnit", "CEffectManager", "CItem", "quest_dialog", "quest_dialog_item", "quest_unit_arrays", "base_unit", "editor_object", "chunk", "level_layout", "chunk_type", "effect_stat", "data_group", "unsigned_int", "equipment_ref"):
            with self.subTest(variant=variant):
                f = self.pinned_destructor(variant)
                header = "TArrayList.h" if variant in ("wstring", "float", "quest_dialog", "quest_dialog_item", "quest_unit_arrays", "base_unit", "editor_object", "chunk", "level_layout", "chunk_type", "effect_stat", "data_group", "unsigned_int", "equipment_ref") else "SafePointer.h"
                with (self.include/header).open("a") as out: out.write("// changed\n")
                self.assertTrue(self.index().build(self.target, "1000: call " + f["address"]).gaps)

    def test_pinned_safe_destructors_require_unique_complete_type(self):
        for variant in ("CCharacter", "CPositionableObject", "CEquipment", "CGraph", "CSkill", "CBaseUnit", "CEffectManager"):
            for change in ("unmapped", "forward", "ambiguous"):
                with self.subTest(variant=variant, change=change):
                    f = self.pinned_destructor(variant)
                    if change == "unmapped": self.mapping.pop(variant)
                    elif change == "forward": self.write_header("Node.h", "class " + variant + ";\n")
                    else:
                        self.write_header("OtherNode.h", "class " + variant + " { int other; };\n")
                        self.mapping[variant].append("OtherNode.h")
                    self.assertTrue(self.index().build(self.target, "1000: call " + f["address"]).gaps)

    def test_pinned_destructors_do_not_hide_unknown_callee(self):
        for variant in ("wstring", "float", "CCharacter", "CPositionableObject", "CEquipment", "CGraph", "CSkill", "CBaseUnit", "CEffectManager", "CItem", "quest_dialog", "quest_dialog_item", "quest_unit_arrays", "base_unit", "editor_object", "chunk", "level_layout", "chunk_type", "effect_stat", "data_group", "unsigned_int", "equipment_ref"):
            with self.subTest(variant=variant):
                f = self.pinned_destructor(variant)
                self.add_function(function(0x3000, "CUnrelated", "missing", tu=2))
                result = self.index().build(self.target, "1000: call " + f["address"] + "\n1005: call 3000")
                self.assertEqual(len(result.gaps), 1)
                self.assertIn("CUnrelated::missing", result.gaps[0])

    def test_quest_array_destructors_require_exact_header_and_snapshot(self):
        for variant in ("quest_dialog", "quest_dialog_item", "quest_unit_arrays", "base_unit", "editor_object", "chunk", "level_layout", "chunk_type", "effect_stat", "data_group", "unsigned_int", "equipment_ref"):
            for change in ("missing", "renamed", "body", "hash", "snapshot"):
                with self.subTest(variant=variant, change=change):
                    f = self.pinned_destructor(variant)
                    self.index().build(self.target, "1000: call " + f["address"]).require_complete()
                    header = self.include / "TArrayList.h"
                    index = self.index() if change == "snapshot" else None
                    if change == "missing":
                        header.unlink()
                    elif change == "renamed":
                        header.rename(self.include / "OtherArray.h")
                    elif change == "body":
                        header.write_text(header.read_text().replace("delete[] data", "delete data"))
                    elif change == "hash":
                        pin = mock.patch.object(ContextIndex, "WINDOW_ARRAY_HEADER_SHA256", "0" * 64)
                        with pin:
                            self.assertTrue(self.index().build(self.target, "1000: call " + f["address"]).gaps)
                        continue
                    else:
                        index.sources["TArrayList.h"] += "// stale scanned snapshot\n"
                    result = (index or self.index()).build(self.target, "1000: call " + f["address"])
                    self.assertTrue(result.gaps)

    def implicit_destructor(self):
        self.write_header("FileInfo.h", "class CFileInfo { public: CFileInfo() {} int value; };\n")
        self.mapping["CFileInfo"] = ["FileInfo.h"]
        f = function(0x2000, "CFileInfo", "~CFileInfo", tu=1,
                     names=["_ZN9CFileInfoD1Ev", "_ZN9CFileInfoD2Ev"], kind="inline_or_template", bind=["weak"], params="")
        self.add_function(f)
        return f

    def test_implicit_destructor_includes_whole_existing_class_header(self):
        self.implicit_destructor()
        result = self.index().build(self.target, "1000: call 2000").require_complete()
        self.assertEqual(result.headers, ("FileInfo.h",))
        self.assertIn("implicitly declared", result.text)
        self.assertIn("CFileInfo() {} int value;", result.text)
        self.assertNotIn("void ~CFileInfo", result.text)

    def test_implicit_destructor_rejects_unproven_forms(self):
        for change in ("strong", "ordinary", "deleting", "wrong_name", "missing_names", "parameters", "forward", "wrong_class"):
            with self.subTest(change=change):
                f = self.implicit_destructor()
                if change == "strong": f["bind"] = ["global"]
                elif change == "ordinary": f["kind"] = "function"
                elif change == "deleting": f["names"] = ["_ZN9CFileInfoD0Ev"]
                elif change == "wrong_name": f["names"] = ["_ZN9OtherInfoD1Ev"]
                elif change == "missing_names": f["names"] = []
                elif change == "parameters": f["params"] = "int"
                elif change == "forward": self.write_header("FileInfo.h", "class CFileInfo;\n")
                elif change == "wrong_class": self.write_header("FileInfo.h", "class OtherInfo { int value; };\n")
                with self.assertRaises(ContextError): self.index().build(self.target, "1000: call 2000").require_complete()

    def test_sdk_exemption_preserves_unrelated_game_data_gap(self):
        self.sdk_event();self.db["globals"].append(object_symbol(0x6000, "gMissingGame"))
        result = self.index().build(self.target, "1000: mov $0x7000,%rax\n1005: mov $0x6000,%rax")
        self.assertIn("SDK declaration", result.text)
        self.assertEqual(len(result.gaps), 1)
        self.assertIn("gMissingGame", result.gaps[0])

    def test_sdk_header_content_pin_mismatch_remains_gap(self):
        self.sdk_event()
        ContextIndex.CEGUI_HEADER_SHA256["CEGUIWindow.h"] = "0" * 64
        with self.assertRaises(ContextError): self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()

    def test_sdk_header_symlink_outside_sdk_is_not_read(self):
        self.sdk_event()
        p = self.root / "third_party/cegui-0.6.2/include/CEGUIWindow.h"
        outside = self.root / "outside.h";outside.write_bytes(p.read_bytes())
        p.unlink();p.symlink_to(outside)
        with self.assertRaises(ContextError): self.index().build(self.target, "1000: mov $0x7000,%rax").require_complete()

    def test_implicit_destructor_ambiguous_complete_class_remains_gap(self):
        self.implicit_destructor()
        self.write_header("OtherFileInfo.h", "class CFileInfo { int other; };\n")
        self.mapping["CFileInfo"].append("OtherFileInfo.h")
        with self.assertRaises(ContextError): self.index().build(self.target, "1000: call 2000").require_complete()

    def test_local_data_same_name_owner_is_not_substituted(self):
        self.write_header("Locals.h", "static int localCounter;\n")
        self.db["globals"] = [object_symbol(0x6000, "localCounter", size=8, bind="local", file="Other.cpp"),
                              object_symbol(0x6010, "localCounter", size=8, bind="local", file="Achievement.cpp")]
        index = self.index()
        wrong = index.build(self.target, "1000: mov $0x6000,%rax")
        self.assertIn("STT_FILE owner Other.cpp", wrong.text)
        self.assertNotIn("static int localCounter;", wrong.text)
        self.assertIn("no same-name declaration substituted", wrong.text)
        with self.assertRaises(ContextError):
            wrong.require_complete()
        right = index.build(self.target, "1000: mov $0x6010,%rax")
        self.assertIn("static int localCounter;", right.text)
        self.assertNotIn("owner Other.cpp", right.text)
        self.assertFalse(right.gaps)

    def test_ownerless_local_data_is_explicit_gap(self):
        self.write_header("Locals.h", "static int counter;\n")
        self.db["globals"] = [object_symbol(0x6000, "counter", bind="local")]
        result = self.index().build(self.target, "1000: mov $0x6000,%rax")
        self.assertTrue(result.gaps)
        self.assertNotIn("static int counter;", result.text)

    def test_actual_namespace_and_unscoped_free_function_headers(self):
        self.write_header("ActualStrings.h", "namespace STRINGS { int GetInt(const wchar_t*); }\n")
        self.write_header("WrongStrings.h", "namespace OTHER { float GetInt(int); } // WRONG_NAMESPACE\n")
        self.write_header("Free.h", "int gameFree(int);\n")
        self.mapping["STRINGS"] = ["WrongStrings.h", "ActualStrings.h"]
        self.add_function(function(0x2000, "STRINGS", "GetInt", tu=1))
        self.add_function(function(0x2100, "", "gameFree", tu=1))
        result = self.index().build(self.target, "1000: call 2000 <STRINGS::GetInt()>\n1005: call 2100 <gameFree()>")
        self.assertEqual(result.headers, ("ActualStrings.h", "Free.h"))
        self.assertIn("namespace STRINGS { int GetInt(const wchar_t*); }", result.text)
        self.assertNotIn("WRONG_NAMESPACE", result.text)

    def test_shared_identity_nested_enum_array_and_FILE(self):
        self.write_header("Nested.h", "#include <cstdio>\nclass CUndo { public: class Data { public: ~Data(); }; enum Kind { K }; void work(Data*, Kind, unsigned int (&values)[6], FILE*); };")
        self.mapping["CUndo"] = "Nested.h"
        exact = "CUndo::Data*, CUndo::Kind, unsigned int (&)[6], _IO_FILE*"
        callee = function(0x2000, "CUndo", "work", params=exact)
        self.add_function(callee)
        self.assertFalse(self.index().build(self.target, "1000: call 2000").gaps)
        for wrong in (exact.replace("CUndo::Data", "Other::Data"), exact.replace("[6]", "[5]"), exact.replace("unsigned int", "const unsigned int"), exact.replace("_IO_FILE*", "Other::_IO_FILE*")):
            callee["params"] = wrong
            self.assertTrue(self.index().build(self.target, "1000: call 2000").gaps)
        callee.update(scope="CUndo::Data", qualified="CUndo::Data::~Data", method="~Data", params="")
        self.assertFalse(self.index().build(self.target, "1000: call 2000").gaps)

    def test_direct_callee_scoped_callback_alias_uses_complete_lexical_identity(self):
        self.write_header("Interpreter.h", "class CInterpreter { public: typedef unsigned int (*Value)(CScene*, const std::wstring&); CInterpreter(Value callback); void set(Value callback); };")
        self.mapping["CInterpreter"] = "Interpreter.h"
        f = function(0x2000, "CInterpreter", "CInterpreter", params="unsigned int (*)(CScene*, std::wstring const&)")
        self.add_function(f)
        self.assertFalse(self.index().build(self.target, "1000: call 2000").gaps)
        for params in ("int (*)(CScene*, std::wstring const&)", "unsigned int (*)(Other::CScene*, std::wstring const&)", "unsigned int (*)(CScene*, std::wstring&)"):
            f["params"] = params
            self.assertTrue(self.index().build(self.target, "1000: call 2000").gaps)

    def test_cross_header_scoped_callback_includes_exact_defining_header_whole(self):
        callback_source = "namespace N { struct Result; struct Arg; typedef Result* (*Callback)(Arg*); }"
        self.write_header("Callbacks.h", callback_source)
        self.write_header("Prop.h", '#include "Callbacks.h"\nclass CProp { public: void work(N::Callback callback); };')
        self.write_header("OtherCallbacks.h", "namespace Other { typedef int (*Callback)(float); }")
        self.mapping["CProp"] = "Prop.h"
        self.add_function(function(0x2000, "CProp", "work", params="N::Result* (*)(N::Arg*)"))
        result = self.index().build(self.target, "1000: call 2000").require_complete()
        self.assertEqual(result.headers, ("Callbacks.h", "Prop.h"))
        self.assertIn(callback_source, result.text)
        self.assertNotIn("namespace Other", result.text)
        # An already shown defining header is not repeated or omitted from the
        # completeness accounting; the untouched original source remains shown.
        shown = self.index().build(self.target, "1000: call 2000", already_shown=["Callbacks.h"]).require_complete()
        self.assertEqual(shown.headers, ("Prop.h",))

    def test_failed_or_shadowed_scoped_callback_never_contributes_dependency(self):
        self.write_header("Callbacks.h", "namespace N { struct Result; struct Arg; typedef Result* (*Callback)(Arg*); }")
        self.write_header("Prop.h", "class CProp { public: void work(N::Callback callback); };")
        self.mapping["CProp"] = "Prop.h"
        f = function(0x2000, "CProp", "work", params="Other::Result* (*)(N::Arg*)")
        self.add_function(f)
        index = self.index()
        declaration = next(d for d in index.declarations["Prop.h"] if d.kind == "function")
        dependencies = set()
        self.assertFalse(index.identity.matches(declaration, f, "Prop.h", dependencies=dependencies))
        self.assertEqual(dependencies, set())
        self.assertTrue(index.build(self.target, "1000: call 2000").gaps)
        f["params"] = "N::Result* (*)(N::Arg*)"
        for source in ("class CProp { public: typedef int Callback; void work(Callback callback); };", "class CProp { public: void work(Other::Callback callback); };"):
            self.write_header("Prop.h", source)
            result = self.index().build(self.target, "1000: call 2000")
            self.assertTrue(result.gaps)
            self.assertNotIn("Callbacks.h", result.headers)
        self.write_header("Prop.h", "class CProp { public: void work(N::Callback callback); };")
        self.write_header("Duplicate.h", "namespace N { typedef Result* (*Callback)(Arg*); }")
        result = self.index().build(self.target, "1000: call 2000")
        self.assertTrue(result.gaps)
        self.assertNotIn("Callbacks.h", result.headers)
        self.assertNotIn("Duplicate.h", result.headers)

    def namespace_local(self, source=None):
        self.write_header("Achievement.h", "namespace ParticleUniverse { class Technique; } class CAchievement { ParticleUniverse::Technique* p; };")
        (self.src / "Achievement.cpp").write_text(source or "namespace ParticleUniverse { class Technique { public: void set(float); }; }")
        self.add_function(function(0x2000, "ParticleUniverse::Technique", "set", params="float", tu=2))

    def test_named_namespace_local_opaque_calls_keep_original_wrapper(self):
        self.namespace_local()
        result = self.index().build(self.target, "1000: call 2000").require_complete()
        self.assertIn("namespace ParticleUniverse {\nclass Technique { public: void set(float); };\n}", result.text)
        self.db["functions"]["0x2000"]["params"] = "int"
        self.assertTrue(self.index().build(self.target, "1000: call 2000").gaps)

    def test_namespace_local_never_reads_foreign_TU_or_borrows_other_scope(self):
        self.namespace_local("namespace Other { class Technique { void set(float); }; }")
        (self.src / "Other.cpp").write_text("namespace ParticleUniverse { class Technique { void set(float); }; }")
        result = self.index().build(self.target, "1000: retq")
        self.assertNotIn("class Technique { void set(float); };", result.text)
        self.namespace_local()
        self.db["functions"]["0x2000"].update(scope="Other::Technique", qualified="Other::Technique::set")
        self.assertTrue(self.index().build(self.target, "1000: call 2000").gaps)

    def test_namespace_local_rejects_fields_virtuals_bases_inline_and_duplicates(self):
        for body in ("int data; void set(float);", "void (*callback)(float); void set(float);", "int data = call(); void set(float);", "virtual void set(float);", "void set(float) {}", "void set(float); class Inner {};", "void set(float);"):
            if body == "void set(float);":
                source = "namespace ParticleUniverse { class Technique : Base { " + body + " }; }"
            else:
                source = "namespace ParticleUniverse { class Technique { " + body + " }; }"
            self.namespace_local(source)
            with self.subTest(source=source), self.assertRaises(ContextError):
                self.index().build(self.target, "1000: call 2000")
        self.namespace_local("namespace ParticleUniverse { class Technique { void set(float); }; class Technique { void set(float); }; }")
        with self.assertRaisesRegex(ContextError, "ambiguous"):
            self.index().build(self.target, "1000: call 2000")

    def test_existing_typed_global_initializer_and_template_arguments_are_verbatim(self):
        declarations = [
            ("static long long g_DescriptionVersion = 0;", "g_DescriptionVersion"),
            ("extern std::map<std::wstring, TArrayList<CEditorBaseObject*>*> g_CachedObjects;", "g_CachedObjects"),
            ("static TRepository<std::wstring> g_GlobalRepository(EMPTY_WSTRING);", "g_GlobalRepository")]
        for declaration, name in declarations:
            source = '#include "Dependency.h"\n' + declaration
            self.write_header("TypedData.h", source)
            self.db["globals"] = [object_symbol(0x6000, name, bind="local", file="Achievement.cpp")]
            with self.subTest(name=name):
                result = self.index().build(self.target, "1000: mov $0x6000,%rax").require_complete()
                self.assertIn(declaration, result.text)
                if name != "g_DescriptionVersion":
                    self.assertIn('#include "Dependency.h"', result.text)
                self.db["globals"][0]["file"] = "Other.cpp"
                self.assertTrue(self.index().build(self.target, "1000: mov $0x6000,%rax").gaps)

    def test_typed_global_parser_never_accepts_expressions_compound_body_or_duplicates(self):
        for declaration in ("static long long value = macro();", "static long long value = ZERO;", "static long long value = 0, other = 0;", "extern std::map<int, int> value, other;", "void f() { static long long value = 0; }", "static TRepository<std::wstring> value(EMPTY_WSTRING);", "static TRepository<std::wstring> g_GlobalRepository(call());"):
            self.write_header("TypedData.h", declaration)
            self.db["globals"] = [object_symbol(0x6000, "value")]
            with self.subTest(declaration=declaration):
                self.assertTrue(self.index().build(self.target, "1000: mov $0x6000,%rax").gaps)
        self.write_header("TypedData.h", "extern std::map<int, int> value; extern std::map<int, int> value;")
        self.assertTrue(self.index().build(self.target, "1000: mov $0x6000,%rax").gaps)

    def new_reviewed_destructor(self, variant):
        actual = Path(__file__).resolve().parents[2] / "decomp/include"
        self.write_header("TArrayList.h", (actual / "TArrayList.h").read_text())
        if variant == "union":
            scope, address, prefix, owner = "TArrayList<UNIONDATA32BIT>", 0x70ca90, "_ZN10TArrayListI14UNIONDATA32BITE", "DescriptorProp.cpp"
            self.write_header("DescriptorProp.h", (actual / "DescriptorProp.h").read_text())
        else:
            scope, address, prefix, owner = "TArrayList<CSkill*>", 0xcd57a0, "_ZN10TArrayListIP6CSkillE", "SkillManager.cpp"
            self.write_header("Skill.h", "class CSkill { public: void work(); };")
            self.mapping["CSkill"] = "Skill.h"
        self.db["tus"][2]["name"] = owner
        names = [prefix + "D1Ev", prefix + "D2Ev"]
        f = function(address, scope, "~TArrayList", size=26, tu=2, kind="inline_or_template", bind=["weak", "weak"], names=names)
        f["mangled"] = names[0]
        self.add_function(f)
        self.image.symbols = [SimpleNamespace(type=2, bind=2, defined=True, value=address, name=n, size=26) for n in names]
        return f

    def test_two_new_destructors_require_exact_ELF_source_element_and_owner(self):
        for variant in ("union", "skill"):
            for change in (None, "variant", "size", "owner", "header", "element", "other_instantiation"):
                with self.subTest(variant=variant, change=change):
                    self.db["functions"] = {}
                    f = self.new_reviewed_destructor(variant)
                    if change == "variant": self.image.symbols.pop()
                    elif change == "size": self.image.symbols[0].size = 27
                    elif change == "owner": self.db["tus"][2]["name"] = "Other.cpp"
                    elif change == "header": (self.include / "TArrayList.h").write_text("// changed\n" + (self.include / "TArrayList.h").read_text())
                    elif change == "element":
                        name = "DescriptorProp.h" if variant == "union" else "Skill.h"
                        (self.include / name).write_text("class CSkill; union UNIONDATA32BIT;")
                    elif change == "other_instantiation":
                        f["scope"] = "TArrayList<Other*>"
                        f["qualified"] = f["scope"] + "::~TArrayList"
                    result = self.index().build(self.target, "1000: call " + f["address"])
                    if change is None:
                        self.assertFalse(result.gaps)
                        self.assertIn("TArrayList.h", result.headers)
                    else:
                        self.assertTrue(result.gaps)

    def test_free_target_does_not_include_every_mapped_header(self):
        target = function(0x1000, "", "freeTarget", size=0x40)
        result = self.index().build(target, "1000: retq")
        self.assertEqual(result.headers, ())
        self.assertNotIn("class CAchievement", result.text)
        self.assertNotIn("SHOULD_NOT_APPEAR", result.text)

    def test_scoped_data_keeps_namespace_and_class_owner(self):
        self.write_header("Namespaces.h", "namespace SETTINGS { namespace FLAGS { extern int enabled; } }\n")
        self.write_header("Holder.h", "class CHolder { public: static int value; long layout[20]; };\n")
        self.db["globals"] = [object_symbol(0x6000, "SETTINGS::FLAGS::enabled", size=4),
                              object_symbol(0x6008, "CHolder::value", size=4)]
        result = self.index().build(self.target, "1000: mov $0x6000,%rax\n1005: mov $0x6008,%rax")
        self.assertIn("namespace SETTINGS {\nnamespace FLAGS {\nextern int enabled;", result.text)
        self.assertEqual(result.headers, ("Holder.h",))
        self.assertIn("long layout[20];", result.text)
        self.assertFalse(result.gaps)

    def test_existing_tu_local_class_but_not_any_foreign_body(self):
        target = function(0x1000, "CCinematics", "reload", size=0x40)
        self.write_header("Cinematics.h", "class CCinematic;\nclass CCinematics { CCinematic* entries; void reload(); };\n")
        self.mapping["CCinematics"] = "Cinematics.h"
        (self.src / "Achievement.cpp").write_text("#include \"Cinematics.h\"\n"
            "int unrelatedBody() { return 666; }\n"
            "// Brace in comment: {\nclass CCinematic\n{\npublic:\n"
            "    std::wstring m_sName;\n    std::wstring m_sText;\n    void load(CDataGroup*);\n};\n"
            "void CCinematic::load(CDataGroup* d) { FOREIGN_BODY(); }\n"
            "class UnusedLocal { int sentinel; };\n")
        self.add_function(function(0x2000, "CCinematic", "load", tu=0, params="CDataGroup*"))
        result = self.index().build(target, "1000: call 2000 <CCinematic::load()>\n1005: retq",
                                    already_shown=["Cinematics.h"])
        self.assertIn("class CCinematic\n{\npublic:", result.text)
        self.assertIn("std::wstring m_sText;", result.text)
        self.assertIn("void load(CDataGroup*);", result.text)
        self.assertNotIn("FOREIGN_BODY", result.text)
        self.assertNotIn("return 666", result.text)
        self.assertNotIn("UnusedLocal", result.text)
        self.assertNotIn("#include", result.text)
        self.assertFalse(result.gaps)

    def test_local_type_via_own_header_even_when_all_methods_are_inlined(self):
        self.write_header("Achievement.h", "class Tiny; class CAchievement { Tiny* p; };\n")
        (self.src / "Achievement.cpp").write_text("#include \"Achievement.h\"\nclass Tiny { int value; };\n"
                                                  "class NotUsed { int other; };\n")
        result = self.index().build(self.target, "1000: retq")
        self.assertIn("class Tiny { int value; };", result.text)
        self.assertNotIn("NotUsed", result.text)
        self.assertNotIn("#include", result.text)

    def test_selected_local_inline_body_or_nested_type_blocks_without_cutting(self):
        self.write_header("Achievement.h", "class Tiny; class CAchievement { Tiny* p; };\n")
        (self.src / "Achievement.cpp").write_text('class Tiny { int f() { return 1; } };\n')
        with self.assertRaisesRegex(ContextError, "inline bodies"):
            self.index().build(self.target, "1000: retq")

    def test_duplicate_local_type_names_fail_instead_of_selecting_last_scope(self):
        self.write_header("Achievement.h", "class Tiny; class CAchievement { Tiny* p; };\n")
        (self.src / "Achievement.cpp").write_text("class Tiny { int a; };\nnamespace N { class Tiny { int b; }; }\n")
        with self.assertRaisesRegex(ContextError, "ambiguous TU-local type name"):
            self.index().build(self.target, "1000: retq")

    def test_braces_in_comments_and_strings_do_not_leak_function_definitions(self):
        self.write_header("Achievement.h", "class Tiny; class CAchievement { Tiny* p; };\n")
        (self.src / "Achievement.cpp").write_text('void f() { const char* s="}; class Impostor {"; }\n'
                                                  'class Tiny { /* { } */ int field; };\n')
        result = self.index().build(self.target, "1000: retq")
        self.assertIn("class Tiny { /* { } */ int field; };", result.text)
        self.assertNotIn("Impostor", result.text)

    def test_anonymous_namespace_local_type_blocks_not_unsafely_extracted(self):
        self.write_header("Achievement.h", "class Tiny; class CAchievement { Tiny* p; };\n")
        (self.src / "Achievement.cpp").write_text("namespace { class Tiny { int x; }; }\n")
        with self.assertRaisesRegex(ContextError, "non-top-level/anonymous scope"):
            self.index().build(self.target, "1000: retq")

    def test_macro_continuations_are_not_indexed_as_existing_data(self):
        continuation = chr(92) + "\n"
        self.write_header("Macro.h", "#define EXAMPLE " + continuation
                          + "extern int macroOnly; " + continuation
                          + "extern int alsoMacroOnly;\nextern int realData;\n")
        self.db["globals"] = [object_symbol(0x6000, "macroOnly"), object_symbol(0x6020, "realData")]
        result = self.index().build(self.target, "1000: mov $0x6000,%rax\n1005: mov $0x6020,%rax")
        self.assertTrue(any("macroOnly" in gap for gap in result.gaps))
        self.assertNotIn("extern int macroOnly;", result.text)
        self.assertIn("extern int realData;", result.text)

    def test_default_arguments_and_pure_virtual_are_declarations_not_bodies(self):
        self.write_header("SteamStats.h", "class CSteamStats { public: virtual int getStatInt(int x = 0) = 0; };\n")
        self.add_function(function(0x2000, "CSteamStats", "getStatInt", tu=1))
        result = self.index().build(self.target, "1000: call 2000")
        self.assertFalse(result.gaps)
        self.assertEqual(result.headers, ("SteamStats.h",))

    def test_readonly_unknown_bytes_only_explicit_diagnostic_prefix(self):
        result = self.index().build(self.target, "1000: mov $0x5000,%rax")
        self.assertIn("hex " + "91 " * 31 + "91", result.text)
        self.assertIn("diagnostic prefix only (32 bytes", result.text)
        self.assertIn("not the whole object", result.text)
        self.assertNotIn("NUL-terminated", result.text)
        self.assertEqual(self.image.reads, [(0x5000, 32)])

    def test_printable_unknown_bytes_are_not_inferred_as_char_or_wchar(self):
        image = FakeImage(section(".rodata", 0x5000, b"CURRENT\0REQUIRED\0"))
        result = self.index(image=image).build(self.target, "1000: mov $0x5000,%rax")
        self.assertIn("43 55 52 52 45 4e 54 00", result.text)
        self.assertNotIn("text b'CURRENT'", result.text)

    def test_unknown_wide_punctuation_bytes_stay_hex_only(self):
        raw = bytes.fromhex("2f00000000000000 310000002f0000003100000000000000 300000002f0000003100000000000000")
        image = FakeImage(section(".rodata", 0x5000, raw))
        result = self.index(image=image).build(self.target, "1000: mov $0x5000,%rax\n1005: mov $0x5008,%rax\n"
                                                          "100a: mov $0x5018,%rax")
        for address, expected in ((0x5000, raw[:32]), (0x5008, raw[8:40]), (0x5018, raw[24:40])):
            self.assertIn(f"{address:#x} (.rodata): hex {expected.hex(' ')}", result.text)
        self.assertNotIn("NUL-terminated", result.text)
        self.assertNotIn("wchar32-LE text", result.text)

    def test_no_reads_from_text_bss_writable_or_non_alloc_sections(self):
        image = FakeImage(section(".text", 0x2000, b"TEXT\0", flags=6),
                          section(".bss", 0x3000, b"", flags=3, typ=8, size=16),
                          section(".data", 0x4000, b"DATA\0", flags=3),
                          section(".debug_str", 0x5000, b"DEBUG\0", flags=0),
                          section(".data.rel.ro", 0x6000, b"RELRO\0", flags=3))
        result = self.index(image=image).build(self.target, "1000: mov $0x2000,%rax\n1005: mov $0x3000,%rax\n"
                                                          "100a: mov $0x4000,%rax\n100f: mov $0x5000,%rax\n"
                                                          "1014: mov $0x6000,%rax")
        self.assertEqual(image.reads, [])
        self.assertNotIn("hex ", result.text)

    def test_section_segment_and_object_bounds(self):
        cases = [(FakeImage(section(".rodata", 0x5000, b"ABCDE")), 0x5003, [], b"DE"),
                 (FakeImage(section(".rodata", 0x5000, b"ABCDE", size=100), file_limit=4),
                  0x5002, [], b"CD"),
                 (FakeImage(section(".rodata", 0x5000, b"ABCDE")), 0x5001,
                  [object_symbol(0x5000, "blob", size=3)], b"BC")]
        self.write_header("Blob.h", "extern unsigned char blob[3];\n")
        for image, address, objects, expected in cases:
            with self.subTest(address=address, objects=objects):
                db = dict(self.db, globals=objects)
                result = self.index(db=db, image=image).build(self.target, f"1000: mov ${address:#x},%rax")
                self.assertIn(expected.hex(" "), result.text)
                self.assertEqual(image.reads, [(address, len(expected))])

    def test_typed_char_and_wchar_text_complete_through_terminator(self):
        self.write_header("Literals.h", "extern const char current[8];\nextern const wchar_t required[9];\n")
        wide = "required\0".encode("utf-32-le")
        image = FakeImage(section(".rodata", 0x5000, b"current\0" + wide))
        self.db["globals"] = [object_symbol(0x5000, "current", size=8), object_symbol(0x5008, "required", size=len(wide))]
        result = self.index(image=image).build(self.target, "1000: mov $0x5000,%rax\n1005: mov $0x5008,%rax")
        self.assertIn("byte text b'current'; 8 bytes complete through terminator", result.text)
        self.assertIn("wchar32-LE text 'required'; 36 bytes complete through terminator", result.text)
        self.assertIn("not ABI proof", result.text)
        self.assertFalse(result.gaps)

    def test_explicit_elf_byte_string_flag_but_no_guessed_wide_encoding(self):
        image = FakeImage(section(".rodata.str1.1", 0x5000, b"hello\0", flags=2 | 0x20, entsize=1),
                          section(".rodata.str4.4", 0x6000, b"W\0\0\0\0\0\0\0", flags=2 | 0x20, entsize=4))
        result = self.index(image=image).build(self.target, "1000: mov $0x5000,%rax\n1005: mov $0x6000,%rax")
        self.assertIn("byte text b'hello'", result.text)
        self.assertIn("ELF SHF_STRINGS, entsize=1", result.text)
        self.assertIn("0x6000 (.rodata.str4.4): hex", result.text)

    def test_char_pointer_and_unsigned_blob_are_not_decoded_as_strings(self):
        self.write_header("Blob.h", "extern const char* pointer;\nextern unsigned char bytes[8];\n")
        image = FakeImage(section(".rodata", 0x5000, b"ASCII\0!!ASCII\0!!"))
        self.db["globals"] = [object_symbol(0x5000, "pointer", size=8), object_symbol(0x5008, "bytes", size=8)]
        result = self.index(image=image).build(self.target, "1000: mov $0x5000,%rax\n1005: mov $0x5008,%rax")
        self.assertNotIn("NUL-terminated", result.text)

    def test_unterminated_or_invalid_typed_wide_only_diagnostic(self):
        self.write_header("Literals.h", "extern const char chars[4];\nextern const wchar_t wide[2];\n")
        image = FakeImage(section(".rodata", 0x5000, b"ABCD" + b"\0\xd8\0\0\0\0\0\0"))
        self.db["globals"] = [object_symbol(0x5000, "chars", size=4), object_symbol(0x5004, "wide", size=8)]
        result = self.index(image=image).build(self.target, "1000: mov $0x5000,%rax\n1005: mov $0x5004,%rax")
        self.assertNotIn("NUL-terminated", result.text)
        self.assertIn("41 42 43 44", result.text)

    def test_misaligned_wchar_interior_address_is_not_decoded(self):
        self.write_header("Literals.h", "extern const wchar_t wide[3];\n")
        image = FakeImage(section(".rodata", 0x5000, "ab\0".encode("utf-32-le")))
        self.db["globals"] = [object_symbol(0x5000, "wide", size=12)]
        result = self.index(image=image).build(self.target, "1000: mov $0x5001,%rax")
        self.assertNotIn("wchar32-LE text", result.text)
        self.assertIn("diagnostic prefix only", result.text)

    def test_typed_long_string_fails_instead_of_silently_truncating(self):
        self.write_header("Literals.h", "extern const char longText[9001];\n")
        image = FakeImage(section(".rodata", 0x5000, b"A" * 9000 + b"\0"))
        self.db["globals"] = [object_symbol(0x5000, "longText", size=9001)]
        with self.assertRaisesRegex(ContextError, "do not truncate"):
            self.index(image=image).build(self.target, "1000: mov $0x5000,%rax")

    def test_duplicate_order_and_already_shown_are_deterministic(self):
        self.add_function(function(0x2000, "CSteamStats", "getStatInt", tu=1))
        self.add_function(function(0x2100, "CSteamStats", "getStatFloat", tu=1))
        asm = "1000: call 2100\n1005: call 2000\n100a: call 2000"
        a = self.index().build(self.target, asm)
        other = copy.deepcopy(self.db)
        other["functions"] = dict(reversed(list(other["functions"].items())))
        b = self.index(db=other, headers=dict(reversed(list(self.mapping.items())))).build(self.target, asm)
        self.assertEqual(a, b)
        self.assertEqual(a.text.count("class CSteamStats"), 1)
        shown = self.index().build(self.target, asm, already_shown=["SteamStats.h", "SteamStats.h"])
        self.assertEqual(shown.headers, ())
        self.assertNotIn("class CSteamStats", shown.text)

    def test_safe_mapping_and_symlink_paths(self):
        for name in ("../Outside.h", "/Outside.h", "x/y.h", "x\\y.h", ".hidden.h", "bad\0.h", "bad\n.h"):
            with self.subTest(name=name), self.assertRaises(ContextError):
                self.index(headers={"CSteamStats": name})
        outside = self.root / "Outside.h"
        outside.write_text("SECRET")
        (self.include / "Escape.h").symlink_to(outside)
        with self.assertRaisesRegex(ContextError, "unsafe include"):
            self.index()

    def test_safe_tu_symlink_and_basename(self):
        index = self.index()
        with self.assertRaises(ContextError):
            index.build(self.target, "1000: retq", tu="../Outside.cpp")
        outside = self.root / "Outside.cpp"
        outside.write_text("SECRET")
        (self.src / "Achievement.cpp").symlink_to(outside)
        with self.assertRaisesRegex(ContextError, "unsafe src"):
            index.build(self.target, "1000: retq")

    def test_already_shown_is_not_a_missing_header_bypass(self):
        with self.assertRaisesRegex(ContextError, "not an existing indexed header"):
            self.index().build(self.target, "1000: retq", already_shown=["Missing.h"])

    def test_missing_selected_header_and_invalid_encoding_are_errors(self):
        self.add_function(function(0x2000, "CMissing", "method", tu=1))
        self.mapping["CMissing"] = "Missing.h"
        with self.assertRaisesRegex(ContextError, "selected header.*missing"):
            self.index().build(self.target, "1000: call 2000")
        (self.include / "Invalid.h").write_bytes(b"\xff")
        with self.assertRaisesRegex(ContextError, "cannot read"):
            self.index()

    def test_no_db_or_image_load_no_subprocess_and_borrowed_image_reuse(self):
        elfdb, elfimage = ModuleType("elfdb"), ModuleType("elfimage")
        elfdb.load_db = mock.Mock(side_effect=AssertionError("DB reload"))
        elfimage.load = mock.Mock(side_effect=AssertionError("ELF reload"))
        with mock.patch.dict(sys.modules, {"elfdb": elfdb, "elfimage": elfimage}), \
                mock.patch("subprocess.Popen", side_effect=AssertionError("subprocess")):
            index = self.index()
            first = index.build(self.target, "1000: mov $0x5000,%rax")
            second = index.build(self.target, "1000: mov $0x5000,%rax")
        self.assertIs(index.image, self.image)
        self.assertEqual(first, second)
        elfdb.load_db.assert_not_called()
        elfimage.load.assert_not_called()

    def test_missing_callee_declaration_does_not_promote_return_hint(self):
        self.add_function(function(0x2000, "CSteamStats", "getStatType", tu=1,
                                   return_hint={"kind": "float", "confidence": "guess"}))
        result = self.index().build(self.target, "1000: call 2000 <CSteamStats::getStatType()>")
        self.assertEqual(result.headers, ("SteamStats.h",))
        self.assertTrue(result.gaps)
        self.assertNotIn("float getStatType", result.text)
        self.assertIn("not confirmed ABI", result.text)

    def test_unknown_named_data_and_unannotated_rip_are_explicit(self):
        self.db["globals"] = [object_symbol(0x6000, "unrestored")]
        result = self.index().build(self.target, "1000: mov $0x6000,%rax\n1005: mov 0x20(%rip),%eax")
        self.assertIn("No existing header declaration", result.text)
        self.assertIn("lacks a numeric target; not guessed", result.text)

    def test_empty_wrong_range_and_invalid_size_fail_closed(self):
        for asm in ("", "2000: retq", "1000 <target>:\nnot disassembly"):
            with self.subTest(asm=asm), self.assertRaisesRegex(ContextError, "no instructions"):
                self.index().build(self.target, asm)
        with self.assertRaises(ContextError):
            self.index().build(dict(self.target, size=0), "1000: retq")

    def test_short_read_is_not_silent(self):
        image = FakeImage(section(".rodata", 0x5000, b"A" * 128))
        image.read = lambda address, size: b"A"
        with self.assertRaisesRegex(ContextError, "short ELF read"):
            self.index(image=image).build(self.target, "1000: mov $0x5000,%rax")

    def test_context_and_prompt_budget_never_cut_mandatory_inputs(self):
        context = self.index().build(self.target, "1000: mov $0x5000,%rax")
        with self.assertRaisesRegex(ContextError, "no headers/data were truncated"):
            self.index().build(self.target, "1000: mov $0x5000,%rax", max_chars=len(context.text) - 1)
        fixed, tail = ["IDIOMS", "WHOLE HEADER"], ["TASK", "EXACT ASM", "FULL DRAFT", "RULES"]
        mandatory = compose_prompt(fixed=fixed, context=context, tail=tail)
        self.assertEqual(compose_prompt(fixed=fixed, context=context, tail=tail, examples="EXAMPLES" * 100,
                                        max_chars=len(mandatory)), mandatory)
        with self.assertRaisesRegex(ContextError, "optional examples cannot solve"):
            compose_prompt(fixed=fixed, context=context, tail=tail, examples="EXAMPLE", max_chars=len(mandatory) - 1)
        full = compose_prompt(fixed=fixed, context=context, tail=tail, examples="EXAMPLE")
        self.assertIn("EXAMPLE", full)
        for text in [*fixed, context.text, *tail]:
            self.assertIn(text, full)

    def test_preparation_failure_blocks_before_provider_call(self):
        # Minimal imitation of the existing run() preparation seam, not another loop.
        provider = mock.Mock(side_effect=AssertionError("provider must not run"))
        status, feedback = None, None
        try:
            context = self.index().build(self.target, "1000: mov $0x5000,%rax")
            prompt = compose_prompt(fixed=["HEADER"], context=context, tail=["ASM"], max_chars=1)
        except ValueError as error:
            status, feedback = "blocked", str(error)
        else:
            provider(prompt)
        self.assertEqual(status, "blocked")
        self.assertIn("mandatory prompt", feedback)
        provider.assert_not_called()


    def level_template_destructor(self, variant):
        f = self.pinned_destructor("base_unit")
        self.db["functions"].pop(f["address"])
        scope, address, size, prefix = {
            "layout": ("TArrayList<CLayout*>", 0x967160, 26, "_ZN10TArrayListIP7CLayoutE"),
            "property": ("TArrayList<CPropertyNode*>", 0x967140, 26, "_ZN10TArrayListIP13CPropertyNodeE"),
            "box": ("TArrayList<Ogre::AxisAlignedBox>", 0x967520, 91, "_ZN10TArrayListIN4Ogre14AxisAlignedBoxEE"),
        }[variant]
        names = [prefix + "D1Ev", prefix + "D2Ev"]
        f.update(address=hex(address), size=size, scope=scope, qualified=scope+"::~TArrayList", names=names, mangled=names[0])
        self.add_function(f)
        self.image.symbols = [SimpleNamespace(type=2, bind=2, defined=True, value=address, name=n, size=size) for n in names]
        if variant == "box":
            cache = self.root / "sdk-cache"
            sdk = cache / "gcc447/ogre-1.6.5/ogre/OgreMain/include"
            sdk.mkdir(parents=True, exist_ok=True)
            pins = {}
            for name in ContextIndex.AXIS_BOX_ARRAY_SDK_SHA256:
                source = ("synthetic SDK guard input " + name + "\n").encode()
                (sdk/name).write_bytes(source)
                pins[name] = hashlib.sha256(source).hexdigest()
            config = b"synthetic pinned compiler profile\n"
            (self.root/"decomp/config.json").write_bytes(config)
            for p in (mock.patch.object(ContextIndex,"AXIS_BOX_ARRAY_SDK_SHA256",pins),
                      mock.patch.object(ContextIndex,"OGRE_CONFIG_SHA256",hashlib.sha256(config).hexdigest()),
                      mock.patch.dict(os.environ,{"OTL_DECOMP_CACHE":str(cache)})):
                p.start(); self.addCleanup(p.stop)
            self.level_box_sdk = sdk
        return f

    def test_level_template_destructors_exact_existing_instantiations(self):
        for variant in ("layout","property","box"):
            with self.subTest(variant=variant):
                f=self.level_template_destructor(variant)
                result=self.index().build(self.target,"1000: call "+f["address"]).require_complete()
                self.assertEqual(result.headers,("TArrayList.h",))

    def test_level_template_destructors_reject_metadata_drift(self):
        for variant in ("layout","property","box"):
            for change in ("address","size","method","params","cv","strong","alias","elf_size","elf_alias"):
                with self.subTest(variant=variant,change=change):
                    f=self.level_template_destructor(variant)
                    if change=="address":
                        self.db["functions"].pop(f["address"]);f["address"]=hex(int(f["address"],16)+16);self.add_function(f)
                    elif change=="size":f["size"]+=1
                    elif change=="method":f["method"]="clear"
                    elif change=="params":f["params"]="int"
                    elif change=="cv":f["cv"]="const"
                    elif change=="strong":f["bind"]=["global"]
                    elif change=="alias":f["names"]=f["names"][:1]
                    elif change=="elf_size":self.image.symbols[0].size+=1
                    else:self.image.symbols.pop()
                    self.assertTrue(self.index().build(self.target,"1000: call "+f["address"]).gaps)

    def test_level_template_destructors_reject_changed_template(self):
        for variant in ("layout","property","box"):
            with self.subTest(variant=variant):
                f=self.level_template_destructor(variant)
                with (self.include/"TArrayList.h").open("a") as out:out.write("// modified\n")
                self.assertTrue(self.index().build(self.target,"1000: call "+f["address"]).gaps)

    def test_level_box_destructor_requires_all_sdk_inputs(self):
        for name in ContextIndex.AXIS_BOX_ARRAY_SDK_SHA256:
            for change in ("missing","changed","outside"):
                with self.subTest(header=name,change=change):
                    f=self.level_template_destructor("box");path=self.level_box_sdk/name
                    if change=="missing":path.unlink()
                    elif change=="changed":path.write_bytes(path.read_bytes()+b" ")
                    else:
                        outside=self.root/"outside-sdk-header";outside.write_bytes(path.read_bytes());path.unlink();path.symlink_to(outside)
                    self.assertTrue(self.index().build(self.target,"1000: call "+f["address"]).gaps)
                    if path.is_symlink():path.unlink()

    def test_level_box_destructor_rejects_compiler_profile_change(self):
        f=self.level_template_destructor("box")
        (self.root/"decomp/config.json").write_text("different flags\n")
        self.assertTrue(self.index().build(self.target,"1000: call "+f["address"]).gaps)

    def test_level_template_destructors_do_not_hide_another_gap(self):
        f=self.level_template_destructor("box");self.add_function(function(0x3000,"CUnrelated","missing",tu=2))
        result=self.index().build(self.target,"1000: call "+f["address"]+"\n1005: call 3000")
        self.assertEqual(len(result.gaps),1)
        self.assertIn("CUnrelated::missing",result.gaps[0])


class UIExactContextPins(TestCase):
    """Exact UI additions remain closed when any identity input changes."""
    def setUp(self):
        temp = TemporaryDirectory(prefix="otl-ui-context-")
        self.addCleanup(temp.cleanup)
        self.index = ContextIndex.__new__(ContextIndex)
        index = self.index
        index.root = Path(temp.name).resolve()
        index.cegui_headers = {}
        index.sources = {"TArrayList.h": "template<class T> class TArrayList {};\n",
                         "iMenuListener.h": "class iMenuListener {};\n"}
        index.mapping = {"iMenuListener": ["iMenuListener.h"]}
        index.header_classes = {"iMenuListener.h": {"iMenuListener"}}
        include = index.root / "decomp/include"
        include.mkdir(parents=True)
        for name, source in index.sources.items():
            (include / name).write_text(source)
        array_pin = mock.patch.object(ContextIndex, "WINDOW_ARRAY_HEADER_SHA256",
            hashlib.sha256(index.sources["TArrayList.h"].encode()).hexdigest())
        array_pin.start()
        self.addCleanup(array_pin.stop)
        strings = mock.patch.object(ContextIndex, "_string_template_headers", return_value=True)
        strings.start()
        self.addCleanup(strings.stop)
        self.objects = []
        digests = {}
        for owner, event, address, name in [
                ("Editbox", "EventTextAccepted", 0x1424940, "CEGUIEditbox.h"),
                ("FrameWindow", "EventCloseClicked", 0x1423c60, "CEGUIFrameWindow.h"),
                ("Window", "EventMouseMove", 0x7000, "CEGUIWindow.h")]:
            source = "namespace CEGUI { class " + owner + " { public: static const String " + event + "; }; }\n"
            folder = index.root / "third_party/cegui-0.6.2/include"
            if owner != "Window":
                folder /= "elements"
            folder.mkdir(parents=True, exist_ok=True)
            (folder / name).write_text(source)
            digests[name] = hashlib.sha256(source.encode()).hexdigest()
            raw = "_ZN5CEGUI" + str(len(owner)) + owner + str(len(event)) + event + "E"
            self.objects.append(dict(address=hex(address), size=176, bind="global", name=raw,
                                     demangled="CEGUI::" + owner + "::" + event))
        pins = mock.patch.dict(ContextIndex.CEGUI_HEADER_SHA256, digests)
        pins.start()
        self.addCleanup(pins.stop)
        index.copy_data = {int(o["address"], 16): o["name"] for o in self.objects}
        index.elf_object_names = {(int(o["address"], 16), o["name"]): {o["name"]} for o in self.objects}
        index.elf_object_sizes = {key: {176} for key in index.elf_object_names}
        index.image = SimpleNamespace(section_at=lambda a: SimpleNamespace(type=8, flags=3, addr=a, size=176))
        wide = "std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >"
        self.add = function(0xafca50, "TArrayList<" + wide + " >", "add", size=439,
                            kind="inline_or_template", bind=["weak"], params=wide)
        self.add["mangled"] = "_ZN10TArrayListISbIwSt11char_traitsIwESaIwEEE3addES3_"
        self.add["names"] = [self.add["mangled"]]
        self.dtor = function(0xb1ba10, "TArrayList<iMenuListener*>", "~TArrayList", size=26,
                             kind="inline_or_template", bind=["weak"])
        self.dtor["names"] = ["_ZN10TArrayListIP13iMenuListenerED1Ev", "_ZN10TArrayListIP13iMenuListenerED2Ev"]
        self.dtor["mangled"] = self.dtor["names"][0]
        index.elf_weak_functions = {(int(row["address"], 16), name, row["size"])
                                    for row in [self.add, self.dtor] for name in row["names"]}

    def test_two_exact_element_copy_declarations(self):
        for obj in self.objects[:2]:
            self.assertIn("SDK declaration static const String Event", self.index._cegui_data(obj))

    def test_wrong_element_identity_rejected(self):
        for obj in self.objects[:2]:
            for delta in [{"size": 8}, {"bind": "local"}, {"name": obj["name"] + "x"},
                          {"address": hex(int(obj["address"], 16) + 8)},
                          {"demangled": obj["demangled"].replace("CEGUI::", "Other::")}]:
                with self.subTest(delta=delta):
                    self.assertIsNone(self.index._cegui_data(dict(obj, **delta)))

    def test_copy_relocation_required(self):
        self.index.copy_data.clear()
        for obj in self.objects[:2]:
            self.assertIsNone(self.index._cegui_data(obj))

    def test_unknown_element_event_is_not_exempt(self):
        for obj in self.objects[:2]:
            self.assertIsNone(self.index._cegui_data(dict(obj, demangled="CEGUI::Editbox::EventTextChanged")))

    def test_changed_sdk_header_bytes_rejected(self):
        folder = self.index.root / "third_party/cegui-0.6.2/include/elements"
        for path in folder.iterdir():
            path.write_bytes(path.read_bytes() + b"// changed\n")
        for obj in self.objects[:2]:
            self.assertIsNone(self.index._cegui_data(obj))

    def test_existing_window_event_keeps_its_header_path(self):
        self.assertIsNotNone(self.index._cegui_data(self.objects[2]))

    def test_reviewed_existing_template_headers(self):
        self.assertEqual(self.index._pinned_insert_headers(self.add, self.add["scope"]), {"TArrayList.h"})
        self.assertEqual(self.index._pinned_destructor_headers(self.dtor, self.dtor["scope"]),
                         {"TArrayList.h", "iMenuListener.h"})

    def test_template_identity_and_header_digest_are_required(self):
        for row, method in [(self.add, self.index._pinned_insert_headers),
                            (self.dtor, self.index._pinned_destructor_headers)]:
            for delta in [{"size": 1}, {"bind": ["global"]}, {"kind": "function"},
                          {"address": "0x1"}, {"method": "other"}, {"params": "const std::wstring&"}]:
                with self.subTest(delta=delta):
                    self.assertEqual(method(dict(row, **delta), row["scope"]), set())
        self.index._path("include", "TArrayList.h").write_text("changed\n")
        self.assertEqual(self.index._pinned_insert_headers(self.add, self.add["scope"]), set())
        self.assertEqual(self.index._pinned_destructor_headers(self.dtor, self.dtor["scope"]), set())

    def test_missing_owner_pointer_arrays_have_exact_existing_destructors(self):
        wide = "std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >"
        for scope, address, prefix, pointee in [
                ("TArrayList<CMod*>", 0xc86b30, "_ZN10TArrayListIP4CModE", "CMod"),
                ("TArrayList<CAchievement*>", 0xecdf30, "_ZN10TArrayListIP12CAchievementE", "CAchievement"),
                ("TArrayList<TArrayList<" + wide + " >*>", 0x935e40,
                 "_ZN10TArrayListIPS_ISbIwSt11char_traitsIwESaIwEEEE", None)]:
            with self.subTest(scope=scope):
                expected = {"TArrayList.h"}
                if pointee:
                    name = pointee + ".h"
                    source = "class " + pointee + " {};\n"
                    self.index.sources[name] = source
                    self.index.mapping[pointee] = [name]
                    self.index.header_classes[name] = {pointee}
                    self.index._path("include", name).write_text(source)
                    expected.add(name)
                row = function(address, scope, "~TArrayList", size=26,
                               kind="inline_or_template", bind=["weak"])
                row["names"] = [prefix + "D1Ev", prefix + "D2Ev"]
                row["mangled"] = row["names"][0]
                self.index.elf_weak_functions.update((address, name, 26) for name in row["names"])
                method = self.index._pinned_destructor_headers
                self.assertEqual(method(row, scope), expected)
                for delta in [{"address": hex(address + 16)}, {"size": 27},
                              {"bind": ["global"]}, {"names": row["names"][:1]},
                              {"params": "int"}, {"cv": "const"}]:
                    self.assertEqual(method(dict(row, **delta), scope), set())
                self.index.elf_weak_functions.remove((address, row["names"][1], 26))
                self.assertEqual(method(row, scope), set())
                self.index.elf_weak_functions.add((address, row["names"][1], 26))
                if pointee:
                    del self.index.header_classes[pointee + ".h"]
                    self.assertEqual(method(row, scope), set())


class TimelineOwningListContextPins(TestCase):
    def setUp(self):
        temp = TemporaryDirectory(prefix="otl-timeline-list-context-")
        self.addCleanup(temp.cleanup)
        self.index = ContextIndex.__new__(ContextIndex)
        self.index.root = Path(temp.name).resolve()
        self.index.sources = {}
        include = self.index.root / "decomp/include"
        include.mkdir(parents=True)
        for header in ContextIndex.TIMELINE_POINT_LIST_HEADER_SHA256:
            raw = (HERE.parent / "decomp/include" / header).read_bytes()
            (include / header).write_bytes(raw)
            self.index.sources[header] = raw.decode("utf-8")
        self.row = function(0x7cd010, "CLList<CTimelineProperty::CTimelinePoint*>",
                            "destroy", size=79, kind="inline_or_template", bind=["weak"])
        self.row["mangled"] = "_ZN6CLListIPN17CTimelineProperty14CTimelinePointEE7destroyEv"
        self.row["names"] = [self.row["mangled"]]
        self.index.elf_weak_functions = {(0x7cd010, self.row["mangled"], 79)}

    def headers(self, row=None, scope=None):
        row = self.row if row is None else row
        return self.index._timeline_point_list_headers(row, row["scope"] if scope is None else scope)

    def test_exact_owning_list_supplies_body_and_both_layouts(self):
        self.assertEqual(self.headers(), {"CLList.h", "TLinkedList.h", "TimelineProperty.h"})

    def test_owning_list_rejects_changed_function_identity(self):
        for delta in [{"address": "0x7cd011"}, {"size": 80}, {"bind": ["global"]},
                      {"kind": "function"}, {"method": "clear"}, {"params": "int"},
                      {"cv": "const"}, {"qualified": "CLList<int>::destroy"},
                      {"mangled": self.row["mangled"] + "x"}, {"names": []},
                      {"names": [self.row["mangled"], "extra"]}]:
            with self.subTest(delta=delta):
                self.assertEqual(self.headers(dict(self.row, **delta)), set())
        self.assertEqual(self.headers(scope="CLList<CEditorBaseObject*>"), set())
        self.index.elf_weak_functions.clear()
        self.assertEqual(self.headers(), set())

    def test_owning_list_requires_every_unchanged_header(self):
        for header in ContextIndex.TIMELINE_POINT_LIST_HEADER_SHA256:
            with self.subTest(header=header):
                path = self.index._path("include", header)
                raw = path.read_bytes()
                path.write_bytes(raw + b"// changed\n")
                self.assertEqual(self.headers(), set())
                path.write_bytes(raw)
                source = self.index.sources.pop(header)
                self.assertEqual(self.headers(), set())
                self.index.sources[header] = source + "// stale index\n"
                self.assertEqual(self.headers(), set())
                self.index.sources[header] = source


class UIScalarInitializers(TestCase):
 def scan(self,text):
  from llm_context import _scan
  return _scan(text)[0]
 def test_verbatim_wide_literal_with_escapes(self):
  text=r'static const std::wstring Help = L"line\n\t\"Текст\"";';rows=self.scan(text);self.assertEqual(len(rows),1);self.assertEqual((rows[0].qualified,rows[0].kind,rows[0].text),('Help','data',text))
 def test_mutable_boolean_and_float_tokens(self):
  for typ,value in [('bool','true'),('bool','false'),('float','1.0f'),('float','-0.0f'),('float','1.25e-3f')]:
   rows=self.scan('static '+typ+' Last = '+value+';');self.assertEqual([r.qualified for r in rows],['Last'])
 def test_expressions_constructors_macros_and_compound_rejected(self):
  for text in ['static const std::wstring Help = make();','static const std::wstring Help = MACRO;', 'static const std::wstring Help = std::wstring(L"text");', 'static bool Last = !false;', 'static float Last = 1.0f + 2.0f;', 'static bool First = false, Last = true;', 'static float Last = nanf("");']:
   self.assertEqual(self.scan(text),[],text)
 def test_unreviewed_wide_literal_forms_rejected(self):
  for value in ['"narrow"','L"one" L"two"',r'L"bad\q"','L"unescaped\nnewline"']:
   self.assertEqual(self.scan('static const std::wstring Help = '+value+';'),[],value)
  self.assertEqual(self.scan('static std::wstring Help = L"mutable";'),[])
 def test_non_top_level_and_nonstatic_initializers_rejected(self):
  for text in ['const std::wstring Help = L"x";', 'namespace NS { static const std::wstring Help = L"x"; }', 'class C { static const std::wstring Help = L"x"; };', 'void fn() { static bool Last = false; }']:
   self.assertEqual(self.scan(text),[],text)
 def test_existing_ui_headers_keep_exact_initializers(self):
  expected={'MainMenuData.h':{'CopyrightInfo'},'NewGameMenuData.h':{'m_gFileVersionExtension'},'SettingsMenuData.h':{'LastMusicMute','LastSoundMute','LastMusicVolume','LastSoundVolume','KShadowSettingNames','KParticleSettingNames'},'ConsoleData.h':{'SetPetsEnabled','fixRoomPieces','gTEXT_HELP'}}
  for name,names in expected.items():self.assertEqual({d.qualified for d in self.scan((HERE.parent/'decomp/include'/name).read_text())},names,name)

if __name__ == "__main__":
    main()
