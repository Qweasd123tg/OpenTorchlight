"""Run standalone branch mutations of one Equipment entry, from the repository root."""
import json, shutil, sys
from pathlib import Path
sys.path.insert(0,'tools/decomp')
import hybrid, mutate
root=Path('build-decomp/canuse_targeted-targeted').resolve()
(root/'src').mkdir(parents=True,exist_ok=True);(root/'tests').mkdir(exist_ok=True)
source=Path('decomp/src/Equipment.cpp').read_text()
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x86e710'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentCanUseTest.cpp','Detour.h']:shutil.copyfile(Path('decomp/hybrid/tests')/name,root/'tests'/name)
mutations=[('charges_negative', 'm_iUnknown248 == 0', 'm_iUnknown248 <= 0'), ('ignore_charges', 'if (m_iUnknown248 == 0) return false;', ';'), ('caster_level', 'int level = static_cast<int>(levelCharacter->m_iUnitLevel);', 'int level = static_cast<int>(character->m_iUnitLevel);'), ('unsigned_level', 'int level = static_cast<int>(levelCharacter->m_iUnitLevel);', 'unsigned int level = levelCharacter->m_iUnitLevel;'), ('level_inclusive', 'getLevelRequirement(character) > level', 'getLevelRequirement(character) >= level'), ('ignore_level', 'if (getLevelRequirement(character) > level) return false;', 'getLevelRequirement(character);'), ('reread_level', '> level) return false;', '> static_cast<int>(levelCharacter->m_iUnitLevel)) return false;'), ('null_owner', 'effect->m_Owner.getObject(), effect', 'NULL, effect'), ('null_effect', 'effect->m_Owner.getObject(), effect', 'effect->m_Owner.getObject(), NULL'), ('stop_on_valid', 'valid = true;', '{ valid = true; break; }'), ('ignore_invalid', 'if (!valid) return false;', ';'), ('any_empty_invalid', 'if (effects.size() != 0)', 'if (true)'), ('effect_first', 'CEffect* effect = effects[i];', 'CEffect* effect = effects[0];'), ('cached_effect_count', 'i < effects.size()', 'i < 1'), ('ignore_busy', 'if (targetCharacter->performingSkillLoose()) return false;', 'targetCharacter->performingSkillLoose();'), ('cached_skill_manager', 'skills = m_pSkillManager;\n        }', ';\n        }'), ('first_skill', 'skills->m_OtherSkills[i]->', 'skills->m_OtherSkills[0]->'), ('omit_last_skill', 'i < skills->m_OtherSkills.size()', 'i + 1 < skills->m_OtherSkills.size()'), ('wrong_skill_target', '->canAffixesAndEffectsBeAppliedToUnit(target, character)', '->canAffixesAndEffectsBeAppliedToUnit(character, character)'), ('ignore_nopets', 'if (ISA(UNITTYPES::NOPETS) &&', 'if (false &&'), ('ignore_petonly', 'if (ISA(UNITTYPES::PETONLY))', 'if (false)'), ('nopets_invert_master', '(!target || targetCharacter->m_pMaster)', '(!target || !targetCharacter->m_pMaster)'), ('petonly_invert_master', 'return target && targetCharacter->m_pMaster;', 'return target && !targetCharacter->m_pMaster;')]
results=[]
for name,before,after in [('baseline','','')]+mutations:
 if name!='baseline' and body.count(before)!=1:raise SystemExit('ambiguous replacement: '+name)
 changed=body if name=='baseline' else body.replace(before,after,1)
 (root/'src/Equipment.cpp').write_text(head+changed+tail)
 try:
  blob,loader=hybrid.build(out=root/name,src=root/'src',tests=sorted((root/'tests').glob('*.cpp')),verbose=False)
  code,report=hybrid.selftest(blob,loader,only='equipment_canuse_differential')
  passed=any('equipment_canuse_differential' in line and 'PASS (0)' in line for line in report)
  if name=='baseline' and (code or not passed):raise SystemExit('baseline failed: '+'\n'.join(report))
  outcome='pass' if name=='baseline' else 'survived' if passed else 'killed' if any('equipment_canuse_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
  row={'name':name,'outcome':outcome,'exit':code}
 except Exception as e:row={'name':name,'outcome':'inconclusive','error':str(e)}
 results.append(row);print(json.dumps(row),flush=True)
 (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
