#include <cstring>
#include <string>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "SkillEvent.h"
#include "SkillProperty.h"
#include "EffectManager.h"
#include "Equipment.h"
#include "Item.h"
#undef protected
#undef private
TL_ORIGINAL(bool,ewOld,(CSkillEvent*,CCharacter*,CItem*,float,float,bool,bool),"_ZN11CSkillEvent17applyWeaponDamageEP10CCharacterP5CItemffbb")
extern "C" bool ewNew(CSkillEvent*,CCharacter*,CItem*,float,float,bool,bool) __asm__("_ZN11CSkillEvent17applyWeaponDamageEP10CCharacterP5CItemffbb");
TL_FUNCTION(ewPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(ewCan,"_ZN11CSkillEvent18canEffectPosObjectERKN4Ogre7Vector3EP19CPositionableObject")
TL_FUNCTION(ewRay,"_ZN6CLevel12rayCollisionERKN4Ogre7Vector3ES3_RS1_S4_b")
TL_FUNCTION(ewCalc,"_ZN14CEffectManager21calculateEffectValuesEv")
TL_FUNCTION(ewTarget,"_ZN10CCharacter9setTargetEPS_")
TL_FUNCTION(ewItem,"_ZN10CCharacter13setTargetItemEP5CItem")
TL_FUNCTION(ewRight,"_ZN10CCharacter20getWeaponInRightHandEv")
TL_FUNCTION(ewLeft,"_ZN10CCharacter19getWeaponInLeftHandEv")
TL_FUNCTION(ewAttack,"_ZN10CCharacter13performAttackEP10CEquipmentjff13EDAMAGE_TYPES")
TL_FUNCTION(ewISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(ewHP,"_ZN10CCharacter2HPEv")
TL_FUNCTION(ewTrigger,"_ZN6CSkill12triggerEventE17ESKILL_EVENT_TYPERKN4Ogre7Vector3ERKNS1_10QuaternionEP9CBaseUnitPS3_")
extern "C" void*ewItemTable[] __asm__("_ZTV5CItem");
namespace {
using namespace smallmass;
unsigned seed,attackCount;CSkillEvent*self;CSkillProperty*property;CCharacter*characters[4];CItem*items[2];CEquipment*weapons[2];CEffectManager*effects;CResourceManager*resources;CLevel*level;CSkill*skill;
int id(const void*p){if(!p)return -1;if(p==self)return 0;if(p==property)return 1;if(p==resources)return 2;if(p==level)return 3;if(p==effects)return 4;if(p==skill)return 5;for(unsigned i=0;i<4;++i)if(p==characters[i])return 10+i;for(unsigned i=0;i<2;++i){if(p==items[i])return 20+i;if(p==weapons[i])return 30+i;}return -2;}
void event(unsigned e,const void*p){number(e);number(id(p));}
Ogre::Vector3 pos(CPositionableObject*p,bool world){event(1,p);number(world);return Ogre::Vector3(float(id(p)),float(int(seed%7)-3),-2.5f);}
bool can(CSkillEvent*p,const Ogre::Vector3&v,CPositionableObject*q){event(2,p);vector(v);number(id(q));return seed%23!=0;}
bool ray(CLevel*p,const Ogre::Vector3&a,const Ogre::Vector3&b,Ogre::Vector3&c,Ogre::Vector3&n,bool flag){event(3,p);vector(a);vector(b);number(flag);c=Ogre::Vector3(1,2,3);n=Ogre::Vector3(0,1,0);return seed%19==0;}
void calc(CEffectManager*p){event(4,p);}
void target(CCharacter*p,CCharacter*q){event(5,p);number(id(q));p->m_targetCharacter.m_pObject=q;}
void item(CCharacter*p,CItem*q){event(6,p);number(id(q));p->m_targetItem.m_pObject=q;}
CEquipment*right(CCharacter*p){event(7,p);return seed&4?weapons[0]:NULL;}
CEquipment*left(CCharacter*p){event(8,p);return seed&8?weapons[1]:NULL;}
void attack(CCharacter*p,CEquipment*w,unsigned flags,float damage,float soak,EDAMAGE_TYPES type){event(9,p);number(id(w));number(flags);floating(damage);floating(soak);number(type);++attackCount;if(seed&2048){self->m_weaponDamageScale+=0.75f;self->m_soakScale-=0.25f;}if(seed%29==0)self->m_pSkillProperty=NULL;}
bool interact(CItem*p,CCharacter*q){event(10,p);number(id(q));return false;}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){event(11,p);number(type);return seed%7!=0 && (type!=8 || seed%5!=0);}
int hp(CCharacter*p){event(12,p);return int(seed%3)-1;}
bool trigger(CSkill*p,ESKILL_EVENT_TYPE type,const Ogre::Vector3&v,const Ogre::Quaternion&q,CBaseUnit*t,const Ogre::Vector3*to){event(13,p);number(type);vector(v);output->add(&q,sizeof(q));number(id(t));number(to!=NULL);return false;}
void weaponSide(Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index<256?c.index:(c.index*40503u+0x1234u)&65535u;attackCount=0;self=static_cast<CSkillEvent*>(object(sizeof(CSkillEvent)));property=static_cast<CSkillProperty*>(object(sizeof(CSkillProperty)));resources=static_cast<CResourceManager*>(object(sizeof(CResourceManager)));level=static_cast<CLevel*>(object(0x2000));effects=static_cast<CEffectManager*>(object(sizeof(CEffectManager)));skill=static_cast<CSkill*>(object(sizeof(CSkill)));
 void*itemVT[120];std::memcpy(itemVT,ewItemTable,sizeof(itemVT));itemVT[2+0x280/8]=reinterpret_cast<void*>(&interact);
 Ogre::SceneNode node(NULL);node.setOrientation(Ogre::Quaternion(0.5f,0.5f,0.5f,0.5f));
 for(unsigned i=0;i<4;++i){characters[i]=static_cast<CCharacter*>(object(sizeof(CCharacter)));new(&characters[i]->m_targetCharacter)TSafePointer<CCharacter>();new(&characters[i]->m_targetItem)TSafePointer<CItem>();characters[i]->m_pEffectManager=seed&16?effects:NULL;characters[i]->m_pSceneNode=seed&32?&node:NULL;}
 for(unsigned i=0;i<2;++i){items[i]=static_cast<CItem*>(object(sizeof(CItem)));*reinterpret_cast<void***>(items[i])=itemVT+2;weapons[i]=static_cast<CEquipment*>(object(sizeof(CEquipment)));}
 for(unsigned i=0;i<4;++i){characters[i]->m_targetCharacter.m_pObject=seed&64?characters[3]:NULL;characters[i]->m_targetItem.m_pObject=seed&128?items[1]:NULL;}
 new(&self->m_target)TSafePointer<CBaseUnit>();new(&self->m_ownerCharacter)TSafePointer<CCharacter>();new(&self->m_skillTarget)TSafePointer<CBaseUnit>();self->m_target.m_pObject=seed%31==0?NULL:characters[0];self->m_ownerCharacter.m_pObject=seed&256?characters[1]:NULL;
 self->m_skillTarget.m_pObject=seed%11==0?characters[2]:NULL;self->m_pSkillProperty=seed%37==0?NULL:property;self->m_pResourceManager=resources;resources->m_pLevel=level;self->m_pSkill=skill;
 self->m_eventType=static_cast<ESKILL_EVENT_TYPE>(seed%7);self->m_weaponDamageScale=seed%41==0?0.0f:seed%17==0?bits(0x7fc00000):-0.75f;self->m_soakScale=1.25f;self->m_damageType=seed%8;
 self->m_useDPS=seed&512;self->m_noStrikeParticles=seed&1024;self->m_noStealEffects=seed&4096;self->m_damageRequiresLOS=seed&8192;property->m_bHasAnimation=seed&2;property->m_bSingleTarget=seed%13==0;property->m_iRequirementLeft=19;
 CCharacter*t=seed&1?characters[2]:NULL;CItem*i=t?(seed%3==0?items[0]:NULL):items[0];bool immediate=seed&16384;bool ignore=seed&32768;
 typedef bool(*Fn)(CSkillEvent*,CCharacter*,CItem*,float,float,bool,bool);Fn fn=ours?ewNew:ewOld;if(!autotest::beginInvocation(out,fn))return;bool result=fn(self,t,i,0.375f,-0.5f,immediate,ignore);out.callCompleted=1;number(result);number(attackCount);for(unsigned j=0;j<4;++j){number(id(characters[j]->m_targetCharacter.getObject()));number(id(characters[j]->m_targetItem.getObject()));}floating(self->m_weaponDamageScale);floating(self->m_soakScale);
}
}
TL_TEST(complete_event_weapon){detour::Set h;TL_REDIRECT(h,ewPosition,&pos);TL_REDIRECT(h,ewCan,&can);TL_REDIRECT(h,ewRay,&ray);TL_REDIRECT(h,ewCalc,&calc);TL_REDIRECT(h,ewTarget,&target);TL_REDIRECT(h,ewItem,&item);TL_REDIRECT(h,ewRight,&right);TL_REDIRECT(h,ewLeft,&left);TL_REDIRECT(h,ewAttack,&attack);TL_REDIRECT(h,ewISA,&isa);TL_REDIRECT(h,ewHP,&hp);TL_REDIRECT(h,ewTrigger,&trigger);if(h.failed())return 1;return smallmass::run(host,0,"complete_event_weapon",0xcb7b70,&weaponSide,1280);}
