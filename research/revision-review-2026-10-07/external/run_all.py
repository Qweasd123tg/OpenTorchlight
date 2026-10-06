#!/usr/bin/env python3
"""Run this revision's probes in a new directory, without changing the project."""
import argparse,hashlib,json,os
from pathlib import Path
import subprocess,sys,tempfile


def main():
 parser=argparse.ArgumentParser(description=__doc__)
 parser.add_argument('project',type=Path)
 parser.add_argument('--out',type=Path,default=Path('/tmp/otl-revision-review'))
 parser.add_argument('--skip-existing-tests',action='store_true')
 args=parser.parse_args();project=args.project.resolve();here=Path(__file__).resolve().parent
 if not(project/'tools/decomp/publication.py').is_file():parser.error('expected updated project with publication.py')
 args.out.mkdir(parents=True,exist_ok=True)
 result=Path(tempfile.mkdtemp(prefix='run-',dir=args.out.resolve()))
 rows=[];env=dict(os.environ,PYTHONDONTWRITEBYTECODE='1')
 scripts=[('review.py','boundaries'),('jump_tables.py','jump-tables')]
 if not args.skip_existing_tests:scripts.append(('run_existing.py','existing-tests'))
 for script,folder in scripts:
  command=[sys.executable,str(here/'probes'/script),'--project',str(project),'--out',str(result/folder)]
  proc=subprocess.run(command,env=env,text=True,capture_output=True,timeout=180)
  (result/(script+'.log')).write_text(proc.stdout+proc.stderr)
  rows.append({'script':script,'returncode':proc.returncode,'command':command})
  print(script,'exit',proc.returncode,flush=True)
 (result/'run.json').write_text(json.dumps({'project':str(project),'steps':rows},indent=2)+'\n')
 print('Results:',result)
 return int(any(r['returncode']for r in rows))
if __name__=='__main__':raise SystemExit(main())
