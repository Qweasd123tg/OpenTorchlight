#include <cstring>
#include <string>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(std::wstring,massHierarchyOldName,(void*,void*,unsigned,void*),"_ZN22CDamageShapeDescriptor21getUnitTypeStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
TL_ORIGINAL(unsigned,massHierarchyOldID,(void*,void*,const std::wstring&,void*),"_ZN22CDamageShapeDescriptor21getUnitTypeIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" std::wstring massHierarchyNewName(void*,void*,unsigned,void*) __asm__("_ZN22CDamageShapeDescriptor21getUnitTypeStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
extern "C" unsigned massHierarchyNewID(void*,void*,const std::wstring&,void*) __asm__("_ZN22CDamageShapeDescriptor21getUnitTypeIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_FUNCTION(massHierarchySingleton,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(massHierarchyName,"_ZN10CHierarchy11getTypeNameEj")
TL_FUNCTION(massHierarchyID,"_ZN10CHierarchy15getTypeIDByNameERKSbIwSt11char_traitsIwESaIwEE")
namespace {
struct Case{unsigned operation,layout,index;const wchar_t* text;};struct List{unsigned* data;unsigned count,capacity,grow;};
void* manager;void* hierarchy;autotest::Capture* capture;
void event(unsigned n){capture->add(&n,4);}void invalid(){capture->issue=autotest::Capture::InvalidReport;}
void* singleton(){event(1);return manager;}
std::wstring name(void* p,unsigned id){if(p!=hierarchy)invalid();event(2);event(id);if(id==0)return L"zero";if(id==7)return L"alpha";if(id==19)return L"beta";return L"unknown";}
unsigned identifier(void* p,const std::wstring& text){if(p!=hierarchy)invalid();event(3);capture->addText(text);if(text==L"alpha")return 7;if(text==L"beta")return 19;if(text==L"last")return 0xffffffffu;return 0;}
void side(Case& c,bool ours,autotest::Capture& out){uint64_t master[24]={0},tree[20]={0};unsigned types[]={7,19,7,0xffffffffu};manager=master;hierarchy=tree;capture=&out;void* pointer=tree;std::memcpy(reinterpret_cast<char*>(master)+0x80,&pointer,8);List list={types,c.layout==0?0u:c.layout==1?1u:4u,c.layout==3?1u:4u,10};std::memcpy(reinterpret_cast<char*>(tree)+0x70,&list,sizeof(list));detour::Set d;TL_REDIRECT(d,massHierarchySingleton,&singleton);TL_REDIRECT(d,massHierarchyName,&name);TL_REDIRECT(d,massHierarchyID,&identifier);if(d.failed()){invalid();return;}std::wstring text(c.text);if(c.operation==0){typedef std::wstring(*Fn)(void*,void*,unsigned,void*);Fn fn=ours?massHierarchyNewName:massHierarchyOldName;if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(0,0,c.index,0);out.callCompleted=1;out.addText(result);}else{typedef unsigned(*Fn)(void*,void*,const std::wstring&,void*);Fn fn=ours?massHierarchyNewID:massHierarchyOldID;if(!autotest::beginInvocation(out,fn))return;unsigned result=fn(0,0,text,0);out.callCompleted=1;out.add(&result,4);}if(types[0]!=7||types[1]!=19||types[2]!=7||types[3]!=0xffffffffu)invalid();out.addText(text);}
void before(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void after(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
int run(const tlhybrid_host* host,unsigned operation,const char* test,uintptr_t address){autotest::Coverage cov(test,address);const unsigned indices[]={0,1,2,3,4,0xffffffffu};const wchar_t* texts[]={L"alpha",L"beta",L"last",L"",L"ALPHA",L"unknown"};for(unsigned layout=0;layout<4;++layout)for(unsigned i=0;i<6;++i){Case c={operation,layout,indices[i],texts[i]};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log(" masshierarchy op%u layout%u i%u exits%d/%d issues%u/%u\n",operation,layout,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);cov.report(host);return 1;}}cov.report(host);return cov.completed==24?0:1;}
}
TL_TEST(mass_descriptor_5bb630){return run(host,0,"mass_descriptor_5bb630",reinterpret_cast<uintptr_t>(&massHierarchyOldName));}
TL_TEST(mass_descriptor_5bb6d0){return run(host,1,"mass_descriptor_5bb6d0",reinterpret_cast<uintptr_t>(&massHierarchyOldID));}
