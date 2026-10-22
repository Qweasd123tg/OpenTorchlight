"""Bounded saved-argument effect/frame certificates, original instructions only.

Valid pre-existing C++ object graphs cannot alias newly allocated private saves.
Only explicit fixed local regions may be exposed as typed call arguments. This is
not an unrestricted machine-state alias theorem or a general x86 interpreter.
Every local content read requires full initialization. A call invalidates retired
caller cells below current SP: child/opaque-import private spills are not assumed
absent, and their abandoned bytes cannot be recovered by stack introspection.
"""
import re
import hashlib
import struct
from dataclasses import dataclass, field
import objdiff_literal_frames as frames
from objdiff_literal_flow import JUMPS, SAVED, registers

RAW=('raw',)
UNINITIALIZED=('uninitialized',)
POISON=('undefined-abi-value',)
VOLATILE={'a','c','d','si','di','8','9','10','11'}
ROOT=('object',None)
STRING_STORAGE=('string-storage',0)
def storage(value):return bool(value and value[0]=='string-storage')
def storage_offset(value,delta):
    offset=None if value[1] is None else value[1]+delta
    return ('string-storage',offset if offset is not None and -32<=offset<=0 else None)

def root(value):return bool(value and value[0] in ('object','string-storage'))
def private(value):return bool(value and value[0] in ('frame','argument'))
CTOR='_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_'
DESTROY='_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_'
REPLACE='_ZNSs7replaceEmmPKcm'
COPY='_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_'
ASSIGN='_ZNSbIwSt11char_traitsIwESaIwEE6assignERKS2_'
FIND='_ZNKSbIwSt11char_traitsIwESaIwEE4findEPKwmm'
WREPLACE='_ZNSbIwSt11char_traitsIwESaIwEE7replaceEmmPKwm'
OUTPUTS={CTOR,COPY,ASSIGN,REPLACE,WREPLACE}
DTORS={'_ZNSsD1Ev','_ZNSbIwSt11char_traitsIwESaIwEED1Ev'}
IMPORTS={CTOR:({'di','si','d'},True), DESTROY:({'di','si'},False),
         REPLACE:({'di','si','d','c','8'},True), WREPLACE:({'di','si','d','c','8'},True),
         COPY:({'di','si'},True), ASSIGN:({'di','si'},True),
         FIND:({'di','si','d','c'},False), 'wcslen':({'di'},False),
         **{name:({'di'},False) for name in DTORS},'_ZdlPv':({'di'},False)}

class Reject(Exception):pass

def require(condition,reason):
    if not condition:raise Reject(reason)

def const(values):
    values=tuple(sorted(set(values)))
    return ('constant',values) if len(values)<=8 else None

def values(v):return v[1] if v and v[0]=='constant' else None

def split(args):return re.split(r',(?=[^)]*(?:\(|$))',args)

def width(side,operand):
    r=side.register(operand)
    return r[1]//8 if r else None

@dataclass
class State:
    regs:dict=field(default_factory=dict)
    cells:dict=field(default_factory=dict)  # offset -> (width,value,saved register)
    sp:int=0
    copied:bool=False
    unwind:bool=False
    writes:frozenset=frozenset()
    ids:dict=field(default_factory=dict)
    cell_ids:dict=field(default_factory=dict)
    arguments:dict=field(default_factory=dict)  # reg -> (8-byte bound, abstract cell value)
    argument_writes:frozenset=frozenset()
    direct_root_writes:bool=False

    def clone(self):return State(dict(self.regs),dict(self.cells),self.sp,self.copied,self.unwind,self.writes,dict(self.ids),dict(self.cell_ids),dict(self.arguments),self.argument_writes,self.direct_root_writes)
    def key(self):return (tuple(sorted(self.regs.items())),tuple(sorted(self.cells.items())),self.sp,self.copied,self.unwind,self.writes,tuple(sorted(self.ids.items())),tuple(sorted(self.cell_ids.items())),tuple(sorted(self.arguments.items())),self.argument_writes,self.direct_root_writes)
    def raw(self):return {r for r,v in self.regs.items() if v==RAW}
    def private(self):return any(v==RAW for _,v,_ in self.cells.values())
    def slots(self):return [p for p,(_,_,saved) in self.cells.items() if saved]

