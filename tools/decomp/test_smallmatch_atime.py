import os
from pathlib import Path
from tempfile import TemporaryDirectory
from types import SimpleNamespace
import unittest
from unittest.mock import patch
import smallmatch_trial_cache as cache

class AtimeFingerprintTests(unittest.TestCase):
    def setUp(self):
        self.tmp=TemporaryDirectory(); self.addCleanup(self.tmp.cleanup)
        self.root=Path(self.tmp.name); (self.root/'usr/bin').mkdir(parents=True)
        (self.root/'usr/bin/g++').write_text('fixture only, never executed')
        self.file=self.root/'input.h'; self.file.write_text('int x;')
        self.guard=cache.StaticInputs.__new__(cache.StaticInputs)
        self.guard.compiler_root=self.root; self.guard.files=[self.file]
        self.guard.trees=[]; self.guard.reason=None

    def test_access_time_is_not_file_identity(self):
        fields=['st_dev','st_ino','st_mode','st_nlink','st_uid','st_gid','st_size','st_mtime_ns','st_ctime_ns']
        values={name:getattr(self.file.stat(),name) for name in fields}
        a=SimpleNamespace(**values,st_atime_ns=0)
        b=SimpleNamespace(**values,st_atime_ns=123456789)
        self.assertEqual(cache._file_identity(a),cache._file_identity(b))
        for field in fields:
            changed=dict(values); changed[field]+=1
            self.assertNotEqual(cache._file_identity(a),cache._file_identity(SimpleNamespace(**changed,st_atime_ns=0)),field)

    def test_cold_access_does_not_disable_reuse(self):
        os.utime(self.file,ns=(0,self.file.stat().st_mtime_ns))
        before=self.file.stat(); token=self.guard(); after=self.file.stat()
        self.assertIsNotNone(token,self.guard.reason)
        self.assertEqual(cache._file_identity(before),cache._file_identity(after))
        self.assertEqual(token,self.guard())

    def test_edit_with_preserved_size_and_mtime_rejects_concurrent_read(self):
        real=cache.digest
        def change(path):
            result=real(path); st=path.stat(); path.write_text('int y;')
            os.utime(path,ns=(st.st_atime_ns,st.st_mtime_ns)); return result
        with patch.object(cache,'digest',change): self.assertIsNone(self.guard())
        self.assertIn('changed',self.guard.reason)

    def test_inode_replacement_with_same_bytes_rejects_concurrent_read(self):
        real=cache.digest
        def change(path):
            result=real(path); st=path.stat(); replacement=path.with_suffix('.new')
            replacement.write_bytes(path.read_bytes());os.utime(replacement,ns=(st.st_atime_ns,st.st_mtime_ns))
            replacement.replace(path); return result
        with patch.object(cache,'digest',change): self.assertIsNone(self.guard())

    def test_symlink_retarget_same_bytes_changes_key(self):
        other=self.root/'other.h'; other.write_bytes(self.file.read_bytes())
        os.utime(other,ns=(self.file.stat().st_atime_ns,self.file.stat().st_mtime_ns))
        link=self.root/'link.h';link.symlink_to(self.file);self.guard.files=[link]
        first=self.guard();self.assertIsNotNone(first)
        link.unlink();link.symlink_to(other);second=self.guard()
        self.assertIsNotNone(second);self.assertNotEqual(first,second)

    def test_symlink_retarget_during_hash_rejects(self):
        other=self.root/'other.h';other.write_bytes(self.file.read_bytes())
        link=self.root/'link.h';link.symlink_to(self.file);self.guard.files=[link];real=cache.digest
        def change(path):
            result=real(path);link.unlink();link.symlink_to(other);return result
        with patch.object(cache,'digest',change):self.assertIsNone(self.guard())

    def test_header_content_still_changes_key_with_same_size_and_mtime(self):
        first=self.guard();st=self.file.stat();self.file.write_text('int y;')
        os.utime(self.file,ns=(st.st_atime_ns,st.st_mtime_ns));self.assertNotEqual(first,self.guard())

    def test_addition_during_hash_rejects(self):
        inputs=self.root/'inputs';inputs.mkdir();self.file=inputs/'x.h';self.file.write_text('x')
        self.guard.files=[];self.guard.trees=[inputs];real=cache.digest
        def change(path):
            result=real(path);(inputs/'new.h').write_text('new');return result
        with patch.object(cache,'digest',change):self.assertIsNone(self.guard())

    def test_deletion_during_hash_rejects(self):
        real=cache.digest
        def change(path):
            result=real(path);path.unlink();return result
        with patch.object(cache,'digest',change):self.assertIsNone(self.guard())

if __name__=='__main__':unittest.main()
