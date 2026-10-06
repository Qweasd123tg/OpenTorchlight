#!/usr/bin/env python3
"""Benchmark a section-indexed equivalent of objdiff.object_functions.

Only reads the checkout. Creates synthetic object files in a temp directory.
This preserves the old normalizer, including its known semantic limitations.
"""
from __future__ import annotations
import argparse,bisect,json,pathlib,re,statistics,subprocess,sys,tempfile,time


def fast_object_functions(mod,obj_path,resolve=None,name_at=None,globalized=()):
    obj=mod.elfimage.load_object(obj_path)
    text=mod.run_objdump([str(obj_path)])
    sections={};current=None
    for line in text.splitlines():
        m=re.match(r'^Disassembly of section (.+):$',line)
        if m:current=m.group(1);sections[current]=[];continue
        if current is not None:sections[current].append(line)
    parsed={name:mod.parse_insns('\n'.join(lines)) for name,lines in sections.items()}
    offsets={name:[i[0] for i in rows] for name,rows in parsed.items()}
    ordered={name:all(a<=b for a,b in zip(vals,vals[1:])) for name,vals in offsets.items()}
    by_name={s.name:s.index for s in obj.sections};side=mod.ObjectSide(obj,resolve,name_at);result={}
    for sym in obj.symbols:
        if sym.type!=mod.elfimage.STT_FUNC or not sym.defined:continue
        section=obj.sections[sym.shndx];rows=parsed.get(section.name,[])
        if ordered.get(section.name,True):
            vals=offsets.get(section.name,[])
            insns=rows[bisect.bisect_left(vals,sym.value):bisect.bisect_left(vals,sym.value+sym.size)]
        else:
            insns=[i for i in rows if sym.value<=i[0]<sym.value+sym.size]
        side.prepare(by_name[section.name]);side.current=sym.name
        bind=mod.elfimage.STB_LOCAL if sym.name in globalized else sym.bind
        result[sym.name]={'size':sym.size,'bind':bind,'norm':side.normalize(insns,sym.value,sym.value+sym.size)}
    return result


def measured(fn,mod,path,repeats=3):
    times=[];counts=[];ret=None
    original=mod.parse_insns
    for _ in range(repeats):
        count=[0,0]
        def wrapped(text):
            count[0]+=1;count[1]+=len(text);return original(text)
        mod.parse_insns=wrapped
        try:
            start=time.perf_counter();value=fn(path);times.append(time.perf_counter()-start)
        finally:mod.parse_insns=original
        counts.append(count)
        if ret is not None:assert value==ret
        ret=value
    return {'median_seconds':statistics.median(times),'samples_seconds':times,'parse_calls':counts[0][0],'parsed_text_characters':counts[0][1]},ret


def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('root',type=pathlib.Path);p.add_argument('--out',type=pathlib.Path,default=pathlib.Path('parser-benchmark.json'));p.add_argument('--sizes',nargs='+',type=int,default=[50,200,500]);p.add_argument('--repeats',type=int,default=3);args=p.parse_args()
    sys.path.insert(0,str(args.root.resolve()/'tools/decomp'));import objdiff
    data={'scope':'Synthetic system-GCC objects; complete function dictionaries must remain equal. No Torchlight ELF or GCC 4.4.7 benchmark.','cases':[]}
    with tempfile.TemporaryDirectory(prefix='otl-parse-') as d:
        work=pathlib.Path(d)
        for n in args.sizes:
            source='\n'.join(f'extern "C" __attribute__((noinline)) unsigned fn_{i}(unsigned x) {{ return (x * {2*i+3}u) ^ {i+17}u; }}' for i in range(n))
            cpp=work/f'{n}.cpp';obj=work/f'{n}.o';cpp.write_text(source)
            subprocess.run(['g++','-std=gnu++98','-O2','-fno-ipa-icf','-c',str(cpp),'-o',str(obj)],check=True,timeout=30)
            old,old_result=measured(objdiff.object_functions,objdiff,obj,args.repeats)
            new,new_result=measured(lambda path:fast_object_functions(objdiff,path),objdiff,obj,args.repeats)
            assert old_result==new_result,f'output differs for {n}'
            row={'functions':len(old_result),'old':old,'indexed':new,'ratio':old['median_seconds']/new['median_seconds'],'outputs_identical':True}
            data['cases'].append(row);print(json.dumps(row),flush=True)
        mixed=r'''
#include <string>
extern void sink(const char*);
extern void may_throw();
static unsigned table[]={3,5,7,11,13};
struct Base { virtual ~Base(); virtual int f(int); };
Base::~Base() {} int Base::f(int x) { return x+17; }
struct Other { virtual ~Other(); }; Other::~Other() {}
struct Child:Base,Other { virtual ~Child(); };Child::~Child() {}
extern "C" unsigned dispatch(unsigned x) { switch(x) { case 0:return 13;case 1:return 27;case 2:return 17;case 3:return 4;default:return x*7; } }
extern "C" void strings() { sink("some literal");sink("same prefix 0123456789"); }
extern "C" int excepts() { try { may_throw(); } catch(int) { return 7; } return 0; }
extern "C" unsigned lookup(unsigned x) { return table[x%5]; }
extern "C" unsigned recursive(unsigned x) { if(x<2)return x;return recursive(x-1)+recursive(x-2); }
'''
        cpp=work/'mixed.cpp';obj=work/'mixed.o';cpp.write_text(mixed)
        subprocess.run(['g++','-std=gnu++98','-O2','-c',str(cpp),'-o',str(obj)],check=True,timeout=30)
        old=objdiff.object_functions(obj);new=fast_object_functions(objdiff,obj)
        assert old==new,'mixed output differs'
        data['mixed_regression']={'functions':len(old),'outputs_identical':True,'features':['multiple text sections','virtual destructors','multiple inheritance thunks','literals','exception handler','data references','recursion','switch']}
    args.out.parent.mkdir(parents=True,exist_ok=True);args.out.write_text(json.dumps(data,indent=2))
    return 0
if __name__=='__main__':sys.exit(main())
