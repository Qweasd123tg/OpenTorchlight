#include "AutoTest.h"
#include "RunicCore.h"
TL_ORIGINAL(void,originalConstruct,(void*),"_ZN10CRunicCoreC1Ev")
extern "C" void candidateConstruct(void*) __asm__("_ZN10CRunicCoreC1Ev");
TL_ORIGINAL(void,originalDestroy,(void*),"_ZN10CRunicCoreD1Ev")
extern "C" void candidateDestroy(void*) __asm__("_ZN10CRunicCoreD1Ev");
TL_ORIGINAL(unsigned,originalAdd,(void*,void*),"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
extern "C" unsigned candidateAdd(void*,void*) __asm__("_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE");
TL_ORIGINAL(void,originalRemove,(void*,void*,unsigned),"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
extern "C" void candidateRemove(void*,void*,unsigned) __asm__("_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj");

namespace {
struct Case{unsigned op,seed;};
struct Pointer{void*object;unsigned index;unsigned padding;};
struct List{Pointer**data;unsigned count,capacity,grow;};
struct Core{void*vtable;List*list;};
void body(Case&c,bool ours,autotest::Capture&out){
 Core core;std::memset(&core,0xa5,sizeof(core));Pointer slots[64];std::memset(slots,0xc7,sizeof(slots));
 originalConstruct(&core);unsigned count=c.seed%49;
 for(unsigned i=0;i<count;++i){unsigned k=(i*13)%53;slots[k].index=originalAdd(&core,&slots[k]);slots[k].object=&core;}
 if(c.seed%7==0&&count){unsigned k=c.seed%count;originalRemove(&core,&slots[k],k);}
 for(unsigned i=0;i<64;++i)if(slots[i].object!=&core){slots[i].object=NULL;slots[i].index=0x80000000u+i+c.seed;}
 unsigned index=c.seed%6==0?~0u:c.seed%6==1?1000u:c.seed%6==2?0u:c.seed%6==3?count:c.seed%6==4?count/2:count-1;
 if(c.op==0)autotest::invoke(out,ours?candidateDestroy:originalDestroy,static_cast<void*>(&core));
 if(c.op==1)autotest::invoke(out,ours?candidateAdd:originalAdd,static_cast<void*>(&core),static_cast<void*>(&slots[63]));
 if(c.op==2)autotest::invoke(out,ours?candidateRemove:originalRemove,static_cast<void*>(&core),static_cast<void*>(&slots[c.seed%64]),index);
 out.add(&core.vtable,8);unsigned exists=core.list!=NULL;out.add(&exists,4);
 if(core.list){out.add(&core.list->count,12);if(core.list->count>64)_exit(55);for(unsigned i=0;i<core.list->count;++i){long k=core.list->data[i]-slots;out.add(&k,sizeof(k));}}
 for(unsigned i=0;i<64;++i){unsigned active=slots[i].object==&core;out.add(&active,4);out.add(&slots[i].index,8);}
 out.add(&g_iTotalCountOfObjects,sizeof(g_iTotalCountOfObjects));out.addHeapInUse();
 if(c.op!=0)originalDestroy(&core);
}
void original(void*p,autotest::Capture&out){body(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){body(*static_cast<Case*>(p),true,out);}
}
namespace {
int observed(const tlhybrid_host*host,unsigned op,const char*name){
 const uint64_t addresses[]={(uint64_t)(uintptr_t)originalDestroy,(uint64_t)(uintptr_t)originalAdd,(uint64_t)(uintptr_t)originalRemove};
 autotest::Coverage coverage(name,addresses[op]);
 for(unsigned n=0;n<294;++n){Case c={op,n};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
  if(coverage.observe(host,a,b)){size_t k=0;while(k<a.capture.length&&k<b.capture.length&&a.capture.data[k]==b.capture.data[k])++k;
   host->log("    observed op %u case %u status %d/%d first %lu bytes %lu/%lu\n",op,n,a.status,b.status,(unsigned long)k,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}
 coverage.report(host);return 0;
}
}
TL_TEST(runic_destroy_observed){return observed(host,0,"runic_destroy_observed");}
TL_TEST(runic_add_observed){return observed(host,1,"runic_add_observed");}
TL_TEST(runic_remove_observed){return observed(host,2,"runic_remove_observed");}
