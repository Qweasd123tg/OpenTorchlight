"""Characterize the original missing-image/forced-refresh edge headlessly.

This is not a differential acceptance test: it deliberately checks a crash
path using controlled window creation and image lookup collaborators. The
ordinary passing fixture never counts a both-crash outcome as equivalent.
"""
import shutil
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid
root = Path('build-decomp/equipment-icon-missing-image').resolve()
(root/'src').mkdir(parents=True,exist_ok=True)
(root/'tests').mkdir(parents=True,exist_ok=True)
shutil.copyfile('decomp/src/Equipment.cpp',root/'src/Equipment.cpp')
shutil.copyfile('decomp/hybrid/tests/Detour.h',root/'tests/Detour.h')
s=Path('decomp/hybrid/tests/EquipmentIconTest.cpp').read_text()
s='static bool unsafeRefresh=false;\n'+s
s=s.replace('if(repeat&&object->m_pIconWindow&&windows[0]->d_children.empty())force=false;', 'if(!unsafeRefresh&&repeat&&object->m_pIconWindow&&windows[0]->d_children.empty())force=false;')
s=s.split('TL_TEST(equipment_icon_differential)',1)[0]+r'''
TL_TEST(equipment_icon_missing_image_characterization){
    int failures=0;Case c={33,2};autotest::Outcome normal,brokenOriginal,brokenRecovered;
    unsafeRefresh=false;autotest::runChild(original,&c,normal);
    TL_CHECK(failures,WIFEXITED(normal.status)&&WEXITSTATUS(normal.status)==0);
    TL_CHECK(failures,normal.capture.length>=9*sizeof(int));
    if(normal.capture.length>=9*sizeof(int)){
        int fields[9];std::memcpy(fields,normal.capture.data+normal.capture.length-sizeof(fields),sizeof(fields));
        host->log("    missing image, original safe retry: parent %d, children %d, created %d, image lookups %d\n",fields[2],fields[3],fields[6],fields[7]);
        TL_CHECK(failures,fields[2]==0&&fields[3]==0&&fields[6]==2&&fields[7]==1);
    }
    unsafeRefresh=true;autotest::runChild(original,&c,brokenOriginal);autotest::runChild(recovered,&c,brokenRecovered);
    int a=WIFEXITED(brokenOriginal.status)?WEXITSTATUS(brokenOriginal.status):-1;
    int b=WIFEXITED(brokenRecovered.status)?WEXITSTATUS(brokenRecovered.status):-1;
    host->log("    characterization only: forced second call exits original=%d recovered=%d (139 is captured SIGSEGV)\n",a,b);
    TL_CHECK(failures,a==139);TL_CHECK(failures,b==139);return failures;
}
'''
(root/'tests/EquipmentIconTest.cpp').write_text(s)
b,l=hybrid.build(out=root/'hybrid',src=root/'src',tests=sorted((root/'tests').glob('*.cpp')))
code,report=hybrid.selftest(b,l)
print('\n'.join(report))
sys.exit(code)
