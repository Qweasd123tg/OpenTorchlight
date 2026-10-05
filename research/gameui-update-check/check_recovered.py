"""Compare shared recovered implementation phases against original frames."""
from pathlib import Path
import sys,shutil,os
sys.path.insert(0,'tools/decomp')
import hybrid
root=Path('build-decomp/gameui-recovered-phases').resolve();(root/'src').mkdir(parents=True,exist_ok=True);(root/'tests'/'implementation').mkdir(parents=True,exist_ok=True)
shutil.copyfile('research/gameui-update-check/implementation/RecoveredPhases.h',root/'tests'/'implementation'/'RecoveredPhases.h')
shutil.copyfile('decomp/hybrid/tests/Detour.h',root/'tests'/'Detour.h')
for kind in ('ActiveFrame','ContextTips'):
    text=Path('research/gameui-update-check/GameUI'+kind+'Probe.cpp').read_text()
    text='#define OTL_RECOVERED_TEST_PLT\n#include "implementation/RecoveredPhases.h"\n'+text
    start=text.index('void model() {');end=text.index('void side(',start)
    code='''void model(){
        gameui_recovered::Labels labels={hpLabels[input->label],manaLabels[input->label],xpLabels[input->label],fleeLabels[input->label]};
        gameui_recovered::Frame frame(world->ui,world->client,&world->renderWindow,input->elapsed,labels);
        frame.run();
    }
'''
    text=text[:start]+code+text[end:]
    text=text.replace('TL_TEST(gameui_','TL_TEST(gameui_recovered_')
    (root/'tests'/(kind+'.cpp')).write_text(text)
for kind in ('Entry','Tooltip'):
    text=Path('research/gameui-update-check/GameUI'+kind+'Probe.cpp').read_text()
    text='#define OTL_RECOVERED_TEST_PLT\n#include "implementation/RecoveredPhases.h"\n'+text
    start=text.index('void model()');end=text.index('void side(',start)
    code='void model(){gameui_recovered::Labels labels={"","","",""};gameui_recovered::Frame frame(w->ui,NULL,NULL,0.125f,labels);if(!frame.entry())_exit(47); }\n'
    text=text[:start]+code+text[end:]
    text=text.replace('TL_TEST(gameui_','TL_TEST(gameui_recovered_')
    (root/'tests'/(kind+'.cpp')).write_text(text)
text=Path('research/gameui-update-check/GameUINoCharacterProbe.cpp').read_text()
text='#define OTL_RECOVERED_TEST_PLT\n#include "implementation/RecoveredPhases.h"\n'+text
start=text.index('void model()');end=text.index('void side(',start)
text=text[:start]+'void model(){gameui_recovered::Labels labels={"","","",""};gameui_recovered::Frame frame(w->ui,&w->client,&w->renderWindow,input->elapsed,labels);frame.noCharacterFrame();}\n'+text[end:]
text=text.replace('TL_TEST(gameui_','TL_TEST(gameui_recovered_')
(root/'tests'/'NoCharacter.cpp').write_text(text)
text=Path('research/gameui-update-check/GameUIMenuProbe.cpp').read_text()
text='#define OTL_RECOVERED_TEST_PLT\n#include "implementation/RecoveredPhases.h"\n'+text
start=text.index('void model()');end=text.index('void side(',start)
text=text[:start]+'void model(){gameui_recovered::Labels labels={"","","",""};gameui_recovered::Frame frame(w->ui,NULL,NULL,0.125f,labels);frame.serviceMenus(L"Retire",L"Cannot retire");frame.questAndFishing();}\n'+text[end:]
text=text.replace('TL_TEST(gameui_','TL_TEST(gameui_recovered_')
(root/'tests'/'Menus.cpp').write_text(text)
shutil.copyfile("research/gameui-update-check/GameUIMenuLifecycleProbe.cpp",root/"tests"/"MenuLifecycle.cpp")
shutil.copyfile("research/gameui-update-check/GameUIVisibleLabelsProbe.cpp",root/"tests"/"VisibleLabels.cpp")
shutil.copyfile("research/gameui-update-check/GameUIPerformanceProbe.cpp",root/"tests"/"Performance.cpp")
shutil.copyfile("research/gameui-update-check/GameUILabelCreationProbe.cpp",root/"tests"/"LabelCreation.cpp")
shutil.copyfile("research/gameui-update-check/GameUILocalizationProbe.cpp",root/"tests"/"Localization.cpp")
blob,loader=hybrid.build(out=root/'hybrid',src=root/'src',tests=sorted((root/'tests').glob('*.cpp')))
code,report=hybrid.selftest(blob,loader,only=os.environ.get("GAMEUI_TEST_ONLY"))
print('\n'.join(report));raise SystemExit(code)
