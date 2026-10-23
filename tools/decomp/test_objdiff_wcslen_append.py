"""Fail-closed original-only paired consumer and dynamic identity checks."""
import hashlib
import struct
import unittest
from pathlib import Path
from types import SimpleNamespace as NS
from unittest.mock import patch
import objdiff
import objdiff_eh
import objdiff_wcslen_append as pair


def image(payload=None):
    payload = payload if payload is not None else '.runicgames/Torchlight/\0'.encode('utf-32le')
    strings = b'\0libc.so.6\0GLIBC_2.2.5\0libstdc++.so.6\0GLIBCXX_3.4\0'
    idx = lambda x: strings.index(x.encode())
    needs = (struct.pack('<HHIII', 1, 1, idx('libc.so.6'), 16, 32)
             + struct.pack('<IHHII', 0, 0, 3, idx('GLIBC_2.2.5'), 0)
             + struct.pack('<HHIII', 1, 1, idx('libstdc++.so.6'), 16, 0)
             + struct.pack('<IHHII', 0, 0, 2, idx('GLIBCXX_3.4'), 0))
    data = b''; sections = {}
    for name, raw in [('.dynstr', strings), ('.gnu.version', struct.pack('<HHH', 0, 3, 2)),
                      ('.gnu.version_r', needs), ('.rodata', payload)]:
        if name == '.rodata':data += bytes(0x1000 - len(data))
        sections[name] = NS(name=name, offset=len(data), size=len(raw), addr=0xff0000, flags=2)
        data += raw
    sec = sections['.rodata']
    syms = [NS(name=n, defined=False, bind=1, type=2, index=i)
            for i, n in enumerate(('wcslen', pair.APPEND), 1)]
    return NS(data=data, sha256=hashlib.sha256(data).hexdigest(), dynsyms=syms, symbols=[],
              section=lambda name: sections[name], sections=sections,
              segments=[(1,4,sec.offset,sec.addr,0,sec.size,sec.size,0x1000)],
              section_at=lambda a: sec if sec.addr <= a < sec.addr + sec.size else None,
              read=lambda a,n: data[sec.offset+a-sec.addr:sec.offset+a-sec.addr+n],
              plt={0x500: 'wcslen', 0x600: pair.APPEND, 0x700: objdiff.OriginalSide.WSTRING_DTOR,
                   0x800: '_Unwind_Resume'})


