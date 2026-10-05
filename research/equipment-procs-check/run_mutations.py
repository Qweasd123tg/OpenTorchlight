"""Run original-vs-recovered mutations of Equipment particle selection only, from repo root.

Dependencies outside Equipment.cpp are resolved from the original ELF. The
normal tools/decomp/check.py separately verifies the integrated checkout.
"""
import sys
import shutil
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import mutate
import hybrid
root = Path.cwd() / 'build-decomp/equipment-procs-mutation-input'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
shutil.copyfile('decomp/src/Equipment.cpp', root / 'src/Equipment.cpp')
for name in ['EquipmentProcsTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutate.SRC = root / 'src'
hybrid.TESTS = root / 'tests'
sys.argv = ['mutate.py', '--hand', '--max', '24', '0x86f4a0']
mutate.main()
