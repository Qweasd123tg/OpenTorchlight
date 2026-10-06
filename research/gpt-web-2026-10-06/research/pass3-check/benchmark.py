import sys,inspect,time,statistics,subprocess,json
from pathlib import Path
sys.path.insert(0,str(Path.cwd()/'tools/decomp'));import objdiff
out=Path('/workspace/scratch/3ba0fff8d310/otl-restore-20261006/pass3-check')
s=inspect.getsource(objdiff.object_functions)
s=s.replace('    by_name =', '''    parsed_sections = {name: parse_insns("\\n".join(lines)) for name, lines in sections.items()}
    section_addrs = {name: [i[0] for i in insns] for name, insns in parsed_sections.items()}
    by_name =''')
s=s.replace('        insns = [i for i in parse_insns("\\n".join(sections.get(section.name, [])))\n                 if sym.value <= i[0] < sym.value + sym.size]', '''        addresses = section_addrs.get(section.name, [])
        insns = parsed_sections.get(section.name, [])[bisect.bisect_left(addresses, sym.value):bisect.bisect_left(addresses, sym.value + sym.size)]''')
ns=dict(vars(objdiff));exec(s,ns);fast=ns['object_functions'];results=[]
for n in (50,200,500):
 src=out/('bench'+str(n)+'.cpp');obj=src.with_suffix('.o')
 src.write_text('\n'.join('extern "C" __attribute__((noinline)) unsigned f%d(unsigned x){return (x*7u)^%du;}'%(i,i) for i in range(n)))
 subprocess.run(['g++','-O2','-c',str(src),'-o',str(obj)],check=True)
 a=objdiff.object_functions(obj);b=fast(obj);assert a==b
 times={}
 for name,fn in [('baseline',objdiff.object_functions),('indexed',fast)]:
  ts=[]
  for _ in range(3):
   t=time.perf_counter();fn(obj);ts.append(time.perf_counter()-t)
  times[name]=statistics.median(ts)
 results.append({'functions':n,'same_result':True,'seconds':times,'ratio':times['baseline']/times['indexed']})
(out/'parser-benchmark.json').write_text(json.dumps(results,indent=2)+'\n');(out/'indexed-function.py.txt').write_text(s);print(json.dumps(results,indent=2))
