#include <cstring>
#include <map>
#include <string>
#include <typeinfo>
#include "SmallMassCompare.h"
#define private public
#define protected public
#include "Skill.h"
#include "SkillManager.h"
#include "SkillProperty.h"
#include "BaseUnit.h"
#include "Character.h"
#include "Equipment.h"
#include "Level.h"
#include "ResourceManager.h"
#include "StringTranslate.h"
#undef protected
#undef private
#define DECL(ret,old,now,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret now args __asm__(sym);
DECL(unsigned,fsOldRequired,fsNewRequired,(void*),"_ZN6CSkill29getLevelRequiredForInvestmentEv")
DECL(bool,fsOldHas,fsNewHas,(void*,int),"_ZN6CSkill8hasEventE17ESKILL_EVENT_TYPE")
DECL(void*,fsOldMaster,fsNewMaster,(void*),"_ZN6CSkill23getMasterOwnerCharacterEv")
DECL(bool,fsOldRange,fsNewRange,(void*,const Ogre::Vector3&,const Ogre::Vector3&,void*,void*),"_ZN6CSkill12getIsInRangeERKN4Ogre7Vector3ES3_P9CBaseUnitS5_")
DECL(bool,fsOldTarget,fsNewTarget,(void*,void*,void*,const Ogre::Vector3*,bool),"_ZN6CSkill16getTargetIsValidEP10CCharacterS1_PKN4Ogre7Vector3Eb")
DECL(bool,fsOldWeapon,fsNewWeapon,(void*,void*),"_ZN6CSkill21weaponRequirementsMetEP10CCharacter")
DECL(std::wstring,fsOldDescription,fsNewDescription,(void*,void*,unsigned),"_ZN6CSkill24getSkillLevelDescriptionEP9CBaseUnitj")
DECL(std::wstring,fsOldStats,fsNewStats,(void*,void*,unsigned),"_ZN6CSkill18getSkillLevelStatsEP9CBaseUnitj")
DECL(int,fsOldManaOT,fsNewManaOT,(void*,void*,unsigned),"_ZN6CSkill23getSkillLevelManaCostOTEP9CBaseUnitj")
DECL(int,fsOldMana,fsNewMana,(void*,void*,unsigned),"_ZN6CSkill21getSkillLevelManaCostEP9CBaseUnitj")
DECL(int,fsOldCooldown,fsNewCooldown,(void*,void*,unsigned),"_ZN6CSkill21getSkillLevelCooldownEP9CBaseUnitj")
DECL(bool,fsOldCalculate,fsNewCalculate,(void*),"_ZN6CSkill28calculateEffectiveSkillLevelEv")
DECL(void,fsOldSet,fsNewSet,(void*,unsigned),"_ZN6CSkill32_setLevelOfSkillFromSkillManagerEj")
DECL(void,fsOldState,fsNewState,(void*,void*,int),"_ZN6CSkill15unitStateChangeEP9CBaseUnit12EUNIT_STATES")
DECL(void,fsOldDestroy,fsNewDestroy,(void*),"_ZN6CSkillD1Ev")
DECL(std::wstring,fsOldType,fsNewType,(void*),"_ZN6CSkill23getSkillTypeDisplayNameEv")
DECL(void*,fsOldOwner,fsNewOwner,(void*),"_ZN6CSkill17getOwnerCharacterEv")
DECL(bool,fsOldRoll,fsNewRoll,(void*),"_ZN6CSkill15rollSkillChanceEv")
DECL(bool,fsOldRequirements,fsNewRequirements,(void*,void*,int,const Ogre::Vector3*,void*,bool),"_ZN6CSkill15requirementsMetEP9CBaseUnit22ESKILL_ACTIVATION_TYPEPKN4Ogre7Vector3ES1_b")
DECL(bool,fsOldStart,fsNewStart,(void*,void*,int,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&,void*),"_ZN6CSkill10startSkillEP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS3_10QuaternionES6_S1_")
#undef DECL
TL_FUNCTION(fsHP,"_ZN10CCharacter2HPEv")
TL_FUNCTION(fsISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(fsEnemy,"_ZN10CCharacter7isEnemyEPS_")
TL_FUNCTION(fsAlignment,"_ZN10CCharacter9alignmentEv")
TL_FUNCTION(fsRight,"_ZN10CCharacter20getWeaponInRightHandEv")
TL_FUNCTION(fsLeft,"_ZN10CCharacter19getWeaponInLeftHandEv")
TL_FUNCTION(fsAddSafe,"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_FUNCTION(fsRemoveSafe,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(fsDescription,"_ZN14CSkillProperty19getSkillDescriptionEv")
TL_FUNCTION(fsStats,"_ZN14CSkillProperty13getSkillStatsEv")
TL_FUNCTION(fsCooldown,"_ZN14CSkillProperty11getCoolDownEv")
TL_FUNCTION(fsEffect,"_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(fsRemoveListener,"_ZN6CLevel22removeListenerFromUnitEP9CBaseUnitP13iUnitObserver")
TL_FUNCTION(fsRemoveListeners,"_ZN6CLevel23removeListenerFromUnitsEP13iUnitObserver")
TL_FUNCTION(fsHasEffect,"_ZN14CEffectManager18hasEffectFromSkillEPK6CSkill")
TL_FUNCTION(fsPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(fsTrigger,"_ZN6CSkill12triggerEventE17ESKILL_EVENT_TYPERKN4Ogre7Vector3ERKNS1_10QuaternionEP9CBaseUnitPS3_")
TL_FUNCTION(fsCoreDtor,"_ZN10CRunicCoreD2Ev")
TL_FUNCTION(fsTranslateSingleton,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(fsTranslate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(fsRandom,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(fsPassable,"_ZN6CLevel15passableBetweenEN4Ogre7Vector3ERKS1_b")
TL_FUNCTION(fsTheme,"_ZN9CBaseUnit12hasUnitThemeEP10CUnitTheme")
TL_FUNCTION(fsEffectHas,"_ZN14CEffectManager9hasEffectE12EEFFECT_TYPE")
TL_FUNCTION(fsAssign,"_ZN6CSkill21assignSkillAnimationsEP9CBaseUnit")
namespace {
using namespace smallmass;
CSkill*self;CSkillProperty*props[4];CSkillManager*manager;CCharacter*chars[3];CEquipment*weapons[2];CResourceManager*resources;CLevel*level;void* effects;unsigned seed;unsigned calls;unsigned operation;
template<class T>T* make(){return static_cast<T*>(object(sizeof(T)));}
int identity(const void*p){if(!p)return -1;if(p==self)return 0;if(p==manager)return 1;if(p==level)return 2;if(p==resources)return 3;if(p==effects)return 4;if(p==static_cast<iUnitObserver*>(self))return 5;for(unsigned i=0;i<4;++i)if(p==props[i])return 10+i;for(unsigned i=0;i<3;++i)if(p==chars[i])return 20+i;for(unsigned i=0;i<2;++i)if(p==weapons[i])return 30+i;return 99;}
void ev(unsigned k,const void*p){number(k);number(identity(p));++calls;}
void invalid(){output->issue=autotest::Capture::InvalidReport;}
int hp(void*p){ev(1,p);return (int(seed/4)%3-1)*10;}
bool isa(void*p,int type){ev(2,p);number(type);return ((seed/8+type+identity(p))%3)!=0;}
int alignment(void*p){ev(3,p);return seed/32%5;}
bool enemy(void*p,void*other){ev(4,p);number(identity(other));return seed&2;}
void*right(void*p){ev(5,p);return seed&1?weapons[0]:NULL;}
void*left(void*p){ev(6,p);return seed&2?weapons[1]:NULL;}
unsigned addSafe(void*p,void*reference){ev(7,p);number(static_cast<char*>(reference)-reinterpret_cast<char*>(self));return 41+identity(p);}
void removeSafe(void*p,void*reference,unsigned index){ev(8,p);number(static_cast<char*>(reference)-reinterpret_cast<char*>(self));number(index);}
std::wstring description(void*p){ev(9,p);return identity(p)&1?L"branch description":L"";}
std::wstring stats(void*p){ev(10,p);return identity(p)&1?L"stat A\n42":L"stat B";}
float cooldown(void*p){ev(11,p);return (int(seed%7)-2)*0.75f;}
float effect(void*p,int type,int damage){ev(12,p);number(type);number(damage);return (int(seed/4%7)-3)*0.75f;}
float namedEffect(void*p,int type,float v,const std::wstring&s){ev(13,p);number(type);floating(v);text(s);return (int(seed/8%5)-2)*1.25f;}
void removeListener(void*p,void*unit,void*observer){ev(14,p);number(identity(unit));number(identity(observer));}
void removeListeners(void*p,void*observer){ev(15,p);number(identity(observer));}
bool hasEffect(void*p,const void*skill){ev(16,p);number(identity(skill));return seed&8;}
Ogre::Vector3 position(void*p,bool absolute){ev(17,p);number(absolute);return Ogre::Vector3(seed%3,2,-3);}
Ogre::Quaternion orientation(1,0,0,0);
const Ogre::Quaternion& orientationSpy(void*p){ev(18,p);return orientation;}
bool trigger(void*p,int event,const Ogre::Vector3&v,const Ogre::Quaternion&q,void*target,const Ogre::Vector3*targetPosition){ev(19,p);number(event);vector(v);output->add(&q,sizeof(q));number(identity(target));number(targetPosition!=NULL);if(targetPosition)vector(*targetPosition);return true;}
void coreDtor(void*p){ev(20,p);}
void propertyDtor(void*p){ev(21,p);}
void*translator(){number(22);++calls;return resources;}
std::wstring translate(void*p,const wchar_t*label){ev(23,p);std::wstring s(label);text(s);return seed&1?s+L" translated":L"";}
int randomBetween(int a,int b){number(24);number(a);number(b);++calls;if(operation==17&&(seed&0x80))self->m_property=NULL;return seed%103;}
void removeAvoidance(void*p,CLevel&l){ev(25,p);number(identity(&l));}
void addAvoidance(void*p,CLevel&l){ev(26,p);number(identity(&l));}
bool passable(void*p,Ogre::Vector3 a,const Ogre::Vector3&b,bool flag){ev(27,p);vector(a);vector(b);number(flag);return seed&16;}
bool theme(void*p,void*t){ev(28,p);number(identity(t));return seed&64;}
bool effectHas(void*p,int type){ev(29,p);number(type);return seed&128;}
void assign(void*p,void*unit){ev(30,p);number(identity(unit));self->m_animationLength=float(seed%5)*0.25f;}
bool install(detour::Set&patches)
{
 TL_REDIRECT(patches,fsHP,&hp);TL_REDIRECT(patches,fsISA,&isa);TL_REDIRECT(patches,fsEnemy,&enemy);TL_REDIRECT(patches,fsAlignment,&alignment);TL_REDIRECT(patches,fsRight,&right);TL_REDIRECT(patches,fsLeft,&left);TL_REDIRECT(patches,fsAddSafe,&addSafe);TL_REDIRECT(patches,fsRemoveSafe,&removeSafe);TL_REDIRECT(patches,fsDescription,&description);TL_REDIRECT(patches,fsStats,&stats);TL_REDIRECT(patches,fsCooldown,&cooldown);TL_REDIRECT(patches,fsEffect,&effect);TL_REDIRECT(patches,fsRemoveListener,&removeListener);TL_REDIRECT(patches,fsRemoveListeners,&removeListeners);TL_REDIRECT(patches,fsHasEffect,&hasEffect);TL_REDIRECT(patches,fsPosition,&position);TL_REDIRECT(patches,fsTrigger,&trigger);TL_REDIRECT(patches,fsCoreDtor,&coreDtor);TL_REDIRECT(patches,fsTranslateSingleton,&translator);TL_REDIRECT(patches,fsTranslate,&translate);TL_REDIRECT(patches,fsRandom,&randomBetween);TL_REDIRECT(patches,fsPassable,&passable);
 TL_REDIRECT(patches,fsTheme,&theme);TL_REDIRECT(patches,fsEffectHas,&effectHas);TL_REDIRECT(patches,fsAssign,&assign);
 return !patches.failed();

}
void execute(Case&c,bool ours,autotest::Capture&out)
{
 input=&c;output=&out;autotest::g_arenaUsed=0;seed=c.index;operation=c.op;calls=0;
 self=make<CSkill>();manager=make<CSkillManager>();resources=make<CResourceManager>();level=make<CLevel>();effects=object(0x40);
 void**vt=static_cast<void**>(object(130*sizeof(void*)));vt[0]=NULL;vt[1]=const_cast<std::type_info*>(&typeid(CCharacter));vt[2+0x258/8]=reinterpret_cast<void*>(&namedEffect);vt[2+0x268/8]=reinterpret_cast<void*>(&removeAvoidance);vt[2+0x270/8]=reinterpret_cast<void*>(&addAvoidance);
 for(unsigned i=0;i<3;++i){chars[i]=make<CCharacter>();field<void*>(chars[i],0)=vt+2;chars[i]->m_eBaseUnitType=static_cast<EBASEUNIT_TYPE>(i%2);chars[i]->m_pDataGroup=reinterpret_cast<CDataGroup*>(resources);chars[i]->m_pMaster=seed&16?chars[0]:NULL;chars[i]->m_pEffectManager=reinterpret_cast<CEffectManager*>(effects);}
 chars[0]->m_pMaster=seed&32?chars[1]:NULL;
 for(unsigned i=0;i<2;++i)weapons[i]=make<CEquipment>();
 resources->m_pLevel=seed&1?level:NULL;
 self->m_resources=resources;self->m_pOwner=seed%4?chars[seed%3]:NULL;self->m_iOwnerSafePointerId=17;self->m_pSkillManager=seed&2?manager:NULL;manager->m_Owner.m_pObject=seed%3?chars[0]:NULL;
 for(unsigned i=0;i<4;++i){props[i]=make<CSkillProperty>();new(&props[i]->m_sName)std::wstring(i&1?L"Fire Ice":L"SKILL");props[i]->m_iLevelRequired=(seed+i)%4?i*3+2:0;props[i]->m_iManaCost=float(int((seed+i)%13)-5)*0.75f;props[i]->m_iManaCostOverTime=float(int((seed+i)%11)-4)*1.25f;}
 self->m_property=seed%5?props[0]:NULL;self->m_baseProperty=seed&8?props[3]:NULL;
 CSkillProperty**data=static_cast<CSkillProperty**>(object(4*sizeof(void*)));for(unsigned i=0;i<4;++i)data[i]=(seed/4+i)%5?props[i]:NULL;
 self->m_levelPropertyData=data;self->m_iSkillLevelCount=seed%5;self->m_levelPropertyCapacity=seed&4?2:4;self->m_skillLevel=seed/5%7;self->m_iEffectiveSkillLevel=seed/9%6;self->m_iRequiredLevel=seed%13;self->m_skillType=int(seed%6)-1;
 self->m_iTargetAlignment=seed/128%4;self->m_targetsDead=seed&4;self->m_requiresLineOfSight=seed&2;
 props[0]->m_eTargetType=seed/16%12;props[0]->m_eTargetUnitType=seed&8?7:0;props[0]->m_iMinimumRange=float(int(seed/16%5)-1);props[0]->m_fRange=float(seed/32%6);props[0]->m_bDuelWeaponRequired=seed&4;props[0]->m_iRequirementRight=seed/4%4;props[0]->m_iRequirementLeft=seed/16%4;
 CDataGroup**allowed=static_cast<CDataGroup**>(object(3*sizeof(void*)));allowed[0]=reinterpret_cast<CDataGroup*>(level);allowed[1]=reinterpret_cast<CDataGroup*>(resources);allowed[2]=NULL;list(self,0x78,allowed,seed/64%4,seed&2?1:3);
 void**events=static_cast<void**>(object(11*sizeof(void*)));for(unsigned i=0;i<11;++i){void*e=object(0x18);field<unsigned>(e,8)=(seed+i)%3;events[i]=(seed+i)%5?e:NULL;}list(props[0],0x58,events,11,seed&4?2:11);
 if(c.op==0){unsigned(*fn)(void*)=ours?fsNewRequired:fsOldRequired;autotest::invoke(out,fn,self);}
 else if(c.op==1){bool(*fn)(void*,int)=ours?fsNewHas:fsOldHas;autotest::invoke(out,fn,self,int(seed%14)-1);}
 else if(c.op==2||c.op==16){void*(*fn)(void*)=c.op==2?(ours?fsNewMaster:fsOldMaster):(ours?fsNewOwner:fsOldOwner);if(!autotest::beginInvocation(out,fn))return;void*r=fn(self);out.callCompleted=1;number(identity(r));}
 else if(c.op==3){const float values[]={0,1,-1,2,5,10};Ogre::Vector3 a(values[seed%6],values[seed/6%6],values[seed/36%6]);Ogre::Vector3 b(0,0,0);bool(*fn)(void*,const Ogre::Vector3&,const Ogre::Vector3&,void*,void*)=ours?fsNewRange:fsOldRange;autotest::invoke(out,fn,self,a,b,seed&4?chars[0]:NULL,seed&8?chars[1]:NULL);}
 else if(c.op==4){bool(*fn)(void*,void*,void*,const Ogre::Vector3*,bool)=ours?fsNewTarget:fsOldTarget;Ogre::Vector3 v(1,2,3);autotest::invoke(out,fn,self,seed%7?chars[0]:NULL,chars[1],&v,bool(seed&1));}
 else if(c.op==5){self->m_property=props[0];bool(*fn)(void*,void*)=ours?fsNewWeapon:fsOldWeapon;autotest::invoke(out,fn,self,chars[0]);}
 else if(c.op==6||c.op==7){std::wstring(*fn)(void*,void*,unsigned)=c.op==6?(ours?fsNewDescription:fsOldDescription):(ours?fsNewStats:fsOldStats);unsigned levels[]={0,1,2,3,4,5,~0u};if(!autotest::beginInvocation(out,fn))return;std::wstring s=fn(self,seed&8?chars[2]:NULL,levels[seed%7]);out.callCompleted=1;text(s);}
 else if(c.op>=8&&c.op<=10){int(*fn)(void*,void*,unsigned)=c.op==8?(ours?fsNewManaOT:fsOldManaOT):c.op==9?(ours?fsNewMana:fsOldMana):(ours?fsNewCooldown:fsOldCooldown);unsigned levels[]={0,1,2,3,4,5,~0u};autotest::invoke(out,fn,self,seed&8?chars[2]:NULL,levels[seed%7]);}
 else if(c.op==11){bool(*fn)(void*)=ours?fsNewCalculate:fsOldCalculate;autotest::invoke(out,fn,self);}
 else if(c.op==12){void(*fn)(void*,unsigned)=ours?fsNewSet:fsOldSet;unsigned levels[]={0,1,2,3,4,5,~0u};autotest::invoke(out,fn,self,levels[seed%7]);}
 else if(c.op==13){void**nodeVT=static_cast<void**>(object(30*sizeof(void*)));nodeVT[0xc8/8]=reinterpret_cast<void*>(&orientationSpy);void*node=object(0x40);field<void*>(node,0)=nodeVT;chars[0]->m_pSceneNode=seed&4?reinterpret_cast<Ogre::SceneNode*>(node):NULL;chars[0]->m_pResourceManager=resources;void(*fn)(void*,void*,int)=ours?fsNewState:fsOldState;autotest::invoke(out,fn,self,seed%7?chars[0]:NULL,int(seed%6));}
 else if(c.op==14){
  new(&self->m_sRequiredSkill)std::wstring(seed&1?L"required skill":L"");
  new(&self->m_sAnimationOverride)std::wstring(seed&2?L"animation":L"");
  new(&self->m_sAnimationOverrideDW)std::wstring(seed&4?L"dual":L"");
  new(&self->m_sLoopAnimationOverride)std::wstring(seed&8?L"loop":L"");
  new(&self->m_sLoopAnimationOverrideDW)std::wstring(seed&16?L"dual loop":L"");
  new(&self->m_sAnimationOverrideLoopEnd)std::wstring(seed&32?L"loop end":L"");
  void**propertyVT=static_cast<void**>(object(2*sizeof(void*)));propertyVT[1]=reinterpret_cast<void*>(&propertyDtor);
  for(unsigned i=0;i<4;++i)field<void*>(props[i],0)=propertyVT;
  self->m_levelPropertyData=new CSkillProperty*[4];for(unsigned i=0;i<4;++i)self->m_levelPropertyData[i]=(seed+i)%3?props[i]:NULL;
  self->m_allowedTargetData.m_pData=new CDataGroup*[3];for(unsigned i=0;i<3;++i)self->m_allowedTargetData.m_pData[i]=allowed[i];
  self->m_activeEvents.m_pData=seed&1?new CSkillEvent*[3]:NULL;self->m_activeEvents.m_nCount=2;self->m_activeEvents.m_nCapacity=3;self->m_activeEvents.m_nGrowBy=10;
  self->m_Target.m_pObject=seed&4?chars[2]:NULL;self->m_Target.m_nIndex=57;
  void(*fn)(void*)=ours?fsNewDestroy:fsOldDestroy;autotest::invoke(out,fn,self);
 }
 else if(c.op==15){std::wstring(*fn)(void*)=ours?fsNewType:fsOldType;if(!autotest::beginInvocation(out,fn))return;std::wstring s=fn(self);out.callCompleted=1;text(s);}
 else if(c.op==17){props[0]->m_iChance=int(seed%106)-2;bool(*fn)(void*)=ours?fsNewRoll:fsOldRoll;autotest::invoke(out,fn,self);}
 else if(c.op==18){
  m_gAllowSkillTesting=seed&512;self->m_bEnabled=seed&1;self->m_iCharges=seed%7?3:0;self->m_eActivationType=static_cast<ESKILL_ACTIVATION_TYPE>(seed/4%5);self->m_checksSilence=seed&8;
  props[0]->m_pRequiredTheme=seed&16?reinterpret_cast<CUnitTheme*>(level):NULL;props[0]->m_pForbiddenTheme=seed&32?reinterpret_cast<CUnitTheme*>(resources):NULL;
  props[0]->m_eTargetType=seed/32%12;Ogre::Vector3 v(1,2,3);void*targetUnit=seed%9?chars[1]:NULL;
  if(props[0]->m_eTargetType==7||props[0]->m_eTargetType==8){void**equipmentVT=static_cast<void**>(object(130*sizeof(void*)));equipmentVT[1]=const_cast<std::type_info*>(&typeid(CEquipment));field<void*>(weapons[0],0)=equipmentVT+2;weapons[0]->m_bUnknown348=seed&256;targetUnit=seed%9?weapons[0]:NULL;}
  bool(*fn)(void*,void*,int,const Ogre::Vector3*,void*,bool)=ours?fsNewRequirements:fsOldRequirements;autotest::invoke(out,fn,self,seed%11?chars[0]:NULL,int(seed/16%5),seed%13?&v:NULL,targetUnit,bool(seed&2));
 }
 else if(c.op==19){
  self->m_baseProperty=props[3];for(unsigned i=0;i<4;++i)data[i]=props[i];
  self->m_iTargetAlignment=seed%5;self->m_pendingStop=true;self->m_animationSpeed=2.0f;self->m_animationTimeRemaining=99.0f;props[0]->m_iChance=seed%3?100:0;
  Ogre::Vector3 v(1,2,3),t(4,5,6);Ogre::Quaternion q(1,0.25f,-0.5f,0.75f);
  bool(*fn)(void*,void*,int,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&,void*)=ours?fsNewStart:fsOldStart;autotest::invoke(out,fn,self,seed%7?chars[0]:NULL,int(seed%5),v,q,t,seed%11?chars[1]:NULL);
 }

 number(calls);out.add(reinterpret_cast<char*>(self)+0x18,0xb8-0x18);out.add(reinterpret_cast<char*>(self)+0xd8,0x128-0xd8);
 for(unsigned i=0;i<4;++i){number(props[i]->m_iSkillLevel);props[i]->m_sName.~basic_string();}
}
int run(const tlhybrid_host*host,unsigned op,const char*name,uintptr_t address,unsigned count)
{
 detour::Set patches;if(!install(patches))return 1;
 return smallmass::run(host,op,name,address,execute,count);
}

}
#define TEST(name,op,old,count) TL_TEST(name){return run(host,op,#name,(uintptr_t)&old,count);}
TEST(finish_skill_required_investment,0,fsOldRequired,224)
TEST(finish_skill_has_event,1,fsOldHas,224)
TEST(finish_skill_master_owner_character,2,fsOldMaster,96)
TEST(finish_skill_in_range,3,fsOldRange,432)
TEST(finish_skill_target_valid,4,fsOldTarget,2048)
TEST(finish_skill_weapon_requirements,5,fsOldWeapon,512)
TEST(finish_skill_level_description,6,fsOldDescription,224)
TEST(finish_skill_level_stats,7,fsOldStats,224)
TEST(finish_skill_level_mana_ot,8,fsOldManaOT,224)
TEST(finish_skill_level_mana,9,fsOldMana,224)
TEST(finish_skill_level_cooldown,10,fsOldCooldown,224)
TEST(finish_skill_calculate_level,11,fsOldCalculate,256)
TEST(finish_skill_set_level,12,fsOldSet,224)
TEST(finish_skill_unit_state,13,fsOldState,96)
TEST(finish_skill_destructor,14,fsOldDestroy,64)
TEST(finish_skill_type_display_name,15,fsOldType,48)
TEST(finish_skill_owner_character,16,fsOldOwner,96)
TEST(finish_skill_roll_chance,17,fsOldRoll,256)
TEST(finish_skill_requirements,18,fsOldRequirements,1024)
TEST(finish_skill_start,19,fsOldStart,384)
#undef TEST
