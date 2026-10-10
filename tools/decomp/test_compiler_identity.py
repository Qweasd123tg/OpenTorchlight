"""Fresh, alias-deduplicated compiler identity and monotonic cost regressions."""
from concurrent.futures import ThreadPoolExecutor
from contextlib import contextmanager
import hashlib
import os
from pathlib import Path
import subprocess
import tempfile
import threading
from types import SimpleNamespace
import unittest
from unittest.mock import patch

import toolchain


def legacy_identity(cmd, root, specs):
    """The previous digest byte stream, independent of candidate scan helpers."""
    digest = hashlib.sha256()
    for path in (Path(cmd[0]), root / 'usr/libexec/gcc' / toolchain.GCC_TRIPLE /
                 toolchain.GCC_VERSION / 'cc1plus', root / 'usr/bin/as'):
        digest.update(hashlib.sha256(path.read_bytes()).hexdigest().encode())
    libraries = root / 'usr/lib64'
    for path in sorted(libraries.rglob('*')):
        if path.is_file():
            digest.update(path.relative_to(libraries).as_posix().encode() + b'\0')
            digest.update(hashlib.sha256(path.read_bytes()).hexdigest().encode())
    digest.update(specs)
    return digest.hexdigest()


class CompilerIdentity(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory(prefix='otl-identity-')
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.driver = self.root / 'usr/bin/g++'
        self.backend = self.root / 'usr/libexec/gcc' / toolchain.GCC_TRIPLE / toolchain.GCC_VERSION / 'cc1plus'
        self.assembler = self.root / 'usr/bin/as'
        self.library = self.root / 'usr/lib64/libreal.so.1'
        self.specs = self.root / 'specs'
        for path, data in ((self.driver, b'driver one'), (self.backend, b'backend one'),
                           (self.assembler, b'assembler one'), (self.library, b'library one'),
                           (self.specs, b'specs one')):
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)
        self.alias = self.library.with_name('libreal.so')
        self.alias.symlink_to(self.library.name)
        self.hardlink = self.library.with_name('libhard.so')
        os.link(self.library, self.hardlink)
        self.cmd = [str(self.driver), '-B' + str(self.root / 'usr/bin/'), '-c']
        self.calls = []
        self.patch = patch.object(toolchain.subprocess, 'run', side_effect=self.dump_specs)
        self.patch.start()
        self.addCleanup(self.patch.stop)
        toolchain.compiler_stats(reset=True)

    def dump_specs(self, cmd, **kwargs):
        self.calls.append((cmd, kwargs))
        return SimpleNamespace(returncode=0, stdout=self.specs.read_bytes())

    def identity(self):
        return toolchain._compiler_identity(self.cmd, self.root)

    def mutate(self, path):
        before = path.stat()
        data = path.read_bytes()
        path.write_bytes(bytes([data[0] ^ 1]) + data[1:])
        os.utime(path, ns=(before.st_atime_ns, before.st_mtime_ns))
        self.assertEqual(before.st_size, path.stat().st_size)
        self.assertEqual(before.st_mtime_ns, path.stat().st_mtime_ns)

    def test_exact_legacy_digest_and_alias_byte_savings(self):
        self.assertEqual(legacy_identity(self.cmd, self.root, self.specs.read_bytes()), self.identity())
        stats = toolchain.compiler_stats()
        self.assertEqual(6, stats['identity_paths'])
        self.assertEqual(4, stats['identity_unique_files'])
        self.assertEqual(2, stats['identity_aliases'])
        self.assertEqual(self.library.stat().st_size * 2, stats['identity_reused_bytes'])
        self.assertEqual(stats['identity_logical_bytes'],
                         stats['identity_hashed_bytes'] + stats['identity_reused_bytes'])
        self.assertEqual(1, stats['identity_specs_calls'])

    def test_every_scan_reads_distinct_contents_and_specs_afresh(self):
        first = self.identity()
        once = toolchain.compiler_stats()
        self.assertEqual(first, self.identity())
        twice = toolchain.compiler_stats()
        self.assertEqual(2 * once['identity_hashed_bytes'], twice['identity_hashed_bytes'])
        self.assertEqual(2, len(self.calls))
        self.assertEqual(2, twice['identity_specs_calls'])

    def test_driver_backend_assembler_library_same_size_restored_mtime(self):
        previous = self.identity()
        for path in (self.driver, self.backend, self.assembler, self.library):
            with self.subTest(path=path.name):
                self.mutate(path)
                current = self.identity()
                self.assertIsNotNone(current)
                self.assertNotEqual(previous, current)
                self.assertEqual(legacy_identity(self.cmd, self.root, self.specs.read_bytes()), current)
                previous = current

    def test_specs_content_and_environment_are_not_memoized(self):
        first = self.identity()
        self.mutate(self.specs)
        self.assertNotEqual(first, self.identity())
        def environment_specs(cmd, **kwargs):
            return SimpleNamespace(returncode=0, stdout=kwargs['env']['OTL_IDENTITY_TEST'].encode())
        with patch.object(toolchain.subprocess, 'run', side_effect=environment_specs):
            with patch.dict(os.environ, {'OTL_IDENTITY_TEST': 'first'}):
                first = self.identity()
            with patch.dict(os.environ, {'OTL_IDENTITY_TEST': 'other'}):
                self.assertNotEqual(first, self.identity())

    def test_in_scan_same_size_restored_mtime_mutation_is_rejected(self):
        for path in (self.driver, self.backend, self.assembler, self.library):
            with self.subTest(path=path.name):
                def mutate_during_specs(cmd, **kwargs):
                    self.mutate(path)
                    return self.dump_specs(cmd, **kwargs)
                with patch.object(toolchain.subprocess, 'run', side_effect=mutate_during_specs):
                    self.assertIsNone(self.identity())
                self.assertIsNotNone(self.identity())

    def test_mutation_while_hash_is_being_completed_is_rejected(self):
        real_count = toolchain._compiler_count
        mutated = False
        def mutate_once(**values):
            nonlocal mutated
            if 'identity_hashed_bytes' in values and not mutated:
                mutated = True
                self.mutate(self.driver)
            real_count(**values)
        with patch.object(toolchain, '_compiler_count', side_effect=mutate_once):
            self.assertIsNone(self.identity())
        self.assertTrue(mutated)

    def test_environment_change_during_scan_is_rejected(self):
        def change_env(cmd, **kwargs):
            os.environ['OTL_IDENTITY_TEST'] = 'other'
            return self.dump_specs(cmd, **kwargs)
        with patch.dict(os.environ, {'OTL_IDENTITY_TEST': 'first'}), \
                patch.object(toolchain.subprocess, 'run', side_effect=change_env):
            self.assertIsNone(self.identity())

    def test_alias_retarget_and_library_add_remove_change_identity(self):
        first = self.identity()
        target = self.root / 'other.so'
        target.write_bytes(b'library two')
        self.alias.unlink()
        self.alias.symlink_to(target)
        second = self.identity()
        self.assertNotEqual(first, second)
        self.alias.unlink()
        third = self.identity()
        self.assertNotEqual(second, third)
        added = self.library.with_name('new.so')
        added.write_bytes(b'new library')
        self.assertNotEqual(third, self.identity())
        added.unlink()
        self.assertEqual(third, self.identity())

    def test_in_scan_symlink_replacement_even_same_target_is_rejected(self):
        def replace_alias(cmd, **kwargs):
            self.alias.unlink()
            self.alias.symlink_to(self.library.name)
            return self.dump_specs(cmd, **kwargs)
        with patch.object(toolchain.subprocess, 'run', side_effect=replace_alias):
            self.assertIsNone(self.identity())

    def test_in_scan_new_library_is_rejected(self):
        def add_library(cmd, **kwargs):
            self.library.with_name('new.so').write_bytes(b'new library')
            return self.dump_specs(cmd, **kwargs)
        with patch.object(toolchain.subprocess, 'run', side_effect=add_library):
            self.assertIsNone(self.identity())

    def test_in_scan_same_content_new_inode_is_rejected(self):
        def replace_driver(cmd, **kwargs):
            replacement = self.driver.with_name('replacement')
            replacement.write_bytes(self.driver.read_bytes())
            os.replace(replacement, self.driver)
            return self.dump_specs(cmd, **kwargs)
        with patch.object(toolchain.subprocess, 'run', side_effect=replace_driver):
            self.assertIsNone(self.identity())

    def test_missing_tool_specs_failure_and_specs_exception_fail_closed(self):
        with patch.object(toolchain.subprocess, 'run', return_value=SimpleNamespace(returncode=1, stdout=b'')):
            self.assertIsNone(self.identity())
        with patch.object(toolchain.subprocess, 'run', side_effect=OSError('missing driver')):
            self.assertIsNone(self.identity())
        self.assembler.unlink()
        self.assertIsNone(self.identity())

    def test_concurrent_scans_have_separate_content_lifetimes_and_exact_counters(self):
        expected = self.identity()
        once = toolchain.compiler_stats(reset=True)
        with ThreadPoolExecutor(max_workers=8) as pool:
            identities = list(pool.map(lambda _: self.identity(), range(16)))
        self.assertEqual([expected] * 16, identities)
        stats = toolchain.compiler_stats()
        for key in ('identity_paths', 'identity_unique_files', 'identity_hashed_bytes',
                    'identity_reused_bytes', 'identity_aliases', 'identity_specs_calls', 'identity_calls'):
            self.assertEqual(16 * once[key], stats[key], key)
        for key, value in stats.items():
            self.assertIsInstance(value, int)
            self.assertGreaterEqual(value, 0)
        self.assertEqual(stats, toolchain.compiler_stats(reset=True))
        self.assertEqual({}, toolchain.compiler_stats())


