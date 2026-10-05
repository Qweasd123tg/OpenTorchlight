"""Target both the shared inlined reduction and each of the five original entries."""
import json,shutil,sys
from pathlib import Path
sys.path.insert(0,'tools/decomp')
import hybrid,mutate
root=Path('build-decomp/equipment-requirement-values-targeted').resolve();(root/'src').mkdir(parents=True,exist_ok=True);(root/'tests').mkdir(exist_ok=True)
source=Path('decomp/src/Equipment.cpp').read_text();masked=mutate.mask(source);db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
for n in ['EquipmentRequirementValuesTest.cpp','Detour.h']:shutil.copyfile(Path('decomp/hybrid/tests')/n,root/'tests'/n)
a=masked.index('{',masked.index('inline int equipmentRequirementReduction('));b=mutate.matching(masked,a,'{','}')
ranges={'helper':(a,b)}
fields=[('0x86dc50','m_iUnknown27C'),('0x86dae0','m_iUnknown280'),('0x86d970','m_iUnknown284'),('0x86d800','m_iUnknown288'),('0x86ddc0','m_iUnknown278')]
for addr,field in fields:ranges[addr]=mutate.definition(source,masked,db['functions'][addr])
mutations=[
 ('general_truncation','helper','int reduction = character ?','float reduction = character ?'),
 ('wrong_general_effect','helper','static_cast<EEFFECT_TYPE>(93)','static_cast<EEFFECT_TYPE>(92)'),
 ('martial_effect','helper','static_cast<EEFFECT_TYPE>(98)','static_cast<EEFFECT_TYPE>(99)'),
 ('ranged_effect','helper','static_cast<EEFFECT_TYPE>(100)','static_cast<EEFFECT_TYPE>(99)'),
 ('magic_effect','helper','static_cast<EEFFECT_TYPE>(101)','static_cast<EEFFECT_TYPE>(99)'),
 ('armor_effect','helper','static_cast<EEFFECT_TYPE>(94)','static_cast<EEFFECT_TYPE>(99)'),
 ('spell_effect','helper','static_cast<EEFFECT_TYPE>(95)','static_cast<EEFFECT_TYPE>(99)'),
 ('martial_type','helper','ISA(UNITTYPES::ITEMCATEGORYMARTIAL)','ISA(UNITTYPES::ITEMCATEGORYRANGED)'),
 ('ranged_type','helper','ISA(UNITTYPES::ITEMCATEGORYRANGED)','ISA(UNITTYPES::ITEMCATEGORYMARTIAL)'),
 ('skip_armor','helper','item->ISA(UNITTYPES::ARMOR)','false'),
 ('skip_spell','helper','item->ISA(UNITTYPES::SPELL)','false'),
 ('double_category','helper','else if (item->ISA(UNITTYPES::ITEMCATEGORYRANGED))','if (item->ISA(UNITTYPES::ITEMCATEGORYRANGED))'),
]
# Removing the initial cast, not merely changing the storage type, tests the
# semantic difference between truncating the general reduction before addition
# and postponing truncation until after the category reduction.
for addr,field in fields:
 mutations += [
  (addr+'_wrong_field',addr,'int requirement = '+field+' - reduction;','int requirement = m_iUnknown274 - reduction;'),
  (addr+'_no_clamp',addr,'return requirement < 0 ? 0 : requirement;','return requirement;'),
  (addr+'_cache_field',addr,'int reduction = equipmentRequirementReduction(this, character);\n    int requirement = '+field+' - reduction;','int saved = '+field+';\n    int reduction = equipmentRequirementReduction(this, character);\n    int requirement = saved - reduction;'),
 ]
mutations.append(('level_null_clamp','0x86ddc0','if (!character) return m_iUnknown278;','if (!character) return m_iUnknown278 < 0 ? 0 : m_iUnknown278;'))
results=[]
for name,scope,before,after in [('baseline','helper','','')]+mutations:
 a,b=ranges[scope];body=source[a:b+1]
 if name!='baseline' and body.count(before)!=1:raise SystemExit('ambiguous replacement: '+name)
 changed=body if name=='baseline' else body.replace(before,after,1)
 if name=='general_truncation':
  changed=changed.replace('static_cast<int>(character->getEffectValue(', 'character->getEffectValue(',1).replace('static_cast<EDAMAGE_TYPES>(7))) : 0;', 'static_cast<EDAMAGE_TYPES>(7)) : 0;',1)
 (root/'src/Equipment.cpp').write_text(source[:a]+changed+source[b+1:])
 try:
  blob,loader=hybrid.build(out=root/name,src=root/'src',tests=sorted((root/'tests').glob('*.cpp')),verbose=False)
  code,report=hybrid.selftest(blob,loader,only='equipment_requirement_values_differential')
  passed=any('equipment_requirement_values_differential' in line and 'PASS (0)' in line for line in report)
  if name=='baseline' and (code or not passed):raise SystemExit('baseline failed: '+'\n'.join(report))
  outcome='pass' if name=='baseline' else 'survived' if passed else 'killed' if any('equipment_requirement_values_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
  row={'name':name,'scope':scope,'outcome':outcome,'exit':code}
 except Exception as e:row={'name':name,'scope':scope,'outcome':'inconclusive','error':str(e)}
 results.append(row);print(json.dumps(row),flush=True);(root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
