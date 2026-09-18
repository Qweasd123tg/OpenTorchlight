#!/usr/bin/env python3
"""Regression checks for work-reduction triage; not gameplay fidelity tests."""
from pathlib import Path
import importlib.util, json, sys

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'tools'))
import tiny_function_catalog as tiny
import auto_triage

checks=0
def require(cond,msg):
 global checks;checks+=1
 if not cond:raise AssertionError(msg)

def main():
 # Exact leaf/routing recognisers should remain conservative and deterministic.
 k,m=tiny.classify([('mov','rax,QWORD PTR [rip+0x1234]'),('ret','')],'CTest::getSingleton()')
 require(k=='global_pointer_getter','RIP-relative singleton getter not recognised')
 k,m=tiny.classify([('add','rdi,0xfffffffffffffff8'),('jmp','0x1234 <target>')],'non-virtual thunk to CTest::f()')
 require(k=='adjusted_this_tail_thunk','adjusted-this thunk not recognised')
 k,m=tiny.classify([('mov','rax,QWORD PTR [rdi]'),('mov','rax,QWORD PTR [rax+0x48]'),('jmp','rax')],'CTest::event()')
 require(k=='virtual_slot_forwarder','virtual slot forwarder not recognised')
 k,m=tiny.classify([('mov','BYTE PTR [rdi+0x10],0x1'),('mov','eax,0x1'),('ret','')],'CTest::handler()')
 require(k=='field_constant_setter_return_constant','tiny flag handler not recognised')
 k,m=tiny.classify([('mov','QWORD PTR [rdi],0x1234'),('jmp','0x2000 <base>')],'CTest::~CTest()')
 require(k=='destructor_tail_base','destructor wrapper not recognised')

 tj=json.loads((ROOT/'research/tiny-functions.json').read_text(encoding='utf8'))
 recognised=len(tj['functions'])-tj['counts']['unclassified']
 require(tj['schema']==2,'tiny catalogue schema drift')
 require(tj['max_bytes']==64,'tiny catalogue expected 64-byte boundary')
 require(recognised>=1300,'mechanical tiny classification unexpectedly regressed')
 require(tj['review_tiers']['manual_or_family']<1400,'tiny manual queue unexpectedly regressed')

 tri=auto_triage.build(ROOT,4)
 require(tri['total_functions']==17023,'original function universe changed unexpectedly')
 require(sum(tri['primary_classes'].values())==tri['total_functions'],'primary triage classes overlap or omit functions')
 require(tri['primary_classes']['compiler_glue']>5000,'compiler glue no longer isolated')
 require(tri['headline']['source_match_before_reverse']>3500,'external-source-first queue unexpectedly shrank')
 require(tri['headline']['manual_reverse_remaining']<3300,'manual queue reduction regressed')
 require(tri['headline']['no_individual_deep_reverse_now']>8500,'automatic/deferred queue reduction regressed')

 shape=json.loads((ROOT/'research/manual-shape-clusters.json').read_text(encoding='utf8'))
 require(shape['clustered_members']>=500,'residual structural batching unexpectedly regressed')
 require(shape['representative_passes_saved_if_all_deltas_validate']>=300,'shape batching savings unexpectedly regressed')
 print(f'PASS: {checks} automatic-function-triage assertions')

if __name__=='__main__':main()
