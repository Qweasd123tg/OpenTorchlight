#include <cstring>
#include <string>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "Skill.h"
#include "SkillProperty.h"
#include "Character.h"
#include "Equipment.h"
#include "Inventory.h"
#include "AttackDescription.h"
#include "GenericModel.h"
#undef protected
#undef private
TL_ORIGINAL(void,saOld,(CSkill*,CBaseUnit*),"_ZN6CSkill21assignSkillAnimationsEP9CBaseUnit")
extern "C" void saNew(CSkill*,CBaseUnit*) __asm__("_ZN6CSkill21assignSkillAnimationsEP9CBaseUnit");
TL_FUNCTION(saEquip,"_ZN10CInventory22getEquipmentEquippedAtE16EEQUIP_LOCATIONS")
TL_FUNCTION(saISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(saLeft,"_ZN10CCharacter19getWeaponInLeftHandEv")
TL_FUNCTION(saFind,"_ZN13CGenericModel19findRandomAnimationERKSs")
TL_FUNCTION(saIndex,"_ZNK13CGenericModel17getAnimationIndexERKSs")
TL_FUNCTION(saLength,"_ZNK13CGenericModel25getAnimationLengthSecondsEi")
TL_FUNCTION(saNarrow,"_ZN7STRINGS21StringConvertToNarrowEPKw")
extern "C" void*saCharacterTable[] __asm__("_ZTV10CCharacter");
extern "C" void*saBaseTable[] __asm__("_ZTV9CBaseUnit");
namespace {
using namespace smallmass;
unsigned seed,indexCalls;CSkill*self;CSkillProperty*property;CCharacter*character;CBaseUnit*unit;CEquipment*equipment[2];CGenericModel*model;CInventory*inventory;
void state(){number(self->m_animationIndex);number(self->m_animationIndexDW);number(self->m_animationIndexLoopInto);number(self->m_animationIndexDWLoopInto);number(self->m_animationIndexLoopEnd);floating(self->m_animationLength);}
void event(unsigned tag){number(tag);state();}
void*getModel(CBaseUnit*p){event(1);number(p==unit);return seed%13==0?NULL:model;}
CEquipment*equip(CInventory*p,EEQUIP_LOCATIONS where){event(2);number(p==inventory);number(where);return seed&(where==0?4:8)?equipment[where==0?0:1]:NULL;}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){event(3);number(p==equipment[0]);number(type);return seed%5!=0;}
CEquipment*left(CCharacter*p){event(4);number(p==character);return seed&8?equipment[1]:NULL;}
int animation(CGenericModel*p,const std::string&name,unsigned tag){event(tag);number(p==model);text(name);++indexCalls;return (seed/3+name.size()+indexCalls)%4==0?-1:int((seed+name.size()+indexCalls)%17);}
int find(CGenericModel*p,const std::string&name){return animation(p,name,5);}
unsigned animationIndex(CGenericModel*p,const std::string&name){return animation(p,name,6);}
float length(CGenericModel*p,int which){event(7);number(p==model);number(which);return seed%19==0?bits(0x7fc00000):float(which)*0.25f-1.5f;}
std::string narrow(const wchar_t*name){event(8);text(std::wstring(name));return std::wstring(name).empty()?"":"narrow_override";}
void animationSide(Case&c,bool ours,autotest::Capture&out){output=&out;seed=c.index<512?c.index:(c.index*40503u+1234u)&65535u;indexCalls=0;new(reinterpret_cast<void*>(0x14ee340))std::string();self=static_cast<CSkill*>(object(sizeof(CSkill)));property=static_cast<CSkillProperty*>(object(sizeof(CSkillProperty)));character=static_cast<CCharacter*>(object(sizeof(CCharacter)));CBaseUnit*base=static_cast<CBaseUnit*>(object(sizeof(CBaseUnit)));model=static_cast<CGenericModel*>(object(sizeof(CGenericModel)));inventory=static_cast<CInventory*>(object(sizeof(CInventory)));void*charVT[150],*baseVT[150];std::memcpy(charVT,saCharacterTable,sizeof(charVT));std::memcpy(baseVT,saBaseTable,sizeof(baseVT));charVT[2+0x1e0/8]=baseVT[2+0x1e0/8]=reinterpret_cast<void*>(&getModel);*reinterpret_cast<void***>(character)=charVT+2;*reinterpret_cast<void***>(base)=baseVT+2;unit=seed&1?static_cast<CBaseUnit*>(character):base;character->m_pInventory=seed&2?inventory:NULL;self->m_property=seed%29==0?NULL:property;property->m_bUseWeaponAnimation=seed&16;property->m_iRequirementRight=8;property->m_iRequirementLeft=19;
 new(&property->m_sAnimation)std::string(seed&32?"CAST":"");new(&property->m_sAnimationDualWield)std::string(seed&64?"CAST_DW":"");new(&property->m_sAnimationLoop)std::string(seed&128?"LOOP":"");new(&property->m_sAnimationLoopEnd)std::string(seed&256?"END":"");new(&property->m_sAnimationDualWieldLoop)std::string(seed&512?"LOOP_DW":"");
 new(&self->m_sAnimationOverride)std::wstring(seed&1024?L"override_a":L"");new(&self->m_sAnimationOverrideDW)std::wstring(seed&2048?L"override_dw":L"");new(&self->m_sLoopAnimationOverride)std::wstring(seed&4096?L"override_loop":L"");new(&self->m_sLoopAnimationOverrideDW)std::wstring(seed&8192?L"override_loop_dw":L"");new(&self->m_sAnimationOverrideLoopEnd)std::wstring(seed&16384?L"override_end":L"");
 for(unsigned i=0;i<2;++i){equipment[i]=static_cast<CEquipment*>(object(sizeof(CEquipment)));CAttackDescription*attack=static_cast<CAttackDescription*>(object(sizeof(CAttackDescription)));new(&attack->m_sAnimationName)std::string(i?"LPISTOL":"RWAND");equipment[i]->m_pAttackDescriptionOverride=attack;CAttackDescription*other=static_cast<CAttackDescription*>(object(sizeof(CAttackDescription)));new(&other->m_sAnimationName)std::string(i?"LAXE":"RBOW");equipment[i]->m_pAttackDescription=other;}
 self->m_animationIndex=seed%7==0?~0u:31;self->m_animationIndexDW=32;self->m_animationIndexLoopInto=33;self->m_animationIndexDWLoopInto=34;self->m_animationIndexLoopEnd=35;self->m_animationLength=-2.25f;
 typedef void(*Fn)(CSkill*,CBaseUnit*);Fn fn=ours?saNew:saOld;if(!autotest::beginInvocation(out,fn))return;fn(self,seed%31==0?NULL:unit);out.callCompleted=1;state();number(indexCalls);
}
}
TL_TEST(complete_skill_animations){detour::Set h;TL_REDIRECT(h,saEquip,&equip);TL_REDIRECT(h,saISA,&isa);TL_REDIRECT(h,saLeft,&left);TL_REDIRECT(h,saFind,&find);TL_REDIRECT(h,saIndex,&animationIndex);TL_REDIRECT(h,saLength,&length);TL_REDIRECT(h,saNarrow,&narrow);if(h.failed())return 1;return smallmass::run(host,0,"complete_skill_animations",0xca4a00,&animationSide,2048);}
