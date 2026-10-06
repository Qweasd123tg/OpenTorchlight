from pathlib import Path
from unittest.mock import patch
import sys,subprocess,json,tempfile,hashlib
sys.path.insert(0,str(Path.cwd()/'tools/decomp'));import mutate,objdiff
out=Path('/workspace/scratch/3ba0fff8d310/otl-restore-20261006/mutation-audit');digests={}
for value in (1,2):
 f=out/('record_v'+str(value)+'.cpp');f.write_text('extern "C" int probe(int x){return x+'+str(value)+';}\n');o=f.with_suffix('.o')
 subprocess.run(['g++','-O2','-c',str(f),'-o',str(o)],check=True)
 digests[value]=objdiff.code_digest(objdiff.object_functions(o)['probe']['norm'])
assert digests[1]!=digests[2]
f={'address':'0x123','demangled':'probe(int)'}
old_results={'0x123':{'name':'probe(int)','strong':True,'tried':10,'killed':9,'code_at_test':digests[1]}}
with tempfile.TemporaryDirectory() as td:
 p=Path(td)/'accepted.json'
 # Replace only environment adapters: current digest comes from the newly compiled body.
 with patch.object(mutate,'ROOT',Path(td)),patch.object(mutate,'ACCEPTED',p),patch.object(mutate,'code_digests',lambda db,fs:{'0x123':digests[2]}):
  mutate.record({},[f],old_results)
 result=json.loads(p.read_text())
assert result['0x123']['code']==digests[2]
r={'old_tested_code':digests[1],'new_current_code':digests[2],'real_record_output':result,'old_results_rebound_to_new_code':True,'scope':'record() regression fixture; no real prior mutation run or original ELF; code digests from real different synthetic objects'}
(out/'record-results.json').write_text(json.dumps(r,indent=2)+'\n');print(json.dumps(r,indent=2))
accepted=json.loads(Path('decomp/autotests.json').read_text());small=[{'address':a,**v} for a,v in accepted.items() if v.get('tried',0)<=2]
(out/'small-sample-inventory.json').write_text(json.dumps({'entries':len(accepted),'one_mutant':sum(x.get('tried')==1 for x in accepted.values()),'two_mutants':sum(x.get('tried')==2 for x in accepted.values()),'examples':small,'scope':'saved snapshot counts, not current PC or evidence of wrong game implementations'},indent=2)+'\n')
