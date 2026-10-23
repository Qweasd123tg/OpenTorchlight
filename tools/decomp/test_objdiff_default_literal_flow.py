"""Bounded default-copy flow: structural, argument, frame and cache negatives."""
import hashlib
import json
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch
import objdiff
import objdiff_eh
import objdiff_literal_flow as flow
import test_objdiff_literal_use as fixtures
REAL_CFI=flow.saved_rbx_cfi


class DefaultFlowTest(unittest.TestCase):
    def setUp(self):
        cfi=patch.object(flow,'saved_rbx_cfi',return_value={'kind':'unit-cfi-fixture'})
        cfi.start();self.addCleanup(cfi.stop)
        self.side=fixtures.ForwardLifetimeTest().side('LINE\0'.encode('utf-32le'))
        self.side.image.sha256='original-snapshot'
        self.side.image.plt.update({0x555400:flow.WCSLEN,0x555500:flow.WIDE_ASSIGN,0x555600:'wmemcmp'})
        self.side.image.symbols=[SimpleNamespace(defined=True,type=1,value=0x600000,size=8)]
        old=self.side.image.section_at
        self.side.image.section_at=lambda a: (SimpleNamespace(addr=0x600000,size=16,flags=3,name='.data')
                                             if 0x600000<=a<0x600010 else old(a))
        self.wrapper=[['push','%rbx'],['mov','%rdx,%rbx'],['call','200 <lookup>'],
            ['test','%rax,%rax'],['je','1009 <default>'],['pop','%rbx'],
            ['mov','$0x1,%esi'],['mov','%rax,%rdi'],['jmp','400 <tail>'],
            ['mov','%rbx,%rdi'],['call','555400 <wcslen>'],['mov','%rbx,%rsi'],
            ['mov','%rax,%rdx'],['mov','$0x600000,%edi'],['call','555500 <assign>'],
            ['mov','$0x600000,%eax'],['pop','%rbx'],['ret','']]
        self.rows={0x1000:[[0x1000+i,*r] for i,r in enumerate(self.wrapper)],
          0x200:[[0x200,'push','%rbx'],[0x201,'test','%eax,%eax'],[0x202,'je','208 <empty>'],
                 [0x203,'xor','%ebx,%ebx'],[0x204,'call','300 <leaf>'],
                 [0x205,'mov','(%rdi),%rdx'],[0x206,'call','555600 <wmemcmp>'],
                 [0x207,'jmp','208 <return>'],[0x208,'xor','%eax,%eax'],[0x209,'pop','%rbx'],[0x20a,'ret','']],
          0x300:[[0x300,'test','%eax,%eax'],[0x301,'je','304 <return>'],
                 [0x302,'mov','(%rdi),%rdx'],[0x303,'ret',''],[0x304,'ret','']],
          0x400:[[0x400,'push','%rbx'],[0x401,'sub','$0x10,%rsp'],
                 [0x402,'mov','(%rdi),%edx'],[0x403,'call','999 <after kill>']]}
        self.side.frames=objdiff_eh.Frames([(None,t,t+len(r),None,'__gxx_personality_v0') for t,r in self.rows.items()])
        def decoded(image,target):
            if target not in self.rows:return None
            rows=self.rows[target]
            return {'start':target,'size':len(rows),'rows':rows,'names':['not-an-allowlist'],
                    'body_sha256':hashlib.sha256(json.dumps(rows).encode()).hexdigest()}
        self.side._callee_body=decoded

    def proof(self):return flow.default_copy(self.side,0x1000)

    def caller(self):
        return [[0x10,'mov','$0xff0000,%edx'],[0x15,'mov','%r13,%rsi'],
                [0x18,'mov','%r12,%rdi'],[0x1b,'call','1000 <wrapper>'],
                [0x20,'mov','%rax,%rsi'],[0x23,'ret','']]

    def test_private_saved_alias_cannot_be_loaded_via_inherited_frame(self):
        self.rows[0x200][5][1:]=['mov','-0x8(%rbp),%rax']
        self.assertIsNone(self.proof())
        self.assertIsNone(self.side.wide_literal_use(0,self.caller(),0x10,0x24))

    def test_partial_immediate_does_not_create_object_pointer_root(self):
        original=[r[:] for r in self.rows[0x300]]
        for source,dest in (('$0x0','%al'),('$0x0','%ax'),('%edi','%rax')):
            self.rows[0x300][:]=[[0x300,'mov',source+','+dest],
                                [0x301,'mov','(%rax),%rdx'],[0x302,'ret','']]
            self.assertIsNone(self.proof())
        self.rows[0x300][:]=original
        self.assertIsNotNone(self.proof())

    def test_closed_private_frame_cannot_revisit_popped_save(self):
        self.rows[0x200][:]=[[0x200,'push','%rbx'],[0x201,'xor','%ebx,%ebx'],
                           [0x202,'pop','%rbx'],[0x203,'sub','$0x8,%rsp'],
                           [0x204,'xor','%eax,%eax'],[0x205,'ret','']]
        self.assertIsNone(self.proof())

    def test_narrow_destructor_exact_standard_this_only_abi(self):
        self.side.image.plt[0x555700]='_ZNSsD1Ev'
        self.assertIsNotNone(self.side._nonobserving_callee(self.side.image,0x555700))
        for bad in ('_ZNSsD1EvX','_ZNSsD1EPKw','_ZNSsD0Ev'):
            self.side.image.plt[0x555700]=bad
            self.assertIsNone(self.side._nonobserving_callee(self.side.image,0x555700))

    def test_cfi_restore_whole_throwing_instruction_span(self):
        text=('00000000 0000001c 00000000 CIE \"zPR\" cf=1 df=-8 ra=16\n\n'
              '00000010 00000000 00000000 FDE cie=00000000 pc=0000000000001000..0000000000001020\n'
              ' LOC CFA rbx ra\n1000 rsp+8 u c-8\n1001 rsp+16 c-16 c-8\n101f rsp+8 c-16 c-8\n\n')
        args=(0x1000,0x1020,0x1010,0x1015)
        self.assertIsNotNone(flow.parse_saved_rbx_cfi(text,*args))
        for bad in (text.replace('c-16','u'),text.replace('rsp+16','rbp+16'),
                    text.replace('101f rsp+8','1012 rsp+8'),text+text,
                    text.replace('CFA rbx ra','CFA r12 ra'),text.replace('1001','1011'),
                    text.replace('ra=16','ra=0'),text.replace('zPR','zUNKNOWN')):
            self.assertIsNone(flow.parse_saved_rbx_cfi(bad,*args))

    def test_cfi_decoder_uses_immutable_snapshot_and_invalidates_identity(self):
        data=b'original image bytes'
        image=SimpleNamespace(data=data,sha256=hashlib.sha256(data).hexdigest())
        side=SimpleNamespace(image=image)
        text=('00000000 1c 00000000 CIE "zPR" cf=1 df=-8 ra=16\n\n'
              '00000010 10 00000000 FDE cie=00000000 pc=1000..1020\n'
              'LOC CFA rbx ra\n1000 rsp+8 u c-8\n1001 rsp+16 c-16 c-8\n\n')
        def decode(argv,**kwargs):
            self.assertEqual(Path(argv[-1]).read_bytes(),image.data)
            return SimpleNamespace(returncode=0,stderr='',stdout=text)
        with patch.object(flow.subprocess,'run',side_effect=decode) as run:
            self.assertIsNotNone(REAL_CFI(side,{'start':0x1000,'size':0x20},0x1010,0x1015))
            self.assertIsNotNone(REAL_CFI(side,{'start':0x1000,'size':0x20},0x1010,0x1015))
            self.assertEqual(run.call_count,1)
            image.data=b'mutated'
            self.assertIsNone(REAL_CFI(side,{'start':0x1000,'size':0x20},0x1010,0x1015))
            image.sha256=hashlib.sha256(image.data).hexdigest()
            self.assertIsNotNone(REAL_CFI(side,{'start':0x1000,'size':0x20},0x1010,0x1015))
            self.assertEqual(run.call_count,2)

    def test_exact_extension_and_float_effects(self):
        good=[('movslq','%r13d,%rax'),('movzbl','0xa0(%rbx),%r13d'),
              ('movzbl','%al,%ecx'),('movss','0x94(%rbx),%xmm0'),
              ('movss','%xmm0,0x8(%rsp)'),('movss','%xmm1,%xmm15')]
        bad=[('movslq','%r13,%rax'),('movslq','%r13d,%eax'),('movslq','(%rbx),%rax'),
             ('movzbl','%eax,%ecx'),('movzbl','(%rbx),%cx'),('movzbl','%sil,%eax'),
             ('movss','%eax,%xmm0'),('movss','%xmm0,%eax'),('movss','%xmm16,%xmm0'),
             ('movss','(%rsi),%xmm0'),('movss','(%rax,%rsi,4),%xmm0'),
             ('movss','%fs:(%rax),%xmm0'),('movss','(%eax),%xmm0'),
             ('movss','(%rax),(%rbx)'),('movss','%xmm0,0x7fff1000')]
        for op,args in good:
            with self.subTest(op=op,args=args):
                self.assertTrue(self.side._literal_independent_instruction(op,args))
        for op,args in bad:
            with self.subTest(op=op,args=args):
                self.assertFalse(self.side._literal_independent_instruction(op,args))
        self.assertFalse(self.side._literal_independent_instruction('movss','(%rdx),%xmm0',{'d'}))

    def test_float_memory_rsi_is_rejected_by_public_wrapper(self):
        for args in ('(%rsi),%xmm0','%xmm0,(%rsi)'):
            rows=self.caller();rows[-2][1:]=['movss',args]
            self.assertIsNone(self.side.wide_literal_use(0,rows,0x10,0x24))

    def test_exact_original_structural_certificate(self):
        p=self.proof();self.assertIsNotNone(p)
        self.assertEqual(p['outgoing_aliases'],['si'])
        self.assertEqual(p['lookup']['outgoing'],['b','d'])
        self.assertEqual(p['found_tail']['outgoing'],[])
        self.assertEqual(p['return'],'independent-object-reference')

    def test_same_pointer_length_and_return_required(self):
        for i,op,args in [(9,'mov','%r12,%rdi'),(11,'mov','%r12,%rsi'),
                         (12,'mov','%rbx,%rdx'),(12,'lea','0x1(%rax),%rdx'),
                         (15,'mov','%rbx,%rax'),(15,'mov','$0x600008,%eax'),
                         (13,'mov','%rbx,%rdi'),(3,'test','%rdx,%rdx')]:
            old=self.rows[0x1000][i][:];self.rows[0x1000][i][1:]=[op,args]
            with self.subTest(i=i,args=args):self.assertIsNone(self.proof())
            self.rows[0x1000][i]=old

    def test_extra_instruction_edge_and_stack_imbalance_reject(self):
        for i,op,args in [(4,'jne','1009 <default>'),(4,'je','100a <middle>'),
                         (5,'pop','%rbp'),(16,'pop','%rdx'),(1,'mov','%rdx,(%rdi)'),
                         (8,'jmp','*%rax'),(2,'call','999 <unknown>')]:
            old=self.rows[0x1000][i][:];self.rows[0x1000][i][1:]=[op,args]
            with self.subTest(i=i,args=args):self.assertIsNone(self.proof())
            self.rows[0x1000][i]=old
        self.rows[0x1000].append([0x1012,'mov','%rbx,(%rdi)'])
        self.assertIsNone(self.proof())

    def test_exact_imports_not_like_names(self):
        for t in (0x555400,0x555500):
            old=self.side.image.plt[t];self.side.image.plt[t]=old+'X'
            self.assertIsNone(self.proof());self.side.image.plt[t]=old

    def test_lookup_observations_callbacks_partial_kills_and_frame_exposure(self):
        for t,i,op,args in [(0x200,1,'test','%rbx,%rbx'),(0x200,1,'mov','%rdx,(%rdi)'),
                           (0x200,5,'mov','%ax,%dx'),(0x200,5,'mov','%fs:(%rdi),%rdx'),
                           (0x200,5,'mov','0x7fff1000,%rdx'),
                           (0x200,5,'mov','(%edi),%rdx'),(0x200,4,'call','*%rax'),
                           (0x200,6,'call','999 <unknown while saved alias lives>'),
                           (0x200,3,'lea','(%rsp),%rdi'),(0x200,8,'pop','%rbp'),
                           (0x300,0,'test','%rdx,%rdx'),(0x300,0,'mov','%rdx,%rax'),
                           (0x300,0,'call','999 <callback>'),(0x400,2,'mov','%ax,%dx')]:
            old=self.rows[t][i][:];self.rows[t][i][1:]=[op,args]
            with self.subTest(t=t,i=i,args=args):self.assertIsNone(self.proof())
            self.rows[t][i]=old

    def test_callee_saved_pointer_must_restore_on_all_return_paths(self):
        self.rows[0x200][0][1:]=['push','%rbp']
        self.rows[0x200][8][1:]=['pop','%rbp']
        self.assertIsNone(self.proof())

    def test_missing_partial_or_unsupported_frame(self):
        old=self.side.frames
        for frames in [objdiff_eh.Frames([]),objdiff_eh.Frames([],error='bad'),
                       objdiff_eh.Frames([(None,0x1001,0x1012,None,None)]),
                       objdiff_eh.Frames([(None,0x1000,0x1012,'EH LSDA unverified',None)])]:
            self.side.frames=frames;self.assertIsNone(self.proof())
        self.side.frames=old

    def test_actual_use_full_payload_and_outgoing_alias(self):
        rows=self.caller();result=self.side.normalize(rows,0x10,0x24)
        self.assertIn('lit:w4:n4:',result[0]);self.assertEqual(self.side.literal_proofs[0]['size'],20)
        self.assertIn('unverified-data:',self.side.name_at(0xff0000,'mov',True))
        for op,args in [('mov','%rsi,%rax'),('mov','(%rsi),%rax'),('call','999 <unknown>')]:
            rows=self.caller();rows[4][1:]=[op,args]
            self.assertIsNone(self.side.wide_literal_use(0,rows,0x10,0x24))

    def test_caller_preconsumer_alias_and_exception_read_reject(self):
        rows=self.caller();rows[1][1:]=['mov','%rdx,%r12']
        self.assertIsNone(self.side.wide_literal_use(0,rows,0x10,0x24))
        rows=self.caller()+[[0x30,'mov','%rsi,%rax'],[0x33,'call','555200 <resume>']]
        eh={'kind':'gcc447-cleanup-v1','rows':[(0xb,5,0x20,0)]}
        with patch.object(self.side,'_literal_eh',return_value=eh):
            self.assertIsNone(self.side.wide_literal_use(0,rows,0x10,0x38))

    def test_warm_summary_mutation_is_not_reused(self):
        self.assertIsNotNone(self.proof())
        self.rows[0x300][0][1:]=['mov','%rdx,%rax']
        self.assertIsNone(self.proof())

    def test_normalization_key_depends_on_new_proof_module(self):
        original=Path.read_bytes
        before=objdiff._norm_key()
        def changed(path):
            value=original(path)
            return value+b'corrupted' if path.name=='objdiff_literal_flow.py' else value
        with patch.object(Path,'read_bytes',changed):self.assertNotEqual(before,objdiff._norm_key())


if __name__=='__main__':unittest.main()
