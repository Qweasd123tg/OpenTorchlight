#!/usr/bin/env python3
"""Cluster the residual manual queue by exact normalized instruction shape.

Input is research/auto-triage.json.  Only functions whose primary class is
``manual`` are considered.  Concrete addresses, immediates, field offsets and
call targets are normalized, so a cluster is a *batching hint*, not proof of
semantic equality.  Each member still needs a delta table for constants,
callees, fields and callers.

The external disassembly must come from the pinned original ELF build.  When an
ELF is supplied its SHA-256 is checked.  This tool never edits transfer status.
"""
from __future__ import annotations
import argparse, hashlib, json, re
from collections import defaultdict
from pathlib import Path

ROOT=Path(__file__).resolve().parents[1]
PINNED_SHA256="91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"
SYM_RE=re.compile(r"^([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+[TtWw]\s+(.+)$")
INS_RE=re.compile(r"\s*([0-9a-f]+):\s+([a-zA-Z][a-zA-Z0-9.]*)\s*(.*)$")


def sha256(path:Path)->str:
 h=hashlib.sha256()
 with path.open('rb') as f:
  for b in iter(lambda:f.read(1024*1024),b''):h.update(b)
 return h.hexdigest()


def normalize(mn:str,op:str)->str:
 op=op.split('#',1)[0].strip()
 if mn.startswith('call'):return mn+' CALL'
 if mn.startswith('j'):return mn+' BR'
 op=re.sub(r'<[^>]+>','SYM',op)
 op=re.sub(r'(?<![A-Za-z0-9_])-?0x[0-9a-f]+','IMM',op)
 op=re.sub(r'(?<![A-Za-z0-9_])-?\d+','N',op)
 return mn+(' '+op if op else '')


def main()->int:
 ap=argparse.ArgumentParser(description=__doc__)
 ap.add_argument('--root',type=Path,default=ROOT)
 ap.add_argument('--disasm',type=Path,required=True)
 ap.add_argument('--elf',type=Path)
 ap.add_argument('--min-cluster',type=int,default=2)
 ap.add_argument('--json',type=Path)
 ap.add_argument('--out',type=Path)
 args=ap.parse_args();root=args.root.resolve()
 if args.elf and sha256(args.elf)!=PINNED_SHA256:raise SystemExit('ELF fingerprint mismatch')
 tri=json.loads((root/'research/auto-triage.json').read_text(encoding='utf8'))
 manual={int(x['address'],16):x for x in tri['functions'] if x['work_class']=='manual'}
 sizes={};symbols={}
 for line in (root/'research/original-symbols.txt').read_text(encoding='utf8',errors='replace').splitlines():
  m=SYM_RE.match(line.strip())
  if not m:continue
  a=int(m.group(1),16)
  if a not in manual:continue
  sz=int(m.group(2),16);sym=m.group(3)
  if a not in sizes or sz>sizes[a]:sizes[a]=sz;symbols[a]=sym
 addrs=sorted(a for a in manual if sizes.get(a,0)>0);instructions={a:[] for a in addrs};idx=0
 with args.disasm.open(encoding='utf8',errors='replace') as fh:
  for line in fh:
   m=INS_RE.match(line)
   if not m:continue
   a=int(m.group(1),16)
   while idx<len(addrs) and a>=addrs[idx]+sizes[addrs[idx]]:idx+=1
   if idx>=len(addrs):break
   start=addrs[idx]
   if start<=a<start+sizes[start] and not m.group(2).startswith('nop'):
    instructions[start].append(normalize(m.group(2),m.group(3)))
 groups=defaultdict(list)
 for a in addrs:groups[tuple(instructions[a])].append(a)
 clusters=[g for g in groups.values() if len(g)>=args.min_cluster]
 clusters.sort(key=lambda g:(-len(g),g[0]))
 members=sum(len(g) for g in clusters);saved=sum(len(g)-1 for g in clusters)
 payload={
  'schema':1,'elf_sha256':PINNED_SHA256,
  'meaning':'Exact normalized machine-shape batching hints for residual manual functions; not semantic equivalence.',
  'manual_with_known_size':len(addrs),'all_shapes':len(groups),'multi_member_clusters':len(clusters),
  'clustered_members':members,'representative_passes_saved_if_all_deltas_validate':saved,
  'clusters':[
   {'size':len(g),'representative':f'0x{g[0]:08x}','members':[{'address':f'0x{a:08x}','symbol':symbols[a]} for a in g]}
   for g in clusters
  ]
 }
 lines=['# Residual manual-queue shape clusters','',
        '> Exact normalized instruction shape is a batching hint only. Constants, fields, call targets and callers remain per-member deltas.','',
        f"Manual functions with known size: **{len(addrs)}**.",
        f"Multi-member exact-shape clusters: **{len(clusters)}**, containing **{members}** functions.",
        f"Maximum individual passes avoided if every cluster validates: **{saved}**.",'']
 for i,g in enumerate(clusters[:80],1):
  lines += [f"## {i}. {len(g)} members",'']
  for a in g[:20]:lines.append(f"- `0x{a:08x}` `{symbols[a]}`")
  if len(g)>20:lines.append(f"- … {len(g)-20} more")
  lines.append('')
 text='\n'.join(lines)
 if args.out:args.out.parent.mkdir(parents=True,exist_ok=True);args.out.write_text(text,encoding='utf8');print('wrote',args.out)
 else:print(text)
 if args.json:args.json.parent.mkdir(parents=True,exist_ok=True);args.json.write_text(json.dumps(payload,ensure_ascii=False,indent=2)+'\n',encoding='utf8');print('wrote',args.json)
 return 0
if __name__=='__main__':raise SystemExit(main())
