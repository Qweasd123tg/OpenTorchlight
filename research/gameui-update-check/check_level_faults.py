"""Clock/widget and dynamic menu-loop errors checked against original frame prefixes."""
import json,os,subprocess,sys
from pathlib import Path
root=Path('build-decomp/gameui-level-faults').resolve();root.mkdir(parents=True,exist_ok=True)
source=Path('research/gameui-update-check/GameUILevelProbe.cpp').read_text()
mutations=[
('immediate_hide','messages','visible(at<void*>(world->ui,pointer),true);','visible(at<void*>(world->ui,pointer),alpha>0);'),
('overshoot_only','messages','oldAlpha+input->elapsed*(-2.0f)','oldAlpha+(-duration)*(-2.0f)'),
('wrong_fade_rate','messages','oldAlpha+input->elapsed*(-2.0f)','oldAlpha+input->elapsed*(-1.0f)'),
('negative_duration','messages','at<float>(world->ui,durationOffset)=0;',''),
('clamp_stored_alpha','messages','at<float>(world->ui,alphaOffset)=oldAlpha+input->elapsed*(-2.0f);','at<float>(world->ui,alphaOffset)=oldAlpha+input->elapsed*(-2.0f);if(at<float>(world->ui,alphaOffset)<0)at<float>(world->ui,alphaOffset)=0;'),
('ignore_nan_change','messages','if(alpha!=oldAlpha)','if(alpha!=oldAlpha&&alpha==alpha)'),
('cached_property_window','messages','property(at<void*>(world->ui,pointer),','property(current,'),
('alpha_before_text','messages','        float oldAlpha=at<float>(world->ui,alphaOffset);',''),
('duration_before_text','messages','        float duration=at<float>(world->ui,durationOffset)-input->elapsed;',''),
('fade_under_modal','messages','if(modal(world->ui)){visible','if(modal(world->ui)&&false){visible'),
('skip_modal_query','messages','if(modal(world->ui)){visible','if(false){visible'),
('always_text','messages','if(current->text!=value)','if(true)'),
('white_shadow','messages','CEGUI::colour(0,0,0,rendered)','CEGUI::colour(1,1,1,rendered)'),
('strict_expiry','messages','if(duration<=0)','if(duration<0)'),
('zero_alpha_active','messages','if(at<float>(world->ui,alphaOffset)>0)','if(at<float>(world->ui,alphaOffset)>=0)'),
('drop_shadow','messages','            property(at<void*>(world->ui,pointer),CEGUI::String("DropTextColour"),CEGUI::PropertyHelper::colourToString(CEGUI::colour(0,0,0,rendered)));',''),
('cached_vector_end','menu_updates','for(unsigned i=0;i<unsigned(at<void**>(world->ui,base+8)-at<void**>(world->ui,base));++i)','unsigned count=at<void**>(world->ui,base+8)-at<void**>(world->ui,base);for(unsigned i=0;i<count;++i)'),
('cached_vector_base','menu_updates','void tickMenus(){','void tickMenus(){void** saved[2]={at<void**>(world->ui,0x1930),at<void**>(world->ui,0x1948)};'),
('skip_dropdowns','menu_updates','void tickMenus(){\n    for(unsigned family=0;family<2;++family)','void tickMenus(){\n    for(unsigned family=0;family<1;++family)'),
('reverse_families','menu_updates','void tickMenus(){\n    for(unsigned family=0;family<2;++family)','void tickMenus(){\n    for(int family=1;family>=0;--family)'),
('interactive_before_fishing','menu_updates','void tickMenus(){','void tickMenus(){void* early=at<void*>(world->ui,0x570);'),
('interactive_before_own_update','menu_updates','tick(at<void*>(world->ui,0x570),input->elapsed);','void* called=at<void*>(world->ui,0x570);tick(called,input->elapsed);'),
('wrong_tick_time','menu_updates','void tickMenus(){','void tickMenus(){'),
('omit_pet_override','menu_updates','    if(interactive)visible(reinterpret_cast<void*>(0x170),false);','')]
results=[]
for name,test,old,new in mutations:
    expected=2 if name in ('cached_property_window','always_text') else 1
    assert source.count(old)==expected,(name,source.count(old))
    text=source.replace(old,new)
    if name=='alpha_before_text':text=text.replace('        std::string value=originalUTF8(at<std::wstring>(world->ui,stringOffset));','        float oldAlpha=at<float>(world->ui,alphaOffset);\n        std::string value=originalUTF8(at<std::wstring>(world->ui,stringOffset));')
    if name=='duration_before_text':text=text.replace('        std::string value=originalUTF8(at<std::wstring>(world->ui,stringOffset));','        float duration=at<float>(world->ui,durationOffset)-input->elapsed;\n        std::string value=originalUTF8(at<std::wstring>(world->ui,stringOffset));')
    if name=='cached_vector_base':text=text.replace('tick(at<void**>(world->ui,base)[i],input->elapsed)','tick(saved[family][i],input->elapsed)')
    if name=='interactive_before_fishing':text=text.replace('tick(at<void*>(world->ui,0x570),input->elapsed);','tick(early,input->elapsed);')
    if name=='interactive_before_own_update':text=text.replace('bool interactive=at<unsigned char>(at<void*>(world->ui,0x570),0x38)!=0;','bool interactive=at<unsigned char>(called,0x38)!=0;')
    if name=='wrong_tick_time':
        start=text.index('void tickMenus(){');end=text.index('void model()',start)
        text=text[:start]+text[start:end].replace('input->elapsed','0.0f')+text[end:]
    file=root/(name+'.cpp');file.write_text(text)
    testname='gameui_messages_prefix_characterization' if test=='messages' else 'gameui_menu_updates_characterization'
    env=dict(os.environ,GAMEUI_ENTRY_SOURCE=str(file),GAMEUI_ENTRY_ROOT=str(root/'work'),GAMEUI_TEST_ONLY=testname,OTL_SELFTEST_TIMEOUT='300')
    proc=subprocess.run([sys.executable,'-u','research/gameui-update-check/check_entry.py'],env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
    (root/(name+'.log')).write_text(proc.stdout)
    killed=proc.returncode!=0 and testname in proc.stdout and 'check failed:' in proc.stdout
    results.append({'name':name,'test':testname,'exit':proc.returncode,'killed':killed});print(name,proc.returncode,killed,flush=True)
    (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
    if not killed:raise SystemExit('Unexpected mutant outcome; inspect log')
