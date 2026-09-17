#!/usr/bin/env python3
"""Build a PIE launcher for this shared Python, without overwriting existing files.

Linux reference-test infrastructure only. Requires a C compiler, Python headers
and the matching shared libpython. A normal PIE Python needs no extra launcher.
"""
from __future__ import annotations

import argparse
import os
from pathlib import Path
import shlex
import struct
import subprocess
import sys
import sysconfig
import tempfile


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    output = args.output.absolute()
    try:
        if sys.platform != 'linux' or not sysconfig.get_config_var('Py_ENABLE_SHARED'):
            raise ValueError('Requires Linux and a shared Python build')
        if output.exists() or output.is_symlink():
            raise FileExistsError(f'Refusing to overwrite {output}')
        include = Path(sysconfig.get_path('include'))
        libdir = Path(sysconfig.get_config_var('LIBDIR') or '')
        library = str(sysconfig.get_config_var('LDLIBRARY') or '')
        if not (include / 'Python.h').is_file() or not (libdir / library).is_file():
            raise ValueError('Matching Python development headers/shared library are absent')
        output.parent.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(prefix='.python-pie-', dir=output.parent) as temp:
            candidate = Path(temp) / 'python-pie'
            command = shlex.split(os.environ.get('CC', 'cc')) + [
                str(Path(__file__).with_name('python_pie_launcher.c')),
                '-I' + str(include), '-L' + str(libdir), '-Wl,-rpath,' + str(libdir),
                '-l:' + library, '-fPIE', '-pie', '-o', str(candidate)]
            subprocess.run(command, check=True)
            header = candidate.read_bytes()[:20]
            if header[:4] != b'\x7fELF' or len(header) != 20 or header[5] not in (1, 2):
                raise ValueError('Compiler did not produce ELF')
            if struct.unpack('<H' if header[5] == 1 else '>H', header[16:18])[0] != 3:
                raise ValueError('Compiler did not produce a position-independent executable')
            actual = subprocess.check_output([str(candidate), '-c',
                'import sys; print(".".join(map(str,sys.version_info[:3])))'], text=True).strip()
            if actual != '.'.join(map(str, sys.version_info[:3])):
                raise ValueError('Launcher selected the wrong Python version')
            # Hard-link is atomic and fails when output already exists.
            os.link(candidate, output)
        print(output)
        return 0
    except (OSError, ValueError, subprocess.SubprocessError) as exc:
        print(f'ERROR: {exc}', file=sys.stderr)
        return 1


if __name__ == '__main__':
    raise SystemExit(main())
