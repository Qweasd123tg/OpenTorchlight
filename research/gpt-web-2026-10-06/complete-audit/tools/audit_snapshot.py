#!/usr/bin/env python3
"""Read-only inventory of an OpenTorchlight source snapshot; no builds, models or games.
Outputs are derived evidence, NOT a replacement for decomp/check.py acceptance.
Python 3.10+; standard library only.
"""
from __future__ import annotations
import argparse, ast, collections, csv, hashlib, json, re
from pathlib import Path

def sha(path: Path) -> str:
    h = hashlib.sha256()
    with path.open('rb') as f:
        for b in iter(lambda: f.read(1024 * 1024), b''): h.update(b)
    return h.hexdigest()

def text(p: Path) -> str:
    return p.read_text(encoding='utf-8', errors='replace') if p.is_file() else ''

def safe_files(root: Path):
    skip = {'.git', '__pycache__', 'build-decomp'}
    return sorted(p for p in root.rglob('*') if p.is_file() and not p.is_symlink()
                  and not any(s in skip for s in p.relative_to(root).parts))

def parse_symbols(s: str):
    out = {}
    for line in s.splitlines():
        m = re.match(r'^([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+([a-zA-Z])\s+(.+)$', line)
        if not m: continue
        addr, size, kind, name = m.groups()
        if kind not in 'TtWw': continue
        a = hex(int(addr, 16))
        row = out.setdefault(a, {'address': a, 'size': int(size, 16), 'names': []})
        row['size'] = max(row['size'], int(size, 16))
        if name not in row['names']: row['names'].append(name)
    return out

def tool_index(root: Path):
    rows = []
    for p in sorted((root/'tools/decomp').rglob('*.py')):
        code = text(p)
        try: tree = ast.parse(code)
        except SyntaxError as e:
            rows.append({'path': str(p.relative_to(root)), 'error': str(e)}); continue
        functions = []
        for n in ast.walk(tree):
            if isinstance(n, (ast.FunctionDef, ast.AsyncFunctionDef, ast.ClassDef)):
                functions.append({'name': n.name, 'line': n.lineno,
                                  'end_line': n.end_lineno,
                                  'doc': (ast.get_docstring(n) or '').split('\n')[0]})
        imports = sorted({n.module or '' for n in ast.walk(tree) if isinstance(n, ast.ImportFrom)} |
                         {a.name for n in ast.walk(tree) if isinstance(n, ast.Import) for a in n.names})
        rows.append({'path': str(p.relative_to(root)), 'lines': len(code.splitlines()),
                     'doc': ast.get_docstring(tree), 'imports': imports,
                     'definitions': sorted(functions, key=lambda x:x['line'])})
    return rows

