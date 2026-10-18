#include <cstring>
#include <map>
#include <string>
#include <vector>
#include "ParentPairs.h"
#include "Detour.h"
#define private public
#define protected public
#include "Skill.h"
#include "SkillEffectAndAffixes.h"
#include "EffectManager.h"
#include "Effect.h"
#include "Affix.h"
#include "BaseUnit.h"
#include "MasterResourceManager.h"
#undef protected
#undef private
#define DECL(ret,old,now,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret now args __asm__(sym);
DECL(CEffect*,dfAddOld,dfAddNew,(CEffectManager*,CEffect*),"_ZN14CEffectManager12addNewEffectEP7CEffect")
DECL(bool,dfRemoveOld,dfRemoveNew,(CSkillEffectAndAffixes*,CBaseUnit*,CCharacter*),"_ZN22CSkillEffectAndAffixes23removeAffixesAndEffectsEP9CBaseUnitP10CCharacter")
DECL(std::wstring,dfStatsOld,dfStatsNew,(CSkillEffectAndAffixes*),"_ZN22CSkillEffectAndAffixes15getDisplayStatsEv")
#undef DECL
TL_FUNCTION(dfOwner,"_ZN7CEffect8setOwnerEP9CBaseUnitb")
TL_FUNCTION(dfClear,"_ZN14CEffectManager20clearOutDescriptionsEv")
TL_FUNCTION(dfDelAffix,"_ZN14CEffectManager11deleteAffixERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(dfDelEffect,"_ZN14CEffectManager12removeEffectERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(dfCreate,"_ZN22CSkillEffectAndAffixes23createAffixesForDisplayEP16CResourceManager")
TL_FUNCTION(dfAffixStats,"_ZN6CAffix15getDisplayStatsEj")
TL_FUNCTION(dfEffectStats,"_ZN7CEffect15getDisplayStatsEjb")
TL_FUNCTION(dfMaster,"_ZN22CMasterResourceManager12getSingletonEv")
namespace {
autotest::Capture*cap;unsigned seed;CEffectManager*manager;CEffect* effects[7];CAffix*affixes[3];CBaseUnit*unit;CSkillEffectAndAffixes*properties;CResourceManager*resource;
void n(unsigned v){cap->add(&v,4);}int id(void*p){if(!p)return -1;for(unsigned i=0;i<7;++i)if(p==effects[i])return i;for(unsigned i=0;i<3;++i)if(p==affixes[i])return 20+i;return p==manager?30:p==unit?31:p==properties?32:p==resource?33:99;}void ptr(void*p){int v=id(p);cap->add(&v,4);}
void owner(CEffect*e,CBaseUnit*u,bool recalc){n(1);ptr(e);ptr(u);n(recalc);e->m_Owner.setObject(u);}
void clear(CEffectManager*m){n(2);ptr(m);m->m_EffectString2E0=L"";m->m_EffectString2E8=L"";m->m_EffectString2F0=L"";}
bool delAffix(CEffectManager*m,const std::wstring&s){n(3);ptr(m);cap->addText(s);return (seed+s.size())%3==0;}
bool delEffect(CEffectManager*m,const std::wstring&s,bool b){n(4);ptr(m);cap->addText(s);n(b);return (seed+s.size())%4==0;}
void create(CSkillEffectAndAffixes*p,CResourceManager*r){n(5);ptr(p);ptr(r);if(seed%2&&p->m_displayAffixes.size()==0)p->m_displayAffixes.add(affixes[0]);}
std::wstring text(unsigned i){const wchar_t*texts[]={L"",L"Fire +1",L"ЖЁЛТЫЙ",L"\n",L"-0.5%"};return texts[(i+seed)%5];}
std::wstring affixStats(CAffix*a,unsigned level){n(6);ptr(a);n(level);return text(id(a));}
std::wstring effectStats(CEffect*e,unsigned level,bool b){n(7);ptr(e);n(level);n(b);return text(id(e));}
CMasterResourceManager* master(){n(8);return NULL;}
void side(void*raw,autotest::Capture&out,bool ours,unsigned mode){seed=static_cast<parentpairs::Case*>(raw)->seed;cap=&out;CRunicCore ownerCore;unit=reinterpret_cast<CBaseUnit*>(&ownerCore);uint64_t units[(sizeof(CBaseUnit)+7)/8],resources[8],ss[(sizeof(CSkill)+7)/8],es[7][(sizeof(CEffect)+7)/8],as[3][(sizeof(CAffix)+7)/8];std::memset(units,0,sizeof(units));std::memset(ss,0,sizeof(ss));std::memset(es,0,sizeof(es));resource=reinterpret_cast<CResourceManager*>(resources);
 manager=new CEffectManager(NULL);manager->m_Owner.setObject(seed%2?unit:NULL);manager->m_EffectString2E0=L"alpha";manager->m_EffectString2E8=L"beta";manager->m_EffectString2F0=L"gamma";
 const unsigned bits[]={0xc4610000,0xc47a0000,0,0x3f800000,0x40000000,0x7f800000,0x7fc00001,0x80000000};
 for(unsigned i=0;i<7;++i){effects[i]=reinterpret_cast<CEffect*>(es[i]);new(effects[i])CRunicCore;new(&effects[i]->m_sName)std::wstring(i<3?L"shared":i<5?L"other":L"");new(&effects[i]->m_Owner)TSafePointer<CBaseUnit>();effects[i]->m_eType=static_cast<EEFFECT_TYPE>((seed+i)%3);effects[i]->m_activation=static_cast<EEFFECT_ACTIVATION>((seed+i)%3);effects[i]->m_flag31=seed%2;effects[i]->m_bDead=(seed+i)%4==0;std::memcpy(&effects[i]->m_fValue24,&bits[(seed+i)%8],4);std::memcpy(&effects[i]->m_fRemainingDuration,&bits[(seed/2+i+2)%8],4);}
 if(mode==0){
  // Cross the same-name/type replacement condition explicitly. Independent
  // duration and remaining values cover both sentinels, NaN and live/dead rows.
  effects[6]->m_sName=L"shared";
  effects[6]->m_eType=static_cast<EEFFECT_TYPE>(seed%3);
  effects[6]->m_flag31=(seed/64)%2;
  for(unsigned i=0;i<3;++i){
   effects[i]->m_eType=effects[6]->m_eType;
   effects[i]->m_bDead=(seed/16+i)%2;
   std::memcpy(&effects[i]->m_fValue24,&bits[seed%8],4);
   std::memcpy(&effects[i]->m_fRemainingDuration,&bits[(seed/8+i)%8],4);
  }
 }
 if(seed%3==0)effects[6]->m_Owner.setObject(unit);for(unsigned i=0;i<(mode==0?6:seed%7);++i)manager->m_Effects[(seed+i)%3].add(effects[i]);for(unsigned i=0;i<3;++i)affixes[i]=reinterpret_cast<CAffix*>(as[i]);
 uint64_t ps[(sizeof(CSkillEffectAndAffixes)+7)/8];std::memset(ps,0,sizeof(ps));properties=reinterpret_cast<CSkillEffectAndAffixes*>(ps);new(properties)CRunicCore;new(&properties->m_affixData)TArrayList<CSkillEffectAndAffixes::CSkillAffixData*>(1);new(&properties->m_effectData)TArrayList<CSkillEffectAndAffixes::CSkillEffectData*>(1);new(&properties->m_displayAffixes)TArrayList<CAffix*>(1);new(&properties->m_affixNames)TArrayList<std::wstring>(1);new(&properties->m_effectNames)TArrayList<std::wstring>(1);new(&properties->m_name)std::wstring(seed%3?L"Skill":L"");CSkill*skill=reinterpret_cast<CSkill*>(ss);skill->m_resources=resource;properties->m_pSkill=seed%7?skill:NULL;
 for(unsigned i=0;i<seed%4;++i){properties->m_displayAffixes.add(affixes[i]);properties->m_affixNames.add(text(i));properties->m_effectNames.add(text(i+1));}
 CSkillEffectAndAffixes::CSkillEffectData data[3];for(unsigned i=0;i<3;++i){for(unsigned j=0;j<(seed+i)%3;++j)data[i].m_effects.add(effects[i*2+j]);if(i<seed%4)properties->m_effectData.add(i==1&&seed%5==0?NULL:&data[i]);}
 CBaseUnit*borrowed=reinterpret_cast<CBaseUnit*>(units);borrowed->m_pEffectManager=seed%3?manager:NULL;
 detour::Set patches;TL_REDIRECT(patches,dfOwner,&owner);TL_REDIRECT(patches,dfClear,&clear);TL_REDIRECT(patches,dfDelAffix,&delAffix);TL_REDIRECT(patches,dfDelEffect,&delEffect);TL_REDIRECT(patches,dfCreate,&create);TL_REDIRECT(patches,dfAffixStats,&affixStats);TL_REDIRECT(patches,dfEffectStats,&effectStats);TL_REDIRECT(patches,dfMaster,&master);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(mode==0){typedef CEffect*(*Fn)(CEffectManager*,CEffect*);Fn f=ours?dfAddNew:dfAddOld;if(!autotest::beginInvocation(out,f))return;ptr(f(manager,effects[6]));out.callCompleted=1;for(unsigned i=0;i<7;++i){out.add(&effects[i]->m_fRemainingDuration,4);n(effects[i]->m_bDead);ptr(effects[i]->m_Owner.getObject());}for(unsigned a=0;a<3;++a){TArrayList<CEffect*>&l=manager->m_Effects[a];n(l.size());n(l.m_nCapacity);for(unsigned i=0;i<l.size();++i)ptr(l[i]);}out.addText(manager->m_EffectString2E0);out.addText(manager->m_EffectString2E8);out.addText(manager->m_EffectString2F0);}
 if(mode==1){typedef bool(*Fn)(CSkillEffectAndAffixes*,CBaseUnit*,CCharacter*);Fn f=ours?dfRemoveNew:dfRemoveOld;if(!autotest::beginInvocation(out,f))return;n(f(properties,seed%5?borrowed:NULL,NULL));out.callCompleted=1;}
 if(mode==2){typedef std::wstring(*Fn)(CSkillEffectAndAffixes*);Fn f=ours?dfStatsNew:dfStatsOld;if(!autotest::beginInvocation(out,f))return;std::wstring s=f(properties);out.callCompleted=1;out.addText(s);n(properties->m_displayAffixes.size());}
 for(unsigned a=0;a<3;++a)manager->m_Effects[a].clear();delete manager;for(unsigned i=0;i<7;++i){effects[i]->m_Owner.~TSafePointer();effects[i]->m_sName.~basic_string();effects[i]->CRunicCore::~CRunicCore();}
 properties->m_affixData.~TArrayList();properties->m_effectData.~TArrayList();properties->m_displayAffixes.~TArrayList();properties->m_affixNames.~TArrayList();properties->m_effectNames.~TArrayList();properties->m_name.~basic_string();properties->CRunicCore::~CRunicCore();out.addHeapInUse();}
#define BODY(name,num) void name##a(void*p,autotest::Capture&c){side(p,c,false,num);}void name##b(void*p,autotest::Capture&c){side(p,c,true,num);}
BODY(add,0)BODY(remove,1)BODY(stats,2)
#undef BODY
}
#define TEST(name,old,a,b) TL_TEST(name){return parentpairs::run(host,#name,(uintptr_t)&old,128,a,b);}
TL_TEST(deepen_effect_add){return parentpairs::run(host,"deepen_effect_add",(uintptr_t)&dfAddOld,256,adda,addb);}
TEST(deepen_skill_effect_remove,dfRemoveOld,removea,removeb)
TEST(deepen_skill_effect_stats,dfStatsOld,statsa,statsb)
