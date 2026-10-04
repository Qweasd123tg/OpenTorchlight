"""Headless mutation check including malloc-call parity (GNU/Linux glibc).

The opt-in interposer counts calls only during getEquipmentEffects. It never
fails allocations. A temporary library is preloaded only for these test runs;
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
root = Path.cwd() / 'build-decomp/equipment-effects-mutation-input'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
shutil.copyfile('decomp/src/Equipment.cpp', root / 'src/Equipment.cpp')
for name in ['EquipmentEffectsTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutate.SRC = root / 'src'
hybrid.TESTS = root / 'tests'
with tempfile.TemporaryDirectory(prefix='otl-effects-alloc-') as temporary:
    shim = Path(temporary) / 'counter.so'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra',
                    'research/equipment-effects-check/malloc_counter.c', '-o', str(shim)], check=True)
    original_env = hybrid.game_env
    def counted(*args, **kwargs):
        game, env = original_env(*args, **kwargs)
        env['LD_PRELOAD'] += ' ' + str(shim)
        env['OTL_ALLOC_REQUIRED'] = '1'
        return game, env
    hybrid.game_env = counted
    sys.argv = ['mutate.py', '--hand', '--max', '24', '0x88c150']
    mutate.main()
