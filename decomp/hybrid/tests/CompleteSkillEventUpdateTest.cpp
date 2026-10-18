#include <cstring>
#include <map>
#include <string>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "SkillEvent.h"
#include "SkillProperty.h"
#include "PathController.h"
#include "Level.h"
#undef protected
#undef private
TL_ORIGINAL(bool,suOld,(CSkillEvent*,float),"_ZN11CSkillEvent11updateEventEf")
extern "C" bool suNew(CSkillEvent*,float) __asm__("_ZN11CSkillEvent11updateEventEf");
TL_ORIGINAL(void,suCtor,(CSkillEvent*,CSkill*,CSkillProperty*,CResourceManager*,CDataGroup*),"_ZN11CSkillEventC1EP6CSkillP14CSkillPropertyP16CResourceManagerP10CDataGroup")
TL_ORIGINAL(void,suDtor,(CSkillEvent*),"_ZN11CSkillEventD1Ev")
TL_ORIGINAL(void,suCoreCtor,(CRunicCore*),"_ZN10CRunicCoreC1Ev")
TL_ORIGINAL(void,suCoreDtor,(CRunicCore*),"_ZN10CRunicCoreD1Ev")
TL_FUNCTION(suStart,"_ZN11CSkillEvent10startEventEP9CBaseUnitP14CSkillPropertyN4Ogre7Vector3ERKNS4_10QuaternionES1_PKS5_")
TL_FUNCTION(suCanStop,"_ZN11CSkillEvent7canStopEv")
TL_FUNCTION(suShouldStop,"_ZN11CSkillEvent10shouldStopEv")
TL_FUNCTION(suOwner,"_ZN14CSkillProperty17getOwnerCharacterEv")
TL_FUNCTION(suPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(suSetPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(suBone,"_ZN11CSkillEvent15getBonePositionEP9CBaseUnit22ESKILL_BONE_ATTACHMENTb")
TL_FUNCTION(suRange,"_ZN6CSkill8getRangeEv")
TL_FUNCTION(suRay,"_ZN6CLevel12rayCollisionERKN4Ogre7Vector3ES3_RS1_S4_b")
TL_FUNCTION(suTimelines,"_ZN12CEditorScene28getNumberOfTimelinesUpdatingEb")
TL_FUNCTION(suStopParticles,"_ZN11CSkillEvent16stopAllParticlesEb")
TL_FUNCTION(suTarget,"_ZN6CSkill13getTargetTypeEv")
TL_FUNCTION(suMove,"_ZN10CCharacter14moveToPositionERKN4Ogre7Vector3Ebb")
TL_FUNCTION(suStopEvent,"_ZN11CSkillEvent9stopEventEv")
TL_FUNCTION(suApply,"_ZN11CSkillEvent12applyEffectsEP9CBaseUnitPKN4Ogre7Vector3Eb")
TL_FUNCTION(suDisable,"_ZN11CSkillEvent22disableAllDamageShapesEv")
TL_FUNCTION(suEnd,"_ZN16ParticleUniverse11LineEmitter6setEndERKN4Ogre7Vector3E")
extern "C" void*suCharacterTable[] __asm__("_ZTV10CCharacter");
namespace {
using namespace smallmass;
CSkillEvent*self;CSkill*skill;CSkillProperty*property;CEditorScene*scene;CCharacter*chars[2];CPathController*path;CResourceManager*resources;CLevel*level;CPositionableObject*particle;ParticleUniverse::LineEmitter*emitter;CDamageShape*shape;unsigned seed;bool updated;Ogre::Matrix4 matrix;
int id(const void*p){if(!p)return -1;if(p==self)return 0;if(p==skill)return 1;if(p==property)return 2;if(p==scene)return 3;if(p==path)return 4;if(p==resources)return 5;if(p==level)return 6;if(p==particle)return 7;if(p==emitter)return 8;if(p==shape)return 9;for(unsigned i=0;i<2;++i)if(p==chars[i])return 10+i;return -2;}
void ev(unsigned tag,const void*p){number(tag);number(id(p));}
bool start(CSkillEvent*p,CBaseUnit*c,CSkillProperty*pr,Ogre::Vector3 v,const Ogre::Quaternion&q,CBaseUnit*t,const Ogre::Vector3*to){ev(1,p);number(id(c));number(id(pr));vector(v);output->add(&q,sizeof(q));number(id(t));number(to!=NULL);if(to)vector(*to);p->m_pause.m_paused=false;return seed&64;}
bool canStop(CSkillEvent*p){ev(2,p);return seed&4;}
bool shouldStop(CSkillEvent*p){ev(3,p);return seed&16;}
CCharacter*owner(CSkillProperty*p){ev(4,p);return seed%17 || self->m_attachToTarget || ((self->m_attachLineEmitter || self->m_attachLineToMaxDistance) && self->m_particleWrappers.size())?chars[0]:NULL;}
Ogre::Vector3 position(CPositionableObject*p,bool absolute){ev(5,p);number(absolute);return Ogre::Vector3(float(id(p))*0.25f,-0.75f,float(id(p))*-0.5f);}
void setPosition(CPositionableObject*p,const Ogre::Vector3&v){ev(6,p);vector(v);}
void setPosition3(CPositionableObject*p,float x,float y,float z){ev(7,p);floating(x);floating(y);floating(z);}
Ogre::Vector3 bone(CSkillEvent*p,CBaseUnit*u,ESKILL_BONE_ATTACHMENT b,bool absolute){ev(8,p);number(id(u));number(b);number(absolute);return Ogre::Vector3(1.25f,-0.5f,2.5f);}
float range(CSkill*p){ev(9,p);return -3.25f;}
bool ray(CLevel*p,const Ogre::Vector3&a,const Ogre::Vector3&b,Ogre::Vector3&hit,Ogre::Vector3&normal,bool flag){ev(10,p);vector(a);vector(b);number(flag);hit=Ogre::Vector3(2,-1,4);normal=Ogre::Vector3(-0.75f,0.5f,0.25f);return seed&64;}
unsigned timelines(CEditorScene*p,bool exclude){ev(11,p);number(exclude);return updated&&seed&128?0:seed/7%3;}
void update(CEditorScene*p,float dt){ev(12,p);floating(dt);updated=true;}
void stopParticles(CSkillEvent*p,bool now){ev(13,p);number(now);}
int target(CSkill*p){ev(14,p);return seed&256?1:2;}
bool move(CCharacter*p,const Ogre::Vector3&v,bool units,bool obstructions){ev(15,p);vector(v);number(units);number(obstructions);return seed&512;}
void stopEvent(CSkillEvent*p){ev(16,p);p->m_active=false;}
bool apply(CSkillEvent*p,CBaseUnit*u,const Ogre::Vector3*v,bool f){ev(17,p);number(id(u));number(v!=NULL);number(f);return false;}
void disable(CSkillEvent*p){ev(18,p);}
void setPath(CCharacter*p,CPathController*path){ev(19,p);number(id(path));}
void setEnd(ParticleUniverse::LineEmitter*p,const Ogre::Vector3&v){ev(20,p);vector(v);}
const Ogre::Matrix4&orientation(CPositionableObject*p){ev(21,p);return matrix;}
Ogre::Quaternion orientationQ(CPositionableObject*p){ev(22,p);return Ogre::Quaternion(0.5f,0.25f,-0.125f,0.75f);}
void setOrientationQ(CPositionableObject*p,const Ogre::Quaternion&q){ev(23,p);output->add(&q,sizeof(q));}
void setOrientationM(CPositionableObject*p,const Ogre::Matrix4&m,bool translated){ev(24,p);output->add(&m,sizeof(m));number(translated);}
const Ogre::Vector3&forward(CPositionableObject*p){ev(25,p);static Ogre::Vector3 v(0.5f,0.25f,-0.75f);return v;}
void pathPosition(CPathController*p,const Ogre::Vector3&v){ev(26,p);vector(v);}
void side(Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;updated=false;
 self=static_cast<CSkillEvent*>(Ogre::GeneralAllocPolicy::allocateBytes(sizeof(CSkillEvent)));suCtor(self,NULL,NULL,NULL,NULL);skill=static_cast<CSkill*>(object(sizeof(CSkill)));property=static_cast<CSkillProperty*>(object(sizeof(CSkillProperty)));scene=static_cast<CEditorScene*>(object(sizeof(CEditorScene)));path=static_cast<CPathController*>(object(sizeof(CPathController)));resources=static_cast<CResourceManager*>(object(sizeof(CResourceManager)));level=static_cast<CLevel*>(object(sizeof(CLevel)));particle=static_cast<CPositionableObject*>(object(sizeof(CPositionableObject)));emitter=static_cast<ParticleUniverse::LineEmitter*>(object(8));shape=static_cast<CDamageShape*>(object(0x200));
 void*vt[150];std::memcpy(vt,suCharacterTable,sizeof(vt));vt[2+0xe8/8]=reinterpret_cast<void*>(&orientation);vt[2+0xf0/8]=reinterpret_cast<void*>(&orientationQ);vt[2+0x130/8]=reinterpret_cast<void*>(&forward);vt[2+0x310/8]=reinterpret_cast<void*>(&setPath);
 Ogre::SceneNode node(NULL);
 for(unsigned i=0;i<2;++i){chars[i]=static_cast<CCharacter*>(object(sizeof(CCharacter)));suCoreCtor(chars[i]);*reinterpret_cast<void***>(chars[i])=vt+2;chars[i]->m_pSceneNode=&node;chars[i]->m_fBaseUnitValue194=0.5f;chars[i]->m_returningToTown=seed&128;chars[i]->m_walkingSpeed=1;chars[i]->m_runningSpeed=2;chars[i]->m_pathToFollow.m_pObject=seed&1024?path:NULL;}
 void*sceneVT[80];std::memset(sceneVT,0,sizeof(sceneVT));sceneVT[0x58/8]=reinterpret_cast<void*>(&setPosition3);sceneVT[0xf0/8]=reinterpret_cast<void*>(&orientationQ);sceneVT[0x108/8]=reinterpret_cast<void*>(&setOrientationQ);sceneVT[0x118/8]=reinterpret_cast<void*>(&setOrientationM);sceneVT[0x208/8]=reinterpret_cast<void*>(&update);*reinterpret_cast<void***>(scene)=sceneVT;
 void*pathVT[60];std::memset(pathVT,0,sizeof(pathVT));pathVT[0x1a8/8]=reinterpret_cast<void*>(&pathPosition);*reinterpret_cast<void***>(path)=pathVT;
 matrix=Ogre::Matrix4(1.25f,0.5f,-0.25f,0.75f,0.25f,1.5f,0.5f,-0.5f,0.125f,-0.25f,0.75f,0.375f,0,0,0,1);
 self->m_pSkill=skill;self->m_pSkillProperty=seed%11?property:NULL;self->m_pEditorScene=seed&2?scene:NULL;self->m_pResourceManager=resources;resources->m_pLevel=level;
 self->m_active=seed&1;self->m_skillTarget.setObject(seed&4?chars[1]:NULL);skill->m_Target.m_pObject=seed&8?chars[1]:NULL;skill->m_animationIndexLoopInto=seed&16?static_cast<unsigned>(-1):2;
 const float times[]={-1,0,0.25f,1.5f,bits(0x7fc00001)};self->m_remainingTime=times[seed/3%5];self->m_durationOverride=times[seed/5%5];self->m_targetAheadOfUnit=times[seed/13%5];self->m_attachmentDistance=-0.75f;self->m_direction=Ogre::Vector3(0.5f,0.25f,-0.75f);
 self->m_attaches=seed&32;self->m_attachToTarget=seed&64;self->m_attachLineToMaxDistance=seed&128;self->m_lineEmitterCollides=seed&256;self->m_pathFollowsTarget=seed&512;self->m_pathToTarget=seed&1024?path:NULL;path->m_bUnknown136=seed&256;
 self->m_firstDamageShape=seed&512?shape:NULL;self->m_attachOwner=seed&256;self->m_scaleAttachDistance=seed&128;self->m_attachIgnoresUnits=seed&64;self->m_attachIgnoresObstructions=seed&32;self->m_applyEffectsAlways=seed&8;self->m_attachLineEmitter=seed&16;self->m_fireFromBone=static_cast<ESKILL_BONE_ATTACHMENT>(seed/17%8);self->m_fireAtBone=SKILL_BONE_HEAD;
 CSkillEvent::CLineEmitterWrapper*wrapper=static_cast<CSkillEvent::CLineEmitterWrapper*>(object(sizeof(CSkillEvent::CLineEmitterWrapper)));wrapper->m_object=particle;wrapper->m_emitter=emitter;if(seed&2048)self->m_particleWrappers.add(wrapper);
 self->m_pause.m_paused=seed&4096;self->m_delayRemaining=times[seed/19%5];self->m_pause.m_caster=chars[0];self->m_pause.m_property=property;self->m_pause.m_position=Ogre::Vector3(-3,2,1);self->m_pause.m_orientation=Ogre::Quaternion(0.5f,0.25f,-0.125f,0.75f);self->m_pause.m_targetPosition=seed&32?Ogre::Vector3(0,0,1):Ogre::Vector3::ZERO;
 if(self->m_active&&self->m_pEditorScene){self->m_pSkillProperty=property;}
 typedef bool(*Fn)(CSkillEvent*,float);Fn fn=ours?suNew:suOld;if(!autotest::beginInvocation(out,fn))return;bool result=fn(self,times[seed/23%5]);out.callCompleted=1;number(result);number(self->m_active);number(self->m_pause.m_paused);floating(self->m_delayRemaining);floating(self->m_remainingTime);number(id(self->m_skillTarget.getObject()));
 self->m_pEditorScene=NULL;self->m_pathToTarget=NULL;self->m_particleWrappers.clear();self->m_pSkillProperty=NULL;suDtor(self);Ogre::GeneralAllocPolicy::deallocateBytes(self);for(unsigned i=0;i<2;++i){chars[i]->m_pathToFollow.m_pObject=NULL;suCoreDtor(chars[i]);}
}
int run(const tlhybrid_host*host){detour::Set h;TL_REDIRECT(h,suStart,&start);TL_REDIRECT(h,suCanStop,&canStop);TL_REDIRECT(h,suShouldStop,&shouldStop);TL_REDIRECT(h,suOwner,&owner);TL_REDIRECT(h,suPosition,&position);TL_REDIRECT(h,suSetPosition,&setPosition);TL_REDIRECT(h,suBone,&bone);TL_REDIRECT(h,suRange,&range);TL_REDIRECT(h,suRay,&ray);TL_REDIRECT(h,suTimelines,&timelines);TL_REDIRECT(h,suStopParticles,&stopParticles);TL_REDIRECT(h,suTarget,&target);TL_REDIRECT(h,suMove,&move);TL_REDIRECT(h,suStopEvent,&stopEvent);TL_REDIRECT(h,suApply,&apply);TL_REDIRECT(h,suDisable,&disable);TL_REDIRECT(h,suEnd,&setEnd);if(h.failed())return 1;return smallmass::run(host,0,"complete_event_update",0xcc5c20,&side,8192);}
}
TL_TEST(complete_event_update){return run(host);}
