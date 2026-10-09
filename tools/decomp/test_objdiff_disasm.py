"""No execution: decoder bounds, cache scope and resolver precedence."""
from pathlib import Path
from types import SimpleNamespace
import tempfile, threading, unittest
from unittest.mock import Mock
import objdiff_disasm, objdiff

class DisassemblyTests(unittest.TestCase):
 def make(self, rows, functions=None, **opts):
  functions=functions or {'0x10':dict(address='0x10',size=2,tu=1),'0x12':dict(address='0x12',size=2,tu=1)}
  section=object();image=SimpleNamespace(path=Path('read-only-original'),section_at=lambda address:section)
  run=Mock(return_value=rows);parse=lambda text:text
  return objdiff_disasm.OriginalInstructions({'functions':functions},image,run,parse,**opts),run,functions
 def test_default_exact_range_and_reuse(self):
  c,run,fs=self.make([[16,'ret','']]);self.assertEqual(c.instructions(fs['0x10']),[[16,'ret','']]);c.instructions(fs['0x10']);self.assertEqual(run.call_count,1)
  self.assertEqual(run.call_args.args[0][:2],['--start-address=0x10','--stop-address=0x12'])
 def test_batch_endpoints(self):
  c,run,fs=self.make([[16,'nop',''],[17,'ret',''],[18,'nop',''],[19,'ret','']],mode='tu')
  self.assertEqual(c.instructions(fs['0x10']),[[16,'nop',''],[17,'ret','']]);self.assertEqual(c.instructions(fs['0x12']),[[18,'nop',''],[19,'ret','']]);self.assertEqual(run.call_count,1)
 def test_nonboundary_falls_back(self):
  c,run,fs=self.make([[16,'mov',''],[19,'ret','']],mode='tu');c.instructions(fs['0x10']);self.assertEqual(run.call_count,2);self.assertEqual(c.stats['boundary_fallbacks'],1)
 def test_missing_start_falls_back(self):
  c,run,fs=self.make([[17,'nop',''],[18,'ret','']],mode='tu');c.instructions(fs['0x10']);self.assertEqual(run.call_count,2)
 def test_duplicate_addresses_fall_back(self):
  c,run,fs=self.make([[16,'ret',''],[16,'nop','']],mode='tu');c.instructions(fs['0x10']);self.assertEqual(run.call_count,2)
 def test_large_interval_is_never_batched(self):
  c,run,fs=self.make([[16,'ret','']],mode='tu',max_range_bytes=1);c.instructions(fs['0x10']);self.assertEqual(c.stats['batch_commands'],0)
 def test_returned_rows_do_not_mutate_cache(self):
  c,run,fs=self.make([[16,'ret','']]);a=c.instructions(fs['0x10']);a[0][1]='corrupt';self.assertEqual(c.instructions(fs['0x10'])[0][1],'ret')
 def test_separate_images_do_not_share(self):
  a,ra,fs=self.make([[16,'ret','']]);b,rb,_=self.make([[16,'nop','']]);a.instructions(fs['0x10']);self.assertEqual(b.instructions(fs['0x10'])[0][1],'nop');self.assertEqual(rb.call_count,1)
 def test_negative_size_uses_exact_original_route(self):
  c,run,fs=self.make([]);f=dict(address='0x10',size=0,tu=1);c.instructions(f);self.assertEqual(run.call_args.args[0][:2],['--start-address=0x10','--stop-address=0x10'])
 def test_invalid_mode_rejected(self):
  with self.assertRaises(ValueError):self.make([],mode='anything')
 def test_bounded_single_cache(self):
  c,run,fs=self.make([[16,'ret','']],max_single_entries=1);c.instructions(fs['0x10']);c.instructions(fs['0x12']);c.instructions(fs['0x10']);self.assertEqual(run.call_count,3)
 def test_other_section_falls_back(self):
  c,run,fs=self.make([[16,'ret','']],mode='tu');c.image.section_at=lambda address: object();c.instructions(fs['0x10']);self.assertEqual(c.stats['batch_commands'],0)
 def test_one_command_for_concurrent_requests(self):
  c,run,fs=self.make([[16,'ret','']],mode='function');threads=[threading.Thread(target=c.instructions,args=(fs['0x10'],)) for _ in range(8)]
  for t in threads:t.start()
  for t in threads:t.join()
  self.assertEqual(run.call_count,1)

class ResolverTests(unittest.TestCase):
 def test_precedence_and_zero(self):
  x=objdiff.Original.__new__(objdiff.Original);x._lock=threading.RLock()
  x.db={'globals':[{'bind':'global','name':'g','address':'0x1'},{'bind':'global','name':'g','address':'0x2'}, {'bind':'local','name':'g','file':'A.cpp','address':'0x0'},{'bind':'local','name':'h','file':'B.cpp','address':'0x8'}],'functions':{}}
  x.image=SimpleNamespace(plt={32:'import@version'},dynsyms=[],path=Path('original'));x.by_name={}
  a=x.resolver(dict(id=1,name='A.cpp'));b=x.resolver(dict(id=2,name='B.cpp'))
  self.assertEqual(a('g'),0);self.assertEqual(b('g'),1);self.assertIsNone(a('h'));self.assertEqual(b('h'),8);self.assertEqual(a('import'),32);self.assertIsNone(a('missing'))
 def test_same_global_mapping_is_shared(self):
  x=objdiff.Original.__new__(objdiff.Original);x._lock=threading.RLock();x.db={'globals':[],'functions':{}};x.image=SimpleNamespace(plt={},dynsyms=[],path=Path('original'));x.by_name={}
  x.resolver(None);old=x._global_data;x.resolver(None);self.assertIs(old,x._global_data)

class CleanupPersistenceTests(unittest.TestCase):
 def original(self, entry):
  x=objdiff.Original.__new__(objdiff.Original);x._lock=threading.RLock();x.image=SimpleNamespace(sha256='test-original');x._norm_cache={'test-original:0x10':entry};x.frames=SimpleNamespace(reason=lambda *args:'EH LSDA equivalence unverified');x.normalized=Mock(return_value=entry['norm']);x._instructions=Mock(return_value=[[16,'ret','']]);return x
 def test_persisted_supported_signature_never_redecoded(self):
  import pickle
  from unittest.mock import patch
  entry={'norm':['ret']};first=self.original(entry);f=dict(address='0x10',size=1)
  signature=('personality',((0,1,0),))
  with patch.object(objdiff.objdiff_eh,'cleanup_signature',return_value=signature) as compare:
   self.assertEqual(first.cleanup_eh(f),signature);self.assertEqual(compare.call_count,1)
  second=self.original(pickle.loads(pickle.dumps(entry)))
  second._instructions.side_effect=AssertionError('immutable signature already persisted')
  with patch.object(objdiff.objdiff_eh,'cleanup_signature',side_effect=AssertionError('must use persisted signature')):
   self.assertEqual(second.cleanup_eh(f),signature)
 def test_unsupported_none_remains_unsupported(self):
  x=self.original({'norm':['ret'],'cleanup_eh':None});x._instructions.side_effect=AssertionError('not needed');self.assertIsNone(x.cleanup_eh(dict(address='0x10',size=1)))

if __name__ == '__main__':
 unittest.main()
