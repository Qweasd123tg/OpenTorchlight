#include <cstring>
#include <new>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "EffectManager.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalElemental,(CEquipment*),"_ZN10CEquipment22createElementalDamagesEv")
TL_FUNCTION(elIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(elAdd,"_ZN10CEquipment14addDamageBonusE13EDAMAGE_TYPESi")
TL_FUNCTION(elDead,"_ZN14CEffectManager17deleteDeadEffectsEv")
TL_FUNCTION(elParticles,"_ZN10CEquipment15createParticlesEv")
extern "C" void tracedoriginalElemental(CEquipment*) __asm__("_ZN10CEquipment22createElementalDamagesEv");
namespace {
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T*get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned n,count,flags,mode;};const Case*input;autotest::Capture*capture;
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}
TArrayList<CEffect*>&list(CEffectManager*m){return *reinterpret_cast<TArrayList<CEffect*>*>(m->m_EffectData10+0x18);}
struct World;World*world;
struct World{Raw<CEquipment>item;Raw<CCharacter>actor;Raw<CEffectManager>managers[2];Raw<CEffect>effects[6];unsigned adds,dead,particles;bool changed;
 World():adds(0),dead(0),particles(0),changed(false){for(unsigned j=0;j<2;++j)new(&list(managers[j].get()))TArrayList<CEffect*>;for(unsigned i=0;i<input->count;++i)list(managers[0].get()).add(effects[i].get());list(managers[1].get()).add(effects[5].get());static const int types[]={52,10,51,11};static const float values[]={-2.8f,-0.2f,0,0.8f,1.2f,19.7f};for(unsigned i=0;i<6;++i){effects[i].get()->m_eType=static_cast<EEFFECT_TYPE>(types[(input->n/8+i)%4]);effects[i].get()->m_eDamageType=static_cast<EDAMAGE_TYPES>((input->n/32+i)%8);effects[i].get()->m_fValueC0=values[(input->n/256+i)%6];effects[i].get()->m_fValue24=3.25f+i;}}
 ~World(){for(unsigned j=0;j<2;++j)list(managers[j].get()).~TArrayList<CEffect*>();}
};
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){number(10);number(p==world->item.get());number(t);if(input->mode==1)world->item.get()->m_pEffectManager=world->managers[1].get();return input->flags&1;}
void add(CEquipment*p,EDAMAGE_TYPES type,int amount){number(11);number(p==world->item.get());number(type);number(amount);++world->adds;if(!world->changed){world->changed=true;if(input->mode==2)list(world->managers[0].get()).add(world->effects[5].get());if(input->mode==3&&list(world->managers[0].get()).size())list(world->managers[0].get())[0]=world->effects[5].get();if(input->mode==4)world->item.get()->m_pEffectManager=world->managers[1].get();}}
void dead(CEffectManager*p){number(12);number(p==world->managers[0].get()?0:1);++world->dead;for(unsigned i=0;i<6;++i)real(world->effects[i].get()->m_fValue24);if(input->mode==5)world->item.get()->m_pEquippedTo=world->actor.get();if(input->mode==6)world->item.get()->m_pEquippedTo=NULL;}
void particles(CEquipment*p){number(13);number(p==world->item.get());++world->particles;}
void side(const Case&c,bool ours,autotest::Capture&out){input=&c;capture=&out;World w;world=&w;CEquipment*p=w.item.get();p->m_pEffectManager=c.flags&2?NULL:w.managers[0].get();p->m_pEquippedTo=c.flags&4?w.actor.get():NULL;if(c.mode==7&&c.count>1)list(w.managers[0].get()).m_nCapacity=1;if(c.mode==8)list(w.managers[0].get()).m_nCount=0x80000000u;
 detour::Set patches;TL_REDIRECT(patches,elIsa,&isa);TL_REDIRECT(patches,elAdd,&add);TL_REDIRECT(patches,elDead,&dead);TL_REDIRECT(patches,elParticles,&particles);if(patches.failed())_exit(42);
 for(unsigned repeat=0;repeat<2;++repeat){if(repeat==0){autotest::invoke(out,ours?&tracedoriginalElemental:&originalElemental,p);}else{if(ours)p->createElementalDamages();else originalElemental(p);}number(w.adds);number(w.dead);number(w.particles);for(unsigned i=0;i<6;++i){real(w.effects[i].get()->m_fValueC0);real(w.effects[i].get()->m_fValue24);}number(list(w.managers[0].get()).size());}
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_elemental_differential){
autotest::Coverage coverage0("equipment_elemental_differential",(uint64_t)(uintptr_t)&originalElemental);
int failures=0;for(unsigned n=0;n<4608;++n){Case c={n,(n/8)%5,n%8,n/512};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage0.observe(host,a,b);bool ok=pair==0&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    elemental case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok){coverage0.report(host);return failures;}}host->log("    elemental: 4608 cases, two calls per side\n");{coverage0.report(host);return failures;}}
