#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
TL_ORIGINAL(void, oldCinematic, (void*,bool), "_ZN14CCameraControl16setCinematicModeEb")
extern "C" void newCinematic(void*,bool) __asm__("_ZN14CCameraControl16setCinematicModeEb");
TL_ORIGINAL(unsigned, oldMods, (void*), "_ZN14CModFileFilter21getNumberOfActiveModsEv")
extern "C" unsigned newMods(void*) __asm__("_ZN14CModFileFilter21getNumberOfActiveModsEv");
namespace {
struct Case {uint64_t camera[20],mods[8],objects[6][16];void* slots[6];unsigned oldFlag,newFlag,count,capacity,kind;};
void cameraSide(Case& c,bool ours,autotest::Capture& out){
    float current,saved,scale;std::memcpy(&current,(char*)c.camera+0x38,4);std::memcpy(&saved,(char*)c.camera+0x94,4);std::memcpy(&scale,(char*)c.camera+0x8c,4);
    uint64_t expected[20];std::memcpy(expected,c.camera,sizeof(expected));
    if(c.oldFlag!=c.newFlag){if(c.newFlag){saved=current;current=28.5f;if(current>28.5f*scale)current=28.5f*scale;}else{current=saved;if(current<14.0f)current=14.0f;else if(current>28.5f*scale)current=28.5f*scale;}
        std::memcpy((char*)expected+0x38,&current,4);std::memcpy((char*)expected+0x94,&saved,4);((char*)expected)[0x98]=c.newFlag;}
    autotest::invoke(out,ours?newCinematic:oldCinematic,c.camera,c.newFlag!=0);
    if(std::memcmp(expected,c.camera,sizeof(expected)))out.issue=autotest::Capture::InvalidReport;out.add(c.camera,sizeof(c.camera));
}
void modSide(Case& c,bool ours,autotest::Capture& out){
    unsigned expected=0;for(unsigned i=0;i<c.count;++i){unsigned char* p=(unsigned char*)c.slots[i<c.capacity?i:0];unsigned priority;std::memcpy(&priority,p+0x74,4);expected+=(p[0x70]!=0&&priority<0x80000000u);}
    typedef unsigned(*Fn)(void*);Fn fn=ours?newMods:oldMods;if(!autotest::beginInvocation(out,fn))return;unsigned result=fn(c.mods);out.callCompleted=1;out.add(&result,4);if(result!=expected)out.issue=autotest::Capture::InvalidReport;
    out.add(c.mods,sizeof(c.mods));out.add(c.slots,sizeof(c.slots));out.add(c.objects,sizeof(c.objects));
}
void before(void* p,autotest::Capture& out){Case& c=*(Case*)p;if(c.kind)modSide(c,false,out);else cameraSide(c,false,out);}
void after(void* p,autotest::Capture& out){Case& c=*(Case*)p;if(c.kind)modSide(c,true,out);else cameraSide(c,true,out);}
}
TL_TEST(camera_cinematic_state){
    autotest::Coverage cov("camera_cinematic_state",(uintptr_t)&oldCinematic);
    const uint32_t bits[]={0,0x80000000u,0x3f000000u,0x3f800000u,0x40000000u,0x415fffffu,0x41600000u,0x41e40000u,0x41e40001u,0x7f800000u,0xff800000u,0x7fc12345u,0x7fc98765u};
    for(unsigned n=0;n<4*13*13;++n){Case c;std::memset(&c,0xa5,sizeof(c));c.kind=0;c.oldFlag=n%2;c.newFlag=n/2%2;((char*)c.camera)[0x98]=c.oldFlag;
        std::memcpy((char*)c.camera+0x38,&bits[n/4%13],4);std::memcpy((char*)c.camera+0x94,&bits[(n/4%13+5)%13],4);std::memcpy((char*)c.camera+0x8c,&bits[n/52%13],4);
        autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log("    camera seed %u issue %u/%u\n",n,a.capture.issue,b.capture.issue);cov.report(host);return 1;}}
    cov.report(host);return 0;
}
TL_TEST(mod_filter_active_count){
    autotest::Coverage cov("mod_filter_active_count",(uintptr_t)&oldMods);const unsigned priorities[]={0,1,0x7fffffffu,0x80000000u,0xffffffffu};
    for(unsigned n=0;n<7*4*5;++n){Case c;std::memset(&c,0xa5,sizeof(c));c.kind=1;c.count=n%7;const unsigned caps[]={0,1,3,6};c.capacity=caps[n/7%4];
        for(unsigned i=0;i<6;++i){c.slots[i]=c.objects[i];((char*)c.objects[i])[0x70]=(i+n)%3==0?0:(i+n)%3==1?1:0x80;std::memcpy((char*)c.objects[i]+0x74,&priorities[(i+n/28)%5],4);}
        void* slots=c.slots;std::memcpy((char*)c.mods+0x18,&slots,8);std::memcpy((char*)c.mods+0x20,&c.count,4);std::memcpy((char*)c.mods+0x24,&c.capacity,4);
        autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log("    mods seed %u\n",n);cov.report(host);return 1;}}
    cov.report(host);return 0;
}
