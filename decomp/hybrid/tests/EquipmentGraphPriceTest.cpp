#include <cstring>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "GraphManager.h"
#include "GameGlobals.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalGraphDamage,(CEquipment*,unsigned),"_ZN10CEquipment14setGraphDamageEj")
TL_ORIGINAL(void,originalGraphArmor,(CEquipment*,unsigned),"_ZN10CEquipment10setGraphACEj")
TL_ORIGINAL(int,originalEnchantPrice,(CEquipment*),"_ZN10CEquipment12enchantPriceEv")
TL_FUNCTION(gpManager,"_ZN13CGraphManager12getSingletonEv")
TL_FUNCTION(gpGraph,"_ZN13CGraphManager8getGraphERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(gpValue,"_ZNK6CGraph8getValueEfj")
TL_FUNCTION(gpGlobals,"_ZN12CGameGlobals12getSingletonEv")
extern "C" void tracedoriginalGraphDamage(CEquipment*,unsigned) __asm__("_ZN10CEquipment14setGraphDamageEj");
extern "C" void tracedoriginalGraphArmor(CEquipment*,unsigned) __asm__("_ZN10CEquipment10setGraphACEj");
extern "C" int tracedoriginalEnchantPrice(CEquipment*) __asm__("_ZN10CEquipment12enchantPriceEv");
namespace {
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T*get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned n,kind,percentage,mode;int rank,count;float value,coefficient;};const Case*input;autotest::Capture*capture;CEquipment*item;CGameGlobals*globals;unsigned long long managerToken,graphTokens[3];unsigned graphID;
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}
CGraphManager*manager(){number(10);if(input->mode==1)item->m_iUnknown274=17;return reinterpret_cast<CGraphManager*>(&managerToken);}
CGraph*graph(CGraphManager*p,const std::wstring&name){number(11);number(p==reinterpret_cast<CGraphManager*>(&managerToken));graphID=name==L"BASE_WEAPON_DAMAGE"?0:name==L"ARMOR_PLAYER_BYLEVEL_FORSET"?1:name==L"PRICE_ENCHANT"?2:3;number(graphID);if(graphID==3)_exit(43);if(input->mode==2){item->m_iUnknown274=23;item->m_iUnknown28C=4;}return reinterpret_cast<CGraph*>(&graphTokens[graphID]);}
float value(const CGraph*p,float level,unsigned line){number(12);number(p==reinterpret_cast<CGraph*>(&graphTokens[graphID]));real(level);number(line);if(input->mode==3)item->m_iUnknown28C=10;if(input->mode==4)item->m_iUnknown344=7;return input->value;}
CGameGlobals*global(){number(13);if(input->mode==5)item->m_iUnknown344=9;return globals;}
void side(const Case&c,bool ours,autotest::Capture&out){Raw<CEquipment>a;Raw<CGameGlobals>b;item=a.get();globals=b.get();input=&c;capture=&out;item->m_iUnknown274=static_cast<int>(c.n%30)-5;item->m_iUnknown28C=c.rank;item->m_iUnknown344=c.count;globals->m_fEnchanterPricePerEnchant=c.coefficient;
 detour::Set patches;TL_REDIRECT(patches,gpManager,&manager);TL_REDIRECT(patches,gpGraph,&graph);TL_REDIRECT(patches,gpValue,&value);TL_REDIRECT(patches,gpGlobals,&global);if(patches.failed())_exit(42);
 for(unsigned repeat=0;repeat<2;++repeat){if(c.kind==0){if(repeat==0){autotest::invoke(out,ours?&tracedoriginalGraphDamage:&originalGraphDamage,item,c.percentage);}else{if(ours)item->setGraphDamage(c.percentage);else originalGraphDamage(item,c.percentage);}}else if(c.kind==1){if(repeat==0){autotest::invoke(out,ours?&tracedoriginalGraphArmor:&originalGraphArmor,item,c.percentage);}else{if(ours)item->setGraphAC(c.percentage);else originalGraphArmor(item,c.percentage);}}else if(repeat==0){autotest::invoke(out,ours?&tracedoriginalEnchantPrice:&originalEnchantPrice,item);}else{number(ours?item->enchantPrice():originalEnchantPrice(item));}number(item->m_iMaximumDamage);number(item->m_iMinimumDamage);number(item->m_iUnknown340);number(item->m_iUnknown338);number(item->m_iUnknown33C);number(item->m_iUnknown28C);number(item->m_iUnknown344);}
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_graph_price_differential){
autotest::Coverage coverage0("equipment_graph_price_differential",(uint64_t)(uintptr_t)&originalGraphDamage);autotest::Coverage coverage1("equipment_graph_price_differential",(uint64_t)(uintptr_t)&originalGraphArmor);autotest::Coverage coverage2("equipment_graph_price_differential",(uint64_t)(uintptr_t)&originalEnchantPrice);
int failures=0;for(unsigned n=0;n<9072;++n){unsigned q=n/3;static const int ranks[]={-2,0,4,5,6,10};static const unsigned percentages[]={20,50,99,100,101,200};static const float values[]={-0.1f,0.0f,0.1f,1.2f,19.9f,299.9f,301.0f};static const float coefficients[]={-0.1f,0.0f,0.05f,0.1f,1.0f};Case c={n,n%3,percentages[(q/6)%6],(q/504)%6,ranks[q%6],static_cast<int>((q/36)%7),values[(q/36)%7],coefficients[(q/252)%5]};if(c.kind==2&&q%11==0){c.count=-1;c.value=0.000001f;c.coefficient=0.1f;}
 autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=(c.kind==0?coverage0:c.kind==1?coverage1:coverage2).observe(host,a,b);bool ok=pair==0&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    graph price case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok){coverage0.report(host);coverage1.report(host);coverage2.report(host);return failures;}}host->log("    graph price: 9072 cases, three entries, two calls per side\n");{coverage0.report(host);coverage1.report(host);coverage2.report(host);return failures;}}
