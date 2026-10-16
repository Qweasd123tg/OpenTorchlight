#include <cstring>
#include <string>
#include <vector>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(std::wstring,massAnimationOld0,(void*,void*,unsigned,void*),"_ZN23CGenericModelDescriptor22GetAnimationStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massAnimationNew0(void*,void*,unsigned,void*) __asm__("_ZN23CGenericModelDescriptor22GetAnimationStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_ORIGINAL(std::wstring,massAnimationOld1,(void*,void*,unsigned,void*),"_ZN18CMonsterDescriptor22GetAnimationStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massAnimationNew1(void*,void*,unsigned,void*) __asm__("_ZN18CMonsterDescriptor22GetAnimationStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_ORIGINAL(unsigned,massAnimationOld2,(void*,void*,const std::wstring&,void*),"_ZN18CMonsterDescriptor22GetAnimationIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" unsigned massAnimationNew2(void*,void*,const std::wstring&,void*) __asm__("_ZN18CMonsterDescriptor22GetAnimationIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_FUNCTION(massAnimationModelQuery,"_ZN10CCharacter12getUnitModelEv")
extern "C" void* massAnimationGenericTable[] __asm__("_ZTV13CGenericModel");
extern "C" void* massAnimationMonsterTable[] __asm__("_ZTV8CMonster");
extern "C" void* massAnimationBaseTable[] __asm__("_ZTV17CEditorBaseObject");
namespace {
struct Case{unsigned operation,kind,count,index;const wchar_t* text;};
void* model;void* monster;autotest::Capture* capture;unsigned calls;
void* modelQuery(void* p){if(p!=monster)capture->issue=autotest::Capture::InvalidReport;++calls;return model;}
void side(Case& c,bool ours,autotest::Capture& out){
 uint64_t receiver[256]={0},generic[80]={0},animations[24]={0};monster=receiver;model=c.kind==3?0:generic;capture=&out;calls=0;
 *reinterpret_cast<void**>(receiver)=c.kind==1?static_cast<void*>(massAnimationBaseTable+2):c.operation==0?static_cast<void*>(massAnimationGenericTable+2):static_cast<void*>(massAnimationMonsterTable+2);
 void* set=c.kind==4?0:animations;
 std::memcpy(reinterpret_cast<char*>(c.operation==0?receiver:generic)+0x1e0,&set,8);
 std::vector<std::string>* names=new(reinterpret_cast<char*>(animations)+0x28)std::vector<std::string>;
 const char* texts[]={"IDLE","walk","ATTACK"};for(unsigned i=0;i<c.count;++i)names->push_back(texts[i]);
 detour::Set d;TL_REDIRECT(d,massAnimationModelQuery,&modelQuery);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 void* object=c.kind==0?0:receiver;std::wstring text(c.text);
 if(c.operation<2){typedef std::wstring(*Fn)(void*,void*,unsigned,void*);Fn fn=c.operation==0?(ours?massAnimationNew0:massAnimationOld0):(ours?massAnimationNew1:massAnimationOld1);if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(0,object,c.index,0);out.callCompleted=1;out.addText(result);}
 else{typedef unsigned(*Fn)(void*,void*,const std::wstring&,void*);Fn fn=ours?massAnimationNew2:massAnimationOld2;if(!autotest::beginInvocation(out,fn))return;unsigned result=fn(0,object,text,0);out.callCompleted=1;out.add(&result,4);}
 if(calls!=((c.operation>0&&c.kind>1)?1u:0u))out.issue=autotest::Capture::InvalidReport;out.add(&calls,4);out.addText(text);
 if(names->size()!=c.count)out.issue=autotest::Capture::InvalidReport;for(unsigned i=0;i<c.count;++i)if((*names)[i]!=texts[i])out.issue=autotest::Capture::InvalidReport;names->~vector();
}
void before(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void after(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address){autotest::Coverage cov(name,address);const unsigned indices[]={0,1,2,3,0xffffffffu};const wchar_t* texts[]={L"",L"IDLE",L"walk",L"ATTACK",L"missing"};for(unsigned kind=0;kind<5;++kind)for(unsigned count=0;count<4;count+=count==0?1:2)for(unsigned i=0;i<5;++i){if(operation==0&&kind==3)continue;Case c={operation,kind,count,indices[i],texts[i]};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log(" massanimation op%u kind%u count%u i%u exits%d/%d issues%u/%u\n",operation,kind,count,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);cov.report(host);return 1;}}cov.report(host);return 0;}
}
TL_TEST(mass_descriptor_5da560){return run(host,0,"mass_descriptor_5da560",reinterpret_cast<uintptr_t>(&massAnimationOld0));}
TL_TEST(mass_descriptor_607920){return run(host,1,"mass_descriptor_607920",reinterpret_cast<uintptr_t>(&massAnimationOld1));}
TL_TEST(mass_descriptor_612fd0){return run(host,2,"mass_descriptor_612fd0",reinterpret_cast<uintptr_t>(&massAnimationOld2));}
