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

root = Path.cwd() / 'build-decomp/equipment-destructor-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
import mutate
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x87d770'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentDestructorTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('skip_visual_reset', 'resetVisualLayout();', ';'), ('wrong_listener_subobject', 'remove(static_cast<iMissile*>(this))', 'remove(reinterpret_cast<iMissile*>(this))'), ('remove_all_listeners', 'm_ActiveMissileRefs[i]->getObject()->m_Listeners.remove(static_cast<iMissile*>(this));', 'm_ActiveMissileRefs[i]->getObject()->m_Listeners.clear();'), ('skip_socket_deletes', 'm_SocketedEquipment.deleteAll();', 'm_SocketedEquipment.clear();'), ('swap_particle_delete_order', 'if (m_pParticle) {delete m_pParticle;m_pParticle=NULL;}\n    if (m_pParticle_3D0) {delete m_pParticle_3D0;m_pParticle_3D0=NULL;}', 'if (m_pParticle_3D0) {delete m_pParticle_3D0;m_pParticle_3D0=NULL;}\n    if (m_pParticle) {delete m_pParticle;m_pParticle=NULL;}'), ('wrong_visibility', 'CItem::setVisible(false,true);', 'CItem::setVisible(true,true);'), ('wrong_immediate_flag', 'CItem::setVisible(false,true);', 'CItem::setVisible(false,false);'), ('skip_first_detach', 'CItem::setVisible(false,true);\n    detachFromLocation();', 'CItem::setVisible(false,true);'), ('keep_entity', 'm_pEntity=NULL;', ';'), ('skip_icon_cleanup', 'destroyIcon();', ';'), ('skip_null_collision_release', 'CMasterResourceManager::getSingleton()->removeCollisionModel(reinterpret_cast<CCollisionModel*>(m_iUnitCollisionModel));', 'if (m_iUnitCollisionModel) CMasterResourceManager::getSingleton()->removeCollisionModel(reinterpret_cast<CCollisionModel*>(m_iUnitCollisionModel));'), ('skip_model_unload', 'unloadModel();', ';'), ('skip_second_detach', 'unloadModel();\n    detachFromLocation();', 'unloadModel();'), ('keep_inventory', 'm_pInventory=NULL;', ';'), ('keep_equipped_owner', 'm_pEquippedTo=NULL;', ';'), ('skip_delete_m_pPositionableObject', 'delete m_pPositionableObject;', ';'), ('skip_delete_m_pParticle', 'delete m_pParticle;', ';'), ('skip_delete_m_pParticle_3D0', 'delete m_pParticle_3D0;', ';'), ('skip_delete_m_pSoundBank', 'delete m_pSoundBank;', ';'), ('skip_delete_m_pPath', 'delete m_pPath;', ';'), ('skip_delete_m_pAttackDescription', 'delete m_pAttackDescription;', ';'), ('skip_delete_m_pAttackDescriptionOverride', 'delete m_pAttackDescriptionOverride;', ';'), ('leak_buffer_m_ElementalDamageTypes', 'm_pInventory=NULL;', 'm_ElementalDamageTypes.swap(*new std::vector<EDAMAGE_TYPES>); m_pInventory=NULL;'), ('leak_buffer_m_ElementalDamageBonuses', 'm_pInventory=NULL;', 'm_ElementalDamageBonuses.swap(*new std::vector<int>); m_pInventory=NULL;'), ('leak_buffer_m_InherentElementalDamage', 'm_pInventory=NULL;', 'm_InherentElementalDamage.swap(*new std::vector<int>); m_pInventory=NULL;'), ('leak_buffer_m_UnknownPOD398', 'm_pInventory=NULL;', 'm_UnknownPOD398.swap(*new std::vector<unsigned char>); m_pInventory=NULL;'), ('leak_buffer_m_UnknownPOD3B0', 'm_pInventory=NULL;', 'm_UnknownPOD3B0.swap(*new std::vector<unsigned char>); m_pInventory=NULL;')]
import tempfile
import subprocess
temporary=tempfile.TemporaryDirectory(prefix='otl-destructor-targeted-')
shim=Path(temporary.name)/'free_watch.so'
subprocess.run(['cc','-shared','-fPIC','-O2','-Wall','-Wextra','research/equipment-destructor-check/free_watch.c','-o',str(shim)],check=True)
original_env=hybrid.game_env
def watched(*args,**kwargs):
    game,env=original_env(*args,**kwargs)
    env['LD_PRELOAD']+=' '+str(shim)
    env['OTL_FREES_REQUIRED']='1'
    return game,env
hybrid.game_env=watched
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + changed + tail)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_destructor_differential')
        passed = any('equipment_destructor_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_destructor_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
