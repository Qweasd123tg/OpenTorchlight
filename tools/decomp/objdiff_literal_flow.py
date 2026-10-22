"""Bounded original default-copy argument flow, never candidate-derived typing.

This is a structural grammar, not a general alias engine. The admitted wrapper
saves one RDX source in RBX, performs a non-observing lookup, then either drops
that source or copies its complete wide sequence into an independent object.
"""
import re
import hashlib
import subprocess
import tempfile
import objdiff_eh

WCSLEN = 'wcslen'
WIDE_ASSIGN = '_ZNSbIwSt11char_traitsIwESaIwEE6assignEPKwm'
JUMPS = {'jmp','je','jne','ja','jae','jb','jbe','jg','jge','jl','jle','js','jns'}
SAVED = {'b','bp','12','13','14','15'}


def registers(side, args):
    return {r[0] for token in re.findall(r'%\w+', args)
            if (r := side.register(token)) is not None}


def kill(side, op, args, live):
    source, comma, dest = args.rpartition(',')
    reg = side.register(dest)
    if not comma or reg is None or reg[1] not in (32,64):
        return None
    if op in ('mov','movl','movq','movabs','lea') and not registers(side,source) & live:
        return reg[0]
    if op in ('xor','xorl','xorq') and source == dest:
        return reg[0]
    return None


def body(side, target):
    if target is None or target in side.image.plt or not hasattr(side.image,'symbols'):
        return None
    result = side._callee_body(side.image,target)
    if result is None:
        return None
    frames = getattr(side,'frames',None)
    if frames is None or frames.error:
        return None
    covered = list(frames._overlapping(result['start'],result['size'],None))
    if (len(covered) != 1 or covered[0][1] > result['start']
            or covered[0][2] < result['start'] + result['size']
            or frames.reason(result['start'],result['size']) is not None
            or covered[0][4] not in (None,'__gxx_personality_v0')):
        return None
    result = dict(result)
    result['frame'] = list(covered[0])
    return result


def object_origins(side, op, args, roots):
    """Roots are pre-existing valid object graphs, disjoint from fresh saves.

    This is an explicit well-defined C++/ABI memory premise, not unrestricted
    numeric-pointer alias analysis. Never invent a root for inherited RBP/SP or
    for an unknown call return. Only the small actual base+offset forms qualify.
    """
    if ':' in args or '#' in args or '*' in args:
        return None
    if op not in JUMPS and op not in ('call','callq','ret','retq','repz ret','repz retq'):
        for operand in re.split(r',(?=[^)]*(?:\(|$))',args):
            if (operand and not operand.startswith(('%','$')) and '(' not in operand):
                return None  # no unproven absolute/private address bases
    bases=[]
    for address in re.findall(r"\(([^()]*)\)",args):
        reg=side.register(address)
        if reg is None or reg[1]!=64 or reg[0] not in roots:
            return None
        bases.append(reg[0])
    source,comma,dest=args.rpartition(',')
    target=side.register(dest)
    if not comma or target is None or op in ('cmp','cmpl','cmpq','test','testl','testq'):
        return roots
    family,width=target; out=set(roots);out.discard(family)
    src=side.register(source)
    immediate=re.fullmatch(r'\$0x([0-9a-f]+)',source)
    static=False
    if immediate:
        value=int(immediate[1],16);section=side.image.section_at(value)
        static=value==0 or (section is not None and getattr(section,'flags',0)&2)
    if op in ('xor','xorl','xorq') and source==dest and width in (32,64):
        out.add(family)  # null, not a private-frame alias
    elif op in ('mov','movl','movq','movabs'):
        if ((static and width in (32,64))
                or (width==64 and ((src and src[1]==64 and src[0] in roots) or bases))):
            out.add(family)
    elif op=='lea' and width==64 and bases:
        out.add(family)
    elif op in ('add','addq') and width==64:
        if bases or (src and src[0] in roots) or (immediate and family in roots):
            out.add(family)
    elif op in ('sub','subq') and width==64 and immediate and family in roots:
        out.add(family)
    return frozenset(out)


