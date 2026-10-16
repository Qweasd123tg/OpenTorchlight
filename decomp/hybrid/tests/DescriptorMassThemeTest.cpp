#include <cstring>
#include <string>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(std::wstring,massThemeOldName,(void*,void*,unsigned,void*),"_ZN18CMonsterDescriptor18getThemeStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
TL_ORIGINAL(unsigned,massThemeOldID,(void*,void*,const std::wstring&,void*),"_ZN18CMonsterDescriptor18getThemeIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" std::wstring massThemeNewName(void*,void*,unsigned,void*) __asm__("_ZN18CMonsterDescriptor18getThemeStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
extern "C" unsigned massThemeNewID(void*,void*,const std::wstring&,void*) __asm__("_ZN18CMonsterDescriptor18getThemeIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_FUNCTION(massThemeSingleton,"_ZN11CUnitThemes12getSingletonEv")
namespace {
struct Case{unsigned operation,layout,index;const wchar_t* text;};struct List{void** data;unsigned count,capacity,grow;};void* manager;unsigned calls;
void* singleton(){++calls;return manager;}
void side(Case& c,bool ours,autotest::Capture& out){uint64_t state[8]={0},themes[3][8];std::memset(themes,0,sizeof(themes));void* data[3];const wchar_t* names[]={L"Alpha",L"Beta",L"Alpha"};for(unsigned i=0;i<3;++i){new(reinterpret_cast<char*>(themes[i])+0x28)std::wstring(names[i]);data[i]=themes[i];}List list={data,c.layout==0?0u:c.layout==1?1u:3u,c.layout==3?1u:3u,2};std::memcpy(reinterpret_cast<char*>(state)+0x18,&list,sizeof(list));manager=state;calls=0;detour::Set d;TL_REDIRECT(d,massThemeSingleton,&singleton);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}std::wstring text(c.text);
 if(c.operation==0){typedef std::wstring(*Fn)(void*,void*,unsigned,void*);Fn fn=ours?massThemeNewName:massThemeOldName;if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(0,0,c.index,0);out.callCompleted=1;out.addText(result);std::wstring expected;if(c.index>0&&c.index<=list.count)expected=names[c.index-1<list.capacity?c.index-1:0];if(result!=expected)out.issue=autotest::Capture::InvalidReport;}
 else{typedef unsigned(*Fn)(void*,void*,const std::wstring&,void*);Fn fn=ours?massThemeNewID:massThemeOldID;if(!autotest::beginInvocation(out,fn))return;unsigned result=fn(0,0,text,0);out.callCompleted=1;out.add(&result,4);unsigned expected=0;if(list.count&&text==L"Alpha")expected=1;if(list.count>1&&list.capacity>1&&text==L"Beta")expected=2;if(result!=expected)out.issue=autotest::Capture::InvalidReport;}
 if(calls!=1)out.issue=autotest::Capture::InvalidReport;out.add(&calls,4);out.addText(text);for(unsigned i=0;i<3;++i){std::wstring* name=reinterpret_cast<std::wstring*>(reinterpret_cast<char*>(themes[i])+0x28);if(*name!=names[i])out.issue=autotest::Capture::InvalidReport;name->~basic_string();}}
void before(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void after(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
int run(const tlhybrid_host* host,unsigned operation,const char* test,uintptr_t address){autotest::Coverage cov(test,address);const unsigned indices[]={0,1,2,3,4,0xffffffffu};const wchar_t* texts[]={L"Alpha",L"Beta",L"",L"alpha",L"Alpha ",L"missing"};for(unsigned layout=0;layout<4;++layout)for(unsigned i=0;i<6;++i){Case c={operation,layout,indices[i],texts[i]};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log(" masstheme op%u layout%u index%u exits%d/%d issues%u/%u\n",operation,layout,c.index,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);cov.report(host);return 1;}}cov.report(host);return cov.completed==24?0:1;}
}
TL_TEST(mass_descriptor_6078b0){return run(host,0,"mass_descriptor_6078b0",reinterpret_cast<uintptr_t>(&massThemeOldName));}
TL_TEST(mass_descriptor_612cc0){return run(host,1,"mass_descriptor_612cc0",reinterpret_cast<uintptr_t>(&massThemeOldID));}
