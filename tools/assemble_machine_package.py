#!/usr/bin/env python3
"""Assemble exact raw bodies with the shared emitter; no ABI/owner inference.

Static dependencies are collected automatically. Observed CALLIND addresses
add exact dispatcher entries, without assuming exhaustive target coverage.
No guest execution, replay, registry promotion or original-file mutation.
"""
from __future__ import annotations

import argparse
from dataclasses import dataclass, field
import hashlib
import json
from pathlib import Path
import subprocess
import sys

from automation_state import source_snapshot, validate_output, write_json
from function_package import ELF_PATH, normalize
import lift_pcode as lift
from original import Original
from run_lift_pipeline import _read_preparation
from screen_function_lifts import load_raw, merge_raw
from setup_ghidra import DIRECTORY

ROOT = Path(__file__).resolve().parents[1]
MAX_FUNCTIONS, MAX_ROUNDS, MAX_BATCH = 4096, 16, 1024


def address(value):
    if not isinstance(value, str):
        raise ValueError('entry must be an exact hexadecimal string')
    return '0x' + normalize(value)


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def exact_entries(original):
    sizes = {}
    for symbol in original.symbols:
        if symbol.kind in 'TtWw' and symbol.size:
            sizes.setdefault(address(hex(symbol.address)), set()).add(symbol.size)
    return {a: next(iter(s)) for a, s in sizes.items() if len(s) == 1 and int(a, 16)}


def inspect_closure(roots, raw, exact, profile, maximum):
    """Reuse the actual emitter's full operation gates, not a second screen."""
    imports = lift.validate_imports(profile)
    selected, reports, missing, pending = set(), {}, set(), list(roots)
    approved = set(exact) - set(imports)
    while pending:
        entry = pending.pop()
        if entry in selected:
            continue
        if entry not in approved:
            raise ValueError('entry is not an exact unambiguous sized source body: ' + entry)
        if len(selected) >= maximum:
            raise ValueError('selected body budget exceeded; no partial program published')
        selected.add(entry)
        source = raw.get(entry)
        if source is None:
            missing.add(entry)
            continue
        if source['raw_status'] != 'verified':
            raise ValueError('failed raw export requires review, not automatic retry: ' + entry)
        _, report = lift.compile_function(source['packet'], {'return': 'void', 'input_registers': []},
            433, source['raw_sha256'], approved, imports, shared_machine=True)
        reports[entry] = report
        for edge in report['approved_dependencies']:
            if edge['kind'] in {'direct_call', 'tail_jump'}:
                pending.append(edge['target'])
    return sorted(selected), sorted(missing), reports


@dataclass(frozen=True)
class Options:
    output: Path
    entries: tuple[str, ...]
    raw_dirs: tuple[Path, ...] = ()
    observed_targets: tuple[Path, ...] = ()
    profile: Path = field(default_factory=lambda: ROOT / 'research/lifted-ui/shared-machine.json')
    original: Path = field(default_factory=lambda: Path(ELF_PATH))
    home: Path = field(default_factory=lambda: ROOT / 'build-source-cache/ghidra' / DIRECTORY)
    analysis_root: Path = field(default_factory=lambda: ROOT / 'build-ghidra-lift')
    max_functions: int = 256
    max_rounds: int = 4
    export: bool = False
    prepare_project: bool = False


