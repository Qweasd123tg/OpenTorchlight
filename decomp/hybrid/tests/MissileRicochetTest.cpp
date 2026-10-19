#include "AutoTest.h"
#include <Ogre.h>
#include <limits>
#define private public
#define protected public
#include "Missile.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"
#include "tests/SmallMassCompare.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(Ogre::Vector3,rcOld,(CMissile*,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&),"_ZN8CMissile15ricochetMissileERKN4Ogre7Vector3ES3_S3_S3_")
extern "C" Ogre::Vector3 rcNew(CMissile*,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&) __asm__("_ZN8CMissile15ricochetMissileERKN4Ogre7Vector3ES3_S3_S3_");
TL_ORIGINAL(void,rcCtor,(CMissile*,CResourceManager*),"_ZN8CMissileC1EP16CResourceManager")
TL_ORIGINAL(void,rcDtor,(CMissile*),"_ZN8CMissileD1Ev")
TL_FUNCTION(rcStart,"_ZN9CParticle5StartEv")
namespace {
nativegame::Services*services;autotest::Capture*output;bool armed;CParticle*particle;
void number(unsigned n){if(armed)output->add(&n,4);}
void vector(const Ogre::Vector3&v){if(armed)output->add(&v,sizeof v);}
void matrix(const Ogre::Matrix4&m){if(armed)output->add(&m,sizeof m);}
struct Particle:CParticle{explicit Particle(CResourceManager*r):CParticle(NULL,L"fixture",r){}virtual void setOrientation(Ogre::Vector3&forward,Ogre::Vector3&up){number(1);vector(forward);vector(up);CParticle::setOrientation(forward,up);vector(forward);vector(up);}};
void start(CParticle*p){number(2);number(p==particle);vector(p->getPosition(true));matrix(p->m_mOrientation);}
float value(unsigned n){const float v[]={0.0f,-0.0f,1e-10f,1.0f,-2.0f,3.25f,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};return v[n%8];}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){output=&out;armed=false;unsigned n=c.index;CResourceManager resources(services->scene);CMissile*m=static_cast<CMissile*>(Ogre::NedAllocImpl::allocBytes(sizeof(CMissile),0,0,0));rcCtor(m,&resources);m->setPosition(Ogre::Vector3(value(n),value(n/2),value(n/3)));m->m_fUnknown16C=value(n/5);m->m_fRadiusOfMissile=value(n/7);m->m_iUnknown17C=n%17;m->m_resetVector148=Ogre::Vector3(value(n/2+1),value(n/3+2),value(n/5+3));particle=(n&1)?new Particle(&resources):NULL;m->m_particles[2]=particle;
 Ogre::Vector3 from(11,12,13),to(-1,-2,-3),position(value(n/3),value(n/7),value(n/11)),normal(value(n/13),value(n/17),value(n/19));const Ogre::Vector3*positionArg=(n/64%4==1||n/64%4==3)?&m->m_resetVector148:&position;const Ogre::Vector3*normalArg=n/64%4>=2?&m->m_resetVector148:&normal;
 detour::Set hooks;TL_REDIRECT(hooks,rcStart,&start);if(hooks.failed())std::abort();typedef Ogre::Vector3(*Fn)(CMissile*,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&);Fn fn=ours?rcNew:rcOld;armed=true;if(!autotest::beginInvocation(out,fn))return;Ogre::Vector3 result=fn(m,from,to,*positionArg,*normalArg);out.callCompleted=1;vector(result);vector(m->m_resetVector148);number(m->m_iUnknown17C);vector(m->getPosition(true));if(particle){vector(particle->getPosition(true));matrix(particle->m_mOrientation);}vector(position);vector(normal);armed=false;hooks.restore();rcDtor(m);Ogre::NedAllocImpl::deallocBytes(m);particle=NULL;
}
int worker(const tlhybrid_host*host){nativegame::Services native;if(!native.ready())return 1;services=&native;Ogre::SceneManager*old=native.master->m_pSceneManager;native.master->m_pSceneManager=native.scene;for(unsigned i=0;i<2;++i){void*p=NULL;void*a=reinterpret_cast<void*>(0x14a4320+8*i);std::memcpy(&p,a,8);if(!p){if(i)new(a)std::wstring;else new(a)std::string;}}int result=smallmass::run(host,0,"missile_ricochet_native",0xd01580,&side,512);native.master->m_pSceneManager=old;return result;}
}
TL_TEST(missile_ricochet_native){return systems_fixture::isolated(&worker,host);}
