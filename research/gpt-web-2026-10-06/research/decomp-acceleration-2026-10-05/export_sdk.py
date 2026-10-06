"""Experiment only: declarations for imported SDK symbols, no production edits."""
import json,subprocess,sys,time
from pathlib import Path
sys.path.insert(0,'tools/decomp')
import types_export,toolchain
root=Path('build-decomp/sdk-prototype-experiment');root.mkdir(parents=True,exist_ok=True)
toolchain.compile_source(Path('research/decomp-acceleration-2026-10-05/sdk_headers.cpp'),root/'sdk_headers.o',['-g','-O0','-fno-eliminate-unused-debug-types','-femit-class-debug-always'])
t=time.monotonic()
dies=types_export.parse_dies(root/'sdk_headers.o')
# Recover names on GCC's out-of-line type-definition DIEs from their declarations.
# Do NOT inherit DW_AT_declaration onto a completed definition.
resolved=0
for d in dies.values():
 spec=dies.get(d['attrs'].get('DW_AT_specification'))
 if spec:
  for key in ('DW_AT_name','DW_AT_linkage_name','DW_AT_type'):
   if key not in d['attrs'] and key in spec['attrs']:d['attrs'][key]=spec['attrs'][key];resolved+=1
# Canonicalize aliases such as Ogre::Real -> float. Leaving Real as an opaque
# 4-byte integer would move float return values from XMM0 to EAX in Ghidra.
_original_type_name=types_export.type_name
def canonical_type_name(dies,ref,depth=0):
 d=dies.get(ref)
 if d and d['tag']=='DW_TAG_typedef' and depth<20:
  return canonical_type_name(dies,d['attrs'].get('DW_AT_type'),depth+1)
 return _original_type_name(dies,ref,depth)
types_export.type_name=canonical_type_name
db=json.load(open('build-decomp/db/elfdb.json'));classes=types_export.header_classes(dies)
selected={a:n for a,n in db['imports']['plt'].items() if n.startswith(('_ZN4Ogre','_ZNK4Ogre','_ZN5CEGUI','_ZNK5CEGUI'))}
names=subprocess.check_output(['c++filt',*selected.values()],text=True).splitlines()
synthetic={'functions':{},'classes':classes}
for (address,mangled),name in zip(selected.items(),names):
 before=name.split('(',1)[0];scope=before.rsplit('::',1)[0] if '::' in before else ''
 synthetic['functions'][address]={'names':[mangled],'scope':scope,'demangled':name}
prototypes=types_export.prototypes(dies,synthetic,set(),set())
# SDK scopes are qualified, while the legacy class map is unqualified. Determine
# an implicit this from DWARF, not membership of that lossy name map.
static_flags={}
for d in dies.values():
 link=d['attrs'].get('DW_AT_linkage_name')
 if d['tag']!='DW_TAG_subprogram' or not link or link in static_flags:continue
 params=[dies[c] for c in d['children'] if dies[c]['tag']=='DW_TAG_formal_parameter']
 static_flags[link]=not(bool(params) and bool(params[0]['attrs'].get('DW_AT_artificial')))
for address,p in prototypes.items():
 p['mangled']=selected[address]
 p['static']=static_flags[selected[address]]
 p['complete_types']='?' not in p['ret'] and all('?' not in a['type'] for a in p['params'])
 if not p['complete_types']:p['trusted']=False
 p['source']='pinned Ogre 1.6.5 / vendored CEGUI 0.6.2 headers, GCC 4.4.7 DWARF'
 p['abi_validation']='header-derived; disassembly/compiler-probe check pending'
for name in ('Vector3','Quaternion'):
 assert all(f['type']=='float' for f in classes[name]['fields'] if f['size']==4),(name,classes[name])
assert prototypes['0x553c78']['static']
assert prototypes['0x555fc8']['static'] and prototypes['0x555fc8']['sret']
assert prototypes['0x5560d8']['sret'] and not prototypes['0x5560d8']['static']
assert prototypes['0x555ba8']['ret']=='float'
result={'sdk_imports' :len(selected),'exported':len(prototypes),'trusted_by_existing_rule':sum(p['trusted'] for p in prototypes.values()),'hidden_returns':sum(p['sret'] for p in prototypes.values()),'resolved_die_attributes':resolved,'complete_prototypes':sum(p['complete_types'] for p in prototypes.values()),'static_or_free':sum(p['static'] for p in prototypes.values()),'seconds':time.monotonic()-t,'prototypes':prototypes,'classes':classes}
(root/'sdk-prototypes.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps({k:v for k,v in result.items() if k not in ('prototypes','classes')}))
for address in ['0x554718','0x5548a8','0x555178','0x5532a8','0x5560d8','0x552ab8','0x5545c8','0x554d48']:
 print(address,prototypes.get(address))
