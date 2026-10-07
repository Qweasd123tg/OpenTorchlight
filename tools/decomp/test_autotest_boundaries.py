"""Calibrate supported argument/return categories through both actual call paths."""
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest
from unittest.mock import patch

import autotest
import toolchain


class ArgumentContracts(unittest.TestCase):
    def plan(self, declared):
        generator = autotest.Generator.__new__(autotest.Generator)
        generator.enums = {}
        statements, members = [], []
        result = generator.argument(declared, 0, statements.append, members)
        return result, '\n'.join(statements), members

    def test_string_value_reference_and_const_reference_keep_declared_category(self):
        for declared in ('std::wstring', 'std::wstring&', 'std::wstring const&'):
            with self.subTest(declared=declared):
                plan, setup, members = self.plan(declared)
                self.assertEqual(autotest.ghidra_cpp.cxx_type(declared), plan.declared_type)
                self.assertEqual('*c.a0', plan.expression)
                self.assertEqual(('out.addText(*c.a0);',), plan.observations)
                self.assertTrue(plan.cleanup)

    def test_scalar_referents_are_initialized_with_typed_values(self):
        for declared in ('int&', 'unsigned int&', 'const int&', 'float&', 'const double&', 'bool&'):
            with self.subTest(declared=declared):
                plan, setup, members = self.plan(declared)
                self.assertEqual(declared, plan.declared_type)
                self.assertIn('*c.a0 = ', setup)
                self.assertEqual('*c.a0', plan.expression)