class PairedTest(unittest.TestCase):
    def side(self, payload=None):
        s = objdiff.OriginalSide.__new__(objdiff.OriginalSide)
        s.image=image(payload);s.func_start={};s.frames=objdiff_eh.Frames([])
        s.obj_starts=[];s.objects=[];s.exact={};s.low=0x100;s.high=0x1000000
        return s

    def rows(self):
        return [[0x100,'mov','$0xff0000,%edi'], [0x105,'call','500 <wcslen>'],
                [0x10a,'mov','$0xff0000,%esi'], [0x10f,'mov','%rax,%rdx'],
                [0x112,'mov','%rbx,%rdi'], [0x115,'call','600 <append>'],
                [0x11a,'mov','%rbx,%rax'], [0x11d,'ret','']]

    def proof(self,s=None,r=None,k=0):
        return pair.certify(s or self.side(),k,r or self.rows(),0x100,0x200)

    def test_both_operands_complete_payload_and_normalization(self):
        s=self.side();r=self.rows()
        for k in (0,2):
            p=self.proof(s,r,k);self.assertEqual(p['payload_size'],96)
            self.assertEqual(p['character_count'],23);self.assertEqual(p['paired_loads'],[0x100,0x10a])
        normalized=s.normalize(r,0x100,0x200)
        self.assertIn('lit:w4:n23:',normalized[0]);self.assertIn('lit:w4:n23:',normalized[2])
        self.assertEqual(len(s.literal_proofs),2)
        self.assertEqual(s.literal_proofs[0]['size'],96)

    def test_exact_import_versions(self):
        s=self.side()
        self.assertEqual(pair.import_identity(s.image,'wcslen')['version'],'GLIBC_2.2.5')
        for old,new in [(b'GLIBC_2.2.5',b'GLIBC_9.9.9'),(b'GLIBCXX_3.4',b'GLIBCXX_9.9'),
                        (b'libc.so.6',b'libx.so.6'),(b'libstdc++.so.6',b'libunknowns.6')]:
            with self.subTest(old=old):
                s=self.side();s.image.data=s.image.data.replace(old,new)
                s.image.sha256=hashlib.sha256(s.image.data).hexdigest()
                self.assertIsNone(self.proof(s))
        s=self.side();s.image.dynsyms.append(s.image.dynsyms[0]);self.assertIsNone(self.proof(s))

    def test_same_name_dynsym_aliases_reject_public_paired_use(self):
        aliases = [(False, 2, 2),  # weak FUNC
                   (False, 1, 1),  # global OBJECT
                   (True, 1, 2),   # defined global FUNC
                   (False, 0, 0),  # local NOTYPE
                   (False, 1, 2)]  # another eligible global FUNC
        for name, version in [('wcslen', 3), (pair.APPEND, 2)]:
            for defined, bind, typ in aliases:
                for alias_version in (version, 5 - version):
                    for prepend in (False, True):
                        with self.subTest(name=name, defined=defined, bind=bind,
                                          typ=typ, version=alias_version, prepend=prepend):
                            s = self.side(); r = self.rows(); im = s.image
                            # A distinct dynsym index with its own same/conflicting
                            # version entry; keep the payload and existing entries intact.
                            versions = im.sections['.gnu.version']
                            versions.offset = len(im.data); versions.size = 8
                            im.data += struct.pack('<HHHH', 0, 3, 2, alias_version)
                            im.sha256 = hashlib.sha256(im.data).hexdigest()
                            valid = [s.wide_literal_use(k, r, 0x100, 0x200) for k in (0, 2)]
                            self.assertTrue(all(p is not None for p in valid))
                            alias = NS(name=name, defined=defined, bind=bind, type=typ,
                                       index=3, value=0, size=0)
                            im.dynsyms.insert(0 if prepend else len(im.dynsyms), alias)
                            for k in (0, 2):
                                self.assertIsNone(s.wide_literal_use(k, r, 0x100, 0x200))
                            self.assertIsNone(pair.import_identity(im, name))
                            normalized = s.normalize(r, 0x100, 0x200)
                            self.assertFalse(s.literal_proofs)
                            self.assertNotIn('lit:w4:', normalized[0])
                            self.assertNotIn('lit:w4:', normalized[2])
                            im.dynsyms.remove(alias)
                            self.assertEqual(valid, [s.wide_literal_use(k, r, 0x100, 0x200)
                                                     for k in (0, 2)])

    def test_single_import_eligibility_and_expected_identity_unchanged(self):
        for name, expected in pair.CONTRACTS.items():
            for field, value in [('defined', True), ('bind', 2), ('type', 1)]:
                s = self.side(); symbol = next(x for x in s.image.dynsyms if x.name == name)
                setattr(symbol, field, value)
                self.assertIsNone(pair.import_identity(s.image, name))
            s = self.side()
            identity = {'symbol': name, 'soname': expected[0], 'version': expected[1],
                        'evidence': 'original dynamic version tables; explicit nonretaining ABI contract'}
            self.assertEqual(pair.import_identity(s.image, name), identity)
            self.assertEqual(pair.import_identity(s.image, name, expected), identity)
            self.assertIsNone(pair.import_identity(s.image, name, ('other.so', expected[1])))
        s = self.side(); s.image.dynsyms[0].name = 'swscanf'
        self.assertIsNone(pair.import_identity(s.image, 'swscanf'))
        self.assertEqual(pair.import_identity(s.image, 'swscanf', ('libc.so.6', 'GLIBC_2.2.5')),
                         {'symbol': 'swscanf', 'soname': 'libc.so.6', 'version': 'GLIBC_2.2.5',
                          'evidence': 'original dynamic version tables; explicit nonretaining ABI contract'})

    def test_mutations_reject_both_operands(self):
        edits=[(0,'mov','$0xff0000,%di'),(0,'mov','$0x100ff0000,%edi'),
               (2,'mov','$0xff0004,%esi'),(2,'mov','%edi,%esi'),
               (3,'movl','%rax,%rdx'),(3,'mov','%eax,%edx'),(3,'mov','%rbx,%rdx'),(3,'add','$0x1,%rdx'),
               (3,'call','500 <wcslen>'),(3,'mov','%rsi,%r12'),(3,'mov','%rsi,(%rbx)'),
               (4,'mov','%rdi,%rdi'),(4,'mov','%rsi,%rdi'),(4,'mov','%rax,%rdi'),
               (4,'mov','%rdx,%rdi'),(4,'mov','%rsp,%rdi'),(4,'mov','%ebx,%edi'),
               (5,'jmp','600 <append>'),(5,'call','*%rax'),(1,'call','501 <other>')]
        for i,op,args in edits:
            for k in (0,2):
                with self.subTest(i=i,args=args,k=k):
                    r=self.rows();r[i][1:]=[op,args];self.assertIsNone(self.proof(r=r,k=k))
        for name in [pair.APPEND+'x','_ZNSs6appendEPKcm','_ZNSbIwSt11char_traitsIwESaIwEE6appendEPKw']:
            s=self.side();s.image.plt[0x600]=name;self.assertIsNone(self.proof(s))

    def test_no_interior_entries(self):
        for target in (0x105,0x10a,0x10f,0x112,0x115):
            s=self.side();s.func_start[target]='secondary';self.assertIsNone(self.proof(s))
            for op in ('jmp','je','call'):
                r=self.rows()+[[0x130,op,f'{target:x} <interior>']];self.assertIsNone(self.proof(r=r))
            s=self.side()
            with patch.object(s,'_literal_eh',return_value={'kind':'gcc447-cleanup-v1','rows':[[0,5,target-0x100,0]]}):
                self.assertIsNone(self.proof(s))

    def test_unknown_prefix_transfer_rejected(self):
        for op,args in [('loop','115 <append>'),('xbegin','115 <append>'),
                        ('jmp','*%rax'),('call','*%rax'),('notrack jmp','*%rax'),
                        ('syscall',''),('iretq','')]:
            s=self.side();r=[[0xfb,op,args]]+self.rows()
            for k in (1,3):
                self.assertIsNone(pair.certify(s,k,r,0xfb,0x200))

    def test_payload_and_identity_fail_closed(self):
        for raw in [b'',b'A\0\0',b'A\0\0\0']:
            self.assertIsNone(self.proof(self.side(raw)))
        s=self.side();s.image.sha256='bad';self.assertIsNone(self.proof(s))
        s=self.side();s.image.sections['.rodata'].flags=3;self.assertIsNone(self.proof(s))
        a=self.proof(self.side('AX\0'.encode('utf-32le')))
        b=self.proof(self.side('AY\0'.encode('utf-32le')))
        self.assertNotEqual(a['payload_sha256'],b['payload_sha256'])
        self.assertEqual(self.proof(self.side(b'\0'*4))['character_count'],0)

    def test_normal_and_eh_alias_observation(self):
        for op,args in [('mov','%rsi,%rax'),('mov','%rsi,(%rbx)'),('cmp','%rsi,%rax'),('call','900 <unknown>')]:
            r=self.rows();r[6][1:]=[op,args];self.assertIsNone(self.proof(r=r))
        for bad in (False,True):
            s=self.side();r=self.rows()+[[0x140,'mov','%rbx,%rdi'],[0x143,'call','700 <dtor>'],
                                      [0x148,'mov','%r12,%rdi'],[0x14b,'call','800 <resume>']]
            if bad:r[8][1:]=['mov','%rsi,%rdi']
            with patch.object(s,'_literal_eh',return_value={'kind':'gcc447-cleanup-v1','rows':[[0x15,5,0x40,0]]}):
                self.assertEqual(self.proof(s,r) is None,bad)

    def test_helper_changes_invalidate_normalization_cache(self):
        read = Path.read_bytes
        before = objdiff._norm_key()
        def changed(path):
            raw = read(path)
            return raw + b'\n# changed helper' if path.name == 'objdiff_wcslen_append.py' else raw
        with patch.object(Path, 'read_bytes', changed):
            self.assertNotEqual(before, objdiff._norm_key())

    def test_loaded_payload_permissions_and_secondary_symbol(self):
        for change in ('missing','write','truncated','different-mapping','overlap-page'):
            s=self.side();seg=list(s.image.segments[0])
            if change=='missing':s.image.segments=[]
            elif change=='overlap-page':s.image.segments.append((1,6,0,0xff0000,0,1,1,4096))
            else:
                if change=='write':seg[1]=6
                if change=='truncated':seg[5]=92
                if change=='different-mapping':seg[2]=0
                s.image.segments=[tuple(seg)]
            self.assertIsNone(self.proof(s))
        s=self.side();s.image.symbols.append(NS(defined=True,value=0x10f,type=0))
        self.assertIsNone(self.proof(s))

    def test_ported_mapping_guard_edges(self):
        s=self.side();self.assertTrue(pair.immutable_loaded_range(s,0xff0000,96))
        base=list(s.image.segments[0])
        for index,value in [(2,-1),(5,-1),(6,95),(2,len(s.image.data)),
                            (2,1),(1,6),(5,92),(1,0)]:
            with self.subTest(index=index,value=value):
                seg=base[:];seg[index]=value;s.image.segments=[tuple(seg)]
                self.assertFalse(pair.immutable_loaded_range(s,0xff0000,96))
        s=self.side()
        for address,size in [(0xfeffff,96),(0xff0000,0),(0xff0000,100)]:
            self.assertFalse(pair.immutable_loaded_range(s,address,size))
        self.assertFalse(pair.immutable_loaded_range(s,0xff0000,96,executable=True))

    def test_partial_readonly_loader_page_alias_rejected(self):
        for delta in (4, 128, 4095):
            for flags in (4,6):
                s=self.side()
                # Valid congruence, different file page; extend backing bytes so
                # rejection is specifically overlap, not an out-of-file range.
                s.image.data += bytes(0x2000)
                s.image.sha256=hashlib.sha256(s.image.data).hexdigest()
                s.image.segments.append((1,flags,0x2000+delta,0xff0000+delta,0,1,1,4096))
                self.assertIsNone(self.proof(s))

    def test_same_address_unproved_and_wider_access_unchanged(self):
        s=self.side();s.normalize(self.rows(),0x100,0x200)
        self.assertIn('unverified-data:',s.name_at(0xff0000,'mov',True))
        before=self.side().name_at(0xff0000,'movq',False)
        self.assertEqual(before,s.name_at(0xff0000,'movq',False))

if __name__=='__main__':unittest.main()
