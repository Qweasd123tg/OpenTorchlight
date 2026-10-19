#include "AutoTest.h"
#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "tests/NativeMenuClient.h"
#include "tests/SystemsFixtureWorker.h"
#include "Utilities.h"
#include <clocale>
TL_ORIGINAL(void,gcSeedOld,(CGameClient*,int),"_ZN11CGameClient13resetGameSeedEi")
TL_ORIGINAL(int,gcRankOld,(CGameClient*,int,CDungeon*,bool),"_ZN11CGameClient24getRankOfMonstersOnFloorEiP8CDungeonb")
TL_ORIGINAL(int,gcRankNameOld,(CGameClient*,int,const std::wstring&,bool),"_ZN11CGameClient24getRankOfMonstersOnFloorEiRKSbIwSt11char_traitsIwESaIwEEb")
TL_ORIGINAL(void,gcMoveOld,(CGameClient*,bool),"_ZN11CGameClient11moveToMouseEb")
TL_ORIGINAL(bool,gcInputOld,(CGameClient*,void*,float,bool),"_ZN11CGameClient12processInputEPvfb")
TL_ORIGINAL(void,gcGoldOld,(CGameClient*),"_ZN11CGameClient14autoPickupGoldEv")
extern "C" void gcSeedNew(CGameClient*,int) __asm__("_ZN11CGameClient13resetGameSeedEi");
extern "C" int gcRankNew(CGameClient*,int,CDungeon*,bool) __asm__("_ZN11CGameClient24getRankOfMonstersOnFloorEiP8CDungeonb");
extern "C" int gcRankNameNew(CGameClient*,int,const std::wstring&,bool) __asm__("_ZN11CGameClient24getRankOfMonstersOnFloorEiRKSbIwSt11char_traitsIwESaIwEEb");
extern "C" void gcMoveNew(CGameClient*,bool) __asm__("_ZN11CGameClient11moveToMouseEb");
extern "C" bool gcInputNew(CGameClient*,void*,float,bool) __asm__("_ZN11CGameClient12processInputEPvfb");
extern "C" void gcGoldNew(CGameClient*) __asm__("_ZN11CGameClient14autoPickupGoldEv");
TL_FUNCTION(gcSetSeed,"_ZN9UTILITIES7setSeedEi")
TL_FUNCTION(gcHistory,"_ZN7CPlayer17hasDungeonHistoryESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(gcRank,"_ZN7CPlayer14getDungeonRankESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(gcDungeon,"_ZN16CResourceManager16getDungeonByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(gcWorld,"_ZN11CGameClient17findWorldLocationERN4Ogre7Vector3Eb")
TL_FUNCTION(gcDestination,"_ZN10CCharacter14setDestinationER6CLevelff")
TL_FUNCTION(gcMenuInput,"_ZN11CGameClient16processMenuInputEPvfb")
TL_FUNCTION(gcGameInput,"_ZN11CGameClient18processIngameInputEPvfb")
TL_FUNCTION(gcAlive,"_ZN10CCharacter5aliveEv")
TL_FUNCTION(gcISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(gcGetItem,"_ZN10CCharacter7getItemEP5CItemR6CLevel")
namespace {
#include "tests/CharacterEmptyGlobals.h"
struct Case{unsigned op,seed;};unsigned seed;bool armed;autotest::Capture*cap;CGameClient*client;CPlayer*player;CDungeon*dungeon;CLevel*level;CItem*items[5];
void num(unsigned n){if(armed)cap->add(&n,4);}void fp(float f){if(armed)cap->add(&f,4);}void wide(const std::wstring&s){num(s.size());if(armed)cap->add(s.data(),s.size()*4);}
void setSeed(int n){num(101);num(n);}
bool history(CPlayer*p,std::wstring name){num(103);num(p==player);wide(name);return seed%3==1;}
int rank(CPlayer*p,std::wstring name){num(107);num(p==player);wide(name);const int ranks[]={0,1,3,17,99,-2};return ranks[(seed/3)%6];}
CDungeon*findDungeon(CResourceManager*p,const std::wstring&name){num(109);num(p==client->m_gameResources);wide(name);return name==L"fallback"||seed%4?dungeon:NULL;}
bool world(CGameClient*p,Ogre::Vector3&result,bool input){num(113);num(p==client);num(input);result=player->m_vPosition;switch((seed/3)%5){case 1:result.x+=.25f;break;case 2:result.z-=3;break;case 3:result.y+=5;break;case 4:result.x=__builtin_nanf("");break;}return seed%3!=0;}
void destination(CCharacter*p,CLevel&w,float x,float z){num(127);num(p==player);num(&w==level);fp(x);fp(z);}
bool menuInput(CGameClient*p,void*w,float elapsed,bool enabled){num(131);num(p==client);num(w==client->m_window);fp(elapsed);num(enabled);return seed%3!=1;}
bool gameInput(CGameClient*p,void*w,float elapsed,bool enabled){num(137);num(p==client);num(w==client->m_window);fp(elapsed);num(enabled);return seed%3!=2;}
bool alive(CCharacter*p){num(139);num(p==player);return seed%3!=1;}
unsigned itemID(const void*p){for(unsigned i=0;i<5;++i)if(p==items[i])return i+1;return 99;}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){num(149);num(itemID(p));num(type);return ((seed>>itemID(p))&1)!=0;}
void getItem(CCharacter*p,CItem*item,CLevel&w){num(151);num(p==player);num(&w==level);num(itemID(item));
 // The real list node is removed here: saving next before the callback matters.
 TLinkedList<CItem*>*list=w.m_pendingItems;for(TLinkedListNode<CItem*>*n=list->m_pHead;n;n=n->m_pNext)if(n->m_Data==item){if(n->m_pPrevious)n->m_pPrevious->m_pNext=n->m_pNext;else list->m_pHead=n->m_pNext;if(n->m_pNext)n->m_pNext->m_pPrevious=n->m_pPrevious;delete n;break;}
}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;cap=&out;armed=false;finishlevel::Fixture w;level=&w.level;dungeon=new CDungeon;dungeon->m_sName=seed&1?L"DUNGEON":L"Башня";dungeon->m_iDungeonIndex=int(seed%11)-5;client->m_level=level;client->m_currentDungeon=seed&1?dungeon:NULL;client->m_gameSeed=int(seed*13)-311;client->m_levelDepth=int(seed%27)-8;
 detour::Set patch;
 if(c.op==0){TL_REDIRECT(patch,gcSetSeed,&setSeed);if(patch.failed())_exit(64);armed=true;typedef void(*F)(CGameClient*,int);F fn=ours?gcSeedNew:gcSeedOld;autotest::invoke(out,fn,client,seed%3?int(seed%15)-7:-1);return;}
 if(c.op==4){TL_REDIRECT(patch,gcMenuInput,&menuInput);TL_REDIRECT(patch,gcGameInput,&gameInput);if(patch.failed())_exit(64);client->m_gameState=static_cast<EGameState>(seed/2%8);client->m_window=&c;armed=true;typedef bool(*F)(CGameClient*,void*,float,bool);F fn=ours?gcInputNew:gcInputOld;if(autotest::beginInvocation(out,fn)){num(fn(client,client->m_window,float(int(seed%7)-3)*.03125f,seed&1));out.callCompleted=1;}return;}
 player=nativegame::createPlayer(client->m_gameResources);client->m_pPlayer=player;player->m_vPosition=Ogre::Vector3(float(seed%5)-2,7,float(seed%7)-3);player->m_moveInputHeld=seed&1;
 if(c.op==1||c.op==2){player->m_iUnitLevel=(seed/5)%23;const float scales[]={0,.25f,.5f,1,1.25f,3};dungeon->m_fMonsterLevelMultiplier=scales[seed%6];const int limits[]={0,1,4,30,-2};dungeon->m_iPlayerLevelMatchMin=limits[(seed/2)%5];dungeon->m_iPlayerLevelMatchMax=limits[(seed/7)%5];dungeon->m_iPlayerLevelMatchOffset=int(seed/11%9)-4;bool match=seed&1;if(match&&seed%13==0)client->m_pPlayer=NULL;TL_REDIRECT(patch,gcHistory,&history);TL_REDIRECT(patch,gcRank,&rank);TL_REDIRECT(patch,gcDungeon,&findDungeon);if(patch.failed())_exit(64);armed=true;
  if(c.op==1){typedef int(*F)(CGameClient*,int,CDungeon*,bool);F fn=ours?gcRankNew:gcRankOld;if(autotest::beginInvocation(out,fn)){num(fn(client,int(seed%17)-5,seed%9?dungeon:NULL,match));out.callCompleted=1;}}
  else{const wchar_t*names[]={L"",L"DUNGEON",L"Башня"};level->m_sDungeonName=L"fallback";if(seed%8==0)client->m_level=NULL;typedef int(*F)(CGameClient*,int,const std::wstring&,bool);F fn=ours?gcRankNameNew:gcRankNameOld;if(autotest::beginInvocation(out,fn)){num(fn(client,int(seed%17)-5,std::wstring(names[seed/4%3]),match));out.callCompleted=1;}}
 }else if(c.op==3){const float times[]={-.1f,0,.001f,.1f,__builtin_nanf("")};client->m_moveTimer=times[(seed/15)%5];TL_REDIRECT(patch,gcWorld,&world);TL_REDIRECT(patch,gcDestination,&destination);if(patch.failed())_exit(64);armed=true;typedef void(*F)(CGameClient*,bool);F fn=ours?gcMoveNew:gcMoveOld;autotest::invoke(out,fn,client,(seed&2)!=0);fp(client->m_moveTimer);
 }else{player->m_isPathing=(seed/3)%3!=0;if(seed%11==0)client->m_pPlayer=NULL;const float distances[]={0,2.999f,3,3.001f,__builtin_nanf("")};for(unsigned i=0;i<5;++i){finishlevel::Item*p=new finishlevel::Item(client->m_gameResources);items[i]=p;p->m_vPosition=player->m_vPosition;p->m_vPosition.x+=distances[(seed+i)%5];p->m_vPosition.y+=100+i;finishlevel::prepend(level->m_pendingItems,static_cast<CItem*>(p));}TL_REDIRECT(patch,gcAlive,&alive);TL_REDIRECT(patch,gcISA,&isa);TL_REDIRECT(patch,gcGetItem,&getItem);if(patch.failed())_exit(64);armed=true;typedef void(*F)(CGameClient*);F fn=ours?gcGoldNew:gcGoldOld;autotest::invoke(out,fn,client);std::vector<CItem*>identities(items,items+5);finishlevel::listState(out,level->m_pendingItems,identities);armed=false;finishlevel::clearNodes(level->m_pendingItems);for(unsigned i=0;i<5;++i)delete items[i];}
 armed=false;client->m_pPlayer=NULL;client->m_level=NULL;client->m_currentDungeon=NULL;patch.restore();nativegame::destroyPlayer(player);delete dungeon;
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
unsigned operation;const char*testName;uintptr_t address;unsigned count;
int worker(const tlhybrid_host*host){initEmptyGlobals();nativegame::Services native;if(!native.ready())return 1;menugui::Audio audio(native.master);menugui::Client owner(*native.settings,native.master,*native.master->m_pSoundManager);client=owner.client;autotest::Stats stats={0,0,0};autotest::Coverage coverage(testName,address);int failures=0;for(unsigned i=0;i<count;++i){Case c={operation,i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    client op%u seed%u status%d/%d child%d/%d started%u/%u completed%u/%u bytes%lu/%lu\n",operation,i,a.status,b.status,a.childStatus,b.childStatus,a.capture.callStarted,b.capture.callStarted,a.capture.callCompleted,b.capture.callCompleted,(unsigned long)a.capture.length,(unsigned long)b.capture.length);break;}}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=count);}
int run(const tlhybrid_host*h,unsigned op,const char*n,uintptr_t a,unsigned c){std::setlocale(LC_CTYPE,"C.UTF-8");operation=op;testName=n;address=a;count=c;return systems_fixture::isolated(&worker,h);}
}
TL_TEST(gameclient_seed){return run(host,0,"gameclient_seed",(uintptr_t)gcSeedOld,96);}
TL_TEST(gameclient_rank){return run(host,1,"gameclient_rank",(uintptr_t)gcRankOld,320);}
TL_TEST(gameclient_rank_name){return run(host,2,"gameclient_rank_name",(uintptr_t)gcRankNameOld,160);}
TL_TEST(gameclient_move){return run(host,3,"gameclient_move",(uintptr_t)gcMoveOld,150);}
TL_TEST(gameclient_input){return run(host,4,"gameclient_input",(uintptr_t)gcInputOld,64);}
TL_TEST(gameclient_gold){return run(host,5,"gameclient_gold",(uintptr_t)gcGoldOld,128);}
