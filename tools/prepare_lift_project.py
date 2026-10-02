#!/usr/bin/env python3
"""Prepare only explicit ELF function spans in a separate pinned Ghidra cache.

No full analysis, decompiler, ABI inference or original-program execution.
Preparation mutates the owned analysis database; later raw exports stay read-only.
"""
from __future__ import annotations

import argparse
import bisect
import hashlib
import json
from pathlib import Path
import subprocess

from automation_state import validate_output, write_json
from function_package import ELF_PATH, normalize
from ghidra_runtime import headless_environment
from original import Original, SUPPORTED_SHA256
from setup_ghidra import DIRECTORY, VERSION, digest, verify_installation

ROOT = Path(__file__).resolve().parents[1]
MAX_BATCH = 1024
MAX_FUNCTION_BYTES = 1 << 20
MAX_BATCH_BYTES = 8 << 20
PROJECT_NAME = 'OpenTorchlight'
MARKER_NAME = 'lift-preparation.json'


def parse_function_symbols(text):
    """STT_FUNC bounds from readelf -Ws, retaining contradictory positive sizes."""
    symbols = {}
    for line in text.splitlines():
        fields = line.split(None, 7)
        if len(fields) != 8 or fields[3] != 'FUNC' or fields[6] in {'UND', 'ABS'}:
            continue
        try:
            address, size = int(fields[1], 16), int(fields[2], 10)
        except ValueError as exc:
            raise ValueError('Malformed ELF function symbol row') from exc
        if not 0 <= address < 1 << 64 or not 0 <= size < 1 << 64:
            raise ValueError('ELF function symbol outside uint64 domain')
        row = symbols.setdefault(address, {'sizes': set(), 'aliases': set()})
        if size:
            row['sizes'].add(size)
        row['aliases'].add(fields[7])
    return symbols


def read_targets(path):
    targets, seen = [], set()
    for line in Path(path).read_text(encoding='utf-8').splitlines():
        line = line.strip()
        if not line or line.startswith('#'):
            continue
        address = int(normalize(line), 16)
        if address in seen:
            raise ValueError('Duplicate normalized preparation target: ' + hex(address))
        seen.add(address)
        targets.append(address)
    if not 1 <= len(targets) <= MAX_BATCH:
        raise ValueError('Select 1..1024 exact preparation targets; no truncation')
    return sorted(targets)


def prepare_request(original, targets, functions):
    if original.sha256 != SUPPORTED_SHA256:
        raise ValueError('Preparation ELF identity differs from supported original')
    if not 1 <= len(targets) <= MAX_BATCH or len(set(targets)) != len(targets):
        raise ValueError('Select 1..1024 unique exact targets')
    # Includes zero-size text labels: a requested range must never swallow a
    # different source entry merely because it was not selected for this batch.
    code_entries = sorted({s.address for s in original.symbols if s.kind in 'TtWw'} | set(functions))
    entries, total = [], 0
    for address in sorted(targets):
        symbol = functions.get(address)
        sizes = symbol['sizes'] if symbol else set()
        if len(sizes) != 1:
            raise ValueError('Missing, unsized or ambiguous exact STT_FUNC target: ' + hex(address))
        size = next(iter(sizes))
        if size > MAX_FUNCTION_BYTES or address + size > 1 << 64:
            raise ValueError('Function span exceeds bounded preparation limit: ' + hex(address))
        if not any(kind == 1 and flags & 1 and start <= address and address + size <= start + file_size
                   for kind, flags, _, start, _, file_size, _, _ in original.segments):
            raise ValueError('Function is not wholly file-backed executable ELF memory: ' + hex(address))
        next_entry = bisect.bisect_right(code_entries, address)
        if next_entry < len(code_entries) and code_entries[next_entry] < address + size:
            raise ValueError('Function span contains another exact source entry: ' +
                             hex(address) + ' -> ' + hex(code_entries[next_entry]))
        raw = original.read(address, size)
        total += size
        if total > MAX_BATCH_BYTES:
            raise ValueError('Selected symbol bytes exceed bounded batch limit')
        entries.append({'address': f'0x{address:08x}', 'size': size,
                        'full_symbol_sha256': hashlib.sha256(raw).hexdigest(),
                        'aliases': sorted(symbol['aliases'])})
    image_base = min(start for kind, _, _, start, _, _, _, _ in original.segments if kind == 1)
    return {'schema': 1, 'kind': 'bounded-lift-preparation-request',
            'original_elf_sha256': original.sha256, 'ghidra_version': VERSION,
            'language': 'x86:LE:64:default', 'image_base': hex(image_base),
            'scope': 'explicit_exact_elf_functions', 'entries': entries,
            'limits': {'maximum_entries': MAX_BATCH, 'maximum_function_bytes': MAX_FUNCTION_BYTES,
                       'maximum_batch_bytes': MAX_BATCH_BYTES}, 'selected_symbol_bytes': total,
            'analysis_requested': False, 'decompiler_requested': False,
            'original_status_promotions': 0, 'game_executed': False}


