"""Fixed-format proof tests: no compiler, game execution or output-init facts."""
import hashlib
import struct
import unittest
from types import SimpleNamespace as NS
from unittest.mock import patch
import objdiff_eh
import objdiff_scanf_literal as fixed
import test_objdiff_wcslen_append as paired_tests

START = 0x1000
TARGET = 0x5000
ADDRESS = 0xff0000


def fixture(size=24, offset=8):
    side = paired_tests.PairedTest().side(fixed.FORMAT)
    image = side.image
    image.dynsyms = [NS(name='swscanf', defined=False, bind=1, type=2, index=1)]
    image.symbols = [NS(name='synthetic', defined=True, bind=1, type=2, value=START, size=34)]
    image.plt = {TARGET: 'swscanf'}
    image.relocs = {0x7000: NS(type=7, symbol='swscanf', addend=0)}
    body = bytes.fromhex('4883ec18488b3fb e0000ff00488d54240831c0e8e83f0000488b4424084883c418c3'.replace(' ',''))
    body = bytearray(body); body[3] = body[32] = size; body[16] = body[28] = offset
    for name, addr, at, raw in [('.text', START, 0x2000, bytes(body)),
                              ('.plt', TARGET, 0x3000, b'\xff\x25'+struct.pack('<i',0x7000-TARGET-6)+b'\0'*10)]:
        image.data += bytes(at-len(image.data)) + raw
        image.sections[name] = NS(name=name, addr=addr, offset=at, size=len(raw), flags=6)
        image.segments.append((1,5,at,addr,0,len(raw),len(raw),0x1000))
    image.sha256 = hashlib.sha256(image.data).hexdigest()
    alloc = [image.sections[n] for n in ('.text','.plt','.rodata')]
    image.section_at = lambda a: next((s for s in alloc if s.addr<=a<s.addr+s.size),None)
    def read(a,n):
        s=image.section_at(a)
        if s is None or a+n>s.addr+s.size: raise ValueError('outside fixture')
        return image.data[s.offset+a-s.addr:s.offset+a-s.addr+n]
    image.read = read
    args=[f'$0x{size:x},%rsp','(%rdi),%rdi',f'$0x{ADDRESS:x},%esi',
          f'0x{offset:x}(%rsp),%rdx','%eax,%eax',f'{TARGET:x} <swscanf@plt>',
          f'0x{offset:x}(%rsp),%rax',f'$0x{size:x},%rsp','']
    rows=[[START+pc,op,arg] for pc,op,arg in zip(fixed.OFFSETS,
          ('sub','mov','mov','lea','xor','call','mov','add','ret'),args)]
    table={'start':START,'end':START+34,'cie':0,
           'rows':[(START,{'CFA':'rsp+8','ra':'c-8'}),
                   (START+4,{'CFA':f'rsp+{size+8}','ra':'c-8'}),
                   (START+33,{'CFA':'rsp+8','ra':'c-8'})]}
    return side,rows,table


def certify(f=None, public=False):
    side,rows,table=f or fixture()
    with patch.object(fixed.frames,'cfi',return_value=table):
        if public: return side.wide_literal_use(2,rows,START,START+34)
        return fixed.certify(side,2,rows,START,START+34)


