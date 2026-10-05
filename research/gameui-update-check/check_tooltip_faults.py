"""Wrong positioning models must differ from the original early-return path."""
import json,os,subprocess,sys
from pathlib import Path
root=Path('build-decomp/gameui-tooltip-faults').resolve();root.mkdir(parents=True,exist_ok=True)
source=Path('research/gameui-update-check/GameUITooltipProbe.cpp').read_text()
mutations=[
('width_without_rounding','float wide=width(window).asAbsolute(1)','CEGUI::UDim raw=width(window);float wide=raw.d_scale+raw.d_offset'),
('height_without_rounding','float high=height(window).asAbsolute(1)','CEGUI::UDim raw=height(window);float high=raw.d_scale+raw.d_offset'),
('wrong_margin','float boundary=high+26.0f','float boundary=high+25.0f'),
('clamp_x_zero','float boundary=high+26.0f','if(x<0)x=0;float boundary=high+26.0f'),
('subtract_y','if(y-boundary<0)y=boundary','if(y-boundary<0)y=boundary;else y-=boundary'),
('clamp_to_screen_height','if(y-boundary<0)y=boundary','if(y-boundary<0)y=boundary;if(y>999.0f-high-26.0f)y=999.0f-high-26.0f'),
('skip_height_query','screenHeight(w->ui);',''),
('reread_window','float available=screenWidth(w->ui)','window=at<void*>(w->holder,0x238);float available=screenWidth(w->ui)'),
('stale_cinema','cinematic(at<void*>(w->ui,0x540),0.125f)','cinematic(w->cinema[0],0.125f)')]
results=[]
for name,old,new in mutations:
    assert source.count(old)==1,(name,source.count(old))
    file=root/(name+'.cpp');file.write_text(source.replace(old,new))
    env=dict(os.environ,GAMEUI_ENTRY_SOURCE=str(file),GAMEUI_ENTRY_ROOT=str(root/'work'))
    proc=subprocess.run([sys.executable,'-u','research/gameui-update-check/check_entry.py'],env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
    (root/(name+'.log')).write_text(proc.stdout)
    killed=proc.returncode!=0 and 'gameui_tooltip_position_characterization' in proc.stdout and 'check failed:' in proc.stdout
    results.append({'name':name,'exit':proc.returncode,'killed':killed});print(name,proc.returncode,killed,flush=True)
    (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
    if not killed:raise SystemExit('Unexpected mutant outcome; inspect log')
