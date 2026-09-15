#!/usr/bin/env python3
"""Compare bounded original numeric code, not a whole player/menu/game.
The three preserved spans come from targeted exports. Sparse relocation retains
all branch/call/load bytes. Synthetic dependencies: no-op journal, two fixed
getEffectValue fields, the host libm ceilf. Menu callbacks/GUI are not executed.
With --original the pinned ELF and constant are read-only verified first.
"""
from __future__ import annotations
import argparse, ctypes, ctypes.util, hashlib, itertools, json, platform, random, struct, subprocess
from pathlib import Path
from compare_ai_cooldown import Executable, asm_bytes, bits, f32
from verify_original_entry_dispatch import ELF_SHA256, virtual_bytes

ROOT=Path(__file__).resolve().parents[1]
SPANS=[('811a70-give-gold.asm',0x811a70,0x811ae8,'34a3d279a232cc6de1b9b4611d3517a3c347b788e3bff305db1282e1afbead3f'),
       ('813a10-max-mana.asm',0x813a10,0x813a8f,'15f681219ff12dafcd1f52668cfbb59c6543fe204be40520c9f52cd19ce43970'),
       ('b05ec0-death-menu-click.asm',0xb06060,0xb060a8,'e1b4b2a89fa6846c47707c5969ba0d35d4377617121b741da47bc907ed99d6c4')]


def constants(probe:Path):
    evidence=json.loads((ROOT/'research/original-combat-inputs.json').read_text())
    if evidence['elf_sha256']!=ELF_SHA256:raise ValueError('evidence belongs to another binary')
    names=['speed_one','percentage_divisor','minimum_attack_speed','innate_attack_range_default',
           'innate_strike_range_default','melee_vertical_cutoff','ai_flag_one_speed_multiplier']
    lines=subprocess.run([str(probe.resolve()),'--constants'],capture_output=True,text=True,check=True,timeout=30).stdout.splitlines()
    if len(lines)!=8:raise ValueError('constant probe output count')
    for n,line in zip(names,lines):
        entry=evidence['constants'][n]
        raw=bytes.fromhex(entry['bytes_le'])
        if len(raw)!=4 or bits(entry['float32'])!=int.from_bytes(raw,'little'):raise ValueError('inconsistent evidence JSON')
        if int(line)!=int.from_bytes(raw,'little'):raise ValueError(f'compiled constant differs: {n}')
    if lines[-1]!=evidence['effect_catalog_path']['utf32le_text']:raise ValueError('wrong effect catalog path')


