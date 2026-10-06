#!/usr/bin/env python3
"""Reassemble selected call-free archival listings as *test-only* native references.
Not a sandbox, not proof of original ELF provenance, and never production output.
Unknown instructions, external control flow, and relocations are rejected.
"""
from __future__ import annotations
import argparse,hashlib,json,re
from pathlib import Path
from archive import symbols
ROW=re.compile(r'^\s*([0-9a-fA-F]+):\s+(.*)$')
BYTE_PREFIX=re.compile(r'^(?:(?:[0-9a-fA-F]{2})\s+)+')
SELECTED=[('91a980.asm',0x91a980,'ref_capture'),('91a680.asm',0x91a680,'ref_keyheld'),
          ('CRandomizer.txt',0xc8a210,'ref_getodds'),('CRandomizer.txt',0xc8a240,'ref_setodds'),
          ('CRandomizer.txt',0xc8a2c0,'ref_removechoice')]
ALLOWED={'mov','movb','movw','movl','movq','movzbl','movzwl','movss','lea','cmp','cmpb','test',
         'shl','add','sub','xor','sete','ret','nop','xchg','cvtsi2ss','cvttss2si',
         'je','jne','ja','jae','jb','jbe','jmp'}

def read_rows(path:Path,start:int,size:int)->list[dict]:
    rows=[]
    for line_no,line in enumerate(path.read_text().splitlines(),1):
        m=ROW.match(line)
        if not m:continue
        address=int(m[1],16)
        if not start<=address<start+size:continue
        raw=m[2].strip(); raw=BYTE_PREFIX.sub('',raw)
        code=raw.split('#')[0].strip()
        code=re.sub(r'\s*<.*>','',code).strip()
        if code:rows.append({'address':address,'text':code,'line':line_no})
    if not rows or rows[0]['address']!=start:raise ValueError('missing function entry')
    if len({r['address'] for r in rows})!=len(rows):raise ValueError('duplicate instruction')
    if rows!=sorted(rows,key=lambda x:x['address']):raise ValueError('unordered listing')
    last=rows[-1]
    expected=2 if last['text']=='repz ret' else 1
    if last['text'] not in ('ret','repz ret') or last['address']+expected!=start+size:
        raise ValueError('unverified function end')
    return rows

def translate(rows:list[dict],name:str,start:int)->str:
    addresses={r['address'] for r in rows}; body=[]
    for row in rows:
        t=row['text']; op=t.split()[0]
        if re.search(r'\b(?:rip|eip|fs|gs|cs|ds|ss)\b',t):raise ValueError('position dependent operand')
        if t.startswith('rep '):
            if t not in ('rep movsq (%rsi),(%rdi)','rep stos %rax,(%rdi)'):
                raise ValueError('unsupported REP')
        elif t=='repz ret':pass
        elif op not in ALLOWED:raise ValueError('unsupported opcode '+op)
        if op.startswith('j'):
            target=re.fullmatch(r'j\w+\s+([0-9a-f]+)',t)
            if not target or int(target[1],16) not in addresses:raise ValueError('external/indirect branch')
            t=op+' .L_'+name+'_'+target[1]
        # Native test references preserve original instruction positions. Shorter encodings
        # are followed by NOP padding; a longer encoding makes the assembler fail closed.
        body+=['.org '+name+'+'+str(row['address']-start)+',0x90', '.L_'+name+'_'+format(row['address'],'x')+':', '    '+t]
    intel=not any('%' in r['text'] for r in rows)
    return '\n'.join(['.text','.intel_syntax noprefix' if intel else '.att_syntax prefix',
        '.globl '+name,'.type '+name+',@function',name+':',*body,'.size '+name+',.-'+name,'.att_syntax prefix'])+'\n'

def build(root:Path,out:Path)->dict:
    by={s['address']:s for s in symbols(root)};out.mkdir(parents=True,exist_ok=True)
    reports=[];asm=[]
    for relative,start,name in SELECTED:
        s=by[start];p=root/'research/disassembly'/relative
        rows=read_rows(p,start,s['size']);asm.append(translate(rows,name,start))
        reports.append({'original_address':hex(start),'name':s['name'],'size':s['size'],
                        'capsule_name':name,'source':str(p.relative_to(root)),
                        'source_sha256':hashlib.sha256(p.read_bytes()).hexdigest(),
                        'instruction_count':len(rows),'rows':rows})
    (out/'native_reference.S').write_text('\n'.join(asm)+'\n.section .note.GNU-stack,"",@progbits\n')
    result={'limitation':'Reassembled archival instruction text, not independently verified original ELF bytes. Test reference only.',
            'functions':reports}
    (out/'native-capsules.json').write_text(json.dumps(result,indent=2))
    return result
if __name__=='__main__':
    a=argparse.ArgumentParser();a.add_argument('root',type=Path);a.add_argument('out',type=Path);p=a.parse_args();build(p.root,p.out)
