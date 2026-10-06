from pathlib import Path
import sys,json,re,subprocess,collections
sys.path.insert(0,'tools/decomp');import objdiff,elfdb
out=Path('research/decomp-acceleration-2026-10-05/clone-delta');db=elfdb.load_db();elf=elfdb.elf_path() if hasattr(elfdb,'elf_path') else Path('../game/Torchlight.bin.x86_64')
rows=[]
for address in (0xb6ab50,0xbf7cc0):
 f=db['functions'][hex(address)];text=objdiff.run_objdump([str(elf),f'--start-address={address}',f'--stop-address={address+f["size"]}']);(out/(hex(address)+'.asm')).write_text(text);ins=objdiff.parse_insns(text);rows.append(ins)
assert len(rows[0])==len(rows[1])
def normalize_exact(ins):
 index={a:i for i,(a,m,o) in enumerate(ins)};r=[]
 for a,m,o in ins:
  if m.startswith('j'):
   dest=int(o.split()[0],16);o='branch-index:'+str(index.get(dest,'EXTERNAL:'+hex(dest)))
  elif m.startswith('call'):
   o=o.split('<')[0].strip() # absolute same target required, including PLT
  else:
   # Resolve RIP-relative address, not merely its different displacement.
   if '%rip' in o and '#' in o:
    suffix=o.split('#',1)[1].strip().split()[0];o=re.sub(r'-?0x[0-9a-f]+\(%rip\)', 'ABS:'+suffix,o.split('#')[0].strip())
   o=re.sub(r'<[^>]+>','',o).strip()
  r.append((m,o))
 return r
normal=[normalize_exact(ins) for ins in rows]
deltas=[{'index':i,'a':rows[0][i],'b':rows[1][i],'normalized_a':a,'normalized_b':b} for i,(a,b) in enumerate(zip(*normal)) if a!=b]
result={'instruction_counts':[len(r) for r in rows],'different_instructions':len(deltas),'deltas':deltas,'caveat':'Instruction comparison only; no runtime, exception table or aliasing proof'}
(out/'delta.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result,indent=2))

# Guard against the old shape cluster's deliberately loose masking.
assert len(deltas)==8
assert all(x['normalized_a']==('mov','0x3440(%rbp),%rdi') and x['normalized_b']==('mov','0x3410(%rbp),%rdi') for x in deltas)
assert normalize_exact([[0,'mov','$0x20,%eax']]) != normalize_exact([[0,'mov','$0x21,%eax']])
assert normalize_exact([[0,'call','1234 <a>']]) != normalize_exact([[0,'call','1235 <b>']])
assert normalize_exact([[0,'mov','0x8(%rbp),%rax']]) != normalize_exact([[0,'mov','0x10(%rbp),%rax']])
assert normalize_exact([[0,'je','10'],[16,'ret','']]) != normalize_exact([[0,'je','0'],[16,'ret','']])
assert normalize_exact([[0,'mov','0x10(%rip),%rax # 1234 <a>']]) == normalize_exact([[20,'mov','0x20(%rip),%rax # 1234 <a>']])
print('Five normalization guards PASS; eight exact field-offset deltas PASS')
