#include <cstring>
#include <string>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,aeOldAll,(void*),"_ZN20CAllDescriptorsScene17createDescriptorsEv")
extern "C" void aeNewAll(void*) __asm__("_ZN20CAllDescriptorsScene17createDescriptorsEv");
TL_ORIGINAL(void,aeOldLayoutDescriptors,(void*),"_ZN12CLayoutScene17createDescriptorsEv")
extern "C" void aeNewLayoutDescriptors(void*) __asm__("_ZN12CLayoutScene17createDescriptorsEv");
TL_ORIGINAL(void,aeOldLayoutCtor,(void*),"_ZN12CLayoutSceneC1Ev")
extern "C" void aeNewLayoutCtor(void*) __asm__("_ZN12CLayoutSceneC1Ev");
TL_FUNCTION(aeSceneBaseCtor,"_ZN12CEditorSceneC2EPKw")
TL_FUNCTION(aeAddDescriptor,"_ZN12CEditorScene13AddDescriptorEPKw")
TL_FUNCTION(aeEditorRunning,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(aeLayoutDescriptors,"_ZN12CLayoutScene17createDescriptorsEv")
extern "C" char aeLayoutTable[] __asm__("_ZTV12CLayoutScene");
namespace {
struct Case{unsigned op,seed;};autotest::Capture* output;Case input;void* self;void* resource;
void number(unsigned n){output->add(&n,4);}void check(void*p,void*expected){number(p==expected);if(p!=expected)output->issue=autotest::Capture::InvalidReport;}
bool running(void*p){number(1);check(p,resource);return input.seed&1;}
void layout(void*p){number(2);check(p,self);}
void* add(void*p,const wchar_t*name){number(3);check(p,self);output->addText(std::wstring(name));return reinterpret_cast<void*>(0x12345670u+input.seed);}
void base(void*p,const wchar_t*name){number(4);check(p,self);output->addText(std::wstring(name));std::memset(p,input.seed,0x180);}
void side(void*p,autotest::Capture&out,bool ours){input=*static_cast<Case*>(p);output=&out;uint64_t memory[128],res[16]={0};std::memset(memory,input.seed|0x80,sizeof(memory));self=memory;resource=res;std::memcpy(static_cast<char*>(self)+0x68,&resource,8);
 detour::Set d;TL_REDIRECT(d,aeEditorRunning,&running);TL_REDIRECT(d,aeAddDescriptor,&add);TL_REDIRECT(d,aeSceneBaseCtor,&base);if(input.op==0)TL_REDIRECT(d,aeLayoutDescriptors,&layout);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void(*Fn)(void*);Fn fn=input.op==0?(ours?aeNewAll:aeOldAll):input.op==1?(ours?aeNewLayoutDescriptors:aeOldLayoutDescriptors):(ours?aeNewLayoutCtor:aeOldLayoutCtor);autotest::invoke(out,fn,self);
 if(input.op==2){number(*reinterpret_cast<void**>(self)==aeLayoutTable+16);std::memset(self,0,8);}out.add(memory,sizeof(memory));
}
void old(void*p,autotest::Capture&c){side(p,c,false);}void newer(void*p,autotest::Capture&c){side(p,c,true);}
int run(const tlhybrid_host*host,unsigned op,const char*name,uint64_t address){autotest::Coverage coverage(name,address);for(unsigned seed=0;seed<32;++seed){Case c={op,seed};autotest::Outcome a,b;autotest::runChild(old,&c,a);autotest::runChild(newer,&c,b);if(coverage.observe(host,a,b)){host->log("    advance scenes %u/%u statuses %d/%d bytes %lu/%lu\n",op,seed,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(advance_editor_all_descriptors){return run(host,0,"advance_editor_all_descriptors",(uint64_t)(uintptr_t)aeOldAll);}
TL_TEST(advance_editor_layout_descriptors){return run(host,1,"advance_editor_layout_descriptors",(uint64_t)(uintptr_t)aeOldLayoutDescriptors);}
TL_TEST(advance_editor_layout_ctor){return run(host,2,"advance_editor_layout_ctor",(uint64_t)(uintptr_t)aeOldLayoutCtor);}
