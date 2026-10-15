#include <string>
#include <cstring>
#include "AutoTest.h"
TL_ORIGINAL(unsigned int, original0, (void*, void*, const std::wstring&, void*), "_ZN23CRandomChoiceDescriptor23GetChoiceTypeIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" unsigned int candidate0(void*, void*, const std::wstring&, void*) __asm__("_ZN23CRandomChoiceDescriptor23GetChoiceTypeIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_ORIGINAL(unsigned int, original1, (void*, void*, const std::wstring&, void*), "_ZN30CParticleTechWrapperDescriptor34GetBillboardRotationTypeIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" unsigned int candidate1(void*, void*, const std::wstring&, void*) __asm__("_ZN30CParticleTechWrapperDescriptor34GetBillboardRotationTypeIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_ORIGINAL(unsigned int, original2, (void*, void*, const std::wstring&, void*), "_ZN22CRandomGroupDescriptor23getDifficultyIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" unsigned int candidate2(void*, void*, const std::wstring&, void*) __asm__("_ZN22CRandomGroupDescriptor23getDifficultyIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_ORIGINAL(unsigned int, original3, (void*, void*, const std::wstring&, void*), "_ZN22CInteractiveDescriptor18GetGroupIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" unsigned int candidate3(void*, void*, const std::wstring&, void*) __asm__("_ZN22CInteractiveDescriptor18GetGroupIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
namespace {
struct Case{unsigned op,seed;std::wstring value;};
void side(Case& c,bool ours,autotest::Capture& out){
 unsigned int (*fn)(void*,void*,const std::wstring&,void*)=0;
 switch(c.op){case 0:fn=ours?candidate0:original0;break;case 1:fn=ours?candidate1:original1;break;case 2:fn=ours?candidate2:original2;break;default:fn=ours?candidate3:original3;}
 const std::wstring before=c.value;if(!autotest::beginInvocation(out,fn))return;
 unsigned int result=fn(reinterpret_cast<void*>(0x10203040u+c.seed),reinterpret_cast<void*>(0x50607080u+c.seed),c.value,reinterpret_cast<void*>(0x90abcdefu+c.seed));out.callCompleted=1;out.add(&result,sizeof(result));if(c.value!=before)out.issue=autotest::Capture::InvalidReport;
 unsigned int expected=0;
 if(c.op==0&&c.value==L"RANDOM")expected=1;
 if(c.op==1&&c.value==L"Texture")expected=1;
 if(c.op==2){expected=14;if(c.value==L"EASY")expected=0;else if(c.value==L"NORMAL")expected=1;else if(c.value==L"HARD")expected=2;else if(c.value==L"VERY HARD")expected=3;}
 if(c.op==3&&c.value==L"ITEMS")expected=1;
 if(result!=expected)out.issue=autotest::Capture::InvalidReport;
 unsigned long size=c.value.size();out.add(&size,sizeof(size));out.add(c.value.data(),c.value.size()*sizeof(wchar_t));
}
void before(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}void after(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address){autotest::Coverage cov(name,address);const wchar_t* values[]={L"",L"WEIGHT",L"RANDOM",L"Geometry",L"Texture",L"EASY",L"NORMAL",L"HARD",L"VERY HARD",L"ITEMS",L"items",L"UNKNOWN",L"RANDOM ",L"texture",L"very hard",L"MONSTERS",L"PLAYERS",L"GEOMETRY",L"WEIGH",L"NORMALX",L"Абя"};for(unsigned i=0;i<24;++i){Case c;c.op=operation;c.seed=i;if(i<21)c.value=values[i];else if(i==21)c.value.assign(256,L'X');else if(i==22)c.value=std::wstring(L"RANDOM\0X",8);else c.value=std::wstring(L"ITEMS\0X",7);autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log("    string converter %u case %u exit %d/%d issue %u/%u\n",operation,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);cov.report(host);return 1;}}cov.report(host);return cov.completed==24?0:1;}
}
TL_TEST(followup_random_choice_id) {return run(host,0,"followup_random_choice_id",reinterpret_cast<uintptr_t>(&original0));}
TL_TEST(followup_billboard_rotation_id) {return run(host,1,"followup_billboard_rotation_id",reinterpret_cast<uintptr_t>(&original1));}
TL_TEST(followup_random_difficulty_id) {return run(host,2,"followup_random_difficulty_id",reinterpret_cast<uintptr_t>(&original2));}
TL_TEST(followup_interactive_group_id) {return run(host,3,"followup_interactive_group_id",reinterpret_cast<uintptr_t>(&original3));}
