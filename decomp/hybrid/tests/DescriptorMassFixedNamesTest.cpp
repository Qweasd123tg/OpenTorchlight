#include <string>
#include "AutoTest.h"
TL_ORIGINAL(std::wstring,massDifficultyOld,(void*,void*,unsigned,void*),"_ZN22CRandomGroupDescriptor23setDifficultyStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
TL_ORIGINAL(std::wstring,massPathGroupOld,(void*,void*,unsigned,void*),"_ZN25CPathControllerDescriptor18GetGroupStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massDifficultyNew(void*,void*,unsigned,void*) __asm__("_ZN22CRandomGroupDescriptor23setDifficultyStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
extern "C" std::wstring massPathGroupNew(void*,void*,unsigned,void*) __asm__("_ZN25CPathControllerDescriptor18GetGroupStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
namespace {
struct Case{unsigned operation,index,seed;};
void side(Case& c,bool ours,autotest::Capture& out){typedef std::wstring(*Fn)(void*,void*,unsigned,void*);Fn fn=c.operation?(ours?massPathGroupNew:massPathGroupOld):(ours?massDifficultyNew:massDifficultyOld);if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(reinterpret_cast<void*>(0x12340000u+c.seed),reinterpret_cast<void*>(0x56780000u+c.seed),c.index,reinterpret_cast<void*>(0x87650000u+c.seed));out.callCompleted=1;out.addText(result);std::wstring expected;if(c.operation)expected=c.index==0?L"MONSTERS":c.index==2?L"PLAYER":L"ITEMS";else{const wchar_t* names[]={L"EASY",L"NORMAL",L"HARD",L"VERY HARD"};if(c.index<4)expected=names[c.index];}if(result!=expected)out.issue=autotest::Capture::InvalidReport;}
void before(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void after(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
int run(const tlhybrid_host* host,unsigned operation,const char* test,uintptr_t address){autotest::Coverage cov(test,address);const unsigned indices[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,31,63,127,255,0x7fffffffu,0x80000000u,0xfffffffeu,0xffffffffu};for(unsigned i=0;i<24;++i){Case c={operation,indices[i],i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){cov.report(host);return 1;}}cov.report(host);return cov.completed==24?0:1;}
}
TL_TEST(mass_descriptor_62e7b0){return run(host,0,"mass_descriptor_62e7b0",reinterpret_cast<uintptr_t>(&massDifficultyOld));}
TL_TEST(mass_descriptor_619260){return run(host,1,"mass_descriptor_619260",reinterpret_cast<uintptr_t>(&massPathGroupOld));}
