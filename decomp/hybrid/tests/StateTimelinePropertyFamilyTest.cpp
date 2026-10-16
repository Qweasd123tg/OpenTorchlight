#include "AutoTest.h"
#include "Detour.h"
#include "Timeline.h"
#include "TimelineProperty.h"
#include "DescriptorProp.h"
#include "EditorScene.h"
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
TL_ORIGINAL(void, old7ccf70, (CTimelineProperty*, int, std::wstring&), "_ZN17CTimelineProperty23SetValueAtPointByStringEiRSbIwSt11char_traitsIwESaIwEE")
extern "C" void new7ccf70(CTimelineProperty*, int, std::wstring&) __asm__("_ZN17CTimelineProperty23SetValueAtPointByStringEiRSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(double, old7c8730, (CTimelineProperty*, unsigned, double, CTimelineProperty::CTimelinePoint*, CTimelineProperty::CTimelinePoint*, unsigned), "_ZN17CTimelineProperty33getValueOfLinearPropertyByPercentEjdPNS_14CTimelinePointES1_j")
extern "C" double new7c8730(CTimelineProperty*, unsigned, double, CTimelineProperty::CTimelinePoint*, CTimelineProperty::CTimelinePoint*, unsigned) __asm__("_ZN17CTimelineProperty33getValueOfLinearPropertyByPercentEjdPNS_14CTimelinePointES1_j");
TL_ORIGINAL(std::wstring, old7c95b0, (CTimelineProperty*, int), "_ZN17CTimelineProperty23GetValueAtPointAsStringEi")
extern "C" std::wstring new7c95b0(CTimelineProperty*, int) __asm__("_ZN17CTimelineProperty23GetValueAtPointAsStringEi");
TL_ORIGINAL(void, old7c83a0, (CTimelineProperty*, int, float), "_ZN17CTimelineProperty21SetTimePercentAtPointEif")
extern "C" void new7c83a0(CTimelineProperty*, int, float) __asm__("_ZN17CTimelineProperty21SetTimePercentAtPointEif");
TL_ORIGINAL(void, old7c88d0, (CTimelineProperty*), "_ZN17CTimelineProperty18fillSplineWithDataEv")
extern "C" void new7c88d0(CTimelineProperty*) __asm__("_ZN17CTimelineProperty18fillSplineWithDataEv");
TL_ORIGINAL(void, old7c8a10, (CTimelineProperty*, ETIMELINE_INTERP_TYPES), "_ZN17CTimelineProperty20SetInterpolationTypeE22ETIMELINE_INTERP_TYPES")
extern "C" void new7c8a10(CTimelineProperty*, ETIMELINE_INTERP_TYPES) __asm__("_ZN17CTimelineProperty20SetInterpolationTypeE22ETIMELINE_INTERP_TYPES");
TL_ORIGINAL(int,addPointOriginal,(CTimelineProperty*),"_ZN17CTimelineProperty8AddPointEv")
TL_FUNCTION(lookupObject,"_ZN12CEditorScene16GetObjectInSceneEx")
TL_FUNCTION(valueString,"_ZN15CDescriptorProp24getPropertyValueAsStringEP17CEditorBaseObject")
TL_FUNCTION(setString,"_ZN15CDescriptorProp24setPropertyValueByStringESbIwSt11char_traitsIwESaIwEEP17CEditorBaseObject")
namespace {
autotest::Capture* capture;CEditorBaseObject* realObject;CEditorScene* realScene;CTimelineProperty::CTimelinePoint* points[5];unsigned pointCount,calls;
CEditorBaseObject* lookup(CEditorScene* p,long long id){if(p!=realScene||id!=7)capture->issue=autotest::Capture::InvalidReport;return realObject;}
unsigned identity(CDescriptorProp* p){for(unsigned i=0;i<pointCount;++i)if(p==&points[i]->m_descriptorProperty)return i;capture->issue=autotest::Capture::InvalidReport;return 99;}
std::wstring getString(CDescriptorProp* p,CEditorBaseObject* object){++calls;unsigned id=identity(p);capture->add(&id,4);bool valid=object==NULL;capture->add(&valid,1);return id%2?L"point value":L"";}
void writeString(CDescriptorProp* p,std::wstring value,CEditorBaseObject* object){++calls;unsigned id=identity(p);capture->add(&id,4);capture->addText(value);bool valid=object==NULL;capture->add(&valid,1);if(!valid)capture->issue=autotest::Capture::InvalidReport;}
void side(void* raw,autotest::Capture& out,bool ours)
{
 Case c=*static_cast<Case*>(raw);capture=&out;calls=0;
 CEditorBaseObject object;realObject=&object;CEditorScene scene(L"property-test");realScene=&scene;CTimeline timeline;
 CDescriptorProp descriptor(L"category",L"name",L"description",NULL,NULL,VARIABLE_TYPE_INTEGER,0);
 for(unsigned i=0;i<3;++i){UNIONDATA32BIT value;value.m_iValue=int(i)*5-3;descriptor.m_DefaultValue.add(value);}
 CTimelineProperty* property=new CTimelineProperty(&timeline,&scene,NULL,~0u,false,7);property->m_descriptorProperty=&descriptor;
 pointCount=c.op==1?2:c.index%5;
 {detour::Set setup;TL_REDIRECT(setup,lookupObject,&lookup);if(setup.failed()){out.issue=autotest::Capture::InvalidReport;return;}for(unsigned i=0;i<pointCount;++i)if(addPointOriginal(property)<0){out.issue=autotest::Capture::InvalidReport;return;}}
 unsigned index=0;for(TLinkedListNode<CTimelineProperty::CTimelinePoint*>* node=property->m_timelinePoints;node;node=node->m_pNext){points[index]=node->m_Data;points[index]->m_pointID=index*2;points[index]->m_timePercent=float(index)*0.25f;++index;}
 int query=int(c.index/5%7)-2;float values[]={-2,-0.0f,0,0.125f,0.5f,1,2,std::numeric_limits<float>::quiet_NaN()};
 detour::Set patches;if(c.op==0)TL_REDIRECT(patches,setString,&writeString);if(c.op==2)TL_REDIRECT(patches,valueString,&getString);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.op==0){std::wstring value=c.index%2?L"edited value":L"";if(c.index%3==0)value.append(1,wchar_t(0));typedef void(*Fn)(CTimelineProperty*,int,std::wstring&);Fn fn=ours?new7ccf70:old7ccf70;if(!autotest::beginInvocation(out,fn))return;fn(property,query,value);out.callCompleted=1;out.addText(value);}
 else if(c.op==1){descriptor.m_eType=static_cast<EVARIABLE_TYPES>(c.index%11);for(unsigned j=0;j<2;++j){points[j]->m_descriptorProperty.m_DefaultValue.clear();for(unsigned i=0;i<c.index/11%4;++i){UNIONDATA32BIT value;if(descriptor.m_eType==VARIABLE_TYPE_FLOAT||descriptor.m_eType>=VARIABLE_TYPE_VECTOR2)value.m_fValue=float(int(c.index)-40+i)*0.125f*(j?1:-1);else value.m_iValue=(int(c.index)-20+i)*(j?3:-2);points[j]->m_descriptorProperty.m_DefaultValue.add(value);}}
  double percent=double(int(c.index/7%9)-3)*0.25;typedef double(*Fn)(CTimelineProperty*,unsigned,double,CTimelineProperty::CTimelinePoint*,CTimelineProperty::CTimelinePoint*,unsigned);Fn fn=ours?new7c8730:old7c8730;if(!autotest::beginInvocation(out,fn))return;double value=fn(property,c.index/11%5,percent,points[0],points[1],c.index/13%4);out.callCompleted=1;out.add(&value,8);
 } else if(c.op==2){typedef std::wstring(*Fn)(CTimelineProperty*,int);Fn fn=ours?new7c95b0:old7c95b0;if(!autotest::beginInvocation(out,fn))return;std::wstring value=fn(property,query);out.callCompleted=1;out.addText(value);}
 else if(c.op==3){typedef void(*Fn)(CTimelineProperty*,int,float);Fn fn=ours?new7c83a0:old7c83a0;if(!autotest::beginInvocation(out,fn))return;fn(property,query,values[c.index/5%8]);out.callCompleted=1;}
 else {
  descriptor.m_eType=static_cast<EVARIABLE_TYPES>(c.index%10);
  unsigned components=descriptor.m_eType==VARIABLE_TYPE_VECTOR3?3:descriptor.m_eType==VARIABLE_TYPE_VECTOR2?2:1;
  for(unsigned j=0;j<pointCount;++j){points[j]->m_descriptorProperty.m_DefaultValue.clear();for(unsigned i=0;i<components;++i){UNIONDATA32BIT value;value.m_iValue=int(j*7+i)-5;points[j]->m_descriptorProperty.m_DefaultValue.add(value);}}
  if(c.index%7==0)property->m_descriptorProperty=NULL;
  if(c.op==4){typedef void(*Fn)(CTimelineProperty*);Fn fn=ours?new7c88d0:old7c88d0;if(!autotest::beginInvocation(out,fn))return;fn(property);out.callCompleted=1;}
  else {typedef void(*Fn)(CTimelineProperty*,ETIMELINE_INTERP_TYPES);Fn fn=ours?new7c8a10:old7c8a10;if(!autotest::beginInvocation(out,fn))return;fn(property,static_cast<ETIMELINE_INTERP_TYPES>(c.index/10%8));out.callCompleted=1;}
  out.add(&property->m_interpolationType,4);
  // Unsupported types call SetInterpolationType(0), leaving the freed spline
  // pointer untouched in the original; observe control state without reading it.
  bool supported=descriptor.m_eType==VARIABLE_TYPE_INTEGER||descriptor.m_eType==VARIABLE_TYPE_FLOAT||descriptor.m_eType==VARIABLE_TYPE_UNSIGNED_INTEGER||descriptor.m_eType==VARIABLE_TYPE_BOOL||descriptor.m_eType==VARIABLE_TYPE_VECTOR2||descriptor.m_eType==VARIABLE_TYPE_VECTOR3;
  bool live=property->m_spline && (c.op==4?(!pointCount||supported):property->m_interpolationType==4);
  if(live){unsigned n=property->m_spline->getNumPoints();out.add(&n,4);for(unsigned i=0;i<n;++i){const Ogre::Vector3& value=property->m_spline->getPoint(i);out.add(&value.x,4);if(components>=2)out.add(&value.y,4);if(components>=3)out.add(&value.z,4);}}
  else if(property->m_spline)property->m_spline=NULL;
 }
 out.add(&calls,4);unsigned count=0;
 for(TLinkedListNode<CTimelineProperty::CTimelinePoint*>* node=property->m_timelinePoints;node;node=node->m_pNext){if(++count>pointCount){out.issue=autotest::Capture::InvalidReport;break;}out.add(&node->m_Data->m_pointID,4);out.add(&node->m_Data->m_timePercent,4);bool previousValid=node->m_pNext==NULL||node->m_pNext->m_pPrevious==node;out.add(&previousValid,1);if(!previousValid)out.issue=autotest::Capture::InvalidReport;}
 if(count!=pointCount)out.issue=autotest::Capture::InvalidReport;
 delete property;
}
void original(void*p,autotest::Capture&c){side(p,c,false);}void candidate(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(state_property_7ccf70) {return runCases(host,0,220,"state_property_7ccf70",(uint64_t)(uintptr_t)old7ccf70,original,candidate);}
TL_TEST(state_property_7c8730) {return runCases(host,1,220,"state_property_7c8730",(uint64_t)(uintptr_t)old7c8730,original,candidate);}
TL_TEST(state_property_7c95b0) {return runCases(host,2,220,"state_property_7c95b0",(uint64_t)(uintptr_t)old7c95b0,original,candidate);}
TL_TEST(state_property_7c83a0) {return runCases(host,3,220,"state_property_7c83a0",(uint64_t)(uintptr_t)old7c83a0,original,candidate);}
TL_TEST(state_property_7c88d0) {return runCases(host,4,220,"state_property_7c88d0",(uint64_t)(uintptr_t)old7c88d0,original,candidate);}
TL_TEST(state_property_7c8a10) {return runCases(host,5,220,"state_property_7c8a10",(uint64_t)(uintptr_t)old7c8a10,original,candidate);}
