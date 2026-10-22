#!/usr/bin/env python3
"""Reviewed-input, read-only MATCH screening; never a promotion/publishing tool."""
import argparse
from contextlib import contextmanager
import hashlib
import json
import os
import shutil
from pathlib import Path
import sys

sys.dont_write_bytecode = True


class GateError(ValueError):
    pass


def require(ok, message):
    if not ok:
        raise GateError(message)


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def json_default(value):
    if isinstance(value, set):
        return sorted(value)
    raise TypeError(type(value))


def read_json(path):
    return json.loads(Path(path).read_text())


def verify_files(entries):
    require(isinstance(entries, dict) and entries, 'empty file identity inventory')
    for path, digest in entries.items():
        require(Path(path).is_absolute() and str(Path(path).resolve()) == path, 'identity paths must be resolved absolute paths')
        require(sha(path) == digest, 'identity mismatch: ' + path)


def inventory(root, pattern):
    return {str(p.resolve()) for p in Path(root).rglob(pattern) if p.is_file()}


def key(row):
    return row['name'], row.get('address')


def row_map(rows):
    result = {key(r): r for r in rows}
    require(len(result) == len(rows), 'duplicate name/address rows')
    return result


def validate_manifest(path, expected_digest):
    require(sha(path) == expected_digest, 'reviewed manifest SHA mismatch')
    m = read_json(path)
    require(m.get('schema') == 1, 'unsupported manifest schema')
    require(m.get('scope') == 'exact-object-single-tu', 'unsupported scope')
    required = {'source', 'object', 'database', 'elf', 'library', 'owners', 'config', 'objdump'}
    require(set(m['inputs']) == required, 'incomplete or unknown required input roles')
    identities = {}
    def add_identity(path, digest):
        require(Path(path).is_absolute(), 'input paths must be absolute')
        resolved = str(Path(path).resolve())
        require(resolved not in identities or identities[resolved] == digest, 'conflicting identity: ' + resolved)
        identities[resolved] = digest
        return resolved
    input_paths = [add_identity(item['path'], item['sha256']) for item in m['inputs'].values()]
    require(len(set(input_paths)) == len(input_paths), 'input roles share a path')
    for group in ('tool_files', 'dependencies', 'compiler_files', 'baseline_tool_files', 'provenance'):
        verify_files(m[group])
        for p, digest in m[group].items():
            add_identity(p, digest)
    protected = set(input_paths) | {str(Path(p).resolve()) for group in ('tool_files', 'dependencies', 'compiler_files', 'baseline_tool_files') for p in m[group]}
    receipt_paths = set()
    for role in ('binding', 'baseline_result', 'baseline_receipt'):
        p = str(Path(m[role]['path']).resolve())
        require(p not in protected and p not in receipt_paths, 'receipt role collides with execution input or another receipt')
        add_identity(m[role]['path'], m[role]['sha256'])
        receipt_paths.add(p)
    verify_files(identities)
    w = Path(m['worktree']).resolve()
    require(inventory(w / 'tools/decomp', '*.py') == set(m['tool_files']), 'tool closure changed')
    require(inventory(w / 'decomp/include', '*') <= set(m['dependencies']), 'header closure incomplete')
    for role, relative in [('source', 'decomp/src/' + m['tu']), ('owners', 'decomp/owners.json'), ('config', 'decomp/config.json')]:
        require(Path(m['inputs'][role]['path']).resolve() == w / relative, role + ' path outside declared worktree')
    owners = read_json(m['inputs']['owners']['path'])['tus']
    require(owners.get(m['tu']) == m['owner'], 'ownership mismatch')
    common = {role: item['sha256'] for role, item in m['inputs'].items()}
    common['dependencies'] = m['dependencies']
    common['compiler_files'] = m['compiler_files']
    binding = read_json(m['binding']['path'])
    require(binding.get('schema') == 1 and binding.get('common_identity') == common,
            'source/object/dependency/compiler binding does not cover current inputs')
    require(binding.get('compiler_config') == read_json(m['inputs']['config']['path']), 'compiler configuration mismatch')
    require(isinstance(binding.get('globalized'), list) and all(isinstance(x, str) for x in binding['globalized']), 'invalid globalization')
    baseline = read_json(m['baseline_result']['path'])
    receipt = read_json(m['baseline_receipt']['path'])
    require(receipt.get('scope') == 'full-tu' and receipt.get('common_identity') == common,
            'baseline not bound to the same complete input identity')
    require(receipt.get('result_sha256') == m['baseline_result']['sha256'], 'baseline result unbound')
    require(receipt.get('tool_files') == m['baseline_tool_files'], 'baseline tool identity unbound')
    require(baseline.get('tu') == m['tu'] and baseline.get('object_digest') == common['object'], 'baseline TU/object mismatch')
    require(baseline.get('source') == 'decomp/src/' + m['tu'], 'baseline source spelling must be canonical and bound to the declared TU')
    prior = row_map(baseline['functions'])
    require(sorted([list(k) for k in prior], key=repr) == sorted(receipt['row_keys'], key=repr), 'baseline completeness receipt mismatch')
    for row in prior.values():
        require(row.get('object_digest') == common['object'], 'baseline row object mismatch')
    require(isinstance(m['selected'], list) and m['selected'], 'empty selection')
    selected = {(r['name'], r['address']) for r in m['selected']}
    require(len(selected) == len(m['selected']), 'duplicate selection')
    require(selected <= prior.keys(), 'selected address absent from bound baseline')
    require(all(prior[k]['status'] in ('DIFF', 'MATCH') for k in selected), 'selected baseline row not comparable')
    return m, identities, baseline, binding


