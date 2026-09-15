#!/usr/bin/env python3
"""Author-built ADMs: authoritative, absent, corrupt, decoy and mixed-case path."""
import argparse, subprocess, tempfile, zipfile
from pathlib import Path
from make_ai_cooldown_fixture import adm
from make_item_cycle_fixture import group

def catalog(index):
    return adm(group('EFFECTS',children=[group('EFFECT',[('NAME',5,'HASTE' if i==index else f'NAME_{i}')]) for i in range(145)]))

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--probe',type=Path,required=True);a=p.parse_args()
    exact='media/EffectsList.dat.adm';decoy='media/somewhere/lookalike.adm'
    cases=[({exact:catalog(22)},'FOUND 22'),({exact:catalog(22),decoy:catalog(0)},'FOUND 22'),
           ({decoy:catalog(22)},'NONE'),({exact:b'corrupt',decoy:catalog(22)},'INVALID'),
           ({'MEDIA/EFFECTSLIST.DAT.ADM':catalog(22)},'FOUND 22'),({},'NONE')]
    with tempfile.TemporaryDirectory(prefix='ot-effect-catalog-') as d:
        for n,(files,expected) in enumerate(cases):
            path=Path(d)/f'{n}.zip'
            with zipfile.ZipFile(path,'w') as z:
                for name,data in files.items():z.writestr(name,data)
            r=subprocess.run([str(a.probe.resolve()),str(path)],text=True,capture_output=True,check=True,timeout=30)
            if r.stdout.strip()!=expected:raise RuntimeError(f'case {n}: {r.stdout!r} != {expected!r}')
    print('PASS: 6 authoritative catalog path / missing / corrupt / decoy cases; authored data only')
if __name__=='__main__':main()
