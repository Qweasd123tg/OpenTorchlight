"""Whole-original-wrapper adversarial fixtures; no game code execution."""
import copy
import hashlib
import struct
import unittest
from types import SimpleNamespace
from unittest.mock import patch
import objdiff
import objdiff_saved_argument as flow

class Fixture(objdiff.OriginalSide):
    register=staticmethod(objdiff.OriginalSide.register)
    padding=staticmethod(objdiff.OriginalSide.padding)
    direct_target=staticmethod(objdiff.OriginalSide.direct_target)
    def __init__(self, middle=(), child=(), suffix=(), cleanup=()):
        self.image=SimpleNamespace(plt={0x1000:flow.CTOR,0x1001:'_Unwind_Resume',0x1002:'_ZNSsD1Ev'},
            data=b'fixture',sha256=hashlib.sha256(b'fixture').hexdigest(),section_at=lambda a:None)
        instructions=[('push','%r12'),('sub','$0x18,%rsp'),('mov','%rdx,%r12'),('xor','%edx,%edx')]
        instructions+=list(middle)
        instructions += [('lea','0x10(%rsp),%rdx'),('lea','(%rsp),%rdi'),('mov','%r12,%rsi'),
                         ('call','1000'),('lea','0x8(%rsp),%r12'),('mov','%rsp,%rsi')]
        instructions+=list(suffix)+[('ret','')]
        self.pad=0x100+len(instructions)
        instructions+=list(cleanup)+[('mov','%rax,%rdi'),('call','1001')]
        rows=[(0x100+i,op,args) for i,(op,args) in enumerate(instructions)]
        consumer=next(pc for pc,op,args in rows if op=='call' and args=='1000')
        self.info={0x100:self.body(0x100,rows)}
        self.eh={0x100:{'kind':'fixture-cleanup','rows':[[consumer-0x100,1,self.pad-0x100,0]]}}
        self.tables={0x100:{'start':0x100,'end':0x100+len(rows),'cie':1,'rows':[
            (0x100,{'CFA':'rsp+8','ra':'c-8'}),
            (0x101,{'CFA':'rsp+16','ra':'c-8','r12':'c-16'}),
            (0x102,{'CFA':'rsp+40','ra':'c-8','r12':'c-16'})]}}
        if child:
            rows=[(0x200+i,op,args) for i,(op,args) in enumerate(child)]
            self.info[0x200]=self.body(0x200,rows)
            self.eh[0x200]={'kind':'fixture-none','rows':[]}
            self.tables[0x200]={'start':0x200,'end':0x200+len(rows),'cie':1,
                'rows':[(0x200,{'CFA':'rsp+8','ra':'c-8'})]}
    @staticmethod
    def body(start,rows):
        return {'start':start,'size':len(rows),'rows':rows,'body_sha256':hashlib.sha256(repr(rows).encode()).hexdigest()}
    def _callee_body(self,image,target):return self.info.get(target)
    def _literal_eh(self,rows,start,end):return self.eh.get(start)
    def run(self):
        e=flow.Engine(self)
        with patch.object(flow.frames,'cfi',side_effect=lambda side,info:self.tables.get(info['start'])):
            result=e.run(0x100,frozenset({'d'}),True)
        return result,e.error

