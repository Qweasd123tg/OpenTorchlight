#include "SmallMassCompare.h"
TL_ORIGINAL(void, original0, (void*,float,void*), "_ZN8CMonster6fleeAIEfR6CLevel")
extern "C" void candidate0(void*,float,void*) __asm__("_ZN8CMonster6fleeAIEfR6CLevel");
TL_ORIGINAL(bool, original1, (void*,float,void*,bool), "_ZN8CMonster20idleAIRangedDefenderEfR6CLevelb")
extern "C" bool candidate1(void*,float,void*,bool) __asm__("_ZN8CMonster20idleAIRangedDefenderEfR6CLevelb");
TL_ORIGINAL(bool, original2, (void*,float,void*,bool), "_ZN8CMonster18idleAIRangedCasterEfR6CLevelb")
extern "C" bool candidate2(void*,float,void*,bool) __asm__("_ZN8CMonster18idleAIRangedCasterEfR6CLevelb");
TL_ORIGINAL(void, original3, (void*,float,void*), "_ZN8CMonster10jumpDownAIEfR6CLevel")
extern "C" void candidate3(void*,float,void*) __asm__("_ZN8CMonster10jumpDownAIEfR6CLevel");
TL_ORIGINAL(bool, original4, (void*,float,void*,bool), "_ZN8CMonster12idleAINormalEfR6CLevelb")
extern "C" bool candidate4(void*,float,void*,bool) __asm__("_ZN8CMonster12idleAINormalEfR6CLevelb");
TL_ORIGINAL(bool, original5, (void*,float,void*,bool), "_ZN8CMonster13idleAICirclerEfR6CLevelb")
extern "C" bool candidate5(void*,float,void*,bool) __asm__("_ZN8CMonster13idleAICirclerEfR6CLevelb");
TL_FUNCTION(dep_target, "_ZN10CCharacter9setTargetEPS_")
TL_FUNCTION(dep_roll, "_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(dep_random, "_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(dep_nearDeath, "_ZN10CCharacter14isPetNearDeathEv")
TL_FUNCTION(dep_hasEffect, "_ZN9CBaseUnit9hasEffectE12EEFFECT_TYPE")
TL_FUNCTION(dep_defensive, "_ZN8CMonster20selectDefensiveSkillEv")
TL_FUNCTION(dep_canCast, "_ZN10CCharacter19canCastCurrentSkillEP9CBaseUnitbb")
TL_FUNCTION(dep_cast, "_ZN10CCharacter9castSkillEx")
TL_FUNCTION(dep_isa, "_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(dep_position, "_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(dep_destination, "_ZN10CCharacter14setDestinationER6CLevelff")
TL_FUNCTION(dep_alignment, "_ZN10CCharacter9alignmentEv")
TL_FUNCTION(dep_master, "_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(dep_getInt, "_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(dep_attached, "_ZN10CCharacter16attachesToMasterEv")
TL_FUNCTION(dep_findTarget, "_ZN10CCharacter22calculateTargetInSightE10EAlignmentb")
TL_FUNCTION(dep_hasDefensive, "_ZN8CMonster17hasDefensiveSkillEv")
TL_FUNCTION(dep_offensive, "_ZN8CMonster20selectOffensiveSkillEb")
TL_FUNCTION(dep_inRange, "_ZN10CCharacter13inAttackRangeE18EATTACK_RANGE_TYPE")
TL_FUNCTION(dep_stop, "_ZN10CCharacter11stopPathingEv")
TL_FUNCTION(dep_sound, "_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(dep_point, "_ZN5CPath8GetPointEj")
TL_FUNCTION(dep_turn, "_ZN10CCharacter18turnTowardPositionERKN4Ogre7Vector3Ef")
TL_FUNCTION(dep_animationLength, "_ZNK13CGenericModel25getAnimationLengthSecondsERKSs")
TL_FUNCTION(dep_animationTime, "_ZN13CGenericModel16setAnimationTimeEf")
TL_FUNCTION(dep_playing, "_ZNK13CGenericModel25animationPlayingSubstringERKSs")
TL_FUNCTION(dep_blend, "_ZN10CCharacter19queueBlendAnimationERKSsbff")
TL_FUNCTION(dep_spline, "_ZN5CPath27GetSplinePositionAtDistanceEf")
TL_FUNCTION(dep_setPosition, "_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(dep_enemy, "_ZN10CCharacter7isEnemyEPS_")

namespace {
using namespace smallmass;
void *self,*services,*victim,*masterObject,*skill;unsigned rolls,randoms;
void target(void* p,void* value){event(1,p);pointer(value);field<void*>(p,0x340)=value;}
int roll(int low,int high){number(2);number(low);number(high);const int values[]={0,9,10,19,20,24,34,35,74,75,100};return values[(input->index/2+rolls++*3)%11];}
float random(float low,float high){number(3);floating(low);floating(high);++randoms;return low+(high-low)*float((input->index+randoms)%5)*.25f;}
bool nearDeath(void* p){event(4,p);return input->index%19==0;}
bool hasEffect(void* p,int type){event(5,p);number(type);return input->index&32;}
void defensive(void* p){event(6,p);field<void*>(p,0x398)=input->index%5?skill:0;}
bool canCast(void* p,void* target,bool a,bool b){event(7,p);pointer(target);number(a);number(b);return input->index&8;}
bool cast(void* p,long long guid){event(8,p);output->add(&guid,8);return input->index&128;}
bool isa(void* p,int type){event(9,p);number(type);return input->index&64;}
Ogre::Vector3 position(void* p,bool absolute){event(10,p);number(absolute);return field<Ogre::Vector3>(p,0x84)+(absolute?Ogre::Vector3(0,0,0):Ogre::Vector3(1,2,3));}
void destination(void* p,void* level,float x,float z){event(11,p);pointer(level);floating(x);floating(z);field<float>(p,0x250)=x;field<float>(p,0x254)=z;}
int alignment(void* p){event(12,p);return input->index%17?1:0;}
void* master(){number(13);return services;}
int getInt(void* p,unsigned key){event(14,p);number(key);return input->index%23==0?1:0;}
bool attached(void* p){event(15,p);return input->index&2;}
void* findTarget(void* p,int alignment,bool flag){event(16,p);number(alignment);number(flag);return input->index%7?victim:0;}
bool hasDefensive(void* p){event(17,p);return input->index&2;}
void offensive(void* p,bool force){event(18,p);number(force);field<void*>(p,0x398)=input->index%3?skill:0;}
bool inRange(void* p,int type){event(19,p);number(type);return input->index&16;}
void stop(void* p){event(20,p);field<bool>(p,0x264)=false;}
void sound(void* p,int id,void* node,float a,float b,bool flag){event(21,p);number(id);pointer(node);floating(a);floating(b);number(flag);}
Ogre::Vector3 point(void* p,unsigned index){event(22,p);number(index);return Ogre::Vector3(float(index)*3,4,float(index)*-2);}
void turn(void* p,const Ogre::Vector3& value,float elapsed){event(23,p);vector(value);floating(elapsed);if(input->index%11==0)field<float>(p,0x678)+=.25f;}
float animationLength(void* p,const std::string& name){event(24,p);text(name);return 2.5f;}
void animationTime(void* p,float time){event(25,p);floating(time);}
bool playing(void* p,const std::string& name){event(26,p);text(name);return input->index&8;}
void blend(void* p,const std::string& name,bool loop,float blend,float speed){event(27,p);text(name);number(loop);floating(blend);floating(speed);}
Ogre::Vector3 spline(void* p,float distance){event(28,p);floating(distance);return Ogre::Vector3(distance,.5f*distance,-distance);}
void setPosition(void* p,const Ogre::Vector3& value){event(29,p);vector(value);vector(field<Ogre::Vector3>(p,0x84));field<Ogre::Vector3>(p,0x84)=value;}
bool enemy(void* p,void* target){event(30,p);pointer(target);return input->index%3!=0;}
void state(void* p,int state){event(31,p);number(state);field<int>(p,0x330)=state;}
bool canAttack(void* p){event(32,p);return input->index&4;}
void update(void* p,float elapsed,bool force){event(33,p);floating(elapsed);number(force);}
void execute(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;rolls=randoms=0;self=object(0x7f8);services=object(0x140);victim=object(0x778);masterObject=object(0x778);skill=object(0x180);
 void* level=object(0x2f0);void* client=object(0x3910);void* resources=object(0x48);void* model=object(0x258);void* path=object(0xd0);void* settings=object(0x120);
 void** table=static_cast<void**>(object(0x430));table[0x348/8]=reinterpret_cast<void*>(&state);table[0x358/8]=reinterpret_cast<void*>(&update);table[0x3f8/8]=reinterpret_cast<void*>(&canAttack);field<void*>(self,0)=table;
 field<void*>(self,0x68)=(c.op==1||c.op==2||c.op==5)&&c.index%29==0?0:resources;field<void*>(resources,0x18)=level;field<void*>(level,0x220)=client;field<int>(client,0x38d0)=c.index%13?1:0;field<void*>(services,0x90)=settings;
 field<void*>(self,0x58)=object(0x100);field<void*>(self,0x200)=model;field<void*>(self,0x298)=c.index&32?services:0;
 field<void*>(self,0x640)=c.index&1?masterObject:0;field<void*>(self,0x340)=victim;field<void*>(self,0x398)=c.index&128?skill:0;
 field<bool>(self,0x321)=true;field<bool>(self,0x264)=c.index%4==0;field<int>(self,0x330)=2;field<int>(self,0x710)=(c.index/2)%3;
 field<Ogre::Vector3>(self,0x84)=Ogre::Vector3(1,2,3);const float distances[]={0,34.999f,35,35.001f,60,bits(0x7fc00000)};field<Ogre::Vector3>(victim,0x84)=Ogre::Vector3(distances[(c.index/4)%6],100,0);field<Ogre::Vector3>(masterObject,0x84)=Ogre::Vector3(0,-100,0);
 field<void*>(self,0x670)=path;field<float>(path,0x18)=c.index%9==0?0:4;const float previous[]={-1,0,1.99f,2,3.9f,4,5,bits(0x7fc00000)};field<float>(self,0x678)=previous[c.index%8];field<float>(self,0x67c)=float((c.index/8)%5)-1;field<bool>(self,0x680)=true;
 detour::Set patches;
 TL_REDIRECT(patches,dep_target,&target);
 TL_REDIRECT(patches,dep_roll,&roll);
 TL_REDIRECT(patches,dep_random,&random);
 TL_REDIRECT(patches,dep_nearDeath,&nearDeath);
 TL_REDIRECT(patches,dep_hasEffect,&hasEffect);
 TL_REDIRECT(patches,dep_defensive,&defensive);
 TL_REDIRECT(patches,dep_canCast,&canCast);
 TL_REDIRECT(patches,dep_cast,&cast);
 TL_REDIRECT(patches,dep_isa,&isa);
 TL_REDIRECT(patches,dep_position,&position);
 TL_REDIRECT(patches,dep_destination,&destination);
 TL_REDIRECT(patches,dep_alignment,&alignment);
 TL_REDIRECT(patches,dep_master,&master);
 TL_REDIRECT(patches,dep_getInt,&getInt);
 TL_REDIRECT(patches,dep_attached,&attached);
 TL_REDIRECT(patches,dep_findTarget,&findTarget);
 TL_REDIRECT(patches,dep_hasDefensive,&hasDefensive);
 TL_REDIRECT(patches,dep_offensive,&offensive);
 TL_REDIRECT(patches,dep_inRange,&inRange);
 TL_REDIRECT(patches,dep_stop,&stop);
 TL_REDIRECT(patches,dep_sound,&sound);
 TL_REDIRECT(patches,dep_point,&point);
 TL_REDIRECT(patches,dep_turn,&turn);
 TL_REDIRECT(patches,dep_animationLength,&animationLength);
 TL_REDIRECT(patches,dep_animationTime,&animationTime);
 TL_REDIRECT(patches,dep_playing,&playing);
 TL_REDIRECT(patches,dep_blend,&blend);
 TL_REDIRECT(patches,dep_spline,&spline);
 TL_REDIRECT(patches,dep_setPosition,&setPosition);
 TL_REDIRECT(patches,dep_enemy,&enemy);

 if(patches.failed())_exit(41);
 float elapsed=float((c.index/7)%5)*.25f;
 switch(c.op){
 case 0:autotest::invoke(out,ours?candidate0:original0,self,elapsed,level);break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self,elapsed,level,bool(c.index&1));break;
 case 2:autotest::invoke(out,ours?candidate2:original2,self,elapsed,level,bool(c.index&1));break;
 case 3:autotest::invoke(out,ours?candidate3:original3,self,elapsed,level);break;
 case 4:autotest::invoke(out,ours?candidate4:original4,self,elapsed,level,bool(c.index&1));break;
 case 5:autotest::invoke(out,ours?candidate5:original5,self,elapsed,level,bool(c.index&1));break;
 }
 number(rolls);number(randoms);number(field<bool>(self,0x321));number(field<bool>(self,0x264));number(field<int>(self,0x330));pointer(field<void*>(self,0x340));pointer(field<void*>(self,0x398));floating(field<float>(self,0x250));floating(field<float>(self,0x254));floating(field<float>(self,0x678));number(field<bool>(self,0x680));vector(field<Ogre::Vector3>(self,0x84));
}
}
TL_TEST(mass3_8d59a0) { return smallmass::run(host,0,"mass3_8d59a0",(uint64_t)(uintptr_t)original0,execute,384); }
TL_TEST(mass3_8e0eb0) { return smallmass::run(host,1,"mass3_8e0eb0",(uint64_t)(uintptr_t)original1,execute,512); }
TL_TEST(mass3_8e0b90) { return smallmass::run(host,2,"mass3_8e0b90",(uint64_t)(uintptr_t)original2,execute,512); }
TL_TEST(mass3_8e1580) { return smallmass::run(host,3,"mass3_8e1580",(uint64_t)(uintptr_t)original3,execute,256); }
TL_TEST(mass3_8e02b0) { return smallmass::run(host,4,"mass3_8e02b0",(uint64_t)(uintptr_t)original4,execute,512); }
TL_TEST(mass3_8e06e0) { return smallmass::run(host,5,"mass3_8e06e0",(uint64_t)(uintptr_t)original5,execute,512); }
