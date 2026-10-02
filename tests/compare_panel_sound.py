#!/usr/bin/env python3
"""Compare normal close/same-closed paths of four unchanged setOpen bodies.

Named adapters record sound/blend calls and supply an opaque constructed-string
sentinel. No original constructors, CEGUI tree, animation or audio device run.
Detached child pointers are null; initialized byte flags are 0/1.
"""
import argparse
import ctypes as c
import hashlib
from pathlib import Path
import platform
import struct
import subprocess
import sys

sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from original import Original
from automation_state import validate_output,write_json
from native_typed_reference import Memory

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--original',type=Path,required=True);p.add_argument('--probe',type=Path,required=True)
    p.add_argument('--output',type=Path,required=True);args=p.parse_args()
    if platform.system()!='Linux' or platform.machine()!='x86_64':return 77
    validate_output(Path(__file__).resolve().parents[1],args.output,[args.original,args.probe])
    original=Original(args.original);memory=Memory();events=[];errors=[];bodies=[]
    current_bank=current_model=0
    def sound(bank,sample,node,volume,radius,untracked):
        events.append(['sound',sample])
        if bank!=current_bank or node or volume or radius or untracked:errors.append('sound arguments')
        return -1
    def string_ctor(destination,text,allocator):
        if text!=0xFE6008:errors.append('non-CLOSE string')
        # GNU old-ABI string representation sentinel avoids unknown allocation/
        # release paths. Requested literal is observed independently above.
        c.c_size_t.from_address(destination).value=0x1423A38
        events.append(['string','CLOSE'])
    def blend(model,string,loop,fade,speed,offset):
        if model!=current_model or loop or (fade,speed,offset)!=(c.c_float(.1).value,2.,-1.):
            errors.append('blend arguments')
        events.append(['blend','CLOSE'])
    members=((0xB4EB70,0x60,0x61,0x9188,0x9170),
             (0xB6A220,0x60,0x61,0xA8,0x90),
             (0xBC2550,0x188,0x189,0x1D8,0x1B0),
             (0xBE1130,0x38,0x39,0xE8,0x60))
    try:
        for address,*_ in members:
            symbol=next(s for s in original.symbols if s.address==address and s.size)
            body=original.read(address,symbol.size);memory.put(address,body)
            bodies.append(dict(address=hex(address),symbol=symbol.name,size=symbol.size,sha256=hashlib.sha256(body).hexdigest()))
        for address in (0xFA480C,0xFA4824,0xFA8760):memory.put(address,original.read(address,4))
        memory.callback(0xA698A0,c.CFUNCTYPE(c.c_int,c.c_size_t,c.c_int,c.c_size_t,c.c_float,c.c_float,c.c_bool),sound)
        memory.callback(0x5562F8,c.CFUNCTYPE(None,c.c_size_t,c.c_size_t,c.c_size_t),string_ctor)
        memory.callback(0x8A71D0,c.CFUNCTYPE(None,c.c_size_t,c.c_size_t,c.c_bool,c.c_float,c.c_float,c.c_float),blend)
        memory.protect();inputs=[];expected=[]
        for bank,(address,flag,aux,sound_field,model_field) in enumerate(members):
            run=c.CFUNCTYPE(None,c.c_size_t,c.c_bool)(address)
            for opened in (False,True):
                obj=c.create_string_buffer(0x9200);bank_obj=c.create_string_buffer(0xD0);model=c.create_string_buffer(0x100)
                current_bank=c.addressof(bank_obj);current_model=c.addressof(model)
                obj[flag]=int(opened);obj[aux]=0
                struct.pack_into('<Q',obj,sound_field,current_bank);struct.pack_into('<Q',obj,model_field,current_model)
                events.clear();run(c.addressof(obj),False)
                sample=events[0][1] if events else -1
                expected_events=[['sound',66],['string','CLOSE'],['blend','CLOSE']] if opened else []
                if events!=expected_events or errors:raise AssertionError((hex(address),opened,events,errors))
                expected.append([sample,obj.raw[flag],obj.raw[aux],int(bool(events))]);inputs.append(f'{bank} {int(opened)}\n')
        result=subprocess.run([str(args.probe.resolve())],input=''.join(inputs),text=True,capture_output=True,check=True,timeout=30)
        actual=[[int(v) for v in line.split()] for line in result.stdout.splitlines()]
        if actual!=expected:raise AssertionError((actual,expected))
        write_json(args.output,dict(schema=1,kind='original-panel-sound-comparison',status='PASS',
            original_elf_sha256=original.sha256,bodies=bodies,cases=len(expected),scope=__doc__,
            original_status_promotions=0,game_executed=False))
        print(f'PASS panel close native comparisons={len(expected)}; original bank-local sound66 then CLOSE blend')
    finally:memory.close()
    return 0

if __name__=='__main__':raise SystemExit(main())
