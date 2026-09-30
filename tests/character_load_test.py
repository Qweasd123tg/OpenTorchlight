#!/usr/bin/env python3
"""Native load controls -> common application -> real isolated OTC store; no SVB/OS parity."""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import tempfile
ROOT = Path(__file__).resolve().parents[1]
EXIT_GAME = 'key ESC\nmenu pause\ndt 0.1\nframes 5\nbutton exit-game\nmenu main\n'

def main() -> int:
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--probe',type=Path,required=True)
    p.add_argument('--game-dir',type=Path,required=True)
    p.add_argument('--output-dir',type=Path,required=True)
    a=p.parse_args(); a.output_dir.mkdir(parents=True,exist_ok=True)
    work=Path(tempfile.mkdtemp(prefix='native-load-',dir=a.output_dir)); saves=work/'saves'
    checks=0
    def require(value,message):
        nonlocal checks
        checks+=1
        if not value: raise AssertionError(message)
    def run(name,script):
        source=work/(name+'.scenario');source.write_text(script,encoding='utf-8')
        output=work/name
        with (work/(name+'.log')).open('w') as log:
            result=subprocess.run([sys.executable,str(ROOT/'tools/run_scenario.py'),
                '--library',str(a.probe),'--game-dir',str(a.game_dir),'--save-dir',str(saves),
                '--script',str(source),'--output',str(output)],stdout=log,stderr=subprocess.STDOUT,timeout=240)
        if result.returncode==77: raise RuntimeError('NOT RUN: EGL unavailable')
        if result.returncode: raise RuntimeError((work/(name+'.log')).read_text()[-6000:])
        return output
    def state(output,name): return json.loads((output/(name+'.state.json')).read_text())
    def files(): return {p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in saves.glob('*.otc')}
    report={'evidence':'real-resource port Application/GL/OTC integration; no original process or Wayland input','output':str(work)}
    try:
        first=run('first','menu main\nbutton new\nmenu create\nbutton class-0\nname Éclair\nbutton create\nlevel Town 0\nframes 2\ncapture first\n'+EXIT_GAME+'button exit\n')
        original=state(first,'first'); original_files=files()
        require(len(original_files)==1,'first campaign did not write one isolated OTC')
        second=run('second','menu main\nbutton new\nmenu create\nbutton class-1\nname Séraphine\nbutton create\nlevel Town 0\nframes 2\ncapture second\n'+EXIT_GAME+
            'button loads\nmenu load\nbutton slot-1\nmenu-capture selected_load\nbutton load\nlevel Town 0\nframes 2\ncapture restored\n'+EXIT_GAME+'button exit\n')
        other=state(second,'second'); restored=state(second,'restored')
        require(other['name']=='Séraphine' and other['class_guid']!=original['class_guid'],'second real save did not use distinct input/class')
        require(restored['name']=='Éclair','native row selected the wrong save')
        for field in ('class_guid','seed','position','hp','max_hp','mana','max_mana','gold','progression','inventory','slots','damage','armor'):
            require(restored[field]==original[field],'selected OTC restore changed '+field)
        require(restored['revision']==1,'native Play bypassed saved campaign revision')
        before=files(); require(len(before)==2,'two campaigns not retained')
        canceled=run('cancel','menu main\nbutton loads\nmenu load\nbutton slot-1\nbutton delete\nbutton decline\nmenu-capture cancelled_load\nbutton back\nmenu main\nbutton exit\n')
        require(files()==before,'Decline changed or removed a real save')
        deleted=run('delete','menu main\nbutton loads\nmenu load\nbutton slot-1\nbutton delete\nbutton accept\nmenu-capture after_delete\nbutton load\nlevel Town 0\nframes 2\ncapture remaining\nquit\n')
        remaining=state(deleted,'remaining')
        require(set(files())==set(original_files),'Accept removed a different campaign or left deleted OTC')
        require(remaining['name']=='Éclair' and remaining['class_guid']==original['class_guid'],'remaining native selection has no real load consumer')
        require(remaining['revision']==2,'remaining campaign identity/revision lost after delete reload')
        for output,label in ((second,'selected_load'),(canceled,'cancelled_load'),(deleted,'after_delete')):
            require((output/(label+'.rgba')).stat().st_size>0,'native Load page was not drawn: '+label)
        report.update(status='PASSED',assertions=checks,processes=4)
        print(f'PASS: native selection/load, cancel leaves both OTC files byte-identical, Accept deletes only selected save; 4 processes, {checks} checks; {work}')
        return 0
    except Exception as exc:
        report.update(status='FAILED',error=str(exc),assertions=checks)
        print('FAIL:',exc,'evidence:',work,file=sys.stderr)
        return 77 if str(exc).startswith('NOT RUN:') else 1
    finally:
        (work/'test-result.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n')

if __name__=='__main__': raise SystemExit(main())
