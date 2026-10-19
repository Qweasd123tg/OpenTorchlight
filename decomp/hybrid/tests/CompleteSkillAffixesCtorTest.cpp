#include <cstring>
#include <string>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "SkillEffectAndAffixes.h"
#include "Skill.h"
#include "Effect.h"
#include "MasterResourceManager.h"
#include "Hierarchy.h"
#include "ResourceManager.h"
#include "DataGroup.h"
#include "DataValue.h"
#include "TRepository.h"
#undef protected
#undef private
TL_ORIGINAL(void,acOld,(CSkillEffectAndAffixes*,CSkill*,CDataGroup*,CSkillEffectAndAffixes*),"_ZN22CSkillEffectAndAffixesC1EP6CSkillP10CDataGroupPS_")
extern "C" void acNew(CSkillEffectAndAffixes*,CSkill*,CDataGroup*,CSkillEffectAndAffixes*) __asm__("_ZN22CSkillEffectAndAffixesC1EP6CSkillP10CDataGroupPS_");
TL_FUNCTION(acTarget,"_ZN6CSkill13getTargetTypeEv")
TL_FUNCTION(acSingleton,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(acHierarchy,"_ZN10CHierarchy15getTypeIDByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(acEffect,"_ZN7CEffectC1EP10CDataGroupP9CBaseUnit")
TL_FUNCTION(acDisplay,"_ZN22CSkillEffectAndAffixes23createAffixesForDisplayEP16CResourceManager")
TL_FUNCTION(acString,"_ZN10CDataValue14GetValueStringEb")
TL_ORIGINAL(const std::wstring&,acNativeString,(CDataValue*,bool),"_ZN10CDataValue14GetValueStringEb")

namespace {
using namespace smallmass;
unsigned seed,created;CSkill*selfSkill;CSkillEffectAndAffixes*self,*source;CResourceManager*resources;
CMasterResourceManager*master;CHierarchy*hierarchy;CDataGroup*root;CDataGroup*effectGroups[32];CEffect*createdEffects[32];CEffect*borrowedEffects[16];unsigned borrowed;
detour::Set*stringHooks;
int target(CSkill*p){number(1);number(p==selfSkill);return int(seed%12);}
CMasterResourceManager*singleton(){number(2);return master;}
UNITTYPES::EUNITTYPES type(CHierarchy*p,const std::wstring&v){number(3);number(p==hierarchy);text(v);return static_cast<UNITTYPES::EUNITTYPES>(v==L"MONSTER"?12:27);}
int effectID(CEffect*p){for(unsigned i=0;i<created;++i)if(createdEffects[i]==p)return int(i);for(unsigned i=0;i<borrowed;++i)if(borrowedEffects[i]==p)return 100+i;return p?200:-1;}
void effectCtor(CEffect*p,CDataGroup*d,CBaseUnit*u){number(4);number(u==NULL);unsigned n=32;for(unsigned i=0;i<32;++i)if(d==effectGroups[i])n=i;number(n);createdEffects[created++]=p;}
const std::wstring& stringValue(CDataValue*p,bool translate){number(6);number(translate);text(p->GetDataValueName());stringHooks->restore();const std::wstring&r=acNativeString(p,false);TL_REDIRECT(*stringHooks,acString,&stringValue);if(stringHooks->failed())std::abort();return r;}
template<class T>void listState(TArrayList<T>&a){number(a.m_nCount);number(a.m_nCapacity);number(a.m_nGrowBy);number(a.m_pData!=NULL);}
void state(){number(self->m_pSkill==selfSkill);text(self->m_name);listState(self->m_affixData);listState(self->m_effectData);listState(self->m_displayAffixes);listState(self->m_affixNames);listState(self->m_effectNames);
 for(unsigned i=0;i<self->m_affixData.size();++i){CSkillEffectAndAffixes::CSkillAffixData*a=self->m_affixData[i];text(a->m_name);number(a->m_value18);number(a->m_unitType);number(a->m_targetType);floating(a->m_durationOverride);}
 for(unsigned i=0;i<self->m_effectData.size();++i){CSkillEffectAndAffixes::CSkillEffectData*e=self->m_effectData[i];number(e->m_flag10);number(e->m_value30);number(e->m_value34);listState(e->m_effects);for(unsigned j=0;j<e->m_effects.size();++j)number(effectID(e->m_effects[j]));}
 for(unsigned i=0;i<self->m_affixNames.size();++i)text(self->m_affixNames[i]);for(unsigned i=0;i<self->m_effectNames.size();++i)text(self->m_effectNames[i]);
}
void display(CSkillEffectAndAffixes*p,CResourceManager*r){number(5);number(p==self);number(r==resources);state();}
const wchar_t*targets[]={L"enemy",L"self",L"pet",L"everybody",L"friend",L"unknown",L""};
void fillStrings(CDataGroup*g,unsigned n,const wchar_t*name){for(unsigned i=0;i<n;++i){CDataValue*v=g->AddDataValue(name,L"",false);if(i%4==0)v->SetValueInt32(37);else if(i%4==1)v->SetValueTranslate(L"translated Ж");else v->SetValueString(i&1?L"AFFIX_X":L"AFFIX_Y");}}
void ctorSide(Case&c,bool ours,autotest::Capture&out){output=&out;seed=c.index;created=0;borrowed=0;std::memset(effectGroups,0,sizeof(effectGroups));std::memset(createdEffects,0,sizeof(createdEffects));new(reinterpret_cast<void*>(0x14ef9e8))std::wstring();const wchar_t* nativeTargets[]={L"ENEMY",L"SELF",L"PET",L"EVERYBODY",L"FRIEND"};for(unsigned i=0;i<5;++i)new(reinterpret_cast<void*>(0x14f0a00+i*8))std::wstring(nativeTargets[i]);
 selfSkill=static_cast<CSkill*>(object(sizeof(CSkill)));resources=static_cast<CResourceManager*>(object(sizeof(CResourceManager)));selfSkill->m_resources=resources;selfSkill->m_iTargetAlignment=(seed/12)%3;
 master=static_cast<CMasterResourceManager*>(object(sizeof(CMasterResourceManager)));hierarchy=static_cast<CHierarchy*>(object(sizeof(CHierarchy)));master->m_pHierarchy=hierarchy;
 root=new CDataGroup(L"SKILL",NULL,20,10,new TRepository<std::wstring>(L""));
 if(seed&1)root->SetDataValue(L"TARGET",targets[(seed/2)%7],false);
 CDataGroup*effects=root;if(seed&2){effects=root->AddDataGroup(L"EFFECTS");if(seed&4)effects->SetDataValue(L"TARGETTYPE",seed&8?L"MONSTER":L"",false);if(seed&16)effects->SetDataValue(L"TARGET",targets[(seed/32)%7],false);if(seed&32)effects->SetDataValue(L"ADDITIONALDESCRIPTION",L"effect\\nЖ",false);}
 unsigned effectCount=(seed/3)%5;if(c.index>=384)effectCount=11+(seed%3);for(unsigned i=0;i<effectCount;++i)effectGroups[i]=effects->AddDataGroup(L"EFFECT");
 unsigned affixCount=(seed/5)%4;if(c.index>=400)affixCount=12;
 for(unsigned i=0;i<affixCount;++i){CDataGroup*g=root->AddDataGroup(L"AFFIXES");if(seed&8)g->SetDataValue(L"AFFIXLEVEL",int((seed+i)%5)-2);if(seed&16)g->SetDataValue(L"DURATION",seed%7==0?bits(0x7fc00000):float(int(seed%5)-2));if(seed&32)g->SetDataValue(L"TARGETTYPE",i&1?L"OTHER":L"MONSTER",false);if(seed&64)g->SetDataValue(L"TARGET",targets[(seed+i)%7],false);if(seed&128)g->SetDataValue(L"ADDITIONALDESCRIPTION",i&1?L"affix\\nsecond":L"",false);fillStrings(g,seed%5,L"AFFIX");fillStrings(g,2,L"OTHER");}
 if(seed&64){CDataGroup*g=root->AddDataGroup(L"AFFIXESREMOVE");g->SetDataValue(L"ADDITIONALDESCRIPTION",L"remove\\nA",false);fillStrings(g,(seed/7)%14,L"ENTRY");}
 if(seed&128){CDataGroup*g=root->AddDataGroup(L"EFFECTSREMOVE");g->SetDataValue(L"ADDITIONALDESCRIPTION",seed&256?L"remove\\nB":L"",false);fillStrings(g,(seed/11)%14,L"NAME");}
 source=NULL;if(seed&4){source=static_cast<CSkillEffectAndAffixes*>(object(sizeof(CSkillEffectAndAffixes)));new(&source->m_affixData)TArrayList<CSkillEffectAndAffixes::CSkillAffixData*>(10);new(&source->m_effectData)TArrayList<CSkillEffectAndAffixes::CSkillEffectData*>(10);
  for(unsigned i=0;i<(seed/13)%4;++i){CSkillEffectAndAffixes::CSkillAffixData*a=new CSkillEffectAndAffixes::CSkillAffixData;a->m_name=i&1?L"inherited Ж":L"source";a->m_value18=i-3;a->m_unitType=i+7;a->m_targetType=i;a->m_durationOverride=5.25f;source->m_affixData.add(a);}
  for(unsigned i=0;i<(seed/17)%4;++i){CSkillEffectAndAffixes::CSkillEffectData*e=new CSkillEffectAndAffixes::CSkillEffectData;e->m_flag10=true;e->m_value30=i+9;e->m_value34=i+1;for(unsigned j=0;j<(seed+i)%4;++j){CEffect*p=static_cast<CEffect*>(object(sizeof(CEffect)));borrowedEffects[borrowed++]=p;e->m_effects.add(p);}source->m_effectData.add(e);}
 }
 self=static_cast<CSkillEffectAndAffixes*>(object(sizeof(CSkillEffectAndAffixes)));std::memset(self,0xcd,sizeof(*self));int before=g_iTotalCountOfObjects;
 typedef void(*Fn)(CSkillEffectAndAffixes*,CSkill*,CDataGroup*,CSkillEffectAndAffixes*);Fn fn=ours?acNew:acOld;if(!autotest::beginInvocation(out,fn))return;fn(self,selfSkill,root,source);out.callCompleted=1;number(created);number(g_iTotalCountOfObjects-before);state();
 TSafePointer<CSkillEffectAndAffixes>observer;observer.setObject(self);number(observer.getObject()==self);observer.setObject(NULL);
}
}
TL_TEST(complete_skill_affixes_ctor){detour::Set p,s;stringHooks=&s;TL_REDIRECT(p,acTarget,&target);TL_REDIRECT(p,acSingleton,&singleton);TL_REDIRECT(p,acHierarchy,&type);TL_REDIRECT(p,acEffect,&effectCtor);TL_REDIRECT(p,acDisplay,&display);TL_REDIRECT(s,acString,&stringValue);if(p.failed()||s.failed())return 1;return smallmass::run(host,0,"complete_skill_affixes_ctor",0xcb47f0,&ctorSide,416);}
