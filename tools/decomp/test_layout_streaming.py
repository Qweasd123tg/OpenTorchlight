"""Streaming instruction indexing: same records; failures never replace cache."""
import io, os, pickle, subprocess, tempfile, unittest
from pathlib import Path
from unittest.mock import patch
import layout

class Process:
 def __init__(self,text,status=0):
  self.stdout=io.StringIO(text);self.returncode=status;self.args=['objdump'];self.killed=False
 def wait(self):return self.returncode
 def poll(self):return self.returncode
 def kill(self):self.killed=True

class StreamingTests(unittest.TestCase):
 def setup_paths(self,d):
  root=Path(d);(root/'elfdb.json').write_text('{}');return root,root/'insns.pickle'
 def test_exact_records_and_serialization(self):
  with tempfile.TemporaryDirectory() as d:
   root,cache=self.setup_paths(d);proc=Process('header\n  10:\tmov    %rax,%rbx # comment\n  11:\tcall   20 <next+0x2>\n  13:\tret\n')
   db={'functions':{'0x10':{'size':3}}}
   with patch.object(layout,'CACHE',cache),patch.object(layout.elfdb,'DEFAULT_OUT',root),patch.object(layout.subprocess,'Popen',return_value=proc):
    out=layout.load_insns(db,'read-only')
   expected={'0x10':[(16,'mov','%rax,%rbx',''),(17,'call','20','next')]}
   self.assertEqual(out,expected);self.assertEqual(cache.read_bytes(),pickle.dumps(expected));self.assertTrue(proc.stdout.closed)
 def test_failed_decoder_does_not_publish(self):
  with tempfile.TemporaryDirectory() as d:
   root,cache=self.setup_paths(d);proc=Process('  10:\tret\n',status=1)
   with patch.object(layout,'CACHE',cache),patch.object(layout.elfdb,'DEFAULT_OUT',root),patch.object(layout.subprocess,'Popen',return_value=proc):
    with self.assertRaises(subprocess.CalledProcessError):layout.load_insns({'functions':{'0x10':{'size':1}}},'read-only')
   self.assertFalse(cache.exists());self.assertTrue(proc.stdout.closed)
 def test_failed_refresh_preserves_previous_cache(self):
  with tempfile.TemporaryDirectory() as d:
   root,cache=self.setup_paths(d);cache.write_bytes(b'old cache must survive');os.utime(cache,(0,0));proc=Process('',status=1)
   with patch.object(layout,'CACHE',cache),patch.object(layout.elfdb,'DEFAULT_OUT',root),patch.object(layout.subprocess,'Popen',return_value=proc):
    with self.assertRaises(subprocess.CalledProcessError):layout.load_insns({'functions':{}},'read-only')
   self.assertEqual(cache.read_bytes(),b'old cache must survive')
 def test_hot_cache_does_not_start_decoder(self):
  with tempfile.TemporaryDirectory() as d:
   root,cache=self.setup_paths(d);cache.write_bytes(pickle.dumps({'0x10':[(16,'ret','','')]}))
   with patch.object(layout,'CACHE',cache),patch.object(layout.elfdb,'DEFAULT_OUT',root),patch.object(layout.subprocess,'Popen',side_effect=AssertionError('unexpected disassembly')):
    self.assertEqual(layout.load_insns({'functions':{}},'read-only'),{'0x10':[(16,'ret','','')]})
if __name__=='__main__':unittest.main()
