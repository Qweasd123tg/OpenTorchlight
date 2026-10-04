import sys,re,json,pathlib,signal,time
sys.path.insert(0,'tools/decomp')
import elfdb,ghidra_cpp
D=elfdb.load_db(); F=D['functions']; T={t['id']:t for t in D['tus']}; A=set(json.load(open('build-decomp/progress.json'))['accepted'])
methods=ghidra_cpp.known_methods(D); signatures=ghidra_cpp.signatures_of(D); enums=ghidra_cpp.parse_enums()
patterns={'string_cleanup':r'_S_empty_rep_storage|_M_destroy|_M_dispose','tree_internals':r'_Rb_tree|_M_(?:left|right|parent)|__rb_tree','vector_internals':r'_M_(?:start|finish|end_of_storage)|_M_(?:insert_aux|realloc_insert)','array_internals':r'm_pData|m_nCapacity|m_nCount|m_nGrowBy','nan_guard':r'!?NAN\s*\(','unknown_abi':r'extraout_|in_stack_|unaff_|__return_storage_ptr__','unwind':r'_Unwind_Resume'}
def timedout(*_): raise TimeoutError()
signal.signal(signal.SIGALRM,timedout)
rows=[]
for f in F.values():
 if T.get(f['tu'],{}).get('kind')!='game' or f['kind'] not in ('function','ctor','dtor','static') or f['size']<1024: continue
 path=pathlib.Path('build-decomp/drafts')/T[f['tu']]['name']/'raw'/(f['address']+'.c')
 if not path.exists(): continue
 raw=path.read_text()
 r={'address':f['address'],'name':f['demangled'],'tu':T[f['tu']]['name'],'bytes':f['size'],'accepted':f['address'] in A,'raw_lines':len(raw.splitlines()),'raw_hits':{k:len(re.findall(p,raw)) for k,p in patterns.items()}}
 if r['accepted']:
  signal.alarm(5); start=time.time()
  try:
   conv=ghidra_cpp.convert(raw,methods,f,signatures,enums)
   r.update(converted_lines=len(conv.splitlines()),converted_hits={k:len(re.findall(p,conv)) for k,p in patterns.items()})
   (pathlib.Path('build-decomp/automation-audit')/(f['address']+'.converted.cpp')).write_text(conv)
  except TimeoutError: r['conversion_timeout_seconds']=5
  finally: signal.alarm(0)
  r['seconds']=round(time.time()-start,3)
  print(r['address'],r['bytes'],r['raw_lines'],r.get('converted_lines','TIMEOUT'),flush=True)
 rows.append(r)
pathlib.Path('build-decomp/automation-audit/measured.json').write_text(json.dumps(rows,indent=2))
for label,rs in [('accepted',[r for r in rows if r['accepted']]),('all_cached_large',rows)]:
 print(label,len(rs),sum(r['bytes'] for r in rs),flush=True)
 for k in patterns: print(k, sum(r['raw_hits'][k]>0 for r in rs),flush=True)
print('SYNTHETIC',repr(ghidra_cpp.tidy_expressions('if (NAN(x) && enabled) { record(); }')),flush=True)
