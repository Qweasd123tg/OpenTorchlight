#!/usr/bin/env python3
"""Read-only, fingerprint-gated native UI probes for the supplied Linux ELF.

Linux x86-64 only; run as a separate unprivileged process. The original loader,
constructors and game are NOT launched. MAP_FIXED_NOREPLACE and RX code protect
existing mappings. Pause decisions execute eight original functions unchanged;
objects/vtables are controlled test fixtures, not original constructed objects.
Scaling executes three original functions unchanged; CEGUI accessors and settings
lookup are controlled callbacks, so CEGUI geometry/layout rendering is NOT tested.
No original instructions/assets are bundled in this package.
"""
from __future__ import annotations
import argparse
import ctypes as C
import itertools
import json
import os
from pathlib import Path
import platform
import random
import struct
from original_reader import Original

VOID = C.c_void_p
U64 = C.c_uint64
F4 = C.c_float * 4
FUNCTIONS = {
    'pause': ('CGameClient::getIsPaused()', 0x56e570, 0x8d),
    'both': ('CGameUI::bothCoveredPartial()', 0xa82ae0, 0x115),
    'modal': ('CGameUI::modalDialogOpenPartial()', 0xa82a80, 0x56),
    'console': ('CGameUI::getConsoleIsOpen()', 0xa84140, 0x1b),
    'inv_right': ('CInventoryMenu::isRight()', 0xb60ed0, 6),
    'inv_partial': ('CInventoryMenu::openPartial()', 0xb60f00, 5),
    'pet_right': ('CPetMenu::isRight()', 0xba5180, 3),
    'pet_partial': ('CPetMenu::openPartial()', 0xba51b0, 5),
    'handle_click': ('CGameUI::handle_onClick(CEGUI::EventArgs const&)', 0xa83690, 0x2e),
    'scale': ('CGameUI::convertToScreenScale(CEGUI::Window*, bool)', 0xa83ed0, 0x172),
    'sx': ('CGameUI::scaledX(float)', 0xa83ea0, 0x24),
    'sy': ('CGameUI::scaledY(float)', 0xa83e70, 0x24),
}

def address(obj):
    return C.addressof(obj)

def pointer(obj, offset, value):
    U64.from_buffer(obj, offset).value = value

def byte(obj, offset, value):
    C.c_ubyte.from_buffer(obj, offset).value = int(value)

def f32(value):
    return struct.unpack('<f', struct.pack('<f', value))[0]

def floats(values):
    return struct.pack('<' + 'f' * len(values), *values)

class MappedFunctions:
    def __init__(self, elf):
        if platform.system() != 'Linux' or platform.machine() not in {'x86_64','AMD64'}:
            raise RuntimeError('Native probes require Linux x86-64')
        if os.sysconf('SC_PAGE_SIZE') != 4096:
            raise RuntimeError('Native probes require 4096-byte pages')
        self.libc = C.CDLL(None, use_errno=True)
        self.libc.mmap.argtypes = [VOID, C.c_size_t, C.c_int, C.c_int, C.c_int, C.c_long]
        self.libc.mmap.restype = VOID
        self.libc.mprotect.argtypes = [VOID, C.c_size_t, C.c_int]
        self.libc.munmap.argtypes = [VOID, C.c_size_t]
        self.pages = set()
        self.callbacks = []
        self.order = []
        self.ratios = (1.,1.)
        try:
            for name, at, size in FUNCTIONS.values():
                symbol = elf.symbol(name)
                if (symbol.address, symbol.size) != (at,size):
                    raise ValueError('Unexpected original symbol: ' + name)
                self.put(at, elf.read(at,size))
            # Controlled setting ids, not production global initialisation.
            self.put(0x150b46c, struct.pack('<II',1,2))
            self.callback(0xc6e410, C.c_float, [VOID,C.c_uint],
                          lambda _settings,key: self.ratios[key-1])
            # Controlled UVector2 storage starts at +0x100 / +0x110 in fake windows.
            self.callback(0x555518, VOID, [VOID], lambda win: win + 0x100)
            def set_position(win, values):
                C.memmove(win+0x100, values, 16)
                self.order.append((win, 'position'))
            def get_size(out,win):
                C.memmove(out, win+0x110, 16)
                return out
            def set_size(win, values):
                C.memmove(win+0x110, values, 16)
                self.order.append((win, 'size'))
            self.callback(0x5548a8,None,[VOID,VOID],set_position)
            self.callback(0x5532a8,VOID,[VOID,VOID],get_size)
            self.callback(0x555178,None,[VOID,VOID],set_size)
            for p in self.pages:
                if self.libc.mprotect(p,4096,3 if p == 0x150b000 else 5):
                    raise OSError(C.get_errno(),'mprotect failed')
            self.pause = C.CFUNCTYPE(C.c_bool, VOID)(FUNCTIONS['pause'][1])
            self.scale = C.CFUNCTYPE(None,VOID,VOID,C.c_bool)(FUNCTIONS['scale'][1])
            self.handle_click = C.CFUNCTYPE(C.c_bool,VOID,VOID)(FUNCTIONS['handle_click'][1])
        except BaseException:
            self.close()
            raise

    def put(self, at, data):
        first,last = at & ~4095,(at + len(data) - 1) & ~4095
        for p in range(first,last+4096,4096):
            if p in self.pages:
                continue
            got = self.libc.mmap(p,4096,3,0x100000 | 0x20 | 2,-1,0)
            if got == VOID(-1).value:
                raise OSError(C.get_errno(), 'mmap MAP_FIXED_NOREPLACE failed')
            if got != p:
                self.libc.munmap(got,4096)
                raise RuntimeError('MAP_FIXED_NOREPLACE not honored')
            self.pages.add(p)
        C.memmove(at,data,len(data))

    def callback(self, at, result, args, body):
        cb = C.CFUNCTYPE(result,*args)(body)
        self.callbacks.append(cb)
        # Tail jump to the controlled external dependency.
        self.put(at,b'\x48\xb8' + struct.pack('<Q',C.cast(cb,VOID).value) + b'\xff\xe0')

    def close(self):
        for p in self.pages:
            self.libc.munmap(p,4096)
        self.pages.clear()


