#!/usr/bin/env python3
"""Execute unchanged menuItemClick/price/gold/stat bodies on explicit raw state.

External inventory, type, factory, input and UI dependencies are named fixture
adapters. This checks actual caller branch/order, not native object constructors,
inventory capacity, original UI input or a complete merchant implementation.
"""
import argparse
import ctypes as c
import hashlib
import json
from pathlib import Path
import platform
import struct
import sys

sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from original import Original
from automation_state import validate_output, write_json
from native_typed_reference import Memory


class MerchantTrace(Memory):
    def __init__(self,original):
        super().__init__()
        self.original=original;self.bodies=[];self.trace=[];self.errors=[];self.owners=[]
        try:
            for entry in (0xA8F780,0x86FB40,0x86FC20,0x811A70,0x8E41A0,0xECE340,0xECE430):
                symbol=next(s for s in original.symbols if s.address==entry and s.size)
                body=original.read(entry,symbol.size);self.put(entry,body)
                self.bodies.append(dict(address=hex(entry),symbol=symbol.name,size=symbol.size,sha256=hashlib.sha256(body).hexdigest()))
            for entry,size in ((0xFA47F8,4),(0xFA483C,4),(0xFA480C,4),(0xFA47FC,4)):
                self.put(entry,original.read(entry,size))
            # Explicit null global pointer input; unchanged Linux incrementStat
            # is REP RET and never dereferences the returned singleton pointer.
            self.put(0x153A840,bytes(8))
            cf=c.CFUNCTYPE
            self.callback(0x7F62A0,cf(c.c_bool,c.c_size_t,c.c_int),self.isa)
            self.callback(0xF63260,cf(c.c_short,c.c_uint),lambda key:-32768)
            self.callback(0x91B340,cf(c.c_size_t,c.c_size_t,c.c_uint),lambda owner,slot:self.item_address if slot==20 else 0)
            self.callback(0x91B3F0,cf(c.c_int,c.c_size_t,c.c_size_t),lambda owner,item:20)
            self.callback(0x924810,cf(c.c_int,c.c_size_t,c.c_size_t),self.remove)
            self.callback(0x9251B0,cf(c.c_size_t,c.c_size_t,c.c_size_t,c.c_bool),self.pickup)
            self.callback(0x924BD0,cf(c.c_size_t,c.c_size_t,c.c_size_t,c.c_int,c.c_bool),self.rollback)
            self.callback(0xD78C50,cf(c.c_size_t,c.c_size_t,c.c_size_t,c.c_int,c.c_bool,c.c_bool),self.create)
            self.callback(0x936550,cf(c.c_size_t,c.c_size_t),lambda level:self.player_address)
            self.callback(0x8137E0,cf(c.c_float,c.c_size_t,c.c_int,c.c_int),self.effect)
            self.callback(0x8119E0,cf(None,c.c_size_t,c.c_int,c.c_int),lambda player,kind,value:self.trace.append(['journal',kind,value]))
            self.callback(0xA698A0,cf(None,c.c_size_t,c.c_int,c.c_size_t,c.c_float,c.c_float,c.c_bool),
                          lambda bank,kind,node,x,y,flag:self.trace.append(['sound',kind]))
            self.callback(0x86EB70,cf(None,c.c_size_t,c.c_size_t),lambda item,node:None)
            self.callback(0xA83D60,cf(None,c.c_size_t),lambda ui:self.trace.append(['cursor']))
            self.callback(0x555678,cf(c.c_size_t),lambda:1)
            self.callback(0x552838,cf(None,c.c_size_t,c.c_float,c.c_float),lambda system,x,y:None)
            self.callback(0x20000100,cf(c.c_bool,c.c_size_t),lambda menu:menu==self.merchant_menu_address)
            self.callback(0x20000200,cf(c.c_size_t,c.c_size_t),lambda menu:self.merchant_address)
            self.callback(0x20000300,cf(None,c.c_size_t),lambda menu:self.trace.append(['layout']))
            self.protect()
            self.click=cf(c.c_int,c.c_size_t,c.c_size_t,c.c_size_t,c.c_int,c.c_bool)(0xA8F780)
        except BaseException:self.close();raise

    def isa(self,unit,kind):
        return (unit==self.merchant_address and kind==0x29) or (unit==self.item_address and kind==0x67 and self.quest_item)

    def effect(self,player,kind,subtype):
        if kind!=0x53 or subtype!=7:self.errors.append(['unexpected_effect',kind,subtype])
        return 0.0

    def inventory_name(self,owner):
        if owner==self.player_inventory_address:return 'player'
        if owner==self.merchant_inventory_address:return 'merchant'
        self.errors.append(['unexpected_inventory',owner]);return 'unknown'

    def remove(self,owner,item):
        self.trace.append(['remove',self.inventory_name(owner)]);return 1

    def pickup(self,owner,item,flag):
        self.trace.append(['pickup',self.inventory_name(owner),item==self.created_address])
        return item if self.pickup_ok else 0

    def rollback(self,owner,item,slot,flag):
        self.trace.append(['rollback',self.inventory_name(owner),slot]);return item

    def create(self,manager,data,index,a,b):
        self.trace.append(['create',index,bool(a),bool(b)]);return self.created_address

    def buffer(self,size):
        value=c.create_string_buffer(size);self.owners.append(value);return value

    def execute(self,operation,count,infinite,gold,pickup_ok=True,quest=False):
        self.trace=[];self.errors=[];self.owners=[];self.pickup_ok=pickup_ok;self.quest_item=quest
        ui=self.buffer(0x1800);player=self.buffer(0x900);merchant=self.buffer(0x900)
        item=self.buffer(0x500);created=self.buffer(0x500);manager=self.buffer(0x40);level=self.buffer(0x40)
        self.player_address=c.addressof(player);self.merchant_address=c.addressof(merchant)
        self.item_address=c.addressof(item);self.created_address=c.addressof(created)
        player_inventory=self.buffer(0x100);merchant_inventory=self.buffer(0x100)
        self.player_inventory_address=c.addressof(player_inventory);self.merchant_inventory_address=c.addressof(merchant_inventory)
        struct.pack_into('<Q',player,0x490,self.player_inventory_address)
        struct.pack_into('<Q',merchant,0x490,self.merchant_inventory_address)
        struct.pack_into('<i',player,0x444,gold)
        struct.pack_into('<Q',manager,0x18,c.addressof(level));struct.pack_into('<Q',item,0x68,c.addressof(manager))
        struct.pack_into('<i',item,0x238,count);struct.pack_into('<iiii',item,0x264,51,7,23,3)
        item[0x348]=1;item[0x25F]=int(infinite)
        c.memmove(self.created_address,self.item_address,0x500)
        vtable=(c.c_size_t*10)();vtable[2]=0x20000200;vtable[4]=0x20000100;vtable[9]=0x20000300
        self.owners.append(vtable)
        menus={offset:self.buffer(0x4000) for offset in (0x4D8,0x4E8,0x4F0,0x4F8,0x500,0x508)}
        self.merchant_menu_address=c.addressof(menus[0x4F0])
        for offset,menu in menus.items():
            struct.pack_into('<Q',menu,0,c.addressof(vtable));struct.pack_into('<Q',ui,offset,c.addressof(menu))
        for offset in (0x4A0,0x4A8,0x4B0):struct.pack_into('<Q',ui,offset,c.addressof(self.buffer(0x40)))
        struct.pack_into('<Q',ui,0x38,self.player_address);struct.pack_into('<q',ui,0xB0,-1)
        owner=self.player_address if operation=='sell' else self.merchant_address
        menu=c.addressof(menus[0x4D8]) if operation=='sell' else self.merchant_menu_address
        self.click(c.addressof(ui),owner,menu,20,False)
        if self.errors:raise AssertionError(self.errors)
        return dict(operation=operation,count=count,infinite=infinite,initial_gold=gold,
                    pickup_ok=pickup_ok,quest=quest,gold=struct.unpack_from('<i',player,0x444)[0],trace=self.trace[:])


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--original',required=True,type=Path);parser.add_argument('--output',required=True,type=Path)
    args=parser.parse_args()
    if platform.system()!='Linux' or platform.machine()!='x86_64':return 77
    validate_output(Path(__file__).resolve().parents[1],args.output,[args.original])
    original=Original(args.original);native=MerchantTrace(original);results=[]
    try:
        for count in (1,2,20):
            for infinite in (False,True):
                sell=native.execute('sell',count,infinite,100000);results.append(sell)
                assert sell['gold']==100000+7*count
                assert ['remove','player'] in sell['trace'] and ['pickup','merchant',False] in sell['trace']
                assert sell['trace'].index(['journal',1,7*count])<sell['trace'].index(['remove','player'])
                buy=native.execute('buy',count,infinite,100000);results.append(buy)
                assert buy['gold']==100000-51*count
                cloned=count==1 and infinite
                assert any(x[0]=='create' for x in buy['trace'])==cloned
                assert (['remove','merchant'] in buy['trace'])!=cloned
                assert ['pickup','player',cloned] in buy['trace']
                denied=native.execute('buy',count,infinite,0);results.append(denied)
                assert denied['gold']==0 and not any(x[0] in ('remove','pickup','create') for x in denied['trace'])
        failed=native.execute('buy',20,True,100000,False);results.append(failed)
        assert failed['gold']==100000 and ['rollback','merchant',20] in failed['trace']
        blocked=native.execute('sell',1,True,100000,quest=True);results.append(blocked)
        assert blocked['gold']==100000 and not any(x[0] in ('journal','remove','pickup') for x in blocked['trace'])
        capped=native.execute('sell',20,True,2147483647);results.append(capped)
        assert capped['gold']==2147483647
        write_json(args.output,dict(schema=1,kind='original-merchant-transfer-trace',status='PASS',
            original_elf_sha256=original.sha256,bodies=native.bodies,cases=results,
            scope=__doc__,game_executed=False,original_status_promotions=0))
        print(f'PASS original merchant caller traces={len(results)}; original bodies with explicit dependency adapters')
        return 0
    finally:native.close()


if __name__=='__main__':raise SystemExit(main())
