#include "ParentPairs.h"
#include "Detour.h"
#include "Timeline.h"
#include "TimelineProperty.h"
TL_ORIGINAL(float,oldUpdate,(CTimeline*,float),"_ZN9CTimeline14UpdateTimelineEf")
extern "C" float newUpdate(CTimeline*,float) __asm__("_ZN9CTimeline14UpdateTimelineEf");
TL_FUNCTION(editorRunning,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(propertyUpdate,"_ZN17CTimelineProperty6UpdateEfb")
namespace {
autotest::Capture* cap;unsigned seed,calls;CTimeline* active;CTimelineProperty* props[3];
bool editor(CResourceManager*){++calls;bool result=seed%5==1 || (seed%5==2 && calls%2);parentpairs::scalar(*cap,result);return result;}
void property(CTimelineProperty*p,float value,bool backward){unsigned index=0;while(index<3&&props[index]!=p)++index;parentpairs::scalar(*cap,index);parentpairs::scalar(*cap,value);parentpairs::scalar(*cap,backward);if(seed%11==1)active->m_bEnabled=false;}
struct Timeline:CTimeline{virtual void BroadcastEvent(unsigned int event){parentpairs::scalar(*cap,event);parentpairs::scalar(*cap,m_fTimelinePosition);parentpairs::scalar(*cap,m_bEnabled);if(seed%11==2)m_bEnabled=false;if(seed%11==3)m_fSetTimelineDuration+=0.25f;}};
void side(void*raw,autotest::Capture&out,bool ours){seed=static_cast<parentpairs::Case*>(raw)->seed;cap=&out;calls=0;Timeline timeline;active=&timeline;float values[]={-1.0f,0.0f,0.125f,0.5f,1.0f,3.0f,9.0f};timeline.m_bTimelineLoops=(seed/2)&1;timeline.m_bIsPlayingBackwards=seed&1;timeline.m_bEnabled=(seed/4)&1;timeline.m_fSetTimelineDuration=values[(seed/8)%7];timeline.m_fTimelinePosition=values[(seed/17)%7];timeline.m_fGetTimelineStep=values[(seed/31)%5];timeline.m_fSetTimelineStep=values[(seed/43)%6];float elapsed=values[(seed/3)%7];unsigned long long scene[(sizeof(CEditorScene)+7)/8]={0};unsigned long long resource[2]={0};CResourceManager*r=reinterpret_cast<CResourceManager*>(resource);std::memcpy(reinterpret_cast<char*>(scene)+0x68,&r,sizeof(r));timeline.SetSceneOwner(reinterpret_cast<CEditorScene*>(scene));unsigned long long propertyMemory[3][(sizeof(CTimelineProperty)+7)/8]={0};typedef std::map<std::pair<int,bool>,CTimelineProperty*> Map;for(unsigned i=0;i<3;++i){props[i]=reinterpret_cast<CTimelineProperty*>(propertyMemory[i]);if(i<seed%4){Map*m=new Map;(*m)[std::make_pair(i,bool(i&1))]=props[i];timeline.m_timelineProperties[10+i]=m;}}
 detour::Set patches;TL_REDIRECT(patches,editorRunning,&editor);TL_REDIRECT(patches,propertyUpdate,&property);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef float(*Fn)(CTimeline*,float);Fn fn=ours?newUpdate:oldUpdate;if(!autotest::beginInvocation(out,fn))return;float result=fn(&timeline,elapsed);out.callCompleted=1;parentpairs::scalar(out,result);parentpairs::scalar(out,timeline.m_bEnabled);parentpairs::scalar(out,timeline.m_fTimelinePosition);parentpairs::scalar(out,timeline.m_fSetTimelineStep);parentpairs::scalar(out,timeline.m_fSetTimelineDuration);parentpairs::scalar(out,calls);for(std::map<long long,Map*>::iterator i=timeline.m_timelineProperties.begin();i!=timeline.m_timelineProperties.end();++i)delete i->second;timeline.m_timelineProperties.clear();timeline.SetSceneOwner(NULL);}
void a(void*p,autotest::Capture&c){side(p,c,false);}void b(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(advance_logic_timeline_update){return parentpairs::run(host,"advance_logic_timeline_update",(uintptr_t)oldUpdate,448,a,b);}
