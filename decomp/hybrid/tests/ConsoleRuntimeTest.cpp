#include "NativeConsoleFixture.h"
#include "GameVariables.h"
#include <CEGUIInputEvent.h>
#include <clocale>
#include <elements/CEGUIEditbox.h>
#include <elements/CEGUIFrameWindow.h>
#include <elements/CEGUIMultiLineEditbox.h>
TL_ORIGINAL(void,ncUpdate,(CConsole*,float),"_ZN8CConsole6updateEf")
TL_ORIGINAL(bool,ncKey,(CConsole*,const CEGUI::EventArgs&),"_ZN8CConsole13handleKeyDownERKN5CEGUI9EventArgsE")
TL_ORIGINAL(bool,ncSubmit,(CConsole*,const CEGUI::EventArgs&),"_ZN8CConsole12handleSubmitERKN5CEGUI9EventArgsE")
TL_ORIGINAL(void,ncNoHistory,(CConsole*,std::wstring),"_ZN8CConsole16addTextNoHistoryESbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,ncText,(CConsole*,std::wstring),"_ZN8CConsole7addTextESbIwSt11char_traitsIwESaIwEE")
extern "C" void ncNewCtor(CConsole*,CGameUI*,CResourceManager*,CEGUI::Window*) __asm__("_ZN8CConsoleC1EP7CGameUIP16CResourceManagerPN5CEGUI6WindowE");
extern "C" void ncNewUpdate(CConsole*,float) __asm__("_ZN8CConsole6updateEf");
extern "C" bool ncNewKey(CConsole*,const CEGUI::EventArgs&) __asm__("_ZN8CConsole13handleKeyDownERKN5CEGUI9EventArgsE");
extern "C" bool ncNewSubmit(CConsole*,const CEGUI::EventArgs&) __asm__("_ZN8CConsole12handleSubmitERKN5CEGUI9EventArgsE");
extern "C" void ncNewNoHistory(CConsole*,std::wstring) __asm__("_ZN8CConsole16addTextNoHistoryESbIwSt11char_traitsIwESaIwEE");
extern "C" void ncNewText(CConsole*,std::wstring) __asm__("_ZN8CConsole7addTextESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(ncAsync,"_Z16GetAsyncKeyStatej")
TL_FUNCTION(ncKeyHook,"_ZN8CConsole13handleKeyDownERKN5CEGUI9EventArgsE")
TL_FUNCTION(ncCloseHook,"_ZN8CConsole11handleCloseERKN5CEGUI9EventArgsE")
TL_FUNCTION(ncSubmitHook,"_ZN8CConsole12handleSubmitERKN5CEGUI9EventArgsE")
namespace {
struct Locale {std::string previous;Locale():previous(std::setlocale(LC_CTYPE,NULL)){if(!std::setlocale(LC_CTYPE,"C.UTF-8"))std::abort();}~Locale(){std::setlocale(LC_CTYPE,previous.c_str());}};
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;unsigned tab,keys,closes,submits;
void num(unsigned n){output->add(&n,4);}
short async(unsigned key){num(key);return tab?short(0x8000):short(0);}
bool keyHit(CConsole*,const CEGUI::EventArgs&){++keys;return true;}
bool closeHit(CConsole*,const CEGUI::EventArgs&){++closes;return true;}
bool submitHit(CConsole*,const CEGUI::EventArgs&){++submits;return true;}
void snapshot(CEGUI::Window*w){std::string s=tlheadless::snapshot(*w);num(s.size());output->add(s.data(),s.size());}
void wide(const std::wstring&s){num(s.size());output->add(s.data(),s.size()*4);}
void state(CConsole*p,menugui::Fixture&f){unsigned v[]={p->m_parentWindow==f.root,p->m_window!=NULL,p->m_inputWindow!=NULL,p->m_historyWindow!=NULL,p->m_resources==&f.resources,p->m_gameClient==f.nativeClient.client,p->m_gameUI==f.ui,unsigned(p->m_historyIndex),p->m_history.m_nCount,p->m_history.m_nCapacity,p->m_history.m_nGrowBy,p->m_logConsole};output->add(v,sizeof(v));for(unsigned i=0;i<p->m_history.size();++i)wide(p->m_history[i]);if(p->m_window)snapshot(p->m_window);}
void consoleSide(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;CStringTranslate translate(L"");settings->SetInt(KSETTINGS_RES_WIDTH,800+int(c.index)*3);settings->SetInt(KSETTINGS_RES_HEIGHT,600+int(c.index)*2);menugui::Fixture f(*settings,scene);f.root->setSize(CEGUI::UVector2(CEGUI::UDim(0,800+int(c.index)*3),CEGUI::UDim(0,600+int(c.index)*2)));
 if(c.op==0){
  menugui::ConsoleStrings strings;CConsole*p=static_cast<CConsole*>(Ogre::NedAllocImpl::allocBytes(sizeof(CConsole),0,0,0));settings->SetInt(KSETTINGS_LOG_CONSOLE,int(c.index)-4);
  typedef void(*Fn)(CConsole*,CGameUI*,CResourceManager*,CEGUI::Window*);Fn fn=ours?ncNewCtor:ncCtor;CGameUI*ui=c.index==0?NULL:f.ui;CResourceManager*resources=c.index==0?NULL:&f.resources;CEGUI::Window*parent=c.index<2?NULL:f.root;
  if(!autotest::beginInvocation(out,fn))return;fn(p,ui,resources,parent);out.callCompleted=1;state(p,f);TSafePointer<CConsole>weak;weak.setObject(p);
  // Observe all four real event slots installed by the constructor.
  if(p->m_window){detour::Set events;keys=closes=submits=0;TL_REDIRECT(events,ncKeyHook,&keyHit);TL_REDIRECT(events,ncCloseHook,&closeHit);TL_REDIRECT(events,ncSubmitHook,&submitHit);if(events.failed())std::abort();CEGUI::KeyEventArgs key(p->m_window);key.scancode=CEGUI::Key::Tab;p->m_window->fireEvent(CEGUI::Window::EventKeyDown,key);CEGUI::WindowEventArgs e(p->m_window);p->m_window->fireEvent(CEGUI::FrameWindow::EventCloseClicked,e);p->m_inputWindow->fireEvent(CEGUI::Editbox::EventTextAccepted,e);p->m_window->getChild(3u)->fireEvent(CEGUI::Window::EventActivated,e);num(keys);num(closes);num(submits);}
  ncDtor(p);num(weak.getObject()!=NULL);Ogre::NedAllocImpl::deallocBytes(p);return;
 }
 menugui::Console console(f);CConsole*p=console.p;CEGUI::Window*input=p->m_inputWindow,*history=p->m_historyWindow;const char*texts[]={"","test","  test","\t\n test","\320\242\320\265\320\272\321\201\321\202 abc","  \346\274\242\345\255\227x","\001\177", " plain ","\n\r\t","x \ty"," \302\240end","  123"};
 if(c.op==1){input->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(texts[c.index%12])));p->m_window->setVisible((c.index/12)&1);if((c.index/24)&1)p->m_inputWindow=NULL;if((c.index/48)&1)history->activate();typedef void(*Fn)(CConsole*,float);Fn fn=ours?ncNewUpdate:ncUpdate;if(!autotest::beginInvocation(out,fn))return;fn(p,c.index&1?.25f:3);out.callCompleted=1;
 }else if(c.op==2){
  unsigned count=c.index/24%3?3:0;const wchar_t*entries[]={L"first",L"Текст 漢字",L"last"};for(unsigned i=0;i<count;++i)p->m_history.add(entries[i]);int indices[]={-1,0,int(count?count-1:0),int(count)};p->m_historyIndex=indices[c.index/6%4];input->setText("before");static_cast<CEGUI::Editbox*>(input)->setCaratIndex(2);if(c.index>=72)p->m_inputWindow=NULL;CEGUI::Key::Scan scan[]={CEGUI::Key::ArrowUp,CEGUI::Key::ArrowDown,CEGUI::Key::Tab,CEGUI::Key::Return,CEGUI::Key::Escape,CEGUI::Key::A};CEGUI::KeyEventArgs e(input);e.scancode=scan[c.index%6];typedef bool(*Fn)(CConsole*,const CEGUI::EventArgs&);Fn fn=ours?ncNewKey:ncKey;if(!autotest::beginInvocation(out,fn))return;num(fn(p,e));out.callCompleted=1;
 }else if(c.op==3){
  tab=(c.index/12)&1;input->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(texts[c.index%12])));if((c.index/24)&1)p->m_inputWindow=NULL;p->m_window->setVisible((c.index/48)&1);detour::Set keyboard;TL_REDIRECT(keyboard,ncAsync,&async);if(keyboard.failed())std::abort();CEGUI::WindowEventArgs e(input);typedef bool(*Fn)(CConsole*,const CEGUI::EventArgs&);Fn fn=ours?ncNewSubmit:ncSubmit;if(!autotest::beginInvocation(out,fn))return;num(fn(p,e));out.callCompleted=1;
 }else{
  const wchar_t*lines[]={L"",L"plain",L"one\ntwo",L"\n\n",L"Текст 漢字",L"one\n",L"\ttext",L"x\ny\nz"};std::wstring text=lines[c.index%8];unsigned old[]={0,20,4995,5000};history->setText(CEGUI::String(std::string(old[c.index/8%4],'a')));p->m_history.add(L"before");p->m_historyIndex=-1;p->m_logConsole=(c.index/32)&1;if(c.index>=64)p->m_historyWindow=NULL;typedef void(*Fn)(CConsole*,std::wstring);Fn fn=c.op==4?(ours?ncNewNoHistory:ncNoHistory):(ours?ncNewText:ncText);if(!autotest::beginInvocation(out,fn))return;fn(p,text);out.callCompleted=1;
 }
 state(p,f);if(p->m_inputWindow)num(static_cast<CEGUI::Editbox*>(p->m_inputWindow)->getCaratIndex());if(p->m_historyWindow)num(static_cast<CEGUI::MultiLineEditbox*>(p->m_historyWindow)->getCaratIndex());p->m_inputWindow=input;p->m_historyWindow=history;
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned count){Locale locale;tlheadless::Environment env;env.loadGameSkin();CEGUI::SchemeManager::getSingleton().loadScheme("media/ui/WindowsLook.scheme");nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,op,name,address,&consoleSide,count);}
}
TL_TEST(complete_ui_console_ctor){return run(host,0,"complete_ui_console_ctor",0xafbee0,24);}
TL_TEST(complete_ui_console_update){return run(host,1,"complete_ui_console_update",0xaecce0,96);}
TL_TEST(complete_ui_console_key){return run(host,2,"complete_ui_console_key",0xaefbb0,96);}
TL_TEST(complete_ui_console_submit){return run(host,3,"complete_ui_console_submit",0xafbb70,96);}
TL_TEST(complete_ui_console_nohistory){return run(host,4,"complete_ui_console_nohistory",0xaf05e0,96);}
TL_TEST(complete_ui_console_addtext){return run(host,5,"complete_ui_console_addtext",0xafa8e0,96);}
