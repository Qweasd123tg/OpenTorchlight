#include <cstring>
#include <stdint.h>
#include <limits>
#include "AutoTest.h"
#include "Detour.h"
#include "TimelineProperty.h"
#include "Timeline.h"
#define TARGET(ret,old,newer,args,symbol) TL_ORIGINAL(ret,old,args,symbol) extern "C" ret newer args __asm__(symbol);
TARGET(void,ctOldLinear,ctNewLinear,(CTimelineProperty*,CTimeline*,float,CTimelineProperty::CTimelinePoint*,CTimelineProperty::CTimelinePoint*),"_ZN17CTimelineProperty21DoLinearInterpolationEP9CTimelinefPNS_14CTimelinePointES3_")
TARGET(void,ctOldUpdate,ctNewUpdate,(CTimelineProperty*,float,bool),"_ZN17CTimelineProperty6UpdateEfb")
TARGET(int,ctOldAdd,ctNewAdd,(CTimelineProperty*),"_ZN17CTimelineProperty8AddPointEv")
TL_FUNCTION(ctGet,"_ZN15CDescriptorProp7getDataERjP17CEditorBaseObject")
TL_FUNCTION(ctType,"_ZN15CDescriptorProp15getVariableTypeEv")
TL_FUNCTION(ctSet,"_ZN15CDescriptorProp7setDataEPK14UNIONDATA32BITjP17CEditorBaseObject")
TL_FUNCTION(ctScene,"_ZN12CEditorScene16GetObjectInSceneEx")
TL_FUNCTION(ctScalar,"_ZN17CTimelineProperty33getValueOfLinearPropertyByPercentEjdPNS_14CTimelinePointES1_j")
TL_FUNCTION(ctValue,"_ZN17CTimelineProperty16SetValueOnObjectEPvj")
TL_FUNCTION(ctPoint,"_ZN17CTimelineProperty16SetValueOnObjectEPNS_14CTimelinePointE")
TL_FUNCTION(ctLinear,"_ZN17CTimelineProperty21DoLinearInterpolationEP9CTimelinefPNS_14CTimelinePointES3_")
TL_FUNCTION(ctSpline,"_ZN17CTimelineProperty21DoSplineInterpolationEP9CTimelinef")
TL_FUNCTION(ctEvent,"_ZN17CTimelineProperty12triggerEventEP9CTimeline")
TL_FUNCTION(ctInterpolation,"_ZN17CTimelineProperty20SetInterpolationTypeE22ETIMELINE_INTERP_TYPES")
TL_FUNCTION(ctPropCtor,"_ZN15CDescriptorPropC1EPS_P17CEditorBaseObject")
namespace {
struct Case{unsigned mode,seed;};autotest::Capture* out;unsigned seed;CTimelineProperty* self;CTimelineProperty::CTimelinePoint* points[4];CDescriptorProp* property;void* object;unsigned components[2];UNIONDATA32BIT data[2][4];
void number(unsigned x){out->add(&x,4);}void real(float x){out->add(&x,4);}void check(bool b){if(!b)out->issue=autotest::Capture::InvalidReport;}
unsigned index(CTimelineProperty::CTimelinePoint* p){for(unsigned i=0;i<4;++i)if(p==points[i])return i;return 99;}
void* get(CDescriptorProp* p,unsigned& size,CEditorBaseObject* ob){number(1);check(ob==NULL);unsigned i=p==&points[0]->m_descriptorProperty?0:1;number(i);size=components[i];return data[i];}
EVARIABLE_TYPES type(CDescriptorProp* p){number(2);check(p==property);return static_cast<EVARIABLE_TYPES>(seed%12);}
void set(CDescriptorProp* p,void* value,unsigned size,CEditorBaseObject* ob){number(3);check(p==property&&ob==object);number(value==data[0]?0:value==data[1]?1:9);number(size);}
CEditorBaseObject* scene(CEditorScene* p,long long id){number(4);check(p==self->m_editorScene&&id==self->m_objectID);return seed%11==0?NULL:static_cast<CEditorBaseObject*>(object);}
double scalar(CTimelineProperty* p,unsigned interpolation,double percent,CTimelineProperty::CTimelinePoint* from,CTimelineProperty::CTimelinePoint* to,unsigned component){number(5);check(p==self);number(interpolation);out->add(&percent,8);number(index(from));number(index(to));number(component);const double values[]={-2.75,0,0.5,0.999,1,1.001,2.75};return values[(seed+component)%7];}
void value(CTimelineProperty* p,void* v,unsigned count){number(6);check(p==self);number(count);out->add(v,count*4);}
void point(CTimelineProperty* p,CTimelineProperty::CTimelinePoint* v){number(7);check(p==self);number(index(v));}
void linear(CTimelineProperty* p,CTimeline* t,float percent,CTimelineProperty::CTimelinePoint* a,CTimelineProperty::CTimelinePoint* b){number(12);check(p==self&&t==self->m_timeline);real(percent);number(index(a));number(index(b));}
void spline(CTimelineProperty* p,CTimeline* t,float percent){number(8);check(p==self&&t==self->m_timeline);real(percent);}
void event(CTimelineProperty* p,CTimeline* t){number(9);check(p==self&&t==self->m_timeline);}
void interpolation(CTimelineProperty* p,ETIMELINE_INTERP_TYPES t){number(10);check(p==self);number(t);}
void propCtor(CDescriptorProp* p,CDescriptorProp* source,CEditorBaseObject* ob){number(11);check(source==property&&ob==object);std::memset(p,0,sizeof(*p));}
void side(void* raw,autotest::Capture& capture,bool ours){Case c=*static_cast<Case*>(raw);out=&capture;seed=c.seed;uint64_t selfMem[20]={0},pointMem[4][24]={0},timelineMem[40]={0},sceneMem[64]={0},descriptorMem[64]={0},propMem[20]={0},objectMem[24]={0};self=reinterpret_cast<CTimelineProperty*>(selfMem);property=reinterpret_cast<CDescriptorProp*>(propMem);object=objectMem;self->m_editorScene=reinterpret_cast<CEditorScene*>(sceneMem);self->m_descriptor=reinterpret_cast<CDescriptor*>(descriptorMem);self->m_descriptorProperty=property;self->m_timeline=reinterpret_cast<CTimeline*>(timelineMem);self->m_objectID=37;self->m_eventID=3;self->m_interpolationType=(seed/12)%2?7:seed%8;self->m_timeline->m_iDefaultInterpolationType=seed%7;self->m_lastTimePercent=seed%4*0.4f-0.01f;TLinkedListNode<CTimelineProperty::CTimelinePoint*> nodes[4];
 for(unsigned i=0;i<4;++i){points[i]=reinterpret_cast<CTimelineProperty::CTimelinePoint*>(pointMem[i]);points[i]->m_timePercent=i/3.0f;points[i]->m_pointID=(seed&1)?int(i):int(i+1);nodes[i].m_Data=points[i];nodes[i].m_pNext=i<3?&nodes[i+1]:NULL;nodes[i].m_pPrevious=i?&nodes[i-1]:NULL;}self->m_timelinePoints=seed%9?nodes:NULL;components[0]=seed%4;components[1]=(seed/3)%4;
 detour::Set d;TL_REDIRECT(d,ctScene,&scene);TL_REDIRECT(d,ctGet,&get);TL_REDIRECT(d,ctType,&type);TL_REDIRECT(d,ctSet,&set);TL_REDIRECT(d,ctValue,&value);TL_REDIRECT(d,ctPoint,&point);TL_REDIRECT(d,ctSpline,&spline);TL_REDIRECT(d,ctEvent,&event);TL_REDIRECT(d,ctInterpolation,&interpolation);TL_REDIRECT(d,ctPropCtor,&propCtor);
 if(c.mode==0){TL_REDIRECT(d,ctScalar,&scalar);if(seed>=72){switch(seed%7){case 0:self->m_editorScene=NULL;break;case 1:self->m_descriptor=NULL;break;case 2:self->m_descriptorProperty=NULL;break;case 3:self->m_objectID=-1LL;break;case 4:self->m_timeline=NULL;break;}}points[1]->m_timePercent=seed&2?points[0]->m_timePercent:1.0f;typedef void(*Fn)(CTimelineProperty*,CTimeline*,float,CTimelineProperty::CTimelinePoint*,CTimelineProperty::CTimelinePoint*);Fn fn=ours?ctNewLinear:ctOldLinear;if(d.failed()){out->issue=autotest::Capture::InvalidReport;return;}if(!autotest::beginInvocation(capture,fn))return;fn(self,self->m_timeline,seed%5*0.3f,seed==78?NULL:points[0],seed==79?NULL:points[1]);capture.callCompleted=1;
 }else if(c.mode==1){TL_REDIRECT(d,ctLinear,&linear);if(seed%5==0)self->m_descriptorProperty=NULL;if(seed>=64){if(seed%3==0)self->m_editorScene=NULL;else if(seed%3==1)self->m_descriptor=NULL;else self->m_objectID=0xffffffffLL;}const float percentages[]={-1,0,0.1f,0.5f,1,2,std::numeric_limits<float>::quiet_NaN()};typedef void(*Fn)(CTimelineProperty*,float,bool);Fn fn=ours?ctNewUpdate:ctOldUpdate;if(d.failed()){out->issue=autotest::Capture::InvalidReport;return;}if(!autotest::beginInvocation(capture,fn))return;fn(self,percentages[seed%7],seed&1);capture.callCompleted=1;real(self->m_lastTimePercent);number(self->m_updating);
 }else{if(seed%8==0){self->m_descriptorProperty=NULL;property=NULL;self->m_eventID=static_cast<unsigned>(-1);}if(seed%8==1)self->m_editorScene=NULL;if(seed%8==2)self->m_objectID=0xffffffffLL;if(seed%8==3)self->m_objectID=-1LL;typedef int(*Fn)(CTimelineProperty*);Fn fn=ours?ctNewAdd:ctOldAdd;if(d.failed()){out->issue=autotest::Capture::InvalidReport;return;}if(!autotest::beginInvocation(capture,fn))return;int result=fn(self);capture.callCompleted=1;number(result);if(result>=0){TLinkedListNode<CTimelineProperty::CTimelinePoint*>* added=self->m_timelinePoints;number(added->m_Data->m_pointID);real(added->m_Data->m_timePercent);number(added->m_pPrevious==NULL);number(added->m_pNext==nodes);number(nodes[0].m_pPrevious==added);Ogre::NedAllocImpl::deallocBytes(added->m_Data);Ogre::NedAllocImpl::deallocBytes(added);}}
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char* name,uintptr_t address,unsigned count){autotest::Coverage coverage(name,address);for(unsigned i=0;i<count;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(h,a,b)){h->log("    timeline op%u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",mode,i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k<a.capture.length&&k<b.capture.length;k+=4){unsigned av=0,bv=0;std::memcpy(&av,a.capture.data+k,4);std::memcpy(&bv,b.capture.data+k,4);h->log("    word%u %x/%x\n",k,av,bv);}coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
TL_TEST(continuation_timeline_linear){return run(host,0,"continuation_timeline_linear",(uintptr_t)&ctOldLinear,84);}
TL_TEST(continuation_timeline_update){return run(host,1,"continuation_timeline_update",(uintptr_t)&ctOldUpdate,72);}
TL_TEST(continuation_timeline_add){return run(host,2,"continuation_timeline_add",(uintptr_t)&ctOldAdd,32);}
