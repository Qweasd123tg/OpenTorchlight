"""Targeted branch mutations for original-vs-recovered Equipment price.

Run from the repository root after the regular hand-test mutation pass. Only
scratch copies are changed; original game services stay read-only.
"""
import json
import shutil
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid

root = Path.cwd() / 'build-decomp/equipment-price-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
import mutate
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x883e20'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentPriceTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('no_zero_value_exit', 'if (value!=0)', 'if (true)'), ('wrong_default_value', 'GetDataValue(L"VALUE",100)', 'GetDataValue(L"VALUE",99)'), ('reset_normal_on_zero', 'm_iUnknown268=1;', 'm_iUnknown268=1; m_iUnknown26C=1; m_iUnknown270=1;'), ('wrong_level_floor', 'std::max(m_iUnknown274,1)', 'std::max(m_iUnknown274,0)'), ('ignore_unique', 'if (ISA(UNITTYPES::UNIQUE))', 'if (false)'), ('ignore_magic', 'else if (isMagical())', 'else if (false)'), ('wrong_unique_buy_curve', 'L"PRICE_PLAYERBUY_UNIQUE"', 'L"PRICE_PLAYERSELL_UNIQUE"'), ('wrong_unique_sell_curve', 'L"PRICE_PLAYERSELL_UNIQUE"', 'L"PRICE_PLAYERBUY_UNIQUE"'), ('wrong_magic_buy_curve', 'L"PRICE_PLAYERBUY_MAGIC"', 'L"PRICE_PLAYERSELL_MAGIC"'), ('wrong_magic_sell_curve', 'L"PRICE_PLAYERSELL_MAGIC"', 'L"PRICE_PLAYERBUY_MAGIC"'), ('wrong_gambler_type', '->ISA(UNITTYPES::GAMBLER)', '->ISA(UNITTYPES::PLAYER)'), ('wrong_gamble_curve', 'L"PRICE_PLAYERGAMBLE_MAGIC"', 'L"PRICE_PLAYERBUY_NORMAL"'), ('264_floor', 'm_iUnknown264=static_cast<int>(ceilf(buyValue*(static_cast<float>(value)/100.0f)))', 'm_iUnknown264=static_cast<int>(floorf(buyValue*(static_cast<float>(value)/100.0f)))'), ('264_rounding_order', 'm_iUnknown264=static_cast<int>(ceilf(buyValue*(static_cast<float>(value)/100.0f)))', 'm_iUnknown264=static_cast<int>(ceilf((buyValue*static_cast<float>(value))/100.0f))'), ('268_floor', 'm_iUnknown268=static_cast<int>(ceilf(sellValue*(static_cast<float>(value)/100.0f)))', 'm_iUnknown268=static_cast<int>(floorf(sellValue*(static_cast<float>(value)/100.0f)))'), ('268_rounding_order', 'm_iUnknown268=static_cast<int>(ceilf(sellValue*(static_cast<float>(value)/100.0f)))', 'm_iUnknown268=static_cast<int>(ceilf((sellValue*static_cast<float>(value))/100.0f))'), ('26C_floor', 'm_iUnknown26C=static_cast<int>(ceilf(buyValue*(static_cast<float>(value)/100.0f)))', 'm_iUnknown26C=static_cast<int>(floorf(buyValue*(static_cast<float>(value)/100.0f)))'), ('26C_rounding_order', 'm_iUnknown26C=static_cast<int>(ceilf(buyValue*(static_cast<float>(value)/100.0f)))', 'm_iUnknown26C=static_cast<int>(ceilf((buyValue*static_cast<float>(value))/100.0f))'), ('270_floor', 'm_iUnknown270=static_cast<int>(ceilf(sellValue*(static_cast<float>(value)/100.0f)))', 'm_iUnknown270=static_cast<int>(floorf(sellValue*(static_cast<float>(value)/100.0f)))'), ('270_rounding_order', 'm_iUnknown270=static_cast<int>(ceilf(sellValue*(static_cast<float>(value)/100.0f)))', 'm_iUnknown270=static_cast<int>(ceilf((sellValue*static_cast<float>(value))/100.0f))')]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + changed + tail)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_price_differential')
        passed = any('equipment_price_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_price_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
