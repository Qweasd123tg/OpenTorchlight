#include <cstring>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#define private public
#include "SDLEventHandler.h"
#undef private
#include "LinuxUtils.h"
TL_ORIGINAL(void, systemsSDLConstructor, (SDLEventHandler*), "_ZN15SDLEventHandlerC1Ev")
TL_ORIGINAL(void, systemsSDLDtor, (SDLEventHandler*), "_ZN15SDLEventHandlerD1Ev")
extern "C" void newSDLCtor(SDLEventHandler*) __asm__("_ZN15SDLEventHandlerC1Ev");
namespace {
struct Case{unsigned pattern;};
void side(void* raw,autotest::Capture& out,bool ours) {
    const Case& c=*static_cast<Case*>(raw);
    union Storage{long double alignment;unsigned char bytes[sizeof(SDLEventHandler)];} storage;
    std::memset(storage.bytes,0xa5,sizeof(storage.bytes));
    SDLEventHandler* self=reinterpret_cast<SDLEventHandler*>(storage.bytes);
    for(unsigned i=0;i<256;++i)UpdateKeyState(i,(i+c.pattern)%3==0);
    if(ours)autotest::invoke(out,newSDLCtor,self);else autotest::invoke(out,systemsSDLConstructor,self);
    unsigned nullClient=self->m_gameClient==NULL;out.add(&nullClient,sizeof(nullClient));out.add(&self->m_modifiers,sizeof(self->m_modifiers));
    unsigned count=self->m_scanCodes.size();out.add(&count,sizeof(count));
    for(std::map<SDL_Scancode,unsigned short>::iterator it=self->m_scanCodes.begin();it!=self->m_scanCodes.end();++it){out.add(&it->first,sizeof(it->first));out.add(&it->second,sizeof(it->second));}
    for(unsigned i=0;i<256;++i){short state=GetAsyncKeyState(i);out.add(&state,sizeof(state));}
    systemsSDLDtor(self);
}
void original(void* p,autotest::Capture& out){side(p,out,false);}
void candidate(void* p,autotest::Capture& out){side(p,out,true);}
}
TL_TEST(complete_sdl_constructor_keymap) {
    autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;
    autotest::Coverage coverage("complete_sdl_constructor_keymap",reinterpret_cast<uintptr_t>(&systemsSDLConstructor));
    for(unsigned i=0;i<8;++i){Case c={i};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sdl_constructor_keymap",cases++,&coverage);TL_CHECK(failures,ok);}
    coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);
}
