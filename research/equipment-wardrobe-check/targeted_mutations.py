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

root = Path.cwd() / 'build-decomp/equipment-wardrobe-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
import mutate
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x87fa70'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentWardrobeTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('query_case_sensitive', 'characterClass=STRINGS::StringUpper(characterClass);', ';'), ('group_case_sensitive', 'STRINGS::StringUpper(wardrobes[i]->GetDataValue(L"CLASS",L""))', 'wardrobes[i]->GetDataValue(L"CLASS",L"")'), ('remove_query_wildcard', 'characterClass.compare(L"")==0 || wardrobeClass==characterClass', 'wardrobeClass==characterClass'), ('wrong_wildcard_side', 'characterClass.compare(L"")==0 || wardrobeClass==characterClass', 'wardrobeClass.compare(L"")==0 || wardrobeClass==characterClass'), ('item_mesh_wrong_key', 'GetDataValue(L"MESH",EMPTY_WSTRING)', 'GetDataValue(L"ITEM_MESH",EMPTY_WSTRING)'), ('icon_wrong_key', 'GetDataValue(L"TEXTURE",EMPTY_WSTRING)', 'GetDataValue(L"ICON",EMPTY_WSTRING)'), ('require_mesh_and_texture', 'GetDataValue(L"MESH",EMPTY_WSTRING)!=EMPTY_WSTRING ||', 'GetDataValue(L"MESH",EMPTY_WSTRING)!=EMPTY_WSTRING &&'), ('skip_last_group', 'i<count;', 'i+1<count;'), ('skip_first_group', 'unsigned int i=0;', 'unsigned int i=1;')]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + changed + tail)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_wardrobe_differential')
        passed = any('equipment_wardrobe_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_wardrobe_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
