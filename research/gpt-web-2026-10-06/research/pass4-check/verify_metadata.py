from pathlib import Path
from unittest.mock import patch
import sys,tempfile,json
sys.path.insert(0,str(Path.cwd()/'tools/decomp'));import headers,parallel
out=Path('/workspace/scratch/3ba0fff8d310/otl-restore-20261006/pass4-check');g=headers.Gen.__new__(headers.Gen);g.resolve=lambda t,d:t
f={'method':'get','params':'','cv':'const','kind':'function'}
decl=g.method_decl(f,'CProbe',{'sys':set(),'local':set(),'forward':set()},ret='int');assert decl=='int get();'
results={'const_declaration':decl,'virtual_identity_const_equals_nonconst':g.virtual_signature(f)==g.virtual_signature(dict(f,cv=''))}
with tempfile.TemporaryDirectory() as td:
 root=Path(td);inc=root/'decomp/include';inc.mkdir(parents=True);(root/'decomp/src').mkdir()
 (inc/'Probe.h').write_text('struct CProbe {\nint read(int);\n};\n')
 fs={'1':{'scope':'CProbe','method':'read','params':'int','cv':'','kind':'function'},'2':{'scope':'CProbe','method':'read','params':'double','cv':'','kind':'function'}}
 g.db={'classes':{'CProbe':{'methods':['1','2']}}};g.funcs=fs;g.game_classes={'CProbe'};g.hand={};g.hand_templates=set();g.hand_enums=set();g.ghidra_return=lambda f:'int'
 with patch.object(headers,'ROOT',root),patch.object(headers,'INCLUDE',inc):
  results['overload_declarations_added']=g.trial_include();assert results['overload_declarations_added']==0
 db={'tus':[{'id':1,'name':'partial.cpp','kind':'game'},{'id':2,'name':'large.cpp','kind':'game'},{'id':3,'name':'small.cpp','kind':'game'}],'classes':{},'functions':{'1':{'tu':1,'kind':'function','size':100},'2':{'tu':2,'kind':'function','size':60001},'3':{'tu':3,'kind':'function','size':100}}}
 (root/'decomp/src/partial.cpp').write_text('// only one unrelated function recovered\n')
 with patch.object(parallel,'ROOT',root),patch.object(parallel,'claims',lambda:{}),patch.object(parallel,'owners',lambda:{}):
  results['queue']=[x[2] for x in parallel.candidates(db)];assert results['queue']==['small.cpp']
(out/'metadata-results.json').write_text(json.dumps(results,indent=2)+'\n');print(json.dumps(results,indent=2))
