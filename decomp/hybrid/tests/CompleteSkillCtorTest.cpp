#include <cstring>
#include <string>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "Skill.h"
#include "SkillProperty.h"
#include "ResourceManager.h"
#include "DataGroup.h"
#include "DataValue.h"
#include "TRepository.h"
#include "UnitResourceList.h"
#include "Constants.h"
#include "SkillDefines.h"
#undef protected
#undef private
TL_ORIGINAL(void,scOld,(CSkill*,CResourceManager*,CDataGroup*),"_ZN6CSkillC1EP16CResourceManagerP10CDataGroup")
extern "C" void scNew(CSkill*,CResourceManager*,CDataGroup*) __asm__("_ZN6CSkillC1EP16CResourceManagerP10CDataGroup");
TL_FUNCTION(scProperty,"_ZN14CSkillPropertyC1EP6CSkillP16CResourceManagerPS_P10CDataGroupj")
TL_FUNCTION(scSet,"_ZN6CSkill32_setLevelOfSkillFromSkillManagerEj")
TL_FUNCTION(scSingleton,"_ZN17CUnitResourceList12getSingletonEv")
TL_FUNCTION(scGet,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(scString,"_ZN10CDataValue14GetValueStringEb")
TL_ORIGINAL(const std::wstring&,scNativeString,(CDataValue*,bool),"_ZN10CDataValue14GetValueStringEb")
namespace {
using namespace smallmass;
unsigned seed,created;CSkill*self;CResourceManager*resources;CDataGroup*data,*levels[16],*units[3];CSkillProperty*properties[20];CUnitResourceList*unitList;detour::Set*stringHooks;
int id(const void*p){if(!p)return -1;if(p==self)return 0;if(p==resources)return 1;if(p==data)return 2;if(p==unitList)return 3;for(unsigned i=0;i<16;++i)if(p==levels[i])return 10+i;for(unsigned i=0;i<3;++i)if(p==units[i])return 30+i;for(unsigned i=0;i<created;++i)if(p==properties[i])return 40+i;return -2;}
template<class T>void list(TArrayList<T>&a){number(a.size());number(a.m_nCapacity);number(a.m_nGrowBy);}
void snapshot(){number(id(self->m_resources));number(self->m_pSkillManager==NULL);number(id(self->m_pDataGroup));number(self->m_pOwner==NULL);number(self->m_iOwnerSafePointerId);number(self->m_Target.getObject()==NULL);number(self->m_Target.m_nIndex);vector(self->m_targetPosition);output->add(&self->m_skillType,0x71-0x5c);list(self->m_allowedTargetData);for(unsigned i=0;i<self->m_allowedTargetData.size();++i)number(id(self->m_allowedTargetData[i]));number(id(self->m_property));number(id(self->m_baseProperty));number(self->m_iSkillLevelCount);number(self->m_levelPropertyCapacity);number(self->m_levelPropertyGrow);for(unsigned i=0;i<self->m_iSkillLevelCount;++i)number(id(self->m_levelPropertyData[i]));list(self->m_activeEvents);text(self->m_sRequiredSkill);output->add(&self->m_iRequiredLevel,0x128-0xd8);text(self->m_sAnimationOverride);text(self->m_sAnimationOverrideDW);text(self->m_sLoopAnimationOverride);text(self->m_sLoopAnimationOverrideDW);text(self->m_sAnimationOverrideLoopEnd);output->add(&self->m_Guid,8);number(self->m_iDisplayedMaxRank);}
void propertyCtor(CSkillProperty*p,CSkill*s,CResourceManager*r,CSkillProperty*parent,CDataGroup*g,unsigned level){number(1);number(id(s));number(id(r));number(id(parent));number(id(g));number(level);snapshot();properties[created++]=p;p->m_uiSkillId=level;}
void setLevel(CSkill*p,unsigned level){number(2);number(id(p));number(level);snapshot();p->m_skillLevel=level;p->m_property=p->m_iSkillLevelCount?p->m_levelPropertyData[0]:p->m_baseProperty;}
CUnitResourceList*singleton(){number(3);return unitList;}
CDataGroup*get(CUnitResourceList*p,const std::wstring&name){number(4);number(id(p));text(name);if(name==L"missing")return NULL;return units[name==L"B"?1:name==L"C"?2:0];}
const std::wstring&stringValue(CDataValue*p,bool translate){number(5);number(translate);text(p->GetDataValueName());stringHooks->restore();const std::wstring&v=scNativeString(p,false);TL_REDIRECT(*stringHooks,scString,&stringValue);if(stringHooks->failed())std::abort();return v;}
void ctorSide(Case&c,bool ours,autotest::Capture&out){output=&out;seed=c.index;created=0;std::memset(levels,0,sizeof(levels));std::memset(properties,0,sizeof(properties));new(reinterpret_cast<void*>(0x14ee340))std::string();new(reinterpret_cast<void*>(0x14ee348))std::wstring();for(unsigned i=0;i<5;++i)new(reinterpret_cast<void*>(0x14ef1c0+i*8))std::wstring(gSKILL_ACTIVATION_TYPE_NAMES[i]);for(unsigned i=0;i<4;++i)new(reinterpret_cast<void*>(0x14ef200+i*8))std::wstring(gSKILL_TYPE_NAMES[i]);for(unsigned i=0;i<7;++i)new(reinterpret_cast<void*>(0x14ee8a0+i*8))std::wstring(KALIGNMENT_STRINGS[i]);
 resources=static_cast<CResourceManager*>(object(sizeof(CResourceManager)));unitList=static_cast<CUnitResourceList*>(object(sizeof(CUnitResourceList)));for(unsigned i=0;i<3;++i)units[i]=static_cast<CDataGroup*>(object(sizeof(CDataGroup)));data=new CDataGroup(L"SKILL",NULL,20,10,new TRepository<std::wstring>(L""));
 unsigned n=(seed/5)%5;if(c.index>=384)n=13;for(unsigned i=0;i<n;++i){wchar_t name[32];std::swprintf(name,32,L"LEVEL%u",i+1);levels[i]=data->AddDataGroup(name);}if(seed&64)data->AddDataGroup(L"LEVEL99");
 const wchar_t*activations[]={L"",L"any",L"proc",L"weapon",L"normal",L"passive",L"unknown"};const wchar_t*types[]={L"",L"skill",L"offensive",L"defensive",L"charm",L"unknown"};const wchar_t*alignments[]={L"",L"NEUTRAL",L"GOOD",L"EVIL",L"ALL",L"BERSERK",L"EVILBERSERK",L"GOODBERSERK",L"good",L"unknown"};if(seed%3)data->SetDataValue(L"ACTIVATION_TYPE",activations[(seed/3)%7],false);if(seed%5)data->SetDataValue(L"SKILL_TYPE",types[(seed/7)%6],false);if(seed%7)data->SetDataValue(L"TARGET_ALIGNMENT",alignments[(seed/11)%10],false);
 const wchar_t*boolKeys[]={L"TARGET_CORPSES",L"HIDDEN",L"ALLOWS_TURNING",L"MOVES_TO_TARGET",L"DONT_STOP_ON_DEATH",L"CAN_BE_SILENCED",L"CAN_LEFT_MAP",L"USEWEAPONANIMATION",L"REQUIRES_PASSABLE_LOS",L"REQUIRES_PATHABLE"};for(unsigned i=0;i<10;++i)if((seed+i)%3)data->SetDataValue(boolKeys[i],bool((seed/3+i)&1));
 const wchar_t*intKeys[]={L"LEVEL_REQUIRED",L"MAX_INVEST_LEVEL",L"COLUMN",L"ROW",L"PANE",L"CHARGES"};for(unsigned i=0;i<6;++i)if((seed/3+i)%3)data->SetDataValue(intKeys[i],int((seed+i)%7)-3);if(seed&2)data->SetDataValue(L"UNIQUE_GUID",static_cast<long long>(seed)*0x123456789LL-3);
 if(seed&8){CDataGroup*g=data->AddDataGroup(L"TARGET_SPECIFIC_UNITS");for(unsigned i=0;i<(seed/13)%14;++i){CDataValue*v=g->AddDataValue(i&1?L"UNIT":L"OTHER",L"",false);if(i%4==0)v->SetValueInt32(12);else if(i%4==1)v->SetValueTranslate(i%3==0?L"missing":L"B");else v->SetValueString(i%3==0?L"missing":i%3==1?L"A":L"C");}}
 CResourceManager*r=seed&1?resources:NULL;CDataGroup*g=c.index<4&&seed&2?NULL:data;self=static_cast<CSkill*>(object(sizeof(CSkill)));std::memset(self,0xcd,sizeof(*self));int before=g_iTotalCountOfObjects;typedef void(*Fn)(CSkill*,CResourceManager*,CDataGroup*);Fn fn=ours?scNew:scOld;if(!autotest::beginInvocation(out,fn))return;fn(self,r,g);out.callCompleted=1;number(g_iTotalCountOfObjects-before);number(created);snapshot();number(reinterpret_cast<char*>(static_cast<iUnitObserver*>(self))-reinterpret_cast<char*>(self));number(dynamic_cast<CSkill*>(static_cast<iUnitObserver*>(self))==self);TSafePointer<CSkill>w;w.setObject(self);number(w.getObject()==self);w.setObject(NULL);
}
}
TL_TEST(complete_skill_ctor){detour::Set p,s;stringHooks=&s;TL_REDIRECT(p,scProperty,&propertyCtor);TL_REDIRECT(p,scSet,&setLevel);TL_REDIRECT(p,scSingleton,&singleton);TL_REDIRECT(p,scGet,&get);TL_REDIRECT(s,scString,&stringValue);if(p.failed()||s.failed())return 1;return smallmass::run(host,0,"complete_skill_ctor",0xca7b10,&ctorSide,416);}
