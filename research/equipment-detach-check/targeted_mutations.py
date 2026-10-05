"""Run standalone branch mutations of one Equipment entry, from the repository root."""
import json, shutil, sys
from pathlib import Path
sys.path.insert(0,'tools/decomp')
import hybrid, mutate
root=Path('build-decomp/targeted_mutations-targeted').resolve()
(root/'src').mkdir(parents=True,exist_ok=True);(root/'tests').mkdir(exist_ok=True)
source=Path('decomp/src/Equipment.cpp').read_text()
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x86ee20'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentDetachTest.cpp','Detour.h']:shutil.copyfile(Path('decomp/hybrid/tests')/name,root/'tests'/name)
mutations=[('skip_equipped_gate', '!m_pEquippedTo || ', 'false || '), ('skip_primary_gate', '!m_pUnitModel || ', 'false || '), ('skip_primary_entity', '!m_pUnitModel->m_pEntity', 'false'), ('skip_actor_entity', 'if (!actorModel->m_pEntity) return;', ';'), ('always_reparent_primary', 'if (parent) {\n        parent->removeChild(m_pUnitModel->m_pSceneNode);', 'if (true) {\n        if (parent) parent->removeChild(m_pUnitModel->m_pSceneNode);'), ('omit_primary_add', 'm_pSceneNode->addChild(m_pUnitModel->m_pSceneNode);', ';'), ('omit_stop', 'm_pParticle->Stop(true);', ';'), ('non_immediate_stop', 'm_pParticle->Stop(true);', 'm_pParticle->Stop(false);'), ('omit_particle_add', 'm_pSceneNode->addChild(m_pParticle->getSceneNode());', ';'), ('omit_primary_paper', 'm_pEquippedTo->setPaperdollItem(static_cast<EEQUIP_LOCATIONS>(m_iUnknown298), NULL);', ';'), ('wrong_primary_slot', 'm_pEquippedTo->setPaperdollItem(static_cast<EEQUIP_LOCATIONS>(m_iUnknown298), NULL);', 'm_pEquippedTo->setPaperdollItem(static_cast<EEQUIP_LOCATIONS>(0), NULL);'), ('cached_primary_actor', 'm_pEquippedTo->setPaperdollItem(', 'actor->setPaperdollItem('), ('cached_primary_slot', 'm_pEquippedTo->setPaperdollItem(static_cast<EEQUIP_LOCATIONS>(m_iUnknown298), NULL);', 'm_pEquippedTo->setPaperdollItem(slot, NULL);'), ('wrong_primary_entity', 'entity->detachObjectFromBone(actor->m_PaperdollItems[slot]);', 'entity->detachObjectFromBone(actor->m_PaperdollItemsSecondary[slot]);'), ('omit_secondary_remove', 'parent->removeChild(m_pUnitModelSecondary->m_pSceneNode);', ';'), ('reparent_secondary', 'parent->removeChild(m_pUnitModelSecondary->m_pSceneNode);', 'parent->removeChild(m_pUnitModelSecondary->m_pSceneNode); m_pSceneNode->addChild(m_pUnitModelSecondary->m_pSceneNode);'), ('omit_secondary_paper', 'm_pEquippedTo->setPaperdollItemSecondary(static_cast<EEQUIP_LOCATIONS>(m_iUnknown298), NULL);', ';'), ('wrong_secondary_slot', 'm_pEquippedTo->setPaperdollItemSecondary(static_cast<EEQUIP_LOCATIONS>(m_iUnknown298), NULL);', 'm_pEquippedTo->setPaperdollItemSecondary(static_cast<EEQUIP_LOCATIONS>(0), NULL);'), ('cached_secondary_actor', 'm_pEquippedTo->setPaperdollItemSecondary(', 'actor->setPaperdollItemSecondary('), ('wrong_secondary_entity', 'entity->detachObjectFromBone(actor->m_PaperdollItemsSecondary[slot]);', 'entity->detachObjectFromBone(actor->m_PaperdollItems[slot]);'), ('keep_equipped', 'm_pEquippedTo = NULL;', ';')]
results=[]
for name,before,after in [('baseline','','')]+mutations:
 if name!='baseline' and body.count(before)!=1:raise SystemExit('ambiguous replacement: '+name)
 changed=body if name=='baseline' else body.replace(before,after,1)
 (root/'src/Equipment.cpp').write_text(head+changed+tail)
 try:
  blob,loader=hybrid.build(out=root/name,src=root/'src',tests=sorted((root/'tests').glob('*.cpp')),verbose=False)
  code,report=hybrid.selftest(blob,loader,only='equipment_detach_differential')
  passed=any('equipment_detach_differential' in line and 'PASS (0)' in line for line in report)
  if name=='baseline' and (code or not passed):raise SystemExit('baseline failed: '+'\n'.join(report))
  outcome='pass' if name=='baseline' else 'survived' if passed else 'killed' if any('equipment_detach_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
  row={'name':name,'outcome':outcome,'exit':code}
 except Exception as e:row={'name':name,'outcome':'inconclusive','error':str(e)}
 results.append(row);print(json.dumps(row),flush=True)
 (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
