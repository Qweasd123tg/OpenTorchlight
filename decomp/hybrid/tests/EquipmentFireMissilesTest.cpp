#include <cstring>
#include <vector>
#include <new>
#include <Ogre.h>
#include <map>
#define protected public
#define private public
#include "Equipment.h"
#include "Character.h"
#include "GenericModel.h"
#include "Missile.h"
#include "MissilePreloader.h"
#include "DataGroup.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool,originalEquipmentFireMissiles,(CEquipment*,CCharacter*,CCharacter*),"_ZN10CEquipment12fireMissilesEP10CCharacterS1_")
TL_FUNCTION(fmLeft,"_ZN10CCharacter19getWeaponInLeftHandEv")
TL_FUNCTION(fmPreloader,"_ZN16CResourceManager19getMissilePreloaderEv")
TL_FUNCTION(fmCreate,"_ZN17CMissilePreloader19createNewMissileRefEP16CResourceManagerRKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(fmFire,"_ZN8CMissile11fireMissileEP9CBaseUnitN4Ogre7Vector3ERKNS2_10QuaternionEP19CPositionableObjectS3_")
extern "C" bool recoveredEquipmentFireMissiles(CEquipment*,CCharacter*,CCharacter*) __asm__("_ZN10CEquipment12fireMissilesEP10CCharacterS1_");
extern "C" void* fireEquipmentTable[] __asm__("_ZTV10CEquipment");
extern "C" void* fireCharacterTable[] __asm__("_ZTV10CCharacter");
namespace {
typedef char equipment_size[sizeof(CEquipment)==0x438?1:-1];
typedef char character_size[sizeof(CCharacter)==0x778?1:-1];
typedef char listeners_offset[__builtin_offsetof(CMissile,m_Listeners)==0x1c8?1:-1];
typedef char refs_offset[__builtin_offsetof(CEquipment,m_ActiveMissileRefs)==0x410?1:-1];
typedef TSafePointer<CMissile> Reference;
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T* get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned seed,mode,warm;};
struct Snapshot{const unsigned char* base;std::vector<unsigned char> bytes;Snapshot(const void* p,size_t n):base(static_cast<const unsigned char*>(p)),bytes(base,base+n){}void pointer(const void* field,uintptr_t id){size_t at=static_cast<const unsigned char*>(field)-base;if(at+sizeof(id)>bytes.size())_exit(71);std::memcpy(&bytes[at],&id,sizeof(id));}void emit(autotest::Capture& out){out.add(&bytes[0],bytes.size());}};struct World;
World* world;const Case* input;autotest::Capture* capture;
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}void vector(const Ogre::Vector3& v){real(v.x);real(v.y);real(v.z);}void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
struct World{
 Raw<CEquipment> item,other;Raw<CCharacter> shooter,target,equipped;Raw<CMissile> missile;Raw<CGenericModel> model;Raw<Ogre::Entity> entity;Raw<CResourceManager> resources;Raw<CMissilePreloader> preloader;
 void* itemTable[110];void* shooterTable[132];void* entityTable[64];Ogre::SceneNode left,right,targetParent,targetNode;Ogre::AxisAlignedBox box;CDataGroup data;unsigned fires,models;
 World():left(NULL),right(NULL),targetParent(NULL),targetNode(NULL),data(L"ACTOR",0,4,4,0),fires(0),models(0){std::memcpy(itemTable,fireEquipmentTable+2,sizeof(itemTable));std::memcpy(shooterTable,fireCharacterTable+2,sizeof(shooterTable));std::memset(entityTable,0,sizeof(entityTable));void** t=itemTable;std::memcpy(item.get(),&t,sizeof(t));t=shooterTable;std::memcpy(shooter.get(),&t,sizeof(t));t=entityTable;std::memcpy(entity.get(),&t,sizeof(t));new(&item.get()->m_sUnknown400)std::wstring();new(&item.get()->m_ActiveMissileRefs)TArrayList<Reference*>(2);new(&missile.get()->m_Listeners)TArrayList<iMissile*>(2);targetParent.addChild(&targetNode);}
 ~World(){for(unsigned i=0;i<item.get()->m_ActiveMissileRefs.size();++i){Reference* r=item.get()->m_ActiveMissileRefs[i];OGRE_DELETE_T(r,Reference,Ogre::MEMCATEGORY_GENERAL);}number(missile.get()->m_pSafePointers?missile.get()->m_pSafePointers->size():0);delete missile.get()->m_pSafePointers;item.get()->m_ActiveMissileRefs.~TArrayList<Reference*>();missile.get()->m_Listeners.~TArrayList<iMissile*>();typedef std::wstring Text;item.get()->m_sUnknown400.~Text();}
};
iMissile* listener(){return static_cast<iMissile*>(world->item.get());}
int listenerId(iMissile* p){return p==listener()?1:p==static_cast<iMissile*>(world->other.get())?2:p==reinterpret_cast<iMissile*>(world->item.get())?3:0;}
CEquipment* leftWeapon(CCharacter* p){number(10);number(p==world->shooter.get());return (input->seed/16)%2?world->item.get():world->other.get();}
void* getModel(CEquipment* p){number(11);number(p==world->item.get());++world->models;return input->seed&8?world->model.get():NULL;}
const Ogre::AxisAlignedBox& bounds(const Ogre::Entity* p){number(12);number(p==world->entity.get());return world->box;}
CMissilePreloader* preloader(CResourceManager* p){number(13);number(p==world->resources.get());return world->preloader.get();}
CMissile* create(CMissilePreloader* p,CResourceManager* r,const std::wstring& name){number(14);number(p==world->preloader.get());number(r==world->resources.get());text(name);if(input->mode==1){world->targetNode.translate(Ogre::Vector3(1,2,3));world->target.get()->m_vPosition=world->targetNode.getPosition();}if(input->mode==2)world->item.get()->m_pEquippedTo=world->target.get();return input->seed&4?world->missile.get():NULL;}
void fire(CMissile* p,CBaseUnit* owner,Ogre::Vector3 origin,const Ogre::Quaternion& q,CPositionableObject* target,Ogre::Vector3 position){number(15);number(p==world->missile.get());number(owner==world->equipped.get()?1:owner==world->target.get()?2:0);vector(origin);real(q.w);real(q.x);real(q.y);real(q.z);number(target==world->target.get());vector(position);number(p->m_Listeners.size());for(unsigned i=0;i<p->m_Listeners.size();++i)number(listenerId(p->m_Listeners[i]));number(world->item.get()->m_ActiveMissileRefs.size());++world->fires;}
void side(const Case& c,bool ours,autotest::Capture& out){input=&c;capture=&out;World w;world=&w;w.itemTable[60]=reinterpret_cast<void*>(&getModel);w.entityTable[27]=reinterpret_cast<void*>(&bounds);
 w.item.get()->m_sUnknown400=c.seed&1?L"Missiles/SEEKINGSHOT":L"";w.item.get()->m_pResourceManager=w.resources.get();w.item.get()->m_pEquippedTo=w.equipped.get();w.shooter.get()->m_pLeftHandNode=&w.left;w.shooter.get()->m_pRightHandNode=&w.right;w.shooter.get()->m_pDataGroup=&w.data;w.shooter.get()->m_vForward=Ogre::Vector3(0.5f,0.25f,1.0f);w.target.get()->m_pSceneNode=&w.targetNode;w.target.get()->m_pParentPositionableObject=w.equipped.get();w.equipped.get()->m_pSceneNode=&w.targetParent;w.targetParent.setPosition(10,2,-3);w.model.get()->m_pEntity=w.entity.get();w.left.setPosition(-2,1,3);w.right.setPosition(4,2,-1);
 unsigned targetMode=(c.seed/32)%3;Ogre::Vector3 origin=(c.seed/16)%2?w.left.getPosition():w.right.getPosition();w.targetNode.setPosition((targetMode==2?origin:Ogre::Vector3(8,3,-5))-w.targetParent.getPosition());if(c.mode==3){w.left.setPosition(0,0,0);w.right.setPosition(0,0,0);w.targetParent.setPosition(0,0,0);w.targetNode.setPosition(Ogre::Vector3(0.000000001f,0,0));}
 w.target.get()->m_vPosition=w.targetNode.getPosition();
 unsigned scale=(c.seed/96)%4;if(scale)w.data.AddDataValue(L"WEAPON_SCALE",scale==1?0.0f:scale==2?0.5f:2.0f);
 unsigned box=(c.seed/1536)%3;if(box==0)w.box.setNull();else if(box==1)w.box.setExtents(-1,-2,-3,4,5,6);else w.box.setInfinite();
 unsigned list=(c.seed/384)%4;if(list==1){w.missile.get()->m_Listeners.add(static_cast<iMissile*>(w.other.get()));w.missile.get()->m_Listeners.add(reinterpret_cast<iMissile*>(w.item.get()));}if(list==2)w.missile.get()->m_Listeners.add(listener());if(list==3)w.missile.get()->m_Listeners.add(reinterpret_cast<iMissile*>(w.item.get()));
 for(unsigned i=0;i<list%3;++i){Reference* r=OGRE_NEW_T(Reference,Ogre::MEMCATEGORY_GENERAL)();r->setObject(w.missile.get());w.item.get()->m_ActiveMissileRefs.add(r);}
 detour::Set patches;TL_REDIRECT(patches,fmLeft,&leftWeapon);TL_REDIRECT(patches,fmPreloader,&preloader);TL_REDIRECT(patches,fmCreate,&create);TL_REDIRECT(patches,fmFire,&fire);if(patches.failed())_exit(42);
 for(unsigned repeat=0;repeat<=c.warm;++repeat){CCharacter* shooter=c.seed&2?w.shooter.get():NULL;CCharacter* target=targetMode?w.target.get():NULL;typedef bool (*Fn)(CEquipment*,CCharacter*,CCharacter*);Fn fn=ours?&recoveredEquipmentFireMissiles:&originalEquipmentFireMissiles;if(repeat==c.warm)autotest::invoke(out,fn,w.item.get(),shooter,target);else {bool result=fn(w.item.get(),shooter,target);number(result);}number(w.fires);number(w.models);number(w.missile.get()->m_Listeners.size());for(unsigned i=0;i<w.missile.get()->m_Listeners.size();++i)number(listenerId(w.missile.get()->m_Listeners[i]));number(w.item.get()->m_ActiveMissileRefs.size());for(unsigned i=0;i<w.item.get()->m_ActiveMissileRefs.size();++i){Reference* r=w.item.get()->m_ActiveMissileRefs[i];number(r->getObject()==w.missile.get());number(r->m_nIndex);}number(w.missile.get()->m_pSafePointers?w.missile.get()->m_pSafePointers->size():0);}
 Snapshot eq(w.item.get(),sizeof(CEquipment));eq.pointer(w.item.get(),*reinterpret_cast<void***>(w.item.get())==w.itemTable?1:255);eq.pointer(&w.item.get()->m_pResourceManager,w.item.get()->m_pResourceManager==w.resources.get()?1:255);eq.pointer(&w.item.get()->m_pEquippedTo,w.item.get()->m_pEquippedTo==w.equipped.get()?1:w.item.get()->m_pEquippedTo==w.target.get()?2:255);eq.pointer(&w.item.get()->m_sUnknown400,1);eq.pointer(&w.item.get()->m_ActiveMissileRefs.m_pData,w.item.get()->m_ActiveMissileRefs.m_pData?1:0);eq.emit(out);text(w.item.get()->m_sUnknown400);
 Snapshot ms(w.missile.get(),sizeof(CMissile));ms.pointer(&w.missile.get()->m_Listeners.m_pData,w.missile.get()->m_Listeners.m_pData?1:0);ms.pointer(&w.missile.get()->m_pSafePointers,w.missile.get()->m_pSafePointers?1:0);ms.emit(out);
 if(w.missile.get()->m_pSafePointers){number(w.missile.get()->m_pSafePointers->m_nCapacity);number(w.missile.get()->m_pSafePointers->m_nGrowBy);for(unsigned i=0;i<w.missile.get()->m_pSafePointers->size();++i){void* p=(*w.missile.get()->m_pSafePointers)[i];unsigned id=0;while(id<w.item.get()->m_ActiveMissileRefs.size()&&p!=w.item.get()->m_ActiveMissileRefs[id])++id;number(id);}}
 vector(w.left.getPosition());vector(w.right.getPosition());vector(w.targetNode.getPosition());vector(w.targetParent.getPosition());vector(w.target.get()->m_vPosition);vector(w.shooter.get()->m_vForward);real(w.data.GetDataValue(L"WEAPON_SCALE",1.0f));number(w.box.isNull()?0:w.box.isInfinite()?2:1);if(!w.box.isNull()&&!w.box.isInfinite()){vector(w.box.getMinimum());vector(w.box.getMaximum());}

}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_fire_missiles_differential){int failures=0;autotest::Coverage coverage("equipment_fire_missiles_differential",(uint64_t)(uintptr_t)&originalEquipmentFireMissiles);
for(unsigned n=0;n<4896;++n)for(unsigned warm=0;warm<2;++warm){Case c={n<4608?n:(n-4608)*16+47,n<4608?0u:1+(n-4608)/96,warm};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int difference=coverage.observe(host,a,b);bool ok=!difference&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus;if(!ok)host->log("    fire missiles seed %u mode %u warm %u status %d/%d lengths %lu/%lu\n",c.seed,c.mode,c.warm,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok){coverage.report(host);return failures;}}
coverage.report(host);return failures;}
