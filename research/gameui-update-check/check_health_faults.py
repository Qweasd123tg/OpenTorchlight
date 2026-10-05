"""Intentional mistakes in the HP prefix model; original ELF stays unchanged."""
import json,os,subprocess,sys
from pathlib import Path
root=Path('build-decomp/gameui-health-faults').resolve();root.mkdir(parents=True,exist_ok=True)
source=Path('research/gameui-update-check/GameUIHealthProbe.cpp').read_text()
mutations=[
('upper_clamp', 'if(ratio<0.0f)ratio=0.0f;', 'if(ratio<0.0f)ratio=0.0f;if(ratio>1.0f)ratio=1.0f;'),
('remove_lower_clamp', 'if(ratio<0.0f)ratio=0.0f;', ''),
('nan_to_zero', 'if(ratio<0.0f)ratio=0.0f;', 'if(!(ratio>=0.0f))ratio=0.0f;'),
('integer_division', 'float(hp(w->character))/float(maxhp(w->character))', 'float(hp(w->character)/maxhp(w->character))'),
('cached_height', 'void model(){float ratio=', 'void model(){const float cachedHeight=dims().d_y.asAbsolute(1);float ratio='),
('wrong_anchor', '(pos().d_y.asAbsolute(1)+dims().d_y.asAbsolute(1))-dims().d_y.asAbsolute(1)*ratio', 'pos().d_y.asAbsolute(1)'),
('mask_sign', '-(dims().d_y.asAbsolute(1)-dims().d_y.asAbsolute(1)*ratio)', '(dims().d_y.asAbsolute(1)-dims().d_y.asAbsolute(1)*ratio)'),
('mask_unscaled', '-(dims().d_y.asAbsolute(1)-dims().d_y.asAbsolute(1)*ratio)', '-dims().d_y.asAbsolute(1)'),
('size_no_pixel_rounding','CEGUI::UDim(0,dims().d_y.asAbsolute(1)*ratio)', 'CEGUI::UDim(0,(dims().d_y.d_scale+dims().d_y.d_offset)*ratio)')]
results=[]
for name,old,new in mutations:
    assert source.count(old)==1,(name,source.count(old))
    text=source.replace(old,new)
    if name=='cached_height':text=text.replace('CEGUI::UDim(0,dims().d_y.asAbsolute(1)*ratio)','CEGUI::UDim(0,cachedHeight*ratio)')
    file=root/(name+'.cpp');file.write_text(text)
    env=dict(os.environ,GAMEUI_ENTRY_SOURCE=str(file),GAMEUI_ENTRY_ROOT=str(root/'work'))
    proc=subprocess.run([sys.executable,'-u','research/gameui-update-check/check_entry.py'],env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
    (root/(name+'.log')).write_text(proc.stdout)
    killed=proc.returncode!=0 and 'gameui_health_prefix_characterization' in proc.stdout and 'check failed:' in proc.stdout
    results.append({'name':name,'exit':proc.returncode,'killed':killed});print(name,proc.returncode,killed,flush=True)
    (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
    if not killed:raise SystemExit('Unexpected mutant outcome; inspect log')
