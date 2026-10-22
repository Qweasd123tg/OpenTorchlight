import copy
import unittest
from types import SimpleNamespace
from unittest.mock import patch
import objdiff_null_field as null
import objdiff_saved_argument as flow
from test_objdiff_saved_argument import Fixture

class NullFixture(Fixture):
    def __init__(self):
        super().__init__()
        rows=[(0x400,'push','%r13'),(0x401,'mov','%rsi,%r13'),(0x402,'push','%rbx'),
              (0x403,'mov','%rdi,%rbx'),(0x404,'sub','$0xb8,%rsp'),
              (0x405,'mov','0x78(%rsp),%rax'),(0x406,'test','%rax,%rax'),(0x407,'je','410'),
              (0x408,'add','$0xb8,%rsp'),(0x409,'pop','%rbx'),(0x40a,'pop','%r13'),(0x40b,'ret',''),
              (0x410,'mov','%r13,%rsi'),(0x411,'movq','$0x0,0x98(%rsp)'),(0x412,'lea','0x98(%rsp),%rdi'),
              (0x413,'mov','$0x5000,%edx'),(0x414,'call','100'),(0x415,'add','$0xb8,%rsp'),
              (0x416,'pop','%rbx'),(0x417,'pop','%r13'),(0x418,'ret',''),
              (0x420,'mov','%rax,%rbx'),(0x421,'lea','0x70(%rsp),%rdi'),(0x422,'call','700'),
              (0x423,'mov','%rbx,%rdi'),(0x424,'call','1001')]
        self.info[0x400]=self.body(0x400,rows);self.info[0x400]['size']=0x25
        self.eh[0x400]={'kind':'fixture-cleanup','rows':[[0x14,1,0x20,0]]}
        self.tables[0x400]={'start':0x400,'end':0x425,'cie':1,'rows':[
            (0x400,{'CFA':'rsp+8','ra':'c-8'}),(0x405,{'CFA':'rsp+208','ra':'c-8','r13':'c-16','rbx':'c-24'})]}
        dtor=[('mov','0x10(%rdi),%rax'),('movq','$0x9000,(%rdi)'),('test','%rax,%rax'),('je','70c'),
              ('mov','(%rax),%edx'),('sub','$0x1,%edx'),('test','%edx,%edx'),('mov','%edx,(%rax)'),
              ('jne','70c'),('mov','(%rdi),%rax'),('mov','0x10(%rax),%rax'),('jmp','*%rax'),('ret','')]
        destroy=[('push','%rbx'),('mov','%rdi,%rbx'),('mov','0x8(%rdi),%rdi'),('test','%rdi,%rdi'),
                 ('je','806'),('call','*%rax'),('mov','0x10(%rbx),%rdi'),('pop','%rbx'),('jmp','2000')]
        for target,body,name in [(0x700,dtor,'_ZN4Ogre9SharedPtrINS_10DataStreamEED1Ev'),
                                 (0x800,destroy,'_ZN4Ogre9SharedPtrINS_10DataStreamEE7destroyEv')]:
            self.info[target]=self.body(target,[(target+i,*r) for i,r in enumerate(body)])
            self.info[target]['names']=[name];self.eh[target]={'kind':'fixture-none','rows':[]}
        self.tables[0x700]={'start':0x700,'end':0x70d,'cie':1,'rows':[(0x700,{'CFA':'rsp+8','ra':'c-8'})]}
        self.tables[0x800]={'start':0x800,'end':0x809,'cie':1,'rows':[(0x800,{'CFA':'rsp+8','ra':'c-8'}),
            (0x801,{'CFA':'rsp+16','ra':'c-8','rbx':'c-16'}),(0x808,{'CFA':'rsp+8','ra':'c-8'})]}
        self.image.plt[0x2000]='_ZN4Ogre12NedAllocImpl12deallocBytesEPv'
        self.image.symbols=[SimpleNamespace(name='_ZTVN4Ogre9SharedPtrINS_10DataStreamEEE',value=0x8ff0,size=40)]
        self.image.section_at=lambda a:SimpleNamespace(addr=0x8ff0,size=40,flags=2) if 0x8ff0<=a<0x9018 else None
        self.image.read=lambda a,n:(0x800).to_bytes(8,'little') if (a,n)==(0x9010,8) else bytes(n)
    def _callee_body(self,image,target,max_bytes=1024):return self.info.get(target)
    def _nonobserving_callee(self,image,target):return {'fixture-pinned-deallocator':True} if target==0x2000 else None
    def change(self,pc,op,args,body=0x400):
        self.info[body]['rows']=[(a,op,args) if a==pc else (a,b,c) for a,b,c in self.info[body]['rows']]
    def check(self,public=False):
        rows=self.info[0x400]['rows']
        with patch.object(flow.frames,'cfi',side_effect=lambda side,info:self.tables.get(info['start'])):
            if public:return self.wide_literal_use(next(i for i,r in enumerate(rows) if r[0]==0x413),rows,0x400,0x425)
            return null.certify(self,rows,next(i for i,r in enumerate(rows) if r[0]==0x413),
                next(i for i,r in enumerate(rows) if r[0]==0x414),0x400,0x425,self.eh[0x400],0x420,flow.Engine(self))