def summary(side, target, incoming, depth=0, active=(), closed=False, origins=None):
    """No incoming pointer observation; private balanced callee-save slots only.

    Unknown calls and frame-address exposure cannot cross a live private save.
    Recursion is bounded and rejected on call cycles; finite CFG state traversal
    proves nonobservation, not termination. A kill may stop tracking only when no
    private alias survives and a caller did not require a closed call footprint.
    """
    if target is None or depth > 3 or target in active:
        return None
    origins=frozenset({'di','si'} if origins is None else origins)
    name = side.image.plt.get(target,'').split('@')[0]
    # Explicit pure/standard ABI inputs, not a mangled-signature inference.
    inputs = {'wmemcmp': {'di','si','d'}}
    if name:
        if name not in inputs or set(incoming) & inputs[name] or not {'di','si'} <= origins:
            return None
        return {'kind':'explicit-import-abi-nonobserving','callee':name,
                'incoming':sorted(incoming),'outgoing':sorted(incoming),'nonthrowing':True,
                'outgoing_roots':sorted(origins & SAVED)}
    info = body(side,target)
    if info is None:
        return None
    rows = info['rows']; positions = {r[0]: i for i,r in enumerate(rows)}
    if len(rows) > 256 or len(positions) != len(rows):
        return None
    initial = frozenset(incoming)
    pending = [(0,initial,(),origins)]; seen = set(); outputs = set(); output_roots=None; edges = []; kills = []
    while pending:
        i, live, stack, roots = pending.pop()
        state = (i,live,stack,roots)
        if state in seen:
            continue
        if len(seen) >= 1024 or not 0 <= i < len(rows):
            return None
        seen.add(state)
        pc,op,args = rows[i]
        private = any(saved for _,saved,_ in stack)
        if not live and not private and not closed and not (initial & SAVED):
            continue
        if op in ('push','pop'):
            reg = side.register(args)
            if reg is None or reg[1] != 64 or reg[0] not in SAVED:
                return None
            family = reg[0]
            if op == 'push':
                if len(stack) >= 8:
                    return None
                stack = stack + ((family,family in live,family in roots),)
            else:
                if not stack or stack[-1][0] != family:
                    return None
                restored,was_root = stack[-1][1:]; stack = stack[:-1]
                live = (live | {family}) if restored else (live - {family})
                roots = (roots | {family}) if was_root else (roots - {family})
            pending.append((i+1,frozenset(live),stack,frozenset(roots))); continue
        # Never expose a private save through an address or explicit stack load.
        # Constant stack adjustment before a kill is harmless only without saves.
        if 'sp' in registers(side,args):
            if not (not closed and not private and op in ('sub','add')
                    and re.fullmatch(r'\$0x[0-9a-f]+,%rsp',args)):
                return None
        roots=object_origins(side,op,args,roots)
        if roots is None:
            return None
        overwritten = kill(side,op,args,live)
        if overwritten is not None and overwritten in live:
            live = live - {overwritten}; kills.append(pc)
            pending.append((i+1,frozenset(live),stack,frozenset(roots))); continue
        if op in ('ret','retq','repz ret','repz retq') and not args:
            if stack or 'a' in live or not (initial & SAVED) <= live:
                return None
            outputs.update(live)
            output_roots=set(roots) if output_roots is None else output_roots & roots
            continue
        if op in ('call','callq'):
            callee = side.direct_target(args)
            proof = summary(side,callee,live,depth+1,active+(target,),closed or private,roots)
            if proof is None:
                return None
            edges.append({'pc':pc,'proof':proof})
            pending.append((i+1,frozenset(proof['outgoing']),stack,frozenset(proof['outgoing_roots']))); continue
        if op.startswith('j'):
            if op not in JUMPS:
                return None
            dest = side.direct_target(args)
            if dest not in positions:
                return None
            pending.append((positions[dest],live,stack,roots))
            if op != 'jmp':
                pending.append((i+1,live,stack,roots))
            continue
        if not side._literal_independent_instruction(op,args,blocked=live):
            return None
        pending.append((i+1,live,stack,roots))
    return {'kind':'original-register-nonobservation-v1',
            'image_sha256':side.image.sha256,'start':target,'size':info['size'],
            'body_sha256':info['body_sha256'],'frame':info['frame'],
            'incoming':sorted(initial),'outgoing':sorted(outputs),
            'object_roots_premise':sorted(origins),'outgoing_roots':sorted(output_roots or ()),
            'closed_calls':closed,'nonthrowing':closed,'kills':sorted(set(kills)),
            'visited':sorted({rows[s[0]][0] for s in seen}),'calls':edges}


