"""Immutable build-local metadata and ordered bounded hybrid assembly."""
import io
import json
import os
from pathlib import Path
import subprocess
import tempfile
import threading
from types import SimpleNamespace as NS
import unittest
from unittest.mock import patch

import elfimage
import hybrid
import toolchain


def symbol(name, defined=True, bind=1, kind=2):
    return NS(name=name, defined=defined, bind=bind, type=kind)


class ObjectSummaryTests(unittest.TestCase):
    def test_one_parse_preserves_function_order_and_symbol_filters(self):
        symbols = [symbol('local', bind=0), symbol('weak', bind=2), symbol(''),
                   symbol('data', kind=1), symbol('missing', False), symbol('', False)]
        with patch.object(elfimage, 'load_object', return_value=NS(symbols=symbols)) as load:
            result = hybrid.object_symbols(Path('one.o'))
        load.assert_called_once_with(Path('one.o'))
        self.assertEqual(result.functions, (('local', 0), ('weak', 2), ('', 1)))
        self.assertEqual(result.defined, frozenset(('weak', 'data')))
        self.assertEqual(result.undefined, frozenset(('missing',)))
        symbols[0].name = 'mutated'
        self.assertEqual(result.functions[0], ('local', 0))
        with self.assertRaises((AttributeError, TypeError)):
            result.defined = frozenset()

    def test_same_path_is_fresh_and_old_snapshot_is_immutable(self):
        with patch.object(elfimage, 'load_object', side_effect=[
                NS(symbols=[symbol('before')]), NS(symbols=[symbol('after')])]) as load:
            before = hybrid.object_symbols('same.o')
            after = hybrid.object_symbols('same.o')
        self.assertEqual(load.call_count, 2)
        self.assertEqual(before.defined, {'before'})
        self.assertEqual(after.defined, {'after'})

    def test_corrupt_object_is_not_hidden(self):
        with patch.object(elfimage, 'load_object', side_effect=ValueError('bad ELF')):
            with self.assertRaisesRegex(ValueError, 'bad ELF'):
                hybrid.object_symbols('bad.o')


class BuildTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory(prefix='hybrid-build-test-')
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        self.src = self.root / 'src'
        self.src.mkdir()
        self.out = self.root / 'out'
        self.tests = []
        self.rows = {}
        for index, stem in enumerate(('A', 'B', 'C')):
            source = self.src / (stem + '.cpp')
            source.write_text(stem)
            self.rows[stem] = [symbol('fn' + stem), symbol('alias'), symbol('compiler'),
                               symbol('external', False), symbol('owned', False)]
        for stem in ('D', 'E'):
            source = self.root / (stem + '.cpp')
            source.write_text(stem)
            self.tests.append(source)
            self.rows['test_' + stem] = [symbol('test' + stem), symbol('external', False)]
        functions = {
            16: dict(names=['fnA', 'alias'], address='0x10', kind='function', demangled='first'),
            32: dict(names=['fnB'], address='0x20', kind='function', demangled='second'),
            48: dict(names=['fnC'], address='0x30', kind='function', demangled='third'),
            64: dict(names=['compiler'], address='0x40', kind='compiler', demangled='compiler')}
        self.ctx = NS(db={}, global_data={'owned': 4096}, local_data={}, functions=functions,
                      image=NS(path=self.root/'original', sha256='original', read=lambda a,n:b'x'*n))
        self.ctx.tu_functions = lambda tu: {name:f for f in functions.values() for name in f['names']}
        self.assembled = []
        self.loaded = []
        self.links = []
        self.active = self.peak = 0
        self.lock = threading.Lock()
        self.after_assemble = None
        self.patches = [
            patch.object(hybrid, 'ROOT', self.root), patch.object(hybrid, 'Context', return_value=self.ctx),
            patch.object(hybrid.objdiff, 'tu_for_source', side_effect=lambda db,p:dict(name=p.stem,id=p.stem)),
            patch.object(hybrid.objdiff, 'unknown_members', return_value=[]),
            patch.object(hybrid.objdiff, 'image_symbol_names', return_value=set()),
            patch.object(hybrid, 'patch_window_ok', side_effect=lambda ctx,a:'short' if a==48 else None),
            patch.object(hybrid, 'originals_script', return_value=('provided\n', {'owned'})),
            patch.object(hybrid, 'library_objects', return_value={}),
            patch.object(toolchain, 'compile_source', side_effect=self.compile),
            patch.object(toolchain, 'assemble', side_effect=self.assemble),
            patch.object(toolchain, 'run_compiler', side_effect=self.loader),
            patch.object(hybrid.subprocess, 'run', side_effect=self.link),
            patch.object(elfimage, 'load_object', side_effect=self.load),
            patch.dict(os.environ, {'OTL_BUILD_JOBS':'3'})]
        for item in self.patches:
            item.start(); self.addCleanup(item.stop)

    def compile(self, source, target, flags, assembly):
        self.assertTrue(assembly)
        target.write_text('.text\n.type owned, @object\nowned:\n.quad 7\n'
                          '.type _GLOBAL__I_init, @function\n.section .ctors,"aw",@progbits\n.quad init\n')

    def assemble(self, source, output, *, capture_output=False):
        with self.lock:
            self.active += 1
            self.peak = max(self.peak, self.active)
        try:
            if self.after_assemble:
                self.after_assemble(source, output)
            output.write_bytes(source.read_bytes())
            self.assembled.append(output.name)
            result = subprocess.CompletedProcess(['as', '--64'], 0,
                                                  (output.stem + '\n').encode(),
                                                  ('warning ' + output.stem + '\n').encode())
            return result if capture_output else output
        finally:
            with self.lock:
                self.active -= 1

    def load(self, path):
        self.loaded.append(Path(path).name)
        return NS(symbols=self.rows.get(Path(path).stem, [symbol('fnA', False)]))

    def link(self, cmd, **kwargs):
        self.links.append(cmd)
        (kwargs['cwd']/'tlhybrid-blob.elf').write_bytes(b'linked')
        return subprocess.CompletedProcess(cmd, 0)

    def loader(self, cmd, **kwargs):
        Path(cmd[cmd.index('-o')+1]).write_bytes(b'loader')
        return subprocess.CompletedProcess(cmd, 0)

    def build(self):
        stdout, stderr = io.StringIO(), io.StringIO()
        with patch.object(hybrid.sys, 'stdout', stdout), patch.object(hybrid.sys, 'stderr', stderr):
            result = hybrid._build(self.out, True, self.src, self.tests)
        return result, stdout.getvalue(), stderr.getvalue()

    def test_exact_units_order_summaries_redirects_and_diagnostics(self):
        finished_b = threading.Event()
        both_assembling = threading.Barrier(2)
        def reversed_finish(source, output):
            if output.stem in ('A', 'B'):
                both_assembling.wait(timeout=5)
            if output.stem == 'A':
                self.assertTrue(finished_b.wait(5))
            elif output.stem == 'B':
                finished_b.set()
        self.after_assemble = reversed_finish
        _, stdout, stderr = self.build()
        self.assertGreaterEqual(self.peak, 2)
        self.assertLessEqual(self.peak, 3)
        self.assertEqual(sorted(self.loaded), ['A.o','B.o','C.o','hooks.o','test_D.o','test_E.o'])
        self.assertEqual(len(self.assembled), 7)
        self.assertEqual(self.links[0][-7:], ['A.o','B.o','C.o','test_D.o','test_E.o','hooks.o','imports.o'])
        self.assertLess(stdout.index('A\n'), stdout.index('B\n'))
        self.assertEqual(stderr, ''.join('warning '+x+'\n' for x in ('A','B','C','test_D','test_E')))
        manifest = json.loads((self.out/'manifest.json').read_text())
        self.assertEqual([x['symbol'] for x in manifest['hooks']], ['fnA','fnB'])
        self.assertEqual(manifest['notes'], ['not hooked third: short'])
        self.assertEqual(manifest['runtime_imports'], ['external'])
        self.assertEqual(manifest['standalone_residual']['original_initializers_omitted'],
                         {'src/A.cpp':['_GLOBAL__I_init'],'src/B.cpp':['_GLOBAL__I_init'],'src/C.cpp':['_GLOBAL__I_init']})
        self.assertNotIn('.quad init', (self.out/'A.hybrid.s').read_text())
        self.assertIn('.quad init', (self.out/'test_D.hybrid.s').read_text())
        self.assertIn('.set\towned, 0x1000', (self.out/'A.hybrid.s').read_text())
        timing = json.loads((self.out/'build-timings.json').read_text())
        self.assertEqual(timing['status'], 'completed')
        self.assertEqual([p['name'] for p in timing['phases']],
                         ['context','compile','rewrite_assemble_metadata','hook_reduction','hooks_imports','link','loader','manifest'])
        for phase in timing['phases']:
            for key in ('wall_seconds','process_cpu_seconds','children_cpu_seconds'):
                self.assertGreaterEqual(phase[key], 0)
        self.assertIsNone(timing['compiler_slot_wait_seconds'])

    def test_failure_replays_prior_diagnostics_and_raises_first_in_source_order(self):
        first = subprocess.CalledProcessError(2, ['as','A.hybrid.s'], output=b'A output\n', stderr=b'A error\n')
        second = SystemExit('B failed')
        def fail(source, output):
            if output.stem == 'B': raise second
            if output.stem == 'A': raise first
        self.after_assemble = fail
        self.out.mkdir()
        (self.out/'manifest.json').write_text('old manifest')
        stdout, stderr = io.StringIO(), io.StringIO()
        with patch.object(hybrid.sys, 'stdout', stdout), patch.object(hybrid.sys, 'stderr', stderr):
            with self.assertRaises(subprocess.CalledProcessError) as raised:
                hybrid._build(self.out, True, self.src, self.tests)
        self.assertIs(raised.exception, first)
        self.assertEqual(stdout.getvalue(), 'A output\n')
        self.assertEqual(stderr.getvalue(), 'A error\n')
        self.assertFalse(self.links)
        self.assertEqual((self.out/'manifest.json').read_text(), 'old manifest')
        self.assertEqual(json.loads((self.out/'build-timings.json').read_text())['status'], 'failed')

    def test_parse_failure_preserves_assembler_warning_and_fails_closed(self):
        with patch.object(elfimage, 'load_object', side_effect=ValueError('bad assembled object')):
            stderr = io.StringIO()
            with patch.object(hybrid.sys, 'stderr', stderr), patch.object(hybrid.sys, 'stdout', io.StringIO()):
                with self.assertRaisesRegex(ValueError, 'bad assembled object'):
                    hybrid._build(self.out, False, self.src, self.tests)
        self.assertEqual(stderr.getvalue(), 'warning A\n')
        self.assertFalse(self.links)
        self.assertFalse((self.out/'manifest.json').exists())

    def test_summary_never_survives_a_rebuild_or_source_mutation(self):
        self.build()
        self.rows['A'].append(symbol('changed_import', False))
        (self.src/'A.cpp').write_text('changed source')
        self.build()
        manifest = json.loads((self.out/'manifest.json').read_text())
        self.assertEqual(manifest['runtime_imports'], ['changed_import','external'])
        self.assertEqual(self.loaded.count('A.o'), 2)
        import hashlib
        self.assertEqual(manifest['standalone_residual']['source_sha256']['src/A.cpp'],
                         hashlib.sha256(b'changed source').hexdigest())

    def test_missing_tu_remains_a_system_exit_without_link(self):
        with patch.object(hybrid.objdiff, 'tu_for_source', return_value=None):
            with self.assertRaisesRegex(SystemExit, 'no unique original TU named A.cpp'):
                hybrid._build(self.out, False, self.src, self.tests)
        self.assertFalse(self.links)

    def test_failed_timing_write_and_warning_stream_do_not_change_build_success(self):
        with patch.object(hybrid._BuildTimings, 'write', side_effect=OSError('ENOSPC')), \
             patch.object(hybrid, 'print', side_effect=OSError('broken diagnostic stream'), create=True):
            result = hybrid._build(self.out, False, self.src, self.tests)
        self.assertEqual(result, (self.out/'tlhybrid-blob.elf', self.out/'libtlhybrid.so'))
        self.assertTrue((self.out/'manifest.json').is_file())

    def test_failed_timing_write_does_not_mask_build_failure(self):
        error = SystemExit('original compiler failure')
        with patch.object(toolchain, 'compile_source', side_effect=error), \
             patch.object(hybrid._BuildTimings, 'write', side_effect=OSError('ENOSPC')), \
             patch.object(hybrid, 'print', side_effect=OSError('broken diagnostic stream'), create=True):
            with self.assertRaises(SystemExit) as raised:
                hybrid._build(self.out, False, self.src, self.tests)
        self.assertIs(raised.exception, error)

    def test_earlier_success_warning_is_preserved_before_later_failure(self):
        failure = subprocess.CalledProcessError(2, ['as','B.hybrid.s'], output=b'', stderr=b'B error\n')
        def fail(source, output):
            if output.stem == 'B': raise failure
        self.after_assemble = fail
        stdout, stderr = io.StringIO(), io.StringIO()
        with patch.object(hybrid.sys, 'stdout', stdout), patch.object(hybrid.sys, 'stderr', stderr):
            with self.assertRaises(subprocess.CalledProcessError):
                hybrid._build(self.out, True, self.src, self.tests)
        self.assertEqual(stderr.getvalue(), 'warning A\nB error\n')
        self.assertIn('src/A.cpp:', stdout.getvalue())
        self.assertNotIn('src/B.cpp:', stdout.getvalue())
        self.assertFalse(self.links)

    def test_preexisting_linked_outputs_force_serial_preparation(self):
        for link_kind in ('hardlink', 'symlink'):
            with self.subTest(link_kind=link_kind):
                self.out = self.root/link_kind
                self.out.mkdir()
                first, second = self.out/'A.o', self.out/'B.o'
                first.write_bytes(b'previous')
                if link_kind == 'hardlink':
                    os.link(first, second)
                else:
                    second.symlink_to(first.name)
                self.peak = 0
                self.build()
                self.assertEqual(self.peak, 1)

    def test_duplicate_object_paths_use_serial_preparation_and_last_summary(self):
        nested = self.src/'nested'
        nested.mkdir()
        (nested/'A.cpp').write_text('duplicate A')
        seen = 0
        original_load = self.load
        def load(path):
            nonlocal seen
            if Path(path).name == 'A.o':
                seen += 1
                return NS(symbols=[symbol('first_only' if seen == 1 else 'last_only', False)])
            return original_load(path)
        with patch.object(elfimage, 'load_object', side_effect=load):
            self.build()
        self.assertEqual(self.peak, 1)
        self.assertEqual(seen, 3)
        imports = json.loads((self.out/'manifest.json').read_text())['runtime_imports']
        self.assertIn('last_only', imports)
        self.assertNotIn('first_only', imports)
        self.assertEqual(self.links[0].count('A.o'), 2)