@unittest.skipUnless(shutil.which('g++'), 'requires host C++ compiler')
class NativeBoundaryCalibration(unittest.TestCase):
    def test_signature_matrix(self):
        self.matrix()

    def test_original_compiler_signature_matrix(self):
        if not (toolchain.cache_dir() / 'gcc447/.complete.json').exists():
            self.skipTest('requires pinned GCC 4.4.7')
        self.matrix(pinned=True)

    def matrix(self, pinned=False):
        header = '''#include <string>
struct Record { std::wstring value; };
class Probe { public: int a; int b;
 static int& external();
 void value(std::wstring); void text(std::wstring&); void number(int&);
 void flag(bool&); void real(float&); void natural(unsigned int&);
 int read(const int&); int length(const std::wstring&);
 int& inside(); int& same(); const int& immutable();
 std::wstring result(); void nothing(); void record(Record&); void chars(wchar_t*); int charsRead(const wchar_t*);
};
'''
        # Expected same / different / incomplete: no comparison uses bothFailed.
        specs = [
            ('external', '', '_ZN5Probe8externalEv', 'incomplete'),
            ('value', 'std::wstring', '_ZN5Probe5valueESbIwSt11char_traitsIwESaIwEE', 'same'),
            ('text', 'std::wstring&', '_ZN5Probe4textERSbIwSt11char_traitsIwESaIwEE', 'different'),
            ('number', 'int&', '_ZN5Probe6numberERi', 'different'),
            ('flag', 'bool&', '_ZN5Probe4flagERb', 'different'),
            ('real', 'float&', '_ZN5Probe4realERf', 'different'),
            ('natural', 'unsigned int&', '_ZN5Probe7naturalERj', 'different'),
            ('read', 'int const&', '_ZN5Probe4readERKi', 'same'),
            ('length', 'std::wstring const&', '_ZN5Probe6lengthERKSbIwSt11char_traitsIwESaIwEE', 'same'),
            ('inside', '', '_ZN5Probe6insideEv', 'different'),
            ('same', '', '_ZN5Probe4sameEv', 'same'),
            ('immutable', '', '_ZN5Probe9immutableEv', 'same'),
            ('result', '', '_ZN5Probe6resultEv', 'same'),
            ('nothing', '', '_ZN5Probe7nothingEv', 'same'),
            ('record', 'Record&', '_ZN5Probe6recordER6Record', 'different'),
            ('chars', 'wchar_t*', '_ZN5Probe5charsEPw', 'different'),
            ('charsRead', 'wchar_t const*', '_ZN5Probe9charsReadEPKw', 'same'),
        ]
        support = r'''
#include "Probe.h"
#include "AutoTest.h"
#include <cstdio>
#include <cstdarg>
namespace autotest { char g_arena[kArenaSize]; size_t g_arenaUsed; Pool g_pool; Outcome g_outcomes[2]; }
static void logline(const char* f,...) { va_list ap;va_start(ap,f);vprintf(f,ap);va_end(ap); }
static int known_pair(uint64_t,uint64_t);
static const tlhybrid_host host={TLHYBRID_ABI_VERSION,logline,known_pair};
int left_value=7, right_value=7;
int& Probe::external() { return right_value; }
void Probe::value(std::wstring v) { if(!v.empty())v[0]=L'Z'; }
void Probe::text(std::wstring& v) { if(!v.empty())v[0]=L'B'; }
void Probe::number(int&) {}
void Probe::flag(bool&) {}
void Probe::real(float&) {}
void Probe::natural(unsigned int&) {}
int Probe::read(const int& v) { return v; }
int Probe::length(const std::wstring& v) { return (int)v.size(); }
int& Probe::inside() { a=b=7; return b; }
int& Probe::same() { a=b=7; return a; }
const int& Probe::immutable() { a=b=7; return a; }
std::wstring Probe::result() { return L"returned object"; }
void Probe::nothing() {}
void Probe::record(Record& r) { if(!r.value.empty())r.value[0]=L'B'; }
void Probe::chars(wchar_t* p) { if(*p)*p=L'B'; }
int Probe::charsRead(const wchar_t* p) { return (int)std::wcslen(p); }
'''
        # Independent typed reference callees. Original adapters are emitted by
        # the real generator; candidate bodies use normal C++ member calls.
        refs = [
            ('int&', '', 'return left_value;'),
            ('void', 'Probe*, std::wstring v', "if(!v.empty())v[0]=L'Z';"),
            ('void', 'Probe*, std::wstring& v', "if(!v.empty())v[0]=L'A';"),
            ('void', 'Probe*, int& v', 'if(v!=0)++v;'),
            ('void', 'Probe*, bool& v', 'if(v)v=false;'),
            ('void', 'Probe*, float& v', 'if(v!=0)v+=1;'),
            ('void', 'Probe*, unsigned int& v', 'if(v!=0)++v;'),
            ('int', 'Probe*, const int& v', 'return v;'),
            ('int', 'Probe*, const std::wstring& v', 'return (int)v.size();'),
            ('int&', 'Probe* p', 'p->a=p->b=7; return p->a;'),
            ('int&', 'Probe* p', 'p->a=p->b=7; return p->a;'),
            ('const int&', 'Probe* p', 'p->a=p->b=7; return p->a;'),
            ('std::wstring', 'Probe*', 'return L"returned object";'),
            ('void', 'Probe*', ''),
            ('void', 'Probe*, Record& r', "if(!r.value.empty())r.value[0]=L'A';"),
            ('void', 'Probe*, wchar_t* p', "if(*p)*p=L'A';"),
            ('int', 'Probe*, const wchar_t* p', 'return (int)std::wcslen(p);'),
        ]
        with tempfile.TemporaryDirectory(prefix='otl-boundary-matrix-') as folder:
            root = Path(folder); include = root/'decomp/include'; include.mkdir(parents=True)
            (include/'Probe.h').write_text(header)
            generator = autotest.Generator.__new__(autotest.Generator)
            generator.db = {}; generator.enums = {}; generator.vtables = {}
            generator.classes = {'Probe': {'size':8,'bases':[], 'fields':[
                {'name':'a','type':'int','offset':0,'size':4}, {'name':'b','type':'int','offset':4,'size':4}]}}
            generator.classes['Record'] = {'size':8,'bases':[], 'fields':[{'name':'value','type':'std::wstring','offset':0,'size':8}]}
            generator.headers = {'Probe':'Probe.h','Record':'Probe.h'}
            code, calls = [], []
            with patch.object(autotest, 'ROOT', root), patch.object(autotest, 'CASES', 40):
                for i, ((name, params, mangled, expected), (result, arguments, body)) in enumerate(zip(specs,refs)):
                    address = hex(0x100+i)
                    f = {'scope':'Probe','demangled':f'Probe::{name}({params})', 'params':params,
                         'kind':'function','names':[mangled],'cv':'','address':address}
                    _, generated = generator.test_for(f); code.append(generated)
                    support += (f'extern "C" {result} reference_{i}({arguments}) __asm__("__tlorig_{mangled}");\n'
                                f'extern "C" {result} reference_{i}({arguments}) {{ {body} }}\n')
                    calls.append(f'auto_{address[2:]}(&host);')
            cpp = root/'probe.cpp'; binary=root/'probe'
            pairs = ' || '.join(f'(a==(uint64_t)(uintptr_t)orig_{hex(0x100+i)[2:]} && b==(uint64_t)(uintptr_t)ours_{hex(0x100+i)[2:]})' for i in range(len(specs)))
            registry = 'static int known_pair(uint64_t a,uint64_t b) { return '+pairs+'; }\n'
            cpp.write_text(support+'\n'+'\n'.join(code)+registry+'\nint main(){'+''.join(calls)+'return 0;}\n')
            includes = ['-I'+str(include),
                        '-I'+str(Path(autotest.__file__).resolve().parents[2]/'decomp/hybrid'),
                        '-I'+str(Path(autotest.__file__).resolve().parents[2]/'decomp/include')]
            if pinned:
                obj = root / 'probe.o'
                toolchain.compile_source(cpp, obj, ['-std=gnu++98'] + includes, cache=False)
                library = toolchain.cache_dir() / 'gcc447/usr/lib64/libstdc++.so.6.0.13'
                compiled = subprocess.run(['g++', '-no-pie', str(obj), str(library),
                    '-Wl,-rpath,'+str(library.parent), '-o', str(binary)], capture_output=True, text=True)
            else:
                compiled = subprocess.run(['g++','-std=gnu++98','-O2','-fno-strict-aliasing',
                    '-D_GLIBCXX_USE_CXX11_ABI=0','-Wno-deprecated-declarations', *includes,
                    str(cpp),'-o',str(binary)],capture_output=True,text=True)
            self.assertEqual(0, compiled.returncode, compiled.stderr)
            if pinned:
                linked = subprocess.check_output(['ldd', str(binary)], text=True)
                self.assertIn(str(library.parent / 'libstdc++.so.6'), linked)
            result=subprocess.run([str(binary)],check=True,capture_output=True,text=True,timeout=35)
            rows={m[0]:tuple(map(int,m[1:])) for m in re.findall(
                r'stats (auto_\w+) same (\d+) both-failed (\d+) different (\d+) incomplete (\d+)',result.stdout)}
            self.assertEqual(len(specs),len(rows),result.stdout)
            for i,(name,params,mangled,expected) in enumerate(specs):
                with self.subTest(name=name):
                    observed = rows['auto_'+hex(0x100+i)[2:]]
                    if expected == 'different':
                        self.assertLess(observed[0], 40, result.stdout)
                        self.assertEqual((0,1,0), observed[1:], result.stdout)
                    else:
                        wanted = {'same':(40,0,0,0),'incomplete':(0,0,0,1)}[expected]
                        self.assertEqual(wanted, observed, result.stdout)


if __name__ == '__main__':
    unittest.main()
