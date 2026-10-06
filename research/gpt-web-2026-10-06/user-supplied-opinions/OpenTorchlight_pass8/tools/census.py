#!/usr/bin/env python3
"""Read-only lexical candidate inventory. No claim of semantic completeness."""
from __future__ import annotations
import argparse,json,re
from collections import Counter
from pathlib import Path
from archive import functions,symbols,remove_comments,mask_literals,close_paren,split_args

def analyse(root:Path)->dict:
    fs=list(functions(root)); syms={s['address']:s for s in symbols(root) if s['kind'] in 'TtWw'}
    cats={'register_fragments':[], 'aggregate_signature':[], 'dynamic_cast':[], 'local_static':[],
          'allocation':[], 'constructor':[], 'floating_point':[]}
    casts=[]; squares=[]
    # This matcher deliberately preserves order, multiplicity and expression boundaries.
    v=r'(?:[A-Za-z_]\w*)'
    pattern=re.compile(rf'(?<![\w.])(?P<a>{v})\s*\*\s*(?P=a)\s*\+\s*(?P<b>{v})\s*\*\s*(?P=b)\s*\+\s*(?P<c>{v})\s*\*\s*(?P=c)(?![\w.])')
    for f in fs:
        text=remove_comments(f.text); code=mask_literals(text)
        sym=syms.get(f.address,{}).get('name',f.name)
        rec=dict(address=hex(f.address),name=sym,path=f.path,line=f.line,size=syms.get(f.address,{}).get('size'))
        if re.search(r'\b(?:in_XMM\w*|extraout_XMM\w*|CONCAT(?:44|88))\b',code):cats['register_fragments'].append(rec)
        if any(t in sym for t in ['Ogre::Vector3','Ogre::Quaternion','Ogre::Matrix3','Ogre::Matrix4']): cats['aggregate_signature'].append(rec)
        if '__dynamic_cast(' in code:cats['dynamic_cast'].append(rec)
        if '__cxa_guard_acquire' in code:cats['local_static'].append(rec)
        if re.search(r'\boperator_new\s*\(|\ballocBytes\s*\(',code):cats['allocation'].append(rec)
        head=f.name.split('::')
        if len(head)>1 and head[-1]==head[-2]:cats['constructor'].append(rec)
        if re.search(r'\bfloat\b|\bdouble\b', code):cats['floating_point'].append(rec)
        for m in re.finditer(r'\b__dynamic_cast\s*\(',code):
            try: end=close_paren(text,m.end()-1); args=split_args(text[m.end():end])
            except ValueError:continue
            item={**rec,'call_line':f.line+f.text.count('\n',0,m.start()),'arguments':args,'status':'UNRESOLVED'}
            if len(args)==4:
                types=[]
                for arg in args[1:3]:
                    mt=re.fullmatch(r'&((?:\w+::)*)typeinfo',arg.strip())
                    typ=mt[1].rstrip(':') if mt else None
                    if typ=='':typ=f.name.rsplit('::',1)[0]
                    types.append(typ)
                if all(types):
                    item.update(source_type=types[0],destination_type=types[1],status='TYPE_ANCHOR_NOT_VERIFIED')
            casts.append(item)
        declared=set(re.findall(r'\bfloat\s+([A-Za-z_]\w*)\s*;',code))
        for m in pattern.finditer(code):
            vals=[m[g] for g in ['a','b','c']]
            if not all(x in declared for x in vals):continue
            squares.append({**rec,'expression_line':f.line+f.text.count('\n',0,m.start()),
                            'expression':text[m.start():m.end()],'components':vals,
                            'candidate':f'Ogre::Vector3({", ".join(vals)}).squaredLength()',
                            'status':'LEXICAL_CANDIDATE_NEEDS_VALUE_FLOW_AND_FP_CHECK'})
    return {'scope':'unique function addresses in research/decompiled-core; historical, not completion status',
            'functions':len(fs),'categories':{k:{'functions':len(v),'bytes':sum(r['size'] or 0 for r in v),'records':v} for k,v in cats.items()},
            'casts':casts,'squared_length':squares,
            'summary':{'casts':len(casts),'resolved_type_anchors':sum(c['status']=='TYPE_ANCHOR_NOT_VERIFIED' for c in casts),
                       'squared_length_sites':len(squares),'squared_length_functions':len(set(x['address'] for x in squares))}}
if __name__=='__main__':
    a=argparse.ArgumentParser();a.add_argument('root',type=Path);a.add_argument('out',type=Path);p=a.parse_args()
    d=analyse(p.root);p.out.write_text(json.dumps(d,ensure_ascii=False,indent=2));print(json.dumps({'functions':d['functions'],'categories':{k:{q:v[q] for q in ['functions','bytes']} for k,v in d['categories'].items()},'summary':d['summary']},ensure_ascii=False,indent=2))
