"""Targeted branch mutations for original-vs-recovered Equipment descriptions.

Run from the repository root after the regular hand-test mutation pass. Only
scratch copies are changed; original game services stay read-only.
"""
import json
import shutil
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid

root = Path.cwd() / 'build-decomp/equipment-description-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
head, body = source.split('std::wstring CEquipment::getEquipmentDescription', 1)
for name in ['EquipmentDescriptionTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [
    ('suffix_requires_best_rank', 'affix->m_iRank>=0', 'affix->m_iRank>rank'),
    ('prefix_equal_rank_replaces', 'affix->m_iRank>rank', 'affix->m_iRank>=rank'),
    ('suffix_does_not_update_rank', 'suffix=affix->m_sSuffix.c_str();\n                rank=affix->m_iRank;', 'suffix=affix->m_sSuffix.c_str();'),
    ('physical_damage_requires_positive', 'm_iMinimumDamage!=0 && m_iMaximumDamage!=0', 'm_iMinimumDamage>0 && m_iMaximumDamage>0'),
    ('elemental_negative_included', 'm_InherentElementalDamage[i]>0', 'm_InherentElementalDamage[i]!=0'),
    ('strict_speed_threshold', 'KWeaponSpeedValues[i]<=attack->m_fAttackSpeed*100.0f', 'KWeaponSpeedValues[i]<attack->m_fAttackSpeed*100.0f'),
    ('armor_percent_floor', 'float percent=ceilf(', 'float percent=floorf('),
    ('armor_flat_floor', 'float flat=ceilf(', 'float flat=floorf('),
    ('no_trinket_retranslation', 'CStringTranslate::getSinglton()->getTranslateString(g_Type)', 'g_Type'),
    ('strip_one_newline_only', "while (result[result.size()-1]==L'\\n')", "if (result[result.size()-1]==L'\\n')"),
]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + 'std::wstring CEquipment::getEquipmentDescription' + changed)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_description_differential')
        passed = any('equipment_description_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_description_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
