// Real manager vector traversal, with observed direct/virtual collaborators.
#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, oldLoaded, (void*,void*), "_ZN18CDescriptorManager28notifyDescriptorsSceneLoadedEP12CEditorScene")
TL_ORIGINAL(void, oldDeactivated, (void*,void*), "_ZN18CDescriptorManager21deactivateDescriptorsEP12CEditorScene")
TL_ORIGINAL(int, oldLoadObjects, (void*,void*,void*), "_ZN18CDescriptorManager21loadDescriptorObjectsEP10CDataGroupP28CDescriptorLoadConfiguration")
extern "C" void newLoaded(void*,void*) __asm__("_ZN18CDescriptorManager28notifyDescriptorsSceneLoadedEP12CEditorScene");
extern "C" void newDeactivated(void*,void*) __asm__("_ZN18CDescriptorManager21deactivateDescriptorsEP12CEditorScene");
extern "C" int newLoadObjects(void*,void*,void*) __asm__("_ZN18CDescriptorManager21loadDescriptorObjectsEP10CDataGroupP28CDescriptorLoadConfiguration");
TL_FUNCTION(loadTarget,"_ZN11CDescriptor11loadObjectsEP10CDataGroupP28CDescriptorLoadConfiguration")
namespace {
struct Case {unsigned operation,count,nonnull,mutation,seed;};
const Case* input;autotest::Capture* capture;void* manager;void* objects[4];void* group;void* config;void** alternative;unsigned calls;
void put(void* p,unsigned offset,void* x){std::memcpy(static_cast<char*>(p)+offset,&x,sizeof(x));}
void number(unsigned x){capture->add(&x,sizeof(x));}
void invalid(){capture->issue=autotest::Capture::InvalidReport;}
unsigned id(void* p){for(unsigned i=0;i<4;++i)if(p==objects[i])return i;invalid();return 99;}
void operation(void* p,void* argument){
    number(id(p));number(argument==group);if(argument!=group)invalid();++calls;
    static_cast<unsigned char*>(p)[0x80]^=static_cast<unsigned char>(calls);
    if(calls==1&&input->mutation==1){void* begin=0;std::memcpy(&begin,static_cast<char*>(manager)+0x40,8);put(manager,0x48,begin);}
    if(calls==1&&input->mutation==2){put(manager,0x40,alternative);put(manager,0x48,alternative+2);put(manager,0x50,alternative+4);}
}
int load(void* p,void* argument,void* cfg){
    if(cfg!=config)invalid();number(cfg==config);operation(p,argument);
    int result=static_cast<int>((id(p)+1)*17)-static_cast<int>(input->seed*31);capture->add(&result,4);return result;
}
void side(Case& c,bool ours,autotest::Capture& out){
    input=&c;capture=&out;calls=0;
    uint64_t managerBytes[16]={0},objectBytes[4][32]={{0}},groupBytes[8]={0},configBytes[8]={0};void* table[18]={0};
    void* initial[4];void* alternate[4];manager=managerBytes;group=c.nonnull?groupBytes:0;config=configBytes;alternative=alternate;
    table[0x70/8]=reinterpret_cast<void*>(&operation);table[0x80/8]=reinterpret_cast<void*>(&operation);
    for(unsigned i=0;i<4;++i){objects[i]=objectBytes[i];put(objects[i],0,table);initial[i]=objects[i];}
    for(unsigned i=0;i<4;++i)alternate[i]=objects[3-i];
    put(manager,0x40,initial);put(manager,0x48,initial+c.count);put(manager,0x50,initial+4);
    unsigned expectedCalls=0;int expectedTotal=0;unsigned end=c.count;bool switched=false;
    if(c.nonnull)for(unsigned i=0;i<end;++i){unsigned index=switched?3-i:i;++expectedCalls;expectedTotal+=static_cast<int>((index+1)*17)-static_cast<int>(c.seed*31);
        if(expectedCalls==1&&c.mutation==1)end=0;if(expectedCalls==1&&c.mutation==2){switched=true;end=2;}}
    detour::Set d;TL_REDIRECT(d,loadTarget,&load);if(d.failed()){invalid();return;}
    if(c.operation==0)autotest::invoke(out,ours?newLoaded:oldLoaded,manager,group);
    else if(c.operation==1)autotest::invoke(out,ours?newDeactivated:oldDeactivated,manager,group);
    else {
        typedef int(*Fn)(void*,void*,void*);Fn fn=ours?newLoadObjects:oldLoadObjects;
        if(!autotest::beginInvocation(out,fn))return;int result=fn(manager,group,config);out.callCompleted=1;out.add(&result,4);if(result!=expectedTotal)invalid();
    }
    if(calls!=expectedCalls)invalid();number(calls);
    void* begin=0;void* last=0;void* capacity=0;std::memcpy(&begin,static_cast<char*>(manager)+0x40,8);std::memcpy(&last,static_cast<char*>(manager)+0x48,8);std::memcpy(&capacity,static_cast<char*>(manager)+0x50,8);
    bool changed=c.nonnull&&c.count!=0;
    void** expectedBegin=changed&&c.mutation==2?alternate:initial;
    unsigned expectedSize=changed&&c.mutation==1?0:changed&&c.mutation==2?2:c.count;
    if(begin!=expectedBegin||last!=expectedBegin+expectedSize||capacity!=expectedBegin+4)invalid();
    number(begin==initial?0:begin==alternate?1:99);number(static_cast<unsigned>((static_cast<void**>(last)-static_cast<void**>(begin))));number(static_cast<unsigned>((static_cast<void**>(capacity)-static_cast<void**>(begin))));
    put(manager,0x40,0);put(manager,0x48,0);put(manager,0x50,0);out.add(manager,sizeof(managerBytes));
    for(unsigned i=0;i<4;++i){void* actual=0;std::memcpy(&actual,objects[i],8);if(actual!=table)invalid();put(objects[i],0,0);out.add(objects[i],sizeof(objectBytes[i]));}
    out.add(groupBytes,sizeof(groupBytes));out.add(configBytes,sizeof(configBytes));
}
void before(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}void after(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address){
    autotest::Coverage coverage(name,address);const unsigned counts[]={0,1,2,4};
    for(unsigned count=0;count<4;++count)for(unsigned nonnull=0;nonnull<2;++nonnull)for(unsigned mutation=0;mutation<3;++mutation)for(unsigned seed=0;seed<2;++seed){
        Case c={operation,counts[count],nonnull,mutation,seed};autotest::Outcome x,y;autotest::runChild(before,&c,x);autotest::runChild(after,&c,y);
        if(coverage.observe(host,x,y)){host->log("    manager op %u count %u nonnull %u mutation %u seed %u exits %d/%d\n",operation,c.count,nonnull,mutation,seed,x.childStatus,y.childStatus);coverage.report(host);return 1;}}
    coverage.report(host);return 0;
}
}
TL_TEST(descriptor_manager_scene_loaded){return run(host,0,"descriptor_manager_scene_loaded",reinterpret_cast<uintptr_t>(&oldLoaded));}
TL_TEST(descriptor_manager_deactivated){return run(host,1,"descriptor_manager_deactivated",reinterpret_cast<uintptr_t>(&oldDeactivated));}
TL_TEST(descriptor_manager_load_objects){return run(host,2,"descriptor_manager_load_objects",reinterpret_cast<uintptr_t>(&oldLoadObjects));}
