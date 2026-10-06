import re,json,collections,pathlib
root=pathlib.Path('/workspace/scratch/3ba0fff8d310/otl-restore-20261006/dot-all-work-2026-10-05/OpenTorchlight/source')
token=re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*|0x[0-9a-fA-F]+|\d+(?:\.\d+)?|[A-Za-z_]\w*|>>|<<|->|::|==|!=|<=|>=|&&|\|\||\S',re.S)
def body(file,name):
 text=(root/'research/decompiled-core'/file).read_text()
 pieces=re.split(r'(?=/\* address=)',text)
 piece=next(p for p in pieces if re.search(r'symbol='+re.escape(name)+r' \*/',p))
 ts=[x for x in token.findall(piece) if not x.startswith(('/*','//'))]
 ts=ts[ts.index('{'):]
 ren={}
 labels={}
 for i,x in enumerate(ts):
  if re.fullmatch(r'(?:\w*Var\d+|local_[0-9a-f]+|this_\d+)',x):
   ts[i]=ren.setdefault(x,'TEMP_'+str(len(ren)))
  if re.fullmatch(r'LAB_[0-9a-f]+',x):
   ts[i]=labels.setdefault(x,'LABEL_'+str(len(labels)))
 return ts
spec=[('merchant_menu.c','CMerchantMenu::setPetSlotIcon'),('stash_menu.c','CStashMenu::setPetSlotIcon'),('stash_menu.c','CStashMenu::setSlotIcon')]
b=[body(*s) for s in spec]
out=[]
for k in (1,2):
 a,c=b[k-1],b[k]
 dif=collections.Counter((x,y) for x,y in zip(a,c) if x!=y)
 out.append({'from':spec[k-1][1],'to':spec[k][1],'tokens':[len(a),len(c)],'different_positions':sum(dif.values()),'substitutions':[{'old':x,'new':y,'count':n} for (x,y),n in dif.items()]})
print(json.dumps(out,indent=2))
