#include <cstring>
#include <string>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "SkillProperty.h"
#include "Skill.h"
#include "SkillEvent.h"
#include "SkillEffectAndAffixes.h"
#include "ResourceManager.h"
#include "DataGroup.h"
#include "TRepository.h"
#include "UnitThemes.h"
#include "SkillDefines.h"
#undef protected
#undef private
TL_ORIGINAL(void,pcOld,(CSkillProperty*,CSkill*,CResourceManager*,CSkillProperty*,CDataGroup*,unsigned),"_ZN14CSkillPropertyC1EP6CSkillP16CResourceManagerPS_P10CDataGroupj")
extern "C" void pcNew(CSkillProperty*,CSkill*,CResourceManager*,CSkillProperty*,CDataGroup*,unsigned) __asm__("_ZN14CSkillPropertyC1EP6CSkillP16CResourceManagerPS_P10CDataGroupj");
TL_FUNCTION(pcUnitType,"_ZN16CResourceManager17getUnitTypeByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(pcThemes,"_ZN11CUnitThemes12getSingletonEv")
TL_FUNCTION(pcEvent,"_ZN11CSkillEventC1EP6CSkillP14CSkillPropertyP16CResourceManagerP10CDataGroup")
TL_FUNCTION(pcClone,"_ZN14CSkillProperty18cloneEventForSkillEP11CSkillEvent")
TL_FUNCTION(pcAffix,"_ZN22CSkillEffectAndAffixesC1EP6CSkillP10CDataGroupPS_")
TL_FUNCTION(pcDuration,"_ZN22CSkillEffectAndAffixes19setDurationOverrideEf")
namespace {
using namespace smallmass;
unsigned seed,count;CSkillProperty*self,*parent;CSkill*skill;CResourceManager*resources;CDataGroup*data;CUnitThemes*themes;CUnitTheme*theme[3];CSkillEvent*events[96];CDataGroup*eventGroups[32];CSkillEffectAndAffixes*effects;
int id(const void*p){if(!p)return -1;if(p==self)return 0;if(p==parent)return 1;if(p==skill)return 2;if(p==resources)return 3;if(p==data)return 4;if(p==effects)return 5;for(unsigned i=0;i<3;++i)if(p==theme[i])return 10+i;for(unsigned i=0;i<count;++i)if(p==events[i])return 20+i;return -2;}
void snapshot(){number(self->m_iRequirementRight);number(self->m_iRequirementLeft);number(self->m_bDuelWeaponRequired);number(id(self->m_pResourceManager));number(id(self->m_pSkillProperty));number(id(self->m_pSkill));number(self->m_uiSkillId);number(self->m_iLevelRequired);number(id(self->m_pDataGroup));number(self->m_iSkillLevel);number(self->m_eTargetType);number(self->m_eTargetUnitType);output->add(&self->m_iManaCost,0xb6-0x78);number(id(self->m_pRequiredTheme));number(id(self->m_pForbiddenTheme));text(self->m_sSkillIcon);text(self->m_sSkillIconInactive);text(self->m_sName);text(self->m_sDisplayName);text(self->m_sUsageDescription);text(self->m_sDescription);text(self->m_sAnimation);text(self->m_sAnimationDualWield);text(self->m_sAnimationLoop);text(self->m_sAnimationLoopEnd);text(self->m_sAnimationDualWieldLoop);number(self->m_eventLists.size());number(self->m_eventLists.m_nCapacity);number(self->m_eventLists.m_nGrowBy);for(unsigned i=0;i<self->m_eventLists.size();++i){TArrayList<CSkillEvent*>*l=self->m_eventLists[i];number(l->size());number(l->m_nCapacity);number(l->m_nGrowBy);for(unsigned j=0;j<l->size();++j)number(id((*l)[j]));}}
unsigned unitType(CResourceManager*p,const std::wstring&s){number(1);number(id(p));text(s);return unsigned(s.size()+7);}
CUnitThemes* singleton(){number(2);return themes;}
void eventCtor(CSkillEvent*p,CSkill*s,CSkillProperty*q,CResourceManager*r,CDataGroup*g){number(3);number(id(s));number(id(q));number(id(r));unsigned index=32;for(unsigned i=0;i<32;++i)if(eventGroups[i]==g)index=i;number(index);snapshot();p->m_eventType=static_cast<ESKILL_EVENT_TYPE>((seed+index)%11);p->m_pSkillProperty=q;events[count++]=p;}
CSkillEvent*cloneBoundary(CSkillProperty*p,CSkillEvent*e){number(4);number(id(p));number(id(e));snapshot();CSkillEvent*c=static_cast<CSkillEvent*>(object(sizeof(CSkillEvent)));c->m_eventType=e->m_eventType;events[count++]=c;p->m_eventLists[c->m_eventType]->add(c);return c;}
void affixCtor(CSkillEffectAndAffixes*p,CSkill*s,CDataGroup*g,CSkillEffectAndAffixes*source){number(5);number(id(s));number(id(g));number(source==NULL);snapshot();effects=p;}
void duration(CSkillEffectAndAffixes*p,float f){number(6);number(id(p));floating(f);}
void strings(CSkillProperty*p,const wchar_t*name){new(&p->m_sSkillIcon)std::wstring(name);new(&p->m_sSkillIconInactive)std::wstring(L"inactive");new(&p->m_sName)std::wstring(L"parent");new(&p->m_sDisplayName)std::wstring(L"display");new(&p->m_sUsageDescription)std::wstring(L"usage\\n");new(&p->m_sDescription)std::wstring(L"description\\n");new(&p->m_sAnimation)std::string("attack");new(&p->m_sAnimationDualWield)std::string(seed&16?"dual":"");new(&p->m_sAnimationLoop)std::string(seed&32?"loop":"");new(&p->m_sAnimationLoopEnd)std::string("end");new(&p->m_sAnimationDualWieldLoop)std::string(seed&64?"dual_loop":"");}
void ctorSide(Case&c,bool ours,autotest::Capture&out){output=&out;seed=c.index;count=0;effects=NULL;std::memset(events,0,sizeof(events));std::memset(eventGroups,0,sizeof(eventGroups));new(reinterpret_cast<void*>(0x14f49a0))std::string();new(reinterpret_cast<void*>(0x14f49a8))std::wstring();for(unsigned i=0;i<11;++i)new(reinterpret_cast<void*>(0x14f5760+i*8))std::wstring(gSKILL_EVENT_TYPE_NAMES[i]);for(unsigned i=0;i<12;++i)new(reinterpret_cast<void*>(0x14f57c0+i*8))std::wstring(gSKILL_TARGET_TYPE_NAMES[i]);
 skill=static_cast<CSkill*>(object(sizeof(CSkill)));resources=static_cast<CResourceManager*>(object(sizeof(CResourceManager)));parent=static_cast<CSkillProperty*>(object(sizeof(CSkillProperty)));strings(parent,L"icon");parent->m_iRequirementRight=7;parent->m_iRequirementLeft=13;parent->m_bDuelWeaponRequired=seed&2;parent->m_bUseWeaponAnimation=seed&4;parent->m_bSingleTarget=seed&8;parent->m_bInterruptable=seed&16;parent->m_bContinuousLooping=seed&32;parent->m_bExclusive=seed&64;parent->m_eTargetType=8;parent->m_eTargetUnitType=41;parent->m_iLevelRequired=-3;parent->m_iChance=34;
 float f[]={-1.2345f,0.0f,0.0001f,1.23456f,bits(0x7fc00000)};float*fp=&parent->m_iManaCost;for(unsigned i=0;i<13;++i)fp[i]=f[(seed/7+i)%5];
 themes=static_cast<CUnitThemes*>(object(sizeof(CUnitThemes)));new(&themes->m_Themes)TArrayList<CUnitTheme*>(2);for(unsigned i=0;i<3;++i){theme[i]=static_cast<CUnitTheme*>(object(sizeof(CUnitTheme)));new(&theme[i]->m_sName)std::wstring(i==0?L"FIRE":i==1?L"EXCLUDE":L"SHARED");themes->m_Themes.add(theme[i]);}parent->m_pRequiredTheme=theme[2];parent->m_pForbiddenTheme=theme[1];
 new(&parent->m_eventLists)TArrayList<TArrayList<CSkillEvent*>*>(10);for(unsigned i=0;i<11;++i){TArrayList<CSkillEvent*>*l=new TArrayList<CSkillEvent*>(10);for(unsigned j=0;j<(seed+i)%3;++j){CSkillEvent*e=static_cast<CSkillEvent*>(object(sizeof(CSkillEvent)));events[count++]=e;l->add(e);}parent->m_eventLists.add(l);}
 data=new CDataGroup(L"SKILL",NULL,20,10,new TRepository<std::wstring>(L""));
 const wchar_t*keys[]={L"TARGET_TYPE",L"TARGET",L"TARGET_UNITTYPE",L"THEMEREQUIRED",L"NOTTHEMED",L"REQUIREMENT_RIGHT",L"REQUIREMENT_LEFT",L"SKILL_ICON",L"SKILL_ICON_INACTIVE",L"NAME",L"DISPLAYNAME",L"USAGE_DESCRIPTION",L"DESCRIPTION",L"ANIMATION",L"ANIMATIONDW",L"ANIMATIONLOOP",L"ANIMATIONDWLOOP",L"ANIMATIONLOOPEND"};
 for(unsigned i=0;i<18;++i)if((seed*40503u+i*7919u)%5<3){const wchar_t*v=L"";if(seed%3){if(i<2)v=seed&2?L"target_pos":L"unrecognized";else if(i==3)v=seed&4?L"fire":L"missing";else if(i==4)v=L"exclude";else v=i<13?L"value\\nЖ":L"animation";}data->SetDataValue(keys[i],v,false);}
 const wchar_t*boolKeys[]={L"DUELWIELD_REQUIRED",L"USEWEAPONANIMATION",L"SINGLETARGET",L"INTERRUPTABLE",L"CONTINUOUSLOOPING",L"EXCLUSIVE"};for(unsigned i=0;i<6;++i)if((seed+i)%3)data->SetDataValue(boolKeys[i],bool((seed/3+i)&1));
 const wchar_t*floatKeys[]={L"MANACOST",L"MANACOSTOT",L"FINDTARGETANGLE",L"RANGE",L"RANGEMIN",L"RANDOMRANGE",L"RANDOMRANGEMIN",L"SPEED"};for(unsigned i=0;i<8;++i)if((seed/3+i)%3)data->SetDataValue(floatKeys[i],f[(seed/5+i)%5]);
 const wchar_t*intKeys[]={L"LEVEL_REQUIRED",L"COOLDOWNMS",L"MONSTERCOOLDOWNMS",L"MINIMUMTIMEMS",L"DURATIONOVERRIDEMS",L"SLOWDOWNMS",L"CHANCE"};for(unsigned i=0;i<7;++i)if((seed/5+i)%3)data->SetDataValue(intKeys[i],int((seed+i*37)%5000)-1000);
 unsigned ng=(seed/11)%4;if(c.index>=384)ng=13;for(unsigned i=0;i<ng;++i){CDataGroup*g=data->AddDataGroup(gSKILL_EVENT_TYPE_NAMES[(seed+i)%11]);eventGroups[i]=g;g->SetDataValue(L"CLONECOUNT",int((seed+i)%4)-1);}
 const wchar_t*affixGroups[]={L"NONE",L"EFFECT",L"EFFECTS",L"AFFIXES",L"AFFIXESREMOVE",L"EFFECTSREMOVE"};if(seed%6)data->AddDataGroup(affixGroups[seed%6]);
 CSkill*s=skill;CResourceManager*r=resources;CDataGroup*g=data;CSkillProperty*source=seed&1?parent:NULL;if(c.index<16){if(seed&1)s=NULL;if(seed&2)r=NULL;if(seed&4)g=NULL;source=seed&8?parent:NULL;}
 self=static_cast<CSkillProperty*>(object(sizeof(CSkillProperty)));std::memset(self,0xcd,sizeof(*self));int before=g_iTotalCountOfObjects;typedef void(*Fn)(CSkillProperty*,CSkill*,CResourceManager*,CSkillProperty*,CDataGroup*,unsigned);Fn fn=ours?pcNew:pcOld;if(!autotest::beginInvocation(out,fn))return;fn(self,s,r,source,g,seed*37);out.callCompleted=1;number(g_iTotalCountOfObjects-before);number(id(self->m_pSkillEffectAndAffixes));snapshot();TSafePointer<CSkillProperty>w;w.setObject(self);number(w.getObject()==self);w.setObject(NULL);
}
}
TL_TEST(complete_skill_property_ctor){detour::Set p;TL_REDIRECT(p,pcUnitType,&unitType);TL_REDIRECT(p,pcThemes,&singleton);TL_REDIRECT(p,pcEvent,&eventCtor);TL_REDIRECT(p,pcClone,&cloneBoundary);TL_REDIRECT(p,pcAffix,&affixCtor);TL_REDIRECT(p,pcDuration,&duration);if(p.failed())return 1;return smallmass::run(host,0,"complete_skill_property_ctor",0xce5f90,&ctorSide,416);}
