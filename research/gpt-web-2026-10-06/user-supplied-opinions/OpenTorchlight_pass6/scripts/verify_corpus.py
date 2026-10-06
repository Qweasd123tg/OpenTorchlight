#!/usr/bin/env python3
"""Read-only archive regression checks; token round trips are NOT semantic proof."""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import family_deltas as fd
import member_alignment as ma


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('root',type=Path)
    ap.add_argument('output',type=Path)
    args=ap.parse_args()
    rows=fd.collect(args.root)
    bodies=ma.gather_bodies(args.root)
    bad=[]
    for r in rows:
        rebuilt=[r['bindings'].get(token,token) for token in r['_key']]
        expected=[v for _,v in bodies[int(r['address'],16)]]
        if rebuilt!=expected:bad.append(r['address'])
    by={r['address']:r for r in rows}
    source=by['0xb6ab50'];target=by['0xbf7cc0']
    same_template=source['_key']==target['_key']
    changes={k:{'from':source['bindings'][k],'to':v} for k,v in target['bindings'].items()
             if source['bindings'].get(k)!=v and not k.startswith(('@LOCAL:','@LABEL:'))}
    wanted={('CMerchantMenu','CStashMenu'),('0x3440','0x3410')}
    actual={(d['from'],d['to']) for d in changes.values()}
    out={'scope':'Lexical round-trip and specific historic pair; no source generation or semantic proof.',
         'body_round_trips':len(rows),'round_trip_failures':bad,
         'merchant_stash_same_template':same_template,
         'merchant_stash_body_tokens':len(source['_key']),
         'merchant_stash_non_alpha_deltas':changes,
         'expected_top_pair_deltas_match':actual==wanted}
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text(json.dumps(out,indent=2,ensure_ascii=False))
    print(json.dumps(out,indent=2,ensure_ascii=False))
    if bad or not same_template or actual!=wanted:raise SystemExit(1)

if __name__=='__main__':main()
