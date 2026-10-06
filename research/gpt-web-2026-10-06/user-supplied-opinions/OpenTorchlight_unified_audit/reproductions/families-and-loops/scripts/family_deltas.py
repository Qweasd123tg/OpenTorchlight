#!/usr/bin/env python3
"""Read-only C-like token family miner over historical Ghidra drafts.
All matches are CANDIDATES, never semantic equivalence or accepted source.
Conserves operators and token order; alpha-renames local temporaries and labels;
parameterizes literal/type/call tokens while conserving their repeated identity.
Does not parse C++ semantics, signature compatibility, CFG, EH or memory effects.
"""
from __future__ import annotations
import argparse,collections,hashlib,json,re
from pathlib import Path
HEADER=re.compile(r'/\*\s*address=([0-9a-fA-F]+)\s+symbol=([^*]+)\*/')
TOKEN=re.compile(r'(?P<ws>\s+)|(?P<comment>//[^\n]*|/\*.*?\*/)|(?P<string>(?:u8|L|u|U)?"(?:\\.|[^"\\])*"|(?:L|u|U)?\'(?:\\.|[^\'\\])*\')|(?P<number>0[xX][0-9a-fA-F]+(?:[uUlL]*)|(?:\d+\.\d*|\.\d+|\d+)(?:[eE][+-]?\d+)?[uUlLfF]*)|(?P<id>[A-Za-z_$][\w$]*)|(?P<op>::|->|<<=|>>=|==|!=|<=|>=|&&|\|\||\+\+|--|\+=|-=|\*=|/=|<<|>>|.)',re.S)
LOCAL=re.compile(r'(?:[A-Za-z]+Var\d+|local_\w+|[A-Za-z]+Stack_\w+|[A-Za-z]+Stack\d+|in_stack_\w+|extraout_\w+|unaff_\w+|in_[A-Z][A-Z0-9_]*)$')
LABEL=re.compile(r'(?:LAB|switchD|caseD)_[\w]+$')
KEYWORDS={'if','while','for','switch','return','sizeof','do','else','case','catch','throw','bool','int','long','uint','ulong','float','double','char','void','short','unsigned','signed','longlong','undefined','undefined1','undefined2','undefined4','undefined8'}
def tokens(text):
    return [(m.lastgroup,m[0]) for m in TOKEN.finditer(text) if m.lastgroup not in ('ws','comment')]
def body_tokens(text):
    ts=tokens(text)
    for j,t in enumerate(ts):
        if t[1]=='{':
            depth=0
            for k in range(j,len(ts)):
                if ts[k][1]=='{':depth+=1
                elif ts[k][1]=='}':
                    depth-=1
                    if depth==0:return ts[j:k+1],ts[:j]
    return [],[]
def canonical(ts,holes=False):
    maps=collections.defaultdict(dict); out=[]; bindings={}
    def var(role,text):
        d=maps[role]
        if text not in d:d[text]=f'@{role}:{len(d)}'
        key=d[text];bindings[key]=text;return key
    for i,(kind,text) in enumerate(ts):
        if kind=='id' and LOCAL.fullmatch(text): out.append(var('LOCAL',text))
        elif kind=='id' and LABEL.fullmatch(text):out.append(var('LABEL',text))
        elif holes and kind in ('number','string'):out.append(var(kind.upper(),text))
        elif holes and kind=='id' and re.fullmatch('C[A-Z]\\w*',text):out.append(var('TYPE',text))
        elif holes and kind=='id' and i+1<len(ts) and ts[i+1][1]=='(' and text not in KEYWORDS:
            out.append(var('CALL',text))
        else:out.append(text)
    return tuple(out),bindings

def collect(root):
    syms={}
    for line in (root/'research/original-symbols.txt').read_text().splitlines():
        m=re.match(r'^([0-9a-f]+) ([0-9a-f]+) [A-Za-z] (.*)$',line)
        if m:syms[int(m[1],16)]={'bytes':int(m[2],16),'full_symbol':m[3]}
    rows={}
    for p in sorted((root/'research/decompiled-core').glob('*.c')):
        text=p.read_text(errors='replace');ms=list(HEADER.finditer(text))
        for i,m in enumerate(ms):
            raw=text[m.end():ms[i+1].start() if i+1<len(ms) else len(text)]
            ts,sig=body_tokens(raw);a=int(m[1],16)
            if not ts:continue
            if a in rows and rows[a]['tokens']>=len(ts):continue
            c,b=canonical(ts,True);exact,eb=canonical(ts,False)
            rows[a]={'address':hex(a),'symbol':m[2].strip(),'path':str(p.relative_to(root)),
                     'line':text.count('\n',0,m.start())+1,'tokens':len(ts),
                     'signature_tokens':[v for _,v in sig], **syms.get(a,{}),
                     '_key':c,'_exact':exact,'bindings':b}
    return list(rows.values())
def run(root):
    rows=collect(root);g=collections.defaultdict(list);eg=collections.defaultdict(list)
    for r in rows:g[r['_key']].append(r);eg[r['_exact']].append(r)
    groups=[]
    old=json.loads((root/'research/manual-shape-clusters.json').read_text())
    oldmembers={int(m['address'],16) for c in old['clusters'] for m in c['members']}
    def clean(r):return {k:v for k,v in r.items() if not k.startswith('_')}
    for key,rs in g.items():
        if len(rs)<2:continue
        base=rs[0];deltas=[]
        for r in rs[1:]:
            diffs={k:{'from':base['bindings'][k],'to':v} for k,v in r['bindings'].items()
                   if base['bindings'].get(k)!=v and not k.startswith(('@LOCAL:','@LABEL:'))}
            deltas.append({'target':r['address'],'changes':diffs})
        groups.append({'family_id':hashlib.sha256(' '.join(key).encode()).hexdigest()[:16],
           'body_tokens':len(key),'members':[clean(r) for r in rs],
           'literal_type_call_deltas':deltas,'total_bytes':sum(r.get('bytes',0) for r in rs),
           'largest_bytes':max(r.get('bytes',0) for r in rs),
           'members_in_old_shape_inventory':sum(int(r['address'],16) in oldmembers for r in rs),
           'status':'CANDIDATE_ONLY'})
    groups.sort(key=lambda x:(-x['largest_bytes'],-len(x['members'])))
    large=[g for g in groups if g['largest_bytes']>=500]
    return {'scope':'Historical pseudocode, not current backlog or semantic verification. Body token matching excludes function signature compatibility. Every concrete hole remains an unverified semantic obligation.',
     'unique_functions':len(rows),'exact_alpha_families':sum(len(v)>1 for v in eg.values()),
     'exact_alpha_members':sum(len(v) for v in eg.values() if len(v)>1),
     'hole_families':len(groups),'hole_members':sum(len(g['members']) for g in groups),
     'families_with_member_ge_500_bytes':len(large),
     'members_in_these_families':sum(len(g['members']) for g in large),
     'sum_bytes_of_these_families':sum(g['total_bytes'] for g in large),
     'groups':groups}

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('root',type=Path);p.add_argument('output',type=Path);a=p.parse_args()
    d=run(a.root);a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_text(json.dumps(d,ensure_ascii=False,indent=2))
    print(json.dumps({k:v for k,v in d.items() if k!='groups'},ensure_ascii=False,indent=2))
    for g in d['groups'][:15]:print(g['largest_bytes'],len(g['members']),[r['symbol'] for r in g['members']])
if __name__=='__main__':main()
