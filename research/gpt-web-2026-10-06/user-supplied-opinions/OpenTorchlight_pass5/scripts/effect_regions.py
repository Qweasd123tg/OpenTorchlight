#!/usr/bin/env python3
"""Extract NORMAL-flow regions and guarded call sites from archived objdump text.
No executable emission, semantic equivalence claim, or completion promotion.
Exception edges and unknown indirect jump targets are explicitly unsupported.
"""
from __future__ import annotations
import argparse, bisect, collections, hashlib, json, re
from pathlib import Path
import networkx as nx

EXIT=-1

def symbols(root):
    out={}
    for line in (root/'research/original-symbols.txt').read_text().splitlines():
        m=re.match(r'^([0-9a-f]+) ([0-9a-f]+) [TtWw] (.*)$',line)
        if m:
            a=int(m[1],16); size=int(m[2],16)
            if size>0:out.setdefault(a,{'address':a,'size':size,'name':m[3]})
    return out

def parse_insn(line):
    m=re.match(r'^\s*([0-9a-fA-F]+):\s+(.*)$',line)
    if not m:return None
    s=re.sub(r'^(?:(?:[0-9a-fA-F]{2})\s+)+','',m[2]).strip()
    p=s.split(None,1)
    if not p or not re.match(r'^[a-zA-Z]',p[0]) or re.fullmatch(r'[a-fA-F0-9]{2}',p[0]):return None
    op=p[0].lower(); args=p[1] if len(p)>1 else ''
    if op in ('rep','repz','repnz','bnd'):
        p=args.split(None,1)
        if not p:return None
        op=p[0].lower();args=p[1] if len(p)>1 else ''
    return int(m[1],16),op,args

def get_funcs(root):
    syms=symbols(root);starts=sorted(syms);fs={}
    for p in sorted((root/'research/disassembly').glob('*')):
        if not p.is_file():continue
        for line in p.read_text(errors='replace').splitlines():
            i=parse_insn(line)
            if not i:continue
            a,op,args=i;k=bisect.bisect_right(starts,a)-1
            if k<0:continue
            s=syms[starts[k]]
            if a>=s['address']+s['size']:continue
            f=fs.setdefault(s['address'],{**s,'insns':{},'sources':set()})
            f['insns'].setdefault(a,{'op':op,'args':args});f['sources'].add(str(p.relative_to(root)))
    return fs

def target(args):
    m=re.match(r'^(?:0x)?([0-9a-f]+)(?:\s|$)',args)
    return int(m[1],16) if m else None

