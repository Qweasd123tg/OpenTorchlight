"""Targeted branch mutations for original-vs-recovered Equipment effect descriptions.

Run from the repository root after the regular hand-test mutation pass. Only
scratch copies are changed; original game services stay read-only.
"""
import json
import shutil
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid

root = Path.cwd() / 'build-decomp/equipment-effects-description-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
head, body = source.split('std::wstring CEquipment::effectsDescription', 1)
for name in ['EquipmentEffectsDescriptionTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [
    ('use_inherent_not_bonus_damage', 'm_ElementalDamageBonuses[i]>0', 'm_InherentElementalDamage[i]>0'),
    ('include_negative_bonus', 'm_ElementalDamageBonuses[i]>0', 'm_ElementalDamageBonuses[i]!=0'),
    ('dynamic_bonus_instead_of_passive', 'activation==EFFECT_ACTIVATION_PASSIVE', 'activation==EFFECT_ACTIVATION_DYNAMIC'),
    ('ignore_embedded_flag', 'if (!embedded)', 'if (true)'),
    ('include_random_magic_socketable_filter', 'ISA(UNITTYPES::SOCKETABLE) && !ISA(UNITTYPES::RANDOMMAGIC_SOCKETABLE)', 'ISA(UNITTYPES::SOCKETABLE)'),
    ('wrong_visual_level', 'static_cast<unsigned int>(-1)', '0u'),
    ('child_not_embedded', 'effectsDescription(activation,true,false)', 'effectsDescription(activation,false,false)'),
    ('visit_newly_appended_sockets', 'static_cast<int>(i)<count', 'i<m_SocketedEquipment.size()'),
    ('trim_all_socket_newlines', 'if (!sockets.empty() && sockets[sockets.size()-1]==L\'\\n\')', 'while (!sockets.empty() && sockets[sockets.size()-1]==L\'\\n\')'),
    ('omit_socket_leading_newline', 'if (result.empty() || result[result.size()-1]!=L\'\\n\') result=result+L"\\n";', ';'),
    ('omit_final_newline', 'if (!result.empty() && result[result.size()-1]!=L\'\\n\') result.append(L"\\n");', ';'),
]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + 'std::wstring CEquipment::effectsDescription' + changed)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_effects_description_differential')
        passed = any('equipment_effects_description_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_effects_description_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
