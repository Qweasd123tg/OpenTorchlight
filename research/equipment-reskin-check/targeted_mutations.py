"""Targeted branch mutations for original-vs-recovered Equipment reskin.

Run from the repository root after the regular hand-test mutation pass. Only
scratch copies are changed; original game services stay read-only.
"""
import json
import shutil
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid

root = Path.cwd() / 'build-decomp/equipment-reskin-targeted'
(root / 'src').mkdir(parents=True, exist_ok=True)
(root / 'tests').mkdir(parents=True, exist_ok=True)
source = Path('decomp/src/Equipment.cpp').read_text()
import mutate
db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
a,b=mutate.definition(source,mutate.mask(source),db['functions']['0x888920'])
head,body,tail=source[:a],source[a:b+1],source[b+1:]
for name in ['EquipmentReskinTest.cpp', 'Detour.h']:
    shutil.copyfile(Path('decomp/hybrid/tests') / name, root / 'tests' / name)
mutations = [('case_sensitive_group', 'STRINGS::StringUpper(wardrobes[i]->GetDataValue(L"CLASS",L""))', 'wardrobes[i]->GetDataValue(L"CLASS",L"")'), ('case_sensitive_query', 'wardrobeClass==STRINGS::StringUpper(characterClass)', 'wardrobeClass==characterClass'), ('empty_query_wildcard', 'wardrobeClass==STRINGS::StringUpper(characterClass)', 'characterClass.empty() || wardrobeClass==STRINGS::StringUpper(characterClass)'), ('wrong_primary_key', 'L"ITEM_MESH"', 'L"MESH"'), ('wrong_secondary_key', 'L"ITEM_MESH_SECONDARY"', 'L"MESH_SECONDARY"'), ('reset_primary_on_missing', 'GetDataValue(L"ITEM_MESH",primary)', 'GetDataValue(L"ITEM_MESH",EMPTY_WSTRING)'), ('reset_secondary_on_missing', 'GetDataValue(L"ITEM_MESH_SECONDARY",secondary)', 'GetDataValue(L"ITEM_MESH_SECONDARY",EMPTY_WSTRING)'), ('stop_first_match', 'secondary=wardrobes[i]->GetDataValue(L"ITEM_MESH_SECONDARY",secondary);', 'secondary=wardrobes[i]->GetDataValue(L"ITEM_MESH_SECONDARY",secondary); break;'), ('reload_empty_primary', 'if (primary!=EMPTY_WSTRING)', 'if (true)'), ('case_sensitive_current', 'STRINGS::StringUpper(primary)!=STRINGS::StringUpper(current)', 'primary!=current'), ('always_reload', 'STRINGS::StringUpper(primary)!=STRINGS::StringUpper(current)', 'true'), ('swap_meshes', 'loadModel(primary,secondary)', 'loadModel(secondary,primary)'), ('discard_secondary', 'loadModel(primary,secondary)', 'loadModel(primary,EMPTY_WSTRING)'), ('clean_path_here', 'loadModel(primary,secondary)', 'loadModel(FILESYSTEM::CleanPath(primary),secondary)')]
results = []
for name, before, after in [('baseline', '', '')] + mutations:
    if name != 'baseline' and body.count(before) != 1:
        raise SystemExit('ambiguous source replacement: ' + name)
    changed = body if name == 'baseline' else body.replace(before, after, 1)
    (root / 'src/Equipment.cpp').write_text(head + changed + tail)
    try:
        blob, loader = hybrid.build(out=root / name, src=root / 'src', tests=sorted((root / 'tests').glob('*.cpp')), verbose=False)
        code, report = hybrid.selftest(blob, loader, only='equipment_reskin_differential')
        passed = any('equipment_reskin_differential' in line and 'PASS (0)' in line for line in report)
        if name == 'baseline' and (code != 0 or not passed):
            raise SystemExit('targeted baseline failed: ' + '\n'.join(report))
        outcome = 'pass' if name == 'baseline' else 'survived' if passed else 'killed' if any('equipment_reskin_differential' in line and 'FAIL' in line for line in report) else 'inconclusive'
        row = {'name': name, 'outcome': outcome, 'exit': code}
    except Exception as e:
        row = {'name': name, 'outcome': 'inconclusive', 'error': str(e)}
    results.append(row)
    print(json.dumps(row), flush=True)
(root / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
