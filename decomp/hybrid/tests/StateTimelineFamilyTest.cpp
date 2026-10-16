#include "AutoTest.h"
#include "Detour.h"
#include "Timeline.h"
#include "TimelineProperty.h"
#include "EditorScene.h"
#include "ResourceManager.h"
#include <limits>

namespace {
struct Case { unsigned op, index; };
typedef void(*Side)(void*,autotest::Capture&);
int runCases(const tlhybrid_host* host,unsigned op,unsigned count,const char* name,uint64_t address,Side original,Side candidate)
{
    autotest::Coverage coverage(name,address);
    for(unsigned i=0;i<count;++i) {
        Case c={op,i};autotest::Outcome& a=autotest::g_outcomes[0];autotest::Outcome& b=autotest::g_outcomes[1];
        autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);
        if(coverage.observe(host,a,b)) {
            host->log("    %s case %u original status %d issue %u started %u completed %u; candidate status %d issue %u started %u completed %u\n",name,i,a.childStatus,a.capture.issue,a.capture.callStarted,a.capture.callCompleted,b.childStatus,b.capture.issue,b.capture.callStarted,b.capture.callCompleted);
            coverage.report(host);return 1;
        }
    }
    coverage.report(host);return coverage.completed!=count || coverage.different || coverage.missing;
}
}
TL_ORIGINAL(void, old7b6cd0, (CTimeline*, float), "_ZN9CTimeline24resetPropertiesToPercentEf")
extern "C" void new7b6cd0(CTimeline*, float) __asm__("_ZN9CTimeline24resetPropertiesToPercentEf");
TL_ORIGINAL(float, old7baef0, (CTimeline*, float), "_ZN9CTimeline22SetTimelinePercentDoneEf")
extern "C" float new7baef0(CTimeline*, float) __asm__("_ZN9CTimeline22SetTimelinePercentDoneEf");
TL_ORIGINAL(bool, old7b6990, (CTimeline*, long long, int, bool), "_ZN9CTimeline14RemovePropertyExib")
extern "C" bool new7b6990(CTimeline*, long long, int, bool) __asm__("_ZN9CTimeline14RemovePropertyExib");
TL_ORIGINAL(bool, old7b6a90, (CTimeline*, long long), "_ZN9CTimeline16RemoveObjectByIDEx")
extern "C" bool new7b6a90(CTimeline*, long long) __asm__("_ZN9CTimeline16RemoveObjectByIDEx");
TL_FUNCTION(propertyUpdate,"_ZN17CTimelineProperty6UpdateEfb")
TL_FUNCTION(editorRunning,"_ZN16CResourceManager18getEditorIsRunningEv")
namespace {
autotest::Capture* capture;unsigned seed,calls;CTimelineProperty* points[12];
void update(CTimelineProperty* p,float percent,bool direction){++calls;unsigned id=99;for(unsigned i=0;i<12;++i)if(points[i]==p)id=i;capture->add(&id,4);capture->add(&percent,4);capture->add(&direction,1);if(id==99)capture->issue=autotest::Capture::InvalidReport;p->m_lastTimePercent=percent;p->m_updating=direction;}
bool running(CResourceManager* p){bool isNull=p==NULL;capture->add(&isNull,1);return seed%3==0;}
void side(void* raw,autotest::Capture& out,bool ours)
{
 Case c=*static_cast<Case*>(raw);capture=&out;seed=c.index;calls=0;
 CTimeline timeline;CEditorScene scene(L"timeline-test");timeline.CEditorBaseObject::SetSceneOwner(&scene);
 typedef std::map<std::pair<int,bool>,CTimelineProperty*> Properties;
 for(unsigned i=0;i<12;++i)points[i]=NULL;
 for(unsigned i=0;i<c.index%4;++i){Properties* properties=new Properties;timeline.m_timelineProperties[static_cast<long long>(i)*0x100000001LL]=properties;
   for(unsigned j=0;j<c.index/4%4;++j){unsigned id=i*4+j;points[id]=new CTimelineProperty(&timeline,NULL,NULL,j,bool(j%2),i);points[id]->m_lastTimePercent=float(id)*0.125f;points[id]->m_updating=true;(*properties)[std::make_pair(int(j)-1,bool(j%2))]=points[id];}}
 const float values[]={-2,-0.0f,0,0.125f,0.999f,1,2,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};float percent=values[c.index%9];
 timeline.m_fSetTimelineDuration=c.index%3==0?0:c.index%3==1?7.25f:-4.5f;
 timeline.m_fGetTimelineStep=c.index/3%4==0?0:c.index/3%4==1?-0.5f:c.index/3%4==2?0.25f:std::numeric_limits<float>::quiet_NaN();
 timeline.m_bEnabled=c.index%2;timeline.m_bIsPlayingBackwards=bool(c.index%3);
 detour::Set patches;if(c.op==1){TL_REDIRECT(patches,propertyUpdate,&update);TL_REDIRECT(patches,editorRunning,&running);}if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.op==0){typedef void(*Fn)(CTimeline*,float);Fn fn=ours?new7b6cd0:old7b6cd0;if(!autotest::beginInvocation(out,fn))return;fn(&timeline,percent);out.callCompleted=1;}
 else if(c.op==1){typedef float(*Fn)(CTimeline*,float);Fn fn=ours?new7baef0:old7baef0;if(!autotest::beginInvocation(out,fn))return;float value=fn(&timeline,percent);out.callCompleted=1;out.add(&value,4);out.add(&timeline.m_fTimelinePosition,4);out.add(&timeline.m_fSetTimelineStep,4);out.add(&calls,4);}
 else if(c.op==2){typedef bool(*Fn)(CTimeline*,long long,int,bool);Fn fn=ours?new7b6990:old7b6990;if(!autotest::beginInvocation(out,fn))return;bool value=fn(&timeline,static_cast<long long>(int(c.index/3%5)-1)*0x100000001LL,int(c.index/5%5)-2,bool(c.index%2));out.callCompleted=1;out.add(&value,1);}
 else {typedef bool(*Fn)(CTimeline*,long long);Fn fn=ours?new7b6a90:old7b6a90;if(!autotest::beginInvocation(out,fn))return;bool value=fn(&timeline,static_cast<long long>(int(c.index/3%5)-1)*0x100000001LL);out.callCompleted=1;out.add(&value,1);}
 unsigned n=timeline.m_timelineProperties.size();out.add(&n,4);
 for(std::map<long long,Properties*>::iterator i=timeline.m_timelineProperties.begin();i!=timeline.m_timelineProperties.end();++i){out.add(&i->first,8);n=i->second->size();out.add(&n,4);for(Properties::iterator j=i->second->begin();j!=i->second->end();++j){out.add(&j->first.first,4);out.add(&j->first.second,1);out.add(&j->second->m_lastTimePercent,4);out.add(&j->second->m_updating,1);}}
}
void original(void*p,autotest::Capture&c){side(p,c,false);}void candidate(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(state_timeline_7b6cd0) {return runCases(host,0,108,"state_timeline_7b6cd0",(uint64_t)(uintptr_t)old7b6cd0,original,candidate);}
TL_TEST(state_timeline_7baef0) {return runCases(host,1,108,"state_timeline_7baef0",(uint64_t)(uintptr_t)old7baef0,original,candidate);}
TL_TEST(state_timeline_7b6990) {return runCases(host,2,108,"state_timeline_7b6990",(uint64_t)(uintptr_t)old7b6990,original,candidate);}
TL_TEST(state_timeline_7b6a90) {return runCases(host,3,108,"state_timeline_7b6a90",(uint64_t)(uintptr_t)old7b6a90,original,candidate);}
