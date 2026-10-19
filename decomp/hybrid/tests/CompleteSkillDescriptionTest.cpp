#include <cstring>
#include <string>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "Skill.h"
#include "SkillProperty.h"
#include "Character.h"
#include "StringTranslate.h"
#undef protected
#undef private
TL_ORIGINAL(std::wstring,sdOld,(CSkill*,CBaseUnit*,unsigned,bool),"_ZN6CSkill14getDescriptionEP9CBaseUnitjb")
extern "C" std::wstring sdNew(CSkill*,CBaseUnit*,unsigned,bool) __asm__("_ZN6CSkill14getDescriptionEP9CBaseUnitjb");
TL_ORIGINAL(std::wstring,srOld,(CSkill*,CBaseUnit*),"_ZN6CSkill25getDescriptionRequirmentsEP9CBaseUnit")
extern "C" std::wstring srNew(CSkill*,CBaseUnit*) __asm__("_ZN6CSkill25getDescriptionRequirmentsEP9CBaseUnit");
TL_ORIGINAL(void,sdCore,(CRunicCore*),"_ZN10CRunicCoreC1Ev")
TL_FUNCTION(sdTranslate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(sdSingleton,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(sdNumber,"_ZN7STRINGS17GetValueAsWStringEf")
TL_FUNCTION(sdDescription,"_ZN14CSkillProperty19getSkillDescriptionEv")
TL_FUNCTION(sdStats,"_ZN14CSkillProperty13getSkillStatsEv")
TL_FUNCTION(sdWeapon,"_ZN6CSkill21weaponRequirementsMetEP10CCharacter")
TL_FUNCTION(sdWeaponName,"_Z15getWeaponStringN9UNITTYPES10EUNITTYPESE")
extern "C" void*sdCharacterTable[] __asm__("_ZTV10CCharacter");
extern "C" void*sdBaseTable[] __asm__("_ZTV9CBaseUnit");
namespace {
using namespace smallmass;
unsigned seed;CSkill*self;CSkillProperty*properties[5];CBaseUnit*units[2];CStringTranslate*translator;
int id(const void*p){if(!p)return -1;for(unsigned i=0;i<2;++i)if(p==units[i])return i;for(unsigned i=0;i<5;++i)if(p==properties[i])return 10+i;return -2;}
void event(unsigned tag){number(tag);number(id(self->m_pOwner));number(self->m_iOwnerSafePointerId);}
CStringTranslate*singleton(){event(1);return translator;}
std::wstring translate(CStringTranslate*p,const wchar_t*textValue){event(2);number(p==translator);text(std::wstring(textValue));return seed%17==0?L"":std::wstring(L"tr:")+textValue;}
std::wstring numberString(float v){event(3);floating(v);return L"mana数";}
std::wstring description(CSkillProperty*p){event(4);number(id(p));return seed%3==0?L"":L"description ж";}
std::wstring stats(CSkillProperty*p){event(5);number(id(p));const wchar_t*values[]={L"",L"stats",L"stats\n",L"\n",L"stats ж"};return values[seed/3%5];}
bool weapon(CSkill*p,CCharacter*c){event(6);number(p==self);number(id(c));if(seed%19==0)p->m_property=properties[1];return seed&1;}
std::wstring weaponName(UNITTYPES::EUNITTYPES t){event(7);number(t);return t==0?L"":L"weapon型";}
void descriptionSide(Case&c,bool ours,autotest::Capture&out){output=&out;seed=c.index;self=static_cast<CSkill*>(object(sizeof(CSkill)));translator=static_cast<CStringTranslate*>(object(sizeof(CStringTranslate)));new(reinterpret_cast<void*>(0x14ee348))std::wstring();for(unsigned i=0;i<2;++i){units[i]=static_cast<CBaseUnit*>(object(sizeof(CCharacter)));sdCore(units[i]);*reinterpret_cast<void***>(units[i])=(seed&2?sdCharacterTable:sdBaseTable)+2;}
 self->m_iOwnerSafePointerId=~0u;new(reinterpret_cast<void*>(&self->m_levelPropertyData))TArrayList<CSkillProperty*>(2);
 for(unsigned i=0;i<5;++i){properties[i]=static_cast<CSkillProperty*>(object(sizeof(CSkillProperty)));new(&properties[i]->m_sDisplayName)std::wstring((seed+i)%3==0?L"":L"Name ж");float values[]={0,-1,1.25f,bits(0x7fc00000)};properties[i]->m_iManaCost=values[(seed/5+i)%4];properties[i]->m_bDuelWeaponRequired=(seed+i)&1;properties[i]->m_bHasAnimation=(seed+i)&4;int req[]={0,8,19,-1};properties[i]->m_iRequirementRight=req[(seed/7+i)%4];properties[i]->m_iRequirementLeft=req[(seed/11+i)%4];}
 self->m_property=seed%23==0?NULL:properties[0];self->m_iEffectiveSkillLevel=seed/3%6;for(unsigned i=0;i<seed/7%5;++i)reinterpret_cast<TArrayList<CSkillProperty*>*>(&self->m_levelPropertyData)->add((seed+i)%3==0?NULL:properties[i+1]);reinterpret_cast<TSafePointer<CBaseUnit>*>(&self->m_pOwner)->setObject(seed&8?units[0]:NULL);CBaseUnit*unit=seed%13==0?NULL:units[seed&1];unsigned levels[]={0,~0u,1,2,3,4,5,~1u};unsigned level=levels[seed/13%8];
 for(unsigned frame=0;frame<2;++frame){if(c.op==0){typedef std::wstring(*Fn)(CSkill*,CBaseUnit*,unsigned,bool);Fn fn=ours?sdNew:sdOld;if(frame==0&&!autotest::beginInvocation(out,fn))return;std::wstring result=fn(self,unit,level,seed&16);text(result);}else{typedef std::wstring(*Fn)(CSkill*,CBaseUnit*);Fn fn=ours?srNew:srOld;if(frame==0&&!autotest::beginInvocation(out,fn))return;std::wstring result=fn(self,unit);text(result);}event(8);for(unsigned i=0;i<2;++i){number(units[i]->m_pSafePointers?units[i]->m_pSafePointers->size():0);if(units[i]->m_pSafePointers)for(unsigned j=0;j<units[i]->m_pSafePointers->size();++j)number((*units[i]->m_pSafePointers)[j]!=NULL);}}
 out.callCompleted=1;
}
int run(const tlhybrid_host*h,unsigned op,const char*name,unsigned address){detour::Set p;TL_REDIRECT(p,sdTranslate,&translate);TL_REDIRECT(p,sdSingleton,&singleton);TL_REDIRECT(p,sdNumber,&numberString);TL_REDIRECT(p,sdDescription,&description);TL_REDIRECT(p,sdStats,&stats);TL_REDIRECT(p,sdWeapon,&weapon);TL_REDIRECT(p,sdWeaponName,&weaponName);if(p.failed())return 1;return smallmass::run(h,op,name,address,&descriptionSide,2048);}
}
TL_TEST(complete_skill_description){return run(host,0,"complete_skill_description",0xca92e0);}
TL_TEST(complete_skill_requirements_description){return run(host,1,"complete_skill_requirements_description",0xca9bd0);}
