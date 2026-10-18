#include "SmallMassCompare.h"
TL_ORIGINAL(void, spawnResetOriginal,(void*),"_ZN12CUnitSpawner5resetEv")
extern "C" void spawnResetCandidate(void*) __asm__("_ZN12CUnitSpawner5resetEv");
TL_ORIGINAL(void, spawnClearOriginal,(void*),"_ZN12CUnitSpawner5clearEv")
extern "C" void spawnClearCandidate(void*) __asm__("_ZN12CUnitSpawner5clearEv");
TL_ORIGINAL(void, trailActiveOriginal,(void*,bool),"_ZN12CWeaponTrail9setActiveEb")
extern "C" void trailActiveCandidate(void*,bool) __asm__("_ZN12CWeaponTrail9setActiveEb");
TL_ORIGINAL(void, propertyActivateOriginal,(void*),"_ZN13CPropertyNode8activateEv")
extern "C" void propertyActivateCandidate(void*) __asm__("_ZN13CPropertyNode8activateEv");
TL_ORIGINAL(void, propertyScaleOriginal,(void*,const Ogre::Vector3&),"_ZN13CPropertyNode12scaleUpdatedERKN4Ogre7Vector3E")
extern "C" void propertyScaleCandidate(void*,const Ogre::Vector3&) __asm__("_ZN13CPropertyNode12scaleUpdatedERKN4Ogre7Vector3E");
TL_ORIGINAL(void, propertyCharacterOriginal,(void*,float,void*),"_ZN13CPropertyNode23characterUpdatedInLevelEfP10CCharacter")
extern "C" void propertyCharacterCandidate(void*,float,void*) __asm__("_ZN13CPropertyNode23characterUpdatedInLevelEfP10CCharacter");
TL_FUNCTION(layoutStop,"_ZN7CLayout4stopEb")
TL_FUNCTION(removeListener,"_ZN6CLevel29removeCharacterUpdateListenerEP22iLevelUpdatedCharacter")
TL_FUNCTION(editorRunning,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(updateBounds,"_ZN13CPropertyNode17updateBoundingBoxEv")
TL_FUNCTION(getPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(allowJump,"_ZN10CCharacter16setAllowJumpDownEb")
namespace {
using namespace smallmass;
void* self;void* unit;unsigned calls;
void stop(void* p,bool value){event(1,p);number(value);++calls;}
void visible(void* p,bool value){event(2,p);number(value);++calls;field<bool>(p,0x81)=value;}
void listener(void* level,void* p){event(3,level);pointer(p);++calls;if(p!=static_cast<char*>(self)+0x100)output->issue=autotest::Capture::InvalidReport;}
void enabled(void* p,bool value){event(4,p);number(value);++calls;field<bool>(p,0x82)=value;}
bool isEnabled(void* p){event(5,p);++calls;return input->index&1;}
bool editor(void* p){event(6,p);++calls;return input->index&1;}
void scale(void* p,float x,float y,float z){event(7,p);floating(x);floating(y);floating(z);++calls;}
void bounds(void* p){event(8,p);++calls;}
Ogre::Vector3 position(void* p,bool absolute){event(9,p);number(absolute);++calls;return field<Ogre::Vector3>(p,0x84);}
void jump(void* p,bool value){event(10,p);number(value);++calls;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;self=object(0x300);unit=object(0x778);void* resources=object(0x50);void* level=object(0x300);field<void*>(self,0x68)=resources;field<void*>(resources,0x18)=c.index%7?level:0;
 void** table=static_cast<void**>(object(0x200));field<void*>(self,0)=table;table[0x40/8]=reinterpret_cast<void*>(&enabled);table[0x48/8]=reinterpret_cast<void*>(&isEnabled);table[0x98/8]=reinterpret_cast<void*>(&scale);
 detour::Set patches;TL_REDIRECT(patches,layoutStop,&stop);TL_REDIRECT(patches,removeListener,&listener);TL_REDIRECT(patches,editorRunning,&editor);TL_REDIRECT(patches,updateBounds,&bounds);TL_REDIRECT(patches,getPosition,&position);TL_REDIRECT(patches,allowJump,&jump);
 if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.op<2){unsigned n=c.index%5;void** data=new void*[n+2];for(unsigned i=0;i<n+2;++i){data[i]=object(0x100);void** v=static_cast<void**>(object(0x80));v[0x50/8]=reinterpret_cast<void*>(&visible);field<void*>(data[i],0)=v;field<bool>(data[i],0x81)=true;}list(self,0x1d0,data,n,n+2);field<int>(self,0x184)=3;field<int>(self,0x188)=5;field<int>(self,0x18c)=7;field<int>(self,0x1a0)=11;
 autotest::invoke(out,ours?(c.op?spawnClearCandidate:spawnResetCandidate):(c.op?spawnClearOriginal:spawnResetOriginal),self);
 for(unsigned i=0;i<n;++i)number(field<bool>(data[i],0x81));number(field<int>(self,0x184));number(field<int>(self,0x188));number(field<int>(self,0x18c));number(field<int>(self,0x1a0));number(calls);if(calls!=2*n)out.issue=autotest::Capture::InvalidReport;delete[]data;
 }else if(c.op==2){void* root=static_cast<char*>(self)+0x10;void* previous=root;unsigned n=c.index%5;for(unsigned i=0;i<n;++i){void* node=::operator new(48);field<void*>(previous,0)=node;field<void*>(node,8)=previous;previous=node;}field<void*>(previous,0)=root;field<void*>(root,8)=previous;field<void*>(self,0x30)=unit;field<void*>(self,0x38)=resources;field<float>(self,0x7c)=-4;field<bool>(self,0x88)=true;
 autotest::invoke(out,ours?trailActiveCandidate:trailActiveOriginal,self,bool(c.index&1));number(field<bool>(self,0x78));pointer(field<void*>(self,0x30));pointer(field<void*>(self,0x38));floating(field<float>(self,0x7c));number(field<bool>(self,0x88));number(field<void*>(root,0)==root);number(field<void*>(root,8)==root);if(field<void*>(root,0)!=root||field<void*>(root,8)!=root)out.issue=autotest::Capture::InvalidReport;
 }else if(c.op==3){field<bool>(self,0x111)=c.index&1;field<bool>(self,0x118)=c.index&2;field<unsigned>(self,0x10c)=c.index%3?6:8;autotest::invoke(out,ours?propertyActivateCandidate:propertyActivateOriginal,self);number(field<bool>(self,0x118));number(field<bool>(self,0x82));number(calls);
 }else if(c.op==4){const float ys[]={3,1000,0,-1,4,bits(0x7fc00001)};Ogre::Vector3 v(c.index,ys[(c.index/2)%6],-2);autotest::invoke(out,ours?propertyScaleCandidate:propertyScaleOriginal,self,v);number(calls);if(calls<2)out.issue=autotest::Capture::InvalidReport;
 }else{field<void*>(self,0x58)=c.index%7?resources:0;field<unsigned>(self,0x10c)=c.index%3?6:2;field<int>(self,0x138)=(c.index/3)%3;
 field<Ogre::Vector3>(self,0x120)=Ogre::Vector3(-1,-2,-3);field<Ogre::Vector3>(self,0x12c)=Ogre::Vector3(1,2,3);const Ogre::Vector3 points[]={Ogre::Vector3(0,0,0),Ogre::Vector3(1,2,3),Ogre::Vector3(-1,-2,-3),Ogre::Vector3(2,0,0),Ogre::Vector3(0,-3,0),Ogre::Vector3(0,0,4),Ogre::Vector3(bits(0x7fc00001),0,0),Ogre::Vector3(0,bits(0x7fc00001),0)};field<Ogre::Vector3>(unit,0x84)=points[(c.index/2)%8];autotest::invoke(out,ours?propertyCharacterCandidate:propertyCharacterOriginal,self,.25f,unit);number(calls);}
}
}
TL_TEST(scene_spawner_reset){return smallmass::run(host,0,"scene_spawner_reset",(uintptr_t)spawnResetOriginal,execute,32);}
TL_TEST(scene_spawner_clear){return smallmass::run(host,1,"scene_spawner_clear",(uintptr_t)spawnClearOriginal,execute,32);}
TL_TEST(scene_weapon_active){return smallmass::run(host,2,"scene_weapon_active",(uintptr_t)trailActiveOriginal,execute,32);}
TL_TEST(scene_property_activate){return smallmass::run(host,3,"scene_property_activate",(uintptr_t)propertyActivateOriginal,execute,48);}
TL_TEST(scene_property_scale){return smallmass::run(host,4,"scene_property_scale",(uintptr_t)propertyScaleOriginal,execute,24);}
TL_TEST(scene_property_character){return smallmass::run(host,5,"scene_property_character",(uintptr_t)propertyCharacterOriginal,execute,64);}
