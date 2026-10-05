"""Standalone targeted comparisons of the non-MATCH graph/price/socket entries."""
import json,shutil,sys,os
from pathlib import Path
sys.path.insert(0,'tools/decomp')
import hybrid,mutate
root=Path(os.environ.get('OTL_GRAPH_TARGET_ROOT','build-decomp/equipment-graphs-sockets-targeted')).resolve()
source=Path('decomp/src/Equipment.cpp').read_text();masked=mutate.mask(source);db=json.loads(Path('build-decomp/db/elfdb.json').read_text())
jobs=[]
# jobs are loaded from a plain, reviewable JSON file next to this runner.
for job in json.loads(Path('research/equipment-graphs-sockets-check/mutations.json').read_text()):
 if len(sys.argv)>1 and job['address'] not in sys.argv[1:]:continue
 address=job['address'];work=root/address;(work/'src').mkdir(parents=True,exist_ok=True);(work/'tests').mkdir(exist_ok=True)
 for n in [job['fixture'],'Detour.h']:shutil.copyfile(Path('decomp/hybrid/tests')/n,work/'tests'/n)
 a,b=mutate.definition(source,masked,db['functions'][address]);body=source[a:b+1];results=[]
 for name,before,after in [('baseline','','')]+job['mutations']:
  if name!='baseline' and body.count(before)!=1:raise SystemExit('ambiguous replacement: '+address+' '+name)
  changed=body if name=='baseline' else body.replace(before,after,1)
  (work/'src/Equipment.cpp').write_text(source[:a]+changed+source[b+1:])
  try:
   blob,loader=hybrid.build(out=work/name,src=work/'src',tests=sorted((work/'tests').glob('*.cpp')),verbose=False)
   code,report=hybrid.selftest(blob,loader,only=job['test'])
   passed=any(job['test'] in line and 'PASS (0)' in line for line in report)
   if name=='baseline' and (code or not passed):raise SystemExit('baseline failed: '+'\n'.join(report))
   outcome='pass' if name=='baseline' else 'survived' if passed else 'killed' if any(job['test'] in line and 'FAIL' in line for line in report) else 'inconclusive'
   row={'name':name,'outcome':outcome,'exit':code}
  except Exception as e:row={'name':name,'outcome':'inconclusive','error':str(e)}
  results.append(row);print(json.dumps({'address':address,**row}),flush=True);(work/'results.json').write_text(json.dumps(results,indent=2)+'\n')
