"""Targeted branch mutations for original-vs-recovered Equipment combat stats.

Run from the repository root after the regular hand-test mutation pass. Only
scratch copies are changed; original game services stay read-only.
"""
import json
import shutil
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid

root = Path.cwd() / 'build-decomp/equipment-combat-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
head, body = source.split('void CEquipment::calculateCombatStats', 1)
for name in ['EquipmentCombatStatsTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [
    ('armor_effect_flag_inverted', 'if (!skipArmorEffects)', 'if (skipArmorEffects)'),
    ('unclamped_armor_rng_upper', 'armorMinimum>armorMaximum?armorMinimum:armorMaximum', 'armorMaximum'),
    ('skip_damage_rng', 'int damage=UTILITIES::randomIntegerBetweenVolatile(m_iMinimumDamage,m_iMaximumDamage);', 'int damage=m_iMaximumDamage;'),
    ('zero_grade_forces_maximum', 'm_iUnknown28C>0', 'm_iUnknown28C>=0'),
    ('negative_armor_physical_ignored', 'if (physical!=-1)', 'if (physical>=0)'),
    ('zero_weapon_physical_ignored', 'if (physical>=0)', 'if (physical>0)'),
    ('armor_not_cached_across_effects', '(percent/100.0f)*armor', '(percent/100.0f)*m_iUnknown338'),
    ('reset_minimum_not_maximum_vector', 'm_InherentElementalDamage[i]=0', 'm_ElementalDamageBonuses[i]=0'),
    ('bow_in_primary_slot', 'm_pAttackDescriptionOverride=new CAttackDescription("BOW"', 'm_pAttackDescription=new CAttackDescription("BOW"'),
    ('staff_not_polearm', 'ISA(UNITTYPES::POLEARM) || ISA(UNITTYPES::STAFF)', 'ISA(UNITTYPES::POLEARM)'),
    ('wrong_armor_element_types', 'types[]={39,37,38,40}', 'types[]={37,39,38,40}'),
    ('attack_speed_scale', 'float attackSpeed=speed/100.0f', 'float attackSpeed=speed/10.0f'),
]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + 'void CEquipment::calculateCombatStats' + changed)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_combat_stats_differential')
        passed = any('equipment_combat_stats_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_combat_stats_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
