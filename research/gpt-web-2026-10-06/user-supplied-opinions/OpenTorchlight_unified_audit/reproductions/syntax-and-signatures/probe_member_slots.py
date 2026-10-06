#!/usr/bin/env python3
"""Compile synthetic C++98 class declarations and read exact virtual-slot fingerprints.
No class instance and no virtual function implementation is needed.
Representation assumption: standard Itanium C++ member pointers on x86-64,
2 eight-byte words (ptr, this adjustment), virtual ptr == slot byte offset + 1.
This is a pilot, not a drop-in general header verifier for the game.
"""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import platform
import subprocess


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--output', type=Path, default=Path('results'))
    a = p.parse_args()
    out = a.output.resolve()
    fx = out / 'fixtures'
    fx.mkdir(parents=True, exist_ok=True)
    if platform.machine() not in ('x86_64', 'AMD64'):
        raise SystemExit('Pilot requires x86-64 Itanium-style C++ ABI; do not infer ARM/Windows layouts.')
    results = {}
    for label, types in [('expected', ('int','long')), ('swapped', ('long','int'))]:
        source = '#include <stdio.h>\n#include <string.h>\nstruct COver {\n'
        source += ''.join('    virtual int f(' + t + ');\n' for t in types)
        source += '''};
// Deliberately NO definitions of either virtual f().
struct Rep { long long ptr, adjustment; };
int main() {
    int (COver::*pi)(int) = &COver::f;
    int (COver::*pl)(long) = &COver::f;
    typedef char rep_size_check[(sizeof(pi) == sizeof(Rep) && sizeof(pi) == 16) ? 1 : -1];
    Rep ri, rl;
    memcpy(&ri, &pi, sizeof(ri));
    memcpy(&rl, &pl, sizeof(rl));
    printf("%lld %lld %lld %lld\\n", ri.ptr, ri.adjustment, rl.ptr, rl.adjustment);
}
'''
        src, exe = fx / ('member_slots_' + label + '.cpp'), fx / ('member_slots_' + label + '.exe')
        src.write_text(source)
        cp = subprocess.run(['g++', '-std=gnu++98', '-O2', str(src), '-o', str(exe)],
                            text=True, capture_output=True, timeout=15)
        if cp.returncode:
            raise RuntimeError(cp.stderr)
        got = subprocess.run([str(exe)], text=True, capture_output=True, timeout=5)
        if got.returncode:
            raise RuntimeError(got.stderr)
        a,b,c,d = map(int, got.stdout.split())
        if not (a & 1 and c & 1):
            raise RuntimeError('Not the expected virtual member-pointer representation')
        results[label] = {'COver::f(int)': {'encoded_ptr': a, 'this_adjustment': b, 'slot': (a-1)//8},
                          'COver::f(long)': {'encoded_ptr': c, 'this_adjustment': d, 'slot': (c-1)//8},
                          'no_method_bodies_linked': True}
    assert results['expected']['COver::f(int)']['slot'] == 0
    assert results['expected']['COver::f(long)']['slot'] == 1
    assert results['swapped']['COver::f(int)']['slot'] == 1
    assert results['swapped']['COver::f(long)']['slot'] == 0
    (out / 'member-slot-results.json').write_text(json.dumps(results, indent=2) + '\n')
    print(json.dumps(results, indent=2))


if __name__ == '__main__':
    main()
