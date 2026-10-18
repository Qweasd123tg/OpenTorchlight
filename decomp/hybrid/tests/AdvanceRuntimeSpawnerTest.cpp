#include "SmallMassCompare.h"
#include "SafePointer.h"
#include "RunicCore.h"
#include "TArrayList.h"
#include <OgreQuaternion.h>
TL_ORIGINAL(void,spawnerOld0,(void*,void*),"_ZN12CUnitSpawnerC1EP16CResourceManager")
TL_ORIGINAL(void,spawnerOld1,(void*),"_ZN12CUnitSpawner19createUnitsInMemoryEv")
TL_ORIGINAL(void,spawnerOld2,(void*,void*),"_ZN12CUnitSpawner14addSpawnedUnitEP9CBaseUnit")
TL_ORIGINAL(void,spawnerOld3,(void*,const std::wstring&,const Ogre::Vector3&,const Ogre::Quaternion&),"_ZN12CUnitSpawner20createAndFireMissileERKSbIwSt11char_traitsIwESaIwEERKN4Ogre7Vector3ERKNS6_10QuaternionE")
TL_ORIGINAL(void,spawnerOld4,(void*,bool),"_ZN12CUnitSpawner19hideAndDisableUnitsEb")
TL_ORIGINAL(void,spawnerOld5,(void*),"_ZN12CUnitSpawner12destroyUnitsEv")
TL_ORIGINAL(void,spawnerOld6,(void*,void*,int),"_ZN12CUnitSpawner15unitStateChangeEP9CBaseUnit12EUNIT_STATES")
extern "C" void spawnerNew0(void*,void*) __asm__("_ZN12CUnitSpawnerC1EP16CResourceManager");
extern "C" void spawnerNew1(void*) __asm__("_ZN12CUnitSpawner19createUnitsInMemoryEv");
extern "C" void spawnerNew2(void*,void*) __asm__("_ZN12CUnitSpawner14addSpawnedUnitEP9CBaseUnit");
extern "C" void spawnerNew3(void*,const std::wstring&,const Ogre::Vector3&,const Ogre::Quaternion&) __asm__("_ZN12CUnitSpawner20createAndFireMissileERKSbIwSt11char_traitsIwESaIwEERKN4Ogre7Vector3ERKNS6_10QuaternionE");
extern "C" void spawnerNew4(void*,bool) __asm__("_ZN12CUnitSpawner19hideAndDisableUnitsEb");
extern "C" void spawnerNew5(void*) __asm__("_ZN12CUnitSpawner12destroyUnitsEv");
extern "C" void spawnerNew6(void*,void*,int) __asm__("_ZN12CUnitSpawner15unitStateChangeEP9CBaseUnit12EUNIT_STATES");
TL_FUNCTION(spawnerShapeCtor,"_ZN6CShapeC1EP16CResourceManager")
TL_FUNCTION(spawnerEditor,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(spawnerGuid,"_ZN9CBaseUnit14setSpawnerGuidEx")
TL_FUNCTION(spawnerAddListener,"_ZN6CLevel17addListenerToUnitEP9CBaseUnitP13iUnitObserver")
TL_FUNCTION(spawnerRemoveListener,"_ZN6CLevel22removeListenerFromUnitEP9CBaseUnitP13iUnitObserver")
TL_FUNCTION(spawnerCreateMissile,"_ZN16CResourceManager13createMissileERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(spawnerFireMissile,"_ZN8CMissile11fireMissileEP9CBaseUnitN4Ogre7Vector3ERKNS2_10QuaternionEP19CPositionableObjectS3_")
TL_FUNCTION(spawnerCharacterVisible,"_ZN10CCharacter10setVisibleEbb")
TL_FUNCTION(spawnerLayoutStop,"_ZN7CLayout4stopEb")
TL_FUNCTION(spawnerLayoutStart,"_ZN7CLayout5startEv")
extern "C" char spawnerLogSingleton[] __asm__("_ZN4Ogre10LogManager12getSingletonEv");
extern "C" char spawnerLogMessage[] __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
extern "C" void* spawnerCharacterTable[] __asm__("_ZTV10CCharacter");
extern "C" void* spawnerItemTable[] __asm__("_ZTV5CItem");
extern "C" void* spawnerEquipmentTable[] __asm__("_ZTV10CEquipment");
namespace {
using namespace smallmass;typedef TSafePointer<CRunicCore> Weak;unsigned calls;void* resources;void* level;void* missile;void** table;
void record(unsigned tag,void* p){event(tag,p);++calls;}
void shapeCtor(void* p,void* r){record(1,p);pointer(r);field<void*>(p,0x68)=r;}
bool editor(void* p){record(2,p);return input->index%7==0;}
void guid(void* p,long long value){record(3,p);output->add(&value,8);field<long long>(p,0x1d0)=value;}
void addListener(void* p,void* unit,void* listener){record(4,p);pointer(unit);pointer(listener);}
void removeListener(void* p,void* unit,void* listener){record(5,p);pointer(unit);pointer(listener);}
void* createMissile(void* p,const std::wstring& n){record(6,p);text(n);return input->index%7?missile:0;}
void spawned(void* p,void* spawner,void* unit){record(7,p);pointer(spawner);pointer(unit);}
void fire(void* p,void* owner,Ogre::Vector3 position,const Ogre::Quaternion& q,void* target,Ogre::Vector3 direction){record(8,p);pointer(owner);vector(position);output->add(&q,sizeof(q));pointer(target);vector(direction);}
void enabled(void* p,bool value){record(9,p);number(value);}
void characterVisible(void* p,bool value,bool recursive){record(10,p);number(value);number(recursive);}
void layoutStop(void* p,bool value){record(11,p);number(value);}
void layoutStart(void* p){record(12,p);}
void visible(void* p,bool value){record(13,p);number(value);}
void die(void* p,void* killer,const Ogre::Vector3* direction,float force,bool silent){record(14,p);pointer(killer);pointer(direction);floating(force);number(silent);if(input->index&8){static_cast<CRunicCore*>(p)->CRunicCore::~CRunicCore();record(15,p);}}
void broadcast(void* p,unsigned eventId){record(16,p);number(eventId);}
void* logSingleton(){record(17,level);return level;}
void logMessage(void* p,const std::string& message,int severity,bool flag){record(18,p);text(message);number(severity);number(flag);}
Weak* weak(void* target){void* storage=Ogre::GeneralAllocPolicy::allocateBytes(sizeof(Weak));Weak* ref=new(storage)Weak;ref->setObject(static_cast<CRunicCore*>(target));return ref;}
void destroyWeak(Weak* ref){ref->~Weak();Ogre::GeneralAllocPolicy::deallocateBytes(ref);}
void registry(void* p){TArrayList<void*>* refs=field<TArrayList<void*>*>(p,8);number(refs!=0);if(refs){number(refs->size());for(unsigned i=0;i<refs->size();++i){void* ref=(*refs)[i];pointer(ref);if(ref){pointer(field<void*>(ref,0));number(field<unsigned>(ref,8));}}}}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;void* self=object(0x240);resources=object(0x48);level=object(0x20);missile=object(0x2d8);field<void*>(self,0x68)=resources;field<long long>(self,0x20)=0x123456780000LL+c.index;field<void*>(resources,0x18)=c.index%3?level:0;table=static_cast<void**>(object(0x350));table[0x30/8]=reinterpret_cast<void*>(&broadcast);table[0x40/8]=reinterpret_cast<void*>(&enabled);table[0x50/8]=reinterpret_cast<void*>(&visible);table[0x330/8]=reinterpret_cast<void*>(&die);field<void*>(self,0)=table;field<void*>(missile,0x220)=c.index&1?self:0;
 void* units[5];for(unsigned i=0;i<5;++i){units[i]=object(0x1148);void** clone=static_cast<void**>(object(0x360));std::memcpy(clone,(c.index+i)%3==0?spawnerCharacterTable:(c.index+i)%3==1?spawnerItemTable:spawnerEquipmentTable,0x360);void** primary=clone+2;primary[0x40/8]=reinterpret_cast<void*>(&enabled);primary[0x330/8]=reinterpret_cast<void*>(&die);field<void*>(units[i],0)=primary;field<void*>(units[i],8)=0;field<void*>(units[i],0x68)=c.index&32?0:resources;}
 TArrayList<void*>& layouts=*new(static_cast<char*>(self)+0x1d0)TArrayList<void*>(c.index%2+1);TArrayList<Weak*>& base=*new(static_cast<char*>(self)+0x1e8)TArrayList<Weak*>(c.index%2+1);TArrayList<Weak*>& characters=*new(static_cast<char*>(self)+0x200)TArrayList<Weak*>(c.index%2+1);TArrayList<void*>& listeners=*new(static_cast<char*>(self)+0x218)TArrayList<void*>(2);new(static_cast<char*>(self)+0x1b0)std::wstring(L"category");new(static_cast<char*>(self)+0x1b8)std::wstring(c.index&1?L"resource.layout":L"");
 Weak* all[10];unsigned allCount=0;
 if(c.op==1){if(c.index&2)base.add(0);if(c.index&4)characters.add(0);field<unsigned>(self,0x190)=c.index*17;static unsigned pulses[]={0,1,2,3,~0u,~1u};field<unsigned>(self,0x194)=pulses[(c.index/8)%6];field<unsigned>(self,0x1c8)=0x1234abcd;}
 if(c.op==2){for(unsigned i=0;i<c.index%4;++i){Weak* ref=weak(units[i+1]);all[allCount++]=ref;(c.index&8?base:characters).add(ref);}}
 if(c.op==3){for(unsigned i=0;i<c.index%5;++i){void* listener=object(8);void** lt=static_cast<void**>(object(24));lt[2]=reinterpret_cast<void*>(&spawned);field<void*>(listener,0)=lt;listeners.add(listener);}}
 if(c.op==4||c.op==5||c.op==6){for(unsigned i=0;i<c.index%5;++i){Weak* ref=weak((c.index+i)%4?units[i]:0);all[allCount++]=ref;(c.op==6?base:characters).add(ref);}if(c.op==5)for(unsigned i=0;i<(c.index/2)%4;++i){Weak* ref=weak((c.index+i)%3?units[i]:0);base.add(ref);all[allCount++]=ref;}if(c.op!=6)for(unsigned i=0;i<(c.index/3)%4;++i){void* layout=object(0x200);field<void*>(layout,0)=table;layouts.add(layout);}field<bool>(self,0x1c0)=true;field<bool>(self,0x1c1)=true;}
 detour::Set d;TL_REDIRECT(d,spawnerShapeCtor,&shapeCtor);TL_REDIRECT(d,spawnerEditor,&editor);TL_REDIRECT(d,spawnerGuid,&guid);TL_REDIRECT(d,spawnerAddListener,&addListener);TL_REDIRECT(d,spawnerRemoveListener,&removeListener);TL_REDIRECT(d,spawnerCreateMissile,&createMissile);TL_REDIRECT(d,spawnerFireMissile,&fire);TL_REDIRECT(d,spawnerCharacterVisible,&characterVisible);TL_REDIRECT(d,spawnerLayoutStop,&layoutStop);TL_REDIRECT(d,spawnerLayoutStart,&layoutStart);d.redirect(spawnerLogSingleton,spawnerLogSingleton,&logSingleton);d.redirect(spawnerLogMessage,spawnerLogMessage,&logMessage);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.op==0){layouts.~TArrayList();base.~TArrayList();characters.~TArrayList();listeners.~TArrayList();field<std::wstring>(self,0x1b0).~basic_string();field<std::wstring>(self,0x1b8).~basic_string();std::memset(self,0xa5,0x240);autotest::invoke(out,ours?spawnerNew0:spawnerOld0,self,c.index&1?resources:0);out.add(static_cast<char*>(self)+0x178,0x38);text(field<std::wstring>(self,0x1b0));text(field<std::wstring>(self,0x1b8));out.add(static_cast<char*>(self)+0x1c0,0x10);for(unsigned i=0;i<4;++i){unsigned offset=0x1d0+i*24;pointer(field<void*>(self,offset));out.add(static_cast<char*>(self)+offset+8,12);}out.add(static_cast<char*>(self)+0x230,16);}
 else if(c.op==1){autotest::invoke(out,ours?spawnerNew1:spawnerOld1,self);number(field<unsigned>(self,0x1c8));}
 else if(c.op==2){autotest::invoke(out,ours?spawnerNew2:spawnerOld2,self,units[0]);for(unsigned g=0;g<2;++g){TArrayList<Weak*>& refs=g?characters:base;for(unsigned i=0;i<refs.size();++i){bool found=false;for(unsigned k=0;k<allCount;++k)if(all[k]==refs[i])found=true;if(!found)all[allCount++]=refs[i];}}}
 else if(c.op==3){Ogre::Vector3 p(float(c.index),-3.5f,0.75f);Ogre::Quaternion q(0.5f,float(c.index)*0.1f,2,-3);std::wstring name=c.index&1?L"missile/Юникод":L"";typedef void(*Fn)(void*,const std::wstring&,const Ogre::Vector3&,const Ogre::Quaternion&);Fn fn=ours?spawnerNew3:spawnerOld3;if(!autotest::beginInvocation(out,fn))return;fn(self,name,p,q);out.callCompleted=1;}
 else if(c.op==4)autotest::invoke(out,ours?spawnerNew4:spawnerOld4,self,bool(c.index&1));
 else if(c.op==5)autotest::invoke(out,ours?spawnerNew5:spawnerOld5,self);
 else autotest::invoke(out,ours?spawnerNew6:spawnerOld6,self,units[c.index%5],int((c.index/5)%5));
 if(c.op!=0){for(unsigned g=0;g<2;++g){TArrayList<Weak*>& refs=g?characters:base;number(refs.size());number(field<unsigned>(&refs,12));for(unsigned i=0;i<refs.size();++i){pointer(refs[i]);if(refs[i]){pointer(refs[i]->getObject());number(field<unsigned>(refs[i],8));}}}for(unsigned i=0;i<5;++i)registry(units[i]);number(field<bool>(self,0x1c0));number(field<bool>(self,0x1c1));}
 number(calls);if(c.op!=5)for(unsigned i=0;i<allCount;++i)destroyWeak(all[i]);for(unsigned i=0;i<5;++i)static_cast<CRunicCore*>(units[i])->CRunicCore::~CRunicCore();layouts.~TArrayList();base.~TArrayList();characters.~TArrayList();listeners.~TArrayList();field<std::wstring>(self,0x1b0).~basic_string();field<std::wstring>(self,0x1b8).~basic_string();
}
}
TL_TEST(advance_runtime_spawner_ctor){return smallmass::run(host,0,"advance_runtime_spawner_ctor",(uintptr_t)spawnerOld0,execute,84);}
TL_TEST(advance_runtime_spawner_memory){return smallmass::run(host,1,"advance_runtime_spawner_memory",(uintptr_t)spawnerOld1,execute,192);}
TL_TEST(advance_runtime_spawner_add){return smallmass::run(host,2,"advance_runtime_spawner_add",(uintptr_t)spawnerOld2,execute,84);}
TL_TEST(advance_runtime_spawner_missile){return smallmass::run(host,3,"advance_runtime_spawner_missile",(uintptr_t)spawnerOld3,execute,84);}
TL_TEST(advance_runtime_spawner_hide){return smallmass::run(host,4,"advance_runtime_spawner_hide",(uintptr_t)spawnerOld4,execute,84);}
TL_TEST(advance_runtime_spawner_destroy){return smallmass::run(host,5,"advance_runtime_spawner_destroy",(uintptr_t)spawnerOld5,execute,84);}
TL_TEST(advance_runtime_spawner_state){return smallmass::run(host,6,"advance_runtime_spawner_state",(uintptr_t)spawnerOld6,execute,150);}
