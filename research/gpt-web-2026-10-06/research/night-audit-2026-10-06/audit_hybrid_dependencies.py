from pathlib import Path
import json,subprocess,collections,sys,hashlib
sys.path.insert(0,'tools/decomp');import elfdb,elfimage
p=Path('build-decomp/hybrid');m=json.loads((p/'manifest.json').read_text());db=elfdb.load_db();image=elfimage.load(elfdb.default_elf());hooks={int(x['original'],16) for x in m['hooks']};functions={int(a,16):f for a,f in db['functions'].items()};rows=[]
for line in subprocess.check_output(['nm','-an',str(p/'tlhybrid-blob.elf')],text=True).splitlines():
 cols=line.split()
 if len(cols)!=3 or cols[1]!='A':continue
 address=int(cols[0],16);name=cols[2];sec=image.section_at(address)
 if not sec:continue
 if name.startswith('__tlorig_'):kind='explicit_original_test_oracle'
 elif address in image.plt:kind='original_plt'
 elif name.startswith('_ZTV'):kind='original_vtable'
 elif name.startswith(('_ZTI','_ZTS')):kind='original_rtti_or_type_name'
 elif address in functions:kind='original_function_hooked' if address in hooks else 'original_function_unhooked'
 else:kind='original_data_or_other'
 rows.append({'name':name,'address':hex(address),'section':sec.name,'kind':kind})
r={'blob_sha256':hashlib.sha256((p/'tlhybrid-blob.elf').read_bytes()).hexdigest(),'original_elf_sha256':image.sha256,'hooks':len(hooks),'runtime_imports':len(m['runtime_imports']),'runtime_copies':m['runtime_copies'],'absolute_symbol_counts':dict(collections.Counter(x['kind'] for x in rows)),'rows':rows,'scope':'symbol inventory, not reachable-code analysis; includes test-only references and alias duplicates; not standalone dependency closure'}
Path('research/night-audit-2026-10-06/hybrid-dependencies.json').write_text(json.dumps(r,indent=2)+'\n');print({k:v for k,v in r.items() if k!='rows'})
