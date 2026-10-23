"""Small concrete bitvector/frame oracle, not a game/runtime emulator."""
import unittest
from types import SimpleNamespace
import objdiff
from objdiff_saved_argument import Engine,State,RAW,ROOT,Reject,const,values

class EffectsTest(unittest.TestCase):
    def setUp(self):
        image=SimpleNamespace(section_at=lambda a:None)
        self.e=Engine(SimpleNamespace(register=objdiff.OriginalSide.register,
                                      padding=objdiff.OriginalSide.padding,image=image))
    def effect(self,st,op,args):self.e.effect(st,op,args,{'12':RAW,'b':None})
    def test_mov_bitvector_grid(self):
        regs={8:'%al',16:'%ax',32:'%eax',64:'%rax'}
        for bits,dest in regs.items():
            for old in [0,1,0x123456789abcdef0,0xffffffffffffffff]:
                for new in [0,1,0x80,0xffff,0x80000000,0xffffffffffffffff]:
                    st=State({'a':const([old])});self.effect(st,'mov',f'${hex(new)},{dest}')
                    mask=(1<<bits)-1
                    expected=(old&~mask)|(new&mask) if bits<32 else new&mask
                    self.assertEqual(values(st.regs['a']),(expected,),(bits,old,new))
    def test_partial_register_copy_grid(self):
        regs={8:('%al','%bl'),16:('%ax','%bx'),32:('%eax','%ebx'),64:('%rax','%rbx')}
        for bits,(src,dst) in regs.items():
            for source in [0,0x123456789abcdef0,0xffffffffffffffff]:
                for old in [0,0x7654321089abcdef]:
                    st=State({'a':const([source]),'b':const([old])});self.effect(st,'mov',src+','+dst)
                    mask=(1<<bits)-1
                    expected=(old&~mask)|(source&mask) if bits<32 else source&mask
                    self.assertEqual(values(st.regs['b']),(expected,))
    def test_shift_bitvector_grid(self):
        for bits,reg in [(8,'%al'),(16,'%ax'),(32,'%eax'),(64,'%rax')]:
            mask=(1<<bits)-1
            for x in [0,1,1<<(bits-1),mask]:
                for n in [0,1,7,8,16,31,32,63,64]:
                    for op in ['shl','shr','sar']:
                        st=State({'a':const([x])});self.effect(st,op,f'${hex(n)},{reg}')
                        count=n&(63 if bits==64 else 31)
                        signed=x-(1<<bits) if x&(1<<(bits-1)) else x
                        expected=((x<<count) if op=='shl' else (x>>count) if op=='shr' else (signed>>count))&mask
                        self.assertEqual(values(st.regs['a']),(expected,),(bits,x,n,op))
    def test_pointer_width_and_high_byte_failclosed(self):
        for origin in [ROOT,('frame',-16)]:
            for src,dest in [('%eax','%ebx'),('%ax','%bx'),('%al','%bl')]:
                st=State({'a':origin})
                if origin[0]=='frame':
                    with self.assertRaises(Reject):self.effect(st,'mov',src+','+dest)
                    continue
                self.effect(st,'mov',src+','+dest)
                self.assertNotIn(st.regs.get('b'),[ROOT,('frame',-16)])
        for arg in ['%ah,%bl','%al,%bh','%ch,%dl','%dh,%al']:
            with self.assertRaises(Reject):self.effect(State(),'mov',arg)
    def test_physical_stack_taint_survives_pop_reallocation(self):
        st=State({'12':RAW},ids={'12':'12'})
        for op,arg in [('push','%r12'),('xor','%r12d,%r12d'),('pop','%r12'),('sub','$0x8,%rsp'),('mov','(%rsp),%rax')]:
            self.effect(st,op,arg)
        self.assertEqual(st.regs['a'],RAW)
        self.assertTrue(st.private())
    def test_mov_restore_keeps_stale_taint(self):
        st=State({'12':RAW},ids={'12':'12'})
        for op,arg in [('push','%r12'),('xor','%r12d,%r12d'),('mov','(%rsp),%r12'),('mov','(%rsp),%rax')]:
            self.effect(st,op,arg)
        self.assertEqual(st.regs['a'],RAW)
    def test_stale_raw_overwrite_full_only(self):
        for n,op in [(1,'movb'),(2,'movw'),(4,'movl'),(8,'movq')]:
            st=State({'12':RAW},ids={'12':'12'})
            self.effect(st,'push','%r12');self.effect(st,'pop','%r12');self.effect(st,'sub','$0x8,%rsp')
            if n<8:
                with self.assertRaises(Reject):self.effect(st,op,'$0x0,(%rsp)')
            else:
                self.effect(st,op,'$0x0,(%rsp)');self.effect(st,'mov','(%rsp),%rax')
                self.assertEqual(values(st.regs['a']),(0,))
    def test_stack_constants_little_endian(self):
        st=State(sp=-16)
        self.effect(st,'movq','$0x8877665544332211,(%rsp)')
        for pos in range(8):
            st.regs['a']=const([0])
            self.effect(st,'mov',f'{hex(pos)}(%rsp),%al')
            self.assertEqual(values(st.regs['a']),(0x11*(pos+1),))
    def test_frame_escape_and_return_address_overlap(self):
        with self.assertRaises(Reject):self.effect(State({'a':('frame',-16),'b':ROOT},sp=-32),'mov','%rax,(%rbx)')
        for offset in [-1,-7,-129]:
            with self.assertRaises(Reject):self.effect(State({'12':RAW},ids={'12':'12'}),'mov',f'%r12,{hex(offset)}(%rsp)')

if __name__=='__main__':unittest.main()
