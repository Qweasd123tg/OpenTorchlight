#include "FinishLevelFixture.h"
#include "NativeConsoleFixture.h"
#include "Equipment.h"
#include "Monster.h"
#include "RandomNames.h"
#include "GameVariables.h"
#include <clocale>
TL_ORIGINAL(void,miMonster,(CConsole*,std::wstring,std::wstring,bool,int),"_ZN8CConsole12spawnMonsterESbIwSt11char_traitsIwESaIwEES3_bi")
TL_ORIGINAL(void,miItem,(CConsole*,std::wstring,long long,std::wstring),"_ZN8CConsole9spawnItemESbIwSt11char_traitsIwESaIwEExS3_")
extern "C" void miNewMonster(CConsole*,std::wstring,std::wstring,bool,int) __asm__("_ZN8CConsole12spawnMonsterESbIwSt11char_traitsIwESaIwEES3_bi");
extern "C" void miNewItem(CConsole*,std::wstring,long long,std::wstring) __asm__("_ZN8CConsole9spawnItemESbIwSt11char_traitsIwESaIwEExS3_");
TL_FUNCTION(miCreateMonster,"_ZN16CResourceManager13createMonsterEPKwib")
TL_FUNCTION(miCreateItemName,"_ZN16CResourceManager10createItemEPKwbb")
TL_FUNCTION(miCreateItemGuid,"_ZN16CResourceManager10createItemExbbb")
TL_FUNCTION(miOpenMonster,"_ZN6CLevel18randomOpenPositionERKN4Ogre7Vector3Efb")
TL_FUNCTION(miOpenItem,"_ZN6CLevel22randomOpenItemPositionERKN4Ogre7Vector3Efb")
TL_FUNCTION(miAddMonster,"_ZN6CLevel12addCharacterEP10CCharacterRKN4Ogre7Vector3Eb")
TL_FUNCTION(miAddItem,"_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
TL_FUNCTION(miGenerate,"_ZN12CRandomNames12generateNameEb")
TL_FUNCTION(miChampion,"_ZN10CCharacter12makeChampionERKSbIwSt11char_traitsIwESaIwEEiS3_")
namespace {
struct Locale {std::string previous;Locale():previous(std::setlocale(LC_CTYPE,NULL)){if(!std::setlocale(LC_CTYPE,"C.UTF-8"))std::abort();}~Locale(){std::setlocale(LC_CTYPE,previous.c_str());}};
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;CResourceManager*resources;CLevel*level;CRandomNames*names;unsigned seed,created,placements,mode;
std::vector<TSafePointer<CBaseUnit>*>units;std::vector<CBaseUnit*>adopted;
void number(unsigned n){output->add(&n,4);}void scalar(float f){output->add(&f,4);}void vector(const Ogre::Vector3&v){scalar(v.x);scalar(v.y);scalar(v.z);}void wide(const std::wstring&s){number(s.size());output->add(s.data(),s.size()*4);}
unsigned identity(CBaseUnit*p){for(unsigned i=0;i<units.size();++i)if(units[i]->getObject()==p)return i+1;return 0;}
bool failure(){++created;return (seed%9==4&&created==2)||(seed%13==1&&created==1);}
void remember(CBaseUnit*p){TSafePointer<CBaseUnit>*weak=new TSafePointer<CBaseUnit>;weak->setObject(p);units.push_back(weak);}
CMonster* monster(CResourceManager*r,const wchar_t*name,int depth,bool flag){number(10);number(r==resources);wide(name);number(depth);number(flag);if(failure())return NULL;CMonster*p=new CMonster(resources,1);remember(p);return p;}
CItem* itemName(CResourceManager*r,const wchar_t*name,bool a,bool b){number(11);number(r==resources);wide(name);number(a);number(b);if(failure())return NULL;CEquipment*p=new CEquipment(resources);remember(p);return p;}
CItem* itemGuid(CResourceManager*r,long long guid,bool a,bool b,bool c){number(12);number(r==resources);output->add(&guid,8);number(a);number(b);number(c);if(failure())return NULL;CEquipment*p=new CEquipment(resources);remember(p);return p;}
Ogre::Vector3 open(CLevel*p,const Ogre::Vector3&input,float radius,bool flag){number(13);number(p==level);vector(input);scalar(radius);number(flag);unsigned local=placements++%5,pattern=seed/9%6;Ogre::Vector3 result=input;bool changed=pattern==0||(pattern==1&&local>=1)||(pattern==2&&local>=4)||(pattern==4&&local==4)||(pattern==5&&local%2);if(changed){if(seed&1)result.z+=.125f;else result.x-=.5f;}return result;}
CCharacter* addMonster(CLevel*p,CCharacter*unit,const Ogre::Vector3&position,bool flag){number(14);number(p==level);number(identity(unit));vector(position);number(flag);adopted.push_back(unit);return unit;}
CItem* addItem(CLevel*p,CItem*unit,const Ogre::Vector3&position,bool flag){number(15);number(p==level);number(identity(unit));vector(position);number(flag);adopted.push_back(unit);return unit;}
std::wstring generate(CRandomNames*p,bool title){number(16);number(p==names);number(title);return seed&1?L"Champion 漢字":L"Test Champion";}
void champion(CCharacter*p,const std::wstring&name,int depth,std::wstring type){number(17);number(identity(p));wide(name);number(depth);wide(type);}
// Native RandomNames' TU-local empty strings and singleton storage are proven
// by its C1/load/getSingleton ASM; use a real C1/D1 owner, never a null/fake this.
struct Names {
 bool n,w;CRandomNames*owned;void*saved;
 Names():n(false),w(false),owned(NULL),saved(NULL){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x151f660),8);if(!p){new(reinterpret_cast<void*>(0x151f660))std::string;n=true;}std::memcpy(&p,reinterpret_cast<void*>(0x151f668),8);if(!p){new(reinterpret_cast<void*>(0x151f668))std::wstring;w=true;}std::memcpy(&saved,reinterpret_cast<void*>(0x151f860),8);if(!saved)owned=new CRandomNames(L"");names=CRandomNames::getSingleton();if(!names)std::abort();}
 ~Names(){delete owned;std::memcpy(reinterpret_cast<void*>(0x151f860),&saved,8);if(w){reinterpret_cast<std::wstring*>(0x151f668)->~basic_string();std::memset(reinterpret_cast<void*>(0x151f668),0,8);}if(n){reinterpret_cast<std::string*>(0x151f660)->~basic_string();std::memset(reinterpret_cast<void*>(0x151f660),0,8);}}
};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;mode=c.op;created=placements=0;units.clear();adopted.clear();CStringTranslate translate(L"");menugui::Fixture gui(*settings,scene);finishlevel::Fixture world;resources=&world.resources;level=&world.level;resources->m_pSceneManager=gui.nativeClient.scenes[0];resources->m_GameClients.add(gui.nativeClient.client);menugui::Console console(gui);console.p->m_resources=resources;console.p->m_gameClient=gui.nativeClient.client;
 CPlayer*player=nativegame::createPlayer(resources);gui.nativeClient.client->m_pPlayer=player;player->setPosition(Ogre::Vector3(float(seed%5)-2,float(seed%3)*.25f,-3.5f));Ogre::Vector3 direction(seed&1?1.0f:0.0f,0,seed&1?0.0f:1.0f),up(0,1,0);player->setOrientation(direction,up);const wchar_t*display[]={L"",L"Hero",L"Already the Cheat"};player->m_characterDisplayName=display[seed%3];const unsigned char markers[]={0,214,1,255};player->m_cheatMarker=markers[seed/2%4];
 const wchar_t*counts[]={L"0",L"1",L"2",L"3",L"1000",L"1001",L"-1",L"x",L"6"};std::wstring count(counts[seed%9]);unsigned normal=c.op==0?108:216;if(seed>=normal){if(seed&1)resources->m_pLevel=NULL;else gui.nativeClient.client->m_pPlayer=NULL;}
 Names randomNames;detour::Set calls;TL_REDIRECT(calls,miCreateMonster,&monster);TL_REDIRECT(calls,miCreateItemName,&itemName);TL_REDIRECT(calls,miCreateItemGuid,&itemGuid);TL_REDIRECT(calls,miOpenMonster,&open);TL_REDIRECT(calls,miOpenItem,&open);TL_REDIRECT(calls,miAddMonster,&addMonster);TL_REDIRECT(calls,miAddItem,&addItem);TL_REDIRECT(calls,miGenerate,&generate);TL_REDIRECT(calls,miChampion,&champion);if(calls.failed())std::abort();
 if(c.op==0){typedef void(*Fn)(CConsole*,std::wstring,std::wstring,bool,int);Fn fn=ours?miNewMonster:miMonster;if(!autotest::beginInvocation(out,fn))return;fn(console.p,L"sample",count,seed/54&1,int(seed/3%4)-1);}
 else{const long long guids[]={-1,0,0x123456789abcdefLL,(-9223372036854775807LL-1)};typedef void(*Fn)(CConsole*,std::wstring,long long,std::wstring);Fn fn=ours?miNewItem:miItem;if(!autotest::beginInvocation(out,fn))return;fn(console.p,L"sample",guids[seed/54%4],count);}
 out.callCompleted=1;number(created);number(placements);number(units.size());number(adopted.size());wide(player->m_characterDisplayName);number(player->m_cheatMarker);for(unsigned i=0;i<units.size();++i){number(units[i]->getObject()!=NULL);number(std::find(adopted.begin(),adopted.end(),units[i]->getObject())!=adopted.end());}calls.restore();for(unsigned i=0;i<units.size();++i){if(units[i]->getObject())delete units[i]->getObject();number(units[i]->getObject()==NULL);delete units[i];}units.clear();adopted.clear();gui.nativeClient.client->m_pPlayer=NULL;nativegame::destroyPlayer(player);resources->m_pLevel=level;resources->m_GameClients.clear();
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned count){Locale locale;tlheadless::Environment env;env.loadGameSkin();CEGUI::SchemeManager::getSingleton().loadScheme("media/ui/WindowsLook.scheme");nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,op,name,address,&side,count);}
}
TL_TEST(complete_ui_console_monster){return run(host,0,"complete_ui_console_monster",0xaee5e0,116);}
TL_TEST(complete_ui_console_item){return run(host,1,"complete_ui_console_item",0xaf2060,224);}
