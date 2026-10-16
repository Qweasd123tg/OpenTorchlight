#include <cstring>
#include <string>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(std::wstring,massPathOldName,(void*,void*,unsigned,void*),"_ZN18CMonsterDescriptor17getPathStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
TL_ORIGINAL(unsigned,massPathOldID,(void*,void*,const std::wstring&,void*),"_ZN18CMonsterDescriptor17getPathIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" std::wstring massPathNewName(void*,void*,unsigned,void*) __asm__("_ZN18CMonsterDescriptor17getPathStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
extern "C" unsigned massPathNewID(void*,void*,const std::wstring&,void*) __asm__("_ZN18CMonsterDescriptor17getPathIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_FUNCTION(massPathsQuery,"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEE")
namespace {
struct PathCase{unsigned operation,count,capacity,index,missing;const wchar_t* text;};
struct List{void** data;unsigned count,capacity,grow;};
List* paths;void* expectedScene;autotest::Capture* capture;unsigned calls;bool missing;
void* query(void* scene,const std::wstring& name){if(scene!=expectedScene||name!=L"Pathing")capture->issue=autotest::Capture::InvalidReport;capture->addText(name);++calls;return missing?0:paths;}
void side(PathCase& c,bool ours,autotest::Capture& out){
 uint64_t scene[4]={0},objects[3][64];std::memset(objects,0,sizeof(objects));void* pointers[3];const wchar_t* names[]={L"Alpha",L"Beta",L"Alpha"};for(unsigned i=0;i<3;++i){new(reinterpret_cast<char*>(objects[i])+0x188)std::wstring(names[i]);pointers[i]=objects[i];}
 List list={pointers,c.count,c.capacity,2};paths=&list;expectedScene=scene;capture=&out;calls=0;missing=c.missing;
 detour::Set redirect;TL_REDIRECT(redirect,massPathsQuery,&query);if(redirect.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 std::wstring text(c.text);if(c.operation==0){typedef std::wstring(*Fn)(void*,void*,unsigned,void*);Fn fn=ours?massPathNewName:massPathOldName;if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(scene,0,c.index,0);out.callCompleted=1;out.addText(result);}
 else{typedef unsigned(*Fn)(void*,void*,const std::wstring&,void*);Fn fn=ours?massPathNewID:massPathOldID;if(!autotest::beginInvocation(out,fn))return;unsigned result=fn(scene,0,text,0);out.callCompleted=1;out.add(&result,4);}
 const bool shouldCall=c.operation? !text.empty():c.index!=0;if(calls!=(shouldCall?1u:0u))out.issue=autotest::Capture::InvalidReport;out.add(&calls,4);
 for(unsigned i=0;i<3;++i){std::wstring* name=reinterpret_cast<std::wstring*>(reinterpret_cast<char*>(objects[i])+0x188);if(*name!=names[i])out.issue=autotest::Capture::InvalidReport;name->~basic_string();}
}
void before(void* p,autotest::Capture& c){side(*static_cast<PathCase*>(p),false,c);}void after(void* p,autotest::Capture& c){side(*static_cast<PathCase*>(p),true,c);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address){autotest::Coverage cov(name,address);const unsigned indices[]={0,1,2,3,4,0xffffffffu};const wchar_t* texts[]={L"",L"Alpha",L"Beta",L"alpha",L"missing",L"Alpha "};for(unsigned layout=0;layout<6;++layout)for(unsigned i=0;i<6;++i){PathCase c={operation,layout==4?3u:layout%4,layout==4?1u:3u,indices[i],layout==5,texts[i]};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log(" masspath op%u layout%u i%u exits%d/%d issues%u/%u\n",operation,layout,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);cov.report(host);return 1;}}cov.report(host);return cov.completed==36?0:1;}
}
TL_TEST(mass_descriptor_617830){return run(host,0,"mass_descriptor_617830",reinterpret_cast<uintptr_t>(&massPathOldName));}
TL_TEST(mass_descriptor_617970){return run(host,1,"mass_descriptor_617970",reinterpret_cast<uintptr_t>(&massPathOldID));}
