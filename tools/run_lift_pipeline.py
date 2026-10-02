#!/usr/bin/env python3
"""Bounded sequential raw-lift collection through existing read-only tools.

This driver collects exact dependency bodies through read-only exports.
Optional preparation changes only an owned bounded database from verified
symbols. It never supplies ABI/owners, runs the game or writes acceptance.
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
from setup_ghidra import DIRECTORY

ROOT = Path(__file__).resolve().parents[1]
MAX_ROUNDS = 16
MAX_FUNCTIONS = 4096
MAX_BATCH = 1024


@dataclass(frozen=True)
class PipelineOptions:
    output: Path
    limit: int
    max_rounds: int
    max_functions: int
    scope: str = 'ui'
    offset: int = 0
    addresses: tuple[str, ...] = ()
    raw_dirs: tuple[Path, ...] = ()
    export_roots: bool = False
    prepare_project: bool = False
    original: Path = field(default_factory=lambda: Path(ELF_PATH))
    home: Path = field(default_factory=lambda: ROOT / 'build-source-cache/ghidra' / DIRECTORY)
    analysis_root: Path | None = None


def _digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def _address(value):
    if not isinstance(value, str):
        raise ValueError('exact source address must be a hexadecimal string')
    return '0x' + normalize(value)


def _run_child(command, log):
    with log.open('w', encoding='utf-8') as stream:
        return subprocess.run(command, stdout=stream, stderr=subprocess.STDOUT,
                              check=False, timeout=960).returncode


def _analysis_root(options, root):
    return (options.analysis_root or root / ('build-ghidra-lift' if options.prepare_project else 'build-ghidra')).resolve()


def _select_root_targets(options, root):
    # Scheduling only: no Ghidra invocation, instruction/ABI inference or
    # registry writes. Source snapshots pin the later export to this selection.
    from screen_function_lifts import select
    selection, _ = select(root, options.scope, options.limit, options.offset, options.addresses)
    return [row['address'] for row in selection['selected']]


def _validate_options(options, root):
    for name, maximum in (('limit', MAX_BATCH), ('max_rounds', MAX_ROUNDS),
                          ('max_functions', MAX_FUNCTIONS)):
        value = getattr(options, name)
        if not isinstance(value, int) or isinstance(value, bool) or not 1 <= value <= maximum:
            raise ValueError(f'{name} must be 1..{maximum}')
    if options.scope not in {'ui', 'all'}:
        raise ValueError('scope must be ui/all')
    if not isinstance(options.offset, int) or isinstance(options.offset, bool) or options.offset < 0:
        raise ValueError('offset must be a nonnegative integer')
    if options.export_roots == bool(options.raw_dirs):
        raise ValueError('choose exactly one initial mode: export_roots or raw_dirs')
    if options.export_roots and options.limit > options.max_functions:
        raise ValueError('root export limit exceeds total function budget')
    if not isinstance(options.prepare_project, bool):
        raise ValueError('prepare_project must be an explicit boolean')
    for address in options.addresses:
        _address(address)
    protected = [options.original.resolve().parent, options.home, _analysis_root(options, root), *options.raw_dirs]
    validate_output(root, options.output, protected, directory=True)
    if options.output.exists() or options.output.is_symlink():
        raise ValueError('Use a fresh output directory; existing evidence is preserved')


def _read_screen(output):
    report_path, plan_path = output / 'report.json', output / 'dependency-plan.json'
    report, plan = json.loads(report_path.read_text()), json.loads(plan_path.read_text())
    for value, kind in ((report, 'raw-function-lift-screening'), (plan, 'raw-lift-dependency-plan')):
        if (value.get('schema') != 1 or value.get('kind') != kind or
                value.get('status') != 'SCREENED' or value.get('source_consistent') is not True or
                value.get('original_status_promotions') != 0):
            raise ValueError('child screen is failed, stale or unsupported')
    if plan.get('report_sha256') != _digest(report_path):
        raise ValueError('dependency plan does not pin the current screen report')
    if report.get('game_executed') is not False or report.get('original_modified') is not False:
        raise ValueError('child screen lacks read-only/no-game guarantees')
    return report, plan


def _read_preparation(output, targets):
    report = json.loads((output / 'report.json').read_text())
    if (report.get('schema') != 1 or report.get('kind') != 'bounded-lift-project-preparation' or
            report.get('status') != 'PREPARED' or report.get('source_consistent') is not True or
            report.get('original_status_promotions') != 0 or report.get('original_modified') is not False or
            report.get('game_executed') is not False or report.get('analysis_requested') is not False or
            report.get('decompiler_requested') is not False or report.get('project_database_modified') is not True):
        raise ValueError('bounded project preparation is failed, stale or unsupported')
    requested = [_address(a) for a in report.get('requested_targets', [])]
    if len(set(requested)) != len(requested) or set(requested) != set(targets):
        raise ValueError('project preparation differs from requested exact targets')
    return report


def _frontier(report, plan, attempted):
    """Only roots without explicit barriers may cause further exports."""
    roots = {_address(row['address']) for row in plan['roots']}
    blocked_roots = {_address(row['address']) for row in plan['roots'] if row['blocked_count'] > 0}
    retry_roots = {_address(root) for target in plan['targets'] if target['retry']
                   for root in target['roots']}
    healthy = roots - blocked_roots - retry_roots
    verified = {_address(row['address']) for row in report['functions'] if row['raw_status'] == 'verified'}
    candidates = {}
    for target in plan['targets']:
        entry = _address(target['address'])
        if not target['retry'] and entry not in attempted and entry not in verified:
            if healthy & {_address(root) for root in target['roots']}:
                if entry in candidates:
                    raise ValueError('duplicate target in child dependency plan')
                candidates[entry] = target
    return ([candidates[a] for a in sorted(candidates, key=lambda a: int(a, 16))],
            sorted(blocked_roots, key=lambda a: int(a, 16)),
            sorted(retry_roots, key=lambda a: int(a, 16)))


def pipeline_markdown(summary):
    counts = summary['counts']
    lines = ['# Bounded raw lift pipeline', '',
             f"Status: {summary['status']}; stop: {summary['stop_reason']}.", '',
             f"Scheduled original bodies: {counts['export_functions']}/{summary['budget']['max_functions']}; "
             f"dependency rounds: {counts['dependency_rounds']}/{summary['budget']['max_rounds']}; "
             f"sequential child commands: {counts['child_commands']}.", '',
             f"Roots with unresolved blockers: {len(summary['blocked_roots'])}; "
             f"roots requiring failed-export review: {len(summary['retry_roots'])}; "
             f"remaining healthy export targets: {counts['remaining_targets']}.", '',
             'Raw dependency collection only. ABI, state owners and original-function acceptance require review.',
             'Original status promotions: 0; game executed: false.']
    if summary['prepare_project']:
        lines += ['', 'Explicit project preparation is enabled; only the owned bounded database may be modified.']
    if summary.get('project_preparation_unconfirmed'):
        lines += ['', 'Preparation did not publish a verified result; the owned database may contain partial changes.']
    if summary.get('final_screen'):
        lines += ['', f"Latest root screen: `{summary['final_screen']}/SUMMARY.md`."]
    if summary.get('error'):
        lines += ['', f"Failure: {summary['error']}"]
    if summary.get('root_export_count_confirmed') is False:
        lines += ['', 'The root export count was not confirmed; the total reserves its requested cap.']
    return '\n'.join(lines) + '\n'


def run_pipeline(options, runner=None, *, root=ROOT, snapshotter=None, root_selector=None):
    """Run bounded child screens sequentially; return and publish an audit.

    ``runner(command, log_path) -> exit_code`` and ``snapshotter(root)`` are
    injectable for contract tests. Production always uses subprocess argv and
    the full tracked/nonignored source snapshot. max_rounds bounds dependency
    expansion rounds after the initial root screen. Failed exports require a
    separate reviewed retry; this driver grants no retry permission.
    """
    root = Path(root).resolve()
    _validate_options(options, root)
    runner = runner or _run_child
    snapshotter = snapshotter or source_snapshot
    root_selector = root_selector or _select_root_targets
    baseline = snapshotter(root)
    options.output.mkdir(parents=True)
    output = options.output.resolve()
    summary = {'schema': 1, 'kind': 'bounded-raw-lift-pipeline', 'status': 'STOPPED',
               'stop_reason': 'not_started', 'meaning': 'Raw dependency collection only; no acceptance inference.',
               'budget': {'max_rounds': options.max_rounds, 'max_functions': options.max_functions,
                          'batch_maximum': MAX_BATCH},
               'source_sha256': baseline['sha256'], 'source_consistent': True,
               'driver_sha256': _digest(Path(__file__)),
               'prepare_project': options.prepare_project,
               'project_database_modified': False,
               'project_preparation_unconfirmed': False,
               'analysis_root': str(_analysis_root(options, root)),
               'counts': {'export_functions': 0, 'dependency_rounds': 0, 'child_commands': 0,
                          'remaining_targets': 0},
               'commands': [], 'raw_dirs': [], 'attempted_targets': [],
               'blocked_roots': [], 'retry_roots': [], 'final_screen': None,
               'original_status_promotions': 0, 'game_executed': False, 'original_modified': False}
    raw_dirs = list(dict.fromkeys(str(p.resolve()) for p in options.raw_dirs))
    attempted, report, plan = set(), None, None
    prepared_roots = None

    def base_command(child_output, root_selection=True):
        command = [sys.executable, str(root / 'tools/screen_function_lifts.py'),
                   '--limit', str(options.limit if root_selection else MAX_BATCH),
                   '--output', str(child_output), '--original', str(options.original.resolve()),
                   '--home', str(options.home.resolve()), '--analysis-root', str(_analysis_root(options, root))]
        if root_selection:
            command += ['--scope', options.scope, '--offset', str(options.offset)]
            for address in options.addresses:
                command += ['--address', _address(address)]
        return command

    def child(command, child_output, role, targets=()):
        if snapshotter(root)['sha256'] != baseline['sha256']:
            summary.update(status='STALE', stop_reason='source_changed', source_consistent=False)
            return None
        child_output.parent.mkdir(parents=True, exist_ok=True)
        log = output / f"child-{len(summary['commands']):03d}.log"
        item = {'role': role, 'command': command, 'output': str(child_output),
                'log': str(log), 'targets': list(targets)}
        summary['commands'].append(item)
        summary['counts']['child_commands'] += 1
        if role == 'root_export':
            # Reserve the requested root cap until its exact selection is
            # confirmed. Failed children may not publish a selection at all.
            summary['counts']['export_functions'] = options.limit
            summary['root_export_count_confirmed'] = False
        elif role == 'dependency_export':
            attempted.update(targets)
            summary['counts']['export_functions'] += len(targets)
        elif role == 'project_prepare':
            summary['project_preparation_unconfirmed'] = True
        try:
            code = runner(command, log)
        except (OSError, subprocess.SubprocessError) as exc:
            item.update(exit_code=None, error=str(exc))
            summary.update(status='FAILED', stop_reason='child_failed', error=str(exc))
            return None
        item['exit_code'] = code
        preparation = None
        if role == 'project_prepare' and code == 0:
            preparation = _read_preparation(child_output, targets)
            summary['project_database_modified'] |= preparation['project_database_modified']
            summary['project_preparation_unconfirmed'] = False
        if snapshotter(root)['sha256'] != baseline['sha256']:
            summary.update(status='STALE', stop_reason='source_changed', source_consistent=False)
            return None
        if code:
            summary.update(status='FAILED', stop_reason='child_failed', error=f'{role} exited {code}; see {log.name}')
            return None
        if role == 'project_prepare':
            return preparation
        return _read_screen(child_output)

    def prepare(targets_file, child_output, entries):
        command = [sys.executable, str(root / 'tools/prepare_lift_project.py'),
                   '--targets-file', str(targets_file), '--output', str(child_output),
                   '--original', str(options.original.resolve()), '--home', str(options.home.resolve()),
                   '--analysis-root', str(_analysis_root(options, root))]
        return child(command, child_output, 'project_prepare', entries)

    def update_remaining():
        if report is None:
            return []
        frontier, blocked, retries = _frontier(report, plan, attempted)
        summary['blocked_roots'], summary['retry_roots'] = blocked, retries
        summary['counts']['remaining_targets'] = len(frontier)
        return frontier

    try:
        initial = output / 'roots'
        if options.export_roots and options.prepare_project:
            entries = [_address(a) for a in root_selector(options, root)]
            if len(set(entries)) != len(entries) or len(entries) > options.limit:
                raise ValueError('root preparation selection exceeds exact scheduling limits')
            entries.sort(key=lambda a: int(a, 16))
            if not entries:
                summary['stop_reason'] = 'no_roots_selected'
                return summary
            targets_file = output / 'root-targets.txt'
            targets_file.write_text(''.join(a + '\n' for a in entries), encoding='utf-8')
            if prepare(targets_file, output / 'root-preparation', entries) is None:
                return summary
            prepared_roots = set(entries)
        command = base_command(initial)
        if options.export_roots:
            command += ['--export']
        else:
            for raw_dir in raw_dirs:
                command += ['--raw-dir', raw_dir]
        result = child(command, initial, 'root_export' if options.export_roots else 'root_reuse')
        if result is not None:
            report, plan = result
            summary['final_screen'] = str(initial)
            if options.export_roots:
                selected = [_address(row['address']) for row in report['selection']['selected']]
                if len(selected) > options.limit:
                    raise ValueError('root child exceeded the selected export limit')
                if prepared_roots is not None and set(selected) != prepared_roots:
                    raise ValueError('root export selection differs from explicitly prepared targets')
                attempted.update(selected)
                summary['counts']['export_functions'] = len(selected)
                summary['root_export_count_confirmed'] = True
                raw_dirs.append(str(initial / 'raw'))
            while True:
                frontier = update_remaining()
                if not plan['roots']:
                    summary['stop_reason'] = 'no_roots_selected'
                    break
                if not frontier:
                    summary['stop_reason'] = ('retry_review_required' if summary['retry_roots'] else
                                              'unresolved_blockers' if summary['blocked_roots'] else
                                              'no_new_targets' if plan['targets'] else 'closure_collected')
                    if summary['stop_reason'] == 'closure_collected':
                        summary['status'] = 'COLLECTED'
                    break
                if summary['counts']['dependency_rounds'] >= options.max_rounds:
                    summary['stop_reason'] = 'round_budget'
                    break
                remaining = options.max_functions - summary['counts']['export_functions']
                if remaining <= 0:
                    summary['stop_reason'] = 'function_budget'
                    break
                round_index = summary['counts']['dependency_rounds'] + 1
                round_output = output / f'round-{round_index:02d}'
                scheduled = frontier[:remaining]
                failed = False
                for start in range(0, len(scheduled), MAX_BATCH):
                    entries = [t['address'] for t in scheduled[start:start + MAX_BATCH]]
                    batch_index = start // MAX_BATCH
                    targets_file = round_output / f'targets-{batch_index:03d}.txt'
                    round_output.mkdir(parents=True, exist_ok=True)
                    targets_file.write_text(''.join(a + '\n' for a in entries), encoding='utf-8')
                    if options.prepare_project:
                        if prepare(targets_file, round_output / f'prepare-{batch_index:03d}', entries) is None:
                            failed = True
                            break
                    child_output = round_output / f'export-{batch_index:03d}'
                    command = base_command(child_output, root_selection=False)
                    command += ['--targets-file', str(targets_file), '--export']
                    result = child(command, child_output, 'dependency_export', entries)
                    if result is None:
                        failed = True
                        break
                    exported = {_address(row['address']) for row in result[0]['selection']['selected']}
                    if exported != set(entries):
                        raise ValueError('dependency child selection differs from scheduled exact targets')
                    raw_dirs.append(str(child_output / 'raw'))
                if failed:
                    break
                joined = round_output / 'joined'
                command = base_command(joined)
                for raw_dir in raw_dirs:
                    command += ['--raw-dir', raw_dir]
                result = child(command, joined, 'root_rejoin')
                if result is None:
                    break
                report, plan = result
                summary['counts']['dependency_rounds'] = round_index
                summary['final_screen'] = str(joined)
    except (OSError, ValueError, KeyError, TypeError, json.JSONDecodeError) as exc:
        summary.update(status='FAILED', stop_reason='invalid_evidence', error=str(exc))
    finally:
        summary['raw_dirs'] = raw_dirs
        summary['attempted_targets'] = sorted(attempted, key=lambda a: int(a, 16))
        if report is not None:
            try:
                update_remaining()
            except (ValueError, KeyError, TypeError) as exc:
                summary.update(status='FAILED', stop_reason='invalid_evidence', error=str(exc))
        write_json(output / 'pipeline.json', summary)
        (output / 'SUMMARY.md').write_text(pipeline_markdown(summary), encoding='utf-8')
    return summary


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, required=True, help='fresh /tmp or ignored build directory')
    parser.add_argument('--scope', choices=['ui', 'all'], default='ui')
    parser.add_argument('--limit', type=int, required=True, help='root scheduling cap, 1..1024')
    parser.add_argument('--offset', type=int, default=0)
    parser.add_argument('--address', action='append', default=[])
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument('--export', action='store_true', help='export the initial residual roots')
    mode.add_argument('--raw-dir', type=Path, action='append', help='reuse verified raw batches; repeat to join')
    parser.add_argument('--prepare-project', action='store_true',
                        help='prepare explicit spans in an owned bounded cache before each read-only export')
    parser.add_argument('--max-rounds', type=int, required=True, help='dependency rounds after root screen, 1..16')
    parser.add_argument('--max-functions', type=int, required=True, help='total newly scheduled export bodies, 1..4096')
    parser.add_argument('--original', type=Path, default=Path(ELF_PATH))
    parser.add_argument('--home', type=Path, default=ROOT / 'build-source-cache/ghidra' / DIRECTORY)
    parser.add_argument('--analysis-root', type=Path,
                        help='defaults to build-ghidra-lift with --prepare-project, otherwise build-ghidra')
    args = parser.parse_args()
    options = PipelineOptions(output=args.output, scope=args.scope, limit=args.limit, offset=args.offset,
                              addresses=tuple(args.address), raw_dirs=tuple(args.raw_dir or []),
                              export_roots=args.export, max_rounds=args.max_rounds,
                              prepare_project=args.prepare_project,
                              max_functions=args.max_functions, original=args.original,
                              home=args.home, analysis_root=args.analysis_root)
    try:
        result = run_pipeline(options)
    except (OSError, ValueError, KeyError, TypeError) as exc:
        parser.exit(2, f'Raw lift pipeline: {exc}\n')
    print(f"Raw lift pipeline stopped: {result['stop_reason']}; {args.output / 'SUMMARY.md'}")
    return 2 if result['status'] in {'FAILED', 'STALE'} else 0


if __name__ == '__main__':
    raise SystemExit(main())
