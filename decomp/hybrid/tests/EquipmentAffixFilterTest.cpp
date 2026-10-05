#include <cstring>
#include <cstdlib>
#include <dlfcn.h>
#include <new>
#include <stdexcept>
#include <Ogre.h>
#define protected public
#define private public
#include "Equipment.h"
#include "EffectManager.h"
#include "Affix.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, originalAffixFilter,(CEquipment*,UNITTYPES::EUNITTYPES),"_ZN10CEquipment36removeAffixesThatDontSupportUnitTypeEN9UNITTYPES10EUNITTYPESE")
TL_ORIGINAL(void, originalContainerAdd,(CEquipment*,CEquipment*),"_ZN10CEquipment16addContainerItemEPS_")
TL_FUNCTION(afPredicate,"_ZN6CAffix22canBeAppliedToUnitTypeEj")
TL_FUNCTION(afDelete,"_ZN14CEffectManager11deleteAffixEP6CAffix")
TL_FUNCTION(afIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(afCalculate,"_ZN14CEffectManager21calculateEffectValuesEv")
namespace {
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T*get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned count,mask,mode,flags,existing,sockets;};
const Case*input;autotest::Capture*capture;bool container;
void number(int n){capture->add(&n,sizeof(n));}
struct World;World*world;
struct World {
 Raw<CEquipment>parent,item,other;Raw<CEffectManager>managers[2];unsigned long long tokens[6];unsigned predicateCalls,deleteCalls,calculateCalls;bool changed;
 World():predicateCalls(0),deleteCalls(0),calculateCalls(0),changed(false){for(unsigned m=0;m<2;++m)new(&managers[m].get()->getAffixes())TArrayList<CAffix*>(2);for(unsigned i=0;i<input->count;++i)managers[0].get()->getAffixes().add(affix(i));managers[1].get()->getAffixes().add(affix(5));new(&parent.get()->m_SocketedEquipment)TArrayList<CEquipment*>;for(unsigned i=0;i<input->existing;++i)parent.get()->m_SocketedEquipment.add(other.get());}
 ~World(){for(unsigned m=0;m<2;++m)managers[m].get()->getAffixes().~TArrayList<CAffix*>();parent.get()->m_SocketedEquipment.~TArrayList<CEquipment*>();}
 CAffix*affix(unsigned n){return reinterpret_cast<CAffix*>(&tokens[n]);}
 int id(CAffix*a){for(unsigned n=0;n<6;++n)if(a==affix(n))return n;return -1;}
};
bool predicate(CAffix*a,UNITTYPES::EUNITTYPES type){number(10);number(world->id(a));number(type);unsigned call=world->predicateCalls++;
 if(input->mode==1&&!world->changed){world->changed=true;world->managers[0].get()->getAffixes().add(world->affix(4));}
 if(input->mode==2)world->item.get()->m_pEffectManager=world->managers[1].get();
 if(input->mode==3&&world->managers[0].get()->getAffixes().size()>1)world->managers[0].get()->getAffixes()[1]=world->affix(5);
 if(input->mode==4&&call==1)throw std::runtime_error("predicate");
 return (input->mask>>(world->id(a)%6))&1;
}
bool deletion(CEffectManager*m,CAffix*a){number(11);number(m==world->managers[0].get()?0:m==world->managers[1].get()?1:2);number(world->id(a));unsigned call=world->deleteCalls++;
 if(input->mode==5)world->item.get()->m_pEffectManager=world->managers[1].get();
 if(input->mode==6&&call==1)throw std::runtime_error("deletion");
 TArrayList<CAffix*>&list=m->getAffixes();for(unsigned j=0;j<list.size();++j)if(list[j]==a){list.removeAt(j);return true;}return false;
}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){number(12);number(p==world->item.get());number(t);if(input->mode==8)world->parent.get()->m_eUnitType=UNITTYPES::ARMOR;return t==UNITTYPES::SOCKETABLE?(input->flags&2)!=0:t==UNITTYPES::RANDOMMAGIC_SOCKETABLE&&(input->flags&4)!=0;}
void calculate(CEffectManager*m){number(13);number(m==world->managers[0].get()?0:m==world->managers[1].get()?1:2);++world->calculateCalls;}
void side(const Case&c,bool ours,autotest::Capture&out){input=&c;capture=&out;World w;world=&w;CEquipment*p=w.parent.get();CEquipment*i=w.item.get();i->m_pEffectManager=c.flags&1?NULL:w.managers[0].get();p->m_iSocketCount=c.sockets;p->m_eUnitType=UNITTYPES::WEAPON;if(c.mode==7&&c.count>1)w.managers[0].get()->getAffixes().m_nCapacity=1;
 detour::Set patches;TL_REDIRECT(patches,afPredicate,&predicate);TL_REDIRECT(patches,afDelete,&deletion);TL_REDIRECT(patches,afIsa,&isa);TL_REDIRECT(patches,afCalculate,&calculate);if(patches.failed())_exit(42);
 typedef void (*Begin)(); typedef void (*End)(unsigned long long*,unsigned long long*);
 Begin begin=reinterpret_cast<Begin>(dlsym(RTLD_DEFAULT,"otl_begin_filter_heap_count")); End end=reinterpret_cast<End>(dlsym(RTLD_DEFAULT,"otl_end_filter_heap_count"));
 if(std::getenv("OTL_FILTER_HEAP_REQUIRED")&&(!begin||!end))_exit(43);
 for(unsigned repeat=0;repeat<2;++repeat){unsigned long long allocs=0,frees=0;if(begin&&end)begin();try{if(container){if(ours)p->addContainerItem(i);else originalContainerAdd(p,i);}else{if(ours)i->removeAffixesThatDontSupportUnitType(UNITTYPES::WEAPON);else originalAffixFilter(i,UNITTYPES::WEAPON);}number(0);}catch(const std::runtime_error&e){number(std::strcmp(e.what(),"predicate")==0?1:2);}
 if(begin&&end){end(&allocs,&frees);capture->add(&allocs,sizeof(allocs));capture->add(&frees,sizeof(frees));}
 number(w.predicateCalls);number(w.deleteCalls);number(w.calculateCalls);number(p->m_SocketedEquipment.size());for(unsigned j=0;j<p->m_SocketedEquipment.size();++j)number(p->m_SocketedEquipment[j]==i?1:0);number(i->m_pEffectManager==w.managers[1].get());
 for(unsigned m=0;m<2;++m){TArrayList<CAffix*>&list=w.managers[m].get()->getAffixes();number(list.size());for(unsigned j=0;j<list.size();++j)number(w.id(list[j]));}}
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_affixfilter_differential){int failures=0;container=false;for(unsigned n=0;n<5120;++n){Case c={n%5,(n/5)%64,(n/320)%8,(n/2560)%2,0,0};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    affix filter case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok)return failures;}host->log("    affix filter: 5120 cases, two calls per side\n");return failures;}
TL_TEST(equipment_container_differential){int failures=0;container=true;for(unsigned n=0;n<5760;++n){Case c={3,(n*37)%64,(n/640)%9,n%8,(n/8)%5,(n/40)%8};if(c.sockets==7)c.sockets=~0u;autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    container case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok)return failures;}host->log("    container: 5760 cases, two calls per side\n");return failures;}
