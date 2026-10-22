"""Conditional, original-body null-field cleanup certificates.

This is a use-site fact, never an unconditional callee whitelist. A fresh
full-width zero-test dominates the operand/call, and closed post-test operations
preserve the private object. The valid Ogre SharedPtr owner-count allocation is
disjoint from its fields/private frame; it may be nonnull even with null pRep.
"""
import re
from objdiff_literal_flow import JUMPS
from objdiff_saved_argument import Engine, State, ROOT, POISON, UNINITIALIZED, VOLATILE, const, values, split, require, Reject
import objdiff_literal_frames as frames


FALLTHROUGH_OPS={'mov','movq','movl','movw','movb','movabs','movslq','movzbl','movzwl',
              'movss','movsd','movaps','movups','movdqa','movdqu','lea','push','pop',
              'add','addl','sub','subl','and','or','xor','shl','shr','sar','lock xadd',
              'test','testl','testq','cmp','cmpl','cmpq','setne','sete','inc','dec','neg','not',
              'xorps','pxor','xchg'}


def stack_effect(side,op,args):
    """Closed stack-register writer grammar, also checked off the guard path."""
    require(op in FALLTHROUGH_OPS or op in JUMPS or op in ('call','callq','ret','retq','repz ret','repz retq')
            or side.padding(op,args),'unsupported caller control/effect opcode')
    if op in ('ret','retq','repz ret','repz retq'):require(not args,'unsupported caller return form')
    if op in ('push','pop'):
        r=side.register(args)
        require(r and r[1]==64 and r[0]!='sp','unsupported caller stack operand')
        return -8 if op=='push' else 8
    parts=split(args);dst=side.register(parts[-1]) if parts else None
    if op in ('xchg','lock xadd'):
        require(not any(side.register(p) and side.register(p)[0]=='sp' for p in parts),
                'implicit caller stack exchange')
    if dst and dst[0]=='sp' and op not in ('test','testl','testq','cmp','cmpl','cmpq'):
        require(len(parts)==2 and dst[1]==64 and op in ('add','sub')
                and re.fullmatch(r'\$0x[0-9a-f]+',parts[0]),'unsupported caller stack write')
        n=int(parts[0][1:],16);require(n%8==0 and n<=256,'unsupported caller frame adjustment')
        return n if op=='add' else -n
    return 0


def graph(side, rows, start, eh):
    positions={pc:i for i,(pc,_,_) in enumerate(rows)};edges={pc:set() for pc,_,_ in rows}
    # Dominance is only meaningful with complete successor coverage, including
    # paths not retained by the later guard proof. Never infer fallthrough for
    # an unknown opcode (LOOP/XBEGIN/prefixed transfers can bypass the guard).
    for i,(pc,op,args) in enumerate(rows):
        stack_effect(side,op,args)
        after=rows[i+1][0] if i+1<len(rows) else None
        if op in ('ret','retq','repz ret','repz retq'):continue
        if op.startswith('j'):
            require(op in JUMPS,'unsupported caller branch')
            target=side.direct_target(args);require(target in positions,'outside/indirect caller branch')
            edges[pc].add(target)
            if op=='jmp':continue
        if op in ('call','callq'):
            target=side.direct_target(args);name=side.image.plt.get(target,'').split('@')[0]
            if name=='_Unwind_Resume':continue
            hits=[row for row in eh['rows'] if row[0]<=pc-start<row[0]+row[1]]
            require(len(hits)<=1,'overlapping caller EH')
            for _,_,pad,_ in hits:
                if pad:
                    require(start+pad in positions,'bad caller EH target');edges[pc].add(start+pad)
            if name in ('__cxa_throw','__cxa_rethrow'):continue
        require(after is not None,'caller falls outside body');edges[pc].add(after)
    return edges


def reach(edges, entry, omit=None):
    pending=[entry];seen=set()
    while pending:
        pc=pending.pop()
        if pc in seen:continue
        seen.add(pc);pending.extend(q for q in edges.get(pc,()) if (pc,q)!=omit)
    return seen


