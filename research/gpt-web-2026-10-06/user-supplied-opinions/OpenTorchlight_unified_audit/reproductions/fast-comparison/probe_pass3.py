#!/usr/bin/env python3
"""Read-only OpenTorchlight diagnostics; synthetic C++ is built outside the project.

python3 probe_pass3.py /path/to/OpenTorchlight --out ./results
Requires Python 3, g++, objdump. Optional: the Z3 shared library (no Python binding).
This is NOT a general x86 verifier and never marks a game function accepted.
"""
from __future__ import annotations
import argparse, collections, csv, ctypes, ctypes.util, json, pathlib, re, subprocess, sys, tempfile

HERE = pathlib.Path(__file__).resolve().parent

def run(args, cwd=None):
    p = subprocess.run(list(map(str,args)), cwd=cwd, text=True, capture_output=True, timeout=40)
    if p.returncode:
        raise RuntimeError(f"command failed ({p.returncode}): {' '.join(map(str,args))}\n{p.stderr}")
    return p.stdout

def disassembly(path, name):
    text=run(['objdump','-d','--no-show-raw-insn',path])
    match=re.search(r'^[0-9a-f]+ <'+re.escape(name)+r'>:\n(.*?)(?=\n\n|\Z)',text,re.M|re.S)
    if not match: raise ValueError(f'missing function {name}')
    return [m.groups() for line in match[1].splitlines() if (m:=re.match(r'^\s*([0-9a-f]+):\s+(\S+)\s*(.*)$',line))]

def bv(n): return f'(_ bv{int(n) % (1<<32)} 32)'

def arithmetic_return(insns):
    """Model ONLY this integer-leaf experiment. Reject other operations.

    ABI: one unsigned 32-bit argument in EDI; result in EAX; no memory,
    branches, calls, stack, or callee-saved registers. Flags are dead at return.
    LEA uses lower 32 bits; upper source-register bits cannot affect EAX.
    """
    regs={'%edi':'x','%rdi':'x'}
    def read(op):
        if op.startswith('$'): return bv(int(op[1:],0))
        if op not in regs: raise ValueError('unsupported input: '+op)
        return regs[op]
    for _,op,operands in insns:
        if op=='ret':
            if '%eax' not in regs: raise ValueError('no return value')
            return regs['%eax']
        if op=='lea':
            m=re.fullmatch(r'(0x[0-9a-f]+)?\((%[a-z0-9]+)?,(%[a-z0-9]+),(1|2|4|8)\),%eax',operands)
            if not m: raise ValueError('unsupported lea: '+operands)
            disp,base,index,scale=m.groups()
            value=f'(bvmul {read(index)} {bv(int(scale))})'
            if base:value=f'(bvadd {value} {read(base)})'
            if disp and int(disp,16): value=f'(bvadd {value} {bv(int(disp,16))})'
            regs['%eax']=value
        elif op in ('sub','add'):
            src,dst=operands.split(',')
            if dst!='%eax': raise ValueError('unsupported destination')
            regs[dst]=f'({"bvsub" if op=="sub" else "bvadd"} {read(dst)} {read(src)})'
        elif op=='imul':
            imm,src,dst=operands.split(',')
            if dst!='%eax' or not imm.startswith('$'): raise ValueError('unsupported imul')
            regs[dst]=f'(bvmul {read(src)} {read(imm)})'
        else: raise ValueError('unsupported instruction: '+op)
    raise ValueError('missing ret')

class Solver:
    def __init__(self):
        name=ctypes.util.find_library('z3')
        if not name: raise RuntimeError('Z3 shared library not found')
        self.lib=ctypes.CDLL(name)
        for fn,args,ret in [('Z3_mk_config',[],ctypes.c_void_p),('Z3_mk_context_rc',[ctypes.c_void_p],ctypes.c_void_p),('Z3_del_context',[ctypes.c_void_p],None),('Z3_del_config',[ctypes.c_void_p],None),('Z3_eval_smtlib2_string',[ctypes.c_void_p,ctypes.c_char_p],ctypes.c_char_p),('Z3_get_full_version',[],ctypes.c_char_p)]:
            f=getattr(self.lib,fn);f.argtypes=args;f.restype=ret
        self.version=self.lib.Z3_get_full_version().decode()
    def evaluate(self,text):
        cfg=self.lib.Z3_mk_config();ctx=self.lib.Z3_mk_context_rc(cfg)
        try:return self.lib.Z3_eval_smtlib2_string(ctx,text.encode()).decode().strip()
        finally:self.lib.Z3_del_context(ctx);self.lib.Z3_del_config(cfg)

