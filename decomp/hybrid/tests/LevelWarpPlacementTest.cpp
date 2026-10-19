#include "tests/FinishLevelFixture.h"
#include "NativeMenuClient.h"
#include "tests/SystemsFixtureWorker.h"
#include "Warper.h"
#include "EditorScene.h"
TL_ORIGINAL(int,wpOld,(CLevel*,std::wstring,int,bool,std::wstring),"_ZN6CLevel31placePlayerAtWarpToDungeonFloorESbIwSt11char_traitsIwESaIwEEibS3_")
extern "C" int wpNew(CLevel*,std::wstring,int,bool,std::wstring) __asm__("_ZN6CLevel31placePlayerAtWarpToDungeonFloorESbIwSt11char_traitsIwESaIwEEibS3_");
TL_FUNCTION(wpObjects,"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEEP10TArrayListIP17CEditorBaseObjectE")
TL_FUNCTION(wpPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(wpDirection,"_ZN19CPositionableObject12setDirectionEN4Ogre7Vector3E")
namespace {
autotest::Capture*output;menugui::Client*client;CPlayer*player;unsigned seed;CEditorScene*scenes[3];std::vector<CEditorBaseObject*>objects[3];
void number(unsigned x){output->add(&x,4);}void vector(const Ogre::Vector3&v){output->add(&v,sizeof v);}void text(const std::wstring&s){number(s.size());if(s.size())output->add(s.data(),s.size()*sizeof(wchar_t));}
void position(CPositionableObject*p,const Ogre::Vector3&v){number(2);number(p==player);vector(v);p->m_vPosition=v;}
void direction(CPositionableObject*p,Ogre::Vector3 v){number(3);number(p==player);vector(v);p->m_vForward=v;}
void query(CEditorScene*p,const std::wstring&name,TArrayList<CEditorBaseObject*>*out){unsigned i=0;while(i<3&&scenes[i]!=p)++i;number(1);number(i);text(name);number(out->size());number(out->m_nCapacity);if(i>=3)std::abort();for(unsigned j=0;j<objects[i].size();++j)out->add(objects[i][j]);}
struct Warp:CWarper{unsigned index;Warp(CResourceManager*r,unsigned i):CWarper(r),index(i){}virtual Ogre::Vector3 getForwardAbsolute(){number(4);number(index);return Ogre::Vector3(float(index+1),float(int(seed%7)-3),float(index)*-.5f);}};
const wchar_t*names[]={L"",L"Entry",L"ENTRY",L"Other",L"\x041b\x0435\x0441"};
const wchar_t*dungeons[]={L"",L"MAIN",L"main",L"TOWN",L"town",L"\x041b\x0435\x0441"};
void initializedText(uintptr_t address){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(address),8);if(!p)new(reinterpret_cast<void*>(address))std::wstring;}
void execute(void*raw,autotest::Capture&out,bool ours){
 output=&out;seed=*static_cast<unsigned*>(raw);initializedText(0x149eb48);initializedText(0x1492210);
 finishlevel::Fixture f;f.resources.m_pSceneManager=client->scenes[0];CStringTranslate translation(L"");player=nativegame::createPlayer(&f.resources);
 CPlayer*previous=client->client->m_pPlayer;client->client->m_pPlayer=seed%11?player:NULL;f.level.m_pGameClient=client->client;
 f.level.m_iLevelDepth=int(seed%9)-4;f.level.m_dungeonDepth=12345;f.level.m_sDungeonName=dungeons[(seed/7)%6];f.level.m_RoomScenes.clear();
 Warp*warps[5];CEditorBaseObject wrong;
 for(unsigned i=0;i<5;++i){warps[i]=new Warp(&f.resources,i);warps[i]->SetName(names[(seed/3+i)%5]);warps[i]->m_sWarpName=L"unrelated-destination-name";warps[i]->m_sDungeon=dungeons[(seed/11+i)%6];warps[i]->m_iLevelDelta=int((seed/17+i)%5)-2;warps[i]->m_iLevelDepth=int((seed/23+i)%5)-2;warps[i]->setPosition(Ogre::Vector3(float(i*7+1),float(i)-.75f,float(i)*-.25f));}
 for(unsigned i=0;i<3;++i){scenes[i]=new CEditorScene(L"warp-placement");objects[i].clear();unsigned n=(seed+i)%8;for(unsigned j=0;j<n;++j)objects[i].push_back(j%7==5?NULL:j%7==6?&wrong:static_cast<CEditorBaseObject*>(warps[(j+i)%5]));if(i<seed%4)f.level.m_RoomScenes.add((seed+i)%7?scenes[i]:NULL);}
 player->m_vPosition=Ogre::Vector3(-71,-72,-73);player->m_vForward=Ogre::Vector3(7,8,9);
 detour::Set hooks;TL_REDIRECT(hooks,wpObjects,&query);TL_REDIRECT(hooks,wpPosition,&position);TL_REDIRECT(hooks,wpDirection,&direction);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef int(*Fn)(CLevel*,std::wstring,int,bool,std::wstring);Fn fn=ours?wpNew:wpOld;std::wstring dungeon=dungeons[seed%6],entry=names[seed/6%5];int floor=int(seed/30%11)-5;
 if(seed>=1320){
  dungeon=L"MAIN";entry=L"";floor=4;f.level.m_iLevelDepth=3;f.level.m_sDungeonName=L"MAIN";client->client->m_pPlayer=player;
  f.level.m_RoomScenes.clear();f.level.m_RoomScenes.add(scenes[0]);for(unsigned i=0;i<3;++i)objects[i].clear();objects[0].push_back(warps[0]);
  warps[0]->m_sDungeon=L"MAIN";warps[0]->m_iLevelDelta=1;warps[0]->m_iLevelDepth=0;
  if(seed&1){warps[0]->m_iLevelDelta=0;warps[0]->m_iLevelDepth=4;}
  if(seed&2){dungeon=L"TOWN";warps[0]->m_sDungeon=L"TOWN";warps[0]->m_iLevelDelta=0;warps[0]->m_iLevelDepth=0;}
 }
 if(!autotest::beginInvocation(out,fn))return;int result=fn(&f.level,dungeon,floor,seed&1,entry);out.callCompleted=1;number(result);vector(player->m_vPosition);vector(player->m_vForward);
 hooks.restore();client->client->m_pPlayer=previous;f.level.m_pGameClient=NULL;f.level.m_RoomScenes.clear();for(unsigned i=0;i<3;++i){delete scenes[i];objects[i].clear();}for(unsigned i=0;i<5;++i)delete warps[i];nativegame::destroyPlayer(player);
}
void original(void*p,autotest::Capture&o){execute(p,o,false);}void candidate(void*p,autotest::Capture&o){execute(p,o,true);}
int run(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;CMasterResourceManager*master=CMasterResourceManager::getSingleton();menugui::Audio audio(master);menugui::Client native(*master->m_pSettings,master,*master->m_pSoundManager);client=&native;autotest::Coverage coverage("level_warp_placement",(uintptr_t)&wpOld);for(unsigned i=0;i<1384;++i){autotest::Outcome a,b;autotest::runChild(original,&i,a);autotest::runChild(candidate,&i,b);if(coverage.observe(host,a,b)){host->log("    warp seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(level_warp_placement){return systems_fixture::isolated(&run,host);}
