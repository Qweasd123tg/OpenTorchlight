#include "SmallMassCompare.h"
TL_ORIGINAL(void, original0, (void*,float), "_ZN10CCharacter15updateSkillKeysEf")
extern "C" void candidate0(void*,float) __asm__("_ZN10CCharacter15updateSkillKeysEf");
TL_ORIGINAL(bool, original1, (void*,void*), "_ZN10CCharacter13doWeaponSkillEP10CEquipment")
extern "C" bool candidate1(void*,void*) __asm__("_ZN10CCharacter13doWeaponSkillEP10CEquipment");
TL_ORIGINAL(void*, original2, (void*), "_ZN10CCharacter12performSkillEv")
extern "C" void* candidate2(void*) __asm__("_ZN10CCharacter12performSkillEv");
#include <OgreQuaternion.h>
TL_FUNCTION(dep_position, "_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(dep_equipped, "_ZN10CInventory22getEquipmentEquippedAtE16EEQUIP_LOCATIONS")
TL_FUNCTION(dep_known, "_ZN13CSkillManager11knownSkillsE22ESKILL_ACTIVATION_TYPE")
TL_FUNCTION(dep_executeSkill, "_ZN13CSkillManager12executeSkillEP6CSkillP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS5_10QuaternionES8_S3_")
TL_FUNCTION(dep_trigger, "_ZN13CSkillManager17triggerSkillEventE17ESKILL_EVENT_TYPERKN4Ogre7Vector3ERKNS1_10QuaternionEP9CBaseUnit")

namespace {
using namespace smallmass;
void *self,*equipment,*manager,*model,*target,*item,*active,*keys[8];unsigned executions;
Ogre::Vector3 position(void* p,bool absolute) {event(1,p);number(absolute);return field<Ogre::Vector3>(p,0x84);}
const Ogre::Vector3& derivedPosition(void* p) {event(2,p);return field<Ogre::Vector3>(p,0x20);}
const Ogre::Quaternion& orientation(void* p) {event(3,p);return field<Ogre::Quaternion>(p,0x30);}
const Ogre::Vector3& forward(void* p) {event(4,p);return field<Ogre::Vector3>(p,0xc0);}
void* equipped(void* p,int slot) {event(5,p);number(slot);return input->index%3?equipment:0;}
int known(void* p,int activation) {event(6,p);number(activation);return input->index%7;}
void* executeSkill(void* p,void* skill,void* caster,int activation,const Ogre::Vector3& start,const Ogre::Quaternion& rotation,const Ogre::Vector3& aim,void* victim) {
 event(7,p);pointer(skill);pointer(caster);number(activation);vector(start);output->add(&rotation,sizeof(rotation));vector(aim);pointer(victim);++executions;
 if(input->index%17==0){field<void*>(self,0x340)=0;field<void*>(self,0x350)=item;}
 return (input->index+executions)%3?skill:0;
}
void trigger(void* p,int type,const Ogre::Vector3& start,const Ogre::Quaternion& rotation,void* target) {
 event(8,p);number(type);vector(start);output->add(&rotation,sizeof(rotation));pointer(target);
 if(input->index%19==0)field<int>(keys[0],0x58)=0xf;
}
void execute(Case& c,bool ours,autotest::Capture& out) {
 input=&c;output=&out;autotest::g_arenaUsed=0;executions=0;
 self=object(0x778);equipment=object(0x480);manager=object(0x98);model=object(0x258);target=object(0x778);item=object(0x380);active=object(0x160);
 void* node=object(0x100);void* right=object(0x100);void* left=object(0x100);
 void** table=static_cast<void**>(object(0x430));table[0x130/8]=reinterpret_cast<void*>(&forward);field<void*>(self,0)=table;
 void** nodeTable=static_cast<void**>(object(0x218));nodeTable[0xc8/8]=reinterpret_cast<void*>(&orientation);nodeTable[0x200/8]=reinterpret_cast<void*>(&derivedPosition);
 field<void*>(node,0)=field<void*>(right,0)=field<void*>(left,0)=nodeTable;
 field<Ogre::Quaternion>(node,0x30)=Ogre::Quaternion(1,.125f,.25f,.5f);
 field<Ogre::Vector3>(right,0x20)=Ogre::Vector3(3,7,-1);field<Ogre::Vector3>(left,0x20)=Ogre::Vector3(-3,6,2);
 field<void*>(self,0x58)=node;field<void*>(self,0x2e8)=c.index%3?right:0;field<void*>(self,0x2f8)=left;
 field<void*>(self,0x200)=model;field<void*>(self,0x1c8)=c.op==0&&c.index%11==0?0:manager;
 field<void*>(equipment,0x1c8)=c.index%13?manager:0;field<void*>(self,0x490)=c.index%5?manager:0;
 field<void*>(self,0x398)=c.index%7?active:0;field<void*>(self,0x340)=c.index%4==1||c.index%4==3?target:0;field<void*>(self,0x350)=c.index%4>=2?item:0;
 field<Ogre::Vector3>(self,0x84)=Ogre::Vector3(float(int(c.index%5)-2),float(int(c.index%7)-3),float(int(c.index%9)-4));
 field<Ogre::Vector3>(self,0xc0)=Ogre::Vector3(.25f,0,.75f);
 field<Ogre::Vector3>(self,0x228)=c.index%5?Ogre::Vector3(-4,1,5):field<Ogre::Vector3>(self,0x84);
 field<float>(self,0x194)=float(int(c.index%9)-3)*.5f;
 field<bool>(self,0x267)=c.index&2;field<float>(self,0x380)=float(int(c.index%5)-2);
 const int states[]={0,1,2,5,6,7,0x29};field<int>(self,0x330)=states[c.index%7];
 field<unsigned>(active,0xec)=c.index%3?12:unsigned(-1);field<bool>(active,0x64)=c.index&1;field<bool>(active,0x66)=c.index&4;
 field<void*>(active,0x90)=c.index%11?manager:0;
 field<unsigned>(active,0xe4)=10;field<unsigned>(active,0xe8)=11;field<unsigned>(active,0xf0)=13;field<unsigned>(active,0xf4)=14;
 void** keyData=static_cast<void**>(object(8*8));void** skills=static_cast<void**>(object(8*8));
 const int events[]={0,0x1c,0xf,7};
 for(unsigned i=0;i<8;++i) {
  keys[i]=keyData[i]=object(0x60);field<int>(keys[i],0x58)=events[(c.index+i)%4];field<unsigned>(keys[i],0x28)=c.index%9==0?unsigned(-1):10+(c.index+i)%7;
  skills[i]=object(0x160);field<bool>(skills[i],0x6b)=(c.index+i)%3==0;field<bool>(skills[i],0x6d)=(c.index+i)%4!=0;
 }
 field<void*>(model,0x1b0)=keyData;field<void*>(model,0x1b8)=keyData+c.index%9;field<void*>(model,0x1c0)=keyData+8;
 list(manager,0x60,skills,8,8);
 detour::Set patches;
 TL_REDIRECT(patches,dep_position,&position);
 TL_REDIRECT(patches,dep_equipped,&equipped);
 TL_REDIRECT(patches,dep_known,&known);
 TL_REDIRECT(patches,dep_executeSkill,&executeSkill);
 TL_REDIRECT(patches,dep_trigger,&trigger);

 if(patches.failed())_exit(41);
 switch(c.op) {
 case 0:autotest::invoke(out,ours?candidate0:original0,self,.125f);break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self,c.index%11?equipment:0);break;
 case 2:autotest::invoke(out,ours?candidate2:original2,self);break;
 }
 number(field<bool>(self,0x384));number(field<bool>(self,0x37d));number(executions);
}
}
TL_TEST(mass3_811650) { return smallmass::run(host,0,"mass3_811650",(uint64_t)(uintptr_t)original0,execute,256); }
TL_TEST(mass3_8245c0) { return smallmass::run(host,1,"mass3_8245c0",(uint64_t)(uintptr_t)original1,execute,256); }
TL_TEST(mass3_827b20) { return smallmass::run(host,2,"mass3_827b20",(uint64_t)(uintptr_t)original2,execute,256); }
