#!/usr/bin/env python3
"""Bounded speed arithmetic comparison, NOT execution of original CCharacter/ELF.
Two unchanged slices from attack @82b550; mock getEffectValue returns one float.
The synthetic ABI adapter and return are outside the preserved instruction spans.
Without --original, 0/1/100/.2 constants are fixture inputs: ELF constants unverified.
With --original, its pinned SHA and all referenced constants are checked first.
Runs only on Linux x86-64, never writes installed game files; the slices and fixture constants share a relocated window.
"""
from __future__ import annotations
import argparse, ctypes, hashlib, itertools, json, math, mmap, platform, random, struct, subprocess
from pathlib import Path
from compare_ai_cooldown import Executable, asm_bytes, bits, f32
from verify_original_entry_dispatch import ELF_SHA256, virtual_bytes

SLICES=[(0x82b976,0x82b9c5),(0x82bcea,0x82bd46)]
# Pinned instruction digests populated from the supplied export, not live ELF claims.
DIGESTS=['02299d125757691c84ba91e8606a95851c8b08e9bbe58ab80af11538fe34988f', '375647ab6819dd2d2e103a1570ff440bee72ba845b26afc0ab19330959f547c5']
CONSTANTS={0xfa47fc:1.,0xfa483c:100.,0xfa86e8:.2}

def compare(probe,code,resource_cases=()):
    mapped=None;wrapper=None
    try:
        # Relocate the entire sparse text/constant window by ONE common bias.
        # Relative calls, branches and RIP-relative loads remain byte-for-byte intact.
        low=0x810000
        window=bytearray(0xfa9000-low)
        def write(address,raw):
            offset=address-low
            if offset<0 or offset+len(raw)>len(window):raise ValueError('mapped window bounds')
            window[offset:offset+len(raw)]=raw
        for (start,end),raw in zip(SLICES,code):write(start,raw)
        write(0x8137e0,bytes.fromhex('f3 0f 10 43 10 c3')) # synthetic getEffectValue
        write(0x82b9c5,bytes.fromhex('48 83 c4 40 5b c3')) # synthetic return
        for address,value in CONSTANTS.items():write(address,struct.pack('<f',value))
        mapped=Executable(bytes(window))
        # void* character, float haste, float resistance; RBX preserved, stack call-aligned.
        adapter=bytes.fromhex('53 48 89 fb 48 83 ec 40 0f 57 db f3 0f 11 5c 24 20 f3 0f 11 4b 10 48 b8')+struct.pack('<Q',mapped.address+0x82b976-low)+bytes.fromhex('ff e0')
        wrapper=Executable(adapter)
        call=ctypes.CFUNCTYPE(ctypes.c_float,ctypes.c_void_p,ctypes.c_float,ctypes.c_float)(wrapper.address)
        character=ctypes.create_string_buffer(0x800);description=ctypes.create_string_buffer(0x80)
        ctypes.c_void_p.from_buffer(character,0x390).value=ctypes.addressof(description)
        denom=ctypes.c_float.from_buffer(description,0x70)
        cases=list(itertools.product([.01,.2,.5,1.,1.1,2.,10.],[-1000.,-100.,-60.,-0.,0.,50.,100.,1000.],[-200.,0.,25.,50.,99.,100.,200.]))
        rng=random.Random(0x82b550)
        cases += [(f32(rng.uniform(.01,20)),f32(rng.uniform(-2000,2000)),f32(rng.uniform(-100,300))) for _ in range(12000)]
        cases += list(resource_cases)
        expected=[];requests=[]
        for d,h,r in cases:
            denom.value=d
            expected.append(bits(call(ctypes.addressof(character),h,r)))
            requests.append(f'{bits(d)} {bits(h)} {bits(r)}\n')
        result=subprocess.run([str(probe.resolve())],input=''.join(requests),text=True,capture_output=True,check=True,timeout=30)
        actual=[int(line) for line in result.stdout.splitlines()]
        if len(actual)!=len(expected):raise ValueError('probe length mismatch')
        for i,(a,b) in enumerate(zip(expected,actual)):
            if a!=b:raise ValueError(f'case {i}, {cases[i]}: slice={a:08x}, portable={b:08x}')
        return len(cases)
    finally:
        if wrapper:wrapper.close()
        if mapped:mapped.close()

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--probe',required=True,type=Path)
    p.add_argument('--original',type=Path)
    p.add_argument('--scenario-dir',type=Path,
                   help='add SPEED/100 cases from successful real-pak application captures; zero effects are an explicit numeric fixture')
    p.add_argument('--disassembly',type=Path,default=Path(__file__).resolve().parents[1]/'research/disassembly/82b550-attack-speed.asm')
    args=p.parse_args()
    if platform.system()!='Linux' or platform.machine() not in ('x86_64','AMD64'):
        print('SKIP: speed instruction adapter requires Linux x86-64');return 77
    try:
        image=args.original.read_bytes() if args.original else None
        if image is not None:
            if hashlib.sha256(image).hexdigest()!=ELF_SHA256:raise ValueError('ELF SHA-256 mismatch')
            for address,value in CONSTANTS.items():
                if virtual_bytes(image,address,4)!=struct.pack('<f',value):raise ValueError(f'constant mismatch at {address:x}')
        code=[virtual_bytes(image,a,b-a) if image is not None else asm_bytes(args.disassembly,a,b) for a,b in SLICES]
        for raw,digest in zip(code,DIGESTS):
            if hashlib.sha256(raw).hexdigest()!=digest:raise ValueError('instruction digest mismatch')
        resource_cases=[]
        if args.scenario_dir:
            observations={}
            for state_path in sorted(args.scenario_dir.glob('*/*.state.json')):
                environment=state_path.parent/'environment.json'
                if not environment.is_file():raise ValueError('scenario has no provenance environment')
                metadata=json.loads(environment.read_text())
                if metadata.get('status')!='PASSED' or not metadata.get('pak_sha256'):
                    raise ValueError('failed/unidentified resource scenario')
                for item in json.loads(state_path.read_text()).get('inventory',[]):
                    if 'speed' not in item:continue
                    speed=float(item['speed'])
                    if not math.isfinite(speed) or speed<=0:raise ValueError('invalid captured weapon speed')
                    observations[(item['guid'],speed)]=f32(f32(speed)/100.)
            if not observations:raise ValueError('no captured weapon SPEED values')
            resource_cases=[(d,0.,0.) for d in observations.values()]
        count=compare(args.probe,code,resource_cases)
        if resource_cases:print(f'Resource-backed extra inputs: {len(resource_cases)} concrete weapon GUID/SPEED pairs; effects deliberately set to zero; NOT full attack trace')
    except (OSError,ValueError,subprocess.SubprocessError) as e:p.exit(1,f'FAIL: {e}\n')
    print(f'PASS: {count} bit-exact speed cases; '+('SHA-checked ELF slices/constants' if image is not None else 'pinned export slices with explicit fixture constants, not ELF validation'))
    return 0
if __name__=='__main__':raise SystemExit(main())
