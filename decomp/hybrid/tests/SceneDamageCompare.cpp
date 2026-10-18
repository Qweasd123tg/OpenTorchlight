#include "SmallMassCompare.h"
#include <utility>
TL_ORIGINAL(void, itemOriginal,(void*,float,void*),"_ZN12CDamageShape18itemUpdatedInLevelEfP5CItem")
extern "C" void itemCandidate(void*,float,void*) __asm__("_ZN12CDamageShape18itemUpdatedInLevelEfP5CItem");
TL_ORIGINAL(void, characterOriginal,(void*,float,void*),"_ZN12CDamageShape23characterUpdatedInLevelEfP10CCharacter")
extern "C" void characterCandidate(void*,float,void*) __asm__("_ZN12CDamageShape23characterUpdatedInLevelEfP10CCharacter");
TL_FUNCTION(aliveTarget,"_ZN10CCharacter5aliveEv")
TL_FUNCTION(shapeTarget,"_ZN6CShape29getPositionIsInShapeAtPercentEfRKN4Ogre7Vector3Ef")
TL_FUNCTION(positionTarget,"_ZN19CPositionableObject11getPositionEb")
namespace {
using namespace smallmass;unsigned calls;
bool enabled(void* p){event(1,p);++calls;return input->index%7!=0;}
bool alive(void* p){event(2,p);++calls;return input->index&4;}
Ogre::Vector3 position(void* p,bool absolute){event(3,p);number(absolute);++calls;return field<Ogre::Vector3>(p,0x84);}
std::pair<bool,float> shape(void* p,float percent,const Ogre::Vector3& v,float radius){event(4,p);floating(percent);vector(v);floating(radius);++calls;return std::make_pair(input->index%5!=0,input->index*.125f);}
void damage(void* p,float elapsed,void* unit,float amount){event(5,p);floating(elapsed);pointer(unit);floating(amount);++calls;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;void* self=object(0x200);void* unit=object(0x778);void** table=static_cast<void**>(object(0x208));table[0x48/8]=reinterpret_cast<void*>(&enabled);table[0x1f8/8]=reinterpret_cast<void*>(&damage);table[0x200/8]=reinterpret_cast<void*>(&damage);field<void*>(self,0)=table;field<bool>(unit,0x218)=c.index%7==0;field<bool>(unit,0x70d)=c.index%11==0;field<bool>(unit,0x531)=c.index%13!=0;field<bool>(self,0x1a8)=c.index&2;field<float>(self,0x190)=float(c.index%4)*.25f;field<float>(unit,0x194)=float(c.index%5)*.5f;field<Ogre::Vector3>(unit,0x84)=Ogre::Vector3(1,-2,c.index*.25f);
 detour::Set p;TL_REDIRECT(p,aliveTarget,&alive);TL_REDIRECT(p,shapeTarget,&shape);TL_REDIRECT(p,positionTarget,&position);if(p.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 void* argument=c.index%17?unit:0;float elapsed=c.index*.125f;if(c.op==0)autotest::invoke(out,ours?itemCandidate:itemOriginal,self,elapsed,argument);else autotest::invoke(out,ours?characterCandidate:characterOriginal,self,elapsed,argument);number(calls);
}
}
TL_TEST(scene_damage_item){return smallmass::run(host,0,"scene_damage_item",(uintptr_t)itemOriginal,execute,48);}
TL_TEST(scene_damage_character){return smallmass::run(host,1,"scene_damage_character",(uintptr_t)characterOriginal,execute,64);}
