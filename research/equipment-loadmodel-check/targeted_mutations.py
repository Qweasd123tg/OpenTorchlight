"""Targeted branch mutations for original-vs-recovered Equipment effects.

Run from the repository root after the regular hand-test mutation pass. Only
scratch copies are changed; original game services stay read-only.
"""
import json
import shutil
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid

root = Path.cwd() / 'build-decomp/equipment-loadmodel-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
import mutate
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x887b30'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentLoadModelTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('omit_unload', 'unloadModel();', ';'), ('primary_factory_flag', 'm_pUnitModel=m_pResourceManager->createGenericModel(NULL,mesh.c_str(),NULL,false,false,true);', 'm_pUnitModel=m_pResourceManager->createGenericModel(NULL,mesh.c_str(),NULL,false,false,false);'), ('omit_primary_detach', 'm_pUnitModel->getSceneNode()->getParent()->removeChild(m_pUnitModel->getSceneNode());', ';'), ('omit_scene_attachment', 'm_pSceneNode->addChild(m_pUnitModel->getSceneNode());', ';'), ('wrong_visibility', 'setVisible(false,true);', 'setVisible(true,false);'), ('wrong_primary_position', 'm_pUnitModel->setPosition(0.0f,0.0f,0.0f);', 'm_pUnitModel->setPosition(1.0f,0.0f,0.0f);'), ('wrong_primary_queue', 'm_pUnitModel->m_pEntity->setRenderQueueGroup(50);', 'm_pUnitModel->m_pEntity->setRenderQueueGroup(51);'), ('ignore_secondary_override', 'secondaryMesh==EMPTY_WSTRING?', 'true?'), ('wrong_secondary_data_key', 'GetDataValue(L"MESHFILE_SECONDARY",EMPTY_WSTRING)', 'GetDataValue(L"MESHFILE",EMPTY_WSTRING)'), ('normalize_explicit_secondary', 'if (secondaryMesh.empty())', 'if (true)'), ('omit_secondary_detach', 'm_pUnitModelSecondary->getSceneNode()->getParent()->removeChild(m_pUnitModelSecondary->getSceneNode());', ';'), ('secondary_casts_shadows', 'm_pUnitModelSecondary->setCastsShadows(false);', 'm_pUnitModelSecondary->setCastsShadows(true);'), ('wrong_secondary_queue', 'm_pUnitModelSecondary->m_pEntity->setRenderQueueGroup(50);', 'm_pUnitModelSecondary->m_pEntity->setRenderQueueGroup(49);'), ('skip_whole_texture_override', 'if (!texture.empty()) m_pUnitModel->setTextureOverride(texture);', ';'), ('drop_last_replacement', 'i<count;', 'i+1<count;'), ('replace_texture_with_name', 'StringConvertToNarrow(name.c_str()),replacement', 'StringConvertToNarrow(name.c_str()),name')]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + changed + tail)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_loadmodel_differential')
        passed = any('equipment_loadmodel_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_loadmodel_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
