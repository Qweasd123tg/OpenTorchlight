"""Run standalone branch mutations of canEquip, from the repository root."""
import json, shutil, sys
from pathlib import Path
sys.path.insert(0,'tools/decomp')
import hybrid, mutate
root=Path('build-decomp/equipment-heirloom-extra-targeted').resolve()
(root/'src').mkdir(parents=True,exist_ok=True);(root/'tests').mkdir(exist_ok=True)
source=Path('decomp/src/Equipment.cpp').read_text()
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x882330'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentHeirloomTest.cpp','Detour.h']:shutil.copyfile(Path('decomp/hybrid/tests')/name,root/'tests'/name)
mutations=[
 ('cached_manager_lists','calculateCombatStats(true);','calculateCombatStats(true); CEffectManager* cachedManager=m_pEffectManager;'),
 ('cached_manager_clear','calculateCombatStats(true);','calculateCombatStats(true); CEffectManager* cachedManager=m_pEffectManager;'),
 ('cached_effect','float saved = effects[i]->m_fValueC0;','CEffect* current=effects[i]; float saved = current->m_fValueC0;'),
 ('double_saved_scale','m_fValueC0 = saved * 1.1f','m_fValueC0 = saved * 1.1'),
 ('wrong_base_mode','static_cast<CEffect::ECALCULATETYPES>(0)','static_cast<CEffect::ECALCULATETYPES>(1)'),
]

results=[]
for name,before,after in [('baseline','','')]+mutations:
 if name!='baseline' and body.count(before)!=(2 if name=='wrong_base_mode' else 1):raise SystemExit('ambiguous replacement: '+name)
 changed=body if name=='baseline' else body.replace(before,after,2 if name=='wrong_base_mode' else 1)
 if name=='cached_manager_lists': changed=changed.replace('m_pEffectManager->m_EffectData10','cachedManager->m_EffectData10')
 if name=='cached_manager_clear': changed=changed.replace('m_pEffectManager->clearOutDescriptions()','cachedManager->clearOutDescriptions()')
 if name=='cached_effect': changed=changed.replace('effects[i]->','current->')
 (root/'src/Equipment.cpp').write_text(head+changed+tail)
 try:
  blob,loader=hybrid.build(out=root/name,src=root/'src',tests=sorted((root/'tests').glob('*.cpp')),verbose=False)
  code,report=hybrid.selftest(blob,loader,only='equipment_heirloom_differential')
  passed=any('equipment_heirloom_differential' in line and 'PASS (0)' in line for line in report)
  if name=='baseline' and (code or not passed):raise SystemExit('baseline failed: '+'\n'.join(report))
  outcome='pass' if name=='baseline' else 'survived' if passed else 'killed' if any('equipment_heirloom_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
  row={'name':name,'outcome':outcome,'exit':code}
 except Exception as e:row={'name':name,'outcome':'inconclusive','error':str(e)}
 results.append(row);print(json.dumps(row),flush=True)
 (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
