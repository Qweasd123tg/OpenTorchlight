"""Check the characterization oracle catches specific wrong reconstructions."""
import json,os,subprocess,sys
from pathlib import Path
root=Path('build-decomp/gameui-entry-faults').resolve();root.mkdir(parents=True,exist_ok=True)
source=Path('research/gameui-update-check/GameUIEntryProbe.cpp').read_text()
mutations=[
('cache_radio', 'selected(at<void*>(w->ui,0x200),next)', 'selected(w->radio[0],next)'),
('first_nonzero', 'unsigned(setting(&w->settings,*reinterpret_cast<unsigned*>(0x150b570))==1)', 'unsigned(setting(&w->settings,*reinterpret_cast<unsigned*>(0x150b570))!=0)'),
('second_nonzero', 'bool next=setting(&w->settings,*reinterpret_cast<unsigned*>(0x150b570))==1', 'bool next=setting(&w->settings,*reinterpret_cast<unsigned*>(0x150b570))!=0'),
('drop_second_read', 'bool next=setting(&w->settings,*reinterpret_cast<unsigned*>(0x150b570))==1', 'bool next=input->first==1'),
('eager_mouse', 'pressed(m,1)||pressed(m,0)||held(m,1)||held(m,0)', 'pressed(m,1)|pressed(m,0)|held(m,1)|held(m,0)'),
('swapped_mouse', 'pressed(m,1)||pressed(m,0)', 'pressed(m,0)||pressed(m,1)'),
('cache_cinema','void*c=at<void*>(w->ui,0x540)','void*c=w->cinema[0]'),
('wrong_cinematic_gate','if(at<unsigned char>(c,0x30)||!at<unsigned char>(c,0x31))','if(at<unsigned char>(c,0x30)&&!at<unsigned char>(c,0x31))'),
('wrong_elapsed','update(c,0.125f)','update(c,0.25f)')]
results=[]
for name,old,new in mutations:
    assert source.count(old)==1,(name,source.count(old))
    file=root/(name+'.cpp');file.write_text(source.replace(old,new))
    env=dict(os.environ,GAMEUI_ENTRY_SOURCE=str(file),GAMEUI_ENTRY_ROOT=str(root/'work'))
    proc=subprocess.run([sys.executable,'-u','research/gameui-update-check/check_entry.py'],env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
    (root/(name+'.log')).write_text(proc.stdout)
    killed=proc.returncode!=0 and 'gameui_cinematic_entry_characterization' in proc.stdout and 'check failed:' in proc.stdout
    results.append({'name':name,'exit':proc.returncode,'killed':killed});print(name,proc.returncode,killed,flush=True)
    (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
    if not killed:raise SystemExit('Unexpected mutant outcome; inspect log')