def assess(baseline, screen, selected, full=None):
    require(isinstance(baseline.get('source'), str) and bool(baseline['source']), 'baseline source absent')
    require(screen.get('source') == baseline['source'] and screen.get('tu') == baseline.get('tu'), 'screen source/TU differs')
    prior, screened = row_map(baseline['functions']), row_map(screen['functions'])
    require(set(screened) == set(selected), 'screen output incomplete or extra')
    require(screen['object_digest'] == baseline['object_digest'], 'screen object differs')
    require(screen['unknown'] == baseline['unknown'], 'unknown references changed')
    require(all(r.get('object_digest') == baseline['object_digest'] for r in screened.values()), 'screen row object mismatch')
    require(all(r['status'] in ('MATCH', 'DIFF') for r in screened.values()), 'screen missing/extra target')
    prior_matches = {r.get('address') for r in prior.values() if r['status'] == 'MATCH'}
    new = sorted({k[1] for k, r in screened.items() if r['status'] == 'MATCH'
                  and prior[k]['status'] != 'MATCH' and k[1] not in prior_matches})
    report = {'screening_only': True, 'validated_comparator_report': False,
              'promotion_authorized': False, 'canonical_new_addresses': new,
              'canonical_candidates': [{'address': address, 'category': 'strict-match-only',
                                        'historically_tested': False, 'countable_historical_gain': False}
                                       for address in new],
              'functions': screen['functions'], 'unknown': screen['unknown'],
              'object_digest': screen['object_digest'], 'source': screen['source'], 'tu': screen['tu'], 'required_next_gate': 'cold full-TU comparison and exact prior MATCH retention'}
    if full is not None:
        require(full.get('source') == baseline['source'] and full.get('tu') == baseline.get('tu'), 'full source/TU differs')
        current = row_map(full['functions'])
        require(all(r.get('object_digest') == baseline['object_digest'] for r in current.values()), 'full row object mismatch')
        require(set(current) == set(prior), 'full row inventory changed (missing/extra/alias)')
        require(full['object_digest'] == baseline['object_digest'], 'full object differs')
        require(full['unknown'] == baseline['unknown'], 'full unknown references changed')
        require(all(current[k] == r for k, r in prior.items() if r['status'] == 'MATCH'), 'prior MATCH dictionary regressed')
        require(all(current[k] == r for k, r in screened.items()), 'screen and full target dictionaries differ')
        report.update(screening_only=False, validated_comparator_report=True,
                      functions=full['functions'], required_next_gate='human integration policy; no automatic promotion')
    return report


@contextmanager
def exact_object(objdiff, object_path, globalized, selection=None):
    old = objdiff.compile_for_diff, objdiff._load_norm_cache, objdiff.object_functions
    objdiff.compile_for_diff = lambda *a, **kw: (object_path, set(globalized))
    objdiff._load_norm_cache = lambda *a: {}
    captured = {}
    def selected_objects(*a, **kw):
        records = old[2](*a, **kw)
        captured.update(records)
        if selection is None:
            return records
        names = {k[0] for k in selection}
        require(names <= records.keys(), 'selected object symbols absent')
        return {name: record for name, record in records.items() if name in names}
    objdiff.object_functions = selected_objects
    try:
        yield captured
    finally:
        objdiff.compile_for_diff, objdiff._load_norm_cache, objdiff.object_functions = old


