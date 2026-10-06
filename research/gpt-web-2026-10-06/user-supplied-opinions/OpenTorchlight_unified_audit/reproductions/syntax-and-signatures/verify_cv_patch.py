#!/usr/bin/env python3
"""Prepare and verify a narrow optional cv-qualifier patch in a TEMPORARY copy.
No game code, original repo files, acceptance policy or build flags are changed.
Usage: python3 verify_cv_patch.py /path/to/repo --output ./results
"""
from __future__ import annotations
import argparse
import difflib
import importlib.util
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('repo', type=Path)
    p.add_argument('--output', type=Path, default=Path('results'))
    a = p.parse_args()
    repo, out = a.repo.resolve(), a.output.resolve()
    out.mkdir(parents=True, exist_ok=True)
    changes = {
        'tools/decomp/ghidra_cpp.py': [
            ('head = f"{prefix}{f[\'demangled\'].split(\'(\')[0]}({params})"',
             'head = f"{prefix}{f[\'demangled\'].split(\'(\')[0]}({params})"\n'
             '            # elfdb.parse_demangled stores textual qualifiers, not mangling letters.\n'
             '            if f.get("cv"):\n'
             '                head += " " + f["cv"].strip()')],
        'tools/decomp/headers.py': [
            ('cv = " const" if "K" in (f.get("cv") or "") else ""',
             'cv = (" " + f["cv"].strip()) if f.get("cv") else ""'),
            ('return (f["method"], f.get("params") or "", "K" in (f.get("cv") or ""))',
             'return (f["method"], f.get("params") or "", tuple((f.get("cv") or "").split()))')]
    }
    patched, diff = {}, []
    for rel, substitutions in changes.items():
        old = (repo / rel).read_text()
        new = old
        for src, dst in substitutions:
            if new.count(src) != 1:
                raise RuntimeError(f'Expected exactly one archived context in {rel}: {src}')
            new = new.replace(src, dst)
        patched[rel] = new
        diff += list(difflib.unified_diff(old.splitlines(True), new.splitlines(True),
                                        fromfile='a/' + rel, tofile='b/' + rel))
    patch_path = out.parent / 'preserve-cv-qualifiers.patch'
    patch_path.write_text(''.join(diff))
    records = {'scope': 'Narrow cv identity repair only. Other findings NOT repaired by this patch.'}
    with tempfile.TemporaryDirectory(prefix='otl-cv-verify-') as t:
        temp = Path(t)
        tools = temp / 'tools/decomp'
        shutil.copytree(repo / 'tools/decomp', tools)
        # Apply the actual patch rather than only testing precomputed in-memory contents.
        applied = subprocess.run(['patch', '-p1', '-i', str(patch_path)], cwd=temp,
                                 text=True, capture_output=True, timeout=10)
        assert applied.returncode == 0, applied.stdout + applied.stderr
        for rel, expected in patched.items():
            assert (temp / rel).read_text() == expected
        records['patch_apply'] = applied.stdout.strip()
        sys.path.insert(0, str(tools))
        import ghidra_cpp as cpp
        import headers
        import elfdb
        qualifiers = ['', 'const', 'volatile', 'const volatile']
        per_case = []
        for q in qualifiers:
            demangled = 'CProbe::get()' + (' ' + q if q else '')
            qualified, params, cv, clone = elfdb.parse_demangled(demangled)
            f = {'method': 'get', 'params': params, 'cv': cv, 'kind': 'function', 'demangled': demangled}
            gen = headers.Gen.__new__(headers.Gen)
            gen.ghidra_return = lambda f: 'int'
            decl = gen.method_decl(f, 'CProbe', {'sys': set(), 'local': set(), 'forward': set()})
            code = cpp.convert('int __thiscall CProbe::get(CProbe *this)\n{\n return this->x;\n}\n', set(), f)
            src = temp / ('probe_' + (q.replace(' ', '_') or 'plain') + '.cpp')
            src.write_text('struct CProbe { int x; ' + decl + ' };\n' + code)
            compiled = subprocess.run(['g++', '-std=gnu++98', '-O2', '-c', str(src), '-o', str(src.with_suffix('.o'))],
                                      text=True, capture_output=True, timeout=15)
            assert compiled.returncode == 0, compiled.stderr
            assert (' ' + q + ';' in decl) if q else decl == 'int get();'
            per_case.append({'cv': q, 'declaration': decl, 'definition': code, 'compiled': True,
                             'signature': gen.virtual_signature(f)})
        assert len({tuple(r['signature'][2]) for r in per_case}) == 4
        records['qualifier_cases'] = per_case
        tests = ['test_ghidra_cpp', 'test_llm_loop_headers', 'test_mutate_overloads']
        test_results = {}
        for label, work in [('original', repo / 'tools/decomp'), ('patched', tools)]:
            result = subprocess.run([sys.executable, '-m', 'unittest', *tests], cwd=work,
                                    text=True, capture_output=True, timeout=25)
            test_results[label] = {'returncode': result.returncode, 'stdout': result.stdout, 'stderr': result.stderr}
        records['existing_tests'] = test_results
        if any(x['returncode'] for x in test_results.values()):
            raise RuntimeError('Existing test failure: ' + json.dumps(test_results))
    (out / 'cv-patch-verification.json').write_text(json.dumps(records, ensure_ascii=False, indent=2) + '\n')
    print(json.dumps(records, ensure_ascii=False, indent=2))


if __name__ == '__main__':
    main()
