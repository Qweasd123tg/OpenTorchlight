#!/usr/bin/env python3
"""Read raw ADM records, not a simulation or a substitute for BASEFILE inheritance."""
import argparse,collections,json,struct,zipfile
from pathlib import Path

def adm(data):
    pos=0
    def take(fmt):
        nonlocal pos
        value=struct.unpack_from('<'+fmt,data,pos)[0];pos+=struct.calcsize('<'+fmt);return value
    if take('I')!=1:raise ValueError('ADM version')
    names={}
    for _ in range(take('I')):
        key=take('I');length=take('I')*2
        if pos+length>len(data):raise ValueError('ADM string bounds')
        names[key]=data[pos:pos+length].decode('utf-16le');pos+=length
    def group(depth=0):
        if depth>256:raise ValueError('depth')
        name=names[take('I')];properties={}
        for _ in range(take('I')):
            key=names[take('I')];kind=take('I')
            if kind in (5,8,9):value=names[take('I')]
            else:value=take({1:'i',2:'f',3:'d',4:'I',6:'I',7:'q'}[kind])
            if kind==6:value=bool(value)
            properties.setdefault(key,value)
        children=[group(depth+1) for _ in range(take('I'))]
        return {'group':name,'properties':properties,'children':children}
    result=group()
    if pos!=len(data):raise ValueError('trailing ADM')
    return result

def main():
    p=argparse.ArgumentParser();p.add_argument('--pak',type=Path,required=True);p.add_argument('--output',type=Path,required=True);args=p.parse_args()
    types=collections.Counter();examples=collections.defaultdict(list);requirements=[];units=[];errors=[];effects=[]
    with zipfile.ZipFile(args.pak) as z:
        for name in z.namelist():
            norm=name.replace('\\','/').lower()
            if not norm.endswith('.adm') or not norm.startswith(('media/units/','media/affixes/')):continue
            try:g=adm(z.read(name))
            except Exception as e:errors.append([name,str(e)]);continue
            if norm.startswith('media/units/'):
                units.append(name)
                req={k:v for k,v in g['properties'].items() if 'REQUIRED' in k or 'REQUIREMENT' in k}
                if req:requirements.append({'path':name,'name':g['properties'].get('NAME'),'requirements':req})
            def walk(group):
                if group['group'].upper()=='EFFECT':
                    props=group['properties'];kind=props.get('TYPE','');types[kind]+=1
                    if len(examples[kind])<6:examples[kind].append({'path':name,'properties':props})
                    effects.append({'path':name,'properties':props})
                for c in group['children']:walk(c)
            walk(g)
    output={'scope':'Raw local ADM groups; counts are not active instances and do not resolve BASEFILE inheritance.','unit_files':len(units),'effect_types':dict(types),'examples':dict(examples),'requirements':requirements,'effects':effects,'errors':errors}
    args.output.write_text(json.dumps(output,ensure_ascii=False,indent=2)+'\n')
    print('unit_files',len(units),'effect_records',len(effects),'requirement_records',len(requirements),'errors',len(errors))
    for kind in ['ARMOR BONUS','ARMOR PERCENT','DEFENSE','DEFENSE BONUS','SPEED','MOVEMENT SPEED']:
        print(kind,types[kind],examples[kind][:2])
if __name__=='__main__':main()
