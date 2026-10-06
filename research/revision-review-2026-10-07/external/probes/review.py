#!/usr/bin/env python3
"""Read-only revision probes. All writes are to --out or temporary synthetic projects.
Original GCC/ELF/Ghidra are not required. Mocked boundaries are disclosed per result.
The tested production Python functions are imported from --project unchanged.
"""
from __future__ import annotations
import argparse
from contextlib import nullcontext
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile
from types import SimpleNamespace
from unittest.mock import patch


def sha(p):
    return hashlib.sha256(Path(p).read_bytes()).hexdigest()


def run(cmd, **kwargs):
    result = subprocess.run(list(map(str, cmd)), text=True, capture_output=True, timeout=25, **kwargs)
    if result.returncode:
        raise RuntimeError(f'{cmd}\nexit={result.returncode}\n{result.stdout}\n{result.stderr}')
    return result.stdout


def fixture(root, sources=None):
    for d in ('decomp/src','decomp/include','decomp/hybrid/tests'):
        (root/d).mkdir(parents=True, exist_ok=True)
    for n,s in (sources or {'Unit.cpp':'int value() { return 7; }\n'}).items():
        (root/'decomp/src'/n).write_text(s)
    (root/'decomp/include/Unit.h').write_text('// original header\n')
    return root


def queue_probe(out):
    import no_llm_loop as n, llm_loop
    root=fixture(out/'queue')
    tasks=[{'id':i,'name':f'{x}Descriptor.cpp','kind':'game'} for i,x in enumerate('ABCDE')]
    calls=[]
    def provider(*args):
        calls.append(args[1]['name'])
        raise RuntimeError('unsupported shape')
    with patch.object(n.elfdb,'ROOT',root),patch.object(n.elfdb,'load_db',return_value={'tus':tasks}), \
         patch.object(n.evidence,'input_digest',return_value='fixed-inputs'), \
         patch.object(n.publication,'Stage',return_value=SimpleNamespace(path=root)), \
         patch.object(n,'provide',side_effect=provider), \
         patch.object(llm_loop.Model,'__init__',side_effect=AssertionError('model forbidden')):
        reports=[n.run([], 'descriptor', limit=3, seconds=120) for _ in range(3)]
        never=[t['name'] for t in tasks if t['name'] not in calls]
        explicit=n.run(['DDescriptor.cpp'],'descriptor',limit=3,seconds=120)
        try:
            n.run(['Equipment.cpp'],'properties')
            equipment='accepted'
        except ValueError as e:
            equipment=str(e)
    return {'proof_type':'real runner, synthetic DB/provider/digest; no compiler or model',
            'runs':reports,'never_reached_after_three_default_runs':never,
            'explicit_selection_reaches_D':explicit['results'][0]['tu']=='DDescriptor.cpp',
            'provider_calls':calls,'Equipment_selection':equipment,
            'detected':never==['DDescriptor.cpp','EDescriptor.cpp']}