class NullFieldTest(unittest.TestCase):
    def test_closed_null_path_keeps_unknown_nonnull_count(self):
        f=NullFixture();p=f.check();self.assertIsNotNone(p,getattr(f,'_null_field_error',None))
        self.assertEqual(p['conditional']['destroy']['calls'][0]['argument'],'count')
    def test_missing_wrong_partial_guard(self):
        for op,args in [('mov','0x78(%rsp),%eax'),('mov','0x80(%rsp),%rax'),('xor','%eax,%eax')]:
            f=NullFixture();f.change(0x405,op,args);self.assertIsNone(f.check())
    def test_guard_bypass_and_interior_entries(self):
        for target in ['406','407','410','413']:
            f=NullFixture();f.change(0x404,'jne',target);self.assertIsNone(f.check())
    def test_receiver_overlap_partial_store_and_output(self):
        for pc,op,args in [(0x411,'movb','$0x0,0x79(%rsp)'),(0x412,'lea','0x78(%rsp),%rdi'),
                           (0x412,'lea','0x70(%rsp),%rdi'),(0x412,'lea','0x80(%rsp),%rdi')]:
            f=NullFixture();f.change(pc,op,args);self.assertIsNone(f.check())
    def test_postguard_exception_route_cannot_reuse_normal_output(self):
        f=NullFixture();f.image.plt[0x1004]=flow.COPY
        replacements={0x410:('lea','0x98(%rsp),%rdi'),0x411:('mov','%r13,%rsi'),
            0x412:('call','1004'),0x413:('jmp','419'),0x414:('jmp','419'),
            0x415:('lea','0x98(%rsp),%rdi'),0x416:('mov','%r13,%rsi'),
            0x417:('mov','$0x5000,%edx'),0x418:('call','100')}
        for pc,(op,args) in replacements.items():f.change(pc,op,args)
        f.info[0x400]['rows'].append((0x419,'ret',''));f.info[0x400]['rows'].sort()
        f.eh[0x400]['rows']=[[0x12,1,0x15,0],[0x18,1,0x20,0]]
        rows=f.info[0x400]['rows']
        with patch.object(flow.frames,'cfi',side_effect=lambda side,info:f.tables.get(info['start'])):
            self.assertIsNone(null.certify(f,rows,next(i for i,r in enumerate(rows) if r[0]==0x417),
                next(i for i,r in enumerate(rows) if r[0]==0x418),0x400,0x425,f.eh[0x400],0x420,flow.Engine(f)))
        self.assertIn('normal return',f._null_field_error)
    def test_unsupported_control_transfer_on_bypass_only_path(self):
        cases=[('loop','410'),('loope','410'),('loopne','410'),('addr32 loop','410'),
               ('jcxz','410'),('jecxz','410'),('jrcxz','410'),('xbegin','410'),
               ('bnd','jmp 410'),('ljmp','410'),('lcall','410'),('iretq',''),
               ('sysret',''),('jmp','*%rax'),('ret','$0x8')]
        for op,args in cases:
            f=NullFixture();f.change(0x408,op,args);self.assertIsNone(f.check(public=True),(op,args))
        f=NullFixture();f.change(0x408,'nop','');f.change(0x409,'jmp','410')
        self.assertIsNone(f.check(public=True))
    def test_guard_ancestors_reject_dynamic_stack_updates(self):
        for op,args in [('pop','%rsp'),('pop','%esp'),('lock xadd','%rsp,(%rax)'),
                        ('mov','%rax,%esp'),('xchg','%rax,%rsp'),('enter','$0x10,$0x0'),('leave','')]:
            f=NullFixture()
            # Standalone frame graph fixture isolates effect classification.
            rows=[(0x100,'sub','$0x10,%rsp'),(0x101,op,args),(0x102,'nop','')]
            edges={0x100:{0x101},0x101:{0x102},0x102:set()}
            with self.assertRaises(flow.Reject):null.frame_at(f,rows,edges,0x102)
    def test_public_dynamic_stack_update_before_fresh_guard(self):
        for extra in [[(0x411,'pop','%rsp'),(0x412,'sub','$0x8,%rsp')],
                      [(0x411,'lock xadd','%rsp,(%rax)')]]:
            f=NullFixture();scale=lambda pc:0x400+4*(pc-0x400)
            rows=[]
            for pc,op,args in f.info[0x400]['rows']:
                target=f.direct_target(args)
                if op.startswith('j') and target is not None and 0x400<=target<0x425:args=f'{scale(target):x}'
                rows.append((scale(pc),op,args))
            rows=sorted(rows+extra);f.info[0x400]=f.body(0x400,rows);f.info[0x400]['size']=scale(0x425)-0x400
            f.eh[0x400]['rows']=[[b*4,n*4,p*4,a] for b,n,p,a in f.eh[0x400]['rows']]
            f.tables[0x400]['end']=scale(0x425)
            f.tables[0x400]['rows']=[(scale(pc),rules) for pc,rules in f.tables[0x400]['rows']]
            with patch.object(flow.frames,'cfi',side_effect=lambda side,info:f.tables.get(info['start'])):
                self.assertIsNone(f.wide_literal_use(next(i for i,r in enumerate(rows) if r[0]==scale(0x413)),
                    rows,0x400,scale(0x425)))
            self.assertIn('stack',f._null_field_error)
    def test_dynamic_stack_writers_reject_on_bypass_only_path(self):
        for op,args in [('pop','%rsp'),('pop','%esp'),('lock xadd','%rsp,(%rax)'),
                        ('lock xadd','%spl,(%rax)'),('mov','%rax,%rsp'),('mov','%eax,%esp'),
                        ('xchg','%rax,%rsp'),('lea','0x8(%rax),%rsp'),('add','%rax,%rsp')]:
            f=NullFixture();f.change(0x408,op,args);self.assertIsNone(f.check(public=True),(op,args))
    def test_fixed_prologue_has_no_reentry(self):
        for target in ['400','401','403','404']:
            f=NullFixture();f.change(0x408,'jmp',target);self.assertIsNone(f.check())
    def test_unknown_postguard_or_root_clobber(self):
        for pc,op,args in [(0x410,'cpuid',''),(0x410,'call','999'),(0x403,'cpuid',''),
                           (0x410,'add','$0x8,%rsp')]:
            f=NullFixture();f.change(pc,op,args);self.assertIsNone(f.check())
    def test_type_layout_vtable_and_callback_are_bound(self):
        f=NullFixture();f.info[0x700]['names']=['unrelated'];self.assertIsNone(f.check())
        f=NullFixture();f.image.symbols=[];self.assertIsNone(f.check())
        f=NullFixture();f.change(0x702,'test','%rsi,%rsi',0x700);self.assertIsNone(f.check())
        f=NullFixture();f.change(0x802,'mov','0x10(%rdi),%rdi',0x800);self.assertIsNone(f.check())
        f=NullFixture();f.change(0x804,'jne','806',0x800);self.assertIsNone(f.check())
    def test_public_entry_conditional_cleanup_and_warm_mutations(self):
        f=NullFixture();p=f.check(public=True);self.assertIsNotNone(p,getattr(f,'_null_field_error',None))
        self.assertEqual(p['cleanup'][0]['kind'],'original-dominating-null-field-cleanup-v1')
        for pc,op,args in [(0x407,'jne','410'),(0x412,'lea','0x78(%rsp),%rdi'),
                           (0x420,'movq','$0x1,0x78(%rsp)'),(0x420,'movb','$0x1,0x7a(%rsp)'),
                           (0x420,'call','2000')]:
            bad=NullFixture();self.assertIsNotNone(bad.check(public=True));bad.change(pc,op,args)
            self.assertIsNone(bad.check(public=True),(pc,op,args))
    def test_tail_restore_and_ordinary_call_cfi(self):
        for pc,op,args in [(0x807,'nop',''),(0x807,'add','$0x8,%rsp'),(0x808,'jmp','*%rax'),
                           (0x801,'mov','%rdi,%rsp'),(0x801,'mov','%rdi,%r12'),
                           (0x802,'mov','0x8(%edi),%rdi')]:
            f=NullFixture();f.change(pc,op,args,0x800);self.assertIsNone(f.check())
        f=NullFixture();f.tables[0x800]['rows'][1][1]['rbx']='u';f.change(0x807,'call','2000',0x800)
        self.assertIsNone(f.check())
    def test_conditional_proof_never_seeds_unconditional_cache(self):
        f=NullFixture();self.assertIsNotNone(f.check());self.assertIsNone(f._nonobserving_callee(f.image,0x700))
        f.change(0x407,'jne','410');self.assertIsNone(f.check())

if __name__=='__main__':unittest.main()
