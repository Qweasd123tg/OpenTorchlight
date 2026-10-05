// Original attachment protocol with real Ogre nodes, tag points, meshes,
// material shared pointers and DataGroups. Renderable entities are spies.
#include <cstring>
#include <new>
#include <map>
#include <limits>
#include <sstream>
#include <Ogre.h>
#include <OgreTagPoint.h>
#include <OgreDefaultHardwareBufferManager.h>
#define private public
#define protected public
#include "Equipment.h"
#include "Particle.h"
#include "MasterResourceManager.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, originalEquipmentAttach, (CEquipment*,CCharacter*,EEQUIP_LOCATIONS), "_ZN10CEquipment21attachToGivenLocationEP10CCharacter16EEQUIP_LOCATIONS")
TL_FUNCTION(atDetach,"_ZN10CEquipment18detachFromLocationEv")
TL_FUNCTION(atParticles,"_ZN10CEquipment15createParticlesEv")
TL_FUNCTION(atIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(atStop,"_ZN9CParticle4StopEb")
TL_FUNCTION(atStart,"_ZN9CParticle5StartEv")
TL_FUNCTION(atMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(atUnique,"_ZN7STRINGS10uniqueNameERKSs")
TL_FUNCTION(atPaper,"_ZN10CCharacter16setPaperdollItemE16EEQUIP_LOCATIONSPN4Ogre6EntityE")
TL_FUNCTION(atPaperSecond,"_ZN10CCharacter25setPaperdollItemSecondaryE16EEQUIP_LOCATIONSPN4Ogre6EntityE")
extern "C" char atMesh[] __asm__("_ZNK4Ogre6Entity7getMeshEv");
extern "C" char atCount[] __asm__("_ZNK4Ogre6Entity17getNumSubEntitiesEv");
extern "C" char atSub[] __asm__("_ZNK4Ogre6Entity12getSubEntityEj");
extern "C" char atSetMaterial[] __asm__("_ZN4Ogre9SubEntity11setMaterialERKNS_11MaterialPtrE");
extern "C" char atBone[] __asm__("_ZN4Ogre6Entity18attachObjectToBoneERKSsPNS_13MovableObjectERKNS_10QuaternionERKNS_7Vector3E");
namespace {
#define AT_OFF(C,F,O) typedef char checked_##F[__builtin_offsetof(C,F)==O?1:-1]
AT_OFF(CCharacter,m_pUnitModel,0x200);AT_OFF(CCharacter,m_pPaperdollModel,0x208);
AT_OFF(CCharacter,m_pRightHandNode,0x2e8);AT_OFF(CCharacter,m_pLeftHandNode,0x2f8);AT_OFF(CCharacter,m_pShieldNode,0x300);
AT_OFF(CCharacter,m_pLeftShoulderNode,0x308);AT_OFF(CCharacter,m_pRightShoulderNode,0x310);AT_OFF(CCharacter,m_pHeadNode,0x318);
AT_OFF(CCharacter,m_iGold,0x444);AT_OFF(CMasterResourceManager,m_pSceneManager,0xd0);AT_OFF(CMasterResourceManager,m_pSoundBankDataInformation,0x100);
#undef AT_OFF
typedef char character_size[sizeof(CCharacter)==0x720?1:-1];
struct Case{unsigned seed,mode;};
struct World;
World* world;autotest::Capture* capture;const Case* input;
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}
void narrow(const std::string& s){number(s.size());capture->add(s.data(),s.size());}
void vector(const Ogre::Vector3& v){real(v.x);real(v.y);real(v.z);}
template<class T> struct Raw{unsigned long long bytes[(sizeof(T)+7)/8];Raw(){std::memset(bytes,0,sizeof(bytes));}T* get(){return reinterpret_cast<T*>(bytes);}};
struct World{
    Raw<CEquipment> equipment;Raw<CCharacter> actor;Raw<CGenericModel> model[5];Raw<CParticle> particle[2];Raw<CMasterResourceManager> master;
    Raw<Ogre::Entity> entity[7];Raw<Ogre::SubEntity> sub[7][3];
    void* equipmentVtable[128];void* actorVtable[128];void* modelVtable[64];void* entityVtable[64];void* subVtable[64];void* managerVtable[128];unsigned long long managerStorage[8];
    Ogre::SceneNode* nodes[14];Ogre::TagPoint* tags[4];
    Ogre::MeshPtr meshes[7];Ogre::MaterialPtr materials[7][3];unsigned subCounts[7];
    CDataGroup equipmentData,actorData;
    unsigned created,unique,meshRole,getModelCalls,starts,stops,boneCalls;int paper[2];bool visualVisible;
    World():equipmentData(L"ITEM",0,4,4,0),actorData(L"ACTOR",0,4,4,0),created(0),unique(0),meshRole(0),getModelCalls(0),starts(0),stops(0),boneCalls(0),visualVisible(true){
        std::memset(equipmentVtable,0,sizeof(equipmentVtable));std::memset(actorVtable,0,sizeof(actorVtable));std::memset(modelVtable,0,sizeof(modelVtable));std::memset(entityVtable,0,sizeof(entityVtable));std::memset(subVtable,0,sizeof(subVtable));std::memset(managerVtable,0,sizeof(managerVtable));std::memset(managerStorage,0,sizeof(managerStorage));paper[0]=paper[1]=-1;
        for(unsigned i=0;i<14;++i)nodes[i]=new Ogre::SceneNode(NULL);
        for(unsigned i=0;i<4;++i)tags[i]=new Ogre::TagPoint(i,NULL);
    }
    ~World(){for(unsigned i=0;i<4;++i)delete tags[i];for(unsigned i=0;i<14;++i)delete nodes[i];typedef std::wstring Text;actor.get()->m_sName.~Text();}
    int entityId(const Ogre::Entity* p){for(unsigned i=0;i<7;++i)if(p==entity[i].get())return i;return -1;}
    int modelId(const CPositionableObject* p){for(unsigned i=0;i<5;++i)if(p==model[i].get())return i;return -1;}
    int nodeId(const Ogre::Node* p){for(unsigned i=0;i<14;++i)if(p==nodes[i])return i;return -1;}
    int subId(const Ogre::SubEntity* p){for(unsigned i=0;i<7;++i)for(unsigned j=0;j<3;++j)if(p==sub[i][j].get())return i*3+j;return -1;}
    Ogre::SceneManager* manager(){return reinterpret_cast<Ogre::SceneManager*>(managerStorage);}
};
CEquipment* object(){return world->equipment.get();}CCharacter* actor(){return world->actor.get();}
void guid(CPositionableObject* p,long long v){number(1);number(world->modelId(p));capture->add(&v,sizeof(v));p->m_iParentGuid=v;}
void visible(CPositionableObject* p,bool v){number(2);number(world->modelId(p));number(v);world->visualVisible=v;}
void* getModel(CCharacter* p){number(3);number(p==actor());++world->getModelCalls;return p->m_pUnitModel;}
void detach(CEquipment* p){number(4);number(p==object());p->m_pEquippedTo=0;p->m_iUnknown298=-1;}
void particles(CEquipment* p){number(5);number(p==object());number(p->m_pEquippedTo==actor());number(p->m_iUnknown298);if(input->mode==3)p->m_pParticle=world->particle[0].get();}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES t){number(6);number(p==object());number(t);unsigned type=(input->seed/12)%4;return t==UNITTYPES::WEAPON?(type&1)!=0:t==UNITTYPES::SHIELD?(type&2)!=0:false;}
void stop(CParticle* p,bool immediate){number(7);number(p==world->particle[1].get());number(immediate);++world->stops;}
void start(CParticle* p){number(8);number(p==world->particle[0].get());++world->starts;}
CMasterResourceManager* master(){number(9);return world->master.get();}
std::string unique(const std::string& prefix){number(10);narrow(prefix);std::ostringstream s;s<<prefix<<world->unique++;return s.str();}
const Ogre::MeshPtr& mesh(const Ogre::Entity* p){int i=world->entityId(p);number(11);number(i);if(i<0||i>1)_exit(62);world->meshRole=i;return world->meshes[i];}
Ogre::Entity* create(Ogre::SceneManager* p,const std::string& name,const std::string& meshName){
    number(12);number(p==world->manager());narrow(name);narrow(meshName);if(world->created>=4)_exit(63);unsigned i=2+world->created++;
    world->meshes[i]=Ogre::MeshManager::getSingleton().getByName(meshName);if(world->meshes[i].isNull())_exit(64);narrow(world->meshes[i]->getName());
    unsigned count=world->subCounts[world->meshRole];world->subCounts[i]=(input->seed/5)%3==0?(count+1)%4:count;
    return world->entity[i].get();
}
unsigned subCount(const Ogre::Entity* p){int i=world->entityId(p);number(13);number(i);if(i<0)_exit(65);return world->subCounts[i];}
Ogre::SubEntity* sub(const Ogre::Entity* p,unsigned index){int i=world->entityId(p);number(14);number(i);number(index);if(i<0||index>=world->subCounts[i]||index>=3)_exit(66);return world->sub[i][index].get();}
const Ogre::MaterialPtr& material(const Ogre::SubEntity* p){int i=world->subId(p);number(15);number(i);if(i<0)_exit(67);return world->materials[i/3][i%3];}
void setMaterial(Ogre::SubEntity* p,const Ogre::MaterialPtr& value){int i=world->subId(p);number(16);number(i);number(value.isNull());if(!value.isNull())narrow(value->getName());if(i<0)_exit(68);world->materials[i/3][i%3]=value;}
void paper(CCharacter* p,EEQUIP_LOCATIONS slot,Ogre::Entity* e){number(17);number(p==actor());number(slot);number(world->entityId(e));world->paper[0]=world->entityId(e);}
void paperSecond(CCharacter* p,EEQUIP_LOCATIONS slot,Ogre::Entity* e){number(18);number(p==actor());number(slot);number(world->entityId(e));world->paper[1]=world->entityId(e);}
Ogre::SceneNode* entityParent(const Ogre::Entity* p){int i=world->entityId(p);number(19);number(i);return (input->seed/3)%2?world->nodes[12]:0;}
Ogre::TagPoint* bone(Ogre::Entity* p,const std::string& name,Ogre::MovableObject* e,const Ogre::Quaternion& rotation,const Ogre::Vector3& offset){
    number(20);number(world->entityId(p));narrow(name);number(world->entityId(static_cast<Ogre::Entity*>(e)));real(rotation.w);real(rotation.x);real(rotation.y);real(rotation.z);vector(offset);
    if(world->boneCalls>=4)_exit(69);unsigned i=world->boneCalls++;return (input->seed+i)%5==0?0:world->tags[i];
}
void initialize(World& w,const Case& c){
    w.actorVtable[0x1e0/8]=reinterpret_cast<void*>(&getModel);w.modelVtable[0x18/8]=reinterpret_cast<void*>(&guid);w.modelVtable[0x50/8]=reinterpret_cast<void*>(&visible);w.entityVtable[0xa0/8]=reinterpret_cast<void*>(&entityParent);w.subVtable[0x10/8]=reinterpret_cast<void*>(&material);w.managerVtable[0x268/8]=reinterpret_cast<void*>(&create);
    *reinterpret_cast<void***>(object())=w.equipmentVtable;*reinterpret_cast<void***>(actor())=w.actorVtable;*reinterpret_cast<void***>(w.manager())=w.managerVtable;
    new(&actor()->m_sName)std::wstring(c.seed%7?L"Actor":L"");actor()->m_pDataGroup=&w.actorData;object()->m_pDataGroup=&w.equipmentData;
    for(unsigned i=0;i<5;++i){*reinterpret_cast<void***>(w.model[i].get())=w.modelVtable;w.model[i].get()->m_iParentGuid=123+i;}
    for(unsigned i=0;i<7;++i){*reinterpret_cast<void***>(w.entity[i].get())=w.entityVtable;w.subCounts[i]=(c.seed/7+i)%4;for(unsigned j=0;j<3;++j){*reinterpret_cast<void***>(w.sub[i][j].get())=w.subVtable;std::ostringstream name;name<<"material_"<<i<<'_'<<j;if((c.seed+i+j)%4)w.materials[i][j]=Ogre::MaterialManager::getSingleton().create(name.str(),"General");}}
    w.meshes[0]=Ogre::MeshManager::getSingleton().createManual("source0","General");w.meshes[1]=Ogre::MeshManager::getSingleton().createManual("source1","General");
    w.model[0].get()->m_pEntity=w.entity[0].get();w.model[1].get()->m_pEntity=w.entity[1].get();w.model[2].get()->m_pEntity=w.entity[6].get();w.model[3].get()->m_pEntity=w.entity[6].get();
    object()->m_pUnitModel=w.model[0].get();object()->m_pUnitModelSecondary=((c.seed/48)&1)?w.model[1].get():0;object()->m_pPositionableObject=c.seed%2?w.model[4].get():0;
    actor()->m_pUnitModel=w.model[2].get();actor()->m_pPaperdollModel=((c.seed/48)&2)?w.model[3].get():0;
    w.model[0].get()->m_pSceneNode=w.nodes[7];w.model[1].get()->m_pSceneNode=w.nodes[8];w.particle[0].get()->m_pSceneNode=w.nodes[9];w.particle[1].get()->m_pSceneNode=w.nodes[10];
    actor()->m_pRightHandNode=w.nodes[0];actor()->m_pLeftHandNode=w.nodes[1];actor()->m_pShieldNode=w.nodes[2];actor()->m_pLeftShoulderNode=w.nodes[3];actor()->m_pRightShoulderNode=w.nodes[4];actor()->m_pHeadNode=w.nodes[5];
    if(c.mode==2){actor()->m_pRightHandNode=0;actor()->m_pLeftHandNode=0;actor()->m_pShieldNode=0;actor()->m_pLeftShoulderNode=0;actor()->m_pHeadNode=0;}
    if(c.seed%3)w.nodes[6]->addChild(w.nodes[7]);if((c.seed/3)%3)w.nodes[6]->addChild(w.nodes[8]);if(c.seed%2)w.nodes[6]->addChild(w.nodes[9]);w.nodes[6]->addChild(w.nodes[10]);
    object()->m_pParticle=((c.seed/48)&4)?w.particle[0].get():0;object()->m_pParticle_3D0=((c.seed/48)&8)?w.particle[1].get():0;
    if(c.mode==4)w.particle[1].get()->m_pSceneNode=0;
    if(c.mode==5){actor()->m_pRightShoulderNode=0;object()->m_pParticle=0;}
    w.master.get()->m_pSceneManager=w.manager();object()->m_iUnknown298=-9;
    static const float scales[]={0.0f,-1.0f,0.5f,1.0f,1.75f,std::numeric_limits<float>::infinity()};
    if(c.seed%3)w.actorData.AddDataValue(L"WEAPON_SCALE",scales[(c.seed/12)%6]);if(c.seed%5)w.actorData.AddDataValue(L"SHIELD_SCALE",scales[(c.seed/24+2)%6]);
    unsigned gate=c.mode==0?(c.seed/48)%6:0;
    if(gate==1){CDataGroup* g=w.equipmentData.AddDataGroup(L"WARDROBE");g->AddDataValue(L"CLASS",std::wstring(L"Actor"),false);g->AddDataValue(L"MESH",std::wstring(L"body"),false);}
    if(gate==2)actor()->m_pUnitModel=0;if(gate==3)w.model[2].get()->m_pEntity=0;if(gate==4)object()->m_pUnitModel=0;if(gate==5)w.model[0].get()->m_pEntity=0;
}
void side(const Case& c,bool ours,autotest::Capture& out){
    input=&c;capture=&out;World w;world=&w;initialize(w,c);
    detour::Set patches;TL_REDIRECT(patches,atDetach,&detach);TL_REDIRECT(patches,atParticles,&particles);TL_REDIRECT(patches,atIsa,&isa);TL_REDIRECT(patches,atStop,&stop);TL_REDIRECT(patches,atStart,&start);TL_REDIRECT(patches,atMaster,&master);TL_REDIRECT(patches,atUnique,&unique);TL_REDIRECT(patches,atPaper,&paper);TL_REDIRECT(patches,atPaperSecond,&paperSecond);
    patches.redirect(atMesh,atMesh,&mesh);patches.redirect(atCount,atCount,&subCount);patches.redirect(atSub,atSub,&sub);patches.redirect(atSetMaterial,atSetMaterial,&setMaterial);patches.redirect(atBone,atBone,&bone);if(patches.failed())_exit(42);
    for(unsigned repeat=0;repeat<2;++repeat){
        EEQUIP_LOCATIONS slot=static_cast<EEQUIP_LOCATIONS>(c.seed%12);if(ours)object()->attachToGivenLocation(actor(),slot);else originalEquipmentAttach(object(),actor(),slot);
        number(100+repeat);number(object()->m_pEquippedTo==actor());number(object()->m_iUnknown298);number(w.created);number(w.getModelCalls);number(w.starts);number(w.stops);number(w.boneCalls);number(w.visualVisible);number(w.paper[0]);number(w.paper[1]);
        for(unsigned i=0;i<2;++i){long long v=w.model[i].get()->m_iParentGuid;capture->add(&v,sizeof(v));number(w.meshes[i].useCount());}
        for(unsigned i=0;i<14;++i){number(w.nodeId(w.nodes[i]->getParent()));vector(w.nodes[i]->getScale());}
        for(unsigned i=0;i<4;++i)vector(w.tags[i]->getScale());
        for(unsigned i=2;i<6;++i)for(unsigned j=0;j<3;++j){number(w.materials[i][j].isNull());if(!w.materials[i][j].isNull())narrow(w.materials[i][j]->getName());}
    }
    patches.restore();
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_attach_differential){
    int failures=0;
    try {
        Ogre::Root root("","","/tmp/otl-equipment-attach-test.log");Ogre::DefaultHardwareBufferManager buffers;
        for(unsigned n=0;n<1728;++n){Case c={n<1344?n:720+(n-1344)%96,n<576?0u:n<1344?1u:2+(n-1344)/96};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
            bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
            if(!ok){size_t i=0;while(i<a.capture.length&&i<b.capture.length&&a.capture.data[i]==b.capture.data[i])++i;host->log("    attach seed %u mode %u status %d/%d bytes %lu/%lu first %lu\n",c.seed,c.mode,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)i);}
            TL_CHECK(failures,ok);if(!ok)return failures;
        }
    } catch(const Ogre::Exception& e){host->log("    attach setup: %s\n",e.getFullDescription().c_str());return 1;}
    host->log("    equipment attach: 1728 cases, two calls per side\n");return failures;
}
