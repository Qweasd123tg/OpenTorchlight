#!/usr/bin/env python3
"""Deletion-based reduction of a synthetic C++98 diagnostic, without an LLM.
Preserves a specific failure, not just a nonzero compiler exit status.
This is a small line-level pilot, not C-Reduce and not a general repair engine.
"""
from __future__ import annotations
import argparse
import json
import math
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=Path('results'))
    args = parser.parse_args()
    compiler = shutil.which('g++')
    if compiler is None:
        raise SystemExit('g++ is required.')
    output = args.output.resolve()
    fixtures = output / 'fixtures'
    fixtures.mkdir(parents=True, exist_ok=True)
    source = [f'struct Noise{i} {{ int value; }};\n' for i in range(80)]
    source.insert(20, 'struct CProbe { int x; int get() const; };\n')
    source.insert(61, 'int CProbe::get() { return x; }\n')
    original = ''.join(source)
    calls = 0
    cache: dict[str, bool] = {}
    with tempfile.TemporaryDirectory(prefix='ot-reduce-diagnostic-') as tmp:
        target = Path(tmp) / 'candidate.cpp'

        def interesting(lines: list[str]) -> bool:
            nonlocal calls
            text = ''.join(lines)
            if text in cache:
                return cache[text]
            target.write_text(text)
            cp = subprocess.run(
                [compiler, '-std=gnu++98', '-fsyntax-only', '-fdiagnostics-color=never', str(target)],
                capture_output=True, text=True, timeout=10,
                env={**os.environ, 'LC_ALL': 'C'})
            calls += 1
            errors = re.findall(r'error: ([^\n]+)', cp.stderr)
            result = (cp.returncode != 0 and bool(errors)
                      and all('no declaration matches' in e and 'CProbe::get()' in e for e in errors))
            cache[text] = result
            return result

        if not interesting(source):
            raise RuntimeError('Expected specific GCC diagnostic was not reproduced.')
        initial_lines = len(source)
        parts = 2
        current = source[:]
        while len(current) >= 2:
            width = math.ceil(len(current) / parts)
            changed = False
            for start in range(0, len(current), width):
                trial = current[:start] + current[start + width:]
                if interesting(trial):
                    current = trial
                    parts = max(parts - 1, 2)
                    changed = True
                    break
            if not changed:
                if parts >= len(current):
                    break
                parts = min(len(current), parts * 2)
        # A line-removal-minimal witness under the specified diagnostic predicate.
        one_minimal = all(not interesting(current[:i] + current[i+1:]) for i in range(len(current)))
        fixed = ''.join(current).replace('int CProbe::get()', 'int CProbe::get() const')
        repaired_not_interesting = not interesting([fixed])
        target.write_text(fixed)
        control = subprocess.run([compiler, '-std=gnu++98', '-fsyntax-only', str(target)],
                                 text=True, capture_output=True, timeout=10)
        assert one_minimal and repaired_not_interesting and control.returncode == 0
        (fixtures / 'reducer_before.cpp').write_text(original)
        (fixtures / 'reducer_minimal.cpp').write_text(''.join(current))
        (fixtures / 'reducer_fixed.cpp').write_text(fixed)
        results = {
            'scope': 'Synthetic source containing the demonstrated missing-const failure plus independent declarations.',
            'reducer': 'Own line deletion pilot, NOT C-Reduce.',
            'predicate': 'Compilation fails specifically with no declaration matches CProbe::get(); no other error class accepted.',
            'input_lines': initial_lines,
            'reduced_lines': len(current),
            'compiler_calls_for_predicate_including_checks': calls,
            'one_line_deletion_minimal': one_minimal,
            'minimal_source': ''.join(current),
            'restoring_const_compiles': control.returncode == 0,
            'game_sources_modified': False,
        }
    (output / 'reducer-results.json').write_text(json.dumps(results, ensure_ascii=False, indent=2) + '\n')
    print(json.dumps(results, ensure_ascii=False, indent=2))


if __name__ == '__main__':
    main()
