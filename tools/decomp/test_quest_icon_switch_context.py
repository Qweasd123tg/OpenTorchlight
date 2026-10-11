"""Fail-closed offline tests for the one pinned compiler switch table."""
import copy
from pathlib import Path
from types import SimpleNamespace
import sys
from unittest import TestCase,main,mock
sys.path.insert(0,str(Path(__file__).resolve().parent))
from llm_context import ContextIndex

PIN='91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b'
CODE='779ab1c7b0f0a6766221424fd1ed0dca53980ebd135c746fe6bd9eedf8a36c66'
ASM='''d308d7: or $0xffffffff,%eax
d308e5: mov 0x70(%rdx),%edx
d308e8: add %eax,%edx
d308ea: cmp $0x3,%edx
d308ed: ja d308bd <default>
d308ef: mov %edx,%edx
d308f1: mov 0xff77d0(,%rdx,4),%eax'''
class SwitchContextTests(TestCase):
 def setUp(self):
  self.i=object.__new__(ContextIndex);self.i.db={'original_elf_sha256':PIN};self.i.tus={244:{'name':'QuestManager.cpp'}};self.i.copy_data={}
  self.sec=SimpleNamespace(name='.rodata',type=1,flags=2,addr=0xff77d0,size=16)
  self.sym=SimpleNamespace(name='CSWTCH.4688',defined=True,type=1,bind=0,value=0xff77d0,size=16,file='QuestManager.cpp')
  self.i.image=SimpleNamespace(sha256=PIN,symbols=[self.sym],section_at=lambda a:self.sec)
  self.table=bytes.fromhex('170000001a00000016000000ffffffff')
  self.i._read_bytes=lambda a,n:self.table if a==0xff77d0 else b'code'
  self.f={'address':'0xd30830','size':202,'tu':244,'names':['_ZN13CQuestManager10getNPCIconEP10CCharacter'],'mangled':'_ZN13CQuestManager10getNPCIconEP10CCharacter','qualified':'CQuestManager::getNPCIcon'}
  self.obj={'name':'CSWTCH.4688','demangled':'CSWTCH.4688','address':'0xff77d0','size':16,'file':'QuestManager.cpp','bind':'local','section':'.rodata'}
  self.hash=mock.patch('llm_context.hashlib.sha256',return_value=SimpleNamespace(hexdigest=lambda:CODE));self.hash.start();self.addCleanup(self.hash.stop)
 def call(self,asm=ASM,tu='QuestManager.cpp'):return self.i._quest_icon_switch_data(self.obj,self.f,asm,tu)
 def test_exact_identity(self):self.assertIn('[23, 26, 22, -1]',self.call())
 def test_object_mismatches(self):
  for key,value in [('name','CSWTCH.999'),('demangled','other'),('address','0xff77d4'),('size',20),('file','Other.cpp'),('bind','global'),('section','.data')]:
   with self.subTest(key=key):
    old=self.obj[key];self.obj[key]=value;self.assertIsNone(self.call());self.obj[key]=old
 def test_symbol_mismatches(self):
  for key,value in [('name','CSWTCH.999'),('defined',False),('type',2),('bind',1),('value',0xff77d4),('size',20),('file','Other.cpp')]:
   with self.subTest(key=key):
    old=getattr(self.sym,key);setattr(self.sym,key,value);self.assertIsNone(self.call());setattr(self.sym,key,old)
  self.i.image.symbols.append(copy.copy(self.sym));self.assertIsNone(self.call())
 def test_section_mismatches(self):
  for key,value in [('name','.data'),('type',8),('flags',3),('flags',6),('size',15)]:
   with self.subTest(key=key,value=value):
    old=getattr(self.sec,key);setattr(self.sec,key,value);self.assertIsNone(self.call());setattr(self.sec,key,old)
 def test_function_mismatches(self):
  for key,value in [('address','0xd30831'),('size',203),('tu',0),('names',['wrong']),('mangled','wrong'),('qualified','CQuestManager::other')]:
   with self.subTest(key=key):
    old=self.f[key];self.f[key]=value;self.assertIsNone(self.call());self.f[key]=old
  self.assertIsNone(self.call(tu='Other.cpp'))
 def test_elf_db_and_code_hash(self):
  self.i.db['original_elf_sha256']='bad';self.assertIsNone(self.call());self.i.db['original_elf_sha256']=PIN
  self.i.image.sha256='bad';self.assertIsNone(self.call());self.i.image.sha256=PIN
  with mock.patch('llm_context.hashlib.sha256',return_value=SimpleNamespace(hexdigest=lambda:'bad')):self.assertIsNone(self.call())
 def test_bytes_copy_and_read_failure(self):
  self.table=b'\x00'*16;self.assertIsNone(self.call());self.table=bytes.fromhex('170000001a00000016000000ffffffff')
  self.i.copy_data={0xff77d0:True};self.assertIsNone(self.call());self.i.copy_data={}
  def fail(a,n):raise ValueError('not backed')
  self.i._read_bytes=fail;self.assertIsNone(self.call())
 def test_bounded_consumer_required(self):
  for old,new in [('0xffffffff','0xfffffffe'),('0x70','0x74'),('$0x3','$0x4'),('ja ','jg '),(',4)',',8)'),('0xff77d0','0xff77d4'),('%eax','%rax')]:
   with self.subTest(old=old):self.assertIsNone(self.call(ASM.replace(old,new)))
  self.assertIsNone(self.call(ASM.replace('d308ea: cmp $0x3,%edx','')))
if __name__=='__main__':main()