class CompilerTiming(unittest.TestCase):
    def setUp(self):
        toolchain.compiler_stats(reset=True)

    def test_monotonic_slot_wait_and_execution_are_separate(self):
        events = []
        @contextmanager
        def slot(name):
            events.append(('enter', name))
            yield
            events.append(('exit', name))
        def run(*args, **kwargs):
            events.append(('run', kwargs['timeout']))
            return 'result'
        with patch.object(toolchain.resource_slots, 'slot', side_effect=slot), \
                patch.object(toolchain.subprocess, 'run', side_effect=run), \
                patch.object(toolchain.time, 'monotonic_ns', side_effect=[100, 300, 400, 900]):
            self.assertEqual('result', toolchain.run_compiler(['g++', '-E'], timeout=7))
        self.assertEqual([('enter', 'compiler'), ('run', 7), ('exit', 'compiler')], events)
        self.assertEqual({'compiler_slot_wait_calls': 1, 'compiler_slot_wait_ns': 200,
                          'preprocess_run_calls': 1, 'preprocess_run_ns': 500}, toolchain.compiler_stats())

    def test_exception_still_records_execution_and_releases_slot(self):
        events = []
        @contextmanager
        def slot(name):
            try:
                yield
            finally:
                events.append('released')
        with patch.object(toolchain.resource_slots, 'slot', side_effect=slot), \
                patch.object(toolchain.subprocess, 'run', side_effect=OSError('failed')):
            with self.assertRaises(OSError):
                toolchain.run_compiler(['g++', '-c'])
        self.assertEqual(['released'], events)
        self.assertEqual(1, toolchain.compiler_stats()['backend_run_calls'])

    def test_failed_slot_wait_does_not_count_backend_execution(self):
        @contextmanager
        def slot(name):
            raise RuntimeError('slot timeout')
            yield
        with patch.object(toolchain.resource_slots, 'slot', side_effect=slot):
            with self.assertRaises(RuntimeError):
                toolchain.run_compiler(['g++', '-c'])
        stats = toolchain.compiler_stats()
        self.assertEqual(1, stats['compiler_slot_wait_failures'])
        self.assertNotIn('backend_run_calls', stats)


