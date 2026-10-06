#!/usr/bin/env python3
"""Reproduce read-only pass8 prototypes with a modern GCC-compatible compiler.
Executes five *selected* native archival test references. Linux x86-64 only.
No game process, ELF loading, network calls, source edits or production installs.
"""
from __future__ import annotations
import argparse,hashlib,json,os,platform,shutil,subprocess,sys,tempfile
from pathlib import Path
HERE=Path(__file__).resolve().parent

def manifest(root:Path)->dict:
    return {str(p.relative_to(root)):hashlib.sha256(p.read_bytes()).hexdigest()
            for p in sorted(root.rglob('*')) if p.is_file()}
def main()->int:
    ap=argparse.ArgumentParser();ap.add_argument('root',type=Path);ap.add_argument('--out',type=Path,default=HERE/'results')
    ap.add_argument('--compiler',default='g++');a=ap.parse_args();root=a.root.resolve();out=a.out.resolve();out.mkdir(parents=True,exist_ok=True)
    if platform.system()!='Linux' or platform.machine() not in ('x86_64','AMD64'):
        ap.error('The native probes require Linux x86-64.')
    if not (root/'AGENTS.md').is_file() or not (root/'research/disassembly/91a980.asm').is_file():ap.error('Wrong project root')
    if out==root or root in out.parents:ap.error('Output must be outside the source archive')
    compiler=shutil.which(a.compiler)
    if not compiler:ap.error('Compiler not found')
    before=manifest(root);commands=[]
    def run(cmd:list[str],dest:str|None=None,timeout:int=40):
        r=subprocess.run([str(x) for x in cmd],text=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE,timeout=timeout)
        commands.append({'command':[str(x) for x in cmd],'returncode':r.returncode,'stderr':r.stderr})
        if dest:(out/dest).write_text(r.stdout if dest.endswith('.json') else r.stdout+r.stderr)
        if r.returncode:raise RuntimeError('Command failed: '+str(cmd)+'\n'+r.stderr+r.stdout)
        return r.stdout
    try:
        py=sys.executable
        run([py,'-m','unittest','discover','-s',HERE/'tests','-v'],'unittests.txt')
        for script,dest in [('census.py','census.json'),('static_guards.py','static-guards.json')]:
            run([py,HERE/'tools'/script,root,out/dest])
        native=out/'native';run([py,HERE/'tools/native_capsule.py',root,native]);run([py,HERE/'tools/memory_transfers.py',root,native])
        include=root/'third_party/ogre-1.6.5-math/OgreMain/include'
        common=[compiler,'-std=gnu++98','-O2','-fno-strict-aliasing','-DNDEBUG']
        ogre=['-D_GLIBCXX_USE_CXX11_ABI=0','-DOGRE_MEMORY_ALLOCATOR=1','-I',str(include)]
        with tempfile.TemporaryDirectory(prefix='torchlight-pass8-') as td:
            b=Path(td)
            jobs=[('abi-probe.json','abi_probe',[HERE/'examples/abi_probe.cpp',HERE/'examples/capture_return.S'],ogre),
                  ('math-probe.json','math_probe',[HERE/'examples/math_probe.cpp'],ogre+['-ffp-contract=off']),
                  ('lifecycle-probe.json','lifecycle_probe',[HERE/'examples/lifecycle_probe.cpp'],[]),
                  ('native-probe.json','native_probe',[HERE/'examples/native_probe.cpp',native/'generated_capture.cpp',native/'native_reference.S'],[])]
            for result,name,inputs,flags in jobs:
                run(common+flags+list(inputs)+['-o',b/name]);run([b/name],result,20)
            run(common+ogre+['-S',HERE/'examples/abi_probe.cpp','-o',out/'abi-probe.s'])
            run(common+['-c',native/'native_reference.S','-o',b/'reference.o'])
            run(['objdump','-drw',b/'reference.o'],'native-disassembled.txt')
            run(['nm','-S',b/'reference.o'],'native-symbols.txt')
        environment={'compiler':run([compiler,'--version']).splitlines()[0],
          'python':sys.version,'machine':platform.machine(),'platform':platform.platform(),
          'assembler':run(['as','--version']).splitlines()[0],
          'ogre_probe_allocator':'OGRE_MEMORY_ALLOCATOR=1; standalone math headers only',
          'original_gcc_4_4_7_run':False,'original_ELF_run':False}
        (out/'environment.json').write_text(json.dumps(environment,indent=2))
    finally:
        after=manifest(root);changed=sorted(k for k in before if before[k]!=after.get(k));added=sorted(set(after)-set(before))
        (out/'source-integrity.json').write_text(json.dumps({'files_before':len(before),'files_after':len(after),'changed_or_deleted':changed,'added':added,'unchanged':before==after},indent=2))
        (out/'commands.json').write_text(json.dumps(commands,indent=2))
        if before!=after:raise RuntimeError('Source files changed unexpectedly')
    print('All pass8 probes completed. Results: '+str(out));return 0
if __name__=='__main__':raise SystemExit(main())
