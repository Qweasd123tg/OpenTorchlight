#include <cstring>
#include <stdint.h>
#include <OgreRenderWindow.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#include "Game.h"
#include "GameClient.h"
#undef private
TL_ORIGINAL(bool, gameFrameQueueOriginal, (CGame*,const Ogre::FrameEvent&), "_ZN5CGame20frameRenderingQueuedERKN4Ogre10FrameEventE")
extern "C" bool gameFrameQueueCandidate(CGame*,const Ogre::FrameEvent&) __asm__("_ZN5CGame20frameRenderingQueuedERKN4Ogre10FrameEventE");
TL_ORIGINAL(long, gameWindowOriginal, (CGame*,void*,unsigned,unsigned,long), "_ZN5CGame7WndProcEPvjjl")
extern "C" long gameWindowCandidate(CGame*,void*,unsigned,unsigned,long) __asm__("_ZN5CGame7WndProcEPvjjl");
TL_FUNCTION(gameFrameClear,"_ZN11CGameClient25clearSceneManagerPassMapsEv")
TL_FUNCTION(gameFrameCursor,"_ZN11CGameClient12updateCursorEv")
TL_FUNCTION(gameFrameKey,"_ZN11CGameClient8keyEventEjjl")
TL_FUNCTION(gameFrameMouse,"_ZN11CGameClient10mouseEventEjj")
extern "C" void frameRootCtor(void*,const std::string&,const std::string&,const std::string&) __asm__("_ZN4Ogre4RootC1ERKSsS2_S2_");
extern "C" void frameRootDtor(void*) __asm__("_ZN4Ogre4RootD1Ev");
namespace {
autotest::Capture* capture;
void word(unsigned x){capture->add(&x,sizeof(x));}
void clear(CGameClient*){word(1);}void cursor(CGameClient*){word(2);}
void key(CGameClient*,unsigned a,unsigned b,long c){word(3);word(a);word(b);capture->add(&c,sizeof(c));}
void mouse(CGameClient*,unsigned a,unsigned b){word(4);word(a);word(b);}
class Window: public Ogre::RenderWindow {
 bool closed;
public:
 Window(bool value):closed(value){}
 void create(const Ogre::String&,unsigned,unsigned,bool,const Ogre::NameValuePairList*){}
 void destroy(){}void resize(unsigned,unsigned){}void reposition(int,int){}
 bool isClosed()const{return closed;}
 void copyContentsToMemory(const Ogre::PixelBox&,Ogre::RenderTarget::FrameBuffer){}
 bool requiresTextureFlipping()const{return false;}
};
struct Case{unsigned target,client,pending,window,message,key;};
void side(void* raw,autotest::Capture& out,bool ours){
 Case c=*static_cast<Case*>(raw);capture=&out;
 union G{long double a;unsigned char data[sizeof(CGame)];} gs;
 union C{long double a;unsigned char data[sizeof(CGameClient)];} cs;
 std::memset(&gs,0,sizeof(gs));std::memset(&cs,0,sizeof(cs));
 CGame*g=reinterpret_cast<CGame*>(gs.data);CGameClient*client=reinterpret_cast<CGameClient*>(cs.data);
 client->m_pendingPassClear=c.pending;g->m_gameClient=c.client?client:NULL;
 detour::Set d;TL_REDIRECT(d,gameFrameClear,&clear);TL_REDIRECT(d,gameFrameCursor,&cursor);TL_REDIRECT(d,gameFrameKey,&key);TL_REDIRECT(d,gameFrameMouse,&mouse);if(d.failed())_exit(64);
 if(c.target==0){
  void*root=Ogre::NedAllocImpl::allocBytes(0x398,0,0,0);std::string empty;frameRootCtor(root,empty,empty,empty);
  {Window window(c.window==2);g->m_renderWindow=c.window?&window:NULL;Ogre::FrameEvent event={.01f,.02f};
   bool(*fn)(CGame*,const Ogre::FrameEvent&)=ours?gameFrameQueueCandidate:gameFrameQueueOriginal;
   if(autotest::beginInvocation(out,fn)){bool result=fn(g,event);out.callCompleted=1;word(result);}
  }frameRootDtor(root);Ogre::NedAllocImpl::deallocBytes(root);
 }else{
  long(*fn)(CGame*,void*,unsigned,unsigned,long)=ours?gameWindowCandidate:gameWindowOriginal;
  if(autotest::beginInvocation(out,fn)){long result=fn(g,reinterpret_cast<void*>(0x1234),c.message,c.key,-317);out.callCompleted=1;out.add(&result,sizeof(result));}
 }
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_game_frame_queue){
 autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_game_frame_queue",reinterpret_cast<uintptr_t>(&gameFrameQueueOriginal));
 for(unsigned c=0;c<2;++c)for(unsigned p=0;p<2;++p)for(unsigned w=0;w<3;++w){Case x={0,c,p,w,0,0};bool ok=autotest::compareCase(original,candidate,&x,stats,host,"complete_game_frame_queue",cases++,&coverage);TL_CHECK(failures,ok);}
 coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);
}
TL_TEST(complete_game_window_dispatch){
 autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_game_window_dispatch",reinterpret_cast<uintptr_t>(&gameWindowOriginal));
 const unsigned messages[]={0,5,7,0x32,0x100,0x101,0x102,0x103,0x104,0x105,0x106,0x201,0x202,0x203,0x204,0x205,0x206,0x207,0x208,0x209,0x20a,0x20b,0x214};
 for(unsigned c=0;c<2;++c)for(unsigned k=0;k<5;++k)for(unsigned m=0;m<23;++m){Case x={1,c,0,0,messages[m],k};bool ok=autotest::compareCase(original,candidate,&x,stats,host,"complete_game_window_dispatch",cases++,&coverage);TL_CHECK(failures,ok);}
 coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);
}
