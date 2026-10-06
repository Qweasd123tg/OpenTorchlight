#!/usr/bin/env python3
"""Execute real normalizer/decision code on synthetic linked ELF and ET_REL objects.
The reference ELF is a generated fixture, not Torchlight (identity check configured for
that fixture). compile_for_diff supplies a host-assembled object; no MATCH result is mocked.
"""
import argparse, hashlib,json,os
from pathlib import Path
import subprocess,sys
from unittest.mock import patch


def command(args):
 r=subprocess.run(list(map(str,args)),text=True,capture_output=True,timeout=20)
 if r.returncode:raise RuntimeError(str(args)+'\n'+r.stdout+r.stderr)
 return r.stdout


def one_case(base,mode):
 import objdiff,elfimage
 base.mkdir(parents=True,exist_ok=True)
 main=base/'main.cpp'
 main.write_text('#include <cstdio>\nextern "C" int probe(unsigned,unsigned); extern "C" int outside_A(unsigned,unsigned){return 22;} extern "C" int outside_B(unsigned,unsigned){return 33;} int main(){std::printf("%d %d %d",probe(0,0),probe(1,0),probe(2,0));}\n')
 if mode=='outside_target':
  template='''.text
.globl probe
.type probe,@function
probe:
 .cfi_startproc
 cmpl $1,%edi
 ja .Ldefault
 movl %edi,%edi
 jmp *.Ltable(,%rdi,8)
.Lzero:
 movl $11,%eax
 ret
.Ldefault:
 movl $-1,%eax
 ret
 .cfi_endproc
.size probe,.-probe
.section .rodata
.p2align 3
.Ltable:
 .quad .Lzero
 .quad OUTSIDE
.section .note.GNU-stack,"",@progbits
'''
  texts=[template.replace('OUTSIDE','outside_A'),template.replace('OUTSIDE','outside_B')]
 else:
  template='''.text
.globl probe
.type probe,@function
probe:
 .cfi_startproc
 cmpl $1,%edi
 ja .Ldefault
 movl %edi,%edi
 cmpl $0,%esi
 sete %al
 movb %al,saved_flag(%rip)
 jmp *.Ltable(,%rdi,8)
.Lzero:
 movl $11,%eax
 ret
.Lone:
 movl $22,%eax
 ret
.Ltwo:
 movl $33,%eax
 ret
.Ldefault:
 movl $-1,%eax
 ret
 .cfi_endproc
.size probe,.-probe
.section .rodata
.p2align 3
.Ltable:
 .quad .Lzero
 .quad TARGET
.data
.globl saved_flag
.type saved_flag,@object
.size saved_flag,1
saved_flag: .byte 0
.section .note.GNU-stack,"",@progbits
'''
  if mode == 'internal_targets':
   template=template.replace(' cmpl $0,%esi\n sete %al\n movb %al,saved_flag(%rip)\n','')
  texts=[template.replace('TARGET','.Lone'),template.replace('TARGET','.Ltwo')]
 binaries=[];objects=[];returns=[]
 for i,t in enumerate(texts):
  asm=base/f'v{i}.s';asm.write_text(t);obj=base/f'v{i}.o';exe=base/f'v{i}.exe'
  command(['gcc','-c',asm,'-o',obj]);command(['g++','-std=gnu++98','-no-pie',obj,main,'-o',exe])
  binaries.append(exe);objects.append(obj);returns.append(command([exe]))
 image=elfimage.load(binaries[0],require_original=False);symbol=next(s for s in image.symbols if s.name=='probe')
 address=hex(symbol.value)
 f={'address':address,'mangled':'probe','names':['probe'],'demangled':'probe(unsigned int, unsigned int)',
    'size':symbol.size,'tu':1,'scope':'','method':'probe','kind':'function','bind':['global']}
 globals_=[{'name':s.name,'address':hex(s.value),'bind':'global','file':'Probe.cpp'} for s in image.symbols if s.name=='saved_flag']
 db={'functions':{address:f},'globals':globals_,'classes':{},'tus':[{'id':1,'name':'Probe.cpp','kind':'game'}]}
 src=base/'Probe.cpp';src.write_text('// native assembler fixture; see v1.s\n')
 with patch.object(elfimage, 'ORIGINAL_SHA256', image.sha256):
  orig=objdiff.Original(db=db,elf=binaries[0])
 with patch.object(objdiff,'NORM_CACHE',base/'cache.pickle'),patch.object(objdiff,'compile_for_diff',return_value=(objects[1],set())):
  result=objdiff.compare_source(src,orig,quiet=True)
 row=next(r for r in result['functions'] if r.get('address')==address)
 with patch.object(objdiff,'NORM_CACHE',base/'cache.pickle'),patch.object(objdiff,'compile_for_diff',return_value=(objects[0],set())):
  control=objdiff.compare_source(src,orig,quiet=True)
 control_status=next(r['status'] for r in control['functions'] if r.get('address')==address)
 norms=[objdiff.object_functions(o)['probe'] for o in objects]
 return {'proof_type':'real Original/compare_source/ELF parser/normalizer/decision, native synthetic x86-64; reference identity set to fixture hash; compile step supplied preassembled object',
         'mode':mode,'executed_original':returns[0],'executed_candidate':returns[1],
         'comparison':row,'identical_control_status':control_status,'unknown':result['unknown'],'object_normalization':norms,
         'false_MATCH':row['status']=='MATCH' and returns[0]!=returns[1]}


def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--project',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args()
 sys.dont_write_bytecode=True;sys.path.insert(0,str(a.project.resolve()/'tools/decomp'));a.out.mkdir(parents=True,exist_ok=True)
 results={mode:one_case(a.out/mode,mode) for mode in ('outside_target','unrelated_cmp','internal_targets')}
 (a.out/'results.json').write_text(json.dumps(results,indent=2,ensure_ascii=False)+'\n')
 for k,v in results.items():print(k,v['comparison']['status'],v['executed_original'],v['executed_candidate'],v['false_MATCH'])
if __name__=='__main__':main()