def coverage_probe(project):
    import check
    paths=sorted((project/'decomp/hybrid/tests').glob('*.cpp'))
    rows=[]
    names=set()
    for p in paths:
        text=p.read_text()
        originals=re.findall(r'TL_ORIGINAL\([^;]*?"(_Z\w+)"\)',text,re.S)
        testnames=re.findall(r'\bTL_TEST\s*\(\s*(\w+)\s*\)',text)
        names.update(originals)
        rows.append({'file':str(p.relative_to(project)), 'fixtures':testnames, 'originals':originals,
                     'has_coverage_text':'coverage ' in text})
    # Use addresses from the uploaded symbol dump where possible, not guessed game addresses.
    sym={}
    for line in (project/'research/original-symbols.txt').read_text(errors='replace').splitlines():
        parts=line.split()
        if parts and parts[-1] in names:
            for token in parts[:-1]:
                if re.fullmatch(r'[0-9a-fA-F]{8,16}',token):
                    sym[parts[-1]]=f'0x{int(token,16):x}'
                    break
    db={'functions': {f'0x{0x1000+i:x}':{'names':[n]} for i,n in enumerate(sorted(names))}}
    actual_evidence=check.shadow_covered(db,[f'tlhybrid: {t} PASS (0)' for r in rows for t in r['fixtures']])
    control_address=next(iter(db['functions']))
    control=check.shadow_covered(db,['tlhybrid: fixture PASS (0)',
          f'    coverage fixture {control_address} completed 20 different 0 incomplete 0'])
    with patch.object(check,'ROOT',project):
        declared=check.shadow_declared(db)
    return {'proof_type':'static inventory plus real receipt parser on synthetic successful log; not game execution',
            'cpp_files':len(paths),'fixtures':sum(len(r['fixtures']) for r in rows),
            'unique_original_symbols':len(names),'declared_addresses_in_synthetic_map':len(declared),
            'emitting_files': [r['file'] for r in rows if r['has_coverage_text']],
            'accepted_with_PASS_only':len(actual_evidence),'positive_receipt_control':list(control),
            'equipment_files':sum(Path(r['file']).name.startswith('Equipment') for r in rows),
            'fixtures_by_file':rows,'detected':len(actual_evidence)==0 and bool(control)}


def native_header_regression(out):
    import publication as p, objdiff, hybrid, toolchain
    root=fixture(out/'cross-tu',{'A.cpp':'extern "C" int control(){return 5;}\n',
              'B.cpp':'#include "Shared.h"\nextern "C" int victim(){return SIDE_VALUE;}\n'})
    (root/'decomp/include/Shared.h').write_text('#define SIDE_VALUE 7\n')
    artifacts=out/'cross-tu-artifacts';artifacts.mkdir(exist_ok=True)
    compiled=[]
    def native_value(source, field):
        index=len(list(artifacts.glob('*.exe')))
        main=artifacts/f'v{index}.cpp';main.write_text(f'#include <cstdio>\nextern "C" int {field}(); int main(){{std::printf("%d",{field}());}}\n')
        exe=artifacts/f'v{index}.exe'
        inc=source.parent.parent/'include'
        run(['g++','-std=gnu++98','-O2','-I',inc,source,main,'-o',exe])
        return int(run([exe]))
    before=native_value(root/'decomp/src/B.cpp','victim')
    stage=p.Stage(root)
    (stage.path/'decomp/include/Shared.h').write_text('#define SIDE_VALUE 99\n')
    (stage.path/'decomp/src/A.cpp').write_text('extern "C" int control(){return 5;}\nextern "C" int added(){return 6;}\n')
    def compare(source,*args,**kwargs):
        name='control' if source.name=='A.cpp' else 'victim'
        value=native_value(source,name)
        expected=5 if name=='control' else 7
        row={'address':'0x100' if name=='control' else '0x200','status':'MATCH' if value==expected else 'DIFF',
             'observed':value,'expected':expected}
        compiled.append({'source':source.name,**row})
        return {'functions':[row], 'unknown':[], 'source':str(source)}
    def build(**kwargs):
        exe=artifacts/'selftest.exe';main=artifacts/'selftest.cpp'
        main.write_text('#include <cstdio>\nextern "C" int control(); int main(){if(control()!=5)return 1; std::puts("tlhybrid: control PASS (0)\\ntlhybrid: 1 tests, 0 failed");return 0;}')
        run(['g++','-std=gnu++98','-O2','-I',stage.path/'decomp/include',*sorted((kwargs['src']).glob('*.cpp')),main,'-o',exe])
        return exe,None
    def selftest(exe,loader):
        proc=subprocess.run([str(exe)],text=True,capture_output=True,timeout=10)
        return proc.returncode,proc.stdout.splitlines()
    with patch.object(objdiff,'Original',return_value=object()),patch.object(objdiff,'compare_source',side_effect=compare), \
         patch.object(hybrid,'build',side_effect=build),patch.object(hybrid,'selftest',side_effect=selftest), \
         patch.object(toolchain,'parallel_map',side_effect=lambda fn,items:[fn(x) for x in items]):
        stage.validate()
        changed=stage.publish()
    after=native_value(root/'decomp/src/B.cpp','victim')
    return {'proof_type':'real Stage.validate/publish, native C++98 synthetic programs; replacement comparator and one native control test, no original game',
            'native_value_before':before,'native_value_after':after,'comparison_rows':compiled,
            'published':changed,'detected':before==7 and after==99 and any(r['status']=='DIFF' for r in compiled)}


