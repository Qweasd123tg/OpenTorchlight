#include <cstring>
#include <map>
#include <string>
#include <stdint.h>
#include "TArrayList.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(unsigned,preloadOld0,(void*),"_ZN18CParticlePreloader21getParticleCacheCountEv")
TL_ORIGINAL(void,preloadOld1,(void*,std::wstring&),"_ZN18CParticlePreloader12getFileNamesERSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(std::wstring,preloadOld2,(void*,const std::wstring&),"_ZN18CParticlePreloader25getParticleNameByFileNameERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,preloadOld3,(void*),"_ZN18CParticlePreloader5cleanEv")
extern "C" unsigned preloadNew0(void*) __asm__("_ZN18CParticlePreloader21getParticleCacheCountEv");
extern "C" void preloadNew1(void*,std::wstring&) __asm__("_ZN18CParticlePreloader12getFileNamesERSbIwSt11char_traitsIwESaIwEE");
extern "C" std::wstring preloadNew2(void*,const std::wstring&) __asm__("_ZN18CParticlePreloader25getParticleNameByFileNameERKSbIwSt11char_traitsIwESaIwEE");
extern "C" void preloadNew3(void*) __asm__("_ZN18CParticlePreloader5cleanEv");
TL_FUNCTION(preloadCleanPathTarget,"_ZN10FILESYSTEM9CleanPathERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(preloadUpperTarget,"_ZN7STRINGS11StringUpperERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(preloadNumberTarget,"_ZN7STRINGS17GetValueAsWStringEi")
TL_FUNCTION(preloadMasterTarget,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(preloadTemplatesTarget,"_ZN16ParticleUniverse21ParticleSystemManager32removeAllParticleSystemTemplatesEv")
namespace {
struct Loader {
 uint64_t table,safe;void* resource;void* settings;
 std::map<std::wstring,TArrayList<std::string>*> scripts;
 std::map<std::wstring,TArrayList<void*>*> caches;
 std::map<std::wstring,std::wstring> names;int property;void* bank;void* layout;
};
struct Case{unsigned operation,index;};struct State{autotest::Capture* out;uint64_t master[64],manager,cache[6][32],layout[8];unsigned index,calls,deleted;};State* active;
void add(unsigned x){active->out->add(&x,4);}void invalid(){active->out->issue=autotest::Capture::InvalidReport;}
void event(unsigned tag,unsigned value){++active->calls;add(tag);add(value);}
const wchar_t* keys[]={L"A",L"PARTICLES/A.PARTICLE",L"OMEGA"};
std::wstring clean(const std::wstring& name){event(1,0);active->out->addText(name);return L"cleaned/path";}
std::wstring upper(const std::wstring& name){event(2,0);active->out->addText(name);if(name!=L"cleaned/path")invalid();return active->index&8?L"ABSENT":keys[(active->index/4)%3];}
std::wstring number(int n){event(3,n);if(n<0||n>3){invalid();return L"bad";}return std::wstring(1,static_cast<wchar_t>(L'0'+n));}
void* master(){event(4,0);return active->master;}
void templates(void* p){if(p!=&active->manager)invalid();event(5,0);}
void destroy(void* p){for(unsigned i=0;i<6;++i)if(p==active->cache[i]){event(6,i);active->deleted|=1u<<i;return;}if(p==active->layout){event(7,0);active->deleted|=64;return;}invalid();}
void side(Case& c,bool ours,autotest::Capture& out){
 State state;std::memset(state.master,0,sizeof(state.master));std::memset(state.cache,0,sizeof(state.cache));std::memset(state.layout,0,sizeof(state.layout));state.out=&out;state.index=c.index;state.calls=state.deleted=0;active=&state;
 void* table[2]={0,reinterpret_cast<void*>(&destroy)};for(unsigned i=0;i<6;++i)*reinterpret_cast<void***>(state.cache[i])=table;*reinterpret_cast<void***>(state.layout)=table;void* manager=&state.manager;std::memcpy(reinterpret_cast<char*>(state.master)+0xf0,&manager,8);
 Loader loader;loader.table=loader.safe=0;loader.resource=c.index&1?&state.manager:0;loader.settings=0;loader.property=23;loader.bank=0;loader.layout=c.index&2?state.layout:0;
 unsigned count=c.index%4;for(unsigned i=0;i<count;++i){loader.names[keys[i]]=i==1?L"":i==2?L"Имя":L"alpha";TArrayList<void*>* caches=new TArrayList<void*>(2);for(unsigned j=0;j<(c.index/4+i)%3;++j)caches->add((c.index&16)&&j==1?0:state.cache[(i*2+j)%6]);loader.caches[keys[i]]=caches;TArrayList<std::string>* scripts=(c.index&32)&&i==1?0:new TArrayList<std::string>(2);if(scripts){scripts->add("one");if(c.index&4)scripts->add("second");}loader.scripts[keys[i]]=scripts;}
 detour::Set d;TL_REDIRECT(d,preloadCleanPathTarget,&clean);TL_REDIRECT(d,preloadUpperTarget,&upper);TL_REDIRECT(d,preloadNumberTarget,&number);TL_REDIRECT(d,preloadMasterTarget,&master);TL_REDIRECT(d,preloadTemplatesTarget,&templates);if(d.failed()){invalid();return;}
 std::wstring text=c.index&4?L"prefix\n":L"",result;
 if(c.operation==0){typedef unsigned(*Fn)(void*);Fn fn=ours?preloadNew0:preloadOld0;if(!autotest::beginInvocation(out,fn))return;add(fn(&loader));}
 else if(c.operation==1){typedef void(*Fn)(void*,std::wstring&);Fn fn=ours?preloadNew1:preloadOld1;if(!autotest::beginInvocation(out,fn))return;fn(&loader,text);}
 else if(c.operation==2){typedef std::wstring(*Fn)(void*,const std::wstring&);Fn fn=ours?preloadNew2:preloadOld2;if(!autotest::beginInvocation(out,fn))return;result=fn(&loader,text);}
 else{typedef void(*Fn)(void*);Fn fn=ours?preloadNew3:preloadOld3;if(!autotest::beginInvocation(out,fn))return;fn(&loader);}
 out.callCompleted=1;out.addText(text);out.addText(result);add(state.calls);add(state.deleted);add(loader.names.size());add(loader.scripts.size());add(loader.caches.size());add(loader.layout!=0);
 for(std::map<std::wstring,TArrayList<void*>*>::iterator it=loader.caches.begin();it!=loader.caches.end();++it){out.addText(it->first);add(it->second->size());delete it->second;}for(std::map<std::wstring,TArrayList<std::string>*>::iterator it=loader.scripts.begin();it!=loader.scripts.end();++it)delete it->second;
}
void before(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}void after(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address){autotest::Coverage cov(name,address);for(unsigned i=0;i<64;++i){Case c={operation,i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log(" preloader operation%u case%u exits%d/%d issues%u/%u\n",operation,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);cov.report(host);return 1;}}cov.report(host);return cov.completed==64?0:1;}
}
TL_TEST(state_preloader_a34e80){return run(host,0,"state_preloader_a34e80",reinterpret_cast<uintptr_t>(&preloadOld0));}
TL_TEST(state_preloader_a37b80){return run(host,1,"state_preloader_a37b80",reinterpret_cast<uintptr_t>(&preloadOld1));}
TL_TEST(state_preloader_a37d70){return run(host,2,"state_preloader_a37d70",reinterpret_cast<uintptr_t>(&preloadOld2));}
TL_TEST(state_preloader_a383a0){return run(host,3,"state_preloader_a383a0",reinterpret_cast<uintptr_t>(&preloadOld3));}