def project_mode(analysis_root):
    """An existing unrelated/full database is never implicitly repaired."""
    project = analysis_root / 'project'
    marker = analysis_root / MARKER_NAME
    gpr = project / (PROJECT_NAME + '.gpr')
    rep = project / (PROJECT_NAME + '.rep')
    if gpr.exists():
        record = json.loads(marker.read_text()) if marker.is_file() else {}
        if (record.get('kind') != 'bounded-lift-project' or record.get('schema') != 1 or
                record.get('original_elf_sha256') != SUPPORTED_SHA256 or
                record.get('ghidra_version') != VERSION or
                record.get('analysis_requested') is not False or
                record.get('decompiler_requested') is not False or
                record.get('project_path') != str(gpr.resolve()) or not rep.is_dir()):
            raise ValueError('Existing project is not a verified owned bounded cache; use a separate analysis root')
        return 'extend', record
    if rep.exists() or marker.exists() or (project.exists() and any(project.iterdir())):
        raise ValueError('Partial/unowned project artifacts exist; preserve them and use a fresh analysis root')
    return 'import', None


def preparation_command(home, analysis_root, original, request_path, result_path, mode):
    command = [str(home / 'support/analyzeHeadless'), str(analysis_root / 'project'), PROJECT_NAME,
               '-max-cpu', '2', '-noanalysis']
    if mode == 'import':
        command += ['-import', str(original), '-processor', 'x86:LE:64:default', '-cspec', 'gcc',
                    '-loader-applyRelocations', 'false', '-loader-applyUndefinedData', 'false',
                    '-loader-loadLibraries', 'false', '-loader-linkExistingProjectLibraries', 'false']
    elif mode == 'extend':
        command += ['-process', original.name]
    else:
        raise ValueError('Unsupported preparation project mode')
    command += ['-scriptPath', str(ROOT / 'tools/ghidra'), '-postScript', 'PrepareLiftEntries.java',
                str(request_path), str(result_path)]
    return command


