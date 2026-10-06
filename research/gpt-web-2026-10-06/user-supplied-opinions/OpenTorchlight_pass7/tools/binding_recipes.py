#!/usr/bin/env python3
"""Extract complete CEGUI adapter construction recipes. Candidates only; no game edits."""
from __future__ import annotations
import argparse,json,re
from collections import Counter
from pathlib import Path
from archive import functions,symbols,remove_comments,mask_literals

def decode_pmf(value: str, adjustment: str, ptr_bytes=8):
    try: adj=int(adjustment,0)
    except ValueError: return {'kind':'unknown','raw':value,'adjustment':adjustment}
    value=value.strip()
    try: raw=int(value,0)
    except ValueError:
        if re.fullmatch(r'(?:\w+::)*\w+',value): return {'kind':'symbol','symbol':value,'this_adjustment':adj}
        return {'kind':'unknown','raw':value,'this_adjustment':adj}
    if raw==0: return {'kind':'null','this_adjustment':adj}
    if raw&1:
        if (raw-1)%ptr_bytes: return {'kind':'invalid_virtual_offset','raw':raw,'this_adjustment':adj}
        return {'kind':'virtual','vtable_byte_offset':raw-1,'slot':(raw-1)//ptr_bytes,'this_adjustment':adj}
    return {'kind':'address','address':hex(raw),'this_adjustment':adj}

def extract(text,vtable_types):
    text=mask_literals(remove_comments(text)); rows=[]
    alloc=re.compile(r'(?P<var>\w+(?:\[0\])?)\s*=\s*operator_new\(0x20\)\s*;')
    for m in alloc.finditer(text):
        var=m['var']; pos=m.end(); assigns={}; spans=[]; ok=True
        for _ in range(4):
            a=re.match(r'\s*([^;{}]+?)\s*=\s*([^;{}]+?)\s*;',text[pos:])
            if not a: ok=False; break
            lhs=re.sub(r'\s+','',a[1]); val=a[2].strip()
            key=0 if lhs=='*'+var else next((i for i in (1,2,3) if lhs==f'{var}[{i}]'),None)
            if key is None or key in assigns: ok=False; break
            assigns[key]=val; spans.append((pos,pos+a.end())); pos+=a.end()
        if not ok or set(assigns)!={0,1,2,3}: continue
        vp=re.fullmatch(r'&PTR__MemberFunctionSlot_([0-9a-fA-F]+)',assigns[0])
        if not vp: continue
        vptr=int(vp[1],16); typ=vtable_types.get(vptr)
        pmf=decode_pmf(assigns[1],assigns[2])
        record={'status':'CANDIDATE_ONLY','text_offset':m.start(),'line_relative':text.count('\n',0,m.start())+1,
                'adapter_type':typ,'vptr':hex(vptr),'allocation_size':32,'slot_storage':var,
                'receiver':assigns[3],'member_pointer':pmf,'assignments':assigns}
        # A typed expression is offered only for a direct named callback, unchanged this, and zero adjustment.
        if typ and pmf['kind']=='symbol' and pmf['this_adjustment']==0 and assigns[3]=='this':
            name=pmf['symbol']; name=name if '::' in name else typ+'::'+name
            record['construction_candidate']=f'CEGUI::SubscriberSlot(&{name}, this)'
        tail=text[pos:pos+800]
        event=re.search(r'CEGUI::\w+::Event\w+',tail)
        # This is navigation context only: not a proven association or replacement of the call.
        if event: record['nearby_event_candidate']=event[0]
        rows.append(record)
    return rows

def run(root):
    syms=symbols(root); vt={}
    exact_symbols={s["name"]:s for s in syms}
    for s in syms:
        m=re.fullmatch(r'vtable for CEGUI::MemberFunctionSlot<([^>]+)>',s['name'])
        if m: vt[s['address']+16]=m[1]
    rows=[]; total_markers=0; nfunc=0
    for f in functions(root):
        nfunc+=1; total_markers+=f.text.count('PTR__MemberFunctionSlot_')
        for r in extract(f.text,vt):
            if 'construction_candidate' in r:
                name=r['member_pointer']['symbol']
                name=name if '::' in name else r['adapter_type']+'::'+name
                signature=name+'(CEGUI::EventArgs const&)'
                match=exact_symbols.get(signature)
                if match:
                    r['callback_symbol_evidence']={'signature':signature,'address':hex(match['address']),'symbol_line':match['line']}
                else:
                    r.pop('construction_candidate')
                    r['blocked_reason']='No exact callback parameter signature in original-symbols.txt'
            r.update(function_address=hex(f.address),function=f.name,file=f.path,
                     approximate_line=f.line+r.pop('line_relative'))
            rows.append(r)
    return {'scope':'archived pseudocode; not binary equivalence or current work status',
            'functions_scanned':nfunc,'vtable_specializations':len(vt),'marker_occurrences':total_markers,
            'complete_recipes':len(rows),'functions_with_recipes':len(set(r['function_address'] for r in rows)),
            'kinds':dict(Counter(r['member_pointer']['kind'] for r in rows)),
            'typed_construction_candidates':sum('construction_candidate'in r for r in rows),
            'exact_callback_signatures_confirmed':sum('callback_symbol_evidence'in r for r in rows),
            'by_function':dict(Counter(r['function'] for r in rows)),'recipes':rows}

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('root',type=Path);p.add_argument('out',type=Path)
    a=p.parse_args(); data=run(a.root);a.out.parent.mkdir(parents=True,exist_ok=True)
    a.out.write_text(json.dumps(data,indent=2,ensure_ascii=False)+'\n')
    print(json.dumps({k:v for k,v in data.items() if k not in ('recipes','by_function')},indent=2))
if __name__=='__main__':main()
