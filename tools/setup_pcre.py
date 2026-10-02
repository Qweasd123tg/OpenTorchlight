#!/usr/bin/env python3
"""Build the existing PCRE1 8.45 host boundary in the ignored project cache.

Archive checksum provenance: SourceForge's published artifact digest, reached
from pcre.org's PCRE1 download link. This is not an authenticated author signature
and does not establish equivalence with the original game's shipped PCRE 7.8.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path, PurePosixPath
import shutil
import subprocess
import tarfile
import tempfile

from automation_state import validate_output, write_json

ROOT = Path(__file__).resolve().parents[1]
VERSION = '8.45'
DIRECTORY = 'pcre-' + VERSION
ARCHIVE = DIRECTORY + '.tar.gz'
SHA256 = '4e6ce03e0336e8b4a3d6c2b70b1c5e18590a5673a98186da90d4f33c23defc09'
URL = 'https://sourceforge.net/projects/pcre/files/pcre/8.45/pcre-8.45.tar.gz/download'
CHECKSUM_SOURCE = URL
CFLAGS = '-O2 -fPIC'


def digest(path):
    value = hashlib.sha256()
    with Path(path).open('rb') as stream:
        for chunk in iter(lambda: stream.read(1 << 20), b''):
            value.update(chunk)
    return value.hexdigest()


def source_inputs(source):
    result = {}
    for path in sorted(source.rglob('*')):
        if path.is_symlink():
            raise ValueError('Source symlinks are not accepted: ' + str(path))
        if path.is_file():
            result[path.relative_to(source).as_posix()] = digest(path)
    if not result:
        raise ValueError('Empty PCRE source tree')
    return result


def checked_members(archive):
    members = archive.getmembers()
    if not members:
        raise ValueError('Empty PCRE archive')
    seen = set()
    for member in members:
        path = PurePosixPath(member.name)
        if (path.is_absolute() or '..' in path.parts or not path.parts
                or path.parts[0] != DIRECTORY or '\\' in member.name
                or not (member.isfile() or member.isdir()) or member.name in seen):
            raise ValueError('Unsafe/unexpected PCRE archive member: ' + member.name)
        seen.add(member.name)
    return members


def run(command, cwd, log, env=None):
    with log.open('w') as stream:
        subprocess.run(command, cwd=cwd, env=env, stdout=stream,
                       stderr=subprocess.STDOUT, check=True, timeout=900)


def installed_inputs(prefix):
    paths = [prefix / 'include/pcre.h', prefix / 'lib/pkgconfig/libpcre.pc',
             prefix / 'bin/pcre-config']
    libraries = [path for path in (prefix / 'lib').glob('libpcre.so.*')
                 if path.is_file() and not path.is_symlink()]
    if len(libraries) != 1:
        raise ValueError('Expected one real installed PCRE1 shared library')
    paths += libraries
    result = {}
    for path in paths:
        if not path.is_file() or path.is_symlink():
            raise ValueError('Missing/unsafe PCRE SDK input: ' + str(path))
        result[path.relative_to(prefix).as_posix()] = digest(path)
    for name in ('libpcre.so', 'libpcre.so.1'):
        path = prefix / 'lib' / name
        if not path.is_symlink() or path.resolve() != libraries[0].resolve():
            raise ValueError('Unexpected PCRE SDK library link: ' + str(path))
        result['lib/' + name] = {'symlink': os.readlink(path)}
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--download', action='store_true')
    parser.add_argument('--jobs', type=int, default=2)
    args = parser.parse_args()
    try:
        if not 1 <= args.jobs <= 16:
            raise ValueError('--jobs must be 1..16')
        cache = ROOT / 'build-source-cache'
        source, build, prefix = cache / DIRECTORY, cache / 'pcre-build', cache / 'pcre-sdk'
        for path in (cache, source, build, prefix):
            validate_output(ROOT, path, directory=True)
            if path.is_symlink():
                raise ValueError('Cache paths cannot be symlinks: ' + str(path))
        cache.mkdir(parents=True, exist_ok=True)
        # Upstream libtool splits paths containing spaces. Use a checked logical
        # alias while every actual file remains in the ignored project cache.
        alias = Path('/tmp') / ('opentorchlight-pcre-' + hashlib.sha256(
            str(cache.resolve()).encode()).hexdigest()[:12])
        if alias.is_symlink():
            if alias.resolve() != cache.resolve():
                raise ValueError('Existing PCRE build alias points elsewhere')
        elif alias.exists():
            raise ValueError('PCRE build alias is not a symlink')
        else:
            alias.symlink_to(cache.resolve(), target_is_directory=True)
        logical_build, logical_source, logical_prefix = alias / build.name, alias / source.name, alias / prefix.name
        archive = cache / ARCHIVE
        if archive.is_symlink():
            raise ValueError('Archive cannot be a symlink')
        if not archive.is_file():
            if not args.download:
                raise ValueError('Pinned archive absent; use --download')
            with tempfile.NamedTemporaryFile(prefix='.pcre-download-', dir=cache, delete=False) as stream:
                partial = Path(stream.name)
            subprocess.run(['curl', '--fail', '--location', '--silent', '--show-error',
                            '--connect-timeout', '10', '--max-time', '120', URL, '-o', str(partial)],
                           check=True, timeout=130)
            if digest(partial) != SHA256:
                raise ValueError('PCRE archive differs from mirror-published pinned digest: ' + str(partial))
            partial.replace(archive)
        if digest(archive) != SHA256:
            raise ValueError('PCRE archive differs from mirror-published pinned digest')
        marker = cache / 'pcre-source.json'
        if source.exists():
            recorded = json.loads(marker.read_text())
            if recorded.get('archive_sha256') != SHA256 or recorded.get('inputs') != source_inputs(source):
                raise ValueError('Existing PCRE source changed; refusing to overwrite evidence')
        else:
            with tempfile.TemporaryDirectory(prefix='.pcre-extract-', dir=cache) as staging:
                with tarfile.open(archive, 'r:gz') as distribution:
                    distribution.extractall(staging, members=checked_members(distribution), filter='data')
                (Path(staging) / DIRECTORY).replace(source)
            write_json(marker, {'archive_sha256': SHA256, 'inputs': source_inputs(source)})
        compiler = shutil.which('cc')
        if not compiler:
            raise ValueError('C compiler is absent')
        compiler = str(Path(compiler).resolve())
        compiler_version = subprocess.check_output([compiler, '--version'], text=True).splitlines()[0]
        configure_args = ['--prefix=' + str(logical_prefix), '--libdir=' + str(logical_prefix / 'lib'),
                          '--enable-shared', '--disable-static', '--disable-cpp',
                          '--enable-utf', '--enable-unicode-properties', '--enable-jit']
        identity = {'schema': 1, 'kind': 'local-pcre1-sdk', 'version': VERSION,
                    'archive_sha256': SHA256, 'source_url': URL,
                    'checksum_source': CHECKSUM_SOURCE, 'checksum_provenance': 'mirror-published',
                    'upstream_signature_verified': False,
                    'source_inputs_sha256': digest(marker), 'compiler': compiler,
                    'compiler_sha256': digest(compiler), 'compiler_version': compiler_version,
                    'configure_args': configure_args, 'cflags': CFLAGS,
                    'pkgconfig_path_adapter': 'physical prefix with quoted include and library flags'}
        sdk_marker = prefix / 'installation.json'
        if prefix.exists():
            previous = json.loads(sdk_marker.read_text())
            if any(previous.get(key) != value for key, value in identity.items()):
                raise ValueError('Existing SDK source/compiler/arguments differ; refusing an unverified cache hit')
            if previous.get('make_check') != 'PASS' or previous.get('installed_inputs') != installed_inputs(prefix):
                raise ValueError('Existing PCRE SDK changed or lacks passed library checks')
        else:
            build.mkdir(parents=True, exist_ok=True)
            env = dict(os.environ)
            env.update(CC=compiler, CFLAGS=CFLAGS, LDFLAGS='', CPPFLAGS='', LIBS='',
                       CONFIG_SITE='/dev/null', PWD=str(logical_build))
            run([str(logical_source / 'configure'), *configure_args],
                logical_build, build / 'configure.log', env)
            run(['make', 'clean'], logical_build, build / 'clean.log', env)
            run(['make', '-j' + str(args.jobs)], logical_build, build / 'build.log', env)
            run(['make', 'check', '-j' + str(args.jobs)], logical_build, build / 'check.log', env)
            run(['make', 'install'], logical_build, build / 'install.log', env)
            # Metadata only: quoted physical paths let pkg-config return a
            # usable SDK after /tmp is cleared, without changing PCRE sources.
            pc = prefix / 'lib/pkgconfig/libpcre.pc'
            text = pc.read_text().replace(str(logical_prefix), str(prefix.resolve()))
            text = text.replace('-L${libdir}', '-L"${libdir}"').replace('-I${includedir}', '-I"${includedir}"')
            pc.write_text(text)
            if subprocess.check_output([str(prefix / 'bin/pcre-config'), '--version'], text=True).strip() != VERSION:
                raise ValueError('Installed PCRE version differs')
            identity.update(make_check='PASS', installed_inputs=installed_inputs(prefix))
            write_json(sdk_marker, identity)
        print('PCRE1 SDK ready: ' + str(prefix))
        print('PKG_CONFIG_PATH=' + str(prefix / 'lib/pkgconfig'))
        print('LD_LIBRARY_PATH=' + str(prefix / 'lib'))
        return 0
    except (OSError, ValueError, KeyError, subprocess.SubprocessError, tarfile.TarError) as exc:
        parser.exit(2, 'PCRE setup: ' + str(exc) + '\n')


if __name__ == '__main__':
    raise SystemExit(main())