def compare(probe:Path,image:bytes|None):
    low=0x550000;window=bytearray(0xfa4900-low)
    def write(va,raw):
        offset=va-low
        if offset<0 or offset+len(raw)>len(window):raise ValueError('sparse map bounds')
        window[offset:offset+len(raw)]=raw
    for file,start,end,digest in SPANS:
        raw=virtual_bytes(image,start,end-start) if image is not None else asm_bytes(ROOT/'research/disassembly'/file,start,end)
        if hashlib.sha256(raw).hexdigest()!=digest:raise ValueError('unexpected code span')
        write(start,raw)
    write(0x8119e0,b'\xc3') # synthetic journal sink
    # Synthetic effect manager returns pct / flat from fixture fields.
    write(0x8137e0,bytes.fromhex('83 fe 13 75 09 f3 0f 10 87 00 07 00 00 c3 f3 0f 10 87 04 07 00 00 c3'))
    libm=ctypes.CDLL(ctypes.util.find_library('m'))
    ceil_address=ctypes.cast(libm.ceilf,ctypes.c_void_p).value
    write(0x553678,b'\x48\xb8'+struct.pack('<Q',ceil_address)+b'\xff\xe0')
    write(0xfa483c,struct.pack('<f',100))
    write(0xb060a8,bytes.fromhex('5d c3')) # synthetic end of menu arithmetic
    executable=Executable(bytes(window));adapter=None
    try:
        gold_fn=ctypes.CFUNCTYPE(None,ctypes.c_void_p,ctypes.c_int32)(executable.address+0x811a70-low)
        mana_fn=ctypes.CFUNCTYPE(ctypes.c_int32,ctypes.c_void_p)(executable.address+0x813a10-low)
        adapter=Executable(bytes.fromhex('55 48 89 f5 48 b8')+struct.pack('<Q',executable.address+0xb06060-low)+bytes.fromhex('ff e0'))
        fee_fn=ctypes.CFUNCTYPE(None,ctypes.c_void_p,ctypes.c_void_p)(adapter.address)
        actor=ctypes.create_string_buffer(0x800);menu=ctypes.create_string_buffer(0x110)
        requests=[];expected=[];rng=random.Random(0x813a10)
        gold_cases=list(itertools.product([0,1,9,10,11,109,2147483646,2147483647],[-2147483648,-2147483647,-100,-1,0,1,10,2147483647]))
        gold_cases += [(rng.randrange(2147483648),rng.randrange(-2147483648,2147483648)) for _ in range(2000)]
        for gold,delta in gold_cases:
            ctypes.c_int32.from_buffer(actor,0x444).value=gold
            gold_fn(ctypes.addressof(actor),delta)
            expected.append(ctypes.c_int32.from_buffer(actor,0x444).value);requests.append(f'0 {gold} {delta}\n')
        mana_cases=list(itertools.product([0,1,31,1000,16777217],[-2.5,0.,.5,10.75],[-90.,0.,12.5,100.],[-.5,0.,.2,100.]))
        mana_cases += [(rng.randrange(50000),f32(rng.uniform(-10,100)),f32(rng.uniform(-90,300)),f32(rng.uniform(-.5,1000))) for _ in range(2000)]
        for base,growth,pct,flat in mana_cases:
            ctypes.c_int32.from_buffer(actor,0x43c).value=base
            ctypes.c_float.from_buffer(actor,0x440).value=growth
            ctypes.c_float.from_buffer(actor,0x700).value=pct
            ctypes.c_float.from_buffer(actor,0x704).value=flat
            expected.append(mana_fn(ctypes.addressof(actor)));requests.append(f'1 {base} {bits(growth)} {bits(pct)} {bits(flat)}\n')
        fee_cases=list(range(111))+[2147483646,2147483647]+[rng.randrange(2147483648) for _ in range(2000)]
        for gold in fee_cases:
            ctypes.c_int32.from_buffer(actor,0x444).value=gold
            fee_fn(ctypes.addressof(menu),ctypes.addressof(actor))
            if (ctypes.c_int32.from_buffer(menu,0xc4).value,ctypes.c_int32.from_buffer(menu,0xf8).value,
                ctypes.c_int32.from_buffer(menu,0xfc).value)!=(1,0,0):raise ValueError('entry mode or xp/fame branch mismatch')
            expected.append(ctypes.c_int32.from_buffer(menu,0x100).value);requests.append(f'2 {gold}\n')
        result=subprocess.run([str(probe.resolve())],input=''.join(requests),capture_output=True,text=True,check=True,timeout=30)
        actual=[int(line) for line in result.stdout.splitlines()]
        if len(actual)!=len(expected):raise ValueError('numeric probe length')
        for i,(a,b) in enumerate(zip(actual,expected)):
            if a!=b:raise ValueError(f'case {i}, request={requests[i].strip()}: portable={a} native={b}')
        return len(gold_cases),len(mana_cases),len(fee_cases)
    finally:
        if adapter:adapter.close()
        executable.close()


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--probe',required=True,type=Path);p.add_argument('--original',type=Path)
    p.add_argument('--constants-only',action='store_true');args=p.parse_args()
    try:
        constants(args.probe)
        if args.constants_only:
            print('PASS: seven compiled float32 constants and effect path match integrator pinned-ELF JSON');return 0
        if platform.system()!='Linux' or platform.machine() not in ('x86_64','AMD64'):
            print('SKIP: instruction adapter requires Linux x86-64');return 77
        image=args.original.read_bytes() if args.original else None
        if image is not None:
            if hashlib.sha256(image).hexdigest()!=ELF_SHA256:raise ValueError('ELF SHA mismatch')
            if virtual_bytes(image,0xfa483c,4)!=struct.pack('<f',100):raise ValueError('ELF divisor mismatch')
        gold,mana,fee=compare(args.probe,image)
        print(f'PASS: gold={gold}, mana={mana}, entry fee={fee}; unchanged numeric spans, synthetic dependencies; '+
              ('SHA-checked ELF inputs' if image is not None else 'targeted export bytes, NOT whole original game'))
    except (OSError,ValueError,subprocess.SubprocessError) as e:p.exit(1,f'FAIL: {e}\n')
    return 0
if __name__=='__main__':raise SystemExit(main())
