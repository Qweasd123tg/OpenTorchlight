#include "MenuGuiFixture.h"
#include "MenuModelGpuBoundary.h"
#include "SettingsMenu.h"
#include "GameVariables.h"
#include <clocale>
#include <limits>
#include <elements/CEGUICheckbox.h>
#include <elements/CEGUICombobox.h>
#include <elements/CEGUIComboDropList.h>
#include <elements/CEGUIListboxTextItem.h>
#include <elements/CEGUISlider.h>
TL_ORIGINAL(void,seCtor,(CSettingsMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*),"_ZN13CSettingsMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_ORIGINAL(void,seDtor,(CSettingsMenu*),"_ZN13CSettingsMenuD1Ev")
TL_ORIGINAL(void,seBaseCreate,(CDropdownMenu*),"_ZN13CDropdownMenu11createMenusEv")
TL_ORIGINAL(void,seCreate,(CSettingsMenu*),"_ZN13CSettingsMenu11createMenusEv")
TL_ORIGINAL(void,seOpen,(CSettingsMenu*,bool),"_ZN13CSettingsMenu7setOpenEb")
TL_ORIGINAL(void,seUpdate,(CSettingsMenu*,float),"_ZN13CSettingsMenu6updateEf")
extern "C" void seNewCreate(CSettingsMenu*) __asm__("_ZN13CSettingsMenu11createMenusEv");
extern "C" void seNewOpen(CSettingsMenu*,bool) __asm__("_ZN13CSettingsMenu7setOpenEb");
extern "C" void seNewUpdate(CSettingsMenu*,float) __asm__("_ZN13CSettingsMenu6updateEf");
TL_FUNCTION(seCreateHook,"_ZN13CSettingsMenu11createMenusEv")
TL_FUNCTION(seInteractive,"_ZN7CGameUI25setInteractiveMenuVisibleEb")
TL_FUNCTION(seSound,"_ZN13CSoundManager17updateAudioLevelsEffbb")
TL_FUNCTION(seSave,"_ZN20CDynamicPropertyFile12SaveSettingsERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(seReset,"_ZN11CGameClient12resetShadowsEb")
TL_FUNCTION(seClose,"_ZN7CGameUI8closeAllEv")
namespace {
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;CGameClient*client;CGameUI*ui;
void num(unsigned n){output->add(&n,4);}void fp(float f){output->add(&f,4);}void wide(const std::wstring&s){num(s.size());output->add(s.data(),s.size()*4);}
// Native bd5022 writes the existing unsigned-byte UI+12fa on the genuine UI.
unsigned restart(){return reinterpret_cast<const unsigned char*>(ui)[0x12fa];}
void interactive(CGameUI*p,bool visible){num(11);num(p==ui);num(visible);}
void audio(CSoundManager*p,float sound,float music,bool muteSound,bool muteMusic){num(12);num(p==CMasterResourceManager::getSingleton()->m_pSoundManager);fp(sound);fp(music);num(muteSound);num(muteMusic);}
bool save(CDynamicPropertyFile*p,const std::wstring&path){num(13);num(p==settings);wide(path);return true;}
void reset(CGameClient*p,bool old){num(14);num(p==client);num(old);}void close(CGameUI*p){num(15);num(p==ui);num(restart());}
void skip(CSettingsMenu*){}
struct Strings {
 bool narrow,wideString,arrays[9];
 Strings():narrow(false),wideString(false){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14d02a0),8);if(!p){new(reinterpret_cast<void*>(0x14d02a0))std::string;narrow=true;}std::memcpy(&p,reinterpret_cast<void*>(0x14d02a8),8);if(!p){new(reinterpret_cast<void*>(0x14d02a8))std::wstring;wideString=true;}const wchar_t*names[]={L"Off",L"Lighting Only",L"Low",L"Medium",L"High",L"Very High",L"Low",L"Medium",L"High"};for(unsigned i=0;i<9;++i){uintptr_t a=0x14d1480+i*8;std::memcpy(&p,reinterpret_cast<void*>(a),8);arrays[i]=!p;if(!p)new(reinterpret_cast<void*>(a))std::wstring(names[i]);}}
 ~Strings(){for(unsigned i=0;i<9;++i)if(arrays[i]){uintptr_t a=0x14d1480+i*8;reinterpret_cast<std::wstring*>(a)->~basic_string();std::memset(reinterpret_cast<void*>(a),0,8);}if(wideString){reinterpret_cast<std::wstring*>(0x14d02a8)->~basic_string();std::memset(reinterpret_cast<void*>(0x14d02a8),0,8);}if(narrow){reinterpret_cast<std::string*>(0x14d02a0)->~basic_string();std::memset(reinterpret_cast<void*>(0x14d02a0),0,8);}}
};
struct ParticleGlobals {float fps,pct;ParticleGlobals(){std::memcpy(&fps,reinterpret_cast<void*>(0x14210d4),4);std::memcpy(&pct,reinterpret_cast<void*>(0x14210d0),4);}~ParticleGlobals(){std::memcpy(reinterpret_cast<void*>(0x14210d4),&fps,4);std::memcpy(reinterpret_cast<void*>(0x14210d0),&pct,4);}void capture(){float f,p;std::memcpy(&f,reinterpret_cast<void*>(0x14210d4),4);std::memcpy(&p,reinterpret_cast<void*>(0x14210d0),4);fp(f);fp(p);}};
struct Menu {Strings strings;CSettingsMenu*p;explicit Menu(menugui::Fixture&f){p=static_cast<CSettingsMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(CSettingsMenu),0,0,0));detour::Set setup;TL_REDIRECT(setup,mgDropdownCreate,&menugui::skipDropdown);TL_REDIRECT(setup,mgTitle,&menugui::skipTitle);TL_REDIRECT(setup,seCreateHook,&skip);if(setup.failed())std::abort();seCtor(p,*f.ui,*settings,f.nativeClient.scenes[0],f.root,&f.resources);}~Menu(){if(p->m_pUnknown18)CEGUI::WindowManager::getSingleton().destroyWindow(static_cast<CEGUI::Window*>(p->m_pUnknown18));seDtor(p);Ogre::NedAllocImpl::deallocBytes(p);}};
// Full property snapshots exceed Capture's fixed 256KiB for this layout.
// A lossless exact-block dictionary retains every byte, with independent
// decode/readback checked against the original snapshot on every invocation.
void snapshot(CEGUI::Window*w){
 std::string s=tlheadless::snapshot(*w),encoded;std::map<std::string,unsigned>dictionary;
 for(size_t at=0;at<s.size();at+=16){std::string block=s.substr(at,16);std::map<std::string,unsigned>::iterator found=dictionary.find(block);unsigned code;
  if(found==dictionary.end()){code=~0u;encoded.append(reinterpret_cast<const char*>(&code),4);unsigned length=block.size();encoded.append(reinterpret_cast<const char*>(&length),4);encoded+=block;unsigned id=dictionary.size();dictionary.insert(std::make_pair(block,id));}
  else{code=found->second;encoded.append(reinterpret_cast<const char*>(&code),4);}
 }
 std::vector<std::string>blocks;std::string decoded;size_t cursor=0;
 while(cursor<encoded.size()){if(encoded.size()-cursor<4)std::abort();unsigned code;std::memcpy(&code,encoded.data()+cursor,4);cursor+=4;
  if(code==~0u){if(encoded.size()-cursor<4)std::abort();unsigned length;std::memcpy(&length,encoded.data()+cursor,4);cursor+=4;if(length>encoded.size()-cursor)std::abort();blocks.push_back(encoded.substr(cursor,length));decoded+=blocks.back();cursor+=length;}
  else{if(code>=blocks.size())std::abort();decoded+=blocks[code];}
 }
 if(decoded!=s)std::abort();num(s.size());num(encoded.size());output->add(encoded.data(),encoded.size());
}
void combo(CEGUI::Window*w){CEGUI::Combobox*p=static_cast<CEGUI::Combobox*>(w);num(p->getItemCount());num(p->getDropList()->isAutoArmEnabled());for(unsigned i=0;i<p->getItemCount();++i){CEGUI::ListboxItem*item=p->getListboxItemFromIndex(i);num(item->getID());num(item->isAutoDeleted());num(item->isSelected());const CEGUI::String&t=item->getText();num(t.length());output->add(t.c_str(),std::strlen(reinterpret_cast<const char*>(t.c_str())));CEGUI::ColourRect colors=item->getSelectionColours();num(colors.d_top_left.getARGB());num(colors.d_top_right.getARGB());num(colors.d_bottom_left.getARGB());num(colors.d_bottom_right.getARGB());}}
void fill(CEGUI::Window*w,unsigned count,int selected){CEGUI::Combobox*p=static_cast<CEGUI::Combobox*>(w);for(unsigned i=0;i<count;++i){CEGUI::ListboxTextItem*item=new CEGUI::ListboxTextItem("existing",i,NULL,false,true);item->setSelectionColours(CEGUI::colour(.25f,.5f,.75f,1));p->addItem(item);}if(count)p->setItemSelectState(static_cast<size_t>(selected%count),true);}
const unsigned*keys(unsigned&count){static unsigned list[20];unsigned i=0;list[i++]=KSETTINGS_FULLSCREEN;list[i++]=KSETTINGS_FSAA;list[i++]=KSETTINGS_RENDERBEHIND;list[i++]=KSETTINGS_RIMLIGHTS_ENABLED;list[i++]=KSETTINGS_ALLOW_HWSKINNING;list[i++]=KSETTINGS_VSYNCH;list[i++]=KSETTINGS_SOUNDMUTE;list[i++]=KSETTINGS_MUSICMUTE;list[i++]=KSETTINGS_SHOW_TIPS;list[i++]=KSETTINGS_FLOATY_NUMBERS;list[i++]=KSETTINGS_SHOW_BLOOD;list[i++]=KSETTINGS_NETBOOK_MODE;list[i++]=KSETTINGS_SHADOW_DETAIL;list[i++]=KSETTINGS_SHADOWS_ENABLED;list[i++]=KSETTINGS_LIGHTING_ENABLED;list[i++]=KSETTINGS_SHADOW_RESOLUTION;list[i++]=KSETTINGS_RES_WIDTH;list[i++]=KSETTINGS_RES_HEIGHT;count=i;return list;}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;unsigned seed=c.index;unsigned nk;const unsigned*k=keys(nk);int values[]={0,1,2,-1};for(unsigned i=0;i<nk;++i)settings->SetInt(k[i],values[(seed/(i%4+1)+i)%4]);settings->SetInt(KSETTINGS_RES_WIDTH,800+int(seed%3)*320);settings->SetInt(KSETTINGS_RES_HEIGHT,600+int(seed%3)*120);float volumes[]={0,.5f,1,1.5f};settings->SetFloat(KSETTINGS_F_SOUNDVOLUME,volumes[seed%4]);settings->SetFloat(KSETTINGS_F_MUSICVOLUME,volumes[seed/4%4]);float fps[]={19,20,25,30,35,40,45,std::numeric_limits<float>::quiet_NaN()};settings->SetFloat(KSETTINGS_F_PARTICLEFPS,fps[seed/12%8]);settings->SetFloat(KSETTINGS_F_PARTICLE_PCT,37);settings->m_resolutions.clear();if(seed%7){for(unsigned i=0;i<3;++i){CSettingsResolution r;r.width=800+int(i)*320;r.height=600+int(i)*120;settings->m_resolutions.add(r);}}
 CStringTranslate translate(L"");menugui::ModelGpuBoundary gpu;menugui::Fixture f(*settings,scene);client=f.nativeClient.client;ui=f.ui;Menu menu(f);CSettingsMenu*p=menu.p;seBaseCreate(p);
 if(c.op==0){typedef void(*Fn)(CSettingsMenu*);Fn fn=ours?seNewCreate:seCreate;if(!autotest::beginInvocation(out,fn))return;fn(p);out.callCompleted=1;snapshot(static_cast<CEGUI::Window*>(p->m_pUnknown18));combo(p->m_windowF8);combo(p->m_window100);combo(p->m_window108);CEGUI::Window*root=static_cast<CEGUI::Window*>(p->m_pUnknown18);num(p->m_iUnknown50==root->recursiveChildSearch("Title"));num(p->m_window130==root->recursiveChildSearch("ShowTips"));num(p->m_window118==root->recursiveChildSearch("SoundVolume"));num(p->m_window110==root->recursiveChildSearch("MusicVolume"));return;}
 seCreate(p);p->m_applyChanges=true;detour::Set observers;TL_REDIRECT(observers,seInteractive,&interactive);TL_REDIRECT(observers,seSound,&audio);TL_REDIRECT(observers,seSave,&save);TL_REDIRECT(observers,seReset,&reset);TL_REDIRECT(observers,seClose,&close);if(observers.failed())std::abort();ParticleGlobals globals;
 if(c.op==1){p->m_bUnknown30=(seed/2)&1;p->m_bUnknown31=(seed/4)&1;if(p->m_bUnknown30)f.root->addChildWindow(static_cast<CEGUI::Window*>(p->m_pUnknown18));if(seed&8){fill(p->m_windowF8,3,seed);fill(p->m_window100,6,seed);fill(p->m_window108,3,seed);}typedef void(*Fn)(CSettingsMenu*,bool);Fn fn=ours?seNewOpen:seOpen;if(!autotest::beginInvocation(out,fn))return;fn(p,seed&1);out.callCompleted=1;
 }else{
 unsigned mode=seed%8;p->m_bUnknown30=mode==1||mode==2;p->m_bUnknown31=mode==0||mode==1;p->m_applyChanges=mode>=4;client->m_gameState=static_cast<EGameState>(seed/32%3);
 if(seed%11)fill(p->m_windowF8,3,seed/16);fill(p->m_window100,8,seed/8%8);fill(p->m_window108,3,seed/128%3);
 CEGUI::Window*boxes[]={p->m_windowC8,p->m_windowD0,p->m_windowD8,p->m_windowE0,p->m_windowE8,p->m_windowF0,p->m_window120,p->m_window128,p->m_window130,p->m_window138,p->m_window140,p->m_window148};for(unsigned i=0;i<12;++i)static_cast<CEGUI::Checkbox*>(boxes[i])->setSelected((seed/(8u<<(i%4))+i)&1);static_cast<CEGUI::Checkbox*>(p->m_window148)->setSelected((seed/64)&1);
 static_cast<CEGUI::Slider*>(p->m_window118)->setMaxValue(2);static_cast<CEGUI::Slider*>(p->m_window118)->setCurrentValue(volumes[seed/8%4]);static_cast<CEGUI::Slider*>(p->m_window110)->setMaxValue(2);static_cast<CEGUI::Slider*>(p->m_window110)->setCurrentValue(volumes[seed/32%4]);typedef void(*Fn)(CSettingsMenu*,float);Fn fn=ours?seNewUpdate:seUpdate;if(!autotest::beginInvocation(out,fn))return;fn(p,seed&1?.25f:3);out.callCompleted=1;globals.capture();num(restart());fp(f.nativeClient.camera->m_cameras[0]->getFarClipDistance());for(unsigned i=0;i<nk;++i)num(settings->GetInt(k[i]));fp(settings->GetFloat(KSETTINGS_F_SOUNDVOLUME));fp(settings->GetFloat(KSETTINGS_F_MUSICVOLUME));fp(settings->GetFloat(KSETTINGS_F_PARTICLEFPS));fp(settings->GetFloat(KSETTINGS_F_PARTICLE_PCT));
 }
 num(p->m_bUnknown30);num(p->m_bUnknown31);num(p->m_applyChanges);snapshot(static_cast<CEGUI::Window*>(p->m_pUnknown18));combo(p->m_windowF8);combo(p->m_window100);combo(p->m_window108);
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned count){std::string old=std::setlocale(LC_CTYPE,NULL);if(!std::setlocale(LC_CTYPE,"C.UTF-8"))return 1;int result;{tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;result=smallmass::run(host,op,name,address,&side,count);}std::setlocale(LC_CTYPE,old.c_str());return result;}
}
TL_TEST(complete_ui_settings_create){return run(host,0,"complete_ui_settings_create",0xbd6ea0,32);}
TL_TEST(complete_ui_settings_open){return run(host,1,"complete_ui_settings_open",0xbd5560,192);}
TL_TEST(complete_ui_settings_update){return run(host,2,"complete_ui_settings_update",0xbd47e0,512);}