def prologue(side,rows):
    """Only fixed pushes/subtraction and entry object-register copies."""
    sp=0;saved={};roots={'di','si'};definitions={}
    for pc,op,args in rows:
        if op=='push':
            reg=side.register(args);require(reg and reg[1]==64 and reg[0] in {'b','bp','12','13','14','15'},'unsupported caller save')
            sp-=8;saved[args[1:]]=sp
        elif op=='sub' and re.fullmatch(r'\$0x[0-9a-f]+,%rsp',args):
            sp-=int(args.split(',')[0][1:],16);require(-256<=sp<0,'caller frame bound')
            return sp,saved,roots,definitions
        elif op=='mov':
            src,dst=split(args);a=side.register(src);b=side.register(dst)
            require(a and b and a[1]==b[1]==64 and a[0] in roots,'unsupported caller entry copy')
            roots.add(b[0]);definitions[b[0]]=pc
        else:raise Reject('unsupported caller frame prologue')
    raise Reject('missing allocated caller frame')


def stable_roots(side,rows,edges,guard,roots,definitions):
    reverse={pc:set() for pc in edges}
    for pc,targets in edges.items():
        for q in targets:reverse[q].add(pc)
    ancestors=reach(reverse,guard)&reach(edges,rows[0][0]);stable=set(roots)-VOLATILE
    for pc,op,args in rows:
        if pc not in ancestors or op in ('push','call','callq') or op.startswith('j') or side.padding(op,args):continue
        operands=split(args)
        dest=side.register(operands[-1]) if operands else None
        writes=[]
        if op=='pop' or op in ('mov','movq','movl','movb','movw','movabs','lea','add','addl','sub','subl','xor','or','and','shl','shr','sar'):
            if dest:writes.append(dest[0])
        elif op in ('xchg','lock xadd'):
            writes.extend(side.register(x)[0] for x in re.findall(r'%[a-z0-9]+',args) if side.register(x))
        elif op not in ('test','cmp'):
            require(op in ('movslq','movzbl','movzwl','movss','movsd','movaps','movups','movdqa','movdqu','xorps','pxor','sete','setne','inc','dec','neg','not'),f'unknown preguard implicit effect: {op} {args}')
            if dest:writes.append(dest[0])
        for reg in writes:
            if definitions.get(reg)!=pc:stable.discard(reg)
    return stable


def frame_at(side,rows,edges,target):
    reverse={pc:set() for pc in edges}
    for pc,targets in edges.items():
        for q in targets:reverse[q].add(pc)
    ancestors=reach(reverse,target);positions={r[0]:i for i,r in enumerate(rows)}
    pending=[(rows[0][0],0)];seen={}
    while pending:
        pc,sp=pending.pop()
        if pc in seen:require(seen[pc]==sp,'inconsistent caller stack merge');continue
        seen[pc]=sp;_,op,args=rows[positions[pc]]
        sp+=stack_effect(side,op,args)
        require(-256<=sp<=0,'caller stack range')
        pending.extend((q,sp) for q in edges[pc]&ancestors)
    require(target in seen,'unreachable frame fact');return seen[target]


