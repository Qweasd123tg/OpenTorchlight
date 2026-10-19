#include "FinishLevelFixture.h"
#include "NativeConsoleFixture.h"
#include "ConsoleData.h"
#include "FileUtilities.h"
#include "RoomPieceDataInformation.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include "DataValue.h"
#include "StringUtilities.h"
#include "UnitResourceList.h"
#include "Monster.h"
#include "Skill.h"
#include "SettingsVariables.h"
#include <elements/CEGUIMultiLineEditbox.h>
#include <clocale>
TL_ORIGINAL(void,ciOriginal,(CConsole*,std::wstring),"_ZN8CConsole18executeCommandLineESbIwSt11char_traitsIwESaIwEE")
extern "C" void ciCandidate(CConsole*,std::wstring) __asm__("_ZN8CConsole18executeCommandLineESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(ciLog,"_ZN8CConsole16addTextNoHistoryESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ciLookup,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ciType,"_ZN16CResourceManager17getUnitTypeByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ciMasterList,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(ciUiVisible,"_ZN7CGameUI18setIngameUIVisibleEb")
TL_FUNCTION(ciFps,"_ZN7CGameUI9toggleFPSEv")
extern CRoomPieceDataInformation*m_gRoomPieceInformation;
namespace {
struct Locale{std::string previous;Locale():previous(std::setlocale(LC_CTYPE,NULL)){if(!std::setlocale(LC_CTYPE,"C.UTF-8"))std::abort();}~Locale(){std::setlocale(LC_CTYPE,previous.c_str());}};
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;CConsole*console;CUnitResourceList*unitlist;CResourceManager*resources;CGameUI*ui;CPlayer*player;
unsigned int keys[]={KSETTINGS_DEBUG_LOGIC,KSETTINGS_SHOW_BLOOD,KSETTINGS_PLAYER_UNTARGETABLE,KSETTINGS_SHOW_MISSILE_TRAILS,KSETTINGS_SHOW_DAMAGE_SHAPES,KSETTINGS_DISPLAY_PATHING,KSETTINGS_SOUND_DEBUG,KSETTINGS_COMBAT_LOG,KSETTINGS_AI_FREEZE};
std::string trace;void append(const void*p,unsigned n){trace.append(static_cast<const char*>(p),n);}void num(unsigned n){append(&n,4);}void wide(const std::wstring&s){num(s.size());append(s.data(),s.size()*4);}
void log(CConsole*p,std::wstring s){num(10);num(p==console);wide(s);num(player->m_cheatMarker);for(unsigned i=0;i<9;++i)num(settings->GetInt(keys[i]));}
CDataGroup* lookup(CUnitResourceList*p,const std::wstring&s){num(11);num(p==unitlist);wide(s);return NULL;}
unsigned type(CResourceManager*p,const std::wstring&s){num(12);num(p==resources);wide(s);return 22;}
CUnitResourceList* masterList(CResourceManager*p){num(13);num(p==resources);return unitlist;}
void visible(CGameUI*p,bool enabled){num(14);num(p==ui);num(enabled);}
void fps(CGameUI*p){num(15);num(p==ui);}
struct Help {bool made;Help():made(false){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14bd5a0),8);if(!p){new(reinterpret_cast<void*>(0x14bd5a0))std::wstring(gTEXT_HELP);made=true;}}~Help(){if(made){reinterpret_cast<std::wstring*>(0x14bd5a0)->~basic_string();std::memset(reinterpret_cast<void*>(0x14bd5a0),0,8);}}};
TL_FUNCTION(ciMessage,"_Z10MessageBoxPvPKwS1_i")
TL_FUNCTION(ciCreateMonster,"_ZN16CResourceManager13createMonsterEPKwib")
TL_FUNCTION(ciCreatePlayer,"_ZN16CResourceManager12createPlayerEPKwb")
TL_FUNCTION(ciRemovePets,"_ZN10CCharacter10removePetsEv")
TL_FUNCTION(ciAddPet,"_ZN10CCharacter6addPetEPS_")
TL_FUNCTION(ciTreeDepth,"_ZN10CCharacter19setMaximumTreeDepthEj")
TL_FUNCTION(ciOpen,"_ZN6CLevel18randomOpenPositionERKN4Ogre7Vector3Efb")
TL_FUNCTION(ciAdd,"_ZN6CLevel12addCharacterEP10CCharacterRKN4Ogre7Vector3Eb")
TL_FUNCTION(ciLoadLayout,"_ZN7CLayout14loadLayoutFileERKSbIwSt11char_traitsIwESaIwEEbP13CTimerStaticsbbj")
TL_FUNCTION(ciLoadData,"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
TL_FUNCTION(ciSaveData,"_ZN10CDataGroup10SaveToFileERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ciFileData,"_ZN10FILESYSTEM11GetFileDataERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ciRoom,"_ZN25CRoomPieceDataInformation40_GetRoomPieceCoreDataByGuidByClosestGuidEx")
TL_FUNCTION(ciSound,"_ZN25CSoundBankDataInformation37getSoundDataObjectByGuidThatIsClosestEx")
extern "C" int ciSystem(const char*) __asm__("system");
CResourceManager*levelResources;CLevel*level;CMonster*oldPet,*newPet,*returnedPet;CRoomPieceDataInformation*rooms;CSoundBankDataInformation*sounds;CRoomPieceDataInformation::CRoomPieceCoreData*piece;CSoundData*sample;unsigned seed,monsterCalls,playerCalls;std::vector<TSafePointer<CLayout>*>layouts;std::vector<TSafePointer<CBaseUnit>*>units;
void scalar(float v){append(&v,4);}void vector(const Ogre::Vector3&v){scalar(v.x);scalar(v.y);scalar(v.z);}void bytes(const std::string&s){num(s.size());append(s.data(),s.size());}
unsigned unitIdentity(CCharacter*p){return p==player?1:p==oldPet?2:p==newPet?3:p==returnedPet?4:0;}
int message(void*parent,const wchar_t*text,const wchar_t*title,int flags){num(20);num(parent==NULL);wide(text);wide(title);num(flags);return 1;}
void remember(CBaseUnit*p){TSafePointer<CBaseUnit>*weak=new TSafePointer<CBaseUnit>;weak->setObject(p);units.push_back(weak);}
CMonster*monster(CResourceManager*p,const wchar_t*name,int depth,bool flag){num(21);num(p==resources?1:p==levelResources?2:0);wide(name);num(depth);num(flag);++monsterCalls;if(std::wstring(name)==L"Dog"){if(seed%4==0)return NULL;newPet=new CMonster(p,1);newPet->m_bInvulnerable=false;newPet->m_petMode=-9;std::memset(newPet->m_CharacterData714,53,4);remember(newPet);return newPet;}if(monsterCalls>seed%3)return NULL;CMonster*value=new CMonster(p,1);remember(value);return value;}
CPlayer*createPlayer(CResourceManager*p,const wchar_t*name,bool flag){num(22);num(p==resources);wide(name);num(flag);++playerCalls;if(playerCalls>seed%3)return NULL;CPlayer*value=nativegame::createPlayer(p);remember(value);return value;}
void removePets(CCharacter*p){num(23);num(p==player);num(p->m_Followers.size());p->m_Followers.clear();}
void addPet(CCharacter*p,CCharacter*child){num(24);num(p==player);num(unitIdentity(child));p->m_Followers.push_back(child);}
void treeDepth(CCharacter*p,unsigned n){num(25);num(unitIdentity(p));num(n);}
Ogre::Vector3 open(CLevel*p,const Ogre::Vector3&pos,float radius,bool flag){num(26);num(p==level);vector(pos);scalar(radius);num(flag);return Ogre::Vector3(pos.x+.125f,pos.y+radius,pos.z-.75f);}
CCharacter*add(CLevel*p,CCharacter*unit,const Ogre::Vector3&pos,bool flag){num(27);num(p==level);num(unitIdentity(unit));vector(pos);num(flag);return seed&1?returnedPet:unit;}
void layout(CLayout*p,const std::wstring&name,bool objects,CTimerStatics*timer,bool force,bool ignore,unsigned value){num(28);num(p->getDescriptorManager()!=NULL);wide(name);num(objects);num(timer==NULL);num(force);num(ignore);num(value);TSafePointer<CLayout>*weak=new TSafePointer<CLayout>;weak->setObject(p);layouts.push_back(weak);}
void dataLoad(CDataGroup*p,const std::wstring&name,CTimerStatics*timer){num(29);wide(p->GetGroupName());wide(name);num(timer==NULL);if(seed%8==0)return;CDataGroup*objects=p->AddDataGroup(L"OBJECTS");if(seed%8==1)return;CDataGroup*object=objects->AddDataGroup(L"object");CDataGroup*properties=object->AddDataGroup(L"PROPERTIES");if(seed%8==2)return;properties->AddDataValue(L"DESCRIPTOR",seed&1?L"Sound":L"Room Piece",false);CDataGroup*guid=properties->AddDataGroup(L"GUID");guid->AddDataValue(L"VALUE",seed&2?L"1x":L"-17",false);}
void tree(CDataGroup*p){wide(p->GetGroupName());num(p->GetNumberOfDataValues());for(unsigned i=0;i<p->GetNumberOfDataValues();++i){CDataValue*v=p->GetDataValue(i);wide(v->GetDataValueName());wide(v->GetValueString(false));}num(p->GetNumberOfDataGroups());for(unsigned i=0;i<p->GetNumberOfDataGroups();++i)tree(p->GetDataGroup(i));}
int dataSave(CDataGroup*p,const std::wstring&name){num(30);wide(name);tree(p);return 1;}
_WIN32_FIND_DATA fileData(const std::wstring&name){num(31);wide(name);_WIN32_FIND_DATA out;std::memset(&out,0,sizeof out);out.attributes=seed&4?1:0;return out;}
int shell(const char*s){num(32);bytes(s);return 0;}
CRoomPieceDataInformation::CRoomPieceCoreData*room(CRoomPieceDataInformation*p,long long guid){num(33);num(p==rooms);append(&guid,8);return seed%8==3?NULL:piece;}
CSoundData*sound(CSoundBankDataInformation*p,long long guid){num(34);num(p==sounds);append(&guid,8);return seed%8==3?NULL:sample;}
void finish(){
 const std::string&s=trace;std::string encoded;std::map<std::string,unsigned>dictionary;
 for(size_t at=0;at<s.size();at+=16){std::string block=s.substr(at,16);std::map<std::string,unsigned>::iterator found=dictionary.find(block);unsigned code;
  if(found==dictionary.end()){code=~0u;encoded.append(reinterpret_cast<const char*>(&code),4);unsigned length=block.size();encoded.append(reinterpret_cast<const char*>(&length),4);encoded+=block;unsigned id=dictionary.size();dictionary.insert(std::make_pair(block,id));}
  else{code=found->second;encoded.append(reinterpret_cast<const char*>(&code),4);}
 }
 std::vector<std::string>blocks;std::string decoded;size_t cursor=0;
 while(cursor<encoded.size()){if(encoded.size()-cursor<4)std::abort();unsigned code;std::memcpy(&code,encoded.data()+cursor,4);cursor+=4;if(code==~0u){if(encoded.size()-cursor<4)std::abort();unsigned length;std::memcpy(&length,encoded.data()+cursor,4);cursor+=4;if(length>encoded.size()-cursor)std::abort();blocks.push_back(encoded.substr(cursor,length));decoded+=blocks.back();cursor+=length;}else{if(code>=blocks.size())std::abort();decoded+=blocks[code];}}
 if(decoded!=s)std::abort();unsigned length=s.size(),packed=encoded.size();output->add(&length,4);output->add(&packed,4);output->add(encoded.data(),encoded.size());
}
const wchar_t*commands[]={L"MEMTEST",L"MEMTEST",L"MEMTEST",L"FIXPET",L"FIXPET",L"FIXPET",L"FIXPET",L"FIXPET",L"FIXPET",L"FIXPET",L"FIXPET",L"FIXPET",L"FIXGUIDS",L"FIXGUIDS",L"FIXGUIDS",L"FIXGUIDS",L"FIXGUIDS",L"FIXGUIDS",L"FIXGUIDS",L"FIXGUIDS",L"FIXGUIDS",L"FIXGUIDS",L"FIXGUIDS",L"FIXGUIDS",L"LAYOUT fixture.layout,0",L"LAYOUT fixture.layout,1",L"LAYOUT Тест.layout,2",L"LAYOUT fixture.layout,3",L"LAYOUT fixture.layout",L"LAYOUT fixture.layout,10001",L"LAYOUT fixture.layout,-1",L"LAYOUT fixture.layout,x"};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;trace.clear();seed=c.index;monsterCalls=playerCalls=0;newPet=NULL;units.clear();layouts.clear();CStringTranslate translate(L"");menugui::Fixture f(*settings,scene);finishlevel::Fixture world;resources=&world.resources;level=&world.level;levelResources=&f.resources;level->m_resourceManager=levelResources;resources->m_pSceneManager=f.nativeClient.scenes[0];resources->m_GameClients.add(f.nativeClient.client);menugui::Console owner(f);console=owner.p;ui=f.ui;console->m_resources=resources;console->m_gameClient=f.nativeClient.client;f.nativeClient.client->m_level=level;
 CUnitResourceList*previous=CUnitResourceList::getSingleton();CUnitResourceList list;unitlist=&list;m_pGlobalUnitResourceList=unitlist;player=nativegame::createPlayer(resources);f.nativeClient.client->m_pPlayer=player;player->setPosition(Ogre::Vector3(.5f+seed,3.25f,-7.5f));player->m_cheatMarker=seed%4==1?214:seed%4;player->m_characterDisplayName=L"Player";oldPet=new CMonster(resources,1);returnedPet=new CMonster(resources,1);oldPet->m_bInvulnerable=false;oldPet->m_petMode=-3;std::memset(oldPet->m_CharacterData714,59,4);std::memset(returnedPet->m_CharacterData714,61,4);player->m_Followers.push_back(oldPet);returnedPet->m_bInvulnerable=false;returnedPet->m_petMode=-7;returnedPet->m_CharacterData714[0]=41;returnedPet->m_CharacterData714[1]=43;returnedPet->m_CharacterData714[2]=47;f.ui->m_name16B8=seed&1?L"Dog 漢字":std::wstring(L"a\0tail",6);if(seed==10)f.nativeClient.client->m_level=NULL;if(seed==11)f.nativeClient.client->m_pPlayer=NULL;
 CMasterResourceManager*master=CMasterResourceManager::getSingleton();CRoomPieceDataInformation*previousRooms=master->m_pRoomPieceInformation,*previousRoomGlobal=m_gRoomPieceInformation;CSoundBankDataInformation*previousSounds=master->m_pSoundBankDataInformation;CRoomPieceDataInformation roomOwner(NULL);CSoundBankDataInformation soundOwner(NULL);rooms=&roomOwner;sounds=&soundOwner;master->m_pRoomPieceInformation=rooms;master->m_pSoundBankDataInformation=sounds;CRoomPieceDataInformation::CRoomPieceCoreData core;piece=&core;core.m_guid=0x123456789abcdefLL;CSoundData soundData;soundData.m_group=NULL;soundData.m_iGuid=-17;sample=&soundData;
 detour::Set calls;TL_REDIRECT(calls,ciLog,&log);TL_REDIRECT(calls,ciLookup,&lookup);TL_REDIRECT(calls,ciType,&type);TL_REDIRECT(calls,ciMasterList,&masterList);TL_REDIRECT(calls,ciMessage,&message);TL_REDIRECT(calls,ciCreateMonster,&monster);TL_REDIRECT(calls,ciCreatePlayer,&createPlayer);TL_REDIRECT(calls,ciRemovePets,&removePets);TL_REDIRECT(calls,ciAddPet,&addPet);TL_REDIRECT(calls,ciTreeDepth,&treeDepth);TL_REDIRECT(calls,ciOpen,&open);TL_REDIRECT(calls,ciAdd,&add);TL_REDIRECT(calls,ciLoadLayout,&layout);TL_REDIRECT(calls,ciLoadData,&dataLoad);TL_REDIRECT(calls,ciSaveData,&dataSave);TL_REDIRECT(calls,ciFileData,&fileData);TL_REDIRECT(calls,ciRoom,&room);TL_REDIRECT(calls,ciSound,&sound);calls.redirect(reinterpret_cast<char*>(&ciSystem),reinterpret_cast<char*>(&ciSystem),&shell);if(calls.failed())std::abort();typedef void(*Fn)(CConsole*,std::wstring);Fn fn=ours?ciCandidate:ciOriginal;if(!autotest::beginInvocation(out,fn))return;fn(console,commands[seed]);out.callCompleted=1;
 num(monsterCalls);num(playerCalls);num(layouts.size());for(unsigned i=0;i<layouts.size();++i)num(layouts[i]->getObject()==NULL);num(player->m_Followers.size());for(unsigned i=0;i<player->m_Followers.size();++i)num(unitIdentity(player->m_Followers[i]));CMonster*values[]={oldPet,newPet,returnedPet};for(unsigned i=0;i<3;++i){num(values[i]!=NULL);if(values[i]){num(values[i]->m_bInvulnerable);num(values[i]->m_petMode);append(values[i]->m_CharacterData714,4);wide(values[i]->m_characterDisplayName);}}
 calls.restore();for(unsigned i=0;i<layouts.size();++i){if(layouts[i]->getObject())delete layouts[i]->getObject();num(layouts[i]->getObject()==NULL);delete layouts[i];}layouts.clear();player->m_Followers.clear();delete oldPet;delete returnedPet;for(unsigned i=0;i<units.size();++i){if(units[i]->getObject())delete units[i]->getObject();num(units[i]->getObject()==NULL);delete units[i];}units.clear();f.nativeClient.client->m_pPlayer=NULL;f.nativeClient.client->m_level=NULL;nativegame::destroyPlayer(player);resources->m_GameClients.clear();m_pGlobalUnitResourceList=previous;master->m_pRoomPieceInformation=previousRooms;master->m_pSoundBankDataInformation=previousSounds;m_gRoomPieceInformation=previousRoomGlobal;level->m_resourceManager=resources;finish();
}
}
TL_TEST(complete_ui_console_dispatch_io){Locale locale;tlheadless::Environment env;env.loadGameSkin();CEGUI::SchemeManager::getSingleton().loadScheme("media/ui/WindowsLook.scheme");nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,0,"complete_ui_console_dispatch_io",0xaf2540,&side,(sizeof(commands)/sizeof(commands[0])));}
