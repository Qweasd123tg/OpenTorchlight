#include "tests/FinishLevelFixture.h"
#include "MenuGuiFixture.h"
#include "Particle.h"
#include "Settings.h"
#include <limits>
TL_ORIGINAL(void,pvOld,(CLevel*,Ogre::Camera*,const Ogre::Vector3&,bool),"_ZN6CLevel22updateVisibleParticlesEPN4Ogre6CameraERKNS0_7Vector3Eb")
extern "C" void pvNew(CLevel*,Ogre::Camera*,const Ogre::Vector3&,bool) __asm__("_ZN6CLevel22updateVisibleParticlesEPN4Ogre6CameraERKNS0_7Vector3Eb");
TL_FUNCTION(pvInit,"_ZN12CEditorScene9InitSceneEP16CResourceManagerj")
TL_FUNCTION(pvPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(pvWidth,"_ZN7CGameUI14getWindowWidthEv")
TL_FUNCTION(pvHeight,"_ZN7CGameUI15getWindowHeightEv")
TL_FUNCTION(pvAspect,"_ZN7CGameUI14getAspectRatioEv")
TL_FUNCTION(pvScreen,"_ZN7CGameUI17getScreenPositionEPKN4Ogre7Vector3ES3_NS0_7Matrix4E")
TL_FUNCTION(pvForce,"_ZN9CParticle19forceParticleUpdateEf")
namespace {
#include "CharacterEmptyGlobals.h"
autotest::Capture*output;CSettings*settings;Ogre::SceneManager*scene;CGameUI*ui;CLayout*layouts[5];CParticle*particles[5];unsigned seed,step;
void word(unsigned v){output->add(&v,4);}void scalar(float f){output->add(&f,4);}void vec(const Ogre::Vector3&v){output->add(&v,sizeof v);}
unsigned id(const void*p){if(!p)return 0;for(unsigned i=0;i<5;++i){if(p==layouts[i])return i+1;if(p==particles[i])return i+11;}return 99;}
void init(CEditorScene*,CResourceManager*r,unsigned flags){if(r||flags)std::abort();}
struct Layout:CLayout{Layout():CLayout(NULL,static_cast<ELAYOUT_TYPES>(0)){}virtual bool getEnabled(){word(1);word(id(this));word(m_bEnabled);return m_bEnabled;}virtual void setVisible(bool visible){word(2);word(id(this));word(visible);m_bVisible=visible;}};
struct Camera:Ogre::Camera{Ogre::Matrix4 projection;Camera(Ogre::SceneManager*s):Ogre::Camera("particle-visibility-camera",s),projection(Ogre::Matrix4::IDENTITY){}virtual const Ogre::Matrix4&getProjectionMatrix()const{word(3);return projection;}};
Ogre::Vector3 position(CPositionableObject*p,bool absolute){word(4);word(id(p));word(absolute);return p->m_vPosition;}
float width(CGameUI*p){word(5);word(p==ui);float v=seed%3==0?320:seed%3==1?1280:1920;scalar(v);return v;}
float height(CGameUI*p){word(6);word(p==ui);float v=seed%2?1080:600;scalar(v);return v;}
float aspect(CGameUI*p){word(7);word(p==ui);const float v[]={0,.5f,1,1.7777778f,-1};float f=v[seed/3%5];scalar(f);return f;}
Ogre::Vector3 screen(CGameUI*p,const Ogre::Vector3*a,const Ogre::Vector3*b,Ogre::Matrix4 matrix){word(8);word(p==ui);vec(*a);vec(*b);output->add(&matrix,sizeof matrix);unsigned n=(id(layouts[(seed+step)%5])+seed+step)%13;float w=seed%3==0?320:seed%3==1?1280:1920;float nan=std::numeric_limits<float>::quiet_NaN();const float x[]={-w,-.5f*w-.01f,-.5f*w,0,w,1.5f*w,1.5f*w+.01f,nan};const float z[]={-1,0,44.999f,45,45.001f,89.999f,90,90.001f,nan};return Ogre::Vector3(x[(seed+step+n)%8],17,z[(seed/8+step+n)%9]);}
void force(CParticle*p,float delta){word(9);word(id(p));scalar(delta);}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;initEmptyGlobals();for(unsigned i=0;i<2;++i){void*p=NULL;void*a=reinterpret_cast<void*>(0x14a4320+8*i);std::memcpy(&p,a,8);if(!p){if(i)new(a)std::wstring;else new(a)std::string;}}
 CStringTranslate translation(L"");menugui::Fixture menu(*settings,scene);ui=menu.ui;finishlevel::Fixture f;f.resources.m_pSceneManager=menu.nativeClient.scenes[0];CMasterResourceManager::getSingleton()->m_pSceneManager=menu.nativeClient.scenes[0];f.level.m_pGameClient=menu.nativeClient.client;
 CGameUI*oldUI=menu.nativeClient.client->m_pGameUI;menu.nativeClient.client->m_pGameUI=seed%19==0?NULL:ui;CPlayer*oldPlayer=menu.nativeClient.client->m_pPlayer;CPlayer*player=nativegame::createPlayer(&f.resources);menu.nativeClient.client->m_pPlayer=seed%3?player:NULL;
 Camera*camera;{menugui::ProjectionDuringConstruction setup;camera=new Camera(menu.nativeClient.scenes[0]);}
 camera->setPosition(Ogre::Vector3(float(seed%5),float(seed%7),-float(seed%3)));camera->setOrientation(Ogre::Quaternion(Ogre::Radian(float(seed%9)*.125f),Ogre::Vector3::UNIT_Y));camera->projection[0][0]=.25f+float(seed%4);camera->projection[1][2]=float(seed%7)*-.125f;camera->projection[3][2]=.03125f;
 {detour::Set setup;TL_REDIRECT(setup,pvInit,&init);if(setup.failed())std::abort();for(unsigned i=0;i<5;++i)layouts[i]=new Layout;}
 for(unsigned i=0;i<5;++i){particles[i]=(seed+i)%4?new CParticle(NULL,L"fixture",&f.resources):NULL;layouts[i]->m_pParticle=particles[i];layouts[i]->m_bVisible=(seed+i)&1;layouts[i]->m_bEnabled=(seed/2+i)%5!=0;layouts[i]->m_vPosition=Ogre::Vector3(float(int((seed+i)%7)-3)*5,float(i)*100,float(int((seed/3+i)%9)-4)*7);if(particles[i])particles[i]->m_bUnknown127=(seed/5+i)%7==0;}
 for(unsigned i=0;i<seed%8;++i)f.level.m_auxiliaryLayouts.add(layouts[(i+seed/8)%5]);settings->SetInt(KSETTINGS_NETBOOK_MODE,seed%3);
 detour::Set hooks;TL_REDIRECT(hooks,pvPosition,&position);TL_REDIRECT(hooks,pvWidth,&width);TL_REDIRECT(hooks,pvHeight,&height);TL_REDIRECT(hooks,pvAspect,&aspect);TL_REDIRECT(hooks,pvScreen,&screen);TL_REDIRECT(hooks,pvForce,&force);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void(*Fn)(CLevel*,Ogre::Camera*,const Ogre::Vector3&,bool);Fn fn=ours?pvNew:pvOld;if(!autotest::beginInvocation(out,fn))return;
 const float displacements[]={0,.24999f,.25f,.25001f,1,-1};for(step=0;step<6;++step){Ogre::Vector3 p(float(seed%7),float(seed%11),float(seed%13));p[seed%3]+=displacements[step];if(seed%17==0&&step==2)p.x=std::numeric_limits<float>::quiet_NaN();fn(&f.level,camera,p,(seed+step)%4==0);for(unsigned i=0;i<5;++i)word(layouts[i]->m_bVisible);}
 out.callCompleted=1;hooks.restore();for(unsigned i=0;i<5;++i){layouts[i]->m_pParticle=NULL;delete particles[i];delete layouts[i];}f.level.m_auxiliaryLayouts.clear();delete camera;menu.nativeClient.client->m_pPlayer=oldPlayer;menu.nativeClient.client->m_pGameUI=oldUI;f.level.m_pGameClient=NULL;nativegame::destroyPlayer(player);
}
}
TL_TEST(level_visible_particles){tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,0,"level_visible_particles",0x9474f0,&side,256);}
