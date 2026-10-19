#include "tests/FinishLevelFixture.h"
#include "GameClientOwnedNative.h"
#include "GameClientUiOwner.h"
#include "GameClientNativeSteam.h"
#include "NativeLevelPreloader.h"
#include "tests/NativeEditorControls.h"
#include "tests/SystemsFixtureWorker.h"
#include <OgreSubMesh.h>
#include <OgreEntity.h>
#include <clocale>
#include <fcntl.h>
#include <ucontext.h>
#include <execinfo.h>
TL_ORIGINAL(void,gcloadOld,(CGameClient*,int,int,std::wstring),"_ZN11CGameClient13loadMenuLevelEiiSbIwSt11char_traitsIwESaIwEE")
extern "C" void gcloadNew(CGameClient*,int,int,std::wstring) __asm__("_ZN11CGameClient13loadMenuLevelEiiSbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(gcloadDungeon,"_ZN11CGameClient17setCurrentDungeonESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(gcloadSeed,"_ZN11CGameClient13resetGameSeedEi")
TL_FUNCTION(gcloadTemplate,"_ZN8CDungeon28getLevelTemplateDataForDepthEP11CGameClientj")
TL_FUNCTION(gcloadRoom,"_ZN6CLevel14loadRoomLayoutESbIwSt11char_traitsIwESaIwEEb15ELevelEntryTypePSt6vectorIS3_SaIS3_EES3_")
TL_FUNCTION(gcloadActivate,"_ZN6CLevel8activateEv")
TL_FUNCTION(gcloadProjector,"_ZN6CLevel16setProjectorPassEPN4Ogre7FrustumES2_P13CGenericModelS4_RKSsS6_")
TL_FUNCTION(gcloadLighting,"_ZN11CGameClient15refreshLightingEv")
TL_FUNCTION(gcloadCursor,"_ZN7CGameUI14setCursorStateE12ECursorState")
TL_FUNCTION(gcloadStop,"_ZN13CSoundManager9stopMusicEv")
TL_FUNCTION(gcloadPlay,"_ZN13CSoundManager9playMusicERSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(gcloadModel,"_ZN16CResourceManager18createGenericModelEPN4Ogre12SceneManagerEPKwS4_bbb")
TL_FUNCTION(gcloadLayout,"_ZN7CLayout14loadLayoutFileERKSbIwSt11char_traitsIwESaIwEEbP13CTimerStaticsbbj")
TL_FUNCTION(gcloadStart,"_ZN7CLayout5startEv")
TL_FUNCTION(gcloadInited,"_ZN6CLevel9setInitedEb")
namespace {
unsigned phase;
void fault(int sig,siginfo_t*info,void*raw){int fd=open("/home/qweasd123tg/Code/левые проекты/OpenTorchlight/build-decomp/all-functions-20261018/skills/ui-rest-20261019/gameclient-load-menu-signal.log",O_WRONLY|O_APPEND|O_CREAT,0600);if(fd>=0){ucontext_t*c=static_cast<ucontext_t*>(raw);char text[200];int n=std::snprintf(text,sizeof(text),"signal%d phase%u rip%llx address%p\n",sig,phase,(unsigned long long)c->uc_mcontext.gregs[REG_RIP],info->si_addr);write(fd,text,n);void*frames[30];int count=backtrace(frames,30);backtrace_symbols_fd(frames,count,fd);close(fd);}signal(sig,SIG_DFL);raise(sig);}
void signals(){struct sigaction a;std::memset(&a,0,sizeof(a));a.sa_flags=SA_SIGINFO|SA_RESETHAND;a.sa_sigaction=&fault;sigaction(SIGSEGV,&a,NULL);sigaction(SIGABRT,&a,NULL);}
nativegame::Services*native;CGameClient*client;CDungeon*dungeon;CLevelTemplateData*rule,*loaded;CGenericModel*models[8];unsigned nextModel,seed;autotest::Capture*cap;bool recording;
void num(unsigned n){if(recording)cap->add(&n,4);}void fp(float f){if(recording)cap->add(&f,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void wide(const std::wstring&s){num(s.size());if(recording)cap->add(s.data(),s.size()*sizeof(wchar_t));}void narrow(const std::string&s){num(s.size());if(recording)cap->add(s.data(),s.size());}
unsigned id(CGenericModel*p){if(!p)return 0;for(unsigned i=0;i<8;++i)if(p==models[i])return i+1;return 99;}
void choose(CGameClient*p,std::wstring name){num(101);num(p==client);wide(name);p->m_currentDungeon=dungeon;}
void reset(CGameClient*p,int value){num(103);num(p==client);num(value);p->m_gameSeed=1234+value;}
CLevelTemplateData*getTemplate(CDungeon*p,CGameClient*c,unsigned depth){num(107);num(p==dungeon);num(c==client);num(depth);return seed&1?rule:NULL;}
void load(CLevel*p,std::wstring name,bool flag,ELevelEntryType entry,std::vector<std::wstring>*extra,std::wstring waypoint){num(109);num(p==client->m_level);wide(name);num(flag);num(entry);num(extra==NULL);wide(waypoint);num(p->m_levelSeed);num(p->m_pGameClient==client);num(p->m_resourceManager==client->m_gameResources);wide(p->m_sDungeonName);client->m_gameResources->m_pLevel=p;p->m_pLevelTemplateData=seed&2?loaded:NULL;p->m_auxiliaryPosition188=Ogre::Vector3(seed*.5f,9,-7);p->m_auxiliaryPosition194=Ogre::Vector3(-3,2,seed*.125f);}
void activate(CLevel*p){num(113);num(p==client->m_level);fp(p->m_updateRange);num(client->m_soundManager->m_bUnknown6A9);}
void projector(CLevel*p,Ogre::Frustum*a,Ogre::Frustum*b,CGenericModel*c,CGenericModel*d,const std::string&one,const std::string&two){num(127);num(p==client->m_level);num(a==client->m_cameraControl->m_pUnknown30);num(b==client->m_cameraControl->m_pUnknown28);num(id(c));num(id(d));narrow(one);narrow(two);}
void lighting(CGameClient*p){num(131);num(p==client);}
void cursor(CGameUI*p,ECursorState state){num(137);num(p==client->m_pGameUI);num(state);}
void stop(CSoundManager*p){num(139);num(p==client->m_soundManager);}
float play(CSoundManager*p,std::wstring&name,bool loop){num(149);num(p==client->m_soundManager);wide(name);num(loop);return 12.5f;}
CGenericModel*create(CResourceManager*r,Ogre::SceneManager*s,const wchar_t*name,const wchar_t*group,bool a,bool b,bool c){num(151);num(r==client->m_gameResources);num(s==NULL);wide(name);wide(group);num(a);num(b);num(c);if(nextModel>=8)std::abort();return models[nextModel++];}
void layout(CLayout*p,const std::wstring&name,bool a,CTimerStatics*t,bool b,bool c,unsigned n){num(157);num(p==client->m_menuLayout);wide(name);num(a);num(t==NULL);num(b);num(c);num(n);num(p->m_Unknown1B8);}
void start(CLayout*p){num(163);num(p==client->m_menuLayout);num(p->m_bActivated);}
void inited(CLevel*p,bool flag){num(167);num(p==client->m_level);num(flag);}
struct Case{unsigned seed;};
void side(void*raw,autotest::Capture&out,bool ours){seed=static_cast<Case*>(raw)->seed;signals();phase=1;recording=false;cap=&out;
 editorlevel::ensurePreloader(native->master);menugui::OwnedClient owner(*native->settings,native->master,*native->master->m_pSoundManager);client=owner.client;dungeon=owner.dungeons->m_lDungeons[0];gameclient_fixture::SteamOwner steam;
 phase=2;CLevelTemplateData ruleData(NULL);rule=&ruleData;rule->m_mainMenuRules=seed&4?L"menu/правила.dat":L"";loaded=new CLevelTemplateData(NULL);loaded->m_state761=true;loaded->m_skybox=seed&4?L"menu/sky.mesh":L"";loaded->m_water=seed&8?L"menu/water.mesh":L"";loaded->m_postWater=seed&16?L"menu/post.mesh":L"";loaded->m_midWater=seed&32?L"menu/mid.mesh":L"";loaded->m_levelParticle=seed&64?L"menu/particles.layout":L"";TSafePointer<CLevelTemplateData>dataWeak;dataWeak.setObject(loaded);
 phase=3;Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().create("load-menu-material","General");material->removeAllTechniques();Ogre::MeshPtr mesh=Ogre::MeshManager::getSingleton().createManual("load-menu-mesh","General");mesh->_setBounds(Ogre::AxisAlignedBox(-1,-1,-1,1,1,1),false);mesh->createSubMesh()->setMaterialName(material->getName());
 phase=4;TSafePointer<CGenericModel>modelWeak[8];for(unsigned i=0;i<8;++i){models[i]=new CGenericModel(NULL,owner.scenes[0],static_cast<OGRE_UTILITIES::EPRIMITIVES>(0));models[i]->setResourceManager(client->m_gameResources);char name[50];std::sprintf(name,"load-menu-model-%u",i);models[i]->m_pEntity=owner.scenes[0]->createEntity(name,mesh->getName());models[i]->m_pEntity->setRenderQueueGroup(17+i);models[i]->setVisible(false);models[i]->setPosition(Ogre::Vector3(3+i,7,11));modelWeak[i].setObject(models[i]);}
 CGenericModel**slots[]={&client->m_menuModel0,&client->m_menuModel1,&client->m_menuModel2,&client->m_menuModel3};for(unsigned i=0;i<4;++i)if((seed>>(i+3))&1)*slots[i]=models[i];nextModel=4;
 TSafePointer<CLayout>oldLayout;if(seed&128){client->m_menuLayout=new CLayout(client->m_gameResources,static_cast<ELAYOUT_TYPES>(0));oldLayout.setObject(client->m_menuLayout);}
 phase=5;gameclient_fixture::UiOwner ui(*native->settings,*client,owner.camera->m_cameras[0],owner.scenes[0],owner.scenes[1],owner.scenes[2],owner.resources);if(seed%3)client->m_pGameUI=ui.ui;
 Ogre::Camera*camera=client->m_cameraControl->m_pUnknown10;if(seed%5==0)client->m_cameraControl->m_pUnknown10=NULL;client->m_gameSeed=-100-int(seed);client->m_deferredFrames=-7;client->m_soundManager->m_bUnknown6A9=false;client->m_projectorTexture="menu/projector";client->m_projectorFalloffTexture="menu/falloff";
 detour::Set hooks;TL_REDIRECT(hooks,gcloadDungeon,&choose);TL_REDIRECT(hooks,gcloadSeed,&reset);TL_REDIRECT(hooks,gcloadTemplate,&getTemplate);TL_REDIRECT(hooks,gcloadRoom,&load);TL_REDIRECT(hooks,gcloadActivate,&activate);TL_REDIRECT(hooks,gcloadProjector,&projector);TL_REDIRECT(hooks,gcloadLighting,&lighting);TL_REDIRECT(hooks,gcloadCursor,&cursor);TL_REDIRECT(hooks,gcloadStop,&stop);TL_REDIRECT(hooks,gcloadPlay,&play);TL_REDIRECT(hooks,gcloadModel,&create);TL_REDIRECT(hooks,gcloadLayout,&layout);TL_REDIRECT(hooks,gcloadStart,&start);TL_REDIRECT(hooks,gcloadInited,&inited);if(hooks.failed())_exit(64);
 phase=6;recording=true;typedef void(*F)(CGameClient*,int,int,std::wstring);F fn=ours?gcloadNew:gcloadOld;if(autotest::beginInvocation(out,fn)){fn(client,int(seed)-91,int(seed%11)-3,seed&1?L"MENU_ONE":L"MENU_TWO");out.callCompleted=1;}
 phase=7;num(client->m_deferredFrames);num(client->m_gameSeed);num(client->m_soundManager->m_bUnknown6A9);num(oldLayout.getObject()==NULL);num(client->m_menuLayout!=NULL);if(client->m_menuLayout)num(client->m_menuLayout->m_bActivated);num(nextModel);for(unsigned i=0;i<4;++i){num(id(*slots[i]));if(*slots[i]){num((*slots[i])->getEntity()->getRenderQueueGroup());num((*slots[i])->getVisible());vec((*slots[i])->getPosition(false));}}if(client->m_cameraControl->m_pUnknown10){vec(camera->getPosition());vec(camera->getDirection());}
 phase=8;recording=false;client->m_pGameUI=NULL;client->m_cameraControl->m_pUnknown10=camera;
 // Unassigned pool models borrow the still-live actual client ResourceManager.
 for(unsigned i=0;i<8;++i){bool owned=false;for(unsigned k=0;k<4;++k)if(*slots[k]==models[i])owned=true;if(!owned)delete modelWeak[i].getObject();}
 gameClientUiOwnerDtor(ui.ui);Ogre::NedAllocImpl::deallocBytes(ui.ui);ui.ui=NULL;
 mgClientDtor(client);Ogre::NedAllocImpl::deallocBytes(client);owner.client=NULL;
 phase=9;for(unsigned i=0;i<8;++i)if(modelWeak[i].getObject())std::abort();if(dataWeak.getObject())delete dataWeak.getObject();
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){signals();tlheadless::Environment environment;environment.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;nativeeditor::Controls editor(services);native=&services;menugui::Audio audio(native->master);void*old=NULL;std::memcpy(&old,reinterpret_cast<void*>(0x1426490),sizeof(old));if(!old)new(reinterpret_cast<void*>(0x1426490))std::wstring;autotest::Stats stats={0,0,0};autotest::Coverage coverage("gameclient_load_menu",(uintptr_t)gcloadOld);int failures=0;for(unsigned i=0;i<256;++i){Case c={i};bool ok=autotest::compareCase(before,after,&c,stats,host,"gameclient_load_menu",i,&coverage);TL_CHECK(failures,ok);if(!ok)break;}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=256);}
}
TL_TEST(gameclient_load_menu){if(!std::setlocale(LC_CTYPE,"C.UTF-8"))return 1;return systems_fixture::isolated(&worker,host);}
