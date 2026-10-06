#!/usr/bin/env python3
"""Suggest cross-class field-offset correspondences from matching token families.
Only same method+parameter signatures are compared. Only literal this+K/this[K]
uses are extracted. A correspondence is not a verified type/layout assertion.
"""
from __future__ import annotations
import argparse,collections,itertools,json,re
from pathlib import Path
import family_deltas as fd

def gather_bodies(root):
    out={}
    for p in sorted((root/'research/decompiled-core').glob('*.c')):
        text=p.read_text(errors='replace');ms=list(fd.HEADER.finditer(text))
        for k,m in enumerate(ms):
            a=int(m[1],16);raw=text[m.end():ms[k+1].start() if k+1<len(ms) else len(text)]
            ts,_=fd.body_tokens(raw)
            if ts and (a not in out or len(ts)>len(out[a])):out[a]=ts
    return out

def direct_this_offsets(ts):
    out={}
    for i,(kind,t) in enumerate(ts):
        if kind!='number' or i<2:continue
        if [v for _,v in ts[i-2:i]] not in [['this','+'],['this','[']]:continue
        try:out[i]=int(re.sub('[uUlL]+$','',t),0)
        except ValueError:continue
    return out

def run(root):
    rows=fd.collect(root);bodies=gather_bodies(root);groups=collections.defaultdict(list)
    for r in rows:groups[r['_key']].append(r)
    pairs=collections.defaultdict(list)
    for rs in groups.values():
        for a,b in itertools.combinations(rs,2):
            own_a,sep,method_a=a['symbol'].rpartition('::');own_b,sep,method_b=b['symbol'].rpartition('::')
            if not own_a or own_a==own_b or method_a!=method_b:continue
            sig_a=a.get('full_symbol','').replace(own_a+'::','OWNER::',1)
            sig_b=b.get('full_symbol','').replace(own_b+'::','OWNER::',1)
            if sig_a!=sig_b:continue
            if own_b<own_a:a,b=b,a;own_a,own_b=own_b,own_a
            aa=direct_this_offsets(bodies[int(a['address'],16)]);bb=direct_this_offsets(bodies[int(b['address'],16)])
            for i in sorted(set(aa)&set(bb)):
                pairs[(own_a,own_b)].append({'from':aa[i],'to':bb[i],
                    'source_function':a['address'],'target_function':b['address'],
                    'source_symbol':a.get('full_symbol',a['symbol']),
                    'target_symbol':b.get('full_symbol',b['symbol']),
                    'token_position':i})
    results=[]
    for (ca,cb),ev in sorted(pairs.items()):
        forward=collections.defaultdict(set);reverse=collections.defaultdict(set)
        for e in ev:forward[e['from']].add(e['to']);reverse[e['to']].add(e['from'])
        maps=[]
        for old,newset in sorted(forward.items()):
            for new in sorted(newset):
                evidence=[e for e in ev if e['from']==old and e['to']==new]
                maps.append({'from_offset':hex(old),'to_offset':hex(new),
                     'conflict':len(newset)>1 or len(reverse[new])>1,
                     'distinct_function_pairs':len({(e['source_function'],e['target_function']) for e in evidence}),
                     'occurrences':len(evidence),'evidence':evidence})
        results.append({'source_class':ca,'target_class':cb,
           'distinct_function_pairs':len({(e['source_function'],e['target_function']) for e in ev}),
           'offset_correspondences':maps,'status':'CANDIDATE_ONLY'})
    return {'scope':'Lexical direct-this offsets from historical drafts. Numeric size, access width, base adjustment, aliasing, callee semantics, EH and current headers still require verification.', 'class_pairs':results}

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('root',type=Path);ap.add_argument('out',type=Path);a=ap.parse_args();d=run(a.root)
    a.out.parent.mkdir(parents=True,exist_ok=True);a.out.write_text(json.dumps(d,indent=2,ensure_ascii=False))
    for r in d['class_pairs']:
        if r['source_class']=='CMerchantMenu' and r['target_class']=='CStashMenu':
            print(r['source_class'],r['target_class'],r['distinct_function_pairs'],'method pairs',len(r['offset_correspondences']),'offset pairs')
            print([(x['from_offset'],x['to_offset'],x['conflict'],x['distinct_function_pairs']) for x in r['offset_correspondences']])
if __name__=='__main__':main()
