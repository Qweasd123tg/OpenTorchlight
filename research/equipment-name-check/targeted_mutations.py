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

root = Path.cwd() / 'build-decomp/equipment-name-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
head, body = source.split('std::wstring CEquipment::getFullItemName', 1)
for name in ['EquipmentFullNameTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('ignore_force_identified', 'if (!forceIdentified && !m_bUnknown348 && !m_sUnidentifiedName.empty())', 'if (!m_bUnknown348 && !m_sUnidentifiedName.empty())'), ('return_empty_unidentified', 'if (!forceIdentified && !m_bUnknown348 && !m_sUnidentifiedName.empty())', 'if (!forceIdentified && !m_bUnknown348)'), ('skip_initial_tag_removal', 'name.replace(begin,end-begin+1,L"");\n        tag=', ';\n        tag='), ('ignore_unique_gate', '&& !ISA(UNITTYPES::UNIQUE)', '&& (ISA(UNITTYPES::UNIQUE),true)'), ('ignore_set_gate', '&& getSet().empty()', '&& (getSet(),true)'), ('last_prefix_instead_of_highest', 'affix->m_iRank>rank', 'affix->m_iRank>=0'), ('strict_suffix_rank', 'affix->m_iRank>=0', 'affix->m_iRank>rank'), ('prefix_concatenation', 'name=STRINGS::replaceWString(prefix,L"[ITEM]",name);', 'name=prefix+L" "+name;'), ('omit_prefix_cache', 'm_sPrefix=prefix;', ';'), ('omit_suffix_cache', 'm_sSuffix=suffix;', ';'), ('case_sensitive_selector', 'if (tag==STRINGS::StringUpper(current))', 'if (tag==current)'), ('uppercase_closing_tag', 'name.find(L"{/"+current,end)', 'name.find(L"{/"+tag,end)'), ('remove_first_tag_only', 'name.replace(closing,closingEnd-closing+1,L"");\n                    name.replace(begin,end-begin+1,L"");', 'name.replace(closing,closingEnd-closing+1,L"");\n                    name.replace(begin,end-begin+1,L"");\n                    break;'), ('keep_nonmatching_block', 'name.replace(begin,end-begin+1,L"");\n                }\n                begin=', 'break;\n                }\n                begin=')]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + 'std::wstring CEquipment::getFullItemName' + changed)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_full_name_differential')
        passed = any('equipment_full_name_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_full_name_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
