#include "tests/FinishLevelFixture.h"
#include "tests/NativeMenuServices.h"
#include "tests/SystemsFixtureWorker.h"
#include "NativeAutomapFixture.h"
#define private public
#define protected public
#include "FormationNode.h"
#include "TimerStatics.h"
#include "MissilePreloader.h"
#include "ParticlePreloader.h"
#include "ResourceSettings.h"
#include "Quadtree.h"
#undef private
#undef protected
#include <OgreStaticGeometry.h>
#include <ucontext.h>
#include <signal.h>
TL_ORIGINAL(void,ldOld,(CLevel*),"_ZN6CLevelD1Ev")
extern "C" void ldNew(CLevel*) __asm__("_ZN6CLevelD1Ev");
TL_ORIGINAL(void,ldCtor,(CLevel*,std::wstring,CSettings*,CGameClient*,CResourceManager*,Ogre::SceneManager*,CSoundManager*,int,int),"_ZN6CLevelC1ESbIwSt11char_traitsIwESaIwEEP9CSettingsP11CGameClientP16CResourceManagerPN4Ogre12SceneManagerEP13CSoundManagerii")
TL_FUNCTION(ldTemplateLoad,"_ZN18CLevelTemplateData4loadEPKw")
TL_FUNCTION(ldClear,"_ZN17CMissilePreloader19clearCachedMissilesEv")
TL_FUNCTION(ldUnload,"_ZN18CParticlePreloader28unloadParticlesOnLevelUnloadEv")
namespace {
nativegame::Services*services; CResourceManager*resources; CAutomap*automap;
CMissilePreloader*missiles;CParticlePreloader*particles;const tlhybrid_host*logger;
autotest::Capture*output;unsigned clearCalls,unloadCalls;detour::Set*clearHook,*unloadHook;volatile sig_atomic_t phase;
void number(unsigned n){output->add(&n,4);}
void fault(int signal,siginfo_t*info,void*raw){ucontext_t*u=static_cast<ucontext_t*>(raw);logger->log("    levelD1 signal%d phase%d rip%lx addr%lx\n",signal,int(phase),(unsigned long)u->uc_mcontext.gregs[REG_RIP],(unsigned long)info->si_addr);struct sigaction a;std::memset(&a,0,sizeof a);a.sa_handler=SIG_DFL;sigemptyset(&a.sa_mask);sigaction(signal,&a,NULL);raise(signal);}
void load(CLevelTemplateData*,const wchar_t*){}
void clear(CMissilePreloader*p){number(1);number(p==missiles);++clearCalls;clearHook->restore();p->clearCachedMissiles();TL_REDIRECT(*clearHook,ldClear,&clear);if(clearHook->failed())std::abort();}
void unload(CParticlePreloader*p){number(2);number(p==particles);++unloadCalls;unloadHook->restore();p->unloadParticlesOnLevelUnload();TL_REDIRECT(*unloadHook,ldUnload,&unload);if(unloadHook->failed())std::abort();}
struct Observer:iUnitObserver{virtual void unitStateChange(CBaseUnit*,EUNIT_STATES){} };
struct Listener:iLevelUpdatedCharacter{virtual void characterUpdatedInLevel(float,CCharacter*){}virtual void itemUpdatedInLevel(float,CItem*){} };
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=*static_cast<unsigned*>(raw);output=&out;phase=10;clearCalls=unloadCalls=0;
 CLevel*level=static_cast<CLevel*>(Ogre::NedAllocImpl::allocBytes(sizeof(CLevel),0,0,0));ldCtor(level,L"level-D1",services->settings,NULL,resources,services->scene,services->master->m_pSoundManager,17,3);
 detour::Set renderer;TL_REDIRECT(renderer,levelFixtureRemoveCollision,&finishlevel::removeNullCollisionModel);TL_REDIRECT(renderer,levelFixtureEditorRunning,&finishlevel::editorNotRunning);TL_REDIRECT(renderer,levelFixtureNodeBounds,&finishlevel::rendererFreeBounds);if(renderer.failed())std::abort();
 TSafePointer<CRunicCore>weak[32];CRunicCore*owned[32];unsigned count=0;
 phase=20;CTimerStatics*timer=NULL;if(seed&1){timer=new CTimerStatics;timer->m_startMicroseconds=0;timer->m_name=L"timer fixture";timer->m_statistics[L"sample"]=std::make_pair(17u,31u);level->m_timerStatics=timer;owned[count]=timer;weak[count++].setObject(timer);}
 if(seed&2)level->m_automap=automap;
 CLevelTemplateData*data=NULL;if(seed%4){detour::Set setup;TL_REDIRECT(setup,ldTemplateLoad,&load);if(setup.failed())std::abort();data=new CLevelTemplateData(L"D1-no-io");data->m_state761=(seed&8)!=0;level->m_pLevelTemplateData=data;owned[count]=data;weak[count++].setObject(data);}
 phase=30;unsigned geometry=(seed/4)%5;std::string names[4];Ogre::StaticGeometry**slots[]={&level->m_nonLightStaticGeometry,&level->m_nonLightStaticGeometry2,&level->m_nonLightStaticGeometry3,&level->m_lightStaticGeometry};for(unsigned i=0;i<geometry;++i){names[i]="level-D1-geometry-"+Ogre::StringConverter::toString(i);*slots[i]=services->scene->createStaticGeometry(names[i]);}
 if(seed&16){CCollisionList*p=new CCollisionList;level->m_collisionList=p;owned[count]=p;weak[count++].setObject(p);}
 if(seed&32){CQuadtree<unsigned>*p=new CQuadtree<unsigned>;p->m_minimumCellSize=1;p->m_minimum=Ogre::Vector3(-2,-3,-4);p->m_maximum=Ogre::Vector3(5,6,7);p->m_root=new CQuadtreeNode<unsigned>;p->m_root->m_subdivided=false;p->m_root->m_maximum=p->m_maximum;p->m_root->m_minimum=p->m_minimum;for(unsigned i=0;i<4;++i)p->m_root->m_children[i]=NULL;p->m_root->m_data.push_back(42);p->m_root->m_dataMinimum.push_back(p->m_minimum);p->m_root->m_dataMaximum.push_back(p->m_maximum);level->m_collisionTree=p;owned[count]=p;weak[count++].setObject(p);owned[count]=p->m_root;weak[count++].setObject(p->m_root);}
 phase=40;for(unsigned i=0;i<seed%3;++i){CEditorScene*p=new CEditorScene(L"level-D1-scene");level->m_RoomScenes.add(p);owned[count]=p;weak[count++].setObject(p);}
 for(unsigned i=0;i<seed/3%3;++i){CFormationNode*p=new CFormationNode(resources,NULL);level->m_formations.add(p);owned[count]=p;weak[count++].setObject(p);}
 phase=50;CCharacter*characters[3];CItem*items[3];unsigned chars=seed/5%4,itemCount=seed/7%4;
 for(unsigned i=0;i<chars;++i){CCharacter*p=new CCharacter(resources);characters[i]=p;owned[count]=p;weak[count++].setObject(p);finishlevel::prepend(level->m_pCharacters,p);if((seed+i)&1)finishlevel::prepend(level->m_activeCharacters,p);if((seed+i)&2)finishlevel::prepend(level->m_pendingCharacters,p);}
 for(unsigned i=0;i<itemCount;++i){CItem*p=new finishlevel::Item(resources);items[i]=p;owned[count]=p;weak[count++].setObject(p);finishlevel::prepend(level->m_items,p);if((seed+i)&1)finishlevel::prepend(level->m_activeItems,p);if((seed+i)&2)finishlevel::prepend(level->m_pendingItems,p);}
 if(seed&64){CItem*p=new finishlevel::Item(resources);owned[count]=p;weak[count++].setObject(p);finishlevel::prepend(level->m_pendingItems,p);finishlevel::prepend(level->m_activeItems,p);}
 if(seed&128){CCharacter*p=new CCharacter(resources);owned[count]=p;weak[count++].setObject(p);finishlevel::prepend(level->m_pendingCharacters,p);finishlevel::prepend(level->m_activeCharacters,p);}
 phase=60;Listener listeners[3];for(unsigned i=0;i<seed/11%4;++i)finishlevel::prepend(level->m_characterUpdateListeners,static_cast<iLevelUpdatedCharacter*>(&listeners[i]));if(seed/13%2&&level->m_characterUpdateListeners->m_pHead)level->m_pendingCharacterUpdateRemovals.add(level->m_characterUpdateListeners->m_pHead);
 Observer observers[3];for(unsigned i=0;i<seed/17%4;++i){TArrayList<iUnitObserver*>*list=NULL;if((seed+i)%3){list=new TArrayList<iUnitObserver*>(2);for(unsigned j=0;j<(seed+i)%4;++j)list->add(&observers[j%3]);}level->m_unitObservers[static_cast<long long>(i)-2]=list;}
 unsigned width=seed/19%5,height=seed/23%5;level->m_passWidth=width;level->m_passHeight=height;if(width){level->m_mapPassability=new short*[width];level->m_objectPassability=new short*[width];for(unsigned x=0;x<width;++x){level->m_mapPassability[x]=(seed+x)%3?new short[height+1]:NULL;level->m_objectPassability[x]=(seed+x)%4?new short[height+1]:NULL;}}
 detour::Set a,b;clearHook=&a;unloadHook=&b;TL_REDIRECT(a,ldClear,&clear);TL_REDIRECT(b,ldUnload,&unload);if(a.failed()||b.failed())std::abort();
 phase=100;{level_native::CameraNotificationDuringCleanup camera;typedef void(*Fn)(CLevel*);Fn fn=ours?ldNew:ldOld;if(!autotest::beginInvocation(out,fn))return;fn(level);out.callCompleted=1;}phase=200;a.restore();b.restore();number(clearCalls);number(unloadCalls);number(count);for(unsigned i=0;i<count;++i)number(weak[i].getObject()==NULL);for(unsigned i=0;i<geometry;++i)number(services->scene->hasStaticGeometry(names[i]));number(resources->m_pLevel==level);
 resources->m_pLevel=NULL;for(unsigned i=0;i<count;++i)if(weak[i].getObject())delete owned[i];Ogre::NedAllocImpl::deallocBytes(level);phase=300;
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){logger=host;struct sigaction a;std::memset(&a,0,sizeof a);a.sa_sigaction=&fault;a.sa_flags=SA_SIGINFO;sigemptyset(&a.sa_mask);sigaction(SIGSEGV,&a,NULL);sigaction(SIGABRT,&a,NULL);nativegame::Services native;services=&native;if(!native.ready())return 1;menugui::Audio audio(native.master);CResourceManager resourceOwner(native.scene);resources=&resourceOwner;finishlevel::initializeCharacterText();void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1495cc8),8);if(!p)new(reinterpret_cast<void*>(0x1495cc8))std::wstring;CMissilePreloader missileOwner(native.master->m_resourceSettings);missiles=&missileOwner;CParticlePreloader particleOwner(native.master->m_resourceSettings);particles=&particleOwner;CParticlePreloader*previous=native.master->m_pParticlePreloader;native.master->m_pParticlePreloader=particles;level_native::Automap map(resources,native.scene);automap=map.map;
 autotest::Coverage coverage("level_destructor",reinterpret_cast<uintptr_t>(ldOld));for(unsigned i=0;i<256;++i){autotest::Outcome a,b;autotest::runChild(original,&i,a);autotest::runChild(candidate,&i,b);if(coverage.observe(host,a,b)){host->log("    levelD1 seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned z=0;z<a.capture.length&&z<b.capture.length;++z)if(a.capture.data[z]!=b.capture.data[z]){host->log("    firstdiff%u old%02x new%02x\n",z,(unsigned char)a.capture.data[z],(unsigned char)b.capture.data[z]);break;}coverage.report(host);native.master->m_pParticlePreloader=previous;return 1;}}coverage.report(host);native.master->m_pParticlePreloader=previous;return coverage.completed!=256||coverage.missing||coverage.different;
}
}
TL_TEST(complete_level_destructor){return systems_fixture::isolated(&worker,host);}
