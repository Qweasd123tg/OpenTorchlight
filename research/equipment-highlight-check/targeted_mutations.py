"""Targeted branch mutations for original-vs-recovered Equipment item-label colors.

Run from the repository root after the regular hand-test mutation pass. Only
scratch copies are changed; original game services stay read-only.
"""
import json
import shutil
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid

root = Path.cwd() / 'build-decomp/equipment-highlight-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
import mutate
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x8824f0'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentTextTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('always_apply', 'getHighlighted() == highlighted', 'false'), ('never_front', 'if (highlighted)\n        m_pItemText->moveToFront();', 'if (false)\n        m_pItemText->moveToFront();'), ('front_when_unselected', 'if (highlighted)\n        m_pItemText->moveToFront();', 'if (!highlighted)\n        m_pItemText->moveToFront();'), ('ignore_quest', 'if (getIsQuestUnit())', 'if (false)'), ('ignore_set', 'else if (getSet()!=EMPTY_WSTRING)', 'else if (getSet()==EMPTY_WSTRING)'), ('ignore_unique', 'else if (ISA(UNITTYPES::UNIQUE))', 'else if (false)'), ('ignore_magic', 'isMagical() || ISA(UNITTYPES::RANDOMMAGIC_SOCKETABLE)', 'isMagical() && ISA(UNITTYPES::RANDOMMAGIC_SOCKETABLE)'), ('ignore_socketable', 'isMagical() || ISA(UNITTYPES::RANDOMMAGIC_SOCKETABLE)', 'isMagical()'), ('wrong_rare_branch', 'if (ISA(UNITTYPES::MAGIC))', 'if (!ISA(UNITTYPES::MAGIC))'), ('wrong_set_color', 'getSetColor(highlighted)', 'getSetColor(!highlighted)'), ('wrong_quest_color', 'getQuestColor(highlighted)', 'getQuestColor(!highlighted)'), ('wrong_unique_color', 'getUniqueColor(highlighted)', 'getUniqueColor(!highlighted)'), ('wrong_rare_color', 'getRareColor(highlighted)', 'getRareColor(!highlighted)'), ('wrong_random_color', 'getRandomEnchantColor(highlighted)', 'getRandomEnchantColor(!highlighted)'), ('wrong_plain_color', 'colour(0.8f,0.8f,0.8f,1.0f)', 'colour(0.7f,0.7f,0.7f,1.0f)')]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + changed + tail)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_text_colors_and_order')
        passed = any('equipment_text_colors_and_order' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_text_colors_and_order' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