def eh_preservation(out):
    import objdiff,candidate
    base=out/'eh';base.mkdir(exist_ok=True)
    source='#include "Types.h"\nextern void raise_value();\nint probe() { try { raise_value(); return 0; } catch(ErrorType) { return 7; } }\n'
    main='#include <cstdio>\nvoid raise_value(){throw 1;}\nint probe(); int main(){try{std::printf("%d",probe());}catch(...){std::printf("99");}}\n'
    rows=[];sources=[]
    for name,typ in [('before','int'),('after','double')]:
        d=base/name;d.mkdir(exist_ok=True)
        s=d/'Probe.cpp';s.write_text(source);sources.append(s)
        (d/'Types.h').write_text(f'typedef {typ} ErrorType;\n');(d/'main.cpp').write_text(main)
        obj=d/'probe.o';exe=d/'probe.exe'
        run(['g++','-std=gnu++98','-O2','-fno-reorder-blocks-and-partition','-c',s,'-o',obj])
        run(['g++','-std=gnu++98',obj,d/'main.cpp','-o',exe])
        mine=objdiff.object_functions(obj)['_Z5probev']
        rows.append({'address':'0x100','status':'DIFF','code':objdiff.code_digest(mine['norm']),
                     'metadata_reasons':mine['metadata_reasons'],'object_digest':sha(obj),
                     'norm':mine['norm'],'execution':int(run([exe]))})
    f={'address':'0x100','demangled':'probe()','scope':'','method':'probe','params':'','cv':'','kind':'function'}
    kept=candidate.preserve_existing(sources[0],sources[1],{'0x100':rows[0]},[rows[1]],{'functions':{'0x100':f}})
    return {'proof_type':'real normalization and preserve_existing; native GCC system C++98 objects/execution, no Torchlight ELF',
            'rows':rows,'same_function_source':sources[0].read_bytes()==sources[1].read_bytes(),
            'preserve_existing':kept,'detected':kept and rows[0]['execution']!=rows[1]['execution']}


def publication_contract(out):
    import publication as p
    root=fixture(out/'validation-snapshot')
    (root/'decomp/hybrid/tests/Control.cpp').write_text('// tested version\n')
    stage=p.Stage(root)
    (stage.path/'decomp/src/Unit.cpp').write_text('int value(){return 9;}\n')
    stage.validated=p.tree_state(stage.path) # model a completed validation; do not claim game test ran
    initial=stage.validated
    (stage.path/'decomp/hybrid/tests/Control.cpp').write_text('// changed after validation\n')
    (stage.path/'decomp/config.json').write_text('{"changed_after_validation":true}\n')
    (stage.path/'decomp/hybrid/tests/New.cpp').write_text('// new necessary regression fixture\n')
    token_unchanged=initial==p.tree_state(stage.path)
    published=stage.publish()
    return {'proof_type':'real Stage receipt/publication rules; completed validation token modeled explicitly',
            'test_config_changes_invalidate_stamp':not token_unchanged,'published_files':published,
            'new_test_published':(root/'decomp/hybrid/tests/New.cpp').exists(),
            'live_old_test':(root/'decomp/hybrid/tests/Control.cpp').read_text(),
            'detected':token_unchanged and not(root/'decomp/hybrid/tests/New.cpp').exists()}


