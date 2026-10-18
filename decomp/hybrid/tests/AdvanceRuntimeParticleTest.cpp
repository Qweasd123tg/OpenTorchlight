#include "SmallMassCompare.h"
#include "TArrayList.h"
#include <map>
TL_ORIGINAL(void,particleOld0,(void*,void*),"_ZN18CParticlePreloaderC1EP17CResourceSettings")
extern "C" void particleNew0(void*,void*) __asm__("_ZN18CParticlePreloaderC1EP17CResourceSettings");
TL_ORIGINAL(void*,particleOld1,(void*,const std::wstring&),"_ZN18CParticlePreloader16getParticleCacheERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void* particleNew1(void*,const std::wstring&) __asm__("_ZN18CParticlePreloader16getParticleCacheERKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void,particleOld2,(void*,void*),"_ZN18CParticlePreloader12LoadParticleEP10CDataGroup")
extern "C" void particleNew2(void*,void*) __asm__("_ZN18CParticlePreloader12LoadParticleEP10CDataGroup");
TL_ORIGINAL(void,particleOld3,(void*),"_ZN18CParticlePreloader15ReloadParticlesEv")
extern "C" void particleNew3(void*) __asm__("_ZN18CParticlePreloader15ReloadParticlesEv");
TL_FUNCTION(particleIndexTarget,"_ZN20CDynamicPropertyFile22GetStringPropertyIndexERKSbIwSt11char_traitsIwESaIwEES3_b")
TL_FUNCTION(particleCreateCacheTarget,"_ZN18CParticlePreloader19createParticleCacheERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(particleValueTarget,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(particleUpperTarget,"_ZN7STRINGS11StringUpperERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(particleCleanPathTarget,"_ZN10FILESYSTEM9CleanPathERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(particleLoadTarget,"_ZN18CParticlePreloader12LoadParticleESbIwSt11char_traitsIwESaIwEES3_")
TL_FUNCTION(particleResourceCtor,"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_FUNCTION(particleSoundCtor,"_ZN10CSoundBankC1ER13CSoundManagerb")
TL_FUNCTION(particleMasterTarget,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(particleCleanTarget,"_ZN18CParticlePreloader5cleanEv")
TL_FUNCTION(particleDataCtor,"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_FUNCTION(particleDataDtor,"_ZN10CDataGroupD1Ev")
TL_FUNCTION(particleLoadFile,"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
TL_FUNCTION(particleStringTarget,"_ZN20CDynamicPropertyFile9GetStringEj")
TL_FUNCTION(particleLoadGroup,"_ZN18CParticlePreloader12LoadParticleEP10CDataGroup")
extern "C" void* particleSingleton __asm__("m_gParticlePreloader");
extern "C" unsigned particleSettingIndex __asm__("_ZL31KRESOURCESETTING_S_PARTICLEFILE");
namespace {
using namespace smallmass;
struct Loader{unsigned long table,safe;void* resource;void* settings;std::map<std::wstring,TArrayList<std::string>*> scripts;std::map<std::wstring,TArrayList<void*>*> caches;std::map<std::wstring,std::wstring> names;unsigned property;void* bank;void* layout;};
Loader* loader;void* token;void* masterObject;void* childGroups[4];void* created[2];unsigned calls,createdCount;std::wstring strings[3];
void record(unsigned tag,void* p){event(tag,p);++calls;}
unsigned index(void* p,const std::wstring& key,std::wstring def,bool flag){record(1,p);text(key);text(def);number(flag);return 31+input->index;}
void* createCache(void* p,const std::wstring& name){record(2,p);text(name);if(createdCount==2){output->issue=autotest::Capture::InvalidReport;return 0;}return created[createdCount++];}
const std::wstring& value(void* p,const std::wstring& key,const std::wstring& fallback){record(3,p);text(key);text(fallback);return key==L"NAME"?strings[0]:strings[1];}
std::wstring upper(const std::wstring& name){record(4,0);text(name);return strings[2];}
std::wstring cleanPath(const std::wstring& name){record(5,0);text(name);return name+L"/CLEAN";}
void load(void* p,std::wstring file,std::wstring name){record(6,p);text(file);text(name);}
void resourceCtor(void* p,void* scene){record(7,p);pointer(scene);}
void soundCtor(void* p,void* manager,bool flag){record(8,p);pointer(manager);number(flag);}
void* master(){record(9,masterObject);return masterObject;}
void clean(void* p){record(10,p);}
void dataCtor(void* p,const std::wstring& n,void* parent,unsigned values,unsigned groups,void* repository){record(11,p);text(n);pointer(parent);number(values);number(groups);pointer(repository);list(p,0x38,childGroups,input->index%5,4);}
void dataDtor(void* p){record(12,p);}
void loadFile(void* p,const std::wstring& file,void* timers){record(13,p);text(file);pointer(timers);}
const std::wstring& getString(void* p,unsigned key){record(14,p);number(key);return strings[1];}
void loadGroup(void* p,void* group){record(15,p);pointer(group);}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=createdCount=0;autotest::g_arenaUsed=0;token=object(0x20);masterObject=object(0x190);field<void*>(masterObject,0x98)=token;for(unsigned i=0;i<4;++i)childGroups[i]=object(0x60);for(unsigned i=0;i<2;++i)created[i]=object(0xe8);strings[0]=c.index&1?L"name/Юникод":L"";strings[1]=c.index&2?L"file/path.particle":L"";strings[2]=c.index&4?L"UPPER/PATH":L"";particleSingleton=c.index&2?token:0;particleSettingIndex=0xdead1234;
 Loader state;state.table=state.safe=0;state.resource=c.index&1?token:0;state.settings=token;state.property=12;state.bank=0;state.layout=0;loader=&state;void* self=c.op==0?object(sizeof(Loader)):&state;
 detour::Set d;TL_REDIRECT(d,particleIndexTarget,&index);TL_REDIRECT(d,particleCreateCacheTarget,&createCache);TL_REDIRECT(d,particleValueTarget,&value);TL_REDIRECT(d,particleUpperTarget,&upper);TL_REDIRECT(d,particleCleanPathTarget,&cleanPath);TL_REDIRECT(d,particleLoadTarget,&load);TL_REDIRECT(d,particleResourceCtor,&resourceCtor);TL_REDIRECT(d,particleSoundCtor,&soundCtor);TL_REDIRECT(d,particleMasterTarget,&master);TL_REDIRECT(d,particleCleanTarget,&clean);TL_REDIRECT(d,particleDataCtor,&dataCtor);TL_REDIRECT(d,particleDataDtor,&dataDtor);TL_REDIRECT(d,particleLoadFile,&loadFile);TL_REDIRECT(d,particleStringTarget,&getString);if(c.op==3)TL_REDIRECT(d,particleLoadGroup,&loadGroup);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.op==0){autotest::invoke(out,ours?particleNew0:particleOld0,self,c.index&1?token:0);Loader* l=static_cast<Loader*>(self);pointer(l->resource);pointer(l->settings);number(l->scripts.size());number(l->caches.size());number(l->names.size());number(l->property);pointer(l->bank);pointer(l->layout);pointer(particleSingleton);number(particleSettingIndex);l->scripts.~map();l->caches.~map();l->names.~map();}
 else if(c.op==1){std::wstring name=c.index&1?L"CACHE":L"ABSENT";if(c.index%7!=0)state.caches[L"CACHE"]=c.index%11==0?0:new TArrayList<void*>(c.index%3+1);TArrayList<void*>* list=state.caches.empty()?0:state.caches.begin()->second;if(list)for(unsigned i=0;i<c.index%4;++i)list->add(childGroups[i]);void* result=0;typedef void*(*Fn)(void*,const std::wstring&);Fn fn=ours?particleNew1:particleOld1;if(!autotest::beginInvocation(out,fn))return;result=fn(self,name);out.callCompleted=1;pointer(result);number(createdCount);if(list){number(list->size());for(unsigned i=0;i<list->size();++i)pointer((*list)[i]);}for(unsigned i=0;i<createdCount;++i)pointer(field<void*>(created[i],0x70));delete list;}
 else if(c.op==2){autotest::invoke(out,ours?particleNew2:particleOld2,self,c.index%7?childGroups[0]:0);}
 else{autotest::invoke(out,ours?particleNew3:particleOld3,self);number(state.resource!=0);number(state.bank!=0);}
 number(calls);
}
}
TL_TEST(advance_runtime_particle_ctor){return smallmass::run(host,0,"advance_runtime_particle_ctor",(uintptr_t)particleOld0,execute,84);}
TL_TEST(advance_runtime_particle_cache){return smallmass::run(host,1,"advance_runtime_particle_cache",(uintptr_t)particleOld1,execute,84);}
TL_TEST(advance_runtime_particle_group){return smallmass::run(host,2,"advance_runtime_particle_group",(uintptr_t)particleOld2,execute,84);}
TL_TEST(advance_runtime_particle_reload){return smallmass::run(host,3,"advance_runtime_particle_reload",(uintptr_t)particleOld3,execute,84);}
