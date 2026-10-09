#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldButton,(void*,void*,unsigned,void*),"_ZN23CEditorButtonDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_")
TL_ORIGINAL(void,oldImage,(void*,void*,unsigned,void*),"_ZN22CEditorImageDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_")
extern "C" void newButton(void*,void*,unsigned,void*) __asm__("_ZN23CEditorButtonDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_");
extern "C" void newImage(void*,void*,unsigned,void*) __asm__("_ZN22CEditorImageDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_");
extern "C" char buttonVtable[] __asm__("_ZTV13CEditorButton");
extern "C" char imageVtable[] __asm__("_ZTV12CEditorImage");
extern "C" char baseVtable[] __asm__("_ZTV17CEditorBaseObject");
TL_FUNCTION(visibleFn,"_ZN12CEditorImage10setVisibleEb")
TL_FUNCTION(enabledFn,"_ZN12CEditorImage10setEnabledEb")
namespace {
struct Case {unsigned method,kind,event,initial;};
autotest::Capture* capture;void* object;bool visible,enabled;
void setVisible(void* p,bool x){int code=1;capture->add(&code,4);capture->add(&x,1);bool same=p==object;capture->add(&same,1);visible=x;}
void setEnabled(void* p,bool x){int code=2;capture->add(&code,4);capture->add(&x,1);bool same=p==object;capture->add(&same,1);enabled=x;}
void side(const Case& c,bool ours,autotest::Capture& out){
 capture=&out;uint64_t memory[512]={0},descriptor[64]={0},sender[32]={0};object=memory;visible=c.initial;enabled=!c.initial;
 *(void**)object=(c.kind==1?imageVtable:c.kind==2?buttonVtable:baseVtable)+16;
 detour::Set d;TL_REDIRECT(d,visibleFn,&setVisible);TL_REDIRECT(d,enabledFn,&setEnabled);if(d.failed())_exit(43);
 typedef void(*Fn)(void*,void*,unsigned,void*);Fn fn=c.method?(ours?&newImage:&oldImage):(ours?&newButton:&oldButton);
 autotest::invoke(out,fn,(void*)descriptor,c.kind?object:0,c.event,(void*)sender);out.add(&visible,1);out.add(&enabled,1);
}
void a(void* p,autotest::Capture& c){side(*(Case*)p,false,c);}void b(void* p,autotest::Capture& c){side(*(Case*)p,true,c);}
int run(const tlhybrid_host* host,unsigned method,const char* name,uint64_t address){
 autotest::Coverage coverage(name,address);unsigned events[]={0,1,2,3,4,14,0x80000000U,0xffffffffU};unsigned total=0;
 for(unsigned kind=0;kind<4;++kind)for(unsigned e=0;e<8;++e)for(unsigned initial=0;initial<2;++initial){Case c={method,kind,events[e],initial};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);int pair=coverage.observe(host,x,y);++total;if(pair||autotest::incomplete(x)||autotest::incomplete(y)){host->log("    method %u class %u event %u status %d/%d bytes %lu/%lu\n",method,kind,c.event,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length);return 1;}}
 coverage.report(host);host->log("    input gate: %u cases\n",total);return 0;
}
}
TL_TEST(button_descriptor_input_gate){return run(host,0,"button_descriptor_input_gate",(uint64_t)(uintptr_t)&oldButton);}
TL_TEST(image_descriptor_input_gate){return run(host,1,"image_descriptor_input_gate",(uint64_t)(uintptr_t)&oldImage);}
