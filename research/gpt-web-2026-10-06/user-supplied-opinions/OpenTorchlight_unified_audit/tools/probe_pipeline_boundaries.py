#!/usr/bin/env python3
"""Read-only regression probes for the supplied OpenTorchlight snapshot.
Real project Python functions and loader.c are exercised. Expensive ELF/Ghidra
operations are replaced only where explicitly recorded. Never invokes a model,
Ghidra, the original game, or writes into the input project.
"""
from __future__ import annotations
import argparse, contextlib, hashlib, io, json, os, shutil, subprocess, sys, tempfile
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

def main() -> int:
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('repo',type=Path);ap.add_argument('--out',type=Path,required=True)
    args=ap.parse_args();root=args.repo.resolve();out=args.out.resolve()
    if out==root or root in out.parents:ap.error('output must be outside the input tree')
    if not (root/'tools/decomp/check.py').is_file():ap.error('invalid project root')
    out.mkdir(parents=True,exist_ok=True)
    sys.dont_write_bytecode=True;sys.path.insert(0,str(root/'tools/decomp'))
    import mutate, check, llm_loop, toolchain, objdiff
    records={}
    def save(name,value):records[name]=value
    with tempfile.TemporaryDirectory(prefix='otl-unified-probes-') as td:
        work=Path(td)
        f={'address':'0x100','demangled':'CProbe::f()','names':['_ZN6CProbe1fEv'],
           'kind':'function','scope':'CProbe','method':'f','params':'','tu':1,'size':16}
        db={'functions':{'0x100':f},'tus':[{'id':1,'name':'Probe.cpp','kind':'game'}]}
        # An old strong result has no recorded baseline digest. record() associates
        # it with a newly computed current code digest without a new mutation run.
        stale={'0x100':{'strong':True,'killed':8,'tried':10,'name':f['demangled']}}
        accepted=work/'accepted.json'
        with patch.object(mutate,'ROOT',work),patch.object(mutate,'ACCEPTED',accepted),patch.object(mutate,'code_digests',return_value={'0x100':'CURRENT_CHANGED_CODE'}),contextlib.redirect_stdout(io.StringIO()):
            mutate.record(db,[f],stale)
        entry=json.loads(accepted.read_text())['0x100']
        assert entry['code']=='CURRENT_CHANGED_CODE'
        save('old_mutation_result_rebound_to_current_code',{
            'reproduced':True,'actual_recorded_entry':entry,
            'mechanism':'real mutate.record; code_digests supplies a different current digest',
            'new_mutation_execution':False,'old_results_contain_baseline_digest':False})

        # Candidate-loop acceptance ignores the process return code.
        generated=work/'autotests';generated.mkdir()
        def exercise_loop(rc:int, differences:int):
            o=llm_loop.Loop.__new__(llm_loop.Loop)
            o.source=work/f'candidate-{rc}-{differences}.cpp'
            o.source.write_text('// previously published source\n')
            o.work=work;o.rounds=5;o.accepted={};o.status={};o.original=None
            o.unit=lambda extra=(): '\n'.join(extra)+'\n'
            code='int CProbe::f() { return 999; }'
            pending={'0x100':{'f':f,'code':code}}
            report=[f'    stats auto_100 same 20 both-failed 0 different {differences}',
                    f'tlhybrid: 1 tests, {int(rc!=0)} failed']
            fakegen=SimpleNamespace(write=lambda funcs:([f],{}))
            with patch.object(llm_loop.autotest,'Generator',return_value=fakegen),patch.object(llm_loop.autotest,'OUT',generated),\
                 patch.object(llm_loop.objdiff,'compare_source',return_value={}),patch.object(llm_loop.hybrid,'build',return_value=(None,None)),\
                 patch.object(llm_loop.hybrid,'selftest',return_value=(rc,report)),patch.dict(os.environ,{},clear=False):
                o.test(pending,{'0x100':'fixture instruction difference'},1)
            return {'accepted':bool(o.accepted),'status':o.status,'pending':list(pending),
                    'source_contains_candidate':code in o.source.read_text()}
        bad_exit=exercise_loop(97,0)
        assert bad_exit['accepted']
        save('loop_accepts_stats_despite_failed_process',dict(reproduced=True,process_returncode=97,**bad_exit,
             mechanism='real Loop.test; synthetic compile/generator/process report; no model called'))
        rejected=exercise_loop(1,1)
        assert not rejected['accepted'] and rejected['source_contains_candidate']
        save('rejected_candidate_left_in_public_source_during_round',dict(reproduced=True,**rejected,
             scope='Loop.test return, before normal Loop.run final rewrite; interruption or concurrent reader can observe this state'))

        # Header promotion compares status words, not bodies/test fingerprints.
        o=llm_loop.Loop.__new__(llm_loop.Loop);o.source=work/'promote.cpp';o.source.write_text('before')
        o.accepted={'0x100':'body'};o.existing=''
        rows=iter([{'functions':[{'address':'0x100','status':'DIFF','code':'before'}]},
                   {'functions':[{'address':'0x100','status':'DIFF','code':'after'}]}])
        o.compare=lambda:next(rows)
        def fake_promote(p):p.write_text('after');return ['Probe.h']
        buf=io.StringIO()
        with patch.object(llm_loop.promote,'promote',side_effect=fake_promote),contextlib.redirect_stdout(buf),patch.dict(os.environ,{},clear=False):o.finish()
        assert 'status changed' not in buf.getvalue()
        save('promotion_does_not_notice_changed_diff_body',{'reproduced':True,'log':buf.getvalue().strip(),
             'mechanism':'real Loop.finish, supplied before/after DIFF rows with different code hashes',
             'game_code_change_demonstrated':False})

        # A new generated header can shadow an old include without changing the old dep list.
        compiler=shutil.which('g++')
        if not compiler:raise RuntimeError('g++ is required for the cache probe')
        high=work/'include-high';low=work/'include-low';high.mkdir();low.mkdir()
        source=work/'cache.cpp';source.write_text('#include <Value.h>\n#include <cstdio>\nint main(){std::printf("%d\\n",VALUE);}\n')
        (low/'Value.h').write_text('#define VALUE 11\n')
        cmd=[compiler,'-std=gnu++98','-I',str(high),'-I',str(low)]
        baseline=work/'baseline';fresh=work/'fresh'
        subprocess.run(cmd+[str(source),'-o',str(baseline)],check=True,capture_output=True,timeout=30)
        cc=work/'cc-cache';cc.mkdir()
        with patch.object(toolchain,'CC_CACHE',cc):
            index,_=toolchain._cache_lookup(cmd,source)
            digest=toolchain._digest(cmd,source,[str(low/'Value.h')])
            cache_obj=cc/(digest+'.o');shutil.copy(baseline,cache_obj)
            index.write_text(json.dumps({'deps':[str(low/'Value.h')],'digest':digest,'output':cache_obj.name}))
            (high/'Value.h').write_text('#define VALUE 22\n')
            _,hit=toolchain._cache_lookup(cmd,source)
            subprocess.run(cmd+[str(source),'-o',str(fresh)],check=True,capture_output=True,timeout=30)
            old_value=subprocess.check_output([str(hit)],text=True,timeout=5).strip()
            fresh_value=subprocess.check_output([str(fresh)],text=True,timeout=5).strip()
        assert hit is not None and (old_value,fresh_value)==('11','22')
        save('new_higher_priority_header_reuses_old_cache',{'reproduced':True,'cache_returned':int(old_value),
             'uncached_compilation_returned':int(fresh_value),
             'mechanism':'real _cache_lookup/_digest with system-compiled native control; old dependency list unchanged',
             'original_GCC447_run':False})

        # A timestamp-only normalization key ignores content changes with preserved mtime.
        nc=work/'norm'/'orig-normalized.pickle';nc.parent.mkdir()
        dbfile=nc.parent/'elfdb.json';dbfile.write_text('{"a":1}')
        with patch.object(objdiff,'NORM_CACHE',nc):
            before=objdiff._norm_key();st=dbfile.stat();dbfile.write_text('{"a":2}');os.utime(dbfile,ns=(st.st_atime_ns,st.st_mtime_ns));after=objdiff._norm_key()
        assert before==after
        save('normalized_cache_key_ignores_same_mtime_content_change',{'reproduced':True,'keys_equal':True,
             'mechanism':'real objdiff._norm_key, database contents changed while mtime preserved'})

        # Declarations are treated as coverage even if no test invokes the original.
        shadow=work/'shadow';testdir=shadow/'decomp/hybrid/tests';testdir.mkdir(parents=True)
        (testdir/'DeclaredOnly.cpp').write_text('TL_ORIGINAL(original_f, "_ZN6CProbe1fEv");\nTL_TEST(unrelated) { return 0; }\n')
        with patch.object(check,'ROOT',shadow):covered=check.shadow_covered(db)
        assert covered=={'0x100'}
        save('declaration_only_counts_as_shadow_coverage',{'reproduced':True,'covered':sorted(covered),
             'mechanism':'real check.shadow_covered, synthetic unused TL_ORIGINAL declaration',
             'existing_handwritten_tests_proven_wrong':False})

        # Real loader implementation, synthetic in-memory section table.
        native=work/'loader_probe.c';native.write_text(r'''
#define __libc_start_main audit_unused_libc_start_main
#include "loader.c"
#undef __libc_start_main
static int invoked;
static int good(const tlhybrid_host *h) { (void)h; invoked++; return 0; }
static int bad(const tlhybrid_host *h) { (void)h; invoked++; return 1; }
int main(void) {
 tlhybrid_test tests[2]={{"good",good},{"bad",bad}};
 Elf64_Ehdr eh={0}; Elf64_Shdr sh={0}; struct blob b={0};
 eh.e_shnum=1; sh.sh_name=1;sh.sh_addr=(uintptr_t)tests;sh.sh_size=sizeof tests;
 b.eh=&eh;b.sh=&sh;b.shstr="\0.tlhybrid.tests\0";
 unsetenv("TLHYBRID_FILTER");invoked=0;int all_rc=run_tests(&b), all_calls=invoked;
 setenv("TLHYBRID_FILTER","not_present",1);invoked=0;int none_rc=run_tests(&b), none_calls=invoked;
 setenv("TLHYBRID_FILTER","good",1);invoked=0;int one_rc=run_tests(&b), one_calls=invoked;
 printf("{\"all_rc\":%d,\"all_invoked\":%d,\"none_rc\":%d,\"none_invoked\":%d,\"one_rc\":%d,\"one_invoked\":%d}\n",all_rc,all_calls,none_rc,none_calls,one_rc,one_calls);
 return !(all_rc==1 && all_calls==2 && none_rc==0 && none_calls==0 && one_calls==1);
}
''')
        exe=work/'loader_probe'
        subprocess.run(['cc','-std=gnu11','-O0','-I',str(root/'decomp/hybrid'),str(native),'-ldl','-o',str(exe)],check=True,capture_output=True,timeout=30)
        result=subprocess.run([str(exe)],capture_output=True,text=True,timeout=5,check=True)
        (out/'loader_probe.c').write_text(native.read_text());(out/'loader.log').write_text(result.stderr)
        v=json.loads(result.stdout)
        assert v['none_rc']==0 and v['none_invoked']==0
        save('real_loader_zero_selected_tests_succeeds',{'reproduced':True,**v,'log':result.stderr,
             'mechanism':'native real loader.c run_tests on synthetic section descriptors; no ELF/game loading'})

        # Mutation score can be 100% based on one tested mutant in actual archived acceptance entries.
        actual=json.loads((root/'decomp/autotests.json').read_text())
        tiny={a:e for a,e in actual.items() if e.get('tried',999)<=2}
        save('archived_acceptance_with_one_or_two_mutants',{'entries':tiny,'total_entries':len(actual),
             'scope':'archive observations, not a claim these implementations are wrong'})
    (out/'boundary-probes.json').write_text(json.dumps(records,ensure_ascii=False,indent=2)+'\n')
    print(json.dumps({'reproduced_cases':sum(r.get('reproduced',False) for r in records.values()),'observations':len(records),'out':str(out)},indent=2))
    return 0
if __name__=='__main__':raise SystemExit(main())
