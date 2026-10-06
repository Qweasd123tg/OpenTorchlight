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
dest=root/'research/night-audit-2026-10-06/eh-export'
command=[str(headless),str(args.project_dir),args.project_name,'-process','Torchlight.bin.x86_64','-noanalysis','-readOnly','-scriptPath',str(dest),'-postScript','ExportExceptionRegions.java',str(dest/'regions.json')]
with (dest/'export.log').open('w') as log:
 proc=subprocess.run(command,env=env,stdout=log,stderr=subprocess.STDOUT)
print(proc.returncode)
lines=(dest/'export.log').read_text().splitlines();print('\n'.join(x for x in lines if 'EXPORTED' in x));print('error_lines',sum('ERROR' in x for x in lines))
