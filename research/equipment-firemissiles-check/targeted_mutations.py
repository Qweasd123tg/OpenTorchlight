"""Targeted branch mutations for original-vs-recovered Equipment missile launch.

Run from the repository root after the regular hand-test mutation pass. Only
scratch copies are changed; original game services stay read-only.
"""
import json
import shutil
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid

root = Path.cwd() / 'build-decomp/equipment-firemissiles-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
import mutate
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x87f120'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentFireMissilesTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('swap_hand_nodes', '? shooter->m_pLeftHandNode : shooter->m_pRightHandNode', '? shooter->m_pRightHandNode : shooter->m_pLeftHandNode'), ('wrong_aim_absolute', 'direction=target->getPosition(true)-origin', 'direction=target->getPosition(false)-origin'), ('wrong_target_absolute', 'targetPosition=target?target->getPosition(true)', 'targetPosition=target?target->getPosition(false)'), ('no_aim_normalise', 'direction.normalise();', ';'), ('wrong_aim_origin', 'direction=target->getPosition(true)-origin', 'direction=target->getPosition(true)'), ('wrong_weapon_scale', 'GetDataValue(L"WEAPON_SCALE",1.0f)', 'GetDataValue(L"WEAPON_SCALE",2.0f)'), ('wrong_bbox_axis', 'getBoundingBox().getSize().y', 'getBoundingBox().getSize().z'), ('wrong_model_offset', 'scale*0.8f', 'scale*1.0f'), ('wrong_no_model_offset', 'Ogre::Vector3 offset=direction', 'Ogre::Vector3 offset=Ogre::Vector3::ZERO'), ('wrong_listener_subobject', 'iMissile* listener=static_cast<iMissile*>(this)', 'iMissile* listener=reinterpret_cast<iMissile*>(this)'), ('duplicate_listener', 'if (missile->m_Listeners.find(listener)==-1)', 'if (true)'), ('skip_listener', 'missile->m_Listeners.add(listener);', ';'), ('reverse_cross_product', 'Ogre::Vector3::UNIT_Y.crossProduct(direction)', 'direction.crossProduct(Ogre::Vector3::UNIT_Y)'), ('wrong_axes', 'orientation.FromAxes(right,Ogre::Vector3::UNIT_Y,direction)', 'orientation.FromAxes(direction,Ogre::Vector3::UNIT_Y,right)'), ('wrong_firing_owner', 'fireMissile(getEquippedTo(),launch', 'fireMissile(shooter,launch'), ('wrong_launch_origin', 'fireMissile(getEquippedTo(),launch', 'fireMissile(getEquippedTo(),origin'), ('discard_target', 'fireMissile(getEquippedTo(),launch,orientation,target,targetPosition)', 'fireMissile(getEquippedTo(),launch,orientation,NULL,targetPosition)'), ('discard_target_position', 'orientation,target,targetPosition)', 'orientation,target,Ogre::Vector3::ZERO)'), ('skip_weak_registration', 'reference->setObject(missile);', ';'), ('skip_reference_retention', 'm_ActiveMissileRefs.add(reference);', ';'), ('snapshot_target_too_early', '    Ogre::Vector3 launch=origin+offset;\n    CResourceManager* resources=m_pResourceManager;\n    CMissile* missile=resources->getMissilePreloader()->createNewMissileRef(resources,m_sUnknown400);\n    if (!missile)\n        return false;\n    iMissile* listener=static_cast<iMissile*>(this);\n    if (missile->m_Listeners.find(listener)==-1)\n        missile->m_Listeners.add(listener);\n    Ogre::Vector3 targetPosition=target?target->getPosition(true):Ogre::Vector3::ZERO;\n', '    Ogre::Vector3 launch=origin+offset;\n    Ogre::Vector3 earlyTarget=target?target->getPosition(true):Ogre::Vector3::ZERO;\n    CResourceManager* resources=m_pResourceManager;\n    CMissile* missile=resources->getMissilePreloader()->createNewMissileRef(resources,m_sUnknown400);\n    if (!missile)\n        return false;\n    iMissile* listener=static_cast<iMissile*>(this);\n    if (missile->m_Listeners.find(listener)==-1)\n        missile->m_Listeners.add(listener);\n    Ogre::Vector3 targetPosition=earlyTarget;\n')]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + changed + tail)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_fire_missiles_differential')
        passed = any('equipment_fire_missiles_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_fire_missiles_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
