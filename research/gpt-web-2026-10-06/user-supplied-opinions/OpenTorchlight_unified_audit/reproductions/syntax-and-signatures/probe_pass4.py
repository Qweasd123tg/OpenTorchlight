#!/usr/bin/env python3
"""Read-only probes of the archived decomp tools. No game or LLM is run.

Usage: python3 probe_pass4.py /path/to/OpenTorchlight-main --output ./results
Requires Python 3.10+, g++, readelf. Tested with GCC 14.2 on x86-64 Linux.
Only fixture source, object files, executables and reports under --output are written.
"""
from __future__ import annotations
import argparse
from collections import Counter, defaultdict
import importlib
import json
from pathlib import Path
import re
import subprocess
import sys
import tempfile
from unittest.mock import patch


def run(args: list[str], *, cwd: Path | None = None) -> subprocess.CompletedProcess:
    return subprocess.run(args, cwd=cwd, text=True, capture_output=True, timeout=20)


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('repo', type=Path)
    ap.add_argument('--output', type=Path, default=Path('results'))
    args = ap.parse_args()
    repo = args.repo.resolve()
    out = args.output.resolve()
    out.mkdir(parents=True, exist_ok=True)
    fx = out / 'fixtures'
    fx.mkdir(exist_ok=True)
    sys.dont_write_bytecode = True
    sys.path.insert(0, str(repo / 'tools/decomp'))
    cpp = importlib.import_module('ghidra_cpp')
    headers = importlib.import_module('headers')
    parallel = importlib.import_module('parallel')
    elfdb = importlib.import_module('elfdb')
    results = {'compiler': run(['g++', '--version']).stdout.splitlines()[0],
               'scope': 'Archived tool functions and synthetic C++98 fixtures; not the original game.'}

    def compile_source(name: str, source: str, execute: bool = True):
        src = fx / (name + '.cpp')
        target = fx / (name + ('.exe' if execute else '.o'))
        src.write_text(source)
        cmd = ['g++', '-std=gnu++98', '-O2', '-fno-strict-aliasing']
        if not execute:
            cmd += ['-c']
        p = run(cmd + [str(src), '-o', str(target)])
        result = {'compiled': p.returncode == 0, 'stderr': p.stderr}
        if p.returncode == 0 and execute:
            x = run([str(target)])
            result.update(returncode=x.returncode, stdout=x.stdout.strip())
        return result

    # 1. A known direct call must not acquire virtual dispatch.
    raw = ('int __thiscall CWrapper::probe(CWrapper *this, CBase *param_1)\n'
           '{\n return CBase::step(param_1);\n}\n')
    f = {'kind': 'function', 'demangled': 'CWrapper::probe(CBase*)', 'params': 'CBase*', 'cv': ''}
    converted = cpp.convert(raw, {('CBase', 'step')}, f)
    prelude = ('#include <stdio.h>\n'
               'struct CBase { virtual int step() { return 11; } };\n'
               'struct CDerived : CBase { int step() { return 22; } };\n'
               'struct CWrapper { int probe(CBase*); };\n')
    tail = 'int main() { CDerived d; CWrapper w; printf("%d\\n", w.probe(&d)); }\n'
    direct = compile_source('direct_expected', prelude +
             'int CWrapper::probe(CBase* p) { return p->CBase::step(); }\n' + tail)
    rewritten = compile_source('direct_rewritten', prelude + converted + tail)
    assert direct.get('stdout') == '11' and rewritten.get('stdout') == '22'
    results['direct_call'] = {'raw': raw, 'converted': converted,
                              'expected_direct': direct, 'actual_rewrite': rewritten}

    # 2. Truth equivalence does not imply value equivalence outside a boolean context.
    bool_expr = 'int normalize(int x) { return x != false; }'
    rewritten_bool = cpp.tidy_expressions(bool_expr)
    main_bool = ('\nint main(){ printf("%d %d %d\\n", normalize(-3), '
                 'normalize(0), normalize(2)); }\n')
    before = compile_source('bool_expected', '#include <stdio.h>\n' + bool_expr + main_bool)
    after = compile_source('bool_rewritten', '#include <stdio.h>\n' + rewritten_bool + main_bool)
    assert before.get('stdout') == '1 0 1' and after.get('stdout') == '-3 0 2'
    results['boolean_value'] = {'before_code': bool_expr, 'after_code': rewritten_bool,
                               'before': before, 'after': after}

    # 3. A whole-text regex changes the contents of actual string literals.
    raw_literal = 'const char *message(void)\n{\n return "bad UTF-8 continuation byte";\n}\n'
    converted_literal = cpp.convert(raw_literal, set())
    tail_literal = '\nint main() { puts(message()); }\n'
    before = compile_source('literal_expected', '#include <stdio.h>\n' + raw_literal + tail_literal)
    after = compile_source('literal_rewritten', '#include <stdio.h>\n' + converted_literal + tail_literal)
    assert before['stdout'] != after['stdout']
    results['literal'] = {'raw': raw_literal, 'converted': converted_literal, 'before': before, 'after': after}
    literal_re = re.compile(r'(?:L)?"(?:[^"\\\n]|\\.)*"')
    literal_hits = []
    for p in sorted((repo / 'research/decompiled-core').glob('*.c')):
        text = p.read_text(errors='replace')
        for m in literal_re.finditer(text):
            literal = m.group()
            changed = literal
            for pattern, replacement in cpp.TYPES:
                changed = re.sub(pattern, replacement, changed)
            if literal != changed:
                literal_hits.append({'file': str(p.relative_to(repo)),
                                     'line': text.count('\n', 0, m.start()) + 1,
                                     'before': literal, 'after': changed})
    results['archived_literal_hits'] = literal_hits

    # Minimal known metadata avoids invoking elfdb or a missing GCC 4.4 toolchain.
    def gen_for(db):
        gen = headers.Gen.__new__(headers.Gen)
        gen.db, gen.funcs = db, db['functions']
        gen.types, gen.return_types = {}, {}
        gen.game_classes = set(db['classes'])
        gen.hand, gen.hand_enums, gen.hand_types = {}, {}, {}
        gen.hand_templates = set()
        gen.enums, gen.typedefs = set(), set()
        gen.ogre, gen.cegui = set(), set()
        gen.ghidra_return = lambda f: 'int'   # explicitly known return type of our fixtures
        return gen

    # 4. elfdb stores textual cv; both emitter paths lose it.
    qualified, params, cv, clone = elfdb.parse_demangled('CProbe::get() const')
    f = {'kind': 'function', 'demangled': 'CProbe::get() const', 'params': params, 'cv': cv,
         'method': 'get', 'qualified': qualified, 'scope': 'CProbe', 'address': '0x1000', 'tu': 1}
    gen = gen_for({'classes': {'CProbe': {}}, 'functions': {'0x1000': f}, 'tus': []})
    decl = gen.method_decl(f, 'CProbe', {'sys': set(), 'local': set(), 'forward': set()})
    raw_const = 'int __thiscall CProbe::get(CProbe *this)\n{\n return this->x;\n}\n'
    converted_const = cpp.convert(raw_const, set(), f)
    prelude_const = '#include <stdio.h>\nstruct CProbe { int x; int get() const; };\n'
    const_result = compile_source('const_rewritten', prelude_const + converted_const, execute=False)
    fixed = converted_const.replace('CProbe::get()', 'CProbe::get() const', 1)
    fixed_result = compile_source('const_control', prelude_const + fixed, execute=False)
    assert decl == 'int get();' and not const_result['compiled'] and fixed_result['compiled']
    results['const_schema'] = {'elfdb_cv': cv, 'generated_declaration': decl, 'converted': converted_const,
                               'actual_compile': const_result, 'control_restoring_const': fixed_result}

    # 5. Per-name declaration completion skips a missing overload when ANY overload is present.
    with tempfile.TemporaryDirectory(prefix='otl-headers-probe-') as temp:
        root = Path(temp)
        inc = root / 'decomp/include'
        inc.mkdir(parents=True)
        (inc / 'Probe.h').write_text('struct CProbe\n{\n int read(int);\n};\n')
        fs = {}
        for i, ptype in enumerate(('int', 'double')):
            a = hex(0x1000 + i * 16)
            fs[a] = {'address': a, 'tu': 1, 'scope': 'CProbe', 'method': 'read', 'params': ptype,
                     'cv': '', 'kind': 'function', 'qualified': 'CProbe::read',
                     'demangled': 'CProbe::read(' + ptype + ')'}
        db = {'functions': fs, 'classes': {'CProbe': {'methods': list(fs)}}, 'tus': []}
        gen = gen_for(db)
        gen.hand = {'CProbe': 'Probe.h'}
        with patch.object(headers, 'ROOT', root), patch.object(headers, 'INCLUDE', inc):
            added = gen.trial_include()
            produced = (root / 'build-decomp/include-trial/Probe.h').read_text()
        assert added == 0 and 'read(double)' not in produced
        # It may compile by silently selecting the wrong overload, not only fail compilation.
        runtime_header = produced + 'int CProbe::read(int) { return 11; }\n'
        tail_over = 'int main(){ CProbe p; printf("%d\\n", p.read(1.5)); }\n'
        missing = compile_source('overload_missing', '#include <stdio.h>\n' + runtime_header + tail_over)
        control_header = ('struct CProbe { int read(int); int read(double); };\n'
                          'int CProbe::read(int) { return 11; }\n'
                          'int CProbe::read(double) { return 22; }\n')
        control = compile_source('overload_control', '#include <stdio.h>\n' + control_header + tail_over)
        assert missing['stdout'] == '11' and control['stdout'] == '22'
        results['missing_overload'] = {'added': added, 'generated_header': produced,
                                       'with_missing_declaration': missing, 'complete_declarations': control}
        # An unrelated class member suppresses a namespace function with the same short name.
        (inc / 'Probe.h').write_text('struct CNoise { int parse(int); };\n')
        nf = {'0x2000': {'address': '0x2000', 'tu': 2, 'scope': 'TOOLS', 'method': 'parse',
                         'params': 'int', 'cv': '', 'kind': 'function', 'qualified': 'TOOLS::parse',
                         'demangled': 'TOOLS::parse(int)'}}
        ng = gen_for({'functions': nf, 'classes': {}, 'tus': [{'id': 2, 'kind': 'game', 'name': 'tools.cpp'}]})
        ng.hand = {'CNoise': 'Probe.h'}
        with patch.object(headers, 'INCLUDE', inc):
            nheader = ng.namespaces_header()
        assert 'namespace TOOLS' not in nheader
        results['namespace_suppression'] = {'unrelated_header': 'struct CNoise { int parse(int); };',
                                            'wanted': 'TOOLS::parse(int)', 'generated': nheader}

    # 6. Vtable order validation based on short names misses swapped overloads.
    vtable_results = {}
    db = {'vtables': {'COver': {'groups': [{'slots': ['0x3000', '0x3010']}]}},
          'functions': {
              '0x3000': {'names': ['_ZN5COver1fEi'], 'scope': 'COver', 'method': 'f', 'params': 'int'},
              '0x3010': {'names': ['_ZN5COver1fEl'], 'scope': 'COver', 'method': 'f', 'params': 'long'}}}
    for label, order in [('expected', ('int', 'long')), ('swapped', ('long', 'int'))]:
        src = fx / ('vtable_' + label + '.cpp')
        obj = src.with_suffix('.o')
        src.write_text('struct COver {\n' + ''.join(' virtual int f(' + t + ');\n' for t in order) +
                       '};\nint COver::f(int) { return 11; }\nint COver::f(long) { return 22; }\nCOver instance;\n')
        p = run(['g++', '-std=gnu++98', '-O2', '-fdump-lang-class', '-c', str(src), '-o', str(obj)])
        if p.returncode:
            raise RuntimeError(p.stderr)
        dumps = sorted(fx.glob(src.name + '.*.class'))
        if not dumps:
            raise RuntimeError('No GCC class dump for ' + str(src))
        dump = dumps[0].read_text()
        # GCC 14 prints a cast on every function entry; the archived parser expects
        # only header metadata to have that prefix. Do NOT hide this incompatibility.
        # A compatibility-shaped input strips only that redundant cast on COver::f.
        compat_dump = dump.replace('(int (*)(...))COver::f', 'COver::f')
        relocs = run(['readelf', '-rW', str(obj)]).stdout
        # Only function references in a vtable data relocation section, not .eh_frame.
        target_order = []
        in_vtable = False
        for line in relocs.splitlines():
            if line.startswith('Relocation section'):
                in_vtable = ('data.rel.ro' in line) and ('_ZTV5COver' in line)
            if in_vtable:
                m = re.search(r'(_ZN5COver1fE[il])\b', line)
                if m:
                    target_order.append(m.group(1))
        vtable_results[label] = {'raw_gcc14_parsed': headers.dumped_vtable(dump, 'COver'),
                                 'raw_gcc14_mismatch': headers.vtable_mismatch(db, 'COver', dump),
                                 'compatibility_adjustment': 'Remove function-entry cast only; header casts unchanged.',
                                 'parsed_by_project': headers.dumped_vtable(compat_dump, 'COver'),
                                 'mismatch': headers.vtable_mismatch(db, 'COver', compat_dump),
                                 'real_relocation_targets': target_order}
        (fx / ('vtable_' + label + '.relocations.txt')).write_text(relocs)
    assert vtable_results['expected']['mismatch'] is None
    assert vtable_results['swapped']['mismatch'] is None
    assert vtable_results['expected']['real_relocation_targets'] == ['_ZN5COver1fEi', '_ZN5COver1fEl']
    assert vtable_results['swapped']['real_relocation_targets'] == ['_ZN5COver1fEl', '_ZN5COver1fEi']
    results['vtable_overloads'] = vtable_results

    # 7. Queue eligibility, not a claim about acceptance of the synthetic files.
    with tempfile.TemporaryDirectory(prefix='otl-queue-probe-') as temp:
        root = Path(temp)
        (root / 'decomp/src').mkdir(parents=True)
        (root / 'decomp/include').mkdir()
        (root / 'decomp/src/Partial.cpp').write_text('// Only one of two methods was recovered.\n')
        tus = [{'id': i, 'name': n, 'kind': 'game'} for i, n in enumerate(('Partial.cpp','Large.cpp','Small.cpp'))]
        fs = {hex(i + 100): {'tu': t, 'size': size, 'kind': 'function', 'scope': ''}
              for i, (t, size) in enumerate([(0, 30), (0, 40), (1, 60001), (2, 100)])}
        db = {'tus': tus, 'functions': fs, 'classes': {}}
        with patch.object(parallel, 'ROOT', root), patch.object(parallel, 'CLAIMS', root / 'claims.json'), \
             patch.object(parallel, 'OWNERS', root / 'owners.json'):
            rows = parallel.candidates(db)
        assert [r[2] for r in rows] == ['Small.cpp']
        results['queue'] = {'candidates': rows,
                            'excluded_despite_no_acceptance_evidence': ['Partial.cpp', 'Large.cpp']}

    # Historical, bounded size evidence; NOT the current remaining work or accepted inventory.
    measured_path = repo / 'research/decomp-automation-audit-2026-10-04/measured.json'
    measured = json.loads(measured_path.read_text())
    by_tu = defaultdict(list)
    for f in measured:
        by_tu[f['tu']].append(f)
    large = {name: sum(f['bytes'] for f in fs) for name, fs in by_tu.items()
             if sum(f['bytes'] for f in fs) > parallel.LARGE_TU}
    existing = [f for f in measured if (repo / 'decomp/src' / f['tu']).exists()]
    combined = [f for f in measured if f['tu'] in large or (repo / 'decomp/src' / f['tu']).exists()]
    results['historical_queue_inventory'] = {
        'source': str(measured_path.relative_to(repo)), 'date': '2026-10-04',
        'meaning': 'Location of historical >=1024-byte sample, not outstanding or accepted work today.',
        'sample_functions': len(measured), 'sample_bytes': sum(f['bytes'] for f in measured),
        'sample_functions_in_existing_source_files': len(existing),
        'sample_bytes_in_existing_source_files': sum(f['bytes'] for f in existing),
        'tus_over_60000_using_only_this_sample_as_lower_bound': large,
        'sample_covered_by_either_exclusion': len(combined),
        'sample_bytes_covered_by_either_exclusion': sum(f['bytes'] for f in combined)}

    # How often full function identity differs in the archived strong C-prefixed symbols.
    cv_symbols, overloads = [], defaultdict(set)
    for line in (repo / 'research/original-symbols.txt').read_text().splitlines():
        m = re.match(r'^([0-9a-f]+)\s+([0-9a-f]+)\s+([Tt])\s+(.+)$', line)
        if not m:
            continue
        address, size, bind, demangled = m.groups()
        qualified, params, cv, clone = elfdb.parse_demangled(demangled)
        if not re.match(r'^C[A-Z]\w*::', qualified) or clone or 'thunk to ' in demangled:
            continue
        if cv:
            cv_symbols.append({'address': '0x' + address.lstrip('0'), 'name': demangled, 'cv': cv})
        if params is not None:
            overloads[qualified].add((params, cv))
    results['identity_inventory'] = {'meaning': 'Strong C-prefixed class symbols only; not remaining work.',
                                     'cv_qualified_symbols': len({r['address'] for r in cv_symbols}),
                                     'examples': cv_symbols[:12],
                                     'overloaded_qualified_names': sum(len(v) > 1 for v in overloads.values())}
    (out / 'probe-results.json').write_text(json.dumps(results, ensure_ascii=False, indent=2) + '\n')
    print(json.dumps({k: v for k, v in results.items() if k in ('compiler','queue','historical_queue_inventory','identity_inventory')},
                     ensure_ascii=False, indent=2))
    print('All assertions passed. Detailed results:', out / 'probe-results.json')


if __name__ == '__main__':
    main()
