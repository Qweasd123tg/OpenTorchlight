"""Read-only helpers for the archived Ghidra text, not a C++ semantic parser."""
from __future__ import annotations
from dataclasses import dataclass
from pathlib import Path
import re

@dataclass
class Function:
    address: int
    name: str
    path: str
    line: int
    text: str

def remove_comments(text: str) -> str:
    # Preserve strings and character literals and preserve all source offsets.
    pat = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*', re.S)
    def repl(m):
        s=m.group()
        return ''.join('\n' if c=='\n' else ' ' for c in s) if s.startswith(('/*','//')) else s
    return pat.sub(repl,text)

def functions(root: Path):
    marker=re.compile(r'/\*\s*address=([0-9a-fA-F]+)\s+symbol=([^*]+)\*/')
    seen=set()
    for p in sorted((root/'research/decompiled-core').glob('*.c')):
        text=p.read_text(errors='replace'); ms=list(marker.finditer(text))
        for i,m in enumerate(ms):
            addr=int(m[1],16)
            if addr in seen: continue
            seen.add(addr)
            yield Function(addr,m[2].strip(),str(p.relative_to(root)),text.count('\n',0,m.start())+1,
                           text[m.end():ms[i+1].start() if i+1<len(ms) else len(text)])

def symbols(root: Path):
    out=[]
    for ln,line in enumerate((root/'research/original-symbols.txt').read_text().splitlines(),1):
        m=re.match(r'([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+(\S)\s+(.+)',line)
        if m: out.append(dict(address=int(m[1],16),size=int(m[2],16),kind=m[3],name=m[4],line=ln))
    return out

def close_paren(text, start):
    depth=0; quote=None; i=start
    while i<len(text):
        c=text[i]
        if quote:
            if c=='\\': i+=2; continue
            if c==quote: quote=None
        elif c in '\"\'': quote=c
        elif c=='(': depth+=1
        elif c==')':
            depth-=1
            if depth==0: return i
        i+=1
    raise ValueError('unbalanced parentheses')

def split_args(text):
    args=[]; start=0; depth=0; quote=None; i=0
    while i<len(text):
        c=text[i]
        if quote:
            if c=='\\': i+=2; continue
            if c==quote: quote=None
        elif c in '\"\'': quote=c
        elif c in '([{': depth+=1
        elif c in ')]}': depth-=1
        elif c==',' and depth==0: args.append(text[start:i].strip());start=i+1
        i+=1
    args.append(text[start:].strip())
    return args


def mask_literals(text: str) -> str:
    """Blank literal tokens while preserving offsets and lines for code searches."""
    pat=re.compile(r"(?:L)?\"(?:\\.|[^\"\\])*\"|(?:L)?'(?:\\.|[^'\\])*'", re.S)
    return pat.sub(lambda m: ''.join('\n' if c=='\n' else ' ' for c in m[0]),text)
