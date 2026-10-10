#include <cstring>
#include <cstdlib>
#include <new>
#include <vector>
#include <map>
#include <stdexcept>
#include <dlfcn.h>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "Missile.h"
#include "MasterResourceManager.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalEquipmentDestructor,(CEquipment*),"_ZN10CEquipmentD1Ev")
// Fixture construction helper, deliberately not marked TL_ORIGINAL coverage.
extern "C" void constructEquipment(CEquipment*,CResourceManager*) __asm__("__tlorig__ZN10CEquipmentC1EP16CResourceManager");
TL_FUNCTION(dtReset,"_ZN10CEquipment17resetVisualLayoutEv")
TL_FUNCTION(dtVisible,"_ZN5CItem10setVisibleEbb")
TL_FUNCTION(dtDetach,"_ZN10CEquipment18detachFromLocationEv")
TL_FUNCTION(dtIcon,"_ZN10CEquipment11destroyIconEv")
TL_FUNCTION(dtMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(dtCollision,"_ZN22CMasterResourceManager20removeCollisionModelEP15CCollisionModel")
extern "C" void tracedoriginalEquipmentDestructor(CEquipment*) __asm__("_ZN10CEquipmentD1Ev");
namespace {
typedef char equipment_size[sizeof(CEquipment)==0x438?1:-1];
typedef char pod398_offset[__builtin_offsetof(CEquipment,m_UnknownPOD398)==0x398?1:-1];
typedef char pod3b0_offset[__builtin_offsetof(CEquipment,m_UnknownPOD3B0)==0x3b0?1:-1];
typedef TSafePointer<CMissile> Reference;
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T* get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned seed,mode;};struct Fake{void** table;};struct World;
World* world;const Case* input;autotest::Capture* capture;
void number(int n){capture->add(&n,sizeof(n));}void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
struct World{Raw<CEquipment> item;Raw<CMissile> missile;Raw<CMasterResourceManager> master;Fake owned[15];void* table[2];bool destroyed[15];unsigned detaches;std::vector<Reference*> references;std::wstring aliases[6];World():detaches(0){std::memset(destroyed,0,sizeof(destroyed));for(unsigned i=0;i<15;++i)owned[i].table=table;new(&missile.get()->m_Listeners)TArrayList<iMissile*>(1);}int id(const void* p){if(!p)return -1;for(unsigned i=0;i<15;++i)if(p==&owned[i])return i;return -2;}int refId(const void* p){for(unsigned i=0;i<references.size();++i)if(p==references[i])return i;return -1;}};
void destroy(void* p){int id=world->id(p);number(10);number(id);if(id<0||world->destroyed[id])_exit(50);world->destroyed[id]=true;if(input->mode==2&&id==9)world->item.get()->m_SocketedEquipment.m_nCount=1;}
void reset(CEquipment* p){number(11);number(p==world->item.get());number(world->id(p->m_pPositionableObject));if(input->mode==1)p->m_pPositionableObject=NULL;if(input->mode==4)throw std::runtime_error("reset callback");}
void visible(CItem* p,bool a,bool b){number(12);number(p==world->item.get());number(a);number(b);p->m_bVisible=a;}
void detach(CEquipment* p){number(13);number(p==world->item.get());number(world->id(p->m_pInventory));number(world->id(p->m_pEquippedTo));++world->detaches;if(input->mode==3&&world->detaches==1)p->m_pSoundBank=NULL;}
void icon(CEquipment* p){number(14);number(p==world->item.get());number(p->m_pEntity==NULL);p->m_pIconWindow=NULL;}
CMasterResourceManager* master(){number(15);return world->master.get();}
void collision(CMasterResourceManager* p,CCollisionModel* model){number(16);number(p==world->master.get());number(world->id(model));}
void side(const Case& c,bool ours,autotest::Capture& out){input=&c;capture=&out;World w;world=&w;w.table[0]=w.table[1]=reinterpret_cast<void*>(&destroy);
 detour::Set patches;TL_REDIRECT(patches,dtReset,&reset);TL_REDIRECT(patches,dtVisible,&visible);TL_REDIRECT(patches,dtDetach,&detach);TL_REDIRECT(patches,dtIcon,&icon);TL_REDIRECT(patches,dtMaster,&master);TL_REDIRECT(patches,dtCollision,&collision);if(patches.failed())_exit(42);
 CEquipment* object=w.item.get();constructEquipment(object,NULL);
 object->m_pPositionableObject=c.seed&1?reinterpret_cast<CPositionableObject*>(&w.owned[0]):NULL;object->m_pParticle=c.seed&2?reinterpret_cast<CParticle*>(&w.owned[1]):NULL;object->m_pParticle_3D0=c.seed&4?reinterpret_cast<CParticle*>(&w.owned[2]):NULL;object->m_pSoundBank=c.seed&8?reinterpret_cast<CSoundBank*>(&w.owned[3]):NULL;object->m_pPath=c.seed&16?reinterpret_cast<CPath*>(&w.owned[4]):NULL;object->m_pAttackDescription=c.seed&32?reinterpret_cast<CAttackDescription*>(&w.owned[5]):NULL;object->m_pAttackDescriptionOverride=c.seed&64?reinterpret_cast<CAttackDescription*>(&w.owned[6]):NULL;object->m_pUnitModel=c.seed&128?reinterpret_cast<CGenericModel*>(&w.owned[7]):NULL;object->m_pUnitModelSecondary=c.seed&256?reinterpret_cast<CGenericModel*>(&w.owned[8]):NULL;
 object->m_pEntity=c.mode==4?NULL:reinterpret_cast<Ogre::Entity*>(&w.owned[11]);object->m_pInventory=reinterpret_cast<CInventory*>(&w.owned[12]);object->m_pEquippedTo=reinterpret_cast<CCharacter*>(&w.owned[13]);object->m_iUnitCollisionModel=c.seed&512?reinterpret_cast<long long>(&w.owned[14]):0;
 unsigned sockets=(c.seed/4)%4;if(sockets){object->m_SocketedEquipment.add(reinterpret_cast<CEquipment*>(&w.owned[9]));if(sockets>=2)object->m_SocketedEquipment.add(NULL);if(sockets==3)object->m_SocketedEquipment.add(reinterpret_cast<CEquipment*>(&w.owned[10]));}
 iMissile* self=static_cast<iMissile*>(object);unsigned listeners=(c.seed/16)%4;if(listeners){w.missile.get()->m_Listeners.add(reinterpret_cast<iMissile*>(&w.owned[11]));w.missile.get()->m_Listeners.add(listeners==2?reinterpret_cast<iMissile*>(object):self);if(listeners==3)w.missile.get()->m_Listeners.add(self);}
 unsigned refs=(c.seed/1024)%4;for(unsigned i=0;i<refs;++i){if(i==1&&(c.seed&2)){object->m_ActiveMissileRefs.add(NULL);continue;}Reference* r=OGRE_NEW_T(Reference,Ogre::MEMCATEGORY_GENERAL)();if(!(i==2&&(c.seed&4)))r->setObject(w.missile.get());object->m_ActiveMissileRefs.add(r);w.references.push_back(r);}
 for(unsigned i=0;i<3;++i){object->m_ElementalDamageTypes.push_back(DAMAGE_FIRE);object->m_ElementalDamageBonuses.push_back(17+i);object->m_InherentElementalDamage.push_back(23+i);object->m_UnknownPOD398.push_back(3+i);object->m_UnknownPOD3B0.push_back(7+i);}
 std::wstring* strings[]={&object->m_sUnidentifiedName,&object->m_sDisplayName,&object->m_sPrefix,&object->m_sSuffix,&object->m_sUnknown3D8,&object->m_sUnknown400};for(unsigned i=0;i<6;++i){*strings[i]=std::wstring(40+i,L'a'+i);w.aliases[i]=*strings[i];}
 void* addresses[]={&object->m_ElementalDamageTypes[0],&object->m_ElementalDamageBonuses[0],&object->m_InherentElementalDamage[0],&object->m_UnknownPOD398[0],&object->m_UnknownPOD3B0[0],object->m_SocketedEquipment.m_pData,object->m_ActiveMissileRefs.m_pData};
 typedef void(*Begin)(void**,unsigned);typedef unsigned(*End)(unsigned*,unsigned*,unsigned);Begin begin=reinterpret_cast<Begin>(dlsym(RTLD_DEFAULT,"otl_watch_frees"));End end=reinterpret_cast<End>(dlsym(RTLD_DEFAULT,"otl_end_frees"));if((begin==NULL)!=(end==NULL)||(std::getenv("OTL_FREES_REQUIRED")&&!begin))_exit(64);if(begin)begin(addresses,7);bool threw=false;
 try{if(true&&!(c.mode==4)){autotest::invoke(out,ours?&tracedoriginalEquipmentDestructor:&originalEquipmentDestructor,object);}else{if(ours)object->CEquipment::~CEquipment();else originalEquipmentDestructor(object);}}catch(const std::runtime_error& e){threw=true;unsigned n=std::strlen(e.what());number(n);capture->add(e.what(),n);}
 unsigned counts[7]={0},order[64]={0};unsigned orderSize=end?end(counts,order,64):0;if(begin){for(unsigned i=0;i<7;++i)if(counts[i]!=(addresses[i]?1u:0u))_exit(65);}number(threw);for(unsigned i=0;i<7;++i)number(counts[i]);number(orderSize);for(unsigned i=0;i<orderSize&&i<64;++i)number(order[i]);
 const size_t offsets[]={__builtin_offsetof(CEquipment,m_pPositionableObject),__builtin_offsetof(CEquipment,m_pParticle),__builtin_offsetof(CEquipment,m_pParticle_3D0),__builtin_offsetof(CEquipment,m_pSoundBank),__builtin_offsetof(CEquipment,m_pPath),__builtin_offsetof(CEquipment,m_pAttackDescription),__builtin_offsetof(CEquipment,m_pAttackDescriptionOverride),__builtin_offsetof(CEquipment,m_pUnitModel),__builtin_offsetof(CEquipment,m_pUnitModelSecondary),__builtin_offsetof(CEquipment,m_pInventory),__builtin_offsetof(CEquipment,m_pEquippedTo)};
 const unsigned char* storage=reinterpret_cast<const unsigned char*>(w.item.data);for(unsigned i=0;i<sizeof(offsets)/sizeof(offsets[0]);++i){void* value=NULL;std::memcpy(&value,storage+offsets[i],sizeof(value));number(value==NULL);}
 for(unsigned i=0;i<15;++i)number(w.destroyed[i]);number(w.detaches);for(unsigned i=0;i<6;++i)text(w.aliases[i]);
 // Inspect surviving external registries, not destroyed Equipment members.
 number(w.missile.get()->m_Listeners.size());for(unsigned i=0;i<w.missile.get()->m_Listeners.size();++i){iMissile* p=w.missile.get()->m_Listeners[i];number(p==self?1:p==reinterpret_cast<iMissile*>(object)?2:3);}unsigned remaining=w.missile.get()->m_pSafePointers?w.missile.get()->m_pSafePointers->size():0;number(remaining);for(unsigned i=0;i<remaining;++i)number(w.refId((*w.missile.get()->m_pSafePointers)[i]));
 while(w.missile.get()->m_pSafePointers&&w.missile.get()->m_pSafePointers->size()){Reference* r=reinterpret_cast<Reference*>((*w.missile.get()->m_pSafePointers)[0]);OGRE_DELETE_T(r,Reference,Ogre::MEMCATEGORY_GENERAL);}delete w.missile.get()->m_pSafePointers;w.missile.get()->m_Listeners.~TArrayList<iMissile*>();
 // Expired unregistered fixture refs are left to child-process teardown; no
 // potentially released pointer is dereferenced after the destructor call.
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_destructor_differential){
autotest::Coverage coverage0("equipment_destructor_differential",(uint64_t)(uintptr_t)&originalEquipmentDestructor);
int failures=0;for(unsigned n=0;n<4352;++n){Case c={n<4096?n:(n-4096)*16+1023,n<4096?0u:1+(n-4096)/64};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=0;if(!(c.mode==4))pair=coverage0.observe(host,a,b);bool ok=pair==0&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    destructor seed %u mode %u status %d/%d lengths %lu/%lu\n",c.seed,c.mode,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok){coverage0.report(host);return failures;}}host->log("    equipment destructor: 4352 cases, free watcher %s\n",dlsym(RTLD_DEFAULT,"otl_watch_frees")?"active":"not loaded");{coverage0.report(host);return failures;}}
