"""Controlled active-frame camera/list/tail mutation checks; no production hooks."""
import json,os,subprocess,sys
from pathlib import Path
root=Path('build-decomp/gameui-active-faults').resolve();root.mkdir(parents=True,exist_ok=True)
source=Path('research/gameui-update-check/GameUIActiveFrameProbe.cpp').read_text()
mutations=[
('reverse_span','(right-left)/at<float>(world->ui,0x1684)','(left-right)/at<float>(world->ui,0x1684)'),
('cached_width','(right-left)/at<float>(world->ui,0x1684)','(right-left)/input->screenWidth'),
('skip_setting','    settingFloat(at<void*>(world->ui,0x78),*reinterpret_cast<unsigned*>(0x150b470));',''),
('skip_inverse','view=view.inverse();',''),
('reverse_matrix','cameraProjection(camera())*view','view*cameraProjection(camera())'),
('wrong_up','cameraOrientation(camera()).yAxis()','cameraOrientation(camera()).xAxis()'),
('inactive_events','events(world->ui,input->elapsed,up,matrix,true);','events(world->ui,input->elapsed,up,matrix,false);'),
('old_level','    level=at<void*>(world->client,0x70);Node* character','    Node* character'),
('skip_items','while(item){','while(false&&item){'),
('skip_actors','while(character){','while(false&&character){'),
('cached_item_next','while(item){modal(world->ui);itemHidden(item->value);item=item->next;}','while(item){Node* next=item->next;modal(world->ui);itemHidden(item->value);item=next;}'),
('cached_actor_next','while(character){modal(world->ui);characterHidden(character->value);character=character->next;}','while(character){Node* next=character->next;modal(world->ui);characterHidden(character->value);character=next;}'),
('skip_item_modal','while(item){modal(world->ui);','while(item){'),
('skip_actor_modal','while(character){modal(world->ui);','while(character){'),
('cached_console','consoleTick(at<void*>(world->ui,0x1690),input->elapsed)','consoleTick(console,input->elapsed)'),
('wrong_final_time','finalTick(at<void*>(world->ui,0x588),input->elapsed,world->client,&world->renderWindow);','finalTick(at<void*>(world->ui,0x588),0.0f,world->client,&world->renderWindow);'),
('cached_camera','void activeCameraAndTail(){','void activeCameraAndTail(){void* savedCamera=camera();'),
('cached_manager','void activeCameraAndTail(){','void activeCameraAndTail(){void* savedManager=at<void*>(world->ui,0x588);')]
results=[]
for name,old,new in mutations:
    assert source.count(old)==1,(name,source.count(old))
    text=source.replace(old,new)
    if name=='cached_camera':
        start=text.index('    Ogre::Matrix3 rotation;',text.index('void activeCameraAndTail'))
        end=text.index('    events(',start)
        text=text[:start]+text[start:end].replace('camera()','savedCamera')+text[end:]
    if name=='cached_manager':text=text.replace('finalTick(at<void*>(world->ui,0x588),','finalTick(savedManager,')
    file=root/(name+'.cpp');file.write_text(text)
    env=dict(os.environ,GAMEUI_ENTRY_SOURCE=str(file),GAMEUI_ENTRY_ROOT=str(root/'work'),OTL_SELFTEST_TIMEOUT='300')
    proc=subprocess.run([sys.executable,'-u','research/gameui-update-check/check_entry.py'],env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
    (root/(name+'.log')).write_text(proc.stdout)
    killed=proc.returncode!=0 and 'gameui_active_frame_characterization' in proc.stdout and 'check failed:' in proc.stdout
    results.append({'name':name,'exit':proc.returncode,'killed':killed});print(name,proc.returncode,killed,flush=True)
    (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
    if not killed:raise SystemExit('Unexpected mutant outcome; inspect log')
