#!/usr/bin/env python3
"""Read-only index of updateIngameUI; does not claim semantic recovery."""
import argparse, collections, hashlib, json, re, subprocess
from pathlib import Path
START, END = 0xab8100, 0xacbb35
SHA = '91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b'
p = argparse.ArgumentParser(); p.add_argument('elf', type=Path); p.add_argument('output', type=Path)
a = p.parse_args()
assert hashlib.sha256(a.elf.read_bytes()).hexdigest() == SHA, 'wrong original ELF'
a.output.mkdir(parents=True, exist_ok=True)
s = subprocess.check_output(['objdump','-d','-C','--no-show-raw-insn', '--start-address='+hex(START),'--stop-address='+hex(END),str(a.elf)], text=True)
(a.output/'updateIngameUI.asm').write_text(s)
rows=[]
for line in s.splitlines():
    m=re.match(r'\s*([0-9a-f]+):\s+(\S+)\s*(.*)', line)
    if m: rows.append((int(m[1],16),m[2],m[3]))
assert rows and rows[0][0] == START and all(START <= r[0] < END for r in rows)
addresses={r[0] for r in rows}; leaders={START}; edges=[]; unresolved=[]
for i,(addr,op,arg) in enumerate(rows):
    if op.startswith('j') or op.startswith('loop'):
        m=re.match(r'([0-9a-f]+)\s',arg)
        if m:
            target=int(m[1],16)
            edges.append((addr,'taken',target))
            if target in addresses: leaders.add(target)
        else: unresolved.append((addr,op,arg))
        if i+1<len(rows):
            leaders.add(rows[i+1][0])
            if op!='jmp': edges.append((addr,'fallthrough',rows[i+1][0]))
    elif op.startswith('ret') and i+1<len(rows): leaders.add(rows[i+1][0])
calls=[r for r in rows if r[1]=='call']; counts=collections.Counter(r[2] for r in calls)
(a.output/'calls.tsv').write_text('address\ttarget\n'+''.join(f'{addr:#x}\t{arg}\n' for addr,op,arg in calls))
(a.output/'branches.tsv').write_text('address\tedge\ttarget\n'+''.join(f'{addr:#x}\t{kind}\t{target:#x}\n' for addr,kind,target in edges))
(a.output/'call_counts.tsv').write_text('count\ttarget\n'+''.join(f'{count}\t{arg}\n' for arg,count in counts.most_common()))
summary={'elf_sha256':SHA,'start':hex(START),'end_exclusive':hex(END),'original_bytes':END-START,'decoded_instructions':len(rows),'call_sites':len(calls),'indirect_call_sites':sum('*' in r[2] for r in calls),'direct_call_targets':len({r[2] for r in calls if '*' not in r[2]}),'syntactic_block_leaders':len(leaders),'unresolved_branches':unresolved,'limitations':['Static call sites, not runtime invocation counts.','No exception landing-pad edges, no indirect-call resolution.','Syntactic block partition is not semantic recovery or coverage.']}
(a.output/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print(json.dumps(summary,indent=2))
