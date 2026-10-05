#include <cstring>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalRenderBehind,(CEquipment*,bool),"_ZN10CEquipment15setRenderBehindEb")
TL_FUNCTION(rbModel,"_ZN13CGenericModel15setRenderBehindEb")
namespace {
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T*get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned n,flags,mode;};const Case*input;autotest::Capture*capture;
void number(int n){capture->add(&n,sizeof(n));}
struct World;World*world;
struct World{Raw<CEquipment>item;Raw<CGenericModel>models[4];Raw<Ogre::Entity>entities[6];void*table[64];unsigned modelsCalled,queuesCalled;
 World():modelsCalled(0),queuesCalled(0){std::memset(table,0,sizeof(table));for(unsigned i=0;i<6;++i)*reinterpret_cast<void***>(entities[i].get())=table;for(unsigned i=0;i<4;++i)models[i].get()->m_pEntity=entities[i].get();}
 int modelID(CGenericModel*p){for(unsigned i=0;i<4;++i)if(p==models[i].get())return i;return -1;}
 int entityID(Ogre::Entity*p){for(unsigned i=0;i<6;++i)if(p==entities[i].get())return i;return -1;}
};
void model(CGenericModel*p,bool behind){number(10);number(world->modelID(p));number(behind);++world->modelsCalled;if(input->mode==1)world->item.get()->m_pUnitModel=world->models[2].get();if(input->mode==2)world->item.get()->m_pUnitModelSecondary=world->models[3].get();if(input->mode==3)p->m_pEntity=world->entities[4].get();if(input->mode==6&&world->modelID(p)!=0)world->item.get()->m_pUnitModelSecondary=world->models[2].get();}
void queue(Ogre::Entity*p,Ogre::uint8 group){number(11);number(world->entityID(p));number(group);++world->queuesCalled;if(input->mode==4)world->item.get()->m_pUnitModelSecondary=world->models[3].get();if(input->mode==5)world->item.get()->m_pUnitModelSecondary=NULL;}
void side(const Case&c,bool ours,autotest::Capture&out){input=&c;capture=&out;World w;world=&w;w.table[0x140/8]=reinterpret_cast<void*>(&queue);w.item.get()->m_pUnitModel=c.flags&1?NULL:w.models[0].get();w.item.get()->m_pUnitModelSecondary=c.flags&2?NULL:w.models[1].get();detour::Set patches;TL_REDIRECT(patches,rbModel,&model);if(patches.failed())_exit(42);
 for(unsigned repeat=0;repeat<2;++repeat){bool behind=(c.n+repeat)%2;if(ours)w.item.get()->setRenderBehind(behind);else originalRenderBehind(w.item.get(),behind);number(w.modelsCalled);number(w.queuesCalled);number(w.modelID(w.item.get()->m_pUnitModel));number(w.modelID(w.item.get()->m_pUnitModelSecondary));}
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_renderbehind_differential){int failures=0;for(unsigned n=0;n<224;++n){Case c={n,(n/2)%4,(n/8)%7};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    render-behind case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok)return failures;}host->log("    render-behind: 224 cases, two calls per side\n");return failures;}