def pause_probes(native):
    inv_vtable,pet_vtable = (U64*6)(),(U64*6)()
    inv_vtable[3],inv_vtable[5] = FUNCTIONS['inv_right'][1],FUNCTIONS['inv_partial'][1]
    pet_vtable[3],pet_vtable[5] = FUNCTIONS['pet_right'][1],FUNCTIONS['pet_partial'][1]
    count = 0
    examples = []
    # Exhaustive small registries, including no panels and repeated same-side panels.
    for n in range(4):
        for states in itertools.product(((0,0),(0,1),(1,0),(1,1)),repeat=n):
            panels = []
            for right, opened in states:
                panel = C.create_string_buffer(0x80)
                pointer(panel,0,address(inv_vtable if right else pet_vtable))
                byte(panel,0x60 if right else 0x68,opened)
                panels.append(panel)
            arr = (U64*max(n,1))(*[address(p) for p in panels])
            for modal,explicit,client_stop in itertools.product((0,1),repeat=3):
                client,ui,dialog = C.create_string_buffer(0x1100),C.create_string_buffer(0x1a00),C.create_string_buffer(0x40)
                dialogs = (U64*1)(address(dialog))
                pointer(client,0x78,address(ui))
                pointer(ui,0x1930,address(arr))
                pointer(ui,0x1938,address(arr)+n*8)
                pointer(ui,0x1948,address(dialogs))
                pointer(ui,0x1950,address(dialogs)+8)
                byte(dialog,0x30,modal)
                byte(ui,0x1999,explicit)
                byte(client,0x10bb,client_stop)
                expected = bool(client_stop or modal or explicit or
                                (any(not r and o for r,o in states) and any(r and o for r,o in states)))
                actual = bool(native.pause(address(client)))
                if actual != expected:
                    raise AssertionError(('pause',states,modal,explicit,client_stop,actual,expected))
                count += 1
                if (not modal and not explicit and not client_stop and
                    (states in ((),((1,1),),((0,1),),((0,1),(1,1)),((1,1),(1,1))))):
                    examples.append({'panels':[{'side':'right' if r else 'left','partial_open':bool(o)} for r,o in states],
                                     'original_paused':actual})
    # Null UI path is also original code, not a callback.
    for flag in (0,1):
        client=C.create_string_buffer(0x1100)
        byte(client,0x10bb,flag)
        assert bool(native.pause(address(client))) == bool(flag)
        count += 1
    return {'cases':count,'passed':count,'examples':examples,
            'scope':'Original decision functions and original Inventory/Pet side/partial getters; controlled objects and vtables, console absent. No actual panel open/close lifecycle tested.'}


