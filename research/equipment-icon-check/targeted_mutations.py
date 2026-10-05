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

root = Path.cwd() / 'build-decomp/equipment-icon-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
head, body = source.split('void CEquipment::createIcon', 1)
for name in ['EquipmentIconTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('ignore_force_gate', '(m_pIconWindow && !force)', 'm_pIconWindow'), ('invert_force_gate', '(m_pIconWindow && !force)', '(m_pIconWindow && force)'), ('clear_gambler_flag_wrong', 'm_bGamblerIcon=false;', 'm_bGamblerIcon=true;'), ('gambler_flag_not_set', 'm_bGamblerIcon=true;', 'm_bGamblerIcon=false;'), ('gambler_fallback_empty', 'GetDataValue(L"GAMBLER_ICON",icon)', 'GetDataValue(L"GAMBLER_ICON",EMPTY_WSTRING)'), ('no_empty_class_wildcard', 'playerClass.compare(L"")==0 || wardrobeClass==playerClass', 'wardrobeClass==playerClass'), ('wrong_wardrobe_field', 'GetDataValue(L"ICON",EMPTY_WSTRING);\n        }', 'GetDataValue(L"ITEM_MESH",EMPTY_WSTRING);\n        }'), ('parent_as_child', 'imageWindow=m_pIconWindow->getChildAtIdx(0);', 'imageWindow=m_pIconWindow;'), ('fixed_container_size', 'CEGUI::UDim(0,ui.scaledY(64.0f)),CEGUI::UDim(0,ui.scaledY(96.0f))', 'CEGUI::UDim(0,64.0f),CEGUI::UDim(0,96.0f)'), ('ignore_missing_image', 'if (!image) return;', ';'), ('width_not_scaled', 'width=image->getWidth()/CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(KSETTINGS_YRATIO);', 'width=image->getWidth();'), ('height_uses_width', 'height=image->getHeight()/', 'height=image->getWidth()/'), ('left_position_wrong', '(64.0f-width)*0.5f/64.0f', '(64.0f-width)/64.0f'), ('top_position_wrong', '(96.0f-height)*0.5f/96.0f', '(96.0f-height)/96.0f'), ('image_property_wrong_case', 'setProperty("Image",', 'setProperty("image",'), ('mouse_passthrough_disabled', 'setMousePassThroughEnabled(true)', 'setMousePassThroughEnabled(false)'), ('events_not_muted', 'setMutedState(true)', 'setMutedState(false)'), ('missing_child_attachment', 'if (!existing) m_pIconWindow->addChildWindow(imageWindow);', ';')]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + 'void CEquipment::createIcon' + changed)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_icon_differential')
        passed = any('equipment_icon_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_icon_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
