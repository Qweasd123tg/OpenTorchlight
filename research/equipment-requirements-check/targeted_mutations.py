"""Targeted branch mutations for original-vs-recovered Equipment requirements.

Run from the repository root after the regular hand-test mutation pass. Only
scratch copies are changed; original game services stay read-only.
"""
import json
import shutil
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid

root = Path.cwd() / 'build-decomp/equipment-requirements-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
import mutate
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x880030'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentRequirementsTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('level_reduction_cap', 'std::min(m_iUnknown28C,5)', 'std::min(m_iUnknown28C,6)'), ('stat_reduction_cap', 'std::min(m_iUnknown28C,10)', 'std::min(m_iUnknown28C,9)'), ('remove_trinket', ' || ISA(UNITTYPES::TRINKET)', ''), ('overwrite_explicit_level', 'm_iUnknown278==0', 'm_iUnknown278!=0'), ('level_graph_key', 'L"ITEM_LEVEL_REQUIREMENTS"', 'L"ITEM_STRENGTH_REQUIREMENTS"'), ('level_clamp_threshold', 'm_iUnknown278=requirement>1?requirement:0', 'm_iUnknown278=requirement>0?requirement:0'), ('level_floor', 'floorf(graph->getValue(static_cast<float>(m_iUnknown274),0))', 'ceilf(graph->getValue(static_cast<float>(m_iUnknown274),0))'), ('strength_graph_key', 'L"ITEM_STRENGTH_REQUIREMENTS"', 'L"ITEM_LEVEL_REQUIREMENTS"'), ('strength_floor', 'floorf(value*static_cast<float>(m_iUnknown27C)/100.0f)', 'ceilf(value*static_cast<float>(m_iUnknown27C)/100.0f)'), ('strength_scale', 'value*static_cast<float>(m_iUnknown27C)/100.0f', 'value*static_cast<float>(m_iUnknown27C)/101.0f'), ('strength_threshold', 'm_iUnknown27C=requirement>1?requirement:0', 'm_iUnknown27C=requirement>0?requirement:0'), ('dexterity_graph_key', 'L"ITEM_DEXTERITY_REQUIREMENTS"', 'L"ITEM_LEVEL_REQUIREMENTS"'), ('dexterity_floor', 'floorf(value*static_cast<float>(m_iUnknown280)/100.0f)', 'ceilf(value*static_cast<float>(m_iUnknown280)/100.0f)'), ('dexterity_scale', 'value*static_cast<float>(m_iUnknown280)/100.0f', 'value*static_cast<float>(m_iUnknown280)/101.0f'), ('dexterity_threshold', 'm_iUnknown280=requirement>1?requirement:0', 'm_iUnknown280=requirement>0?requirement:0'), ('magic_graph_key', 'L"ITEM_MAGIC_REQUIREMENTS"', 'L"ITEM_LEVEL_REQUIREMENTS"'), ('magic_floor', 'floorf(value*static_cast<float>(m_iUnknown284)/100.0f)', 'ceilf(value*static_cast<float>(m_iUnknown284)/100.0f)'), ('magic_scale', 'value*static_cast<float>(m_iUnknown284)/100.0f', 'value*static_cast<float>(m_iUnknown284)/101.0f'), ('magic_threshold', 'm_iUnknown284=requirement>1?requirement:0', 'm_iUnknown284=requirement>0?requirement:0'), ('defense_graph_key', 'L"ITEM_DEFENSE_REQUIREMENTS"', 'L"ITEM_LEVEL_REQUIREMENTS"'), ('defense_floor', 'floorf(value*static_cast<float>(m_iUnknown288)/100.0f)', 'ceilf(value*static_cast<float>(m_iUnknown288)/100.0f)'), ('defense_scale', 'value*static_cast<float>(m_iUnknown288)/100.0f', 'value*static_cast<float>(m_iUnknown288)/101.0f'), ('defense_threshold', 'm_iUnknown288=requirement>1?requirement:0', 'm_iUnknown288=requirement>0?requirement:0')]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + changed + tail)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_requirements_differential')
        passed = any('equipment_requirements_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_requirements_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
