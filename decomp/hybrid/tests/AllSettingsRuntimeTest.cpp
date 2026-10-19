#include <string>
#include <vector>
#include <map>
#include <typeinfo>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "Settings.h"
#include "GameVariables.h"
#undef protected
#undef private
TL_ORIGINAL(void,settingsOriginalCtor,(CSettings*,std::wstring,std::wstring,std::wstring,std::wstring),"_ZN9CSettingsC1ESbIwSt11char_traitsIwESaIwEES3_S3_S3_")
extern "C" void settingsRecoveredCtor(CSettings*,std::wstring,std::wstring,std::wstring,std::wstring) __asm__("_ZN9CSettingsC1ESbIwSt11char_traitsIwESaIwEES3_S3_S3_");
TL_ORIGINAL(void,settingsOriginalDtor,(CSettings*),"_ZN9CSettingsD1Ev")
extern "C" void settingsRecoveredDtor(CSettings*) __asm__("_ZN9CSettingsD1Ev");
TL_ORIGINAL(void,settingsOriginalDefaults,(CSettings*,int,int,std::string),"_ZN9CSettings13assignDefaultEiiSs")
extern "C" void settingsRecoveredDefaults(CSettings*,int,int,std::string) __asm__("_ZN9CSettings13assignDefaultEiiSs");
TL_FUNCTION(settingsDesktop,"_ZN10LinuxUtils20GetDesktopResolutionERiS0_")
TL_FUNCTION(settingsRegisterInt,"_ZN20CDynamicPropertyFile19GetIntPropertyIndexERKSbIwSt11char_traitsIwESaIwEEib")
TL_FUNCTION(settingsRegisterFloat,"_ZN20CDynamicPropertyFile21GetFloatPropertyIndexERKSbIwSt11char_traitsIwESaIwEEfb")
TL_FUNCTION(settingsRegisterString,"_ZN20CDynamicPropertyFile22GetStringPropertyIndexERKSbIwSt11char_traitsIwESaIwEES3_b")
TL_ORIGINAL(void,settingsParserDtor,(CCmdLineParser*),"_ZN14CCmdLineParserD1Ev")
namespace {
using namespace smallmass;
unsigned currentSeed;
unsigned registrationCount;
TSafePointer<CSettings>* weakSettings;
TSafePointer<CCmdLineParser>* weakParser;
unsigned registration(CDynamicPropertyFile* p,unsigned kind,const std::wstring& name,bool nonlocal){
 CSettings* settings=static_cast<CSettings*>(p);
 if(registrationCount==0){weakSettings->setObject(settings);weakParser->setObject(settings->m_pCmdLineParser);}
 number(kind);text(name);number(nonlocal);
 if(++registrationCount==currentSeed+1)throw 77;
 return registrationCount+0x12300;
}
unsigned registerInt(CDynamicPropertyFile*p,const std::wstring& name,int value,bool nonlocal){number(value);return registration(p,1,name,nonlocal);}
unsigned registerFloat(CDynamicPropertyFile*p,const std::wstring& name,float value,bool nonlocal){floating(value);return registration(p,2,name,nonlocal);}
unsigned registerString(CDynamicPropertyFile*p,const std::wstring& name,std::wstring value,bool nonlocal){text(value);return registration(p,3,name,nonlocal);}
void desktop(int& width,int& height){
 static const int widths[]={320,640,1024,1366,1920,2560,7680};
 static const int heights[]={200,480,768,1080,1440,2160};
 width=widths[(currentSeed/7)%7];height=heights[(currentSeed/11)%6];
}
template<class T> void scalarList(const std::vector<T>& v){number(v.size());for(unsigned i=0;i<v.size();++i)output->add(&v[i],sizeof(T));}
void stringList(const std::vector<std::wstring>& v){number(v.size());for(unsigned i=0;i<v.size();++i)text(v[i]);}
void indexMap(const std::map<std::wstring,unsigned>& map){number(map.size());for(std::map<std::wstring,unsigned>::const_iterator i=map.begin();i!=map.end();++i){text(i->first);number(i->second);}}
void capture(CSettings* p){
 text(std::string(typeid(*p).name()));text(p->m_directory);text(p->m_file);text(p->m_secondaryFile);text(p->m_missingString);
 scalarList(p->m_intValues);scalarList(p->m_floatValues);stringList(p->m_stringValues);stringList(p->m_nonLocalVariables);
 indexMap(p->m_intIndices);indexMap(p->m_floatIndices);indexMap(p->m_stringIndices);
 number(p->m_callbacks.size());for(unsigned i=0;i<p->m_callbacks.size();++i)number(p->m_callbacks[i].size());
 output->add(p->m_Unrecovered130,4);number(p->m_lastFileError);number(p->m_resolutions.size());number(p->m_resolutions.m_nCapacity);number(p->m_resolutions.m_nGrowBy);
 for(unsigned i=0;i<p->m_resolutions.size();++i){const CSettingsResolution&r=p->m_resolutions[i];number(r.width);number(r.height);number(r.flag8);number(r.flag9);number(r.flagA);}
 number(p->m_pCmdLineParser!=NULL);
 if(p->m_pCmdLineParser){const std::map<std::wstring,std::vector<std::wstring> >&params=p->m_pCmdLineParser->m_params;number(params.size());for(std::map<std::wstring,std::vector<std::wstring> >::const_iterator i=params.begin();i!=params.end();++i){text(i->first);stringList(i->second);}}
 number(KSETTINGS_LEVEL_SEED);
 number(KSETTINGS_OPENGL);
 number(KSETTINGS_RENDERBEHIND);
 number(KSETTINGS_FULLSCREEN);
 number(KSETTINGS_RESTART_ON_FULLSCREEN_CHANGE);
 number(KSETTINGS_RESTARTING);
 number(KSETTINGS_FLOATY_NUMBERS);
 number(KSETTINGS_F_PARTICLEFPS);
 number(KSETTINGS_F_PARTICLE_PCT);
 number(KSETTINGS_F_ANIMATION_FPS);
 number(KSETTINGS_VSYNCH);
 number(KSETTINGS_WIN_WIDTH);
 number(KSETTINGS_WIN_HEIGHT);
 number(KSETTINGS_RES_WIDTH);
 number(KSETTINGS_RES_HEIGHT);
 number(KSETTINGS_XRATIO);
 number(KSETTINGS_YRATIO);
 number(KSETTINGS_MAX_FPS);
 number(KSETTINGS_CURRENT_FPS);
 number(KSETTINGS_F_AVERAGE_FPS);
 number(KSETTINGS_MAX_PARTICLES);
 number(KSETTINGS_SHADOWS_ENABLED);
 number(KSETTINGS_SHADOW_DETAIL);
 number(KSETTINGS_RIMLIGHTS_ENABLED);
 number(KSETTINGS_LIGHTING_ENABLED);
 number(KSETTINGS_DONT_POPULATE);
 number(KSETTINGS_NO_PET);
 number(KSETTINGS_DISPLAY_PATHING);
 number(KSETTINGS_ENABLE_DSP);
 number(KSETTINGS_CONSOLE_NOPAUSE);
 number(KSETTINGS_NO_SOUNDS);
 number(KSETTINGS_SHOW_TIPS);
 number(KSETTINGS_NETBOOK_MODE);
 number(KSETTINGS_ALLOW_HWSKINNING);
 number(KSETTINGS_ALLOW_CONSOLE);
 number(KSETTINGS_GAME_COMPLETED_ONCE);
 number(KSETTINGS_RETIREE_QUEST);
 number(KSETTINGS_AI_FREEZE);
 number(KSETTINGS_PLAYER_UNTARGETABLE);
 number(KSETTINGS_DESTROY_MONSTERS_AFTER_DEATH);
 number(KSETTINGS_UPDATE_PERF);
 number(KSETTINGS_DISPLAY_STATS);
 number(KSETTINGS_COMBAT_LOG);
 number(KSETTINGS_SOUND_DEBUG);
 number(KSETTINGS_MAX_RENDER_FPS);
 number(KSETTINGS_NUM_TICKS_PER_SECOND);
 number(KSETTINGS_GAME_TYPE);
 number(KSETTINGS_S_NAME);
 number(KSETTINGS_S_PATH_RESOURCES);
 number(KSETTINGS_S_PATH_SCREENSHOTS);
 number(KSETTINGS_S_EDITOR_RESOURCES);
 number(KSETTINGS_F_PARTICLE_FALLOFF);
 number(KSETTINGS_F_FOV);
 number(KSETTINGS_F_NEARCLIP);
 number(KSETTINGS_F_FARCLIP);
 number(KSETTINGS_F_SOUNDVOLUME);
 number(KSETTINGS_F_MUSICVOLUME);
 number(KSETTINGS_SOUNDMUTE);
 number(KSETTINGS_MUSICMUTE);
 number(KSETTINGS_FSAA);
 number(KSETTINGS_SHADOW_RESOLUTION);
 number(KSETTINGS_DISPLAY_COLLISION);
 number(KSETTINGS_OVERRIDE_LIGHTING);
 number(KSETTINGS_AMBIENT_LIGHT_RED);
 number(KSETTINGS_AMBIENT_LIGHT_GREEN);
 number(KSETTINGS_AMBIENT_LIGHT_BLUE);
 number(KSETTINGS_MATERIAL_AMBIENT_LIGHT_RED);
 number(KSETTINGS_MATERIAL_AMBIENT_LIGHT_GREEN);
 number(KSETTINGS_MATERIAL_AMBIENT_LIGHT_BLUE);
 number(KSETTINGS_DIRECTIONAL_LIGHT_RED);
 number(KSETTINGS_DIRECTIONAL_LIGHT_GREEN);
 number(KSETTINGS_DIRECTIONAL_LIGHT_BLUE);
 number(KSETTINGS_F_DIRECTIONAL_INTENSITY);
 number(KSETTINGS_F_AUTOMAP_ZOOM);
 number(KSETTINGS_AUTOMAP);
 number(KSETTINGS_S_VERSION);
 number(KSETTINGS_TOGGLE_ITEM_NAME);
 number(KSETTINGS_SHOW_MISSILE_TRAILS);
 number(KSETTINGS_SHOW_DAMAGE_SHAPES);
 number(KSETTINGS_S_ZIP_LOADING);
 number(KSETTINGS_ZIP_COUNT);
 number(KSETTINGS_DEBUG_LOGIC);
 number(KSETTINGS_LOG_CONSOLE);
 number(KSETTINGS_STEAM_CLOUD);
 number(KSETTINGS_IGNORE_STEAM_CLOUD);
 number(KSETTINGS_SHOW_BLOOD);
 number(KSETTINGS_NO_CAMERASHAKE);
 number(KSETTINGS_KEYMAP_1);
 number(KSETTINGS_KEYMAP_2);
 number(KSETTINGS_KEYMAP_3);
 number(KSETTINGS_KEYMAP_4);
 number(KSETTINGS_KEYMAP_5);
 number(KSETTINGS_KEYMAP_6);
 number(KSETTINGS_KEYMAP_7);
 number(KSETTINGS_KEYMAP_8);
 number(KSETTINGS_KEYMAP_9);
 number(KSETTINGS_KEYMAP_0);
 number(KSETTINGS_FKEYMAP_1);
 number(KSETTINGS_FKEYMAP_2);
 number(KSETTINGS_FKEYMAP_3);
 number(KSETTINGS_FKEYMAP_4);
 number(KSETTINGS_FKEYMAP_5);
 number(KSETTINGS_FKEYMAP_6);
 number(KSETTINGS_FKEYMAP_7);
 number(KSETTINGS_FKEYMAP_8);
 number(KSETTINGS_FKEYMAP_9);
 number(KSETTINGS_FKEYMAP_10);
 number(KSETTINGS_FKEYMAP_11);
 number(KSETTINGS_FKEYMAP_12);
 number(KSETTINGS_KEYMAP_INVENTORY);
 number(KSETTINGS_KEYMAP_PET);
 number(KSETTINGS_KEYMAP_STATS);
 number(KSETTINGS_KEYMAP_SKILLS);
 number(KSETTINGS_KEYMAP_QUESTS);
 number(KSETTINGS_KEYMAP_JOURNAL);
 number(KSETTINGS_KEYMAP_OPTIONS);
 number(KSETTINGS_KEYMAP_PAUSE);
 number(KSETTINGS_KEYMAP_AUTOMAP);
 number(KSETTINGS_KEYMAP_AUTOMAPZOOMIN);
 number(KSETTINGS_KEYMAP_AUTOMAPZOOMOUT);
 number(KSETTINGS_KEYMAP_HOLDPOS);
 number(KSETTINGS_KEYMAP_SHOWITEMS);
 number(KSETTINGS_KEYMAP_CYCLESKILLUP);
 number(KSETTINGS_KEYMAP_CYCLESKILLDOWN);
 number(KSETTINGS_KEYMAP_SWAPSKILLS);
 number(KSETTINGS_KEYMAP_WEAPONSET);
 number(KSETTINGS_KEYMAP_CLOSEALL);
 number(KSETTINGS_KEYMAP_ZOOMIN);
 number(KSETTINGS_KEYMAP_ZOOMOUT);
 number(KSETTINGS_KEYMAP_CONSOLE_PRESS);
 number(KSETTINGS_KEYMAP_CONSOLE_HOLD);
}
void settingsSide(Case& c,bool ours,autotest::Capture& out){
 output=&out;currentSeed=c.index;
 union Storage{long double align;unsigned char bytes[sizeof(CSettings)];} storage;
 std::memset(storage.bytes,(c.index%3==0?0xa5:c.index%3==1?0x5a:0x33),sizeof(storage.bytes));
 CSettings* p=reinterpret_cast<CSettings*>(storage.bytes);
 static const wchar_t* commands[]={L"",L"-SAFEMODE=1",L"-FOO=bar -COUNT=17",L"-FOO=alpha -FOO=beta",L"-NAME=герой -BOOL=0"};
 std::wstring command=commands[c.index%5],directory=c.index&1?L"/tmp/settings/путь/":L"",file=c.index&2?L"local.ini":L"",secondary=c.index&4?L"shared.ini":L"";
 int created=g_iTotalCountOfObjects;
 if(c.op==2){
  TSafePointer<CSettings> settingsObserver;TSafePointer<CCmdLineParser> parserObserver;weakSettings=&settingsObserver;weakParser=&parserObserver;registrationCount=0;
  typedef void(*F)(CSettings*,std::wstring,std::wstring,std::wstring,std::wstring);F fn=ours?settingsRecoveredCtor:settingsOriginalCtor;
  if(!autotest::beginInvocation(out,fn))return;
  try{fn(p,command,directory,file,secondary);number(0);}catch(int value){number(value);}catch(...){number(99);}
  number(registrationCount);number(settingsObserver.getObject()==NULL);number(parserObserver.getObject()==NULL);number(g_iTotalCountOfObjects-created);
  if(parserObserver.getObject()){CCmdLineParser* parser=parserObserver.getObject();settingsParserDtor(parser);Ogre::NedAllocImpl::deallocBytes(parser);}return;
 }
 if(c.op==0){typedef void(*F)(CSettings*,std::wstring,std::wstring,std::wstring,std::wstring);F fn=ours?settingsRecoveredCtor:settingsOriginalCtor;autotest::invoke(out,fn,p,command,directory,file,secondary);}
 else{
  settingsOriginalCtor(p,command,directory,file,secondary);
  static const int resolutions[][2]={{320,200},{640,480},{800,600},{1024,768},{1280,720},{1920,1080},{2560,1440},{1366,768}};
  for(unsigned i=0;i<c.index%9;++i)p->addResolutionCombo(resolutions[i][0],resolutions[i][1],i&1,i&2,i&4);
  if(c.op==3){TSafePointer<CSettings> settingsObserver;TSafePointer<CCmdLineParser> parserObserver;settingsObserver.setObject(p);parserObserver.setObject(p->m_pCmdLineParser);typedef void(*F)(CSettings*);F fn=ours?settingsRecoveredDtor:settingsOriginalDtor;autotest::invoke(out,fn,p);number(settingsObserver.getObject()==NULL);number(settingsObserver.m_nIndex);number(parserObserver.getObject()==NULL);number(parserObserver.m_nIndex);number(p->m_pCmdLineParser==NULL);number(p->m_resolutions.m_pData==NULL);return;}
  static const int caps[]={-1,0,389,390,511,512,599,600,601,1024,2147483647};
  static const int perf[]={-1,0,300,301,999,1000,1599,1600,1799,1800,1999,2000,4000};
  static const char* renderers[]={"", "NVIDIA", "Intel GMA", "INTEL HD INTEGRATED", "gma", "other integrated", "Intel GMA INTEGRATED"};
  int capability=caps[c.index%11],performance=perf[(c.index/11)%13];std::string renderer=renderers[(c.index/143)%7];
  typedef void(*F)(CSettings*,int,int,std::string);F fn=ours?settingsRecoveredDefaults:settingsOriginalDefaults;autotest::invoke(out,fn,p,capability,performance,renderer);
 }
 number(g_iTotalCountOfObjects-created);capture(p);settingsOriginalDtor(p);
}
int runSettingsUnwind(const tlhybrid_host*host){
 smallmass::side=&settingsSide;
 for(unsigned i=0;i<131;++i){Case c={2,i};autotest::Outcome a,b;autotest::runChild(smallmass::original,&c,a);autotest::runChild(smallmass::recovered,&c,b);
  bool valid=a.status==0&&b.status==0&&a.reportValid&&b.reportValid&&a.capture.issue==0&&b.capture.issue==0&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==0xd80cf0&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget);
  bool same=valid&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
  if(!same){host->log("    expected_unwind all_settings_constructor_unwind pairs %u different %u incomplete %u; no acceptance credit\n",i+1,valid?1u:0u,valid?0u:1u);return 1;}
 }
 host->log("    expected_unwind all_settings_constructor_unwind pairs 131 different 0 incomplete 0; no acceptance credit\n");return 0;
}
}
TL_TEST(all_settings_constructor){return smallmass::run(host,0,"all_settings_constructor",0xd80cf0,&settingsSide,64);}
TL_TEST(all_settings_defaults){detour::Set hooks;TL_REDIRECT(hooks,settingsDesktop,&desktop);if(hooks.failed())return 1;return smallmass::run(host,1,"all_settings_defaults",0xd7fd30,&settingsSide,1001);}
TL_TEST(all_settings_constructor_unwind){detour::Set hooks;TL_REDIRECT(hooks,settingsRegisterInt,&registerInt);TL_REDIRECT(hooks,settingsRegisterFloat,&registerFloat);TL_REDIRECT(hooks,settingsRegisterString,&registerString);if(hooks.failed())return 1;return runSettingsUnwind(host);}
TL_TEST(all_settings_destructor){return smallmass::run(host,3,"all_settings_destructor",0xd864a0,&settingsSide,72);}
