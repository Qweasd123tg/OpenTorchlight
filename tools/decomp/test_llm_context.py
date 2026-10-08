"""Offline regression tests: no original ELF, provider, game, Ghidra or compiler."""
from __future__ import annotations

from pathlib import Path
from tempfile import TemporaryDirectory
from types import SimpleNamespace, ModuleType
from unittest import TestCase, main, mock
import copy
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
from llm_context import Context, ContextError, ContextIndex, compose_prompt


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
    return dict(address=hex(address), size=size, scope=scope, method=method,
                qualified=qualified, demangled=qualified + "()", mangled="_fake_" + method,
                tu=tu, **extra)


def object_symbol(address, name, *, size=32, bind="global", file=None):
    return dict(address=hex(address), name=name, demangled=name, size=size, bind=bind, file=file)


class PacketContextTests(TestCase):
    def setUp(self):
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
        self.add_function(function(0x2000, "CCinematic", "load", tu=0))
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


if __name__ == "__main__":
    main()
