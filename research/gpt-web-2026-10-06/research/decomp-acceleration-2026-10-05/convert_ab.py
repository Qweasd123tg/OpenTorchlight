from pathlib import Path
import json,sys
sys.path.insert(0,'tools/decomp');import elfdb,ghidra_cpp
from rewrite_geometry import rewrite
root=Path('build-decomp/sdk-prototype-experiment');db=elfdb.load_db();methods=ghidra_cpp.known_methods(db);signatures=ghidra_cpp.signatures_of(db);enums=ghidra_cpp.parse_enums();results=[]
for address in (root/'targets.txt').read_text().splitlines():
 row={'address':address,'arms':{}}
 for arm in ('baseline','enriched'):
  raw=(root/arm/(address+'.c')).read_text();converted=ghidra_cpp.convert(raw,methods,db['functions'][address],signatures,enums)
  (root/arm/(address+'.cpp')).write_text(converted)
  repaired,changes=rewrite(raw);repaired=ghidra_cpp.convert(repaired,methods,db['functions'][address],signatures,enums)
  (root/arm/(address+'.geometry.cpp')).write_text(repaired)
  row['arms'][arm]={'converted_lines':len(converted.splitlines()),'geometry_changes':changes,'repaired_lines':len(repaired.splitlines())}
 results.append(row)
Path('research/decomp-acceleration-2026-10-05/results/conversion.json').write_text(json.dumps(results,indent=2)+'\n')
for r in results:print(r['address'],{arm:{'lines':v['converted_lines'],'geometry_calls':len(v['geometry_changes'])} for arm,v in r['arms'].items()})
