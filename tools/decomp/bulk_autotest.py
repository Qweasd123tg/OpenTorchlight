#!/usr/bin/env python3
"""Explore all written, unaccepted game functions in one diagnostic hybrid.

    python3 tools/decomp/bulk_autotest.py --out build-decomp/bulk-probe --run

This does not publish source, mutate the acceptance registry or run the full
regression suite. Generic random objects are diagnostic inputs, especially for
constructors, destructors and containers. A passing probe still needs review
of legal object lifetimes and branch coverage before behavioral acceptance.
"""
from __future__ import annotations

import argparse
from collections import Counter
import json
from pathlib import Path
import re
import time

import autotest
import check
import elfdb
import evidence
import hybrid
import toolchain


def select(db, progress, addresses=()):
    game = {tu['id'] for tu in db['tus'] if tu['kind'] == 'game'}
    wanted = {hex(int(address, 16)) for address in addresses}
    accepted = set(progress.get('accepted', {}))
    # Some reports store the accepted list under the matching/game summary.
    accepted.update(progress.get('comparison_evidence', {}))
    rows = {}
    for unit in progress['units']:
        for row in unit['functions']:
            address = row.get('address')
            f = db['functions'].get(address)
            if (f and f['tu'] in game and f['kind'] in check.WRITTEN
                    and row['status'] == 'DIFF' and not row.get('weak')
                    and address not in accepted and (not wanted or address in wanted)):
                rows[address] = f
    if wanted - rows.keys():
        raise ValueError('addresses are not unaccepted strong game DIFF: ' +
                         ', '.join(sorted(wanted - rows.keys())))
    return [rows[address] for address in sorted(rows, key=lambda a: int(a, 16))]


def classify(address, lines, valid):
    """Keep diagnostic PASS separate from acceptance and reject partial runs."""
    name = 'auto_' + address[2:]
    if not valid:
        return {'status': 'INVALID_RUN'}
    coverage = [m for line in lines
                if (m := re.fullmatch(r'\s+coverage (\w+) (0x[0-9a-f]+) completed (\d+) '
                                      r'different (\d+) incomplete (\d+)', line))
                and m.group(1) == name and m.group(2) == address]
    if len(coverage) != 1:
        return {'status': 'MISSING_COVERAGE'}
    completed, different, incomplete = map(int, coverage[0].groups()[2:])
    passed = any(re.fullmatch(r'tlhybrid: ' + re.escape(name) + r'\s+PASS \(0\)', line)
                 for line in lines)
    status = ('DIFFERENT' if different else 'INCOMPLETE' if incomplete else
              'TOO_FEW_NORMAL_PAIRS' if completed < autotest.MIN_COMPLETED else
              'PASSED_PROBE' if passed else 'FAILED_FIXTURE')
    return {'status': status, 'completed': completed, 'different': different,
            'incomplete': incomplete, 'fixture': name}


def save(path, value):
    path.write_text(json.dumps(value, ensure_ascii=False, indent=1) + '\n')


def fixture_manifest(directory):
    return evidence.manifest_paths([(p.name, p) for p in sorted(directory.glob('*.cpp'))])


def run(out, execute=False, addresses=()):
    root = elfdb.ROOT.resolve()
    out = Path(out).resolve()
    if not out.is_relative_to(root / 'build-decomp'):
        raise ValueError('--out must be inside this checkout\'s ignored build-decomp')
    if out.exists() and any(out.iterdir()):
        raise ValueError('use a new empty output directory; earlier probes are preserved')
    out.mkdir(parents=True, exist_ok=True)
    fixtures = out / 'fixtures'
    fixtures.mkdir()
    gen = autotest.Generator()
    progress = json.loads((root / 'build-decomp/progress.json').read_text())
    functions = select(gen.db, progress, addresses)
    before = evidence.input_manifest(gen.db)
    save(out / 'inputs-before.json', before)
    started = time.monotonic()
    rows, sources = [], []
    for f in functions:
        row = {'address': f['address'], 'name': f['demangled'], 'kind': f['kind']}
        rows.append(row)
        try:
            includes, code = gen.test_for(f)
        except autotest.Unsupported as error:
            row.update(status='UNSUPPORTED', reason=str(error))
            continue
        path = fixtures / ('Auto_' + f['address'][2:] + '.cpp')
        head = ['#include "EmptyStrings.h"'] + [f'#include "{h}"' for h in sorted(includes)] + [
            '#include "TArrayList.h"', '#include "AutoTest.h"', '#include <cstring>', '']
        path.write_text('\n'.join(head) + code)
        row.update(status='GENERATED', source=path.relative_to(out).as_posix())
        sources.append((row, path))
    report = {'schema': 1, 'mode': 'DIAGNOSTIC_ONLY', 'acceptance_claims': 0,
              'original_elf_sha256': gen.db['original_elf_sha256'],
              'inputs_digest': evidence.manifest_digest(before), 'functions': rows,
              'selected': len(functions), 'generated': len(sources)}
    save(out / 'report.json', report)
    print(f'selected {len(functions)} unaccepted strong game functions; generated {len(sources)}', flush=True)
    if execute:
        def compile_one(item):
            row, path = item
            obj = path.with_suffix('.o')
            try:
                toolchain.compile_source(path, obj, ['-I', str(hybrid.HYBRID)], quiet=True)
            except SystemExit as error:
                log = path.with_suffix('.compile-error.txt')
                log.write_text(str(error) + '\n')
                row.update(status='COMPILE_ERROR', diagnostics=log.relative_to(out).as_posix())
                return None
            finally:
                obj.unlink(missing_ok=True)
            return path
        compiled = [p for p in toolchain.parallel_map(compile_one, sources, phase='build') if p]
        report['compiled'] = len(compiled)
        save(out / 'report.json', report)
        print(f'compiled {len(compiled)} probes; building one hybrid with all production TUs', flush=True)
        if compiled:
            runtime = autotest.write_runtime(fixtures)
            fixture_before = fixture_manifest(fixtures)
            save(out / 'fixtures-before.json', fixture_before)
            # A changed canonical input during compilation must not be mixed
            # into the runtime diagnostic, even though no result is published.
            if not check.unchanged_inputs(before, evidence.input_manifest(gen.db), 'bulk probe inputs changed'):
                raise ValueError('canonical inputs changed before hybrid build')
            blob, loader = hybrid.build(out=out / 'hybrid', tests=[runtime, *compiled])
            code, lines = hybrid.selftest(blob, loader)
            (out / 'selftest.txt').write_text('\n'.join(lines) + '\n')
            after = evidence.input_manifest(gen.db)
            fixture_after = fixture_manifest(fixtures)
            save(out / 'inputs-after.json', after)
            save(out / 'fixtures-after.json', fixture_after)
            unchanged = (check.unchanged_inputs(before, after, 'bulk probe inputs changed') and
                         fixture_before == fixture_after)
            valid = unchanged and code in (0, 1)
            report.update(returncode=code, unchanged_inputs=unchanged, valid_run=valid)
            for row in rows:
                if row['status'] == 'GENERATED':
                    row.update(classify(row['address'], lines, valid))
        else:
            report.update(returncode=2, valid_run=False)
    report['elapsed'] = time.monotonic() - started
    report['states'] = dict(Counter(row['status'] for row in rows))
    save(out / 'report.json', report)
    print(json.dumps(report['states'], sort_keys=True), flush=True)
    return 0 if not execute or report.get('valid_run') else 2


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('addresses', nargs='*')
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--run', action='store_true')
    args = parser.parse_args()
    return run(args.out, args.run, args.addresses)


if __name__ == '__main__':
    raise SystemExit(main())
