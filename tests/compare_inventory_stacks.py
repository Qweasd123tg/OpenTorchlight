#!/usr/bin/env python3
"""Unchanged findFreeSlot body; two explicit pane-selection ABI adapters.

Dense, occupied, stack-enabled potion pane followed by one free slot. GUID,
signed count/maximum and replacement order are original instructions. Does not
run constructors, panes/type classification, drag splitting or merchant UI.
"""
import argparse
import ctypes as c
from pathlib import Path
import platform
import random
import struct
import subprocess
import sys

sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from original import Original
from compare_ai_cooldown import Executable


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--original',required=True,type=Path)
    parser.add_argument('--probe',required=True,type=Path)
    args=parser.parse_args()
    if platform.system()!='Linux' or platform.machine()!='x86_64':return 77
    original=Original(args.original);base=0x91B000;body=bytearray(0x1000)
    body[0xA50:0xA50+506]=original.read(0x91BA50,506)
    # Explicit getRequiredPane/getPaneIndex adapters return pane zero. The
    # tested function's branch/field instructions remain unchanged.
    for entry in (0x91B9C0,0x91B050):body[entry-base:entry-base+3]=bytes.fromhex('31 c0 c3')
    memory=Executable(bytes(body))
    try:
        run=c.CFUNCTYPE(c.c_int32,c.c_void_p,c.c_void_p)(memory.address+0xA50)
        rng=random.Random(0x91BA50)
        cases=[(5,20,[6,9,7]),(5,20,[6,4,7]),(5,20,[4,4]),(4,20,[18,18]),(1,1,[1,1])]
        inputs=[];expected=[]
        for iteration in range(6000):
            maximum=rng.randrange(1,41);count=rng.randrange(1,maximum+1)
            cases.append((count,maximum,[rng.randrange(1,maximum+1) for _ in range(rng.randrange(12))]))
        for index,(count,maximum,counts) in enumerate(cases):
            guids=[9 if index<5 or rng.randrange(4) else 10 for _ in counts]
            incoming=c.create_string_buffer(0x240);inventory=c.create_string_buffer(0x90)
            equips=[c.create_string_buffer(0x240) for _ in counts]
            references=[c.create_string_buffer(0x20) for _ in counts]
            addresses=(c.c_void_p*max(1,len(counts)))(*[c.addressof(x) for x in references])
            panes=(c.c_uint32*1)(19)
            inventory[0x14]=1
            struct.pack_into('<I',inventory,0x28,19+len(counts)+1)
            struct.pack_into('<QII',inventory,0x30,c.addressof(addresses),len(counts),len(counts))
            struct.pack_into('<QQ',inventory,0x78,c.addressof(panes),c.addressof(panes)+4)
            struct.pack_into('<q',incoming,0x1A0,9);struct.pack_into('<ii',incoming,0x238,count,maximum)
            for slot,(equip,reference,value,guid) in enumerate(zip(equips,references,counts,guids)):
                struct.pack_into('<q',equip,0x1A0,guid);struct.pack_into('<ii',equip,0x238,value,maximum)
                struct.pack_into('<Qi',reference,0x10,c.addressof(equip),19+slot)
            expected.append(run(c.addressof(inventory),c.addressof(incoming))-19)
            inputs.append(f'{count} {maximum} {len(counts)} '+ ' '.join(f'{v} {g}' for v,g in zip(counts,guids))+'\n')
        output=subprocess.run([str(args.probe.resolve())],input=''.join(inputs),text=True,capture_output=True,check=True,timeout=30)
        actual=[int(line) for line in output.stdout.splitlines()]
        if actual!=expected:
            bad=next((i for i,(a,b) in enumerate(zip(actual,expected)) if a!=b),None)
            raise AssertionError(f'original/port stack selection differs at {bad}: {inputs[bad] if bad is not None else "result count"}')
        print(f'PASS native findFreeSlot comparisons={len(cases)}; two explicit pane adapters; no full inventory claim')
    finally:memory.close()
    return 0


if __name__=='__main__':raise SystemExit(main())