def crash_publication(out):
    import publication as p
    root=fixture(out/'crash')
    baseline=p.tree_state(root)
    child_program = """
import os,sys
from pathlib import Path
sys.dont_write_bytecode=True
sys.path.insert(0,sys.argv[1])
import publication as p
root=Path(sys.argv[2])
stage=p.Stage(root)
(stage.path/'decomp/src/Unit.cpp').write_text('new source\\n')
(stage.path/'decomp/include/Unit.h').write_text('new header\\n')
stage.validated=p.tree_state(stage.path)
original=stage._replace
def stop_after_first(name,data):
    original(name,data)
    os._exit(77)
stage._replace=stop_after_first
stage.publish()
"""
    result=subprocess.run([sys.executable,'-c',child_program,str(Path(p.__file__).parent),str(root)],
                          text=True,capture_output=True,timeout=10)
    exit_code=result.returncode
    final=p.tree_state(root)
    changes=[n for n in final if final[n]!=baseline[n]]
    return {'proof_type':'real child process exits immediately after first real _replace, validation token modeled; temp files only',
            'child_exit':exit_code,'changed_files':changes,
            'source':(root/'decomp/src/Unit.cpp').read_text(),'header':(root/'decomp/include/Unit.h').read_text(),
            'detected':exit_code==77 and len(changes)==1}


def independent_publications(out):
    import publication as p
    root=fixture(out/'parallel',{'A.cpp':'int a(){return 1;}\n','B.cpp':'int b(){return 2;}\n'})
    a,b=p.Stage(root),p.Stage(root)
    (a.path/'decomp/src/A.cpp').write_text('int a(){return 3;}\n')
    (b.path/'decomp/src/B.cpp').write_text('int b(){return 4;}\n')
    a.validated=p.tree_state(a.path);b.validated=p.tree_state(b.path)
    changed=a.publish()
    try:
        b.publish();error=None
    except RuntimeError as e:
        error=str(e)
    return {'proof_type':'real stages and publication, simulated prior validation; no game execution',
            'first_published':changed,'second_error':error,'second_work_preserved_at':str(b.path),
            'interpretation':'safe conservative refusal, not false acceptance; automatic rebase/revalidation is missing',
            'detected':bool(error)}


def cache_modes(out):
    import candidate as c,publication as p
    root=fixture(out/'mode-cache')
    source=root/'decomp/src/Unit.cpp'
    old=source.read_text()
    s=p.Stage(root);target=s.path/'decomp/src/Unit.cpp';target.write_text(old+'int added(){return 8;}\n')
    f={'address':'0x1','demangled':'value()','params':'','cv':'','kind':'function'}
    prior={'address':'0x1','status':'DIFF','code':'unchanged','metadata_reasons':['EH LSDA equivalence unverified']}
    added={'address':'0x2','status':'MATCH','code':'new'}
    def compare(path,*args,**kwargs):
        return {'functions':[prior] if Path(path)==source else [prior,added], 'unknown':[], 'object_digest':'object'}
    db={'tus':[{'name':'Unit.cpp','kind':'game'}],'functions':{'0x1':f}}
    with patch.object(c.elfdb,'load_db',return_value=db),patch.object(c.evidence,'input_digest',return_value='same'), \
         patch.object(c.objdiff,'Original',return_value=object()),patch.object(c.objdiff,'compare_source',side_effect=compare), \
         patch.object(c.promote,'promote'):
        first=c.evaluate('Unit.cpp',target,root=root,stage=s,incremental=False)
        second=c.evaluate('Unit.cpp',target,root=root,stage=s,incremental=True)
        for f in (root/'build-decomp/candidate-failures').glob('*.json'):f.unlink()
        cold=c.evaluate('Unit.cpp',target,root=root,stage=s,incremental=True)
    return {'proof_type':'real candidate decision and cache; compiler/digest mocked with explicit records',
            'first_nonincremental':first['status'],'second_incremental':second['status'],
            'second_used_cache':second.get('cached_failure',False),'fresh_incremental':cold['status'],
            'detected':second['status']!='MATCH' and cold['status']=='MATCH'}


