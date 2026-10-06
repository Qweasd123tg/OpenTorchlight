#!/usr/bin/env python3
"""Measure an opt-in compiler cache on unchanged real sources. Does NOT compare to original ELF."""
import argparse,pathlib,subprocess,time,statistics,hashlib,json,tempfile,shutil,random
p=argparse.ArgumentParser();p.add_argument('repo',type=pathlib.Path);p.add_argument('out',type=pathlib.Path);p.add_argument('--repeats',type=int,default=9);a=p.parse_args();a.repo=a.repo.resolve();a.out.mkdir(parents=True,exist_ok=True)
flags=['-std=gnu++98','-O2','-fno-strict-aliasing','-DNDEBUG','-D_GLIBCXX_USE_CXX11_ABI=0','-I',str(a.repo/'decomp/include'),'-I',str(a.repo/'third_party/ogre-1.6.5-math/OgreMain/include'),'-I',str(a.repo/'third_party/cegui-0.6.2/include')]
compiler=shutil.which('g++');assert compiler
rows=[]
with tempfile.TemporaryDirectory(prefix='otl-pch-') as td:
 td=pathlib.Path(td);h=td/'prefix.h';h.write_text('#include "EmptyStrings.h"\n')
 cmd=[compiler,*flags,'-x','c++-header',str(h),'-o',str(h)+'.gch'];t=time.perf_counter();r=subprocess.run(cmd,capture_output=True,text=True,timeout=30);r.check_returncode();build=time.perf_counter()-t
 for name in ['BinaryStyle.cpp','utilities.cpp']:
  src=a.repo/'decomp/src'/name
  if not src.read_text().lstrip().startswith('#include "EmptyStrings.h"'):raise RuntimeError('prefix is not exactly the first include: '+name)
  opt=['-include',str(h),'-Winvalid-pch']
  probe=subprocess.run([compiler,*flags,*opt,'-H','-c',str(src),'-o',str(td/'probe.o')],capture_output=True,text=True,timeout=30)
  probe.check_returncode();used=any(line.startswith('! ') and '.gch' in line for line in probe.stderr.splitlines())
  if not used:raise RuntimeError('PCH was not used: '+probe.stderr[:1000])
  times={'plain':[],'pch':[]};hashes={'plain':set(),'pch':set()};sizes={}
  for rnd in range(a.repeats+1):
   order=['plain','pch'] if rnd%2==0 else ['pch','plain']
   for mode in order:
    dest=td/(mode+'.o');cmd=[compiler,*flags,* (opt if mode=='pch' else []),'-c',str(src),'-o',str(dest)]
    t=time.perf_counter();r=subprocess.run(cmd,capture_output=True,text=True,timeout=30);elapsed=time.perf_counter()-t;r.check_returncode()
    if rnd:times[mode].append(elapsed)
    data=dest.read_bytes();hashes[mode].add(hashlib.sha256(data).hexdigest());sizes[mode]=len(data)
  med={k:statistics.median(v) for k,v in times.items()}
  row={'source':'decomp/src/'+name,'seconds':times,'median_seconds':med,'ratio':med['plain']/med['pch'],'pch_confirmed_used':used,'object_bytes':sizes,'object_sha256':{k:sorted(v) for k,v in hashes.items()},'objects_byte_identical':len(hashes['plain'])==1 and hashes['plain']==hashes['pch']}
  rows.append(row)
report={'compiler':subprocess.check_output([compiler,'--version'],text=True).splitlines()[0],'flags':flags,'pch_build_seconds':build,'repeats_per_mode':a.repeats,'warmup_per_mode':1,'rows':rows,'scope':'Compiler-only benchmark, no cc-cache, unchanged real source files, host GCC; no game equivalence or whole-pipeline speedup measured'}
(a.out/'pch-benchmark.json').write_text(json.dumps(report,indent=2))
for r in rows:print(r['source'],{k:round(v*1000,2) for k,v in r['median_seconds'].items()},'ratio',round(r['ratio'],2),'identical',r['objects_byte_identical'])
print('build_seconds',build)
