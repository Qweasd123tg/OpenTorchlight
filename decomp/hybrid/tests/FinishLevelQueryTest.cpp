#include "FinishLevelFixture.h"
#include "DataGroup.h"
#include "EditorScene.h"
TL_ORIGINAL(CBaseUnit*,queryOld0,(CLevel*,CDataGroup*),"_ZN6CLevel22getBaseUnitByDataGroupEP10CDataGroup")
extern "C" CBaseUnit* queryNew0(CLevel*,CDataGroup*) __asm__("_ZN6CLevel22getBaseUnitByDataGroupEP10CDataGroup");
TL_ORIGINAL(CCharacter*,queryOld1,(CLevel*,long long),"_ZN6CLevel18getCharacterByGuidEx")
extern "C" CCharacter* queryNew1(CLevel*,long long) __asm__("_ZN6CLevel18getCharacterByGuidEx");
TL_ORIGINAL(CItem*,queryOld2,(CLevel*,long long,long long),"_ZN6CLevel13getItemByGuidExx")
extern "C" CItem* queryNew2(CLevel*,long long,long long) __asm__("_ZN6CLevel13getItemByGuidExx");
TL_ORIGINAL(void,queryOld3,(CLevel*,long long,bool),"_ZN6CLevel20makeQuestUnitsUncoolExb")
extern "C" void queryNew3(CLevel*,long long,bool) __asm__("_ZN6CLevel20makeQuestUnitsUncoolExb");
TL_ORIGINAL(CCharacter*,queryOld4,(CLevel*,long long,long long,int),"_ZN6CLevel26getCharacterByOriginalGuidExxi")
extern "C" CCharacter* queryNew4(CLevel*,long long,long long,int) __asm__("_ZN6CLevel26getCharacterByOriginalGuidExxi");
TL_ORIGINAL(CItem*,queryOld5,(CLevel*,long long,long long,int,long long),"_ZN6CLevel21getItemByOriginalGuidExxix")
extern "C" CItem* queryNew5(CLevel*,long long,long long,int,long long) __asm__("_ZN6CLevel21getItemByOriginalGuidExxix");
TL_ORIGINAL(CEditorScene*,queryOld6,(CLevel*,const Ogre::Vector3&),"_ZN6CLevel23getRoomThatPositionIsInERKN4Ogre7Vector3E")
extern "C" CEditorScene* queryNew6(CLevel*,const Ogre::Vector3&) __asm__("_ZN6CLevel23getRoomThatPositionIsInERKN4Ogre7Vector3E");
TL_ORIGINAL(bool,queryOld7,(CLevel*,const Ogre::Vector3&,float),"_ZN6CLevel17isInNoSpawnRegionERKN4Ogre7Vector3Ef")
extern "C" bool queryNew7(CLevel*,const Ogre::Vector3&,float) __asm__("_ZN6CLevel17isInNoSpawnRegionERKN4Ogre7Vector3Ef");
TL_ORIGINAL(void,queryOld8,(CLevel*,UNITTYPES::EUNITTYPES,TArrayList<CBaseUnit*>&),"_ZN6CLevel18getUnitsByUnitTypeEN9UNITTYPES10EUNITTYPESER10TArrayListIP9CBaseUnitE")
extern "C" void queryNew8(CLevel*,UNITTYPES::EUNITTYPES,TArrayList<CBaseUnit*>&) __asm__("_ZN6CLevel18getUnitsByUnitTypeEN9UNITTYPES10EUNITTYPESER10TArrayListIP9CBaseUnitE");
TL_ORIGINAL(void,queryOld9,(CLevel*,CDataGroup*,TArrayList<CBaseUnit*>&),"_ZN6CLevel23getBaseUnitsByDataGroupEP10CDataGroupR10TArrayListIP9CBaseUnitE")
extern "C" void queryNew9(CLevel*,CDataGroup*,TArrayList<CBaseUnit*>&) __asm__("_ZN6CLevel23getBaseUnitsByDataGroupEP10CDataGroupR10TArrayListIP9CBaseUnitE");
TL_ORIGINAL(void,queryOld10,(CLevel*,const Ogre::Vector3&,float,TArrayList<CCharacter*>&,TArrayList<CItem*>&),"_ZN6CLevel24getActiveUnitsAtPositionERKN4Ogre7Vector3EfR10TArrayListIP10CCharacterERS4_IP5CItemE")
extern "C" void queryNew10(CLevel*,const Ogre::Vector3&,float,TArrayList<CCharacter*>&,TArrayList<CItem*>&) __asm__("_ZN6CLevel24getActiveUnitsAtPositionERKN4Ogre7Vector3EfR10TArrayListIP10CCharacterERS4_IP5CItemE");
TL_ORIGINAL(void,queryOld11,(CLevel*,const Ogre::Vector3&,UNITTYPES::EUNITTYPES,EAlignment,float,bool,bool,TArrayList<CCharacter*>&),"_ZN6CLevel29getActiveCharactersAtPositionERKN4Ogre7Vector3EN9UNITTYPES10EUNITTYPESE10EAlignmentfbbR10TArrayListIP10CCharacterE")
extern "C" void queryNew11(CLevel*,const Ogre::Vector3&,UNITTYPES::EUNITTYPES,EAlignment,float,bool,bool,TArrayList<CCharacter*>&) __asm__("_ZN6CLevel29getActiveCharactersAtPositionERKN4Ogre7Vector3EN9UNITTYPES10EUNITTYPESE10EAlignmentfbbR10TArrayListIP10CCharacterE");
TL_FUNCTION(queryHierarchyISA,"_ZN16CResourceManager3ISAEN9UNITTYPES10EUNITTYPESES1_")
namespace finishquery {
struct Case{unsigned target,variant;};
static int hierarchyISA(CResourceManager*,UNITTYPES::EUNITTYPES unit,UNITTYPES::EUNITTYPES type){return unit==type || (int(type)==0x1d && int(unit)==0x22);}
static unsigned identity(const void* result,const std::vector<const void*>& ids){if(!result)return 0;for(unsigned i=0;i<ids.size();++i)if(ids[i]==result)return i+1;return ~0u;}
static void side(void* input,autotest::Capture& out,bool candidate){
 Case c=*static_cast<Case*>(input);finishlevel::Fixture f;
 CCharacter ch0(NULL),ch1(NULL),ch2(NULL);CCharacter* ch[]={&ch0,&ch1,&ch2};
 finishlevel::Item it0(NULL),it1(NULL),it2(NULL);CItem* it[]={&it0,&it1,&it2};
 CEditorScene scene0(L"owner0"),scene1(L"owner1");scene0.setOriginalGuid(70);scene1.setOriginalGuid(71);
 CDataGroup data0(L"D0",NULL,2,2,NULL),data1(L"D1",NULL,2,2,NULL);
 CPropertyNode region0(NULL),region1(NULL);region0.m_pResourceManager=&f.resources;region1.m_pResourceManager=&f.resources;region0.m_bounds.setExtents(Ogre::Vector3(-1,-1,-1),Ogre::Vector3(1,1,1));region1.m_bounds.setExtents(Ogre::Vector3(3,-2,1),Ogre::Vector3(5,2,3));
 detour::Set hierarchyBoundary;TL_REDIRECT(hierarchyBoundary,queryHierarchyISA,&hierarchyISA);if(hierarchyBoundary.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 std::vector<const void*> ids;for(unsigned i=0;i<3;++i)ids.push_back(ch[i]);for(unsigned i=0;i<3;++i)ids.push_back(it[i]);ids.push_back(&scene0);ids.push_back(&scene1);
 // Scalar ABI views provide external client/player context; no Player lifetime is claimed.
 union ClientView{long double align;char bytes[sizeof(CGameClient)];}clientStorage;union PlayerView{long double align;char bytes[sizeof(CPlayer)];}playerStorage;std::memset(&clientStorage,0,sizeof clientStorage);std::memset(&playerStorage,0,sizeof playerStorage);CGameClient*client=reinterpret_cast<CGameClient*>(clientStorage.bytes);CPlayer*player=reinterpret_cast<CPlayer*>(playerStorage.bytes);player->m_iGuid=100+c.variant%3;client->m_pPlayer=c.variant%4?player:NULL;if(c.target==1&&c.variant%5)f.level.m_pGameClient=client;ids.push_back(player);
 unsigned count=c.variant%4;
 for(unsigned i=0;i<3;++i){
  ch[i]->setGuid(100+i);it[i]->setGuid(200+i);ch[i]->setOriginalGuid(10+i%2);it[i]->setOriginalGuid(20+i%2);
  ch[i]->m_pDataGroup=i%2?&data1:&data0;it[i]->m_pDataGroup=i%2?&data1:&data0;
  ch[i]->m_iRoomIndex=(c.variant+i)%3-1;it[i]->m_iRoomIndex=(c.variant+i*2)%3-1;
  ch[i]->m_pSceneOwner=i==0?NULL:i==1?&scene0:&scene1;it[i]->m_pSceneOwner=i==0?NULL:i==1?&scene0:&scene1;
  ch[i]->m_iParentHierarchyHashCode=30+i;it[i]->m_iParentHierarchyHashCode=40+i;
  ch[i]->m_vPosition=Ogre::Vector3(float(i),float(i%2),float(i)*0.5f);it[i]->m_vPosition=Ogre::Vector3(float(i)-1,0,float(i));
  ch[i]->m_eUnitType=static_cast<UNITTYPES::EUNITTYPES>(i==1?0x29:0x1d);it[i]->m_eUnitType=static_cast<UNITTYPES::EUNITTYPES>(i==1?0x67:0x22);
  ch[i]->m_pResourceManager=&f.resources;it[i]->m_pResourceManager=&f.resources;
  ch[i]->m_alignment=static_cast<EAlignment>((i+c.variant)%3);ch[i]->m_eAIState=static_cast<EAIState>(i==1?5:i==2?6:0);
  it[i]->m_iQuestGuid=100+i%2;it[i]->m_bBaseUnitFlag190=false;
  if(i<count){finishlevel::prepend(f.level.m_pCharacters,ch[i]);finishlevel::prepend(f.level.m_items,it[i]);finishlevel::prepend(f.level.m_activeCharacters,ch[i]);finishlevel::prepend(f.level.m_activeItems,it[i]);}
 }
 if((c.target==0||c.target==1||c.target==9)&&c.variant%5==0){finishlevel::prepend<CCharacter*>(f.level.m_pCharacters,NULL);finishlevel::prepend<CItem*>(f.level.m_items,NULL);}
 f.level.m_RoomScenes.add(&scene0);f.level.m_RoomScenes.add(&scene1);f.level.m_roomBounds.add(Ogre::AxisAlignedBox(Ogre::Vector3(-2,-2,-2),Ogre::Vector3(0.5f,2,0.5f)));f.level.m_roomBounds.add(Ogre::AxisAlignedBox(Ogre::Vector3(0.5f,-2,0.5f),Ogre::Vector3(3,2,3)));
 if(c.variant%3){f.level.m_noSpawnRegions.push_back(&region0);if(c.variant%2)f.level.m_noSpawnRegions.push_back(&region1);}
 CDataGroup*group=c.variant%4==0?NULL:c.variant%4==1?&data1:&data0;
 long long guid=99+c.variant%6,original=(c.target==4?9:19)+c.variant%4,parent=c.variant%3==0?-1:69+c.variant%4,hierarchy=c.variant%4==0?0:39+c.variant%5;int room=int(c.variant%4)-1;
 // Exercise the player-only hit and the player/list duplicate with distinct identities.
 if(c.target==1){unsigned mode=c.variant%8;f.level.m_pGameClient=mode?client:NULL;client->m_pPlayer=mode==1?NULL:player;player->m_iGuid=mode==3?100:777;guid=(mode==2||mode==6)?777:mode==3?100:mode==4?101:999;}
 const float coordinates[]={-2,-1,0,0.5f,1,2,3,5};Ogre::Vector3 point(coordinates[c.variant%8],0,coordinates[(c.variant/4)%8]);
 const float radii[]={-1,0,0.5f,1,2,5};float radius=radii[(c.variant/16)%6];
 UNITTYPES::EUNITTYPES type=static_cast<UNITTYPES::EUNITTYPES>(c.variant%3==0?0x1d:c.variant%3==1?0x29:0x67);EAlignment alignment=static_cast<EAlignment>((c.variant/4)%4);
 TArrayList<CBaseUnit*> units;TArrayList<CCharacter*> chars;TArrayList<CItem*> items;if(c.variant%2){units.add(&ch2);chars.add(&ch2);items.add(&it2);}
 switch(c.target){
 case 0:{typedef CBaseUnit*(*Fn)(CLevel*,CDataGroup*);Fn fn=candidate?&queryNew0:&queryOld0;if(!autotest::beginInvocation(out,fn))return;CBaseUnit* result=fn(&f.level,group);out.callCompleted=1;finishlevel::number(out,identity(result,ids));break;}
 case 1:{typedef CCharacter*(*Fn)(CLevel*,long long);Fn fn=candidate?&queryNew1:&queryOld1;if(!autotest::beginInvocation(out,fn))return;CCharacter* result=fn(&f.level,guid);out.callCompleted=1;finishlevel::number(out,identity(result,ids));break;}
 case 2:{typedef CItem*(*Fn)(CLevel*,long long,long long);Fn fn=candidate?&queryNew2:&queryOld2;if(!autotest::beginInvocation(out,fn))return;CItem* result=fn(&f.level,original,parent);out.callCompleted=1;finishlevel::number(out,identity(result,ids));break;}
 case 3:if(candidate)autotest::invoke<void(*)(CLevel*,long long,bool),CLevel*,long long,bool>(out,queryNew3,&f.level,guid,bool(c.variant%2));else autotest::invoke<void(*)(CLevel*,long long,bool),CLevel*,long long,bool>(out,queryOld3,&f.level,guid,bool(c.variant%2));break;
 case 4:{typedef CCharacter*(*Fn)(CLevel*,long long,long long,int);Fn fn=candidate?&queryNew4:&queryOld4;if(!autotest::beginInvocation(out,fn))return;CCharacter* result=fn(&f.level,original,parent,room);out.callCompleted=1;finishlevel::number(out,identity(result,ids));break;}
 case 5:{typedef CItem*(*Fn)(CLevel*,long long,long long,int,long long);Fn fn=candidate?&queryNew5:&queryOld5;if(!autotest::beginInvocation(out,fn))return;CItem* result=fn(&f.level,original,parent,room,hierarchy);out.callCompleted=1;finishlevel::number(out,identity(result,ids));break;}
 case 6:{typedef CEditorScene*(*Fn)(CLevel*,const Ogre::Vector3&);Fn fn=candidate?&queryNew6:&queryOld6;if(!autotest::beginInvocation(out,fn))return;CEditorScene* result=fn(&f.level,point);out.callCompleted=1;finishlevel::number(out,identity(result,ids));break;}
 case 7:if(candidate)autotest::invoke<bool(*)(CLevel*,const Ogre::Vector3&,float),CLevel*,const Ogre::Vector3&,float>(out,queryNew7,&f.level,point,radius);else autotest::invoke<bool(*)(CLevel*,const Ogre::Vector3&,float),CLevel*,const Ogre::Vector3&,float>(out,queryOld7,&f.level,point,radius);break;
 case 8:if(candidate)autotest::invoke<void(*)(CLevel*,UNITTYPES::EUNITTYPES,TArrayList<CBaseUnit*>&),CLevel*,UNITTYPES::EUNITTYPES,TArrayList<CBaseUnit*>&>(out,queryNew8,&f.level,type,units);else autotest::invoke<void(*)(CLevel*,UNITTYPES::EUNITTYPES,TArrayList<CBaseUnit*>&),CLevel*,UNITTYPES::EUNITTYPES,TArrayList<CBaseUnit*>&>(out,queryOld8,&f.level,type,units);break;
 case 9:if(candidate)autotest::invoke<void(*)(CLevel*,CDataGroup*,TArrayList<CBaseUnit*>&),CLevel*,CDataGroup*,TArrayList<CBaseUnit*>&>(out,queryNew9,&f.level,group,units);else autotest::invoke<void(*)(CLevel*,CDataGroup*,TArrayList<CBaseUnit*>&),CLevel*,CDataGroup*,TArrayList<CBaseUnit*>&>(out,queryOld9,&f.level,group,units);break;
 case 10:if(candidate)autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&,float,TArrayList<CCharacter*>&,TArrayList<CItem*>&),CLevel*,const Ogre::Vector3&,float,TArrayList<CCharacter*>&,TArrayList<CItem*>&>(out,queryNew10,&f.level,point,radius,chars,items);else autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&,float,TArrayList<CCharacter*>&,TArrayList<CItem*>&),CLevel*,const Ogre::Vector3&,float,TArrayList<CCharacter*>&,TArrayList<CItem*>&>(out,queryOld10,&f.level,point,radius,chars,items);break;
 case 11:if(candidate)autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&,UNITTYPES::EUNITTYPES,EAlignment,float,bool,bool,TArrayList<CCharacter*>&),CLevel*,const Ogre::Vector3&,UNITTYPES::EUNITTYPES,EAlignment,float,bool,bool,TArrayList<CCharacter*>&>(out,queryNew11,&f.level,point,type,alignment,radius,bool(c.variant%2),bool(c.variant%4/2),chars);else autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&,UNITTYPES::EUNITTYPES,EAlignment,float,bool,bool,TArrayList<CCharacter*>&),CLevel*,const Ogre::Vector3&,UNITTYPES::EUNITTYPES,EAlignment,float,bool,bool,TArrayList<CCharacter*>&>(out,queryOld11,&f.level,point,type,alignment,radius,bool(c.variant%2),bool(c.variant%4/2),chars);break;
 }
 finishlevel::number(out,units.size());for(unsigned i=0;i<units.size();++i)finishlevel::number(out,identity(units[i],ids));
 finishlevel::number(out,chars.size());for(unsigned i=0;i<chars.size();++i)finishlevel::number(out,identity(chars[i],ids));
 finishlevel::number(out,items.size());for(unsigned i=0;i<items.size();++i)finishlevel::number(out,identity(items[i],ids));
 for(unsigned i=0;i<3;++i){finishlevel::number(out,ch[i]->m_iRoomIndex);finishlevel::number(out,it[i]->m_iRoomIndex);finishlevel::number(out,it[i]->m_bBaseUnitFlag190);ch[i]->m_pResourceManager=NULL;it[i]->m_pResourceManager=NULL;ch[i]->m_pSceneOwner=NULL;it[i]->m_pSceneOwner=NULL;}
}
static void original(void*p,autotest::Capture&o){side(p,o,false);}static void ours(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(finish_level_query_935f10){autotest::Coverage coverage("finish_level_query_935f10",0x935f10);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishquery::Case c={0,n};autotest::compareCase(finishquery::original,finishquery::ours,&c,stats,host,"query",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_query_935f80){autotest::Coverage coverage("finish_level_query_935f80",0x935f80);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishquery::Case c={1,n};autotest::compareCase(finishquery::original,finishquery::ours,&c,stats,host,"query",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_query_9362b0){autotest::Coverage coverage("finish_level_query_9362b0",0x9362b0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishquery::Case c={2,n};autotest::compareCase(finishquery::original,finishquery::ours,&c,stats,host,"query",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_query_9365c0){autotest::Coverage coverage("finish_level_query_9365c0",0x9365c0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishquery::Case c={3,n};autotest::compareCase(finishquery::original,finishquery::ours,&c,stats,host,"query",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_query_944ed0){autotest::Coverage coverage("finish_level_query_944ed0",0x944ed0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishquery::Case c={4,n};autotest::compareCase(finishquery::original,finishquery::ours,&c,stats,host,"query",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_query_944fe0){autotest::Coverage coverage("finish_level_query_944fe0",0x944fe0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishquery::Case c={5,n};autotest::compareCase(finishquery::original,finishquery::ours,&c,stats,host,"query",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_query_945110){autotest::Coverage coverage("finish_level_query_945110",0x945110);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishquery::Case c={6,n};autotest::compareCase(finishquery::original,finishquery::ours,&c,stats,host,"query",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_query_9453f0){autotest::Coverage coverage("finish_level_query_9453f0",0x9453f0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishquery::Case c={7,n};autotest::compareCase(finishquery::original,finishquery::ours,&c,stats,host,"query",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_query_949540){autotest::Coverage coverage("finish_level_query_949540",0x949540);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishquery::Case c={8,n};autotest::compareCase(finishquery::original,finishquery::ours,&c,stats,host,"query",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_query_94a660){autotest::Coverage coverage("finish_level_query_94a660",0x94a660);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishquery::Case c={9,n};autotest::compareCase(finishquery::original,finishquery::ours,&c,stats,host,"query",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_query_948430){autotest::Coverage coverage("finish_level_query_948430",0x948430);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishquery::Case c={10,n};autotest::compareCase(finishquery::original,finishquery::ours,&c,stats,host,"query",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_query_949230){autotest::Coverage coverage("finish_level_query_949230",0x949230);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishquery::Case c={11,n};autotest::compareCase(finishquery::original,finishquery::ours,&c,stats,host,"query",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
