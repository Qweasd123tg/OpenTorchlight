#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
extern "C" void* layoutSoundTable[] __asm__("_ZTV12CSoundObject");
extern "C" void* layoutOtherTable[] __asm__("_ZTV17CEditorBaseObject");
TL_ORIGINAL(void, oldLayoutEvent, (void*,unsigned,long long), "_ZN12CLayoutScene9fireEventE14EEDITOR_EVENTSx")
extern "C" void newLayoutEvent(void*,unsigned,long long) __asm__("_ZN12CLayoutScene9fireEventE14EEDITOR_EVENTSx");
TL_FUNCTION(layoutDescriptorTarget,"_ZN18CDescriptorManager13GetDescriptorEPKwb")
TL_FUNCTION(layoutPlayTarget,"_ZN12CSoundObject4playEv")
TL_FUNCTION(layoutStopTarget,"_ZN12CSoundObject4stopEv")
namespace {
struct Case {uint64_t scene[40],manager[4],descriptor[36],objects[4][64];void* slots[4];unsigned event,count,capacity,mode,mutation;long long guid;};
Case* input;autotest::Capture* output;unsigned lookups,calls;
void invalid(){output->issue=autotest::Capture::InvalidReport;}
void number(unsigned n){output->add(&n,4);}
void* descriptor(void* manager,const wchar_t* name,bool create){if(manager!=input->manager||std::wcscmp(name,L"Sound")||create||lookups++)invalid();output->add(name,6*sizeof(wchar_t));number(create);return input->mode==0?0:input->descriptor;}
void sound(void* object,unsigned event){unsigned id=99;for(unsigned i=0;i<4;++i)if(object==input->objects[i])id=i;if(event!=input->event||id==99)invalid();number(id);number(event);++calls;if(id!=99)((char*)object)[0x80]^=calls;if(calls==1&&input->mutation){unsigned count=input->mutation==1?0:4;std::memcpy((char*)input->descriptor+0xe8,&count,4);}}
void play(void* p){sound(p,1);}void stop(void* p){sound(p,0);}
void body(Case& c,bool ours,autotest::Capture& out){
    input=&c;output=&out;calls=lookups=0;unsigned expected=0,end=c.count;if(c.event<2&&c.mode)for(unsigned i=0;i<end;++i){unsigned index=i<c.capacity?i:0;if(c.slots[index]==c.objects[index]&&index%2==0){++expected;if(expected==1&&c.mutation)end=c.mutation==1?0:4;}}
    detour::Set d;TL_REDIRECT(d,layoutDescriptorTarget,&descriptor);TL_REDIRECT(d,layoutPlayTarget,&play);TL_REDIRECT(d,layoutStopTarget,&stop);if(d.failed()){invalid();return;}
    autotest::invoke(out,ours?newLayoutEvent:oldLayoutEvent,c.scene,c.event,c.guid);if(lookups!=(c.event<2?1u:0u)||calls!=expected)invalid();number(lookups);number(calls);out.add(c.scene,sizeof(c.scene));out.add(c.descriptor,sizeof(c.descriptor));out.add(c.objects,sizeof(c.objects));out.add(c.slots,sizeof(c.slots));
}
void before(void* p,autotest::Capture& out){body(*(Case*)p,false,out);}void after(void* p,autotest::Capture& out){body(*(Case*)p,true,out);}
}
TL_TEST(layout_sound_events){
    autotest::Coverage coverage("layout_sound_events",(uintptr_t)&oldLayoutEvent);const unsigned events[]={0,1,2,0xffffffffu};const unsigned caps[]={0,1,4};
    for(unsigned n=0;n<4*5*3*3*3;++n){Case c;std::memset(&c,0,sizeof(c));c.event=events[n%4];c.count=n/4%5;c.capacity=caps[n/20%3];c.mode=n/60%3;c.mutation=n/180%3;c.guid=n%2?-1:0x123456789abcdefLL;
        void* manager=c.manager;std::memcpy((char*)c.scene+0x100,&manager,8);void* slots=c.slots;std::memcpy((char*)c.descriptor+0xe0,&slots,8);std::memcpy((char*)c.descriptor+0xe8,&c.count,4);std::memcpy((char*)c.descriptor+0xec,&c.capacity,4);
        for(unsigned i=0;i<4;++i){void* table=(i%2?layoutOtherTable:layoutSoundTable)+2;std::memcpy(c.objects[i],&table,8);c.slots[i]=c.mode==2&&i==0?0:c.objects[i];}
        autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    layout sound seed %u exit %d/%d issue %u/%u\n",n,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);coverage.report(host);return 1;}}
    coverage.report(host);return 0;
}
