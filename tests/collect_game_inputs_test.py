#!/usr/bin/env python3
"""Negative/synthetic tests for the private-input collector. No original assets."""
from pathlib import Path
import hashlib
import importlib.util
import json
import tempfile
import unittest
import zipfile

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('collect_game_inputs', ROOT/'tools/collect_game_inputs.py')
collector = importlib.util.module_from_spec(spec)
spec.loader.exec_module(collector)


class CollectInputs(unittest.TestCase):
    def test_selected_only_and_read_only(self):
        with tempfile.TemporaryDirectory() as tmp:
            base=Path(tmp); game=base/'game';game.mkdir()
            sources={'pak.zip':b'authored fixture pak', 'Torchlight.bin.x86_64':b'not executable; must never run',
                     'libCEGUIBase.so.0':b'authored library placeholder'}
            for name, content in sources.items(): (game/name).write_bytes(content)
            (game/'saves').mkdir();(game/'saves/hero.svt').write_text('PRIVATE SAVE')
            (game/'settings.ini').write_text('PRIVATE SETTINGS')
            report=collector.collect(game,base/'inputs.zip')
            self.assertFalse(report['original_executed']);self.assertEqual(report['missing'],[])
            with zipfile.ZipFile(base/'inputs.zip') as archive:
                self.assertEqual(set(archive.namelist()),set(sources)|{'INPUTS_MANIFEST.json'})
                manifest=json.loads(archive.read('INPUTS_MANIFEST.json'))
                for record in manifest['files']:
                    content=archive.read(record['path'])
                    self.assertEqual(content,sources[record['path']])
                    self.assertEqual(record['sha256'],hashlib.sha256(content).hexdigest())
                    self.assertEqual(record['bytes'],len(content))
                    self.assertEqual((game/record['path']).read_bytes(),content)
            self.assertEqual((game/'settings.ini').read_text(),'PRIVATE SETTINGS')
            self.assertFalse(list(base.glob('.ot-original-inputs-*')))

    def test_missing_binary_remains_explicit(self):
        with tempfile.TemporaryDirectory() as tmp:
            base=Path(tmp);game=base/'game';game.mkdir();(game/'pak.zip').write_bytes(b'fixture')
            report=collector.collect(game,base/'partial.zip')
            self.assertEqual(report['missing'],['Torchlight.bin.x86_64'])
            self.assertFalse(report['files'][0]['matches_previously_inspected_build'])

    def test_existing_output_not_replaced(self):
        with tempfile.TemporaryDirectory() as tmp:
            base=Path(tmp);game=base/'game';game.mkdir();(game/'pak.zip').write_bytes(b'fixture')
            out=base/'existing.zip';out.write_bytes(b'KEEP')
            with self.assertRaises(FileExistsError):collector.collect(game,out)
            self.assertEqual(out.read_bytes(),b'KEEP')
            self.assertFalse(list(base.glob('.ot-original-inputs-*')))

    def test_no_write_inside_game_or_repository(self):
        with tempfile.TemporaryDirectory() as tmp:
            game=Path(tmp);(game/'pak.zip').write_bytes(b'fixture')
            for out in (game/'inputs.zip',ROOT/'never-create-private-original-inputs.zip'):
                with self.assertRaises(ValueError):collector.collect(game,out)
                self.assertFalse(out.exists())

    def test_external_library_symlink_excluded(self):
        with tempfile.TemporaryDirectory() as tmp:
            base=Path(tmp);game=base/'game';game.mkdir();(game/'pak.zip').write_bytes(b'fixture')
            secret=base/'private';secret.write_text('PRIVATE')
            (game/'libOgreMain.so').symlink_to(secret)
            report=collector.collect(game,base/'inputs.zip')
            self.assertEqual(len(report['ignored']),1)
            with zipfile.ZipFile(base/'inputs.zip') as archive:self.assertNotIn('libOgreMain.so',archive.namelist())

    def test_empty_input_fails_without_archive(self):
        with tempfile.TemporaryDirectory() as tmp:
            base=Path(tmp);game=base/'game';game.mkdir()
            with self.assertRaises(FileNotFoundError):collector.collect(game,base/'missing.zip')
            self.assertFalse((base/'missing.zip').exists())

    def test_disable_libraries(self):
        with tempfile.TemporaryDirectory() as tmp:
            base=Path(tmp);game=base/'game';game.mkdir();(game/'pak.zip').write_bytes(b'fixture')
            (game/'libCEGUIBase.so').write_bytes(b'library')
            report=collector.collect(game,base/'inputs.zip',libraries=False)
            self.assertEqual([item['path'] for item in report['files']],['pak.zip'])

if __name__ == '__main__': unittest.main()
