#include "SmallMassCompare.h"
TL_ORIGINAL(void, original0, (void*,void*,const Ogre::Vector3&,float), "_ZN9CItemGold6updateEPN4Ogre6CameraERKNS0_7Vector3Ef")
extern "C" void candidate0(void*,void*,const Ogre::Vector3&,float) __asm__("_ZN9CItemGold6updateEPN4Ogre6CameraERKNS0_7Vector3Ef");
TL_ORIGINAL(void, original1, (void*,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&), "_ZN6CShape20calculateOrientationERKN4Ogre7Vector3ERS1_S4_S4_")
extern "C" void candidate1(void*,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&) __asm__("_ZN6CShape20calculateOrientationERKN4Ogre7Vector3ERS1_S4_S4_");
TL_ORIGINAL(void, original2, (void*,bool), "_ZN8CConsole10setVisibleEb")
extern "C" void candidate2(void*,bool) __asm__("_ZN8CConsole10setVisibleEb");
#include <CEGUIString.h>
TL_FUNCTION(dep_itemUpdate, "_ZN5CItem6updateEPN4Ogre6CameraERKNS0_7Vector3Ef")
TL_FUNCTION(dep_stop, "_ZN9CParticle4StopEb")
TL_FUNCTION(dep_start, "_ZN9CParticle5StartEv")
TL_FUNCTION(dep_position, "_ZN19CPositionableObject11getPositionEb")
extern "C" char dep_windowVisible[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
extern "C" char dep_windowActivate[] __asm__("_ZN5CEGUI6Window8activateEv");
extern "C" char dep_windowFront[] __asm__("_ZN5CEGUI6Window11moveToFrontEv");
extern "C" char dep_windowText[] __asm__("_ZN5CEGUI6Window7setTextERKNS_6StringE");
namespace {
using namespace smallmass;
void* self;void* nextWindow;void* particle2;
void itemUpdate(void* p,void* camera,const Ogre::Vector3& position,float elapsed) { event(1,p);pointer(camera);vector(position);floating(elapsed);if(input->index%11==0)field<bool>(p,0x208)=!field<bool>(p,0x208); }
void stop(void* p,bool immediate) { event(2,p);number(immediate); }
void start(void* p) { event(3,p);if(input->index%7==0)field<void*>(self,0x280)=particle2; }
void visible(void* p,bool value) { event(4,p);number(value);field<bool>(p,0x81)=value; }
void scale(void* p,float value) { event(5,p);floating(value);field<float>(p,0x90)=value; }
Ogre::Vector3 position(void* p,bool absolute) { event(6,p);number(absolute);return field<Ogre::Vector3>(p,0x84); }
Ogre::Vector3 forward(void* p) { event(7,p);return Ogre::Vector3(0.25f,1,-2); }
Ogre::Vector3 up(void* p) { event(8,p);return Ogre::Vector3(3,-1,0.5f); }
Ogre::Vector3 right(void* p) { event(9,p);return Ogre::Vector3(-4,7,8); }
void windowVisible(void* p,bool value) { event(10,p);number(value);if(input->index%3==0)field<void*>(self,0x18)=nextWindow; }
void windowActivate(void* p) { event(11,p);if(input->index%5==0)field<void*>(self,0x18)=nextWindow; }
void windowFront(void* p) { event(12,p);if(input->index%7==0)field<void*>(self,0x20)=nextWindow; }
void windowText(void* p,const CEGUI::String& value) { event(13,p);number(value.length());for(unsigned i=0;i<value.length();++i)number(value[i]); }
void execute(Case& c,bool ours,autotest::Capture& out) {
 input=&c;output=&out;autotest::g_arenaUsed=0;
 self=object(0x288);particle2=object(0x168);void* particle=object(0x168);void* camera=object(32);nextWindow=object(32);
 void** table=static_cast<void**>(object(0x200));table[0x50/8]=reinterpret_cast<void*>(&visible);table[0x90/8]=reinterpret_cast<void*>(&scale);table[0x138/8]=reinterpret_cast<void*>(&forward);table[0x190/8]=reinterpret_cast<void*>(&up);table[0x168/8]=reinterpret_cast<void*>(&right);
 field<void*>(self,0)=table;field<void*>(particle,0)=table;field<void*>(particle2,0)=table;
 field<void*>(self,0x280)=c.index%5==0?NULL:particle;
 field<bool>(self,0x208)=c.index&1;field<bool>(self,0x81)=c.index&2;field<bool>(particle,0x81)=c.index&4;
 const float times[]={0,0.1f,0.35f,0.7f,-1,1};field<float>(self,0x234)=times[(c.index/8)%6];field<float>(self,0x230)=float(int(c.index%7)-2)*0.5f;
 field<int>(self,0x108)=int(c.index%7)-1;field<Ogre::Vector3>(self,0x84)=Ogre::Vector3(2,-9,-3);
 field<void*>(self,0x18)=c.index%5==0?NULL:object(32);field<void*>(self,0x20)=object(32);
 detour::Set patches;
 TL_REDIRECT(patches,dep_itemUpdate,&itemUpdate);
 TL_REDIRECT(patches,dep_stop,&stop);
 TL_REDIRECT(patches,dep_start,&start);
 TL_REDIRECT(patches,dep_position,&position);
 patches.redirect(dep_windowVisible,dep_windowVisible,&windowVisible);
 patches.redirect(dep_windowActivate,dep_windowActivate,&windowActivate);
 patches.redirect(dep_windowFront,dep_windowFront,&windowFront);
 patches.redirect(dep_windowText,dep_windowText,&windowText);
 if(patches.failed())_exit(41);
 Ogre::Vector3 p=c.index%11==0?field<Ogre::Vector3>(self,0x84):Ogre::Vector3(float(int(c.index%13)-4),7,float(int(c.index%9)-3));
 Ogre::Vector3 f(9,8,7),u(6,5,4),r(3,2,1);
 switch(c.op) {
 case 0:{void(*fn)(void*,void*,const Ogre::Vector3&,float)=ours?candidate0:original0;if(!autotest::beginInvocation(out,fn))return;fn(self,c.index&8?camera:NULL,p,times[(c.index/3)%6]);out.callCompleted=1;break;}
 case 1:{void(*fn)(void*,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&)=ours?candidate1:original1;if(!autotest::beginInvocation(out,fn))return;fn(self,p,f,c.index%13==0?f:u,c.index%17==0?u:r);out.callCompleted=1;vector(p);vector(f);vector(u);vector(r);break;}
 case 2:autotest::invoke(out,ours?candidate2:original2,self,bool(c.index&1));break;
 }
 out.add(autotest::g_arena,autotest::g_arenaUsed);
}
}
TL_TEST(restore69_8c2760) { return smallmass::run(host,0,"restore69_8c2760",(uint64_t)(uintptr_t)original0,execute,128); }
TL_TEST(restore69_a06700) { return smallmass::run(host,1,"restore69_a06700",(uint64_t)(uintptr_t)original1,execute,140); }
TL_TEST(restore69_aed310) { return smallmass::run(host,2,"restore69_aed310",(uint64_t)(uintptr_t)original2,execute,64); }
