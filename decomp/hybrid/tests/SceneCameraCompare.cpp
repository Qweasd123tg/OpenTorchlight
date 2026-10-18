#include "SmallMassCompare.h"
TL_ORIGINAL(void, stopOriginal,(void*),"_ZN17CCameraController10stopCameraEv")
extern "C" void stopCandidate(void*) __asm__("_ZN17CCameraController10stopCameraEv");
TL_ORIGINAL(void, startOriginal,(void*),"_ZN17CCameraController11startCameraEv")
extern "C" void startCandidate(void*) __asm__("_ZN17CCameraController11startCameraEv");
TL_ORIGINAL(void, updateOriginal,(void*,float),"_ZN17CCameraController6updateEf")
extern "C" void updateCandidate(void*,float) __asm__("_ZN17CCameraController6updateEf");
TL_FUNCTION(cameraSingleton,"_ZN14CCameraControl12getSingletonEv")
TL_FUNCTION(gameUISingleton,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(closeAll,"_ZN7CGameUI8closeAllEv")
TL_FUNCTION(hideDialogs,"_ZN7CGameUI16hideModalDialogsEv")
TL_FUNCTION(configureUnit,"_ZN17CCameraController13configureUnitEv")
TL_FUNCTION(stopCamera,"_ZN17CCameraController10stopCameraEv")
TL_FUNCTION(getPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(stopPathing,"_ZN10CCharacter11stopPathingEv")
TL_FUNCTION(graphClear,"_ZN6CGraph5clearEj")
TL_FUNCTION(graphAdd,"_ZN6CGraph8addValueEffj")
TL_FUNCTION(graphProcess,"_ZN6CGraph13processPointsEv")
TL_FUNCTION(graphValue,"_ZNK6CGraph8getValueEfj")
namespace {
using namespace smallmass;void* self;void* camera;void* ui;void* unit;unsigned calls;
void* cameraInstance(){event(1,camera);++calls;return camera;}
void* uiInstance(){event(2,ui);++calls;return ui;}
void close(void* p){event(3,p);++calls;}
void dialogs(void* p){event(4,p);++calls;}
void configure(void* p){event(5,p);++calls;field<void*>(p,0x120)=input->index%7?unit:0;}
void stop(void* p){event(6,p);++calls;field<bool>(p,0x82)=false;}
Ogre::Vector3 position(void* p,bool absolute){event(7,p);number(absolute);++calls;return field<Ogre::Vector3>(p,0x84)+(absolute?Ogre::Vector3(10,20,30):Ogre::Vector3::ZERO);}
void pathing(void* p){event(8,p);++calls;}
void clear(void* p,unsigned line){event(9,p);number(line);++calls;}
void add(void* p,float x,float y,unsigned line){event(10,p);floating(x);floating(y);number(line);++calls;}
void process(void* p){event(11,p);++calls;}
float value(void* p,float x,unsigned line){event(12,p);floating(x);number(line);++calls;const float values[]={0,.5f,1,1.5f,bits(0x7fc00001)};return values[input->index%5];}
void enabled(void* p,bool v){event(13,p);number(v);++calls;field<bool>(p,0x82)=v;}
bool isEnabled(void* p){event(14,p);++calls;return field<bool>(p,0x82);}
void state(void* p,int v){event(15,p);number(v);++calls;field<int>(p,0x330)=v;}
void broadcast(void* p,unsigned v){event(16,p);number(v);++calls;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;self=object(0x200);camera=object(0xa0);ui=object(0x20);unit=object(0x778);void* resources=object(0x50);void* client=object(0x3910);void* player=object(0x778);void* scene=object(0x100);
 field<void*>(self,0x100)=resources;field<void*>(self,0x68)=resources;field<void*>(self,0x48)=scene;void* clients[]={client};list(resources,0x28,clients,c.op==0&&c.index%9==0?0:1,1);field<void*>(client,0x58)=c.index%7?player:0;
 void** t=static_cast<void**>(object(0x350));t[0x30/8]=reinterpret_cast<void*>(&broadcast);t[0x40/8]=reinterpret_cast<void*>(&enabled);t[0x48/8]=reinterpret_cast<void*>(&isEnabled);t[0x348/8]=reinterpret_cast<void*>(&state);field<void*>(self,0)=t;field<void*>(player,0)=t;
 field<Ogre::Vector3>(self,0x84)=Ogre::Vector3(1,2,3);field<Ogre::Vector3>(scene,0x84)=Ogre::Vector3(4,-5,6);field<Ogre::Vector3>(unit,0x84)=Ogre::Vector3(-3,7,-1);field<Ogre::Vector3>(player,0x84)=Ogre::Vector3(8,-9,10);field<Ogre::Vector3>(camera,0x4c)=Ogre::Vector3(2,-1,3);field<Ogre::Vector3>(client,0x38e0)=Ogre::Vector3(99,98,97);field<int>(client,0x390c)=c.index%3;
 field<bool>(self,0x82)=c.index%11!=0;field<void*>(self,0x120)=c.index%3?unit:0;field<int>(self,0x1c0)=c.index%2;field<bool>(self,0x160)=c.index&2;field<bool>(self,0x161)=c.index&4;field<bool>(self,0x162)=c.index&8;field<bool>(self,0x163)=c.index&16;
 const float times[]={-1,0,.25f,1,bits(0x7fc00001),2};field<float>(self,0x148)=times[(c.index/2)%6];field<float>(self,0x14c)=times[c.index%6];field<float>(self,0x150)=.8f;field<float>(self,0x154)=.9f;field<float>(self,0x158)=c.index%3?1:0;field<float>(self,0x15c)=times[(c.index/3)%6];field<Ogre::Vector3>(self,0x130)=Ogre::Vector3(-1,3,2);field<Ogre::Vector3>(self,0x13c)=Ogre::Vector3(4,-2,1);
 detour::Set p;TL_REDIRECT(p,cameraSingleton,&cameraInstance);TL_REDIRECT(p,gameUISingleton,&uiInstance);TL_REDIRECT(p,closeAll,&close);TL_REDIRECT(p,hideDialogs,&dialogs);TL_REDIRECT(p,configureUnit,&configure);TL_REDIRECT(p,getPosition,&position);TL_REDIRECT(p,stopPathing,&pathing);TL_REDIRECT(p,graphClear,&clear);TL_REDIRECT(p,graphAdd,&add);TL_REDIRECT(p,graphProcess,&process);TL_REDIRECT(p,graphValue,&value);if(c.op!=0){TL_REDIRECT(p,stopCamera,&stop);}if(p.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.op==0)autotest::invoke(out,ours?stopCandidate:stopOriginal,self);else if(c.op==1)autotest::invoke(out,ours?startCandidate:startOriginal,self);else autotest::invoke(out,ours?updateCandidate:updateOriginal,self,times[(c.index/4)%6]);
 vector(field<Ogre::Vector3>(client,0x38e0));number(field<int>(client,0x390c));number(field<bool>(self,0x82));number(field<bool>(self,0x160));number(field<bool>(self,0x163));floating(field<float>(self,0x14c));floating(field<float>(self,0x15c));vector(field<Ogre::Vector3>(self,0x130));vector(field<Ogre::Vector3>(self,0x13c));number(calls);
}
}
TL_TEST(scene_camera_stop){return smallmass::run(host,0,"scene_camera_stop",(uintptr_t)stopOriginal,execute,48);}
TL_TEST(scene_camera_start){return smallmass::run(host,1,"scene_camera_start",(uintptr_t)startOriginal,execute,48);}
TL_TEST(scene_camera_update){return smallmass::run(host,2,"scene_camera_update",(uintptr_t)updateOriginal,execute,64);}
