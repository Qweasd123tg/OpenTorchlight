"""Run standalone branch mutations of canEquip, from the repository root."""
import json, shutil, sys
from pathlib import Path
sys.path.insert(0,'tools/decomp')
import hybrid, mutate
root=Path('build-decomp/equipment-inventory-entry-check-targeted').resolve()
(root/'src').mkdir(parents=True,exist_ok=True);(root/'tests').mkdir(exist_ok=True)
source=Path('decomp/src/Equipment.cpp').read_text()
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x884a20'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentInventoryEntryTest.cpp','Detour.h']:shutil.copyfile(Path('decomp/hybrid/tests')/name,root/'tests'/name)
mutations=[('quest_same_inventory', 'inventory != m_pInventory', 'true'), ('skip_previous_quest', 'questEventFire(static_cast<EQUEST_EVENTS>(5), m_pResourceManager->getGameClient()->getPlayer(), this);', ';'), ('wrong_previous_quest', 'static_cast<EQUEST_EVENTS>(5)', 'static_cast<EQUEST_EVENTS>(4)'), ('ignore_gambler', 'if (m_bGamblerIcon &&', 'if (true &&'), ('omit_icon', 'createIcon(*m_pResourceManager->getGameClient()->getGameUI(), true);', ';'), ('wrong_icon_flag', 'getGameUI(), true', 'getGameUI(), false'), ('omit_price', 'recalculatePrice();', ';'), ('omit_parent_guid', 'setParentGuid(character->getGuid());', ';'), ('wrong_parent_guid', 'setParentGuid(character->getGuid());', 'setParentGuid(0);'), ('omit_state', 'broadcastUnitState(static_cast<EUNIT_STATES>(3));', ';'), ('wrong_state', 'static_cast<EUNIT_STATES>(3)', 'static_cast<EUNIT_STATES>(2)'), ('ignore_master', '|| (character->m_pMaster && character->m_pMaster->ISA(UNITTYPES::PLAYER))', '|| false'), ('any_master', 'character->m_pMaster && character->m_pMaster->ISA(UNITTYPES::PLAYER)', 'character->m_pMaster'), ('skip_pickup_quest', 'questEventFire(static_cast<EQUEST_EVENTS>(0), m_pResourceManager->getGameClient()->getPlayer(), this);', ';'), ('omit_event', 'BroadcastEvent(27);', ';'), ('wrong_event', 'BroadcastEvent(27);', 'BroadcastEvent(26);'), ('omit_item_flag', 'm_bItemFlag1F2 = true;', ';'), ('omit_scene_remove', 'if (getSceneOwner()) getSceneOwner()->RemoveObjectInScene(this);', ';'), ('wrong_stop_flag', 'm_pParticle_3D0->Stop(false);', 'm_pParticle_3D0->Stop(true);'), ('omit_reset', 'resetVisualLayout();', ';')]
results=[]
for name,before,after in [('baseline','','')]+mutations:
 if name!='baseline' and body.count(before)!=1:raise SystemExit('ambiguous replacement: '+name)
 changed=body if name=='baseline' else body.replace(before,after,1)
 (root/'src/Equipment.cpp').write_text(head+changed+tail)
 try:
  blob,loader=hybrid.build(out=root/name,src=root/'src',tests=sorted((root/'tests').glob('*.cpp')),verbose=False)
  code,report=hybrid.selftest(blob,loader,only='equipment_inventory_entry_differential')
  passed=any('equipment_inventory_entry_differential' in line and 'PASS (0)' in line for line in report)
  if name=='baseline' and (code or not passed):raise SystemExit('baseline failed: '+'\n'.join(report))
  outcome='pass' if name=='baseline' else 'survived' if passed else 'killed' if any('equipment_inventory_entry_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
  row={'name':name,'outcome':outcome,'exit':code}
 except Exception as e:row={'name':name,'outcome':'inconclusive','error':str(e)}
 results.append(row);print(json.dumps(row),flush=True)
 (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
