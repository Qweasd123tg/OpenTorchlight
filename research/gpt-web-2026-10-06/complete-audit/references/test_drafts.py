#!/usr/bin/env python3
"""Tests real Python orchestration, with a controllable stand-in for Ghidra's file I/O.
No test here executes Ghidra, an original game binary, or validates game semantics.
"""
import argparse,contextlib,importlib.util,io,json,os,pathlib,sys,tempfile,threading,types,unittest
from unittest.mock import patch
P=argparse.ArgumentParser();P.add_argument('repo',type=pathlib.Path);P.add_argument('preview',type=pathlib.Path);P.add_argument('results',type=pathlib.Path)
ARGS=P.parse_args();sys.path.insert(0,str(ARGS.repo/'tools/decomp'))
ORIGINAL=ARGS.repo/'tools/decomp/ghidra_draft.py';PATCHED=ARGS.preview/'tools/decomp/ghidra_draft.py'
records={}
def load(path,label):
 sp=importlib.util.spec_from_file_location('gd9_'+label,path);m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);return m

def fixture(path,root,shared,tag='A',n=1):
 m=load(path,tag+str(id(root)));root.mkdir(parents=True,exist_ok=True)
 base=root/'build-decomp';base.mkdir(exist_ok=True)
 (base/'types.json').write_text(json.dumps({'classes':{},'vtables':{},'prototypes':{}}))
 jp=root/'tools/decomp/ghidra/DecompDrafts.java';jp.parent.mkdir(parents=True,exist_ok=True);jp.write_text('// test script input')
 fs={hex(0x100+i*0x10):{'address':hex(0x100+i*0x10),'tu':1,'kind':'function','scope':tag,'size':16} for i in range(n)}
 db={'original_elf_sha256':'fixture-elf','tus':[{'id':1,'name':tag+'.cpp','kind':'game'}],'functions':fs}
 m.ROOT=root;m.OUT=base/'drafts';m.workspace=lambda:shared
 m.subprocess=types.SimpleNamespace(run=lambda *args,**kw:types.SimpleNamespace(returncode=0))
 m.elfdb=types.SimpleNamespace(load_db=lambda:db);m.tools_digest=lambda:'fixture-tools'
 m._prototypes=lambda:{}
 shared.mkdir(parents=True,exist_ok=True)
 raw=m.OUT/(tag+'.cpp')/'raw';raw.mkdir(parents=True)
 def stamp():
  (raw.parent/'inputs.json').write_text(json.dumps({'elf':'fixture-elf','tools':'fixture-tools','classes':{},'prototypes':m.prototype_digest({},list(fs))}))
 stamp();return m,db,raw,stamp

def backend(args,log,outputs=None,seen=None):
 i=args.index('-postScript');target=pathlib.Path(args[i+3]);out=pathlib.Path(args[i+4]);addrs=target.read_text().splitlines();out.mkdir(parents=True,exist_ok=True)
 if seen is not None:seen.append({'targets':addrs,'log':log,'timeout':args[i+5] if len(args)>i+5 else 'hardcoded 120','io':str(target.parent)})
 for adr in addrs:
  value=(outputs or {}).get(adr,'int fn() { return 42; }\n')
  if value is not None:(out/(adr+'.c')).write_text(value)
 return types.SimpleNamespace(returncode=0)