class AssembleAndTimingTests(unittest.TestCase):
    def test_capture_is_optional_and_keeps_command_flags_and_shared_gate(self):
        result = subprocess.CompletedProcess([],0,b'output',b'warning')
        with patch.object(toolchain, 'cache_dir', return_value=Path('/pinned')), \
             patch.object(toolchain, 'run_compiler', return_value=result) as run:
            self.assertEqual(toolchain.assemble(Path('in.s'), Path('out.o')), Path('out.o'))
            self.assertIs(toolchain.assemble(Path('in.s'), Path('out.o'), capture_output=True), result)
        self.assertEqual(run.call_args.args[0], ['/pinned/gcc447/usr/bin/as','--64','-o','out.o','in.s'])
        self.assertTrue(run.call_args.kwargs['check'])
        self.assertTrue(run.call_args.kwargs['capture_output'])

    def test_timings_measure_cpu_not_concurrent_wall_and_write_atomically(self):
        with tempfile.TemporaryDirectory() as folder:
            out = Path(folder)
            report = out/'build-timings.json'
            report.write_text('previous')
            with patch.object(hybrid._BuildTimings, 'sample', side_effect=[(10,2,5),(11,3,7),(15,4,11)]):
                timing = hybrid._BuildTimings()
                timing.phase('work')
                timing.write(out, 'completed')
            result = json.loads(report.read_text())
            self.assertEqual(result['phases'][0], dict(name='work',wall_seconds=4,process_cpu_seconds=1,children_cpu_seconds=4))
            self.assertEqual(result['total'], dict(wall_seconds=5,process_cpu_seconds=2,children_cpu_seconds=6))
            old = report.read_bytes()
            with patch.object(hybrid.os, 'replace', side_effect=OSError('atomic failure')):
                with self.assertRaisesRegex(OSError, 'atomic failure'):
                    hybrid._BuildTimings().write(out, 'completed')
            self.assertEqual(report.read_bytes(), old)
            self.assertFalse(list(out.glob('.build-timings-*')))


if __name__ == '__main__':
    unittest.main()
