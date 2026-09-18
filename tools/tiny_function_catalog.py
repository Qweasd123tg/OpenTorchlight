#!/usr/bin/env python3
"""Conservatively classify tiny original Torchlight C* methods.

This is a work-reduction catalogue, not an automatic port. It recognises only
very small, obvious machine-code shapes (no-op, return constant, direct field
getter/setter, tail thunk). Everything else stays 'unclassified'.

The original ELF is read-only and fingerprint checked. One objdump pass covers
all requested functions, so thousands of small methods do not require thousands
of subprocesses.
"""
from __future__ import annotations
import argparse
import hashlib
import json
import re
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PINNED_SHA256 = "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"
SYM_RE = re.compile(r"^([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+([TtWw])\s+(.+)$")
INS_RE = re.compile(r"\s*([0-9a-f]+):\s+([a-zA-Z][a-zA-Z0-9.]*)\s*(.*)$")


def sha256(path: Path) -> str:
    h=hashlib.sha256()
    with path.open('rb') as f:
        for b in iter(lambda:f.read(1024*1024), b''): h.update(b)
    return h.hexdigest()


def game_symbol(symbol: str) -> bool:
    s=symbol.split('thunk to ',1)[-1]
    return re.match(r'^C[A-Za-z0-9_]+::',s) is not None


def load_functions(max_bytes: int) -> list[dict]:
    by={}
    for line in (ROOT/'research/original-symbols.txt').read_text(encoding='utf-8',errors='replace').splitlines():
        m=SYM_RE.match(line.strip())
        if not m: continue
        a,size,_t,sym=m.groups(); a=int(a,16); size=int(size,16)
        if size<=0 or size>max_bytes or not game_symbol(sym): continue
        cur=by.get(a)
        if cur is None or size>cur['size']:
            by[a]={'address':a,'size':size,'symbol':sym}
    return sorted(by.values(),key=lambda x:x['address'])


def clean_ops(ops: str) -> str:
    return ops.split('#',1)[0].strip()


def classify(ins: list[tuple[str,str]]) -> tuple[str,dict]:
    # Ignore alignment nops at the end/beginning only.
    seq=[]
    for m,o in ins:
        if m.startswith('nop'):
            continue
        o=clean_ops(o)
        if m in {'repz','rep'} and o=='ret':
            seq.append(('ret',''))
        else:
            seq.append((m,o))
    if seq==[('ret','')]: return 'noop',{}
    if len(seq)==2 and seq[-1][0]=='ret':
        m,o=seq[0]
        if m=='xor' and (re.fullmatch(r'%e?ax,%e?ax',o) or o in {'eax,eax','rax,rax'}): return 'return_zero',{'register':'eax'}
        mm=re.fullmatch(r'\$(0x[0-9a-f]+|-?\d+),%(e?ax|rax)',o)
        if m.startswith('mov') and mm: return 'return_constant',{'value':mm.group(1),'register':mm.group(2)}
        # direct this-field getter (integer/pointer/float bit pattern register moves)
        gm=re.fullmatch(r'(-?0x[0-9a-f]+)?\(%rdi\),%(rax|eax|ax|al|xmm0)',o)
        if m.startswith('mov') and gm:
            return 'field_getter',{'offset':gm.group(1) or '0x0','register':gm.group(2),'mnemonic':m}
        lm=re.fullmatch(r'(-?0x[0-9a-f]+)?\(%rdi\),%rax',o)
        if m=='lea' and lm:
            return 'field_address_getter',{'offset':lm.group(1) or '0x0'}
        # direct this-field setter from common first scalar/pointer argument registers.
        sm=re.fullmatch(r'%(rsi|esi|si|sil|xmm0),(-?0x[0-9a-f]+)?\(%rdi\)',o)
        if m.startswith('mov') and sm:
            return 'field_setter',{'source':sm.group(1),'offset':sm.group(2) or '0x0','mnemonic':m}
        # Intel-syntax equivalents used by the saved full disassembly.
        cm=re.fullmatch(r'(e?ax|rax),(0x[0-9a-f]+|-?\d+)',o)
        if m.startswith('mov') and cm:
            return 'return_constant',{'value':cm.group(2),'register':cm.group(1)}
        gm_i=re.fullmatch(r'(rax|eax|ax|al|xmm0),(?:BYTE PTR |WORD PTR |DWORD PTR |QWORD PTR )?\[rdi(?:\+(-?0x[0-9a-f]+))?\]',o)
        if (m.startswith('mov') or m in {'movzx','movsx','movsxd','movss','movsd'}) and gm_i:
            return 'field_getter',{'offset':gm_i.group(2) or '0x0','register':gm_i.group(1),'mnemonic':m}
        la_i=re.fullmatch(r'rax,\[rdi(?:\+(-?0x[0-9a-f]+))?\]',o)
        if m=='lea' and la_i:
            return 'field_address_getter',{'offset':la_i.group(1) or '0x0'}
        sm_i=re.fullmatch(r'(?:BYTE PTR |WORD PTR |DWORD PTR |QWORD PTR )?\[rdi(?:\+(-?0x[0-9a-f]+))?\],(rsi|esi|si|sil|xmm0)',o)
        if m.startswith('mov') and sm_i:
            return 'field_setter',{'source':sm_i.group(2),'offset':sm_i.group(1) or '0x0','mnemonic':m}
    if len(seq)==1 and seq[0][0].startswith('jmp'):
        return 'tail_thunk',{'target':seq[0][1]}
    if len(seq)==2 and seq[0][0].startswith('jmp') and seq[1][0]=='ret':
        return 'tail_thunk',{'target':seq[0][1]}
    return 'unclassified',{}