def analyze(f):
    inst=f['insns'];order=sorted(inst);entry=f['address'];succ={};unknown=[]
    if entry not in inst:return {'address':hex(entry),'name':f['name'],'skip':'entry missing in archived range'}
    for idx,a in enumerate(order):
        op,args=inst[a]['op'],inst[a]['args'];nxt=order[idx+1] if idx+1<len(order) else EXIT
        if op.startswith('ret') or op in ('ud2','hlt'): s=[EXIT]
        elif op.startswith('jmp'):
            t=target(args)
            if t is None:unknown.append({'address':hex(a),'kind':'indirect jump','text':args});s=[EXIT]
            elif t in inst:s=[t]
            elif entry<=t<entry+f['size']:unknown.append({'address':hex(a),'kind':'missing internal jump target','target':hex(t)});s=[EXIT]
            else:s=[EXIT]
        elif (op.startswith('j') or op.startswith('loop')):
            t=target(args)
            if t in inst:s=[t,nxt]
            else:
                unknown.append({'address':hex(a),'kind':'missing conditional target','text':args});s=[EXIT,nxt]
        else:s=[nxt]
        succ[a]=list(dict.fromkeys(s))
    leaders={entry}
    for idx,a in enumerate(order):
        op=inst[a]['op']
        if op.startswith('j') or op.startswith('loop') or op.startswith('ret') or op in ('ud2','hlt'):
            leaders.update(t for t in succ[a] if t!=EXIT)
            if idx+1<len(order):leaders.add(order[idx+1])
    blocks={};owner={};cur=None
    for a in order:
        if a in leaders or cur is None:cur=a;blocks[cur]=[]
        blocks[cur].append(a);owner[a]=cur
    g=nx.DiGraph();g.add_nodes_from(blocks);g.add_node(EXIT)
    for b,aa in blocks.items():
        for t in succ[aa[-1]]:g.add_edge(b,owner[t] if t!=EXIT else EXIT)
    reachable={entry}|nx.descendants(g,entry);g=g.subgraph(reachable).copy()
    if EXIT not in g:
        return {'address':hex(entry),'name':f['name'],'skip':'no normal exit in modeled graph'}
    can_exit={EXIT}|nx.ancestors(g,EXIT);rg=g.subgraph(can_exit).copy()
    idom=nx.immediate_dominators(g,entry);ipdom=nx.immediate_dominators(rg.reverse(copy=False),EXIT)
    # Include reflexive roots independently of the NetworkX implementation.
    idom[entry]=entry;ipdom[EXIT]=EXIT
    def dominates(a,b):
        while b in idom:
            if a==b:return True
            nb=idom[b]
            if nb==b:return False
            b=nb
        return False
    # Conditional control dependence via postdominator walk; absent exception edges.
    guards=collections.defaultdict(set)
    for a in rg:
        if a==EXIT or rg.out_degree(a)<2:continue
        stop=ipdom.get(a)
        for child in rg.successors(a):
            runner=child;seen=set()
            while runner!=stop and runner!=EXIT and runner not in seen:
                seen.add(runner);guards[runner].add(a)
                runner=ipdom.get(runner,EXIT)
    regions=[]
    for h in rg:
        if h==EXIT or rg.out_degree(h)<2:continue
        end=ipdom.get(h)
        if end is None or end==EXIT or end==h:continue
        members=set();todo=[h]
        while todo and len(members)<=1000:
            n=todo.pop()
            if n==end or n in members:continue
            if n==EXIT:members.add(EXIT);break
            members.add(n);todo.extend(rg.successors(n))
        if EXIT in members or len(members)>1000 or len(members)<2:continue
        if any(not dominates(h,n) for n in members):continue
        if any(p not in members and n!=h for n in members for p in g.predecessors(n)):continue
        if any(t not in members and t!=end for n in members for t in g.successors(n)):continue
        calls=[a for n in sorted(members) for a in blocks[n] if inst[a]['op'].startswith('call')]
        regions.append({'header':hex(h),'merge':hex(end),'block_count':len(members),
                        'instruction_count':sum(len(blocks[n]) for n in members),
                        'calls':len(calls),'call_addresses':[hex(x) for x in calls],
                        'block_addresses':[hex(x) for x in sorted(members)]})
    backedges=[(a,b) for a,b in g.edges() if b!=EXIT and dominates(b,a)]
    call_sites=[]
    for b in g:
        if b==EXIT:continue
        for a in blocks[b]:
            if inst[a]['op'].startswith('call'):
                call_sites.append({'address':hex(a),'target':inst[a]['args'],
                                   'guard_blocks':[hex(n) for n in sorted(guards[b])],
                                   'enclosing_regions':[r['header'] for r in regions if hex(b) in r['block_addresses']]})
    return {'address':hex(entry),'name':f['name'],'symbol_size':f['size'],
            'archived_instruction_count':len(inst),'normal_flow_blocks':len(g)-1,
            'normal_flow_edges':g.number_of_edges(),'loop_back_edges':len(backedges),
            'non_exiting_reachable_blocks':len(set(g)-can_exit),
            'exception_edges_modeled':False,'call_arguments_recovered':False,
            'unresolved_transfers':unknown,'normal_flow_regions':regions,
            'region_count':len(regions),'call_sites':call_sites,'sources':sorted(f['sources']),
            'scope':'NORMAL-flow candidate analysis only. Calls assumed to return; EH edges, memory dependencies and listing completeness not established. Regions overlap and are not independent implementations.'}

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('root',type=Path);p.add_argument('output',type=Path);a=p.parse_args()
    rows=[analyze(f) for f in get_funcs(a.root).values()]
    out={'functions':rows,'normal_flow_only':True,'game_source_changed':False}
    a.output.parent.mkdir(parents=True,exist_ok=True)
    a.output.write_text(json.dumps(out,indent=2,ensure_ascii=False))
    for r in sorted(rows,key=lambda r:r.get('archived_instruction_count',0),reverse=True)[:12]:
        print(r['name'],r.get('archived_instruction_count'),r.get('normal_flow_blocks'),r.get('loop_back_edges'),r.get('region_count'),'unresolved',len(r.get('unresolved_transfers',[])))
if __name__=='__main__':main()
