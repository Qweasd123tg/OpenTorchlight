from pathlib import Path
import copy,json
root=Path('research/decomp-acceleration-2026-10-05');out=Path('build-decomp/sdk-prototype-experiment');sdk=json.load(open(out/'sdk-prototypes.json'));base=json.load(open('build-decomp/types.json'))
selected=['0x8ac190','0x92b4b0','0xba26b0','0xa06b30','0x87f880']
(out/'targets.txt').write_text('\n'.join(selected)+'\n')
(out/'baseline-types.json').write_text(json.dumps(base)+'\n')
enriched=copy.deepcopy(base)
# Only small, unambiguous, fully represented ABI value types. Do not inject the
# whole SDK class map: unqualified names and multidimensional arrays need care.
small=['UDim','UVector2','Vector3','Quaternion','ColourValue','colour']
added=[]
for name in small:
 entry=sdk['classes'].get(name)
 if entry and name not in enriched['classes'] and all('[' not in f['type'] and '?' not in f['type'] for f in entry['fields']):enriched['classes'][name]=entry;added.append(name)
scalar={'void','bool','char','signed char','unsigned char','short int','short unsigned int','int','unsigned int','long int','long unsigned int','long long int','long long unsigned int','float','double','wchar_t'}
def safe_shape(p):
 if not p['complete_types'] or not p['trusted']:return False
 # Unknown by-value objects may use SSE registers or invisible references.
 # Keep the original inference until their complete ABI has a separate check.
 if any(a['type'] not in scalar and not a['type'].endswith('*') for a in p['params']):return False
 return p['sret'] or p['ret'] in scalar or p['ret'].endswith('*') or p['ret'] in added
protos={a:p for a,p in sdk['prototypes'].items() if safe_shape(p)}
rejected={a:p['name'] for a,p in sdk['prototypes'].items() if a not in protos}
(root/'results/excluded-sdk-shapes.json').write_text(json.dumps(rejected,indent=2)+'\n')
enriched['prototypes'].update(protos)
(out/'enriched-types.json').write_text(json.dumps(enriched)+'\n')
java=Path('tools/decomp/ghidra/DecompDrafts.java').read_text().replace('public class DecompDrafts','public class SDKPrototypeAB')
java=java.replace('decompiler.setOptions(new DecompileOptions());','DecompileOptions options = new DecompileOptions();\n            options.setMaxPayloadMBytes(128);\n            decompiler.setOptions(options);\n            decompiler.toggleSyntaxTree(false);')
java=java.replace('callback.setTimeout(120);','callback.setTimeout(600);')
(root/'SDKPrototypeAB.java').write_text(java)
meta={'targets':selected,'negative_control':'0x87f880 (accepted, no SDK calls)','SDK_added_prototypes':len(protos),'SDK_added_value_layouts':added,'timeout_seconds':600,'payload_MiB':128,'script_base':'2464d59 DecompDrafts.java; common resource settings changed identically for A/B','not_fixed_here':'protoType(void) falls back to inferred return; retained in both arms to isolate SDK delta'}
(root/'results/ab-design.json').write_text(json.dumps(meta,indent=2)+'\n')
print(json.dumps(meta))
