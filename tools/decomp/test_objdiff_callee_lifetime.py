"""Original-body summaries and pinned dependency invalidation, never name hints."""
import hashlib
import pickle
from pathlib import Path
from types import SimpleNamespace
import tempfile
import unittest
from unittest.mock import patch

import objdiff
import objdiff_eh


class CalleeLifetimeTest(unittest.TestCase):
    def side(self):
        side = objdiff.OriginalSide.__new__(objdiff.OriginalSide)
        side.image = SimpleNamespace(sha256='original', plt={0x900: '_Unwind_Resume'})
        side.library_identity = objdiff.OGRE_LITERAL_SHA256
        return side

    def body(self, start, rows):
        return {'start':start, 'size':rows[-1][0]-start+1, 'rows':rows,
                'names':['test'], 'body_sha256':'body'}

    def summary(self, bodies, target=0x100, side=None):
        side = side or self.side()
        with patch.object(side, '_callee_body', side_effect=lambda image, pc:bodies.get(pc)), \
             patch.object(objdiff.objdiff_eh,'inspect',return_value=objdiff_eh.Frames([])):
            return side._nonobserving_callee(side.image,target)

    def wrapper(self):
        return {0x100:self.body(0x100, [[0x100,'test','%rdi,%rdi'],
             [0x103,'je','110 <null>'],[0x105,'jmp','200 <free>'],
             [0x110,'repz ret','']]),
             0x200:self.body(0x200, [[0x200,'mov','%rdi,%rsi'],
             [0x203,'xor','%edi,%edi'],[0x205,'jmp','999 <unknown>']])}

    def test_nullable_wrapper_is_preserving_not_kill(self):
        proof=self.summary(self.wrapper())
        self.assertEqual(proof['effect'],'may-preserve-not-observe')
        self.assertEqual(proof['preserving_returns'],[0x110])
        self.assertEqual(proof['kills'],[])
        self.assertEqual(proof['calls'][0]['proof']['kills'],[0x200])

    def test_partial_writes_aliases_unknown_effects_and_calls_rejected(self):
        for op,args in [('mov','%di,%si'),('mov','%rsi,%r12'),('push','%rsi'),
                        ('cmp','%rsi,%rdi'),('lodsq',''),('syscall',''),
                        ('call','*%rax'),('jmp','*%rax'),('call','800 <unknown>')]:
            bodies=self.wrapper();bodies[0x200]=self.body(0x200,[[0x200,op,args],[0x205,'ret','']])
            with self.subTest(op=op,args=args): self.assertIsNone(self.summary(bodies))

    def test_recursive_cycle_and_missing_callee_fail_closed(self):
        bodies={0x100:self.body(0x100,[[0x100,'call','100 <self>'],[0x105,'ret','']])}
        self.assertIsNone(self.summary(bodies))
        self.assertIsNone(self.summary({}))

    def test_branch_into_instruction_middle_or_outside_is_not_assumed_safe(self):
        bodies=self.wrapper();bodies[0x100]['rows'][1]=[0x103,'je','111 <not_boundary>']
        self.assertIsNone(self.summary(bodies))

    def test_caller_must_continue_after_preserving_callee(self):
        side=self.side();proof={'kind':'original-body-no-rsi-observation','effect':'may-preserve-not-observe'}
        rows=[[0x300,'call','100 <nullable>'],[0x305,'mov','%rsi,%rax'],
              [0x308,'call','900 <resume>']]
        with patch.object(side,'_nonobserving_callee',return_value=proof):
            self.assertIsNone(side._rsi_cleanup_dead(rows,0x300,0x300,{'rows':[]}))
        rows[1]=[0x305,'mov','%rdi,%rsi']
        with patch.object(side,'_nonobserving_callee',return_value=proof):
            self.assertIsNotNone(side._rsi_cleanup_dead(rows,0x300,0x300,{'rows':[]}))

    def test_malformed_eh_and_exceptional_rsi_observation_rejected(self):
        side=self.side();bodies=self.wrapper()
        with patch.object(side,'_callee_body',return_value=bodies[0x100]), \
             patch.object(objdiff.objdiff_eh,'inspect',return_value=objdiff_eh.Frames([],error='bad')):
            self.assertIsNone(side._nonobserving_callee(side.image,0x100))
        side.image.plt[0x800]='_ZdlPv'
        rows=[[0x100,'call','800 <delete>'],[0x105,'ret',''],
              [0x110,'mov','%rsi,%rax'],[0x113,'call','900 <resume>']]
        with patch.object(side,'_callee_body',return_value=self.body(0x100,rows)), \
             patch.object(objdiff.objdiff_eh,'inspect',return_value=objdiff_eh.Frames([])), \
             patch.object(objdiff.OriginalSide,'_literal_eh',return_value={'rows':[(0,5,0x10,0)]}):
            self.assertIsNone(side._nonobserving_callee(side.image,0x100))

    def test_missing_mutated_or_mid_session_library_is_not_reused(self):
        side=self.side()
        side._literal_library=SimpleNamespace(sha256=objdiff.OGRE_LITERAL_SHA256)
        for identity in ['missing','mutated']:
            with patch.object(objdiff,'literal_library_identity',return_value=identity):
                self.assertIsNone(side._pinned_literal_library())
        with patch.object(objdiff,'literal_library_identity',return_value=objdiff.OGRE_LITERAL_SHA256):
            self.assertIs(side._pinned_literal_library(),side._literal_library)

    def test_unpinned_import_name_does_not_supply_proof(self):
        side=self.side();side.image.plt[0x800]='_ZN4Ogre12NedAllocImpl12deallocBytesEPv'
        with patch.object(side,'_pinned_literal_library',return_value=None):
            self.assertIsNone(side._nonobserving_callee(side.image,0x800))
        library=SimpleNamespace(dynsyms=[])
        with patch.object(side,'_pinned_literal_library',return_value=library):
            self.assertIsNone(side._nonobserving_callee(side.image,0x800))

    def test_library_bytes_are_in_normalization_key(self):
        with patch.object(objdiff,'literal_library_identity',return_value='a'):
            a=objdiff._norm_key()
        with patch.object(objdiff,'literal_library_identity',return_value='b'):
            b=objdiff._norm_key()
        self.assertNotEqual(a,b)
        original=SimpleNamespace(_literal_library_identity='a')
        with patch.object(objdiff,'literal_library_identity',return_value='b'):
            # Must return before accessing/writing any normal cache.
            self.assertIsNone(objdiff.save_norm_cache(original))

    def test_library_path_hash_missing_and_real_bytes(self):
        with tempfile.TemporaryDirectory() as directory:
            file=Path(directory)/'lib.so'
            with patch.object(objdiff,'literal_library_path',return_value=file):
                self.assertEqual(objdiff.literal_library_identity(),'missing')
                file.write_bytes(b'library-a')
                self.assertEqual(objdiff.literal_library_identity(),hashlib.sha256(b'library-a').hexdigest())
                file.write_bytes(b'library-b')
                self.assertEqual(objdiff.literal_library_identity(),hashlib.sha256(b'library-b').hexdigest())

