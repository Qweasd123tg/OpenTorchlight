import re,pathlib,difflib,json
root=pathlib.Path('/workspace/scratch/3ba0fff8d310/otl-restore-20261006/dot-all-work-2026-10-05/OpenTorchlight/source/research/decompiled-core')
pat=re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*|0x[0-9a-fA-F]+|\d+(?:\.\d+)?|[A-Za-z_]\w*|>>|<<|->|::|==|!=|<=|>=|&&|\|\||\S',re.S)
def get(file,owner):
 text=(root/file).read_text();parts=re.split(r'(?=/\* address=)',text)
 raw=next(p for p in parts if 'symbol='+owner+'::setSlotIcon */' in p)
 # Hand-selected first executable statement, only for these two archive bodies.
 raw=raw[raw.index('lVar16 = (long)param_2;'):]
 tokens=[t for t in pat.findall(raw) if not t.startswith(('/*','//'))]
 keys=[]
 for t in tokens:
  if re.fullmatch(r'(?:\w*Var\d+|local_[0-9a-f]+|this_\d+)',t):k='TEMP'
  elif re.fullmatch(r'LAB_[0-9a-f]+',t):k='LABEL'
  elif t==owner:k='OWNER'
  else:k=t
  keys.append(k)
 return tokens,keys
a,ak=get('merchant_menu.c','CMerchantMenu');b,bk=get('stash_menu.c','CStashMenu')
s=difflib.SequenceMatcher(None,ak,bk,autojunk=False)
changes=[]
for tag,i,j,k,l in s.get_opcodes():
 if tag!='equal': changes.append({'kind':tag,'source_tokens':a[i:j],'target_tokens':b[k:l],'source_start':i,'target_start':k,'context_before':a[max(0,i-8):i]})
out={'scope':'NAVIGATION_ONLY. Temporary identities erased for alignment; no equivalence proof. Declarations omitted by hand-selected boundary. Constants and calls retained.','tokens':[len(a),len(b)],'matched_tokens':sum(m.size for m in s.get_matching_blocks()),'changes':changes}
print(json.dumps(out,indent=2))