def destroyed_null(side,target):
    """Exact small owner-count D1 grammar; conditional destroy CFG is separate."""
    info=side._callee_body(side.image,target);require(info,'missing original SharedPtr body')
    require(set(info['names'])&{'_ZN4Ogre9SharedPtrINS_10DataStreamEED1Ev','_ZN4Ogre9SharedPtrINS_10DataStreamEED2Ev'},'missing original SharedPtr type identity')
    rows=[r for r in info['rows'] if not side.padding(r[1],r[2])]
    require(len(rows)==13,'unsupported owner-count destructor shape')
    exact={0:('mov','0x10(%rdi),%rax'),2:('test','%rax,%rax'),4:('mov','(%rax),%edx'),
           5:('sub','$0x1,%edx'),6:('test','%edx,%edx'),7:('mov','%edx,(%rax)'),
           9:('mov','(%rdi),%rax'),10:('mov','0x10(%rax),%rax'),11:('jmp','*%rax')}
    require(all(tuple(rows[i][1:])==v for i,v in exact.items()),'changed owner-count effects')
    require(rows[3][1]=='je' and rows[8][1]=='jne' and rows[12][1] in ('ret','retq','repz ret','repz retq') and not rows[12][2],'changed owner-count exits')
    require(all(side.direct_target(rows[i][2])==rows[12][0] for i in (3,8)),'changed owner-count edges')
    m=re.fullmatch(r'\$0x([0-9a-f]+),\(%rdi\)',rows[1][2]);require(rows[1][1]=='movq' and m,'missing exact vptr store')
    table=int(m[1],16);sec=side.image.section_at(table)
    require(sec and sec.flags&2 and not sec.flags&1 and table+24<=sec.addr+sec.size,'mutable/invalid vtable')
    require(any(x.name=='_ZTVN4Ogre9SharedPtrINS_10DataStreamEEE' and x.value+16==table and x.size>=40 for x in side.image.symbols),'missing original typed vtable identity')
    callee=int.from_bytes(side.image.read(table+16,8),'little')
    eh=side._literal_eh(info['rows'],target,target+info['size']);require(eh is not None and not eh['rows'],'unsupported destructor EH')
    cfi=frames.cfi(side,info);require(frames.span_rules(cfi,rows[11][0],rows[12][0],0,{}),'destructor tail frame mismatch')
    proof=destroy_cfg(side,callee)
    return {'kind':'conditional-original-null-SharedPtr-cleanup-v1','body_sha256':info['body_sha256'],
            'target':target,'vtable':table,'vtable_slot':table+16,'destroy':proof,
            'premise':'valid Ogre SharedPtr; distinct unsigned-int owner-count allocation; count may be nonnull; pRep==0',
            'abi_support':{'header':'Ogre 1.6.5 OgreSharedPtr.h','sha256':'494536e944f2e02587ce3c41d67b2b0afe52045a5bfc0cfa4f9fde982399382f','role':'public ABI/model support, not original game source'}}


def destroy_cfg(side,target):
    info=side._callee_body(side.image,target);require(info and len(info['rows'])<=64,'missing bounded destroy body')
    require('_ZN4Ogre9SharedPtrINS_10DataStreamEE7destroyEv' in info['names'],'missing original destroy type identity')
    rows=info['rows'];positions={r[0]:i for i,r in enumerate(rows)}
    eh=side._literal_eh(rows,target,target+info['size']);require(eh is not None and not eh['rows'],'unsupported destroy EH')
    table=frames.cfi(side,info);require(table,'missing destroy CFI')
    pending=[(0,{'di':'receiver','b':'old-b'},None,0)];seen=set();calls=[];exits=0
    while pending:
        i,regs,zf,sp=pending.pop();key=(i,tuple(sorted(regs.items())),zf,sp)
        if key in seen:continue
        require(len(seen)<256 and 0<=i<len(rows),'destroy CFG bound');seen.add(key)
        pc,op,args=rows[i];after=rows[i+1][0] if i+1<len(rows) else target+info['size']
        if side.padding(op,args):pending.append((i+1,regs,zf,sp));continue
        if op=='push' and args=='%rbx':require(sp==0 and regs.get('b')=='old-b','bad destroy save');sp=-8
        elif op=='pop' and args=='%rbx':require(sp==-8,'bad destroy restore');sp=0;regs['b']='old-b'
        elif op=='mov':
            operands=split(args);require(len(operands)==2,'bad destroy move');src,dst=operands;r=side.register(dst)
            require(r and r[0] in {'a','di','b'},'unsupported destroy destination/stack effect')
            source=side.register(src)
            if source:
                require(source[1]==r[1]==64 and regs.get(source[0])=='receiver','unsupported destroy copy');regs[r[0]]='receiver'
            else:
                m=re.fullmatch(r'0x(8|10|18)\((%[a-z0-9]+)\)',src);base=side.register(m[2]) if m else None
                require(m and base and base[1]==64 and regs.get(base[0])=='receiver','unproved destroy field')
                require(r[1]==(32 if m[1]=='18' else 64),'partial destroy pointer field')
                regs[r[0]]={'8':'zero','10':'count','18':'method'}[m[1]]
        elif op in ('test','cmp'):
            src,dst=split(args);r=side.register(dst);require(r and r[0]!='si','destroy comparison observes RSI')
            if op=='test':require(src==dst,'unsupported destroy test');zf=True if regs.get(r[0])=='zero' else None
            else:require(src in ('$0x1','$0x2') and r[1]==32,'unsupported destroy comparison');zf=None
        elif op in ('je','jne','jmp') and side.direct_target(args) in positions:
            dest=positions[side.direct_target(args)]
            if op=='jmp':pending.append((dest,dict(regs),zf,sp));continue
            taken=zf if op=='je' else (not zf if zf is not None else None)
            if taken is not False:pending.append((dest,dict(regs),zf,sp))
            if taken is not True:pending.append((i+1,regs,zf,sp))
            continue
        elif op in ('call','callq','jmp'):
            callee=side.direct_target(args);name=side.image.plt.get(callee,'').split('@')[0]
            require(name=='_ZN4Ogre12NedAllocImpl12deallocBytesEPv' and regs.get('di') in ('zero','count'),'unproved destroy callback/deallocation')
            proof=side._nonobserving_callee(side.image,callee);require(proof,'missing pinned deallocation proof')
            if op!='jmp':require(frames.span_rules(table,pc,after,sp,{'rbx':-8} if sp==-8 else {}),'destroy call CFI mismatch')
            calls.append({'pc':pc,'argument':regs['di'],'proof':proof})
            if op=='jmp':require(sp==0 and regs.get('b')=='old-b','unbalanced destroy tail');exits+=1;continue
            regs={r:v for r,v in regs.items() if r not in VOLATILE};zf=None
        else:raise Reject('unsupported reachable null destroy effect')
        pending.append((i+1,regs,zf,sp))
    require(exits,'missing destroy terminal')
    return {'start':target,'body_sha256':info['body_sha256'],'visited':sorted({rows[x[0]][0] for x in seen}),'calls':calls,'null_field':8}