def include_graph(root: Path):
    hdr = {p.name: p for p in (root/'decomp/include').glob('*.h')}
    direct = {}
    for p in list(hdr.values())+list((root/'decomp/src').glob('*.cpp')):
        direct[str(p.relative_to(root))] = sorted(set(re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)[>"]', text(p),re.M)))
    result = []
    for name in sorted(hdr):
        users = []
        for src in sorted((root/'decomp/src').glob('*.cpp')):
            todo = list(direct[str(src.relative_to(root))]); seen = set()
            while todo:
                n=todo.pop()
                if n in seen: continue
                seen.add(n)
                if n in hdr: todo.extend(direct[str(hdr[n].relative_to(root))])
            if name in seen: users.append(src.name)
        result.append({'header':name,'source_dependents':len(users),'sources':users})
    return sorted(result,key=lambda r:(-r['source_dependents'], r['header']))

def largest_corpus(root: Path, symbols):
    p=root/'research/decomp-automation-audit-2026-10-04/measured.json'
    if not p.is_file(): return {'available':False}
    rows=json.loads(text(p)); sorted_rows=sorted(rows,key=lambda r:-r['bytes'])
    total=sum(r['bytes'] for r in rows)
    targets=[]
    src={p.name.lower():p for p in (root/'decomp/src').glob('*.cpp')}
    for r in sorted_rows:
        rr=dict(r); s=src.get(r['tu'].lower())
        rr['source_file_present_now']=s is not None
        rr['source_relative_path']=str(s.relative_to(root)) if s else None
        rr['acceptance_warning']='accepted is from a historical measurement; file existence is not acceptance'
        targets.append(rr)
    per_tu=collections.defaultdict(lambda:{'functions':0,'bytes':0})
    for r in rows:
        per_tu[r['tu']]['functions']+=1; per_tu[r['tu']]['bytes']+=r['bytes']
    return {'available':True,'source':str(p.relative_to(root)), 'functions':len(rows),'bytes':total,
            'historically_accepted':sum(bool(r.get('accepted')) for r in rows),
            'top_n_bytes':{str(n):sum(r['bytes'] for r in sorted_rows[:n]) for n in (10,20,50,100,200)},
            'top_40':targets[:40], 'all_functions':targets,
            'by_tu':sorted([dict(tu=k,**v) for k,v in per_tu.items()],key=lambda r:-r['bytes'])}

def callers(root: Path, symbols):
    p=root/'research/original-callgraph.tsv'
    if not p.is_file(): return []
    d=collections.defaultdict(set)
    with p.open(encoding='utf-8') as f:
        for r in csv.DictReader(f,delimiter='\t'):
            try: a=hex(int(r['callee_address'],16)); c=hex(int(r['caller_address'],16))
            except (KeyError, ValueError): continue
            if a!=c:d[a].add(c)
    out=[]
    for a, cs in d.items():
        sym=symbols.get(a)
        if not sym: continue
        name=sym['names'][0]
        if not re.match(r'^C[A-Z]\w*::',name): continue
        out.append({'address':a,'name':name,'bytes':sym['size'],
                    'distinct_direct_callers':len(cs),
                    'caller_bytes_sum':sum(symbols.get(c,{}).get('size',0) for c in cs),
                    'warning':'Static archived call graph; weights overlap, incomplete for indirect calls.'})
    return sorted(out,key=lambda r:-r['distinct_direct_callers'])

def run(root: Path, output: Path):
    root=root.resolve(); output=output.resolve()
    if not (root/'decomp/config.json').is_file(): raise ValueError('Not an OpenTorchlight decomp source root')
    if output.is_relative_to(root): raise ValueError('Use an output directory outside the source tree')
    output.mkdir(parents=True,exist_ok=True)
    files=safe_files(root)
    manifest=[{'path':str(p.relative_to(root)),'size':p.stat().st_size,'sha256':sha(p)} for p in files]
    syms=parse_symbols(text(root/'research/original-symbols.txt'))
    indices=tool_index(root); large=largest_corpus(root,syms)
    README=text(root/'decomp/README.md')
    last_lines=[{'line':i,'text':s} for i,s in enumerate(README.splitlines(),1)
                if re.search(r'(?:Итог check\.py|[0-9]+/5247|[0-9]+ из 5247)',s)]
    binary_names=[]
    for p in files:
        if p.stat().st_size<4: continue
        with p.open('rb') as f: magic=f.read(4)
        if magic==b'\x7fELF' or magic[:2]==b'MZ':binary_names.append(str(p.relative_to(root)))
    unit_tests=[p.name for p in (root/'tools/decomp').glob('test_*.py')]
    runtime_tests=list((root/'decomp/hybrid/tests').glob('*.cpp'))
    accepted=json.loads(text(root/'decomp/autotests.json') or '{}')
    minimum_mutations=[dict(address=a,**r) for a,r in accepted.items() if r.get('tried',0)<5]
    overview={'scope':'Source snapshot read-only inventory; no current ELF/GCC acceptance run.',
              'files':len(files),'total_file_bytes':sum(x['size'] for x in manifest),
              'decomp_sources':len(list((root/'decomp/src').glob('*.cpp'))),
              'decomp_headers':len(list((root/'decomp/include').glob('*.h'))),
              'active_python_tools_and_tests':len(indices),
              'active_python_lines':sum(r.get('lines',0) for r in indices),
              'active_java_files':len(list((root/'tools/decomp').rglob('*.java'))),
              'runtime_test_cpp_files':len(runtime_tests),
              'runtime_test_macro_count':sum(len(re.findall(r'^TL_TEST\(',text(p),re.M)) for p in runtime_tests),
              'unit_test_files':unit_tests,'recorded_autotests':len(accepted),
              'autotests_fewer_than_5_mutants':minimum_mutations,
              'native_executable_files_in_archive':binary_names,
              'symbol_addresses_with_size':len(syms),
              'historical_progress_lines':last_lines[-12:],
              'config':json.loads(text(root/'decomp/config.json')),
              'largest_corpus':{k:v for k,v in large.items() if k not in ('all_functions','by_tu')},
              'caution':'No counts from historical and active tracking are added. Native prerequisites may exist outside this archive.'}
    docs={'source_manifest.json':manifest,'snapshot.json':overview,'tool_index.json':indices,
          'header_dependencies.json':include_graph(root),'large_functions.json':large,
          'helper_fanout.json':callers(root,syms)}
    for name,data in docs.items():
        (output/name).write_text(json.dumps(data,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({k:v for k,v in overview.items() if k not in ('largest_corpus','config','unit_test_files','historical_progress_lines','autotests_fewer_than_5_mutants')},ensure_ascii=False,indent=2))
    return overview

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('root',type=Path); p.add_argument('--out',required=True,type=Path)
    a=p.parse_args()
    try: run(a.root,a.out)
    except (OSError,ValueError,json.JSONDecodeError) as e: p.exit(2,f'Audit failed: {e}\n')
if __name__=='__main__': main()
