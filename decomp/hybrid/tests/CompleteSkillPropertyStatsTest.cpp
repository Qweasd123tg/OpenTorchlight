#include <cstring>
#include <string>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "SkillProperty.h"
#include "Skill.h"
#include "SkillEvent.h"
#include "SkillEffectAndAffixes.h"
#include "ExecuteSkillProps.h"
#include "BaseUnit.h"
#include "StringTranslate.h"
#undef protected
#undef private
TL_ORIGINAL(std::wstring,psOld,(CSkillProperty*),"_ZN14CSkillProperty13getSkillStatsEv")
extern "C" std::wstring psNew(CSkillProperty*) __asm__("_ZN14CSkillProperty13getSkillStatsEv");
TL_FUNCTION(psEffects,"_ZN22CSkillEffectAndAffixes15getDisplayStatsEv")
TL_FUNCTION(psEvent,"_ZN11CSkillEvent15getDisplayStatsEP14CSkillProperty")
TL_FUNCTION(psExecute,"_ZN18CExecuteSkillProps13getSkillStatsEP9CBaseUniti")
TL_FUNCTION(psNumber,"_ZN7STRINGS17GetValueAsWStringEf")
TL_FUNCTION(psSingleton,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(psTranslate,"_ZN16CStringTranslate18getTranslateStringEPKw")
namespace {
using namespace smallmass;
unsigned seed;CSkillProperty*self;CSkill*skill;CBaseUnit*units[2];CSkillEvent*events[12];CExecuteSkillProps*executes[24];CSkillEffectAndAffixes*effects;CStringTranslate*translator;
int id(const void*p){if(!p)return -1;if(p==self)return 0;if(p==skill)return 1;if(p==effects)return 2;if(p==translator)return 3;for(unsigned i=0;i<2;++i)if(p==units[i])return 10+i;for(unsigned i=0;i<12;++i)if(p==events[i])return 20+i;for(unsigned i=0;i<24;++i)if(p==executes[i])return 40+i;return -2;}
void event(unsigned tag,const void*p){number(tag);number(id(p));}
std::wstring value(unsigned n){const wchar_t*v[]={L"",L"stats",L"stats\n",L"\n",L"stats Ж\n\n"};return v[(seed+n)%5];}
CStringTranslate*singleton(){event(1,translator);return translator;}
std::wstring translate(CStringTranslate*p,const wchar_t*s){event(2,p);text(std::wstring(s));return seed%17==0?L"":std::wstring(L"tr:")+s;}
std::wstring numberString(float f){event(3,self);floating(f);return seed%7==0?L"":L"12.5Ж";}
std::wstring effectStats(CSkillEffectAndAffixes*p){event(4,p);if(seed&1024)events[0]->m_cloneSource=events[1];return value(1);}
std::wstring eventStats(CSkillEvent*p,CSkillProperty*q){event(5,p);number(id(q));if(seed&2048)p->m_statsHidden=!p->m_statsHidden;return value(unsigned(id(p)));}
std::wstring executeStats(CExecuteSkillProps*p,CBaseUnit*u,int level){event(6,p);number(id(u));number(level);if(seed&512){++self->m_iSkillLevel;++self->m_uiSkillId;if(self->m_pSkill)self->m_pSkill->m_pOwner=(u==units[0]?units[1]:units[0]);}return value(unsigned(id(p)));}
void statsSide(Case&c,bool ours,autotest::Capture&out){output=&out;seed=c.index<1024?c.index:(c.index*40503u+1234u)&65535u;new(reinterpret_cast<void*>(0x14f49a8))std::wstring();self=static_cast<CSkillProperty*>(object(sizeof(CSkillProperty)));skill=static_cast<CSkill*>(object(sizeof(CSkill)));effects=static_cast<CSkillEffectAndAffixes*>(object(sizeof(CSkillEffectAndAffixes)));translator=static_cast<CStringTranslate*>(object(sizeof(CStringTranslate)));for(unsigned i=0;i<2;++i)units[i]=static_cast<CBaseUnit*>(object(sizeof(CBaseUnit)));self->m_pSkill=seed&1?skill:NULL;skill->m_pOwner=seed&2?units[0]:NULL;self->m_pSkillEffectAndAffixes=seed&4?effects:NULL;self->m_iSkillLevel=int(seed%9)-4;self->m_uiSkillId=seed%13-5;new(&self->m_eventLists)TArrayList<TArrayList<CSkillEvent*>*>(2);
 for(unsigned i=0;i<24;++i)executes[i]=static_cast<CExecuteSkillProps*>(object(sizeof(CExecuteSkillProps)));
 float damage[]={0.0f,-0.0f,1.25f,-2.5f,bits(0x7fc00001),bits(0x7f800000)};
 for(unsigned i=0;i<12;++i){CSkillEvent*p=static_cast<CSkillEvent*>(object(sizeof(CSkillEvent)));events[i]=p;p->m_weaponDamageScale=damage[(seed/7+i)%6];p->m_useDPS=(seed/11+i)&1;p->m_statsHidden=(seed/13+i)&1;new(&p->m_executeSkills)TArrayList<CExecuteSkillProps*>(2);for(unsigned j=0;j<(seed/17+i)%3;++j)p->m_executeSkills.add(executes[i*2+j]);}
 for(unsigned i=0;i<12;++i)events[i]->m_cloneSource=(seed/5+i)%4==0?events[(i+1)%12]:NULL;
 for(unsigned i=0;i<(seed/3)%4;++i){TArrayList<CSkillEvent*>*list=new TArrayList<CSkillEvent*>(2);for(unsigned j=0;j<(seed/19+i)%5;++j)list->add(events[i*4+j]);self->m_eventLists.add(list);}
 typedef std::wstring(*Fn)(CSkillProperty*);Fn fn=ours?psNew:psOld;if(!autotest::beginInvocation(out,fn))return;for(unsigned frame=0;frame<2;++frame){std::wstring r=fn(self);text(r);number(self->m_iSkillLevel);number(self->m_uiSkillId);number(id(skill->m_pOwner));for(unsigned i=0;i<12;++i)number(events[i]->m_statsHidden);}out.callCompleted=1;
}
}
TL_TEST(complete_skill_property_stats){detour::Set p;TL_REDIRECT(p,psEffects,&effectStats);TL_REDIRECT(p,psEvent,&eventStats);TL_REDIRECT(p,psExecute,&executeStats);TL_REDIRECT(p,psNumber,&numberString);TL_REDIRECT(p,psSingleton,&singleton);TL_REDIRECT(p,psTranslate,&translate);if(p.failed())return 1;return smallmass::run(host,0,"complete_skill_property_stats",0xce3fb0,&statsSide,2048);}
