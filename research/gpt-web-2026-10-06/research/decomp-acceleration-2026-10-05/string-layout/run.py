"""Run equal-resource, read-only A/B exports from one saved analysis project."""
from pathlib import Path
import argparse,hashlib,json,os,subprocess,time
root=Path.cwd();experiment=root/'build-decomp/sdk-prototype-experiment';shared=root.parent/'gameui-analysis'
parser=argparse.ArgumentParser()
parser.add_argument('--project-dir',type=Path,default=shared/'ghidra-project')
parser.add_argument('--project-name',default='GameUI')
parser.add_argument('--ghidra-home',type=Path,default=root.parent/'repo/build-source-cache/ghidra/ghidra_12.1.3_PUBLIC')
parser.add_argument('--java-home',type=Path,default=root.parent/'cache/jdk/jdk-21.0.12.1+1')
args=parser.parse_args();headless=args.ghidra_home/'support/analyzeHeadless'
shared.mkdir(exist_ok=True)
env=dict(os.environ,JAVA_HOME=str(args.java_home),XDG_CONFIG_HOME=str(shared/'ghidra-config'),XDG_CACHE_HOME=str(shared/'ghidra-cache'),GHIDRA_HEADLESS_MAXMEM='3G')
results=[]
for arm in ('string-layout',):
 dest=experiment/arm;dest.mkdir(exist_ok=True)
 for target in (experiment/'targets.txt').read_text().splitlines():(dest/(target+'.c')).unlink(missing_ok=True)
 command=[str(headless),str(args.project_dir),args.project_name,'-process','Torchlight.bin.x86_64','-noanalysis','-readOnly','-scriptPath',str(root/'research/decomp-acceleration-2026-10-05'),'-postScript','SDKPrototypeAB.java',str(experiment/(arm+'-types.json')),str(experiment/'targets.txt'),str(dest)]
 start=time.monotonic()
 with (experiment/(arm+'.log')).open('w') as log:proc=subprocess.run(command,env=env,stdout=log,stderr=subprocess.STDOUT)
 output=[]
 for target in (experiment/'targets.txt').read_text().splitlines():
  file=dest/(target+'.c');text=file.read_text() if file.exists() else ''
  output.append({'address':target,'bytes':len(text.encode()),'lines':len(text.splitlines()),'success':bool(text) and not text.startswith('// failed:')})
 result={'input_sha256':hashlib.sha256((experiment/(arm+'-types.json')).read_bytes()).hexdigest(),'script_sha256':hashlib.sha256((root/'research/decomp-acceleration-2026-10-05/SDKPrototypeAB.java').read_bytes()).hexdigest(),'arm':arm,'wall_seconds':time.monotonic()-start,'exit':proc.returncode,'outputs':output};results.append(result);print(json.dumps(result),flush=True)
 (root/'research/decomp-acceleration-2026-10-05/string-layout/runs.json').write_text(json.dumps(results,indent=2)+'\n')
 if proc.returncode or not all(x['success'] for x in output):raise SystemExit('Export incomplete; inspect log rather than accepting headless exit alone')
