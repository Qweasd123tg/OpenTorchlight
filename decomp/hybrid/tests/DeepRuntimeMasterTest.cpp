#include "tests/SmallMassCompare.h"
#include "GameVariables.h"
#include <vector>
#define DECL(ret,id,args,sym) TL_ORIGINAL(ret,id##Old,args,sym) extern "C" ret id##New args __asm__(sym);
DECL(void,deepMasterLoad,(void*),"_ZN22CMasterResourceManager13loadParticlesEv")
DECL(void,deepMasterReload,(void*),"_ZN22CMasterResourceManager15reloadResourcesEv")
DECL(void,deepMasterLocation,(void*,const std::wstring&,const std::string&,bool),"_ZN22CMasterResourceManager19addResourceLocationERKSbIwSt11char_traitsIwESaIwEERKSsb")
TL_FUNCTION(deepMasterCreate,"_ZN22CMasterResourceManager22createParticleReloaderEv")
TL_FUNCTION(deepMasterParticles,"_ZN18CParticlePreloader15ReloadParticlesEv")
TL_FUNCTION(deepMasterGraphs,"_ZN13CGraphManager6reloadEv")
TL_FUNCTION(deepMasterEffects,"_ZN19CEffectGroupManager6reloadEv")
TL_FUNCTION(deepMasterMissiles,"_ZN17CMissilePreloader14reloadMissilesEv")
TL_FUNCTION(deepMasterSkills,"_ZN12CSkillParser12reloadSkillsEv")
TL_FUNCTION(deepMasterSpawns,"_ZN17CSpawnClassParser19reloadFromDirectoryEPKw")
TL_FUNCTION(deepMasterSounds,"_ZN22CMasterResourceManager19reloadSoundBankDataEv")
TL_FUNCTION(deepMasterGraph,"_ZN13CGraphManager8getGraphERKSbIwSt11char_traitsIwESaIwEE")
extern "C" char deepMasterResourceSingleton[] __asm__("_ZN4Ogre20ResourceGroupManager12getSingletonEv");
extern "C" char deepMasterAddLocation[] __asm__("_ZN4Ogre20ResourceGroupManager19addResourceLocationERKSsS2_S2_b");
extern "C" char deepMasterInitGroup[] __asm__("_ZN4Ogre20ResourceGroupManager23initialiseResourceGroupERKSs");
namespace {
using namespace smallmass;unsigned calls;void* token;void* self;void* global;void* alternate;
void record(unsigned n,void* p){event(n,p);++calls;}
void create(void* p){record(1,p);field<void*>(p,0xf8)=token;}
void particles(void* p){record(2,p);}
void graphs(void* p){record(3,p);m_pMasterResourceManager=static_cast<CMasterResourceManager*>(alternate);}
void effects(void* p){record(4,p);}
void missiles(void* p){record(5,p);}
void skills(){number(6);++calls;}
void spawns(void* p,const wchar_t* path){record(7,p);text(std::wstring(path));}
void sounds(void* p){record(8,p);}
void* graph(void* p,const std::wstring& name){record(9,p);text(name);return name==L"EXPERIENCEGATE"?token:alternate;}
void* resourceSingleton(){record(10,token);return token;}
void addLocation(void* p,const std::string& location,const std::string& type,const std::string& group,bool recursive){record(11,p);text(location);text(type);text(group);number(recursive);}
void initGroup(void* p,const std::string& group){record(12,p);text(group);}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;self=object(0x190);global=object(0x190);alternate=object(0x190);token=object(8);void* values[8];for(unsigned i=0;i<8;++i)values[i]=object(8);unsigned fields[]={0x48,0x58,0x60,0x78,0x90,0x98,0xc8,0xf0,0xf8};for(unsigned i=0;i<9;++i){field<void*>(self,fields[i])=values[i%8];field<void*>(global,fields[i])=values[(i+1)%8];field<void*>(alternate,fields[i])=values[(i+3)%8];}
field<void*>(self,0xf0)=c.index&1?token:0;field<void*>(self,0x90)=c.index&2?token:0;field<void*>(self,0x98)=c.index&4?token:0;field<void*>(self,0xc8)=c.index&8?token:0;
CMasterResourceManager* previous=m_pMasterResourceManager;m_pMasterResourceManager=static_cast<CMasterResourceManager*>(c.index&16?global:self);
std::vector<std::string>& locations=*new(static_cast<char*>(self)+0x108)std::vector<std::string>();std::wstring path=c.index&1?L"media/CasePath/Ю":L"";std::string group=c.index&2?"MyGroup":"";if(c.index&4)locations.reserve(9);for(unsigned i=0;i<(c.index/8)%4;++i)locations.push_back(i==1?"MEDIA/CASEPATH/Ю":"OTHER");
detour::Set d;TL_REDIRECT(d,deepMasterCreate,&create);TL_REDIRECT(d,deepMasterParticles,&particles);TL_REDIRECT(d,deepMasterGraphs,&graphs);TL_REDIRECT(d,deepMasterEffects,&effects);TL_REDIRECT(d,deepMasterMissiles,&missiles);TL_REDIRECT(d,deepMasterSkills,&skills);TL_REDIRECT(d,deepMasterSpawns,&spawns);TL_REDIRECT(d,deepMasterSounds,&sounds);TL_REDIRECT(d,deepMasterGraph,&graph);d.redirect(deepMasterResourceSingleton,deepMasterResourceSingleton,&resourceSingleton);d.redirect(deepMasterAddLocation,deepMasterAddLocation,&addLocation);d.redirect(deepMasterInitGroup,deepMasterInitGroup,&initGroup);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
if(c.op==0)autotest::invoke(out,ours?deepMasterLoadNew:deepMasterLoadOld,self);else if(c.op==1)autotest::invoke(out,ours?deepMasterReloadNew:deepMasterReloadOld,self);else {typedef void(*Fn)(void*,const std::wstring&,const std::string&,bool);autotest::invoke<Fn,void*,const std::wstring&,const std::string&,bool>(out,ours?deepMasterLocationNew:deepMasterLocationOld,self,path,group,bool(c.index&16));}
number(calls);pointer(field<void*>(self,0xf8));pointer(field<void*>(self,0x168));pointer(field<void*>(self,0x170));number(locations.size());for(unsigned i=0;i<locations.size();++i)text(locations[i]);locations.~vector();m_pMasterResourceManager=previous;}
}
TL_TEST(deep_runtime_master_particles){return smallmass::run(host,0,"deep_runtime_master_particles",(uintptr_t)deepMasterLoadOld,execute,64);}
TL_TEST(deep_runtime_master_reload){return smallmass::run(host,1,"deep_runtime_master_reload",(uintptr_t)deepMasterReloadOld,execute,64);}
TL_TEST(deep_runtime_master_location){return smallmass::run(host,2,"deep_runtime_master_location",(uintptr_t)deepMasterLocationOld,execute,96);}