def run(options, *, root=ROOT, runner=None, snapshotter=source_snapshot, original_factory=Original):
    root = Path(root).resolve()
    for name, cap in (('max_functions', MAX_FUNCTIONS), ('max_rounds', MAX_ROUNDS)):
        value = getattr(options, name)
        if type(value) is not int or not 1 <= value <= cap:
            raise ValueError(f'{name} must be 1..{cap}')
    if not options.entries or len(options.entries) > options.max_functions:
        raise ValueError('explicit roots required within selected-body budget')
    if options.prepare_project and not options.export:
        raise ValueError('project preparation requires explicit --export')
    protected = [options.original.resolve().parent, options.home, options.analysis_root,
                 options.profile, *options.raw_dirs, *options.observed_targets]
    validate_output(root, options.output, protected, directory=True)
    if options.output.exists() or options.output.is_symlink():
        raise ValueError('fresh output required; previous evidence is preserved')
    baseline = snapshotter(root)
    options.output.mkdir(parents=True)
    out = options.output.resolve()
    summary = dict(schema=1, kind='shared-machine-package', status='BLOCKED',
        source_sha256=baseline['sha256'], source_consistent=True, commands=[], inputs={},
        selected_entries=[], missing_entries=[], dynamic_callsites=[], counts=dict(exported=0, rounds=0),
        original_status_promotions=0, game_executed=False, original_modified=False,
        project_database_modified=False, project_preparation_unconfirmed=False,
        dynamic_target_coverage='not exhaustive; only supplied or observed exact entries',
        replay_performed=False)

    def check_inputs():
        try:
            changed = (snapshotter(root)['sha256'] != baseline['sha256'] or
                       any(digest(p) != h for p, h in summary['inputs'].items()))
        except OSError:
            changed = True
        if changed:
            summary.update(status='STALE', source_consistent=False)
            raise ValueError('source/profile/raw/observation inputs changed during assembly')

    def pin(path):
        path = str(Path(path).resolve())
        current = digest(path)
        if path in summary['inputs'] and summary['inputs'][path] != current:
            raise ValueError('changed reused input: ' + path)
        summary['inputs'][path] = current

    def child(script, destination, targets):
        check_inputs()
        command = [sys.executable, str(root / 'tools' / script), '--targets-file', str(targets),
            '--output', str(destination), '--original', str(options.original.resolve()),
            '--home', str(options.home.resolve()), '--analysis-root', str(options.analysis_root.resolve())]
        if script == 'screen_function_lifts.py':
            command += ['--export', '--limit', str(MAX_BATCH)]
        item = dict(command=command, log=str(out / f"child-{len(summary['commands']):03d}.log"))
        summary['commands'].append(item)
        if script == 'prepare_lift_project.py':
            summary['project_preparation_unconfirmed'] = True
        if runner:
            code = runner(command, Path(item['log']))
        else:
            with Path(item['log']).open('w') as stream:
                code = subprocess.run(command, stdout=stream, stderr=subprocess.STDOUT,
                                      timeout=960, check=False).returncode
        item['exit_code'] = code
        check_inputs()
        if code:
            raise ValueError(f'{script} failed ({code}); see {item["log"]}')
        if script == 'prepare_lift_project.py':
            _read_preparation(destination, targets.read_text().splitlines())
            summary.update(project_database_modified=True, project_preparation_unconfirmed=False)
        else:
            report = json.loads((destination / 'report.json').read_text())
            if (report.get('kind') != 'raw-function-lift-screening' or report.get('schema') != 1 or
                    report.get('status') != 'SCREENED' or report.get('source_consistent') is not True or
                    report.get('original_status_promotions') != 0 or report.get('game_executed') is not False or
                    report.get('original_modified') is not False or
                    {address(r['address']) for r in report['selection']['selected']} !=
                    set(targets.read_text().splitlines())):
                raise ValueError('export child identity/selection/read-only guarantees differ')

    try:
        pin(options.profile); profile = json.loads(options.profile.read_text())
        if (profile.get('schema') != 1 or profile.get('execution_mode') != 'shared_machine' or
                profile.get('memory_space_id') != 433 or 'functions' in profile or
                type(profile.get('max_call_depth', 64)) is not int or
                not 1 <= profile.get('max_call_depth', 64) <= 64):
            raise ValueError('verified shared_machine profile required')
        original = original_factory(options.original)
        pin(options.original)
        if (profile['original_elf_sha256'] != original.sha256 or
                summary['inputs'][str(options.original.resolve())] != original.sha256):
            raise ValueError('profile ELF differs from original')
        summary['original_elf_sha256'] = original.sha256
        exact = exact_entries(original)
        roots = {address(a) for a in options.entries}
        summary['explicit_roots'] = sorted(roots)
        for path in options.observed_targets:
            pin(path); observation = json.loads(path.read_text())
            if (observation.get('schema') != 1 or observation.get('kind') != 'observed-machine-call-targets' or
                    observation.get('original_elf_sha256') != original.sha256 or
                    not isinstance(observation.get('targets'), list) or not observation['targets'] or
                    len(observation['targets']) > options.max_functions):
                raise ValueError('invalid/stale observed target report')
            roots.update(address(a) for a in observation['targets'])
        raw = {}

        def reuse(directory, expected=None):
            # Pin before and after loading, including every manifest member.
            pin(directory / 'manifest.json')
            manifest = json.loads((directory / 'manifest.json').read_text())
            for row in manifest['functions']:
                path = (directory / row['json']).resolve()
                if not path.is_relative_to(directory.resolve()):
                    raise ValueError('unsafe raw member path')
                pin(path)
            members, paths, _ = load_raw(directory, original)
            if expected is not None and set(members) != set(expected):
                raise ValueError('exported raw entries differ from exact requested set')
            for path in paths: pin(path)
            merge_raw(raw, members)  # Conflicting/failed packets never silently replaced.

        for directory in options.raw_dirs: reuse(directory)
        for iteration in range(options.max_rounds + 1):
            selected, missing, reports = inspect_closure(roots, raw, exact, profile, options.max_functions)
            summary.update(selected_entries=selected, missing_entries=missing,
                dynamic_callsites=[dict(caller=a, **edge) for a, r in sorted(reports.items())
                                  for edge in r['approved_dependencies'] if edge['kind'] == 'indirect_call'])
            if not missing:
                paths = [raw[a]['raw_path'] for a in selected]
                header, report = lift.generate(paths, profile)
                check_inputs()
                (out / 'program.hpp').write_text(header)
                write_json(out / 'generation.json', report)
                summary.update(status='GENERATED', generated_header_sha256=digest(out / 'program.hpp'))
                break
            (out / 'missing-targets.txt').write_text(''.join(a+'\n' for a in missing))
            if not options.export:
                summary['status'] = 'NEEDS_EXPORT'; break
            if iteration == options.max_rounds:
                summary['status'] = 'ROUND_BUDGET'; break
            summary['counts']['rounds'] += 1
            for start in range(0, len(missing), MAX_BATCH):
                batch = missing[start:start+MAX_BATCH]
                prefix = out / f'round-{iteration+1:02d}-batch-{start//MAX_BATCH:03d}'
                targets = prefix.with_suffix('.txt')
                targets.write_text(''.join(a+'\n' for a in batch))
                if options.prepare_project:
                    child('prepare_lift_project.py', Path(str(prefix)+'-preparation'), targets)
                destination = Path(str(prefix)+'-export')
                child('screen_function_lifts.py', destination, targets)
                reuse(destination / 'raw', batch)
                summary['counts']['exported'] += len(batch)
        check_inputs()
    except (OSError, ValueError, TypeError, KeyError, subprocess.SubprocessError) as error:
        summary['error'] = str(error)
    finally:
        write_json(out / 'package.json', summary)
        (out / 'SUMMARY.md').write_text(f"# Shared machine package\n\nStatus: {summary['status']}.\n\n"
            f"Selected bodies: {len(summary['selected_entries'])}; missing: {len(summary['missing_entries'])}; "
            f"exported: {summary['counts']['exported']}.\n\n"
            'Generated code is not execution, production integration or original-function acceptance.\n'
            'Dynamic target coverage is not exhaustive; no guest replay or status promotion.\n' +
            (f"\nFailure: {summary['error']}\n" if summary.get('error') else ''))
    return summary


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--entry', action='append', required=True)
    parser.add_argument('--raw-dir', type=Path, action='append', default=[])
    parser.add_argument('--observed-targets', type=Path, action='append', default=[])
    parser.add_argument('--profile', type=Path, default=Options.__dataclass_fields__['profile'].default_factory())
    parser.add_argument('--original', type=Path, default=Path(ELF_PATH))
    parser.add_argument('--home', type=Path, default=Options.__dataclass_fields__['home'].default_factory())
    parser.add_argument('--analysis-root', type=Path, default=ROOT / 'build-ghidra-lift')
    parser.add_argument('--max-functions', type=int, default=256)
    parser.add_argument('--max-rounds', type=int, default=4)
    parser.add_argument('--export', action='store_true')
    parser.add_argument('--prepare-project', action='store_true')
    args = parser.parse_args()
    values = vars(args); values['entries'] = tuple(values.pop('entry'))
    for name in ('raw_dirs', 'observed_targets'):
        if name == 'raw_dirs': values[name] = tuple(values.pop('raw_dir'))
        else: values[name] = tuple(values[name])
    try: result = run(Options(**values))
    except (OSError, ValueError, TypeError, KeyError) as error: parser.exit(2, f'Machine assembly: {error}\n')
    print(f"Machine assembly: {result['status']}; {args.output / 'SUMMARY.md'}")
    return 0 if result['status'] == 'GENERATED' else 2


if __name__ == '__main__':
    raise SystemExit(main())
