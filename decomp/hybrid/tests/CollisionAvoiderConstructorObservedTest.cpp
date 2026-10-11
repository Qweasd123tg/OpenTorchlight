
#include <cstring>
#include <string>
#include <stdexcept>
#include "AutoTest.h"
#include "ObservedWitness.h"
#include "Detour.h"
TL_ORIGINAL(void,originalConstructor,(void*,void*),"_ZN24CCollisionAvoiderWrapperC1EP16CResourceManager")
extern "C" void candidateConstructor(void*,void*) __asm__("_ZN24CCollisionAvoiderWrapperC1EP16CResourceManager");
TL_FUNCTION(targetBase,"_ZN16CColliderWrapperC2EP16CResourceManagerSs")
TL_FUNCTION(targetDestroy,"_ZN16CColliderWrapperD2Ev")
TL_FUNCTION(targetRadius,"_ZN16ParticleUniverse26CollisionAvoidanceAffector9setRadiusEf")
namespace {
struct Case{unsigned seed;};Case*input;autotest::Capture*output;void*affector;
void event(unsigned k,void*p){output->add(&k,4);output->add(&p,8);}
void base(void*p,void*resources,std::string name){event(1,p);output->add(&resources,8);output->addText(name);std::memset(p,input->seed*13+5,0x120);std::memcpy(static_cast<char*>(p)+0x110,&affector,8);if(input->seed%5==1)throw std::runtime_error("base constructor");}
void destroy(void*p){event(2,p);output->add(p,0x120);}
void radius(void*p,float value){event(3,p);output->add(&value,4);std::memcpy(p,&value,4);if(input->seed%5==2)throw std::runtime_error("radius setter");}
void side(void*p,autotest::Capture&out,bool ours){Case&c=*static_cast<Case*>(p);input=&c;output=&out;unsigned long long storage[0x120/8],resources[8],particle[8];std::memset(storage,c.seed,sizeof(storage));std::memset(resources,0x66,sizeof(resources));std::memset(particle,0x47,sizeof(particle));affector=particle;detour::Set patches;TL_REDIRECT(patches,targetBase,&base);TL_REDIRECT(patches,targetDestroy,&destroy);TL_REDIRECT(patches,targetRadius,&radius);if(patches.failed())_exit(41);void(*fn)(void*,void*)=ours?candidateConstructor:originalConstructor;if(!autotest::beginInvocation(out,fn))return;unsigned threw=0;try{fn(storage,c.seed&8?resources:NULL);out.callCompleted=1;}catch(const std::runtime_error&e){threw=std::strcmp(e.what(),"base constructor")==0?1u:std::strcmp(e.what(),"radius setter")==0?2u:~0u;out.addText(e.what());}out.add(&threw,4);out.add(storage,sizeof(storage));out.add(resources,sizeof(resources));out.add(particle,sizeof(particle));out.addHeapInUse();observed_witness::finish(out,threw);}
void original(void*p,autotest::Capture&out){side(p,out,false);}void recovered(void*p,autotest::Capture&out){side(p,out,true);}
}
TL_TEST(collision_avoider_constructor_observed){autotest::Coverage coverage("collision_avoider_constructor_observed",(uint64_t)(uintptr_t)originalConstructor);unsigned witnesses=0;for(unsigned n=0;n<320;++n){Case c={n};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);const unsigned expectedFault=n%5==1?1u:n%5==2?2u:0u;if(observed_witness::observe(host,coverage,a,b,expectedFault,witnesses)){size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    avoider case %u status %d/%d first %lu bytes %lu/%lu\n",n,a.status,b.status,(unsigned long)at,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}if(expectedFault&&witnesses==1&&!observed_witness::negativeControls(host,coverage,a,b,expectedFault))return 1;}coverage.report(host);return observed_witness::totals(host,coverage,witnesses,192,128)?0:1;}
