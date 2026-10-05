#include <cstring>
#include <new>
#include <vector>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "EffectManager.h"
#include "Effect.h"
#undef private
#undef protected
#include "AutoTest.h"
TL_ORIGINAL(void,originalInherentAdd,(CEquipment*,EDAMAGE_TYPES,int),"_ZN10CEquipment17addInherentDamageE13EDAMAGE_TYPESi")
TL_ORIGINAL(void,originalBonusAdd,(CEquipment*,EDAMAGE_TYPES,int),"_ZN10CEquipment14addDamageBonusE13EDAMAGE_TYPESi")
TL_ORIGINAL(int,originalDamageBonus,(CEquipment*,EDAMAGE_TYPES),"_ZN10CEquipment14getDamageBonusE13EDAMAGE_TYPES")
namespace {
typedef char effect_damage_offset[__builtin_offsetof(CEffect,m_eDamageType)==0x14?1:-1];
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T*get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned seed,kind;};
TArrayList<CEffect*>&passive(CEffectManager*m){return *reinterpret_cast<TArrayList<CEffect*>*>(m->m_EffectData10+0x18);}
struct World{
 Raw<CEquipment>item,children[3];Raw<CEffectManager>managers[3];Raw<CEffect>effects[12];
 World(unsigned n){CEquipment*p=item.get();new(&p->m_ElementalDamageTypes)std::vector<EDAMAGE_TYPES>;new(&p->m_ElementalDamageBonuses)std::vector<int>;new(&p->m_InherentElementalDamage)std::vector<int>;new(&p->m_SocketedEquipment)TArrayList<CEquipment*>;
 if(n&1)p->m_ElementalDamageTypes.reserve(8);if(n&2)p->m_ElementalDamageBonuses.reserve(8);if(n&4)p->m_InherentElementalDamage.reserve(8);
 for(unsigned i=0;i<(n/8)%5;++i){p->m_ElementalDamageTypes.push_back(static_cast<EDAMAGE_TYPES>((n/40+i%2)%8));p->m_ElementalDamageBonuses.push_back(static_cast<int>((n+i*7)%21)-10);p->m_InherentElementalDamage.push_back(static_cast<int>((n/3+i*11)%31)-15);}
 static const float vals[]={-3.8f,-1.2f,-0.8f,0.0f,0.2f,0.8f,1.2f,4.7f};static const int types[]={10,52,9,51};
 for(unsigned i=0;i<12;++i){effects[i].get()->m_eType=static_cast<EEFFECT_TYPE>(types[(n/7+i)%4]);effects[i].get()->m_eDamageType=static_cast<EDAMAGE_TYPES>((n/5+i%3)%8);effects[i].get()->m_fValueC0=vals[(n/11+i)%8];}
 for(unsigned j=0;j<3;++j){new(&passive(managers[j].get()))TArrayList<CEffect*>;unsigned count=(n/13+j)%5;for(unsigned i=0;i<count;++i)passive(managers[j].get()).add(effects[(j*4+i)%12].get());children[j].get()->m_pEffectManager=(n/17+j)%4?managers[j].get():NULL;if((n/19+j)%5==0&&count>1)passive(managers[j].get()).m_nCapacity=1;if(n>=3584&&j==1)passive(managers[j].get()).m_nCount=0x80000000u;}
 for(unsigned i=0;i<(n/23)%4;++i)p->m_SocketedEquipment.add(children[i].get());if(n%7==0&&p->m_SocketedEquipment.size()>1)p->m_SocketedEquipment.m_nCapacity=1;if(n>=3840)p->m_SocketedEquipment.m_nCount=0x80000000u;
 }
 ~World(){for(unsigned i=0;i<3;++i)passive(managers[i].get()).~TArrayList<CEffect*>();CEquipment*p=item.get();p->m_SocketedEquipment.~TArrayList<CEquipment*>();p->m_ElementalDamageTypes.~vector<EDAMAGE_TYPES>();p->m_ElementalDamageBonuses.~vector<int>();p->m_InherentElementalDamage.~vector<int>();}
};
void number(autotest::Capture&c,int n){c.add(&n,sizeof(n));}
template<class T>void captureVector(autotest::Capture&c,const std::vector<T>&v){number(c,v.size());number(c,v.capacity());for(unsigned i=0;i<v.size();++i)number(c,v[i]);}
void side(const Case&c,bool ours,autotest::Capture&out){World w(c.seed);CEquipment*p=w.item.get();EDAMAGE_TYPES type=static_cast<EDAMAGE_TYPES>((c.seed/3)%8);int amount=static_cast<int>((c.seed/5)%15)-7;
 for(unsigned repeat=0;repeat<2;++repeat){if(c.kind==0){if(ours)p->addInherentDamage(type,amount);else originalInherentAdd(p,type,amount);}else if(c.kind==1){if(ours)p->addDamageBonus(type,amount);else originalBonusAdd(p,type,amount);}else{int result=ours?p->getDamageBonus(type):originalDamageBonus(p,type);number(out,result);}
 captureVector(out,p->m_ElementalDamageTypes);captureVector(out,p->m_ElementalDamageBonuses);captureVector(out,p->m_InherentElementalDamage);}
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_damage_arrays_differential){int failures=0;for(unsigned n=0;n<12288;++n){Case c={n/3,n%3};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    damage arrays case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok)return failures;}host->log("    damage arrays: 12288 cases, three entries, two calls per side\n");return failures;}
