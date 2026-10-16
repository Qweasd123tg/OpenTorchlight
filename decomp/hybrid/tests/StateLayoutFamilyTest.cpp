#include "AutoTest.h"
#include "Detour.h"
#include "Layout.h"
#include "Timeline.h"
#include "Particle.h"
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
TL_ORIGINAL(void, old9d3ea0, (CLayout*, bool), "_ZN7CLayout10setVisibleEb")
extern "C" void new9d3ea0(CLayout*, bool) __asm__("_ZN7CLayout10setVisibleEb");
TL_ORIGINAL(void, old9de2d0, (CLayout*, bool), "_ZN7CLayout14setStartOnLoadEb")
extern "C" void new9de2d0(CLayout*, bool) __asm__("_ZN7CLayout14setStartOnLoadEb");
TL_ORIGINAL(void, old9dfa60, (CLayout*), "_ZN7CLayout10initOnLoadEv")
extern "C" void new9dfa60(CLayout*) __asm__("_ZN7CLayout10initOnLoadEv");
TL_ORIGINAL(void, old9d3f40, (CLayout*, CResourceManager*, ELAYOUT_TYPES), "_ZN7CLayoutC1EP16CResourceManager13ELAYOUT_TYPES")
extern "C" void new9d3f40(CLayout*, CResourceManager*, ELAYOUT_TYPES) __asm__("_ZN7CLayoutC1EP16CResourceManager13ELAYOUT_TYPES");
TL_ORIGINAL(void, old9d3d10, (CLayout*, float), "_ZN7CLayout23setDurationModificationEf")
extern "C" void new9d3d10(CLayout*, float) __asm__("_ZN7CLayout23setDurationModificationEf");
TL_ORIGINAL(CLayout*, old9ddb00, (CLayout*, const std::wstring&), "_ZN7CLayout16getLayoutToCloneERKSbIwSt11char_traitsIwESaIwEE")
extern "C" CLayout* new9ddb00(CLayout*, const std::wstring&) __asm__("_ZN7CLayout16getLayoutToCloneERKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void,layoutCtor,(CLayout*,CResourceManager*,ELAYOUT_TYPES),"_ZN7CLayoutC1EP16CResourceManager13ELAYOUT_TYPES")
TL_FUNCTION(initScene,"_ZN12CEditorScene9InitSceneEP16CResourceManagerj")
TL_FUNCTION(editorRunning,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(startLayout,"_ZN7CLayout5startEv")
TL_FUNCTION(stopLayout,"_ZN7CLayout4stopEb")
TL_FUNCTION(startParticle,"_ZN9CParticle5StartEv")
TL_FUNCTION(stopParticle,"_ZN9CParticle4StopEb")
TL_FUNCTION(objectsByDescriptor,"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEE")
namespace {
autotest::Capture* capture;CLayout* receiver;CParticle* particle;unsigned seed,calls,initCalls;TArrayList<CEditorBaseObject*> timelineList;
void number(unsigned n){capture->add(&n,4);}
void sceneInit(CEditorScene* object,CResourceManager* manager,unsigned flags){++initCalls;bool valid=object==receiver&&manager==NULL&&flags==0;capture->add(&valid,1);if(!valid)capture->issue=autotest::Capture::InvalidReport;}
bool running(CResourceManager* p){++calls;number(1);number(p==NULL);return seed%3!=0;}
void start(CLayout* p){++calls;number(2);number(p==receiver);if(p!=receiver)capture->issue=autotest::Capture::InvalidReport;}
void stop(CLayout* p,bool immediate){++calls;number(3);number(p==receiver);capture->add(&immediate,1);if(p!=receiver||immediate)capture->issue=autotest::Capture::InvalidReport;}
void particleStart(CParticle* p){++calls;number(4);number(p==particle);if(p!=particle)capture->issue=autotest::Capture::InvalidReport;}
void particleStop(CParticle* p,bool immediate){++calls;number(5);number(p==particle);capture->add(&immediate,1);if(p!=particle||immediate)capture->issue=autotest::Capture::InvalidReport;}
TArrayList<CEditorBaseObject*>* objects(CEditorScene* p,const std::wstring& name){++calls;number(6);number(p==receiver);capture->addText(name);if(p!=receiver||name!=L"Timeline")capture->issue=autotest::Capture::InvalidReport;return seed%5==0?NULL:&timelineList;}
void state(CLayout* p){capture->add(&p->m_bStartOnLoad,1);capture->add(&p->m_iRandomWeight,4);capture->add(&p->m_iUnknown1A8,4);capture->add(&p->m_iUnknown1AC,4);capture->add(&p->m_iUnknown1B0,4);capture->add(&p->m_fDurationModification,4);capture->add(&p->m_Unknown1B8,4);capture->add(&p->m_iUnknown1C0,8);capture->add(&p->m_bUnknown1C8,1);capture->add(&p->m_bUnknown1C9,1);capture->add(&p->m_bUnknown1E8,1);bool enabled=p->getEnabled(),visible=p->getVisible();capture->add(&enabled,1);capture->add(&visible,1);}
void side(void* raw,autotest::Capture& out,bool ours)
{
 Case c=*static_cast<Case*>(raw);capture=&out;seed=c.index;calls=initCalls=0;
 receiver=static_cast<CLayout*>(autotest::allocate(sizeof(CLayout)));
 ELAYOUT_TYPES type=static_cast<ELAYOUT_TYPES>(c.index%4);
 if(c.op==3){detour::Set patches;TL_REDIRECT(patches,initScene,&sceneInit);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef void(*Fn)(CLayout*,CResourceManager*,ELAYOUT_TYPES);Fn fn=ours?new9d3f40:old9d3f40;if(!autotest::beginInvocation(out,fn))return;fn(receiver,NULL,type);out.callCompleted=1;out.add(&initCalls,4);state(receiver);return;}
 {detour::Set setup;TL_REDIRECT(setup,initScene,&sceneInit);if(setup.failed()){out.issue=autotest::Capture::InvalidReport;return;}layoutCtor(receiver,NULL,type);}
 out.add(&initCalls,4);if(initCalls!=1){out.issue=autotest::Capture::InvalidReport;return;}
 CTimeline timeline[3];CEditorBaseObject other;
 for(unsigned i=0;i<3;++i){timeline[i].m_bLayoutCanControl=(i+c.index)%2;timeline[i].m_iDurationModificationType=i;timeline[i].m_fSetTimelineDuration=4+i;timeline[i].m_bStartOnLoad=true;timeline[i].m_bManualUpdate=false;}
 for(unsigned i=0;i<c.index%6;++i)receiver->m_Unknown1D0.add(i<3?static_cast<CEditorBaseObject*>(&timeline[i]):i==3?&other:NULL);
 if(c.op==0){CParticle actualParticle(NULL,std::wstring(L"fixture"),NULL);particle=&actualParticle;receiver->CSceneNodeObject::setVisible(bool(c.index%2));receiver->m_pParticle=c.index%3?particle:NULL;
  detour::Set patches;TL_REDIRECT(patches,startParticle,&particleStart);TL_REDIRECT(patches,stopParticle,&particleStop);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef void(*Fn)(CLayout*,bool);Fn fn=ours?new9d3ea0:old9d3ea0;if(!autotest::beginInvocation(out,fn))return;fn(receiver,bool(c.index/2%2));out.callCompleted=1;receiver->m_pParticle=NULL;
 } else if(c.op==1){detour::Set patches;TL_REDIRECT(patches,editorRunning,&running);TL_REDIRECT(patches,startLayout,&start);TL_REDIRECT(patches,stopLayout,&stop);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef void(*Fn)(CLayout*,bool);Fn fn=ours?new9de2d0:old9de2d0;if(!autotest::beginInvocation(out,fn))return;fn(receiver,bool(c.index/3%2));out.callCompleted=1;
 } else if(c.op==2){receiver->m_bStartOnLoad=c.index%2;timelineList.clear();for(unsigned i=0;i<c.index/2%4;++i)timelineList.add(&timeline[i]);detour::Set patches;TL_REDIRECT(patches,objectsByDescriptor,&objects);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef void(*Fn)(CLayout*);Fn fn=ours?new9dfa60:old9dfa60;if(!autotest::beginInvocation(out,fn))return;fn(receiver);out.callCompleted=1;timelineList.clear();
 } else if(c.op==4){const float values[]={-2,-0.0f,0,0.125f,1,2,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};typedef void(*Fn)(CLayout*,float);Fn fn=ours?new9d3d10:old9d3d10;if(!autotest::beginInvocation(out,fn))return;fn(receiver,values[c.index/4%8]);out.callCompleted=1;
 } else {receiver->removeAllCloneableObjects();receiver->addLayoutForCloningAndControlling(std::wstring(L"alpha"));receiver->addLayoutForCloningAndControlling(std::wstring(L"middle-long"));receiver->addLayoutForCloningAndControlling(std::wstring(L"zebra"));const wchar_t* names[]={L"",L"a",L"alpha",L"alpha-extra",L"middle",L"middle-long",L"zebra",L"zzzz",L"not present"};std::wstring name=names[c.index%9];typedef CLayout*(*Fn)(CLayout*,const std::wstring&);Fn fn=ours?new9ddb00:old9ddb00;if(!autotest::beginInvocation(out,fn))return;CLayout* value=fn(receiver,name);out.callCompleted=1;unsigned id=value==NULL?0:value==receiver?1:99;out.add(&id,4);if(id==99)out.issue=autotest::Capture::InvalidReport;receiver->removeAllCloneableObjects();}
 out.add(&calls,4);state(receiver);
 for(unsigned i=0;i<3;++i){out.add(&timeline[i].m_fSetTimelineDuration,4);out.add(&timeline[i].m_bStartOnLoad,1);out.add(&timeline[i].m_bManualUpdate,1);}
 receiver->m_Unknown1D0.clear();
}
void original(void*p,autotest::Capture&c){side(p,c,false);}void candidate(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(state_layout_9d3ea0) {return runCases(host,0,96,"state_layout_9d3ea0",(uint64_t)(uintptr_t)old9d3ea0,original,candidate);}
TL_TEST(state_layout_9de2d0) {return runCases(host,1,96,"state_layout_9de2d0",(uint64_t)(uintptr_t)old9de2d0,original,candidate);}
TL_TEST(state_layout_9dfa60) {return runCases(host,2,96,"state_layout_9dfa60",(uint64_t)(uintptr_t)old9dfa60,original,candidate);}
TL_TEST(state_layout_9d3f40) {return runCases(host,3,96,"state_layout_9d3f40",(uint64_t)(uintptr_t)old9d3f40,original,candidate);}
TL_TEST(state_layout_9d3d10) {return runCases(host,4,96,"state_layout_9d3d10",(uint64_t)(uintptr_t)old9d3d10,original,candidate);}
TL_TEST(state_layout_9ddb00) {return runCases(host,5,96,"state_layout_9ddb00",(uint64_t)(uintptr_t)old9ddb00,original,candidate);}
