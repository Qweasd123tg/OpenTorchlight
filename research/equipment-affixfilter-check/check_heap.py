"""Scoped allocation/free parity; standalone fixture with original services."""
import os,sys,subprocess,shutil
from pathlib import Path
sys.path.insert(0,'tools/decomp')
import hybrid
root=Path('build-decomp/equipment-affixfilter-heap').resolve()
(root/'src').mkdir(parents=True,exist_ok=True);(root/'tests').mkdir(exist_ok=True)
shutil.copyfile('decomp/src/Equipment.cpp',root/'src/Equipment.cpp')
for n in ['EquipmentAffixFilterTest.cpp','Detour.h']:shutil.copyfile(Path('decomp/hybrid/tests')/n,root/'tests'/n)
lib=root/'heap_counter.so'
subprocess.run(['cc','-shared','-fPIC','-O2','-Wall','-Wextra','research/equipment-affixfilter-check/heap_counter.c','-o',str(lib)],check=True)
old=hybrid.game_env
def env(*a,**kw):
 game,e=old(*a,**kw);e['LD_PRELOAD']+=':'+str(lib);e['OTL_FILTER_HEAP_REQUIRED']='1';return game,e
hybrid.game_env=env
blob,loader=hybrid.build(out=root/'hybrid',src=root/'src',tests=sorted((root/'tests').glob('*.cpp')))
code,report=hybrid.selftest(blob,loader);print('\n'.join(report));raise SystemExit(code)
