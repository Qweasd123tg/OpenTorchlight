#!/usr/bin/env python3
"""Index CDataGroup reads by the exact local string object, preserving defaults.
All associations from text are candidates; no claim of CFG/lifetime/alias proof.
"""
from __future__ import annotations
import argparse,json,re
from collections import Counter
from pathlib import Path
from archive import functions,remove_comments,close_paren,split_args,mask_literals

def local_var(expr):
    # Only a final local identifier, after optional simple casts/parentheses.
    m=re.search(r'\b(local_[\da-fA-F]+)\s*\)*\s*$',expr)
    return m[1] if m else None

def calls(text,name):
    for m in re.finditer(re.escape(name)+r'\s*\(',mask_literals(text)):
        p=text.find('(',m.start())
        try: end=close_paren(text,p)
        except ValueError: continue
        yield m.start(),end+1,split_args(text[p+1:end])

def extract(text):
    text=remove_comments(text); ctors=[]
    for st,en,args in calls(text,'std::wstring::wstring'):
        if len(args)<2: continue
        var=local_var(args[0])
        if var and re.fullmatch(r'L"(?:\\.|[^"\\])*"',args[1],re.S):
            ctors.append((st,en,var,args[1]))
    rows=[]
    for st,en,args in calls(text,'CDataGroup::GetDataValue'):
        if len(args)!=3: continue
        var=local_var(args[1]); candidates=[c for c in ctors if c[1]<st and c[2]==var] if var else []
        rec={'status':'CANDIDATE_ONLY','line_relative':text.count('\n',0,st)+1,
             'input_group':args[0],'key_expression':args[1],'default_expression':args[2]}
        if candidates:
            ctor=max(candidates,key=lambda c:c[0]);rec['key_literal']=ctor[3]
            rec['key_construction_line_relative']=text.count('\n',0,ctor[0])+1
            # Preserve repeated key construction and do not claim a reaching definition across branches.
            rec['association']='latest preceding construction of the same local identifier; CFG unverified'
            rec['earlier_constructions_same_local']=len(candidates)-1
            # Restricted copy-back shape, for discovery only.
            left=text[text.rfind(';',0,st)+1:st]
            result=re.search(r'\b(\w+)\s*=\s*(?:\(\w+\))?\s*$',left)
            if result:
                r=result[1]
                dst=re.match(r'\s*;\s*this\[(0x[\da-fA-F]+|\d+)\]\s*=\s*'+re.escape(r)+r'\s*;',text[en:])
                if dst:
                    rec['copyback_field_offset_literal']=dst[1];rec['result_local']=r
                    before=text[max(0,ctor[0]-300):ctor[0]]
                    origins=list(re.finditer(r'\b'+re.escape(r)+r'\s*=\s*this\[(0x[\da-fA-F]+|\d+)\]\s*;',before))
                    if origins:
                        origin=origins[-1][1];rec['possible_default_field_offset_literal']=origin
                        if origin==dst[1] and re.fullmatch(r'\(bool\)\s*'+re.escape(r),args[2]):
                            rec['pattern']='bool_read_with_existing_field_default'
                            rec['candidate_expression']=f'field_{int(origin,0):x} = {args[0]}->GetDataValue({ctor[3]}, field_{int(origin,0):x});'
        rows.append(rec)
    return rows

def run(root):
    rows=[]
    for f in functions(root):
        for r in extract(f.text):
            r.update(function_address=hex(f.address),function=f.name,file=f.path,approximate_line=f.line+r.pop('line_relative'))
            rows.append(r)
    resolved=[r for r in rows if 'key_literal'in r]
    return {'scope':'textual associations, not accepted C++ and not current remaining work',
            'getdatavalue_calls':len(rows),'literal_key_candidates':len(resolved),
            'distinct_literal_keys':len({r['key_literal'] for r in resolved}),
            'functions_with_literal_candidates':len({r['function_address'] for r in resolved}),
            'bool_copyback_candidates':sum(r.get('pattern')=='bool_read_with_existing_field_default' for r in rows),
            'by_function':dict(Counter(r['function'] for r in resolved)),
            'reads':rows}

if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('root',type=Path);p.add_argument('out',type=Path);a=p.parse_args()
    d=run(a.root);a.out.write_text(json.dumps(d,indent=2,ensure_ascii=False)+'\n')
    print(json.dumps({k:v for k,v in d.items()if k not in ('reads','by_function')},indent=2))
