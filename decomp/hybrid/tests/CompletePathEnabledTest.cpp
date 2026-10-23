#include <execinfo.h>
#include <ucontext.h>
#include "AutoTest.h"
#include "tests/FinishLevelFixture.h"
#include "tests/NativeMenuClient.h"
#include "tests/CharacterEmptyGlobals.h"
#include "tests/SystemsFixtureWorker.h"
#include "PathController.h"
#include "DataGroup.h"
TL_ORIGINAL(void,peOld,(CPathController*,bool),"_ZN15CPathController10setEnabledEb")
extern "C" void peNew(CPathController*,bool) __asm__("_ZN15CPathController10setEnabledEb");
TL_ORIGINAL(void,peCharacterCtor,(CCharacter*,CResourceManager*),"_ZN10CCharacterC1EP16CResourceManager")
TL_ORIGINAL(void,peCharacterDtor,(CCharacter*),"_ZN10CCharacterD1Ev")
namespace {
const tlhybrid_host* diagnosticHost;
struct Case { unsigned seed, negative; };
volatile sig_atomic_t diagnosticStage, diagnosticSeed, diagnosticOurs;
void diagnosticAbort(int line){diagnosticHost->log("    fixture abort at line%d\n",line);std::abort();}
void diagnosticFault(int signal, siginfo_t*, void* context){
    ucontext_t* machine=static_cast<ucontext_t*>(context);
    diagnosticHost->log("    path signal%d seed%d candidate%d stage%d rip%p\n",signal,int(diagnosticSeed),int(diagnosticOurs),int(diagnosticStage),reinterpret_cast<void*>(machine->uc_mcontext.gregs[REG_RIP]));
    void* frames[32];int count=backtrace(frames,32);
    for(int i=0;i<count;++i)diagnosticHost->log("    fixture signal%d frame%d %p\n",signal,i,frames[i]);
    _exit(128+signal);
}
void installDiagnostics(unsigned seed,bool ours){
    diagnosticSeed=seed;diagnosticOurs=ours;diagnosticStage=0;
    struct sigaction action;std::memset(&action,0,sizeof action);action.sa_sigaction=&diagnosticFault;action.sa_flags=SA_SIGINFO;sigemptyset(&action.sa_mask);
    sigaction(SIGABRT,&action,NULL);sigaction(SIGSEGV,&action,NULL);
}

CResourceManager*resources;CLevel*level;CGameClient*client;CCharacter*units[3];CDataGroup*data;CDataGroup*otherData;CPathController*path;CPathController*other;autotest::Capture*output;bool invoking;
void n(autotest::Capture&o,unsigned x){o.add(&x,4);}void f(autotest::Capture&o,float x){o.add(&x,4);}unsigned unitID(CCharacter*p){for(unsigned i=0;i<3;++i)if(p==units[i])return i;return p?0xfffffffe:0xffffffff;}unsigned pathID(CPathController*p){return p==path?1:p==other?2:p?3:0;}
struct Path: CPathController{Path(CResourceManager*p):CPathController(p){}virtual void BroadcastEvent(unsigned event){if(invoking){n(*output,0x12345678);n(*output,event);}CEditorBaseObject::BroadcastEvent(event);}};
void state(autotest::Capture&o,CCharacter*p){n(o,p->getEnabled());n(o,p->getAIState());n(o,pathID(p->m_pathToFollow.getObject()));n(o,unitID(p->m_targetCharacter.getObject()));n(o,p->m_targetItem.getObject()==NULL);n(o,p->m_isPathing);f(o,p->m_pathGraceTime);f(o,p->m_pathTime);o.add(p->m_pathDestination.ptr(),12);n(o,p->m_savedPathIterations);}
void side(void*raw,autotest::Capture&out,bool ours){const Case& c=*static_cast<Case*>(raw);unsigned seed=c.seed;installDiagnostics(seed,ours);output=&out;invoking=false;CEditorScene owner(L"path-enabled-scene");Path actual(resources);CPathController alternate(resources);path=&actual;other=&alternate;path->SetSceneOwner(seed/4%3?&owner:NULL);path->setPosition(Ogre::Vector3(-1.f,2.f,3.f));path->m_bEnabled=seed%2;bool enabled=seed/2%2;path->m_bEnableUnitOnStart=seed/8%2;path->m_bWalkToPlayer=seed/16%2;path->m_bUnknown136=true;unsigned mode=seed/32%5;path->m_bUnknown137=mode==3||mode==4;path->m_pUnitInteractDataGroup=seed/5%3?data:NULL;path->m_fUnknown180=57.f;path->m_pathDistances.add(99.f);for(unsigned i=0;i<seed/3%5;++i){path->m_pathCoordinates.add(float(i)*3);path->m_pathCoordinates.add(float(i)*-2);path->m_pathCoordinates.add(float(i)*4);}client->m_pPlayer=mode==4?NULL:static_cast<CPlayer*>(units[0]);
 for(unsigned i=0;i<3;++i){CCharacter*p=units[i];p->m_eAIState=static_cast<EAIState>(seed/11%4);p->setEnabled(seed/7%2);p->m_isPathing=seed/6%2;p->m_pathGraceTime=.25f;p->m_pathTime=.75f;p->m_pathDestination=Ogre::Vector3(7,8,9);p->m_targetLocked=false;p->m_bBaseUnitFlag0=false;p->m_pathToFollow.setObject(seed/9%3==0?path:seed/9%3==1?other:NULL);p->m_targetCharacter.setObject(units[(i+1)%3]);p->setPosition(Ogre::Vector3(float(i)*3.f,1.f,float(i)*-2.f));p->m_pDataGroup=(i+seed/7)%3?data:otherData;}
 if(mode<3){for(unsigned i=0;i<mode+1;++i){TSafePointer<CCharacter>*safe=OGRE_NEW_T(TSafePointer<CCharacter>,Ogre::MEMCATEGORY_GENERAL)();if(!enabled&&!path->m_bEnableUnitOnStart&&seed/13%2&&i==0)safe->setObject(NULL);else safe->setObject(units[(i+seed/3)%3]);path->m_units.add(safe);}}
 void(*fn)(CPathController*,bool)=ours?peNew:peOld;invoking=true;if(autotest::beginInvocation(out,fn)){diagnosticStage=1;fn(path,enabled);out.callCompleted=1;diagnosticStage=2;}if(ours&&c.negative)path->m_bEnabled=!path->m_bEnabled;invoking=false;n(out,path->m_bEnabled);n(out,path->m_bUnknown136);n(out,path->m_units.size());for(unsigned i=0;i<path->m_units.size();++i)n(out,unitID(path->m_units[i]->getObject()));Ogre::Vector3 position=path->getPosition(false);out.add(position.ptr(),12);f(out,path->m_fUnknown180);n(out,path->m_pathDistances.size());for(unsigned i=0;i<path->m_pathDistances.size();++i)f(out,path->m_pathDistances[i]);for(unsigned i=0;i<3;++i)state(out,units[i]);for(unsigned i=0;i<3;++i){units[i]->m_pathToFollow.setObject(NULL);units[i]->m_targetCharacter.setObject(NULL);}client->m_pPlayer=NULL;diagnosticStage=4;
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){diagnosticHost=host;initEmptyGlobals();void*pathGroup=NULL;std::memcpy(&pathGroup,reinterpret_cast<void*>(0x1428748),8);if(!pathGroup)new(reinterpret_cast<void*>(0x1428748))std::wstring(L"MONSTERS");nativegame::Services native;if(!native.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());menugui::Client actualClient(*CMasterResourceManager::getSingleton()->m_pSettings,CMasterResourceManager::getSingleton(),*CMasterResourceManager::getSingleton()->m_pSoundManager);client=actualClient.client;finishlevel::Fixture fixture;resources=&fixture.resources;resources->m_pSceneManager=native.scene;resources->m_GameClients.add(client);level=&fixture.level;CDataGroup group(L"unit",NULL,10,10,NULL),otherGroup(L"other",NULL,10,10,NULL);data=&group;otherData=&otherGroup;units[0]=nativegame::createPlayer(resources);for(unsigned i=1;i<3;++i){units[i]=static_cast<CCharacter*>(Ogre::NedAllocImpl::allocBytes(sizeof(CCharacter),0,0,0));std::memset(units[i],0,sizeof(CCharacter));peCharacterCtor(units[i],resources);}for(unsigned i=0;i<3;++i){units[i]->sceneNodeSetParent(native.scene->getRootSceneNode(),false);finishlevel::prepend(level->m_pCharacters,units[i]);}finishlevel::Item item(resources);item.m_pDataGroup=data;finishlevel::prepend<CItem*>(level->m_items,&item);
 autotest::Coverage coverage("complete_path_enabled",reinterpret_cast<uintptr_t>(peOld));for(unsigned seed=0;seed<640;++seed){Case c={seed,0};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    path enabled seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);if(a.capture.length==b.capture.length)for(unsigned j=0;j<a.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %u/%u\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}coverage.report(host);return 1;}}coverage.report(host);
 Case control={114,1};autotest::Outcome a,b;autotest::runChild(original,&control,a);autotest::runChild(candidate,&control,b);
 bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);
 bool completed=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!autotest::incomplete(a)&&!autotest::incomplete(b);
 host->log("    complete_path_enabled negative detected%u completed%u valid%u/%u exit%d/%d incomplete%u/%u\n",unsigned(detected),unsigned(completed),a.reportValid,b.reportValid,a.childStatus,b.childStatus,unsigned(autotest::incomplete(a)),unsigned(autotest::incomplete(b)));
 if(!detected||!completed)return 1;
 finishlevel::clearNodes(level->m_pCharacters);finishlevel::clearNodes(level->m_items);for(unsigned i=1;i<3;++i){peCharacterDtor(units[i]);Ogre::NedAllocImpl::deallocBytes(units[i]);}nativegame::destroyPlayer(static_cast<CPlayer*>(units[0]));resources->m_GameClients.clear();return coverage.completed!=640||coverage.missing||coverage.different;}
}
TL_TEST(complete_path_enabled){return systems_fixture::isolated(&worker,host);}