class Tests(unittest.TestCase):
 def setUp(self):
  self.tmp=tempfile.TemporaryDirectory();self.base=pathlib.Path(self.tmp.name)
 def tearDown(self):self.tmp.cleanup()
 def setup_m(self,n=1):return fixture(PATCHED,self.base/'repo',self.base/'shared',n=n)
 def test_raw_status(self):
  m,db,raw,s=self.setup_m();cases={'// failed: process: timeout\n':'failed','// no function\n':'failed','/* DECOMPILATION FAILED: timeout */':'failed','/* {} */':'no-body','int fn();':'no-body','':'no-body','int fn(){ return 1; }':'ok','void fn(){ const char* s="// failed: {}"; }':'ok'}
  for text,expected in cases.items():
   with self.subTest(text=text):
    p=raw/'0x100.c';p.write_text(text);self.assertEqual(m.raw_status(p),expected)
  self.assertEqual(m.raw_status(raw/'absent.c'),'missing')
 def test_failure_is_not_fresh(self):
  report={}
  for label,path in [('original',ORIGINAL),('patched',PATCHED)]:
   m,db,raw,s=fixture(path,self.base/label,self.base/('shared'+label));(raw/'0x100.c').write_text('// failed: process: timeout\n')
   state,reasons=m.draft_state('A.cpp',db,{})
   report[label]={'state':state,'reasons':reasons}
  self.assertEqual(report['original']['state'],'fresh');self.assertEqual(report['patched']['state'],'stale');records['failed_export_freshness']=report
 def test_missing_is_stale(self):
  m,db,raw,s=self.setup_m();self.assertEqual(m.draft_state('A.cpp',db,{})[0],'stale')
 def test_healthy_is_fresh(self):
  m,db,raw,s=self.setup_m();(raw/'0x100.c').write_text('void f() {}');self.assertEqual(m.draft_state('A.cpp',db,{})[0],'fresh')
 def test_selective_retry(self):
  m,db,raw,s=self.setup_m(2);(raw/'0x100.c').write_text('void keep() {}');(raw/'0x110.c').write_text('// failed: timeout')
  seen=[];m.headless=lambda a,l:backend(a,l,seen=seen)
  self.assertEqual(m.drafts(['A.cpp'],timeout=600,retry_failed=True),0)
  self.assertEqual(seen[0]['targets'],['0x110']);self.assertEqual(seen[0]['timeout'],'600')
  self.assertEqual((raw/'0x100.c').read_text(),'void keep() {}');self.assertEqual(m.draft_state('A.cpp',db,{})[0],'fresh')
  records['selective_retry']={'targets':seen[0]['targets'],'timeout':seen[0]['timeout'],'healthy_body_preserved':True}
 def test_changed_inputs_force_full_refresh(self):
  m,db,raw,s=self.setup_m(2)
  for adr in db['functions']:(raw/(adr+'.c')).write_text('void old() {}')
  meta=raw.parent/'inputs.json';d=json.loads(meta.read_text());d['elf']='old-elf';meta.write_text(json.dumps(d))
  seen=[];m.headless=lambda a,l:backend(a,l,seen=seen)
  self.assertEqual(m.drafts(['A.cpp'],timeout=600,retry_failed=True),0);self.assertEqual(len(seen[0]['targets']),2)
 def test_disabled_prototypes_force_refresh(self):
  m,db,raw,s=self.setup_m(2)
  for adr in db['functions']:(raw/(adr+'.c')).write_text('void previous() {}')
  seen=[];m.headless=lambda a,l:backend(a,l,seen=seen)
  with patch.dict(os.environ,{'OTL_DRAFT_PROTOTYPES':'0'}):
   self.assertEqual(m.drafts(['A.cpp'],retry_failed=True),0)
  self.assertEqual(len(seen[0]['targets']),2)
 def test_retry_preserves_type_dependencies(self):
  m,db,raw,s=self.setup_m(2)
  cls={'FixtureA':{'size':4},'FixtureB':{'size':8}}
  (m.ROOT/'build-decomp/types.json').write_text(json.dumps({'classes':cls,'prototypes':{}}))
  meta=raw.parent/'inputs.json';d=json.loads(meta.read_text());d['classes']=m.class_digests(cls,cls);meta.write_text(json.dumps(d))
  (raw/'0x100.c').write_text('void keep() { FixtureA value; }')
  (raw/'0x110.c').write_text('// failed: timeout')
  seen=[];m.headless=lambda a,l:backend(a,l,outputs={'0x110':'void replace() { FixtureB value; }'},seen=seen)
  self.assertEqual(m.drafts(['A.cpp'],retry_failed=True),0)
  self.assertEqual(seen[0]['targets'],['0x110'])
  self.assertEqual(set(json.loads(meta.read_text())['classes']),{'FixtureA','FixtureB'})
 def test_retry_already_done_does_not_launch(self):
  m,db,raw,s=self.setup_m();(raw/'0x100.c').write_text('void done() {}')
  def nope(*args):self.fail('unexpected Ghidra launch')
  m.headless=nope;self.assertEqual(m.drafts(['A.cpp'],retry_failed=True),0)
 def test_failed_run_returns_nonzero(self):
  m,db,raw,s=self.setup_m();m.headless=lambda a,l:backend(a,l,outputs={'0x100':'// failed: timeout'})
  self.assertEqual(m.drafts(['A.cpp']),1);self.assertEqual(m.draft_state('A.cpp',db,{})[0],'stale')
 def test_missing_output_does_not_leave_old_success(self):
  m,db,raw,s=self.setup_m();(raw/'0x100.c').write_text('void old() {}');m.headless=lambda a,l:backend(a,l,outputs={'0x100':None})
  self.assertEqual(m.drafts(['A.cpp']),1);self.assertEqual(m.raw_status(raw/'0x100.c'),'failed')
 def test_hard_backend_failure(self):
  m,db,raw,s=self.setup_m();m.headless=lambda a,l:types.SimpleNamespace(returncode=3)
  with self.assertRaisesRegex(SystemExit,'Ghidra failed'):m.drafts(['A.cpp'])
 def test_unknown_tu_rejected(self):
  m,db,raw,s=self.setup_m()
  with self.assertRaisesRegex(SystemExit,'unknown TU'):m.drafts(['not-there.cpp'])
 def test_timeout_validation(self):
  m,db,raw,s=self.setup_m()
  for timeout in (0,-1,True,0.5):
   with self.subTest(timeout=timeout),self.assertRaises(SystemExit):m.drafts(['A.cpp'],timeout=timeout)
 def test_no_shared_io_deletion(self):
  m,db,raw,s=self.setup_m();marker=self.base/'shared/io/keep';marker.parent.mkdir(parents=True);marker.write_text('other worker')
  m.headless=lambda a,l:backend(a,l);self.assertEqual(m.drafts(['A.cpp']),0);self.assertEqual(marker.read_text(),'other worker')
 def test_parallel_separate_worktrees(self):
  report={}
  for label,path in [('original',ORIGINAL),('patched',PATCHED)]:
   root=self.base/label;shared=root/'shared';arr=[fixture(path,root/tag,shared,tag=tag) for tag in ('A','B')]
   # Distinct targets, as they would be in two worktrees processing different TUs.
   bm,bd,br,bs=arr[1];f=bd['functions'].pop('0x100');f['address']='0x200';bd['functions']['0x200']=f;bs()
   ready=threading.Event();barrier=threading.Barrier(2);seen={};errors={}
   def run(idx):
    m,db,raw,stamp=arr[idx];tag='AB'[idx]
    def fake(args,log):
     if idx==0:ready.set()
     barrier.wait(timeout=10)
     i=args.index('-postScript');tp=pathlib.Path(args[i+3]);seen[tag]={'expected':list(db['functions']),'observed':tp.read_text().splitlines(),'log':log}
     return backend(args,log)
    m.headless=fake
    try:m.drafts([tag+'.cpp'])
    except BaseException as e:errors[tag]=repr(e)
   ta=threading.Thread(target=run,args=(0,));ta.start();self.assertTrue(ready.wait(5));tb=threading.Thread(target=run,args=(1,));tb.start();ta.join(12);tb.join(12)
   self.assertFalse(ta.is_alive() or tb.is_alive());self.assertFalse(errors,errors)
   report[label]={'jobs':seen,'A_body_exists':(arr[0][2]/'0x100.c').exists(),'B_body_exists':(arr[1][2]/'0x200.c').exists()}
  self.assertEqual(report['original']['jobs']['A']['observed'],['0x200']);self.assertFalse(report['original']['A_body_exists'])
  self.assertEqual(report['patched']['jobs']['A']['observed'],['0x100']);self.assertTrue(report['patched']['A_body_exists']);self.assertTrue(report['patched']['B_body_exists'])
  self.assertNotEqual(report['patched']['jobs']['A']['log'],report['patched']['jobs']['B']['log'])
  records['parallel_io']=report

if __name__=='__main__':
 suite=unittest.defaultTestLoader.loadTestsFromTestCase(Tests);buf=io.StringIO()
 with contextlib.redirect_stdout(buf):result=unittest.TextTestRunner(verbosity=2).run(suite)
 ARGS.results.parent.mkdir(parents=True,exist_ok=True)
 ARGS.results.write_text(json.dumps({'tests_run':result.testsRun,'failures':len(result.failures),'errors':len(result.errors),'scope':'Real Python code; Ghidra backend replaced only for deterministic orchestration tests','records':records,'stdout':buf.getvalue()},indent=2))
 sys.exit(not result.wasSuccessful())
