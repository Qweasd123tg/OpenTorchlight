"""Run standalone branch mutations of canEquip, from the repository root."""
import json, shutil, sys
from pathlib import Path
sys.path.insert(0,'tools/decomp')
import hybrid, mutate
root=Path('build-decomp/equipment-heirloom-check-targeted').resolve()
(root/'src').mkdir(parents=True,exist_ok=True);(root/'tests').mkdir(exist_ok=True)
source=Path('decomp/src/Equipment.cpp').read_text()
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x882330'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentHeirloomTest.cpp','Detour.h']:shutil.copyfile(Path('decomp/hybrid/tests')/name,root/'tests'/name)
mutations=[('omit_combat', 'calculateCombatStats(true);', ';'), ('combat_not_forced', 'calculateCombatStats(true);', 'calculateCombatStats(false);'), ('rank_inclusive', 'm_iUnknown28C < 10', 'm_iUnknown28C <= 10'), ('rank_unsigned', 'm_iUnknown28C < 10', 'static_cast<unsigned int>(m_iUnknown28C) < 10'), ('omit_manager_guard', '&& m_pEffectManager', '&& true'), ('two_activations', 'activation < 3', 'activation < 2'), ('wrong_value_first', 'value(static_cast<EEFFECT_VALUES>(0))', 'value(static_cast<EEFFECT_VALUES>(1))'), ('wrong_value_second', 'value(static_cast<EEFFECT_VALUES>(1))', 'value(static_cast<EEFFECT_VALUES>(0))'), ('omit_first_base', 'effects[i]->m_fValueC4 = value * 1.1f;\n                effects[i]->calculateBaseValue(static_cast<CEffect::ECALCULATETYPES>(0));', 'effects[i]->m_fValueC4 = value * 1.1f;'), ('omit_second_base', 'effects[i]->m_fValueC8 = value * 1.1f;\n                effects[i]->calculateBaseValue(static_cast<CEffect::ECALCULATETYPES>(0));', 'effects[i]->m_fValueC8 = value * 1.1f;'), ('wrong_first_scale', 'm_fValueC4 = value * 1.1f', 'm_fValueC4 = value'), ('wrong_second_scale', 'm_fValueC8 = value * 1.1f', 'm_fValueC8 = value'), ('wrong_saved_scale', 'm_fValueC0 = saved * 1.1f', 'm_fValueC0 = saved'), ('reread_saved', 'm_fValueC0 = saved * 1.1f', 'm_fValueC0 = effects[i]->m_fValueC0 * 1.1f'), ('wrong_first_entry', 'effects[i]->m_fValueC4 =', 'effects[0]->m_fValueC4 ='), ('wrong_second_entry', 'effects[i]->m_fValueC8 =', 'effects[0]->m_fValueC8 ='), ('wrong_saved_entry', 'effects[i]->m_fValueC0 = saved', 'effects[0]->m_fValueC0 = saved'), ('omit_clear', 'm_pEffectManager->clearOutDescriptions();', ';'), ('omit_requirements', 'setRequirements();', ';'), ('single_effect', 'i < effects.size()', 'i < 1'), ('cache_count', 'for (unsigned int i = 0; i < effects.size(); ++i)', 'unsigned int count=effects.size(); for (unsigned int i = 0; i < count; ++i)'), ('double_first_scale', 'm_fValueC4 = value * 1.1f', 'm_fValueC4 = value * 1.1'), ('double_second_scale', 'm_fValueC8 = value * 1.1f', 'm_fValueC8 = value * 1.1')]
results=[]
for name,before,after in [('baseline','','')]+mutations:
 if name!='baseline' and body.count(before)!=1:raise SystemExit('ambiguous replacement: '+name)
 changed=body if name=='baseline' else body.replace(before,after,1)
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
