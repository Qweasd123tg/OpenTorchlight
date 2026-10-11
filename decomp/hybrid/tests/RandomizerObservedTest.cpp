#include "AutoTest.h"
#include "Randomizer.h"
#include "Utilities.h"
TL_ORIGINAL(void,originalConstruct,(void*,ERANDOMIZER_TYPE),"_ZN11CRandomizerC1E16ERANDOMIZER_TYPE")
extern "C" void candidateConstruct(void*,ERANDOMIZER_TYPE) __asm__("_ZN11CRandomizerC1E16ERANDOMIZER_TYPE");
TL_ORIGINAL(void,originalRemove,(void*,unsigned),"_ZN11CRandomizer12removeChoiceEj")
extern "C" void candidateRemove(void*,unsigned) __asm__("_ZN11CRandomizer12removeChoiceEj");
TL_ORIGINAL(int,originalGetIndex,(void*,int&),"_ZN11CRandomizer9getRandomERi")
extern "C" int candidateGetIndex(void*,int&) __asm__("_ZN11CRandomizer9getRandomERi");
TL_ORIGINAL(int,originalGet,(void*),"_ZN11CRandomizer9getRandomEv")
extern "C" int candidateGet(void*) __asm__("_ZN11CRandomizer9getRandomEv");

namespace {
struct Case{unsigned op,seed;};struct List{unsigned*data;unsigned count,capacity,grow;};
void body(Case&c,bool ours,autotest::Capture&out){
 unsigned long long bytes[sizeof(CRandomizer)/8];std::memset(bytes,0xa5,sizeof(bytes));unsigned count=c.seed%18;
 originalConstruct(bytes,ERANDOMIZER_TYPE(count?c.seed%2:0));CRandomizer*p=reinterpret_cast<CRandomizer*>(bytes);
 for(unsigned i=0;i<count;++i)p->addChoice(int((i+c.seed)%11)-3,c.seed%7==0?0:int((i*7+c.seed)%51)-5);
 float decay=float(int(c.seed%14)-2)/8.0f;std::memcpy(reinterpret_cast<char*>(p)+0x5c,&decay,4);
 if(c.seed%3==0)p->computeOdds();
 int seed=c.seed*313+7;
 if(count&&c.seed%5==0){UTILITIES::setSeed(seed);float roll=UTILITIES::randomBetween(0.0f,1.0f);p->computeOdds();List*l=reinterpret_cast<List*>(reinterpret_cast<char*>(p)+0x40);std::memcpy(l->data,&roll,4);}
 UTILITIES::setSeed(seed);
 if(c.op==0)autotest::invoke(out,ours?candidateRemove:originalRemove,static_cast<void*>(p),unsigned(int(c.seed%15)-4));
 if(c.op==1){int index=0x12340000+c.seed;int(*fn)(void*,int&)=ours?candidateGetIndex:originalGetIndex;if(!autotest::beginInvocation(out,fn))return;int result=fn(p,index);out.callCompleted=1;out.add(&result,4);out.add(&index,4);}
 if(c.op==2)autotest::invoke(out,ours?candidateGet:originalGet,static_cast<void*>(p));
 for(unsigned i=0;i<3;++i){List*l=reinterpret_cast<List*>(reinterpret_cast<char*>(p)+0x10+24*i);out.add(&l->count,12);unsigned exists=l->data!=NULL;out.add(&exists,4);if(l->count>64)_exit(52);out.add(l->data,4*l->count);}
 out.add(reinterpret_cast<char*>(p)+0x58,0x10);float next=UTILITIES::randomBetween(-1.0f,1.0f);out.add(&next,4);out.addHeapInUse();p->~CRandomizer();
}
void original(void*p,autotest::Capture&out){body(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){body(*static_cast<Case*>(p),true,out);}
}
namespace {
int observed(const tlhybrid_host*host,unsigned op,const char*name){
 const uint64_t addresses[]={(uint64_t)(uintptr_t)originalRemove,(uint64_t)(uintptr_t)originalGetIndex,(uint64_t)(uintptr_t)originalGet};
 autotest::Coverage coverage(name,addresses[op]);
 for(unsigned n=0;n<540;++n){Case c={op,n};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
  if(coverage.observe(host,a,b)){size_t k=0;while(k<a.capture.length&&k<b.capture.length&&a.capture.data[k]==b.capture.data[k])++k;
   host->log("    observed op %u case %u status %d/%d first %lu bytes %lu/%lu\n",op,n,a.status,b.status,(unsigned long)k,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}
 coverage.report(host);return 0;
}
}
TL_TEST(randomizer_remove_observed){return observed(host,0,"randomizer_remove_observed");}
TL_TEST(randomizer_index_observed){return observed(host,1,"randomizer_index_observed");}
TL_TEST(randomizer_get_observed){return observed(host,2,"randomizer_get_observed");}
