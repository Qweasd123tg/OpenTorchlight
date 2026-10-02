#!/usr/bin/env python3
"""Unchanged pause query and its real getter/property chain on explicit state.

Only CEGUI Window::isVisible is an evaluated-query adapter. Menu getters,
two-pass coverage, modal scan, console guard and GetInt are original bodies.
Property key index zero is explicit private initialized fixture state.
No constructors, game process, UI events or dynamic list mutation are executed.
"""
import argparse
import ctypes as c
import hashlib
import itertools
from pathlib import Path
import platform
import struct
import subprocess
import sys

sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from original import Original
from automation_state import validate_output, write_json
from native_typed_reference import Memory

PANELS=((0xB60ED0,0xB60F00,0x60),(0xB77580,0xB775B0,0x60),
        (0xBCCA70,0xBCCAA0,0x188),(0xBEE2B0,0xBEE2E0,0x38))


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--original',required=True,type=Path);parser.add_argument('--probe',required=True,type=Path)
    parser.add_argument('--output',required=True,type=Path);args=parser.parse_args()
    if platform.system()!='Linux' or platform.machine()!='x86_64':return 77
    validate_output(Path(__file__).resolve().parents[1],args.output,[args.original,args.probe])
    original=Original(args.original);memory=Memory();bodies=[]
    visibility=[False];errors=[]
    def visible(window,local):
        if local:errors.append('Console unexpectedly requested local visibility')
        return visibility[0]
    try:
        for entry in (0x56E570,0xA82AE0,0xA82A80,0xA84140,0xAE1DF0,0xC6E440,
                      *[entry for panel in PANELS for entry in panel[:2]]):
            symbol=next(s for s in original.symbols if s.address==entry and s.size)
            body=original.read(entry,symbol.size);memory.put(entry,body)
            bodies.append(dict(address=hex(entry),symbol=symbol.name,size=symbol.size,sha256=hashlib.sha256(body).hexdigest()))
        memory.put(0x150B4CC,bytes(4))
        memory.callback(0x5561D8,c.CFUNCTYPE(c.c_bool,c.c_size_t,c.c_bool),visible)
        memory.protect()
        run=c.CFUNCTYPE(c.c_ubyte,c.c_void_p)(0x56E570)
        client=c.create_string_buffer(0x1100);ui=c.create_string_buffer(0x1A00)
        props=c.create_string_buffer(0x60);console=c.create_string_buffer(0x30)
        integers=(c.c_int*1)();dialog=c.create_string_buffer(0x40)
        modal_array=(c.c_size_t*1)(c.addressof(dialog))
        menus=[c.create_string_buffer(0x200) for _ in PANELS]
        tables=[(c.c_size_t*6)() for _ in PANELS]
        array=(c.c_size_t*4)(*[c.addressof(menu) for menu in menus])
        for panel,menu,table in zip(PANELS,menus,tables):
            table[3]=panel[0];table[5]=panel[1];struct.pack_into('<Q',menu,0,c.addressof(table))
        struct.pack_into('<QQ',ui,0x1930,c.addressof(array),c.addressof(array)+32)
        struct.pack_into('<QQ',ui,0x1948,c.addressof(modal_array),c.addressof(modal_array)+8)
        struct.pack_into('<Q',ui,0x1690,c.addressof(console));struct.pack_into('<Q',console,0x18,1)
        struct.pack_into('<Q',client,0x50,c.addressof(props))
        struct.pack_into('<QQ',props,0x40,c.addressof(integers),c.addressof(integers)+4)
        inputs=[];expected=[]
        for forced,present,console_open,no_pause,modal,explicit,mask in itertools.product(
                (0,1),(0,1),(0,1),(-1,0,1),(0,1),(0,1),range(16)):
            client[0x10BB]=forced;struct.pack_into('<Q',client,0x78,c.addressof(ui) if present else 0)
            visibility[0]=bool(console_open);integers[0]=no_pause;dialog[0x30]=modal;ui[0x1999]=explicit
            for index,(menu,panel) in enumerate(zip(menus,PANELS)):menu[panel[2]]=(mask>>index)&1
            expected.append(run(c.addressof(client)))
            inputs.append(f'{forced} {present} {console_open} {no_pause} {modal} {explicit} {mask}\n')
        result=subprocess.run([str(args.probe.resolve())],input=''.join(inputs),text=True,capture_output=True,check=True,timeout=30)
        actual=[int(line) for line in result.stdout.splitlines()]
        if actual!=expected or errors:
            bad=next((i for i,(a,b) in enumerate(zip(actual,expected)) if a!=b),None)
            raise AssertionError(f'pause mismatch {bad}: {inputs[bad] if bad is not None else "result count"}; {errors}')
        write_json(args.output,dict(schema=1,kind='original-pause-comparison',status='PASS',
            original_elf_sha256=original.sha256,bodies=bodies,cases=len(expected),
            scope=__doc__,game_executed=False,original_status_promotions=0))
        print(f'PASS original pause comparisons={len(expected)}, 14 unchanged bodies, one explicit visibility adapter')
        return 0
    finally:memory.close()


if __name__=='__main__':raise SystemExit(main())
