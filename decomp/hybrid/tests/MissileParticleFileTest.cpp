#include "AutoTest.h"
#include <Ogre.h>
#include "Missile.h"
#include "ParticlePreloader.h"
#include "MasterResourceManager.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/SmallMassCompare.h"
TL_ORIGINAL(void,mfOld,(CMissile*,EMISSILE_PARTICLES,std::wstring),"_ZN8CMissile15setParticleFileE18EMISSILE_PARTICLESSbIwSt11char_traitsIwESaIwEE")
extern "C" void mfNew(CMissile*,EMISSILE_PARTICLES,std::wstring) __asm__("_ZN8CMissile15setParticleFileE18EMISSILE_PARTICLESSbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(mfLoad,"_ZN18CParticlePreloader12LoadParticleESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(mfGet,"_ZN18CParticlePreloader11GetParticleEP16CResourceManagerPKw")
TL_FUNCTION(mfStop,"_ZN9CParticle4StopEb")
namespace {
nativegame::Services*services;autotest::Capture*output;CMissile*missile;CParticlePreloader*preloaders[2];CResourceManager*managers[2];unsigned seed,slot;bool armed;
void number(unsigned n){if(armed)output->add(&n,4);}
void text(const std::wstring&s){number(s.size());if(armed)output->add(s.data(),s.size()*sizeof(wchar_t));}
struct Particle:CParticle{unsigned id;Particle(CResourceManager*r,unsigned n):CParticle(NULL,L"fixture",r),id(n){}virtual ~Particle(){number(7);number(id);number(missile->m_particles[slot]==this);text(missile->m_particleFiles[slot]);}};
void load(CParticlePreloader*p,std::wstring file){number(1);number(p==preloaders[0]?0:p==preloaders[1]?1:99);text(file);text(missile->m_particleFiles[slot]);number(missile->m_particles[slot]==NULL);if(seed/192&2){CMasterResourceManager::getSingleton()->m_pParticlePreloader=preloaders[1];missile->setResourceManager(managers[1]);}}
CParticle*get(CParticlePreloader*p,CResourceManager*r,const wchar_t*file){number(2);number(p==preloaders[0]?0:p==preloaders[1]?1:99);number(r==managers[0]?0:r==managers[1]?1:99);text(file);if(seed/192&1)return NULL;return new Particle(r,2);}
void stop(CParticle*p,bool immediate){number(3);number(static_cast<Particle*>(p)->id);number(p==missile->m_particles[slot]);number(immediate);}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){output=&out;armed=false;seed=c.index;slot=seed%4;CResourceManager first(services->scene),second(services->scene);managers[0]=&first;managers[1]=&second;CParticlePreloader preloader0(NULL),preloader1(NULL);preloaders[0]=&preloader0;preloaders[1]=&preloader1;CParticlePreloader*old=services->master->m_pParticlePreloader;services->master->m_pParticlePreloader=&preloader0;missile=new CMissile(&first);
 const wchar_t*prior[]={L"",L"MEDIA\\PARTICLE",L"UNICODE \x422\x415\x421\x422",L"OTHER"};const wchar_t*requested[]={L"",L"media\\particle",L"MEDIA\\PARTICLE",L"new",L"unicode \x442\x435\x441\x442",L"other"};for(unsigned i=0;i<4;++i)missile->m_particleFiles[i]=prior[(seed/4+i)%4];if(seed/96&1)missile->m_particles[slot]=new Particle(&first,1);
 detour::Set hooks;TL_REDIRECT(hooks,mfLoad,&load);TL_REDIRECT(hooks,mfGet,&get);TL_REDIRECT(hooks,mfStop,&stop);if(hooks.failed())std::abort();typedef void(*Fn)(CMissile*,EMISSILE_PARTICLES,std::wstring);Fn fn=ours?mfNew:mfOld;armed=true;if(!autotest::beginInvocation(out,fn))return;
 for(unsigned i=0;i<2;++i){fn(missile,static_cast<EMISSILE_PARTICLES>(slot),requested[seed/16%6]);for(unsigned j=0;j<4;++j){text(missile->m_particleFiles[j]);number(missile->m_particles[j]?static_cast<Particle*>(missile->m_particles[j])->id:0);}}
 out.callCompleted=1;armed=false;hooks.restore();services->master->m_pParticlePreloader=old;delete missile;
}
int worker(const tlhybrid_host*host){nativegame::Services native;if(!native.ready())return 1;services=&native;Ogre::SceneManager*old=native.master->m_pSceneManager;native.master->m_pSceneManager=native.scene;for(unsigned i=0;i<2;++i){void*p=NULL;void*a=reinterpret_cast<void*>(0x14a4320+8*i);std::memcpy(&p,a,8);if(!p){if(i)new(a)std::wstring;else new(a)std::string;}}int result=smallmass::run(host,0,"missile_particle_file_native",0xd032b0,&side,768);native.master->m_pSceneManager=old;return result;}
}
TL_TEST(missile_particle_file_native){return systems_fixture::isolated(&worker,host);}
