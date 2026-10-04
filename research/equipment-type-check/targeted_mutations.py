"""Targeted branch mutations for original-vs-recovered Equipment types.

Run from the repository root after the regular hand-test mutation pass. Only
scratch copies are changed; original game services stay read-only.
"""
import json
import shutil
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid

root = Path.cwd() / 'build-decomp/equipment-type-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
head, body = source.split('std::wstring CEquipment::getEquipmentType', 1)
for name in ['EquipmentTypeTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [
    ('omit_quest_marker', 'if (getIsQuestUnit()) result=g_QuestItem;', 'if (getIsQuestUnit()) result=L"";'),
    ('append_socketable', 'result=g_Socketable;', 'result=result+g_Socketable;'),
    ('append_potion', 'result=g_Potion;', 'result=result+g_Potion;'),
    ('append_scroll', 'result=g_Scroll;', 'result=result+g_Scroll;'),
    ('quality_ignores_flag', 'else if (showQuality)', 'else if (true)'),
    ('unidentified_requires_flag', 'if (!m_bUnknown348)', 'if (!m_bUnknown348 && showQuality)'),
    ('remove_empty_braces', 'start+1<end', 'start+1<=end'),
    ('choose_last_open_brace', 'result.find(L"{")', 'result.rfind(L"{")'),
    ('close_brace_from_start', 'result.find(L"}",start)', 'result.find(L"}",0)'),
    ('cache_helmet_translation', 'result=result+CStringTranslate::getSinglton()->getTranslateString(L"Helmet");', 'result=result+g_Helmet;'),
]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + 'std::wstring CEquipment::getEquipmentType' + changed)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_type_differential')
        passed = any('equipment_type_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_type_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
