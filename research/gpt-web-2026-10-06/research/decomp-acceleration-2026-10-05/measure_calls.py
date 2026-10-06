"""A narrow call-arity diagnostic, not proof of whole-function equivalence."""
from pathlib import Path
import collections,json,re,sys
sys.path.insert(0,'tools/decomp');import ghidra_cpp
root=Path('build-decomp/sdk-prototype-experiment');sdk_all=json.load(open(root/'sdk-prototypes.json'))['prototypes'];applied=json.load(open(root/'enriched-types.json'))['prototypes'];sdk={a:p for a,p in sdk_all.items() if a in applied}
groups=collections.defaultdict(list)
for a,p in sdk.items():
 name=p['name'].split('(',1)[0]
 if 'operator' in name or name.rsplit('::',1)[-1].startswith('~') or name.rsplit('::',1)[-1]==name.split('::')[-2]:continue
 groups[name].append(p)
expected={name:len(ps[0]['params'])+int(not ps[0]['static'])+int(ps[0]['sret']) for name,ps in groups.items() if len(ps)==1}
results=[]
for address in (root/'targets.txt').read_text().splitlines():
 row={'address':address,'arms':{}}
 for arm in ('baseline','enriched'):
  text=(root/arm/(address+'.c')).read_text();text=re.sub(r'/\*.*?\*/','',text,flags=re.S)
  calls=[]
  for name,n in expected.items():
   for m in re.finditer(re.escape(name)+r'\s*\(',text):
    close=ghidra_cpp.closing_paren(text[m.end():]);args=text[m.end():m.end()+close];parts=ghidra_cpp.split_args(args)
    if len(parts)==1 and not parts[0].strip():parts=[]
    calls.append({'name':name,'observed':len(parts),'expected':n,'conformant':len(parts)==n,'arguments':args.strip()})
  row['arms'][arm]={'calls':len(calls),'nonconformant':sum(not c['conformant'] for c in calls),'extraout_markers':text.count('extraout_'),'details':calls}
 results.append(row)
Path('research/decomp-acceleration-2026-10-05/results/call-arity.json').write_text(json.dumps(results,indent=2)+'\n')
for row in results:print(row['address'],{arm:{k:v for k,v in metrics.items() if k!='details'} for arm,metrics in row['arms'].items()})
