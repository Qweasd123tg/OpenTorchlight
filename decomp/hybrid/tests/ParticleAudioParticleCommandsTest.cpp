#include <cstring>
#include <stdint.h>
#include <string>
#include <limits>
#include <new>
#include "TArrayList.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,particleOld0,(void*,float),"_ZN9CParticle19forceParticleUpdateEf")
TL_ORIGINAL(void,particleOld1,(void*),"_ZN9CParticle6ResumeEv")
TL_ORIGINAL(void,particleOld2,(void*),"_ZN9CParticle5PauseEv")
TL_ORIGINAL(void,particleOld3,(void*,TArrayList<void*>&),"_ZN9CParticle14getAllEmittersER10TArrayListIPN16ParticleUniverse15ParticleEmitterEE")
extern "C" void particleNew0(void*,float) __asm__("_ZN9CParticle19forceParticleUpdateEf");
extern "C" void particleNew1(void*) __asm__("_ZN9CParticle6ResumeEv");
extern "C" void particleNew2(void*) __asm__("_ZN9CParticle5PauseEv");
extern "C" void particleNew3(void*,TArrayList<void*>&) __asm__("_ZN9CParticle14getAllEmittersER10TArrayListIPN16ParticleUniverse15ParticleEmitterEE");
TL_FUNCTION(particleUpdateTarget,"_ZN16ParticleUniverse14ParticleSystem7_updateEf")
TL_FUNCTION(particleResumeTarget,"_ZN16ParticleUniverse14ParticleSystem6resumeEv")
TL_FUNCTION(particlePauseTarget,"_ZN16ParticleUniverse14ParticleSystem5pauseEv")
TL_FUNCTION(particleNumTechTarget,"_ZNK16ParticleUniverse14ParticleSystem16getNumTechniquesEv")
TL_FUNCTION(particleTechTarget,"_ZNK16ParticleUniverse14ParticleSystem12getTechniqueEm")
TL_FUNCTION(particleNumEmitterTarget,"_ZNK16ParticleUniverse17ParticleTechnique14getNumEmittersEv")
TL_FUNCTION(particleEmitterTarget,"_ZNK16ParticleUniverse17ParticleTechnique10getEmitterEm")
TL_FUNCTION(particleCacheTarget,"_ZN18CParticlePreloader16getParticleCacheERKSbIwSt11char_traitsIwESaIwEE")
namespace {
struct Case{unsigned operation,index;};struct State{autotest::Capture* out;uint64_t systems[3],techniques[3][3],emitters[9],preloader;void* cache;unsigned index,calls;};State* active;
void add(unsigned x){active->out->add(&x,4);}void invalid(){active->out->issue=autotest::Capture::InvalidReport;}
unsigned system(void* p){for(unsigned i=0;i<3;++i)if(p==&active->systems[i])return i;invalid();return 0;}
unsigned technique(void* p){for(unsigned i=0;i<3;++i)for(unsigned j=0;j<3;++j)if(p==&active->techniques[i][j])return i*3+j;invalid();return 0;}
void event(unsigned tag,unsigned id){++active->calls;add(tag);add(id);}
void update(void* p,float elapsed){event(1,system(p));active->out->add(&elapsed,4);if(elapsed!=0.1f)invalid();}
void resume(void* p){event(2,system(p));}void pause(void* p){event(3,system(p));}
unsigned long numTech(void* p){unsigned i=system(p);event(4,i);return (active->index+i)%3;}
void* tech(void* p,unsigned long i){unsigned s=system(p);event(5,s);add(i);if(i>2){invalid();i=0;}return (active->index&16)&&i==1?0:&active->techniques[s][i];}
unsigned long numEmitter(void* p){unsigned i=technique(p);event(6,i);return (active->index+i)%4;}
void* emitter(void* p,unsigned long i){unsigned n=technique(p);event(7,n);add(i);if(i>2){invalid();i=0;}return (active->index&32)&&i==1?0:&active->emitters[(n+i)%9];}
void* cache(void* p,const std::wstring& filename){if(p!=&active->preloader)invalid();event(8,0);active->out->addText(filename);return active->index&8?0:active->cache;}
unsigned emitterID(void* p){if(!p)return 99;for(unsigned i=0;i<9;++i)if(p==&active->emitters[i])return i;invalid();return 98;}
void side(Case& c,bool ours,autotest::Capture& out){
 uint64_t object[0x138/8]={0},cacheObject[0xe8/8]={0};State state;state.out=&out;state.index=c.index;state.calls=0;state.cache=cacheObject;active=&state;
 TArrayList<void*>* systems=new(reinterpret_cast<char*>(cacheObject)+0x10)TArrayList<void*>(2);for(unsigned i=0;i<c.index%4;++i)systems->add(&state.systems[i]);
 void* initial=c.index&4?0:cacheObject;std::memcpy(reinterpret_cast<char*>(object)+0x108,&initial,8);void* loader=&state.preloader;std::memcpy(reinterpret_cast<char*>(object)+0x130,&loader,8);reinterpret_cast<unsigned char*>(object)[0x81]=c.index&1;
 std::wstring* filename=new(reinterpret_cast<char*>(object)+0x110)std::wstring(L"particles/test.particle");TArrayList<void*> result(2);result.add(&state.emitters[8]);
 detour::Set d;TL_REDIRECT(d,particleUpdateTarget,&update);TL_REDIRECT(d,particleResumeTarget,&resume);TL_REDIRECT(d,particlePauseTarget,&pause);TL_REDIRECT(d,particleNumTechTarget,&numTech);TL_REDIRECT(d,particleTechTarget,&tech);TL_REDIRECT(d,particleNumEmitterTarget,&numEmitter);TL_REDIRECT(d,particleEmitterTarget,&emitter);TL_REDIRECT(d,particleCacheTarget,&cache);if(d.failed()){invalid();return;}
 const float times[]={-0.3f,0.0f,0.05f,0.1f,0.11f,0.3f,std::numeric_limits<float>::quiet_NaN(),-0.0f};
 if(c.operation==0){typedef void(*Fn)(void*,float);Fn fn=ours?particleNew0:particleOld0;if(!autotest::beginInvocation(out,fn))return;fn(object,times[(c.index/4)%8]);}
 else if(c.operation==1||c.operation==2){typedef void(*Fn)(void*);Fn fn=c.operation==1?(ours?particleNew1:particleOld1):(ours?particleNew2:particleOld2);if(!autotest::beginInvocation(out,fn))return;fn(object);}
 else{typedef void(*Fn)(void*,TArrayList<void*>&);Fn fn=ours?particleNew3:particleOld3;if(!autotest::beginInvocation(out,fn))return;fn(object,result);}
 out.callCompleted=1;add(state.calls);add(result.size());for(unsigned i=0;i<result.size();++i)add(emitterID(result[i]));void* finalCache;std::memcpy(&finalCache,reinterpret_cast<char*>(object)+0x108,8);add(finalCache==cacheObject);out.addText(*filename);systems->~TArrayList();filename->~basic_string();
}
void before(void* p,autotest::Capture& o){side(*static_cast<Case*>(p),false,o);}void after(void* p,autotest::Capture& o){side(*static_cast<Case*>(p),true,o);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address){autotest::Coverage cov(name,address);for(unsigned i=0;i<64;++i){Case c={operation,i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log(" particle operation%u case%u exits%d/%d issues%u/%u\n",operation,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);cov.report(host);return 1;}}cov.report(host);return cov.completed==64?0:1;}
}
TL_TEST(state_particle_a29d80){return run(host,0,"state_particle_a29d80",reinterpret_cast<uintptr_t>(&particleOld0));}
TL_TEST(state_particle_a2a060){return run(host,1,"state_particle_a2a060",reinterpret_cast<uintptr_t>(&particleOld1));}
TL_TEST(state_particle_a2a0d0){return run(host,2,"state_particle_a2a0d0",reinterpret_cast<uintptr_t>(&particleOld2));}
TL_TEST(state_particle_a29e40){return run(host,3,"state_particle_a29e40",reinterpret_cast<uintptr_t>(&particleOld3));}