def verify_result(result, request, request_sha):
    if (result.get('schema') != 1 or result.get('kind') != 'bounded-lift-preparation-result' or
            result.get('status') != 'PREPARED' or result.get('request_sha256') != request_sha or
            result.get('original_elf_sha256') != request['original_elf_sha256'] or
            result.get('ghidra_version') != VERSION or result.get('language') != request['language'] or
            result.get('analysis_requested') is not False or result.get('decompiler_requested') is not False or
            result.get('program_bytes_modified') is not False or result.get('game_executed') is not False):
        raise ValueError('Incomplete/unsupported preparation result; launcher exit alone is not evidence')
    expected = {row['address']: row for row in request['entries']}
    actual = result.get('entries')
    if not isinstance(actual, list) or len(actual) != len(expected):
        raise ValueError('Preparation result does not contain the complete target set')
    seen = set()
    for row in actual:
        entry = row.get('address')
        source = expected.get(entry)
        if entry in seen or source is None or any(row.get(k) != source[k] for k in ('size', 'full_symbol_sha256')):
            raise ValueError('Preparation target identity/bounds/bytes differ')
        seen.add(entry)
        if row.get('instructions', 0) < 1 or not 0 < row.get('instruction_bytes', 0) <= source['size']:
            raise ValueError('Preparation target lacks bounded decoded instructions')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--targets-file', type=Path, required=True)
    parser.add_argument('--original', type=Path, default=Path(ELF_PATH))
    parser.add_argument('--analysis-root', type=Path, default=ROOT / 'build-ghidra-lift')
    parser.add_argument('--home', type=Path, default=ROOT / 'build-source-cache/ghidra' / DIRECTORY)
    parser.add_argument('--output', '--out', type=Path, required=True, help='fresh ignored build or /tmp report directory')
    args = parser.parse_args()
    published = False
    try:
        original = Original(args.original)
        analysis_root, home, output = args.analysis_root.resolve(), args.home.resolve(), args.output.resolve()
        protected = [original.path.parent, args.targets_file, home]
        validate_output(ROOT, analysis_root, [*protected, output], directory=True)
        validate_output(ROOT, output, [*protected, analysis_root], directory=True)
        if output.exists():
            raise ValueError('Use a fresh output directory; existing evidence is preserved')
        installation = verify_installation(home)
        mode, previous = project_mode(analysis_root)
        targets = read_targets(args.targets_file)
        symbols = parse_function_symbols(subprocess.check_output(
            ['readelf', '--wide', '--symbols', str(original.path)], text=True))
        request = prepare_request(original, targets, symbols)
        env, runtime = headless_environment(analysis_root)
        inputs = [original.path, args.targets_file.resolve(), Path(__file__).resolve(),
                  ROOT / 'tools/ghidra/PrepareLiftEntries.java', ROOT / 'tools/original.py',
                  ROOT / 'tools/setup_ghidra.py', ROOT / 'tools/automation_state.py',
                  ROOT / 'tools/function_package.py', ROOT / 'tools/ghidra_runtime.py',
                  home.parent / 'installation.json', Path(runtime['java_executable']),
                  Path(runtime['java_home']) / 'bin/javac']
        before = {str(p): digest(p) for p in inputs}
        output.mkdir(parents=True)
        published = True
        request_path, result_path = output / 'request.json', output / 'preparation.json'
        write_json(request_path, request)
        request_sha = digest(request_path)
        (analysis_root / 'project').mkdir(parents=True, exist_ok=True)
        command = preparation_command(home, analysis_root, original.path, request_path, result_path, mode)
        with (output / 'headless.log').open('w') as log:
            subprocess.run(command, env=env, stdout=log, stderr=subprocess.STDOUT, check=True, timeout=900)
        result = json.loads(result_path.read_text())
        verify_result(result, request, request_sha)
        if not (analysis_root / 'project' / (PROJECT_NAME + '.gpr')).is_file():
            raise ValueError('Prepared database was not saved')
        after = {p: digest(Path(p)) for p in before}
        if before != after or digest(request_path) != request_sha:
            raise ValueError('Preparation source inputs changed; no current cache acceptance')
        accepted = {r['address']: r for r in (previous or {}).get('entries', [])}
        accepted.update({r['address']: r for r in request['entries']})
        record = {'schema': 1, 'kind': 'bounded-lift-project', 'original_elf_sha256': original.sha256,
                  'ghidra_version': VERSION, 'project_path': str(analysis_root / 'project' / (PROJECT_NAME + '.gpr')),
                  'analysis_requested': False, 'decompiler_requested': False,
                  'entries': [accepted[a] for a in sorted(accepted, key=lambda a: int(a, 16))],
                  'last_preparation': str(output / 'report.json')}
        report = {'schema': 1, 'kind': 'bounded-lift-project-preparation', 'status': 'PREPARED',
                  'mode': mode, 'source_consistent': True, 'request': request,
                  'requested_targets': [row['address'] for row in request['entries']],
                  'request_sha256': request_sha, 'result_sha256': digest(result_path),
                  'command': command, 'inputs_before': before, 'inputs_after': after,
                  'runtime': runtime,
                  'tool_inputs': installation['tool_inputs'], 'tool_archive_sha256': installation['archive_sha256'],
                  'analysis_requested': False, 'decompiler_requested': False,
                  'project_database_modified': True, 'original_modified': False,
                  'original_status_promotions': 0, 'game_executed': False}
        write_json(output / 'report.json', report)
        write_json(analysis_root / MARKER_NAME, record)
        print(f'Prepared {len(targets)} exact functions ({request["selected_symbol_bytes"]} symbol bytes); '
              f'full analysis disabled: {output / "report.json"}')
        return 0
    except (OSError, ValueError, KeyError, TypeError, subprocess.SubprocessError) as exc:
        if published:
            write_json(args.output / 'report.json', {'schema': 1, 'kind': 'bounded-lift-project-preparation',
                'status': 'FAILED', 'reason': str(exc), 'original_status_promotions': 0,
                'game_executed': False, 'original_modified': False})
        parser.exit(2, f'Bounded Ghidra preparation: {exc}\n')


if __name__ == '__main__':
    raise SystemExit(main())