def inventory(root):
    symbols=[]
    for line in (root/'research/original-symbols.txt').read_text().splitlines():
        m=re.match(r'^([0-9a-f]+)(?:\s+([0-9a-f]+))?\s+([A-Za-z?])\s+(.+)$',line)
        if m:symbols.append(dict(address=int(m[1],16),size=int(m[2],16) if m[2] else 0,kind=m[3],name=m[4]))
    funcs={s['address']:s for s in symbols if s['kind'] in 'TtWw'}
    clones=[s for s in funcs.values() if '[clone ' in s['name']]
    thunks=[s for s in funcs.values() if 'thunk to ' in s['name']]
    large=json.loads((root/'research/decomp-automation-audit-2026-10-04/measured.json').read_text())
    large_sizes={int(x['address'],16):x['bytes'] for x in large}
    inc=collections.defaultdict(set)
    with (root/'research/original-callgraph.tsv').open() as stream:
        for row in csv.DictReader(stream,delimiter='\t'):
            inc[int(row['callee_address'],16)].add(int(row['caller_address'],16))
    rank=[]
    for target,callers in inc.items():
        hit=callers&large_sizes.keys()
        if target in funcs and hit:
            rank.append(dict(address=hex(target),name=funcs[target]['name'],large_direct_callers=len(hit),all_direct_callers=len(callers),bytes_of_large_callers=sum(large_sizes[a] for a in hit)))
    rank.sort(key=lambda r:(-r['large_direct_callers'],-r['all_direct_callers']))
    serializers=[]
    for path in (root/'research/decompiled-core').glob('*.c'):
        for block in re.split(r'/\* address=',path.read_text())[1:]:
            address=int(block.splitlines()[0].strip(),16)
            if address not in funcs:continue
            fw=len(re.findall(r'\bfwrite\s*\(',block));fr=len(re.findall(r'\bfread\s*\(',block))
            if fw+fr>=10: serializers.append(dict(address=hex(address),name=funcs[address]['name'],bytes=funcs[address]['size'],fwrite_sites=fw,fread_sites=fr,path=str(path.relative_to(root))))
    serializers.sort(key=lambda r:-(r['fwrite_sites']+r['fread_sites']))
    return dict(provenance='Archived symbol/callgraph/pseudocode files; not a new ELF scan or current acceptance report',function_addresses=len(funcs),clone_count=len(clones),static_initializer_clones=sum('__static_initialization_and_destruction_' in s['name'] for s in clones),other_clones=[s for s in clones if '__static_initialization_and_destruction_' not in s['name']],thunk_count=len(thunks),thunk_bytes=sum(s['size'] for s in thunks),source_files=len(list((root/'decomp/src').glob('*.cpp'))),test_translation_units=len(list((root/'decomp/hybrid/tests').glob('*.cpp'))),callee_rankings=rank,serializer_sites=serializers)

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('root',type=pathlib.Path);parser.add_argument('--out',type=pathlib.Path,default=pathlib.Path('results'))
    args=parser.parse_args();root=args.root.resolve();out=args.out.resolve();out.mkdir(parents=True,exist_ok=True)
    if not (root/'decomp/hybrid/AutoTest.h').is_file():parser.error('not an OpenTorchlight checkout')
    results={'scope':'Synthetic local probes and archived metadata only. No target compiler, original ELF, Ghidra, game execution, or game acceptance.', 'compiler':run(['g++','--version']).splitlines()[0]}
    data=inventory(root);(out/'inventory.json').write_text(json.dumps(data,ensure_ascii=False,indent=2))
    with tempfile.TemporaryDirectory(prefix='otl-pass3-') as tmp_:
        tmp=pathlib.Path(tmp_)
        run(['g++','-std=gnu++98','-O2','-fno-strict-aliasing','-Wno-deprecated-declarations','-I'+str(root/'decomp/hybrid'),HERE/'probe_runtime.cpp','-o',tmp/'runtime'])
        results['capture']=json.loads(run([tmp/'runtime']))
        for suffix in ('a','b'):
            run(['g++','-std=gnu++98','-O2','-fno-strict-aliasing','-c',HERE/f'context_{suffix}.cpp','-o',tmp/f'context_{suffix}.o'])
        context={suffix:disassembly(tmp/f'context_{suffix}.o','probe') for suffix in ('a','b')}
        results['same_source_different_tu_context']={'assembly':context,'body_equal':[(m,o) for _,m,o in context['a']]==[(m,o) for _,m,o in context['b']], 'note':'helper body visible only in b; helper is noinline in both; same probe source and flags'}
        for opt in ('O2','Os'):
            run(['g++','-std=gnu++98','-'+opt,'-c',HERE/'algebra.cpp','-o',tmp/f'{opt}.o'])
        original=disassembly(tmp/'O2.o','mul7');equiv=disassembly(tmp/'Os.o','mul7');bad=disassembly(tmp/'Os.o','mul8_bad')
        expressions={'original':arithmetic_return(original),'candidate':arithmetic_return(equiv),'wrong_candidate':arithmetic_return(bad)}
        solver_result={'assembly':{'original':original,'candidate':equiv,'wrong_candidate':bad},'expressions':expressions,'scope':'only unsigned 32-bit return equivalence for these checked leaf instructions; not a general binary verifier'}
        try:
            solver=Solver();solver_result['z3_version']=solver.version
            pre='(set-option :timeout 10000)\n(set-option :produce-models true)\n(declare-const x (_ BitVec 32))\n'
            for label in ('candidate','wrong_candidate'):
                smt=pre+f'(assert (not (= {expressions["original"]} {expressions[label]})))\n(check-sat)\n'
                answer=solver.evaluate(smt)
                solver_result[label]={'check':answer}
                if answer=='sat':
                    solver_result[label]['counterexample']=solver.evaluate(smt+'(get-value (x))\n')
                (out/f'{label}.smt2').write_text(smt)
            assert solver_result['candidate']['check']=='unsat',solver_result
            assert solver_result['wrong_candidate']['check']=='sat',solver_result
        except RuntimeError as error:
            solver_result['skipped']=str(error)
        results['integer_leaf_equivalence']=solver_result
    (out/'probe-results.json').write_text(json.dumps(results,ensure_ascii=False,indent=2))
    print(json.dumps(results,ensure_ascii=False,indent=2))
    return 0
if __name__=='__main__':sys.exit(main())
