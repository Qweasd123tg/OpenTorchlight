#include <cstring>
#include <new>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "AttackDescription.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(long,originalDPS,(CEquipment*),"_ZN10CEquipment3DPSEv")
TL_FUNCTION(dpBonus,"_ZN10CEquipment14getDamageBonusE13EDAMAGE_TYPES")
extern "C" long tracedoriginalDPS(CEquipment*) __asm__("_ZN10CEquipment3DPSEv");
namespace {
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T*get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned n,mode,count,slots;};const Case*input;autotest::Capture*capture;
void number(int n){capture->add(&n,sizeof(n));}
struct World;World*world;
struct World{Raw<CEquipment>item,children[3];Raw<CAttackDescription>attacks[2];unsigned calls;bool changed;
 World():calls(0),changed(false){new(&item.get()->m_SocketedEquipment)TArrayList<CEquipment*>(1);for(unsigned i=0;i<input->count;++i)item.get()->m_SocketedEquipment.add((input->n+i)%5?children[i%3].get():NULL);}
 ~World(){item.get()->m_SocketedEquipment.~TArrayList<CEquipment*>();}
 int id(CEquipment*p){if(p==item.get())return 0;for(unsigned i=0;i<3;++i)if(p==children[i].get())return i+1;return -1;}
};
int bonus(CEquipment*p,EDAMAGE_TYPES type){int id=world->id(p);number(10);number(id);number(type);++world->calls;
 if(input->mode==1){world->attacks[0].get()->m_fAttackSpeed=17.0f;world->attacks[1].get()->m_fAttackSpeed=19.0f;world->item.get()->m_iMaximumDamage=777;}
 if(input->mode==2)world->item.get()->m_iSocketCount=0;
 if(input->mode==3&&!world->changed){world->changed=true;world->item.get()->m_SocketedEquipment.add(world->children[2].get());}
 if(input->mode==4&&id>0&&!world->changed){world->changed=true;world->item.get()->m_iSocketCount=5;world->children[id-1].get()->m_iMaximumDamage=555;}
 if(input->mode==5&&world->item.get()->m_SocketedEquipment.size()>1)world->item.get()->m_SocketedEquipment[1]=world->children[2].get();
 return static_cast<int>((input->n+id*7+static_cast<int>(type)*11)%19)-9;
}
void side(const Case&c,bool ours,autotest::Capture&out){input=&c;capture=&out;World w;world=&w;CEquipment*p=w.item.get();p->m_iSocketCount=c.slots;p->m_iMaximumDamage=static_cast<int>(c.n%61)-30;p->m_pAttackDescription=w.attacks[0].get();p->m_pAttackDescriptionOverride=c.n&1?w.attacks[1].get():NULL;
 static const float speeds[]={0.25f,0.5f,0.75f,1.0f,1.25f,2.0f,-0.5f,-2.0f};for(unsigned i=0;i<2;++i)w.attacks[i].get()->m_fAttackSpeed=speeds[(c.n/3+i)%8];for(unsigned i=0;i<3;++i)w.children[i].get()->m_iMaximumDamage=static_cast<int>((c.n/5+i*3)%31)-15;
 if(c.mode==6&&c.count>1)p->m_SocketedEquipment.m_nCapacity=1;
 detour::Set patches;TL_REDIRECT(patches,dpBonus,&bonus);if(patches.failed())_exit(42);
 for(unsigned repeat=0;repeat<2;++repeat){if(repeat==0){autotest::invoke(out,ours?&tracedoriginalDPS:&originalDPS,p);}else{long value=ours?p->DPS():originalDPS(p);out.add(&value,sizeof(value));}number(w.calls);number(p->m_iSocketCount);number(p->m_SocketedEquipment.size());}
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_dps_differential){
autotest::Coverage coverage0("equipment_dps_differential",(uint64_t)(uintptr_t)&originalDPS);
int failures=0;for(unsigned n=0;n<3584;++n){Case c={n,n/512,n%4,(n/4)%6};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage0.observe(host,a,b);bool ok=pair==0&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    DPS case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok){coverage0.report(host);return failures;}}host->log("    DPS: 3584 cases, two calls per side\n");{coverage0.report(host);return failures;}}