def parse_saved_rbx_cfi(text, start, end, call, after):
    """One recognized table, expected save rule throughout the throwing call."""
    blocks = re.split(r"(?m)(?=^[0-9a-f]+ .* FDE )", text)
    matches=[]
    for block in blocks:
        header=re.match(r"[^\n]* FDE cie=[0-9a-f]+ pc=([0-9a-f]+)\.\.([0-9a-f]+)\n",block)
        if header and int(header[1],16) <= start and end <= int(header[2],16):
            matches.append(block)
    if len(matches) != 1:
        return None
    cie=int(re.search(r'FDE cie=([0-9a-f]+)',matches[0])[1],16)
    cies=[m for m in re.finditer(r'(?m)^([0-9a-f]+) [^\n]* CIE ([^\n]*)$',text)
          if int(m[1],16)==cie]
    if len(cies)!=1 or not re.fullmatch(r'"z(?:P)?R" cf=1 df=-8 ra=16',cies[0][2]):
        return None
    lines=matches[0].splitlines(); columns=lines[1].split() if len(lines)>1 else []
    if columns != ['LOC','CFA','rbx','ra']:
        return None
    table=[]
    for line in lines[2:]:
        if not line.strip():break
        cells=line.split()
        if len(cells)!=4 or not re.fullmatch('[0-9a-f]+',cells[0]):return None
        table.append((int(cells[0],16),*cells[1:]))
    if (not table or table[0][0] != start or not start <= call < after <= end
            or any(a[0]>=b[0] for a,b in zip(table,table[1:]))
            or any(not start <= row[0] < end for row in table)):
        return None
    active=[row for row in table if row[0] <= call]
    if not active or active[-1][1:] != ('rsp+16','c-16','c-8'):
        return None
    if any(call < row[0] < after and row[1:] != ('rsp+16','c-16','c-8') for row in table):
        return None
    return {'kind':'original-cfi-rbx-save-v1','call_span':[call,after],
            'cfa':'rsp+16','rbx':'cfa-16','return_address':'cfa-8',
            'cie':cies[0][2],
            'table_sha256':hashlib.sha256(repr(table).encode()).hexdigest()}


def saved_rbx_cfi(side, info, call, after):
    image=side.image
    if hashlib.sha256(image.data).hexdigest() != image.sha256:
        return None
    cached=getattr(side,'_default_copy_cfi',None)
    if cached is None or cached[0] != image.sha256:
        try:
            with tempfile.NamedTemporaryFile() as snapshot:
                snapshot.write(image.data);snapshot.flush()
                result=subprocess.run(['readelf','--debug-dump=frames-interp',snapshot.name],
                                      capture_output=True,text=True,check=False)
            if result.returncode or result.stderr:
                return None
        except (OSError,ValueError):
            return None
        cached=(image.sha256,result.stdout)
        side._default_copy_cfi=cached
    return parse_saved_rbx_cfi(cached[1],info['start'],info['start']+info['size'],call,after)


