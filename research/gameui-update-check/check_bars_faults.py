"""Fault sensitivity for active HP/mana geometry and tooltip reconstruction."""
import json,os,subprocess,sys
from pathlib import Path
root=Path('build-decomp/gameui-bars-faults').resolve();root.mkdir(parents=True,exist_ok=True)
source=Path('research/gameui-update-check/GameUIBarsProbe.cpp').read_text()
mutations=[
('integer_mana_gauge','current=mana(actor());maximum=maxmana(actor());','current=float(int(mana(actor())));maximum=maxmana(actor());'),
('round_mana_label','originalNumber(int(mana(actor())))','originalNumber(int(mana(actor())+0.5f))'),
('ansi_instead_of_utf8','reinterpret_cast<const CEGUI::utf8*>(text.c_str())','text.c_str()'),
('extra_label_space','+":"+now','+": "+now'),
('stale_tooltip_actor','originalNumber(maxhp(actor()))','originalNumber(maxhp(world->actors[0]))'),
('swap_hp_query_order','std::string top=originalNumber(maxhp(actor()));\n        std::string now=originalNumber(hp(actor()));','std::string now=originalNumber(hp(actor()));\n        std::string top=originalNumber(maxhp(actor()));'),
('wrong_hp_tooltip_window','tooltip(reinterpret_cast<void*>(0x148),converted)','tooltip(reinterpret_cast<void*>(0x140),converted)'),
('wrong_mana_label','std::string(manaLabels[input->label])','std::string(hpLabels[input->label])'),
('upper_clamp','if(ratio<0.0f) ratio=0.0f;','if(ratio<0.0f) ratio=0.0f;if(ratio>1.0f)ratio=1.0f;'),
('nan_to_zero','if(ratio<0.0f) ratio=0.0f;','if(!(ratio>=0.0f)) ratio=0.0f;'),
('wrong_mana_geometry','bar(0x16dc,0x172c,0x158,0x168','bar(0x16cc,0x171c,0x158,0x168'),
('reverse_current_max_label','+":"+now+"/"+top','+":"+top+"/"+now')]
results=[]
for name,old,new in mutations:
    expected=2 if name in ('ansi_instead_of_utf8','extra_label_space','reverse_current_max_label') else 1
    assert source.count(old)==expected,(name,source.count(old))
    file=root/(name+'.cpp');file.write_text(source.replace(old,new))
    env=dict(os.environ,GAMEUI_ENTRY_SOURCE=str(file),GAMEUI_ENTRY_ROOT=str(root/'work'))
    proc=subprocess.run([sys.executable,'-u','research/gameui-update-check/check_entry.py'],env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
    (root/(name+'.log')).write_text(proc.stdout)
    killed=proc.returncode!=0 and 'gameui_bars_prefix_characterization' in proc.stdout and 'check failed:' in proc.stdout
    results.append({'name':name,'exit':proc.returncode,'killed':killed});print(name,proc.returncode,killed,flush=True)
    (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
    if not killed:raise SystemExit('Unexpected mutant outcome; inspect log')
