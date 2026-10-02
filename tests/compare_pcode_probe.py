#!/usr/bin/env python3
"""Compare pinned Ghidra execution with unchanged native leaf bytes in private memory.

Only the explicitly selected no-call functions are executed; the unresolved
petIndex call must remain UNKNOWN. No original game, loader or resources run.
"""
import argparse
import ctypes as c
import json
from pathlib import Path
import platform
import sys
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from original import Original
from compare_ai_cooldown import Executable

ENTRIES={0x7F5FD0,0x7F5FE0,0x805110,0x80E890}


def compare(original,profile,result):
    if result['original_elf_sha256']!=original.sha256 or profile['original_elf_sha256']!=original.sha256:
        raise ValueError('Oracle/profile source identity differs')
    actual={r['id']:r for r in result['results']}
    if len(actual)!=len(profile['cases']):raise ValueError('Missing/duplicate emulator result')
    libc=c.CDLL(None,use_errno=True)
    libc.mmap.argtypes=[c.c_void_p,c.c_size_t,c.c_int,c.c_int,c.c_int,c.c_long];libc.mmap.restype=c.c_void_p
    libc.munmap.argtypes=[c.c_void_p,c.c_size_t]
    allocations=[];native={};complete=unknown=0
    try:
        for entry in ENTRIES:
            symbol=next(s for s in original.symbols if s.address==entry and s.size)
            native[entry]=Executable(original.read(entry,symbol.size))
        region_shapes={int(r['address'],16):len(bytes.fromhex(r['bytes_le']))
                       for case in profile['cases'] for r in case['regions'] if r['name']!='stack'}
        for address,size in region_shapes.items():
            length=(size+4095)&~4095
            value=libc.mmap(address,length,3,0x100000|0x20|2,-1,0)
            if value==c.c_void_p(-1).value:raise OSError(c.get_errno(),'MAP_FIXED_NOREPLACE; use PIE Python')
            if value!=address:
                libc.munmap(value,length);raise ValueError('Kernel ignored fixed no-replace mapping')
            allocations.append((address,length))
        for case in profile['cases']:
            answer=actual[case['id']];entry=int(case['entry'],16)
            if entry not in ENTRIES:
                if answer['status']!='UNKNOWN' or 'External/computed target' not in answer['reason']:
                    raise ValueError('Unresolved dependency was guessed instead of UNKNOWN')
                unknown+=1;continue
            if answer['status']!='COMPLETE':raise ValueError(case['id']+': '+answer['reason'])
            for region in case['regions']:
                if region['name']=='stack':continue
                data=bytes.fromhex(region['bytes_le']);c.memmove(int(region['address'],16),data,len(data))
            rdi=int.from_bytes(bytes.fromhex(case['registers']['RDI']),'little')
            rsi=int.from_bytes(bytes.fromhex(case['registers']['RSI']),'little')
            function=c.CFUNCTYPE(c.c_uint64,c.c_void_p,c.c_uint64)(native[entry].address)
            returned=function(rdi,rsi)
            if 'RAX' in answer['observations'] and returned!=int.from_bytes(bytes.fromhex(answer['observations']['RAX']),'little'):
                raise ValueError('Native return bits differ: '+case['id'])
            for region in case['observe_regions']:
                data=c.string_at(int(region['address'],16),region['size']).hex()
                if data!=answer['observations'][region['name']]:raise ValueError('Native memory differs: '+case['id'])
            complete+=1
        return {'native_compared':complete,'explicit_unknown':unknown,'original_status_promotions':0}
    finally:
        for memory in native.values():memory.close()
        for address,size in allocations:libc.munmap(address,size)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    for arg in ('original','profile','result'):parser.add_argument('--'+arg,required=True,type=Path)
    args=parser.parse_args()
    if platform.system()!='Linux' or platform.machine()!='x86_64':print('SKIP Linux x86-64 required');return 77
    result=compare(Original(args.original),json.loads(args.profile.read_text()),json.loads(args.result.read_text()))
    print('PASS:',json.dumps(result),'raw return bits/full observed buffers; no ownership or whole-game proof')
    return 0


if __name__=='__main__':raise SystemExit(main())
