#!/usr/bin/env python3
"""Compare generated scalar UI Y scaling/GetFloat with unchanged original bodies.

UI/settings objects and evaluated dynamic property indices are explicit fixtures.
The caller trampoline returns XMM0 bits in EAX without a Python float conversion.
X scaling is optional native calibration only, with no production X policy claim.
No constructors, global registration, fenv/MXCSR parity, game timing or GUI runs.
"""
import argparse
import ctypes as c
import hashlib
import json
from pathlib import Path
import platform
import random
import struct
import subprocess
import sys

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'tools'))
from automation_state import validate_output, write_json
from original import Original
from native_typed_reference import Memory

Y=0xA83E70
X=0xA83EA0
GET=0xC6E410
ENTRIES=((Y,36),(GET,41))
Y_INDEX=0x150B470
X_INDEX=0x150B46C
MINUS_ONE=0xFA8760


class Native(Memory):
    def __init__(self,original,calibrate_x=False):
        super().__init__()
        self.bodies=[]
        try:
            for address,size in ENTRIES+(((X,36),) if calibrate_x else ()):
                symbols={s for s in original.symbols if s.address==address and s.size}
                if len(symbols)!=1 or next(iter(symbols)).size!=size:
                    raise ValueError(f'original whole symbol size drifted: {address:#x}')
                body=original.read(address,size)
                self.put(address,body)
                self.bodies.append(dict(address=hex(address),size=size,
                    sha256=hashlib.sha256(body).hexdigest()))
            literal=original.read(MINUS_ONE,4)
            if literal!=struct.pack('<I',0xBF800000):
                raise ValueError('original GetFloat out-of-bounds literal drifted')
            self.put(MINUS_ONE,literal)
            # Synthetic evaluated bindings: both fixture property IDs are zero.
            # The original global registration/index discovery is not executed.
            self.put(Y_INDEX,struct.pack('<I',0))
            if calibrate_x:self.put(X_INDEX,struct.pack('<I',0))
            for i,address in enumerate([Y,GET]+([X] if calibrate_x else [])):
                wrapper=0x20000000+0x100*i
                # raw offset bits arrive in ESI for scaling; original ABI wants
                # XMM0. GetFloat keeps ESI as its actual uint32 index argument.
                initialize=bytes.fromhex('66 0f 6e c6') if address!=GET else b''
                self.put(wrapper,initialize+bytes.fromhex('48 83 ec 08 48 b8')+
                    struct.pack('<Q',address)+bytes.fromhex(
                        'ff d0 66 0f 7e c0 48 83 c4 08 c3'))
                function=c.CFUNCTYPE(c.c_uint32,c.c_void_p,c.c_uint32)(wrapper)
                if address==Y:self.scaled_y=function
                elif address==X:self.scaled_x=function
                else:self.get=function
            self.protect()
        except BaseException:
            self.close()
            raise

    @staticmethod
    def settings(values,rng):
        # Guard bytes are part of every observed buffer, including empty vectors.
        raw_values=bytearray(rng.randbytes(16+4*len(values)+16))
        for i,value in enumerate(values):struct.pack_into('<I',raw_values,16+4*i,value)
        vector=c.create_string_buffer(bytes(raw_values),len(raw_values))
        settings=c.create_string_buffer(rng.randbytes(0x80),0x80)
        start=c.addressof(vector)+16
        struct.pack_into('<QQ',settings,0x58,start,start+4*len(values))
        return settings,vector

    def property(self,values,index,rng):
        settings,vector=self.settings(values,rng)
        before=(bytes(settings),bytes(vector))
        result=self.get(c.addressof(settings),index)
        if before!=(bytes(settings),bytes(vector)):
            raise AssertionError('original GetFloat mutated full settings/vector fixture')
        return result

    def scale(self,offset,ratio,rng,x=False):
        settings,vector=self.settings([ratio],rng)
        ui=c.create_string_buffer(rng.randbytes(0x80),0x80)
        struct.pack_into('<Q',ui,0x78,c.addressof(settings))
        before=(bytes(ui),bytes(settings),bytes(vector))
        result=(self.scaled_x if x else self.scaled_y)(c.addressof(ui),offset)
        if before!=(bytes(ui),bytes(settings),bytes(vector)):
            raise AssertionError('original scalar scaling mutated UI/settings/vector fixture')
        return result


