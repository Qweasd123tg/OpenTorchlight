"""Atomic publication of the derived original-normalization cache."""
import errno
from pathlib import Path
import pickle
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

import objdiff


class NormCacheTest(unittest.TestCase):
    def setUp(self):
        directory = tempfile.TemporaryDirectory(prefix="otl-norm-cache-")
        self.addCleanup(directory.cleanup)
        self.root = Path(directory.name)
        self.path = self.root / "orig-normalized.pickle"
        self.key = [objdiff.NORMALIZER_VERSION, "synthetic-parser-and-input-digest"]
        self.old = {"original:0x100": {"norm": ["ret"], "metadata_reasons": []}}
        self.new = dict(self.old, **{
            "original:0x200": {"norm": ["mov", "ret"], "metadata_reasons": [],
                               "cleanup_eh": None}})
        self.old_bytes = pickle.dumps({"key": self.key, "functions": self.old})
        self.path.write_bytes(self.old_bytes)
        self.original = SimpleNamespace(_norm_cache=self.new)
        self.dirty = {"original:0x200"}
        for name, value in (("NORM_CACHE", self.path), ("_NORM_DIRTY", self.dirty)):
            replacement = patch.object(objdiff, name, value)
            replacement.start()
            self.addCleanup(replacement.stop)
        key_patch = patch.object(objdiff, "_norm_key", return_value=self.key)
        key_patch.start()
        self.addCleanup(key_patch.stop)

    def assert_old_preserved(self):
        self.assertEqual(self.path.read_bytes(), self.old_bytes)
        self.assertEqual(objdiff._load_norm_cache(), self.old)
        self.assertEqual(self.dirty, {"original:0x200"})
        self.assertEqual(list(self.root.iterdir()), [self.path])

    def test_success_replaces_complete_payload_and_reloads(self):
        replace = objdiff.os.replace

        def publish(source, target):
            self.assertEqual(Path(source).parent, self.path.parent)
            self.assertEqual(target, self.path)
            self.assertEqual(self.path.read_bytes(), self.old_bytes)
            self.assertEqual(pickle.loads(Path(source).read_bytes()),
                             {"key": self.key, "functions": self.new})
            return replace(source, target)

        with patch.object(objdiff.os, "replace", side_effect=publish) as replaced:
            objdiff.save_norm_cache(self.original)
        replaced.assert_called_once()
        self.assertEqual(self.path.read_bytes(),
                         pickle.dumps({"key": self.key, "functions": self.new}))
        self.assertEqual(objdiff._load_norm_cache(), self.new)
        self.assertEqual(self.dirty, set())
        self.assertEqual(list(self.root.iterdir()), [self.path])

    def test_partial_write_failure_preserves_old_cache_and_dirty(self):
        create = tempfile.NamedTemporaryFile

        def failing_file(*args, **kwargs):
            stream = create(*args, **kwargs)
            write = stream.write

            def partial_write(payload):
                write(payload[:7])
                stream.flush()
                self.assertEqual(Path(stream.name).read_bytes(), payload[:7])
                raise OSError(errno.ENOSPC, "injected partial write")

            stream.write = partial_write
            return stream

        with patch.object(objdiff.tempfile, "NamedTemporaryFile", side_effect=failing_file), \
                patch.object(objdiff.os, "replace") as replaced:
            with self.assertRaises(OSError) as error:
                objdiff.save_norm_cache(self.original)
        self.assertEqual(error.exception.errno, errno.ENOSPC)
        replaced.assert_not_called()
        self.assert_old_preserved()

    def test_replace_failure_preserves_old_cache_and_dirty(self):
        def fail_replace(source, target):
            self.assertEqual(pickle.loads(Path(source).read_bytes()),
                             {"key": self.key, "functions": self.new})
            raise OSError(errno.ENOSPC, "injected replacement failure")

        with patch.object(objdiff.os, "replace", side_effect=fail_replace):
            with self.assertRaises(OSError) as error:
                objdiff.save_norm_cache(self.original)
        self.assertEqual(error.exception.errno, errno.ENOSPC)
        self.assert_old_preserved()

    def test_clean_cache_does_not_write(self):
        self.dirty.clear()
        with patch.object(objdiff.tempfile, "NamedTemporaryFile") as create:
            objdiff.save_norm_cache(self.original)
        create.assert_not_called()
        self.assertEqual(self.path.read_bytes(), self.old_bytes)

    def test_empty_cache_retains_dirty_marker_without_writing(self):
        with patch.object(objdiff.tempfile, "NamedTemporaryFile") as create:
            objdiff.save_norm_cache(SimpleNamespace(_norm_cache={}))
        create.assert_not_called()
        self.assert_old_preserved()


if __name__ == "__main__":
    unittest.main()
