"""Select reproducible read-only large-function candidates from the supplied snapshot."""
from pathlib import Path
import bisect,collections,json,os,re,subprocess
out=Path('build-decomp/sdk-prototype-experiment');out.mkdir(exist_ok=True)
db=json.load(open('build-decomp/db/elfdb.json'));accepted=set(json.load(open('../repo/build-decomp/progress.json'))['accepted'])
headers=json.load(open(out/'sdk-prototypes.json'));sdk=set(headers['prototypes'])
asm=out/'original.asm'
if not asm.exists():
 with asm.open('w') as f:subprocess.run(['objdump','-d','--no-show-raw-insn',str(Path(os.environ['TORCHLIGHT_GAME_DIR'])/'Torchlight.bin.x86_64')],stdout=f,check=True)
functions=db['functions'];addresses=sorted(int(a,16) for a in functions);calls=collections.defaultdict(collections.Counter)
for line in asm.open():
 m=re.match(r'\s*([0-9a-f]+):\s+callq?\s+([0-9a-f]+)\s',line)
 if not m:continue
 site,target=[int(a,16) for a in m.groups()];index=bisect.bisect_right(addresses,site)-1
 if index<0:continue
 address=hex(addresses[index]);function=functions[address]
 if site>=addresses[index]+function['size']:continue
 calls[address][hex(target)]+=1
rows=[];tu={t['id']:t for t in db['tus']};large=collections.Counter()
for address,f in functions.items():
 if f['kind'] not in ('function','ctor','dtor','static') or tu[f['tu']]['kind']!='game' or f['size']<1024:continue
 raw=Path('../incoming-drafts-2464d59/drafts')/tu[f['tu']]['name']/'raw'/(address+'.c')
 text=raw.read_text(errors='replace') if raw.exists() else ''
 state='missing' if not text else 'failed' if text.startswith('// failed:') else 'available'
 large[state]+=1
 if address in accepted or f['scope'] in ('CEquipment','CGameUI') or not 2048<=f['size']<=24000:continue
 covered={a:n for a,n in calls[address].items() if a in sdk}
 if not covered:continue
 rows.append({'address':address,'name':f['demangled'],'original_bytes':f['size'],'tu':tu[f['tu']]['name'],'draft':state,'draft_lines':len(text.splitlines()),'sdk_calls':sum(covered.values()),'sdk_distinct':len(covered),'sdk_targets':[{'address':a,'count':n,'name':headers['prototypes'][a]['name']} for a,n in covered.items()]})
rows.sort(key=lambda r:(r['sdk_distinct'],r['sdk_calls']),reverse=True)
result={'large_draft_status':dict(large),'candidate_count':len(rows),'candidates':rows}
Path('research/decomp-acceleration-2026-10-05/results/candidates.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps({'large_draft_status':dict(large),'candidate_count':len(rows)}))
for r in rows[:20]:print(r['address'],r['original_bytes'],r['draft'],r['sdk_calls'],r['sdk_distinct'],r['name'])
