#include <cstring>
#include <map>
#include <string>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(std::wstring,massAnimResourceOld,(void*,void*,unsigned,void*),"_ZN26CAnimationPlayerDescriptor21GetResourceStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massAnimResourceNew(void*,void*,unsigned,void*) __asm__("_ZN26CAnimationPlayerDescriptor21GetResourceStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
extern "C" void* massAnimResourceTable[] __asm__("_ZTV16CAnimationPlayer");
extern "C" void* massAnimResourceBase[] __asm__("_ZTV17CEditorBaseObject");
TL_FUNCTION(massAnimResourceMaster,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(massAnimResourceGroup,"_ZN17CUnitResourceList14getGroupByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(massAnimResourceValue,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(massAnimResourceSingleton,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(massAnimResourceTypeName,"_ZN10CHierarchy11getTypeNameEj")
namespace {
struct Case{unsigned kind,category,count,index;};struct List{unsigned* data;unsigned count,capacity,grow;};
struct State{uint64_t master[24],hierarchy[20];unsigned char resources,units;std::wstring names[3];std::map<long long,void*> map;autotest::Capture* capture;unsigned calls;};State* state;
void invalid(){state->capture->issue=autotest::Capture::InvalidReport;}void event(unsigned n){state->capture->add(&n,4);++state->calls;}
void* master(void* p){if(p!=&state->resources)invalid();event(1);return &state->units;}
void* group(void* p,const std::wstring& text){if(p!=&state->units||(text!=L"MONSTERS"&&text!=L"PROPS"))invalid();event(2);state->capture->addText(text);return &state->map;}
const std::wstring& value(void* p,const std::wstring& key,const std::wstring& fallback){event(3);state->capture->addText(key);state->capture->addText(fallback);if(key!=L"NAME"||!fallback.empty())invalid();for(unsigned i=0;i<3;++i)if(p==&state->names[i]){state->capture->add(&i,4);return state->names[i];}invalid();return state->names[0];}
void* singleton(){event(4);return state->master;}
std::wstring typeName(void* p,unsigned type){if(p!=state->hierarchy)invalid();event(5);state->capture->add(&type,4);return type==7?L"first":type==19?L"second":L"unknown";}
void side(Case& c,bool ours,autotest::Capture& out){State s;state=&s;s.capture=&out;s.calls=0;std::memset(s.master,0,sizeof(s.master));std::memset(s.hierarchy,0,sizeof(s.hierarchy));unsigned types[]={7,19,31};List list={types,c.count,3,10};std::memcpy(reinterpret_cast<char*>(s.hierarchy)+0x70,&list,sizeof(list));void* tree=s.hierarchy;std::memcpy(reinterpret_cast<char*>(s.master)+0x80,&tree,8);const wchar_t* names[]={L"Alpha",L"Beta",L"Omega"};for(unsigned i=0;i<c.count;++i){s.names[i]=names[i];s.map[static_cast<long long>(i)*7-3]=&s.names[i];}
 uint64_t receiver[32]={0};*reinterpret_cast<void**>(receiver)=c.kind==1?static_cast<void*>(massAnimResourceBase+2):static_cast<void*>(massAnimResourceTable+2);void* resources=&s.resources;std::memcpy(reinterpret_cast<char*>(receiver)+0x58,&resources,8);const wchar_t* categories[]={L"PLAYER",L"MONSTERS",L"UNITTYPE",L"PROP",L"UNKNOWN"};std::wstring* category=new(reinterpret_cast<char*>(receiver)+0x80)std::wstring(categories[c.category]);
 detour::Set d;TL_REDIRECT(d,massAnimResourceMaster,&master);TL_REDIRECT(d,massAnimResourceGroup,&group);TL_REDIRECT(d,massAnimResourceValue,&value);TL_REDIRECT(d,massAnimResourceSingleton,&singleton);TL_REDIRECT(d,massAnimResourceTypeName,&typeName);if(d.failed()){invalid();return;}typedef std::wstring(*Fn)(void*,void*,unsigned,void*);Fn fn=ours?massAnimResourceNew:massAnimResourceOld;if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(0,c.kind==0?0:receiver,c.index,0);out.callCompleted=1;out.addText(result);out.add(&s.calls,4);if(*category!=categories[c.category])invalid();if(c.kind==2&&(c.category==1||c.category==2||c.category==3)&&s.calls==0)invalid();category->~basic_string();}
void before(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void after(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(mass_descriptor_da6e20){autotest::Coverage cov("mass_descriptor_da6e20",reinterpret_cast<uintptr_t>(&massAnimResourceOld));const unsigned indices[]={0,1,2,3,0xffffffffu};for(unsigned kind=0;kind<3;++kind)for(unsigned category=0;category<5;++category)for(unsigned count=0;count<4;count+=count==0?1:2)for(unsigned i=0;i<5;++i){if(kind<2&&(count!=0||category!=0))continue;Case c={kind,category,count,indices[i]};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log(" massanimresource kind%u cat%u count%u index%u exits%d/%d issues%u/%u\n",kind,category,count,c.index,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);cov.report(host);return 1;}}cov.report(host);return 0;}
