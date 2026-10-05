"""Targeted branch mutations for original-vs-recovered Equipment particle selection.

Run from the repository root after the regular hand-test mutation pass. Only
scratch copies are changed; original game services stay read-only.
"""
import json
import shutil
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid

root = Path.cwd() / 'build-decomp/equipment-procs-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
import mutate
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x86f4a0'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentProcsTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('ignore_has_effect', 'hasEffect(type) &&', 'true &&'), ('ignore_skill_manager', '&& m_pSkillManager)', ')'), ('skip_transfer_list', 'activation<3', 'activation<2'), ('extra_activation', 'activation<3', 'activation<4'), ('ignore_effect_type', 'if (effects[i]->m_eType==type)', 'if (true)'), ('wrong_random_min', 'randomIntegerBetweenVolatile(0,100)', 'randomIntegerBetweenVolatile(1,100)'), ('wrong_random_max', 'randomIntegerBetweenVolatile(0,100)', 'randomIntegerBetweenVolatile(0,99)'), ('strict_chance', '>=static_cast<float>(roll)', '>static_cast<float>(roll)'), ('allow_nan_chance', 'effects[i]->value(static_cast<EEFFECT_VALUES>(0))>=static_cast<float>(roll)', '!(effects[i]->value(static_cast<EEFFECT_VALUES>(0))<static_cast<float>(roll))'), ('wrong_effect_value_field', 'static_cast<EEFFECT_VALUES>(0)', 'static_cast<EEFFECT_VALUES>(1)'), ('wrong_skill_level', 'effects[i]->m_sName,effects[i]->m_iLevel', 'effects[i]->m_sName,effects[i]->m_iLevel+1'), ('ignore_missing_skill', 'if (skill)', 'if (true)'), ('always_target_caster', '(target?target:character)->getPosition(true)', 'character->getPosition(true)'), ('local_target_position', '(target?target:character)->getPosition(true)', '(target?target:character)->getPosition(false)'), ('local_caster_position', 'Ogre::Vector3 position=character->getPosition(true);', 'Ogre::Vector3 position=character->getPosition(false);'), ('derived_orientation', 'character->m_pSceneNode->getOrientation()', 'character->m_pSceneNode->_getDerivedOrientation()'), ('copy_orientation', 'const Ogre::Quaternion& orientation', 'Ogre::Quaternion orientation'), ('wrong_activation', 'SKILL_ACTIVATION_PROC,position', 'SKILL_ACTIVATION_NORMAL,position'), ('swap_positions', 'position,orientation,targetPosition,target', 'targetPosition,orientation,position,target'), ('drop_target', 'position,orientation,targetPosition,target', 'position,orientation,targetPosition,NULL'), ('skip_execution', 'm_pSkillManager->executeSkill(skill,character,SKILL_ACTIVATION_PROC,position,orientation,targetPosition,target);', ';'), ('captured_count', 'for (unsigned int i=0;i<effects.size();++i)', 'unsigned int count=effects.size(); for (unsigned int i=0;i<count;++i)')]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + changed + tail)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_procs_differential')
        passed = any('equipment_procs_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_procs_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
