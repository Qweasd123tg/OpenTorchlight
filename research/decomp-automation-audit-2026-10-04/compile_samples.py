import sys,re,json,pathlib,contextlib,io
sys.path.insert(0,'tools/decomp')
import elfdb,ghidra_cpp,ghidra_draft,objdiff
D=elfdb.load_db(); O=objdiff.Original(db=D); root=pathlib.Path('build-decomp/automation-audit'); results=[]
addresses=['0x803100','0xd5e7c0','0x6ff300','0xe4e3a0','0xa60190','0xe4f0f0','0xc78930','0xc731f0']
T={t['id']:t['name'] for t in D['tus']}
for a in addresses:
 f=D['functions'][a];tu=T[f['tu']];text=(pathlib.Path('decomp/src')/tu).read_text();span=ghidra_draft.find_definition(text,f)
 if a=='0xc731f0':
  start=text.index('bool CFileReader::ReadFile(const std::wstring& filename)'); end=ghidra_cpp.balanced_block_end(text,start); span=(start,end)
 row={'address':a,'name':f['demangled'],'bytes':f['size']}
 if not span: row['status']='not-located'; results.append(row);continue
 draft=(root/(a+'.converted.cpp')).read_text(); body=draft[draft.find('\n{'):] if '\n{' in draft else draft
 head=text[span[0]:span[1]];signature=head[:head.find('{')].rstrip();inside=signature[signature.find('(')+1:];inside=inside[:ghidra_cpp.closing_paren(inside)]
 for i,p in enumerate(ghidra_cpp.split_args(inside),1):
  n=re.findall(r'(\w+)\s*(?:\[\d*\])?$',p.strip())
  if n:body=re.sub(rf'\bparam_{i}\b',n[0],body)
 work=root/a;work.mkdir(exist_ok=True);path=work/tu;path.write_text(text[:span[0]]+signature+body+text[span[1]:])
 errors=io.StringIO()
 try:
  with contextlib.redirect_stderr(errors): result=objdiff.compare_source(path,O,extra=ghidra_draft.EXTRA,quiet=True)
  found=[r for r in result['functions'] if r.get('address')==a];row['status']=found[0]['status'] if found else 'missing';row['comparison']=found
 except SystemExit as e:
  row['status']='compile-error'; errors.write(str(e));row['first_errors']=[s for s in errors.getvalue().splitlines() if 'error:' in s][:6]
 (work/'errors.txt').write_text(errors.getvalue());results.append(row);print(json.dumps(row),flush=True)
(root/'compile-samples.json').write_text(json.dumps(results,indent=2))