class SavedArgumentTest(unittest.TestCase):
    def accept(self,f):
        result,error=f.run();self.assertIsNotNone(result,error);return result
    def reject(self,f):
        result,error=f.run();self.assertIsNone(result,(result,error))
    def test_copy_and_exception_alias_are_independent(self):
        p=self.accept(Fixture());self.assertEqual(p['normal_aliases'],[])
        self.assertEqual(p['exception_aliases'],['si']);self.assertEqual(len(p['copy_consumers']),1)
    def test_child_preserves_raw_and_entry_identities(self):
        p=self.accept(Fixture(middle=[('call','200')],child=[('xor','%eax,%eax'),('ret','')]))
        self.assertTrue(any(x['proof']['kind'].startswith('original-') for x in p['calls']))
    def test_child_extra_return_alias_rejected(self):
        for register in ['%rsi','%rax','%rdx']:
            self.reject(Fixture(middle=[('call','200')],child=[('mov',f'%r12,{register}'),('ret','')]))
    def test_child_unknown_callback_and_raw_observation(self):
        for op,args in [('call','*%rax'),('call','999'),('test','%r12,%r12'),('mov','%r12,(%rdi)'),('mov','(%r12),%rax')]:
            self.reject(Fixture(middle=[('call','200')],child=[(op,args),('ret','')]))
    def test_saved_entry_identity_change_rejected(self):
        for reg in ['%rbx','%rbp','%r13','%r14','%r15']:
            self.reject(Fixture(middle=[('call','200')],child=[('mov',f'$0x0,{reg}'),('ret','')]))
    def test_overlapping_caller_frame_bindings_rejected(self):
        for off in ['0x0','0x4']:
            self.reject(Fixture(middle=[('lea','(%rsp),%rdi'),('lea',f'{off}(%rsp),%rsi'),('call','200')],
                                child=[('ret','')]))
    def test_private_caller_save_argument_rejected(self):
        self.reject(Fixture(middle=[('lea','0x18(%rsp),%rdi'),('call','200')],child=[('ret','')]))
    def test_child_footprint_escape_rejected(self):
        for access in ['-0x1(%rdi)','0x8(%rdi)','0x4(%rdi)']:
            self.reject(Fixture(middle=[('lea','(%rsp),%rdi'),('call','200')],
                child=[('mov',f'{access},%rax'),('ret','')]))
    def test_unproven_inherited_frame_base_rejected(self):
        self.reject(Fixture(middle=[('call','200')],child=[('mov','-0x8(%rbp),%rax'),('ret','')]))
    def test_cleanup_raw_read_rejected(self):
        for code in [[('test','%rsi,%rsi')],[('mov','%rsi,%rax'),('mov','%rax,(%rdi)')],
                     [('mov','%r12d,%esi')],[('call','*%rax')]]:
            self.reject(Fixture(cleanup=code))
    def test_wrong_consumer_identity_and_source(self):
        f=Fixture();f.image.plt[0x1000]=flow.CTOR.replace('C1','C2');self.reject(f)
        f=Fixture();f.info[0x100]['rows']=[(pc,op,'%r12,%rdi' if arg=='%r12,%rsi' else arg)
                                                  for pc,op,arg in f.info[0x100]['rows']];self.reject(f)
    def test_bad_cfi_at_consumer_and_cleanup(self):
        for rule in ['rsp+32','rsp+48']:
            f=Fixture();f.tables[0x100]['rows'][-1][1]['CFA']=rule;self.reject(f)
        f=Fixture();f.tables[0x100]['rows'].append((f.pad,{'CFA':'rsp+40','ra':'c-8','r12':'c-24'}));self.reject(f)
    def test_missing_or_malformed_cleanup(self):
        for rows in [None,[[8,1,999,0]],[[8,1,12,0],[8,1,12,0]]]:
            f=Fixture()
            if rows is None:f.eh[0x100]=None
            else:
                call=next(pc for pc,op,args in f.info[0x100]['rows'] if args=='1000')
                for r in rows:r[0]=call-0x100
                f.eh[0x100]['rows']=rows
            self.reject(f)
    def test_restored_stale_raw_slot_not_exposed(self):
        e=flow.Engine(Fixture())
        st=flow.State({'di':('frame',-8)},cells={-8:(8,flow.RAW,None)},sp=-16)
        with self.assertRaises(flow.Reject):e.typed_local(st,'di',8)
    def test_typed_call_rejects_unbounded_frame_source(self):
        e=flow.Engine(Fixture())
        st=flow.State({'12':flow.RAW,'di':('frame',-32),'si':('frame',-24),'d':('frame',-16)},sp=-40)
        with self.assertRaises(flow.Reject):e.standard(st,flow.CTOR)
    def test_partial_initialization_of_child_argument_rejected(self):
        for code in [[('movb','$0x0,(%rdi)'),('mov','0x4(%rdi),%eax'),('ret','')],
                     [('movl','$0x0,(%rdi)'),('mov','(%rdi),%rax'),('ret','')]]:
            self.reject(Fixture(middle=[('lea','(%rsp),%rdi'),('call','200')],child=code))
        e=flow.Engine(Fixture());st=flow.State({'di':('argument','di',0)},arguments={'di':(8,flow.UNINITIALIZED)})
        e.write(st,'(%rdi)',1,flow.const([0]))
        self.assertEqual(st.arguments['di'][1],flow.UNINITIALIZED)
        with self.assertRaises(flow.Reject):e.read(st,'(%rdi)',8)
        e.write(st,'(%rdi)',8,flow.ROOT);self.assertEqual(e.read(st,'(%rdi)',8),flow.ROOT)
    def test_child_stack_residue_cannot_be_read_after_reallocation(self):
        for prefix in [[],[('sub','$0x10,%rsp'),('movq','$0x1,(%rsp)'),('add','$0x10,%rsp')]]:
            f=Fixture(child=[('push','%r12'),('pop','%r12'),('ret','')])
            code=prefix+[('call','200'),('sub','$0x10,%rsp'),('mov','(%rsp),%eax'),('add','$0x10,%rsp'),('ret','')]
            rows=[(0x100+i,op,args) for i,(op,args) in enumerate(code)]
            f.info[0x100]=f.body(0x100,rows);f.eh[0x100]={'kind':'fixture-none','rows':[]}
            f.tables[0x100]={'start':0x100,'end':0x100+len(rows),'cie':1,'rows':[(0x100,{'CFA':'rsp+8','ra':'c-8'})]}
            e=flow.Engine(f)
            with patch.object(flow.frames,'cfi',side_effect=lambda side,info:f.tables.get(info['start'])):
                self.assertIsNone(e.run(0x100,frozenset({'12'})),e.error)
                self.assertIn('uninitialized',e.error['reason'])
    def test_eh_does_not_retain_nonraw_volatile_root(self):
        self.reject(Fixture(middle=[('mov','%rdi,%r11')],cleanup=[('mov','(%r11),%rax')]))
    def test_uninitialized_typed_destructor_rejected(self):
        e=flow.Engine(Fixture())
        for value in [('frame',-8),('argument','di',0)]:
            st=flow.State({'di':value,'12':flow.RAW},sp=-16,arguments={'di':(8,flow.UNINITIALIZED)})
            with self.assertRaises(flow.Reject):e.standard(st,'_ZNSsD1Ev')
    def test_replace_updates_object_pointer_not_old_constant(self):
        side=Fixture();side.image.section_at=lambda a:SimpleNamespace(addr=0x4000,size=32,flags=3) if 0x4000<=a<0x4020 else None
        e=flow.Engine(side)
        st=flow.State({'12':flow.RAW,'di':('frame',-8),'si':flow.const([0]),'d':flow.const([0]),'c':flow.const([0x4000]),'8':flow.const([1])},
                      cells={-8:(8,flow.const([0x4000]),None)},sp=-16)
        e.standard(st,flow.REPLACE);self.assertEqual(st.cells[-8][1],flow.STRING_STORAGE)
    def test_public_original_operand_and_outer_exception_continuation(self):
        for unsafe in [False,True]:
            f=Fixture();rows=[(0x400,'mov','$0x5000,%edx'),(0x405,'call','100'),(0x40a,'ret',''),
                (0x410,'mov','%rsi,%rax') if unsafe else (0x410,'xor','%esi,%esi'),(0x413,'ret','')]
            f.eh[0x400]={'kind':'fixture-cleanup','rows':[[5,5,16,0]]}
            with patch.object(flow.frames,'cfi',side_effect=lambda side,info:f.tables.get(info['start'])):
                p=f.wide_literal_use(0,rows,0x400,0x414)
            if unsafe:self.assertIsNone(p)
            else:
                self.assertIsNotNone(p);self.assertEqual(p['width'],4)
                self.assertEqual(p['model'],'original-saved-wide-argument-v1');self.assertTrue(p['cleanup'])
    def test_public_source_operand_escape_and_indirect_consumer(self):
        for op,args in [('mov','%rdx,%rax'),('mov','%rdx,(%rdi)'),('cmp','%rdx,%rax'),('call','*%rax')]:
            f=Fixture();rows=[(0x400,'mov','$0x5000,%edx'),(0x405,op,args),(0x408,'call','100'),(0x40d,'ret','')]
            f.eh[0x400]={'kind':'fixture-none','rows':[]}
            with patch.object(flow.frames,'cfi',side_effect=lambda side,info:f.tables.get(info['start'])):
                self.assertIsNone(f.wide_literal_use(0,rows,0x400,0x40e))

    def test_mutated_original_snapshot_rejects_even_warm_memo(self):
        f=Fixture();e=flow.Engine(f)
        with patch.object(flow.frames,'cfi',side_effect=lambda side,info:f.tables.get(info['start'])):
            self.assertIsNotNone(e.run(0x100,frozenset({'d'}),True))
            f.image.data=b'mutated'
            self.assertIsNone(e.run(0x100,frozenset({'d'}),True))

    def test_private_return_and_returned_binding_provenance(self):
        self.reject(Fixture(middle=[('call','200')],child=[('lea','(%rsp),%rax'),('ret','')]))
        self.accept(Fixture(middle=[('lea','(%rsp),%rdi'),('call','200')],child=[('mov','%rdi,%rax'),('ret','')]))
        self.reject(Fixture(middle=[('lea','(%rsp),%rdi'),('call','200'),('mov','%rax,(%rsi)')],
                            child=[('mov','%rdi,%rax'),('ret','')]))
    def test_import_declared_scalar_inputs_must_be_defined(self):
        e=flow.Engine(Fixture())
        for name,args in [(flow.FIND,{'di':flow.ROOT,'si':flow.ROOT,'d':None,'c':None}),
                          (flow.WREPLACE,{'di':flow.ROOT,'si':None,'d':None,'c':flow.ROOT,'8':None})]:
            e.standard(flow.State(args.copy()),name)
            for reg in flow.IMPORTS[name][0]:
                for invalid in [flow.POISON,('entry','b')]:
                    bad=args.copy();bad[reg]=invalid
                    with self.assertRaises(flow.Reject):e.standard(flow.State(bad),name)
    def test_string_storage_producer_and_exact_count_footprint(self):
        e=flow.Engine(Fixture())
        st=flow.State({'di':('frame',-16),'si':flow.ROOT,'d':('frame',-8)},sp=-16)
        e.standard(st,flow.CTOR);self.assertEqual(st.cells[-16][1],flow.STRING_STORAGE)
        st.regs['di']=e.read(st,'(%rsp)',8)
        e.effect(st,'sub','$0x18,%rdi',{});self.assertEqual(st.regs['di'],('string-storage',-24))
        e.write(st,'0x10(%rdi)',4,None);self.assertFalse(st.direct_root_writes)
        self.assertIsNone(e.read(st,'(%rdi)',8))
        for offset,size in [('0x8',4),('0x10',8),('0x11',1)]:
            other=st.clone();e.write(other,f'{offset}(%rdi)',size,None);self.assertTrue(other.direct_root_writes)
        st.regs['di']=flow.STRING_STORAGE;e.effect(st,'add','$0x4,%rdi',{})
        self.assertEqual(st.regs['di'],('string-storage',None))
        e.effect(st,'sub','$0xc,%rdi',{});e.write(st,'(%rdi)',4,None);self.assertTrue(st.direct_root_writes)
    def test_exact_string_object_import_sources_and_return_aliases(self):
        e=flow.Engine(Fixture())
        for name in [flow.COPY,flow.ASSIGN]:
            st=flow.State({'di':('frame',-16),'si':('frame',-8)},sp=-16,
                          cells={-16:(8,flow.STRING_STORAGE,None),-8:(8,flow.STRING_STORAGE,None)})
            e.standard(st,name);self.assertEqual(st.cells[-16][1],flow.STRING_STORAGE)
            if name==flow.ASSIGN:self.assertEqual(st.regs['a'],('frame',-16))
            for source in [flow.RAW,flow.UNINITIALIZED]:
                bad=flow.State({'di':('frame',-16),'si':('frame',-8)},sp=-16,
                               cells={-16:(8,flow.STRING_STORAGE,None),-8:(8,source,None)})
                with self.assertRaises(flow.Reject):e.standard(bad,name)
        for name in ['wcslen',flow.FIND,flow.WREPLACE]:
            st=flow.State({'di':('frame',-16),'si':('frame',-8),'c':('frame',-8)},sp=-16,
                          cells={-16:(8,flow.STRING_STORAGE,None),-8:(8,flow.const([0]),None)})
            with self.assertRaises(flow.Reject):e.standard(st,name)

    def test_undefined_abi_values_cannot_be_relabelled_scalar(self):
        self.reject(Fixture(middle=[('call','200'),('mov','%rax,(%rdi)')],child=[('call','1002'),('ret','')]))
        self.reject(Fixture(middle=[('call','200')],child=[('mov','%rbp,%rax'),('mov','%rax,(%rdi)'),('ret','')]))
        self.reject(Fixture(middle=[('call','200')],child=[('call','1002'),('mov','%rax,%rdx'),('xor','%eax,%eax'),('ret','')]))
        e=flow.Engine(Fixture());st=flow.State({'di':('frame',-16),'si':flow.const([0]),'d':flow.const([0]),'c':flow.ROOT,'8':flow.const([0])},
                                            sp=-16,cells={-16:(8,flow.ROOT,None)})
        e.standard(st,flow.REPLACE);self.assertEqual(st.regs['a'],('frame',-16))
        with self.assertRaises(flow.Reject):e.effect(st,'mov','%rax,(%r13)',{})

    def test_whole_wrapper_private_pointer_laundering(self):
        variants=[[('mov','%rsp,%rax'),(op,args)] for op,args in
                  [('or','$0x0,%rax'),('xor','$0x0,%rax'),('and','$0xffffffffffffffff,%rax'),
                   ('shr','$0x0,%rax'),('add','%rax,%rcx'),('lock xadd','%rax,(%rdi)')]]
        variants += [[('lea','(%rsp,%rcx,1),%rax')],[('lea','(%rsp),%eax')],
                     [('mov','%rsp,%rax'),('mov','$0x0,%ax')]]
        for ops in variants:
            body=[('push','%r12')]+ops+[('mov','%rax,(%rdi)'),('mov','(%rdi),%rdx'),
                 ('mov','(%rdx),%rax'),('test','%rax,%rax'),('pop','%r12'),('xor','%eax,%eax'),('ret','')]
            self.reject(Fixture(middle=[('call','200')],child=body))

    def test_private_address_arithmetic_cannot_launder_escape(self):
        e=flow.Engine(Fixture())
        for op,args in [('or','$0x0,%rax'),('xor','$0x1,%rax'),('and','$0xffffffffffffffff,%rax'),
                        ('shr','$0x0,%rax'),('add','%rax,%rbx'),('lea','(%rax,%rcx,1),%rbx'),
                        ('lea','(%rcx,%rax,1),%rbx')]:
            with self.assertRaises(flow.Reject):e.effect(flow.State({'a':('frame',-8),'b':flow.const([0])},sp=-16),op,args,{})
        st=flow.State({'a':('argument','di',0)},arguments={'di':(8,flow.ROOT)})
        e.effect(st,'add','$0x8,%rax',{});self.assertEqual(st.regs['a'],('argument','di',8))
        with self.assertRaises(flow.Reject):e.effect(st,'add','$0x1,%rax',{})

    def test_partial_private_pointer_values_do_not_escape(self):
        e=flow.Engine(Fixture())
        for op,args in [('mov','$0x0,%al'),('lea','(%rax),%ebx'),('mov','%eax,%ebx')]:
            with self.assertRaises(flow.Reject):e.effect(flow.State({'a':('frame',-8)},sp=-16),op,args,{})
    def test_public_normal_outgoing_rsi_is_not_forgotten(self):
        for unsafe in [False,True]:
            f=Fixture();f.info[0x100]['rows']=[(pc,'mov','0x18(%rsp),%r12') if args=='0x8(%rsp),%r12'
                else (pc,'add','$0x20,%rsp') if args=='%rsp,%rsi' else (pc,op,args)
                for pc,op,args in f.info[0x100]['rows']]
            rows=[(0x400,'mov','$0x5000,%edx'),(0x405,'call','100'),
                  (0x40a,'mov','%rsi,%rax') if unsafe else (0x40a,'xor','%esi,%esi'),(0x40d,'ret','')]
            f.eh[0x400]={'kind':'fixture-none','rows':[]}
            with patch.object(flow.frames,'cfi',side_effect=lambda side,info:f.tables.get(info['start'])):
                p=f.wide_literal_use(0,rows,0x400,0x40e)
            if unsafe:self.assertIsNone(p)
            else:self.assertIsNotNone(p)
    def test_use_site_full_payload_no_global_width_poison(self):
        f=Fixture();f.func_start={};f.objects=[];f.obj_starts=[];f.exact={};f.literal_proofs=[]
        payload='rb\0'.encode('utf-32le')
        f.image.section_at=lambda a:SimpleNamespace(name='.rodata',addr=0x5000,size=len(payload),flags=2)
        f.image.read=lambda a,n:payload[a-0x5000:a-0x5000+n]
        proof={'load':0x400,'call':0x405,'literal':0x5000,'width':4,'model':'original-saved-wide-argument-v1'}
        token=f.name_at(0x5000,'mov',True,proof);self.assertEqual(token,'lit:w4:n2:7200000062000000')
        self.assertTrue(f.name_at(0x5000,'mov',True).startswith('unverified-data:'))
        payload='rx\0'.encode('utf-32le');self.assertNotEqual(token,f.name_at(0x5000,'mov',True,proof))
        payload='rb'.encode('utf-32le');self.assertTrue(f.name_at(0x5000,'mov',True,proof).startswith('unverified-data:'))
    def test_exact_gnu_import_identity_and_r12_only_contract(self):
        def make(version='GLIBCXX_3.4',library='libstdc++.so.6',symbol=flow.DESTROY):
            strings=b'\0'+library.encode()+b'\0'+version.encode()+b'\0'
            ver=struct.pack('<H',2);need=struct.pack('<HHIII',1,1,1,16,0)+struct.pack('<IHHII',0,0,2,len(library)+2,0)
            parts={};blob=b''
            for name,data in [('.gnu.version',ver),('.gnu.version_r',need),('.dynstr',strings)]:
                parts[name]=SimpleNamespace(offset=len(blob),size=len(data));blob+=data
            image=SimpleNamespace(data=blob,section=lambda name:parts[name],
                dynsyms=[SimpleNamespace(name=symbol,defined=False,bind=1,type=2,index=0)])
            return flow.Engine(SimpleNamespace(image=image))
        self.assertEqual(make().old_gnu_identity(flow.DESTROY)['version'],'GLIBCXX_3.4')
        for e in [make(version='GLIBCXX_3.4.1'),make(library='other.so'),make(symbol=flow.DESTROY+'bad')]:
            with self.assertRaises(flow.Reject):e.old_gnu_identity(flow.DESTROY)
        e=make();e.side.image.dynsyms[0].type=1
        with self.assertRaises(flow.Reject):e.old_gnu_identity(flow.DESTROY)
        for extra in ['si','13','d']:
            with self.assertRaises(flow.Reject):make().standard(flow.State({'12':flow.RAW,extra:flow.RAW}),flow.DESTROY)

    def test_call_clobbers_identity_as_well_as_value(self):
        e=flow.Engine(Fixture())
        st=flow.State({'12':flow.RAW,'di':flow.ROOT,'a':('entry','b')},ids={'a':'b','12':'12'})
        e.standard(st,'_ZNSsD1Ev');self.assertNotIn('a',st.ids);self.assertEqual(st.regs['a'],flow.POISON)

if __name__=='__main__':unittest.main()
