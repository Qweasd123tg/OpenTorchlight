"""Run standalone branch mutations of canEquip, from the repository root."""
import json, shutil, sys
from pathlib import Path
sys.path.insert(0,'tools/decomp')
import hybrid, mutate
root=Path('build-decomp/equipment-canequip-targeted').resolve()
(root/'src').mkdir(parents=True,exist_ok=True);(root/'tests').mkdir(exist_ok=True)
source=Path('decomp/src/Equipment.cpp').read_text()
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x86f150'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentCanEquipTest.cpp','Detour.h']:shutil.copyfile(Path('decomp/hybrid/tests')/name,root/'tests'/name)
mutations=[
 ('allow_merchant','character->ISA(UNITTYPES::MERCHANT)','false'),
 ('allow_stash','character->ISA(UNITTYPES::STASH)','false'),
 ('ignore_master','character->m_pMaster && character->m_pMaster->ISA(UNITTYPES::PLAYER)','false'),
 ('any_master','character->m_pMaster->ISA(UNITTYPES::PLAYER)','true'),
 ('master_weapon','&& !ISA(UNITTYPES::TRINKET))\n        return false;\n    if (character->m_bCharacterFlag4A0', '&& !ISA(UNITTYPES::WEAPON))\n        return false;\n    if (character->m_bCharacterFlag4A0'),
 ('ignore_identification','character->m_bCharacterFlag4A0 && !m_bUnknown348','false'),
 ('always_identification','character->m_bCharacterFlag4A0 && !m_bUnknown348','!m_bUnknown348'),
 ('always_type','checkType &&','true &&'),
 ('ignore_type','checkType &&','false &&'),
 ('no_spell','&& !ISA(UNITTYPES::SPELL)','&& true'),
 ('no_armor','&& !ISA(UNITTYPES::ARMOR)','&& true'),
 ('zero_req_still_called','getLevelRequirement(character) != 0','getLevelRequirement(character) >= 0'),
 ('level_inclusive','level < getLevelRequirement(character)','level <= getLevelRequirement(character)'),
 ('level_reread','level < getLevelRequirement(character)','static_cast<int>(character->m_iUnitLevel) < getLevelRequirement(character)'),
 ('level_unsigned','int level = static_cast<int>(character->m_iUnitLevel);','unsigned int level = character->m_iUnitLevel;'),
 ('strength_boundary','value < getStrengthRequirement(character)','value <= getStrengthRequirement(character)'),
 ('dexterity_boundary','value < getDexterityRequirement(character)','value <= getDexterityRequirement(character)'),
 ('magic_boundary','value < getMagicRequirement(character)','value <= getMagicRequirement(character)'),
 ('defense_boundary','value < getDefenseRequirement(character)','value <= getDefenseRequirement(character)'),
 ('strength_unconditional','if (character->m_bCharacterFlag4A0) {\n        int value = character->strength();','if (true) {\n        int value = character->strength();'),
 ('dexterity_unconditional','if (character->m_bCharacterFlag4A0) {\n        int value = character->dexterity();','if (true) {\n        int value = character->dexterity();'),
 ('magic_unconditional','if (character->m_bCharacterFlag4A0) {\n        int value = character->magic();','if (true) {\n        int value = character->magic();'),
 ('defense_unconditional','if (character->m_bCharacterFlag4A0) {\n        int value = character->defense();','if (true) {\n        int value = character->defense();'),
]
results=[]
for name,before,after in [('baseline','','')]+mutations:
 if name!='baseline' and body.count(before)!=1:raise SystemExit('ambiguous replacement: '+name)
 changed=body if name=='baseline' else body.replace(before,after,1)
 (root/'src/Equipment.cpp').write_text(head+changed+tail)
 try:
  blob,loader=hybrid.build(out=root/name,src=root/'src',tests=sorted((root/'tests').glob('*.cpp')),verbose=False)
  code,report=hybrid.selftest(blob,loader,only='equipment_canequip_differential')
  passed=any('equipment_canequip_differential' in line and 'PASS (0)' in line for line in report)
  if name=='baseline' and (code or not passed):raise SystemExit('baseline failed: '+'\n'.join(report))
  outcome='pass' if name=='baseline' else 'survived' if passed else 'killed' if any('equipment_canequip_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
  row={'name':name,'outcome':outcome,'exit':code}
 except Exception as e:row={'name':name,'outcome':'inconclusive','error':str(e)}
 results.append(row);print(json.dumps(row),flush=True)
 (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
