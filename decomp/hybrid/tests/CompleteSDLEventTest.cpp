#include <map>
#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#include "SDLEventHandler.h"
#undef private
#include "SDL.h"
#include "LinuxUtils.h"
#include "GameClient.h"
TL_ORIGINAL(void, eventHandlerCtor, (SDLEventHandler*), "_ZN15SDLEventHandlerC1Ev")
TL_ORIGINAL(void, eventHandlerDtor, (SDLEventHandler*), "_ZN15SDLEventHandlerD1Ev")
TL_ORIGINAL(void, originalProcessEvent, (SDLEventHandler*,const SDL_Event&), "_ZN15SDLEventHandler12ProcessEventERK9SDL_Event")
extern "C" void candidateProcessEvent(SDLEventHandler*,const SDL_Event&) __asm__("_ZN15SDLEventHandler12ProcessEventERK9SDL_Event");
TL_FUNCTION(eventClientKey,"_ZN11CGameClient8keyEventEjjl")
TL_FUNCTION(eventClientMouse,"_ZN11CGameClient10mouseEventEjj")
namespace {
struct Case {unsigned kind,state,mods,connected;};
autotest::Capture* capture;unsigned short currentMods;
void word(unsigned x){capture->add(&x,sizeof(x));}
void key(CGameClient*,unsigned msg,unsigned code,long value){word(1);word(msg);word(code);capture->add(&value,sizeof(value));}
void mouse(CGameClient*,unsigned msg,unsigned value){word(2);word(msg);word(value);}
SDL_Keymod mods(){word(3);return static_cast<SDL_Keymod>(currentMods);}
void side(void* raw,autotest::Capture& out,bool ours){
 Case c=*static_cast<Case*>(raw);capture=&out;currentMods=c.mods;
 union Storage{long double align;unsigned char bytes[sizeof(SDLEventHandler)];} storage;
 SDLEventHandler* h=reinterpret_cast<SDLEventHandler*>(storage.bytes);eventHandlerCtor(h);
 unsigned char client[8];h->m_gameClient=c.connected?reinterpret_cast<CGameClient*>(client):NULL;
 h->m_modifiers=static_cast<unsigned short>((c.mods^0x3c3)&(c.state==2?0xffff:0x43));
 for(unsigned i=0;i<256;++i)UpdateKeyState(i,(i+c.kind)%5==0);
 UpdateCursorPos(-271,891);
 SDL_Event e;std::memset(&e,0xa5,sizeof(e));
 const unsigned types[]={0,0x200,0x300,0x301,0x303,0x400,0x401,0x402,0x403};
 e.type=types[c.kind];
 if(e.type==0x300||e.type==0x301){e.key.state=c.state;e.key.keysym.scancode=static_cast<SDL_Scancode>(c.mods&1?41:511);}
 if(e.type==0x303)e.text.text[0]=static_cast<char>(c.state==0?0:(c.state==1?0x41:0xe9));
 if(e.type==0x400){e.motion.x=static_cast<int>(0x80000017u+c.mods);e.motion.y=31337;}
 if(e.type==0x401||e.type==0x402){e.button.button=c.mods%5;e.button.state=c.state;e.button.x=-17;e.button.y=187;}
 if(e.type==0x403){e.wheel.x=c.state==2?-1:static_cast<int>(c.state);e.wheel.y=c.mods&1?41:511;}
 detour::Set d;TL_REDIRECT(d,eventClientKey,&key);TL_REDIRECT(d,eventClientMouse,&mouse);
 d.redirect(reinterpret_cast<char*>(&SDL_GetModState),reinterpret_cast<char*>(&SDL_GetModState),&mods);
 if(d.failed())_exit(64);
 if(ours)autotest::invoke(out,candidateProcessEvent,h,e);else autotest::invoke(out,originalProcessEvent,h,e);
 word(h->m_modifiers);
 POINT p;GetCursorPos(&p);out.add(&p,sizeof(p));
 for(unsigned i=0;i<256;++i){short s=GetAsyncKeyState(i);out.add(&s,sizeof(s));}
 eventHandlerDtor(h);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_sdl_event_forwarding){
 autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;
 autotest::Coverage coverage("complete_sdl_event_forwarding",reinterpret_cast<uintptr_t>(&originalProcessEvent));
 const unsigned masks[]={0,1,2,3,0x40,0x80,0x100,0x200,0x3c3};
 for(unsigned k=0;k<9;++k)for(unsigned s=0;s<3;++s)for(unsigned m=0;m<9;++m)for(unsigned conn=0;conn<2;++conn){Case c={k,s,masks[m],conn};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sdl_event_forwarding",cases++,&coverage);TL_CHECK(failures,ok);}
 coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);
}
