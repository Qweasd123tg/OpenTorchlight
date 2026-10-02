#!/usr/bin/env python3
"""Unchanged whole autoPickupGold/alive bodies against production selection.

Named adapters supply ISA, getPosition's SysV float-vector return and record
getItem. Raw linked nodes, character state/pathing and coordinates are explicit.
getItem invalidates each current node's next field to exercise cached-next order.
No original game/constructors, full getItem or native linked-list ownership run.
"""
import argparse
import ctypes as c
import hashlib
import math
from pathlib import Path
import platform
import random
import struct
import subprocess
import sys

sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from original import Original
from automation_state import validate_output,write_json
from native_typed_reference import Memory
from compare_ai_cooldown import bits,f32


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--original',required=True,type=Path);parser.add_argument('--probe',required=True,type=Path)
    parser.add_argument('--output',required=True,type=Path);args=parser.parse_args()
    if platform.system()!='Linux' or platform.machine()!='x86_64':return 77
    validate_output(Path(__file__).resolve().parents[1],args.output,[args.original,args.probe])
    original=Original(args.original);memory=Memory();bodies=[]
    selected=[];lookup={};errors=[];nodes_by_item={}
    def isa(item,kind):
        if kind!=0x22:errors.append(['unexpected_type',kind])
        return lookup[item][1]
    def get_item(player,item,level):
        selected.append(lookup[item][0])
        # autoPickupGold loads next before this callback. No node allocation or
        # original deletion is emulated; this visible mutation checks the order.
        struct.pack_into('<Q',nodes_by_item[item],8,0)
    try:
        for entry in (0x56E3A0,0x80E850):
            symbol=next(s for s in original.symbols if s.address==entry and s.size)
            body=original.read(entry,symbol.size);memory.put(entry,body)
            bodies.append(dict(address=hex(entry),symbol=symbol.name,size=symbol.size,sha256=hashlib.sha256(body).hexdigest()))
        radius=original.read(0xFA86D4,4)
        if radius.hex()!='00004040':raise ValueError('Unsupported original auto-gold radius')
        memory.put(0xFA86D4,radius)
        memory.callback(0x7F62A0,c.CFUNCTYPE(c.c_bool,c.c_size_t,c.c_int),isa)
        # Explicit ABI position adapter: x/y packed in XMM0, z in XMM1;
        # caller instructions confirm the aggregate return and argument true.
        memory.put(0x9E7080,bytes.fromhex('f3 0f 7e 87 84 00 00 00 f3 0f 10 8f 8c 00 00 00 c3'))
        memory.callback(0x83B1A0,c.CFUNCTYPE(None,c.c_size_t,c.c_size_t,c.c_size_t),get_item)
        memory.protect();run=c.CFUNCTYPE(None,c.c_void_p)(0x56E3A0)
        edge=[(0.,0.,0.),(2.999999761581421,500.,0.),(3.,0.,0.),(3.000000238418579,0.,0.),
              (0.,-500.,2.999999761581421),(2.,99.,2.),(-3.,0.,0.)]
        cases=[]
        for state in (0,5,6):
            for moving in (0,1):cases.append((state,moving,(0.,0.,0.),[(i!=0,p) for i,p in enumerate(edge)]))
        rng=random.Random(0x56E3A0)
        for _ in range(6000):
            player=tuple(f32(rng.uniform(-1000,1000)) for _ in range(3))
            points=[(bool(rng.randrange(2)),(f32(player[0]+rng.uniform(-4,4)),
                     f32(rng.uniform(-1000,1000)),f32(player[2]+rng.uniform(-4,4)))) for _ in range(rng.randrange(12))]
            cases.append((rng.choice((0,5,6)),rng.randrange(2),player,points))
        inputs=[];expected=[]
        for state,moving,position,points in cases:
            selected.clear();lookup.clear();nodes_by_item.clear()
            client=c.create_string_buffer(0x80);player=c.create_string_buffer(0x400);level=c.create_string_buffer(0xD0)
            items=[c.create_string_buffer(0x100) for _ in points];nodes=[c.create_string_buffer(16) for _ in points]
            head=(c.c_size_t*1)(c.addressof(nodes[0]) if nodes else 0)
            struct.pack_into('<Q',client,0x58,c.addressof(player));struct.pack_into('<Q',client,0x70,c.addressof(level))
            struct.pack_into('<Q',level,0xC0,c.addressof(head));struct.pack_into('<i',player,0x330,state)
            player[0x264]=moving;struct.pack_into('<fff',player,0x84,*position)
            for index,(item,node,(gold,point)) in enumerate(zip(items,nodes,points)):
                address=c.addressof(item);lookup[address]=(index+1,gold);nodes_by_item[address]=node
                struct.pack_into('<fff',item,0x84,*point)
                struct.pack_into('<QQ',node,0,address,c.addressof(nodes[index+1]) if index+1<len(nodes) else 0)
            run(c.addressof(client));expected.append(selected[:])
            inputs.append(f'{int(state not in (5,6))} {moving} '+ ' '.join(str(bits(v)) for v in position)+f' {len(points)} '+
                          ' '.join(str(int(gold))+' '+' '.join(str(bits(v)) for v in point) for gold,point in points)+'\n')
        result=subprocess.run([str(args.probe.resolve())],input=''.join(inputs),text=True,capture_output=True,check=True,timeout=30)
        actual=[]
        for line in result.stdout.splitlines():
            row=[int(value) for value in line.split()]
            if not row or row[0]!=len(row)-1:raise ValueError('Invalid production probe output')
            actual.append(row[1:])
        if actual!=expected or errors:
            bad=next((i for i,(a,b) in enumerate(zip(actual,expected)) if a!=b),None)
            raise AssertionError(f'auto-gold mismatch {bad}: {cases[bad] if bad is not None else "result count"}; {errors}')
        write_json(args.output,dict(schema=1,kind='original-auto-gold-comparison',status='PASS',
            original_elf_sha256=original.sha256,bodies=bodies,cases=len(expected),radius_bytes_le=radius.hex(),
            scope=__doc__,game_executed=False,original_status_promotions=0))
        print(f'PASS auto-gold native comparisons={len(expected)}; original state/pathing/XZ/strict boundary/cached-next order')
        return 0
    finally:memory.close()


if __name__=='__main__':raise SystemExit(main())
