// Differential calls into the untouched original and the recovered editor API.
// Real original RTTI tests successful casts, wrong classes and null objects.
// Collaborator spies record call order, exact arguments and receiver identity;
// object bytes and aliased reference outputs are compared after each call.
#include <cstring>
#include <limits>
#include "AutoTest.h"
#include "Detour.h"
extern "C" void* editorGlobal __asm__("gEditor");
extern "C" void* groupTable[] __asm__("_ZTV11CLogicGroup");
extern "C" void* timelineTable[] __asm__("_ZTV9CTimeline");
extern "C" void* baseTable[] __asm__("_ZTV17CEditorBaseObject");
TL_ORIGINAL(unsigned,original0,(long long,unsigned,unsigned),"_Z33EditorGetLogicLinkInputFunctionIDxjj")
extern "C" unsigned candidate0(long long,unsigned,unsigned) __asm__("_Z33EditorGetLogicLinkInputFunctionIDxjj");
TL_ORIGINAL(unsigned,original1,(long long,unsigned,unsigned),"_Z34EditorGetLogicLinkOutputFunctionIDxjj")
extern "C" unsigned candidate1(long long,unsigned,unsigned) __asm__("_Z34EditorGetLogicLinkOutputFunctionIDxjj");
TL_ORIGINAL(unsigned,original2,(long long,unsigned,unsigned),"_Z31EditorGetLogicObjectIDLinkingToxjj")
extern "C" unsigned candidate2(long long,unsigned,unsigned) __asm__("_Z31EditorGetLogicObjectIDLinkingToxjj");
TL_ORIGINAL(void,original3,(long long,unsigned,int*,int*),"_Z28EditorGetLogicObjectPositionxjRiS_")
extern "C" void candidate3(long long,unsigned,int*,int*) __asm__("_Z28EditorGetLogicObjectPositionxjRiS_");
TL_ORIGINAL(void,original4,(long long,unsigned,int,int),"_Z28EditorSetLogicObjectPositionxjii")
extern "C" void candidate4(long long,unsigned,int,int) __asm__("_Z28EditorSetLogicObjectPositionxjii");
TL_ORIGINAL(bool,original5,(long long,unsigned,unsigned),"_Z21EditorDeleteLogicLinkxjj")
extern "C" bool candidate5(long long,unsigned,unsigned) __asm__("_Z21EditorDeleteLogicLinkxjj");
TL_ORIGINAL(bool,original6,(long long,int),"_Z23EditorDeleteLogicObjectxi")
extern "C" bool candidate6(long long,int) __asm__("_Z23EditorDeleteLogicObjectxi");
TL_ORIGINAL(void,original7,(long long,unsigned,unsigned),"_Z26EditorInvokeOutputFunctionxjj")
extern "C" void candidate7(long long,unsigned,unsigned) __asm__("_Z26EditorInvokeOutputFunctionxjj");
TL_ORIGINAL(int,original8,(long long),"_Z40EditorGetCountOfLogicObjectsInLogicGroupx")
extern "C" int candidate8(long long) __asm__("_Z40EditorGetCountOfLogicObjectsInLogicGroupx");
TL_ORIGINAL(float,original9,(long long,float),"_Z20EditorTimelineUpdatexf")
extern "C" float candidate9(long long,float) __asm__("_Z20EditorTimelineUpdatexf");
TL_ORIGINAL(long long,original10,(long long,long long,int,bool),"_Z32EditorTimelineAddPointToPropertyxxib")
extern "C" long long candidate10(long long,long long,int,bool) __asm__("_Z32EditorTimelineAddPointToPropertyxxib");
TL_ORIGINAL(long long,original11,(long long,long long,int,int,bool),"_Z49EditorTimelineGetPointIDInTimelinePropertyByIndexxxiib")
extern "C" long long candidate11(long long,long long,int,int,bool) __asm__("_Z49EditorTimelineGetPointIDInTimelinePropertyByIndexxxiib");
TL_ORIGINAL(long long,original12,(long long,long long,int,int,bool),"_Z37EditorTimelineRemovePointFromPropertyxxiib")
extern "C" long long candidate12(long long,long long,int,int,bool) __asm__("_Z37EditorTimelineRemovePointFromPropertyxxiib");
TL_ORIGINAL(long long,original13,(long long,long long,int,bool),"_Z28EditorTimelineRemovePropertyxxib")
extern "C" long long candidate13(long long,long long,int,bool) __asm__("_Z28EditorTimelineRemovePropertyxxib");
TL_ORIGINAL(float,original14,(long long,long long,int,int,bool),"_Z35EditorTimelineGetTimePercentAtPointxxiib")
extern "C" float candidate14(long long,long long,int,int,bool) __asm__("_Z35EditorTimelineGetTimePercentAtPointxxiib");
TL_ORIGINAL(void,original15,(long long,long long,int,int,float,bool),"_Z41EditorTimelineSetPropertyPointTimePercentxxiifb")
extern "C" void candidate15(long long,long long,int,int,float,bool) __asm__("_Z41EditorTimelineSetPropertyPointTimePercentxxiifb");
TL_FUNCTION(target_lookup,"_Z16GetObjectInScenex")
TL_FUNCTION(target_getTimeline,"_Z11GetTimelinex")
TL_FUNCTION(target_getLogic,"_ZN11CLogicGroup21GetLogicObjectByIndexEj")
TL_FUNCTION(target_getLink,"_ZN12CLogicObject19GetLogicLinkByIndexEj")
TL_FUNCTION(target_getInput,"_ZN10CLogicLink14GetInputFuncIDEv")
TL_FUNCTION(target_getOutput,"_ZN10CLogicLink15GetOutputFuncIDEv")
TL_FUNCTION(target_getIndex,"_ZN11CLogicGroup19GetLogicObjectIndexEP12CLogicObject")
TL_FUNCTION(target_setX,"_ZN12CLogicObject12SetXPositionEi")
TL_FUNCTION(target_setY,"_ZN12CLogicObject12SetYPositionEi")
TL_FUNCTION(target_removeLink,"_ZN11CLogicGroup22RemoveLogicObjectsLinkEjj")
TL_FUNCTION(target_removeObject,"_ZN11CLogicGroup24RemoveLogicObjectByIndexEj")
TL_FUNCTION(target_updateTimeline,"_ZN9CTimeline14UpdateTimelineEf")
TL_FUNCTION(target_addPoint,"_ZN9CTimeline18AddPointToPropertyExib")
TL_FUNCTION(target_pointID,"_ZN9CTimeline35GetPointIDInTimelinePropertyByIndexExiib")
TL_FUNCTION(target_removePoint,"_ZN9CTimeline23RemovePointFromPropertyExiib")
TL_FUNCTION(target_removeProperty,"_ZN9CTimeline14RemovePropertyExib")
TL_FUNCTION(target_getPercent,"_ZN9CTimeline27GetPropertyPointTimePercentExiib")
TL_FUNCTION(target_setPercent,"_ZN9CTimeline27SetPropertyPointTimePercentExiifb")
TL_FUNCTION(target_invokeLogic,"_ZN12CLogicObject6InvokeEj")

