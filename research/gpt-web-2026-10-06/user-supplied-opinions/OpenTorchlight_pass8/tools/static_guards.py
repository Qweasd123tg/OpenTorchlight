#!/usr/bin/env python3
"""Pair guard variables with local statics using full demangled identities.
Duplicate identities are explicitly blocked: original mangled symbols/relocations
are needed to distinguish multiple locals which have the same printed name.
"""
from __future__ import annotations
import argparse,json
from collections import defaultdict
from pathlib import Path
from archive import symbols

def pair(records:list[dict])->dict:
    by=defaultdict(list);guards=defaultdict(list)
    prefix='guard variable for '
    for r in records:
        if r['name'].startswith(prefix):guards[r['name'][len(prefix):]].append(r)
        else:by[r['name']].append(r)
    out=[]
    for name,gs in sorted(guards.items()):
        objects=by.get(name,[])
        out.append({'identity':name,'guards':gs,'objects':objects,
                    'status':'UNIQUE_SYMBOL_PAIR_TYPE_AND_CFG_REQUIRED' if len(gs)==len(objects)==1 else 'BLOCKED_AMBIGUOUS_OR_MISSING'})
    return {'guard_symbols':sum(len(x) for x in guards.values()),'identities':len(out),
            'unique_pairs':sum(r['status'].startswith('UNIQUE') for r in out),'records':out,
            'scope':'symbol identity only; no inferred initializer, type, lifetime or source generation'}
if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('root',type=Path);p.add_argument('out',type=Path);a=p.parse_args()
    d=pair(symbols(a.root));a.out.write_text(json.dumps(d,ensure_ascii=False,indent=2))
    print(json.dumps({k:v for k,v in d.items() if k!='records'},ensure_ascii=False))
