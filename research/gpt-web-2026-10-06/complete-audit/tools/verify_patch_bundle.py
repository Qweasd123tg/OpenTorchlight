#!/usr/bin/env python3
"""Apply bundled patches ONLY to a temporary copy. Does not run a game or a model."""
from __future__ import annotations
import argparse, ast, json, os, shutil, subprocess, sys, tempfile
from pathlib import Path

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('repo',type=Path);p.add_argument('--out',type=Path,required=True)
    a=p.parse_args();root=a.repo.resolve();out=a.out.resolve()
    if out.is_relative_to(root):p.error('Output must be outside the repository')
    if not (root/'tools/decomp/objdiff.py').is_file():p.error('Wrong source root')
    out.mkdir(parents=True,exist_ok=True)
    package=Path(__file__).resolve().parent.parent
    env=dict(os.environ,PYTHONDONTWRITEBYTECODE='1')
    report={'scope':'Patch compatibility and Python regressions only; no original ELF or GCC 4.4.7 run.', 'patches':[]}
    with tempfile.TemporaryDirectory(prefix='otl-combined-') as d:
        tmp=Path(d)/'repo';shutil.copytree(root,tmp,ignore=shutil.ignore_patterns('.git','__pycache__','build-decomp'))
        for patch in sorted((package/'patches').glob('*.patch')):
            check=subprocess.run(['git','apply','--check',str(patch)],cwd=tmp,capture_output=True,text=True,env=env)
            report['patches'].append({'name':patch.name,'applies_after_previous':check.returncode==0,'diagnostic':check.stderr})
            if check.returncode:raise RuntimeError(check.stderr)
            subprocess.run(['git','apply',str(patch)],cwd=tmp,check=True,env=env)
        for s in (tmp/'tools/decomp').glob('*.py'):ast.parse(s.read_text())
        run=subprocess.run([sys.executable,'-m','unittest','discover','-s','tools/decomp','-p','test_*.py','-v'],cwd=tmp,text=True,capture_output=True,env=env)
        (out/'patched_unittests.log').write_text(run.stdout+run.stderr)
        report['unit_test_process_returncode']=run.returncode
        report['python_syntax_valid']=True
        # Pin classification from actual log; retain full failures, never convert errors into PASS.
        report['unit_test_ok_lines']=sum(line.endswith(' ... ok') for line in run.stderr.splitlines())
        report['unit_test_error_lines']=[line for line in run.stderr.splitlines() if line.endswith(' ... ERROR')]
        regression=package/'references/test_drafts.py'
        if regression.exists():
            r=subprocess.run([sys.executable,str(regression),str(root),str(tmp),str(out/'draft_bundle_regressions.json')],env=env,text=True,capture_output=True)
            (out/'draft_bundle_regressions.log').write_text(r.stdout+r.stderr)
            report['draft_regression_returncode']=r.returncode
        report['changed_paths']=[]
        for patch in sorted((package/'patches').glob('*.patch')):
            for line in patch.read_text().splitlines():
                if line.startswith('+++ b/'):
                    rel=line[6:];report['changed_paths'].append(rel)
    (out/'patch_bundle_check.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n')
    print(json.dumps(report,ensure_ascii=False,indent=2))
    # Test suite may genuinely require the missing target toolchain. Report that, not a fake success.
    return 0 if (report['unit_test_process_returncode'] == 0 and report.get('draft_regression_returncode', 0) == 0) else 1
if __name__=='__main__':raise SystemExit(main())
