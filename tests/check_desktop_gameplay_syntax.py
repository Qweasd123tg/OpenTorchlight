#!/usr/bin/env python3
"""Compile-check the shared application used by window AND scenarios.
No source rewriting, window declarations or gameplay copies. Not a Wayland link test.
"""
import argparse
from pathlib import Path
import subprocess

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--root', type=Path, required=True)
    p.add_argument('--compiler', required=True)
    p.add_argument('--include-dirs', default='', help='CMake-evaluated include directories, separated by semicolons')
    p.add_argument('--system-include-dirs', default='', help='CMake-evaluated SYSTEM directories, separated by semicolons')
    p.add_argument('--definitions', default='', help='CMake-evaluated definitions, separated by semicolons')
    a = p.parse_args()
    result = subprocess.run([a.compiler, '-std=c++17', '-fsyntax-only', '-Wall', '-Wextra',
                             '-Wpedantic', '-Werror', '-I'+str(a.root/'include'),
                             *['-I'+path for path in a.include_dirs.split(';') if path],
                             *[argument for path in a.system_include_dirs.split(';') if path for argument in ('-isystem',path)],
                             *['-D'+value for value in a.definitions.split(';') if value],
                             str(a.root/'src/application.cpp')], check=False)
    if result.returncode == 0:
        print('Shared application compiled without rewriting. Window ABI/link not tested here.')
    return result.returncode
if __name__ == '__main__': raise SystemExit(main())
