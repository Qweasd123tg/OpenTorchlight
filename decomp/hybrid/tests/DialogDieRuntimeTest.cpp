#include "MenuQuestWorld.h"
#include "MenuModelGpuBoundary.h"
#include "DialogMenu.h"
#include "DieMenu.h"
#include "GameVariables.h"
#include <OgreLogManager.h>
#include <clocale>
typedef char ddPlayerSize[sizeof(CPlayer)==0xa70?1:-1];
typedef char ddSaveOnDeathOffset[__builtin_offsetof(CPlayer,m_saveOnDeath)==0xa15?1:-1];
TL_ORIGINAL(void,ddDialogCtor,(CDialogMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*),"_ZN11CDialogMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_ORIGINAL(void,ddDieCtor,(CDieMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*),"_ZN8CDieMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_ORIGINAL(void,ddDialogDtor,(CDialogMenu*),"_ZN11CDialogMenuD1Ev")
TL_ORIGINAL(void,ddDieDtor,(CDieMenu*),"_ZN8CDieMenuD1Ev")
TL_ORIGINAL(void,ddBaseCreate,(CDropdownMenu*),"_ZN13CDropdownMenu11createMenusEv")
TL_ORIGINAL(void,ddDialogCreate,(CDialogMenu*),"_ZN11CDialogMenu11createMenusEv")
TL_ORIGINAL(void,ddDieCreate,(CDieMenu*),"_ZN8CDieMenu11createMenusEv")
TL_ORIGINAL(void,ddNPC,(CDialogMenu*,CCharacter*),"_ZN11CDialogMenu6setNPCEP10CCharacter")
TL_ORIGINAL(void,ddOpen,(CDieMenu*,bool),"_ZN8CDieMenu7setOpenEb")
extern "C" void ddNewDialogCreate(CDialogMenu*) __asm__("_ZN11CDialogMenu11createMenusEv");
extern "C" void ddNewDieCreate(CDieMenu*) __asm__("_ZN8CDieMenu11createMenusEv");
extern "C" void ddNewNPC(CDialogMenu*,CCharacter*) __asm__("_ZN11CDialogMenu6setNPCEP10CCharacter");
extern "C" void ddNewOpen(CDieMenu*,bool) __asm__("_ZN8CDieMenu7setOpenEb");
TL_FUNCTION(ddDialogCreateHook,"_ZN11CDialogMenu11createMenusEv")
TL_FUNCTION(ddDieCreateHook,"_ZN8CDieMenu11createMenusEv")
TL_FUNCTION(ddDialogs,"_ZN13CQuestManager16getDialogsForNPCER10TArrayListIP12CQuestDialogEP9CBaseUnitb")
TL_FUNCTION(ddText,"_ZN12CQuestDialog9getDialogEb")
TL_FUNCTION(ddDetails,"_ZN6CQuest15getQuestDetailsEv")
extern "C" void ddLog(Ogre::LogManager*,const std::string&,Ogre::LogMessageLevel,bool) __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
TL_FUNCTION(ddInteractive,"_ZN7CGameUI25setInteractiveMenuVisibleEb")
TL_FUNCTION(ddExperience,"_ZN22CMasterResourceManager14experienceGateEi")
TL_FUNCTION(ddFame,"_ZN22CMasterResourceManager8fameGateEi")
namespace {
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;menugui::Fixture*fixture;menugui::QuestWorld*world;CPlayer*npc;CQuest*quest;CQuestDialog*dialog;CQuestDialog*prior;unsigned seed,zCalls;
void num(unsigned n){output->add(&n,4);}void bytes(const std::string&s){num(s.size());output->add(s.data(),s.size());}void wide(const std::wstring&s){num(s.size());output->add(s.data(),s.size()*4);}void snapshot(CEGUI::Window*w){bytes(tlheadless::snapshot(*w));}
void skipDialog(CDialogMenu*){}void skipDie(CDieMenu*){}
void dialogs(CQuestManager*p,TArrayList<CQuestDialog*>&list,CBaseUnit*unit,bool retry){num(10);num(p==world->manager);num(unit==npc);num(unit==NULL);num(retry);num(list.size());num(list.m_nGrowBy);switch(seed/6%4){case 1:list.add(NULL);break;case 2:list.add(dialog);break;case 3:list.add(dialog);list.add(prior);break;}}
std::wstring text(unsigned profile){switch(profile%4){case 0:return L"";case 1:return L"dialog text";case 2:return L"Квест 漢字 Ω";default:return std::wstring(L"before\0after",12);}}
std::wstring dialogText(CQuestDialog*p,bool random){num(11);num(p==dialog);num(random);return text(seed/192);}
std::wstring details(CQuest*p){num(12);num(p==quest);return L"details "+text(seed/192);}
void log(Ogre::LogManager*p,const std::string&s,Ogre::LogMessageLevel level,bool debug){num(13);num(p==Ogre::LogManager::getSingletonPtr());bytes(s);num(level);num(debug);}
void interactive(CGameUI*p,bool visible){num(14);num(p==fixture->ui);num(visible);}
int experience(CMasterResourceManager*p,int level){num(15);num(p==CMasterResourceManager::getSingleton());num(level);const unsigned values[]={0,1,0x7fffffff,0x80000000,0xffffffff,101};return static_cast<int>(values[(static_cast<unsigned>(level)+seed/32)%6]);}
int fame(CMasterResourceManager*p,int level){num(16);num(p==CMasterResourceManager::getSingleton());num(level);const unsigned values[]={0xffffffff,101,0,0x80000000,1,0x7fffffff};return static_cast<int>(values[(static_cast<unsigned>(level)+seed/16)%6]);}
bool changed(const CEGUI::EventArgs&){++zCalls;return false;}
struct Strings {uintptr_t n,w;bool ownN,ownW;Strings(uintptr_t narrow,uintptr_t wide):n(narrow),w(wide),ownN(false),ownW(false){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(n),8);if(!p){new(reinterpret_cast<void*>(n))std::string;ownN=true;}std::memcpy(&p,reinterpret_cast<void*>(w),8);if(!p){new(reinterpret_cast<void*>(w))std::wstring;ownW=true;}}~Strings(){if(ownW){reinterpret_cast<std::wstring*>(w)->~basic_string();std::memset(reinterpret_cast<void*>(w),0,8);}if(ownN){reinterpret_cast<std::string*>(n)->~basic_string();std::memset(reinterpret_cast<void*>(n),0,8);}}};
struct Menu {
 Strings strings;CDropdownMenu*p;bool isDialog;
 Menu(menugui::Fixture&f,bool d):strings(d?0x14bd5c0:0x14beb20,d?0x14bd5c8:0x14beb28),p(NULL),isDialog(d){detour::Set setup;TL_REDIRECT(setup,mgDropdownCreate,&menugui::skipDropdown);TL_REDIRECT(setup,mgTitle,&menugui::skipTitle);TL_REDIRECT(setup,ddDialogCreateHook,&skipDialog);TL_REDIRECT(setup,ddDieCreateHook,&skipDie);if(setup.failed())std::abort();if(d){CDialogMenu*q=static_cast<CDialogMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(CDialogMenu),0,0,0));ddDialogCtor(q,*f.ui,*settings,f.nativeClient.scenes[0],f.root,&f.resources);p=q;}else{CDieMenu*q=static_cast<CDieMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(CDieMenu),0,0,0));ddDieCtor(q,*f.ui,*settings,f.nativeClient.scenes[0],f.root,&f.resources);p=q;}}
 ~Menu(){if(p->m_pUnknown18)CEGUI::WindowManager::getSingleton().destroyWindow(static_cast<CEGUI::Window*>(p->m_pUnknown18));if(isDialog)ddDialogDtor(static_cast<CDialogMenu*>(p));else ddDieDtor(static_cast<CDieMenu*>(p));Ogre::NedAllocImpl::deallocBytes(p);}
};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;settings->SetFloat(KSETTINGS_YRATIO,.5f+float(seed%3)*.25f);settings->SetInt(KSETTINGS_RES_WIDTH,800+int(seed%12)*80);settings->SetInt(KSETTINGS_RES_HEIGHT,600+int(seed%7)*30);CStringTranslate translate(L"");menugui::ModelGpuBoundary gpu;menugui::Fixture f(*settings,scene);fixture=&f;Menu menu(f,c.op<2);CDropdownMenu*base=menu.p;ddBaseCreate(base);CEGUI::Window*root=static_cast<CEGUI::Window*>(base->m_pUnknown18);
 if(c.op==0){CDialogMenu*p=static_cast<CDialogMenu*>(base);typedef void(*Fn)(CDialogMenu*);Fn fn=ours?ddNewDialogCreate:ddDialogCreate;if(!autotest::beginInvocation(out,fn))return;fn(p);out.callCompleted=1;num(p->m_promptWindow==root->recursiveChildSearch("Ok"));num(p->m_acceptWindow==root->recursiveChildSearch("Accept"));num(p->m_declineWindow==root->recursiveChildSearch("Decline"));num(p->m_extraWindow==root->recursiveChildSearch("DialogText"));num(p->m_iUnknown50==root->recursiveChildSearch("Title"));snapshot(root);
 }else if(c.op==1){CDialogMenu*p=static_cast<CDialogMenu*>(base);ddDialogCreate(p);menugui::QuestWorld graph(f);world=&graph;npc=nativegame::createPlayer(&f.resources);npc->m_sName=L"speaker "+text(seed/192);quest=graph.add(L"Quest",L"text");CQuest*old=graph.add(L"Previous",L"prior");dialog=quest->m_pQuestDialog;prior=old->m_pQuestDialog;dialog->m_iDialogType=seed%6;prior->m_iDialogType=1;p->m_speaker=graph.player;p->m_dialogOwner=prior;p->m_extraWindow->setText(seed&1?"before":"old");CEGUI::Window*ok=p->m_promptWindow,*accept=p->m_acceptWindow,*decline=p->m_declineWindow;ok->setVisible(seed&1);accept->setVisible(seed&2);decline->setVisible(seed&4);unsigned mask=seed/24%8;if(mask&1)p->m_promptWindow=NULL;if(mask&2)p->m_acceptWindow=NULL;if(mask&4)p->m_declineWindow=NULL;CCharacter*input=mask&&(seed&1)?NULL:npc;
  detour::Set calls;TL_REDIRECT(calls,ddDialogs,&dialogs);TL_REDIRECT(calls,ddText,&dialogText);TL_REDIRECT(calls,ddDetails,&details);calls.redirect(reinterpret_cast<char*>(&ddLog),reinterpret_cast<char*>(&ddLog),&log);if(calls.failed())std::abort();typedef void(*Fn)(CDialogMenu*,CCharacter*);Fn fn=ours?ddNewNPC:ddNPC;if(!autotest::beginInvocation(out,fn))return;fn(p,input);out.callCompleted=1;num(p->m_speaker==input);num(p->m_dialogOwner==dialog);num(p->m_dialogOwner==NULL);snapshot(root);p->m_promptWindow=ok;p->m_acceptWindow=accept;p->m_declineWindow=decline;p->m_dialogOwner=NULL;p->m_speaker=NULL;nativegame::destroyPlayer(npc);
 }else if(c.op==2){CDieMenu*p=static_cast<CDieMenu*>(base);typedef void(*Fn)(CDieMenu*);Fn fn=ours?ddNewDieCreate:ddDieCreate;if(!autotest::beginInvocation(out,fn))return;fn(p);out.callCompleted=1;const char*names[]={"Resurrect1","Resurrect2","Resurrect3","Choice1","Choice2","Choice3"};CEGUI::Window*windows[]={p->m_windowC8,p->m_windowD0,p->m_windowD8,p->m_windowE0,p->m_windowE8,p->m_windowF0};for(unsigned i=0;i<6;++i)num(windows[i]==root->recursiveChildSearch(names[i]));num(p->m_iUnknown50==root->recursiveChildSearch("Title"));snapshot(root);
 }else{CDieMenu*p=static_cast<CDieMenu*>(base);ddDieCreate(p);CPlayer*player=nativegame::createPlayer(&f.resources);f.nativeClient.client->m_pPlayer=player;const unsigned levels[]={0,1,2,0x80000000,0xffffffff,27};const int gold[]={0,9,10,-9,0x7fffffff,static_cast<int>(0x80000000)};player->m_iUnitLevel=levels[seed/32%6];player->m_fameLevel=static_cast<int>(levels[seed/16%6]);player->m_iGold=gold[seed/8%6];player->m_saveOnDeath=seed/8&1;p->m_famePenalty=-123;p->m_experiencePenalty=456;p->m_goldPenalty=-789;p->m_bUnknown30=seed/2&1;p->m_bUnknown31=seed/4&1;static_cast<CEGUI::Window*>(p->m_pUnknown20)->setPosition(CEGUI::UVector2(CEGUI::UDim(.2f,31),CEGUI::UDim(.7f,-15)));if(seed/16&1)f.root->addChildWindow(root);f.root->addChildWindow(CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","sibling"));root->setZOrderingEnabled(seed/64%3!=0);root->subscribeEvent(CEGUI::String("ZChanged"),CEGUI::Event::Subscriber(&changed));zCalls=0;if(!(seed&1)&&seed>=192)f.nativeClient.client->m_pPlayer=NULL;
  detour::Set calls;TL_REDIRECT(calls,ddInteractive,&interactive);TL_REDIRECT(calls,ddExperience,&experience);TL_REDIRECT(calls,ddFame,&fame);if(calls.failed())std::abort();typedef void(*Fn)(CDieMenu*,bool);Fn fn=ours?ddNewOpen:ddOpen;if(!autotest::beginInvocation(out,fn))return;fn(p,seed&1);out.callCompleted=1;num(p->m_bUnknown30);num(p->m_bUnknown31);num(p->m_famePenalty);num(p->m_experiencePenalty);num(p->m_goldPenalty);num(root->getParent()==f.root);num(zCalls);snapshot(root);snapshot(f.root);f.nativeClient.client->m_pPlayer=NULL;nativegame::destroyPlayer(player);
 }
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned count){std::string old=std::setlocale(LC_CTYPE,NULL);if(!std::setlocale(LC_CTYPE,"C.UTF-8"))return 1;int result;{tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;result=smallmass::run(host,op,name,address,&side,count);}std::setlocale(LC_CTYPE,old.c_str());return result;}
}
TL_TEST(complete_ui_dialog_create){return run(host,0,"complete_ui_dialog_create",0xb05390,24);}
TL_TEST(complete_ui_dialog_npc){return run(host,1,"complete_ui_dialog_npc",0xb04b00,768);}
TL_TEST(complete_ui_die_create){return run(host,2,"complete_ui_die_create",0xb0f540,24);}
TL_TEST(complete_ui_die_open){return run(host,3,"complete_ui_die_open",0xb0dbd0,384);}
