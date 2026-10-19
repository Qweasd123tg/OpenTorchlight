#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <typeinfo>
#include "tests/FinishLevelFixture.h"
#define private public
#define protected public
#include "Equipment.h"
#include "Hierarchy.h"
#include "Breakable.h"
#include "TriggerUnit.h"
#include "SpawnClass.h"
#include "DataGroup.h"
#include "StringTranslate.h"
#include "SoundManager.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"

#define PAIR(R,N,A,S) TL_ORIGINAL(R,old##N,A,S) extern "C" R new##N A __asm__(S);
PAIR(CItem*,Item,(CResourceManager*,CDataGroup*),"_ZN16CResourceManager13createNewItemEP10CDataGroup")
PAIR(void,Units,(CResourceManager*,CSpawnClass*,unsigned,const Ogre::Vector3&,CLevel*,CCharacter*,CCharacter*,int),"_ZN16CResourceManager40createUnitsBySpawnClassAtPositionInLevelEP11CSpawnClassjRKN4Ogre7Vector3EP6CLevelP10CCharacterS9_i")
TL_FUNCTION(rcCreate,"_ZN16CResourceManager23createUnitsBySpawnClassEP11CSpawnClassR10TArrayListIP9CBaseUnitEjP10CCharacterS8_ii")
TL_FUNCTION(rcPosition,"_ZN6CLevel18randomOpenPositionERKN4Ogre7Vector3Efb")
TL_FUNCTION(rcAdd,"_ZN6CLevel7addUnitEP9CBaseUnitRKN4Ogre7Vector3E")
TL_FUNCTION(rcSpawn,"_ZN10CCharacter5spawnEv")
TL_FUNCTION(rcGoldModel,"_ZN9CItemGold9loadModelESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(rcParticle,"_ZN16CResourceManager14createParticleEPKw")
TL_FUNCTION(rcVolatile,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_ORIGINAL(void,rcSoundCtor,(CSoundManager*,bool),"_ZN13CSoundManagerC1Eb")
TL_ORIGINAL(void,rcSoundDtor,(CSoundManager*),"_ZN13CSoundManagerD1Ev")
namespace {
struct Case {unsigned mode,seed;};
struct NativeAudio {
 CSoundManager*sound;CSoundManager*previous;
 NativeAudio():sound(static_cast<CSoundManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CSoundManager),0,0,0))),previous(CMasterResourceManager::getSingleton()->m_pSoundManager){std::memset(sound,0,sizeof(CSoundManager));rcSoundCtor(sound,false);CMasterResourceManager::getSingleton()->m_pSoundManager=sound;}
 ~NativeAudio(){CMasterResourceManager::getSingleton()->m_pSoundManager=previous;rcSoundDtor(sound);Ogre::NedAllocImpl::deallocBytes(sound);}
};
autotest::Capture* output;unsigned seed,randomCalls,addCalls;
CBaseUnit* pool[4]; CCharacter* owner; CCharacter* source;
void word(unsigned n){output->add(&n,4);}void scalar(float n){output->add(&n,4);}
void vector(const Ogre::Vector3&v){scalar(v.x);scalar(v.y);scalar(v.z);}
unsigned id(CBaseUnit*p){if(!p)return 0;for(unsigned i=0;i<4;++i)if(pool[i]==p)return i+1;return 99;}
// Native Gold construction stays intact; only asset/GPU collaborators are
// replaced with typed observations. No Gold constructor acceptance is claimed.
void goldModel(CItemGold*,std::wstring name){word(105);word(name.size());for(unsigned i=0;i<name.size();++i)word(name[i]);}
CParticle* particle(CResourceManager*,const wchar_t*name){word(106);for(unsigned i=0;name[i];++i)word(name[i]);word(0);return NULL;}
float volatileRandom(float a,float b){word(107);scalar(a);scalar(b);return a+(b-a)*0.375f;}
void create(CResourceManager*,CSpawnClass*,TArrayList<CBaseUnit*>& units,unsigned count,CCharacter*a,CCharacter*b,int level,int flags){
 word(101);word(count);word(a==owner);word(b==source);word(level);word(flags);word(units.size());word(units.m_nCapacity);
 unsigned n=seed%15;for(unsigned i=0;i<n;++i)units.add(pool[(seed+i)%4]);
}
Ogre::Vector3 position(CLevel*,const Ogre::Vector3&v,float radius,bool option){
 word(102);vector(v);scalar(radius);word(option);++randomCalls;
 return Ogre::Vector3(v.x+radius+float(randomCalls),v.y-17.25f,v.z-radius-float(randomCalls)*0.5f);
}
void add(CLevel*,CBaseUnit*unit,const Ogre::Vector3&v){word(103);word(id(unit));vector(v);unit->m_vPosition=v;++addCalls;}
void spawn(CCharacter*who){word(104);word(id(who));vector(who->m_vForward);vector(who->m_vRight);vector(who->m_vPosition);}
void execute(void*raw,autotest::Capture&out,bool ours){
 Case c=*static_cast<Case*>(raw);output=&out;seed=c.seed;randomCalls=addCalls=0;
 finishlevel::Fixture fixture;fixture.resources.m_pSceneManager=Ogre::Root::getSingleton().getSceneManager("rc-scene");
 if(c.mode==0){
  CStringTranslate translation(L"");
  CDataGroup data(L"resource creation",NULL,4,2,NULL);
  const wchar_t*types[]={L"EQUIPMENT",L"equipment",L"EqUiPmEnT",L"BREAKABLE",L"breakable",L"TRIGGER",L"trigger",L"GOLD",L"gold",L"",L"MONSTER",L" EQUIPMENT",L"GOLD ",L"UNKNOWN",L"\u0422\u0420\u0418\u0413\u0413\u0415\u0420"};
  if(seed%16!=15)data.SetDataValue(L"CREATEAS",types[seed%15],false);
  detour::Set assets;TL_REDIRECT(assets,rcGoldModel,&goldModel);TL_REDIRECT(assets,rcParticle,&particle);TL_REDIRECT(assets,rcVolatile,&volatileRandom);
  if(assets.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  typedef CItem*(*Fn)(CResourceManager*,CDataGroup*);Fn fn=ours?newItem:oldItem;
  if(!autotest::beginInvocation(out,fn))return;CItem*item=fn(&fixture.resources,&data);out.callCompleted=1;
  word(item!=NULL);
  if(item){
   word(dynamic_cast<CEquipment*>(item)!=NULL);word(dynamic_cast<CBreakable*>(item)!=NULL);word(dynamic_cast<CTriggerUnit*>(item)!=NULL);word(dynamic_cast<CItemGold*>(item)!=NULL);
   CItemGold*gold=dynamic_cast<CItemGold*>(item);if(gold)word(gold->m_goldAmount);
   word(item->getResourceManager()==&fixture.resources);word(item->m_eUnitType);word(item->m_bVisible);vector(item->m_vPosition);vector(item->m_vScale);
   TSafePointer<CItem> weak;weak.setObject(item);delete item;word(weak.getObject()==NULL);
  }
 }else{
  fixture.resources.m_pHierarchy=CMasterResourceManager::getSingleton()->m_pHierarchy;
  for(unsigned i=0;i<3;++i){const unsigned types[]={8,31,34};fixture.resources.m_pHierarchy->m_parentTypes[types[i]].clear();fixture.resources.m_pHierarchy->m_parentTypes[types[i]].push_back(types[i]);}fixture.resources.m_pHierarchy->m_parentTypes[34].push_back(31);
  CCharacter a(&fixture.resources),b(&fixture.resources),d(&fixture.resources);finishlevel::Item item(&fixture.resources);
  pool[0]=&a;pool[1]=&b;pool[2]=&item;pool[3]=&d;owner=seed%3?&a:NULL;source=seed%4?&d:NULL;
  for(unsigned i=0;i<4;++i){pool[i]->m_vPosition=Ogre::Vector3(float(i*3),float(i)-2,float(i)*0.5f);pool[i]->m_eUnitType=static_cast<UNITTYPES::EUNITTYPES>((seed+i)%5==0?31:((seed+i)%5==1?34:8));}
  CSpawnClass spawnClass(L"creation-test");fixture.level.m_dungeonDepth=int(seed%9)-3;
  Ogre::Vector3 target(float(int(seed%17)-8),float(seed%7)*0.25f,float(int(seed%13)-6));
  detour::Set hooks;TL_REDIRECT(hooks,rcCreate,&create);TL_REDIRECT(hooks,rcPosition,&position);TL_REDIRECT(hooks,rcAdd,&add);TL_REDIRECT(hooks,rcSpawn,&spawn);
  if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  typedef void(*Fn)(CResourceManager*,CSpawnClass*,unsigned,const Ogre::Vector3&,CLevel*,CCharacter*,CCharacter*,int);Fn fn=ours?newUnits:oldUnits;
  if(!autotest::beginInvocation(out,fn))return;
  fn(&fixture.resources,seed%31==0?NULL:&spawnClass,seed%23,target,seed%37==0?NULL:&fixture.level,owner,source,seed%3?-1:int(seed%11)-4);out.callCompleted=1;
  word(randomCalls);word(addCalls);for(unsigned i=0;i<4;++i){vector(pool[i]->m_vPosition);vector(pool[i]->m_vForward);vector(pool[i]->m_vRight);}
 }
}
void original(void*p,autotest::Capture&o){execute(p,o,false);}void candidate(void*p,autotest::Capture&o){execute(p,o,true);}
int run(const tlhybrid_host*host,unsigned mode,const char*name,uintptr_t address){
 nativegame::Services services;if(!services.ready())return 1;
 NativeAudio audio;
 Ogre::SceneManager*scene=Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC,"rc-scene");
 autotest::Coverage coverage(name,address);unsigned n=mode?512:128;
 for(unsigned i=0;i<n;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    resource mode%u seed%u issue%u/%u status%d/%d length%lu/%lu\n",mode,i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);Ogre::Root::getSingleton().destroySceneManager(scene);return 1;}}
 coverage.report(host);Ogre::Root::getSingleton().destroySceneManager(scene);return 0;
}
}
TL_TEST(all_resource_creation_item){return run(host,0,"all_resource_creation_item",(uintptr_t)&oldItem);}
TL_TEST(all_resource_creation_units){return run(host,1,"all_resource_creation_units",(uintptr_t)&oldUnits);}
