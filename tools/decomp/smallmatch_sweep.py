#!/usr/bin/env python3
"""Generate bounded C++ hypotheses and keep only pinned-compiler MATCH results.

Every trial is isolated outside decomp/src. The final candidates preserve full
original TUs and still require smallmatch_verify.py's combined regression pass.
"""
import argparse
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor, as_completed
import hashlib
import json
import os
from pathlib import Path
import time

import llm_definitions
import objdiff
import smallmatch_families
from smallmatch import Generator, Unsupported
import toolchain


def render(g, rows):
    prior = g.root / 'decomp/src' / rows[0]['tu']
    text = prior.read_text() if prior.exists() else ''
    headers = {r['header'] for r in rows}
    headers.update(r['callee_header'] for r in rows if 'callee_header' in r)
    headers.update(h for r in rows for h in r.get('extra_headers', []))
    text = ''.join('#include "' + h + '"\n' for h in sorted(headers)
                   if '#include "' + h + '"' not in text) + text
    return text + '\n' + '\n'.join(r['source'] for r in rows)


def run(g, output, jobs):
    output = Path(output).resolve()
    output.mkdir(parents=True, exist_ok=True)
    trials = output.parent / (output.name + '-trials')
    trials.mkdir(parents=True, exist_ok=True)
    # Reusing an output directory must never retain a stale accepted TU.
    for path in output.glob('*.cpp'):
        path.unlink()
    os.environ['TORCHLIGHT_ELF'] = str(g.kit / 'original/Torchlight.bin.x86_64')
    compiler = toolchain.compile_source(None, None, probe=True)
    original = objdiff.Original(db=g.db)
    rows, blocked, seen = [], [], set()
    for f in g.targets:
        identity = llm_definitions.identity(f)
        try:
            if identity in seen:
                raise Unsupported('same C++ definition is tested through its representative')
            try:
                row = g.generate(f)
            except Unsupported as old_reason:
                try:
                    row = smallmatch_families.generate(g, f)
                except Unsupported as new_reason:
                    raise Unsupported(str(old_reason) + '; ' + str(new_reason))
            seen.add(identity)
            row['assembly_sha256'] = hashlib.sha256((g.kit / f['assembly']).read_bytes()).hexdigest()
            rows.append(row)
        except Unsupported as exc:
            blocked.append({'address': f['address'], 'name': f['demangled'], 'tu': f['tu_name'],
                            'original_size': f['size'], 'status': 'BLOCKED', 'reason': str(exc)})
    print('Source hypotheses:', len(rows), dict(Counter(r['family'] for r in rows)), flush=True)
    targets = {f['address']: f for f in g.targets}
    started = time.monotonic()

    def probe(row):
        folder = trials / row['address']
        folder.mkdir(parents=True, exist_ok=True)
        versions = [row['source']] + row.get('alternatives', [])
        attempts = []
        for index, source in enumerate(versions):
            variant = {**row, 'source': source}
            variant_dir = folder / ('variant-' + str(index))
            variant_dir.mkdir(parents=True, exist_ok=True)
            path = variant_dir / row['tu']
            path.write_text(render(g, [variant]))
            try:
                result = objdiff.compare_source(path, original, quiet=True, scores=False)
                status, reason = llm_definitions.verdict(targets[row['address']], result, g.db)
            except (Exception, SystemExit) as exc:
                result = {'error': str(exc), 'functions': []}
                status, reason = 'compile-error', str(exc)
            (variant_dir / 'comparison.json').write_text(json.dumps(result, indent=1) + '\n')
            attempts.append({'variant': index, 'status': status, 'reason': reason,
                             'source_sha256': hashlib.sha256(source.encode()).hexdigest()})
            if status == 'MATCH':
                break
        (folder / 'comparison.json').write_text(json.dumps(result, indent=1) + '\n')
        variant.pop('alternatives', None)
        return {**variant, 'status': status, 'reason': reason, 'attempts': attempts}

    verdicts = []
    with ThreadPoolExecutor(max_workers=jobs) as pool:
        futures = [pool.submit(probe, row) for row in rows]
        for i, future in enumerate(as_completed(futures), 1):
            row = future.result()
            verdicts.append(row)
            print(i, '/', len(rows), row['status'], row['name'], flush=True)
    accepted = sorted((r for r in verdicts if r['status'] == 'MATCH'), key=lambda r: (r['tu'], r['address']))
    blocked += [r for r in verdicts if r['status'] != 'MATCH']
    units = defaultdict(list)
    for row in accepted:
        units[row['tu']].append(row)
    for tu, group in units.items():
        (output / tu).write_text(render(g, group))
    report = {'schema': 2, 'policy': 'smallmatch-v2-static-sweep', 'compiler': compiler,
              'candidates': accepted, 'blocked': blocked, 'candidate_count': len(accepted),
              'candidate_bytes': sum(r['original_size'] for r in accepted),
              'families': dict(Counter(r['family'] for r in accepted)), 'tu_count': len(units),
              'trial_count': len(verdicts), 'trial_statuses': dict(Counter(r['status'] for r in verdicts)),
              'elapsed_seconds': time.monotonic() - started,
              'note': 'Individual static trials passed. Combined TUs require smallmatch_verify.py.'}
    (output / 'generation.json').write_text(json.dumps(report, ensure_ascii=False, indent=2) + '\n')
    (trials / 'verdicts.json').write_text(json.dumps(verdicts, ensure_ascii=False, indent=2) + '\n')
    print(json.dumps({k: v for k, v in report.items() if k not in ('candidates', 'blocked')}, indent=2), flush=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--kit', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--jobs', type=int, default=2, choices=(1, 2))
    args = parser.parse_args()
    run(Generator(args.kit, Path(__file__).resolve().parents[2]), args.output, args.jobs)