def accepted_inputs(original):
    """Pin complete bodies and each executed instruction in accepted raw inputs."""
    sources=[]
    for address in (Y,GET):
        path=ROOT/'research/lifted-ui'/f'{address:08x}.json'
        data=json.loads(path.read_text())
        if data['original_elf_sha256']!=original.sha256 or int(data['address'],16)!=address:
            raise ValueError('accepted scaling raw input differs from source identity')
        symbol=next(s for s in original.symbols if s.address==address and s.size)
        if (data['original_symbol_size']!=symbol.size or
                hashlib.sha256(original.read(address,symbol.size)).hexdigest()!=
                data['original_symbol_body_sha256']):
            raise ValueError(f'accepted whole symbol body drifted: {address:#x}')
        for row in data['instructions']:
            raw=bytes.fromhex(row['bytes'])
            if raw!=original.read(int(row['address'],16),len(raw)):
                raise ValueError(f'accepted instruction drifted: {row["address"]}')
        sources.append(dict(path=str(path.relative_to(ROOT)),
            sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
    return sources


def cases():
    rng=random.Random(Y)
    # Finite boundaries, precision-rounding ties, zeros, overflow and underflow.
    finite=[0,0x80000000,1,2,3,0x007FFFFF,0x00800000,0x00800001,
        0x3EAAAAAB,0x3F000000,0x3F7FFFFF,0x3F800000,0x3F800001,
        0x3FC00000,0x40000000,0x40400000,0x4B800000,0x7F7FFFFF,
        0xBF000000,0xBF800000,0xFF7FFFFF]
    nonfinite=[0x7F800000,0xFF800000,0x7FC12345,0xFFC23456,
        0x7F800001,0xFF800123]
    scale=[(offset,ratio,'finite') for offset in finite for ratio in finite]
    scale += [(offset,ratio,'raw_nonfinite') for offset in finite+nonfinite
                for ratio in finite+nonfinite if offset in nonfinite or ratio in nonfinite]
    scale += [(rng.getrandbits(32),rng.getrandbits(32),'random_bits') for _ in range(2048)]
    properties=[]
    for count in (0,1,2,7,32):
        values=(finite+nonfinite)[:count]
        if len(values)<count:values += [rng.getrandbits(32) for _ in range(count-len(values))]
        indices={0,1,2,count,max(0,count-1),count+1,0x7FFFFFFF,0x80000000,0xFFFFFFFF}
        indices.update(range(count))
        properties += [(values,index) for index in sorted(indices)]
    properties += [([rng.getrandbits(32) for _ in range(rng.randrange(33))],
                    rng.getrandbits(32)) for _ in range(512)]
    return scale,properties


def compare(original,probe,calibrate_x=False):
    sources=accepted_inputs(original)
    scale,properties=cases()
    rng=random.Random(GET)
    payload=[];expected=[];labels=[]
    with_native=Native(original,calibrate_x)
    calibration=[]
    try:
        for offset,ratio,kind in scale:
            payload.append(f's {offset} {ratio}\n')
            native=with_native.scale(offset,ratio,rng)
            expected.append(native)
            labels.append(dict(operation='scaledY',offset_bits=hex(offset),ratio_bits=hex(ratio),kind=kind))
            if calibrate_x:
                answer=with_native.scale(offset,ratio,rng,x=True)
                if answer!=native:
                    calibration.append(dict(offset_bits=hex(offset),ratio_bits=hex(ratio),
                        y_result_bits=hex(native),x_result_bits=hex(answer)))
        for values,index in properties:
            payload.append('g '+str(len(values))+' '+str(index)+' '+
                ' '.join(map(str,values))+'\n')
            expected.append(with_native.property(values,index,rng))
            labels.append(dict(operation='GetFloat',count=len(values),index=index,
                values_bits=[hex(value) for value in values]))
        result=subprocess.run([str(probe.resolve())],input=''.join(payload),
            text=True,capture_output=True,check=True,timeout=60)
        actual=[int(row) for row in result.stdout.splitlines()]
        if len(actual)!=len(expected):raise ValueError('production probe result count differs')
        mismatches=[dict(case=i,**labels[i],original_bits=hex(want),production_bits=hex(got))
            for i,(want,got) in enumerate(zip(expected,actual)) if want!=got]
        return dict(status='FAIL' if mismatches or calibration else 'PASS',cases=len(expected),
            scaling_cases=len(scale),property_cases=len(properties),
            mismatch_count=len(mismatches),mismatches=mismatches,
            whole_original_bodies=with_native.bodies,original_elf_sha256=original.sha256,
            accepted_instruction_inputs=sources,
            observed_buffers='all bytes: UI 128, settings 128, vector values plus 16-byte guards',
            evaluated_property_bindings=dict(y_fixture_index=0,
                x_fixture_index=0 if calibrate_x else None,
                source_global_registration='not executed'),
            x_native_calibration=dict(cases=len(scale) if calibrate_x else 0,
                mismatch_count=len(calibration),mismatches=calibration,
                scope='native X/Y scalar calibration with equal evaluated property values; no production X caller policy'),
            scope='Whole scalarY/GetFloat bodies, raw return bits including NaN payloads, uint32 index edges/control exits. Explicit borrowed values and property bindings. No original constructors, global registration, fenv/MXCSR parity, game timing, ownership or GUI.')
    finally:
        with_native.close()


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    for name in ('original','probe','output'):parser.add_argument('--'+name,type=Path,required=True)
    parser.add_argument('--calibrate-x',action='store_true',help='separate native X/Y scalar calibration')
    args=parser.parse_args()
    if platform.system()!='Linux' or platform.machine()!='x86_64':return 77
    validate_output(ROOT,args.output,[args.original,args.probe])
    report=compare(Original(args.original),args.probe,args.calibrate_x)
    write_json(args.output,report)
    print(f'{report["status"]}: {report["cases"]} cases '
        f'({report["scaling_cases"]} scaling, {report["property_cases"]} properties), '
        f'{report["mismatch_count"]} raw-bit mismatches; '
        f'X native calibration {report["x_native_calibration"]["cases"]} cases')
    return 0 if report['status']=='PASS' else 1


if __name__=='__main__':raise SystemExit(main())
