"""Offline exact-identity guards for the reviewed Level Quadtree context."""
from pathlib import Path
from tempfile import TemporaryDirectory
from types import SimpleNamespace
from unittest import TestCase, main
import copy
import sys
sys.path.insert(0, str(Path(__file__).resolve().parent))
from llm_context import ContextIndex
from test_llm_context import FakeImage, section, function, object_symbol

ORIGINAL = '91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b'
FN = '_ZN6CLevel6updateEPN4Ogre6CameraERKNS0_7Vector3EffP7CPlayer'
RAW = '_ZZ' + FN[2:] + 'E11UpdateTimer'
READABLE = 'CLevel::update(Ogre::Camera*, Ogre::Vector3 const&, float, float, CPlayer*)'

class QuadtreeContextTests(TestCase):
    def setUp(self):
        self.tmp = TemporaryDirectory(dir=Path(__file__).resolve().parents[2] / 'build-decomp')
        self.addCleanup(self.tmp.cleanup)
        self.root=Path(self.tmp.name)
        include=self.root/'decomp/include';include.mkdir(parents=True)
        src=self.root/'decomp/src';src.mkdir()
        self.header=include/'Quadtree.h'
        self.header.write_bytes((Path(__file__).resolve().parents[2]/'decomp/include/Quadtree.h').read_bytes())
        (include/'Level.h').write_text('class CLevel { public: void update(); };')
        self.db={'original_elf_sha256':ORIGINAL,'tus':[{'id':0,'name':'level.cpp','kind':'game'}],'functions':{},'globals':[]}
        self.target=function(0x95c7f0,'CLevel','update',tu=0,size=376,names=[FN]);self.target.update(mangled=FN,demangled=READABLE)
        self.image=FakeImage(section('.data',0x14210b4,bytes.fromhex('0000c842'),flags=3))
        self.image.sha256=ORIGINAL

    def index(self, db=None, image=None):
        return ContextIndex(root=self.root,db=db or self.db,image=image or self.image,headers={'CLevel':'Level.h'})

    def method(self, method):
        sort=method=='sort';address,size=(0x9689b0,905) if sort else (0x967af0,1586)
        name=('_ZN13CQuadtreeNodeIjE4sortERKN4Ogre7Vector3ES4_bRSt6vectorIjSaIjEE' if sort else '_ZN13CQuadtreeNodeIjE7addDataEjRKN4Ogre7Vector3ES4_f')
        params=('Ogre::Vector3 const&, Ogre::Vector3 const&, bool, std::vector<unsigned int, std::allocator<unsigned int> >&' if sort else 'unsigned int, Ogre::Vector3 const&, Ogre::Vector3 const&, float')
        f=function(address,'CQuadtreeNode<unsigned int>',method,tu=0,size=size,kind='inline_or_template',bind=['weak'],names=[name],params=params);f['mangled']=name
        symbol=SimpleNamespace(name=name,value=address,size=size,type=2,bind=2,defined=True)
        return f,symbol

    def test_two_exact_template_declarations(self):
        for method in ('sort','addData'):
            f,s=self.method(method);self.db['functions']={f['address']:f};self.image.symbols=[s]
            r=self.index().build(self.target,'95c7f0: call '+f['address'])
            r.require_complete();self.assertEqual(r.headers,('Quadtree.h',));self.assertIn('No specialization or prototype synthesized',r.text)

    def test_template_rejects_identity_or_header_changes(self):
        for method in ('sort','addData'):
            for change in ('address','size','kind','bind','params','cv','mangled','names','qualified','scope','missing_elf','elf_size','elf_bind'):
                with self.subTest(method=method,change=change):
                    f,s=self.method(method)
                    if change=='missing_elf': symbols=[]
                    else:
                        symbols=[s]
                        if change=='elf_size':s.size+=1
                        elif change=='elf_bind':s.bind=1
                        elif change=='size':f[change]+=1
                        elif change=='address':f[change]='0x1234'
                        elif change=='names':f[change]=['wrong']
                        elif change=='bind':f[change]=['global']
                        else:f[change]='wrong'
                    self.db['functions']={f['address']:f};self.image.symbols=symbols
                    self.assertTrue(self.index().build(self.target,'95c7f0: call '+f['address']).gaps)
        f,s=self.method('sort');self.db['functions']={f['address']:f};self.image.symbols=[s]
        original=self.header.read_bytes();self.header.write_bytes(original+b'\n')
        self.assertTrue(self.index().build(self.target,'95c7f0: call '+f['address']).gaps)

    def timer(self):
        d=object_symbol(0x14210b4,READABLE+'::UpdateTimer',size=4,bind='local',file='level.cpp');d['name']=RAW
        self.db['globals']=[d]
        self.image.symbols=[SimpleNamespace(name=RAW,value=0x14210b4,size=4,type=1,bind=0,defined=True,file='level.cpp')]

    def test_target_local_file_backed_initializer(self):
        self.timer();r=self.index().build(self.target,'95c7f0: mov $0x14210b4,%rax');r.require_complete();self.assertIn('all 4 initializer bytes 00 00 c8 42',r.text);self.assertNotIn('extern float',r.text)

    def test_timer_rejects_any_evidence_drift(self):
        self.timer()
        for change in ('db_hash','image_hash','symbol_name','symbol_size','symbol_owner','symbol_bind','db_size','db_owner','db_name','db_demangled','section_type','section_name','section_flags','section_size','initializer','target_size','target_address','target_name'):
            with self.subTest(change=change):
                db,image,target=copy.deepcopy(self.db),copy.deepcopy(self.image),copy.deepcopy(self.target)
                sym,d,sec=image.symbols[0],db['globals'][0],image.sections[0]
                if change=='db_hash':db['original_elf_sha256']='wrong'
                elif change=='image_hash':image.sha256='wrong'
                elif change=='symbol_name':sym.name='wrong'
                elif change=='symbol_size':sym.size=8
                elif change=='symbol_owner':sym.file='Other.cpp'
                elif change=='symbol_bind':sym.bind=1
                elif change=='db_size':d['size']=8
                elif change=='db_owner':d['file']='Other.cpp'
                elif change=='db_name':d['name']='wrong'
                elif change=='db_demangled':d['demangled']='wrong'
                elif change=='section_type':sec.type=8
                elif change=='section_name':sec.name='.rodata'
                elif change=='section_flags':sec.flags=2
                elif change=='section_size':sec.size=3
                elif change=='initializer':sec.contents=bytes(4)
                elif change=='target_size':target['size']=375
                elif change=='target_address':target['address']='0x95c7f1'
                elif change=='target_name':target['mangled']='wrong'
                self.assertTrue(self.index(db,image).build(target,target['address'][2:]+': mov $0x14210b4,%rax').gaps)

if __name__=='__main__': main()
