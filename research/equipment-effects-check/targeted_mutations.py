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

root = Path.cwd() / 'build-decomp/equipment-effects-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
head, body = source.split('std::wstring CEquipment::getEquipmentEffects', 1)
for name in ['EquipmentEffectsTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [
    ('identified_guard_inverted', 'if (!m_bUnknown348) return result;', 'if (m_bUnknown348) return result;'),
    ('first_activation_passive', 'effectsDescription(EFFECT_ACTIVATION_DYNAMIC,false,false)', 'effectsDescription(EFFECT_ACTIVATION_PASSIVE,false,false)'),
    ('normal_transfer_passive', 'effectsDescription(EFFECT_ACTIVATION_TRANSFER,false,false)', 'effectsDescription(EFFECT_ACTIVATION_PASSIVE,false,false)'),
    ('normal_dynamic_uses_sockets', 'effectsDescription(EFFECT_ACTIVATION_DYNAMIC,false,false)', 'effectsDescription(EFFECT_ACTIVATION_DYNAMIC,false,true)'),
    ('socket_dynamic_embedded', 'effectsDescription(EFFECT_ACTIVATION_DYNAMIC,false,true)', 'effectsDescription(EFFECT_ACTIVATION_DYNAMIC,true,true)'),
    ('socket_passive_transfer', 'effectsDescription(EFFECT_ACTIVATION_PASSIVE,false,true)', 'effectsDescription(EFFECT_ACTIVATION_TRANSFER,false,true)'),
    ('leave_first_section_untrimmed', 'result=result+removeWhiteSpace(effectsDescription(EFFECT_ACTIVATION_DYNAMIC,false,false));', 'result=result+effectsDescription(EFFECT_ACTIVATION_DYNAMIC,false,false);'),
    ('remove_internal_linefeeds', 'result=result+removeWhiteSpace(effectsDescription(EFFECT_ACTIVATION_DYNAMIC,false,false));', 'result=result+STRINGS::replaceWString(effectsDescription(EFFECT_ACTIVATION_DYNAMIC,false,false),L"\\n",L"");'),
    ('assign_discarded_accumulator_trim', 'result=result+L"\\n"+removeWhiteSpace(effectsDescription(EFFECT_ACTIVATION_PASSIVE,false,false));\n    removeWhiteSpace(result);', 'result=result+L"\\n"+removeWhiteSpace(effectsDescription(EFFECT_ACTIVATION_PASSIVE,false,false));\n    result=removeWhiteSpace(result);'),
    ('assign_discarded_final_trim', 'result=result+L"\\n"+removeWhiteSpace(skillDescription());\n    removeWhiteSpace(result);', 'result=result+L"\\n"+removeWhiteSpace(skillDescription());\n    result=removeWhiteSpace(result);'),
    ('omit_skill_section', 'result=result+L"\\n"+removeWhiteSpace(skillDescription());', ';'),
    ('recheck_identification_midway', 'result=result+removeWhiteSpace(effectsDescription(EFFECT_ACTIVATION_DYNAMIC,false,false));', 'result=result+removeWhiteSpace(effectsDescription(EFFECT_ACTIVATION_DYNAMIC,false,false));\n    if (!m_bUnknown348) return result;'),
]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + 'std::wstring CEquipment::getEquipmentEffects' + changed)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_effects_differential')
        passed = any('equipment_effects_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_effects_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
