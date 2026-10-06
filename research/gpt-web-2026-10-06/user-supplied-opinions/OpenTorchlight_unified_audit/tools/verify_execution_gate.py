#!/usr/bin/env python3
"""Verify a narrow optional acceptance patch in a temporary tree, not the input checkout."""
from __future__ import annotations
import argparse, contextlib, difflib, io, json, os, shutil, subprocess, sys, tempfile
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('repo',type=Path);p.add_argument('--out',type=Path,required=True)
 a=p.parse_args();repo=a.repo.resolve();out=a.out.resolve();out.mkdir(parents=True,exist_ok=True)
 if out==repo or repo in out.parents:p.error('output must be outside the repository')
 substitutions={
 'decomp/hybrid/loader.c':[
  ('    int failed = 0;\n    for (size_t i = 0; i < count; i++) {','    int failed = 0;\n    size_t executed = 0;\n    for (size_t i = 0; i < count; i++) {'),
  ('        int failures = test[i].run(&g_host);','        executed++;\n        int failures = test[i].run(&g_host);'),
  ('    fprintf(stderr, "tlhybrid: %zu tests, %d failed\\n", count, failed);\n    return failed ? 1 : 0;',
   '    fprintf(stderr, "tlhybrid: %zu tests, %d failed (%zu available)\\n", executed, failed, count);\n    if (!executed) {\n        fprintf(stderr, "tlhybrid: no tests selected; refusing a successful selftest\\n");\n        return 2;\n    }\n    return failed ? 1 : 0;')],
 'tools/decomp/hybrid.py':[
  ('    game, env = game_env(blob, loader, extra, headless=True)\n    result = subprocess.run',
   '    game, env = game_env(blob, loader, extra, headless=True)\n    if not only:\n        env.pop("TLHYBRID_FILTER", None)\n    result = subprocess.run')],
 'tools/decomp/llm_loop.py':[
  ('                _, report = hybrid.selftest(blob, loader, only=', '                test_code, report = hybrid.selftest(blob, loader, only='),
  ('            for line in report:\n                m = re.match(r"\\s+stats auto_',
   '            # A partial report from a failed process is not acceptance evidence.\n            if report and test_code != 0:\n                print(f"  hybrid selftest failed with exit code {test_code}; no candidates accepted", flush=True)\n                report = []\n            for line in report:\n                m = re.match(r"\\s+stats auto_')]
 }
 diff=[]
 for rel, pairs in substitutions.items():
  old=(repo/rel).read_text();new=old
  for src,dst in pairs:
   if new.count(src)!=1:raise RuntimeError(f'Archived patch context does not match: {rel}: {src[:70]}')
   new=new.replace(src,dst)
  diff.extend(difflib.unified_diff(old.splitlines(True),new.splitlines(True),fromfile='a/'+rel,tofile='b/'+rel))
 patchfile=out/'test-execution-gate.patch';patchfile.write_text(''.join(diff))
 records={'scope':'narrow test-dispatch and process-exit gates; no coverage or mutation provenance fix; no game run'}
 with tempfile.TemporaryDirectory(prefix='otl-execution-gate-') as td:
  root=Path(td);shutil.copytree(repo/'tools/decomp',root/'tools/decomp');shutil.copytree(repo/'decomp/hybrid',root/'decomp/hybrid')
  subprocess.run(['git','apply','--check',str(patchfile)],cwd=root,check=True,capture_output=True)
  subprocess.run(['git','apply',str(patchfile)],cwd=root,check=True,capture_output=True)
  sys.dont_write_bytecode=True;sys.path.insert(0,str(root/'tools/decomp'))
  import hybrid,llm_loop
  # Preserve the existing source's exception path: report=[] short-circuits test_code.
  generated=root/'generated';generated.mkdir()
  f={'address':'0x100','demangled':'CProbe::f()'}
  def exercise(rc,different):
   o=llm_loop.Loop.__new__(llm_loop.Loop);o.source=root/'Probe.cpp';o.work=root;o.rounds=5;o.accepted={};o.status={};o.original=None
   o.unit=lambda extra=(): '\n'.join(extra)+'\n'
   pending={'0x100':{'f':f,'code':'int f(){return 7;}'}}
   report=[f'    stats auto_100 same 20 both-failed 0 different {different}']
   with patch.object(llm_loop.autotest,'Generator',return_value=SimpleNamespace(write=lambda _:([f],{}))),patch.object(llm_loop.autotest,'OUT',generated),patch.object(llm_loop.objdiff,'compare_source',return_value={}),patch.object(llm_loop.hybrid,'build',return_value=(None,None)),patch.object(llm_loop.hybrid,'selftest',return_value=(rc,report)),patch.dict(os.environ,{},clear=False),contextlib.redirect_stdout(io.StringIO()):
    o.test(pending,{'0x100':'fixture difference'},1)
   return bool(o.accepted)
  records['loop_good_accepted']=exercise(0,0);records['loop_failed_process_rejected']=not exercise(97,0);records['loop_divergence_rejected']=not exercise(0,1)
  assert all(records[k] for k in ('loop_good_accepted','loop_failed_process_rejected','loop_divergence_rejected'))
  seen=[]
  def fake_run(*args,**kwargs):seen.append(dict(kwargs['env']));return SimpleNamespace(returncode=0,stderr='tlhybrid: 1 tests, 0 failed\n')
  for only in (None,'requested'):
   def env(*args,**kwargs):return root,{'TLHYBRID_FILTER':kwargs.get('extra',{}).get('TLHYBRID_FILTER','inherited')}
   def environment(blob,loader,extra,headless):return root,dict(TLHYBRID_FILTER=extra.get('TLHYBRID_FILTER','inherited'))
   with patch.object(hybrid,'game_env',side_effect=environment),patch.object(hybrid.subprocess,'run',side_effect=fake_run):hybrid.selftest(None,None,only=only)
  records['ambient_filter_removed']='TLHYBRID_FILTER' not in seen[0];records['explicit_filter_preserved']=seen[1]['TLHYBRID_FILTER']=='requested'
  assert records['ambient_filter_removed'] and records['explicit_filter_preserved']
  fixture=Path(__file__).resolve().parents[1]/'reproductions/loader_probe.c'
  text=fixture.read_text().replace('none_rc==0 && none_calls==0','none_rc==2 && none_calls==0')
  src=root/'fixture.c';src.write_text(text);exe=root/'fixture'
  subprocess.run(['cc','-std=gnu11','-O0','-I',str(root/'decomp/hybrid'),str(src),'-ldl','-o',str(exe)],check=True,capture_output=True,timeout=30)
  r=subprocess.run([str(exe)],capture_output=True,text=True,check=True,timeout=5)
  records['native_loader']=json.loads(r.stdout);records['native_log']=r.stderr
  assert records['native_loader']['none_rc']==2 and records['native_loader']['none_invoked']==0
  assert records['native_loader']['one_rc']==0 and records['native_loader']['one_invoked']==1
  tests=subprocess.run([sys.executable,'-m','unittest','test_ghidra_cpp','test_llm_loop_headers','test_mutate_overloads','test_objdiff_literals'],cwd=root/'tools/decomp',env=dict(os.environ,PYTHONDONTWRITEBYTECODE='1'),capture_output=True,text=True,timeout=30)
  records['existing_tests']={'returncode':tests.returncode,'log':tests.stdout+tests.stderr}
  assert tests.returncode==0,tests.stderr
 (out/'verification.json').write_text(json.dumps(records,ensure_ascii=False,indent=2)+'\n')
 print(json.dumps(records,ensure_ascii=False,indent=2))
if __name__=='__main__':main()
