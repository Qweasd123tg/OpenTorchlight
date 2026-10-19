#include "AutoTest.h"
#include "tests/SystemsNativeGame.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/NativeMenuClient.h"
#include "SubMenu.h"
TL_ORIGINAL(void,preViewportOriginal,(CGame*,const Ogre::RenderTargetViewportEvent&),"_ZN5CGame17preViewportUpdateERKN4Ogre25RenderTargetViewportEventE")
extern "C" void preViewportCandidate(CGame*,const Ogre::RenderTargetViewportEvent&) __asm__("_ZN5CGame17preViewportUpdateERKN4Ogre25RenderTargetViewportEventE");
TL_ORIGINAL(void,viewportUICtor,(CGameUI*,CSettings&,CGameClient&,void*,Ogre::RenderWindow*,Ogre::Camera*,Ogre::SceneManager*,Ogre::SceneManager*,Ogre::SceneManager*,CResourceManager*),"_ZN7CGameUIC1ER9CSettingsR11CGameClientPvPN4Ogre12RenderWindowEPNS5_6CameraEPNS5_12SceneManagerESB_SB_P16CResourceManager")
TL_FUNCTION(viewportLevelVisibility,"_ZN6CLevel29setLightStaticGeometryVisibleEb")
TL_FUNCTION(viewportUICreate,"_ZN7CGameUI6createEv")
namespace {
nativegame::Services*services;autotest::Capture*cap;
void word(unsigned x){cap->add(&x,4);}void real(float x){cap->add(&x,4);}
bool skipUICreate(CGameUI*){return false;}
CLevel*levelReceiver;void observeLevel(CLevel*receiver,bool visible){word(13);word(receiver==levelReceiver);word(visible);}
struct Window:Ogre::RenderWindow{Window(unsigned w,unsigned h){mWidth=w;mHeight=h;}void create(const Ogre::String&,unsigned,unsigned,bool,const Ogre::NameValuePairList*){}void destroy(){}void resize(unsigned,unsigned){}void reposition(int,int){}bool isClosed()const{return false;}void copyContentsToMemory(const Ogre::PixelBox&,Ogre::RenderTarget::FrameBuffer){}bool requiresTextureFlipping()const{return false;}};
struct Panel:CSubMenu{bool right,opened;float edge;Panel(bool r,bool o,float e):right(r),opened(o),edge(e){}CBaseUnit*getOwner(){return NULL;}bool isRight(){word(10);word(right);return right;}bool open(){word(11);word(opened);return opened;}bool openPartial(){return opened;}float screenEdge(){word(12);real(edge);return edge;}void setOwner(CCharacter*){}void setOpen(bool b){opened=b;}void updateLayout(){}void update(float){}};
struct Case{unsigned mode,size;bool different;};
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);cap=&out;CSettings*settings=CMasterResourceManager::getSingleton()->m_pSettings;SystemsNativeGame native(Ogre::Root::getSingletonPtr(),settings);CGame*g=native.game;
 menugui::Audio audio(CMasterResourceManager::getSingleton());menugui::Client client(*settings,CMasterResourceManager::getSingleton(),*CMasterResourceManager::getSingleton()->m_pSoundManager);
 const unsigned widths[]={800,1025,1920},heights[]={600,769,1080};Window window(widths[c.size],heights[c.size]);Ogre::Viewport*viewport=window.addViewport(client.camera->m_cameras[0]);
 settings->SetInt(KSETTINGS_RES_WIDTH,widths[c.size]);settings->SetInt(KSETTINGS_RES_HEIGHT,heights[c.size]);g->m_viewport=viewport;g->m_cameraControl=client.camera;g->m_sceneManager=client.scenes[0];g->m_gameClient=c.mode==0?NULL:client.client;
 Panel left(false,c.mode&1,float(widths[c.size])/4),right(true,c.mode&2,float(widths[c.size])*3/4),extra(false,true,float(widths[c.size])/3);
 CGameUI*ui=NULL;if(c.mode>=2){ui=static_cast<CGameUI*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGameUI),0,0,0));detour::Set creation;TL_REDIRECT(creation,viewportUICreate,&skipUICreate);if(creation.failed())_exit(64);viewportUICtor(ui,*settings,*client.client,NULL,&window,client.camera->m_cameras[0],client.scenes[0],client.scenes[1],client.scenes[2],client.resources);creation.restore();ui->m_submenus.push_back(&left);ui->m_submenus.push_back(&right);if(c.mode&4)ui->m_submenus.push_back(&extra);client.client->m_pGameUI=ui;}
 // Level is an opaque collaborator boundary: target only checks its identity
 // and invokes this one method. No Level constructor/runtime credit.
 unsigned levelIdentity=0;levelReceiver=reinterpret_cast<CLevel*>(&levelIdentity);client.client->m_level=(c.mode&8)?levelReceiver:NULL;detour::Set level;TL_REDIRECT(level,viewportLevelVisibility,&observeLevel);if(level.failed())_exit(65);
 Ogre::RenderTargetViewportEvent event;event.source=c.different?NULL:viewport;
 void(*fn)(CGame*,const Ogre::RenderTargetViewportEvent&)=ours?preViewportCandidate:preViewportOriginal;if(autotest::beginInvocation(out,fn)){fn(g,event);out.callCompleted=1;}
 real(viewport->getLeft());real(viewport->getTop());real(viewport->getWidth());real(viewport->getHeight());word(viewport->getActualWidth());word(viewport->getActualHeight());word(client.scenes[0]->getVisibilityMask());word(client.scenes[2]->getRenderQueue()->getRenderableListener()==static_cast<Ogre::RenderQueue::RenderableListener*>(g));real(client.camera->m_cameras[0]->getAspectRatio());
 level.restore();client.client->m_level=NULL;client.scenes[2]->getRenderQueue()->setRenderableListener(NULL);window.removeAllViewports();client.client->m_pGameUI=NULL;g->m_viewport=NULL;g->m_gameClient=NULL;g->m_cameraControl=NULL;
 // UI's unrelated graphics-create path was bounded; its real owning vectors
 // remain alive until this isolated case exits. No UI lifecycle credit.
 if(ui)ui->m_submenus.clear();
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services native;services=&native;autotest::Stats stats={0,0,0};int failures=0;unsigned n=0;autotest::Coverage cov("complete_game_pre_viewport",reinterpret_cast<uintptr_t>(preViewportOriginal));for(unsigned m=0;m<16;++m)for(unsigned size=0;size<3;++size)for(unsigned different=0;different<2;++different){Case c={m,size,different!=0};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_game_pre_viewport",n++,&cov);TL_CHECK(failures,ok);}cov.report(host);return failures+stats.incomplete+(cov.completed!=n);}
}
TL_TEST(complete_game_pre_viewport){return systems_fixture::isolated(&worker,host);}
