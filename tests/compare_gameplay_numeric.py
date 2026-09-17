#!/usr/bin/env python3
"""SHA-checked native effect accumulation + population count/RNG comparisons.

Executes ONLY two unchanged bounded functions in isolated memory. Synthetic
objects model their data fields; native libm supplies ceilf. This is not a game
launch, spawning/placement parity, full effect scheduling or graphics comparison.
Run under a PIE Python host: fixed original RNG pages must not collide with it.
"""
from __future__ import annotations
import argparse
import ctypes as c
import ctypes.util
import platform
from pathlib import Path
import random
import struct
import subprocess
import sys
from compare_ai_cooldown import Executable, bits, f32
from compare_original_random import OriginalRandom
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from original import Original


def recovery(original: Original, probe: Path) -> int:
    low, high=0x7eb000,0xfc9000
    code=bytearray(high-low)
    for address,size in ((0x7eb5f0,0x1ce),(0xfa86dc,4),(0xfc89b8,8)):
        code[address-low:address-low+size]=original.read(address,size)
    memory=Executable(bytes(code))
    try:
        fn=c.CFUNCTYPE(c.c_float,c.c_void_p,c.c_int32,c.c_int32)(memory.address+0x7eb5f0-low)
        manager=c.create_string_buffer(0x400)
        effect=c.create_string_buffer(0x100)
        pointers=(c.c_void_p*1)(c.addressof(effect))
        struct.pack_into('<QII',manager,0x28,c.addressof(pointers),1,1)
        struct.pack_into('<i',effect,0x14,0)  # a concrete damage type, not aggregate-cache shortcut
        struct.pack_into('<f',effect,0x24,4)
        values=[0.,.001,.125,1.,50.,520.,1250.,3124.,9374.,1e9]
        rng=random.Random(0x7eb5f0)
        values += [f32(rng.uniform(0,1e9)) for _ in range(2500)]
        inputs=[];expected=[]
        for effect_type in (6,7,123,124):
            struct.pack_into('<i',effect,0x1c,effect_type)
            struct.pack_into('<f',manager,0x80+4*effect_type,1)
            for value in values:
                struct.pack_into('<f',effect,0xc0,value)
                expected.append(bits(fn(c.addressof(manager),effect_type,0)))
                inputs.append(f'r {bits(value)}\n')
        result=subprocess.run([str(probe)],input=''.join(inputs),text=True,capture_output=True,check=True,timeout=30)
        actual=[int(line) for line in result.stdout.splitlines()]
        if actual!=expected:
            first=next((i for i,pair in enumerate(zip(actual,expected)) if pair[0]!=pair[1]),None)
            raise ValueError(f'finite recovery native mismatch at {first}; lengths {len(actual)}/{len(expected)}')
        return len(expected)
    finally:memory.close()


def population(original: Original,probe: Path) -> int:
    old=OriginalRandom(original)
    regions=[]
    libc=old.libc
    try:
        for address in (0x971000,0x553000,0xfce000):
            result=libc.mmap(address,4096,3,0x100000|0x20|0x02,-1,0)
            if result==c.c_void_p(-1).value:raise OSError(c.get_errno(),'MAP_FIXED_NOREPLACE; use PIE Python')
            if result!=address:
                libc.munmap(result,4096);raise RuntimeError('kernel ignored no-replace fixed mapping')
            regions.append(address)
        c.memmove(0x971530,original.read(0x971530,0xaf),0xaf)
        c.memmove(0xfce4e0,original.read(0xfce4e0,4),4)
        libm=c.CDLL(ctypes.util.find_library('m'))
        stub=b'\x48\xb8'+struct.pack('<Q',c.cast(libm.ceilf,c.c_void_p).value)+b'\xff\xe0'
        c.memmove(0x553678,stub,len(stub))
        for address,protection in ((0x971000,5),(0x553000,5),(0xfce000,1)):
            if libc.mprotect(address,4096,protection)!=0:raise OSError(c.get_errno(),'mprotect')
        fn=c.CFUNCTYPE(c.c_uint32,c.c_void_p,c.c_int32,c.c_uint32)(0x971530)
        template=c.create_string_buffer(0x800)
        rng=random.Random(0x971530)
        cases=[]
        for seed in (1,17,0x7fffffff,0x80000000,0xffffffff):
            for a,b,d,e,n in ((0,0,.01,.0125,12000),(0,0,.0175,.0175,22500),
                             (0,0,0,.5,1000),(0,0,.5,0,1000),(3,7,99,99,0),
                             (7,3,99,99,0),(1,1,0,0,0),(0,0,.5,.25,0),
                             (.5,2.5,0,0,1000),(0,0,.01,.01,650),(0,0,.01,.01,651)):
                cases.append((seed,a,b,d,e,n))
        for i in range(10000):
            seed=rng.randrange(1,2**32)
            if i%2:cases.append((seed,0,0,f32(rng.uniform(.0001,1)),f32(rng.uniform(.0001,1)),rng.randrange(0,30000)))
            else:cases.append((seed,f32(rng.uniform(0,100)),f32(rng.uniform(0,100)),0,0,0))
        expected=[];inputs=[]
        for seed,a,b,d,e,n in cases:
            struct.pack_into('<ff',template,0x634,a,b)
            struct.pack_into('<ff',template,0x5dc,d,e)
            old.seed(c.c_int32(seed).value)
            count=fn(c.addressof(template),0,n)
            expected.append((count,old.state()))
            inputs.append(f'p {seed} {bits(a)} {bits(b)} {bits(d)} {bits(e)} {n}\n')
        result=subprocess.run([str(probe)],input=''.join(inputs),text=True,capture_output=True,check=True,timeout=30)
        actual=[tuple(map(int,line.split())) for line in result.stdout.splitlines()]
        if actual!=expected:
            first=next((i for i,pair in enumerate(zip(actual,expected)) if pair[0]!=pair[1]),None)
            raise ValueError(f'population native mismatch at {first}: '+str((cases[first],actual[first],expected[first]) if first is not None else 'result count'))
        return len(expected)
    finally:
        for address in reversed(regions):libc.munmap(address,4096)
        old.close()


def main() -> int:
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--original',type=Path,required=True);p.add_argument('--probe',type=Path,required=True)
    a=p.parse_args()
    if platform.system()!='Linux' or platform.machine() not in ('x86_64','AMD64'):
        print('SKIP: native isolated functions require Linux x86-64');return 77
    source=Original(a.original)
    r=recovery(source,a.probe.resolve());n=population(source,a.probe.resolve())
    print(f'PASS: finite recovery {r} exact binary32 cases; population {n} counts AND RNG states; bounded native functions, NOT whole game')
    return 0
if __name__=='__main__':raise SystemExit(main())