def cleanup_shape(side,rows,entry,sp,table,saved,eh,start):
    positions={r[0]:i for i,r in enumerate(rows)};require(entry in positions,'bad outer cleanup')
    st=State({r:POISON for r in VOLATILE},sp=sp);st.regs['a']=ROOT
    engine=Engine(side);i=positions[entry];seen=set();conditional=[];calls=[]
    while i not in seen:
        seen.add(i);require(0<=i<len(rows),'cleanup escape');pc,op,args=rows[i]
        after=rows[i+1][0] if i+1<len(rows) else table['end']
        if op=='jmp':
            dest=side.direct_target(args);require(dest in positions,'bad cleanup branch');i=positions[dest];continue
        if op in ('call','callq'):
            dest=side.direct_target(args);name=side.image.plt.get(dest,'').split('@')[0]
            require(frames.span_rules(table,pc,after,sp,saved),'outer cleanup frame mismatch')
            require(not any(pad for begin,n,pad,_ in eh['rows'] if begin<=pc-start<begin+n),'nested outer cleanup unsupported')
            if name=='_Unwind_Resume':
                require(st.regs.get('di')==ROOT,'missing exception object')
                require(len(conditional)==1,'missing/ambiguous conditional cleanup')
                return conditional[0],calls
            proof=side._nonobserving_callee(side.image,dest)
            require(proof is None or conditional,'unclosed call before null cleanup')
            if proof is None:
                receiver=st.regs.get('di');require(receiver and receiver[0]=='frame','cleanup receiver is not private object')
                conditional.append({'pc':pc,'target':dest,'receiver':receiver[1]})
            calls.append({'pc':pc,'proof':proof})
            for reg in VOLATILE:st.regs[reg]=POISON
        else:
            require(side._literal_independent_instruction(op,args),'cleanup observes RSI/implicit state')
            operands=split(args)
            require(op in ('mov','lea') and len(operands)==2 and side.register(operands[1]),'cleanup memory write/unsupported mutation')
            engine.effect(st,op,args,{})
            require(st.sp==sp and not st.direct_root_writes,'unexpected cleanup frame/external write')
        i+=1
    raise Reject('cyclic outer cleanup')


