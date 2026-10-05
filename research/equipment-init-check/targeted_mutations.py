"""Targeted branch mutations for original-vs-recovered Equipment initialization.

Run from the repository root after the regular hand-test mutation pass. Only
scratch copies are changed; original game services stay read-only.
"""
import json
import shutil
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid

root = Path.cwd() / 'build-decomp/equipment-init-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
head, body = source.split('void CEquipment::unitInit', 1)
for name in ['EquipmentInitTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [
    ('remove_empty_name_braces', 'if (end!=-1 && start!=-1 && start+1<end) m_sUnidentifiedName', 'if (end!=-1 && start!=-1 && start+1<=end) m_sUnidentifiedName'),
    ('no_empty_player_class_wildcard', 'playerClass.compare(L"")==0 || wardrobeClass==playerClass', 'wardrobeClass==playerClass'),
    ('first_matching_wardrobe', 'path=wardrobes[i]->GetDataValue(L"ITEM_MESH",EMPTY_WSTRING);', '{path=wardrobes[i]->GetDataValue(L"ITEM_MESH",EMPTY_WSTRING);break;}'),
    ('normalize_wardrobe_path', 'path=wardrobes[i]->GetDataValue(L"ITEM_MESH",EMPTY_WSTRING);', 'path=FILESYSTEM::CleanPath(wardrobes[i]->GetDataValue(L"ITEM_MESH",EMPTY_WSTRING));'),
    ('wrong_unlimited_sentinel', '? -9999 :', '? -1 :'),
    ('clamp_negative_sockets', 'm_iSocketCount=sockets<2 ? sockets : 2;', 'm_iSocketCount=sockets<0 ? 0 : sockets<2 ? sockets : 2;'),
    ('wrong_block_effect', 'static_cast<EEFFECT_TYPE>(62)', 'static_cast<EEFFECT_TYPE>(63)'),
    ('unique_identified_before_enchant', 'if (ISA(UNITTYPES::UNIQUE)) m_bUnknown348=false;', 'if (ISA(UNITTYPES::UNIQUE)) m_bUnknown348=true;'),
    ('always_identified_from_input', 'm_pDataGroup->GetDataValue(L"ALWAYS_IDENTIFIED",false)', 'data->GetDataValue(L"ALWAYS_IDENTIFIED",false)'),
    ('sounds_from_input', 'm_pDataGroup->GetDataValue(keys[i],EMPTY_WSTRING)', 'data->GetDataValue(keys[i],EMPTY_WSTRING)'),
    ('swap_sound_slots', 'slots[]={16,17,18,10,1,20}', 'slots[]={17,16,18,10,1,20}'),
    ('clear_attached_layout_flag', 'if (!layout.empty()) m_bUnknown430=true;', 'm_bUnknown430=!layout.empty();'),
]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + 'void CEquipment::unitInit' + changed)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_init_differential')
        passed = any('equipment_init_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_init_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
