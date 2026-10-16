#include <cstring>
#include <stdint.h>
#include <string>
#include <map>
#include "AutoTest.h"
#define private public
#include "Achievements.h"
#include "Achievement.h"
#undef private
TL_ORIGINAL(CAchievement*,oName,(CAchievements*,std::string),"_ZN13CAchievements14getAchievementESs")
extern "C" CAchievement*nName(CAchievements*,std::string) __asm__("_ZN13CAchievements14getAchievementESs");
namespace {
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=*static_cast<unsigned*>(raw);uint64_t ms[(sizeof(CAchievements)+7)/8],as[6][(sizeof(CAchievement)+7)/8];CAchievements*self=reinterpret_cast<CAchievements*>(ms);new(&self->m_achievements)TArrayList<CAchievement*>(2);std::string names[]={"","a","A","aa",std::string("a\0b",3),"Ж"};for(unsigned i=0;i<6;++i){CAchievement*a=reinterpret_cast<CAchievement*>(as[i]);new(&a->m_strName)std::string(names[(seed/3+i)%6]);if(i<seed%7)self->m_achievements.add(a);}if((seed&16)&&self->m_achievements.size())self->m_achievements.m_nCapacity=(seed/8)%2;CAchievement*(*fn)(CAchievements*,std::string)=ours?nName:oName;if(!autotest::beginInvocation(out,fn))return;CAchievement*r=fn(self,names[(seed/6)%6]);out.callCompleted=1;int identity=r?-2:-1;for(unsigned i=0;i<6;++i)if(r==reinterpret_cast<CAchievement*>(as[i]))identity=i;out.add(&identity,4);for(unsigned i=0;i<6;++i){out.addText(reinterpret_cast<CAchievement*>(as[i])->m_strName);reinterpret_cast<CAchievement*>(as[i])->m_strName.~basic_string();}self->m_achievements.~TArrayList();}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(state_achievement_name){autotest::Coverage coverage("state_achievement_name",(uintptr_t)&oName);for(unsigned seed=0;seed<120;++seed){autotest::Outcome x,y;autotest::runChild(a,&seed,x);autotest::runChild(b,&seed,y);if(coverage.observe(host,x,y)){host->log("    achievement name seed %u issue %u/%u exits %d/%d\n",seed,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
