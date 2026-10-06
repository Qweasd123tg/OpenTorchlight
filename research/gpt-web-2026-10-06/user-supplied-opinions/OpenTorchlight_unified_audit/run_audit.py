#!/usr/bin/env python3
"""Read-only audit and archived regression reproduction. No LLM, network or game launch.
Default: inventories source and compares reviewed fingerprints. --verify additionally
runs host-compiled synthetic probes and five isolated archived assembly fixtures.
Full original-game verification is NOT performed. Linux x86-64 is needed for all probes.
"""
from __future__ import annotations
import argparse, concurrent.futures, hashlib, json, os, platform, subprocess, sys, time
from pathlib import Path
HERE=Path(__file__).resolve().parent
EXCLUDED={'.git','__pycache__','build','build-decomp','node_modules','.venv','venv'}
def manifest(root:Path):
 result={}
 for directory,dirs,files in os.walk(root,followlinks=False):
  dirs[:]=[d for d in dirs if d not in EXCLUDED and not (Path(directory)/d).is_symlink()]
  for name in files:
   p=Path(directory)/name
   if p.is_symlink():continue
   h=hashlib.sha256()
   with p.open('rb') as stream:
    for block in iter(lambda:stream.read(1024*1024),b''):h.update(block)
   result[p.relative_to(root).as_posix()]={'bytes':p.stat().st_size,'sha256':h.hexdigest()}
 return result

def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('repo',type=Path);p.add_argument('--out',type=Path,required=True);p.add_argument('--verify',action='store_true');p.add_argument('--jobs',type=int,default=2)
 a=p.parse_args();repo=a.repo.resolve();out=a.out.resolve()
 if not (repo/'tools/decomp/check.py').is_file():p.error('repo must contain tools/decomp/check.py')
 if out==repo or repo in out.parents:p.error('--out must be outside the input checkout')
 if a.jobs<1 or a.jobs>8:p.error('--jobs must be between 1 and 8')
 out.mkdir(parents=True,exist_ok=True);before=manifest(repo)
 (out/'source_manifest.json').write_text(json.dumps(before,ensure_ascii=False,indent=2))
 expected=json.loads((HERE/'results/reference_source_fingerprints.json').read_text())
 changed=[r for r,h in expected.items() if before.get(r,{}).get('sha256')!=h]
 summary={'scope':'archive audit, not game acceptance','input':str(repo),'source_files':len(before),'skipped_directories':sorted(EXCLUDED),'reviewed_inputs_changed_or_missing':changed,'original_game_executed':False,'original_GCC447_run':False,'verification_requested':a.verify}
 if a.verify and changed:
  summary['verification']='NOT_RUN: archived probes need adaptation to changed sources; no patches were applied'
  (out/'summary.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2));print(json.dumps(summary,ensure_ascii=False,indent=2));return 2
 jobs=[];py=sys.executable;r=HERE/'reproductions'
 def add(name,args):
  dest=out/name;dest.mkdir(exist_ok=True);jobs.append((name,args(dest)))
 if a.verify:
  if platform.system()!='Linux' or platform.machine() not in ('x86_64','AMD64'):p.error('--verify requires Linux x86-64')
  add('new-boundaries',lambda d:[py,str(HERE/'tools/probe_pipeline_boundaries.py'),str(repo),'--out',str(d)])
  add('test-execution-gate',lambda d:[py,str(HERE/'tools/verify_execution_gate.py'),str(repo),'--out',str(d)])
  add('input-freshness',lambda d:[py,str(r/'input-freshness/probe_draft_invalidation.py'),str(repo)])
  add('types-and-comparison',lambda d:[py,str(r/'types-and-comparison/probe_pipeline.py'),str(repo),'--out',str(d/'results.json')])
  add('fast-comparison',lambda d:[py,str(r/'fast-comparison/verify_patch.py'),str(repo),'--out',str(d/'results.json')])
  add('capture-and-equivalence',lambda d:[py,str(r/'fast-comparison/probe_pass3.py'),str(repo),'--out',str(d)])
  add('syntax-and-signatures',lambda d:[py,str(r/'syntax-and-signatures/probe_pass4.py'),str(repo),'--output',str(d)])
  add('cv-patch',lambda d:[py,str(r/'syntax-and-signatures/verify_cv_patch.py'),str(repo),'--output',str(d)])
  add('control-flow',lambda d:[py,str(r/'control-flow/scripts/test_stage_tools.py')])
  add('families-and-loops',lambda d:[py,str(r/'families-and-loops/scripts/test_stage_prototypes.py')])
  add('resource-operations',lambda d:[py,str(r/'resource-operations/tools/run_checks.py'),str(repo),'--out',str(d)])
  add('memory-abi-lifetime',lambda d:[py,str(r/'memory-abi-lifetime/run_all.py'),str(repo),'--out',str(d)])
  add('draft-isolation',lambda d:[py,str(r/'draft-isolation/run_checks.py'),str(repo),'--out',str(d)])
 def run(job):
  name,cmd=job;t=time.monotonic()
  try:
   proc=subprocess.run(cmd,capture_output=True,text=True,env=dict(os.environ,PYTHONDONTWRITEBYTECODE='1'),timeout=180)
   (out/name/'run.log').write_text(proc.stdout+proc.stderr)
   result={'name':name,'returncode':proc.returncode,'seconds':round(time.monotonic()-t,3),'command':cmd}
  except (subprocess.TimeoutExpired,OSError) as e:
   result={'name':name,'returncode':None,'error':str(e),'seconds':round(time.monotonic()-t,3),'command':cmd}
  print(name+': '+('PASS' if result.get('returncode')==0 else 'ERROR'),flush=True);return result
 try:
  with concurrent.futures.ThreadPoolExecutor(max_workers=a.jobs) as pool:results=list(pool.map(run,jobs))
 finally:
  after=manifest(repo);modified=sorted(k for k in before.keys()|after.keys() if before.get(k)!=after.get(k))
  (out/'integrity.json').write_text(json.dumps({'source_files_before':len(before),'source_files_after':len(after),'changed_missing_or_added':modified,'unchanged':not modified},indent=2))
 summary['runs']=results;summary['source_unchanged']=not modified
 summary['verification']='COMPLETED' if a.verify else 'NOT_REQUESTED'
 (out/'summary.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2))
 print('Report: '+str(out/'summary.json'))
 return 1 if modified or any(x.get('returncode')!=0 for x in results) else 0
if __name__=='__main__':raise SystemExit(main())
