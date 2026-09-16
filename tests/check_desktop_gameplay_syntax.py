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
    a = p.parse_args()
    result = subprocess.run([a.compiler, '-std=c++17', '-fsyntax-only', '-Wall', '-Wextra',
                             '-Wpedantic', '-Werror', '-I'+str(a.root/'include'),
                             str(a.root/'src/application.cpp')], check=False)
    if result.returncode == 0:
        print('Shared application compiled without rewriting. Window ABI/link not tested here.')
    return result.returncode
if __name__ == '__main__': raise SystemExit(main())
