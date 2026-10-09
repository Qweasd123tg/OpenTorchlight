#!/usr/bin/env python3
"""Compile reviewed C++ recipes against recovered headers and prune DIFF.

The catalog is an explicit record of human/assistant assembly review, not an
inferred specification. This driver does not invent gameplay. It validates
input hashes, emits readable recipes, compiles with the pinned toolchain, and
removes every non-MATCH definition. Pruning is repeated because removing a
function can change GCC 4.4's inlining decisions in the remaining TU.
"""
import argparse
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
import os
from pathlib import Path
import shutil
import time

import llm_definitions
import objdiff
import smallmatch_layouts
import toolchain


def render(root, unit, rows):
    prior = root / 'decomp/src' / unit['tu']
    text = prior.read_text() if prior.exists() else ''
    prefix = ''.join('#include "' + h + '"\n' for h in unit['headers'] if '#include "' + h + '"' not in text)
    prefix += '\n' + unit.get('preamble', '')
    return prefix + text + '\n' + '\n'.join(r['source'] for r in rows) + '\n' + unit.get('instantiations', '')


def next_survivors(rows, comparison, targets, db):
    keep, rejected = [], []
    for row in rows:
        status, reason = llm_definitions.verdict(targets[row['address']], comparison, db)
        result = {**row, 'status': status, 'reason': reason}
        (keep if status == 'MATCH' else rejected).append(result)
    return keep, rejected


