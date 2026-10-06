from pathlib import Path
from unittest.mock import patch
import tempfile,json,copy,sys
sys.path.insert(0,'tools/decomp');import ghidra_draft as g
results={}
with tempfile.TemporaryDirectory() as td:
 root=Path(td);(root/'A.cpp').mkdir()
 db={'original_elf_sha256':'fixture','tus':[{'id':1,'name':'A.cpp'},{'id':2,'name':'B.cpp'}],'functions':{'0x1':{'tu':1},'0x2':{'tu':2}}}
 types={'Child':{'size':16,'fields':[],'bases':[{'name':'Base','offset':0}]},'Base':{'size':8,'fields':[{'name':'x','type':'int','offset':0,'size':4}],'bases':[]}}
 protos={'0x1':{'ret':'int'},'0x2':{'ret':'int'}}
 meta={'elf':'fixture','tools':g.tools_digest(),'classes':g.class_digests(types,{'Child'}),'prototypes':g.prototype_digest(protos,['0x1'])}
 (root/'A.cpp'/'inputs.json').write_text(json.dumps(meta))
 with patch.object(g,'OUT',root),patch.object(g,'_prototypes',lambda:protos):
  results['unchanged']=g.draft_state('A.cpp',db,types)
  protos['0x2']['ret']='double';results['callee_other_tu_return_changed']=g.draft_state('A.cpp',db,types)
  types['Base']['fields'][0]['type']='float';results['referenced_base_layout_changed']=g.draft_state('A.cpp',db,types)
  protos['0x1']['ret']='double';results['own_return_changed']=g.draft_state('A.cpp',db,types)
assert results['unchanged'][0]=='fresh' and results['callee_other_tu_return_changed'][0]=='fresh' and results['referenced_base_layout_changed'][0]=='fresh' and results['own_return_changed'][0]=='stale'
Path('research/night-audit-2026-10-06/staleness.json').write_text(json.dumps(results,indent=2)+'\n');print(json.dumps(results,indent=2))
