#include "tests/SmallMassCompare.h"
#include "UnitSpawner.h"
#include "Character.h"
#include "Layout.h"
#include "GenericModel.h"
#include "UnitSpawnerDescriptorNames.h"
#include "DataGroup.h"
#include "EmptyStrings.h"
#define DECL(ret,id,args,sym) TL_ORIGINAL(ret,id##Old,args,sym) extern "C" ret id##New args __asm__(sym);
DECL(void,deepSpawn,(void*),"_ZN12CUnitSpawner5spawnEv")
DECL(void,deepSpawnUpdate,(void*,float),"_ZN12CUnitSpawner6updateEf")
DECL(void,deepSpawnSet,(void*,std::wstring),"_ZN12CUnitSpawner16setResourceSpawnESbIwSt11char_traitsIwESaIwEE")
DECL(void,deepSpawnParticles,(void*,const std::wstring&,const Ogre::Vector3&,const Ogre::Quaternion&,unsigned),"_ZN12CUnitSpawner22createParticleSystemAtERKSbIwSt11char_traitsIwESaIwEERKN4Ogre7Vector3ERKNS6_10QuaternionEj")
DECL(void,deepSpawnDestroy,(void*),"_ZN12CUnitSpawnerD1Ev")
TL_FUNCTION(deepSpawnReset,"_ZN12CUnitSpawner5resetEv")
TL_FUNCTION(deepSpawnIndex,"_ZN12CUnitSpawner16spawnUnitByIndexEj")
TL_FUNCTION(deepSpawnEditor,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(deepSpawnAlive,"_ZN10CCharacter5aliveEv")
TL_FUNCTION(deepSpawnSafeRemove,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(deepSpawnMaster,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(deepSpawnData,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(deepSpawnModel,"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerESbIwSt11char_traitsIwESaIwEES8_b")
TL_FUNCTION(deepSpawnLoad,"_ZN13CGenericModel9loadModelESbIwSt11char_traitsIwESaIwEES3_bbb")
TL_FUNCTION(deepSpawnParent,"_ZN16CSceneNodeObject18sceneNodeSetParentEPN4Ogre9SceneNodeEb")
TL_FUNCTION(deepSpawnSnap,"_ZN6CLevel17snapToValidGroundERN4Ogre7Vector3Ef")
TL_FUNCTION(deepSpawnLayout,"_ZN7CLayoutC1EP16CResourceManager13ELAYOUT_TYPES")
TL_FUNCTION(deepSpawnLayoutLoad,"_ZN7CLayout14loadLayoutFileERKSbIwSt11char_traitsIwESaIwEEbP13CTimerStaticsbbj")
TL_FUNCTION(deepSpawnLayoutStart,"_ZN7CLayout5startEv")
TL_FUNCTION(deepSpawnPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(deepSpawnLayoutStop,"_ZN7CLayout4stopEb")
TL_FUNCTION(deepSpawnRemoveUnits,"_ZN6CLevel23removeListenerFromUnitsEP13iUnitObserver")
TL_FUNCTION(deepSpawnShapeDestroy,"_ZN6CShapeD2Ev")
namespace {using namespace smallmass;void** layoutVtable;void** nodeVtable;void* node;void* token;CDataGroup* data;unsigned attempts;
TSafePointer<CCharacter>* callbackReplacement;
unsigned callbackSwaps;
CRunicCore* callbackOwnerA;
CRunicCore* callbackOwnerB;
TSafePointer<CCharacter>* callbackReferenceA;
bool callbackCase(){return input->op==1 && input->index>=256;}
unsigned registered(CRunicCore* owner){TArrayList<TSafePointer<void*>*>* refs=field<TArrayList<TSafePointer<void*>*>*>(owner,8);return refs?refs->size():0;}
void visible(void* p,bool b){event(1,p);number(b);}
void broadcast(void* p,int id){event(2,p);number(id);
    if(callbackCase() && id==24){
        TArrayList<void*>& characters=field<TArrayList<void*> >(p,0x200);
        number(characters.size());pointer(characters[0]);pointer(callbackReplacement);
        characters[0]=callbackReplacement;++callbackSwaps;
    }
}
void reset(void* p){event(3,p);field<float>(p,0x184)=field<float>(p,0x188)=field<float>(p,0x1a0)=0;field<unsigned>(p,0x18c)=0;}
bool index(void* p,unsigned i){event(4,p);number(i);++attempts;return (i+input->index)%3!=0;}
bool editor(void* p){event(5,p);return callbackCase()?false:bool(input->index&4);}
bool alive(void* p){event(6,p);return field<unsigned>(p,0x10)&1;}
void safeRemove(void* p,void* ref,unsigned i){event(7,p);number(i);number(field<void*>(ref,0)==p);}
void* master(void* p){event(8,p);return token;}
CDataGroup* find(void* p,const std::wstring& category,const std::wstring& name){event(9,p);text(category);text(name);return input->index&8?0:data;}
void destroy(void* p){event(10,p);Ogre::NedAllocImpl::deallocBytes(p);}
void model(void* p,void* resources,void* scene,std::wstring a,std::wstring b,bool flag){event(11,p);pointer(resources);pointer(scene);text(a);text(b);number(flag);field<void**>(p,0)=layoutVtable;}
void load(void* p,std::wstring a,std::wstring b,bool c,bool d,bool e){event(12,p);text(a);text(b);number(c);number(d);number(e);}
void parent(void* p,void* node,bool b){event(13,p);pointer(node);number(b);}
bool snap(void* p,Ogre::Vector3& position,float f){event(14,p);vector(position);floating(f);position.y+=2;return input->index&1;}
void layout(void* p,void* resources,int type){event(15,p);pointer(resources);number(type);field<void**>(p,0)=layoutVtable;field<void*>(p,0x58)=node;}
bool layoutLoad(void* p,const std::wstring& name,bool a,void* timer,bool b,bool c,unsigned n){event(16,p);text(name);number(a);pointer(timer);number(b);number(c);number(n);return true;}
void start(void* p){event(17,p);}
void position(void* p,const Ogre::Vector3& v){event(18,p);vector(v);}
void orientation(void* p,const Ogre::Quaternion& q){event(19,p);output->add(&q,sizeof(q));}
void nodeUpdate(void* p,bool a,bool b){event(20,p);number(a);number(b);}
void layoutUpdate(void* p,float f){event(21,p);floating(f);}
void stop(void* p,bool b){event(22,p);number(b);}
void removeUnits(void* p,void* observer){event(23,p);pointer(observer);}
void shapeDestroy(void* p){event(24,p);}
void spawned(void* p,void* spawner,void* layout){event(25,p);pointer(spawner);pointer(layout);}
void* heap(unsigned size){void* p=Ogre::NedAllocImpl::allocBytes(size,NULL,0,NULL);std::memset(p,0,size);return p;}
void* newLayout(){void* p=heap(sizeof(CLayout));field<void**>(p,0)=layoutVtable;field<void*>(p,0x58)=node;return p;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;autotest::g_arenaUsed=0;attempts=0;callbackSwaps=0;callbackReplacement=callbackReferenceA=0;callbackOwnerA=callbackOwnerB=0;void* self=object(sizeof(CUnitSpawner));token=object(8);void* resources=object(0x100);field<void*>(resources,0x18)=c.index&32?0:token;field<void*>(self,0x68)=resources;field<void*>(self,0x58)=token;void** selfVtable=static_cast<void**>(object(0x220));selfVtable[0x50/8]=reinterpret_cast<void*>(&visible);selfVtable[0x30/8]=reinterpret_cast<void*>(&broadcast);field<void**>(self,0)=selfVtable;layoutVtable=static_cast<void**>(object(0x220));layoutVtable[8/8]=reinterpret_cast<void*>(&destroy);layoutVtable[0x50/8]=reinterpret_cast<void*>(&visible);layoutVtable[0x108/8]=reinterpret_cast<void*>(&orientation);layoutVtable[0x208/8]=reinterpret_cast<void*>(&layoutUpdate);nodeVtable=static_cast<void**>(object(0x220));nodeVtable[0x218/8]=reinterpret_cast<void*>(&nodeUpdate);node=object(8);field<void**>(node,0)=nodeVtable;
std::wstring& category=*new(static_cast<char*>(self)+0x1b0)std::wstring(gSPAWN_TYPE_NAMES[c.index%7]);std::wstring& name=*new(static_cast<char*>(self)+0x1b8)std::wstring(L"before");TArrayList<void*>& layouts=*new(static_cast<char*>(self)+0x1d0)TArrayList<void*>(2);TArrayList<void*>& units=*new(static_cast<char*>(self)+0x1e8)TArrayList<void*>(2);TArrayList<void*>& chars=*new(static_cast<char*>(self)+0x200)TArrayList<void*>(2);TArrayList<void*>& listeners=*new(static_cast<char*>(self)+0x218)TArrayList<void*>(2);for(unsigned i=0;i<c.index%3;++i)layouts.add(newLayout());
void** listenerVtable=static_cast<void**>(object(24));listenerVtable[2]=reinterpret_cast<void*>(&spawned);for(unsigned i=0;i<(c.index/2)%3;++i){void* listener=object(8);field<void**>(listener,0)=listenerVtable;listeners.add(listener);}
field<float>(self,0x180)=c.op==0?float(int(c.index%4)-1):float(c.index%3+1);field<unsigned>(self,0x190)=c.index%4;unsigned pulses[]={0,1,2,~0u};field<unsigned>(self,0x194)=pulses[(c.index/4)%4];field<unsigned>(self,0x1c8)=3;field<unsigned>(self,0x18c)=c.index%3;field<unsigned>(self,0x198)=c.index%2;field<float>(self,0x184)=float(int(c.index%5)-2)*.2f;field<float>(self,0x188)=float(c.index%3)*.5f;field<float>(self,0x1a0)=float(int(c.index%3)-1)*.2f;field<float>(self,0x1cc)=float(int(c.index%3)-1)*.2f;field<bool>(self,0x1c1)=c.index&2;field<unsigned>(self,0x19c)=c.index&8;
if((c.op==1 && c.index<256) || c.op==4){for(unsigned i=0;i<(c.index/8)%4;++i){void* character=object(0x20);field<unsigned>(character,0x10)=i+c.index;void* ref=heap(16);field<void*>(ref,0)=((i+c.index)%3)?character:0;field<unsigned>(ref,8)=i+10;chars.add(ref);}if(c.op==4){for(unsigned i=0;i<c.index%3;++i){void* ref=heap(16);field<void*>(ref,0)=i?token:0;field<unsigned>(ref,8)=i+20;units.add(ref);}}}
if(callbackCase()){
    // The callback replaces a valid occupied slot; its old owner keeps the
    // displaced reference alive outside the list until after the invocation.
    callbackOwnerA=new(object(sizeof(CCharacter))) CRunicCore();
    callbackOwnerB=new(object(sizeof(CCharacter))) CRunicCore();
    field<unsigned>(callbackOwnerA,0x10)=0;
    field<unsigned>(callbackOwnerB,0x10)=1;
    callbackReferenceA=new(heap(sizeof(TSafePointer<CCharacter>))) TSafePointer<CCharacter>();
    callbackReplacement=new(heap(sizeof(TSafePointer<CCharacter>))) TSafePointer<CCharacter>();
    callbackReferenceA->setObject(reinterpret_cast<CCharacter*>(callbackOwnerA));
    callbackReplacement->setObject(reinterpret_cast<CCharacter*>(callbackOwnerB));
    chars.add(callbackReferenceA);
    field<bool>(self,0x1c1)=false;
    field<float>(self,0x1cc)=-.25f;
}
data=new CDataGroup(EMPTY_WSTRING,NULL,20,10,NULL);if(c.index&16)data->AddDataValue(L"SPAWNER",L"model.mesh",false);if(c.op==2 && c.index&32){void* preview=heap(sizeof(CGenericModel));field<void**>(preview,0)=layoutVtable;field<void*>(self,0x238)=preview;}
detour::Set d;TL_REDIRECT(d,deepSpawnReset,&reset);TL_REDIRECT(d,deepSpawnIndex,&index);TL_REDIRECT(d,deepSpawnEditor,&editor);TL_REDIRECT(d,deepSpawnAlive,&alive);if(!callbackCase())TL_REDIRECT(d,deepSpawnSafeRemove,&safeRemove);TL_REDIRECT(d,deepSpawnMaster,&master);TL_REDIRECT(d,deepSpawnData,&find);TL_REDIRECT(d,deepSpawnModel,&model);TL_REDIRECT(d,deepSpawnLoad,&load);TL_REDIRECT(d,deepSpawnParent,&parent);TL_REDIRECT(d,deepSpawnSnap,&snap);TL_REDIRECT(d,deepSpawnLayout,&layout);TL_REDIRECT(d,deepSpawnLayoutLoad,&layoutLoad);TL_REDIRECT(d,deepSpawnLayoutStart,&start);TL_REDIRECT(d,deepSpawnPosition,&position);TL_REDIRECT(d,deepSpawnLayoutStop,&stop);TL_REDIRECT(d,deepSpawnRemoveUnits,&removeUnits);TL_REDIRECT(d,deepSpawnShapeDestroy,&shapeDestroy);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
if(c.op==0)autotest::invoke(out,ours?deepSpawnNew:deepSpawnOld,self);else if(c.op==1)autotest::invoke(out,ours?deepSpawnUpdateNew:deepSpawnUpdateOld,self,float(c.index%5)*.25f);else if(c.op==2)autotest::invoke(out,ours?deepSpawnSetNew:deepSpawnSetOld,self,std::wstring(c.index&1?L"afterЖ":L""));else if(c.op==3){std::wstring name=L"particles/a.layout";Ogre::Vector3 pos(1,2,-3);Ogre::Quaternion q(Ogre::Radian(.5f),Ogre::Vector3::UNIT_Y);typedef void(*Fn)(void*,const std::wstring&,const Ogre::Vector3&,const Ogre::Quaternion&,unsigned);autotest::invoke<Fn,void*,const std::wstring&,const Ogre::Vector3&,const Ogre::Quaternion&,unsigned>(out,ours?deepSpawnParticlesNew:deepSpawnParticlesOld,self,name,pos,q,c.index%4);}else autotest::invoke(out,ours?deepSpawnDestroyNew:deepSpawnDestroyOld,self);
if(callbackCase()){
    number(callbackSwaps);number(registered(callbackOwnerA));number(registered(callbackOwnerB));
    if(registered(callbackOwnerA)){callbackReferenceA->~TSafePointer<CCharacter>();Ogre::NedAllocImpl::deallocBytes(callbackReferenceA);}
    if(registered(callbackOwnerB)){callbackReplacement->~TSafePointer<CCharacter>();Ogre::NedAllocImpl::deallocBytes(callbackReplacement);}
    number(registered(callbackOwnerA));number(registered(callbackOwnerB));
    callbackOwnerA->CRunicCore::~CRunicCore();callbackOwnerB->CRunicCore::~CRunicCore();
}
number(attempts);if(c.op!=4){text(name);number(field<bool>(self,0x1c3));out.add(static_cast<char*>(self)+0x180,0x30);out.add(static_cast<char*>(self)+0x1c0,0x10);number(layouts.size());number(chars.size());for(unsigned i=0;i<chars.size();++i){pointer(field<void*>(chars[i],0));number(field<unsigned>(chars[i],8));}for(unsigned i=0;i<layouts.size();++i)Ogre::NedAllocImpl::deallocBytes(layouts[i]);for(unsigned i=0;i<chars.size();++i)Ogre::NedAllocImpl::deallocBytes(chars[i]);for(unsigned i=0;i<units.size();++i)Ogre::NedAllocImpl::deallocBytes(units[i]);if(field<void*>(self,0x238))Ogre::NedAllocImpl::deallocBytes(field<void*>(self,0x238));layouts.~TArrayList();chars.~TArrayList();units.~TArrayList();listeners.~TArrayList();name.~basic_string();category.~basic_string();}delete data;}
}
TL_TEST(deep_runtime_spawner_spawn){return smallmass::run(host,0,"deep_runtime_spawner_spawn",(uintptr_t)deepSpawnOld,execute,128);}
TL_TEST(deep_runtime_spawner_update){return smallmass::run(host,1,"deep_runtime_spawner_update",(uintptr_t)deepSpawnUpdateOld,execute,288);}
TL_TEST(deep_runtime_spawner_resource){return smallmass::run(host,2,"deep_runtime_spawner_resource",(uintptr_t)deepSpawnSetOld,execute,128);}
TL_TEST(deep_runtime_spawner_particles){return smallmass::run(host,3,"deep_runtime_spawner_particles",(uintptr_t)deepSpawnParticlesOld,execute,96);}
TL_TEST(deep_runtime_spawner_destructor){return smallmass::run(host,4,"deep_runtime_spawner_destructor",(uintptr_t)deepSpawnDestroyOld,execute,96);}
