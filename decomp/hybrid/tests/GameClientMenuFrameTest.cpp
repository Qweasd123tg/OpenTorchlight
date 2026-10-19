#include "tests/FinishLevelFixture.h"
#include "GameClientOwnedNative.h"
#include "GameClientUiOwner.h"
#include "GameClientRectangleSetup.h"
#include "tests/NativeEditorControls.h"
#include "tests/SystemsFixtureWorker.h"
#include "ParticleUniverseSystemManager.h"
#include <OgreRectangle2D.h>
TL_ORIGINAL(void,gcmOld,(CGameClient*,float,Ogre::RenderWindow*,float,bool),"_ZN11CGameClient10updateMenuEfPN4Ogre12RenderWindowEfb")
extern "C" void gcmNew(CGameClient*,float,Ogre::RenderWindow*,float,bool) __asm__("_ZN11CGameClient10updateMenuEfPN4Ogre12RenderWindowEfb");
TL_FUNCTION(gcmCinematic,"_ZN7CGameUI19isCinematicMenuOpenEv")
TL_FUNCTION(gcmClose,"_ZN7CGameUI18closeCinematicMenuEv")
TL_FUNCTION(gcmRandom,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(gcmMouse,"_ZN13CMouseManager7captureEv")
TL_FUNCTION(gcmKey,"_ZN11CKeyManager7captureEv")
TL_FUNCTION(gcmLevel,"_ZN6CLevel6updateEPN4Ogre6CameraERKNS0_7Vector3EffP7CPlayer")
TL_FUNCTION(gcmLayout,"_ZN7CLayout6updateEf")
TL_FUNCTION(gcmLayouts,"_ZN6CLevel13updateLayoutsEf")
TL_FUNCTION(gcmAnimation,"_ZN6CLevel24updateCharacterAnimationEffP7CPlayer")
TL_FUNCTION(gcmPaused,"_ZN11CGameClient11getIsPausedEv")
TL_FUNCTION(gcmParticles,"_ZN6CLevel22updateVisibleParticlesEPN4Ogre6CameraERKNS0_7Vector3Eb")
TL_FUNCTION(gcmUI,"_ZN7CGameUI6updateEfP11CGameClientPN4Ogre12RenderWindowE")
TL_FUNCTION(gcmCursor,"_ZN7CGameUI14setCursorStateE12ECursorState")
TL_FUNCTION(gcmCamera,"_ZN14CCameraControl16updateGameCameraEfP16CResourceManagerN4Ogre7Vector3E14ECAMERA_STATES")
TL_FUNCTION(gcmSkills,"_ZN13CSkillManager21globallyDisableSkillsEb")
namespace {
CGameClient*client;CLevel*level;CGameUI*ui;CLayout*layout;CGenericModel*model;unsigned seed,randomCalls;autotest::Capture*cap;
void num(unsigned n){cap->add(&n,4);}void fp(float f){cap->add(&f,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}
bool cinematic(CGameUI*p){num(101);num(p==ui);return seed&1;}
void close(CGameUI*p){num(103);num(p==ui);}
float random(float a,float b){num(107);fp(a);fp(b);const float f[]={0,.5f,1,.75f};return a+(b-a)*f[(seed+randomCalls++)%4];}
void mouse(CMouseManager*p){num(109);num(p==&client->m_mouseManager);}
void key(CKeyManager*p){num(113);num(p==client->getKeyManager());}
void updateLevel(CLevel*p,Ogre::Camera*c,const Ogre::Vector3&position,float a,float b,CPlayer*player){num(127);num(p==level);num(c==client->m_cameraControl->m_pUnknown10);vec(position);fp(a);fp(b);num(player==client->m_pPlayer);p->m_auxiliaryPosition194.y+=.25f;}
void updateLayout(CLayout*p,float elapsed){num(131);num(p==layout);fp(elapsed);}
void layouts(CLevel*p,float elapsed){num(137);num(p==level);fp(elapsed);}
void animation(CLevel*p,float elapsed,float scale,CPlayer*player){num(139);num(p==level);fp(elapsed);fp(scale);num(player==NULL);}
bool paused(CGameClient*p){num(149);num(p==client);return seed&2;}
void particles(CLevel*p,Ogre::Camera*c,const Ogre::Vector3&position,bool flag){num(151);num(p==level);num(c==client->m_cameraControl->m_pUnknown10);vec(position);num(flag);}
void updateUI(CGameUI*p,float elapsed,CGameClient*c,Ogre::RenderWindow*w){num(157);num(p==ui);fp(elapsed);num(c==client);num(w==NULL);p->m_bExitButtonPressed=seed&4;p->m_gap12FA=(seed&8)!=0;}
void cursor(CGameUI*p,ECursorState state){num(163);num(p==ui);num(state);}
void camera(CCameraControl*p,float elapsed,CResourceManager*r,Ogre::Vector3 position,ECAMERA_STATES state){num(167);num(p==client->m_cameraControl);fp(elapsed);num(r==client->m_gameResources);vec(position);num(state);p->m_pUnknown10->setPosition(position+Ogre::Vector3(7,11,-3));}
void skills(bool flag){num(173);num(flag);}
struct Case{unsigned seed;};
void side(void*raw,autotest::Capture&out,bool ours){seed=static_cast<Case*>(raw)->seed;cap=&out;randomCalls=0;client->m_level=level;client->m_pGameUI=seed%5?ui:NULL;client->m_menuLayout=seed&1?layout:NULL;client->m_menuModel0=seed&2?model:NULL;client->m_pPlayer=NULL;client->m_quitRequested=false;client->m_restartRequested=false;
 const float angles[]={-6,-.1f,0,1,6.2831854820251465f-.0625f,6.2831854820251465f,12.75f,18.9f};client->m_lightFlicker=angles[seed/7%8];level->m_auxiliaryPosition194=Ogre::Vector3(float(seed%7)-3,4,float(seed%11)-5);client->m_cameraControl->m_fUnknown4C=seed*.25f;client->m_cameraControl->m_fUnknown50=-3;client->m_cameraControl->m_fUnknown54=-static_cast<float>(seed)*.125f;CMasterResourceManager::getSingleton()->m_pParticleSystemManager->m_paused=true;
 detour::Set hooks;TL_REDIRECT(hooks,gcmCinematic,&cinematic);TL_REDIRECT(hooks,gcmClose,&close);TL_REDIRECT(hooks,gcmRandom,&random);TL_REDIRECT(hooks,gcmMouse,&mouse);TL_REDIRECT(hooks,gcmKey,&key);TL_REDIRECT(hooks,gcmLevel,&updateLevel);TL_REDIRECT(hooks,gcmLayout,&updateLayout);TL_REDIRECT(hooks,gcmLayouts,&layouts);TL_REDIRECT(hooks,gcmAnimation,&animation);TL_REDIRECT(hooks,gcmPaused,&paused);TL_REDIRECT(hooks,gcmParticles,&particles);TL_REDIRECT(hooks,gcmUI,&updateUI);TL_REDIRECT(hooks,gcmCursor,&cursor);TL_REDIRECT(hooks,gcmCamera,&camera);TL_REDIRECT(hooks,gcmSkills,&skills);if(hooks.failed())_exit(64);
 const float elapsed[]={0,.001f,.016f,.017f,.03125f,.3f,.31f,1,-.01f};const float others[]={0,.007f,.1f,-.007f};typedef void(*F)(CGameClient*,float,Ogre::RenderWindow*,float,bool);F fn=ours?gcmNew:gcmOld;if(autotest::beginInvocation(out,fn)){for(unsigned i=0;i<3;++i){fn(client,elapsed[(seed+i)%9],NULL,others[seed/9%4],(seed&16)!=0);fp(client->m_lightFlicker);vec(client->m_audioListenerPosition);num(client->m_quitRequested);num(client->m_restartRequested);num(CMasterResourceManager::getSingleton()->m_pParticleSystemManager->m_paused);vec(CMasterResourceManager::getSingleton()->m_pParticleSystemManager->m_cameraPosition);if(client->m_menuModel0)vec(model->getPosition(false));if(client->m_menuLayout)vec(layout->getPosition(false));const Ogre::AxisAlignedBox&box=client->m_playerLight->getBoundingBox();vec(box.getMinimum());vec(box.getMaximum());}out.callCompleted=1;}
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){tlheadless::Environment environment;environment.loadGameSkin();nativegame::Services native;if(!native.ready())return 1;nativeeditor::Controls editor(native);menugui::Audio audio(native.master);menugui::OwnedClient owner(*native.settings,native.master,*native.master->m_pSoundManager);client=owner.client;gameclient_fixture::UiOwner uiOwner(*native.settings,*client,owner.camera->m_cameras[0],owner.scenes[0],owner.scenes[1],owner.scenes[2],owner.resources);ui=uiOwner.ui;finishlevel::Fixture world;level=&world.level;layout=new CLayout(client->m_gameResources,static_cast<ELAYOUT_TYPES>(0));model=new CGenericModel(NULL,owner.scenes[0],static_cast<OGRE_UTILITIES::EPRIMITIVES>(0));model->setResourceManager(client->m_gameResources);{gameclient_fixture::RectangleDuringConstruction graphics;client->m_playerLight=new Ogre::Rectangle2D(true);}
 autotest::Stats stats={0,0,0};autotest::Coverage coverage("gameclient_menu_frame",(uintptr_t)gcmOld);int failures=0;for(unsigned i=0;i<288;++i){Case c={i};bool ok=autotest::compareCase(before,after,&c,stats,host,"gameclient_menu_frame",i,&coverage);TL_CHECK(failures,ok);if(!ok)break;}coverage.report(host);delete model;delete layout;return failures+stats.incomplete+(coverage.completed!=288);}
}
TL_TEST(gameclient_menu_frame){return systems_fixture::isolated(&worker,host);}
