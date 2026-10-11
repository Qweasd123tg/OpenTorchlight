
#include <cstring>
#include <string>
#include <stdexcept>
#include "AutoTest.h"
#include "ObservedWitness.h"
#include "Detour.h"
TL_ORIGINAL(void,originalReload,(void*),"_ZN11CFileSystem6reloadEv")
extern "C" void candidateReload(void*) __asm__("_ZN11CFileSystem6reloadEv");
TL_FUNCTION(targetRefresh,"_ZN14CModFileFilter14refreshAllModsEv")
TL_FUNCTION(targetCtor,"_ZN14CModFileFilterC1Ev")
TL_FUNCTION(targetParam,"_ZN14CCmdLineParser11GetIntParamERKSbIwSt11char_traitsIwESaIwEEi")
namespace {
struct Case{unsigned seed;bool throwConstructor;};Case*input;autotest::Capture*output;char*active;void*other;void*allocated;
void event(unsigned k,void*p){output->add(&k,4);output->add(&p,8);}void put(char*p,unsigned o,void*v){std::memcpy(p+o,&v,8);}
void refresh(void*p){event(1,p);static_cast<char*>(p)[input->seed%56]^=0x34;if(input->seed%5==0)put(active,0x18,NULL);else if(input->seed%5==1)put(active,0x18,other);active[0x20]=false;}
void construct(void*p){event(2,p);std::memset(p,0x31+(input->seed%29),56);allocated=p;if(input->throwConstructor){allocated=NULL;throw std::runtime_error("mod constructor");}put(active,0x18,other);active[0x20]=false;}
int parameter(void*p,const std::wstring&name,int fallback){event(3,p);output->addText(name);output->add(&fallback,4);put(active,0x18,other);active[0x20]=false;const int values[]={0,1,-1,0x7fffffff,int(0x80000000u),0,0};return values[(input->seed/3)%7];}
void side(void*p,autotest::Capture&out,bool ours){Case&c=*static_cast<Case*>(p);input=&c;output=&out;allocated=NULL;unsigned long long fs[32],settings[48],parser[8],filter[7],replacement[7];std::memset(fs,c.seed*17+3,sizeof(fs));std::memset(settings,0x61,sizeof(settings));std::memset(parser,0x23,sizeof(parser));std::memset(filter,0x44,sizeof(filter));std::memset(replacement,0x55,sizeof(replacement));active=reinterpret_cast<char*>(fs);other=replacement;put(active,0x18,c.seed%3?NULL:filter);put(active,0x40,settings);put(reinterpret_cast<char*>(settings),0x140,parser);active[0x20]=c.seed&1;
 detour::Set patches;TL_REDIRECT(patches,targetRefresh,&refresh);TL_REDIRECT(patches,targetCtor,&construct);TL_REDIRECT(patches,targetParam,&parameter);if(patches.failed())_exit(41);void(*fn)(void*)=ours?candidateReload:originalReload;if(!autotest::beginInvocation(out,fn))return;unsigned threw=0;try{fn(fs);out.callCompleted=1;}catch(const std::runtime_error&e){threw=std::strcmp(e.what(),"mod constructor")==0?1u:~0u;out.addText(e.what());}out.add(&threw,4);out.add(fs,sizeof(fs));out.add(settings,sizeof(settings));out.add(parser,sizeof(parser));out.add(filter,sizeof(filter));out.add(replacement,sizeof(replacement));if(allocated)out.add(allocated,56);out.addHeapInUse();observed_witness::finish(out,threw);
}
void original(void*p,autotest::Capture&out){side(p,out,false);}void recovered(void*p,autotest::Capture&out){side(p,out,true);}
}
TL_TEST(filesystem_reload_next){autotest::Coverage coverage("filesystem_reload_next",(uint64_t)(uintptr_t)originalReload);unsigned witnesses=0;for(unsigned n=0;n<421;++n){/* Seed 1 has no filter and parameter 0: the final case reaches the constructor. */Case c={n==420?1u:n,n==420};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);const unsigned expectedFault=c.throwConstructor?1u:0u;if(observed_witness::observe(host,coverage,a,b,expectedFault,witnesses)){host->log("    reload case %u status %d/%d bytes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}if(expectedFault&&witnesses==1&&!observed_witness::negativeControls(host,coverage,a,b,expectedFault))return 1;}coverage.report(host);return observed_witness::totals(host,coverage,witnesses,420,1)?0:1;}
