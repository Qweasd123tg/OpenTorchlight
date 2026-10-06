"""Reproduce acceptance collisions with pinned GCC, without touching production."""
from pathlib import Path
import sys,json,subprocess
sys.path.insert(0,'tools/decomp');import toolchain,objdiff,elfimage
out=Path('research/night-audit-2026-10-06/acceptance');out.mkdir(exist_ok=True)

def compile(name,source):
 p=out/(name+'.cpp');p.write_text(source);o=out/(name+'.o');toolchain.compile_source(p,o)
 (out/(name+'.asm')).write_text(subprocess.check_output(['objdump','-drC',str(o)],text=True))
 return o,objdiff.object_functions(o)
results={}
for n in (80,300):
 a,fa=compile('lit'+str(n)+'a','extern "C" void sink(const char*); extern "C" void probe(){sink("'+'A'*n+'X");}\n')
 b,fb=compile('lit'+str(n)+'b','extern "C" void sink(const char*); extern "C" void probe(){sink("'+'A'*n+'Y");}\n')
 results['literal_'+str(n)]={'norm_equal':fa['probe']['norm']==fb['probe']['norm'],'digest_equal':objdiff.code_digest(fa['probe']['norm'])==objdiff.code_digest(fb['probe']['norm']),'norm_a':fa['probe']['norm'],'norm_b':fb['probe']['norm']}
for typ in ('int','double'):
 o,f=compile('catch_'+typ,'extern "C" void raise_value(); extern "C" int probe(){try {raise_value();} catch('+typ+') {return 7;} return 0;}\n')
 image=elfimage.load_object(o);lsda=image.section_bytes(next(s.index for s in image.sections if s.name=='.gcc_except_table'))
 results['catch_'+typ]={'norm':f['probe']['norm'],'digest':objdiff.code_digest(f['probe']['norm']),'lsda_hex':lsda.hex()}
 driver,unused=compile('driver','extern "C" void raise_value(){throw 3;} extern "C" int probe(); int main(){try{return probe();}catch(...){return 99;}}\n')
 exe=out/('catch_'+typ);subprocess.run(['g++','-no-pie',str(o),str(driver),'-o',str(exe)],check=True)
 results['catch_'+typ]['exit']=subprocess.run([str(exe.resolve())]).returncode
results['catch_norm_equal']=results['catch_int']['norm']==results['catch_double']['norm']
(out/'results.json').write_text(json.dumps(results,indent=2)+'\n');print(json.dumps(results,indent=2))
assert all(results['literal_'+str(n)]['norm_equal'] for n in (80,300))
assert results['catch_norm_equal'] and results['catch_int']['exit']==7 and results['catch_double']['exit']==99
print('Reproduced both acceptance gaps with pinned compiler')
