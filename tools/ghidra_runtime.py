"""Local Ghidra launch environment; never change a system JDK or tool install.

Some distributions ship jdk.compiler with java but omit the javac executable.
Ghidra's pinned LaunchSupport requires both names. A local javac launcher uses
that actual compiler module, with no version override or substitute compiler.
"""
from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import shlex
import shutil
import subprocess

from automation_state import validate_output, write_json

ROOT = Path(__file__).resolve().parents[1]


def headless_environment(analysis_root):
    analysis_root = Path(analysis_root).resolve()
    env = {**os.environ, 'XDG_CONFIG_HOME': str(analysis_root / 'config'),
           'XDG_CACHE_HOME': str(analysis_root / 'cache')}
    supplied = env.get('JAVA_HOME')
    if supplied:
        home = Path(supplied).resolve()
        executable = home / 'bin/java'
    else:
        found = shutil.which('java')
        if not found:
            raise ValueError('Java is absent; install a supported JDK before Ghidra')
        executable = Path(found).resolve()
        home = executable.parent.parent
    if not executable.is_file():
        raise ValueError('Java executable absent from selected Java home')
    version = subprocess.run([str(executable), '-version'], capture_output=True,
                             text=True, check=True, timeout=15)
    identity = {'java_executable': str(executable),
                'java_sha256': hashlib.sha256(executable.read_bytes()).hexdigest(),
                'java_version': (version.stderr + version.stdout).strip()}
    if (home / 'bin/javac').is_file():
        env['JAVA_HOME'] = str(home)
        return env, {**identity, 'kind': 'installed-jdk', 'java_home': str(home)}
    modules = subprocess.run([str(executable), '--list-modules'], capture_output=True,
                             text=True, check=True, timeout=15)
    if not any(line.split('@', 1)[0] == 'jdk.compiler' for line in modules.stdout.splitlines()):
        raise ValueError('Selected Java has no javac or jdk.compiler; a supported JDK is required')
    compiler = subprocess.run([str(executable), '-m',
                              'jdk.compiler/com.sun.tools.javac.Main', '-version'],
                             capture_output=True, text=True, check=True, timeout=15)
    sdk = analysis_root / 'java-sdk'
    validate_output(ROOT, sdk, [home], directory=True)
    launcher = '#!/bin/sh\nexec ' + shlex.quote(str(executable)) + ' -m jdk.compiler/com.sun.tools.javac.Main "$@"\n'
    record = {**identity, 'kind': 'local-jdk-compiler-launcher',
              'compiler_version': (compiler.stdout + compiler.stderr).strip(),
              'javac_launcher_sha256': hashlib.sha256(launcher.encode()).hexdigest()}
    marker = sdk / 'runtime.json'
    if sdk.exists():
        if (not marker.is_file() or json.loads(marker.read_text()) != record or
                not (sdk / 'bin/java').is_symlink() or
                (sdk / 'bin/java').resolve() != executable or
                (sdk / 'bin/javac').is_symlink() or
                (sdk / 'bin/javac').read_text() != launcher or
                not os.access(sdk / 'bin/javac', os.X_OK)):
            raise ValueError('Existing local JDK adapter differs; preserve it and use a fresh analysis root')
    else:
        (sdk / 'bin').mkdir(parents=True)
        (sdk / 'bin/java').symlink_to(executable)
        javac = sdk / 'bin/javac'
        javac.write_text(launcher)
        javac.chmod(0o755)
        write_json(marker, record)
    env['JAVA_HOME'] = str(sdk)
    return env, {**record, 'java_home': str(sdk)}
