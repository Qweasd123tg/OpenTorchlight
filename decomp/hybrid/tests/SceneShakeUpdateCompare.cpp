#include "SmallMassCompare.h"
TL_ORIGINAL(bool, updateOriginal,(void*,float,Ogre::Vector3&,Ogre::Vector3&,bool),"_ZN12CCameraShake6updateEfRN4Ogre7Vector3ES2_b")
extern "C" bool updateCandidate(void*,float,Ogre::Vector3&,Ogre::Vector3&,bool) __asm__("_ZN12CCameraShake6updateEfRN4Ogre7Vector3ES2_b");
TL_FUNCTION(graphValue,"_ZNK6CGraph8getValueEfj")
namespace {
using namespace smallmass;unsigned calls;
float graph(void* p,float ratio,unsigned line){event(1,p);floating(ratio);number(line);++calls;const float values[]={0,.5f,-1,2,bits(0x7fc00001),bits(0x7f800000)};return values[input->index%6];}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;void* self=object(0xa0);void* g=object(0x60);field<void*>(self,0x70)=c.index%11?g:0;const float values[]={0,.5f,-1,2,bits(0x7fc00001),bits(0x7f800000),bits(0xff800000),bits(0x80000000)};field<float>(self,0x58)=values[c.index%8];field<float>(self,0x5c)=values[(c.index/2)%8];field<float>(self,0x60)=values[(c.index/3)%8];field<Ogre::Vector3>(self,0x64)=Ogre::Vector3(.5f,-1,2);field<Ogre::Vector3>(self,0x8c)=Ogre::Vector3(c.index%7*2,99,3);field<bool>(self,0x98)=c.index&1;field<bool>(self,0x99)=c.index&2;
 Ogre::Vector3 camera(c.index%5*3,-7,c.index%9);Ogre::Vector3 offset= c.index%4?Ogre::Vector3(c.index%3*.5f,1,-2):Ogre::Vector3(8,-4,16);Ogre::Vector3& cameraArgument=c.index%17==0?offset:camera;
 detour::Set p;TL_REDIRECT(p,graphValue,&graph);if(p.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 bool(*fn)(void*,float,Ogre::Vector3&,Ogre::Vector3&,bool)=ours?updateCandidate:updateOriginal;if(!autotest::beginInvocation(out,fn))return;bool result=fn(self,values[(c.index/5)%8],cameraArgument,offset,c.index&4);out.callCompleted=1;number(result);vector(camera);vector(offset);floating(field<float>(self,0x5c));vector(field<Ogre::Vector3>(self,0x8c));number(calls);
}
}
TL_TEST(scene_shake_update){return smallmass::run(host,0,"scene_shake_update",(uintptr_t)updateOriginal,execute,64);}
