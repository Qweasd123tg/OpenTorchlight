"""Pet HUD/control/status faults checked against two original frames per case."""
import json,os,subprocess,sys
from pathlib import Path
root=Path('build-decomp/gameui-pet-faults').resolve();root.mkdir(parents=True,exist_ok=True)
source=Path('research/gameui-update-check/GameUIPetProbe.cpp').read_text()
mutations=[
('reread_pet_after_show','visible(reinterpret_cast<void*>(0x170),true);','visible(reinterpret_cast<void*>(0x170),true);pet=*at<void**>(actor(),0x648);'),
('stale_pet_before_cover','        begin=at<unsigned long>(actor(),0x648);end=at<unsigned long>(actor(),0x650);',''),
('skip_left_cover','!=0&&!covered(world->ui)','!=0'),
('eager_left_cover','void petHUD() {','void petHUD() {bool left=covered(world->ui);'),
('omit_mode_cache','            at<int>(world->ui,0x16c8)=mode;',''),
('cache_mode_after_callback','            at<int>(world->ui,0x16c8)=mode;',''),
('swap_mode_buttons','select(reinterpret_cast<void*>(0x1c8),true)','select(reinterpret_cast<void*>(0x1b8),true)'),
('unknown_mode_select','else if(mode==2)select(reinterpret_cast<void*>(0x1c0),true);','else if(mode==2)select(reinterpret_cast<void*>(0x1c0),true);else select(reinterpret_cast<void*>(0x1c8),true);'),
('upper_pet_clamp','if(ratio<0)ratio=0;','if(ratio<0)ratio=0;if(ratio>1)ratio=1;'),
('integer_pet_mana','ratio=mana(pet);','ratio=float(int(mana(pet)));'),
('fractional_pet_width','float(int(cached(0x175c).d_x.asAbsolute(1)*ratio))','cached(0x175c).d_x.asAbsolute(1)*ratio'),
('always_name_set','if(world->nameWindow->text!=name)','if(true)'),
('always_status_set','if(world->statusWindow->text!=value)','if(true)'),
('cached_pet_ai','std::string narrow=originalNarrow','int cachedAI=at<int>(pet,0x330);std::string narrow=originalNarrow'),
('timer_precedence','if(at<int>(pet,0x330)==0x2a)','if(at<int>(pet,0x330)==0x2a&&!nearDeath(pet))'),
('timer_strict_minute','while(remaining>=60.0f)','while(remaining>60.0f)'),
('no_hour_wrap','while(minutes>59)','while(minutes>60000)'),
('seconds_prefix_ten','(remaining<10.0f?"0":"")','(remaining<=10.0f?"0":"")'),
('missing_flee_suffix','std::string(fleeLabels[input->label])+"!"','std::string(fleeLabels[input->label])'),
('wrong_status_visibility','} else visible(world->statusWindow,false);','} else visible(world->statusWindow,true);'),
('wrong_pet_tooltip','tooltip(reinterpret_cast<void*>(0x178),converted)','tooltip(reinterpret_cast<void*>(0x180),converted)')]
results=[]
for name,old,new in mutations:
    expected=2 if name in ('upper_pet_clamp','always_status_set') else 1
    assert source.count(old)==expected,(name,source.count(old))
    text=source.replace(old,new)
    if name=='eager_left_cover':text=text.replace('!=0&&!covered(world->ui)','!=0&&!left')
    if name=='cache_mode_after_callback':text=text.replace('else if(mode==2)select(reinterpret_cast<void*>(0x1c0),true);','else if(mode==2)select(reinterpret_cast<void*>(0x1c0),true);at<int>(world->ui,0x16c8)=at<int>(pet,0x710);')
    if name=='cached_pet_ai':text=text.replace('if(at<int>(pet,0x330)==0x2a)','if(cachedAI==0x2a)')
    file=root/(name+'.cpp');file.write_text(text)
    env=dict(os.environ,GAMEUI_ENTRY_SOURCE=str(file),GAMEUI_ENTRY_ROOT=str(root/'work'))
    proc=subprocess.run([sys.executable,'-u','research/gameui-update-check/check_entry.py'],env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
    (root/(name+'.log')).write_text(proc.stdout)
    killed=proc.returncode!=0 and 'gameui_pet_prefix_characterization' in proc.stdout and 'check failed:' in proc.stdout
    results.append({'name':name,'exit':proc.returncode,'killed':killed});print(name,proc.returncode,killed,flush=True)
    (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
    if not killed:raise SystemExit('Unexpected mutant outcome; inspect log')
