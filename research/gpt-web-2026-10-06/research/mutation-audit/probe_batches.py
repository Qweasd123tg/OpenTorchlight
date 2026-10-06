from pathlib import Path
import sys,subprocess,json
sys.path.insert(0,str(Path.cwd()/'tools/decomp'));import mutate
out=Path('/workspace/scratch/3ba0fff8d310/otl-restore-20261006/mutation-audit')
base='''#include <cstdio>
int helper(int) __attribute__((noinline));
int caller(int) __attribute__((noinline));
int (* volatile dispatch)(int)=helper;
int helper(int x){return x+10;}
int caller(int x){if(x==0)return 7;return dispatch(x);}
int main(){printf("%d %d\\n",caller(1),helper(1));}
'''
rows={};asms={}
for label,am,bm in [('baseline',False,False),('caller_only',True,False),('helper_only',False,True),('both',True,True)]:
 text=base.replace('return 7','return 8') if am else base
 if bm:text=text.replace('x+10','x+20')
 f=out/(label+'.cpp');f.write_text(text)
 subprocess.run(['g++','-std=c++98','-O2','-S',str(f),'-o',str(f.with_suffix('.s'))],check=True)
 subprocess.run(['g++','-std=c++98','-O2',str(f),'-o',str(out/label)],check=True)
 rows[label]=subprocess.check_output([str(out/label)],text=True).strip()
 asms[label]=mutate.functions_in_asm(f.with_suffix('.s').read_text())
known=set(asms['baseline']);refs=mutate.references(asms['baseline'],known)
def reach(name):
 seen=set();todo=[name]
 while todo:
  n=todo.pop()
  if n not in seen:seen.add(n);todo.extend(refs.get(n,()))
 return seen
ca='_Z6calleri';he='_Z6helperi';affA={n for n in known|set(asms['caller_only']) if asms['baseline'].get(n)!=asms['caller_only'].get(n)};affB={n for n in known|set(asms['helper_only']) if asms['baseline'].get(n)!=asms['helper_only'].get(n)}
allowed=not(reach(ca)&affB) and not(reach(he)&affA)
r={'outputs_caller_then_helper':rows,'caller_references':sorted(refs[ca]),'caller_reach':sorted(reach(ca)),'helper_reach':sorted(reach(he)),'caller_mutation_affected':sorted(affA),'helper_mutation_affected':sorted(affB),'existing_reach_conflict_check_allows_batch':allowed,'scope':'real functions_in_asm/references and real compiled synthetic programs; whole Torchlight mutation runner not executed'}
assert rows['baseline']==rows['caller_only']=='11 11';assert rows['helper_only']==rows['both']=='21 21';assert allowed
(out/'batch-results.json').write_text(json.dumps(r,indent=2)+'\n');print(json.dumps(r,indent=2))