def click_probes(native,elf):
    event_symbol=elf.symbol('CEGUI::Window::EventMouseButtonDown')
    assert event_symbol.address==0x14247e0
    # The original subscription passes THIS event object, not EventClicked.
    assert elf.read(0xa97f04,5)==b'\xba\xe0\x47\x42\x01'
    called=[]
    @C.CFUNCTYPE(C.c_bool,VOID,C.c_int)
    def on_click(_ui,command):
        called.append(command)
        return True
    vtable=(U64*3)();vtable[2]=C.cast(on_click,VOID).value
    ui=C.create_string_buffer(8);pointer(ui,0,address(vtable))
    count=0
    for command in (1,34,213):
        code=C.c_int(command)
        win=C.create_string_buffer(0x1e0);pointer(win,0x1d8,address(code))
        for present,button in itertools.product((False,True),range(8)):
            event=C.create_string_buffer(0x30)
            pointer(event,0x10,address(win) if present else 0)
            C.c_int.from_buffer(event,0x28).value=button
            called.clear()
            result=native.handle_click(address(ui),address(event))
            expected=[command] if present and button==0 else []
            if not result or called!=expected:
                raise AssertionError(('click',present,button,command,result,called))
            count+=1
    return {'cases':count,'passed':count,'subscription_event':'CEGUI::Window::EventMouseButtonDown',
            'event_symbol_address':hex(event_symbol.address),'subscription_argument_instruction':'0xa97f04',
            'scope':'Original handler dispatches immediately for mouse button code 0 with a window. UI onClick virtual target is a recording callback. CEGUI event generation/capture and actual gameplay command are not executed.'}


def scaling_probes(native,elf):
    rng = random.Random(140015)
    ui = C.create_string_buffer(0x80)
    checked_nodes=0
    scalar_checks=0
    calls=0
    roundtrip_examples=[]
    constants = {hex(at):struct.unpack('<f',elf.read(at,4))[0] for at in (0xfa4804,0xfa4808)}
    assert constants == {'0xfa4804':768.0,'0xfa4808':1/1024}
    for width,height in ((1024,768),(1280,720),(1920,1080),(2560,1440),(1023,767)):
        native.ratios=(f32(width*constants['0xfa4808']),f32(height/constants['0xfa4804']))
        for use_x in (False,True):
            ratio=native.ratios[0 if use_x else 1]
            for case in range(40):
                nodes=[C.create_string_buffer(0x120) for _ in range(3)]
                child=(U64*2)(address(nodes[1]),address(nodes[2]))
                pointer(nodes[0],0x78,address(child));pointer(nodes[0],0x80,address(child)+16)
                initial=[]
                for node in nodes:
                    values=[f32(rng.uniform(-1,1) if k%2==0 else rng.uniform(-1024,2048)) for k in range(8)]
                    initial.append(values)
                    C.memmove(address(node)+0x100,floats(values),32)
                native.order.clear()
                native.scale(address(ui),address(nodes[0]),use_x)
                calls+=1
                expected_order=[(address(nodes[k]),mode) for k in (1,2,0) for mode in ('position','size')]
                if native.order!=expected_order:
                    raise AssertionError('Scaling does not run child-first as expected')
                for node,values in zip(nodes,initial):
                    expected=[f32(v*ratio) if k%2 else v for k,v in enumerate(values)]
                    actual=C.string_at(address(node)+0x100,32)
                    if actual!=floats(expected):
                        raise AssertionError(('scaling',width,height,use_x,values,expected))
                    checked_nodes+=1;scalar_checks+=8
        roundtrip_examples.append({'viewport':[width,height],'y_ratio':native.ratios[1],
                                   'raw_width':390.0,'scaled_offset_width':f32(390*native.ratios[1])})
    # Original mutates values. Reapplying it is not a valid resize reset.
    node=C.create_string_buffer(0x120)
    values=[0.,0.,0.,0.,0.,390.,0.,768.]
    C.memmove(address(node)+0x100,floats(values),32)
    native.ratios=(1920/1024,1080/768)
    native.scale(address(ui),address(node),False)
    first=F4.from_buffer(node,0x110)[1]
    native.scale(address(ui),address(node),False)
    second=F4.from_buffer(node,0x110)[1]
    assert first==548.4375 and second==771.240234375
    return {'tree_calls':calls,'nodes_bit_exact':checked_nodes,'float_fields_bit_exact':scalar_checks,
            'child_first_order_checks':calls,'constants':constants,'examples':roundtrip_examples,
            'repeat_mutation':{'first_width':first,'second_width':second},
            'scope':'Three original functions unchanged; settings query and CEGUI accessors stubbed. No CEGUI final rectangles, rounding, autoscale, rendering, events, or resize lifecycle claimed.'}


def main():
    if not __debug__:
        raise RuntimeError('Run without -O: assertions are part of this verification')
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--elf',type=Path,required=True)
    ap.add_argument('--output',type=Path,required=True)
    args=ap.parse_args()
    elf=Original(args.elf)
    native=MappedFunctions(elf)
    try:
        report={'elf_sha256':elf.sha256,'functions':{k:{'symbol':n,'address':hex(a),'size':s} for k,(n,a,s) in FUNCTIONS.items()},
                'pause':pause_probes(native),'click':click_probes(native,elf),'scaling':scaling_probes(native,elf),
                'not_a_full_game_or_pixel_parity_test':True}
    finally:
        native.close()
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({k:report[k] for k in ('pause','click','scaling')},ensure_ascii=False,indent=2))

if __name__=='__main__':
    main()
