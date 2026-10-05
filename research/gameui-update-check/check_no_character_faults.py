"""Mutation checks for the complete no-character original frame path."""
import json,os,subprocess,sys
from pathlib import Path
root=Path('build-decomp/gameui-no-character-faults').resolve();root.mkdir(parents=True,exist_ok=True)
source=Path('research/gameui-update-check/GameUINoCharacterProbe.cpp').read_text()
mutations=[
('reverse_matrix_order','projection(camera())*view','view*projection(camera())'),
('omit_inverse','view=view.inverse();',''),
('omit_translation','view.setTrans(position(camera()));','position(camera());'),
('wrong_up_axis','orientation(camera()).yAxis()','orientation(camera()).xAxis()'),
('cache_camera','void model(){','void model(){void*cached=camera();'),
('cache_console','console(at<void*>(w->ui,0x1690),input->elapsed)','console(p,input->elapsed)'),
('cache_menu_manager','menus(at<void*>(w->ui,0x588),input->elapsed','menus(&w->menus[0],input->elapsed'),
('wrong_events_flag','events(w->ui,input->elapsed,up,matrix,false)','events(w->ui,input->elapsed,up,matrix,true)'),
('wrong_elapsed','events(w->ui,input->elapsed,up,matrix,false)','events(w->ui,0.0f,up,matrix,false)'),
('window_guard_or','at<void*>(w->ui,0x138)&&at<void*>(w->ui,0x120)','at<void*>(w->ui,0x138)||at<void*>(w->ui,0x120)'),
('skip_modal_query','modal(w->ui);',''),
('swap_client_window','&w->client,&w->renderWindow);}', '&w->renderWindow,&w->client);}')]
results=[]
for name,old,new in mutations:
    assert source.count(old)==1,(name,source.count(old))
    text=source.replace(old,new)
    if name=='cache_camera':
        start=text.index('void model(){');end=text.index('\nvoid side(',start)
        text=text[:start]+text[start:end].replace('orientation(camera())','orientation(cached)').replace('position(camera())','position(cached)').replace('projection(camera())','projection(cached)')+text[end:]
    file=root/(name+'.cpp');file.write_text(text)
    env=dict(os.environ,GAMEUI_ENTRY_SOURCE=str(file),GAMEUI_ENTRY_ROOT=str(root/'work'))
    proc=subprocess.run([sys.executable,'-u','research/gameui-update-check/check_entry.py'],env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
    (root/(name+'.log')).write_text(proc.stdout)
    killed=proc.returncode!=0 and 'gameui_no_character_frame_characterization' in proc.stdout and 'check failed:' in proc.stdout
    results.append({'name':name,'exit':proc.returncode,'killed':killed});print(name,proc.returncode,killed,flush=True)
    (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
    if not killed:raise SystemExit('Unexpected mutant outcome; inspect log')
