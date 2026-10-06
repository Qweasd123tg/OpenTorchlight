"""Diagnostic experiment only. Do not promote unqualified String globally."""
from pathlib import Path
import json
p=Path('build-decomp/sdk-prototype-experiment')
a=json.loads((p/'sdk-prototypes.json').read_text()); b=json.loads((p/'enriched-types.json').read_text())
assert 'String' not in b['classes']
b['classes']['String']=a['classes']['String']
(p/'string-layout-types.json').write_text(json.dumps(b)+'\n')
collisions=[]
for addr,proto in b['prototypes'].items():
 if proto['name'].startswith('Ogre::') and any(x['type']=='String*' for x in proto['params']):
  collisions.append({'address':addr,'name':proto['name'],'params':proto['params']})
Path('research/decomp-acceleration-2026-10-05/string-layout/namespace-collisions.json').write_text(json.dumps(collisions,indent=2)+'\n')
print('Diagnostic input written; namespace collisions:',len(collisions))
