#include <cstring>
#include <map>
#include <string>
#include <new>
#include "SmallMassCompare.h"
#define private public
#define protected public
#include "SkillController.h"
#include "SkillManager.h"
#include "Skill.h"
#include "GameClient.h"
#undef protected
#undef private
#define DECL(ret,old,now,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret now args __asm__(sym);
DECL(void,fcOldUpdate,fcNewUpdate,(CSkillController*,float),"_ZN16CSkillController6updateEf")
DECL(void,fcOldDestroy,fcNewDestroy,(CSkillController*),"_ZN16CSkillControllerD1Ev")
#undef DECL
TL_FUNCTION(fcConfigure,"_ZN16CSkillController13configureUnitEv")
TL_FUNCTION(fcLearn,"_ZN16CSkillController10learnSkillEv")
TL_FUNCTION(fcUnlearn,"_ZN16CSkillController12unlearnSkillEv")
TL_FUNCTION(fcTarget,"_ZN16CSkillController14getSkillTargetEv")
TL_FUNCTION(fcName,"_ZN6CSkill7getNameEv")
TL_FUNCTION(fcUpdating,"_ZN13CSkillManager24getSkillIsUpdatingByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(fcStop,"_ZN13CSkillManager16stopSkillsByNameESbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(fcGet,"_ZN13CSkillManager8getSkillERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(fcGetLevel,"_ZN13CSkillManager8getSkillERKSbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(fcSetLevel,"_ZN13CSkillManager13setSkillLevelEP6CSkillj")
TL_FUNCTION(fcCast,"_ZN10CCharacter9castSkillEx")
TL_FUNCTION(fcSetTarget,"_ZN10CCharacter9setTargetEPS_")
TL_FUNCTION(fcAttempt,"_ZN10CCharacter24attemptStopOfActiveSkillEv")
TL_FUNCTION(fcPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(fcExecute,"_ZN13CSkillManager12executeSkillERKSbIwSt11char_traitsIwESaIwEEP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS9_10QuaternionESC_S7_i")
TL_FUNCTION(fcRemoveSafe,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(fcBaseDestroy,"_ZN19CPositionableObjectD2Ev")
namespace {
using namespace smallmass;
CSkillController*self;CCharacter*units[2];CSkillManager*manager;CSkill*skills[4];unsigned seed,calls;std::wstring skillName;
int id(const void*p){if(!p)return -1;if(p==self)return 0;if(p==manager)return 1;for(unsigned i=0;i<2;++i)if(p==units[i])return 10+i;for(unsigned i=0;i<4;++i)if(p==skills[i])return 20+i;return 99;}
void ev(unsigned k,const void*p){number(k);number(id(p));++calls;}
bool configure(CSkillController*p){ev(1,p);if(seed&256&&p->m_pRunicCore)p->m_pRunicCore=units[1];return seed&1;}
void learn(CSkillController*p){ev(2,p);}
void unlearn(CSkillController*p){ev(3,p);}
CCharacter*target(CSkillController*p){ev(4,p);return seed&32?units[1]:NULL;}
const std::wstring&name(CSkill*p){ev(5,p);return skillName;}
bool updating(CSkillManager*p,const std::wstring&s){ev(6,p);text(s);return seed&16;}
void stop(CSkillManager*p,std::wstring s,bool force){ev(7,p);text(s);number(force);}
CSkill*get(CSkillManager*p,const std::wstring&s){ev(8,p);text(s);return seed&128?NULL:skills[0];}
CSkill*getLevel(CSkillManager*p,const std::wstring&s,int level){ev(9,p);text(s);number(level);return skills[1];}
void setLevel(CSkillManager*p,CSkill*s,unsigned level){ev(10,p);number(id(s));number(level);s->m_skillLevel=level;}
bool cast(CCharacter*p,long long index){ev(11,p);output->add(&index,8);return seed&1;}
void setTarget(CCharacter*p,CCharacter*t){ev(12,p);number(id(t));}
bool attempt(CCharacter*p){ev(13,p);return false;}
Ogre::Vector3 position(void*p,bool absolute){ev(14,p);number(absolute);return Ogre::Vector3(float(id(p)),2,-3);}
Ogre::Quaternion orientation(void*p){ev(15,p);return Ogre::Quaternion(1,0.25f,0.5f,-0.75f);}
CSkill*executeSkill(CSkillManager*p,const std::wstring&s,CBaseUnit*u,ESKILL_ACTIVATION_TYPE activation,const Ogre::Vector3&v,const Ogre::Quaternion&q,const Ogre::Vector3&t,CBaseUnit*target,int level){ev(16,p);text(s);number(id(u));number(activation);vector(v);output->add(&q,sizeof(q));vector(t);number(id(target));number(level);return skills[2];}
void broadcast(CSkillController*p,unsigned event){ev(17,p);number(event);}
void removeSafe(void*p,void*reference,unsigned index){ev(18,p);number(static_cast<char*>(reference)-reinterpret_cast<char*>(self));number(index);}
void baseDestroy(void*p){ev(19,p);number(self->m_bSkillStartRequested);number(id(self->m_pRunicCore));number(self->m_iRunicCoreSafePointerId);number(id(self->m_pSecondaryRunicCore));number(self->m_iSecondaryRunicCoreSafePointerId);number(self->m_pUnitInteractDataGroup!=NULL);}
bool install(detour::Set&p){TL_REDIRECT(p,fcConfigure,&configure);TL_REDIRECT(p,fcLearn,&learn);TL_REDIRECT(p,fcUnlearn,&unlearn);TL_REDIRECT(p,fcName,&name);TL_REDIRECT(p,fcUpdating,&updating);TL_REDIRECT(p,fcStop,&stop);TL_REDIRECT(p,fcGet,&get);TL_REDIRECT(p,fcGetLevel,&getLevel);TL_REDIRECT(p,fcSetLevel,&setLevel);TL_REDIRECT(p,fcCast,&cast);TL_REDIRECT(p,fcSetTarget,&setTarget);TL_REDIRECT(p,fcAttempt,&attempt);TL_REDIRECT(p,fcPosition,&position);TL_REDIRECT(p,fcExecute,&executeSkill);TL_REDIRECT(p,fcRemoveSafe,&removeSafe);TL_REDIRECT(p,fcBaseDestroy,&baseDestroy);return !p.failed();}
void execute(Case&c,bool ours,autotest::Capture&out)
{
 input=&c;output=&out;autotest::g_arenaUsed=0;seed=c.index;calls=0;
 self=static_cast<CSkillController*>(object(sizeof(CSkillController)));manager=static_cast<CSkillManager*>(object(sizeof(CSkillManager)));for(unsigned i=0;i<2;++i)units[i]=static_cast<CCharacter*>(object(sizeof(CCharacter)));for(unsigned i=0;i<4;++i)skills[i]=static_cast<CSkill*>(object(sizeof(CSkill)));
 void**vt=static_cast<void**>(object(8*sizeof(void*)));vt[6]=reinterpret_cast<void*>(&broadcast);field<void*>(self,0)=vt;void**unitVT=static_cast<void**>(object(35*sizeof(void*)));unitVT[0xf0/8]=reinterpret_cast<void*>(&orientation);
 for(unsigned i=0;i<2;++i){field<void*>(units[i],0)=unitVT;units[i]->m_eBaseUnitType=static_cast<EBASEUNIT_TYPE>((seed/8+i)%2);units[i]->m_pSkillManager=seed%11?manager:NULL;units[i]->m_activeSkill=seed&128?NULL:skills[2];}
 CResourceManager*resources=static_cast<CResourceManager*>(object(sizeof(CResourceManager)));CGameClient*client=static_cast<CGameClient*>(object(sizeof(CGameClient)));CGameClient**clients=static_cast<CGameClient**>(object(sizeof(void*)));clients[0]=client;resources->m_GameClients.m_pData=clients;resources->m_GameClients.m_nCount=1;resources->m_GameClients.m_nCapacity=1;client->m_pPlayer=seed&32?reinterpret_cast<CPlayer*>(units[1]):NULL;self->m_pResourceManager=resources;for(unsigned i=0;i<2;++i)units[i]->m_targetCharacter.m_pObject=seed&32?units[1]:NULL;
 skillName=seed&64?L"different":L"synthetic Skill";
 new(&self->m_sCategory)std::wstring(seed&1?L"category":L"");new(&self->m_sUnitInteractWith)std::wstring(seed&2?L"unit":L"");new(&self->m_sSkillName)std::wstring(seed%13?L"synthetic Skill":L"");self->m_pRunicCore=seed%7?units[0]:NULL;self->m_iRunicCoreSafePointerId=17;self->m_pSecondaryRunicCore=seed&4?units[1]:NULL;self->m_iSecondaryRunicCoreSafePointerId=29;self->m_pUnitInteractDataGroup=reinterpret_cast<CDataGroup*>(manager);self->m_bLearnSkillOnStart=seed&4;self->m_bUnlearnSkillOnStop=seed&8;self->m_bSkillStartRequested=seed&2;self->m_bSkillStopRequested=seed&4;self->m_bForceStop=seed&32;self->m_bUsePlayerAsTarget=seed&64;self->m_bUseUnitTarget=seed&16;self->m_iSkillLevel=int(seed/16%5)-1;
 CSkill**data=static_cast<CSkill**>(object(4*sizeof(void*)));for(unsigned i=0;i<4;++i)data[i]=skills[(i+seed)%4];list(manager,0x60,data,seed%5,4);
 if(c.op==0){void(*fn)(CSkillController*,float)=ours?fcNewUpdate:fcOldUpdate;autotest::invoke(out,fn,self,float(seed)/10);text(self->m_sCategory);text(self->m_sUnitInteractWith);text(self->m_sSkillName);self->m_sSkillName.~basic_string();self->m_sUnitInteractWith.~basic_string();self->m_sCategory.~basic_string();}
 else{void(*fn)(CSkillController*)=ours?fcNewDestroy:fcOldDestroy;autotest::invoke(out,fn,self);}
 number(calls);out.add(reinterpret_cast<char*>(self)+0x100,0x120-0x100);out.add(reinterpret_cast<char*>(self)+0x138,0x154-0x138);for(unsigned i=0;i<4;++i)number(skills[i]->m_skillLevel);
}
int run(const tlhybrid_host*host,unsigned op,const char*name,uintptr_t address,unsigned count){detour::Set patches;if(!install(patches))return 1;return smallmass::run(host,op,name,address,execute,count);}
}
TL_TEST(finish_skill_controller_update){return run(host,0,"finish_skill_controller_update",(uintptr_t)&fcOldUpdate,1024);}
TL_TEST(finish_skill_controller_destructor){return run(host,1,"finish_skill_controller_destructor",(uintptr_t)&fcOldDestroy,64);}
