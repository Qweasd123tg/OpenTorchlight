#include "AutoTest.h"
#include "tests/SystemsNativeGame.h"
#include "tests/SystemsNativeMaster.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/NativeMenuClient.h"
TL_ORIGINAL(void,gameCameraOriginal,(CGame*),"_ZN5CGame12createCameraEv")
extern "C" void gameCameraCandidate(CGame*) __asm__("_ZN5CGame12createCameraEv");
namespace {
struct Case{int netbook;bool previous;unsigned seed;};
Ogre::Root*serviceRoot;CSettings*serviceSettings;autotest::Capture*cap;Ogre::SceneManager*scenes[3];Ogre::Camera*cameras[3];
void word(unsigned v){cap->add(&v,4);}void real(float v){cap->add(&v,4);}
Ogre::Camera*cameraBoundary(Ogre::SceneManager*scene,const std::string&name){
 unsigned i=scene==scenes[0]?0:scene==scenes[1]?1:scene==scenes[2]?2:3;word(i);cap->addText(name);if(i==3)_exit(65);return cameras[i];
}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);cap=&out;SystemsNativeGame native(serviceRoot,serviceSettings);CGame*g=native.game;
 serviceSettings->SetInt(KSETTINGS_NETBOOK_MODE,c.netbook);
 // All owning cameras and their scene maps come from the shipped OGRE factory.
 // Its projection conversion boundary is active only during preparation.
 {menugui::ProjectionDuringConstruction projection;
  for(unsigned i=0;i<3;++i){scenes[i]=serviceRoot->createSceneManager(Ogre::ST_GENERIC);char name[40];std::sprintf(name,"prepared-camera-%u",i);cameras[i]=scenes[i]->createCamera(name);cameras[i]->setPosition(Ogre::Vector3(c.seed,-float(c.seed),17));}
 }
 g->m_sceneManager=scenes[0];g->m_uiScene=scenes[1];g->m_backgroundScene=scenes[2];
 if(c.previous)g->m_cameraControl=new CCameraControl(NULL,NULL,NULL,NULL,NULL);
 else g->m_cameraControl=NULL;
 void*lib=dlopen("libOgreMain-1.6.5.so",RTLD_NOW|RTLD_NOLOAD);if(!lib)_exit(66);void*entry=dlsym(lib,"_ZN4Ogre12SceneManager12createCameraERKSs");dlclose(lib);if(!entry)_exit(67);
 void*bridge=mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);if(bridge==MAP_FAILED)_exit(68);unsigned char jump[]={0x48,0xb8,0,0,0,0,0,0,0,0,0xff,0xe0};Ogre::Camera*(*callback)(Ogre::SceneManager*,const std::string&)=&cameraBoundary;std::memcpy(jump+2,&callback,8);std::memcpy(bridge,jump,12);if(mprotect(bridge,4096,PROT_READ|PROT_EXEC))_exit(68);
 detour::Set d;d.redirect(static_cast<char*>(entry),static_cast<char*>(entry),reinterpret_cast<Ogre::Camera*(*)(Ogre::SceneManager*,const std::string&)>(bridge));if(d.failed())_exit(68);
 void(*fn)(CGame*)=ours?gameCameraCandidate:gameCameraOriginal;if(autotest::beginInvocation(out,fn)){fn(g);out.callCompleted=1;}
 d.restore();munmap(bridge,4096);word(g->m_cameraControl!=NULL);
 for(unsigned i=0;i<3;++i){Ogre::Camera*camera=cameras[i];word(g->m_cameraControl->m_cameras[i]==camera);real(camera->getFOVy().valueRadians());real(camera->getNearClipDistance());real(camera->getFarClipDistance());word(camera->getProjectionType());word(camera->getAutoAspectRatio());out.add(&camera->getPosition(),sizeof(Ogre::Vector3));out.add(&camera->getOrientation(),sizeof(Ogre::Quaternion));}
 word(g->m_cameraControl->m_cameras[3]==NULL);word(g->m_cameraControl->m_cameras[4]==NULL);
 delete g->m_cameraControl;g->m_cameraControl=NULL;
 {menugui::CameraNotificationDuringCleanup cleanup;for(unsigned i=0;i<3;++i)serviceRoot->destroySceneManager(scenes[i]);}
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services native;serviceRoot=Ogre::Root::getSingletonPtr();serviceSettings=CMasterResourceManager::getSingleton()->m_pSettings;autotest::Stats stats={0,0,0};int failures=0;unsigned n=0;autotest::Coverage cov("complete_game_camera",reinterpret_cast<uintptr_t>(gameCameraOriginal));const int netbooks[]={-7,0,1,2,17};for(unsigned a=0;a<5;++a)for(unsigned old=0;old<2;++old)for(unsigned seed=0;seed<3;++seed){Case c={netbooks[a],old!=0,seed*13};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_game_camera",n++,&cov);if(!ok&&n<=3){const autotest::Outcome&a=autotest::g_outcomes[0];const autotest::Outcome&b=autotest::g_outcomes[1];host->log("    camera diagnostics A status %d report %u started %u completed %u; B status %d report %u started %u completed %u\n",a.childStatus,a.reportValid,a.capture.callStarted,a.capture.callCompleted,b.childStatus,b.reportValid,b.capture.callStarted,b.capture.callCompleted);}
TL_CHECK(failures,ok);}cov.report(host);return failures+stats.incomplete+(cov.completed!=n);}
}
TL_TEST(complete_game_camera){return systems_fixture::isolated(&worker,host);}
