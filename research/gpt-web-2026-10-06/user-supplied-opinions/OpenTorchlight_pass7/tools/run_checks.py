#!/usr/bin/env python3
"""Reproduce pass 7 on a local original archive tree, without modifying that tree.
Requires Python 3.10+, GNU g++, and the bundled CEGUI 0.6.2 sources in the tree.
This runs synthetic fixtures and archive analysis; it never executes the game.
"""
from __future__ import annotations
import argparse,hashlib,json,subprocess,sys
from pathlib import Path
import binding_recipes,resource_recipes,effect_table_inventory
from check_cegui_recipes import run as check_cegui
from check_snapshot_roundtrip import run as check_snapshot


def digest_tree(root: Path) -> dict[str,str]:
    return {p.relative_to(root).as_posix():hashlib.sha256(p.read_bytes()).hexdigest()
            for p in root.rglob('*') if p.is_file()}


def save(path: Path,value) -> None:
    path.write_text(json.dumps(value,indent=2,ensure_ascii=False)+'\n',encoding='utf-8')


def main() -> None:
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('root',type=Path,help='Extracted original OpenTorchlight-main directory')
    parser.add_argument('--out',type=Path,default=Path(__file__).resolve().parents[1]/'results')
    args=parser.parse_args();root=args.root.resolve();out=args.out.resolve()
    if not (root/'research/original-symbols.txt').is_file():
        parser.error('root must contain research/original-symbols.txt')
    if out==root or root in out.parents:
        parser.error('output must be outside the original project')
    out.mkdir(parents=True,exist_ok=True);before=digest_tree(root)
    package=Path(__file__).resolve().parents[1]
    tests=subprocess.run([sys.executable,'-m','unittest','discover','-s',str(package/'tests'),'-v'],
                         capture_output=True,text=True,timeout=30)
    (out/'unit-tests.txt').write_text(tests.stdout+tests.stderr)
    if tests.returncode:raise RuntimeError('unit tests failed; see unit-tests.txt')
    bindings=binding_recipes.run(root);resources=resource_recipes.run(root)
    tables=effect_table_inventory.run(root)
    save(out/'binding-recipes.json',bindings);save(out/'resource-recipes.json',resources)
    save(out/'effect-table-inventory.json',tables)
    check_cegui(root,out,bindings)
    src=package/'examples/resource_default_test.cpp'
    # Verify that the three fixture expressions really occur among this archive's recipes.
    names=('SAVE','USEOWNERLEVEL','EXCLUSIVE')
    for name in names:
        rows=[r for r in resources['reads'] if 'CEffect::CEffect' in r['function']
              and r.get('key_literal')=='L"'+name+'"' and 'candidate_expression'in r]
        if not rows or not any(r['candidate_expression'] in src.read_text() for r in rows):
            raise RuntimeError('fixture recipe not found in archive: '+name)
    exe=out/'resource_default_test'
    cmd=['g++','-std=gnu++98','-O2','-fno-strict-aliasing',str(src),'-o',str(exe)]
    subprocess.run(cmd,check=True,capture_output=True,text=True,timeout=30)
    done=subprocess.run([str(exe)],check=True,capture_output=True,text=True,timeout=10)
    save(out/'resource-default-test.json',json.loads(done.stdout))
    check_snapshot(out)
    after=digest_tree(root)
    changed=[p for p in sorted(set(before)|set(after)) if before.get(p)!=after.get(p)]
    save(out/'reproduction-integrity.json',{'checked_files':len(before),'modified_missing_or_added':changed})
    if changed:raise RuntimeError('input tree changed during checks')
    save(out/'summary.json',{
        'scope':'archived candidates and limited fixtures only; no game binary executed',
        'binding_complete_recipes':bindings['complete_recipes'],
        'binding_typed_candidates':bindings['typed_construction_candidates'],
        'binding_exact_callback_signatures':bindings['exact_callback_signatures_confirmed'],
        'resource_literal_candidates':resources['literal_key_candidates'],
        'resource_bool_copyback_candidates':resources['bool_copyback_candidates'],
        'effect_table_shapes':tables['table_count'],
        'effect_table_candidate_rows':tables['row_count_candidates'],
        'game_table_values_extracted':False,'original_files_unchanged':not changed,
        'new_original_game_functions_accepted':0})
    print('All checks passed. Original input tree unchanged.')

if __name__=='__main__':
    main()