namespace {
struct Case {unsigned operation,mode,index,link;long long guid,object;int property,point,x,y;bool event,alias;float amount;unsigned result;float response;long long responseID;};
const Case* input;autotest::Capture* capture;unsigned lookups,updateCalls,resultCalls;
void* firstObject;void* secondObject;void* logic;void* linkedLogic;void* linkObject;void* editor2;
void number(unsigned n){capture->add(&n,4);}
unsigned identity(void*p){return !p?0:p==firstObject?1:p==secondObject?2:p==logic?3:p==linkedLogic?4:p==linkObject?5:999;}
void event(unsigned id,void*p){number(id);number(identity(p));}
void pointerAt(void*p,unsigned at,void*v){std::memcpy(static_cast<char*>(p)+at,&v,8);}
void* lookup(long long id){number(1);capture->add(&id,8);++lookups;
 if(input->mode==10)editorGlobal=editor2;
 if((lookups==1&&(input->mode==3||input->mode==11))||(lookups==2&&(input->mode==5||input->mode==11)))return NULL;
 return lookups==1?firstObject:secondObject;}
void* getTimeline(long long id){number(2);capture->add(&id,8);++lookups;return input->mode==9||input->mode==3?NULL:firstObject;}
void* getLogic(void*p,unsigned i){event(3,p);number(i);return input->mode==6?NULL:logic;}
void* getLink(void*p,unsigned i){event(4,p);number(i);return input->mode==7?NULL:linkObject;}
unsigned getInput(void*p){event(5,p);return input->result;}
unsigned getOutput(void*p){event(6,p);return input->result;}
unsigned getIndex(void*p,void*o){event(7,p);number(identity(o));return input->result;}
void setX(void*p,int x){event(8,p);capture->add(&x,4);float f=x;std::memcpy(static_cast<char*>(p)+0x70,&f,4);}
void setY(void*p,int y){event(9,p);capture->add(&y,4);float f=y;std::memcpy(static_cast<char*>(p)+0x74,&f,4);}
bool removeLink(void*p,unsigned i,unsigned j){event(10,p);number(i);number(j);return input->event;}
bool removeObject(void*p,unsigned i){event(11,p);number(i);return input->event;}
void invokeLogic(void*p,unsigned i){event(12,p);number(i);}
float updateTimeline(void*p,float t){event(13,p);capture->add(&t,4);++updateCalls;return input->response;}
long long resultID(){++resultCalls;return input->responseID;}
void timelineArgs(unsigned code,void*p,long long id,int property){event(code,p);capture->add(&id,8);capture->add(&property,4);}
long long addPoint(void*p,long long id,int property,bool e){timelineArgs(14,p,id,property);number(e);return resultID();}
long long pointID(void*p,long long id,int property,int point,bool e){timelineArgs(15,p,id,property);capture->add(&point,4);number(e);return resultID();}
long long removePoint(void*p,long long id,int property,int point,bool e){timelineArgs(16,p,id,property);capture->add(&point,4);number(e);return resultID();}
long long removeProperty(void*p,long long id,int property,bool e){timelineArgs(17,p,id,property);number(e);return resultID();}
float getPercent(void*p,long long id,int property,int point,bool e){timelineArgs(18,p,id,property);capture->add(&point,4);number(e);return input->amount;}
void setPercent(void*p,long long id,int property,int point,float value,bool e){timelineArgs(19,p,id,property);capture->add(&point,4);capture->add(&value,4);number(e);}
void side(Case&c,bool ours,autotest::Capture&out){
 input=&c;capture=&out;lookups=updateCalls=resultCalls=0;
 unsigned long long editor[2][64]={{0}},objects[2][64]={{0}},logicBytes[2][32]={{0}},linkBytes[16]={0};
 firstObject=objects[0];secondObject=objects[1];logic=logicBytes[0];linkedLogic=logicBytes[1];linkObject=linkBytes;editor2=editor[1];
 editorGlobal=editor[0];reinterpret_cast<char*>(editor[0])[0x49]=c.mode==1;
 reinterpret_cast<char*>(editor[1])[0x49]=1;
 pointerAt(editor[0],0x58,c.mode==2?NULL:editor[1]);
 pointerAt(firstObject,0,(c.mode==4?baseTable:c.operation<9?groupTable:timelineTable)+2);
 pointerAt(secondObject,0,baseTable+2);
 std::memcpy(static_cast<char*>(firstObject)+0x68,&c.result,4);
 pointerAt(linkObject,0x28,c.mode==8?NULL:linkedLogic);
 std::memcpy(static_cast<char*>(logic)+0x70,&c.amount,4);
 float f=c.amount==-0.0f?-17.75f:c.amount/2;
 std::memcpy(static_cast<char*>(logic)+0x74,&f,4);
 int x=c.x,y=c.y;
 detour::Set patches;
 TL_REDIRECT(patches,target_lookup,&lookup);
 TL_REDIRECT(patches,target_getTimeline,&getTimeline);
 TL_REDIRECT(patches,target_getLogic,&getLogic);
 TL_REDIRECT(patches,target_getLink,&getLink);
 TL_REDIRECT(patches,target_getInput,&getInput);
 TL_REDIRECT(patches,target_getOutput,&getOutput);
 TL_REDIRECT(patches,target_getIndex,&getIndex);
 TL_REDIRECT(patches,target_setX,&setX);
 TL_REDIRECT(patches,target_setY,&setY);
 TL_REDIRECT(patches,target_removeLink,&removeLink);
 TL_REDIRECT(patches,target_removeObject,&removeObject);
 TL_REDIRECT(patches,target_updateTimeline,&updateTimeline);
 TL_REDIRECT(patches,target_addPoint,&addPoint);
 TL_REDIRECT(patches,target_pointID,&pointID);
 TL_REDIRECT(patches,target_removePoint,&removePoint);
 TL_REDIRECT(patches,target_removeProperty,&removeProperty);
 TL_REDIRECT(patches,target_getPercent,&getPercent);
 TL_REDIRECT(patches,target_setPercent,&setPercent);
 TL_REDIRECT(patches,target_invokeLogic,&invokeLogic);
 if(patches.failed())_exit(41);
 switch(c.operation){
 case 0:autotest::invoke(out,ours?&candidate0:&original0,c.guid,c.index,c.link);break;
 case 1:autotest::invoke(out,ours?&candidate1:&original1,c.guid,c.index,c.link);break;
 case 2:autotest::invoke(out,ours?&candidate2:&original2,c.guid,c.index,c.link);break;
 case 3:autotest::invoke(out,ours?&candidate3:&original3,c.guid,c.index,&x,c.alias?&x:&y);break;
 case 4:autotest::invoke(out,ours?&candidate4:&original4,c.guid,c.index,c.x,c.y);break;
 case 5:autotest::invoke(out,ours?&candidate5:&original5,c.guid,c.index,c.link);break;
 case 6:autotest::invoke(out,ours?&candidate6:&original6,c.guid,static_cast<int>(c.index));break;
 case 7:autotest::invoke(out,ours?&candidate7:&original7,c.guid,c.index,c.link);break;
 case 8:autotest::invoke(out,ours?&candidate8:&original8,c.guid);break;
 case 9:autotest::invoke(out,ours?&candidate9:&original9,c.guid,c.amount);break;
 case 10:autotest::invoke(out,ours?&candidate10:&original10,c.guid,c.object,c.property,c.event);break;
 case 11:autotest::invoke(out,ours?&candidate11:&original11,c.guid,c.object,c.property,c.point,c.event);break;
 case 12:autotest::invoke(out,ours?&candidate12:&original12,c.guid,c.object,c.property,c.point,c.event);break;
 case 13:autotest::invoke(out,ours?&candidate13:&original13,c.guid,c.object,c.property,c.event);break;
 case 14:autotest::invoke(out,ours?&candidate14:&original14,c.guid,c.object,c.property,c.point,c.event);break;
 case 15:autotest::invoke(out,ours?&candidate15:&original15,c.guid,c.object,c.property,c.point,c.amount,c.event);break;

 }
 // Mode zero is an explicit live-path witness, independent of all guards.
 if(c.mode==0){
  if(c.operation==9&&(updateCalls!=1||c.response==c.amount))out.issue=autotest::Capture::InvalidReport;
  const unsigned long long id=static_cast<unsigned long long>(c.responseID);
  if(c.operation>=10&&c.operation<=13&&(resultCalls!=1||static_cast<unsigned>(id>>32)==static_cast<unsigned>(id)))
   out.issue=autotest::Capture::InvalidReport;
 }
 number(updateCalls);number(resultCalls);
 number(lookups);number(editorGlobal==editor2);out.add(&x,4);out.add(&y,4);
 out.add(editor,sizeof(editor));out.add(objects,sizeof(objects));out.add(logicBytes,sizeof(logicBytes));out.add(linkBytes,sizeof(linkBytes));
 patches.restore();
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}
void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(editor_mass_logic_timeline_differential){
 const uint64_t addresses[]={
(uint64_t)(uintptr_t)&original0,(uint64_t)(uintptr_t)&original1,(uint64_t)(uintptr_t)&original2,(uint64_t)(uintptr_t)&original3,(uint64_t)(uintptr_t)&original4,(uint64_t)(uintptr_t)&original5,(uint64_t)(uintptr_t)&original6,(uint64_t)(uintptr_t)&original7,(uint64_t)(uintptr_t)&original8,(uint64_t)(uintptr_t)&original9,(uint64_t)(uintptr_t)&original10,(uint64_t)(uintptr_t)&original11,(uint64_t)(uintptr_t)&original12,(uint64_t)(uintptr_t)&original13,(uint64_t)(uintptr_t)&original14,(uint64_t)(uintptr_t)&original15};

 const unsigned integers[]={0,1,7,0x80000000u,0xfffffffeu,0xffffffffu};
 const long long ids[]={0,1,-1,0x1234567887654321LL,-0x1234567890LL};
 const float floats[]={0.0f,-0.0f,0.125f,-3.75f,12345.5f,2147483520.0f,-2147483648.0f,
  std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};
 const float responses[]={19.25f,-21.5f,0.75f,-0.125f,1000.5f,-123.75f};
 const long long responseIDs[]={0x1234567887654321LL,0x7654321001234567LL,0x1234567800000000LL,
  -0x1234567890LL,(-0x7fffffffffffffffLL-1),0x0000000080000000LL};
 for(unsigned operation=0;operation<16;++operation){
  unsigned independentReturnWitnesses=0;
  autotest::Coverage coverage("editor_mass_logic_timeline_differential",addresses[operation]);
  for(unsigned n=0;n<720;++n){
   Case c={operation,n%12,integers[(n/12)%6],integers[(n/72)%6],ids[(n/12)%5],ids[(n/60)%5],
    static_cast<int>(integers[(n/24)%6]),static_cast<int>(integers[(n/36)%6]),
    static_cast<int>(integers[(n/72)%6]),static_cast<int>(integers[(n/48)%6]),
    ((n/12)%2)!=0,((n/24)%2)!=0,floats[(n/12)%9],integers[(n/120)%6],responses[(n/120)%6],responseIDs[(n/120)%6]};
   autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
   int result=coverage.observe(host,a,b);
   if(result){host->log("    editor logic operation %u case %u pair %d status %d/%d bytes %lu/%lu\n",operation,n,result,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}
   if(c.mode==0&&operation>=9&&operation<=13)++independentReturnWitnesses;
  }
  coverage.report(host);
  if(coverage.completed!=720||coverage.different||coverage.missing||
     independentReturnWitnesses!=((operation>=9&&operation<=13)?60u:0u))return 1;
  if(independentReturnWitnesses)host->log("    editor timeline operation %u independent-return live witnesses %u\n",operation,independentReturnWitnesses);
 }
 return 0;
}
