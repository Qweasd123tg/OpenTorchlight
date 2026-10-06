#!/usr/bin/env python3
"""Compile extracted expressions against bundled CEGUI with synthetic owner classes.
This validates generation and library layout, not the original game's callbacks.
"""
from __future__ import annotations
import argparse,json,subprocess
from collections import defaultdict
from pathlib import Path

EXTRA=r'''
struct PmfBits { intptr_t target, adjustment; };
struct AdapterBits { void* vptr; PmfBits pmf; void* receiver; };
template<class T> AdapterBits view(const CEGUI::MemberFunctionSlot<T>& slot) {
    AdapterBits b;
    if (sizeof(b)!=sizeof(slot)) { std::cerr<<"unsupported adapter ABI";std::exit(2); }
    std::memcpy(&b,&slot,sizeof(b)); return b;
}
struct First { virtual ~First(){}; int a; };
struct Second {
    virtual ~Second(){};
    virtual bool changed(const CEGUI::EventArgs&) { trace_value=701;return false; }
    bool direct(const CEGUI::EventArgs&) { trace_value=702;return true; }
};
struct Derived: First,Second {
    bool changed(const CEGUI::EventArgs&) { trace_value=703;return true; }
};
int test_pmf() {
    int errors=0; CEGUI::EventArgs e; Derived d;
    typedef bool(Derived::*P)(const CEGUI::EventArgs&);
    P v=static_cast<P>(&Second::changed), n=static_cast<P>(&Second::direct);
    CEGUI::MemberFunctionSlot<Derived> sv(v,&d), sn(n,&d);
    AdapterBits vb=view(sv),nb=view(sn);
    const intptr_t adjustment=reinterpret_cast<char*>(static_cast<Second*>(&d))-reinterpret_cast<char*>(&d);
    trace_value=0; if(!sv(e)||trace_value!=703) ++errors;
    trace_value=0; if(!sn(e)||trace_value!=702) ++errors;
    if(!(vb.pmf.target&1)||!adjustment||vb.pmf.adjustment!=adjustment||nb.pmf.adjustment!=adjustment) ++errors;
    if(nb.pmf.target&1) ++errors;
    if(vb.receiver!=&d||nb.receiver!=&d) ++errors;
    std::cout<<"PMF "<<adjustment<<" "<<vb.pmf.target<<" "<<vb.pmf.adjustment<<" "<<errors<<"\n";
    return errors;
}
'''

def run(root,out,recipes):
    out.mkdir(parents=True,exist_ok=True)
    rows=[r for r in recipes['recipes'] if 'construction_candidate'in r]
    classes=defaultdict(list)
    for i,r in enumerate(rows): classes[r['adapter_type']].append((i,r))
    callbacks={}; counter=0
    lines=['// SYNTHETIC OWNERS ONLY. No game logic or original class layout is tested.',
      '#include "CEGUISubscriberSlot.h"','#include "CEGUIEventArgs.h"','#include <stdint.h>',
      '#include <cstring>','#include <cstdlib>','#include <iostream>','static int trace_value=0;']
    for typ,entries in sorted(classes.items()):
        lines.append('struct '+typ+' {')
        for name in sorted({r['member_pointer']['symbol'].split('::')[-1] for _,r in entries}):
            counter+=1;callbacks[(typ,name)]=counter
            lines.append(f'bool {name}(const CEGUI::EventArgs& e) {{ trace_value={counter};return e.handled; }}')
        for i,r in entries: lines.append(f'CEGUI::SubscriberSlot make_{i}() {{ return {r["construction_candidate"]}; }}')
        lines.append('};')
    lines.append(EXTRA)
    lines.append('int main(){ int errors=0,checks=0;CEGUI::EventArgs e;')
    for typ,entries in sorted(classes.items()):
        lines.append('{ '+typ+' object;')
        for i,r in entries:
            expected=callbacks[(typ,r['member_pointer']['symbol'].split('::')[-1])]
            lines.append(f'{{ CEGUI::SubscriberSlot s=object.make_{i}(); for(int flag=0;flag<2;++flag){{e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!={expected})++errors;}}s.cleanup(); }}')
        lines.append('}')
    lines.append('errors+=test_pmf();std::cout<<"TOTAL "<<checks<<" "<<errors<<"\\n";return errors?1:0;}')
    src=out/'generated_cegui_fixture.cpp';src.write_text('\n'.join(lines)+'\n')
    exe=out/'cegui_fixture'
    cmd=['g++','-std=gnu++98','-O2','-fno-strict-aliasing','-I',str(root/'third_party/cegui-0.6.2/include'),str(src),str(root/'third_party/cegui-0.6.2/src/CEGUISubscriberSlot.cpp'),'-o',str(exe)]
    c=subprocess.run(cmd,capture_output=True,text=True,timeout=40)
    if c.returncode: raise RuntimeError(c.stderr)
    r=subprocess.run([str(exe)],capture_output=True,text=True,timeout=10)
    result={'scope':'synthetic owner methods, actual bundled CEGUI headers and SubscriberSlot.cpp',
            'generated_expressions':len(rows),'owner_classes':len(classes),'compiler':subprocess.check_output(['g++','--version'],text=True).splitlines()[0],
            'stdout':r.stdout,'stderr':r.stderr,'returncode':r.returncode,
            'not_tested':['original callback bodies','original class layouts','event connection lifetime','exceptional paths','GCC 4.4.7']}
    (out/'cegui-compilation.json').write_text(json.dumps(result,indent=2,ensure_ascii=False)+'\n')
    print(json.dumps(result,indent=2,ensure_ascii=False))
    if r.returncode: raise RuntimeError('fixture failed')

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('root',type=Path);p.add_argument('out',type=Path);p.add_argument('recipes',type=Path);a=p.parse_args()
    run(a.root,a.out,json.loads(a.recipes.read_text()))
