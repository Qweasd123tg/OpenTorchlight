#!/usr/bin/env python3
"""Read-only inventory of historical decompilation artifacts. Not completion tracking."""
from __future__ import annotations
import argparse, collections, csv, hashlib, json, re
from pathlib import Path

HEADER = re.compile(r'/\*\s*address=([0-9a-fA-F]+)\s+symbol=([^*]+)\*/')
def mask_text(text: str) -> str:
    # Preserve offsets/newlines while masking comments and literals; metrics only.
    pat = re.compile(r'//[^\n]*|/\*.*?\*/|(?:L|u8|u|U)?"(?:\\.|[^"\\])*"|(?:L|u|U)?\'(?:\\.|[^\'\\])*\'', re.S)
    return pat.sub(lambda m: ''.join('\n' if c=='\n' else ' ' for c in m.group()), text)

def run(root: Path) -> dict:
    records=[]; symbols={}
    for line in (root/'research/original-symbols.txt').read_text().splitlines():
        m=re.match(r'^([0-9a-f]+) ([0-9a-f]+) [A-Za-z] (.*)$',line)
        if m: symbols[int(m[1],16)]={'size':int(m[2],16),'full_symbol':m[3]}
    for p in sorted((root/'research/decompiled-core').glob('*.c')):
        text=p.read_text(); marks=list(HEADER.finditer(text))
        for i,m in enumerate(marks):
            end=marks[i+1].start() if i+1<len(marks) else len(text)
            body=text[m.end():end]; code=mask_text(body); addr=int(m[1],16)
            rec={'address':hex(addr),'symbol':m[2].strip(),'path':str(p.relative_to(root)),
                 'line':text.count('\n',0,m.start())+1,'text_lines':len(body.splitlines()),
                 'goto_count':len(re.findall(r'\bgoto\s+\w+\s*;',code)),
                 'if_count':len(re.findall(r'\bif\s*\(',code)),
                 'case_count':len(re.findall(r'\bcase\s',code)),
                 'loop_keywords':len(re.findall(r'\b(?:while|for)\s*\(',code)),
                 'indirect_code_casts':len(re.findall(r'\bcode\s*\*',code)),
                 'instruction_export_available':False,**symbols.get(addr,{})}
            records.append(rec)
    unique={}
    for r in records:
        if r['address'] not in unique or r['text_lines']>unique[r['address']]['text_lines']:
            unique[r['address']]=r
    rows=list(unique.values()); graph=collections.defaultdict(set); names={}
    with (root/'research/original-callgraph.tsv').open() as f:
        for r in csv.DictReader(f,delimiter='\t'):
            a,b=int(r['caller_address'],16),int(r['callee_address'],16)
            graph[a].add(b); names[a]=r['caller_symbol'];names[b]=r['callee_symbol']
    incoming=collections.defaultdict(set)
    for a,bs in graph.items():
        for b in bs:incoming[b].add(a)
    known=set(int(r['address'],16) for r in rows)
    hubs=[{'address':hex(a),'symbol':names.get(a,symbols.get(a,{}).get('full_symbol','?')),
           'distinct_callers':len(callers),'body_size':symbols.get(a,{}).get('size'),
           'archived_callers_with_pseudocode':sum(c in known for c in callers)}
          for a,callers in incoming.items() if a in known]
    out={'scope':'Historical archive; lexical counts are candidate signals, not CFG completeness or current outstanding work.',
         'archive_decompiled_files':len(list((root/'research/decompiled-core').glob('*.c'))),
         'unique_exported_functions':len(rows),'with_goto':sum(r['goto_count']>0 for r in rows),
         'with_10_or_more_gotos':sum(r['goto_count']>=10 for r in rows),
         'with_20_or_more_cases':sum(r['case_count']>=20 for r in rows),
         'top_goto':sorted(rows,key=lambda r:r['goto_count'],reverse=True)[:25],
         'top_cases':sorted(rows,key=lambda r:r['case_count'],reverse=True)[:20],
         'small_high_fan_in':sorted([r for r in hubs if r['body_size'] and r['body_size']<=800],key=lambda r:r['distinct_callers'],reverse=True)[:30],
         'functions':rows}
    return out

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('root',type=Path);p.add_argument('output',type=Path);a=p.parse_args()
    d=run(a.root);a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_text(json.dumps(d,indent=2,ensure_ascii=False))
    print(json.dumps({k:v for k,v in d.items() if k not in ('functions','top_goto','top_cases','small_high_fan_in')},indent=2,ensure_ascii=False))
    print('TOP GOTO');[print(r['symbol'],r['goto_count'],r.get('size'),r['text_lines']) for r in d['top_goto'][:10]]
    print('HUBS');[print(r) for r in d['small_high_fan_in'][:12]]
if __name__=='__main__':main()
