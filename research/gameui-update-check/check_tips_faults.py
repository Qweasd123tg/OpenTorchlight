"""Queued-tip ordering, marking and queue-consumption wrong-model checks."""
import json,os,subprocess,sys
from pathlib import Path
root=Path('build-decomp/gameui-tips-faults').resolve();root.mkdir(parents=True,exist_ok=True)
source=Path('research/gameui-update-check/GameUIContextTipsProbe.cpp').read_text()
mutations=[
('ignore_modal','if(modal(world->ui)||!actor()','if((modal(world->ui)&&false)||!actor()'),
('key_after_global','int key=*at<int*>(world->ui,0x1960);void* globals=global();','void* globals=global();int key=*at<int*>(world->ui,0x1960);'),
('cached_key_seen','if(!value.empty()&&!at<unsigned char>(actor(),0xa17+*at<int*>(world->ui,0x1960)))','if(!value.empty()&&!at<unsigned char>(actor(),0xa17+key))'),
('cached_key_mark','    at<unsigned char>(actor(),0xa17+*at<int*>(world->ui,0x1960))=1;','    at<unsigned char>(actor(),0xa17+key)=1;'),
('ignore_seen','if(!value.empty()&&!at<unsigned char>(actor(),0xa17+*at<int*>(world->ui,0x1960)))','if(!value.empty())'),
('show_empty','if(!value.empty()&&!at<unsigned char>(actor(),0xa17+*at<int*>(world->ui,0x1960)))','if(!at<unsigned char>(actor(),0xa17+*at<int*>(world->ui,0x1960)))'),
('keep_empty','    if(!value.empty()&&!at<unsigned char>','    if(value.empty())return;\n    if(!value.empty()&&!at<unsigned char>'),
('keep_seen','    if(!value.empty()&&!at<unsigned char>','    if(at<unsigned char>(actor(),0xa17+*at<int*>(world->ui,0x1960)))return;\n    if(!value.empty()&&!at<unsigned char>'),
('omit_mark','    at<unsigned char>(actor(),0xa17+*at<int*>(world->ui,0x1960))=1;',''),
('omit_dequeue','    --at<int*>(world->ui,0x1968);',''),
('omit_shift','for(unsigned i=0;i+1<count;++i)','for(unsigned i=0;false;++i)'),
('skip_one_extra','    --at<int*>(world->ui,0x1968);','    if(count>1)--at<int*>(world->ui,0x1968);\n    --at<int*>(world->ui,0x1968);'),
('cached_menu','contents(at<void*>(world->ui,0x550),value);tipVisible(at<void*>(world->ui,0x550),true);','void* menu=at<void*>(world->ui,0x550);contents(menu,value);tipVisible(menu,true);'),
('cached_actor','int key=*at<int*>(world->ui,0x1960);','void* savedActor=actor();int key=*at<int*>(world->ui,0x1960);'),
('cached_queue','    unsigned count=at<int*>(world->ui,0x1968)-at<int*>(world->ui,0x1960);',''),
('reverse_show_order','contents(at<void*>(world->ui,0x550),value);tipVisible(at<void*>(world->ui,0x550),true);','tipVisible(at<void*>(world->ui,0x550),true);contents(at<void*>(world->ui,0x550),value);')]
results=[]
for name,old,new in mutations:
    assert source.count(old)==1,(name,source.count(old))
    text=source.replace(old,new)
    if name=='cached_actor':
        start=text.index('void queuedTips()');end=text.index('void activeCameraAndTail()',start)
        text=text[:start]+text[start:end].replace('at<unsigned char>(actor(),','at<unsigned char>(savedActor,')+text[end:]
    if name=='cached_queue':text=text.replace('    int key=*at<int*>(world->ui,0x1960);','    unsigned count=at<int*>(world->ui,0x1968)-at<int*>(world->ui,0x1960);\n    int key=*at<int*>(world->ui,0x1960);')
    file=root/(name+'.cpp');file.write_text(text)
    env=dict(os.environ,GAMEUI_ENTRY_SOURCE=str(file),GAMEUI_ENTRY_ROOT=str(root/'work'),OTL_SELFTEST_TIMEOUT='300')
    proc=subprocess.run([sys.executable,'-u','research/gameui-update-check/check_entry.py'],env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
    (root/(name+'.log')).write_text(proc.stdout)
    killed=proc.returncode!=0 and 'gameui_context_tips_characterization' in proc.stdout and 'check failed:' in proc.stdout
    results.append({'name':name,'exit':proc.returncode,'killed':killed});print(name,proc.returncode,killed,flush=True)
    (root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
    if not killed:raise SystemExit('Unexpected mutant outcome; inspect log')
