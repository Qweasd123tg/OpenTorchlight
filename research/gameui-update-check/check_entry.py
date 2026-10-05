"""Original-only, headless entry characterization. No production hooks."""
from pathlib import Path
import sys, shutil, os
sys.path.insert(0,'tools/decomp')
import hybrid
root=Path(os.environ.get('GAMEUI_ENTRY_ROOT','build-decomp/gameui-entry-characterization')).resolve()
(root/'src').mkdir(parents=True,exist_ok=True)
(root/'tests').mkdir(exist_ok=True)
shutil.copyfile(os.environ.get('GAMEUI_ENTRY_SOURCE','research/gameui-update-check/GameUIEntryProbe.cpp'),root/'tests/GameUIEntryProbe.cpp')
shutil.copyfile('decomp/hybrid/tests/Detour.h',root/'tests/Detour.h')
blob,loader=hybrid.build(out=root/'hybrid',src=root/'src',tests=sorted((root/'tests').glob('*.cpp')))
code,report=hybrid.selftest(blob,loader,only=os.environ.get("GAMEUI_TEST_ONLY"))
print('\n'.join(report))
raise SystemExit(code)
