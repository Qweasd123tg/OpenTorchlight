#include "FinishLevelFixture.h"
#include "NativeConsoleFixture.h"
#include "UnitResourceList.h"
#include "GameVariables.h"
#include <clocale>
TL_ORIGINAL(void,suOld,(CConsole*,std::wstring,std::wstring),"_ZN8CConsole9spawnUnitESbIwSt11char_traitsIwESaIwEES3_")
extern "C" void suNew(CConsole*,std::wstring,std::wstring) __asm__("_ZN8CConsole9spawnUnitESbIwSt11char_traitsIwESaIwEES3_");
TL_FUNCTION(suCreate,"_ZN16CResourceManager10createUnitEPKwS1_ib")
TL_FUNCTION(suOpen,"_ZN6CLevel22randomOpenItemPositionERKN4Ogre7Vector3Efb")
TL_FUNCTION(suAdd,"_ZN6CLevel7addUnitEP9CBaseUnitRKN4Ogre7Vector3E")
namespace {
struct Locale {std::string previous;Locale():previous(std::setlocale(LC_CTYPE,NULL)){if(!std::setlocale(LC_CTYPE,"C.UTF-8"))std::abort();}~Locale(){std::setlocale(LC_CTYPE,previous.c_str());}};
autotest::Capture*output;CSettings*settings;Ogre::SceneManager*scene;
CResourceManager*resources;CLevel*level;unsigned seed,created,placements;
std::vector<TSafePointer<CPlayer>*>units;std::vector<CBaseUnit*>adopted;
void number(unsigned n){output->add(&n,4);}void scalar(float f){output->add(&f,4);}
void vector(const Ogre::Vector3&v){scalar(v.x);scalar(v.y);scalar(v.z);}
void wide(const std::wstring&s){number(s.size());output->add(s.data(),s.size()*4);}
unsigned identity(CBaseUnit*p){for(unsigned i=0;i<units.size();++i)if(units[i]->getObject()==p)return i+1;return 0;}
CBaseUnit* create(CResourceManager*r,const wchar_t*category,const wchar_t*name,int depth,bool flag){
 number(10);number(r==resources);wide(category);wide(name);number(depth);number(flag);++created;
 // Exercise the 10000/10001 count boundary without constructing 10000 owners.
 if((seed%9==4&&created==2)||(seed%9==7&&created==1))return NULL;
 CPlayer*p=nativegame::createPlayer(resources);TSafePointer<CPlayer>*weak=new TSafePointer<CPlayer>;weak->setObject(p);units.push_back(weak);return p;
}
Ogre::Vector3 open(CLevel*p,const Ogre::Vector3&input,float radius,bool flag){
 number(11);number(p==level);vector(input);scalar(radius);number(flag);
 unsigned local=placements++%5,mode=seed/36%6;Ogre::Vector3 result=input;
 bool changed=mode==0||(mode==1&&local>=1)||(mode==2&&local>=4)||(mode==4&&local==4)||(mode==5&&local%2);
 if(changed){if(seed&1)result.z+=.125f;else result.x-=.5f;}
 return result;
}
CBaseUnit* add(CLevel*p,CBaseUnit*unit,const Ogre::Vector3&position){number(12);number(p==level);number(identity(unit));vector(position);adopted.push_back(unit);return unit;}
struct Groups {
 bool owned[4];Groups(){const wchar_t*names[]={L"ITEMS",L"MONSTERS",L"PLAYERS",L"PROPS"};for(unsigned i=0;i<4;++i){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14bc560+i*8),8);owned[i]=!p;if(owned[i])new(reinterpret_cast<void*>(0x14bc560+i*8))std::wstring(names[i]);}}
 ~Groups(){for(unsigned i=0;i<4;++i)if(owned[i]){reinterpret_cast<std::wstring*>(0x14bc560+i*8)->~basic_string();std::memset(reinterpret_cast<void*>(0x14bc560+i*8),0,8);}}
};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;created=placements=0;units.clear();adopted.clear();Groups groups;CStringTranslate translate(L"");
 menugui::Fixture gui(*settings,scene);finishlevel::Fixture world;resources=&world.resources;level=&world.level;resources->m_pSceneManager=gui.nativeClient.scenes[0];
 menugui::Console console(gui);console.p->m_resources=resources;console.p->m_gameClient=gui.nativeClient.client;
 CPlayer*player=nativegame::createPlayer(resources);gui.nativeClient.client->m_pPlayer=player;
 player->setPosition(Ogre::Vector3(float(seed%5)-2,float(seed%3)*.25f,-3.5f));
 Ogre::Vector3 direction(seed&1?1.0f:0.0f,0,seed&1?0.0f:1.0f),up(0,1,0);player->setOrientation(direction,up);
 CUnitResourceList*savedList=m_pGlobalUnitResourceList;
 {
 CUnitResourceList list;m_pGlobalUnitResourceList=&list;CDataGroup data(L"UNIT",NULL,2,2,NULL);
 const wchar_t*names[]={L"ITEMS",L"MONSTERS",L"PLAYERS",L"PROPS"};unsigned group=seed/9%4;
 list.m_dataGroupsByResourceGroupAndName[names[group]][L"SAMPLE"]=&data;
 const wchar_t*counts[]={L"0",L"1",L"2",L"3",L"10000",L"10001",L"-1",L"x",L"6"};std::wstring count(counts[seed%9]);
 // Separate genuine null-level and null-player entry branches.
 if(seed>=216){if(seed&1)resources->m_pLevel=NULL;else gui.nativeClient.client->m_pPlayer=NULL;}
 detour::Set collaborators;TL_REDIRECT(collaborators,suCreate,&create);TL_REDIRECT(collaborators,suOpen,&open);TL_REDIRECT(collaborators,suAdd,&add);if(collaborators.failed())std::abort();
 typedef void(*Fn)(CConsole*,std::wstring,std::wstring);Fn fn=ours?suNew:suOld;if(!autotest::beginInvocation(out,fn))return;fn(console.p,L"sample",count);out.callCompleted=1;
 number(created);number(placements);number(units.size());number(adopted.size());for(unsigned i=0;i<units.size();++i){number(units[i]->getObject()!=NULL);number(std::find(adopted.begin(),adopted.end(),units[i]->getObject())!=adopted.end());}
 collaborators.restore();for(unsigned i=0;i<units.size();++i){if(units[i]->getObject())nativegame::destroyPlayer(units[i]->getObject());number(units[i]->getObject()==NULL);delete units[i];}units.clear();adopted.clear();
 }
 m_pGlobalUnitResourceList=savedList;gui.nativeClient.client->m_pPlayer=NULL;nativegame::destroyPlayer(player);resources->m_pLevel=level;
}
int run(const tlhybrid_host*host){Locale locale;tlheadless::Environment env;env.loadGameSkin();CEGUI::SchemeManager::getSingleton().loadScheme("media/ui/WindowsLook.scheme");nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,0,"complete_ui_console_spawnunit",0xae19e0,&side,232);}
}
TL_TEST(complete_ui_console_spawnunit){return run(host);}
