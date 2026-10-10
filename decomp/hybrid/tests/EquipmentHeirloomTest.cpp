#include <cstring>
#include <new>
#include <limits>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "EffectManager.h"
#include "Effect.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, originalHeirloom,(CEquipment*),"_ZN10CEquipment15improveHeirloomEv")
TL_FUNCTION(heCombat,"_ZN10CEquipment20calculateCombatStatsEb")
TL_FUNCTION(heRequirements,"_ZN10CEquipment15setRequirementsEv")
TL_FUNCTION(heClear,"_ZN14CEffectManager20clearOutDescriptionsEv")
TL_FUNCTION(heBase,"_ZN7CEffect18calculateBaseValueENS_15ECALCULATETYPESE")
TL_FUNCTION(heValue,"_ZN7CEffect5valueE14EEFFECT_VALUES")
extern "C" void tracedoriginalHeirloom(CEquipment*) __asm__("_ZN10CEquipment15improveHeirloomEv");
namespace {
typedef char effect_size[sizeof(CEffect)==0x138?1:-1];
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T*get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned n,mode,count,trigger;int rank;};const Case*input;autotest::Capture*capture;
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}
TArrayList<CEffect*>&list(CEffectManager*m,unsigned a){return *reinterpret_cast<TArrayList<CEffect*>*>(m->m_EffectData10+0x18+a*0x18);}
struct World;World*world;detour::Set*valuePatch;
struct World{
 Raw<CEquipment>item;Raw<CEffectManager>managers[2];Raw<CEffect>effects[9];unsigned valueCalls,baseCalls;bool changed;
 World():valueCalls(0),baseCalls(0),changed(false){for(unsigned m=0;m<2;++m)for(unsigned a=0;a<3;++a){new(&list(managers[m].get(),a))TArrayList<CEffect*>;unsigned count=m?1:((input->count>>(a*2))&3);for(unsigned i=0;i<count;++i)list(managers[m].get(),a).add(effects[(a*2+i+m)%9].get());}
  static const float values[]={0.0f,-0.0f,1.0f,-1.0f,0.1f,17.25f,100000.125f,std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};
  for(unsigned i=0;i<9;++i){effects[i].get()->m_fValueC0=values[(input->n+i)%10];effects[i].get()->m_fValueC4=values[(input->n/10+i+3)%10];effects[i].get()->m_fValueC8=values[(input->n/100+i+6)%10];}
 }
 ~World(){for(unsigned m=0;m<2;++m)for(unsigned a=0;a<3;++a)list(managers[m].get(),a).~TArrayList<CEffect*>();}
 int id(CEffect*e){for(unsigned i=0;i<9;++i)if(e==effects[i].get())return i;return -1;}
};
void mutate(unsigned call){
 if(call!=input->trigger)return;
 if(input->mode==3)world->item.get()->m_pEffectManager=world->managers[1].get();
 if(input->mode==4)for(unsigned a=0;a<3;++a)if(list(world->managers[0].get(),a).size())list(world->managers[0].get(),a)[0]=world->effects[8].get();
 if(input->mode==5&&!world->changed){world->changed=true;for(unsigned a=0;a<3;++a)list(world->managers[0].get(),a).add(world->effects[8].get());}
 if(input->mode==6)for(unsigned i=0;i<9;++i)world->effects[i].get()->m_fValueC0=71.125f;
 if(input->mode==7)for(unsigned a=0;a<3;++a)list(world->managers[0].get(),a).m_nCount=0;
}
void combat(CEquipment*p,bool f){number(10);number(p==world->item.get());number(f);if(input->mode==1)p->m_iUnknown28C=10;if(input->mode==2){p->m_iUnknown28C=9;p->m_pEffectManager=world->managers[1].get();}}
void requirements(CEquipment*p){number(11);number(p==world->item.get());}
void clear(CEffectManager*p){number(12);number(p==world->managers[0].get()?0:1);}
float value(CEffect*p,EEFFECT_VALUES v){number(13);number(world->id(p));number(v);++world->valueCalls;valuePatch->restore();typedef float(*Function)(CEffect*,EEFFECT_VALUES);float result=reinterpret_cast<Function>(heValue_original)(p,v);TL_REDIRECT(*valuePatch,heValue,&value);if(valuePatch->failed())_exit(45);mutate(world->valueCalls+world->baseCalls);return result;}
void base(CEffect*p,CEffect::ECALCULATETYPES t){number(14);number(world->id(p));number(t);real(p->m_fValueC0);real(p->m_fValueC4);real(p->m_fValueC8);++world->baseCalls;p->m_fValueC0=static_cast<float>(world->baseCalls)+0.375f;mutate(world->valueCalls+world->baseCalls);}
void side(const Case&c,bool ours,autotest::Capture&out){input=&c;capture=&out;World w;world=&w;CEquipment*p=w.item.get();p->m_iUnknown28C=c.rank;p->m_pEffectManager=c.n%11?w.managers[0].get():NULL;
 if(c.mode==8)for(unsigned a=0;a<3;++a)if(list(w.managers[0].get(),a).size()>1)list(w.managers[0].get(),a).m_nCapacity=1;
 detour::Set patches,values;valuePatch=&values;TL_REDIRECT(patches,heCombat,&combat);TL_REDIRECT(patches,heRequirements,&requirements);TL_REDIRECT(patches,heClear,&clear);TL_REDIRECT(patches,heBase,&base);TL_REDIRECT(values,heValue,&value);if(patches.failed()||values.failed())_exit(42);
 for(unsigned repeat=0;repeat<2;++repeat){if(repeat==0){autotest::invoke(out,ours?&tracedoriginalHeirloom:&originalHeirloom,p);}else{if(ours)p->improveHeirloom();else originalHeirloom(p);}number(p->m_iUnknown28C);number(w.valueCalls);number(w.baseCalls);for(unsigned i=0;i<9;++i){real(w.effects[i].get()->m_fValueC0);real(w.effects[i].get()->m_fValueC4);real(w.effects[i].get()->m_fValueC8);}for(unsigned m=0;m<2;++m)for(unsigned a=0;a<3;++a)number(list(w.managers[m].get(),a).size());}
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_heirloom_differential){
autotest::Coverage coverage0("equipment_heirloom_differential",(uint64_t)(uintptr_t)&originalHeirloom);
int failures=0;for(unsigned n=0;n<4608;++n){static const int ranks[]={-2,0,8,9,10,11};Case c={n,0,n%64,1,ranks[(n/64)%6]};if(n>=2304){unsigned q=n-2304;c.mode=1+(q/256)%8;c.rank=9;c.trigger=1+(q/64)%4;c.count=1+(q%63);}
 autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage0.observe(host,a,b);bool ok=pair==0&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    heirloom case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok){coverage0.report(host);return failures;}}host->log("    heirloom: 4608 cases, two calls per side\n");{coverage0.report(host);return failures;}}