def default_copy(side, target):
    """Match all meaningful instructions and edges of one bounded copy wrapper."""
    info = body(side,target)
    if info is None:
        return None
    rows = [r for r in info['rows'] if not side.padding(r[1],r[2])]
    if len(rows) != 18:
        return None
    exact = {0:('push','%rbx'),1:('mov','%rdx,%rbx'),3:('test','%rax,%rax'),
             5:('pop','%rbx'),6:('mov','$0x1,%esi'),7:('mov','%rax,%rdi'),
             9:('mov','%rbx,%rdi'),11:('mov','%rbx,%rsi'),12:('mov','%rax,%rdx'),
             16:('pop','%rbx'),17:('ret','')}
    if any(tuple(rows[i][1:]) != wanted for i,wanted in exact.items()):
        return None
    if rows[4][1] != 'je' or side.direct_target(rows[4][2]) != rows[9][0]:
        return None
    for i in (2,10,14):
        if rows[i][1] not in ('call','callq'):
            return None
    if rows[8][1] != 'jmp':
        return None
    destination = re.fullmatch(r'\$0x([0-9a-f]+),%edi',rows[13][2])
    if rows[13][1] != 'mov' or destination is None:
        return None
    address = int(destination.group(1),16)
    if tuple(rows[15][1:]) != ('mov',f'$0x{address:x},%eax'):
        return None
    section = side.image.section_at(address)
    if (section is None or not section.flags & 1
            or address + 8 > section.addr + section.size):
        return None
    # Destination is a defined independent object, never the raw source pointer.
    objects = [s for s in side.image.symbols if s.defined and s.type == 1
               and s.value == address and s.size >= 8]
    if not objects:
        return None
    names = [side.image.plt.get(side.direct_target(rows[i][2]),'').split('@')[0]
             for i in (10,14)]
    if names != [WCSLEN,WIDE_ASSIGN]:
        return None
    lookup = summary(side,side.direct_target(rows[2][2]),{'d','b'},closed=True)
    tail = summary(side,side.direct_target(rows[8][2]),{'d'})
    if (lookup is None or 'b' not in lookup['outgoing'] or 'a' not in lookup['outgoing_roots']
            or not lookup['nonthrowing'] or tail is None or tail['outgoing']):
        return None
    cfi=saved_rbx_cfi(side,info,rows[14][0],rows[15][0])
    if cfi is None:
        return None
    # Complete body grammar binds the same saved pointer to wcslen and assign,
    # the unchanged length return to RDX, and an independent object to RAX.
    return {'kind':'original-default-wide-copy-v1','image_sha256':side.image.sha256,
            'start':target,'size':info['size'],'body_sha256':info['body_sha256'],
            'frame':info['frame'],'assign_unwind':cfi,'lookup':lookup,'found_tail':tail,
            'copy':{'length_call':rows[10][0],'assign_call':rows[14][0],
                    'contracts':[WCSLEN,WIDE_ASSIGN],'destination':address,
                    'wcslen_nonthrowing':True,'assign_may_throw':True},
            'outgoing_aliases':['si'],'exception_aliases':['si'],
            'callee_save':'balanced-private-rbx','return':'independent-object-reference'}


def wide_literal_use(side,k,insns,start,end):
    if start is None or end is None or not insns or insns[0][0] != start:
        return None
    address,op,args = insns[k]
    match = re.fullmatch(r'\$0x([0-9a-f]+),%(?:edx|rdx)',args)
    if op not in ('mov','movl','movq','movabs') or not match or not start <= address < end:
        return None
    eh = side._literal_eh(insns,start,end)
    if eh is None:
        return None
    for i in range(k+1,len(insns)):
        pc,mnemonic,operands = insns[i]
        if mnemonic in ('call','callq'):
            proof = default_copy(side,side.direct_target(operands))
            if proof is None:
                return None
            break
        if not side._literal_independent_instruction(mnemonic,operands,blocked={'d'}):
            return None
    else:
        return None
    if i+1 >= len(insns):
        return None
    normal = side._rsi_normal_dead(insns,insns[i+1][0],start,eh)
    if normal is None:
        return None
    cleanups=[]
    for begin,count,pad,_ in eh['rows']:
        if begin <= pc-start < begin+count and pad:
            cleanup = side._rsi_cleanup_dead(insns,start+pad,start,eh)
            if cleanup is None:
                return None
            cleanups.append(cleanup)
    return {'load':address,'call':pc,'argument':'rdx','width':4,
            'literal':int(match.group(1),16),'model':'original-default-wide-copy-v1',
            'consumer':proof,'normal':normal,'cleanup':cleanups,'eh_kind':eh['kind']}
