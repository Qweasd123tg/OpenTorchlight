import argparse, copy, hashlib, importlib.util, json, statistics, sys, time
from collections import Counter, defaultdict
from pathlib import Path
parser = argparse.ArgumentParser(description="Verify and benchmark the optimizer without compiling or executing game code.")
for arg in ('kit', 'package', 'root', 'output'):
    parser.add_argument('--' + arg, type=Path, required=True)
parser.add_argument('--repeats', type=int, default=3)
a=parser.parse_args()
if a.repeats < 1 or a.repeats > 10: parser.error('--repeats must be 1..10')
k,p,w,b=[x.resolve() for x in (a.kit,a.package,a.root,a.output)]
if any(b.is_relative_to(x) for x in (w/'decomp', w/'tools', w/'third_party', k/'original')):
    parser.error('--output must not be inside source/original directories')
if b.exists() and any(b.iterdir()): parser.error('--output must be a new empty directory')
b.mkdir(parents=True,exist_ok=True)
sys.path.insert(0,str(w/'tools/decomp'))
import llm_definitions as d
from smallmatch_trial_cache import TrialMemo
report={'mode':'metadata_and_archived_trial_replay_only','compiler_executions':0,'game_executions':0,'new_match_claims':0}
db=json.loads((k/'reference/elfdb.json').read_text()); targets=json.loads((k/'targets.json').read_text()); report.update(database_functions=len(db['functions']),targets=len(targets))
old_times=[];new_times=[]
for _ in range(a.repeats):
 t=time.perf_counter();old=[sorted(d.closure(f,db)) for f in targets];old_times.append(time.perf_counter()-t)
 t=time.perf_counter();index=d.DefinitionIndex(db);new=[sorted(index.closure(f)) for f in targets];new_times.append(time.perf_counter()-t)
 assert old==new
report['abi_lookup']={'old_seconds':old_times,'new_seconds_including_index_construction':new_times,'median_speedup':statistics.median(old_times)/statistics.median(new_times),'all_3630_groups_identical':True}
print('ABI',report['abi_lookup'],flush=True)
units={}
for prefix in ('existing','candidate'):
 for path in sorted((p/'reports/units').glob(prefix+'-*.json')):
  units[path.name[len(prefix)+1:-5].lower()]=json.loads(path.read_text())
t=time.perf_counter();old=[d.verdict(f,units.get(f['tu_name'].lower(),{'functions':[]}),db) for f in targets];old_time=time.perf_counter()-t
t=time.perf_counter();index=d.DefinitionIndex(db);new=[index.verdict(f,units.get(f['tu_name'].lower(),{'functions':[]}) ) for f in targets];new_time=time.perf_counter()-t
assert old==new
report['archived_verdicts']={'old_seconds':old_time,'new_seconds':new_time,'speedup':old_time/new_time,'all_3630_verdicts_and_reasons_identical':True,'results':dict(Counter(x[0] for x in new)),'note':'Reads existing comparison reports; it does not rerun their compilation or establish fresh MATCH.'}
print('VERDICTS',report['archived_verdicts'],flush=True)
# Frozen-trace replay: assess memo behavior, not end-to-end compilation speed.
folders=defaultdict(list)
for f in (p/'reports/trials').rglob('*.cpp'):
 if f.is_file() and (f.parent/'comparison.json').is_file():
  folders[(f.relative_to(p/'reports/trials').parts[0],f.name)].append(f)
actual=0;hits=0;requests=0;error_bypass=0
output=b/'replay';output.mkdir(exist_ok=True)
for key,files in sorted(folders.items()):
 files.sort(key=lambda f:int(f.parent.name.split('-')[-1])); reference={}
 def evaluate(rows,phase,address):
  global actual
  f=Path(rows[0]['archived_path']);actual+=1
  r=json.loads((f.parent/'comparison.json').read_text())
  dst=output/(str(actual)+'.cpp');dst.write_text(f.read_text());r['_trial_source']=str(dst)
  return r
 memo=TrialMemo(evaluate,lambda rows:Path(rows[0]['archived_path']).read_text(),lambda:'immutable-archive-trace-not-live-MATCH')
 for f in files:
  expected=json.loads((f.parent/'comparison.json').read_text())
  result=memo([{'archived_path':str(f)}],'trace',None)
  assert result.get('object_digest')==expected.get('object_digest')
  assert result['functions']==expected['functions']
  assert result.get('unknown',[])==expected.get('unknown',[])
  assert bool(result.get('error'))==bool(expected.get('error'))
 requests+=memo.stats['requests'];hits+=memo.stats['hits'];error_bypass+=memo.stats['errors_not_cached']
report['trial_replay']={'requests':requests,'distinct_evaluations_with_conservative_memo':actual,'avoided_duplicates':hits,'errors_not_cached':error_bypass,'all_results_identical':True,'note':'Replays saved reports with a frozen input token; not a measurement of real compiler-time speedup.'}
print('REPLAY',report['trial_replay'],flush=True)
(b/'benchmark.json').write_text(json.dumps(report,indent=2)+'\n')

def load(name,path):
 spec=importlib.util.spec_from_file_location(name,path);mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod);return mod
import smallmatch, smallmatch_families
oldg=load('otl_before_generator',p/'tools/decomp/smallmatch.py');oldf=load('otl_before_families',p/'tools/decomp/smallmatch_families.py')
results=[];seconds=[]
for label,gen,fam in [('before',oldg,oldf),('after',smallmatch,smallmatch_families)]:
 t=time.perf_counter();g=gen.Generator(k,w);rows=[]
 for f in g.targets:
  errors=[]
  for provider in (g.generate,lambda f:fam.generate(g,f)):
   try:
    r=provider(f);rows.append({'address':f['address'],'candidate':r});break
   except (smallmatch.Unsupported,oldg.Unsupported) as e:errors.append(str(e))
  else: rows.append({'address':f['address'],'errors':errors})
 elapsed=time.perf_counter()-t
 print(label,elapsed,'hypotheses',sum('candidate' in x for x in rows),flush=True)
 results.append(rows);seconds.append(elapsed)
assert results[0]==results[1]
out={'mode':'generation_only_no_compiler','targets':len(results[0]),'before_seconds':seconds[0],'after_seconds':seconds[1],'speedup':seconds[0]/seconds[1], 'all_hypotheses_and_rejection_reasons_identical':True,'result_sha256':hashlib.sha256(json.dumps(results[0],sort_keys=True).encode()).hexdigest(),'hypotheses':sum('candidate' in x for x in results[0]),'new_match_claims':0}
report['generator']=out
(b/'benchmark.json').write_text(json.dumps(report,indent=2)+'\n')
print('GENERATOR',out,flush=True)
