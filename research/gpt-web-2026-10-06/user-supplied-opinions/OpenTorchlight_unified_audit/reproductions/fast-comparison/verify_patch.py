#!/usr/bin/env python3
"""Apply the optional objdiff patch in a temporary directory and compare outputs.

Never modifies the checkout. Requires Python 3, g++, objdump and patch.
"""
from __future__ import annotations
import argparse
import importlib.util
import io
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('root', type=Path)
    parser.add_argument('--out', type=Path, default=Path('patch-verification.json'))
    args = parser.parse_args()
    tools = args.root.resolve() / 'tools/decomp'
    if not (tools / 'objdiff.py').is_file():
        parser.error('root does not contain tools/decomp/objdiff.py')
    sys.path.insert(0, str(tools))
    import objdiff
    import test_objdiff_literals
    report = {'scope': 'Patch applied only to a temporary copy; synthetic GCC objects and normalizer unit tests.', 'cases': []}
    with tempfile.TemporaryDirectory(prefix='otl-patch-') as folder:
        work = Path(folder)
        target = work / 'tools/decomp/objdiff.py'
        target.parent.mkdir(parents=True)
        shutil.copyfile(tools / 'objdiff.py', target)
        patch = Path(__file__).with_name('objdiff-section-index.patch')
        completed = subprocess.run(['patch', '--batch', '-p1', '-i', str(patch)], cwd=work, text=True, capture_output=True, timeout=20, check=True)
        report['patch_output'] = completed.stdout.strip()
        spec = importlib.util.spec_from_file_location('objdiff_patched_probe', target)
        if spec is None or spec.loader is None:
            raise RuntimeError('Cannot load temporary patched module')
        patched = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(patched)
        cases = {
            '500_functions': '\n'.join(f'extern "C" __attribute__((noinline)) unsigned f_{i}(unsigned x) {{return x*{2*i+3}u+{i}u;}}' for i in range(500)),
            'aliases_and_sections': r'''
extern "C" int base(int x) {return x+1;}
extern "C" int alias(int) __attribute__((alias("base")));
extern "C" __attribute__((weak)) int weakfunc(int x) {return x*3;}
struct Root {virtual ~Root();}; Root::~Root() {}
struct Other {virtual ~Other();}; Other::~Other() {}
struct Child: Root, Other {virtual ~Child();}; Child::~Child() {}
extern void may_throw();
extern void sink(const char*);
extern "C" int excepts() {try {may_throw();} catch (int) {return 7;} return 0;}
extern "C" void strings() {sink("test literal");}
'''
        }
        for label, source in cases.items():
            cpp = work / f'{label}.cpp'
            obj = work / f'{label}.o'
            cpp.write_text(source)
            subprocess.run(['g++', '-std=gnu++98', '-O2', '-fno-ipa-icf', '-c', str(cpp), '-o', str(obj)], check=True, timeout=30)
            original_result = objdiff.object_functions(obj)
            patched_result = patched.object_functions(obj)
            if original_result != patched_result:
                raise AssertionError(f'Normalizer output differs: {label}')
            report['cases'].append({'name': label, 'functions': len(original_result), 'outputs_identical': True})
        for label, module in [('original', objdiff), ('patched', patched)]:
            test_objdiff_literals.objdiff = module
            suite = unittest.defaultTestLoader.loadTestsFromModule(test_objdiff_literals)
            stream = io.StringIO()
            result = unittest.TextTestRunner(stream=stream, verbosity=2).run(suite)
            report[label + '_normalizer_tests'] = {'run': result.testsRun, 'successful': result.wasSuccessful(), 'log': stream.getvalue()}
            if not result.wasSuccessful():
                raise AssertionError(stream.getvalue())
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(json.dumps(report, ensure_ascii=False, indent=2))
    print(json.dumps(report, ensure_ascii=False, indent=2))
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
