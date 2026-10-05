#!/usr/bin/env python3
"""Make a line-linked reading view; never rewrite/compile a decompiler draft."""
import argparse,re
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('input',type=Path);p.add_argument('output',type=Path);a=p.parse_args()
original=a.input.read_text();lines=original.splitlines();out=[];folds=[];i=0;comment=False
# Full raw input stays authoritative and available next to this reading aid.
while i<len(lines):
    line=lines[i];start=i
    if '/*' in line:
        if line.lstrip().startswith('/*'):
            while '*/' not in lines[i] and i+1<len(lines):i+=1
            i+=1;continue
    if line.lstrip().startswith('if ((allocator *)'):
        j=i;header=''
        while j<len(lines) and '{' not in lines[j] and j<i+6:
            header+=lines[j];j+=1
        if j<len(lines):header+=lines[j]
        if '_Rep::_S_empty_rep_storage' in header:
            depth=0;k=j
            while k<len(lines):
                depth+=lines[k].count('{')-lines[k].count('}')
                if depth==0:break
                k+=1
            body='\n'.join(lines[i:k+1])
            next_line=lines[k+1].strip() if k+1<len(lines) else ''
            # Only narrow allocator/refcount cleanup candidates. No domain
            # service call or control-transfer is silently hidden.
            forbidden=re.search(r'\b(?:C[A-Z]\w*|Ogre|STRINGS|UTILITIES)::|\b(?:goto|return|throw)\b|"',body)
            if k<len(lines) and not forbidden and not next_line.startswith('else'):
                out.append(f'{i+1:5}-{k+1:<5} [allocator/refcount cleanup candidate folded; see raw lines]')
                folds.append((i+1,k+1));i=k+1;continue
    if line.strip():out.append(f'{i+1:5} {line}')
    i+=1
a.output.write_text('READING AID ONLY. Numbers refer to '+a.input.name+'.\nNot recovered source; omitted cleanup still needs correct source-level lifetimes.\n\n'+'\n'.join(out)+'\n')
print('input lines',len(lines),'reading lines',len(out),'folded candidates',len(folds))
