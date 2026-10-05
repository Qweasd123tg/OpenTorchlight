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

root = Path.cwd() / 'build-decomp/equipment-enchant-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
import mutate
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x8845c0'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentEnchantTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('no_force_randommagic', 'if (ISA(UNITTYPES::RANDOMMAGIC)) force=true;', ';'), ('skip_generatable', 'if (!attempt && m_bItemFlag20A)', 'if (!attempt)'), ('ignore_force', 'attempt=force;', 'attempt=false;'), ('randomize_forced', 'if (!force)', 'if (true)'), ('chance_inclusive', 'attempt=roll<CGameGlobals', 'attempt=roll<=CGameGlobals'), ('chance_scale', 'm_fRandomEnchantChance*10.0f', 'm_fRandomEnchantChance'), ('ignore_unique_affixes', '(!ISA(UNITTYPES::UNIQUE) || emptyUnique)', 'true'), ('allow_socketable_socket', 'ISA(UNITTYPES::NECKLACE)))\n        {', 'ISA(UNITTYPES::NECKLACE) || ISA(UNITTYPES::RANDOMMAGIC_SOCKETABLE)))\n        {'), ('skip_primary_affixes', 'm_pResourceManager->createAffixesForUnit(this,m_iUnknown274,count);', ';'), ('wrong_primary_level', 'this,m_iUnknown274,count', 'this,m_iUnknown274+1,count'), ('wrong_fallback_level', 'this,m_iUnknown274+1,count', 'this,m_iUnknown274,count'), ('skip_unique_fallback', 'm_pResourceManager->createAffixesForUnit(this,m_iUnknown274+1,count);', ';'), ('wrong_passive_count', 'm_EffectData10+0x18', 'm_EffectData10'), ('reroll_existing_sockets', 'm_iSocketCount==0 &&', 'true &&'), ('ignore_resource_guard', 'm_pResourceManager && m_pResourceManager->getLevel()', 'm_pResourceManager->getLevel()'), ('ignore_level_guard', 'm_pResourceManager->getLevel() &&', 'true &&'), ('socket_inclusive', 'roll<CGameGlobals::getSingleton()->m_fRandomSocketChance', 'roll<=CGameGlobals::getSingleton()->m_fRandomSocketChance'), ('second_inclusive', 'roll<CGameGlobals::getSingleton()->m_fSecondSocketChance', 'roll<=CGameGlobals::getSingleton()->m_fSecondSocketChance'), ('allow_unique_socket', '&& !ISA(UNITTYPES::UNIQUE) &&', '&& true &&'), ('zero_based_sockets', 'm_iSocketCount=1+', 'm_iSocketCount=0+'), ('wrong_socket_roll', 'roll=UTILITIES::randomBetweenVolatile(0.0f,1000.0f);\n            m_iSocketCount', 'roll=0.0f;\n            m_iSocketCount'), ('skip_always_identified', 'if (!m_bUnknown348 && m_pDataGroup', 'if (false && m_pDataGroup'), ('ignore_identified_guard', 'if (!m_bUnknown348 && m_pDataGroup', 'if (m_pDataGroup'), ('skip_price', 'recalculatePrice();', ';')]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + changed + tail)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_enchant_differential')
        passed = any('equipment_enchant_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_enchant_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
