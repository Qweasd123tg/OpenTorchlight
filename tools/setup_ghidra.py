#!/usr/bin/env python3
"""Install the pinned research tool into ignored cache; never modify game inputs."""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path, PurePosixPath
import stat
import subprocess
import tempfile
import zipfile
from automation_state import validate_output, write_json

ROOT = Path(__file__).resolve().parents[1]
VERSION = "12.1.3"
DIRECTORY = "ghidra_12.1.3_PUBLIC"
ARCHIVE = DIRECTORY + "_20260817.zip"
SHA256 = "93a5d11a9ad510622acaaf908c556a7b9b764d338e78a7567f3689bf5081fd54"
URL = "https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_12.1.3_build/" + ARCHIVE


def digest(path: Path) -> str:
    value = hashlib.sha256()
    with path.open('rb') as stream:
        for data in iter(lambda: stream.read(1 << 20), b''): value.update(data)
    return value.hexdigest()


def checked_members(archive: zipfile.ZipFile) -> list:
    members = archive.infolist()
    if not members: raise ValueError('Empty Ghidra archive')
    for entry in members:
        path = PurePosixPath(entry.filename)
        if (path.is_absolute() or '..' in path.parts or not path.parts
                or path.parts[0] != DIRECTORY or '\\' in entry.filename
                or stat.S_ISLNK(entry.external_attr >> 16)):
            raise ValueError('Unsafe/unexpected tool archive member: ' + entry.filename)
    return members


def verify_installation(home: Path) -> dict:
    record = json.loads((home.parent / 'installation.json').read_text())
    required = {'support/analyzeHeadless', 'Ghidra/application.properties',
                'Ghidra/Framework/SoftwareModeling/lib/SoftwareModeling.jar',
                'Ghidra/Framework/Emulation/lib/Emulation.jar',
                'Ghidra/Processors/x86/data/languages/x86-64.sla'}
    if (record.get('kind') != 'pinned-ghidra-installation' or record.get('version') != VERSION
            or record.get('archive_sha256') != SHA256
            or not required.issubset(record.get('tool_inputs', {}))):
        raise ValueError('Missing/unsupported pinned Ghidra installation provenance')
    for path, expected in record['tool_inputs'].items():
        relative = PurePosixPath(path)
        if relative.is_absolute() or '..' in relative.parts or digest(home / path) != expected:
            raise ValueError('Pinned tool input changed: ' + path)
    return record


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cache', type=Path, default=ROOT / 'build-source-cache/ghidra')
    parser.add_argument('--download', action='store_true', help='download exact official archive if absent')
    args = parser.parse_args()
    try:
        cache = args.cache.resolve()
        validate_output(ROOT, cache, directory=True)
        cache.mkdir(parents=True, exist_ok=True)
        archive = cache / ARCHIVE
        if not archive.is_file():
            if not args.download: raise ValueError('Pinned archive absent; use --download: ' + str(archive))
            partial = archive.with_suffix('.zip.part')
            subprocess.run(['curl', '-sS', '-L', '--fail', '--retry', '2', URL, '-o', str(partial)], check=True)
            if digest(partial) != SHA256: raise ValueError('Downloaded Ghidra SHA-256 differs from pinned release')
            partial.replace(archive)
        if digest(archive) != SHA256: raise ValueError('Unsupported/corrupt Ghidra archive SHA-256')
        home = cache / DIRECTORY
        marker = cache / 'installation.json'
        if home.exists():
            verify_installation(home)
        else:
            with tempfile.TemporaryDirectory(prefix='.ghidra-install-', dir=cache) as staging:
                with zipfile.ZipFile(archive) as source:
                    for entry in checked_members(source):
                        source.extract(entry, staging)
                        path = Path(staging) / entry.filename
                        if not entry.is_dir() and entry.external_attr >> 16 & 0o111:
                            path.chmod(path.stat().st_mode | (entry.external_attr >> 16 & 0o111))
                tool = Path(staging) / DIRECTORY
                properties = (tool / 'Ghidra/application.properties').read_text()
                if 'application.version=' + VERSION not in properties:
                    raise ValueError('Extracted tool version differs from pinned release')
                files = ['support/analyzeHeadless', 'Ghidra/application.properties',
                         *[str(p.relative_to(tool)) for p in tool.glob('Ghidra/Framework/SoftwareModeling/lib/*.jar')],
                         *[str(p.relative_to(tool)) for p in tool.glob('Ghidra/Framework/Emulation/lib/*.jar')],
                         *[str(p.relative_to(tool)) for p in tool.glob('Ghidra/Processors/x86/data/languages/*.sla')]]
                record = {'schema': 1, 'kind': 'pinned-ghidra-installation', 'version': VERSION,
                          'archive_sha256': SHA256, 'source_url': URL,
                          'tool_inputs': {path: digest(tool / path) for path in sorted(files)}}
                tool.replace(home)
                write_json(marker, record)
        print('Pinned Ghidra ready: ' + str(home))
        return 0
    except (OSError, ValueError, KeyError, subprocess.SubprocessError) as exc:
        parser.exit(2, f'Ghidra setup: {exc}\n')


if __name__ == '__main__': raise SystemExit(main())