class FixedFormatTest(unittest.TestCase):
    def test_positive_and_no_initialization_facts(self):
        for size in (24,40,56,72,88,104,120):
            for offset in range(8,size-7,8):
                with self.subTest(size=size,offset=offset):
                    p=certify(fixture(size,offset),True)
                    self.assertIsNotNone(p)
                    self.assertEqual(p['output']['initialization'],'not-proved')
                    self.assertEqual(p['output']['conversion_success'],'not-proved')
                    self.assertEqual(p['normal']['returns'],[START+33])
                    self.assertEqual(p['normal']['kills'],[])
                    self.assertEqual(p['payload_size'],20)

    def test_full_original_payload_and_import(self):
        for old,new in [(b'GLIBC_2.2.5',b'GLIBC_9.9.9'),(b'libc.so.6',b'libx.so.6'),
                        (fixed.FORMAT,'%lln\0'.encode('utf-32le')),
                        (fixed.FORMAT,'%lldX'.encode('utf-32le'))]:
            f=fixture();im=f[0].image;im.data=im.data.replace(old,new)
            im.sha256=hashlib.sha256(im.data).hexdigest()
            self.assertIsNone(certify(f,True))
        for name in ('__isoc99_swscanf','sscanf','fwscanf','swscanf@other'):
            f=fixture();f[0].image.plt[TARGET]=name;self.assertIsNone(certify(f,True))
        f=fixture();f[0].image.dynsyms*=2;self.assertIsNone(certify(f))
        for field,value in [('type',1),('symbol','sscanf'),('addend',1)]:
            f=fixture();setattr(f[0].image.relocs[0x7000],field,value);self.assertIsNone(certify(f))

    def test_duplicate_name_identity_and_warm_reuse(self):
        for defined,bind,typ in [(False,2,2),(True,1,2),(False,1,1),(False,0,0)]:
            f=fixture();self.assertIsNotNone(certify(f));im=f[0].image
            im.dynsyms.append(NS(name='swscanf',defined=defined,bind=bind,type=typ,index=2,
                                value=0,size=0))
            self.assertIsNone(certify(f,True));im.dynsyms.pop();self.assertIsNotNone(certify(f))
        f=fixture();self.assertIsNotNone(certify(f));im=f[0].image;old=im.data
        im.data=im.data.replace(b'GLIBC_2.2.5',b'GLIBC_9.9.9')
        self.assertIsNone(certify(f))
        im.sha256=hashlib.sha256(im.data).hexdigest();self.assertIsNone(certify(f))
        im.data=old;im.sha256=hashlib.sha256(old).hexdigest();self.assertIsNotNone(certify(f))

    def test_instruction_and_alias_mutations_public(self):
        edits=[(0,'sub','$0x18,%esp'),(0,'sub','$0x20,%rsp'),
               (1,'mov','%rsi,%rdi'),(2,'mov','$0xff0000,%si'),
               (2,'mov','$0x100ff0000,%rsi'),(3,'lea','0x18(%rsp),%rdx'),
               (3,'lea','0x8(%rsp),%edx'),(3,'mov','%rsi,%rdx'),
               (4,'xor','%al,%al'),(4,'mov','$0x1,%eax'),(4,'mov','%rsi,%r12'),
               (5,'call','*%rax'),(5,'call','5010 <swscanf>'),(5,'jmp','5000'),
               (6,'mov','%rsi,%rax'),(6,'mov','0x10(%rsp),%rax'),
               (6,'mov','%rsi,0x8(%rsp)'),(6,'test','%rsi,%rsi'),
               (6,'xorps','(%rsi),%xmm0'),(6,'call','5010'),
               (6,'mov','0x8(%rsp),%eax'),(7,'add','$0x18,%esp'),
               (8,'ret','$0x8'),(8,'loop','1000'),(8,'jmp','*%rsi')]
        for i,op,arg in edits:
            with self.subTest(i=i,op=op,arg=arg):
                f=fixture();f[1][i][1:]=[op,arg];self.assertIsNone(certify(f,True))
        for i in range(9):
            f=fixture();f[1].insert(i,[START+i,'nop','']);self.assertIsNone(certify(f))
        for size,offset in [(16,8),(32,8),(24,1),(24,24),(8,8)]:
            self.assertIsNone(certify(fixture(size,offset)))

    def test_body_snapshot_and_boundaries(self):
        for byte in range(34):
            f=fixture();im=f[0].image;data=bytearray(im.data);data[0x2000+byte]^=1
            im.data=bytes(data);im.sha256=hashlib.sha256(im.data).hexdigest()
            self.assertIsNone(certify(f))
        f=fixture();f[0].image.sha256='bad';self.assertIsNone(certify(f))
        f=fixture();f[0].image.symbols[0].size=33;self.assertIsNone(certify(f))
        f=fixture();f[0].func_start[START+19]='other';self.assertIsNone(certify(f))
        f=fixture();f[0].image.symbols.append(NS(defined=True,value=START+17));self.assertIsNone(certify(f))
        f=fixture();f[1][-1][0]+=1;self.assertIsNone(certify(f))

    def test_complete_readonly_mapping(self):
        for name in ('.text','.plt','.rodata'):
            f=fixture();f[0].image.sections[name].flags |= 1;self.assertIsNone(certify(f))
        for index in range(3):
            f=fixture();im=f[0].image;seg=list(im.segments[index]);seg[1]|=2;im.segments[index]=tuple(seg)
            self.assertIsNone(certify(f))
            f=fixture();f[0].image.segments.append(f[0].image.segments[index]);self.assertIsNone(certify(f))
        f=fixture();f[0].image.sections['.rodata'].size=16;self.assertIsNone(certify(f))

    def test_eh_and_cfi_are_independent(self):
        f=fixture();f[0].frames=objdiff_eh.Frames([],lsdas=[(None,START,START+34,1,0,None)])
        self.assertIsNone(certify(f,True))
        f=fixture();f[0].frames=objdiff_eh.Frames([],error='bad');self.assertIsNone(certify(f,True))
        for pc in (START,START+4,START+19,START+20,START+23,START+33):
            for rules in ({'CFA':'rsp+8','ra':'c-8'},{'CFA':'rsp+32','ra':'c-16'},
                          {'CFA':'rsp+32','ra':'c-8','rbx':'u'}):
                f=fixture();t=f[2];t['rows']=[r for r in t['rows'] if r[0]!=pc]+[(pc,rules)]
                t['rows'].sort()
                if rules=={'CFA':'rsp+8','ra':'c-8'} and pc in (START,START+33):continue
                self.assertIsNone(certify(f))
        f=fixture();self.assertIsNone(certify((f[0],f[1],None)))
        f=fixture()
        with patch.object(f[0],'_rsi_normal_dead',return_value=None):self.assertIsNone(certify(f))


if __name__ == '__main__': unittest.main()
