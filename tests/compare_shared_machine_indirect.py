#!/usr/bin/env python3
"""Unchanged source CALLIND chains, actual source tables, isolated guest RAM.

Calibrates the execution mechanism, not gameplay reconstruction. No constructor,
library callback, game/UI process or completion promotion. Noncanonical flag
bytes test machine instructions only, not valid constructed C++ bool objects.
"""
import argparse
import ctypes as c
import hashlib
import itertools
import json
from pathlib import Path
import platform
import random
import struct
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from automation_state import validate_output, write_json
from original import Original
from screen_function_lifts import validate_raw
from native_typed_reference import Memory

SOURCES = ((0xA82AE0,277),(0xAE15F0,3),(0xAE1620,8),(0xBCCA70,6),
           (0xBCCAA0,8),(0x5BB4A0,39),(0x5A6CD0,8))
GLOBAL = 0x142C4A0
GUARD = 16

def guarded(data):
    raw = bytes([0xa7])*GUARD + bytes(data) + bytes([0xa7])*GUARD
    buf = c.create_string_buffer(raw, len(raw))
    return buf, c.addressof(buf)+GUARD, raw

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    for name in ('original','probe','output'):
        parser.add_argument('--'+name,type=Path,required=True)
    args=parser.parse_args()
    if platform.system()!='Linux' or platform.machine()!='x86_64': return 77
    validate_output(ROOT,args.output,[args.original,args.probe])
    original=Original(args.original)
    memory=Memory()
    try:
        bodies=[]
        for address,size in SOURCES:
            raw_path=ROOT/'research/lifted-machine-fixtures'/f'{address:08x}.json'
            packet=json.loads(raw_path.read_text())
            symbol=next(s for s in original.symbols if s.address==address and s.size)
            if symbol.size!=size: raise ValueError('source symbol size drift')
            body=original.read(address,size)
            if packet['original_symbol_body_sha256']!=hashlib.sha256(body).hexdigest():
                raise ValueError('full original body drift')
            validate_raw(packet,original,symbol,packet['address'])
            memory.put(address,body)
            bodies.append(dict(address=hex(address),size=size,sha256=hashlib.sha256(body).hexdigest()))
        tables=json.loads((ROOT/'research/lifted-machine-fixtures/vtables.json').read_text())
        if tables['original_elf_sha256']!=original.sha256: raise ValueError('table source mismatch')
        table_text=[]
        for table in tables['tables']:
            address=int(table['address'],16);data=original.read(address,table['size'])
            if data.hex()!=table['bytes'] or hashlib.sha256(data).hexdigest()!=table['sha256']:
                raise ValueError('actual source table drift')
            for slot,target in table['consumed_slots'].items():
                if struct.unpack_from('<Q',data,int(slot,16))[0]!=int(target,16):
                    raise ValueError('actual source virtual target drift')
            memory.put(address,data);table_text.append(f'{address:x} {data.hex()}\n')
        memory.put(GLOBAL-GUARD,bytes([0xa7])*(GUARD*2+4))
        memory.protect(writable={GLOBAL & ~4095})
        panel=c.CFUNCTYPE(c.c_uint64,c.c_void_p)(0xA82AE0)
        enabled=c.CFUNCTYPE(c.c_uint64,c.c_void_p,c.c_void_p)(0x5BB4A0)
        rng=random.Random(0xCA111D)
        # All short normal lists; longer shuffled polymorphic lists, including
        # raw machine-only noncanonical flag values and both two-pass orders.
        cases=[list(x) for n in range(5) for x in itertools.product(((0,0),(0,1),(1,0),(1,1)),repeat=n)]
        cases += [[(rng.randrange(2),rng.choice((0,1,2,127,128,255)))
                   for _ in range(rng.randrange(41))] for _ in range(1024)]
        payload=[];expected=[]
        for rows in cases:
            objects=[];pointers=[]
            for kind,flag in rows:
                data=bytearray(rng.randbytes(0x200))
                struct.pack_into('<Q',data,0,0xff0e30 if kind else 0xfe6270)
                data[0x188 if kind else 0x98]=flag
                buf,ptr,before=guarded(data);objects.append((buf,before));pointers.append(ptr)
            vector,vector_ptr,vector_before=guarded(b''.join(struct.pack('<Q',v) for v in pointers))
            data=bytearray(rng.randbytes(0x1940))
            struct.pack_into('<QQ',data,0x1930,vector_ptr,vector_ptr+len(rows)*8)
            ui,ui_ptr,ui_before=guarded(data)
            expected.append((int(panel(ui_ptr)),))
            if bytes(ui)!=ui_before or bytes(vector)!=vector_before or any(bytes(b)!=old for b,old in objects):
                raise AssertionError('source query mutated initialized owner/vector/guard bytes')
            payload.append('p '+str(len(rows))+''.join(f' {kind} {flag}' for kind,flag in rows)+'\n')
        descriptor_cases=[(present,flag,rng.getrandbits(32),rng.getrandbits(32))
                          for present in (0,1) for flag in (0,1,2,127,128,255) for _ in range(64)]
        descriptor_cases += [(rng.randrange(2),rng.randrange(256),rng.getrandbits(32),rng.getrandbits(32))
                             for _ in range(1024)]
        for present,flag,count_value,global_value in descriptor_cases:
            data=bytearray(rng.randbytes(0x200));struct.pack_into('<Q',data,0,0xfd8e50);data[0x82]=flag
            obj,obj_ptr,obj_before=guarded(data)
            count_buf,count_ptr,count_before=guarded(struct.pack('<I',count_value))
            global_before=bytes([0xa7])*GUARD+struct.pack('<I',global_value)+bytes([0xa7])*GUARD
            c.memmove(GLOBAL-GUARD,global_before,len(global_before))
            pointer=int(enabled(obj_ptr if present else 0,count_ptr if present else 0))
            count_after=bytearray(count_before);global_after=bytearray(global_before)
            if present:struct.pack_into('<I',count_after,GUARD,1);global_after[GUARD]=flag
            if bytes(obj)!=obj_before or bytes(count_buf)!=bytes(count_after) or c.string_at(GLOBAL-GUARD,len(global_after))!=bytes(global_after):
                raise AssertionError('source descriptor store/guard contract differs')
            expected.append((pointer,struct.unpack_from('<I',count_buf,GUARD)[0],
                             struct.unpack('<I',c.string_at(GLOBAL,4))[0]))
            payload.append(f'e {present} {flag} {count_value} {global_value}\n')
        with tempfile.TemporaryDirectory(prefix='indirect-source-tables-',dir='/tmp') as temp:
            path=Path(temp)/'tables.txt';path.write_text(''.join(table_text))
            result=subprocess.run([str(args.probe.resolve()),str(path)],input=''.join(payload),text=True,
                                  capture_output=True,check=True,timeout=90)
        actual=[tuple(map(int,line.split())) for line in result.stdout.splitlines()]
        if actual!=expected: raise AssertionError('shared CALLIND execution differs from unchanged original')
        write_json(args.output,dict(schema=1,status='PASS',kind='shared-machine-indirect-calibration',
            cases=len(expected),panel_cases=len(cases),descriptor_cases=len(descriptor_cases),mismatch_count=0,
            original_elf_sha256=original.sha256,whole_original_bodies=bodies,
            actual_vtables=[{k:t[k] for k in ('address','size','sha256','consumed_slots')} for t in tables['tables']],
            comparison='Return bits and every initialized source owner/vector/object/output/guard byte; guest probe checks readonly snapshots, count/global guards, saved registers and real RET/RSP.',
            scope=__doc__,original_status_promotions=0,game_executed=False,original_modified=False))
        print(f'PASS shared CALLIND: {len(expected)} cases, 7 unchanged bodies, actual source vtables; no callbacks')
        return 0
    finally:memory.close()

if __name__=='__main__':raise SystemExit(main())
