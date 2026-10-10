#include <cstring>
#include "StatsMenuFill.h"
#include "AutoTest.h"
TL_ORIGINAL(void,oldSpent,(CStatsMenuFill*,int),"_ZN14CStatsMenuFill18addExperienceSpentEi")
extern "C" void newSpent(CStatsMenuFill*,int) __asm__("_ZN14CStatsMenuFill18addExperienceSpentEi");
namespace {
struct Case {unsigned present,pattern,spent;int amount;};
void side(const Case& c,bool ours,autotest::Capture& out){
 unsigned long long menuData[64],playerData[0x900/8];
 std::memset(menuData,c.pattern?0x5a:0xa5,sizeof(menuData));
 std::memset(playerData,c.pattern?0xa5:0x5a,sizeof(playerData));
 CStatsMenuFill* menu=reinterpret_cast<CStatsMenuFill*>(menuData);
 menu->m_pPlayer=c.present?reinterpret_cast<CPlayer*>(playerData):0;
 std::memcpy(reinterpret_cast<char*>(playerData)+0x880,&c.spent,4);
 if(ours)autotest::invoke(out,&newSpent,menu,c.amount);
 else autotest::invoke(out,&oldSpent,menu,c.amount);
 // Remove only the temporary allocation's address from otherwise complete state.
 unsigned identity=menu->m_pPlayer==reinterpret_cast<CPlayer*>(playerData)?1:menu->m_pPlayer==0?0:2;
 out.add(&identity,sizeof(identity));if(identity==2)out.add(&menu->m_pPlayer,sizeof(menu->m_pPlayer));menu->m_pPlayer=0;
 out.add(menuData,sizeof(menuData));out.add(playerData,sizeof(playerData));
}
void originalSide(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}
void candidateSide(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(stats_fill_spent_differential){
 autotest::Coverage coverage("stats_fill_spent_differential",reinterpret_cast<uintptr_t>(&oldSpent));
 const unsigned values[]={0u,1u,2u,37u,100u,2147483647u,2147483648u,4294967196u,4294967295u};
 const int amounts[]={(-2147483647-1),-2147483647,-100,-1,0,1,2,37,2147483647};
 for(unsigned present=0;present<2;++present)for(unsigned pattern=0;pattern<2;++pattern)
 for(unsigned i=0;i<9;++i)for(unsigned j=0;j<9;++j){
  Case c={present,pattern,values[i],amounts[j]};autotest::Outcome a,b;
  autotest::runChild(originalSide,&c,a);autotest::runChild(candidateSide,&c,b);
  int difference=coverage.observe(host,a,b);
  if(difference||autotest::incomplete(a)||autotest::incomplete(b)||a.childStatus||b.childStatus){
   coverage.report(host);host->log("    spent case %u/%u/%u/%u\n",present,pattern,i,j);return 1;
  }
 }
 coverage.report(host);return 0;
}
