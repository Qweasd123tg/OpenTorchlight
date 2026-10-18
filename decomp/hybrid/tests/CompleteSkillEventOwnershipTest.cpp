#include <cstring>
#include <string>
#include <map>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "SkillEvent.h"
#include "SkillProperty.h"
#include "DamageShape.h"
#include "UnitSpawner.h"
#include "Missile.h"
#include "ExecuteSkillProps.h"
#include "PathController.h"
#include "GenericModel.h"
#include "Equipment.h"
#undef protected
#undef private
#define DECL(ret,old,now,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret now args __asm__(sym);
DECL(void,soOldReset,soNewReset,(CSkillEvent*),"_ZN11CSkillEvent5resetEv")
DECL(void,soOldDtor,soNewDtor,(CSkillEvent*),"_ZN11CSkillEventD1Ev")
DECL(void,soOldListeners,soNewListeners,(CSkillEvent*),"_ZN11CSkillEvent12addListenersEv")
DECL(void,soOldSpawn,soNewSpawn,(CSkillEvent*,CUnitSpawner*,CPositionableObject*),"_ZN11CSkillEvent26unitSpawnedFromUnitSpawnerEP12CUnitSpawnerP19CPositionableObject")
DECL(void,soOldFired,soNewFired,(CSkillEvent*,CMissile*),"_ZN11CSkillEvent17missileBeingFiredEP8CMissile")
DECL(void,soOldDieing,soNewDieing,(CSkillEvent*,CMissile*),"_ZN11CSkillEvent13missileDieingEP8CMissile")
DECL(void,soOldInvoke,soNewInvoke,(CSkillEvent*,CCharacter*),"_ZN11CSkillEvent15invokeHitSkillsEP10CCharacter")
DECL(void,soOldMinMax,soNewMinMax,(CSkillEvent*,CResourceManager*,unsigned,float&,float&),"_ZN11CSkillEvent28addMinAndMaxValuesOfAnEffectEP16CResourceManagerjRfS2_")
DECL(CPositionableObject*,soOldValidate,soNewValidate,(CSkillEvent*,CMissile*,CPositionableObject*,Ogre::Vector3&),"_ZN11CSkillEvent33missileValidateTargetBeforeLaunchEP8CMissileP19CPositionableObjectRN4Ogre7Vector3E")
#undef DECL
TL_ORIGINAL(void,soCtor,(CSkillEvent*,CSkill*,CSkillProperty*,CResourceManager*,CDataGroup*),"_ZN11CSkillEventC1EP6CSkillP14CSkillPropertyP16CResourceManagerP10CDataGroup")
TL_ORIGINAL(void,soCoreCtor,(CRunicCore*),"_ZN10CRunicCoreC1Ev")
TL_ORIGINAL(void,soCoreDtor,(CRunicCore*),"_ZN10CRunicCoreD1Ev")
TL_FUNCTION(soObjects,"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(soAlignment,"_ZN10CCharacter9alignmentEv")
TL_FUNCTION(soSetAlignment,"_ZN10CCharacter12setAlignmentE10EAlignment")
TL_FUNCTION(soAddPet,"_ZN10CCharacter6addPetEPS_")
TL_FUNCTION(soPlaying,"_ZN10CCharacter19getAnimationPlayingEv")
TL_FUNCTION(soName,"_ZNK13CGenericModel16getAnimationNameEj")
TL_FUNCTION(soTime,"_ZN13CGenericModel16getAnimationTimeEv")
TL_FUNCTION(soIndex,"_ZNK13CGenericModel17getAnimationIndexERKSs")
TL_FUNCTION(soAIAnimation,"_ZN10CCharacter18setAIPlayAnimationERKSsbff")
TL_FUNCTION(soEffect,"_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(soApply,"_ZN11CSkillEvent12applyEffectsEP9CBaseUnitPKN4Ogre7Vector3Eb")
TL_FUNCTION(soPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(soTrigger,"_ZN6CSkill12triggerEventE17ESKILL_EVENT_TYPERKN4Ogre7Vector3ERKNS1_10QuaternionEP9CBaseUnitPS3_")
TL_FUNCTION(soHP,"_ZN10CCharacter2HPEv")
TL_FUNCTION(soMaster,"_ZN6CSkill23getMasterOwnerCharacterEv")
TL_FUNCTION(soOwner,"_ZN6CSkill17getOwnerCharacterEv")
TL_FUNCTION(soTarget,"_ZN6CSkill13getTargetTypeEv")
TL_FUNCTION(soRight,"_ZN10CCharacter20getWeaponInRightHandEv")
TL_FUNCTION(soLeft,"_ZN10CCharacter19getWeaponInLeftHandEv")
TL_FUNCTION(soMinimum,"_ZN10CEquipment13minimumDamageEv")
TL_FUNCTION(soMaximum,"_ZN10CEquipment13maximumDamageEv")
TL_FUNCTION(soMinMax,"_ZN22CSkillEffectAndAffixes28addMinAndMaxValuesOfAnEffectEP16CResourceManagerjRfS2_")
TL_FUNCTION(soBone,"_ZN11CSkillEvent15getBonePositionEP9CBaseUnit22ESKILL_BONE_ATTACHMENTb")
extern "C" void*soDamageTable[] __asm__("_ZTV12CDamageShape");
extern "C" void*soSpawnerTable[] __asm__("_ZTV12CUnitSpawner");
extern "C" void*soCharacterTable[] __asm__("_ZTV10CCharacter");
extern "C" void*soMissileTable[] __asm__("_ZTV8CMissile");
namespace {
using namespace smallmass;
CSkillEvent*self;CEditorScene*scene;void*owned[8];CCharacter*chars[2];CMissile*missiles[2];CDamageShape*shapes[2];CUnitSpawner*spawners[2];CGenericModel*model;unsigned seed;CSkill*skill;CEquipment*weapons[2];TArrayList<CEditorBaseObject*>*shapeList,*spawnerList;
int id(const void*p){if(!p)return -1;if(p==self)return 0;if(p==scene)return 1;if(p==model)return 2;if(p==skill)return 3;for(unsigned i=0;i<2;++i)if(p==weapons[i])return 60+i;for(unsigned i=0;i<8;++i)if(p==owned[i])return 10+i;for(unsigned i=0;i<2;++i){if(p==chars[i])return 20+i;if(p==missiles[i])return 30+i;if(p==shapes[i])return 40+i;if(p==spawners[i])return 50+i;}return -2;}
void ev(unsigned e,const void*p){number(e);number(id(p));}
void ownedDtor(CRunicCore*p){ev(1,p);number(self->m_pSkill==NULL);number(self->m_active);}
void visible(CEditorScene*p,bool value){ev(2,p);number(value);}
TArrayList<CEditorBaseObject*>*objects(CEditorScene*p,const std::wstring&name){ev(3,p);text(name);return seed%13==0?NULL:name==L"Damage Shape"?shapeList:spawnerList;}
int alignment(CCharacter*p){ev(4,p);return seed%5;}
void setAlignment(CCharacter*p,EAlignment a){ev(5,p);number(a);}
void setLevel(CCharacter*p,unsigned level,bool apply){ev(6,p);number(level);number(apply);}
void addPet(CCharacter*p,CCharacter*q){ev(7,p);number(id(q));}
void*unitModel(CCharacter*p){ev(8,p);return seed&16?model:NULL;}
unsigned playing(CCharacter*p){ev(9,p);return 31;}
const std::string&getName(CGenericModel*p,unsigned index){ev(10,p);number(index);static std::string value;value=seed&32?"cast_spell":"";return value;}
float animTime(CGenericModel*p){ev(11,p);return 0.375f;}
int index(CGenericModel*p,const std::string&value){ev(12,p);text(value);return seed&64?7:-1;}
void aiAnimation(CCharacter*p,const std::string&value,bool loop,float blend,float speed){ev(13,p);text(value);number(loop);floating(blend);floating(speed);}
void updateAnimation(CCharacter*p,float dt){ev(14,p);floating(dt);}
float effect(CCharacter*p,EEFFECT_TYPE type,EDAMAGE_TYPES damage){ev(15,p);number(type);number(damage);return -2.75f;}
bool apply(CSkillEvent*p,CBaseUnit*u,const Ogre::Vector3*v,bool flag){ev(16,p);number(id(u));number(v!=NULL);number(flag);return false;}
Ogre::Vector3 position(CPositionableObject*p,bool absolute){ev(17,p);number(absolute);return Ogre::Vector3(float(id(p)),2,-3);}
bool trigger(CSkill*p,ESKILL_EVENT_TYPE type,const Ogre::Vector3&v,const Ogre::Quaternion&q,CBaseUnit*t,const Ogre::Vector3*to){ev(18,p);number(type);vector(v);output->add(&q,sizeof(q));number(id(t));number(to!=NULL);return false;}
int hp(CCharacter*p){ev(19,p);return int(seed%3)-1;}
CCharacter*master(CSkill*p){ev(20,p);return seed&32?chars[0]:NULL;}
CCharacter*owner(CSkill*p){ev(21,p);return seed&16?chars[1]:NULL;}
int target(CSkill*p){ev(22,p);const int a[]={0,1,2,11};return a[seed/4%4];}
void*right(CCharacter*p){ev(23,p);if(seed&128)self->m_ownerCharacter.setObject(NULL);return seed&2?weapons[0]:NULL;}
void*left(CCharacter*p){ev(24,p);return seed&4?weapons[1]:NULL;}
int minimum(CEquipment*p){ev(25,p);return seed&64?-7:13+id(p);}
int maximum(CEquipment*p){ev(26,p);return seed&64?-3:19+id(p);}
void minMax(CSkillEffectAndAffixes*p,CResourceManager*r,unsigned effect,float&lo,float&hi){ev(27,p);number(r==reinterpret_cast<CResourceManager*>(owned[7]));number(effect);lo+=0.25f;hi-=0.5f;}
Ogre::Vector3 bone(CSkillEvent*p,CBaseUnit*u,ESKILL_BONE_ATTACHMENT b,bool absolute){ev(28,p);number(id(u));number(b);number(absolute);return Ogre::Vector3(-1,2.5f,3.75f);}
void side(Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;new(reinterpret_cast<void*>(0x14f0ca0))std::string();
 skill=static_cast<CSkill*>(object(sizeof(CSkill)));for(unsigned i=0;i<2;++i)weapons[i]=static_cast<CEquipment*>(object(sizeof(CEquipment)));
 self=static_cast<CSkillEvent*>(Ogre::GeneralAllocPolicy::allocateBytes(sizeof(CSkillEvent)));soCtor(self,NULL,NULL,NULL,NULL);
 void*ownedVT[16];std::memset(ownedVT,0,sizeof(ownedVT));ownedVT[1]=reinterpret_cast<void*>(&ownedDtor);ownedVT[0x50/8]=reinterpret_cast<void*>(&visible);
 for(unsigned i=0;i<8;++i){owned[i]=object(0x400);*reinterpret_cast<void***>(owned[i])=ownedVT;}
 scene=static_cast<CEditorScene*>(owned[7]);self->m_pEditorScene=seed&1?scene:NULL;
 void*characterVT[150];std::memcpy(characterVT,soCharacterTable,sizeof(characterVT));characterVT[2+0x318/8]=reinterpret_cast<void*>(&setLevel);characterVT[2+0x1e0/8]=reinterpret_cast<void*>(&unitModel);characterVT[2+0x310/8]=reinterpret_cast<void*>(&updateAnimation);
 model=static_cast<CGenericModel*>(object(sizeof(CGenericModel)));model->m_animationSpeed=-0.25f;
 for(unsigned i=0;i<2;++i){chars[i]=static_cast<CCharacter*>(object(sizeof(CCharacter)));soCoreCtor(chars[i]);*reinterpret_cast<void***>(chars[i])=characterVT+2;chars[i]->m_iUnitLevel=71+i;missiles[i]=static_cast<CMissile*>(object(sizeof(CMissile)));soCoreCtor(missiles[i]);*reinterpret_cast<void***>(missiles[i])=soMissileTable+2;new(&missiles[i]->m_Listeners)TArrayList<iMissile*>(2);missiles[i]->m_pRunicCore=NULL;missiles[i]->m_iUnknown228=-1;}
 self->m_ownerCharacter.setObject(seed&2?chars[0]:NULL);self->m_caster.setObject(seed&4?chars[1]:NULL);self->m_target.setObject(seed&8?chars[0]:NULL);self->m_skillTarget.setObject(seed&16?chars[1]:NULL);self->m_pause.m_target.setObject(seed&32?chars[0]:NULL);
 Ogre::SceneNode nativeNode(NULL);for(unsigned i=0;i<2;++i){missiles[i]->m_pSceneNode=&nativeNode;chars[i]->m_pSceneNode=&nativeNode;}
 self->m_active=self->m_started=self->m_effectApplied=self->m_hitSkillInvoked=true;self->m_pSkillProperty=reinterpret_cast<CSkillProperty*>(owned[6]);
 TSafePointer<CMissile>*handles[5];unsigned count=seed%4;for(unsigned i=0;i<count;++i){handles[i]=new(Ogre::GeneralAllocPolicy::allocateBytes(sizeof(TSafePointer<CMissile>)))TSafePointer<CMissile>;handles[i]->setObject(seed&64?NULL:missiles[i%2]);self->m_missiles.add(handles[i]);missiles[i%2]->m_Listeners.add(static_cast<iMissile*>(self));}
 TArrayList<CEditorBaseObject*> shapeObjects(2),spawnerObjects(2);shapeList=&shapeObjects;spawnerList=&spawnerObjects;
 for(unsigned i=0;i<2;++i){shapes[i]=static_cast<CDamageShape*>(object(sizeof(CDamageShape)));*reinterpret_cast<void***>(shapes[i])=soDamageTable+2;new(&shapes[i]->m_damageListeners)TArrayList<iDamageShape*>(1);spawners[i]=static_cast<CUnitSpawner*>(object(sizeof(CUnitSpawner)));*reinterpret_cast<void***>(spawners[i])=soSpawnerTable+2;new(&spawners[i]->m_spawnListeners)TArrayList<iUnitSpawner*>(1);if(seed&(1u<<(i+5))){shapes[i]->m_damageListeners.add(static_cast<iDamageShape*>(self));spawners[i]->m_spawnListeners.add(static_cast<iUnitSpawner*>(self));}if(i<seed%3){shapeObjects.add(shapes[i]);spawnerObjects.add(spawners[i]);}}
 if(seed&128){shapeObjects.add(NULL);spawnerObjects.add(NULL);}if(seed&256){shapeObjects.add(chars[0]);spawnerObjects.add(chars[0]);}
 if(c.op==1){self->m_pathToTarget=seed&2?static_cast<CPathController*>(owned[0]):NULL;self->m_pSkillEffectAndAffixes=seed&4?reinterpret_cast<CSkillEffectAndAffixes*>(owned[1]):NULL;self->m_pRandomizer=seed&8?static_cast<CRandomizer*>(owned[2]):NULL;for(unsigned i=0;i<seed%3;++i){self->m_particleWrappers.add(static_cast<CSkillEvent::CLineEmitterWrapper*>(owned[3+i]));self->m_executeSkills.add(static_cast<CExecuteSkillProps*>(owned[5+i]));}self->m_specificUnits.add(reinterpret_cast<CDataGroup*>(owned[6]));self->m_pSkill=reinterpret_cast<CSkill*>(owned[7]);}
 self->m_targetCorpses=seed&2;self->m_maxUnitsHit=int(seed%5)-2;self->m_firstDamageShape=seed&4?shapes[1]:NULL;
 self->m_makePet=seed&4;self->m_matchPetDuration=seed&8;self->m_syncPetsToOwner=seed&128;
 if(c.op>=4)self->m_pSkill=seed&8?skill:NULL;
 if(c.op==6&&seed%5==0)self->m_pSkill=NULL;
 if(c.op==7){self->m_pSkill=skill;self->m_pSkillProperty=seed&16?reinterpret_cast<CSkillProperty*>(owned[6]):NULL;if(self->m_pSkillProperty){self->m_pSkillProperty->m_bDuelWeaponRequired=seed&4;self->m_pSkillProperty->m_bHasAnimation=seed&8;}self->m_pSkillEffectAndAffixes=seed&1?reinterpret_cast<CSkillEffectAndAffixes*>(owned[0]):NULL;const float scales[]={-1,0,0.25f,1.5f,bits(0x7fc00001)};self->m_weaponDamageScale=scales[seed/3%5];}
 if(c.op==8){self->m_pSkill=seed%7==0?NULL:skill;skill->m_Target.m_pObject=seed&2?chars[0]:NULL;self->m_missileTargetSelf=seed&1;if(self->m_missileTargetSelf)self->m_pSkill=skill;self->m_targetOffset=Ogre::Vector3(7,8,9);}
 self->m_eventType=static_cast<ESKILL_EVENT_TYPE>(seed%11);
 TSafePointer<CSkillEvent>witness;witness.setObject(self);int live=g_iTotalCountOfObjects;
 if(c.op<2){typedef void(*Fn)(CSkillEvent*);Fn fn=c.op==0?(ours?soNewReset:soOldReset):(ours?soNewDtor:soOldDtor);if(!autotest::beginInvocation(out,fn))return;fn(self);}
 if(c.op==2){typedef void(*Fn)(CSkillEvent*);Fn fn=ours?soNewListeners:soOldListeners;if(!autotest::beginInvocation(out,fn))return;fn(self);}
 if(c.op==3){typedef void(*Fn)(CSkillEvent*,CUnitSpawner*,CPositionableObject*);Fn fn=ours?soNewSpawn:soOldSpawn;CPositionableObject*unit=seed%5==0?NULL:seed&1?static_cast<CPositionableObject*>(missiles[0]):static_cast<CPositionableObject*>(chars[1]);if(!autotest::beginInvocation(out,fn))return;fn(self,spawners[0],unit);}
 if(c.op==4||c.op==5){typedef void(*Fn)(CSkillEvent*,CMissile*);Fn fn=c.op==4?(ours?soNewFired:soOldFired):(ours?soNewDieing:soOldDieing);if(!autotest::beginInvocation(out,fn))return;fn(self,missiles[0]);}
 if(c.op==6){typedef void(*Fn)(CSkillEvent*,CCharacter*);Fn fn=ours?soNewInvoke:soOldInvoke;if(!autotest::beginInvocation(out,fn))return;fn(self,seed%5==0?NULL:chars[0]);}
 if(c.op==7){typedef void(*Fn)(CSkillEvent*,CResourceManager*,unsigned,float&,float&);Fn fn=ours?soNewMinMax:soOldMinMax;float lo=-1.25f,hi=3.75f;if(!autotest::beginInvocation(out,fn))return;fn(self,reinterpret_cast<CResourceManager*>(owned[7]),seed%145,lo,hi);floating(lo);floating(hi);}
 if(c.op==8){typedef CPositionableObject*(*Fn)(CSkillEvent*,CMissile*,CPositionableObject*,Ogre::Vector3&);Fn fn=ours?soNewValidate:soOldValidate;Ogre::Vector3 v(-4,-5,-6);if(!autotest::beginInvocation(out,fn))return;number(id(fn(self,missiles[0],chars[1],v)));vector(v);number(missiles[0]->m_bUnknown144);}
 if(c.op==4)handles[count++]=self->m_missiles[self->m_missiles.size()-1];
 out.callCompleted=1;number(g_iTotalCountOfObjects-live);number(witness.getObject()!=NULL);number(self->m_active);number(self->m_started);number(self->m_effectApplied);number(self->m_hitSkillInvoked);number(id(self->m_ownerCharacter.getObject()));number(id(self->m_caster.getObject()));number(id(self->m_target.getObject()));number(id(self->m_skillTarget.getObject()));number(self->m_pSkillProperty==NULL);number(self->m_missiles.size());for(unsigned i=0;i<self->m_missiles.size();++i){number(id(self->m_missiles[i]->getObject()));number(self->m_missiles[i]->m_nIndex);}
 number(id(self->m_firstDamageShape));number(self->m_spawners.size());floating(self->m_remainingTime);
 for(unsigned i=0;i<2;++i){number(shapes[i]->m_bTargetOnlyDead);number(shapes[i]->m_iTotalNumberOfTargets);number(shapes[i]->m_damageListeners.size());number(spawners[i]->m_spawnListeners.size());number(missiles[i]->m_Listeners.size());number(id(missiles[i]->m_pRunicCore));number(missiles[i]->m_iUnknown228);}
 for(unsigned actor=0;actor<4;++actor){CRunicCore*core=actor<2?static_cast<CRunicCore*>(chars[actor]):static_cast<CRunicCore*>(missiles[actor-2]);TArrayList<TSafePointer<void*>*>*refs=core->m_pSafePointers;number(refs!=NULL);if(refs){number(refs->size());for(unsigned i=0;i<refs->size();++i){TSafePointer<void*>*ref=(*refs)[i];unsigned identity=9000;if(!ref)identity=0;else if(reinterpret_cast<char*>(ref)>=reinterpret_cast<char*>(self)&&reinterpret_cast<char*>(ref)<reinterpret_cast<char*>(self)+sizeof(CSkillEvent))identity=1000+reinterpret_cast<char*>(ref)-reinterpret_cast<char*>(self);else for(unsigned j=0;j<count;++j)if(ref==reinterpret_cast<TSafePointer<void*>*>(handles[j]))identity=2000+j;number(identity);if(ref){number(id(ref->getObject()));number(ref->m_nIndex);}}}}
 for(unsigned i=0;i<count;++i){if(c.op==5&&self->m_missiles.find(handles[i])==-1)continue;handles[i]->~TSafePointer<CMissile>();Ogre::GeneralAllocPolicy::deallocateBytes(handles[i]);}
 if(c.op!=1){self->m_missiles.clear();self->m_pEditorScene=NULL;self->m_pSkillProperty=NULL;self->m_pSkillEffectAndAffixes=NULL;soOldDtor(self);}Ogre::GeneralAllocPolicy::deallocateBytes(self);
 for(unsigned i=0;i<2;++i){shapes[i]->m_damageListeners.~TArrayList<iDamageShape*>();spawners[i]->m_spawnListeners.~TArrayList<iUnitSpawner*>();missiles[i]->m_Listeners.~TArrayList<iMissile*>();if(missiles[i]->m_pRunicCore)missiles[i]->m_pRunicCore->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&missiles[i]->m_pRunicCore),missiles[i]->m_iUnknown228);soCoreDtor(missiles[i]);soCoreDtor(chars[i]);}
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned cases){detour::Set h;TL_REDIRECT(h,soObjects,&objects);TL_REDIRECT(h,soAlignment,&alignment);TL_REDIRECT(h,soSetAlignment,&setAlignment);TL_REDIRECT(h,soAddPet,&addPet);TL_REDIRECT(h,soPlaying,&playing);TL_REDIRECT(h,soName,&getName);TL_REDIRECT(h,soTime,&animTime);TL_REDIRECT(h,soIndex,&index);TL_REDIRECT(h,soAIAnimation,&aiAnimation);TL_REDIRECT(h,soEffect,&effect);TL_REDIRECT(h,soApply,&apply);TL_REDIRECT(h,soPosition,&position);TL_REDIRECT(h,soTrigger,&trigger);TL_REDIRECT(h,soHP,&hp);TL_REDIRECT(h,soMaster,&master);TL_REDIRECT(h,soOwner,&owner);TL_REDIRECT(h,soTarget,&target);TL_REDIRECT(h,soRight,&right);TL_REDIRECT(h,soLeft,&left);TL_REDIRECT(h,soMinimum,&minimum);TL_REDIRECT(h,soMaximum,&maximum);TL_REDIRECT(h,soMinMax,&minMax);TL_REDIRECT(h,soBone,&bone);if(h.failed())return 1;return smallmass::run(host,op,name,address,&side,cases);}
}
TL_TEST(complete_event_full_reset){return run(host,0,"complete_event_full_reset",0xcc1100,256);}
TL_TEST(complete_event_destructor){return run(host,1,"complete_event_destructor",0xcc16b0,256);}
TL_TEST(complete_event_listeners){return run(host,2,"complete_event_listeners",0xcc3aa0,512);}
TL_TEST(complete_event_spawned){return run(host,3,"complete_event_spawned",0xcc12e0,512);}

TL_TEST(complete_event_missile_fired){return run(host,4,"complete_event_missile_fired",0xcc0ce0,256);}
TL_TEST(complete_event_missile_dieing){return run(host,5,"complete_event_missile_dieing",0xcb7670,256);}
TL_TEST(complete_event_invoke_hit){return run(host,6,"complete_event_invoke_hit",0xcb7290,128);}
TL_TEST(complete_event_min_max){return run(host,7,"complete_event_min_max",0xcb6fc0,512);}
TL_TEST(complete_event_validate_target){return run(host,8,"complete_event_validate_target",0xcb8b20,256);}
