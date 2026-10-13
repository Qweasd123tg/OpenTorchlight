#include "SmallMassCompare.h"
TL_ORIGINAL(void, original0, (void*,bool,bool), "_ZN10CCharacter10setVisibleEbb")
extern "C" void candidate0(void*,bool,bool) __asm__("_ZN10CCharacter10setVisibleEbb");
TL_ORIGINAL(void, original1, (void*,float,bool), "_ZN10CCharacter13updateOpacityEfb")
extern "C" void candidate1(void*,float,bool) __asm__("_ZN10CCharacter13updateOpacityEfb");
TL_ORIGINAL(void, original2, (void*,bool), "_ZN10CCharacter9interruptEb")
extern "C" void candidate2(void*,bool) __asm__("_ZN10CCharacter9interruptEb");
TL_FUNCTION(dep_theme, "_ZN9CBaseUnit12hasUnitThemeEP10CUnitTheme")
TL_FUNCTION(dep_start, "_ZN9CParticle5StartEv")
TL_FUNCTION(dep_stop, "_ZN9CParticle4StopEb")
TL_FUNCTION(dep_loop, "_ZN9CParticle7loopingEv")
TL_FUNCTION(dep_trailActive, "_ZN12CWeaponTrail9setActiveEb")
TL_FUNCTION(dep_trailVisible, "_ZN12CWeaponTrail10setVisibleEb")
TL_FUNCTION(dep_setPosition, "_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(dep_baseVisible, "_ZN16CSceneNodeObject10setVisibleEb")
TL_FUNCTION(dep_opacity, "_ZN13CGenericModel10setOpacityEf")
TL_FUNCTION(dep_equipped, "_ZN10CInventory22getEquipmentEquippedAtE16EEQUIP_LOCATIONS")
TL_FUNCTION(dep_ai, "_ZN10CAIManager9hasAIFlagE13EAIFLAG_TYPES")
TL_FUNCTION(dep_exists, "_ZNK13CGenericModel15animationExistsERKSs")
TL_FUNCTION(dep_randomAnimation, "_ZN13CGenericModel19findRandomAnimationERKSs")
TL_FUNCTION(dep_blend, "_ZN10CCharacter14blendAnimationEibfff")
TL_FUNCTION(dep_queue, "_ZN13CGenericModel19queueBlendAnimationERKSsbff")
TL_FUNCTION(dep_stopSkills, "_ZN13CSkillManager13stopAllSkillsEbbb")

TL_FUNCTION(dep_visible, "_ZN10CCharacter10setVisibleEbb")
TL_FUNCTION(dep_updateOpacity, "_ZN10CCharacter13updateOpacityEfb")
namespace {
using namespace smallmass;
void *self,*model,*equipment,*secondary;unsigned animationCalls;
bool theme(void* p,void* value) {event(1,p);pointer(value);return input->index%3!=0;}
void start(void* p) {event(2,p);field<bool>(p,0x81)=true;}
void stop(void* p,bool immediate) {event(3,p);number(immediate);field<bool>(p,0x81)=false;}
int loop(void* p) {event(4,p);return field<int>(p,0x90);}
void trailActive(void* p,bool v) {event(5,p);number(v);field<bool>(p,0x10)=v;}
void trailVisible(void* p,bool v) {event(6,p);number(v);field<bool>(p,0x11)=v;}
void setPosition(void* p,const Ogre::Vector3& v) {event(7,p);vector(v);field<Ogre::Vector3>(p,0x84)=v;}
void baseVisible(void* p,bool v) {event(8,p);number(v);field<bool>(p,0x81)=v;}
void simpleVisible(void* p,bool v) {event(9,p);number(v);field<bool>(p,0x52c)=v;}
void visible(void* p,bool v,bool immediate) {event(10,p);number(v);number(immediate);field<bool>(p,0x81)=v;field<bool>(p,0x52c)=v;}
void updateOpacity(void* p,float elapsed,bool force) {event(11,p);floating(elapsed);number(force);}
void opacity(void* p,float v) {event(12,p);floating(v);field<float>(p,0x210)=v;}
void* equipped(void* p,int slot) {event(13,p);number(slot);return (slot+input->index)%4==0?equipment:0;}
void* primary(void* p) {event(14,p);return input->index%5?model:0;}
void* secondaryModel(void* p) {event(15,p);return input->index%3?secondary:0;}
bool ai(void* p,int flag) {event(16,p);number(flag);return input->index%17==0;}
bool exists(void* p,const std::string& name) {event(17,p);text(name);++animationCalls;return input->index%3!=0&&(input->index%7!=0||animationCalls<3);}
int randomAnimation(void* p,const std::string& name) {event(18,p);text(name);return name=="HIT"?7:11;}
void blend(void* p,int index,bool loop,float fade,float speed,float start) {event(19,p);number(index);number(loop);floating(fade);floating(speed);floating(start);}
void queue(void* p,const std::string& name,bool loop,float fade,float speed) {event(20,p);text(name);number(loop);floating(fade);floating(speed);}
void stopSkills(void* p,bool a,bool b,bool c) {event(21,p);number(a);number(b);number(c);}
void state(void* p,int v) {event(22,p);number(v);field<int>(p,0x330)=v;}
void execute(Case& c,bool ours,autotest::Capture& out) {
 input=&c;output=&out;autotest::g_arenaUsed=0;animationCalls=0;
 self=object(0x778);model=object(0x258);secondary=object(0x258);equipment=object(0x480);
 void* manager=object(0x100);void* skill=object(0x160);void* path=object(0x80);
 void** table=static_cast<void**>(object(0x430));table[0x50/8]=reinterpret_cast<void*>(&simpleVisible);table[0x348/8]=reinterpret_cast<void*>(&state);field<void*>(self,0)=table;
 void** equipTable=static_cast<void**>(object(0x380));equipTable[0x1e0/8]=reinterpret_cast<void*>(&primary);equipTable[0x2f0/8]=reinterpret_cast<void*>(&secondaryModel);field<void*>(equipment,0)=equipTable;
 field<void*>(self,0x200)=c.index%11?model:0;
 if(c.op==2)field<void*>(self,0x200)=model;
 field<void*>(self,0x490)=c.index%5?manager:0;
 field<void*>(self,0x718)=c.index%3?manager:0;
 field<void*>(self,0x1c8)=c.index%5?manager:0;
 field<void*>(self,0x398)=c.index%3?skill:0;
 field<bool>(self,0x81)=c.index&1;field<bool>(self,0x52c)=c.index&2;
 field<bool>(self,0x70d)=c.index%7==0;field<bool>(self,0x19a)=c.index&4;
 field<bool>(self,0x681)=c.index&8;field<void*>(self,0x670)=path;
 field<float>(path,0x18)=10;field<float>(self,0x678)=float(c.index%13);
 const float opacities[]={-1,0,.25f,.75f,1,1.5f};field<float>(self,0x528)=opacities[(c.index/4)%6];
 const int states[]={0,2,5,6,0x10,0x28,0x29,0x23,0x1d,0xc};field<int>(self,0x330)=states[(c.index/2)%10];
 field<bool>(self,0x267)=c.index&2;field<float>(self,0x380)=float(int(c.index%3)-1);field<bool>(self,0x37d)=c.index&4;field<bool>(self,0x3a8)=c.index&8;
 field<float>(self,0x378)=5;field<bool>(self,0x264)=c.index&16;field<float>(self,0x278)=3;
 field<Ogre::Vector3>(self,0x84)=Ogre::Vector3(1,2,3);
 void** triggers=static_cast<void**>(object(8*8));void* particles[8];unsigned n=c.index%9;
 for(unsigned i=0;i<8;++i) {
  triggers[i]=object(0x68);particles[i]=object(0x300);
  field<void*>(triggers[i],0x38)=(i+c.index)%5?particles[i]:0;
  field<bool>(triggers[i],0x59)=i&1;field<bool>(triggers[i],0x5a)=i&2;
  field<bool>(triggers[i],0x20)=(i+c.index)&1;field<bool>(triggers[i],0x58)=(i+c.index)&2;
  field<void*>(triggers[i],0x50)=i&4?manager:0;field<int>(particles[i],0x90)=(i+c.index)%3;
 }
 list(self,0x738,triggers,n,8);
 for(unsigned i=0;i<4;++i)field<void*>(self,0x698+8*i)=(c.index+i)%3?object(0xa0):0;
 detour::Set patches;
 TL_REDIRECT(patches,dep_theme,&theme);
 TL_REDIRECT(patches,dep_start,&start);
 TL_REDIRECT(patches,dep_stop,&stop);
 TL_REDIRECT(patches,dep_loop,&loop);
 TL_REDIRECT(patches,dep_trailActive,&trailActive);
 TL_REDIRECT(patches,dep_trailVisible,&trailVisible);
 TL_REDIRECT(patches,dep_setPosition,&setPosition);
 TL_REDIRECT(patches,dep_baseVisible,&baseVisible);
 TL_REDIRECT(patches,dep_opacity,&opacity);
 TL_REDIRECT(patches,dep_equipped,&equipped);
 TL_REDIRECT(patches,dep_ai,&ai);
 TL_REDIRECT(patches,dep_exists,&exists);
 TL_REDIRECT(patches,dep_randomAnimation,&randomAnimation);
 TL_REDIRECT(patches,dep_blend,&blend);
 TL_REDIRECT(patches,dep_queue,&queue);
 TL_REDIRECT(patches,dep_stopSkills,&stopSkills);

 if(c.op!=0) {TL_REDIRECT(patches,dep_visible,&visible);}
 if(c.op!=1) {TL_REDIRECT(patches,dep_updateOpacity,&updateOpacity);}
 const float times[]={0,.1f,.5f,1,-.25f};float elapsed=times[(c.index/8)%5];
 if(patches.failed())_exit(41);
 switch(c.op) {
 case 0:autotest::invoke(out,ours?candidate0:original0,self,bool(c.index&16),bool(c.index&32));break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self,elapsed,bool(c.index&32));break;
 case 2:autotest::invoke(out,ours?candidate2:original2,self,bool(c.index&32));break;
 }
 number(field<bool>(self,0x81));number(field<bool>(self,0x52c));floating(field<float>(self,0x528));number(field<int>(self,0x330));floating(field<float>(self,0x378));floating(field<float>(self,0x380));number(field<bool>(self,0x267));number(field<bool>(self,0x264));floating(field<float>(self,0x278));vector(field<Ogre::Vector3>(self,0x21c));
 for(unsigned i=0;i<n;++i){number(field<bool>(particles[i],0x81));vector(field<Ogre::Vector3>(particles[i],0x84));}
}
}
TL_TEST(mass3_812950) { return smallmass::run(host,0,"mass3_812950",(uint64_t)(uintptr_t)original0,execute,256); }
TL_TEST(mass3_812e70) { return smallmass::run(host,1,"mass3_812e70",(uint64_t)(uintptr_t)original1,execute,256); }
TL_TEST(mass3_811230) { return smallmass::run(host,2,"mass3_811230",(uint64_t)(uintptr_t)original2,execute,256); }
