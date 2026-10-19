#include "MenuGuiFixture.h"
#include "NewGameMenu.h"
#include "DataGroup.h"
#include "FileUtilities.h"
#include "StringUtilities.h"
#include "GameVariables.h"
#include <clocale>
#include <elements/CEGUIEditbox.h>
TL_ORIGINAL(void,ngCtor,(CNewGameMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*),"_ZN12CNewGameMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_ORIGINAL(void,ngDtor,(CNewGameMenu*),"_ZN12CNewGameMenuD1Ev")
TL_ORIGINAL(void,ngBaseCreate,(CDropdownMenu*),"_ZN13CDropdownMenu11createMenusEv")
TL_ORIGINAL(void,ngCreate,(CNewGameMenu*),"_ZN12CNewGameMenu11createMenusEv")
TL_ORIGINAL(void,ngUpdate,(CNewGameMenu*,float),"_ZN12CNewGameMenu6updateEf")
TL_ORIGINAL(void,ngOpen,(CNewGameMenu*,bool),"_ZN12CNewGameMenu7setOpenEb")
TL_ORIGINAL(bool,ngClick,(CNewGameMenu*,ELayoutFunction,std::wstring),"_ZN12CNewGameMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(bool,ngSubmit,(CNewGameMenu*,const CEGUI::EventArgs&),"_ZN12CNewGameMenu16handle_SubmitPetERKN5CEGUI9EventArgsE")
TL_ORIGINAL(std::wstring,ngSave,(CNewGameMenu*,std::wstring),"_ZN12CNewGameMenu12getEmptySaveESbIwSt11char_traitsIwESaIwEE")
extern "C" void ngNewCreate(CNewGameMenu*) __asm__("_ZN12CNewGameMenu11createMenusEv");
extern "C" void ngNewUpdate(CNewGameMenu*,float) __asm__("_ZN12CNewGameMenu6updateEf");
extern "C" void ngNewOpen(CNewGameMenu*,bool) __asm__("_ZN12CNewGameMenu7setOpenEb");
extern "C" bool ngNewClick(CNewGameMenu*,ELayoutFunction,std::wstring) __asm__("_ZN12CNewGameMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE");
extern "C" bool ngNewSubmit(CNewGameMenu*,const CEGUI::EventArgs&) __asm__("_ZN12CNewGameMenu16handle_SubmitPetERKN5CEGUI9EventArgsE");
extern "C" std::wstring ngNewSave(CNewGameMenu*,std::wstring) __asm__("_ZN12CNewGameMenu12getEmptySaveESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(ngCreateHook,"_ZN12CNewGameMenu11createMenusEv")
TL_FUNCTION(ngClass,"_ZN11CGameClient16setCreationClassESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ngPet,"_ZN11CGameClient14setCreationPetESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ngRequest,"_ZN7CGameUI19requestSetGameStateE10EGameState5EMenu")
TL_FUNCTION(ngList,"_ZN10FILESYSTEM20GetFileListRecursiveERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES5_")
TL_FUNCTION(ngExists,"_ZN10FILESYSTEM10FileExistsERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ngPath,"_ZN10FILESYSTEM15GetSaveDataPathEv")
TL_FUNCTION(ngSubmitHook,"_ZN12CNewGameMenu13handle_SubmitERKN5CEGUI9EventArgsE")
TL_FUNCTION(ngSubmitPetHook,"_ZN12CNewGameMenu16handle_SubmitPetERKN5CEGUI9EventArgsE")
namespace {
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;unsigned seed,submits,pets;CGameClient*client;CGameUI*ui;
void num(unsigned n){output->add(&n,4);}void wide(const std::wstring&s){num(s.size());output->add(s.data(),s.size()*4);}
void chooseClass(CGameClient*p,std::wstring s){num(21);num(p==client);wide(s);}void choosePet(CGameClient*p,std::wstring s){num(22);num(p==client);wide(s);}void request(CGameUI*p,EGameState state,EMenu menu){num(23);num(p==ui);num(state);num(menu);}
std::wstring savePath(){num(24);return L"/ui-proof/save/";}
void list(const std::wstring&path,TArrayList<std::wstring>&files,const std::wstring&pattern){num(25);wide(path);wide(pattern);num(files.m_nGrowBy);const wchar_t*names[][6]={{NULL},{L"0.svt",NULL},{L"2.svt",L"0.svt",L"1.svt",NULL},{L"4.svt",L"0.svt",L"2.svt",NULL},{L"0.svt",L"0.svt",L"1.svt",NULL},{L"abc.svt",L"-1.svt",L"10.svt",NULL},{L"a",L".svt",L"7.svt",NULL},{L"3.svt",L"1.svt",L"0.svt",L"2.svt",NULL}};unsigned profile=seed%8;for(unsigned i=0;names[profile][i];++i)files.add(i&1?std::wstring(names[profile][i]):std::wstring(L"/ui-proof/save/")+names[profile][i]);}
bool exists(const std::wstring&name){num(26);wide(name);int index=STRINGS::GetInt(name.substr(0,name.size()-4));unsigned profile=seed/8%4;return profile==1?index<2:profile==2?index==1||index==3:profile==3?index<4:false;}
void skip(CNewGameMenu*){}bool submitHit(CNewGameMenu*,const CEGUI::EventArgs&){++submits;return true;}bool petHit(CNewGameMenu*,const CEGUI::EventArgs&){++pets;return true;}
void snapshot(CEGUI::Window*w){std::string s=tlheadless::snapshot(*w);num(s.size());output->add(s.data(),s.size());}
struct Strings {bool n,w,e;Strings():n(false),w(false),e(false){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14dc480),8);if(!p){new(reinterpret_cast<void*>(0x14dc480))std::string;n=true;}std::memcpy(&p,reinterpret_cast<void*>(0x14dc488),8);if(!p){new(reinterpret_cast<void*>(0x14dc488))std::wstring;w=true;}std::memcpy(&p,reinterpret_cast<void*>(0x14dd9a0),8);if(!p){new(reinterpret_cast<void*>(0x14dd9a0))std::wstring(L".svt");e=true;}}~Strings(){if(e){reinterpret_cast<std::wstring*>(0x14dd9a0)->~basic_string();std::memset(reinterpret_cast<void*>(0x14dd9a0),0,8);}if(w){reinterpret_cast<std::wstring*>(0x14dc488)->~basic_string();std::memset(reinterpret_cast<void*>(0x14dc488),0,8);}if(n){reinterpret_cast<std::string*>(0x14dc480)->~basic_string();std::memset(reinterpret_cast<void*>(0x14dc480),0,8);}}};
struct Menu {Strings strings;CNewGameMenu*p;explicit Menu(menugui::Fixture&f){p=static_cast<CNewGameMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(CNewGameMenu),0,0,0));detour::Set setup;TL_REDIRECT(setup,mgDropdownCreate,&menugui::skipDropdown);TL_REDIRECT(setup,ngCreateHook,&skip);if(setup.failed())std::abort();ngCtor(p,*f.ui,*settings,f.nativeClient.scenes[0],f.root,&f.resources);}~Menu(){if(p->m_pUnknown18)CEGUI::WindowManager::getSingleton().destroyWindow(static_cast<CEGUI::Window*>(p->m_pUnknown18));ngDtor(p);Ogre::NedAllocImpl::deallocBytes(p);}};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;settings->SetInt(KSETTINGS_RES_WIDTH,800+int(seed%12)*80);settings->SetInt(KSETTINGS_RES_HEIGHT,600+int(seed%7)*30);CStringTranslate translate(L"");menugui::Fixture f(*settings,scene);client=f.nativeClient.client;ui=f.ui;Menu menu(f);CNewGameMenu*p=menu.p;ngBaseCreate(p);
 if(c.op==0){typedef void(*Fn)(CNewGameMenu*);Fn fn=ours?ngNewCreate:ngCreate;if(!autotest::beginInvocation(out,fn))return;fn(p);out.callCompleted=1;snapshot(static_cast<CEGUI::Window*>(p->m_pUnknown18));CEGUI::Window*root=static_cast<CEGUI::Window*>(p->m_pUnknown18);unsigned fields[]={p->m_iUnknownC8==root->recursiveChildSearch("CreatePlayer"),p->m_pUnknownD0==root->recursiveChildSearch("EditBox"),p->m_pUnknownD8==root->recursiveChildSearch("EditBoxPet"),p->m_iUnknownE0==root->recursiveChildSearch("CharacterClass"),p->m_iUnknownE8==root->recursiveChildSearch("CharacterClassDescription"),p->m_iUnknownF0==root->recursiveChildSearch("Back")};out.add(fields,sizeof(fields));detour::Set events;submits=pets=0;TL_REDIRECT(events,ngSubmitHook,&submitHit);TL_REDIRECT(events,ngSubmitPetHook,&petHit);if(events.failed())std::abort();CEGUI::WindowEventArgs e(root);p->m_pUnknownD0->fireEvent(CEGUI::Editbox::EventTextAccepted,e);p->m_pUnknownD8->fireEvent(CEGUI::Editbox::EventTextAccepted,e);num(submits);num(pets);return;}
 detour::Set collaborators;TL_REDIRECT(collaborators,ngClass,&chooseClass);TL_REDIRECT(collaborators,ngPet,&choosePet);TL_REDIRECT(collaborators,ngRequest,&request);TL_REDIRECT(collaborators,ngList,&list);TL_REDIRECT(collaborators,ngExists,&exists);TL_REDIRECT(collaborators,ngPath,&savePath);if(collaborators.failed())std::abort();
 if(c.op==1){const wchar_t*names[]={L"",L"Hero",L"Герой 漢字"};typedef std::wstring(*Fn)(CNewGameMenu*,std::wstring);Fn fn=ours?ngNewSave:ngSave;if(!autotest::beginInvocation(out,fn))return;wide(fn(p,names[seed/32%3]));out.callCompleted=1;return;}
 ngCreate(p);p->m_bUnknown30=(seed/8)&1;p->m_bUnknown31=(seed/16)&1;p->m_bUnknownF8=(seed/32)&1;if(p->m_bUnknown30)f.root->addChildWindow(static_cast<CEGUI::Window*>(p->m_pUnknown18));const char*names[]={"","Hero","\320\223\320\265\321\200\320\276\320\271", "\346\274\242\345\255\227"};p->m_pUnknownD0->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(names[seed%4])));p->m_pUnknownD8->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(names[seed/4%4])));p->m_iUnknownF0->setVisible(seed&1);ui->m_text16C0=L"before-save";ui->m_name16B0=L"before-name";ui->m_name16B8=L"before-pet";
 if(c.op==2){int functions[]={7,14,87,88,89,2,0,94};const wchar_t*values[]={L"Destroyer",L"Cat",L"Герой",L""};typedef bool(*Fn)(CNewGameMenu*,ELayoutFunction,std::wstring);Fn fn=ours?ngNewClick:ngClick;if(!autotest::beginInvocation(out,fn))return;num(fn(p,static_cast<ELayoutFunction>(functions[seed%8]),values[seed/8%4]));out.callCompleted=1;
 }else if(c.op==3){CEGUI::WindowEventArgs e(p->m_pUnknownD8);typedef bool(*Fn)(CNewGameMenu*,const CEGUI::EventArgs&);Fn fn=ours?ngNewSubmit:ngSubmit;if(!autotest::beginInvocation(out,fn))return;num(fn(p,e));out.callCompleted=1;
 }else if(c.op==4){typedef void(*Fn)(CNewGameMenu*,bool);Fn fn=ours?ngNewOpen:ngOpen;if(!autotest::beginInvocation(out,fn))return;fn(p,seed&1);out.callCompleted=1;
 }else{
 CDataGroup group(L"CHARACTER",NULL,3,1,NULL);group.SetDataValue(L"DISPLAYNAME",seed&4?L"Warrior":L"Воин 漢字",false);group.SetDataValue(L"DESCRIPTION",seed&8?L"Description":L"Описание",false);CPlayer*player=nativegame::createPlayer(&f.resources);CDataGroup*previousData=player->m_pDataGroup;player->m_pDataGroup=&group;player->m_sName=seed&2?L"Warrior":L"Воин 漢字";ui->m_pCharacter=seed%5?player:NULL;p->m_iUnknownE0->setText(seed&1?CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(STRINGS::StringConvertToUTF8(player->getName()).c_str())):CEGUI::String("before"));p->m_iUnknownE8->setText("before-description");typedef void(*Fn)(CNewGameMenu*,float);Fn fn=ours?ngNewUpdate:ngUpdate;if(!autotest::beginInvocation(out,fn))return;fn(p,seed&1?.25f:7);out.callCompleted=1;ui->m_pCharacter=NULL;player->m_pDataGroup=previousData;nativegame::destroyPlayer(player);
 }
 snapshot(static_cast<CEGUI::Window*>(p->m_pUnknown18));num(p->m_bUnknown30);num(p->m_bUnknown31);wide(ui->m_text16C0);wide(ui->m_name16B0);wide(ui->m_name16B8);
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned count){std::string old=std::setlocale(LC_CTYPE,NULL);if(!std::setlocale(LC_CTYPE,"C.UTF-8"))return 1;int result;{tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;result=smallmass::run(host,op,name,address,&side,count);}std::setlocale(LC_CTYPE,old.c_str());return result;}
}
TL_TEST(complete_ui_newgame_create){return run(host,0,"complete_ui_newgame_create",0xc5d730,24);}
TL_TEST(complete_ui_newgame_save){return run(host,1,"complete_ui_newgame_save",0xc5b950,96);}
TL_TEST(complete_ui_newgame_click){return run(host,2,"complete_ui_newgame_click",0xc5c040,128);}
TL_TEST(complete_ui_newgame_submit){return run(host,3,"complete_ui_newgame_submit",0xc5c2f0,96);}
TL_TEST(complete_ui_newgame_open){return run(host,4,"complete_ui_newgame_open",0xc5c5a0,64);}
TL_TEST(complete_ui_newgame_update){return run(host,5,"complete_ui_newgame_update",0xc5cc30,96);}
