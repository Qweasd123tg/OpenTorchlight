#!/usr/bin/env python3
"""Static byte-provenance recovery for a small, fail-closed x86 MOV/LEA/REP subset.
Produces ordinary C++ memcpy/memset; never emits an instruction interpreter.
Preconditions: valid ordinary object storage, no concurrent/volatile observations,
DF=0 at ABI entry, fixed bounded ranges, and no exceptional memory accesses.
"""
from __future__ import annotations
import argparse,json,re
from dataclasses import dataclass
from pathlib import Path
from native_capsule import read_rows
@dataclass(frozen=True)
class Ptr:
    offset:int
REG={}
for root,names in {'rax':['rax','eax','ax','al'],'rcx':['rcx','ecx','cx','cl'],
                  'rdx':['rdx','edx','dx','dl'],'rsi':['rsi','esi','si','sil'],
                  'rdi':['rdi','edi','di','dil']}.items():
    for name,width in zip(names,(8,4,2,1)):REG['%'+name]=(root,width)

def split_operands(text:str)->list[str]:
    out=[];start=0;depth=0
    for i,c in enumerate(text):
        if c=='(':depth+=1
        elif c==')':depth-=1
        elif c==',' and not depth:out.append(text[start:i].strip());start=i+1
    return out+[text[start:].strip()]

def integer_bytes(n:int,width:int)->tuple:
    return tuple((n>>(8*i))&255 for i in range(width))

class Analysis:
    def __init__(self):
        self.reg={'rdi':Ptr(0)};self.mem={};self.writes=[];self.reads=[]
    def readreg(self,token:str):
        name,n=REG[token]
        v=self.reg.get(name,tuple(('unknown',name,i) for i in range(8)))
        if isinstance(v,Ptr):
            if n!=8:raise ValueError('partial pointer read')
            return v
        return v[:n]
    def writereg(self,token:str,value):
        name,n=REG[token]
        if isinstance(value,Ptr):
            if n!=8:raise ValueError('partial pointer assignment')
            self.reg[name]=value;return
        if len(value)!=n:raise ValueError('width mismatch')
        old=self.reg.get(name,tuple(('unknown',name,i) for i in range(8)))
        if isinstance(old,Ptr):old=tuple(('unknown',name,i) for i in range(8))
        self.reg[name]=tuple(value)+(integer_bytes(0,4) if n==4 else old[n:])
    def number(self,token:str)->int:
        b=self.readreg(token)
        if isinstance(b,Ptr) or not all(isinstance(x,int) for x in b):raise ValueError('nonconstant count')
        return sum(x<<(i*8) for i,x in enumerate(b))
    def address(self,text:str)->int:
        m=re.fullmatch(r'(-?(?:0x[\da-f]+|\d+))?\((%\w+)\)',text)
        if not m:raise ValueError('unsupported address '+text)
        p=self.readreg(m[2])
        if not isinstance(p,Ptr):raise ValueError('unknown address')
        a=p.offset+(int(m[1],0) if m[1] else 0)
        if not 0<=a<65536:raise ValueError('out of analysis bounds')
        return a
    def load(self,a:int,n:int)->tuple:
        self.reads.append((a,n))
        return tuple(self.mem.get(i,('input',i)) for i in range(a,a+n))
    def store(self,a:int,v:tuple):
        for i,x in enumerate(v):self.mem[a+i]=x;self.writes.append((a+i,x))
    def execute(self,text:str):
        text=' '.join(text.split())
        if text=='ret':return
        if text.startswith('rep '):
            count=self.number('%rcx')
            if count>4096:raise ValueError('unbounded REP')
            dst=self.readreg('%rdi');src=self.readreg('%rsi')
            if not isinstance(dst,Ptr):raise ValueError('unknown destination')
            if text=='rep movsq (%rsi),(%rdi)':
                if not isinstance(src,Ptr):raise ValueError('unknown source')
                for i in range(count):self.store(dst.offset+8*i,self.load(src.offset+8*i,8))
                self.writereg('%rsi',Ptr(src.offset+8*count))
            elif text=='rep stos %rax,(%rdi)':
                value=self.readreg('%rax')
                if isinstance(value,Ptr):raise ValueError('pointer fill')
                for i in range(count):self.store(dst.offset+8*i,value)
            else:raise ValueError('unsupported REP')
            self.writereg('%rdi',Ptr(dst.offset+8*count));self.writereg('%rcx',integer_bytes(0,8));return
        op,rest=text.split(' ',1);parts=split_operands(rest)
        if len(parts)!=2:raise ValueError('unsupported operand count')
        src,dst=parts
        if op=='lea':self.writereg(dst,Ptr(self.address(src)));return
        if op not in ('mov','movb','movw','movl','movq','movzbl','movzwl'):raise ValueError('unsupported '+op)
        zero_width={'movzbl':1,'movzwl':2}.get(op)
        n=zero_width or ({'movb':1,'movw':2,'movl':4,'movq':8}.get(op))
        if n is None:
            n=REG[dst][1] if dst in REG else REG[src][1]
        if src.startswith('$'):value=integer_bytes(int(src[1:],0),n)
        elif src in REG:value=self.readreg(src)
        else:value=self.load(self.address(src),n)
        if zero_width:value=tuple(value)+integer_bytes(0,REG[dst][1]-zero_width)
        if dst in REG:self.writereg(dst,value)
        else:
            if isinstance(value,Ptr):raise ValueError('pointer escape')
            self.store(self.address(dst),value)
    def recipes(self)->list[dict]:
        # Replay grouped stores. Check that any memcpy reads the current source value,
        # not a stale value which was loaded before an intervening write.
        groups=[];state={};i=0
        while i<len(self.writes):
            dst,v=self.writes[i];input_value=isinstance(v,tuple) and v[0]=='input'
            if not input_value and v!=0:raise ValueError('non-copy/nonzero write')
            source=v[1] if input_value else None;j=i+1
            while j<len(self.writes):
                d,x=self.writes[j];k=j-i
                if d!=dst+k or x!=(('input',source+k) if input_value else 0):break
                j+=1
            n=j-i
            if input_value:
                if max(dst,source)<min(dst+n,source+n):raise ValueError('overlap: memcpy forbidden')
                for k in range(n):
                    if state.get(source+k,('input',source+k))!=('input',source+k):
                        raise ValueError('stale source: cannot emit memcpy')
                groups.append({'operation':'memcpy','destination':dst,'source':source,'bytes':n})
            else:groups.append({'operation':'memset','destination':dst,'value':0,'bytes':n})
            for k in range(n):state[dst+k]=self.writes[i+k][1]
            i=j
        return groups

