#include <ctime>
#include <cerrno>
#include <OgreLogManager.h>
#include <map>
#define private public
#include "SDLEventHandler.h"
#undef private
#include "SystemsNativeGame.h"
#include "CmdLineParser.h"
#include "FileReader.h"
TL_ORIGINAL(void,gameCtorOriginal,(CGame*,std::string,CSettings*,bool),"_ZN5CGameC1ESsP9CSettingsb")
extern "C" void gameCtorCandidate(CGame*,std::string,CSettings*,bool) __asm__("_ZN5CGameC1ESsP9CSettingsb");
TL_FUNCTION(ctorSave,"_ZN20CDynamicPropertyFile12SaveSettingsERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ctorRead,"_ZN11CFileReader8ReadFileERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ctorLine,"_ZN11CFileReader8ReadLineEw")
TL_FUNCTION(ctorMessage,"_Z10MessageBoxPvPKwS1_i")
extern "C" void ctorLog(Ogre::LogManager*,const std::string&,Ogre::LogMessageLevel,bool) __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
extern "C" void ctorTimerReset(Ogre::Timer*) __asm__("_ZN4Ogre5Timer5resetEv");
namespace {
struct Case{unsigned mode;bool first;};const Case*current;autotest::Capture*cap;
void word(unsigned x){cap->add(&x,sizeof(x));}
int video(const char*driver){word(1);word(driver==NULL);return 0;}int displays(){word(2);return 0;}
int desktop(int n,SDL_DisplayMode*m){word(3);word(n);std::memset(m,0,sizeof(*m));m->w=1600;m->h=900;return 0;}
bool save(CSettings*s,const std::wstring&path){word(4);cap->addText(path);word(s->GetInt(KSETTINGS_FULLSCREEN));word(s->GetInt(KSETTINGS_RIMLIGHTS_ENABLED));word(s->GetInt(KSETTINGS_ALLOW_HWSKINNING));s->m_lastFileError=13;return current->mode!=2;}
bool read(CFileReader*,const std::wstring&path){word(5);cap->addText(path);return current->mode>=3;}
std::wstring line(CFileReader*,wchar_t sep){word(6);word(sep);return current->mode==3?L"":current->mode==4?L"1.27-test":L"тест-版本";}
int message(void*,const wchar_t*text,const wchar_t*title,int type){word(7);cap->addText(std::wstring(text));cap->addText(std::wstring(title));word(type);return 1;}
void log(Ogre::LogManager*,const std::string&s,Ogre::LogMessageLevel level,bool mask){word(8);cap->addText(s);word(level);word(mask);}
void reset(Ogre::Timer*){word(9);}time_t clock(time_t*p){word(10);if(p)*p=1700000000;return 1700000000;}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);current=&c;cap=&out;SystemsNativeGame native;CSettings*s=native.settings;
 s->SetInt(KSETTINGS_FULLSCREEN,1);s->SetInt(KSETTINGS_RIMLIGHTS_ENABLED,1);s->SetInt(KSETTINGS_ALLOW_HWSKINNING,1);s->SetInt(KSETTINGS_NUM_TICKS_PER_SECOND,29);s->SetInt(KSETTINGS_UPDATE_PERF,3);s->SetInt(KSETTINGS_CURRENT_FPS,4);s->SetInt(KSETTINGS_AI_FREEZE,5);s->SetInt(KSETTINGS_PLAYER_UNTARGETABLE,6);s->SetInt(KSETTINGS_DEBUG_LOGIC,7);
 if(c.mode==1||c.mode==2)s->m_pCmdLineParser->m_params[L"SAFEMODE"].push_back(L"1");*reinterpret_cast<bool*>(0x14210a4)=true;
 CGame*g=static_cast<CGame*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGame),0,0,0));std::memset(g,0xa5,sizeof(CGame));
 detour::Set d;TL_REDIRECT(d,ctorSave,&save);TL_REDIRECT(d,ctorRead,&read);TL_REDIRECT(d,ctorLine,&line);TL_REDIRECT(d,ctorMessage,&message);d.redirect(reinterpret_cast<char*>(&ctorLog),reinterpret_cast<char*>(&ctorLog),&log);d.redirect(reinterpret_cast<char*>(&ctorTimerReset),reinterpret_cast<char*>(&ctorTimerReset),&reset);d.redirect(reinterpret_cast<char*>(&SDL_VideoInit),reinterpret_cast<char*>(&SDL_VideoInit),&video);d.redirect(reinterpret_cast<char*>(&SDL_GetNumVideoDisplays),reinterpret_cast<char*>(&SDL_GetNumVideoDisplays),&displays);d.redirect(reinterpret_cast<char*>(&SDL_GetDesktopDisplayMode),reinterpret_cast<char*>(&SDL_GetDesktopDisplayMode),&desktop);d.redirect(reinterpret_cast<char*>(&std::time),reinterpret_cast<char*>(&std::time),&clock);if(d.failed())_exit(64);
 void(*fn)(CGame*,std::string,CSettings*,bool)=ours?gameCtorCandidate:gameCtorOriginal;if(autotest::beginInvocation(out,fn)){fn(g,"test",s,c.first);out.callCompleted=1;}
 word(g->m_cameraControl==NULL);word(g->m_root==NULL);word(g->m_backgroundScene==NULL);word(g->m_sceneManager==NULL);word(g->m_uiScene==NULL);word(g->m_renderBehindScene==NULL);word(g->m_renderBehindParticleScene==NULL);word(g->m_automapScene==NULL);word(g->m_viewport==NULL);word(g->m_renderWindow==NULL);word(g->m_gameClient==NULL);word(g->m_windowHandle==NULL);word(g->m_editorWindow==NULL);word(g->m_settings==s);word(g->m_soundManager==NULL);word(g->m_focused);word(g->m_disableRenderBehind);word(g->m_disableRendering);word(g->m_requestRestart);cap->addText(g->m_title);cap->addText(g->m_pluginsFile);word(g->m_masterResourceManager==NULL);word(g->m_behindMaterial.isNull());word(g->m_particleMaterial.isNull());word(g->m_renderParticles);word(g->m_frameTimes.size());word(g->m_frameTimeCount);out.add(&g->m_frameTimeSum,4);word(g->m_renderBehind);word(g->m_sdlWindow==NULL);word(g->m_eventHandler.m_gameClient==NULL);word(g->m_eventHandler.m_scanCodes.size());word(*reinterpret_cast<bool*>(0x1426408));word(*reinterpret_cast<bool*>(0x14210a4));
 const int settings[]={KSETTINGS_FULLSCREEN,KSETTINGS_RIMLIGHTS_ENABLED,KSETTINGS_ALLOW_HWSKINNING,KSETTINGS_NUM_TICKS_PER_SECOND,KSETTINGS_UPDATE_PERF,KSETTINGS_CURRENT_FPS,KSETTINGS_AI_FREEZE,KSETTINGS_PLAYER_UNTARGETABLE,KSETTINGS_DEBUG_LOGIC};for(unsigned i=0;i<9;++i)word(s->GetInt(settings[i]));cap->addText(s->GetString(KSETTINGS_S_VERSION));
 d.restore();g->m_settings=NULL;systemsGameDtor(g);Ogre::NedAllocImpl::deallocBytes(g);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_game_constructor){autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_game_constructor",reinterpret_cast<uintptr_t>(&gameCtorOriginal));for(unsigned mode=0;mode<6;++mode)for(unsigned first=0;first<2;++first){Case c={mode,first!=0};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_game_constructor",cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
