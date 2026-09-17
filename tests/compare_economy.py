#!/usr/bin/env python3
"""Execute unchanged bounded buyPrice/sellPrice, with two explicit ABI stubs.

getPlayer returns the supplied fake level; getEffectValue reads its stored barter.
No economy, inventory generation or merchant UI is executed by this oracle.
"""
import argparse,ctypes as c,platform,random,struct,subprocess,sys
from pathlib import Path
from compare_ai_cooldown import Executable,bits,f32
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from original import Original

def main():
 p=argparse.ArgumentParser();p.add_argument('--original',type=Path,required=True);p.add_argument('--probe',type=Path,required=True);a=p.parse_args()
 if platform.machine() not in ('x86_64','AMD64'):return 77
 o=Original(a.original);low,high=0x813000,0xfa5000;code=bytearray(high-low)
 for addr,size in ((0x86fb40,0xd9),(0x86fc20,0xea),(0xfa47f8,4),(0xfa483c,4)):
  code[addr-low:addr-low+size]=o.read(addr,size)
 for addr,stub in ((0x936550,bytes.fromhex('48 89 f8 c3')),(0x8137e0,bytes.fromhex('f3 0f 10 07 c3'))):
  code[addr-low:addr-low+len(stub)]=stub
 memory=Executable(bytes(code))
 try:
  buy=c.CFUNCTYPE(c.c_int32,c.c_void_p)(memory.address+0x86fc20-low);sell=c.CFUNCTYPE(c.c_int32,c.c_void_p)(memory.address+0x86fb40-low)
  equipment=c.create_string_buffer(0x400);manager=c.create_string_buffer(0x40);player=c.create_string_buffer(0x40)
  struct.pack_into('<Q',equipment,0x68,c.addressof(manager));struct.pack_into('<Q',manager,0x18,c.addressof(player))
  cases=[]
  for n in (-2,0,1,2,20):
   for price in (0,1,3,99,10000):
    for identified in (0,1):
     for barter in (0.,.001,33.3333,99.999,100.,125.):cases.append((price,price,price+1,price+2,n,identified,f32(barter)))
  rng=random.Random(0x86fc20)
  for _ in range(10000):cases.append((rng.randrange(100000),rng.randrange(100000),rng.randrange(100000),rng.randrange(100000),rng.randrange(-3,21),rng.randrange(2),f32(rng.uniform(0,150))))
  inputs=[];expected=[]
  for b,s,ub,us,n,identified,barter in cases:
   struct.pack_into('<i',equipment,0x238,n);struct.pack_into('<iiii',equipment,0x264,b,s,ub,us);equipment[0x348]=identified;struct.pack_into('<f',player,0,barter)
   for op,fn in (('b',buy),('s',sell)):
    inputs.append(f'{op} {b} {s} {ub} {us} {n} {identified} {bits(barter)}\n');expected.append(fn(c.addressof(equipment)))
  result=subprocess.run([str(a.probe)],input=''.join(inputs),text=True,capture_output=True,check=True,timeout=30)
  actual=list(map(int,result.stdout.split()))
  if actual!=expected:
   i=next((i for i,(v,w) in enumerate(zip(actual,expected)) if v!=w),None);raise RuntimeError(f'price mismatch {i}: {inputs[i] if i is not None else len(actual)} expected={expected[i] if i is not None else len(expected)} got={actual[i] if i is not None else "length"}')
  print(f'PASS buy/sell native comparisons={len(expected)} cases={len(cases)}')
 finally:memory.close()
 return 0
if __name__=='__main__':raise SystemExit(main())
