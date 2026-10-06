from pathlib import Path
import sys,subprocess,json
base=Path('/workspace/scratch/3ba0fff8d310/otl-restore-1522')
root=base/'dot-all-work-2026-10-05/OpenTorchlight/source'
out=base/'table-audit'
sys.path.insert(0,str(root/'tools/decomp'))
import name_tables
obj=name_tables.Tables.__new__(name_tables.Tables)
obj.recover=lambda *args:({'demangled':'sample','file':'sample.cpp'},(('std::wstring','L'),['FIRST',None,'THIRD'],[1]))
generated=obj.definition('sample')
program='#include <string>\n#include <cstdio>\n'+generated+'\nint main(){std::printf("count=%lu slot1_is_THIRD=%d\\n",(unsigned long)(sizeof(sample)/sizeof(sample[0])),sample[1]==L"THIRD");}\n'
(out/'generated.cpp').write_text(program)
subprocess.run(['g++','-std=gnu++98','-O2',str(out/'generated.cpp'),'-o',str(out/'probe')],check=True)
r=subprocess.run([str(out/'probe')],capture_output=True,text=True,check=True)
assert r.stdout=='count=2 slot1_is_THIRD=1\n'
res={'scope':'Actual name_tables.Tables.definition with synthetic recover result. No original ELF or recovered game table used.','generated':generated,'runtime':r.stdout.strip(),'expected_logical_slot_count':3,'actual_slot_count':2,'source_changed':False}
(out/'result.json').write_text(json.dumps(res,indent=2));print(json.dumps(res,indent=2))
