#include "AutoTest.h"
#include "tests/Detour.h"
#include "GameMainRuntime.h"
#include "MainFileSandbox.h"
#include "Game.h"
#include "SDL.h"
extern "C" void SDL_VideoQuit();
#include "Editor.h"
#include "CmdLineParser.h"
#include <OgreMemoryAllocatorConfig.h>
extern unsigned int KSETTINGS_RESTARTING;
extern unsigned int KSETTINGS_IGNORE_STEAM_CLOUD;
TL_ORIGINAL(int,entryOriginal,(int,char**),"main")
extern "C" int entryCandidate(int,char**) __asm__("main");
TL_ORIGINAL(void,entrySettingsCtor,(CSettings*,std::wstring,std::wstring,std::wstring,std::wstring),"_ZN9CSettingsC1ESbIwSt11char_traitsIwESaIwEES3_S3_S3_")
TL_ORIGINAL(void,entrySettingsDtor,(CSettings*),"_ZN9CSettingsD1Ev")
TL_FUNCTION(entryInit,"_ZN10LinuxUtils4InitEv")
TL_FUNCTION(entryEditor,"_ZN7CEditor12getSingletonEv")
TL_FUNCTION(entrySettings,"_Z14createSettingsRKSsRb")
TL_FUNCTION(entryBegin,"_ZN5CGame5beginEPv")
TL_FUNCTION(entryGetSettings,"_ZN5CGame11getSettingsEv")
TL_FUNCTION(entrySave,"_ZN20CDynamicPropertyFile12SaveSettingsERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(entryActivate,"_Z22ActivateRestartProcessP5CGame")
TL_FUNCTION(entryFinish,"_Z22DoRestartProcessFinishb")
TL_FUNCTION(entryWait,"_Z28WaitForPreviousProcessFinishv")
TL_FUNCTION(entryMessage,"_Z10MessageBoxPvPKwS1_i")
namespace {
struct Case{unsigned mode,flags,args;};const Case*current;autotest::Capture*cap;CSettings*settingsTemplate;
void word(unsigned x){cap->add(&x,sizeof(x));}
void init(){word(1);}CEditor* editor(){word(2);return NULL;}
CSettings*settings(const std::string& line,bool& first){word(3);cap->addText(line);word(first);first=current->flags&1;return settingsTemplate;}
bool save(CDynamicPropertyFile*s,const std::wstring&name){word(4);word(s==settingsTemplate);cap->addText(name);word(settingsTemplate->GetInt(KSETTINGS_RESTARTING));return true;}
long begin(CGame*g,void*window){word(5);word(window==reinterpret_cast<void*>(0xdeadbeef));word(g->m_settings==settingsTemplate);word(settingsTemplate->GetInt(KSETTINGS_RESTARTING));word(settingsTemplate->GetInt(KSETTINGS_FULLSCREEN));g->m_requestRestart=current->mode==4||current->mode==5;return current->mode==1||current->mode==6?-1L:current->mode==2?0x80004005u:current->mode==3?-4294967296L:0L;}
CSettings*nullSettings(CGame*){word(6);return NULL;}
bool activate(CGame*g){word(7);word(g->m_settings==settingsTemplate);return current->mode!=5;}
void finish(bool restart){word(8);word(restart);}bool wait(){word(9);return false;}
int message(void*window,const wchar_t*text,const wchar_t*title,int flags){word(10);word(window!=NULL);cap->addText(std::wstring(text));cap->addText(std::wstring(title));word(flags);return 1;}
int video(const char*driver){word(11);word(driver!=NULL);return 0;}int displays(){word(12);return 0;}
int desktop(int index,SDL_DisplayMode*m){word(13);word(index);std::memset(m,0,sizeof(*m));m->w=1280;m->h=720;return 0;}
void videoQuit(){word(14);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);current=&c;cap=&out;mainfiles::Sandbox s;
 settingsTemplate->SetInt(KSETTINGS_RESTARTING,(c.flags>>1)==0?0:(c.flags>>1)==1?1:2);settingsTemplate->SetInt(KSETTINGS_IGNORE_STEAM_CLOUD,1);
 if(c.mode==6||c.mode==8)settingsTemplate->m_pCmdLineParser->m_params[L"QUIT"].push_back(c.mode==6?L"yes":L"0");else if(c.mode==7)settingsTemplate->m_pCmdLineParser->m_params[L"QUIT"].push_back(L"");
 std::vector<std::string> strings;strings.push_back("torchlight");if(c.args){strings.push_back(c.args==1?"--restart":"--test");strings.push_back("abc д");if(c.args==2){strings.push_back("");strings.push_back("--restart");}}
 std::vector<char*> args;for(unsigned i=0;i<strings.size();++i)args.push_back(const_cast<char*>(strings[i].c_str()));args.push_back(NULL);
 detour::Set d;TL_REDIRECT(d,entryInit,&init);TL_REDIRECT(d,entryEditor,&editor);TL_REDIRECT(d,entrySettings,&settings);TL_REDIRECT(d,entryBegin,&begin);TL_REDIRECT(d,entrySave,&save);TL_REDIRECT(d,entryActivate,&activate);TL_REDIRECT(d,entryFinish,&finish);TL_REDIRECT(d,entryWait,&wait);TL_REDIRECT(d,entryMessage,&message);if(c.mode==9)TL_REDIRECT(d,entryGetSettings,&nullSettings);
 d.redirect(reinterpret_cast<char*>(&SDL_VideoInit),reinterpret_cast<char*>(&SDL_VideoInit),&video);d.redirect(reinterpret_cast<char*>(&SDL_GetNumVideoDisplays),reinterpret_cast<char*>(&SDL_GetNumVideoDisplays),&displays);d.redirect(reinterpret_cast<char*>(&SDL_GetDesktopDisplayMode),reinterpret_cast<char*>(&SDL_GetDesktopDisplayMode),&desktop);d.redirect(reinterpret_cast<char*>(&SDL_VideoQuit),reinterpret_cast<char*>(&SDL_VideoQuit),&videoQuit);if(d.failed())_exit(64);
 int(*fn)(int,char**)=ours?entryCandidate:entryOriginal;if(autotest::beginInvocation(out,fn)){int result=fn(strings.size(),&args[0]);out.callCompleted=1;out.add(&result,sizeof(result));}mainfiles::capture(out,s.base,".runicgames");d.restore();
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_main_entry){settingsTemplate=static_cast<CSettings*>(Ogre::NedAllocImpl::allocBytes(sizeof(CSettings),0,0,0));entrySettingsCtor(settingsTemplate,L"",L"",L"",L"");autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_main_entry",reinterpret_cast<uintptr_t>(&entryOriginal));for(unsigned mode=0;mode<10;++mode)for(unsigned flags=0;flags<6;++flags)for(unsigned args=0;args<3;++args){Case c={mode,flags,args};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_main_entry",cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);entrySettingsDtor(settingsTemplate);Ogre::NedAllocImpl::deallocBytes(settingsTemplate);return failures+stats.incomplete+(coverage.completed!=cases);}
