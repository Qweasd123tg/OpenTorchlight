"""Headless mutation check including buffer-free count/order parity (GNU/Linux glibc).

The opt-in interposer watches selected buffers only during destruction. It never
changes allocator behavior. A temporary library is preloaded only for these test runs;
normal check.py remains unchanged and runs the output/call-protocol checks.
"""
import sys
import shutil
import subprocess
import tempfile
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import mutate
import hybrid
root = Path.cwd() / 'build-decomp/equipment-destructor-mutation-input'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
shutil.copyfile('decomp/src/Equipment.cpp', root / 'src/Equipment.cpp')
for name in ['EquipmentDestructorTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutate.SRC = root / 'src'
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
    sys.argv = ['mutate.py', '--hand', '--max', '24', '0x87d770']
    mutate.main()
