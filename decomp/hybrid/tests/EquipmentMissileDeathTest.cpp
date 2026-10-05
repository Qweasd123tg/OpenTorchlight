#include <cstring>
#include <new>
#include <stdexcept>
#include <dlfcn.h>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "Missile.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalMissileDeath,(CEquipment*,CMissile*),"_ZN10CEquipment13missileDieingEP8CMissile")
TL_FUNCTION(mdRemove,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
// Both the original method and the blob link this low-address ELF PLT entry.
// Observe that shared call boundary; the library implementation stays untouched.
extern "C" char mdFree[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
namespace {
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T*get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned n,count,pattern,target,mode;};const Case*input;autotest::Capture*capture;
void number(int n){capture->add(&n,sizeof(n));}
struct World;World*world;detour::Set*removePatch;detour::Set*freePatch;char*realFree;
struct World{
 Raw<CEquipment>item;Raw<CMissile>missiles[2];TSafePointer<CMissile>*refs[6];bool freed[6];bool changed;unsigned removes,frees;
 World():changed(false),removes(0),frees(0){new(&item.get()->m_ActiveMissileRefs)TArrayList<TSafePointer<CMissile>*>(1);unsigned bits=input->pattern;for(unsigned i=0;i<6;++i){freed[i]=false;refs[i]=OGRE_NEW_T(TSafePointer<CMissile>,Ogre::MEMCATEGORY_GENERAL)();unsigned role=bits%3;bits/=3;if(role)refs[i]->setObject(missiles[role-1].get());if(i<input->count)item.get()->m_ActiveMissileRefs.add(refs[i]);}}
 ~World(){for(unsigned i=0;i<6;++i)if(!freed[i]){OGRE_FREE(refs[i],Ogre::MEMCATEGORY_GENERAL);}item.get()->m_ActiveMissileRefs.~TArrayList<TSafePointer<CMissile>*>();for(unsigned j=0;j<2;++j)delete missiles[j].get()->m_pSafePointers;}
 int id(const void*p){for(unsigned i=0;i<6;++i)if(p==refs[i])return i;return p?-2:-1;}
 int owner(CRunicCore*p){return p==missiles[0].get()?0:p==missiles[1].get()?1:p?-2:-1;}
};
void release(void*p){int id=world->id(p);number(20);number(id);if(id<0||world->freed[id])_exit(49);number(world->refs[id]->getObject()==NULL);number(world->refs[id]->m_nIndex);world->freed[id]=true;++world->frees;freePatch->restore();reinterpret_cast<void(*)(void*)>(realFree)(p);freePatch->redirect(mdFree,mdFree,&release);if(freePatch->failed())_exit(48);}
void remove(CRunicCore*p,TSafePointer<void*>*ref,unsigned index){number(10);number(world->owner(p));number(world->id(ref));number(index);++world->removes;
 if(input->mode==4&&!world->changed){world->changed=true;throw std::runtime_error("remove");}
 removePatch->restore();typedef void(*Function)(CRunicCore*,TSafePointer<void*>*,unsigned);reinterpret_cast<Function>(mdRemove_original)(p,ref,index);TL_REDIRECT(*removePatch,mdRemove,&remove);if(removePatch->failed())_exit(47);
 if(!world->changed){world->changed=true;TArrayList<TSafePointer<CMissile>*>&list=world->item.get()->m_ActiveMissileRefs;
  unsigned at=0;while(at<list.size()&&list[at]!=reinterpret_cast<TSafePointer<CMissile>*>(ref))++at;
  if(input->mode==1&&at<list.size())list[at]=world->refs[5];
  if(input->mode==2)list.add(world->refs[5]);
  if(input->mode==3&&at<list.size())list.m_nCount=at+1;
  if(input->mode==5)for(unsigned i=0;i<5;++i)if(world->refs[i]!=reinterpret_cast<TSafePointer<CMissile>*>(ref)&&!world->freed[i]){world->refs[i]->setObject(NULL);break;}
 }
}
void side(const Case&c,bool ours,autotest::Capture&out){input=&c;capture=&out;World w;world=&w;realFree=reinterpret_cast<char*>(dlsym(RTLD_DEFAULT,"_ZN4Ogre12NedAllocImpl12deallocBytesEPv"));if(!realFree)_exit(46);detour::Set removals,deallocations;removePatch=&removals;freePatch=&deallocations;TL_REDIRECT(removals,mdRemove,&remove);deallocations.redirect(mdFree,mdFree,&release);if(removals.failed()||deallocations.failed())_exit(42);CEquipment*p=w.item.get();CMissile*target=c.target<2?w.missiles[c.target].get():NULL;
 for(unsigned repeat=0;repeat<2;++repeat){try{if(ours)p->CEquipment::missileDieing(target);else originalMissileDeath(p,target);number(0);}catch(const std::runtime_error&e){number(std::strcmp(e.what(),"remove")==0?1:2);}
 number(w.removes);number(w.frees);number(p->m_ActiveMissileRefs.size());for(unsigned i=0;i<p->m_ActiveMissileRefs.size();++i)number(w.id(p->m_ActiveMissileRefs[i]));
 // Grow-by-one initializes every allocated slot. Compare inactive tail slots
 // as pointer identities too; never dereference a freed reference.
 number(p->m_ActiveMissileRefs.m_nCapacity); for(unsigned i=0;i<p->m_ActiveMissileRefs.m_nCapacity;++i)number(w.id(p->m_ActiveMissileRefs.m_pData[i]));
 for(unsigned i=0;i<6;++i){number(w.freed[i]);if(!w.freed[i]){number(w.owner(w.refs[i]->getObject()));number(w.refs[i]->m_nIndex);}}
 for(unsigned j=0;j<2;++j){TArrayList<TSafePointer<void*>*>*list=w.missiles[j].get()->m_pSafePointers;number(list?list->size():0);if(list)for(unsigned i=0;i<list->size();++i)number(w.id((*list)[i]));}}
 removals.restore();deallocations.restore();
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_missile_death_differential){int failures=0;for(unsigned n=0;n<5832;++n){Case c={n,n%6,(n/6)%243,(n/1458)%3,0};if(n>=4374){unsigned q=n-4374;c.count=1+q%5;c.pattern=q%243;c.target=q%3;c.mode=1+(q/243)%5;}
 autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    missile death case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok)return failures;}host->log("    missile death: 5832 cases, real safe-pointer lists and observed Ogre frees\n");return failures;}