def recover(rows:list[dict])->dict:
    a=Analysis()
    for row in rows:a.execute(row['text'])
    recipes=a.recipes(); emitted={}
    for r in recipes:
        d,n=r['destination'],r['bytes']
        if r['operation']=='memcpy':
            values=[emitted.get(r['source']+i,('input',r['source']+i)) for i in range(n)]
        else:values=[0]*n
        for i,v in enumerate(values):emitted[d+i]=v
    if emitted!=a.mem:raise ValueError('emitted transfer map differs from instruction model')
    return {'instructions':len(rows),'byte_stores':len(a.writes),'recipes':recipes,
            'symbolic_final_byte_maps_equal':True,
            'preconditions':['valid ordinary object memory','no concurrent or volatile observations','DF=0','no memory faults'],
            'scope':'static narrow instruction subset; no unknown operations allowed'}
def emit(recipes:list[dict])->str:
    lines=['// Automatically inferred from archival CKeyManager::capture instruction listing.',
           '// Test candidate only. Offsets are not claims about original field names.',
           '#include <cstring>','extern "C" void generated_capture(unsigned char* object) {']
    for r in recipes:
        dst='object + '+hex(r['destination'])
        if r['operation']=='memcpy':lines.append('    std::memcpy(%s, object + %s, %d);'%(dst,hex(r['source']),r['bytes']))
        else:lines.append('    std::memset(%s, 0, %d);'%(dst,r['bytes']))
    return '\n'.join(lines+['}',''])
if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('root',type=Path);p.add_argument('out',type=Path);a=p.parse_args();a.out.mkdir(parents=True,exist_ok=True)
    rows=read_rows(a.root/'research/disassembly/91a980.asm',0x91a980,0x119);result=recover(rows)
    (a.out/'memory-recovery.json').write_text(json.dumps(result,indent=2))
    (a.out/'generated_capture.cpp').write_text(emit(result['recipes']))
    print(json.dumps(result,indent=2))
