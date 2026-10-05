"""Targeted branch mutations for original-vs-recovered Equipment particle selection.

Run from the repository root after the regular hand-test mutation pass. Only
scratch copies are changed; original game services stay read-only.
"""
import json
import shutil
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid

root = Path.cwd() / 'build-decomp/equipment-particles-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
import mutate
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x885a70'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentParticlesTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('ignore_quest', 'if (getIsQuestUnit())', 'if (false)'), ('ignore_unique', 'else if (ISA(UNITTYPES::UNIQUE))', 'else if (false)'), ('ignore_magical', 'else if (isMagical())', 'else if (false)'), ('wrong_drop_quest', 'particle=L"QUEST_ITEM"', 'particle=L"GENERIC_WEAPON"'), ('wrong_drop_unique', 'particle=L"UNIQUE_WEAPON"', 'particle=L"GENERIC_WEAPON"'), ('wrong_drop_magic', 'particle=L"MAGIC_WEAPON"', 'particle=L"GENERIC_WEAPON"'), ('always_create_custom', 'if (!m_pParticle_3D0)\n        {', 'if (true)\n        {'), ('skip_preload', 'CMasterResourceManager::getSingleton()->m_pParticlePreloader->LoadParticle(m_sUnknown3D8);', ';'), ('drop_case_sensitive', 'STRINGS::StringUpper(*reinterpret_cast<const std::wstring*>(&m_pParticle_3D0->m_pUnknown110))', '*reinterpret_cast<const std::wstring*>(&m_pParticle_3D0->m_pUnknown110)'), ('element_case_sensitive', 'STRINGS::StringUpper(*reinterpret_cast<const std::wstring*>(&m_pParticle->m_pUnknown110))', '*reinterpret_cast<const std::wstring*>(&m_pParticle->m_pUnknown110)'), ('retain_wrong_drop', 'delete m_pParticle_3D0;', ';'), ('retain_wrong_element', 'delete m_pParticle;', ';'), ('ignore_drop_visible', 'm_pParticle_3D0 && m_bVisible && !m_pEquippedTo && m_pUnitModel', 'm_pParticle_3D0 && !m_pEquippedTo && m_pUnitModel'), ('ignore_drop_equipped', 'm_pParticle_3D0 && m_bVisible && !m_pEquippedTo && m_pUnitModel', 'm_pParticle_3D0 && m_bVisible && m_pUnitModel'), ('gate_element_on_visible', 'if (m_pParticle && m_pUnitModel)', 'if (m_pParticle && m_pUnitModel && m_bVisible)'), ('gate_element_on_equipped', 'if (m_pParticle && m_pUnitModel)', 'if (m_pParticle && m_pUnitModel && !m_pEquippedTo)'), ('skip_weapon_guard', 'if (!ISA(UNITTYPES::WEAPON)) return;', ';'), ('zero_electric_counts', 'damage>0?DAMAGE_ELECTRIC:DAMAGE_PHYSICAL', 'damage>=0?DAMAGE_ELECTRIC:DAMAGE_PHYSICAL'), ('poison_wins_ties', 'if (damage>largest) type=DAMAGE_POISON', 'if (damage>=largest) type=DAMAGE_POISON'), ('electricity_pistol_name', 'L"WEAPON_ELECTRICITY_PISTOL"', 'L"WEAPON_ELECTRICITY"'), ('fire_pistol_name', 'L"WEAPON_FIRE_PISTOL"', 'L"WEAPON_FIRE"'), ('ice_pistol_name', 'L"WEAPON_ICE_PISTOL"', 'L"WEAPON_ICE"'), ('poison_pistol_name', 'L"WEAPON_POISON_PISTOL"', 'L"WEAPON_POISON"')]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + changed + tail)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_particles_differential')
        passed = any('equipment_particles_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_particles_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
