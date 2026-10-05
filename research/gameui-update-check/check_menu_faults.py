"""Intentional transition mistakes, tested against original frame prefix."""
import json,os,subprocess,sys
from pathlib import Path
root=Path('build-decomp/gameui-menu-faults').resolve();root.mkdir(parents=True,exist_ok=True)
source=Path('research/gameui-update-check/GameUIMenuProbe.cpp').read_text()
mutations=[
('skip_close','all(w->ui);',''),
('skip_inventory','open(w->menus[0],true);',''),
('swap_owner_player','  player(w->menus[index],actor());','  player(w->menus[index],w->actors[0]);'),
('stale_target','else owner(w->menus[index],target(targetOffset));','else owner(w->menus[index],at<void*>(w->actors[0],targetOffset));'),
('wrong_item_owner','if(s==0x16)itemOwner(w->menus[index],target(targetOffset));','if(s==0x16)owner(w->menus[index],target(targetOffset));'),
('wrong_enchant_state','enchanting(w->menus[index],true,s);','enchanting(w->menus[index],true,0x15);'),
('wrong_final_state','s==0x24?0x26:0x1c','s==0x24?0x26:2'),
('stale_state_actor','state(actor(),s==0x13','state(w->actors[0],s==0x13'),
('wrong_sound','sound(bank,0x26,0.0f,0.1f)','sound(bank,0x27,0.0f,0.1f)'),
('show_fishing','\n defaultMenu(w->menus[5],false)','\n defaultMenu(w->menus[5],true)'),
('negative_limit_blocked','limit>=0&&unsigned(limit)>at<unsigned>(actor(),0x100)','unsigned(limit)>at<unsigned>(actor(),0x100)'),
('signed_level','unsigned(limit)>at<unsigned>(actor(),0x100)','limit>int(at<unsigned>(actor(),0x100))'),
('reject_equal_level','unsigned(limit)>at<unsigned>(actor(),0x100)','unsigned(limit)>=at<unsigned>(actor(),0x100)'),
('cached_level_actor','unsigned(limit)>at<unsigned>(actor(),0x100)','unsigned(limit)>at<unsigned>(w->actors[0],0x100)'),
('wrong_modal_choice','std::wstring(L"Cannot retire")+format(limit),false','std::wstring(L"Cannot retire")+format(limit),true'),
('denial_state','state(actor(),2);','state(actor(),0x1c);'),
('retirement_mode','enchanting(w->menus[index],true,s);','enchanting(w->menus[index],true,s==0x1b?0x15:s);')]
results=[]
for name,old,new in mutations:
    assert source.count(old)==1,(name,source.count(old))
    file=root/(name+'.cpp');file.write_text(source.replace(old,new))
    env=dict(os.environ,GAMEUI_ENTRY_SOURCE=str(file),GAMEUI_ENTRY_ROOT=str(root/'work'))
    proc=subprocess.run([sys.executable,'-u','research/gameui-update-check/check_entry.py'],env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
    (root/(name+'.log')).write_text(proc.stdout)
    killed=proc.returncode!=0 and 'gameui_menu_prefix_characterization' in proc.stdout and 'check failed:' in proc.stdout
    results.append({'name':name,'exit':proc.returncode,'killed':killed});print(name,proc.returncode,killed,flush=True)
    (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
    if not killed:raise SystemExit('Unexpected mutant outcome; inspect log')
