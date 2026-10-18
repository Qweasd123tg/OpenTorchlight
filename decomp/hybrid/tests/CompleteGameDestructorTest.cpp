#include <OgreLogManager.h>
#include <OgreRenderWindow.h>
#include "SystemsNativeGame.h"
#include "CameraControl.h"
#include "SoundManager.h"
TL_ORIGINAL(void,dtorOriginal,(CGame*),"_ZN5CGameD1Ev")
extern "C" void dtorCandidate(CGame*) __asm__("_ZN5CGameD1Ev");
TL_ORIGINAL(void,dtorSoundCtor,(CSoundManager*,bool),"_ZN13CSoundManagerC1Eb")
TL_FUNCTION(dtorSave,"_ZN20CDynamicPropertyFile12SaveSettingsERKSbIwSt11char_traitsIwESaIwEE")
namespace {
autotest::Capture*cap;void word(unsigned x){cap->add(&x,sizeof(x));}
class Window:public Ogre::RenderWindow{public:void create(const Ogre::String&,unsigned,unsigned,bool,const Ogre::NameValuePairList*){}void destroy(){}void resize(unsigned,unsigned){}void reposition(int,int){}bool isClosed()const{return false;}void copyContentsToMemory(const Ogre::PixelBox&,Ogre::RenderTarget::FrameBuffer){}bool requiresTextureFlipping()const{return false;}};
bool save(CSettings*,const std::wstring&path){word(1);cap->addText(path);return true;}void videoQuit(){word(2);}
void side(void*raw,autotest::Capture&out,bool ours){unsigned mode=*static_cast<unsigned*>(raw);cap=&out;SystemsNativeGame native;CGame*g=native.game;
 if(mode&1)g->m_root=native.root;
 if(mode&2){
  CSoundManager*sound=static_cast<CSoundManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CSoundManager),0,0,0));
  dtorSoundCtor(sound,false);
  // Disabled audio never acquires these groups; native C1 leaves both unwritten.
  sound->m_iUnknown6E0=NULL;sound->m_iUnknown6E8=NULL;
  g->m_soundManager=sound;
 }
 if(mode&4)g->m_cameraControl=new CCameraControl(NULL,NULL,NULL,NULL,NULL);
 if(!(mode&8))g->m_settings=NULL;
 g->m_frameTimes.push_back(.01f);g->m_frameTimes.push_back(.02f);g->m_title=L"Destructor ownership";g->m_pluginsFile="native";
 Window*window=mode&16?new Window:NULL;g->m_renderWindow=window;if(window)Ogre::WindowEventUtilities::addWindowEventListener(window,g);
 detour::Set d;TL_REDIRECT(d,dtorSave,&save);d.redirect(reinterpret_cast<char*>(&SDL_VideoQuit),reinterpret_cast<char*>(&SDL_VideoQuit),&videoQuit);if(d.failed())_exit(64);
 void(*fn)(CGame*)=ours?dtorCandidate:dtorOriginal;if(autotest::beginInvocation(out,fn)){fn(g);out.callCompleted=1;}
 word(g->m_root==NULL);word(g->m_soundManager==NULL);word(g->m_cameraControl==NULL);word(g->m_settings==NULL);word(g->m_gameClient==NULL);word(g->m_logManager==NULL);
 d.restore();if(window)delete window;if(mode&1)native.root=NULL;if(mode&8)native.settings=NULL;native.game=NULL;Ogre::NedAllocImpl::deallocBytes(g);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_game_destructor){autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_game_destructor",reinterpret_cast<uintptr_t>(&dtorOriginal));for(unsigned mode=0;mode<32;++mode){if((mode&17)==17)continue;bool ok=autotest::compareCase(original,candidate,&mode,stats,host,"complete_game_destructor",cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