def stage_cache(out):
    import publication as p,toolchain as t
    root=fixture(out/'cache-isolation')
    a,b=p.Stage(root),p.Stage(root)
    entries=[]
    for stage in (a,b):
        with stage.activate():
            src=stage.path/'decomp/src/Unit.cpp'
            cmd=['g++','-I',str(stage.path/'decomp/include'),'-c']
            index,_=t._cache_lookup(cmd,src,'identical-preprocessed-input')
            entries.append({'cache':str(t.CC_CACHE),'index':str(index),
                            'content_hash':sha(src), 'command':cmd,
                            'digest':t._digest(cmd,src,[],'identical-preprocessed-input')})
    return {'proof_type':'real Stage.activate/cache identity functions, no compilation or speed claim',
            'stages':entries,'same_source':entries[0]['content_hash']==entries[1]['content_hash'],
            'same_cache_location':entries[0]['cache']==entries[1]['cache'],
            'same_content_key':entries[0]['digest']==entries[1]['digest'],
            'detected':entries[0]['content_hash']==entries[1]['content_hash'] and entries[0]['digest']!=entries[1]['digest']}


def scope_probe():
    import no_llm_loop,candidate,objdiff_eh
    return {'proof_type':'static source lines',
            'no_llm_descriptor_filter':next(l.strip() for l in Path(no_llm_loop.__file__).read_text().splitlines() if 'tasks = ' in l),
            'providers':next(l.strip() for l in Path(no_llm_loop.__file__).read_text().splitlines() if 'choices=(' in l),
            'candidate_requires_match':next(l.strip() for l in Path(candidate.__file__).read_text().splitlines() if 'any(r["status"] != "MATCH" for r in added)' in l),
            'lsda_policy':next(l.strip() for l in Path(objdiff_eh.__file__).read_text().splitlines() if 'EH LSDA equivalence unverified' in l)}


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--project',type=Path,required=True);ap.add_argument('--out',type=Path,required=True)
    args=ap.parse_args();project=args.project.resolve();out=args.out.resolve();out.mkdir(parents=True,exist_ok=True)
    sys.dont_write_bytecode=True;sys.path.insert(0,str(project/'tools/decomp'))
    needed=['g++','objdump','readelf']
    for n in needed:
        if not shutil.which(n):raise SystemExit('missing host tool '+n)
    actions={
        'queue_progress':lambda:queue_probe(out),
        'coverage_wiring':lambda:coverage_probe(project),
        'cross_tu_regression':lambda:native_header_regression(out),
        'eh_preservation':lambda:eh_preservation(out),
        'validation_snapshot':lambda:publication_contract(out),
        'interrupted_publication':lambda:crash_publication(out),
        'independent_publications':lambda:independent_publications(out),
        'failure_cache_modes':lambda:cache_modes(out),
        'stage_cache':lambda:stage_cache(out),
        'provider_scope':scope_probe,
    }
    summary={'schema':1,'project':str(project),'host_compiler':run(['g++','--version']).splitlines()[0],
             'original_elf_used':False,'pinned_gcc_used':False,'models_called':False,'probes':{}}
    for name,fn in actions.items():
        try:
            row=fn();row['probe_completed']=True
        except BaseException as e:
            import traceback
            row={'probe_completed':False,'error':str(e),'traceback':traceback.format_exc()}
        summary['probes'][name]=row
        (out/f'{name}.json').write_text(json.dumps(row,indent=2,ensure_ascii=False)+'\n')
        print(name, 'complete' if row['probe_completed'] else 'ERROR',row.get('detected',''),flush=True)
    (out/'summary.json').write_text(json.dumps(summary,indent=2,ensure_ascii=False)+'\n')
    return int(any(not r['probe_completed'] for r in summary['probes'].values()))

if __name__=='__main__':raise SystemExit(main())
