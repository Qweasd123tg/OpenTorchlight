#include "AutoTest.h"
#include <Ogre.h>
#include <limits>
#define private public
#define protected public
#include "Missile.h"
#include "Particle.h"
#include "Path.h"
#include "iMissile.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/SmallMassCompare.h"
#define DECL(R,N,A,S) TL_ORIGINAL(R,mrOld##N,A,S) extern "C" R mrNew##N A __asm__(S);
DECL(void,Reset,(CMissile*),"_ZN8CMissile12resetMissileEv")
DECL(void,Arch,(CMissile*,float),"_ZN8CMissile18addArchFromMissileEf")
DECL(bool,Death,(CMissile*,float),"_ZN8CMissile20handleDeathOfMissileEf")
DECL(void,Kill,(CMissile*),"_ZN8CMissile11killMissileEv")
#undef DECL
TL_FUNCTION(mrSpline,"_ZN5CPath27GetSplinePositionAtDistanceEf")
TL_FUNCTION(mrStop,"_ZN9CParticle4StopEb")
TL_FUNCTION(mrCount,"_ZN9CParticle28getNumberOfParticlesUpdatingEb")
TL_FUNCTION(mrStart,"_ZN9CParticle5StartEv")
namespace {
nativegame::Services*services;autotest::Capture*output;unsigned seed,stops;
CMissile*missile;CPath*path;CParticle*particles[4];bool armed;
void number(unsigned n){if(armed)output->add(&n,4);}
void scalar(float f){if(armed)output->add(&f,4);}
void vector(const Ogre::Vector3&v){scalar(v.x);scalar(v.y);scalar(v.z);}
unsigned identity(const CParticle*p){for(unsigned i=0;i<4;++i)if(p==particles[i])return i+1;return p?99:0;}
Ogre::Vector3 spline(CPath*p,float distance){number(1);number(p==path);scalar(distance);return Ogre::Vector3(distance*.25f,distance*.5f+2.0f,-distance);}
void stop(CParticle*p,bool immediate){number(2);number(identity(p));number(immediate);++stops;}
int count(CParticle*p,bool updating){number(3);number(identity(p));number(updating);return seed%5==identity(p)?int(seed%3):0;}
void start(CParticle*p){number(4);number(identity(p));vector(p->getPosition(true));}
struct Particle:CParticle {
 explicit Particle(CResourceManager*r):CParticle(NULL,L"fixture",r){}
 virtual void setVisible(bool visible){number(5);number(identity(this));number(visible);CParticle::setVisible(visible);}
};
struct Listener:iMissile {
 unsigned id;bool appended;Listener*next;
 Listener(unsigned n):id(n),appended(false),next(NULL){}
 virtual void missileBeingFired(CMissile*){}
 virtual void missileDieing(CMissile*p){number(6);number(id);number(p==missile);number(p->m_bUnknown184);scalar(p->m_fUnknown1B4);if(next&&!appended){appended=true;p->m_Listeners.add(next);}}
 virtual bool missileApplyingEffects(CMissile*,CCharacter*,const Ogre::Vector3*,float,float){return false;}
 virtual bool getCharacterCanBeHarmedByMissile(CMissile*,CCharacter*){return false;}
 virtual CPositionableObject*missileValidateTargetBeforeLaunch(CMissile*,CPositionableObject*p,Ogre::Vector3&){return p;}
};
float value(unsigned n){const float values[]={-2.0f,-0.0f,0.0f,.25f,.999f,1.0f,1.001f,2.5f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};return values[n%10];}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;armed=false;seed=c.index;stops=0;
 CResourceManager resources(services->scene);missile=new CMissile(&resources);
 missile->setPosition(Ogre::Vector3(float(seed%7)-3.0f,7.0f,-float(seed%5)));
 missile->m_bUnknown185=seed&1;missile->m_fUnknown1BC=value(seed);missile->m_iUnknown1C4=seed+11;missile->m_fUnknown1C0=value(seed+1);missile->m_iUnknown17C=seed+17;
 missile->m_resetVector148=Ogre::Vector3(value(seed+2),value(seed+3),value(seed+4));missile->m_resetVector1A0=Ogre::Vector3(11,12,13);
 missile->m_bUnknown184=seed&2;missile->m_fUnknown1B4=value(seed+2);missile->m_fUnknown16C=value(seed+3);
 missile->m_fUnknown198=value(seed/3);missile->m_fMissileArchHeight=value(seed/7);missile->m_fMaxVelocity=value(seed/11);missile->m_fDistanceAllowedToTraveled=value(seed/13);missile->m_fUnknown218=-7;missile->m_bTargetsPosition=seed&4;
 path=new CPath("missile-arch",false,Ogre::Vector3::ZERO);path->AddPoint(Ogre::Vector3(0,0,0),-1,1);path->AddPoint(Ogre::Vector3(5,3,7),-1,1);missile->m_pPath=seed%9?path:NULL;
 for(unsigned i=0;i<4;++i){particles[i]=(seed+i)%3?new Particle(&resources):NULL;missile->m_particles[i]=particles[i];if(particles[i])particles[i]->setPosition(Ogre::Vector3(float(i),float(i+3),float(i+6)));}
 Listener a(1),b(2),d(3);if(seed&8)missile->m_Listeners.add(&a);if(seed&16)missile->m_Listeners.add(&b);if(seed&32)a.next=&d;
 Ogre::SceneNode*nodes[3];for(unsigned i=0;i<3;++i){nodes[i]=services->scene->createSceneNode();if((seed+i)&1)services->scene->getRootSceneNode()->addChild(nodes[i]);if(i<seed%4)missile->m_sceneNodes.add(nodes[i]);}
 detour::Set hooks;TL_REDIRECT(hooks,mrSpline,&spline);TL_REDIRECT(hooks,mrStop,&stop);TL_REDIRECT(hooks,mrCount,&count);TL_REDIRECT(hooks,mrStart,&start);if(hooks.failed())std::abort();
 armed=true;
 if(c.op==0){typedef void(*Fn)(CMissile*);Fn fn=ours?mrNewReset:mrOldReset;if(!autotest::beginInvocation(out,fn))return;fn(missile);out.callCompleted=1;}
 if(c.op==1){typedef void(*Fn)(CMissile*,float);Fn fn=ours?mrNewArch:mrOldArch;if(!autotest::beginInvocation(out,fn))return;fn(missile,value(seed/17));out.callCompleted=1;}
 if(c.op==2){typedef bool(*Fn)(CMissile*,float);Fn fn=ours?mrNewDeath:mrOldDeath;if(!autotest::beginInvocation(out,fn))return;number(fn(missile,value(seed/17)));out.callCompleted=1;}
 if(c.op==3){typedef void(*Fn)(CMissile*);Fn fn=ours?mrNewKill:mrOldKill;if(!autotest::beginInvocation(out,fn))return;fn(missile);out.callCompleted=1;}
 number(missile->m_bUnknown185);scalar(missile->m_fUnknown1BC);number(missile->m_iUnknown1C4);scalar(missile->m_fUnknown1C0);number(missile->m_iUnknown17C);vector(missile->m_resetVector148);vector(missile->m_resetVector1A0);number(missile->m_bUnknown184);scalar(missile->m_fUnknown1B4);scalar(missile->m_fUnknown218);vector(missile->getPosition(true));number(missile->m_Listeners.size());number(missile->m_Listeners.m_nCapacity);number(stops);
 for(unsigned i=0;i<4;++i){number(particles[i]!=NULL);if(particles[i]){number(particles[i]->m_bVisible);vector(particles[i]->getPosition(true));}}
 for(unsigned i=0;i<3;++i)number(nodes[i]->getParentSceneNode()!=NULL);
 armed=false;hooks.restore();missile->m_Listeners.clear();missile->m_sceneNodes.clear();missile->m_pPath=NULL;for(unsigned i=0;i<4;++i){missile->m_particles[i]=NULL;delete particles[i];particles[i]=NULL;}
 delete path;delete missile;for(unsigned i=0;i<3;++i)services->scene->destroySceneNode(nodes[i]);
}
unsigned operation;
int worker(const tlhybrid_host*host){nativegame::Services native;if(!native.ready())return 1;services=&native;Ogre::SceneManager*old=native.master->m_pSceneManager;native.master->m_pSceneManager=native.scene;
 for(unsigned i=0;i<2;++i){void*p=NULL;void*a=reinterpret_cast<void*>(0x14a4320+8*i);std::memcpy(&p,a,8);if(!p){if(i)new(a)std::wstring;else new(a)std::string;}}
 const char*names[]={"missile_reset_native","missile_arch_native","missile_death_native","missile_kill_native"};const unsigned addresses[]={0xcf8f00,0xcf9450,0xcf9840,0xd014a0};int result=smallmass::run(host,operation,names[operation],addresses[operation],&side,192);native.master->m_pSceneManager=old;return result;}
}
TL_TEST(missile_reset_native){operation=0;return systems_fixture::isolated(&worker,host);}
TL_TEST(missile_arch_native){operation=1;return systems_fixture::isolated(&worker,host);}
TL_TEST(missile_death_native){operation=2;return systems_fixture::isolated(&worker,host);}
TL_TEST(missile_kill_native){operation=3;return systems_fixture::isolated(&worker,host);}
