"""Targeted branch mutations for original-vs-recovered Equipment skill descriptions.

Run from the repository root after the regular hand-test mutation pass. Only
scratch copies are changed; original game services stay read-only.
"""
import json
import shutil
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid

root = Path.cwd() / 'build-decomp/equipment-skilldescription-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
import mutate
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x87e640'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentSkillDescriptionTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('wrong_group', 'L"SKILL_TO_GIVE"', 'L"SKILL"'), ('skip_name', 'name=groups[i]->GetDataValue(L"NAME",name);', ';'), ('skip_displayname', 'name=groups[i]->GetDataValue(L"DISPLAYNAME",name);', ';'), ('wrong_root_default', 'm_pDataGroup->GetDataValue(L"LEVEL",1)', 'm_pDataGroup->GetDataValue(L"LEVEL",0)'), ('ignore_root_level', 'm_pDataGroup->GetDataValue(L"LEVEL",1)', '1'), ('wrong_child_level', 'groups[i]->GetDataValue(L"LEVEL",m_pDataGroup->GetDataValue(L"LEVEL",1))', 'm_pDataGroup->GetDataValue(L"LEVEL",1)'), ('wrong_level_separator', '+g_Level+L": "', '+g_Level+L":"'), ('drop_space_before_level', '+name+L" "', '+name+L""'), ('include_disabled', 'skill->m_bEnabled & !skill->m_bExecutedByProperty', 'true & !skill->m_bExecutedByProperty'), ('include_property', 'skill->m_bEnabled & !skill->m_bExecutedByProperty', 'skill->m_bEnabled'), ('wrong_skill_level', 'getDescription(this,static_cast<unsigned int>(-1),true)', 'getDescription(this,0,true)'), ('wrong_skill_flag', 'getDescription(this,static_cast<unsigned int>(-1),true)', 'getDescription(this,static_cast<unsigned int>(-1),false)'), ('wrong_skill_owner', 'getDescription(this,static_cast<unsigned int>(-1),true)', 'getDescription(NULL,static_cast<unsigned int>(-1),true)'), ('skip_last_group', 'i<count;', 'i+1<count;'), ('cached_count', 'for (unsigned int i=0;i<static_cast<unsigned int>(m_pSkillManager->knownSkills(SKILL_ACTIVATION_ANY));++i)', 'for (unsigned int i=0, total=static_cast<unsigned int>(m_pSkillManager->knownSkills(SKILL_ACTIVATION_ANY));i<total;++i)'), ('skill_newline_by_result', 'if (i!=0) result=result+L"\\n";\n                result.append', 'if (!result.empty()) result=result+L"\\n";\n                result.append'), ('group_newline_by_result', 'if (i!=0) result=result+L"\\n";\n        result=', 'if (i==0) result=result+L"\\n";\n        result=')]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + changed + tail)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_skill_description_differential')
        passed = any('equipment_skill_description_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_skill_description_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