def run(m, baseline, binding, full_on_gain=False):
    # This imports a reviewed exact tool closure, not a downloaded candidate package.
    os.environ['TORCHLIGHT_GAME_DIR'] = str(Path(m['inputs']['library']['path']).parent.parent)
    os.environ['OTL_ORIGINAL_DISASM'] = 'function'
    os.environ['PATH'] = str(Path(m['inputs']['objdump']['path']).parent) + os.pathsep + os.environ.get('PATH', '')
    # CLI owns a fresh process; never accidentally reuse an already-imported
    # comparator/dependency from another worktree or a previous tool revision.
    tool_modules = {Path(path).stem for path in m['tool_files']}
    require(not tool_modules.intersection(sys.modules), 'tool modules already imported; use a fresh process')
    sys.path.insert(0, str(Path(m['worktree']) / 'tools/decomp'))
    require(Path(shutil.which('objdump')).resolve() == Path(m['inputs']['objdump']['path']).resolve(), 'wrong objdump resolution')
    import objdiff
    require(Path(objdiff.__file__).resolve() in {Path(p) for p in m['tool_files']}, 'wrong comparator import')
    require(sha(objdiff.literal_library_path()) == objdiff.OGRE_LITERAL_SHA256 == m['inputs']['library']['sha256'], 'unpinned literal library')
    require(Path(objdiff.literal_library_path()).resolve() == Path(m['inputs']['library']['path']).resolve(), 'library path differs')
    selected = {(r['name'], r['address']) for r in m['selected']}
    def compare(selection):
        original = objdiff.Original(db=read_json(m['inputs']['database']['path']), elf=m['inputs']['elf']['path'])
        with exact_object(objdiff, m['inputs']['object']['path'], binding['globalized'], selection) as records:
            result = objdiff.compare_source(Path(m['inputs']['source']['path']), original, quiet=True, scores=False)
        # Every baseline object symbol must be represented, even when screening.
        require(set(records) <= {r['name'] for r in baseline['functions']}, 'baseline omitted object symbols')
        if selection is not None:
            result['functions'] = [r for r in result['functions'] if key(r) in selection]
        addresses = {r.get('address') for r in result['functions']}
        evidence = {'object_functions': records, 'original_functions': {k: v for k, v in original._norm_cache.items() if k.rsplit(':', 1)[-1] in addresses}}
        return result, evidence
    screen, screen_evidence = compare(selected)
    report = assess(baseline, screen, selected)
    if full_on_gain and report['canonical_new_addresses']:
        full, full_evidence = compare(None)
        report = assess(baseline, screen, selected, full)
        report['full_evidence'] = full_evidence
    report['evidence_scope'] = 'full object parsing; selected original normalization' if report['screening_only'] else 'full object and full-TU original normalization'
    report['screen_evidence'] = screen_evidence
    return report


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--manifest', type=Path, required=True)
    p.add_argument('--manifest-sha256', required=True, help='Externally reviewed manifest digest; never auto-trust current inputs')
    p.add_argument('--output', type=Path, required=True)
    p.add_argument('--full-on-gain', action='store_true')
    a = p.parse_args()
    m, identities, baseline, binding = validate_manifest(a.manifest, a.manifest_sha256)
    output = a.output.resolve()
    require(not output.is_relative_to(Path(m['worktree']).resolve()), 'output must be outside worktree')
    require(str(output) not in identities and output != a.manifest.resolve(), 'output collides with input')
    require(not output.exists(), 'refusing to overwrite evidence')
    report = run(m, baseline, binding, a.full_on_gain)
    verify_files(identities)
    require(sha(a.manifest) == a.manifest_sha256, 'manifest changed during comparison')
    require(inventory(Path(m['worktree']) / 'tools/decomp', '*.py') == set(m['tool_files']), 'tool closure changed during comparison')
    require(inventory(Path(m['worktree']) / 'decomp/include', '*') <= set(m['dependencies']), 'header closure changed during comparison')
    report.update(schema=1, manifest_sha256=a.manifest_sha256, input_identity=identities, tu=m['tu'])
    with output.open('x') as stream:
        json.dump(report, stream, indent=2, default=json_default)
    print(json.dumps({'output': str(output), 'validated_comparator_report': report['validated_comparator_report'], 'promotion_authorized': False}))


if __name__ == '__main__':
    main()
