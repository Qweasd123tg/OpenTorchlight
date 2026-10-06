#!/usr/bin/env python3
"""Re-emit typed logical table values as C++98. Not a live process memory dumper.
Unknown cells, invalid code points, pointers and unsupported types are rejected.
The caller must separately check initialization side effects and linkage.
"""
from __future__ import annotations
import argparse,json,math,re
from pathlib import Path

def wide_literal(units):
    if not isinstance(units,list):raise ValueError('expected a list of UTF-32 code points')
    out=[]
    for u in units:
        if not isinstance(u,int) or isinstance(u,bool) or not 0<=u<=0x10ffff or 0xd800<=u<=0xdfff: raise ValueError('unsupported wchar code point')
        if u==34:out.append('\\"')
        elif u==92:out.append('\\\\')
        elif 32<=u<127:out.append(chr(u))
        elif u<256:out.append('\\%03o'%u)
        elif u<=0xffff:out.append('\\u%04x'%u)
        else:out.append('\\U%08x'%u)
    return 'std::wstring(L"'+''.join(out)+'", '+str(len(units))+')'

def validate_shape(shape):
    if not isinstance(shape,list) or not shape or len(shape)>3 or any(type(x)is not int or x<=0 for x in shape):
        raise ValueError('invalid shape')
    n=math.prod(shape)
    if n>100000:raise ValueError('table exceeds prototype limit')
    return n

def initializer(vals,shape):
    if len(shape)==1:return '{\n'+',\n'.join('    '+v for v in vals)+'\n}'
    step=math.prod(shape[1:]);return '{\n'+',\n'.join(initializer(vals[i:i+step],shape[1:]) for i in range(0,len(vals),step))+'\n}'

def emit(snapshot):
    if snapshot.get('format')!='typed-logical-tables-v1':raise ValueError('unsupported snapshot format')
    lines=['// Generated logical values only. Initializer order and behavior require a separate check.', '#include <string>'];seen=set()
    for tab in snapshot['tables']:
        name=tab['name']
        if not re.fullmatch(r'[A-Za-z_]\w*',name) or name in seen:raise ValueError('invalid or duplicate name')
        seen.add(name);shape=tab['shape'];n=validate_shape(shape);data=tab['values']
        if len(data)!=n or any(v is None for v in data):raise ValueError('incomplete table')
        typ=tab['type']
        if typ=='wstring': vals=[wide_literal(x)for x in data];ctype='std::wstring'
        elif typ=='int32':
            if any(type(x)is not int or not -2**31<=x<2**31 for x in data):raise ValueError('int32 out of range')
            vals=[str(x)if x!=-2**31 else '(-2147483647 - 1)' for x in data];ctype='int'
        else:raise ValueError('unsupported type; no guessing')
        linkage=tab.get('linkage','external')
        if linkage not in ('external','internal'):raise ValueError('unsupported linkage')
        prefix='static 'if linkage=='internal'else ''
        lines.append(prefix+ctype+' '+name+''.join('['+str(x)+']'for x in shape)+' = '+initializer(vals,shape)+';')
    return '\n\n'.join(lines)+'\n'

if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('snapshot',type=Path);p.add_argument('out',type=Path);a=p.parse_args()
    a.out.write_text(emit(json.loads(a.snapshot.read_text())))
