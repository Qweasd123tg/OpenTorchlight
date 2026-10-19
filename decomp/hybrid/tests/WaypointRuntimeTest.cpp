#include "AutoTest.h"
#include "HeadlessGui.h"
#define private public
#define protected public
#include "Player.h"
#include "LevelTemplateData.h"
#undef protected
#undef private
#include "StringUtilities.h"
#include "MenuGuiFixture.h"
#include "MenuModelGpuBoundary.h"
#include "WaypointMenu.h"
#include "Player.h"
#include "Equipment.h"
#include "DungeonTracker.h"
#include "DungeonManager.h"
#include "Dungeon.h"
#include "LevelTemplateData.h"
#include "GameVariables.h"
#include <clocale>
#include <ucontext.h>
#include <signal.h>
#include <execinfo.h>
#include <fcntl.h>
TL_ORIGINAL(void,wpCtor,(CWaypointMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*),"_ZN13CWaypointMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_ORIGINAL(void,wpDtor,(CWaypointMenu*),"_ZN13CWaypointMenuD1Ev")
TL_ORIGINAL(void,wpBaseCreate,(CDropdownMenu*),"_ZN13CDropdownMenu11createMenusEv")
TL_ORIGINAL(void,wpCreate,(CWaypointMenu*),"_ZN13CWaypointMenu11createMenusEv")
TL_ORIGINAL(void,wpOpen,(CWaypointMenu*,bool),"_ZN13CWaypointMenu7setOpenEb")
TL_ORIGINAL(bool,wpClick,(CWaypointMenu*,ELayoutFunction,std::wstring),"_ZN13CWaypointMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE")
extern "C" void wpNewCtor(CWaypointMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*) __asm__("_ZN13CWaypointMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager");
extern "C" void wpNewCreate(CWaypointMenu*) __asm__("_ZN13CWaypointMenu11createMenusEv");
extern "C" void wpNewOpen(CWaypointMenu*,bool) __asm__("_ZN13CWaypointMenu7setOpenEb");
extern "C" bool wpNewClick(CWaypointMenu*,ELayoutFunction,std::wstring) __asm__("_ZN13CWaypointMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(wpCreateHook,"_ZN13CWaypointMenu11createMenusEv")
TL_FUNCTION(wpOpenHook,"_ZN13CWaypointMenu7setOpenEb")
TL_FUNCTION(wpWarp,"_ZN11CGameClient10warpLevelsESbIwSt11char_traitsIwESaIwEEiibS3_b")
TL_FUNCTION(wpInteractive,"_ZN7CGameUI25setInteractiveMenuVisibleEb")
TL_FUNCTION(wpDungeon,"_ZN15CDungeonManager16getDungeonByNameESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(wpTemplate,"_ZN8CDungeon28getLevelTemplateDataForDepthEP11CGameClientj")
TL_FUNCTION(wpTemplateLoad,"_ZN18CLevelTemplateData4loadEPKw")
namespace {
unsigned phase;bool diagnosticOurs;
void fault(int signum,siginfo_t*info,void*context){int fd=open("/home/qweasd123tg/Code/левые проекты/OpenTorchlight/build-decomp/all-functions-20261018/skills/ui-rest-20261019/waypoint-signal.log",O_WRONLY|O_CREAT|O_APPEND,0600);if(fd>=0){ucontext_t*c=static_cast<ucontext_t*>(context);char line[200];int n=std::snprintf(line,sizeof(line),"signal%d side%u phase%u rip%llx address%p\n",signum,unsigned(diagnosticOurs),phase,static_cast<unsigned long long>(c->uc_mcontext.gregs[REG_RIP]),info->si_addr);write(fd,line,n);void*stack[32];int count=backtrace(stack,32);backtrace_symbols_fd(stack,count,fd);close(fd);}raise(signum);}
autotest::Capture*output;CSettings*settings;Ogre::SceneManager*scene;menugui::Fixture*fixture;CWaypointMenu*menu;CLevelTemplateData*templates[2];unsigned seed,zCalls,lookups;
void num(unsigned n){output->add(&n,4);}void wide(const std::wstring&s){num(s.size());output->add(s.data(),s.size()*4);}void bytes(const std::string&s){num(s.size());output->add(s.data(),s.size());}void snapshot(CEGUI::Window*w){
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
std::wstring label(unsigned n){switch(n%4){case 0:return L"";case 1:return L"Mines";case 2:return L"Шахта 洞穴 Ω";default:return std::wstring(L"before\0after",12);}}
void skipCreate(CWaypointMenu*){}void skipLoad(CLevelTemplateData*,const wchar_t*){}
void close(CWaypointMenu*p,bool open){num(10);num(p==menu);num(open);p->m_bUnknown30=open;}
void warp(CGameClient*p,std::wstring dungeon,int delta,int depth,bool waypoint,std::wstring entrance,bool flag){num(11);num(p==fixture->nativeClient.client);wide(dungeon);num(delta);num(depth);num(waypoint);wide(entrance);num(flag);}
void interactive(CGameUI*p,bool open){num(12);num(p==fixture->ui);num(open);}
CDungeon*dungeon(CDungeonManager*p,std::wstring name){num(13);num(p==fixture->nativeClient.dungeons);wide(name);unsigned index=lookups++;return seed/32%4==1&&index%3==0?NULL:fixture->nativeClient.dungeons->m_lDungeons[0];}
CLevelTemplateData*data(CDungeon*p,CGameClient*client,unsigned depth){num(14);num(p==fixture->nativeClient.dungeons->m_lDungeons[0]);num(client==fixture->nativeClient.client);num(depth);return templates[(depth+seed)%2];}
bool zChanged(const CEGUI::EventArgs&){++zCalls;return false;}
struct Strings {uintptr_t n,w;bool ownN,ownW;Strings(uintptr_t a,uintptr_t b):n(a),w(b),ownN(false),ownW(false){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(n),8);if(!p){new(reinterpret_cast<void*>(n))std::string;ownN=true;}std::memcpy(&p,reinterpret_cast<void*>(w),8);if(!p){new(reinterpret_cast<void*>(w))std::wstring;ownW=true;}}~Strings(){if(ownW){reinterpret_cast<std::wstring*>(w)->~basic_string();std::memset(reinterpret_cast<void*>(w),0,8);}if(ownN){reinterpret_cast<std::string*>(n)->~basic_string();std::memset(reinterpret_cast<void*>(n),0,8);}}};
struct Menu {
 Strings strings;CWaypointMenu*p;
 Menu(menugui::Fixture&f,bool construct,bool ours,autotest::Capture&out):strings(0x1533740,0x1533748),p(static_cast<CWaypointMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(CWaypointMenu),0,0,0))){
  if(construct){typedef void(*Fn)(CWaypointMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*);Fn fn=ours?wpNewCtor:wpCtor;if(!autotest::beginInvocation(out,fn))std::abort();fn(p,*f.ui,*settings,f.nativeClient.scenes[0],f.root,&f.resources);out.callCompleted=1;}
  else{detour::Set setup;TL_REDIRECT(setup,mgDropdownCreate,&menugui::skipDropdown);TL_REDIRECT(setup,mgTitle,&menugui::skipTitle);TL_REDIRECT(setup,wpCreateHook,&skipCreate);if(setup.failed())std::abort();wpCtor(p,*f.ui,*settings,f.nativeClient.scenes[0],f.root,&f.resources);setup.restore();wpBaseCreate(p);for(unsigned i=0;i<50;++i)p->m_destinationWindows[i]=p->m_floorWindows[i]=NULL;}
 }
 ~Menu(){if(p->m_pUnknown18)CEGUI::WindowManager::getSingleton().destroyWindow(static_cast<CEGUI::Window*>(p->m_pUnknown18));wpDtor(p);Ogre::NedAllocImpl::deallocBytes(p);}
};
void state(CWaypointMenu*p){num(p->m_bUnknown30);num(p->m_bUnknown31);num(p->m_bUnknown32);num(p->m_bUnknownC0);num(p->m_bUnknownC1);num(p->m_destinations.size());for(unsigned i=0;i<p->m_destinations.size();++i)wide(p->m_destinations[i]);num(p->m_floors.size());for(unsigned i=0;i<p->m_floors.size();++i)num(p->m_floors[i]);}
void bindings(CWaypointMenu*p){CEGUI::Window*root=static_cast<CEGUI::Window*>(p->m_pUnknown18);for(unsigned i=0;i<50;++i){num(p->m_destinationWindows[i]==root->recursiveChildSearch(CEGUI::String("Button"+STRINGS::GetValueAsString(i+1))));num(p->m_floorWindows[i]==root->recursiveChildSearch(CEGUI::String("Choice"+STRINGS::GetValueAsString(i+1))));}num(p->m_iUnknown50==root->recursiveChildSearch("Title"));}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 phase=1;diagnosticOurs=ours;struct sigaction action;std::memset(&action,0,sizeof(action));action.sa_sigaction=&fault;action.sa_flags=SA_SIGINFO|SA_RESETHAND;sigemptyset(&action.sa_mask);sigaction(SIGSEGV,&action,NULL);sigaction(SIGABRT,&action,NULL);
 output=&out;seed=c.index;lookups=0;settings->SetFloat(KSETTINGS_YRATIO,.5f+float(seed%3)*.25f);settings->SetInt(KSETTINGS_RES_WIDTH,800+int(seed%12)*80);settings->SetInt(KSETTINGS_RES_HEIGHT,600+int(seed%7)*30);CStringTranslate translate(L"");menugui::ModelGpuBoundary gpu;menugui::Fixture f(*settings,scene);fixture=&f;Menu holder(f,c.op==3,ours,out);CWaypointMenu*p=holder.p;menu=p;CEGUI::Window*root=static_cast<CEGUI::Window*>(p->m_pUnknown18);
 if(c.op==3){state(p);bindings(p);snapshot(root);return;}
 if(c.op==0){typedef void(*Fn)(CWaypointMenu*);Fn fn=ours?wpNewCreate:wpCreate;if(!autotest::beginInvocation(out,fn))return;fn(p);out.callCompleted=1;bindings(p);snapshot(root);return;}
 wpCreate(p);
 if(c.op==1){unsigned lengths[]={0,1,17,50};unsigned count=lengths[seed/140%4];for(unsigned i=0;i<count;++i){p->m_destinations.push_back(label(i+seed/70));p->m_floors.push_back(static_cast<int>(0x80000000u+i*29u+seed));}p->m_bUnknown30=seed/70&1;p->m_bUnknown32=seed/35&1;ELayoutFunction function=static_cast<ELayoutFunction>(seed%70-2);detour::Set calls;TL_REDIRECT(calls,wpOpenHook,&close);TL_REDIRECT(calls,wpWarp,&warp);if(calls.failed())std::abort();typedef bool(*Fn)(CWaypointMenu*,ELayoutFunction,std::wstring);Fn fn=ours?wpNewClick:wpClick;if(!autotest::beginInvocation(out,fn))return;bool result=fn(p,function,label(seed));out.callCompleted=1;num(result);state(p);return;}
 phase=10;CPlayer*player=nativegame::createPlayer(&f.resources);f.nativeClient.client->m_pPlayer=player;unsigned sizes[]={0,1,2,48,49,51};unsigned groups=seed/64%4;
 for(unsigned i=0;i<groups;++i){CDungeonTracker*t=new CDungeonTracker;t->m_name=label(seed/16+i);t->m_value8=7;t->m_rank=-3;t->m_value10=10;unsigned count=sizes[(seed/8+i)%6];for(unsigned j=0;j<count;++j)t->m_levels.push_back(j%7==0?static_cast<int>(0x7fffffff):j%11==0?-2:int(j));player->m_dungeonTrackers.add(t);}
 phase=20;Strings templateStrings(0x1495cc0,0x1495cc8);detour::Set templateSetup;TL_REDIRECT(templateSetup,wpTemplateLoad,&skipLoad);if(templateSetup.failed())std::abort();phase=21;templates[0]=new CLevelTemplateData(NULL);phase=22;templates[1]=new CLevelTemplateData(NULL);phase=23;templateSetup.restore();for(unsigned i=0;i<2;++i){templates[i]->m_showFloorNumber=i;templates[i]->m_levelName=label(seed/8+i);}
 phase=30;p->m_destinations.push_back(L"previous");p->m_destinations.push_back(L"other");p->m_floors.push_back(123);p->m_floors.push_back(-99);p->m_bUnknown30=seed/2&1;p->m_bUnknown31=seed/4&1;CEGUI::Window*saved[50];for(unsigned i=0;i<50;++i){if(seed/64%2 && !p->m_destinationWindows[i]){p->m_destinationWindows[i]=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow",CEGUI::String("extra-destination-"+STRINGS::GetValueAsString(i)));root->addChildWindow(p->m_destinationWindows[i]);if(!p->m_floorWindows[i]){p->m_floorWindows[i]=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow",CEGUI::String("extra-floor-"+STRINGS::GetValueAsString(i)));root->addChildWindow(p->m_floorWindows[i]);}}saved[i]=p->m_destinationWindows[i];if(p->m_destinationWindows[i])p->m_destinationWindows[i]->setVisible((seed+i)%2);if(p->m_floorWindows[i]){p->m_floorWindows[i]->setVisible((seed+i)%3==0);p->m_floorWindows[i]->setText("old");}if(seed/16%4==2&&i==seed%50)p->m_destinationWindows[i]=NULL;}
 static_cast<CEGUI::Window*>(p->m_pUnknown20)->setPosition(CEGUI::UVector2(CEGUI::UDim(.2f,3),CEGUI::UDim(.8f,-7)));if(seed/8&1)f.root->addChildWindow(root);f.root->addChildWindow(CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","sibling"));root->setZOrderingEnabled(seed/128%3!=0);root->subscribeEvent(CEGUI::String("ZChanged"),CEGUI::Event::Subscriber(&zChanged));zCalls=0;
 phase=35;CEquipment*item=new CEquipment(&f.resources);for(unsigned i=0;i<4;++i)if(seed/32&(1u<<i))f.nativeClient.client->getMouseClickUnit(i).setObject(i<2?static_cast<CBaseUnit*>(player):static_cast<CBaseUnit*>(item));
 detour::Set calls;TL_REDIRECT(calls,wpInteractive,&interactive);TL_REDIRECT(calls,wpDungeon,&dungeon);TL_REDIRECT(calls,wpTemplate,&data);if(calls.failed())std::abort();typedef void(*Fn)(CWaypointMenu*,bool);Fn fn=ours?wpNewOpen:wpOpen;if(!autotest::beginInvocation(out,fn))return;phase=40;fn(p,seed&1);phase=41;out.callCompleted=1;num(zCalls);state(p);num(root->getParent()==f.root);for(unsigned i=0;i<4;++i)num(f.nativeClient.client->getMouseClickUnit(i).getObject()!=NULL);snapshot(root);for(unsigned i=0;i<50;++i)p->m_destinationWindows[i]=saved[i];calls.restore();for(unsigned i=0;i<4;++i)f.nativeClient.client->getMouseClickUnit(i).setObject(NULL);phase=50;delete item;phase=60;delete templates[0];phase=61;delete templates[1];phase=70;f.nativeClient.client->m_pPlayer=NULL;nativegame::destroyPlayer(player);phase=80;
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned count){std::string old=std::setlocale(LC_CTYPE,NULL);if(!std::setlocale(LC_CTYPE,"C.UTF-8"))return 1;int result;{tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;result=smallmass::run(host,op,name,address,&side,count);}std::setlocale(LC_CTYPE,old.c_str());return result;}
}
TL_TEST(complete_ui_waypoint_create){return run(host,0,"complete_ui_waypoint_create",0xea58b0,24);}
TL_TEST(complete_ui_waypoint_click){return run(host,1,"complete_ui_waypoint_click",0xea45d0,560);}
TL_TEST(complete_ui_waypoint_open){return run(host,2,"complete_ui_waypoint_open",0xea4970,384);}
TL_TEST(complete_ui_waypoint_ctor){return run(host,3,"complete_ui_waypoint_ctor",0xea62a0,24);}