PINNED = toolchain.cache_dir() / 'gcc447'


@unittest.skipUnless((PINNED / '.complete.json').exists(), 'requires pinned GCC 4.4.7')
class RealIdentityCache(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory(prefix='otl-identity-real-')
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.source = self.root / 'Probe.cpp'
        self.source.write_text('extern "C" int value() { return 7; }\n')
        for name, value in (('SHARED_CC_CACHE', self.root / 'shared'), ('CC_CACHE', self.root / 'local')):
            context = patch.object(toolchain, name, value)
            context.start(); self.addCleanup(context.stop)
        context = patch.dict(os.environ, {}, clear=False)
        context.start(); self.addCleanup(context.stop)
        os.environ.pop('OTL_NO_CC_CACHE', None)
        context = patch.object(toolchain, 'config', return_value={'cflags': ['-O2'], 'include': []})
        context.start(); self.addCleanup(context.stop)
        toolchain.shared_cache_stats(reset=True)
        toolchain.compiler_stats(reset=True)

    def compile(self, name, **kwargs):
        return toolchain.compile_source(self.source, self.root / name, quiet=True, **kwargs)

    def test_legacy_key_hit_and_byte_equality_with_actual_pinned_toolchain(self):
        cmd = [str(PINNED / 'usr/bin/g++'),
               f'-B{PINNED}/usr/libexec/gcc/{toolchain.GCC_TRIPLE}/{toolchain.GCC_VERSION}/',
               f'-B{PINNED}/usr/bin/']
        specs = subprocess.run(cmd + ['-dumpspecs'], env=toolchain.driver_env(PINNED),
                               capture_output=True, check=True).stdout
        expected = legacy_identity(cmd, PINNED, specs)
        self.assertEqual(expected, toolchain._compiler_identity(cmd, PINNED))
        with patch.object(toolchain, '_compiler_identity', return_value=expected):
            first = self.compile('legacy.o')
        toolchain.compiler_stats(reset=True)
        current = self.compile('current.o')
        self.assertEqual(first.read_bytes(), current.read_bytes())
        self.assertEqual({'hit': 1, 'miss': 1, 'fallback': 0}, toolchain.shared_cache_stats())
        stats = toolchain.compiler_stats()
        self.assertEqual(1, stats['identity_calls'])
        self.assertEqual(1, stats['shared_preprocess_calls'])
        self.assertEqual(1, stats['preprocess_run_calls'])
        self.assertNotIn('backend_run_calls', stats)
        self.assertGreater(stats['identity_reused_bytes'], 0)

    def test_fresh_cpath_environment_shadowing_with_same_size_restored_mtime(self):
        self.source.write_text('#include <Value.h>\nextern "C" int value() { return VALUE; }\n')
        first, second = self.root / 'first', self.root / 'second'
        first.mkdir(); second.mkdir()
        (first / 'Value.h').write_text('#define VALUE 7\n')
        (second / 'Value.h').write_text('#define VALUE 9\n')
        with patch.dict(os.environ, {'CPATH': str(first)}):
            a = self.compile('first.o')
        with patch.dict(os.environ, {'CPATH': str(second)}):
            b = self.compile('second.o')
        self.assertNotEqual(a.read_bytes(), b.read_bytes())
        header = second / 'Value.h'
        saved = header.stat()
        header.write_text('#define VALUE 3\n')
        os.utime(header, ns=(saved.st_atime_ns, saved.st_mtime_ns))
        with patch.dict(os.environ, {'CPATH': str(second)}):
            c = self.compile('third.o')
        self.assertNotEqual(b.read_bytes(), c.read_bytes())
        self.assertEqual({'hit': 0, 'miss': 3, 'fallback': 0}, toolchain.shared_cache_stats())

    def test_before_after_backend_identity_difference_never_publishes(self):
        identity = toolchain._compiler_identity
        calls = 0
        def changed(*args):
            nonlocal calls
            calls += 1
            value = identity(*args)
            return value if calls == 1 else 'changed compiler content'
        with patch.object(toolchain, '_compiler_identity', side_effect=changed):
            result = self.compile('fallback.o')
        cold = self.compile('cold.o', cache=False)
        self.assertEqual(result.read_bytes(), cold.read_bytes())
        self.assertEqual([], list((self.root / 'shared').glob('*/result.json')))
        self.assertEqual({'hit': 0, 'miss': 1, 'fallback': 1}, toolchain.shared_cache_stats())

    def test_corrupt_hit_is_rebuilt_and_backend_calls_are_measured(self):
        first = self.compile('first.o')
        cached = next((self.root / 'shared').glob('*/output.o'))
        cached.write_bytes(b'corrupt')
        second = self.compile('second.o')
        third = self.compile('third.o')
        self.assertEqual(first.read_bytes(), second.read_bytes())
        self.assertEqual(first.read_bytes(), third.read_bytes())
        self.assertEqual({'hit': 1, 'miss': 2, 'fallback': 0}, toolchain.shared_cache_stats())
        stats = toolchain.compiler_stats()
        self.assertEqual(5, stats['identity_calls'])
        self.assertEqual(2, stats['backend_run_calls'])
        self.assertEqual(3, stats['preprocess_run_calls'])
        self.assertEqual(3, stats['compile_source_calls'])


if __name__ == '__main__':
    unittest.main()
