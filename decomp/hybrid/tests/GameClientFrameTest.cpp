#include "tests/FinishLevelFixture.h"
#include "GameClientUiOwner.h"
#include "GameClientCpuTextures.h"
#include "tests/SystemsFixtureWorker.h"
#include "GameClientData.h"
TL_ORIGINAL(void,gcfOld,(CGameClient*,float,Ogre::RenderWindow*,float,bool),"_ZN11CGameClient6updateEfPN4Ogre12RenderWindowEfb")
extern "C" void gcfNew(CGameClient*,float,Ogre::RenderWindow*,float,bool) __asm__("_ZN11CGameClient6updateEfPN4Ogre12RenderWindowEfb");
TL_FUNCTION(gcfModal,"_ZN7CGameUI15modalDialogOpenEv")
TL_FUNCTION(gcfCinematic,"_ZN7CGameUI18getUIIsInCinematicEv")
TL_FUNCTION(gcfRight,"_ZN7CGameUI12rightCoveredEv")
TL_FUNCTION(gcfLeft,"_ZN7CGameUI11leftCoveredEv")
TL_FUNCTION(gcfClose,"_ZN7CGameUI8closeAllEv")
TL_FUNCTION(gcfRequest,"_ZN7CGameUI21clearGameStateRequestEv")
TL_FUNCTION(gcfNPC,"_ZN6CLevel14updateNPCIconsEv")
TL_FUNCTION(gcfKill,"_ZN11CGameClient8killPetsEv")
TL_FUNCTION(gcfSave,"_ZN11CGameClient13saveCharacterEbb")
TL_FUNCTION(gcfState,"_ZN11CGameClient12setGameStateE10EGameState5EMenu")
TL_FUNCTION(gcfMenu,"_ZN11CGameClient10updateMenuEfPN4Ogre12RenderWindowEfb")
TL_FUNCTION(gcfGame,"_ZN11CGameClient12updateIngameEfPN4Ogre12RenderWindowEfb")
TL_FUNCTION(gcfRelease,"_ZN13CSoundManager19releaseUnusedSoundsEv")
TL_FUNCTION(gcfUnused,"_ZN22CMasterResourceManager12removeUnusedEv")
namespace {
CGameClient*client;CGameUI*ui;CLevel*level;unsigned seed,phase;autotest::Capture*cap;
void num(unsigned n){cap->add(&n,4);}void fp(float f){cap->add(&f,4);}
bool modal(CGameUI*p){num(101);num(p==ui);return seed/9%4==1;}
bool cinematic(CGameUI*p){num(103);num(p==ui);return ((seed+phase)/3%2)!=0;}
bool right(CGameUI*p){num(107);num(p==ui);return seed/7%4==1;}
bool left(CGameUI*p){num(109);num(p==ui);return seed/5%4==1;}
void close(CGameUI*p){num(113);num(p==ui);}
void request(CGameUI*p){num(127);num(p==ui);p->m_requestedGameState=static_cast<EGameState>(6);}
void npc(CLevel*p){num(131);num(p==level);}
void kill(CGameClient*p){num(137);num(p==client);}
void save(CGameClient*p,bool a,bool b){num(139);num(p==client);num(a);num(b);}
void state(CGameClient*p,EGameState s,EMenu menu){num(149);num(p==client);num(s);num(menu);p->m_gameState=s;}
void frame(CGameClient*p,float elapsed,Ogre::RenderWindow*window,float other,bool enabled,unsigned tag){num(tag);num(p==client);fp(elapsed);num(window==NULL);fp(other);num(enabled);}
void menu(CGameClient*p,float e,Ogre::RenderWindow*w,float o,bool n){frame(p,e,w,o,n,151);}
void game(CGameClient*p,float e,Ogre::RenderWindow*w,float o,bool n){frame(p,e,w,o,n,157);}
void release(CSoundManager*p){num(163);num(p==client->m_soundManager);}
void unused(CMasterResourceManager*p){num(167);num(p==client->m_masterResources);}
struct Case{unsigned seed;};
void side(void*raw,autotest::Capture&out,bool ours){seed=static_cast<Case*>(raw)->seed;cap=&out;phase=0;client->m_pGameUI=seed%11?ui:NULL;client->m_level=seed%13?level:NULL;client->m_gameState=static_cast<EGameState>(seed%8);client->m_blockInputFrames=int(seed/3%5)-2;client->m_deferredFrames=int(seed/5%5)-1;client->m_transitionTime=(int(seed%7)-3)*.0625f;client->m_leftHeld=seed&1;client->m_rightHeld=seed&2;client->m_inputConsumed=seed&4;ui->m_requestedGameState=static_cast<EGameState>(seed/8%7);ui->m_requestedMenu=static_cast<EMenu>(seed/17%9);GForceMenuExit=seed&1;
 detour::Set hooks;TL_REDIRECT(hooks,gcfModal,&modal);TL_REDIRECT(hooks,gcfCinematic,&cinematic);TL_REDIRECT(hooks,gcfRight,&right);TL_REDIRECT(hooks,gcfLeft,&left);TL_REDIRECT(hooks,gcfClose,&close);TL_REDIRECT(hooks,gcfRequest,&request);TL_REDIRECT(hooks,gcfNPC,&npc);TL_REDIRECT(hooks,gcfKill,&kill);TL_REDIRECT(hooks,gcfSave,&save);TL_REDIRECT(hooks,gcfState,&state);TL_REDIRECT(hooks,gcfMenu,&menu);TL_REDIRECT(hooks,gcfGame,&game);TL_REDIRECT(hooks,gcfRelease,&release);TL_REDIRECT(hooks,gcfUnused,&unused);if(hooks.failed())_exit(64);
 typedef void(*F)(CGameClient*,float,Ogre::RenderWindow*,float,bool);F fn=ours?gcfNew:gcfOld;if(autotest::beginInvocation(out,fn)){for(phase=0;phase<3;++phase){fn(client,(int(seed%9)-3)*.03125f,NULL,(int(seed/9%9)-3)*.0625f,(seed&8)!=0);num(client->m_gameState);num(client->m_blockInputFrames);num(client->m_deferredFrames);fp(client->m_transitionTime);num(client->m_gameResources->m_bFlag0);num(client->m_leftHeld);num(client->m_rightHeld);num(client->m_inputConsumed);num(ui->m_requestedGameState);num(GForceMenuExit);}out.callCompleted=1;}
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){tlheadless::Environment environment;environment.loadGameSkin();nativegame::Services native;if(!native.ready())return 1;menugui::Audio audio(native.master);menugui::Client owner(*native.settings,native.master,*native.master->m_pSoundManager);client=owner.client;gameclient_fixture::UiOwner uiOwner(*native.settings,*client,owner.camera->m_cameras[0],owner.scenes[0],owner.scenes[1],owner.scenes[2],owner.resources);ui=uiOwner.ui;finishlevel::Fixture world;level=&world.level;gameclient_cpu::Textures textures;autotest::Stats stats={0,0,0};autotest::Coverage coverage("gameclient_frame",(uintptr_t)gcfOld);int failures=0;for(unsigned i=0;i<384;++i){Case c={i};bool ok=autotest::compareCase(before,after,&c,stats,host,"gameclient_frame",i,&coverage);TL_CHECK(failures,ok);if(!ok)break;}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=384);}
}
TL_TEST(gameclient_frame){return systems_fixture::isolated(&worker,host);}
