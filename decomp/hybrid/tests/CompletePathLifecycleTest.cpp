#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#define private public
#define protected public
#include "PathController.h"
#include "RunicCore.h"
#include "Player.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(void,pathLifeOldCtor,(CPathController*,CResourceManager*),"_ZN15CPathControllerC1EP16CResourceManager")
TL_ORIGINAL(void,pathLifeOldDtor,(CPathController*),"_ZN15CPathControllerD1Ev")
extern "C" void pathLifeNewCtor(CPathController*,CResourceManager*) __asm__("_ZN15CPathControllerC1EP16CResourceManager");
extern "C" void pathLifeNewDtor(CPathController*) __asm__("_ZN15CPathControllerD1Ev");
TL_ORIGINAL(void,pathLifeResourceCtor,(CResourceManager*,Ogre::SceneManager*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,pathLifeResourceDtor,(CResourceManager*),"_ZN16CResourceManagerD1Ev")
namespace {
CResourceManager*resources;CPlayer*player;
struct Case{unsigned seed,operation,negative;};
void word(autotest::Capture&o,unsigned n){o.add(&n,sizeof n);}void real(autotest::Capture&o,float n){o.add(&n,sizeof n);}
void initWide(uintptr_t address,const wchar_t*value){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(address),8);if(!p)new(reinterpret_cast<void*>(address))std::wstring(value);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);CPathController*path=static_cast<CPathController*>(Ogre::NedAllocImpl::allocBytes(sizeof(CPathController),0,0,0));std::memset(path,0xa5,sizeof(CPathController));int before=g_iTotalCountOfObjects;
 CResourceManager*rm=c.seed%2?resources:NULL;
 if(c.operation==0){void(*fn)(CPathController*,CResourceManager*)=ours?pathLifeNewCtor:pathLifeOldCtor;if(autotest::beginInvocation(out,fn)){fn(path,rm);out.callCompleted=1;}}
 else pathLifeOldCtor(path,rm);
 if(c.operation==0){word(out,g_iTotalCountOfObjects-before);word(out,path->getResourceManager()==rm);word(out,path->getSceneNode()!=NULL);word(out,path->m_pUnitInteractDataGroup==NULL);word(out,path->m_units.size());word(out,path->m_units.m_nCapacity);word(out,path->m_pathNodes.size());word(out,path->m_pathNodes.m_nCapacity);word(out,path->m_pathCoordinates.size());word(out,path->m_pathCoordinates.m_nCapacity);word(out,path->m_pathDistances.size());word(out,path->m_pathDistances.m_nCapacity);out.addText(path->m_pCategory);out.addText(path->m_sUnitInteractWith);out.addText(path->m_pathName);word(out,path->m_bVisible);word(out,path->m_bUnknown131);word(out,path->m_bUnknown132);word(out,path->m_bEnabled);word(out,path->m_bUnitRunsOnPath);word(out,path->m_bWalkToPlayer);word(out,path->m_bUnknown136);word(out,path->m_bUnknown137);real(out,path->m_fUnknown180);word(out,path->m_iNumberOfPathPoints);word(out,path->m_bEnableUnitOnStart);pathLifeOldDtor(path);}
 else {unsigned n=c.seed%9;for(unsigned i=0;i<n;++i){TSafePointer<CCharacter>*safe=OGRE_NEW_T(TSafePointer<CCharacter>,Ogre::MEMCATEGORY_GENERAL)();if((i+c.seed)%3)safe->setObject(player);path->m_units.add(safe);}for(unsigned i=0;i<c.seed%7;++i)path->m_pathNodes.add(NULL);for(unsigned i=0;i<c.seed%17;++i){path->m_pathCoordinates.add(i+.5f);path->m_pathDistances.add(i+.25f);}path->m_pathName=c.seed%2?L"route":L"\u0422\u0440\u043e\u043f\u0430";path->m_pCategory=L"MONSTERS";path->m_sUnitInteractWith=L"PLAYER";TSafePointer<CPathController> observer;observer.setObject(path);word(out,player->m_pSafePointers?player->m_pSafePointers->size():0);void(*fn)(CPathController*)=ours?pathLifeNewDtor:pathLifeOldDtor;if(autotest::beginInvocation(out,fn)){fn(path);out.callCompleted=1;}word(out,observer.getObject()==NULL);word(out,player->m_pSafePointers?player->m_pSafePointers->size():0);word(out,g_iTotalCountOfObjects-before);}
 if(ours&&c.negative)word(out,0xbadc0de);
 Ogre::NedAllocImpl::deallocBytes(path);
}
void oldSide(void*p,autotest::Capture&o){side(p,o,false);}void newSide(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;initWide(0x1428728,L"");initWide(0x1428748,L"MONSTERS");resources=static_cast<CResourceManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CResourceManager),0,0,0));pathLifeResourceCtor(resources,services.scene);player=nativegame::createPlayer(resources);autotest::Coverage ctor("complete_path_lifecycle",reinterpret_cast<uintptr_t>(pathLifeOldCtor)),dtor("complete_path_lifecycle",reinterpret_cast<uintptr_t>(pathLifeOldDtor));for(unsigned op=0;op<2;++op)for(unsigned seed=0;seed<128;++seed){Case c={seed,op};autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);autotest::Coverage&coverage=op?dtor:ctor;if(coverage.observe(host,a,b)){host->log("    path lifecycle op%u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",op,seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}ctor.report(host);dtor.report(host);for(unsigned op=0;op<2;++op){Case control={71,op,1};autotest::Outcome a,b;autotest::runChild(oldSide,&control,a);autotest::runChild(newSide,&control,b);bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);bool completed=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!autotest::incomplete(a)&&!autotest::incomplete(b);host->log("    path lifecycle negative op%u detected%u completed%u\n",op,unsigned(detected),unsigned(completed));if(!detected||!completed)return 1;}nativegame::destroyPlayer(player);pathLifeResourceDtor(resources);Ogre::NedAllocImpl::deallocBytes(resources);return ctor.completed!=128||dtor.completed!=128||ctor.missing||dtor.missing||ctor.different||dtor.different;
}
}
TL_TEST(complete_path_lifecycle){return systems_fixture::isolated(&worker,host);}