def preserve_prefix(side,engine,rows,chain,sp,saved,roots,guard_reg,receiver,table,call):
    st=State({r:POISON for r in VOLATILE},sp=sp);st.regs.update({r:ROOT for r in roots});st.regs[guard_reg]=const([0])
    calls=[];protected=[(receiver,receiver+32)]
    def local(v,n=8):
        require(v and v[0]=='frame' and frames.local_access(v[1],n,sp,list(saved.values())),'unbounded caller argument')
        require(not frames.overlaps(v[1],n,protected),'caller argument overlaps protected receiver')
    for i in chain:
        pc,op,args=rows[i];after=rows[i+1][0] if i+1<len(rows) else table['end']
        if op in ('call','callq'):
            target=side.direct_target(args);require(target is not None,'unknown postguard call')
            require(frames.span_rules(table,pc,after,sp,saved),'postguard call CFI mismatch')
            name=side.image.plt.get(target,'').split('@')[0]
            if pc==call or not name:
                destination=st.regs.get('di');local(destination)
                require(st.regs.get('si')==ROOT,'unproved caller input source')
                value=engine.read(st,f'{hex(destination[1]-sp)}(%rsp)',8,allow_uninitialized=True)
                incoming=frozenset({'d'}) if pc==call else frozenset()
                proof=engine.run(target,incoming,wrapper=pc==call,arguments={'si':ROOT},bindings={'di':(8,value)})
                require(proof and not proof['direct_root_writes'],'unclosed original write footprint')
                require(set(proof['argument_writes'])<={'di'},'unexpected output binding')
                if pc==call:
                    require(value!=UNINITIALIZED and not proof['normal_aliases'] and set(proof['exception_aliases'])<={'si'},'changed wrapper continuation')
                    calls.append({'pc':pc,'output':[destination[1],8],'proof':proof});return calls
                if 'di' in proof['argument_writes']:
                    engine.write(st,f'{hex(destination[1]-sp)}(%rsp)',8,proof['argument_writes']['di'])
                for reg in VOLATILE:st.regs[reg]=POISON
                if not proof['returns_indeterminate']:st.regs['a']=None
                if proof['returns_object']:st.regs['a']=ROOT
                if proof['return_argument'] is not None:
                    require(proof['return_argument']=='di','unexpected returned binding');st.regs['a']=destination
            else:
                from objdiff_saved_argument import IMPORTS, COPY, ASSIGN, DTORS
                require(name in IMPORTS,'unknown postguard import')
                for reg in IMPORTS[name][0]:
                    value=st.regs.get(reg)
                    if value and value[0] in ('frame','argument'):
                        require(value[0]=='frame' and (reg=='di' or name in (COPY,ASSIGN) and reg=='si'),'unbounded typed frame exposure')
                        local(value)
                proof=engine.standard(st,name)
            calls.append({'pc':pc,'proof':proof})
        elif op=='jmp':continue
        else:
            operands=split(args)
            if len(operands)==2 and not side.register(operands[1]) and not op in ('test','cmp'):
                size={'movq':8,'movl':4,'movw':2,'movb':1}.get(op)
                src=side.register(operands[0]);size=size or (src[1]//8 if src else None)
                require(size,'unknown postguard write width')
                address=engine.address(st,operands[1],size)
                require(address[0]=='frame' and not frames.overlaps(address[1],size,protected),'postguard write escapes/overlaps receiver')
            engine.effect(st,op,args,{})
            require(st.sp==sp and not st.direct_root_writes,'postguard frame/external write')
    raise Reject('missing wrapper call')


def certify(side,rows,k,call_index,start,end,eh,pad,engine):
    """No shared cache: the guard fact belongs only to this original operand."""
    try:
        info=side._callee_body(side.image,start,max_bytes=4096)
        require(info and info['size']==end-start and info['rows']==rows,'caller body snapshot mismatch')
        require(k<call_index and re.fullmatch(r'\$0x[0-9a-f]+,%(?:edx|rdx)',rows[k][2]) and rows[k][1] in ('mov','movl','movq','movabs'),'missing original selected operand')
        require(all(side._literal_independent_instruction(op,args,blocked={'d'}) for _,op,args in rows[k+1:call_index]),'selected argument modified/escaped')
        edges=graph(side,rows,start,eh);positions={r[0]:i for i,r in enumerate(rows)}
        table=frames.cfi(side,info);require(table,'missing caller CFI')
        sp,saved,roots,definitions=prologue(side,rows)
        cleanup,calls=cleanup_shape(side,rows,pad,sp,table,saved,eh,start)
        receiver=cleanup['receiver'];require(sp<=receiver and receiver+32<=0 and not frames.overlaps(receiver,32,[(p,p+8) for p in saved.values()]),'invalid SharedPtr region')
        predecessors={pc:set() for pc in edges}
        for pc,targets in edges.items():
            for dest in targets:predecessors[dest].add(pc)
        # Entry-root copies and saved registers are entry facts, not reusable
        # definitions after a balanced backedge into the prologue.
        for j,(pc,op,args) in enumerate(rows):
            require(predecessors[pc]==({rows[j-1][0]} if j else set()),'caller prologue reentry/bypass')
            if op=='sub' and re.fullmatch(r'\$0x[0-9a-f]+,%rsp',args):break
        load=rows[k][0];call=rows[call_index][0];candidates=[]
        for i in range(len(rows)-2):
            pc,op,args=rows[i];m=re.fullmatch(r'0x([0-9a-f]+)\(%rsp\),(%[a-z0-9]+)',args)
            if op!='mov' or not m or sp+int(m[1],16)!=receiver+8:continue
            reg=side.register(m[2])
            if not reg or reg[1]!=64 or tuple(rows[i+1][1:])!=('test',m[2]+','+m[2]) or rows[i+2][1]!='je':continue
            branch=rows[i+2][0];zero=side.direct_target(rows[i+2][2])
            if zero not in positions or predecessors[rows[i+1][0]]!={pc} or predecessors[branch]!={rows[i+1][0]}:continue
            if load not in reach(edges,start) or call not in reach(edges,start):continue
            if load in reach(edges,start,(branch,zero)) or call in reach(edges,start,(branch,zero)):continue
            candidates.append((i,branch,zero,reg[0]))
        require(len(candidates)==1,'missing/ambiguous dominating full-width null edge')
        guard,branch,zero,reg=candidates[0]
        require(frame_at(side,rows,edges,rows[guard][0])==sp and frame_at(side,rows,edges,call)==sp,'changed caller frame base')
        require(frames.span_rules(table,rows[guard][0],rows[guard+3][0],sp,saved),'guard frame mismatch')
        # All paths which can reach this call after the guard must form the
        # supported linear closure. Earlier throwing paths may terminate.
        prefix_edges={pc:(set() if pc==call else targets) for pc,targets in edges.items()}
        reverse={pc:set() for pc in edges}
        for pc,targets in prefix_edges.items():
            for dest in targets:reverse[dest].add(pc)
        relevant=reach(prefix_edges,zero)&reach(reverse,call);require(call in relevant,'zero edge misses call')
        chain=[];pc=zero
        while pc!=call:
            require(pc not in [rows[i][0] for i in chain],'cyclic postguard prefix');chain.append(positions[pc])
            successors=edges[pc]&relevant;require(len(successors)==1,'branching/unproved postguard prefix')
            successor=next(iter(successors));j=positions[pc]
            if rows[j][1] in ('call','callq'):
                require(j+1<len(rows) and successor==rows[j+1][0],'postguard closure requires normal return')
                require(not any(pad and begin<=pc-start<begin+count and start+pad in relevant
                                for begin,count,pad,_ in eh['rows']),'postguard EH reentry is unsupported')
            pc=successor
        chain.append(call_index)
        stable=stable_roots(side,rows,edges,rows[guard][0],roots,definitions)
        closed=preserve_prefix(side,engine,rows,chain,sp,saved,stable,reg,receiver,table,call)
        conditional=destroyed_null(side,cleanup['target'])
        return {'entry':pad,'kind':'original-dominating-null-field-cleanup-v1','caller_sha256':info['body_sha256'],
                'image_sha256':side.image.sha256,'guard':[rows[guard][0],branch,zero],
                'receiver':[receiver,32],'null_field':[receiver+8,8],'call':call,
                'postguard_calls':closed,'cleanup_calls':calls,'conditional':conditional,
                'premise':'valid separate typed objects and allocator storage; no interposition/asynchronous mutation; closed effects after fresh guard'}
    except (Reject,KeyError,IndexError,TypeError,ValueError) as error:
        side._null_field_error=str(error);return None
