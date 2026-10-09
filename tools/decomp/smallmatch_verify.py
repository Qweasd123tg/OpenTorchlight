#!/usr/bin/env python3
"""Reproduce a static MATCH-kit pass without publication or game execution.

Run from the unmodified source snapshot with the smallmatch tools installed.
All candidate TUs retain the complete prior source. Headers equal the kit or
an explicitly reviewed recovery manifest; config always equals the kit.
Header recovery additionally requires prior candidates, unit reports and ledgers.
Only unique, strong target addresses count. The original ELF is never run.
"""
import argparse
from collections import Counter
from concurrent.futures import ThreadPoolExecutor, as_completed
import hashlib
import json
import os
from pathlib import Path
import sys
import time

import llm_definitions
import objdiff
import toolchain


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def check_inputs(kit, root, candidate_dir, recovery_manifest=None, previous_candidates=None):
    subpaths = ('decomp/src',) if recovery_manifest else ('decomp/include', 'decomp/src')
    if recovery_manifest:
        import smallmatch_layouts
        smallmatch_layouts.validate_manifest(kit, root, json.loads(Path(recovery_manifest).read_text()))
    for subpath in subpaths:
        expected = {p.relative_to(kit / 'project' / subpath): digest(p)
                    for p in (kit / 'project' / subpath).rglob('*') if p.is_file()}
        actual = {p.relative_to(root / subpath): digest(p)
                  for p in (root / subpath).rglob('*') if p.is_file()}
        if expected != actual:
            raise ValueError(subpath + ' differs from kit; use a separate checkout at its base commit')
    if digest(root / 'decomp/config.json') != digest(kit / 'project/decomp/config.json'):
        raise ValueError('compiler configuration differs from kit')
    for path in candidate_dir.glob('*.cpp'):
        prior = root / 'decomp/src' / path.name
        if prior.exists() and prior.read_text() not in path.read_text():
            raise ValueError('candidate does not preserve complete prior TU: ' + path.name)
    if previous_candidates:
        for prior in Path(previous_candidates).glob('*.cpp'):
            current = candidate_dir / prior.name
            if not current.exists() or prior.read_text() not in current.read_text():
                raise ValueError('candidate does not preserve prior generated TU: ' + prior.name)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--kit', type=Path, required=True)
    parser.add_argument('--candidate-dir', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--jobs', type=int, default=2)
    parser.add_argument('--previous-ledger', type=Path,
                        help='address ledger of the prior pass; all its MATCH results must remain')
    parser.add_argument('--baseline-matches', type=Path,
                        help='JSON list of previously accepted strong machine-match addresses')
    parser.add_argument('--recovery-manifest', type=Path, help='reviewed exact header changes and original type witnesses')
    parser.add_argument('--previous-candidates', type=Path, help='all prior generated C++ TUs to preserve')
    parser.add_argument('--previous-units', type=Path, help='prior existing/candidate unit reports for unknown-reference regression')
    args = parser.parse_args()
    kit, candidates, out = args.kit.resolve(), args.candidate_dir.resolve(), args.output.resolve()
    root = Path(__file__).resolve().parents[2]
    if args.jobs < 1 or args.jobs > 2:
        parser.error('use one or two compiler workers')
    if args.recovery_manifest and not all((args.previous_candidates, args.previous_units, args.previous_ledger, args.baseline_matches)):
        parser.error('header recovery requires previous candidates, unit reports, ledger and baseline match addresses')
    check_inputs(kit, root, candidates, args.recovery_manifest, args.previous_candidates)
    layout_report = None
    if args.recovery_manifest:
        import smallmatch_layouts
        layout_report = smallmatch_layouts.verify_layouts(kit, root, args.recovery_manifest, out / 'layout')
    os.environ['TORCHLIGHT_ELF'] = str(kit / 'original/Torchlight.bin.x86_64')
    identity = toolchain.compile_source(None, None, probe=True)
    db = json.loads((kit / 'reference/elfdb.json').read_text())
    targets = {f['address']: f for f in json.loads((kit / 'targets.json').read_text())}
    accepted = set(json.loads((kit / 'reference/accepted-main.json').read_text())['accepted'])
    generation = json.loads((candidates / 'generation.json').read_text())
    original = objdiff.Original(db=db)
    out.mkdir(parents=True, exist_ok=True)
    started = time.monotonic()

    def compile_one(phase, path):
        tick = time.monotonic()
        try:
            row = objdiff.compare_source(path, original, quiet=True, scores=False)
        except (Exception, SystemExit) as exc:
            row = {'tu': path.name, 'source': str(path), 'error': str(exc), 'functions': []}
        row.update(seconds=time.monotonic() - tick, source_sha256=digest(path), phase=phase)
        (out / (phase + '-' + path.name + '.json')).write_text(json.dumps(row, indent=1) + '\n')
        return phase, path.name, row

    work = [('existing', p) for p in sorted((root / 'decomp/src').glob('*.cpp'))]
    work += [('candidate', p) for p in sorted(candidates.glob('*.cpp'))]
    phases = {'existing': {}, 'candidate': {}}
    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        futures = [pool.submit(compile_one, phase, path) for phase, path in work]
        for i, future in enumerate(as_completed(futures), 1):
            phase, name, result = future.result()
            phases[phase][name] = result
            if i % 20 == 0 or 'error' in result:
                print(i, '/', len(work), phase, name, result.get('error', 'OK')[:200], flush=True)

    final = {**phases['existing'], **phases['candidate']}
    def matches(units):
        return {f['address']: f for u in units.values() for f in u['functions']
                if f.get('address') and f['status'] == 'MATCH' and not f.get('weak')}
    before, after = matches(phases['existing']), matches(final)
    regressions = sorted((set(before) & accepted) - set(after))
    expected_baseline = (set(json.loads(args.baseline_matches.read_text()))
                         if args.baseline_matches else set(before) & accepted)
    if not expected_baseline <= accepted:
        raise ValueError('baseline match list contains an address absent from accepted-main.json')
    regressions = sorted(set(regressions) | (expected_baseline - set(after)))
    previous = ({r['address'] for r in json.loads(args.previous_ledger.read_text())
                 if r['status'] == 'MATCH'} if args.previous_ledger else set())
    if not previous <= set(targets):
        raise ValueError('previous ledger contains MATCH addresses outside the task kit')
    previous_regressions = sorted(previous - set(after))
    errors = {phase + ':' + name: row['error'] for phase, units in phases.items()
              for name, row in units.items() if 'error' in row}
    unknown = {}
    for name, unit in phases['candidate'].items():
        prior_names = {x['name'] for x in phases['existing'].get(name, {}).get('unknown', [])}
        new_names = {x['name'] for x in unit.get('unknown', [])} - prior_names
        if new_names:
            unknown[name] = sorted(new_names)
    if args.previous_units:
        previous_units = {}
        for phase in ('existing', 'candidate'):
            for path in sorted(args.previous_units.glob(phase + '-*.json')):
                row = json.loads(path.read_text())
                previous_units[path.name[len(phase) + 1:-len('.json')]] = row
        if not set(phases['existing']) <= set(previous_units):
            raise ValueError('previous unit reports do not cover every existing TU')
        for name, unit in final.items():
            prior_names = {x['name'] for x in previous_units.get(name, {}).get('unknown', [])}
            new_names = {x['name'] for x in unit.get('unknown', [])} - prior_names
            if new_names:
                unknown[name] = sorted(set(unknown.get(name, [])) | new_names)
    vtable_report = None
    if args.recovery_manifest and not errors:
        import smallmatch_vtables
        vtable_report = smallmatch_vtables.verify(original, json.loads(args.recovery_manifest.read_text()), candidates, out / 'vtables')
    verdicts = []
    for candidate in generation['candidates']:
        f = targets[candidate['address']]
        unit = phases['candidate'].get(candidate['tu'], {'functions': []})
        status, reason = llm_definitions.verdict(f, unit, db)
        verdicts.append({**candidate, 'status': status, 'reason': reason})
    newly_verified = sorted(set(targets) & set(after))
    existing_verified = sorted(set(targets) & set(before))
    generated_verified = sorted(set(newly_verified) - set(existing_verified))
    summary = {'schema': 1, 'base_commit': '824e3d3a33242c9ea775ca8a5ff36e87d6fd23ee',
               'original_elf_sha256': original.image.sha256, 'compiler': identity,
               'target_count': len(targets), 'new_match_count': len(newly_verified),
               'new_original_bytes': sum(targets[a]['size'] for a in newly_verified),
               'existing_source_new_matches': len(existing_verified),
               'existing_source_new_bytes': sum(targets[a]['size'] for a in existing_verified),
               'generated_new_matches': len(generated_verified),
               'generated_new_bytes': sum(targets[a]['size'] for a in generated_verified),
               'generated_definition_count': len(verdicts),
               'header_recovery': layout_report, 'new_class_vtables': vtable_report,
               'previous_cpp_tus_preserved': len(list(args.previous_candidates.glob('*.cpp'))) if args.previous_candidates else None,
               'generated_verdicts': dict(Counter(r['status'] for r in verdicts)),
               'prior_accepted_machine_matches_checked': len(set(before) & accepted),
               'accepted_machine_regressions': regressions, 'compile_errors': errors,
               'baseline_machine_matches_required': len(expected_baseline),
               'previous_pass_matches_required': len(previous),
               'previous_pass_regressions': previous_regressions,
               'incremental_match_count': len(set(newly_verified) - previous),
               'incremental_original_bytes': sum(targets[a]['size'] for a in set(newly_verified) - previous),
               'new_unknown_references': unknown, 'elapsed_seconds': time.monotonic() - started,
               'existing_tus': len(phases['existing']), 'candidate_tus': len(phases['candidate']),
               'game_executions': 0, 'model_calls': 0, 'published': False,
               'tool_sha256': {p.name: digest(p) for p in (root / 'tools/decomp').glob('*.py')
                               if p.name in ('objdiff.py', 'objdiff_eh.py', 'elfimage.py', 'toolchain.py',
                                             'smallmatch.py', 'smallmatch_verify.py',
                                             'smallmatch_families.py', 'smallmatch_sweep.py',
                                             'smallmatch_layouts.py', 'smallmatch_recovery.py', 'smallmatch_vtables.py')}}
    ledger = []
    blocked = {r['address']: r for r in generation['blocked']}
    for address, target in targets.items():
        matched = after.get(address)
        ledger.append({'address': address, 'name': target['demangled'], 'tu': target['tu_name'],
                       'original_size': target['size'],
                       'status': 'MATCH' if matched else blocked.get(address, {}).get('status', 'UNVERIFIED'),
                       'route': (('existing_cpp_recovered_headers' if args.recovery_manifest and address not in previous else 'existing_cpp_metadata') if address in existing_verified else 'generated_cpp') if matched else None,
                       'object_digest': matched.get('object_digest') if matched else None,
                       'reason': None if matched else blocked.get(address, {}).get('reason', 'not verified')})
    (out / 'summary.json').write_text(json.dumps(summary, ensure_ascii=False, indent=2) + '\n')
    (out / 'ledger.json').write_text(json.dumps(ledger, ensure_ascii=False, indent=1) + '\n')
    (out / 'generated-verdicts.json').write_text(json.dumps(verdicts, ensure_ascii=False, indent=2) + '\n')
    print(json.dumps(summary, ensure_ascii=False, indent=2), flush=True)
    failed = regressions or previous_regressions or errors or unknown or any(r['status'] != 'MATCH' for r in verdicts)
    return 1 if failed else 0


if __name__ == '__main__':
    sys.exit(main())
