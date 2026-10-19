#include <cstring>
#include <string>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "SkillEffectAndAffixes.h"
#include "Skill.h"
#include "Character.h"
#include "Effect.h"
#include "Affix.h"
#include "Level.h"
#undef protected
#undef private
TL_ORIGINAL(bool,afOldCan,(CSkillEffectAndAffixes*,CBaseUnit*,CCharacter*),"_ZN22CSkillEffectAndAffixes35canAffixesAndEffectsBeAppliedToUnitEP9CBaseUnitP10CCharacter")
extern "C" bool afNewCan(CSkillEffectAndAffixes*,CBaseUnit*,CCharacter*) __asm__("_ZN22CSkillEffectAndAffixes35canAffixesAndEffectsBeAppliedToUnitEP9CBaseUnitP10CCharacter");
TL_ORIGINAL(bool,afOldApply,(CSkillEffectAndAffixes*,CBaseUnit*,CCharacter*,const Ogre::Vector3*,bool),"_ZN22CSkillEffectAndAffixes22applyAffixesAndEffectsEP9CBaseUnitP10CCharacterPKN4Ogre7Vector3Eb")
extern "C" bool afNewApply(CSkillEffectAndAffixes*,CBaseUnit*,CCharacter*,const Ogre::Vector3*,bool) __asm__("_ZN22CSkillEffectAndAffixes22applyAffixesAndEffectsEP9CBaseUnitP10CCharacterPKN4Ogre7Vector3Eb");
TL_FUNCTION(afISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(afAlign,"_ZN10CCharacter9alignmentEv")
TL_FUNCTION(afEnemy,"_ZN10CCharacter7isEnemyEPS_")
TL_FUNCTION(afCreate,"_ZN16CResourceManager17getNewAffixByNameERKSbIwSt11char_traitsIwESaIwEEj")
TL_FUNCTION(afSkill,"_ZN6CAffix13setSkillOwnerEP6CSkill")
TL_FUNCTION(afLevel,"_ZN6CAffix8setLevelEj")
TL_FUNCTION(afDirection,"_ZN6CAffix12setDirectionEPKN4Ogre7Vector3E")
TL_FUNCTION(afAdd,"_ZN9CBaseUnit8addAffixEP6CAffixjPS_f")
TL_FUNCTION(afDuration,"_ZN6CAffix17effectHasDurationE12EEFFECT_TYPE")
TL_FUNCTION(afListen,"_ZN6CLevel17addListenerToUnitEP9CBaseUnitP13iUnitObserver")
TL_FUNCTION(afEffectSkill,"_ZN7CEffect13setSkillOwnerEP6CSkill")
TL_FUNCTION(afEffectOwner,"_ZN7CEffect8setOwnerEP9CBaseUnitb")
extern "C" void*afCharacterTable[] __asm__("_ZTV10CCharacter");
namespace {
using namespace smallmass;
unsigned seed;CSkillEffectAndAffixes*self;CCharacter*characters[2];CBaseUnit*unit;CCharacter*source;CResourceManager*resources;CLevel*level;CSkill*skill;CEffect*effects[6];CAffix*affixes[3];unsigned created;
int id(const void*p){if(!p)return -1;if(p==self)return 0;if(p==resources)return 1;if(p==level)return 2;if(p==skill)return 3;for(unsigned i=0;i<2;++i)if(p==characters[i])return 10+i;for(unsigned i=0;i<6;++i)if(p==effects[i])return 20+i;for(unsigned i=0;i<3;++i)if(p==affixes[i])return 30+i;return -2;}
void event(unsigned e,const void*p){number(e);number(id(p));}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){event(1,p);number(t);return (seed/3+int(t))%7!=0;}
EAlignment align(CCharacter*p){event(2,p);return static_cast<EAlignment>((seed/7+(p==characters[0]?0:1))%(seed&16?2:1));}
bool enemy(CCharacter*p,CCharacter*q){event(3,p);number(id(q));return seed&32;}
bool valid(CBaseUnit*p,CCharacter*q,CBaseUnit*t,CEffect*e){event(4,p);number(id(q));number(id(t));number(id(e));return (seed+id(e))%5!=0;}
bool apply(CBaseUnit*p,CCharacter*q,CBaseUnit*t,CEffect*e){event(5,p);number(id(q));number(id(t));number(id(e));vector(e->m_direction);if(seed&512){e->m_fValue24=1.5f;e->m_eType=static_cast<EEFFECT_TYPE>(7);}return(seed+id(e))%3!=0;}
CAffix*create(CResourceManager*p,const std::wstring&name,unsigned levelValue){event(6,p);text(name);number(levelValue);CAffix*a=affixes[created++%3];return seed%11==0?NULL:a;}
void affixSkill(CAffix*p,CSkill*s){event(7,p);number(id(s));}
void affixLevel(CAffix*p,unsigned n){event(8,p);number(n);}
void direction(CAffix*p,const Ogre::Vector3*v){event(9,p);number(v!=NULL);if(v)vector(*v);}
CAffix*add(CBaseUnit*p,CAffix*a,unsigned n,CBaseUnit*s,float scale){event(10,p);number(id(a));number(n);number(id(s));floating(scale);floating(a->m_fDuration);return a;}
bool hasDuration(CAffix*p,EEFFECT_TYPE t){event(11,p);number(t);return(seed/13+int(t)+id(p))%5==0;}
bool listen(CLevel*p,CBaseUnit*u,iUnitObserver*o){event(12,p);number(id(u));number(o==static_cast<iUnitObserver*>(skill));return false;}
void effectSkill(CEffect*p,CSkill*s){event(13,p);number(id(s));}
void effectOwner(CEffect*p,CBaseUnit*u,bool recalc){event(14,p);number(id(u));number(recalc);}
void affixSide(Case&c,bool ours,autotest::Capture&out){output=&out;seed=c.index<512?c.index:(c.index*40503u+1234u)&65535u;created=0;self=static_cast<CSkillEffectAndAffixes*>(object(sizeof(CSkillEffectAndAffixes)));new(&self->m_affixData)TArrayList<CSkillEffectAndAffixes::CSkillAffixData*>(2);new(&self->m_effectData)TArrayList<CSkillEffectAndAffixes::CSkillEffectData*>(2);resources=static_cast<CResourceManager*>(object(sizeof(CResourceManager)));level=static_cast<CLevel*>(object(sizeof(CLevel)));resources->m_pLevel=level;skill=static_cast<CSkill*>(object(sizeof(CSkill)));self->m_pSkill=seed&64?skill:NULL;void*vt[150];std::memcpy(vt,afCharacterTable,sizeof(vt));vt[2+0x238/8]=reinterpret_cast<void*>(&valid);vt[2+0x240/8]=reinterpret_cast<void*>(&apply);
 for(unsigned i=0;i<2;++i){characters[i]=static_cast<CCharacter*>(object(sizeof(CCharacter)));*reinterpret_cast<void***>(characters[i])=vt+2;characters[i]->m_pResourceManager=resources;characters[i]->m_pMaster=seed&4?characters[0]:NULL;}characters[0]->m_pMaster=seed&4?characters[1]:NULL;unit=characters[0];unit->m_eBaseUnitType=static_cast<EBASEUNIT_TYPE>(seed&1?0:1);if(seed&128)unit->m_pResourceManager=NULL;source=seed&2?characters[1]:characters[0];if(c.op==0&&seed%17==0)source=NULL;if(source==unit)unit->m_pResourceManager=resources;
 for(unsigned i=0;i<6;++i){effects[i]=static_cast<CEffect*>(object(sizeof(CEffect)));effects[i]->m_direction=Ogre::Vector3(-1,2,-3);effects[i]->m_fValue24=(seed+i)%3==0?0:1.25f;int types[]={0x34,7,0x7c,9};effects[i]->m_eType=static_cast<EEFFECT_TYPE>(types[(seed+i)%4]);}
 for(unsigned i=0;i<3;++i){affixes[i]=static_cast<CAffix*>(object(sizeof(CAffix)));affixes[i]->m_fDuration=-2.5f;affixes[i]->m_bHasDuration=(seed+i)&1;CSkillEffectAndAffixes::CSkillAffixData*a=static_cast<CSkillEffectAndAffixes::CSkillAffixData*>(object(sizeof(*a)));new(&a->m_name)std::wstring(i?L"AFFIX Ж":L"AFFIX");a->m_value18=seed%7;a->m_unitType=(seed/11+i)%4;a->m_targetType=(seed/7+i)%6-1;a->m_durationOverride=seed%19==0?bits(0x7fc00000):1.75f;if(i<seed/3%4)self->m_affixData.add(a);CSkillEffectAndAffixes::CSkillEffectData*e=static_cast<CSkillEffectAndAffixes::CSkillEffectData*>(object(sizeof(*e)));new(&e->m_effects)TArrayList<CEffect*>(2);for(unsigned j=0;j<(seed/13+i)%3;++j)e->m_effects.add(effects[i*2+j]);e->m_value30=(seed/17+i)%4;e->m_value34=(seed/5+i)%6-1;if(i<seed/19%4)self->m_effectData.add(e);}
 if(c.op==0 && c.index==2048){seed=0;source=NULL;unit->m_eBaseUnitType=static_cast<EBASEUNIT_TYPE>(1);self->m_effectData.clear();self->m_affixData.clear();CSkillEffectAndAffixes::CSkillAffixData*a=static_cast<CSkillEffectAndAffixes::CSkillAffixData*>(object(sizeof(*a)));a->m_unitType=1;a->m_targetType=1;self->m_affixData.add(a);}
 bool result;if(c.op==0){typedef bool(*Fn)(CSkillEffectAndAffixes*,CBaseUnit*,CCharacter*);Fn fn=ours?afNewCan:afOldCan;if(!autotest::beginInvocation(out,fn))return;result=fn(self,unit,source);}else{Ogre::Vector3 v(1.25f,-2.5f,3.75f);typedef bool(*Fn)(CSkillEffectAndAffixes*,CBaseUnit*,CCharacter*,const Ogre::Vector3*,bool);Fn fn=ours?afNewApply:afOldApply;if(!autotest::beginInvocation(out,fn))return;result=fn(self,seed%23==0?NULL:unit,source,seed&8?&v:NULL,seed&256);}out.callCompleted=1;number(result);number(created);for(unsigned i=0;i<6;++i){vector(effects[i]->m_direction);floating(effects[i]->m_fValue24);number(effects[i]->m_eType);}for(unsigned i=0;i<3;++i)floating(affixes[i]->m_fDuration);
}
int run(const tlhybrid_host*h,unsigned op,const char*name,unsigned a){detour::Set p;TL_REDIRECT(p,afISA,&isa);TL_REDIRECT(p,afAlign,&align);TL_REDIRECT(p,afEnemy,&enemy);TL_REDIRECT(p,afCreate,&create);TL_REDIRECT(p,afSkill,&affixSkill);TL_REDIRECT(p,afLevel,&affixLevel);TL_REDIRECT(p,afDirection,&direction);TL_REDIRECT(p,afAdd,&add);TL_REDIRECT(p,afDuration,&hasDuration);TL_REDIRECT(p,afListen,&listen);TL_REDIRECT(p,afEffectSkill,&effectSkill);TL_REDIRECT(p,afEffectOwner,&effectOwner);if(p.failed())return 1;return smallmass::run(h,op,name,a,&affixSide,op?2048:2049);}
}
TL_TEST(complete_skill_affixes_can){return run(host,0,"complete_skill_affixes_can",0xcabbc0);}
TL_TEST(complete_skill_affixes_apply){return run(host,1,"complete_skill_affixes_apply",0xcac040);}
