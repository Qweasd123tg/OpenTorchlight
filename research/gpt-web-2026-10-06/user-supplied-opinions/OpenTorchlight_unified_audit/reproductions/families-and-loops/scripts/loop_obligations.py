#!/usr/bin/env python3
"""Finite-width invariant experiments, using libz3's SMT-LIB interface.
Checks explicit scalar/state models; NOT an x86-to-SMT lifter or full-game proof.
No Python z3 dependency. A recent libz3 shared library is required.
"""
from __future__ import annotations
import argparse,ctypes,ctypes.util,json,re,time
from pathlib import Path
import family_deltas as fd
class SMT:
    def __init__(self):
        path=ctypes.util.find_library('z3')
        if not path:raise RuntimeError('libz3 unavailable')
        self.lib=ctypes.CDLL(path)
        self.lib.Z3_mk_config.restype=ctypes.c_void_p
        self.lib.Z3_mk_context.argtypes=[ctypes.c_void_p];self.lib.Z3_mk_context.restype=ctypes.c_void_p
        self.lib.Z3_del_config.argtypes=[ctypes.c_void_p];self.lib.Z3_del_context.argtypes=[ctypes.c_void_p]
        self.lib.Z3_eval_smtlib2_string.argtypes=[ctypes.c_void_p,ctypes.c_char_p];self.lib.Z3_eval_smtlib2_string.restype=ctypes.c_char_p
        self.lib.Z3_get_full_version.restype=ctypes.c_char_p
        self.version=self.lib.Z3_get_full_version().decode()
    def check(self,code):
        cfg=self.lib.Z3_mk_config();ctx=self.lib.Z3_mk_context(cfg);self.lib.Z3_del_config(cfg)
        try:return self.lib.Z3_eval_smtlib2_string(ctx,code.encode()).decode().strip()
        finally:self.lib.Z3_del_context(ctx)
PRE='''(set-logic QF_AUFBV)
(set-option :timeout 5000)
(set-option :produce-models true)
(declare-const i (_ BitVec 32))
(declare-const n (_ BitVec 32))
(declare-const capacity (_ BitVec 32))
(declare-const off (_ BitVec 64))
(declare-const base (_ BitVec 64))
(declare-const heap (Array (_ BitVec 64) (_ BitVec 64)))
(define-fun index64 () (_ BitVec 64) ((_ zero_extend 32) i))
(define-fun offsetFromI () (_ BitVec 64) (bvmul index64 (_ bv8 64)))
(define-fun inv () Bool (= off offsetFromI))
(define-fun nextI () (_ BitVec 32) (bvadd i (_ bv1 32)))
(define-fun nextOffset () (_ BitVec 64) (bvadd off (_ bv8 64)))
(define-fun mutantOffset () (_ BitVec 64) (bvadd off (_ bv16 64)))
(define-fun expectedNext () (_ BitVec 64) (bvmul ((_ zero_extend 32) nextI) (_ bv8 64)))
'''
OBLIGATIONS=[
 ('base','unsat','(assert (= i (_ bv0 32)))\n(assert (= off (_ bv0 64)))\n(assert (not inv))', 'Zero initial index and offset establish relation.'),
 ('step_with_uint_bound','unsat','(assert inv)\n(assert (bvult i n))\n(assert (not (= nextOffset expectedNext)))','i<n, both uint32, rules out wrap on this increment.'),
 ('same_memory_read','unsat','(assert inv)\n(assert (not (= (select heap (bvadd base off)) (select heap (bvadd base offsetFromI)))))','Same effective address in flat read-only memory model. Does not prove C++ pointer validity.'),
 ('missing_bound','sat','(assert inv)\n(assert (= i #xffffffff))\n(assert (not (= nextOffset expectedNext)))','Counterexample if the increment may occur at UINT_MAX.'),
 ('wrong_stride','sat','(assert inv)\n(assert (bvult i n))\n(assert (= i (_ bv0 32)))\n(assert (= n (_ bv1 32)))\n(assert (not (= (bvadd off (_ bv16 64)) expectedNext)))','A stride of 16 is not equivalent to index increment for 8-byte elements.'),
 ('capacity_branch_under_invariant','unsat','(assert (bvult i n))\n(assert (bvule n capacity))\n(assert (not (bvult i capacity)))','Only under count<=capacity can the out-of-capacity path be excluded.'),
 ('capacity_branch_without_invariant','sat','(assert (bvult i n))\n(assert (not (bvult i capacity)))\n(assert (= i (_ bv1 32)))\n(assert (= n (_ bv2 32)))\n(assert (= capacity (_ bv1 32)))','A valid search bound alone does not justify bypassing TArrayList fallback.'),
 ('invariant_preserved_by_increment_in_capacity','unsat','(assert (bvult n capacity))\n(assert (not (bvule (bvadd n (_ bv1 32)) capacity)))','Already-reserved append preserves count<=capacity in uint32 model.'),
 ('invariant_preserved_by_remove','unsat','(assert (bvule n capacity))\n(assert (bvult i n))\n(assert (not (bvule (bvsub n (_ bv1 32)) capacity)))','Valid removal decreases count without unsigned wrap.'),
 ('capacity_growth_wrap_counterexample','sat','(assert (= n #xfffffffe))\n(assert (= capacity #xfffffffe))\n(assert (not (bvule (bvadd n (_ bv1 32)) (bvadd capacity (_ bv2 32)))))','Naive preservation by growing an unsigned capacity fails on wrap; actual allocation behavior not modeled.'),
]