class SnapshotAndCacheTest(unittest.TestCase):
    def test_frozen_session_key_cannot_relabel_A_as_B(self):
        with tempfile.TemporaryDirectory() as directory:
            path=Path(directory)/'norm.pickle'
            key=[objdiff.NORMALIZER_VERSION,'A','tools']
            original=SimpleNamespace(_literal_library_identity='A', _normalization_key=key,
                _norm_cache={'function':{'proof':'A'}})
            with patch.object(objdiff,'NORM_CACHE',path), patch.object(objdiff,'_NORM_DIRTY',{'function'}), \
                 patch.object(objdiff,'literal_library_identity',return_value='A'), \
                 patch.object(objdiff,'_norm_key',return_value=[objdiff.NORMALIZER_VERSION,'B','tools']):
                objdiff.save_norm_cache(original)
                self.assertEqual(pickle.loads(path.read_bytes())['key'],key)
                self.assertEqual(objdiff._load_norm_cache(),{})
                self.assertEqual(objdiff._load_norm_cache(key),original._norm_cache)

    def test_legacy_identity_without_frozen_key_rejects_race(self):
        with tempfile.TemporaryDirectory() as directory:
            path=Path(directory)/'norm.pickle'
            original=SimpleNamespace(_literal_library_identity='A',_norm_cache={'f':{'proof':'A'}})
            with patch.object(objdiff,'NORM_CACHE',path), patch.object(objdiff,'_NORM_DIRTY',{'f'}), \
                 patch.object(objdiff,'literal_library_identity',side_effect=['A','B']):
                objdiff.save_norm_cache(original)
                self.assertFalse(path.exists())

    def test_body_decoder_uses_snapshot_not_backing_path(self):
        raw=b'pin-this-snapshot'
        image=SimpleNamespace(data=raw,sha256=hashlib.sha256(raw).hexdigest(),path=Path('/mutable/not-read'),
             symbols=[SimpleNamespace(defined=True,type=objdiff.elfimage.STT_FUNC,value=0x100,size=1,name='f')],
             dynsyms=[], section_at=lambda a:SimpleNamespace(flags=4,addr=0x100,size=1),
             read=lambda a,n:raw[:n])
        side=objdiff.OriginalSide.__new__(objdiff.OriginalSide)
        def disassemble(args):
            self.assertNotEqual(args[0],str(image.path))
            self.assertEqual(Path(args[0]).read_bytes(),raw)
            return ' 100: ret\n'
        with patch.object(objdiff,'run_objdump',side_effect=disassemble):
            proof=side._callee_body(image,0x100)
            self.assertEqual(proof['body_sha256'],hashlib.sha256(raw[:1]).hexdigest())
        image.sha256='corrupted'
        with patch.object(objdiff,'run_objdump') as decode:
            self.assertIsNone(side._callee_body(image,0x100)); decode.assert_not_called()

if __name__=='__main__': unittest.main()