def main() -> int:
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--elf',type=Path,required=True)
    ap.add_argument('--max-bytes',type=int,default=32)
    ap.add_argument('--disasm',type=Path,help='pre-generated objdump -d text for speed')
    ap.add_argument('--json',type=Path)
    ap.add_argument('--out',type=Path)
    args=ap.parse_args()
    if sha256(args.elf)!=PINNED_SHA256:
        raise SystemExit('ELF fingerprint mismatch')
    funcs=load_functions(args.max_bytes)
    # One disassembly pass. Prefer a pre-generated dump; spawning objdump over the
    # whole executable is intentionally optional because it can take minutes.
    proc = None
    if args.disasm:
        stream = args.disasm.open('r', encoding='utf-8', errors='replace')
    else:
        proc=subprocess.Popen(['objdump','-d','--no-show-raw-insn',str(args.elf)],stdout=subprocess.PIPE,text=True,errors='replace')
        assert proc.stdout is not None
        stream = proc.stdout
    idx=0
    for f in funcs: f['instructions']=[]
    try:
        for line in stream:
            m=INS_RE.match(line)
            if not m: continue
            a=int(m.group(1),16)
            while idx<len(funcs) and a>=funcs[idx]['address']+funcs[idx]['size']: idx+=1
            if idx>=len(funcs): break
            f=funcs[idx]
            if f['address']<=a<f['address']+f['size']:
                f['instructions'].append((m.group(2),m.group(3)))
    finally:
        if args.disasm:
            stream.close()
    if proc is not None:
        rc=proc.wait()
        if rc: raise SystemExit(f'objdump failed: {rc}')
    counts={}
    rows=[]
    for f in funcs:
        kind,meta=classify(f['instructions'])
        counts[kind]=counts.get(kind,0)+1
        rows.append({'address':f"0x{f['address']:08x}",'size':f['size'],'symbol':f['symbol'],'kind':kind,'meta':meta,
                     'instruction_count':len(f['instructions'])})
    payload={'schema':1,'elf_sha256':PINNED_SHA256,'max_bytes':args.max_bytes,
             'meaning':'Conservative tiny-function triage; not semantic completion or an automatic port.',
             'counts':dict(sorted(counts.items(),key=lambda kv:(-kv[1],kv[0]))),'functions':rows}
    lines=['# Tiny original-function catalogue','',
           '> Conservative scheduling aid. Classified functions still need field/constant/caller review; they should not be counted as full independent feature tasks.','',
           f'Game-style `C*` methods ≤ {args.max_bytes} bytes: **{len(rows)}**.','']
    for k,v in payload['counts'].items(): lines.append(f'- `{k}`: {v}')
    lines += ['', 'Recognised shapes can normally be reviewed in batches by kind; `unclassified` remains normal code-first work.','']
    text='\n'.join(lines)
    if args.out:
        args.out.parent.mkdir(parents=True,exist_ok=True);args.out.write_text(text,encoding='utf-8');print('wrote',args.out)
    else: print(text)
    if args.json:
        args.json.parent.mkdir(parents=True,exist_ok=True);args.json.write_text(json.dumps(payload,ensure_ascii=False,indent=2)+'\n',encoding='utf-8');print('wrote',args.json)
    return 0

if __name__=='__main__': raise SystemExit(main())