def run(kit, root, previous, catalog_path, manifest_path, output, jobs):
    started = time.monotonic()
    kit, root, previous, output = map(lambda p: Path(p).resolve(), (kit, root, previous, output))
    catalog = json.loads(Path(catalog_path).read_text())
    manifest = json.loads(Path(manifest_path).read_text())
    smallmatch_layouts.validate_manifest(kit, root, manifest)
    os.environ['TORCHLIGHT_ELF'] = str(kit / 'original/Torchlight.bin.x86_64')
    compiler = toolchain.compile_source(None, None, probe=True)
    db = json.loads((kit / 'reference/elfdb.json').read_text())
    targets = {f['address']: f for f in json.loads((kit / 'targets.json').read_text())}
    baseline = json.loads((previous / 'generation.json').read_text())
    prior_ids = {llm_definitions.identity(targets[r['address']]) for r in baseline['candidates']}
    seen = set()
    for unit in catalog['units']:
        if Path(unit['tu']).name != unit['tu'] or not unit['tu'].endswith('.cpp'):
            raise ValueError('invalid catalog TU path')
        if (previous / unit['tu']).exists():
            raise ValueError('this catalog cannot rewrite a previously generated TU')
        for row in unit['candidates']:
            f = targets.get(row['address'])
            if not f or f['source_status'] != 'MISSING' or f['size'] >= 1000 or f['tu_name'] != unit['tu']:
                raise ValueError('catalog candidate is outside missing small targets')
            identity = llm_definitions.identity(f)
            if identity in seen or identity in prior_ids:
                raise ValueError('catalog duplicates a prior or current definition')
            seen.add(identity)
            if smallmatch_layouts.digest(kit / f['assembly']) != row['assembly_sha256']:
                raise ValueError('catalog assembly evidence changed')
            error = llm_definitions.single_definition(f, row['source'])
            if error:
                raise ValueError(f['demangled'] + ': ' + error)
            if any(db['functions'][a]['size'] >= 1000 for a in llm_definitions.closure(f, db)):
                raise ValueError('catalog closure includes an excluded large function')
    output.mkdir(parents=True, exist_ok=True)
    for path in output.glob('*.cpp'):
        path.unlink()
    for path in previous.glob('*.cpp'):
        shutil.copy2(path, output / path.name)
    trials = output.parent / (output.name + '-trials')
    trials.mkdir(parents=True, exist_ok=True)
    original = objdiff.Original(db=db)

    def prune(unit):
        rows = unit['candidates']
        removed, history = [], []
        for iteration in range(len(rows) + 1):
            if not rows:
                break
            folder = trials / unit['tu'] / ('round-' + str(iteration))
            folder.mkdir(parents=True, exist_ok=True)
            path = folder / unit['tu']
            path.write_text(render(root, unit, rows))
            try:
                comparison = objdiff.compare_source(path, original, quiet=True, scores=False)
            except (Exception, SystemExit) as exc:
                comparison = {'error': str(exc), 'functions': []}
            (folder / 'comparison.json').write_text(json.dumps(comparison, indent=1) + '\n')
            keep, rejected = next_survivors(rows, comparison, targets, db)
            history.append({'round': iteration, 'input_definitions': len(rows),
                            'kept': [r['address'] for r in keep],
                            'rejected': [{'address': r['address'], 'status': r['status'], 'reason': r['reason']} for r in rejected],
                            'source_sha256': smallmatch_layouts.digest(path),
                            'object_digest': comparison.get('object_digest'), 'error': comparison.get('error')})
            removed += [{**r, 'pruning_round': iteration} for r in rejected]
            rows = keep
            if not rejected:
                # Copy exactly the source bytes that just passed, not a re-render.
                shutil.copy2(path, output / unit['tu'])
                break
        else:
            raise AssertionError('monotone pruning did not terminate')
        print(unit['tu'], 'MATCH definitions:', len(rows), 'rejected:', len(removed), 'TU comparisons:', len(history), flush=True)
        return rows, removed, {'tu': unit['tu'], 'rounds': history}

    selected, rejected, histories = [], [], []
    with ThreadPoolExecutor(max_workers=jobs) as pool:
        for keep, removed, history in pool.map(prune, catalog['units']):
            selected += keep; rejected += removed; histories.append(history)
    all_candidates = baseline['candidates'] + selected
    selected_addresses = {a for row in selected for a in row['closure']}
    blocked = [r for r in baseline['blocked'] if r['address'] not in selected_addresses]
    failures = {r['address']: r for r in rejected}
    blocked = [failures.get(r['address'], r) for r in blocked]
    report = {'schema': 3, 'policy': 'reviewed-layout-recipes-monotone-pruning', 'compiler': compiler,
              'catalog_sha256': smallmatch_layouts.digest(catalog_path),
              'recovery_manifest_sha256': smallmatch_layouts.digest(manifest_path),
              'previous_generation_sha256': smallmatch_layouts.digest(previous / 'generation.json'),
              'candidates': all_candidates, 'blocked': blocked, 'candidate_count': len(all_candidates),
              'candidate_bytes': sum(r['original_size'] for r in all_candidates),
              'families': dict(Counter(r['family'] for r in all_candidates)),
              'new_reviewed_hypotheses': sum(len(u['candidates']) for u in catalog['units']),
              'new_matched_definitions': len(selected), 'new_rejected_definitions': len(rejected),
              'tu_comparisons': sum(len(h['rounds']) for h in histories),
              'tu_count': len(list(output.glob('*.cpp'))), 'elapsed_seconds': time.monotonic() - started,
              'game_executions': 0, 'external_model_calls': 0,
              'note': 'Every new TU passed after removing all DIFF recipes. Full old/new source and header regression is still required.'}
    for name, value in [('generation.json', report), ('recovery-history.json', histories), ('recovery-rejected.json', rejected)]:
        (output / name).write_text(json.dumps(value, ensure_ascii=False, indent=2) + '\n')
    print(json.dumps({k: v for k, v in report.items() if k not in ('candidates', 'blocked')}, indent=2), flush=True)
    return report


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--kit', type=Path, required=True)
    parser.add_argument('--previous-candidates', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--catalog', type=Path, default=Path(__file__).with_name('smallmatch-recovery-catalog.json'))
    parser.add_argument('--manifest', type=Path, default=Path(__file__).with_name('smallmatch-recovery-manifest.json'))
    parser.add_argument('--jobs', type=int, choices=(1, 2), default=2)
    args = parser.parse_args()
    run(args.kit, Path(__file__).resolve().parents[2], args.previous_candidates,
        args.catalog, args.manifest, args.output, args.jobs)
