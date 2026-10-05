#include <cstring>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "Level.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(int,originalBuyPrice,(CEquipment*),"_ZN10CEquipment8buyPriceEv")
TL_ORIGINAL(int,originalSellPrice,(CEquipment*),"_ZN10CEquipment9sellPriceEv")
TL_FUNCTION(tpPlayer,"_ZN6CLevel9getPlayerEv")
TL_FUNCTION(tpEffect,"_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
namespace {
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T*get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned n,kind,flags,mode;int stack,buy,sell;float modifier;};const Case*input;autotest::Capture*capture;
void number(int n){capture->add(&n,sizeof(n));}
struct World;World*world;
struct World{Raw<CEquipment>item;Raw<CCharacter>actors[2];Raw<CResourceManager>managers[2];unsigned long long levels[2];unsigned players,effects;World():players(0),effects(0){for(unsigned i=0;i<2;++i)managers[i].get()->m_pLevel=reinterpret_cast<CLevel*>(&levels[i]);}};
CCharacter*player(CLevel*p){unsigned id=p==reinterpret_cast<CLevel*>(&world->levels[0])?0:p==reinterpret_cast<CLevel*>(&world->levels[1])?1:2;number(10);number(id);++world->players;if(input->mode==1)world->item.get()->m_pResourceManager=world->managers[1].get();if(input->mode==2){world->item.get()->m_iUnknown264=999;world->item.get()->m_iUnknown268=777;}return input->flags&8?NULL:world->actors[id%2].get();}
float effect(CCharacter*p,EEFFECT_TYPE t,EDAMAGE_TYPES damage){number(11);number(p==world->actors[0].get()?0:1);number(t);number(damage);++world->effects;if(input->mode==3){world->item.get()->m_iUnknown238=9;world->item.get()->m_bUnknown348=false;}return input->modifier;}
void side(const Case&c,bool ours,autotest::Capture&out){input=&c;capture=&out;World w;world=&w;CEquipment*p=w.item.get();p->m_iUnknown238=c.stack;p->m_bUnknown348=(c.flags&1)!=0;p->m_iUnknown264=c.buy;p->m_iUnknown268=c.sell;p->m_iUnknown26C=c.buy+3;p->m_iUnknown270=c.sell+5;p->m_pResourceManager=c.flags&2?NULL:w.managers[0].get();if(c.flags&4)w.managers[0].get()->m_pLevel=NULL;detour::Set patches;TL_REDIRECT(patches,tpPlayer,&player);TL_REDIRECT(patches,tpEffect,&effect);if(patches.failed())_exit(42);
 for(unsigned repeat=0;repeat<2;++repeat){int result=c.kind==0?(ours?p->buyPrice():originalBuyPrice(p)):(ours?p->sellPrice():originalSellPrice(p));number(result);number(w.players);number(w.effects);number(p->m_iUnknown238);number(p->m_bUnknown348);}
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_trade_price_differential){int failures=0;for(unsigned n=0;n<8192;++n){unsigned q=n/2;static const int stacks[]={-3,0,1,2,10};static const int prices[]={-5,0,1,2,7,99,100,301};static const float mods[]={-150,-50,-0.1f,0,0.1f,25,99,100,101,150};Case c={n,n%2,q%16,(q/1024)%4,stacks[(q/16)%5],prices[(q/80)%8],prices[(q/80+3)%8],mods[(q/5)%10]};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    trade price case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok)return failures;}host->log("    trade price: 8192 cases, two entries, two calls per side\n");return failures;}
