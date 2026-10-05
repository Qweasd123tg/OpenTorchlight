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

root = Path.cwd() / 'build-decomp/equipment-attach-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
import mutate
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x886d40'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentAttachTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('omit_wardrobe_gate', 'if (isWardrobed(character->getName())) return;', ';', 0, 1), ('omit_secondary_parent_guid', 'if (m_pUnitModelSecondary) m_pUnitModelSecondary->setParentGuid(-1);', ';', 0, 1), ('omit_third_model_query', '    character->getUnitModel();\n    Ogre::Entity* entity=', '    Ogre::Entity* entity=', 0, 1), ('wrong_stored_slot', 'm_iUnknown298=location;', 'm_iUnknown298=static_cast<int>(location)+1;', 0, 1), ('stop_drop_particle_immediately', 'm_pParticle_3D0->Stop(false);', 'm_pParticle_3D0->Stop(true);', 0, 1), ('omit_drop_particle_detach', 'OGRE_UTILITIES::removeChildFromParentNode(m_pParticle_3D0->getSceneNode());', ';', 0, 1), ('shield_wrong_bone', 'bone=KEQUIP_LOCATION_BONES[11]', 'bone=KEQUIP_LOCATION_BONES[0]', 0, 1), ('shield_wrong_anchor', 'anchor=11;', 'anchor=location;', 0, 1), ('omit_primary_node_attachment', 'node->addChild(m_pUnitModel->getSceneNode());', ';', 0, 1), ('omit_secondary_node_attachment', 'node->addChild(m_pUnitModelSecondary->getSceneNode());', ';', 0, 1), ('primary_guard_source_material', 'if (!target->getMaterial().isNull())', 'if (!source->getMaterial().isNull())', 0, 2), ('primary_copy_target_to_itself', 'target->setMaterial(source->getMaterial());', 'target->setMaterial(target->getMaterial());', 0, 2), ('primary_omit_mesh_clone', 'mesh->clone(name);', ';', 0, 2), ('primary_wrong_tag_scale', 'tag->setScale(scale,scale,scale);', 'tag->setScale(scale,scale,scale*2.0f);', 0, 2), ('secondary_guard_source_material', 'if (!target->getMaterial().isNull())', 'if (!source->getMaterial().isNull())', 1, 2), ('secondary_copy_target_to_itself', 'target->setMaterial(source->getMaterial());', 'target->setMaterial(target->getMaterial());', 1, 2), ('secondary_omit_mesh_clone', 'mesh->clone(name);', ';', 1, 2), ('secondary_wrong_tag_scale', 'tag->setScale(scale,scale,scale);', 'tag->setScale(scale,scale,scale*2.0f);', 1, 2), ('primary_weapon_uses_shield_scale', 'GetDataValue(L"WEAPON_SCALE",1.0f)', 'GetDataValue(L"SHIELD_SCALE",1.0f)', 0, 2), ('secondary_shield_uses_weapon_scale', 'GetDataValue(L"SHIELD_SCALE",1.0f)', 'GetDataValue(L"WEAPON_SCALE",1.0f)', 1, 2), ('primary_paperdoll_wrong_slot', 'character->setPaperdollItem(location,dummy);', 'character->setPaperdollItem(static_cast<EEQUIP_LOCATIONS>(anchor),dummy);', 0, 1), ('secondary_uses_primary_entity', 'entity=m_pUnitModelSecondary->m_pEntity;', 'entity=m_pUnitModel->m_pEntity;', 0, 1), ('omit_secondary_existing_parent_scale', 'if (dummy->getParentSceneNode()) dummy->getParentSceneNode()->setScale(scale,scale,scale);', ';', 0, 1), ('ignore_secondary_bone_gate', 'if (KEQUIP_LOCATION_BONES_SECONDARY[location]!=EMPTY_STRING && m_pUnitModelSecondary)', 'if (m_pUnitModelSecondary)', 0, 1), ('secondary_wrong_bone_name', 'attachObjectToBone(KEQUIP_LOCATION_BONES_SECONDARY[location],', 'attachObjectToBone(KEQUIP_LOCATION_BONES[location],', 0, 1)]
results = []
for name, before, after, occurrence, expected in [('baseline', '', '', 0, 1)] + mutations:
    if name != 'baseline' and body.count(before) != expected:
        raise SystemExit('ambiguous source replacement: ' + name)
    if name == 'baseline':
        changed=body
    else:
        parts=body.split(before)
        changed=before.join(parts[:occurrence+1])+after+before.join(parts[occurrence+1:])
    (root / 'src/Equipment.cpp').write_text(head + changed + tail)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_attach_differential')
        passed = any('equipment_attach_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_attach_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
