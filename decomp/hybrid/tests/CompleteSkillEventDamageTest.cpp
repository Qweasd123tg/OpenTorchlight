#include <cstring>
#include <map>
#include <string>
#include <typeinfo>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "SkillEvent.h"
#include "SkillProperty.h"
#include "SkillEffectAndAffixes.h"
#include "DamageShape.h"
#include "Missile.h"
#include "AIManager.h"
#include "Level.h"
#include "GenericModel.h"
#include <OgreEntity.h>
#include <OgreMesh.h>
#undef protected
#undef private
#define DECL(ret,old,now,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret now args __asm__(sym);
DECL(bool,sdOldApply,sdNewApply,(CSkillEvent*,CBaseUnit*,const Ogre::Vector3*,bool),"_ZN11CSkillEvent12applyEffectsEP9CBaseUnitPKN4Ogre7Vector3Eb")
DECL(bool,sdOldShape,sdNewShape,(CSkillEvent*,CDamageShape*,CCharacter*,Ogre::Vector3*),"_ZN11CSkillEvent30characterEffectedByDamageShapeEP12CDamageShapeP10CCharacterPN4Ogre7Vector3E")
DECL(bool,sdOldItem,sdNewItem,(CSkillEvent*,CDamageShape*,CItem*),"_ZN11CSkillEvent25itemEffectedByDamageShapeEP12CDamageShapeP5CItem")
DECL(bool,sdOldMissile,sdNewMissile,(CSkillEvent*,CMissile*,CCharacter*,const Ogre::Vector3*,float,float),"_ZN11CSkillEvent22missileApplyingEffectsEP8CMissileP10CCharacterPKN4Ogre7Vector3Eff")
DECL(bool,sdOldShapeCan,sdNewShapeCan,(CSkillEvent*,CDamageShape*,CCharacter*),"_ZN11CSkillEvent38getCharacterCanBeAffectedByDamageShapeEP12CDamageShapeP10CCharacter")
DECL(bool,sdOldMissileCan,sdNewMissileCan,(CSkillEvent*,CMissile*,CCharacter*),"_ZN11CSkillEvent32getCharacterCanBeHarmedByMissileEP8CMissileP10CCharacter")
DECL(Ogre::Vector3,sdOldBone,sdNewBone,(CSkillEvent*,CBaseUnit*,ESKILL_BONE_ATTACHMENT,bool),"_ZN11CSkillEvent15getBonePositionEP9CBaseUnit22ESKILL_BONE_ATTACHMENTb")
#undef DECL
TL_ORIGINAL(void,sdCtor,(CSkillEvent*,CSkill*,CSkillProperty*,CResourceManager*,CDataGroup*),"_ZN11CSkillEventC1EP6CSkillP14CSkillPropertyP16CResourceManagerP10CDataGroup")
TL_FUNCTION(sdMaster,"_ZN6CSkill23getMasterOwnerCharacterEv")
TL_FUNCTION(sdMasterUnit,"_ZN6CSkill14getMasterOwnerEv")
TL_FUNCTION(sdPropertyOwner,"_ZN14CSkillProperty17getOwnerCharacterEv")
TL_FUNCTION(sdTargetType,"_ZN6CSkill13getTargetTypeEv")
TL_FUNCTION(sdHP,"_ZN10CCharacter2HPEv")
TL_FUNCTION(sdAlive,"_ZN10CCharacter5aliveEv")
TL_FUNCTION(sdISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(sdEnemy,"_ZN10CCharacter7isEnemyEPS_")
TL_FUNCTION(sdAlignment,"_ZN10CCharacter9alignmentEv")
TL_FUNCTION(sdAIFlag,"_ZN10CAIManager9hasAIFlagE13EAIFLAG_TYPES")
TL_FUNCTION(sdPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(sdApply,"_ZN22CSkillEffectAndAffixes22applyAffixesAndEffectsEP9CBaseUnitP10CCharacterPKN4Ogre7Vector3Eb")
TL_FUNCTION(sdRemove,"_ZN22CSkillEffectAndAffixes23removeAffixesAndEffectsEP9CBaseUnitP10CCharacter")
TL_FUNCTION(sdDamaging,"_ZN22CSkillEffectAndAffixes10isDamagingEv")
TL_FUNCTION(sdWeapon,"_ZN11CSkillEvent17applyWeaponDamageEP10CCharacterP5CItemffbb")
TL_FUNCTION(sdInvoke,"_ZN11CSkillEvent15invokeHitSkillsEP10CCharacter")
TL_FUNCTION(sdUpdateEffects,"_ZN10CCharacter13updateEffectsEfR6CLevel")
TL_FUNCTION(sdRay,"_ZN6CLevel12rayCollisionERKN4Ogre7Vector3ES3_RS1_S4_b")
TL_FUNCTION(sdTrigger,"_ZN6CSkill12triggerEventE17ESKILL_EVENT_TYPERKN4Ogre7Vector3ERKNS1_10QuaternionEP9CBaseUnitPS3_")
extern "C" char sdMeshGet[] __asm__("_ZNK4Ogre6Entity7getMeshEv");
extern "C" char sdMeshBounds[] __asm__("_ZNK4Ogre4Mesh9getBoundsEv");
namespace {
using namespace smallmass;
CSkillEvent*self;CSkill*skill;CSkillProperty*property;CCharacter*characters[3];CResourceManager*resources;CLevel*level;CDamageShape*shape;CMissile*missile;CItem*item;CSkillEffectAndAffixes*effects[2];CDataGroup*groups[2];CAIManager*ai;CGenericModel*model;
unsigned seed,op;Ogre::MeshPtr* meshRef;Ogre::Entity* entity;Ogre::Mesh* mesh;Ogre::AxisAlignedBox box;
int id(const void*p){if(!p)return -1;if(p==self)return 0;if(p==skill)return 1;if(p==property)return 2;if(p==shape)return 3;if(p==missile)return 4;if(p==item)return 5;if(p==resources)return 6;if(p==level)return 7;if(p==ai)return 8;if(p==model)return 9;for(unsigned i=0;i<3;++i)if(p==characters[i])return 10+i;for(unsigned i=0;i<2;++i){if(p==effects[i])return 20+i;if(p==groups[i])return 30+i;}return -2;}
void ev(unsigned e,const void*p){number(e);number(id(p));}
CCharacter*master(CSkill*p){ev(1,p);return seed%5==0?NULL:characters[0];}
CBaseUnit*masterUnit(CSkill*p){ev(2,p);return characters[0];}
CCharacter*owner(CSkillProperty*p){ev(3,p);return seed%7==0?NULL:characters[1];}
int targetType(CSkill*p){ev(4,p);const int a[]={0,2,9,10,11};return a[seed/3%5];}
int hp(CCharacter*p){ev(5,p);return (int(seed/2%3)-1)*10;}
bool alive(CCharacter*p){ev(6,p);return seed&1;}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){ev(7,p);number(type);return seed&16;}
bool enemy(CCharacter*p,CCharacter*q){ev(8,p);number(id(q));return seed&32;}
int alignment(CCharacter*p){ev(9,p);return seed/13%5;}
bool aiFlag(CAIManager*p,EAIFLAG_TYPES type){ev(10,p);number(type);return seed%11==0;}
Ogre::Vector3 position(CPositionableObject*p,bool absolute){ev(11,p);number(absolute);float y=float(int(seed/7%9)-4);return Ogre::Vector3(float(id(p))*0.25f,p==shape||p==missile?0:y,float(id(p))*-0.75f);}
bool apply(CSkillEffectAndAffixes*p,CBaseUnit*u,CCharacter*c,const Ogre::Vector3*v,bool f){ev(12,p);number(id(u));number(id(c));number(v!=NULL);if(v)vector(*v);number(f);return seed&2;}
bool remove(CSkillEffectAndAffixes*p,CBaseUnit*u,CCharacter*c){ev(13,p);number(id(u));number(id(c));return seed&4;}
bool damaging(CSkillEffectAndAffixes*p){ev(14,p);return seed&8;}
bool weapon(CSkillEvent*p,CCharacter*c,CItem*i,float a,float b,bool x,bool y){ev(15,p);number(id(c));number(id(i));floating(a);floating(b);number(x);number(y);return seed&64;}
bool applyEvent(CSkillEvent*p,CBaseUnit*u,const Ogre::Vector3*v,bool f){ev(25,p);number(id(u));number(v!=NULL);if(v)vector(*v);number(f);return seed&2;}
void invoke(CSkillEvent*p,CCharacter*c){ev(16,p);number(id(c));}
void updateEffects(CCharacter*p,float dt,CLevel&l){ev(17,p);floating(dt);number(id(&l));}
bool ray(CLevel*p,const Ogre::Vector3&a,const Ogre::Vector3&b,Ogre::Vector3&,Ogre::Vector3&,bool f){ev(18,p);vector(a);vector(b);number(f);return seed&128;}
void state(CCharacter*p,EAIState s){ev(19,p);number(s);}
const Ogre::Quaternion&orientation(Ogre::SceneNode*){static Ogre::Quaternion q(0.25f,0.5f,-0.75f,1);number(20);return q;}
bool trigger(CSkill*p,ESKILL_EVENT_TYPE type,const Ogre::Vector3&v,const Ogre::Quaternion&q,CBaseUnit*t,const Ogre::Vector3*to){ev(21,p);number(type);vector(v);output->add(&q,sizeof(q));number(id(t));number(to!=NULL);return false;}
float*scale(CBaseUnit*p){ev(22,p);static float f;f=float(int(seed/2%5)-2)*0.75f;return &f;}
void* unitModel(CBaseUnit*p){ev(23,p);return seed&128?model:NULL;}
const Ogre::Vector3&boneNode(Ogre::SceneNode*){static Ogre::Vector3 v(1.25f,-0.5f,2.5f);number(24);return v;}
const Ogre::MeshPtr& meshGet(const Ogre::Entity*p){number(26);number(p==entity);return *meshRef;}
const Ogre::AxisAlignedBox& meshBounds(const Ogre::Mesh*p){number(27);number(p==mesh);return box;}
void side(Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;op=c.op;
 self=static_cast<CSkillEvent*>(object(sizeof(CSkillEvent)));sdCtor(self,NULL,NULL,NULL,NULL);
 skill=static_cast<CSkill*>(object(sizeof(CSkill)));property=static_cast<CSkillProperty*>(object(sizeof(CSkillProperty)));resources=static_cast<CResourceManager*>(object(sizeof(CResourceManager)));level=static_cast<CLevel*>(object(sizeof(CLevel)));ai=static_cast<CAIManager*>(object(sizeof(CAIManager)));model=static_cast<CGenericModel*>(object(sizeof(CGenericModel)));
 Ogre::MeshPtr shared;mesh=static_cast<Ogre::Mesh*>(object(8));entity=static_cast<Ogre::Entity*>(object(8));shared.pRep=seed&2048?mesh:NULL;meshRef=&shared;box.setExtents(-2,float(int(seed%5)-2),-3,4,float(int(seed/5%5)-2),7);model->m_pEntity=seed&1024?entity:NULL;
 shape=static_cast<CDamageShape*>(object(sizeof(CDamageShape)));missile=static_cast<CMissile*>(object(sizeof(CMissile)));item=static_cast<CItem*>(object(sizeof(CItem)));
 void*vt[150];std::memset(vt,0,sizeof(vt));vt[1]=const_cast<std::type_info*>(&typeid(CCharacter));vt[2+0x348/8]=reinterpret_cast<void*>(&state);vt[2+0xa0/8]=reinterpret_cast<void*>(&scale);vt[2+0x1e0/8]=reinterpret_cast<void*>(&unitModel);
 Ogre::SceneNode parentNode(NULL);parentNode.setPosition(10,20,-30);Ogre::SceneNode* nativeNode=op==6?new Ogre::SceneNode(NULL):NULL;if(nativeNode)parentNode.addChild(nativeNode);if(nativeNode)nativeNode->setPosition(1.25f,float(int(seed%7)-3)*0.5f,2.5f);
 void*node=object(8);void*nodeVT[40];std::memset(nodeVT,0,sizeof(nodeVT));nodeVT[0xc8/8]=reinterpret_cast<void*>(&orientation);nodeVT[0xf8/8]=reinterpret_cast<void*>(&boneNode);*reinterpret_cast<void***>(node)=nodeVT;
 for(unsigned i=0;i<3;++i){characters[i]=static_cast<CCharacter*>(object(sizeof(CCharacter)));*reinterpret_cast<void***>(characters[i])=vt+2;characters[i]->m_pResourceManager=seed&256?resources:NULL;characters[i]->m_pMaster=seed&(1u<<i)?characters[0]:NULL;characters[i]->m_pAIManager=seed&64?ai:NULL;characters[i]->m_fBaseUnitValue194=0.5f;characters[i]->m_pHeadNode=characters[i]->m_pRightHandNode=characters[i]->m_pLeftHandNode=characters[i]->m_pLeftShoulderNode=characters[i]->m_pRightShoulderNode=seed&512?(nativeNode?nativeNode:static_cast<Ogre::SceneNode*>(node)):NULL;}
 characters[0]->m_pMaster=seed&8?characters[2]:NULL;resources->m_pLevel=seed&512?level:NULL;
 for(unsigned i=0;i<2;++i){effects[i]=static_cast<CSkillEffectAndAffixes*>(object(sizeof(CSkillEffectAndAffixes)));groups[i]=static_cast<CDataGroup*>(object(sizeof(CDataGroup)));}
 characters[2]->m_pDataGroup=groups[seed%2];
 self->m_pSkill=op==3&&seed%17==0?NULL:skill;self->m_pResourceManager=resources;self->m_pSkillProperty=seed%19==0?NULL:property;self->m_pSkillEffectAndAffixes=seed&2?effects[0]:NULL;property->m_pSkillEffectAndAffixes=seed&4?effects[1]:NULL;
 property->m_bSingleTarget=seed&8;property->m_eTargetUnitType=seed&16?7:0;property->m_eTargetType=seed%7==0?4:0;property->m_iSkillLevel=seed/11%4;
 self->m_skillTarget.m_pObject=seed&32?characters[2]:characters[1];self->m_targetCorpses=seed&64;self->m_missileTargetSelf=seed&128;self->m_damageRequiresLOS=seed&16;
 self->m_eventType=static_cast<ESKILL_EVENT_TYPE>(seed/13%11);shape->m_bTargetOnlyDead=seed&256;shape->m_shapeKind=seed&512?4:0;missile->m_bUnknown294=seed&1024;missile->m_pSceneNode=static_cast<Ogre::SceneNode*>(node);missile->m_owner.m_pObject=seed%5?NULL:characters[0];
 if(seed&256)self->m_specificUnits.add(groups[0]);if(seed&512)self->m_specificUnits.add(groups[1]);
 CCharacter*target=seed%23==0?NULL:characters[2];Ogre::Vector3 v(0.25f,-1.5f,3.75f);bool result=false;
 if(op==0){typedef bool(*Fn)(CSkillEvent*,CBaseUnit*,const Ogre::Vector3*,bool);Fn fn=ours?sdNewApply:sdOldApply;if(!autotest::beginInvocation(out,fn))return;result=fn(self,target,seed&1?&v:NULL,seed&8);}
 if(op==1){typedef bool(*Fn)(CSkillEvent*,CDamageShape*,CCharacter*,Ogre::Vector3*);Fn fn=ours?sdNewShape:sdOldShape;self->m_pSkillProperty=property;if(!autotest::beginInvocation(out,fn))return;result=fn(self,shape,characters[2],seed&1?&v:NULL);}
 if(op==2){typedef bool(*Fn)(CSkillEvent*,CDamageShape*,CItem*);Fn fn=ours?sdNewItem:sdOldItem;self->m_pSkillProperty=property;if(!autotest::beginInvocation(out,fn))return;result=fn(self,shape,item);}
 if(op==3){typedef bool(*Fn)(CSkillEvent*,CMissile*,CCharacter*,const Ogre::Vector3*,float,float);Fn fn=ours?sdNewMissile:sdOldMissile;self->m_pSkillProperty=property;if(!autotest::beginInvocation(out,fn))return;result=fn(self,missile,characters[2],seed&1?&v:NULL,0.25f,-0.75f);}
 if(op==4){typedef bool(*Fn)(CSkillEvent*,CDamageShape*,CCharacter*);Fn fn=ours?sdNewShapeCan:sdOldShapeCan;if(!autotest::beginInvocation(out,fn))return;result=fn(self,shape,target);}
 if(op==5){typedef bool(*Fn)(CSkillEvent*,CMissile*,CCharacter*);Fn fn=ours?sdNewMissileCan:sdOldMissileCan;if(!autotest::beginInvocation(out,fn))return;result=fn(self,missile,target);}
 if(op==6){typedef Ogre::Vector3(*Fn)(CSkillEvent*,CBaseUnit*,ESKILL_BONE_ATTACHMENT,bool);Fn fn=ours?sdNewBone:sdOldBone;self->m_caster.m_pObject=characters[0];if(!autotest::beginInvocation(out,fn))return;v=fn(self,target,static_cast<ESKILL_BONE_ATTACHMENT>(seed/4%9),seed&1);}
 out.callCompleted=1;number(result);vector(v);shared.pRep=NULL;delete nativeNode;self->m_specificUnits.~TArrayList<CDataGroup*>();
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned cases){
 detour::Set h;TL_REDIRECT(h,sdMaster,&master);TL_REDIRECT(h,sdMasterUnit,&masterUnit);TL_REDIRECT(h,sdPropertyOwner,&owner);TL_REDIRECT(h,sdTargetType,&targetType);TL_REDIRECT(h,sdHP,&hp);TL_REDIRECT(h,sdAlive,&alive);TL_REDIRECT(h,sdISA,&isa);TL_REDIRECT(h,sdEnemy,&enemy);TL_REDIRECT(h,sdAlignment,&alignment);TL_REDIRECT(h,sdAIFlag,&aiFlag);TL_REDIRECT(h,sdPosition,&position);TL_REDIRECT(h,sdApply,&apply);TL_REDIRECT(h,sdRemove,&remove);TL_REDIRECT(h,sdDamaging,&damaging);TL_REDIRECT(h,sdWeapon,&weapon);TL_REDIRECT(h,sdInvoke,&invoke);TL_REDIRECT(h,sdUpdateEffects,&updateEffects);TL_REDIRECT(h,sdRay,&ray);TL_REDIRECT(h,sdTrigger,&trigger);
 if(op>=1&&op<=3)h.redirect(reinterpret_cast<char*>(&sdOldApply),reinterpret_cast<char*>(&sdNewApply),&applyEvent);
 h.redirect(sdMeshGet,sdMeshGet,&meshGet);h.redirect(sdMeshBounds,sdMeshBounds,&meshBounds);
 if(h.failed())return 1;return smallmass::run(host,op,name,address,&side,cases);
}
}
TL_TEST(complete_event_apply_effects){return run(host,0,"complete_event_apply_effects",0xcb7850,1024);}
TL_TEST(complete_event_shape_effects){return run(host,1,"complete_event_shape_effects",0xcc1c40,1024);}
TL_TEST(complete_event_item_effects){return run(host,2,"complete_event_item_effects",0xcb84f0,512);}
TL_TEST(complete_event_missile_effects){return run(host,3,"complete_event_missile_effects",0xcb8360,2048);}
TL_TEST(complete_event_shape_target){return run(host,4,"complete_event_shape_target",0xcc1e40,4096);}
TL_TEST(complete_event_missile_target){return run(host,5,"complete_event_missile_target",0xcb73c0,4096);}
TL_TEST(complete_event_bone){return run(host,6,"complete_event_bone",0xcb87a0,4096);}
