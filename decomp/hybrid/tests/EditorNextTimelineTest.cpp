// Actual original/replacement pairs, including both object lookups and every
// interpolation name. Real original RTTI; only direct collaborators are spied.
#include <cstring>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
extern "C" void* editorGlobal __asm__("gEditor");
extern "C" void* timelineTable[] __asm__("_ZTV9CTimeline");
extern "C" void* groupTable[] __asm__("_ZTV11CLogicGroup");
extern "C" void* baseTable[] __asm__("_ZTV17CEditorBaseObject");
static const std::wstring* const interpNames = reinterpret_cast<const std::wstring*>(0x1462000UL);
extern wchar_t editorString[] __asm__("sEditorString");
TL_ORIGINAL(void,original0,(long long,long long,int,int,void*),"_Z35EditorTimelineSetPropertyPointValuexxiiPv")
extern "C" void candidate0(long long,long long,int,int,void*) __asm__("_Z35EditorTimelineSetPropertyPointValuexxiiPv");
TL_ORIGINAL(void,original1,(long long,long long,int,int,int,void*),"_Z40EditorTimelineSetPropertyPointValueArrayxxiiiP14UNIONDATA32BIT")
extern "C" void candidate1(long long,long long,int,int,int,void*) __asm__("_Z40EditorTimelineSetPropertyPointValueArrayxxiiiP14UNIONDATA32BIT");
TL_ORIGINAL(void,original2,(long long,long long,int,bool),"_Z25EditorTimelineAddPropertyxxib")
extern "C" void candidate2(long long,long long,int,bool) __asm__("_Z25EditorTimelineAddPropertyxxib");
TL_ORIGINAL(wchar_t*,original3,(long long,long long,int),"_Z35EditorTimelineGetPropertyInterpTypexxi")
extern "C" wchar_t* candidate3(long long,long long,int) __asm__("_Z35EditorTimelineGetPropertyInterpTypexxi");
TL_ORIGINAL(void,original4,(long long,long long,int,const wchar_t*),"_Z35EditorTimelineSetPropertyInterpTypexxiPKw")
extern "C" void candidate4(long long,long long,int,const wchar_t*) __asm__("_Z35EditorTimelineSetPropertyInterpTypexxiPKw");
TL_ORIGINAL(unsigned,original5,(long long,unsigned,unsigned,unsigned,unsigned),"_Z21EditorCreateLogicLinkxjjjj")
extern "C" unsigned candidate5(long long,unsigned,unsigned,unsigned,unsigned) __asm__("_Z21EditorCreateLogicLinkxjjjj");
TL_ORIGINAL(unsigned,original6,(unsigned,unsigned,wchar_t*,bool),"_Z20EditorGetLogicFuncIdjjPwb")
extern "C" unsigned candidate6(unsigned,unsigned,wchar_t*,bool) __asm__("_Z20EditorGetLogicFuncIdjjPwb");
TL_FUNCTION(target_lookup,"_Z16GetObjectInScenex")
TL_FUNCTION(target_value,"_ZN9CTimeline21SetPropertyPointValueExiiPvj")
TL_FUNCTION(target_add,"_ZN9CTimeline11AddPropertyEP12CEditorScenexib")
TL_FUNCTION(target_getInterp,"_ZN9CTimeline33GetPropertyPointInterpolationTypeExi")
TL_FUNCTION(target_setInterp,"_ZN9CTimeline33SetPropertyPointInterpolationTypeExi22ETIMELINE_INTERP_TYPES")
TL_FUNCTION(target_logic,"_ZN11CLogicGroup21GetLogicObjectByIndexEj")
TL_FUNCTION(target_link,"_ZN12CLogicObject12AddLogicLinkEjPS_j")
TL_FUNCTION(target_scene,"_ZN7CEditor14GetEditorSceneEj")
TL_FUNCTION(target_descriptor,"_ZN18CDescriptorManager13GetDescriptorEj")
TL_FUNCTION(target_inputID,"_ZN11CDescriptor25GetInputLogicWrapperIndexESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_outputID,"_ZN11CDescriptor26GetOutputLogicWrapperIndexESbIwSt11char_traitsIwESaIwEE")

namespace {
struct Case{unsigned op,mode,variant,index,second,output,input;long long id,object;int property,point,count;bool flag;};
const Case* in;autotest::Capture* out;void* objects[6];void* editor2;unsigned lookups,logicCalls;
unsigned identity(void*p){if(!p)return 0;for(unsigned i=0;i<6;++i)if(objects[i]==p)return i+1;return 999;}
void num(unsigned n){out->add(&n,4);}void ptr(void*p){num(identity(p));}
void at(void*p,unsigned offset,void*v){std::memcpy(static_cast<char*>(p)+offset,&v,8);}
void event(unsigned n,void*p){num(n);ptr(p);}
void* lookup(long long id){num(1);out->add(&id,8);++lookups;if(in->mode==9)editorGlobal=editor2;
 if((lookups==1&&in->mode==3)||(lookups==2&&in->mode==5))return NULL;return objects[lookups==1?0:1];}
void value(void*p,long long id,int property,int point,void*data,unsigned count){event(2,p);out->add(&id,8);out->add(&property,4);out->add(&point,4);num(count);out->add(data,16);}
void add(void*p,void*scene,long long id,int property,bool flag){event(3,p);ptr(scene);out->add(&id,8);out->add(&property,4);num(flag);}
std::wstring getInterp(void*p,long long id,int property){event(4,p);out->add(&id,8);out->add(&property,4);return in->variant==9?std::wstring(1050,L'Z'):interpNames[in->variant%8];}
void setInterp(void*p,long long id,int property,int type){event(5,p);out->add(&id,8);out->add(&property,4);out->add(&type,4);}
void* logic(void*p,unsigned index){event(6,p);num(index);++logicCalls;return (in->mode==6&&logicCalls==1)||(in->mode==7&&logicCalls==2)?NULL:objects[logicCalls==1?3:4];}
unsigned link(void*p,unsigned a,void*q,unsigned b){event(7,p);num(a);ptr(q);num(b);return in->variant*0x17231u+0x80000000u;}
void* scene(void*p,unsigned index){num(8);num(p==editor2);num(index);return in->mode==3?NULL:objects[2];}
void* descriptor(void*p,unsigned index){event(9,p);num(index);return in->mode==5?NULL:objects[5];}
unsigned wrapper(unsigned n,void*p,std::wstring name){event(n,p);num(name.size());out->add(name.c_str(),name.size()*4);return in->variant*0x1825u+0x80000000u;}
unsigned inputID(void*p,std::wstring name){return wrapper(10,p,name);}unsigned outputID(void*p,std::wstring name){return wrapper(11,p,name);}
void side(Case&c,bool ours,autotest::Capture&capture){
 in=&c;out=&capture;lookups=logicCalls=0;
 unsigned long long editor[2][64]={{0}},storage[6][80]={{0}};unsigned data[4]={c.index,c.second,c.output,c.input};
 for(unsigned i=0;i<6;++i)objects[i]=storage[i];editor2=editor[1];editorGlobal=editor[0];
 reinterpret_cast<char*>(editor[0])[0x49]=c.mode==1;reinterpret_cast<char*>(editor[1])[0x49]=1;
 at(editor[0],0x58,c.mode==2?NULL:editor2);at(objects[0],0,(c.mode==4?baseTable:c.op==5?groupTable:timelineTable)+2);
 at(objects[1],0,baseTable+2);at(objects[1],0x48,c.mode==8?NULL:objects[2]);at(objects[2],0x100,c.mode==4?NULL:objects[5]);
 std::wstring text=c.variant<8?interpNames[c.variant]:c.variant==8?L"UNKNOWN":c.variant==9?L"":L"linear";
 for(unsigned i=0;i<1000;++i)editorString[i]=static_cast<wchar_t>(0x100+i);
 detour::Set patches;
 TL_REDIRECT(patches,target_lookup,&lookup);
 TL_REDIRECT(patches,target_value,&value);
 TL_REDIRECT(patches,target_add,&add);
 TL_REDIRECT(patches,target_getInterp,&getInterp);
 TL_REDIRECT(patches,target_setInterp,&setInterp);
 TL_REDIRECT(patches,target_logic,&logic);
 TL_REDIRECT(patches,target_link,&link);
 TL_REDIRECT(patches,target_scene,&scene);
 TL_REDIRECT(patches,target_descriptor,&descriptor);
 TL_REDIRECT(patches,target_inputID,&inputID);
 TL_REDIRECT(patches,target_outputID,&outputID);
 if(patches.failed())_exit(41);
 switch(c.op){
 case 0:autotest::invoke(capture,ours?candidate0:original0,c.id,c.object,c.property,c.point,data);break;
 case 1:autotest::invoke(capture,ours?candidate1:original1,c.id,c.object,c.property,c.point,c.count,data);break;
 case 2:autotest::invoke(capture,ours?candidate2:original2,c.id,c.object,c.property,c.flag);break;
 case 3:{wchar_t*(*fn)(long long,long long,int)=ours?candidate3:original3;if(!autotest::beginInvocation(capture,fn))return;wchar_t*r=fn(c.id,c.object,c.property);capture.callCompleted=1;num(r==editorString);break;}
 case 4:autotest::invoke(capture,ours?candidate4:original4,c.id,c.object,c.property,text.c_str());break;
 case 5:autotest::invoke(capture,ours?candidate5:original5,c.id,c.index,c.second,c.output,c.input);break;
 case 6:autotest::invoke(capture,ours?candidate6:original6,c.index,c.second,c.mode==10?NULL:const_cast<wchar_t*>(text.c_str()),c.flag);break;

 }
 num(lookups);num(logicCalls);num(editorGlobal==editor2);capture.add(editorString,4000);capture.add(storage,sizeof(storage));patches.restore();
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(editor_next_timeline_differential){
 const uint64_t addresses[]={(uint64_t)(uintptr_t)&original0,(uint64_t)(uintptr_t)&original1,(uint64_t)(uintptr_t)&original2,(uint64_t)(uintptr_t)&original3,(uint64_t)(uintptr_t)&original4,(uint64_t)(uintptr_t)&original5,(uint64_t)(uintptr_t)&original6};
 const unsigned values[]={0,1,7,0x80000000u,0xfffffffeu,0xffffffffu};
 const long long ids[]={0,1,-1,0x1234567887654321LL,-0x123456789LL};
 for(unsigned op=0;op<7;++op){autotest::Coverage coverage("editor_next_timeline_differential",addresses[op]);
  for(unsigned n=0;n<660;++n){unsigned v=(n/11)%12;Case c={op,n%11,v%11,values[v%6],values[(v/2)%6],values[(n/33)%6],values[(n/55)%6],ids[(n/11)%5],ids[(n/55)%5],static_cast<int>(values[(n/22)%6]),static_cast<int>(values[(n/33)%6]),static_cast<int>(values[(n/44)%6]),((n/11)&1)!=0};
   autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int result=coverage.observe(host,a,b);
   if(result){host->log("    editor next op %u case %u pair %d status %d/%d bytes %lu/%lu\n",op,n,result,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}
  }coverage.report(host);
 }return 0;
}
