#include "AutoTest.h"
#include <Ogre.h>
#include <limits>
#define private public
#define protected public
#include "Missile.h"
#include "Path.h"
#include "Settings.h"
#include "SettingsVariables.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"
#include "tests/FinishLevelFixture.h"
#include "tests/SmallMassCompare.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(Ogre::Vector3,mvOld,(CMissile*,float),"_ZN8CMissile24updatePositionByVelocityEf")
extern "C" Ogre::Vector3 mvNew(CMissile*,float) __asm__("_ZN8CMissile24updatePositionByVelocityEf");
TL_FUNCTION(mvAlive,"_ZN10CCharacter5aliveEv")
TL_FUNCTION(mvClosest,"_ZN8CMissile16getClosestTargetERKN4Ogre10QuaternionERKNS0_7Vector3E")
TL_FUNCTION(mvRandom,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(mvSettings,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(mvSphere,"_ZN8CMissile11placeSphereEv")
namespace {
nativegame::Services*services;autotest::Capture*output;bool armed;unsigned seed;CMissile*missile;CCharacter*first;CCharacter*second;
void number(unsigned n){if(armed)output->add(&n,4);}void scalar(float n){if(armed)output->add(&n,4);}void vector(const Ogre::Vector3&v){scalar(v.x);scalar(v.y);scalar(v.z);}
unsigned id(CPositionableObject*p){return !p?0:p==first?1:p==second?2:99;}
float value(unsigned n){const float v[]={0,-0.0f,1e-10f,1,-2,3.25f,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};return v[n%8];}
bool alive(CCharacter*c){number(1);number(id(c));return seed&32;}
CCharacter*closest(CMissile*m,const Ogre::Quaternion&q,const Ogre::Vector3&p){number(2);number(m==missile);scalar(q.w);scalar(q.x);scalar(q.y);scalar(q.z);vector(p);return seed&64?second:NULL;}
float random(float low,float high){number(3);scalar(low);scalar(high);return low*.25f+high*.5f;}
int settings(CDynamicPropertyFile*p,unsigned property){number(4);number(p==services->settings);number(property==KSETTINGS_SHOW_MISSILE_TRAILS);return seed/32%3;}
void sphere(CMissile*m){number(5);number(m==missile);vector(m->getPosition(true));vector(m->m_previousVelocityPosition);++m->m_iUnknown208;}
struct Particle:CParticle{explicit Particle(CResourceManager*r):CParticle(NULL,L"fixture",r){}virtual void setOrientation(Ogre::Vector3&f,Ogre::Vector3&u){number(6);vector(f);vector(u);CParticle::setOrientation(f,u);vector(f);vector(u);}};
struct Missile:CMissile{explicit Missile(CResourceManager*r):CMissile(r){}virtual void setOrientation(Ogre::Vector3&f,Ogre::Vector3&u){number(7);vector(f);vector(u);CPositionableObject::setOrientation(f,u);vector(f);vector(u);}};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){output=&out;armed=false;seed=c.index;CResourceManager resources(services->scene);Missile actual(&resources);missile=&actual;first=new CCharacter(NULL);second=new CCharacter(NULL);first->setPosition(Ogre::Vector3(3,5,7));second->setPosition(Ogre::Vector3(-3,2,4));actual.setPosition(Ogre::Vector3(1,2,3));actual.CPositionableObject::setOrientation(Ogre::Quaternion(Ogre::Degree(float(seed%13)*7),Ogre::Vector3::UNIT_Y));actual.m_resetVector148=Ogre::Vector3(value(seed/3),value(seed/5),value(seed/7));actual.m_fForceAppliedPerSecond=seed%5*.3f;actual.m_fFriction=seed%7*.25f;actual.m_fUnknown258=seed%4==0?-.1f:seed%4==1?0:.1f;actual.m_fTargetHomingValue=seed%6*.2f;actual.m_fUnknown25C=seed%5*.025f;actual.m_fRadiusOfMissile=seed%9*.05f;actual.m_fTurnAcceleration=seed%11*.4f;actual.m_fUnknown274=-1+seed%13*.3f;actual.m_fMaxTurnRate=(seed&128?-1:1)*(seed%5*.5f);actual.m_fUnknown278=seed%7*.02f;actual.m_fRandomizedTurnUpdate=seed%4*.03f;actual.m_fRandomizedTurnAcceleration=seed%8*.3f;actual.m_previousVelocityPosition=Ogre::Vector3(value(seed/11),value(seed/13),value(seed/17));actual.m_iUnknown208=seed%5;actual.m_iUnknown1C4=seed%7*.125f;
 if(seed&1)actual.setTarget(first);if(seed&2)actual.m_collisionUnits.add(first);if(seed&4)actual.m_particles[1]=new Particle(&resources);if(seed&8){actual.m_pPath=new CPath("velocity",false,Ogre::Vector3::ZERO);actual.m_pPath->AddPoint(Ogre::Vector3(0,0,0),1,2);actual.m_pPath->AddPoint(Ogre::Vector3(1,2,0),1,2);actual.m_pPath->AddPoint(Ogre::Vector3(3,0,0),1,2);}if((seed&8)&&(seed&16))actual.m_resetVector148=Ogre::Vector3(seed%7*.25f,seed%5*.125f,seed%3*.5f);actual.m_fMissileArchHeight=seed&16?1:-1;actual.m_fUnknown1BC=seed%9*.15f;actual.m_fUnknown1C0=seed%7*.2f;
 detour::Set hooks;TL_REDIRECT(hooks,mvAlive,&alive);TL_REDIRECT(hooks,mvClosest,&closest);TL_REDIRECT(hooks,mvRandom,&random);TL_REDIRECT(hooks,mvSettings,&settings);TL_REDIRECT(hooks,mvSphere,&sphere);if(hooks.failed())std::abort();const float times[]={0,1.0f/60,1.0f/30,.1f,-.025f,.2f};float elapsed=times[seed/16%6];typedef Ogre::Vector3(*Fn)(CMissile*,float);Fn fn=ours?mvNew:mvOld;armed=true;if(!autotest::beginInvocation(out,fn))return;Ogre::Vector3 result=fn(missile,elapsed);out.callCompleted=1;vector(result);vector(actual.m_resetVector148);scalar(actual.m_fUnknown258);scalar(actual.m_fUnknown25C);scalar(actual.m_fUnknown274);scalar(actual.m_fUnknown278);scalar(actual.m_iUnknown1C4);scalar(actual.m_fUnknown1BC);scalar(actual.m_fUnknown1C0);vector(actual.m_previousVelocityPosition);number(actual.m_iUnknown208);number(id(actual.m_target.getObject()));number(id(actual.m_targetCharacter.getObject()));vector(actual.m_vForward);vector(actual.m_vRight);out.add(&actual.m_mOrientation,sizeof actual.m_mOrientation);if(actual.m_particles[1]){vector(actual.m_particles[1]->getPosition(true));out.add(&actual.m_particles[1]->m_mOrientation,sizeof actual.m_mOrientation);}armed=false;hooks.restore();actual.m_target.setObject(NULL);actual.m_targetCharacter.setObject(NULL);delete first;delete second;
}
int worker(const tlhybrid_host*host){finishlevel::initializeCharacterText();nativegame::Services native;if(!native.ready())return 1;services=&native;Ogre::SceneManager*old=native.master->m_pSceneManager;native.master->m_pSceneManager=native.scene;for(unsigned i=0;i<2;++i){void*p=NULL;void*a=reinterpret_cast<void*>(0x14a4320+8*i);std::memcpy(&p,a,8);if(!p){if(i)new(a)std::wstring;else new(a)std::string;}}int result=smallmass::run(host,0,"missile_velocity_native",0xd02720,&side,1024);native.master->m_pSceneManager=old;return result;}
}
TL_TEST(missile_velocity_native){return systems_fixture::isolated(&worker,host);}
