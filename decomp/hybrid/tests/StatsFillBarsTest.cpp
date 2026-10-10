#include <cstring>
#include <limits>
#include <fenv.h>
#include "StatsMenuFill.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldFill,(CStatsMenuFill*,ESTATSMENU_STATS,float),"_ZN14CStatsMenuFill11fillIntoBarE16ESTATSMENU_STATSf")
TL_ORIGINAL(void,oldRemove,(CStatsMenuFill*,ESTATSMENU_STATS,float),"_ZN14CStatsMenuFill13removeFromBarE16ESTATSMENU_STATSf")
TL_ORIGINAL(void,oldUpdate,(CStatsMenuFill*,float),"_ZN14CStatsMenuFill6updateEf")
extern "C" void newFill(CStatsMenuFill*,ESTATSMENU_STATS,float) __asm__("_ZN14CStatsMenuFill11fillIntoBarE16ESTATSMENU_STATSf");
extern "C" void newRemove(CStatsMenuFill*,ESTATSMENU_STATS,float) __asm__("_ZN14CStatsMenuFill13removeFromBarE16ESTATSMENU_STATSf");
extern "C" void newUpdate(CStatsMenuFill*,float) __asm__("_ZN14CStatsMenuFill6updateEf");
TL_FUNCTION(addAmountFn,"_ZN14CStatsMenuFill18getAmountOfXPToAddE16ESTATSMENU_STATSf")
TL_FUNCTION(removeAmountFn,"_ZN14CStatsMenuFill21getAmountOfXPToRemoveE16ESTATSMENU_STATSf")
TL_FUNCTION(totalFn,"_ZN14CStatsMenuFill21getStatBarTotalAmountE16ESTATSMENU_STATS")
TL_FUNCTION(visualFn,"_ZN14CStatsMenuFill13updateVisualsEv")
TL_FUNCTION(playFn,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(stopFn,"_ZN10CSoundBank4stopEi")
TL_FUNCTION(baseUpdateFn,"_ZN13CDropdownMenu6updateEf")
TL_FUNCTION(fillFn,"_ZN14CStatsMenuFill11fillIntoBarE16ESTATSMENU_STATSf")
TL_FUNCTION(removeFn,"_ZN14CStatsMenuFill13removeFromBarE16ESTATSMENU_STATSf")
namespace {
struct Case{unsigned kind,pattern,filling,alternate,addMask,removeMask;int which,current;float amount,total,elapsed,cooldown,countdown,interval;};
const Case* cs;autotest::Capture* cap;CStatsMenuFill* menu;CPlayer* players[2];CSoundBank* banks[2];
void n(int x){cap->add(&x,sizeof(x));}void f(float x){cap->add(&x,sizeof(x));}
void call(unsigned code,CStatsMenuFill* p,ESTATSMENU_STATS which,float elapsed){n(code);n(p==menu);n(which);f(elapsed);}
float addAmount(CStatsMenuFill* p,ESTATSMENU_STATS which,float elapsed){call(1,p,which,elapsed);return cs->amount;}
float removeAmount(CStatsMenuFill* p,ESTATSMENU_STATS which,float elapsed){call(2,p,which,elapsed);return cs->amount;}
float total(CStatsMenuFill* p,ESTATSMENU_STATS which){n(3);n(p==menu);n(which);if(cs->alternate)menu->m_pPlayer=players[1];return cs->total;}
void visual(CStatsMenuFill* p){n(4);n(p==menu);f(p->m_BarCooldown);n(p->m_Filling);if(cs->alternate)p->m_Filling=!p->m_Filling;}
void play(CSoundBank* p,int index,Ogre::SceneNode* node,float a,float b,bool c){n(5);n(p==banks[0]?0:p==banks[1]?1:99);n(index);n(node==0);f(a);f(b);n(c);if(cs->alternate)menu->m_pFillSoundBank=banks[1];}
void stop(CSoundBank* p,int index){n(6);n(p==banks[0]?0:p==banks[1]?1:99);n(index);}
void base(CDropdownMenu* p,float elapsed){n(7);n(p==menu);f(elapsed);if(cs->alternate){menu->m_BarCooldown=cs->cooldown;menu->m_FillSoundCountdown=cs->countdown;}}
void fill(CStatsMenuFill* p,ESTATSMENU_STATS which,float elapsed){call(8,p,which,elapsed);p->m_HeldTime=-7.5f;if(cs->alternate){p->m_FillSoundCountdown=cs->countdown;p->m_pFillSoundBank=banks[1];}}
void remove(CStatsMenuFill* p,ESTATSMENU_STATS which,float elapsed){call(9,p,which,elapsed);p->m_HeldTime=3.25f;if(cs->alternate){p->m_FillSoundCountdown=cs->countdown;p->m_pFillSoundBank=banks[1];}}
void set(void* p,unsigned offset,unsigned value){std::memcpy((char*)p+offset,&value,4);}
void canonical(unsigned char* snapshot,unsigned offset,void* a,void* b){void* p;std::memcpy(&p,snapshot+offset,8);if(p==a||p==b||p==0){uintptr_t value=p==a?1:p==b?2:0;std::memcpy(snapshot+offset,&value,8);}}
void side(const Case& c,bool ours,autotest::Capture& out){
 unsigned long long mem[0x1a8/8],playerMem[2][0x890/8],bankMem[2][8];std::memset(mem,c.pattern?0x5a:0xa5,sizeof(mem));std::memset(playerMem,c.pattern?0xa5:0x5a,sizeof(playerMem));std::memset(bankMem,0,sizeof(bankMem));cs=&c;cap=&out;menu=(CStatsMenuFill*)mem;
 for(unsigned i=0;i<2;++i){players[i]=(CPlayer*)playerMem[i];banks[i]=(CSoundBank*)bankMem[i];unsigned stats[]={0x42c,0x428,0x434,0x430},allocated[]={0x870,0x874,0x87c,0x878};for(unsigned j=0;j<4;++j){set(players[i],stats[j],c.pattern?2147483647u:10u+i*100u+j);set(players[i],allocated[j],static_cast<unsigned>(c.current)+i*13u+j*3u);}set(players[i],0x448,1000000u);set(players[i],0x880,c.pattern?4294967295u:17u+i);}
 menu->m_pPlayer=players[0];menu->m_pFillSoundBank=banks[0];menu->m_Filling=c.filling;menu->m_HeldTime=17.25f;menu->m_BarCooldown=c.cooldown;menu->m_FillSoundCountdown=c.countdown;menu->m_FillSoundInterval=c.interval;
 for(unsigned i=0;i<4;++i){menu->m_AddHeld[i]=(c.addMask&(1u<<i))!=0;menu->m_RemoveHeld[i]=(c.removeMask&(1u<<i))!=0;}
 detour::Set d;TL_REDIRECT(d,playFn,&play);TL_REDIRECT(d,stopFn,&stop);
 if(c.kind==2){TL_REDIRECT(d,baseUpdateFn,&base);TL_REDIRECT(d,fillFn,&fill);TL_REDIRECT(d,removeFn,&remove);}
 else{TL_REDIRECT(d,addAmountFn,&addAmount);TL_REDIRECT(d,removeAmountFn,&removeAmount);TL_REDIRECT(d,totalFn,&total);TL_REDIRECT(d,visualFn,&visual);}
 if(d.failed())_exit(61);
 ESTATSMENU_STATS which=static_cast<ESTATSMENU_STATS>(c.which);
 ::feclearexcept(FE_ALL_EXCEPT);
 if(c.kind==0){if(ours)autotest::invoke(out,&newFill,menu,which,c.elapsed);else autotest::invoke(out,&oldFill,menu,which,c.elapsed);}
 else if(c.kind==1){if(ours)autotest::invoke(out,&newRemove,menu,which,c.elapsed);else autotest::invoke(out,&oldRemove,menu,which,c.elapsed);}
 else{if(ours)autotest::invoke(out,&newUpdate,menu,c.elapsed);else autotest::invoke(out,&oldUpdate,menu,c.elapsed);}
 n(::fetestexcept(FE_ALL_EXCEPT));
 unsigned char snapshot[sizeof(mem)];std::memcpy(snapshot,mem,sizeof(snapshot));canonical(snapshot,0x160,players[0],players[1]);canonical(snapshot,0x180,banks[0],banks[1]);cap->add(snapshot,sizeof(snapshot));cap->add(playerMem,sizeof(playerMem));cap->add(bankMem,sizeof(bankMem));
}
void a(void* p,autotest::Capture& out){side(*(Case*)p,false,out);}void b(void* p,autotest::Capture& out){side(*(Case*)p,true,out);}
bool compare(autotest::Coverage& coverage,const tlhybrid_host* host,Case& c){autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int diff=coverage.observe(host,u,v);if(diff||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus){coverage.report(host);size_t first=0;while(first<u.capture.length&&first<v.capture.length&&u.capture.data[first]==v.capture.data[first])++first;host->log("    bar kind %u stat %d current %d amount %g total %g alternate %u exits %d/%d first %lu lengths %lu/%lu\n",c.kind,c.which,c.current,c.amount,c.total,c.alternate,u.childStatus,v.childStatus,(unsigned long)first,(unsigned long)u.capture.length,(unsigned long)v.capture.length);return false;}return true;}
int bars(const tlhybrid_host* host,unsigned kind){autotest::Coverage coverage(kind?"stats_fill_remove_differential":"stats_fill_add_differential",kind?(uintptr_t)&oldRemove:(uintptr_t)&oldFill);const int currents[]={0,99,-3};const float amounts[]={-1.f,0.f,.999f,1.f,1.75f,100.f,2147483648.f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN(),-std::numeric_limits<float>::infinity()};const float totals[]={100.f,-1.f,std::numeric_limits<float>::quiet_NaN()};
 for(unsigned pattern=0;pattern<2;++pattern)for(unsigned filling=0;filling<2;++filling)for(unsigned alt=0;alt<2;++alt)for(int which=-1;which<=4;++which)for(unsigned current=0;current<3;++current)for(unsigned amount=0;amount<10;++amount)for(unsigned total=0;total<(kind?1u:3u);++total){Case c={kind,pattern,filling,alt,5,10,which,currents[current],amounts[amount],totals[total],.125f,.3f,-.1f,.5f};if(!compare(coverage,host,c))return 1;}
 coverage.report(host);return 0;}
}
TL_TEST(stats_fill_add_differential){return bars(host,0);}
TL_TEST(stats_fill_remove_differential){return bars(host,1);}
TL_TEST(stats_fill_tick_differential){
 autotest::Coverage coverage("stats_fill_tick_differential",(uintptr_t)&oldUpdate);const unsigned masks[]={0,1,2,4,8,15};const float times[]={-1.f,0.f,.125f,std::numeric_limits<float>::quiet_NaN()};
 for(unsigned alt=0;alt<2;++alt)for(unsigned add=0;add<6;++add)for(unsigned remove=0;remove<6;++remove)for(unsigned delta=0;delta<4;++delta)for(unsigned cool=0;cool<4;++cool)for(unsigned countdown=0;countdown<4;++countdown){Case c={2,alt,alt,alt,masks[add],masks[remove],0,0,0,0,times[delta],times[cool],times[countdown],alt?.5f:0.f};if(!compare(coverage,host,c))return 1;}
 coverage.report(host);return 0;
}