def recurrence_candidates(root):
    rows=[];seen=set()
    for p in sorted((root/'research/decompiled-core').glob('*.c')):
        text=p.read_text(errors='replace');ms=list(fd.HEADER.finditer(text))
        for k,m in enumerate(ms):
            a=int(m[1],16)
            if a in seen:continue
            raw=text[m.end():ms[k+1].start() if k+1<len(ms) else len(text)]
            ts,_=fd.body_tokens(raw)
            if not ts:continue
            seen.add(a);ss=' '.join(v for _,v in ts)
            incs=re.findall(r'\b([A-Za-z_]\w*) = \1 \+ (0x[\da-f]+|[0-9]+) ;',ss)
            by=collections.defaultdict(list)
            for var,v in incs:by[int(v,0)].append(var)
            if 1 in by and any(s in by for s in (2,4,8,12,16,24,32,64)):
                rows.append({'address':hex(a),'symbol':m[2].strip(),'path':str(p.relative_to(root)),
                             'line':text.count('\n',0,m.start())+1,
                             'increments':dict(by),'status':'LEXICAL_CANDIDATE_ONLY',
                             'limitation':'Co-occurrence does not establish same loop, dominance, initialization, invariant or absence of other assignments.'})
    return rows
import collections

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('root',type=Path);ap.add_argument('out',type=Path);a=ap.parse_args()
    a.out.mkdir(parents=True,exist_ok=True);s=SMT();results=[]
    for name,expect,asserts,meaning in OBLIGATIONS:
        program=PRE+asserts+'\n(check-sat)\n';(a.out/(name+'.smt2')).write_text(program)
        t=time.perf_counter();r=s.check(program);elapsed=time.perf_counter()-t
        status=r.splitlines()[0];model=None
        if status=='sat':model=s.check(program+'(get-value (i n capacity off nextOffset expectedNext mutantOffset))\n')
        results.append({'name':name,'expected':expect,'status':status,'output':r,'model':model,'seconds':elapsed,'meaning':meaning})
        if status!=expect:raise RuntimeError(f'{name}: {r}, expected {expect}')
    rec=recurrence_candidates(a.root)
    out={'scope':'Scalar bitvector/state-model obligations only. No full original function or x86 semantics proof; no generated game C++.',
       'z3_version':s.version,'obligations':results,'recurrence_cooccurrence_functions':len(rec),'recurrence_candidates':rec}
    (a.out/'loop-results.json').write_text(json.dumps(out,ensure_ascii=False,indent=2))
    print('Z3',s.version,[(r['name'],r['status']) for r in results]);print('recurrence candidate functions',len(rec))
if __name__=='__main__':main()
