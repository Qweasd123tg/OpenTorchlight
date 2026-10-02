#!/usr/bin/env python3
"""Export and analyze bounded pinned functions using the durable Ghidra project."""
from __future__ import annotations
import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
from automation_state import source_snapshot, validate_output, write_json
from original import Original
from analyze_pcode import analyze
from setup_ghidra import VERSION, DIRECTORY, digest, verify_installation

ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--original', type=Path, required=True)
    parser.add_argument('--address', action='append', required=True, type=lambda x: int(x, 0))
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--home', type=Path, default=Path(os.environ.get('GHIDRA_HOME', ROOT / 'build-source-cache/ghidra' / DIRECTORY)))
    parser.add_argument('--analysis-root', type=Path, default=Path(os.environ.get('TORCHLIGHT_GHIDRA_ROOT', ROOT / 'build-ghidra')))
    parser.add_argument('--profile', type=Path, help='explicit bounded emulator input profile; no inferred defaults')
    args = parser.parse_args()
    allowed = False
    try:
        validate_output(ROOT, args.out, [args.original.resolve().parent, *([args.profile] if args.profile else [])], directory=True)
        if args.out.exists(): raise ValueError('Use a fresh output directory; existing evidence is preserved')
        if not 1 <= len(set(args.address)) <= 64: raise ValueError('Select 1..64 function entries')
        original = Original(args.original)
        symbols = [original.symbol(next(s.name for s in original.symbols if s.address == address and s.size), address)
                   for address in dict.fromkeys(args.address)]
        launcher = args.home / 'support/analyzeHeadless'
        if not launcher.is_file() or not (args.analysis_root / 'project/OpenTorchlight.gpr').is_file():
            raise ValueError('Prepare pinned tool and saved project first: setup_ghidra.py / ghidra/analyze_original.sh')
        properties = (args.home / 'Ghidra/application.properties').read_text()
        if 'application.version=' + VERSION not in properties: raise ValueError('Unsupported Ghidra tool version')
        installation = verify_installation(args.home)
        before = source_snapshot(ROOT)
        args.out.mkdir(parents=True)
        allowed = True
        targets = args.out / 'targets.txt'
        targets.write_text('\n'.join(hex(s.address) for s in symbols) + '\n')
        env = {**os.environ, 'XDG_CONFIG_HOME': str(args.analysis_root / 'config'),
               'XDG_CACHE_HOME': str(args.analysis_root / 'cache')}
        command = [str(launcher), str(args.analysis_root / 'project'), 'OpenTorchlight', '-max-cpu', '2',
                   '-process', original.path.name, '-noanalysis', '-readOnly', '-scriptPath', str(ROOT / 'tools/ghidra'),
                   '-postScript', 'ExportCodeFirstPacket.java', str(targets.resolve()), str((args.out / 'raw').resolve()), original.sha256]
        if args.profile:
            command += ['-postScript', 'ProbePcodeFunction.java', str(args.profile.resolve()),
                        str((args.out / 'emulation.json').resolve()), original.sha256]
        with (args.out / 'headless.log').open('w') as log:
            subprocess.run(command, env=env, stdout=log, stderr=subprocess.STDOUT, check=True, timeout=900)
        manifest = json.loads((args.out / 'raw/manifest.json').read_text())
        if manifest['original_elf_sha256'] != original.sha256 or manifest['ghidra_version'] != VERSION:
            raise ValueError('Exported program/tool identity mismatch')
        if ({int(item['address'],16) for item in manifest['functions']} != {s.address for s in symbols}
                or any(item['status']!='exported' for item in manifest['functions'])):
            raise ValueError('Incomplete function export')
        emulation = None
        if args.profile:
            emulation=json.loads((args.out/'emulation.json').read_text())
            profile=json.loads(args.profile.read_text())
            expected_ids=[case['id'] for case in profile['cases']]
            actual_ids=[case['id'] for case in emulation['results']]
            if (emulation.get('kind')!='bounded-original-pcode-execution'
                    or emulation.get('original_elf_sha256')!=original.sha256
                    or actual_ids!=expected_ids or len(set(actual_ids))!=len(actual_ids)
                    or any(case['status'] not in ('COMPLETE','UNKNOWN') for case in emulation['results'])):
                raise ValueError('Incomplete/unsupported emulator results')
        summaries = []
        for symbol in symbols:
            path = args.out / 'raw' / (f'{symbol.address:08x}.json')
            packet = json.loads(path.read_text())
            for instruction in packet['instructions']:
                raw = bytes.fromhex(instruction['bytes'])
                if original.read(int(instruction['address'],16),len(raw)) != raw:
                    raise ValueError('Imported program bytes differ from external original')
            evidence = analyze(packet)
            output = args.out / (f'{symbol.address:08x}-analysis.json')
            write_json(output, evidence)
            summaries.append({'address': hex(symbol.address), 'symbol': symbol.name,
                'original_size': symbol.size, 'original_body_sha256': hashlib.sha256(original.read(symbol.address,symbol.size)).hexdigest(),
                'instructions': len(packet['instructions']), 'memory_accesses': len(evidence['memory_accesses']),
                'control_flows': len(evidence['control_flow']), 'unresolved': len(evidence['unresolved']),
                'raw_packet': str(path.relative_to(args.out)), 'raw_packet_sha256': digest(path),
                'evidence': output.name, 'evidence_sha256': digest(output)})
        consistent = before['sha256'] == source_snapshot(ROOT)['sha256']
        write_json(args.out / 'summary.json', {'schema': 1, 'kind': 'ghidra-behavior-research',
            'status': 'COLLECTED' if consistent else 'STALE', 'original_elf_sha256': original.sha256,
            'ghidra_version': VERSION, 'source_consistent': consistent, 'functions': summaries,
            'tool_inputs': installation['tool_inputs'], 'tool_archive_sha256': installation['archive_sha256'],
            'tool_scripts': {p.name:digest(p) for p in (ROOT/'tools/ghidra/ExportCodeFirstPacket.java',ROOT/'tools/ghidra/ProbePcodeFunction.java',Path(__file__),ROOT/'tools/analyze_pcode.py')},
            'profile_sha256':digest(args.profile) if args.profile else None,
            'emulation': {'complete':sum(case['status']=='COMPLETE' for case in emulation['results']),
                          'unknown':sum(case['status']=='UNKNOWN' for case in emulation['results'])} if emulation else None,
            'original_status_promotions': 0, 'game_executed': False})
        print(f"Collected {len(summaries)} original functions; source_consistent={consistent}; unresolved effects remain explicit: {args.out}")
        return 0 if consistent else 2
    except (OSError, ValueError, KeyError, TypeError, StopIteration, subprocess.SubprocessError) as exc:
        if allowed: write_json(args.out / 'summary.json', {'schema':1,'kind':'ghidra-behavior-research','status':'FAILED','reason':str(exc),'original_status_promotions':0})
        parser.exit(2, f'Ghidra behavior research: {exc}\n')


if __name__ == '__main__': raise SystemExit(main())
