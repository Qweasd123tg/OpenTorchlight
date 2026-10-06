from pathlib import Path
import sys,json
sys.path.insert(0,'tools/decomp');import calls
tr=calls.Tracer.__new__(calls.Tracer)
f={'address':'0x0','params':'int','scope':None,'kind':'function'}
tr.insns={'0x0':[(0,'test','%edi,%edi',''),(2,'jne','20',''),(4,'mov','$0x1,%edi',''),(9,'jmp','30',''),(0x20,'mov','$0x2,%edi',''),(0x30,'call','100','sink'),(0x35,'ret','','')]}
tr.by_name={'sink':{'address':'0x100','demangled':'sink(int)','scope':None,'kind':'function','params':'int'}};tr.plt={};tr.immediate=lambda x:('imm',x)
lines=tr.trace(f);assert any('sink(2)' in x for x in lines)
result={'trace':lines,'actual_join_values':[1,2],'scope':'synthetic branch CFG, existing human-readable linear tracer; not proof any current descriptor was misgenerated','recommendation':'generator must track per-block state and join conflicting values to unknown or phi; never emit unconditional constant from this trace'}
Path('research/night-audit-2026-10-06/branch-trace.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result))
