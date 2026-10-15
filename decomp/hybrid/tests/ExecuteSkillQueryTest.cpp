#include <cstring>
#include <string>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(std::wstring, oldSkillStats, (void*,void*,int), "_ZN18CExecuteSkillProps13getSkillStatsEP9CBaseUniti")
TL_ORIGINAL(std::wstring, oldSkillDescription, (void*,void*,int), "_ZN18CExecuteSkillProps19getSkillDescriptionEP9CBaseUniti")
extern "C" std::wstring newSkillStats(void*,void*,int) __asm__("_ZN18CExecuteSkillProps13getSkillStatsEP9CBaseUniti");
extern "C" std::wstring newSkillDescription(void*,void*,int) __asm__("_ZN18CExecuteSkillProps19getSkillDescriptionEP9CBaseUniti");
TL_FUNCTION(addSkillTarget,"_ZN13CSkillManager8addSkillERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(levelSkillTarget,"_ZN6CSkill32_setLevelOfSkillFromSkillManagerEj")
TL_FUNCTION(skillStatsTarget,"_ZN6CSkill18getSkillLevelStatsEP9CBaseUnitj")
TL_FUNCTION(skillDescriptionTarget,"_ZN6CSkill14getDescriptionEP9CBaseUnitjb")
namespace {
struct Case {uint64_t object[12],skill[8],returned[8],manager[4],unit[4];unsigned operation,mode,mutation;int level;std::wstring name;};
Case* input;autotest::Capture* output;unsigned calls;
void invalid(){output->issue=autotest::Capture::InvalidReport;}
void number(unsigned n){output->add(&n,4);}
void step(unsigned expected){if(++calls!=expected)invalid();number(expected);}
void* addSkill(void* manager,const std::wstring& name,bool flag){
    if(manager!=input->manager||name!=input->name||flag)invalid();number(manager==input->manager);output->addText(name);number(flag);step(1);
    if(input->mutation){void* zero=0;std::memcpy((char*)input->object+0x10,&zero,8);std::memcpy((char*)input->skill+0x20,&zero,8);}
    return input->mode==3?0:input->returned;
}
void setLevel(void* skill,unsigned level){if(skill!=(input->mode==3?0:input->returned)||level!=(unsigned)input->level)invalid();number(skill!=0);number(level);step(2);}
std::wstring result(void* skill,void* unit,unsigned level,bool flag,unsigned operation){
    if(skill!=(input->mode==3?0:input->returned)||unit!=(input->mode==4?0:input->unit)||level!=(unsigned)input->level||flag||input->operation!=operation)invalid();
    number(skill!=0);number(unit!=0);number(level);number(flag);step(3);std::wstring text=L"query";text+=wchar_t(0);text+=wchar_t(0x416+operation);return text;
}
std::wstring stats(void* s,void* u,unsigned n){return result(s,u,n,false,0);}
std::wstring description(void* s,void* u,unsigned n,bool flag){return result(s,u,n,flag,1);}
void body(Case& c,bool ours,autotest::Capture& out){
    input=&c;output=&out;calls=0;detour::Set patches;TL_REDIRECT(patches,addSkillTarget,&addSkill);TL_REDIRECT(patches,levelSkillTarget,&setLevel);TL_REDIRECT(patches,skillStatsTarget,&stats);TL_REDIRECT(patches,skillDescriptionTarget,&description);if(patches.failed()){invalid();return;}
    typedef std::wstring(*Fn)(void*,void*,int);Fn fn=c.operation?(ours?newSkillDescription:oldSkillDescription):(ours?newSkillStats:oldSkillStats);if(!autotest::beginInvocation(out,fn))return;
    std::wstring value=fn(c.object,c.mode==4?0:c.unit,c.level);out.callCompleted=1;
    unsigned expectedCalls=c.mode<2?0:3;if(calls!=expectedCalls)invalid();{std::wstring expected;if(c.mode>=2){expected=L"query";expected+=wchar_t(0);expected+=wchar_t(0x416+c.operation);}if(value!=expected)invalid();}
    number(calls);out.addText(value);out.add(c.object,sizeof(c.object));out.add(c.skill,sizeof(c.skill));out.add(c.returned,sizeof(c.returned));out.add(c.manager,sizeof(c.manager));out.add(c.unit,sizeof(c.unit));
}
void before(void* p,autotest::Capture& out){body(*(Case*)p,false,out);}void after(void* p,autotest::Capture& out){body(*(Case*)p,true,out);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address){
    autotest::Coverage coverage(name,address);const int levels[]={-1,0,1,(-2147483647-1),2147483647};
    for(unsigned n=0;n<5*5*2*3;++n){Case c;std::memset(c.object,0x93,sizeof(c.object));std::memset(c.skill,0xa1,sizeof(c.skill));std::memset(c.returned,0xb1,sizeof(c.returned));std::memset(c.manager,0xc1,sizeof(c.manager));std::memset(c.unit,0xd1,sizeof(c.unit));c.operation=operation;c.mode=n%5;c.level=levels[n/5%5];c.mutation=n/25%2;c.name=n/50%3==0?L"":n/50%3==1?L"SKILL":L"Имя";if(n/50%3==2){c.name+=wchar_t(0);c.name+=L"tail";}
        void* skill=c.mode==0?0:c.skill;void* manager=c.mode==1?0:c.manager;std::memcpy((char*)c.object+0x10,&skill,8);std::memcpy((char*)c.skill+0x20,&manager,8);new ((char*)c.object+0x20) std::wstring(c.name);
        autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);((std::wstring*)((char*)c.object+0x20))->~basic_string();if(coverage.observe(host,a,b)){host->log("    skill query seed %u exits %d/%d issue %u/%u\n",n,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);coverage.report(host);return 1;}}
    coverage.report(host);return 0;
}
}
TL_TEST(execute_skill_stats_query){return run(host,0,"execute_skill_stats_query",(uintptr_t)&oldSkillStats);}
TL_TEST(execute_skill_description_query){return run(host,1,"execute_skill_description_query",(uintptr_t)&oldSkillDescription);}
