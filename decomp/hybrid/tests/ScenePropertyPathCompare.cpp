#include "SmallMassCompare.h"
#include <OgreAxisAlignedBox.h>
TL_ORIGINAL(void, pathOriginal,(void*),"_ZN13CPropertyNode15updatePathNodesEv")
extern "C" void pathCandidate(void*) __asm__("_ZN13CPropertyNode15updatePathNodesEv");
TL_FUNCTION(incrementTarget,"_ZN6CLevel23incrementMapPassabilityERKN4Ogre14AxisAlignedBoxEf")
TL_FUNCTION(decrementTarget,"_ZN6CLevel23decrementMapPassabilityERKN4Ogre14AxisAlignedBoxEf")
TL_FUNCTION(killTarget,"_ZN13CPropertyNode19killOrMoveBaseUnitsEv")
namespace {
using namespace smallmass;void* self;unsigned calls;
bool enabled(void* p){event(1,p);++calls;return field<bool>(p,0x82);}
float scale(void* p){event(2,p);++calls;return field<float>(p,0x90);}
void increment(void* p,const Ogre::AxisAlignedBox& bounds,float radius){event(3,p);vector(bounds.getMinimum());vector(bounds.getMaximum());floating(radius);number(field<bool>(self,0x150));++calls;if(!field<bool>(self,0x150))output->issue=autotest::Capture::InvalidReport;}
void decrement(void* p,const Ogre::AxisAlignedBox& bounds,float radius){event(4,p);vector(bounds.getMinimum());vector(bounds.getMaximum());floating(radius);number(field<bool>(self,0x150));++calls;if(field<bool>(self,0x150))output->issue=autotest::Capture::InvalidReport;}
void kill(void* p){event(5,p);++calls;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;self=object(0x158);void* resources=object(0x50);void* level=object(0x300);field<void*>(self,0x68)=resources;field<void*>(resources,0x18)=c.index%11?level:0;field<unsigned>(level,0x50)=c.index%5?2:0;field<unsigned>(level,0x54)=c.index%7?3:0;field<bool>(self,0x82)=c.index&1;field<bool>(self,0x150)=c.index&2;field<unsigned>(self,0x10c)=c.index%3==0?8:c.index%3==1?9:6;field<float>(self,0x90)=c.index*.125f;new(static_cast<char*>(self)+0x120)Ogre::AxisAlignedBox(Ogre::Vector3(-1,-2,-3),Ogre::Vector3(4,5,6));void** table=static_cast<void**>(object(0xb8));table[0x48/8]=reinterpret_cast<void*>(&enabled);table[0xb0/8]=reinterpret_cast<void*>(&scale);field<void*>(self,0)=table;
 detour::Set p;TL_REDIRECT(p,incrementTarget,&increment);TL_REDIRECT(p,decrementTarget,&decrement);TL_REDIRECT(p,killTarget,&kill);if(p.failed()){out.issue=autotest::Capture::InvalidReport;return;}autotest::invoke(out,ours?pathCandidate:pathOriginal,self);number(field<bool>(self,0x150));number(calls);field<Ogre::AxisAlignedBox>(self,0x120).~AxisAlignedBox();
}
}
TL_TEST(scene_property_path_nodes){return smallmass::run(host,0,"scene_property_path_nodes",(uintptr_t)pathOriginal,execute,48);}
