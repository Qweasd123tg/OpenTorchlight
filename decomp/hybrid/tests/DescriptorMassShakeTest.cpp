#include <cstring>
#include <map>
#include <string>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(std::wstring,massShakeOld,(void*,void*,unsigned,void*),"_ZN22CCameraShakeDescriptor28getCameraShakeNameStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massShakeNew(void*,void*,unsigned,void*) __asm__("_ZN22CCameraShakeDescriptor28getCameraShakeNameStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_FUNCTION(massShakeSingleton,"_ZN13CGraphManager12getSingletonEv")
namespace {
struct Case{unsigned layout,index;};void* manager;unsigned calls;
void* singleton(){++calls;return manager;}
void side(Case& c,bool ours,autotest::Capture& out){
 uint64_t state[32]={0},graphs[5][16];std::memset(graphs,0,sizeof(graphs));manager=state;calls=0;
 std::map<std::wstring,void*>* map=new(reinterpret_cast<char*>(state)+0x48)std::map<std::wstring,void*>;
 const wchar_t* keys[]={L"A_OTHER",L"B_CAMERASHAKES_ONE",L"C_CAMERASHAKE",L"D_camerashakes",L"E_CAMERASHAKES_TWO"};const wchar_t* names[]={L"other",L"first",L"singular",L"lower",L"second"};
 for(unsigned i=0;i<5;++i){new(reinterpret_cast<char*>(graphs[i])+0x30)std::wstring(c.layout==3&&i==1?L"":names[i]);if(c.layout!=0&&(c.layout!=1||i==0))(*map)[keys[i]]=graphs[i];}
 detour::Set d;TL_REDIRECT(d,massShakeSingleton,&singleton);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef std::wstring(*Fn)(void*,void*,unsigned,void*);Fn fn=ours?massShakeNew:massShakeOld;if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(0,0,c.index,0);out.callCompleted=1;out.addText(result);out.add(&calls,4);if(calls!=1)out.issue=autotest::Capture::InvalidReport;
 std::wstring expected;if(c.layout>=2){if(c.index==1)expected=L"second";else if(c.index==0)expected=c.layout==3?L"":L"first";else expected=c.layout==3?L"second":L"first";}if(result!=expected)out.issue=autotest::Capture::InvalidReport;
 for(unsigned i=0;i<5;++i)reinterpret_cast<std::wstring*>(reinterpret_cast<char*>(graphs[i])+0x30)->~basic_string();map->~map();
}
void before(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}void after(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(mass_descriptor_5b11e0){autotest::Coverage cov("mass_descriptor_5b11e0",reinterpret_cast<uintptr_t>(&massShakeOld));const unsigned indices[]={0,1,2,3,8,0xffffffffu};for(unsigned layout=0;layout<4;++layout)for(unsigned i=0;i<6;++i){Case c={layout,indices[i]};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log(" massshake layout%u index%u exits%d/%d issue%u/%u\n",layout,c.index,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);cov.report(host);return 1;}}cov.report(host);return cov.completed==24?0:1;}
