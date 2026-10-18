#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <stdint.h>
#include <new>
#include <OgreVector3.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#define protected public
#include "Descriptor.h"
#include "Equipment.h"
#include "UnitSpawner.h"
#include "Room.h"
#include "Teleport.h"
#include "Level.h"
#include "ResourceManager.h"
#include "EditorScene.h"
#include "DescriptorSaveConfiguration.h"
#undef private
#undef protected
#define TARGET(n,newer,args,sym) TL_ORIGINAL(void,n,args,sym) extern "C" void newer args __asm__(sym);
TARGET(aeWOldItem,aeWNewItem,(void*,void*),"_ZN15CItemDescriptor24descriptorSceneActivatedEP12CEditorScene")
TARGET(aeWOldUpdate,aeWNewUpdate,(void*,float),"_ZN22CUnitSpawnerDescriptor6updateEf")
TARGET(aeWOldActivated,aeWNewActivated,(void*,void*),"_ZN22CUnitSpawnerDescriptor24descriptorSceneActivatedEP12CEditorScene")
TARGET(aeWOldTeleport,aeWNewTeleport,(void*,void*,unsigned,void*),"_ZN19CTeleportDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_")
TARGET(aeWOldRoom,aeWNewRoom,(void*,void*,void*,void*),"_ZN15CRoomDescriptor10saveObjectEP17CEditorBaseObjectP10CDataGroupP28CDescriptorSaveConfiguration")
TL_FUNCTION(aeWPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(aeWAdd,"_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
TL_FUNCTION(aeWEditor,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(aeWUpdate,"_ZN12CUnitSpawner6updateEf")
TL_FUNCTION(aeWCreate,"_ZN12CUnitSpawner19createUnitsInMemoryEv")
TL_FUNCTION(aeWSpawn,"_ZN12CUnitSpawner5spawnEv")
TL_FUNCTION(aeWActivate,"_ZN9CTeleport8activateEN4Ogre7Vector3ES1_")
TL_FUNCTION(aeWPieces,"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(aeWSave,"_ZN11CDescriptor10saveObjectEP17CEditorBaseObjectP10CDataGroupP28CDescriptorSaveConfiguration")
extern "C" char aeWLogGet[] __asm__("_ZN4Ogre10LogManager12getSingletonEv");
extern "C" char aeWLog[] __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
extern "C" char aeWBase[] __asm__("_ZTV17CEditorBaseObject");
extern "C" char aeWEquipment[] __asm__("_ZTV10CEquipment");
extern "C" char aeWSpawner[] __asm__("_ZTV12CUnitSpawner");
extern "C" char aeWRoom[] __asm__("_ZTV5CRoom");
extern "C" char aeWTeleport[] __asm__("_ZTV9CTeleport");
const wchar_t* const aeSpawnNames[] = {L"Monsters", L"Items", L"Particle", L"Spawn Class", L"Missiles", L"Unit Type", L"Props"};
namespace {
struct Case{unsigned op,seed,kind;};Case input;autotest::Capture*output;CDescriptor*descriptor;CEditorBaseObject*object;CResourceManager*resources[2];CEditorScene*scenes[2];CLevel*levels[2];void*group;void*config;void*logObject;TArrayList<CEditorBaseObject*>*pieces;Ogre::Vector3 forward;
void number(unsigned n){output->add(&n,4);}void check(bool x){number(x);if(!x)output->issue=autotest::Capture::InvalidReport;}
void event(unsigned n,void*p){number(n);check(p==object);}
Ogre::Vector3 position(void*p,bool absolute){event(1,p);number(absolute);if(input.op==3)forward=Ogre::Vector3(-8.75f,2.5f,1.25f);if(input.op==0&&input.seed%8==6)descriptor->m_pSceneOwner=scenes[1];return Ogre::Vector3(input.seed*0.25f,-2.5f,5.75f);}
void* add(void*p,void*item,const Ogre::Vector3&v,bool flag){number(2);check(p==levels[input.op==0&&input.seed%8==6?1:0]);check(item==object);output->add(&v,12);number(flag);number(static_cast<CEquipment*>(item)->m_bSaveFlag191);if(input.seed%8==7)descriptor->m_Objects.clear();return item;}
bool editor(void*p){number(3);check(p==resources[0]);return input.seed&1;}
void update(void*p,float elapsed){event(4,p);output->add(&elapsed,4);if(input.seed%8==7)descriptor->m_Objects.clear();}
void create(void*p){event(5,p);CUnitSpawner*spawner=static_cast<CUnitSpawner*>(p);if(input.seed&16)spawner->m_spawnOnCreate=!spawner->m_spawnOnCreate;if(input.seed&32)spawner->m_category=aeSpawnNames[4];}
void spawn(void*p){event(6,p);if(input.seed%8==7)descriptor->m_Objects.clear();}
void enabled(void*p,bool flag){event(7,p);number(flag);static_cast<CTeleport*>(p)->m_bEnabled=flag;}
void visible(void*p,bool flag){event(8,p);number(flag);}
const Ogre::Vector3&getForward(void*p){event(9,p);return forward;}
void activate(void*p,Ogre::Vector3 a,Ogre::Vector3 b){event(10,p);output->add(&a,12);output->add(&b,12);}
void*getPieces(void*p,const std::wstring&name){number(11);check(p==scenes[0]);output->addText(name);return input.seed%3==0?NULL:pieces;}
void save(void*p,void*obj,void*g,void*c){number(12);check(p==descriptor);check(obj==object);check(g==group);check(c==config);output->addText(static_cast<CRoom*>(obj)->getMeshFileCreatedDynamically());}
void*logGet(){number(13);return logObject;}
void log(void*p,const std::string&text,unsigned level,bool mask){number(14);check(p==logObject);output->addText(text);number(level);number(mask);}
void side(void*raw,autotest::Capture&out,bool ours){input=*static_cast<Case*>(raw);output=&out;uint64_t desc[128]={0},obj[1024]={0},sc[2][(sizeof(CEditorScene)+7)/8]={{0}},res[2][(sizeof(CResourceManager)+7)/8]={{0}},lev[2][(sizeof(CLevel)+7)/8]={{0}},gr[16]={0},cf[(sizeof(CDescriptorSaveConfiguration)+7)/8]={0},lg[16]={0};descriptor=reinterpret_cast<CDescriptor*>(desc);object=reinterpret_cast<CEditorBaseObject*>(obj);group=gr;config=cf;logObject=lg;for(unsigned i=0;i<2;++i){scenes[i]=reinterpret_cast<CEditorScene*>(sc[i]);resources[i]=reinterpret_cast<CResourceManager*>(res[i]);levels[i]=reinterpret_cast<CLevel*>(lev[i]);scenes[i]->m_pResourceManager=resources[i];resources[i]->m_pLevel=levels[i];}descriptor->m_pSceneOwner=scenes[0];
 char*table=input.kind==0?aeWBase:input.op==0?aeWEquipment:input.op==1||input.op==2?aeWSpawner:input.op==3?aeWTeleport:aeWRoom;void*otable[100]={0};std::memcpy(otable,table,(input.kind==0||input.op==4?12:80)*8);otable[2+8]=reinterpret_cast<void*>(&enabled);otable[2+10]=reinterpret_cast<void*>(&visible);otable[2+0x130/8]=reinterpret_cast<void*>(&getForward);*reinterpret_cast<void**>(object)=otable+2;
 if(input.op<3){static_cast<CSceneNodeObject*>(object)->m_pResourceManager=resources[0];new(&descriptor->m_Objects)TArrayList<CEditorBaseObject*>(2);if(input.seed%5){descriptor->m_Objects.add(object);descriptor->m_Objects.add(NULL);}if(input.seed%5==4)descriptor->m_Objects.add(object);}
 if(input.op==0&&input.seed%8==0)resources[0]->m_pLevel=NULL;
 if(input.op==1||input.op==2){CUnitSpawner*spawner=reinterpret_cast<CUnitSpawner*>(object);spawner->m_spawnOnCreate=input.seed&2;const unsigned categories[]={4,2,0,6};new(&spawner->m_category)std::wstring(aeSpawnNames[categories[(input.seed/4)%4]]);levels[0]->m_flag258=input.seed&4;}
 if(input.op==3){forward=Ogre::Vector3(1,2,3);reinterpret_cast<CTeleport*>(object)->m_bEnabled=input.seed&1;}
 TArrayList<CEditorBaseObject*> p(2);pieces=&p;if(input.seed%3==2)p.add(object);
 if(input.op==4){CRoom*room=reinterpret_cast<CRoom*>(object);new(&room->m_sSceneOverrideFile)std::wstring(input.seed&1?L"override.layout":L"");new(&room->m_sMeshFileCreatedDynamically)std::wstring(L"old.mesh");CDescriptorSaveConfiguration*cfg=reinterpret_cast<CDescriptorSaveConfiguration*>(config);const wchar_t*names[]={L"",L"file.layout",L"a.b.c",L".hidden",L"plain",L"Ж/room.layout"};new(&cfg->m_sFileName)std::wstring(names[input.seed%6]);}
 detour::Set d;TL_REDIRECT(d,aeWPosition,&position);TL_REDIRECT(d,aeWAdd,&add);TL_REDIRECT(d,aeWEditor,&editor);TL_REDIRECT(d,aeWUpdate,&update);TL_REDIRECT(d,aeWCreate,&create);TL_REDIRECT(d,aeWSpawn,&spawn);TL_REDIRECT(d,aeWActivate,&activate);TL_REDIRECT(d,aeWPieces,&getPieces);TL_REDIRECT(d,aeWSave,&save);d.redirect(aeWLogGet,aeWLogGet,&logGet);d.redirect(aeWLog,aeWLog,&log);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(input.op==0)autotest::invoke(out,ours?aeWNewItem:aeWOldItem,descriptor,scenes[0]);
 if(input.op==1){const uint32_t bits[]={0,0x80000000u,0x3f800000u,0xbf800000u,0x7fc12345u,0x7f800000u};float elapsed;uint32_t b=bits[input.seed%6];std::memcpy(&elapsed,&b,4);autotest::invoke(out,ours?aeWNewUpdate:aeWOldUpdate,descriptor,elapsed);}
 if(input.op==2)autotest::invoke(out,ours?aeWNewActivated:aeWOldActivated,descriptor,scenes[0]);
 if(input.op==3){const unsigned events[]={0,1,2,3,4,37,38,39,0xffffffffu};autotest::invoke(out,ours?aeWNewTeleport:aeWOldTeleport,descriptor,input.seed%7?object:NULL,events[input.seed%9],group);number(reinterpret_cast<CTeleport*>(object)->m_bEnabled);}
 if(input.op==4){autotest::invoke(out,ours?aeWNewRoom:aeWOldRoom,descriptor,input.seed%7?object:NULL,group,config);CRoom*room=reinterpret_cast<CRoom*>(object);out.addText(room->m_sMeshFileCreatedDynamically);room->m_sSceneOverrideFile.~basic_string();room->m_sMeshFileCreatedDynamically.~basic_string();reinterpret_cast<CDescriptorSaveConfiguration*>(config)->m_sFileName.~basic_string();}
 if(input.op<3){number(descriptor->m_Objects.size());descriptor->m_Objects.~TArrayList<CEditorBaseObject*>();if(input.op==0)number(reinterpret_cast<CEquipment*>(object)->m_bSaveFlag191);}
 if(input.op==1||input.op==2){CUnitSpawner*spawner=reinterpret_cast<CUnitSpawner*>(object);number(spawner->m_spawnOnCreate);out.addText(spawner->m_category);spawner->m_category.~basic_string();}
}
void old(void*p,autotest::Capture&c){side(p,c,false);}void newer(void*p,autotest::Capture&c){side(p,c,true);}
int run(const tlhybrid_host*host,unsigned op,const char*name,uint64_t address){autotest::Coverage coverage(name,address);for(unsigned seed=0;seed<144;++seed)for(unsigned kind=0;kind<2;++kind){Case c={op,seed,kind};autotest::Outcome a,b;autotest::runChild(old,&c,a);autotest::runChild(newer,&c,b);if(coverage.observe(host,a,b)){host->log("    advance world %u/%u kind%u status%d/%d bytes%lu/%lu\n",op,seed,kind,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(advance_editor_item_activation){return run(host,0,"advance_editor_item_activation",(uint64_t)(uintptr_t)aeWOldItem);}
TL_TEST(advance_editor_spawner_update){return run(host,1,"advance_editor_spawner_update",(uint64_t)(uintptr_t)aeWOldUpdate);}
TL_TEST(advance_editor_spawner_activation){return run(host,2,"advance_editor_spawner_activation",(uint64_t)(uintptr_t)aeWOldActivated);}
TL_TEST(advance_editor_teleport_dispatch){return run(host,3,"advance_editor_teleport_dispatch",(uint64_t)(uintptr_t)aeWOldTeleport);}
TL_TEST(advance_editor_room_save){return run(host,4,"advance_editor_room_save",(uint64_t)(uintptr_t)aeWOldRoom);}
