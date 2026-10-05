// Real data groups, TArrayList and knownSkills; only translation and skill text
// are controlled. Run each side in a fresh child so static caches start cold.
#include <cstring>
#include <new>
#include <Ogre.h>
#include <map>
#define protected public
#define private public
#include "Equipment.h"
#include "DataGroup.h"
#include "Skill.h"
#include "SkillManager.h"
#include "StringTranslate.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(std::wstring, originalEquipmentSkillDescription,(CEquipment*),"_ZN10CEquipment16skillDescriptionEv")
TL_FUNCTION(sdSingleton,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(sdTranslate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(sdDescription,"_ZN6CSkill14getDescriptionEP9CBaseUnitjb")
namespace {
struct Case {unsigned seed,mode;};
const Case* input;autotest::Capture* capture;CEquipment* equipment;CSkillManager* first;CSkillManager* second;CSkill* skills[5];unsigned calls;int service;
void number(int n){capture->add(&n,sizeof(n));}
void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
CStringTranslate* singleton(){number(100);return reinterpret_cast<CStringTranslate*>(&service);}
std::wstring translate(CStringTranslate*,const wchar_t* s){number(101);text(s);switch(input->seed%4){case 0:return L"Level";case 1:return L"\x443\x440\x43e\x432\x435\x43d\x44c";case 2:return L"";default:return std::wstring(L"x\0y",3);}}
std::wstring description(CSkill* p,CBaseUnit* unit,unsigned level,bool flag){
    unsigned id=0;while(id<5&&skills[id]!=p)++id;
    number(200);number(id);number(unit==equipment);number(level);number(flag);
    if(++calls==1){
        if(input->mode==1)first->m_OtherSkills.m_nCount=1;
        if(input->mode==2)first->m_OtherSkills.add(skills[4]);
        if(input->mode==3)equipment->m_pSkillManager=second;
    }
    switch((input->seed/4+id)%5){case 0:return L"";case 1:return L"Skill";case 2:return L"\n";case 3:return L"|cFF0000test|u";default:return std::wstring(L"\x416\0z",3);}
}
void side(const Case& c,bool ours,autotest::Capture& out){
    input=&c;capture=&out;calls=0;
    unsigned long long eqStorage[(sizeof(CEquipment)+7)/8], managerStorage[2][(sizeof(CSkillManager)+7)/8],skillStorage[5][(sizeof(CSkill)+7)/8];
    std::memset(eqStorage,0,sizeof(eqStorage));std::memset(managerStorage,0,sizeof(managerStorage));std::memset(skillStorage,0,sizeof(skillStorage));
    equipment=reinterpret_cast<CEquipment*>(eqStorage);first=reinterpret_cast<CSkillManager*>(managerStorage[0]);second=reinterpret_cast<CSkillManager*>(managerStorage[1]);
    new(&first->m_OtherSkills)TArrayList<CSkill*>(8);new(&second->m_OtherSkills)TArrayList<CSkill*>(8);
    for(unsigned i=0;i<5;++i){skills[i]=reinterpret_cast<CSkill*>(skillStorage[i]);unsigned flags=(c.seed/20+i)%4;skills[i]->m_bEnabled=(flags&1)!=0;skills[i]->m_bExecutedByProperty=(flags&2)!=0;second->m_OtherSkills.add(skills[i]);}
    unsigned managerCount=(c.seed/80)%5;for(unsigned i=0;i<managerCount;++i)first->m_OtherSkills.add(skills[i]);
    if(c.mode){first->m_OtherSkills.clear();for(unsigned i=0;i<3;++i){skills[i]->m_bEnabled=true;skills[i]->m_bExecutedByProperty=false;first->m_OtherSkills.add(skills[i]);}skills[4]->m_bEnabled=true;skills[4]->m_bExecutedByProperty=false;}
    equipment->m_pSkillManager=(c.seed/400)%2?NULL:first;
    if(c.mode)equipment->m_pSkillManager=first;
    CDataGroup data(L"ITEM",0,4,4,0);equipment->m_pDataGroup=&data;
    static const int levels[]={1,0,-1,99,2147483647,(-2147483647-1)};
    if(c.seed%7)data.AddDataValue(L"LEVEL",static_cast<unsigned int>(levels[c.seed%6]));
    unsigned count=(c.seed/800)%4;
    for(unsigned i=0;i<count;++i){CDataGroup* g=data.AddDataGroup(L"SKILL_TO_GIVE");unsigned mode=(c.seed/7+i)%5;
        if(mode!=0)g->AddDataValue(L"NAME",mode==1?L"":mode==2?L"Fire":L"\x416 skill",false);
        if(mode>=3)g->AddDataValue(L"DISPLAYNAME",mode==3?L"":L"Shown",false);
        if((c.seed+i)%3)g->AddDataValue(L"LEVEL",static_cast<unsigned int>(levels[(c.seed/3+i)%6]));
    }
    data.AddDataGroup(L"SKILL")->AddDataValue(L"NAME",std::wstring(L"unrelated"),false);
    detour::Set patches;TL_REDIRECT(patches,sdSingleton,&singleton);TL_REDIRECT(patches,sdTranslate,&translate);TL_REDIRECT(patches,sdDescription,&description);if(patches.failed())_exit(42);
    for(unsigned repeat=0;repeat<2;++repeat){text(ours?equipment->skillDescription():originalEquipmentSkillDescription(equipment));number(calls);number(first->m_OtherSkills.size());number(equipment->m_pSkillManager==second);}
    patches.restore();first->m_OtherSkills.~TArrayList<CSkill*>();second->m_OtherSkills.~TArrayList<CSkill*>();
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_skill_description_differential){
    int failures=0;
    for(unsigned n=0;n<3500;++n){Case c={n<3200?n:(n-3200)%100+2400,n<3200?0u:1+(n-3200)/100};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok)host->log("    skill description seed %u mode %u status %d/%d lengths %lu/%lu\n",c.seed,c.mode,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
        TL_CHECK(failures,ok);if(!ok)return failures;
    }
    host->log("    equipment skill description: 3500 cases, two calls per side\n");return failures;
}
