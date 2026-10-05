import sys, shutil
from pathlib import Path
sys.path.insert(0,'tools/decomp')
import hybrid, mutate
root=Path('build-decomp/equipment-eligibility-mutation-input').resolve()
(root/'src').mkdir(parents=True,exist_ok=True);(root/'tests').mkdir(exist_ok=True)
shutil.copyfile('decomp/src/Equipment.cpp',root/'src/Equipment.cpp')
for n in ['EquipmentCanEquipTest.cpp','EquipmentCanUseTest.cpp','Detour.h']:shutil.copyfile(Path('decomp/hybrid/tests')/n,root/'tests'/n)
mutate.SRC=root/'src';hybrid.TESTS=root/'tests'
sys.argv=['mutate.py','--hand','--max','24','0x86f150','0x86e710']
mutate.main()
