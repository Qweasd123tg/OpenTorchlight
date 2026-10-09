import os, threading, unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import Mock, patch
import objdiff, objdiff_disasm

class AdditionalReuseTests(unittest.TestCase):
    def make(self, **kwargs):
        functions={hex(i):dict(address=hex(i),size=1,tu=i//2) for i in (16,17,20,21)}
        section=object()
        image=SimpleNamespace(path=Path('unused'),section_at=lambda a:section)
        def decode(args):
            lo=int(args[0].split('=')[1],16);hi=int(args[1].split('=')[1],16)
            return [[i,'nop',''] for i in range(lo,hi)]
        run=Mock(side_effect=decode)
        c=objdiff_disasm.OriginalInstructions({'functions':functions},image,run,lambda x:x,mode='tu',**kwargs)
        return c,run,functions

    def test_batch_copy_is_independent(self):
        c,run,fs=self.make();rows=c.instructions(fs['0x10']);rows[0][1]='bad'
        self.assertEqual(c.instructions(fs['0x10']),[[16,'nop','']])
        self.assertEqual(run.call_count,1)

    def test_group_eviction_redecodes(self):
        c,run,fs=self.make(max_groups=1)
        for k in ('0x10','0x14','0x10'):c.instructions(fs[k])
        self.assertEqual(run.call_count,3);self.assertEqual(len(c.groups),1)

    def test_failed_decode_not_cached(self):
        c,run,fs=self.make();good=run.side_effect
        run.side_effect=RuntimeError('decoder failure')
        with self.assertRaises(RuntimeError):c.instructions(fs['0x10'])
        self.assertFalse(c.groups)
        run.side_effect=good
        self.assertEqual(c.instructions(fs['0x10']),[[16,'nop','']])

    def test_failed_index_initialization_can_retry(self):
        x=objdiff.Original.__new__(objdiff.Original);x._lock=threading.RLock()
        x.db={'globals':[], 'functions':{}};x.by_name={}
        x.image=SimpleNamespace(plt={},dynsyms=[],path=Path('unused'))
        with patch.dict(os.environ,{'OTL_ORIGINAL_DISASM':'invalid'}):
            with self.assertRaises(ValueError):x.resolver(None)
        self.assertNotIn('_global_data',x.__dict__)
        with patch.dict(os.environ,{'OTL_ORIGINAL_DISASM':'function'}):
            self.assertIsNone(x.resolver(None)('missing'))
            self.assertTrue(hasattr(x,'_disassembly'))

if __name__=='__main__':unittest.main()
