"""Bounded in-session reuse of *selection* trials, never final acceptance.

The first compared source remains the receipt's source. Reusing a trial does
not copy a receipt onto a different file. The normal final full-project gate
is unchanged. No MATCH/DIFF cache is persisted between processes.
"""
from collections import OrderedDict
import copy
import hashlib
import json
import os
from pathlib import Path
import shutil


def digest(path):
    h = hashlib.sha256()
    with Path(path).open('rb') as stream:
        for chunk in iter(lambda: stream.read(1 << 20), b''):
            h.update(chunk)
    return h.hexdigest()


class StaticInputs:
    """Rehash static compiler inputs, including directory additions/deletions.

    This is deliberately independent of runtime evidence: no ldd, original
    executable, test process or model is ever invoked. Missing inputs disable
    reuse. Hashes (not environment values) may be written to diagnostics.
    """
    def __init__(self, kit, root, previous, catalog, compiler_root, cfg):
        self.kit, self.root = Path(kit).resolve(), Path(root).resolve()
        self.compiler_root = Path(compiler_root).resolve()
        self.files = [self.kit / 'original/Torchlight.bin.x86_64',
                      self.kit / 'targets.json', self.kit / 'reference/elfdb.json',
                      self.kit / 'reference/types.json', Path(catalog).resolve(),
                      self.root / 'decomp/config.json']
        self.trees = [self.root / 'decomp', self.root / 'tools/decomp',
                      self.root / 'third_party', Path(previous).resolve(), self.compiler_root]
        for kind in ('include', 'system_include'):
            for item in cfg.get(kind, []):
                item = item.replace('@OGRE@', str(self.compiler_root / 'ogre-1.6.5/ogre'))
                p = Path(item)
                base = Path(os.environ.get('OTL_INCLUDE_ROOT', self.root)) if item.startswith('decomp/') else self.root
                self.trees.append((p if p.is_absolute() else base / p).resolve())
        for item in filter(None, os.environ.get('OTL_EXTRA_INCLUDE', '').split(':')):
            self.trees.append(Path(item).resolve())
        for name in ('objdump', 'nm', 'readelf'):
            executable = shutil.which(name)
            if executable:
                self.files.append(Path(executable).resolve())
        self.reason = None

    def __call__(self):
        required = self.compiler_root / 'usr/bin/g++'
        if not required.is_file():
            self.reason = 'Pinned GCC is unavailable; trial reuse is disabled.'
            return None
        try:
            files = set(self.files)
            listings = []
            for tree in sorted(set(self.trees)):
                if not tree.is_dir():
                    self.reason = 'A configured input directory is unavailable.'
                    return None
                found = sorted(p for p in tree.rglob('*')
                               if '__pycache__' not in p.parts and p.is_file())
                listings.append((tree, found))
                files.update(found)
            h = hashlib.sha256(b'smallmatch-selection-inputs-v1\0')
            # No raw environment data are exposed in reports.
            h.update(json.dumps(dict(os.environ), sort_keys=True).encode())
            for path in sorted(files):
                before = path.stat()
                if path.suffix.lower() in {'.h', '.hpp', '.hxx', '.c', '.cc', '.cpp', '.cxx', '.inc', '.tcc'}:
                    raw = path.read_bytes()
                    if any(token in raw for token in (b'__DATE__', b'__TIME__', b'__TIMESTAMP__')):
                        self.reason = 'Clock-dependent source/header macro disables reuse.'
                        return None
                h.update(str(path).encode() + b'\0' + digest(path).encode())
                # __TIMESTAMP__ and symlink/include-path changes are inputs too.
                h.update(str(before.st_mtime_ns).encode() + b'\0')
                if before != path.stat():
                    self.reason = 'An input changed while being fingerprinted.'
                    return None
            for tree, found in listings:
                if found != sorted(p for p in tree.rglob('*')
                                   if '__pycache__' not in p.parts and p.is_file()):
                    self.reason = 'An input directory changed while being fingerprinted.'
                    return None
            self.reason = None
            return h.hexdigest()
        except (OSError, ValueError):
            self.reason = 'An input could not be fingerprinted; reuse is disabled.'
            return None


class TrialMemo:
    """One TU, one invocation; all context is supplied explicitly by the driver."""
    def __init__(self, evaluate, render, input_token, *, max_entries=128, max_bytes=32 << 20):
        if max_entries < 1 or max_bytes < 1:
            raise ValueError('positive cache bounds required')
        self.evaluate, self.render, self.input_token = evaluate, render, input_token
        self.max_entries, self.max_bytes = max_entries, max_bytes
        self.entries, self.used = OrderedDict(), 0
        self.stats = {'requests': 0, 'evaluations': 0, 'hits': 0, 'bypasses': 0,
                      'evictions': 0, 'invalid_sources': 0, 'input_changes': 0, 'errors_not_cached': 0}

    def __call__(self, rows, phase, candidate):
        self.stats['requests'] += 1
        source = self.render(rows)
        if not isinstance(source, str):
            raise TypeError('trial renderer must return complete source text')
        token = self.input_token()
        # Clock-dependent builtins cannot be a deterministic retry recipe.
        volatile = any(s in source for s in ('__DATE__', '__TIME__', '__TIMESTAMP__', '__FILE__', '__BASE_FILE__'))
        key = None if token is None or volatile else (token, hashlib.sha256(source.encode()).hexdigest())
        entry = self.entries.get(key) if key else None
        if entry:
            result, source_hash, size = entry
            path = Path(result.get('_trial_source', ''))
            try:
                valid = path.is_file() and digest(path) == source_hash
            except OSError:
                valid = False
            if valid:
                self.entries.move_to_end(key)
                self.stats['hits'] += 1
                return copy.deepcopy(result)
            self.stats['invalid_sources'] += 1
            self.used -= size
            del self.entries[key]
        self.stats['evaluations'] += 1
        if key is None:
            self.stats['bypasses'] += 1
        result = self.evaluate(rows, phase, candidate)
        after = self.input_token() if token is not None else None
        if token is not None and after != token:
            self.stats['input_changes'] += 1
            raise RuntimeError('Static inputs changed during selection. Start a fresh isolated attempt.')
        if result.get('error'):
            # Resource failures/timeouts are not deterministic C++ rejections.
            self.stats['errors_not_cached'] += 1
        if key is not None and not result.get('error'):
            path = Path(result.get('_trial_source', ''))
            if path.is_file() and path.read_text() == source:
                data = copy.deepcopy(result)
                size = len(json.dumps(data).encode()) + len(source.encode())
                if size <= self.max_bytes:
                    while self.entries and (len(self.entries) >= self.max_entries or self.used + size > self.max_bytes):
                        _, (_, _, old_size) = self.entries.popitem(last=False)
                        self.used -= old_size
                        self.stats['evictions'] += 1
                    self.entries[key] = data, digest(path), size
                    self.used += size
        return result
