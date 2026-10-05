"""Headless destructor baseline with observed buffer-free counts/order (glibc).

The opt-in interposer watches selected buffer addresses only during destruction.
It never changes allocator behavior. A temporary library is preloaded only for these test runs;
normal check.py remains unchanged and runs the output/call-protocol checks.
"""
import sys
import shutil
import subprocess
import tempfile
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid
root = Path.cwd() / 'build-decomp/equipment-destructor-free-check'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
shutil.copyfile('decomp/src/Equipment.cpp', root / 'src/Equipment.cpp')
for name in ['EquipmentDestructorTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
hybrid.TESTS = root / 'tests'
with tempfile.TemporaryDirectory(prefix='otl-equipment-frees-') as temporary:
    shim = Path(temporary) / 'counter.so'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra',
                    'research/equipment-destructor-check/free_watch.c', '-o', str(shim)], check=True)
    original_env = hybrid.game_env
    def counted(*args, **kwargs):
        game, env = original_env(*args, **kwargs)
        env['LD_PRELOAD'] += ' ' + str(shim)
        env['OTL_FREES_REQUIRED'] = '1'
        return game, env
    hybrid.game_env = counted
    blob, loader = hybrid.build(out=root / 'hybrid', src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')))
    code, report = hybrid.selftest(blob, loader)
    print('\n'.join(report))
    sys.exit(code)
