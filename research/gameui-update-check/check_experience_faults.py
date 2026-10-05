"""Specific wrong XP formulas/read ordering must fail original-prefix comparisons."""
import json,os,subprocess,sys
from pathlib import Path
root=Path('build-decomp/gameui-experience-faults').resolve();root.mkdir(parents=True,exist_ok=True)
source=Path('research/gameui-update-check/GameUIExperienceProbe.cpp').read_text()
mutations=[
('omit_upper_clamp','if(ratio<0.0f)ratio=0.0f;else if(ratio>1.0f)ratio=1.0f;','if(ratio<0.0f)ratio=0.0f;'),
('omit_lower_clamp','if(ratio<0.0f)ratio=0.0f;else if(ratio>1.0f)ratio=1.0f;','if(ratio>1.0f)ratio=1.0f;'),
('decompiler_nan_one','if(ratio<0.0f)ratio=0.0f;else if(ratio>1.0f)ratio=1.0f;','if(ratio!=ratio)ratio=1.0f;else if(ratio<0.0f)ratio=0.0f;else if(ratio>1.0f)ratio=1.0f;'),
('integer_numerator','float experience=float(at<int>(actor(),0x448));','int experience=at<int>(actor(),0x448);'),
('cached_xp_tooltip','originalNumber(at<int>(actor(),0x448))','originalNumber(int(experience))'),
('reuse_previous_gate','float(currentGate-previousAgain)','float(currentGate-previous)'),
('reuse_tooltip_gate','std::string top=originalNumber(gate(resource,level));','gate(resource,level);std::string top=originalNumber(currentGate);'),
('level_after_singleton','void* resource=manager();int previous=gate(resource,level-1);','void* resource=manager();level=at<int>(actor(),0x100);int previous=gate(resource,level-1);'),
('xp_after_singleton','void* resource=manager();int previous=gate(resource,level-1);','void* resource=manager();experience=float(at<int>(actor(),0x448));int previous=gate(resource,level-1);'),
('fractional_width','float(int(cached(0x173c).d_x.asAbsolute(1)*ratio))','cached(0x173c).d_x.asAbsolute(1)*ratio'),
('round_width','float(int(cached(0x173c).d_x.asAbsolute(1)*ratio))','float(int(cached(0x173c).d_x.asAbsolute(1)*ratio+0.5f))'),
('wrong_height','CEGUI::UDim(0,cached(0x173c).d_y.asAbsolute(1))','CEGUI::UDim(0,cached(0x173c).d_x.asAbsolute(1))'),
('rebased_tooltip','originalNumber(at<int>(actor(),0x448))','originalNumber(at<int>(actor(),0x448)-previous)'),
('wrong_current_level','int currentGate=gate(resource,level);','int currentGate=gate(resource,level-1);')]
results=[]
for name,old,new in mutations:
    assert source.count(old)==1,(name,source.count(old))
    text=source.replace(old,new)
    if name=='integer_numerator':text=text.replace('(experience-float(previous))','float(experience-previous)')
    file=root/(name+'.cpp');file.write_text(text)
    env=dict(os.environ,GAMEUI_ENTRY_SOURCE=str(file),GAMEUI_ENTRY_ROOT=str(root/'work'))
    proc=subprocess.run([sys.executable,'-u','research/gameui-update-check/check_entry.py'],env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
    (root/(name+'.log')).write_text(proc.stdout)
    killed=proc.returncode!=0 and 'gameui_experience_prefix_characterization' in proc.stdout and 'check failed:' in proc.stdout
    results.append({'name':name,'exit':proc.returncode,'killed':killed});print(name,proc.returncode,killed,flush=True)
    (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
    if not killed:raise SystemExit('Unexpected mutant outcome; inspect log')
