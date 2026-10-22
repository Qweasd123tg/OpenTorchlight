"""Bounded original fixed-frame certificates; no mutable-path decoder input."""
import hashlib
import re
import subprocess
import tempfile

REGS = {'rbx','rbp','r12','r13','r14','r15'}


def parse_cfi(text, start, end):
    blocks = re.split(r'(?m)(?=^[0-9a-f]+ .* (?:FDE|CIE) )', text)
    matches=[]
    for block in blocks:
        head=re.match(r'[^\n]* FDE cie=([0-9a-f]+) pc=([0-9a-f]+)\.\.([0-9a-f]+)\n',block)
        if head and int(head[2],16) < end and start < int(head[3],16):
            matches.append((head,block))
    if len(matches)!=1:return None
    head,block=matches[0]
    if (int(head[2],16),int(head[3],16))!=(start,end):return None
    cie=int(head[1],16)
    cies=[b for b in blocks if re.match(r'([0-9a-f]+).* CIE ',b)
          and int(re.match('[0-9a-f]+',b)[0],16)==cie]
    if len(cies)!=1:return None
    lines=cies[0].splitlines()
    if not re.fullmatch(r'[0-9a-f]+ [0-9a-f]+ [0-9a-f]+ CIE "z(?:P)?(?:L)?R" cf=1 df=-8 ra=16',lines[0]):return None
    initial=[line.split() for line in lines[1:] if line.strip()]
    if initial!=[['LOC','CFA','ra'],['0000000000000000','rsp+8','c-8']]:return None
    lines=block.splitlines()
    if not any(line.strip() for line in lines[1:]):
        return {'start':start,'end':end,'cie':cie,'rows':[(start,{'CFA':'rsp+8','ra':'c-8'})]}
    columns=lines[1].split() if len(lines)>1 else []
    if (len(columns)<3 or columns[:2]!=['LOC','CFA'] or columns[-1]!='ra'
            or len(columns)!=len(set(columns)) or not set(columns[2:-1])<=REGS):return None
    rows=[]
    for line in lines[2:]:
        if not line.strip():break
        cells=line.split()
        if len(cells)!=len(columns) or not re.fullmatch('[0-9a-f]+',cells[0]):return None
        pc=int(cells[0],16)
        if not start<=pc<end or (rows and pc<=rows[-1][0]):return None
        rows.append((pc,dict(zip(columns[1:],cells[1:]))))
    if not rows or rows[0][0]!=start:return None
    return {'start':start,'end':end,'cie':cie,'rows':rows}


def cfi(side, info):
    image=side.image
    if hashlib.sha256(image.data).hexdigest()!=image.sha256:return None
    cached=getattr(side,'_saved_argument_cfi',None)
    if cached is None or cached[0]!=image.sha256:
        try:
            with tempfile.NamedTemporaryFile(prefix='otl-fixed-frame-',suffix='.elf') as f:
                f.write(image.data);f.flush()
                result=subprocess.run(['readelf','--debug-dump=frames-interp',f.name],
                                      text=True,capture_output=True,timeout=30,check=True)
        except (OSError,ValueError,subprocess.SubprocessError):return None
        cached=(image.sha256,result.stdout);side._saved_argument_cfi=cached
    return parse_cfi(cached[1],info['start'],info['start']+info['size'])


def span_rules(table, begin, end, sp, saved):
    """Bind CFA/RA and actual old-register slots throughout an instruction.

    sp/slots are entry-RSP-relative offsets from the independently checked body.
    Missing callee-save columns mean the recognized CIE's unchanged ABI state;
    an explicit undefined/expression rule is never treated as preservation.
    """
    if table is None or not table['start']<=begin<end<=table['end']:return None
    before=[row for row in table['rows'] if row[0]<=begin]
    if not before:return None
    relevant=[before[-1]]+[r for r in table['rows'] if begin<r[0]<end]
    expected={'CFA':f'rsp+{8-sp}','ra':'c-8'}
    expected.update({reg:f'c{offset-8}' for reg,offset in saved.items()})
    for _,rules in relevant:
        if any(rules.get(reg)!=value for reg,value in expected.items()):return None
        if any(reg in rules and rules[reg] not in ('s',) for reg in REGS-set(saved)):
            return None
    return {'span':[begin,end],'sp':sp,'saved':dict(saved),'rules':expected,
            'cie':table['cie']}


def overlaps(offset, width, regions):
    return any(offset<end and begin<offset+width for begin,end in regions)


def local_access(offset, width, sp, slots):
    """An allocated local region, never RA, a private save, or red-zone guess."""
    return (0<width<=16 and sp<=offset and offset+width<=0
            and not overlaps(offset,width,[(slot,slot+8) for slot in slots]))
