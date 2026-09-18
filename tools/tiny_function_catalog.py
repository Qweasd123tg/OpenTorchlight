#!/usr/bin/env python3
"""Conservatively classify small original Torchlight C* methods.

This is a work-reduction catalogue, not an automatic port. It recognises only
small, obvious machine-code shapes (no-op, return constant, direct field
getter/setter, forwarding thunk, trivial destructor wrapper, etc.). Everything
else stays ``unclassified``.

The catalogue is deliberately split between *leaf semantics* and *routing
semantics*.  A field getter is useful as an exact leaf description.  A virtual
forwarder or destructor wrapper is useful because the wrapper itself no longer
needs a separate deep reverse pass, but the target method still carries the
meaning.  Neither category is automatically promoted in function-transfer.json.

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


MEM = r"(?:BYTE PTR |WORD PTR |DWORD PTR |QWORD PTR )?"


def classify(ins: list[tuple[str,str]], symbol: str = "") -> tuple[str,dict]:
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
        # Singleton/global pointer accessors.  RIP-relative storage is data, not
        # an object field; preserve the displacement so a later pass can tie it
        # to the corresponding symbol/relocation.
        gp=re.fullmatch(r'rax,QWORD PTR \[rip\+(-?0x[0-9a-f]+)\]',o)
        if m=='mov' and gp:
            return 'global_pointer_getter',{'displacement':gp.group(1)}
        # Trivial passthrough methods such as missile target validators.
        ap=re.fullmatch(r'(rax|eax),(rdi|edi|rsi|esi|rdx|edx|rcx|ecx|r8|r8d|r9|r9d)',o)
        if m=='mov' and ap:
            return 'argument_passthrough',{'destination':ap.group(1),'source':ap.group(2)}
        # Constant field write / tiny arithmetic mutator.
        cs=re.fullmatch(MEM+r'\[rdi(?:\+(-?0x[0-9a-f]+))?\],(0x[0-9a-f]+|-?\d+)',o)
        if m.startswith('mov') and cs:
            return 'field_constant_setter',{'offset':cs.group(1) or '0x0','value':cs.group(2),'mnemonic':m}
        au=re.fullmatch(MEM+r'\[rdi(?:\+(-?0x[0-9a-f]+))?\],(esi|rsi|edx|rdx|ecx|rcx|0x[0-9a-f]+|-?\d+)',o)
        if m in {'add','sub'} and au:
            return 'field_arithmetic_update',{'operation':m,'offset':au.group(1) or '0x0','rhs':au.group(2)}
        iu=re.fullmatch(MEM+r'\[rdi(?:\+(-?0x[0-9a-f]+))?\]',o)
        if m in {'inc','dec'} and iu:
            return 'field_arithmetic_update',{'operation':m,'offset':iu.group(1) or '0x0'}
    if len(seq)==1 and seq[0][0].startswith('jmp'):
        return 'tail_thunk',{'target':seq[0][1]}
    if len(seq)==2 and seq[0][0].startswith('jmp') and seq[1][0]=='ret':
        return 'tail_thunk',{'target':seq[0][1]}
    # C++ adjusted-this thunks: the wrapper has no independent semantics; the
    # target function remains the unit that must be understood.
    if len(seq)==2 and seq[-1][0].startswith('jmp'):
        m,o=seq[0]
        if ((m in {'add','sub'} and re.fullmatch(r'rdi,(?:0x[0-9a-f]+|-?\d+)',o)) or
            (m=='lea' and re.fullmatch(r'rdi,\[rdi(?:\+|-)(?:0x[0-9a-f]+|\d+)\]',o))):
            return 'adjusted_this_tail_thunk',{'adjustment':o,'target':seq[-1][1]}
        delegate=re.fullmatch(r'rdi,QWORD PTR \[rdi(?:\+(-?0x[0-9a-f]+))?\]',o)
        if m=='mov' and delegate:
            return 'field_delegate_tailcall',{'offset':delegate.group(1) or '0x0','target':seq[-1][1]}
        if m in {'mov','xor'} and re.match(r'(esi|edi|edx|ecx|r8d|r9d),',o):
            return 'constant_arg_tailcall',{'setup':m+' '+o,'target':seq[-1][1]}

    # Pure virtual dispatch wrappers are common in menu/equipment families.
    # Record the slot and any one-instruction argument adapter; do not infer
    # which override will be selected at runtime.
    if len(seq) in {3,4} and seq[0]==('mov','rax,QWORD PTR [rdi]') and seq[-1]==('jmp','rax'):
        middle=seq[1:-1]
        if len(middle)==1 and middle[0][0]=='mov' and re.fullmatch(r'rax,QWORD PTR \[rax\+0x[0-9a-f]+\]',middle[0][1]):
            return 'virtual_slot_forwarder',{'slot':middle[0][1]}
        if (len(middle)==2 and middle[-1][0]=='mov' and
            re.fullmatch(r'rax,QWORD PTR \[rax\+0x[0-9a-f]+\]',middle[-1][1]) and
            middle[0][0] in {'add','sub','mov','movzx'}):
            return 'virtual_slot_forwarder_with_arg_adapter',{
                'adapter':middle[0][0]+' '+middle[0][1], 'slot':middle[-1][1]}

    # A very common UI handler shape: write a flag and return true/false.
    if len(seq)==3 and seq[-1][0]=='ret' and seq[1][0]=='mov' and re.fullmatch(r'eax,(?:0x[0-9a-f]+|-?\d+)',seq[1][1]):
        m,o=seq[0]
        cs=re.fullmatch(MEM+r'\[rdi(?:\+(-?0x[0-9a-f]+))?\],(0x[0-9a-f]+|-?\d+)',o)
        if m.startswith('mov') and cs:
            return 'field_constant_setter_return_constant',{
                'offset':cs.group(1) or '0x0','value':cs.group(2),'return':seq[1][1],'mnemonic':m}

    # Key/mouse state accessors and similar direct predicates over an object
    # field/index.  Restrict this to compare+setcc with no calls or stores.
    if len(seq) in {3,4} and seq[-1][0]=='ret' and seq[-2][0].startswith('set'):
        prefix=seq[:-2]
        compare=prefix[-1] if prefix else None
        if compare and compare[0]=='cmp' and '[' in compare[1] and 'rdi' in compare[1]:
            return 'indexed_or_field_predicate',{
                'predicate':seq[-2][0], 'compare':compare[1],
                'index_setup':[m+' '+o for m,o in prefix[:-1]]}

    # Null-guarded editor/property setters.  The recognised form performs only
    # an optional scalar load and a direct write into the target object.
    if len(seq) in {4,5} and seq[-1][0]=='ret' and seq[0][0]=='test' and seq[0][1] in {'rdi,rdi','edi,edi'} and seq[1][0].startswith('j'):
        body=seq[2:-1]
        if len(body)==1:
            m,o=body[0]
            if m.startswith('mov') and re.search(r'\[rdi(?:\+0x[0-9a-f]+)?\]',o):
                return 'null_guarded_field_setter',{'write':m+' '+o}
        if (len(body)==2 and body[0][0] in {'mov','movzx','movsxd'} and
            body[1][0].startswith('mov') and '[rdi' in body[1][1]):
            return 'null_guarded_field_setter',{
                'load':body[0][0]+' '+body[0][1], 'write':body[1][0]+' '+body[1][1]}

    # Trivial destructor wrappers are scheduling noise, but not proof that the
    # called base destructor is trivial.  Symbol identity is required to avoid
    # classifying an arbitrary vtable write as lifecycle code.
    if '::~' in symbol:
        if (len(seq)==2 and seq[-1][0]=='ret' and seq[0][0]=='mov' and
            re.fullmatch(r'QWORD PTR \[rdi(?:\+0x[0-9a-f]+)?\],0x[0-9a-f]+',seq[0][1])):
            return 'destructor_vptr_leaf',{}
        if (2<=len(seq)<=4 and seq[-1][0].startswith('jmp') and
            all(m=='mov' and re.fullmatch(r'QWORD PTR \[rdi(?:\+0x[0-9a-f]+)?\],0x[0-9a-f]+',o)
                for m,o in seq[:-1])):
            return 'destructor_tail_base',{'target':seq[-1][1]}
        if len(seq)<=8 and any(m=='call' for m,_ in seq) and seq[-1][0].startswith('jmp'):
            return 'deleting_destructor_wrapper',{'target':seq[-1][1]}
    return 'unclassified',{}


ROUTING_KINDS = {
    'tail_thunk','adjusted_this_tail_thunk','field_delegate_tailcall',
    'constant_arg_tailcall','virtual_slot_forwarder','virtual_slot_forwarder_with_arg_adapter',
}
LIFECYCLE_KINDS = {'destructor_vptr_leaf','destructor_tail_base','deleting_destructor_wrapper'}
BINDING_KINDS = {'null_guarded_field_setter'}


def review_tier(kind: str) -> str:
    """Return a scheduling tier, never a completion/status promotion."""
    if kind == 'unclassified':
        return 'manual_or_family'
    if kind in ROUTING_KINDS:
        return 'routing_exact'
    if kind in LIFECYCLE_KINDS:
        return 'lifecycle_wrapper'
    if kind in BINDING_KINDS:
        return 'binding_mechanical'
    return 'leaf_exact'


def main() -> int:
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--elf',type=Path,required=True)
    ap.add_argument('--max-bytes',type=int,default=64)
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
        kind,meta=classify(f['instructions'], f['symbol'])
        counts[kind]=counts.get(kind,0)+1
        rows.append({'address':f"0x{f['address']:08x}",'size':f['size'],'symbol':f['symbol'],'kind':kind,
                     'review_tier':review_tier(kind),'meta':meta,
                     'instruction_count':len(f['instructions'])})
    tiers={}
    for row in rows:
        tiers[row['review_tier']]=tiers.get(row['review_tier'],0)+1
    payload={'schema':2,'elf_sha256':PINNED_SHA256,'max_bytes':args.max_bytes,
             'meaning':'Conservative small-function triage; not semantic completion or an automatic port. Routing/lifecycle wrappers move review to their target instead of closing it.',
             'review_tiers':dict(sorted(tiers.items(),key=lambda kv:(-kv[1],kv[0]))),
             'counts':dict(sorted(counts.items(),key=lambda kv:(-kv[1],kv[0]))),'functions':rows}
    lines=['# Tiny original-function catalogue','',
           '> Conservative scheduling aid. Classified functions still need field/constant/caller review; they should not be counted as full independent feature tasks.','',
           f'Game-style `C*` methods ≤ {args.max_bytes} bytes: **{len(rows)}**.','',
           '## Scheduling tiers','']
    for k,v in payload['review_tiers'].items(): lines.append(f'- `{k}`: {v}')
    lines += ['', '## Recognised machine-code shapes', '']
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