class Engine:
    def __init__(self,side):
        self.side=side;self.error=None;self.memo={}

    def mapped(self,address,size):
        s=self.side.image.section_at(address)
        return bool(s and s.flags&2 and address+size<=s.addr+s.size)

    def address(self,st,operand,size,lea=False):
        require(':' not in operand and '*' not in operand,'unsupported address')
        m=re.fullmatch(r'(-?0x[0-9a-f]+)?\((%[a-z0-9]+)(?:,(%[a-z0-9]+),([1248]))?\)',operand)
        if not m:
            require(re.fullmatch('0x[0-9a-f]+',operand),'unsupported address shape')
            a=int(operand,16);require(self.mapped(a,size),'unmapped absolute address')
            return ('static',(a,))
        disp=int(m[1] or '0',16);reg=self.side.register(m[2])
        require(reg and reg[1]==64,'non-64bit address base')
        base=('frame',st.sp) if reg[0]=='sp' else st.regs.get(reg[0])
        require(base!=RAW,'raw pointer address observation')
        require(base!=POISON and not(base and base[0]=='entry'),'undefined ABI address base')
        offsets=(disp,)
        if m[3]:
            index=self.side.register(m[3]);require(index and index[1]==64,'bad index register')
            indexv=st.regs.get(index[0]);require(indexv!=RAW,'raw pointer index')
            require(indexv!=POISON and not(indexv and indexv[0]=='entry'),'undefined ABI address index')
            iv=values(indexv)
            if iv is None:
                require(lea and not private(base) and not private(indexv),'unbounded/private address index');return None
            offsets=tuple(disp+x*int(m[4]) for x in iv)
        if base and base[0]=='argument':
            require(len(offsets)==1,'indexed argument region')
            offset=base[2]+offsets[0];bound=st.arguments[base[1]][0]
            require(0<=offset and offset+(0 if lea else size)<=bound,'argument footprint escape')
            return ('argument',base[1],offset)
        if base and base[0]=='frame':
            require(len(offsets)==1,'indexed local region')
            offset=base[1]+offsets[0]
            if not lea:require(st.sp<=offset and offset+size<=0,'out-of-frame access')
            return ('frame',offset)
        if base and base[0]=='region':
            require(all(abs(x)<=4096 for x in offsets),'unbounded static region offset')
            return base
        if storage(base):
            require(len(offsets)==1 and abs(offsets[0])<=4096,'unbounded string storage offset')
            return storage_offset(base,offsets[0])
        if root(base):
            require(all(abs(x)<=4096 for x in offsets),'unbounded object offset')
            return base if offsets==(0,) else ROOT
        cv=values(base)
        if cv is not None:
            candidates=[b+d for b in cv for d in offsets]
            if all(self.mapped(a,size) for a in candidates):return ('static',tuple(sorted(set(candidates))))
        require(lea,'unproven memory origin')
        return None

    def read(self,st,operand,size,allow_uninitialized=False):
        require(operand not in ('%ah','%bh','%ch','%dh'),'unsupported high-byte register')
        r=self.side.register(operand)
        if r:
            v=('frame',st.sp) if r[0]=='sp' and r[1]==64 else st.regs.get(r[0])
            require(v!=POISON and not(v and v[0]=='entry'),'undefined ABI register read')
            require(v!=RAW or r[1]==64,'partial raw read')
            require(not(v and v[0] in ('frame','argument')) or r[1]==64,'partial private-frame pointer read')
            cv=values(v)
            return const(x&((1<<r[1])-1) for x in cv) if cv is not None else (v if r[1]==64 else None)
        if operand.startswith('$'):
            require(re.fullmatch(r'\$-?0x[0-9a-f]+',operand),'bad immediate')
            return const([int(operand[1:],16)&((1<<(8*size))-1)])
        addr=self.address(st,operand,size)
        if addr[0]=='argument':
            n,v=st.arguments[addr[1]]
            require(v!=UNINITIALIZED or allow_uninitialized,'uninitialized argument read')
            return v if addr[2]==0 and size==n else None
        if addr[0]=='frame':
            p=addr[1];hits=[(q,n,v,saved) for q,(n,v,saved) in st.cells.items()
                           if frames.overlaps(p,size,[(q,q+n)])]
            require(not any(saved for _,_,_,saved in hits),'private save read outside restore')
            require(not any(v==RAW and (p,size)!=(q,n) for q,n,v,_ in hits),'partial stale raw read')
            initialized=all(any(q<=byte<q+n and v!=UNINITIALIZED for q,n,v,_ in hits) for byte in range(p,p+size))
            require(initialized or allow_uninitialized,'uninitialized or partial local read')
            if not initialized:return UNINITIALIZED
            if len(hits)!=1:return None
            q,n,v,_=hits[0]
            if (p,size)==(q,n):return v if size==8 or not (root(v) or (v and v[0]=='frame')) else None
            cv=values(v)
            return const((x>>(8*(p-q)))&((1<<(8*size))-1) for x in cv) if cv is not None and q<=p and p+size<=q+n else None
        if addr[0]=='static':
            if any(self.side.image.section_at(a).flags&1 for a in addr[1]):return None
            return const(int.from_bytes(self.side.image.read(a,size),'little') for a in addr[1])
        return ROOT if root(addr) and not storage(addr) and size==8 else None

    def write(self,st,operand,size,value):
        require(operand not in ('%ah','%bh','%ch','%dh'),'unsupported high-byte register')
        r=self.side.register(operand)
        if r:
            require(r[0]!='sp','unrecognized stack write')
            old=st.regs.get(r[0]);st.ids.pop(r[0],None)
            if r[1]<64 and value and (root(value) or value[0] in ('frame','argument','region')):value=None
            if r[1]<32:
                require(old!=RAW and value!=RAW,'partial raw write')
                require(old!=POISON and not(old and old[0]=='entry'),'partial undefined ABI register write')
                require(not(old and old[0] in ('frame','argument')),'partial private-frame pointer write')
                a,b=values(old),values(value)
                value=const((x&~((1<<r[1])-1))|y for x in a for y in b) if a is not None and b is not None else None
            st.regs[r[0]]=value
            return
        require(value!=RAW,'raw pointer escape')
        require(not (value and value[0] in ('frame','argument')),'frame pointer escape')
        addr=self.address(st,operand,size)
        if addr[0]=='static':require(all(self.side.image.section_at(a).flags&1 for a in addr[1]),'write to immutable table')
        if addr[0]=='region':require(self.side.image.section_at(addr[1]).flags&1,'write to immutable region')
        if addr[0]=='argument':
            bound,old=st.arguments[addr[1]]
            st.arguments[addr[1]]=(bound,value if addr[2]==0 and size==bound else UNINITIALIZED if old==UNINITIALIZED else None)
            st.argument_writes=st.argument_writes|{addr[1]};return
        if root(addr) and not(storage(addr) and addr[1]==-8 and size==4):st.direct_root_writes=True
        if root(addr) and not storage(addr) and addr[1] and (root(value) or (values(value) is not None and all(self.mapped(x,8) for x in values(value)))):
            st.writes=st.writes|{addr[1]}
        if addr[0]=='frame':
            p=addr[1]
            require(frames.local_access(p,size,st.sp,st.slots()),'write to save/RA/outside local region')
            require(not any(v==RAW and frames.overlaps(p,size,[(q,q+n)]) and not (p<=q and q+n<=p+size) for q,(n,v,_) in st.cells.items()),'partial stale raw overwrite')
            st.cells={q:cell for q,cell in st.cells.items() if not frames.overlaps(p,size,[(q,q+cell[0])])}
            st.cells[p]=(size,value,None)

    def save(self,st,reg,offset,entry):
        require(reg in SAVED and -256<=offset<=-8 and offset%8==0,'invalid private save')
        require(st.sp<=offset or (st.sp==0 and offset>=-128),'save outside allocated/red-zone prologue')
        require(not frames.overlaps(offset,8,[(q,q+n) for q,(n,_,saved) in st.cells.items() if saved]),'overlapping private save')
        require(not any(v==RAW and frames.overlaps(offset,8,[(q,q+n)]) and not (offset<=q and q+n<=offset+8) for q,(n,v,_) in st.cells.items()),'partial stale save overwrite')
        st.cells={q:cell for q,cell in st.cells.items() if not frames.overlaps(offset,8,[(q,q+cell[0])])}
        require(st.regs.get(reg)==entry.get(reg) and st.ids.get(reg)==reg,'save is not incoming callee value')
        st.cells[offset]=(8,st.regs.get(reg),reg);st.cell_ids[offset]=st.ids.get(reg)

    def restore(self,st,reg,offset):
        cell=st.cells.get(offset)
        require(cell and cell[0]==8 and cell[2]==reg,'mismatched restore')
        st.regs.pop(reg,None)
        if cell[1] is not None:st.regs[reg]=cell[1]
        st.ids.pop(reg,None)
        if st.cell_ids.get(offset) is not None:st.ids[reg]=st.cell_ids[offset]
        st.cells[offset]=(cell[0],cell[1],None)  # physical bytes survive restore

    def effect(self,st,op,args,entry):
        side=self.side
        require(not re.search(r'%(?:ah|bh|ch|dh)\b',args),'unsupported high-byte register')
        if side.padding(op,args):return
        if op in ('push','pop'):
            r=side.register(args);require(r and r[1]==64 and r[0] in SAVED,'unsupported push/pop')
            if op=='push':st.sp-=8;self.save(st,r[0],st.sp,entry)
            else:self.restore(st,r[0],st.sp);st.sp+=8
            return
        operands=split(args);require(len(operands)==2,'unsupported operand count')
        source,dest=operands;dst=side.register(dest);src=side.register(source)
        if dest=='%rsp':
            require(op in ('add','sub') and re.fullmatch(r'\$0x[0-9a-f]+',source),'variable stack adjustment')
            n=int(source[1:],16);require(n%8==0 and n<=256,'unsupported frame size')
            st.sp+=n if op=='add' else -n
            require(-256<=st.sp<=0,'unbalanced frame range');return
        # Explicit old-register spills/restores, not a general raw-store rule.
        if op in ('mov','movq') and src and src[1]==64 and src[0] in SAVED:
            m=re.fullmatch(r'(-?0x[0-9a-f]+)?\(%rsp\)',dest)
            if m:
                self.save(st,src[0],st.sp+int(m[1] or '0',16),entry);return
        if op in ('mov','movq') and dst and dst[1]==64 and dst[0] in SAVED:
            m=re.fullmatch(r'(-?0x[0-9a-f]+)?\(%rsp\)',source)
            if m and st.sp+int(m[1] or '0',16) in st.slots():
                self.restore(st,dst[0],st.sp+int(m[1] or '0',16));return
        size=width(side,dest) or width(side,source) or {'movq':8,'movl':4,'movb':1,'movw':2}.get(op)
        require(size in (1,2,4,8),'unknown instruction width')
        if op=='lea':
            require(dst and dst[1] in (32,64),'bad lea destination')
            v=self.address(st,source,1,lea=True)
            if v and v[0]=='static':v=const(v[1])
            require(dst[1]==64 or not(v and v[0] in ('frame','argument')),'truncated private-frame address')
            if dst[1]!=64:v=None
            self.write(st,dest,size,v);return
        if op in ('mov','movq','movl','movb','movw','movabs'):
            if src and dst:require(src[1]==dst[1],'invalid register widths')
            identity=st.ids.get(src[0]) if src and src[1]==64 else None
            self.write(st,dest,size,self.read(st,source,size))
            if dst and dst[1]==64 and identity is not None:st.ids[dst[0]]=identity
            return
        if op=='movzwl':
            require(src and src[1]==16 and dst and dst[1]==32,'invalid movzwl')
            self.write(st,dest,4,self.read(st,source,2));return
        require(op in ('test','cmp','xor','or','and','add','sub','shl','shr','sar','lock xadd'),'unsupported explicit effect')
        if op=='xor' and source==dest and dst and dst[1]>=32:
            self.write(st,dest,size,const([0]));return
        a=self.read(st,dest,size);b=self.read(st,source,size)
        require(a!=RAW and b!=RAW,'raw value observation')
        if op in ('test','cmp'):return
        av,bv=values(a),values(b);v=None
        require(not(private(a) or private(b)) or (op in ('add','sub') and private(a) and bv is not None and len(bv)==1),'unsupported private-frame arithmetic')
        if op in ('add','sub') and a and a[0]=='argument' and bv is not None:
            offset=a[2]+(bv[0] if op=='add' else -bv[0])
            require(0<=offset<=st.arguments[a[1]][0],'argument arithmetic footprint escape')
            v=('argument',a[1],offset)
        if op in ('add','sub') and root(a) and bv is not None and all(abs(x)<=4096 for x in bv):v=storage_offset(a,bv[0] if op=='add' else -bv[0]) if storage(a) and len(bv)==1 else ROOT if not storage(a) else None
        if op in ('add','sub') and a and a[0]=='frame' and bv is not None and len(bv)==1:
            v=('frame',a[1]+(bv[0] if op=='add' else -bv[0]))
        if op in ('add','sub') and a and a[0]=='region' and bv is not None and all(x<=4096 for x in bv):v=a
        if op in ('add','sub') and av is not None and bv is not None and all(self.mapped(a,1) for a in av) and all(x<=4096 for x in bv):
            sections={self.side.image.section_at(x).addr for x in av}
            if len(sections)==1:v=('region',next(iter(sections)))
        if av is not None and bv is not None and v is None:
            ops={'add':lambda x,y:x+y,'sub':lambda x,y:x-y,'and':lambda x,y:x&y,
                 'or':lambda x,y:x|y,'xor':lambda x,y:x^y,'shl':lambda x,y:x<<(y&(63 if size==8 else 31)),
                 'shr':lambda x,y:x>>(y&(63 if size==8 else 31)),
                 'sar':lambda x,y:(x-(1<<(size*8)) if x&(1<<(size*8-1)) else x)>>(y&(63 if size==8 else 31))}
            if op in ops:v=const(ops[op](x,y)&((1<<(8*size))-1) for x in av for y in bv)
        if op=='lock xadd':
            require(src and src[1] in (32,64) and not dst,'invalid lock xadd')
            self.write(st,source,size,a)
        self.write(st,dest,size,v)

    def typed_local(self,st,reg,size):
        v=st.regs.get(reg)
        require(v and (root(v) or v[0] in ('frame','constant','argument')),'missing typed argument')
        if v[0]=='argument':
            require(0<=v[2] and v[2]+size<=st.arguments[v[1]][0],'typed argument footprint escape')
            require(st.arguments[v[1]][1]!=RAW,'raw pointer hidden in typed argument')
        if v[0]=='frame':
            require(frames.local_access(v[1],size,st.sp,st.slots()),'argument exposes private frame')
            require(not any(x==RAW and frames.overlaps(v[1],size,[(p,p+n)]) for p,(n,x,_) in st.cells.items()),'typed argument exposes stale raw bytes')
        if v[0]=='constant':require(all(self.mapped(x,size) for x in values(v)),'invalid static argument')

    def old_gnu_identity(self,name):
        image=self.side.image
        try:
            syms=[s for s in image.dynsyms if s.name==name and not s.defined and s.bind==1 and s.type==2]
            require(len(syms)==1,'ambiguous GNU import identity')
            def data(section):
                s=image.section(section);return image.data[s.offset:s.offset+s.size]
            versions=data('.gnu.version');needs=data('.gnu.version_r');strings=data('.dynstr')
            index=struct.unpack_from('<H',versions,2*syms[0].index)[0]&0x7fff
            def string(offset):
                require(0<=offset<len(strings),'invalid version string')
                end=strings.find(b'\0',offset);require(end>=offset,'unterminated version string')
                return strings[offset:end].decode('ascii')
            found=[];off=0;visited=set()
            while off not in visited:
                visited.add(off)
                version,count,file,aux,nxt=struct.unpack_from('<HHIII',needs,off)
                require(version==1 and 0<count<=256,'invalid version-need entry')
                library=string(file);a=off+aux;seen=set()
                for _ in range(count):
                    require(a not in seen,'cyclic version auxiliary');seen.add(a)
                    _,flags,other,label,following=struct.unpack_from('<IHHII',needs,a)
                    if other&0x7fff==index:found.append((library,string(label),flags))
                    a+=following
                if not nxt:break
                off+=nxt
            require(found==[('libstdc++.so.6','GLIBCXX_3.4',0)],'unsupported GNU import version')
            return {'soname':found[0][0],'version':found[0][1],'symbol':name,
                    'evidence':'original dynamic symbol/version tables; explicit ABI semantics, not original DSO bytes'}
        except (KeyError,IndexError,ValueError,UnicodeError,struct.error) as error:
            raise Reject('malformed GNU import version') from error

    def standard(self,st,name):
        require(name in IMPORTS,'unknown imported consumer')
        inputs,throws=IMPORTS[name];raw=st.raw()
        require(all(st.regs.get(r,POISON)!=POISON and not(st.regs.get(r) and st.regs[r][0]=='entry') for r in inputs),'undefined declared import argument')
        identity=None
        if name==DESTROY:
            require(raw<={'12'},'GNU helper contract only covers incoming R12')
            identity=self.old_gnu_identity(name)
            require(not storage(st.regs.get('di')) or st.regs['di'][1]==-24,'wrong known string rep address')
        consumed=name==CTOR and 'si' in raw
        require(not raw&inputs or (consumed and raw&inputs=={'si'}),'raw argument to nonconsumer')
        for reg,n in ({'di':8,'d':1} if name==CTOR else
                      {'di':1,'si':1} if name==DESTROY else
                      {'di':8,'c':4 if name==WREPLACE else 1} if name in (REPLACE,WREPLACE) else
                      {'di':8,'si':8} if name in (COPY,ASSIGN) else {'di':8,'si':4} if name==FIND else
                      {'di':8} if name in DTORS else {'di':4} if name=='wcslen' else {'di':1}).items():
            self.typed_local(st,reg,n)
        initialized=({'di'} if name in DTORS or name in (REPLACE,WREPLACE,FIND) else
                     {'di','si'} if name==ASSIGN else {'si'} if name==COPY else set())
        for reg in initialized:
            v=st.regs.get(reg)
            if v and v[0]=='frame':self.read(st,f'{hex(v[1]-st.sp)}(%rsp)',8)
            if v and v[0]=='argument':require(st.arguments[v[1]][1]!=UNINITIALIZED,'typed object is not initialized')
        if name==CTOR and not consumed:
            require(root(st.regs.get('si')),'unbounded constructor input is not pre-existing object')
        for reg in ({'c'} if name in (REPLACE,WREPLACE) else {'si'} if name==FIND else {'di'} if name=='wcslen' else set()):
            require(root(st.regs.get(reg)) or values(st.regs.get(reg)) is not None,'unbounded string source is not pre-existing/static')
        if name in (DESTROY,'_ZdlPv'):
            require(root(st.regs.get('di')),'deallocation needs pre-existing heap rep')
        if consumed:st.copied=True
        output=st.regs.get('di') if name in OUTPUTS else None
        if output and output[0]=='frame':self.write(st,f'{hex(output[1]-st.sp)}(%rsp)',8,STRING_STORAGE)
        elif output and output[0]=='argument':
            require(output[2]==0 and st.arguments[output[1]][0]==8,'constructor footprint mismatch')
            st.arguments[output[1]]=(8,STRING_STORAGE);st.argument_writes=st.argument_writes|{output[1]}
        elif output and root(output) and not storage(output) and output[1]:st.writes=st.writes|{output[1]}
        for reg in VOLATILE-raw:st.regs[reg]=POISON;st.ids.pop(reg,None)
        if name in (REPLACE,WREPLACE,ASSIGN):st.regs['a']=output
        if name in (FIND,'wcslen'):st.regs['a']=None
        return {'kind':'explicit-cxx-sysv-import-contract','name':name,'may_throw':throws,
                'incoming_raw':sorted(raw),'preserved_raw':sorted(raw),'import_identity':identity,'consumes_wide':consumed,
                'contract':('gnu-old-cow-string-stdallocator-wchar-GLIBCXX_3.4-v1'
                            if name==DESTROY else 'standard-nonretaining-object-operation-v1')}

    def run(self,target,incoming=frozenset({'12'}),wrapper=False,depth=0,active=(),arguments=None,bindings=None):
        snapshot=getattr(self.side.image,'data',None)
        if not isinstance(snapshot,bytes) or hashlib.sha256(snapshot).hexdigest()!=getattr(self.side.image,'sha256',None):
            self.error={'target':target,'reason':'original snapshot identity mismatch'};return None
        arguments=arguments if arguments is not None else ({'di':ROOT,'si':ROOT} if wrapper else {})
        bindings=bindings or {}
        key=(self.side.image.sha256,target,tuple(sorted(incoming)),wrapper,tuple(sorted(arguments.items())),tuple(sorted(bindings.items())))
        if key in self.memo:return self.memo[key]
        try:
            require(depth<=3 and target not in active,'recursive/bounded call closure')
            info=self.side._callee_body(self.side.image,target);require(info,'missing original bounded body')
            rows=info['rows'];start=info['start'];end=start+info['size']
            require(len(rows)<=256,'instruction bound')
            eh=self.side._literal_eh(rows,start,end);require(eh is not None,'unsupported EH')
            table=frames.cfi(self.side,info);require(table,'missing original frame certificate')
            positions={r[0]:i for i,r in enumerate(rows)}
            entry={r:('entry',r) for r in SAVED};entry.update({r:POISON for r in VOLATILE})
            entry.update(arguments)
            entry.update({r:('argument',r,0) for r in bindings})
            entry.update({r:RAW for r in incoming})
            initial=State(dict(entry),ids={r:r for r in SAVED},arguments=dict(bindings))
            pending=[(0,initial)];seen=set();normal=[];exception=[];edges=[];certs=[];consumer=[];direct_writes=False
            while pending:
                i,st=pending.pop();state=(i,st.key());direct_writes|=st.direct_root_writes
                if state in seen:continue
                require(len(seen)<4096 and 0<=i<len(rows),'CFG state bound/escape')
                seen.add(state);pc,op,args=rows[i];after=rows[i+1][0] if i+1<len(rows) else end
                if wrapper and st.copied and not st.raw() and not st.private():
                    normal.append((frozenset(),None,st.writes,dict(st.arguments),st.argument_writes));continue
                if op in ('ret','retq','repz ret','repz retq'):
                    require(not args and st.sp==0 and not st.slots(),'unbalanced return')
                    require(st.regs.get('a')!=RAW,'raw pointer return')
                    require(not(st.regs.get('a') and st.regs['a'][0]=='frame'),'private-frame pointer return')
                    require(not wrapper or st.copied,'normal path never copied source')
                    require(all(st.ids.get(r)==r for r in SAVED),'callee-saved entry identity changed')
                    require(wrapper or st.raw()==set(incoming),'extra/lost outgoing raw alias')
                    normal.append((frozenset(st.raw()),st.regs.get('a'),st.writes,dict(st.arguments),st.argument_writes));continue
                if op in JUMPS:
                    dest=self.side.direct_target(args);require(dest in positions,'outside/interior indirect branch')
                    pending.append((positions[dest],st.clone()))
                    if op!='jmp':pending.append((i+1,st))
                    continue
                if op in ('call','callq'):
                    callee=self.side.direct_target(args);require(callee is not None,'indirect call')
                    name=self.side.image.plt.get(callee,'').split('@')[0]
                    saved={('r'+reg if reg.isdigit() else {'b':'rbx','bp':'rbp'}[reg]):p
                           for p,(_,v,reg) in st.cells.items() if reg and v==entry.get(reg)}
                    require(all(st.sp<=p for p in st.slots()),'call exposes unallocated red-zone save')
                    require(all(st.ids.get(r)==r or any(reg==r and v==entry.get(r) and st.cell_ids.get(p)==r for p,(_,v,reg) in st.cells.items()) for r in SAVED),'unwind loses callee-saved entry identity')
                    certificate=frames.span_rules(table,pc,after,st.sp,saved)
                    require(certificate,'body/CFI disagreement at call');certs.append(certificate)
                    if name=='_Unwind_Resume':
                        require(st.unwind and st.regs.get('di')!=RAW,'unsupported Resume')
                        outgoing=set(st.raw())
                        for p,(_,v,reg) in st.cells.items():
                            if reg:
                                if v==RAW:outgoing.add(reg)
                                else:outgoing.discard(reg)
                        require(incoming&SAVED<=outgoing,'exception loses incoming saved alias')
                        require(wrapper or outgoing==set(incoming),'extra/lost exceptional raw alias')
                        exception.append(frozenset(outgoing));continue
                    # Any callee may overwrite its own abandoned lower stack.
                    st.cells={p:cell for p,cell in st.cells.items() if p>=st.sp}
                    st.cell_ids={p:v for p,v in st.cell_ids.items() if p>=st.sp}
                    before=st.clone();exception_regions=[]
                    if name:
                        proof=self.standard(st,name)
                        # Only the selected exact import contract permits consuming.
                        if proof['consumes_wide']:consumer.append(pc)
                        if name in OUTPUTS:exception_regions=['di']
                    else:
                        raw=frozenset(st.raw());require(raw<=SAVED,'local call receives volatile raw alias')
                        childargs={};childbindings={}
                        regions=[]
                        for reg,v in st.regs.items():
                            if reg not in {'di','si','d','c','8','9'} or reg in raw:continue
                            if v and v[0]=='frame':
                                self.typed_local(st,reg,8)
                                cell=self.read(st,f'{hex(v[1]-st.sp)}(%rsp)',8,allow_uninitialized=True)
                                require(not(cell and cell[0] in ('frame','argument')),'nested frame pointer escape')
                                require(not frames.overlaps(v[1],8,[(a,b) for kind,a,b in regions if kind=='frame']),'overlapping caller argument regions')
                                regions.append(('frame',v[1],v[1]+8));childbindings[reg]=(8,cell)
                            elif v and v[0]=='argument':
                                self.typed_local(st,reg,8);require(v[2]==0,'subobject call unsupported')
                                require(not any(kind==v[1] for kind,_,_ in regions),'overlapping caller argument aliases')
                                regions.append((v[1],0,8));childbindings[reg]=st.arguments[v[1]]
                            elif v is None or root(v) or values(v) is not None or (v and v[0]=='region'):childargs[reg]=v
                        proof=self.run(callee,raw,False,depth+1,active+(target,),childargs,childbindings)
                        require(proof is not None,f'unproved original local call: {self.error}')
                        exception_regions=list(childbindings)
                        require(set(proof['normal_aliases'])==set(raw) and set(proof['exception_aliases'])<=set(raw),'outgoing alias mismatch')
                        for reg in VOLATILE-raw:st.regs[reg]=POISON;st.ids.pop(reg,None)
                        if not proof['returns_indeterminate']:st.regs['a']=None
                        if proof['returns_object']:st.regs['a']=ROOT
                        if proof['return_argument'] is not None:st.regs['a']=before.regs[proof['return_argument']]
                        for reg,value in proof['argument_writes'].items():
                            dest=before.regs[reg]
                            if dest[0]=='frame':self.write(st,f'{hex(dest[1]-st.sp)}(%rsp)',8,value)
                            elif dest[0]=='argument':
                                st.arguments[dest[1]]=(8,value);st.argument_writes=st.argument_writes|{dest[1]}
                    direct_writes|=proof.get('direct_root_writes',False)
                    edges.append({'pc':pc,'proof':proof})
                    if proof['may_throw']:
                        hits=[row for row in eh['rows'] if row[0]<=pc-start<row[0]+row[1]]
                        require(len(hits)<=1,'overlapping exception rows')
                        # A cleanup-only row with no pad propagates; a missing row
                        # in an LSDA terminates and cannot observe the raw address.
                        if hits and hits[0][2]:
                            pad=start+hits[0][2];require(pad in positions,'bad cleanup target')
                            ex=before.clone();ex.unwind=True
                            for reg in VOLATILE-ex.raw():ex.regs[reg]=POISON;ex.ids.pop(reg,None)
                            ex.regs['a']=ROOT;ex.regs['d']=None;ex.ids.pop('a',None);ex.ids.pop('d',None)
                            # A throwing child may have changed any exposed cell.
                            # Never reuse its pre-call scalar/root snapshot on EH.
                            for reg in exception_regions:
                                v=before.regs.get(reg)
                                if v and v[0]=='frame':
                                    old=self.read(before,f'{hex(v[1]-before.sp)}(%rsp)',8,allow_uninitialized=True)
                                    self.write(ex,f'{hex(v[1]-ex.sp)}(%rsp)',8,UNINITIALIZED if old==UNINITIALIZED else None)
                                elif v and v[0]=='argument':
                                    ex.arguments[v[1]]=(8,UNINITIALIZED if before.arguments[v[1]][1]==UNINITIALIZED else None);ex.argument_writes=ex.argument_writes|{v[1]}
                            pending.append((positions[pad],ex))
                        elif not eh['rows'] or hits:
                            out=set(before.raw())
                            for _,v,reg in before.cells.values():
                                if reg:
                                    if v==RAW:out.add(reg)
                                    else:out.discard(reg)
                            require(wrapper or out==set(incoming),'extra/lost propagated alias')
                            exception.append(frozenset(out))
                    pending.append((i+1,st));continue
                self.effect(st,op,args,entry);pending.append((i+1,st))
            require(normal,'no verified normal exit')
            if wrapper:require(consumer,'no complete wide-copy consumer')
            argument_returns=[x[1] for x in normal if x[1] and x[1][0]=='argument']
            require(not argument_returns or (len(argument_returns)==len(normal) and len(set(argument_returns))==1 and argument_returns[0][2]==0),'inconsistent returned argument alias')
            allwrites=set(normal[0][2])
            for _,_,writes,_,_ in normal:allwrites&=set(writes)
            argwrites={}
            for reg in set().union(*(set(x[4]) for x in normal)):
                vals=[x[3][reg][1] for x in normal]
                argwrites[reg]=UNINITIALIZED if UNINITIALIZED in vals else vals[0] if all(v==vals[0] for v in vals) else ROOT if all(root(v) for v in vals) else None
            result={'kind':'original-saved-argument-frame-effects-v1','start':start,'size':info['size'],
                    'image_sha256':self.side.image.sha256,'body_sha256':info['body_sha256'],
                    'incoming_raw':sorted(incoming),'normal_aliases':sorted(set().union(*(x[0] for x in normal))),
                    'exception_aliases':sorted(set().union(*exception)) if exception else [],
                    'may_throw':bool(exception),'returns_object':all(root(x[1]) for x in normal),
                    'returns_indeterminate':any(x[1]==POISON for x in normal),
                    'return_argument':argument_returns[0][1] if argument_returns else None,
                    'direct_root_writes':direct_writes,'owned_storage_contract':'old GNU COW string data; only offset -8 width4 direct count writes are private-disjoint','writes_pointer_arguments':sorted(allwrites),'argument_writes':argwrites,'copy_consumers':sorted(set(consumer)),
                    'eh_kind':eh['kind'],'eh_rows':eh['rows'],'calls':edges,'frame_spans':certs,
                    'visited':sorted({rows[x[0]][0] for x in seen}),
                    'premise':'valid pre-existing object graphs and std string storage; allocated typed locals disjoint from private saves'}
            self.memo[key]=result;return result
        except Reject as error:
            self.error={'target':target,'pc':locals().get('pc'),'reason':str(error)}
            return None
