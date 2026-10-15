#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, oldUpdateDescriptors, (void*,float), "_ZN18CDescriptorManager6updateEf")
TL_ORIGINAL(void, oldProcessDescriptors, (void*,void*,void*), "_ZN18CDescriptorManager28postProcessDescriptorObjectsEP10CDataGroupP28CDescriptorLoadConfiguration")
extern "C" void newUpdateDescriptors(void*,float) __asm__("_ZN18CDescriptorManager6updateEf");
extern "C" void newProcessDescriptors(void*,void*,void*) __asm__("_ZN18CDescriptorManager28postProcessDescriptorObjectsEP10CDataGroupP28CDescriptorLoadConfiguration");
TL_FUNCTION(processTarget,"_ZN11CDescriptor18postProcessObjectsEP10CDataGroupP28CDescriptorLoadConfiguration")
namespace {
struct Case {uint64_t manager[16],objects[5][24],group[4],config[4];void* initial[8];void* alternate[8];void* table[24];unsigned operation,count,mutation,nonnull;uint32_t delta;};
Case* input;autotest::Capture* output;unsigned calls;
void put(void* p,unsigned offset,void* value){std::memcpy((char*)p+offset,&value,8);}
void invalid(){output->issue=autotest::Capture::InvalidReport;}
void number(unsigned n){output->add(&n,4);}
void visit(void* p){
    unsigned id=99;for(unsigned i=0;i<5;++i)if(p==input->objects[i])id=i;number(id);if(id==99){invalid();return;}
    ((char*)p)[0x80]^=++calls;
    if(calls==1){if(input->mutation==1)put(input->manager,0x48,input->initial);if(input->mutation==2){put(input->manager,0x40,input->alternate);put(input->manager,0x48,input->alternate+3);put(input->manager,0x50,input->alternate+8);}if(input->mutation==3){input->initial[input->count]=input->objects[4];put(input->manager,0x48,input->initial+input->count+1);}}
}
void update(void* p,float delta){uint32_t bits;std::memcpy(&bits,&delta,4);number(bits);if(input->operation||bits!=input->delta)invalid();visit(p);}
void process(void* p,void* group,void* config){number(group==input->group);number(config==input->config);if(!input->operation||group!=input->group||config!=input->config)invalid();visit(p);}
void body(Case& c,bool ours,autotest::Capture& out){
    input=&c;output=&out;calls=0;detour::Set d;TL_REDIRECT(d,processTarget,&process);if(d.failed()){invalid();return;}
    unsigned expected=(!c.operation||c.nonnull)?c.count:0;if(expected){if(c.mutation==1)expected=1;else if(c.mutation==2)expected=3;else if(c.mutation==3)++expected;}
    if(c.operation){typedef void(*Fn)(void*,void*,void*);Fn fn=ours?newProcessDescriptors:oldProcessDescriptors;if(!autotest::beginInvocation(out,fn))return;fn(c.manager,c.nonnull?c.group:0,c.config);}
    else{typedef void(*Fn)(void*,float);Fn fn=ours?newUpdateDescriptors:oldUpdateDescriptors;float delta;std::memcpy(&delta,&c.delta,4);if(!autotest::beginInvocation(out,fn))return;fn(c.manager,delta);}
    out.callCompleted=1;if(calls!=expected)invalid();number(calls);out.add(c.manager,sizeof(c.manager));out.add(c.objects,sizeof(c.objects));out.add(c.initial,sizeof(c.initial));out.add(c.alternate,sizeof(c.alternate));out.add(c.group,sizeof(c.group));out.add(c.config,sizeof(c.config));
}
void before(void* p,autotest::Capture& out){body(*(Case*)p,false,out);}void after(void* p,autotest::Capture& out){body(*(Case*)p,true,out);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address){
    autotest::Coverage coverage(name,address);const uint32_t deltas[]={0,0x80000000u,0x3f800000u,0xbf800000u,0x7f800000u,0x7fc12345u};
    for(unsigned n=0;n<5*4*2*6;++n){Case c;std::memset(&c,0,sizeof(c));c.operation=operation;c.count=n%5;c.mutation=n/5%4;c.nonnull=n/20%2;c.delta=deltas[n/40%6];c.table[8]=(void*)&update;
        for(unsigned i=0;i<5;++i){put(c.objects[i],0,c.table);c.initial[i]=c.objects[i];c.alternate[i]=c.objects[4-i];}put(c.manager,0x40,c.initial);put(c.manager,0x48,c.initial+c.count);put(c.manager,0x50,c.initial+8);
        autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    descriptor update/process seed %u exit %d/%d issue %u/%u\n",n,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);coverage.report(host);return 1;}}
    coverage.report(host);return 0;
}
}
TL_TEST(descriptor_update_traversal){return run(host,0,"descriptor_update_traversal",(uintptr_t)&oldUpdateDescriptors);}
TL_TEST(descriptor_post_process_traversal){return run(host,1,"descriptor_post_process_traversal",(uintptr_t)&oldProcessDescriptors);}
