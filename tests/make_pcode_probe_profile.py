#!/usr/bin/env python3
"""Explicit SysV64 raw-state calibration, not constructed original game objects."""
import argparse
import json
from pathlib import Path
import random
import struct
import sys
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from original import SUPPORTED_SHA256

OBJECT, NODE, STACK, RETURN = 0x3000000, 0x3001000, 0x3F00000, 0x5000000


def make_case(identity, entry, actor, argument=0, node=None, returns=False):
    stack=bytearray(4096);struct.pack_into('<Q',stack,0x800,RETURN)
    registers={name: bytes(8).hex() for name in ('RAX','RBX','RCX','RDX','RBP','R8','R9','R10','R11','R12','R13','R14','R15')}
    registers.update({name: struct.pack('<Q',value).hex() for name,value in
                      (('RIP',entry),('RDI',OBJECT),('RSI',argument),('RSP',STACK+0x800))})
    registers.update({name:'00' for name in ('CF','PF','AF','ZF','SF','OF','DF')})
    regions=[{'name':'object','address':hex(OBJECT),'bytes_le':actor.hex(),'writable':True},
             {'name':'stack','address':hex(STACK),'bytes_le':stack.hex(),'writable':True}]
    observe=[{'name':'object','address':hex(OBJECT),'size':len(actor)}]
    if node is not None:
        regions.append({'name':'node','address':hex(NODE),'bytes_le':node.hex(),'writable':True})
        observe.append({'name':'node','address':hex(NODE),'size':len(node)})
    return {'id':identity,'entry':hex(entry),'return_address':hex(RETURN),'max_instructions':64,
            'regions':regions,'registers':registers,'observe_registers':['RAX'] if returns else [],
            'observe_regions':observe}


def profile():
    cases=[]
    for entry,offset in ((0x7F5FE0,0x1A9),(0x805110,0x1A8)):
        for value in range(256):
            actor=bytearray(2048);actor[offset]=value
            cases.append(make_case(f'{entry:x}-byte-{value}',entry,actor,returns=True))
    rng=random.Random(0x7F5FD0)
    for value in (0,1,0xFFFFFFFF,0x8000000000000000,0xFFFFFFFFFFFFFFFF,*[rng.getrandbits(64) for _ in range(32)]):
        cases.append(make_case(f'guid-{value:x}',0x7F5FD0,bytearray(2048),value))
    for present in (False,True):
        for value in (0,1,31,0x7FFFFFFF,0x80000000,0xFFFFFFFF):
            actor=bytearray(2048);struct.pack_into('<Q',actor,0x268,NODE if present else 0)
            cases.append(make_case(f'depth-{present}-{value}',0x80E890,actor,value,bytearray(256)))
    # A real unresolved call must stop execution, without a guessed stub/result.
    cases.append(make_case('external-call-must-remain-unknown',0x80EC60,bytearray(2048)))
    return {'schema':1,'original_elf_sha256':SUPPORTED_SHA256,'language':'x86:LE:64:default',
            'scope':'Explicit SysV64 register bits and synthetic raw object/stack buffers. Exhaustive byte inputs include values outside a constructed bool object domain. No owner/constructor/valid-world-state inference, external-call stubs, game launch or whole-function completion.',
            'cases':cases}


if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('output',type=Path)
    args=parser.parse_args();args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text(json.dumps(profile(),separators=(',',':'))+'\n')
    print('Wrote',len(profile()['cases']),'explicit raw-state cases')
