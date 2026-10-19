#include "CompleteQuestFixture.h"
#define CQ_PAIR(R,N,A,S) TL_ORIGINAL(R,cqOld##N,A,S) extern "C" R cqNew##N A __asm__(S);
CQ_PAIR(int,Floor,(CQuest*),"_ZN6CQuest18getDungeonMaxFloorEv")
CQ_PAIR(long long,Random,(CQuest*),"_ZN6CQuest23getQuestHasRandomPiecesEv")
CQ_PAIR(int,XP,(CQuest*),"_ZN6CQuest16getQuestRewardXPEv")
CQ_PAIR(int,Fame,(CQuest*),"_ZN6CQuest18getQuestRewardFameEv")
CQ_PAIR(int,Gold,(CQuest*),"_ZN6CQuest18getQuestRewardGoldEv")
CQ_PAIR(void,Accepted,(CQuest*,bool),"_ZN6CQuest16setQuestAcceptedEb")
CQ_PAIR(void,DialogCleanup,(CQuest*,TArrayList<CQuestDialog*>&),"_ZN6CQuest13cleanUpDialogER10TArrayListIP12CQuestDialogE")
CQ_PAIR(void,Populate,(CQuest*,CLevel*),"_ZN6CQuest8populateEP6CLevel")
CQ_PAIR(long long,Dialog,(CQuest*,CBaseUnit*),"_ZN6CQuest14getQuestDialogEP9CBaseUnit")
CQ_PAIR(int,Valid,(CQuest*,CBaseUnit*),"_ZN6CQuest21getQuestIsValidForNPCEP9CBaseUnit")
CQ_PAIR(void,Initialize,(CQuest*,CBaseUnit*),"_ZN6CQuest22initializeQuestWithNPCEP9CBaseUnit")
CQ_PAIR(void,Cleanup,(CQuest*,bool),"_ZN6CQuest7cleanUpEb")
CQ_PAIR(void,Reward,(CQuest*),"_ZN6CQuest18giveRewardForQuestEv")
#undef CQ_PAIR
TL_FUNCTION(cqDeepest,"_ZN14CQuestUnitData15getDeepestFloorEv")
TL_FUNCTION(cqRandom,"_ZN14CQuestUnitData11getIsRandomEv")
TL_FUNCTION(cqCalculate,"_ZN13CQuestRewards16calculateRewardsEv")
TL_FUNCTION(cqEvent,"_ZN13CQuestManager16questEventUpdateE13EQUEST_EVENTSP10CCharacterP9CBaseUnit")
TL_FUNCTION(cqCleanDialog,"_ZN12CQuestDialog7cleanUpEv")
TL_FUNCTION(cqPopUnit,"_ZN14CQuestUnitData8populateEP6CLevel")
TL_FUNCTION(cqPopDialog,"_ZN12CQuestDialog8populateEv")
TL_FUNCTION(cqForNPC,"_ZN12CQuestDialog14dialogIsForNPCEP9CBaseUnit")
TL_FUNCTION(cqComplete,"_ZN6CQuest10isCompleteEb")
TL_FUNCTION(cqRequirements,"_ZN18CQuestRequirements27questRequirmentsHaveBeenMetEv")
TL_FUNCTION(cqGetDialog,"_ZN6CQuest14getQuestDialogEP9CBaseUnit")
TL_FUNCTION(cqHasQuest,"_ZN13CQuestManager17getPlayerHasQuestEP6CQuest")
TL_FUNCTION(cqDungeon,"_ZN16CResourceManager16getDungeonByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cqClearHistory,"_ZN7CPlayer19clearDungeonHistoryESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cqStored,"_ZN7CPlayer18updateStoredLevelsER6CLevel")
TL_FUNCTION(cqRank,"_ZN11CGameClient24getRankOfMonstersOnFloorEiP8CDungeonb")
TL_FUNCTION(cqVolatile,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(cqReinit,"_ZN6CQuest17reinitializeQuestEbb")
TL_FUNCTION(cqRewardReinit,"_ZN13CQuestRewards19reInitializeRewardsEv")
TL_FUNCTION(cqRemove,"_ZN7CPlayer49removeQuestItemFromInventoryOrPetsInventoryByGuidExxbbN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(cqUncool,"_ZN6CLevel20makeQuestUnitsUncoolExb")
TL_FUNCTION(cqCleanUnit,"_ZN14CQuestUnitData24cleanUpForQuestRemoveallEb")
TL_FUNCTION(cqJournal,"_ZN7CPlayer25incrementJournalStatisticE17EJournalStatistici")
TL_FUNCTION(cqRewardPlayer,"_ZN13CQuestRewards12rewardPlayerEv")
TL_FUNCTION(cqLookup,"_ZN13CQuestManager14getQuestByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cqGive,"_ZN13CQuestManager9giveQuestEP6CQuestP9CBaseUnitb")
TL_FUNCTION(cqAccept,"_ZN6CQuest16setQuestAcceptedEb")
TL_FUNCTION(cqCleanup,"_ZN6CQuest7cleanUpEb")
namespace {
using namespace smallmass;unsigned seed,mode,calls;Ogre::SceneManager*scene;CQuest*self,*next;CQuestManager*manager,*otherManager;CResourceManager*resources,*alternate;CPlayer*player;CLevel*level;CDungeon*dungeon;CQuestRewards*reward,*otherReward;CBaseUnit*npc;CGameClient*client;std::vector<CQuestUnitData*>units;std::vector<CQuestDialog*>dialogs;
int unitID(CQuestUnitData*p){for(unsigned i=0;i<units.size();++i)if(p==units[i])return i;return -1;}
int dialogID(CQuestDialog*p){for(unsigned i=0;i<dialogs.size();++i)if(p==dialogs[i])return i;return -1;}
int ownerID(CQuest*p){return p==self?0:p==next?1:p?2:-1;}
void event(unsigned tag){number(tag);}
int deepest(CQuestUnitData*p){event(1);number(unitID(p));const int depths[]={INT_MIN,-1,0,1,8,INT_MAX};return depths[(seed+unitID(p))%6];}
bool randomUnit(CQuestUnitData*p){event(2);number(unitID(p));return (seed+unitID(p))%5==0;}
void calculate(CQuestRewards*p){event(3);number(p==reward);if(seed&16)self->m_pQuestRewards=otherReward;}
void questEvent(CQuestManager*p,EQUEST_EVENTS e,CCharacter*a,CBaseUnit*b){event(4);number(p==manager);number(e);number(a==NULL);number(b==NULL);number(self->m_questAccepted);}
void cleanDialog(CQuestDialog*p){event(5);number(dialogID(p));p->m_bDialogInitialized=false;if((seed&128)&&mode==5&&calls++==0)self->m_acceptDialogs.removeAt(0);}
void populateUnit(CQuestUnitData*p,CLevel*l){event(6);number(unitID(p));number(l==level);}
void populateDialog(CQuestDialog*p){event(7);number(dialogID(p));p->m_bDialogInitialized=true;}
bool forNPC(CQuestDialog*p,CBaseUnit*u){event(8);number(dialogID(p));number(u==npc);bool match=((seed>>((unsigned(dialogID(p))%8)+2))&1)!=0;if(seed&2048){self->m_questAccepted=(calls++%3)==0;}return match;}
long long complete(CQuest*p,bool force){event(9);number(ownerID(p));number(force);return(seed&1)!=0;}
char requirements(CQuestRequirements*p){event(10);number(p==self->m_pQuestRequirements);if(seed&128)self->m_bUnknown20B=true;return(seed&4)!=0;}
long long selected(CQuest*p,CBaseUnit*u){event(11);number(ownerID(p));number(u==npc);return seed&8?reinterpret_cast<long long>(dialogs[0]):0;}
bool hasQuest(CQuestManager*p,CQuest*q){event(12);number(p==manager);number(ownerID(q));return(seed&2)!=0;}
CDungeon*findDungeon(CResourceManager*p,const std::wstring&s){event(13);number(p==resources);text(s);return seed&4?dungeon:NULL;}
void clearHistory(CPlayer*p,std::wstring s){event(14);number(p==player);text(s);if(seed&256)self->m_pQuestManager=otherManager;}
void stored(CPlayer*p,CLevel&l){event(15);number(p==player);number(&l==level);}
int rank(CGameClient*p,int floor,CDungeon*d,bool flag){event(16);number(p==client);number(floor);number(d==dungeon);number(flag);return 17+(seed%13);}
int volatileRandom(int a,int b){event(17);number(a);number(b);return int(seed)*137-103;}
void reinit(CQuest*p,bool a,bool b){event(18);number(ownerID(p));number(a);number(b);if(seed&512)p->m_bUnknown2D=true;}
void rewardReinit(CQuestRewards*p){event(19);number(p==reward);number(self->m_bUnknown2D);}
bool remove(CPlayer*p,long long quest,long long guid,bool a,bool b,UNITTYPES::EUNITTYPES t){event(20);number(p==player);output->add(&quest,8);output->add(&guid,8);number(a);number(b);number(t);if(seed&256)self->m_pQuestManager=otherManager;return true;}
void uncool(CLevel*p,long long q,bool flag){event(21);number(p==level);output->add(&q,8);number(flag);}
void cleanUnit(CQuestUnitData*p,bool flag){event(22);number(unitID(p));number(flag);}
void journal(CPlayer*p,EJournalStatistic stat,int count){event(23);number(p==player);number(stat);number(count);}
void rewardPlayer(CQuestRewards*p){event(24);number(p==reward);}
long long lookup(CQuestManager*p,const std::wstring&s){event(25);number(p==manager?0:p==otherManager?1:2);text(s);if(seed&128)self->m_pQuestManager=otherManager;return s==L"MISSING"?0:reinterpret_cast<long long>(next);}
void give(CQuestManager*p,CQuest*q,CBaseUnit*u,bool f){event(26);number(p==manager?0:p==otherManager?1:2);number(ownerID(q));number(u==NULL);number(f);}
void accept(CQuest*p,bool flag){event(27);number(ownerID(p));number(flag);}
void cleanup(CQuest*p,bool flag){event(28);number(ownerID(p));number(flag);}
void fill(CQuest*q){units.clear();dialogs.clear();TArrayList<TArrayList<CQuestUnitData*>*>*outer[]={&q->m_Unknown130,&q->m_Unknown148,&q->m_Unknown160};for(unsigned f=0;f<3;++f)for(unsigned i=0;i<(seed/(f+1))%3;++i){TArrayList<CQuestUnitData*>*list=new TArrayList<CQuestUnitData*>(1);outer[f]->add(list);for(unsigned j=0;j<(seed+i+f)%4;++j){CQuestUnitData*u=new CQuestUnitData(q);units.push_back(u);list->add(u);}}TArrayList<CQuestDialog*>*lists[]={&q->m_acceptDialogs,&q->m_Unknown78,&q->m_Unknown90,&q->m_UnknownA8};for(unsigned f=0;f<4;++f)for(unsigned i=0;i<2;++i){CQuestDialog*d=new CQuestDialog(q);d->m_bDialogInitialized=((seed>>(i+f))&1)!=0;dialogs.push_back(d);lists[f]->add(d);}}
void side(Case&c,bool ours,autotest::Capture&out){output=&out;seed=c.index;mode=c.op;calls=0;completequest::init();finishlevel::Fixture fixture;resources=&fixture.resources;resources->m_pSceneManager=scene;level=&fixture.level;CResourceManager other(NULL);alternate=&other;completequest::Manager m(resources),m2(resources);manager=m.p;otherManager=m2.p;completequest::Quest q(resources,manager),n(resources,manager);self=q.p;next=n.p;fill(self);self->m_pUnknown30=L"DUNGEON";self->m_iUnknown20=(seed%5==0)?INT_MIN:int(seed%19)-4;self->m_questAccepted=seed&2;self->m_bUnknown2D=seed&8;self->m_iUnknown1C8=0x123456789abcdefLL;self->m_iUnknown20C=777;self->m_iUnknown1C=123;CQuestRewards rw(self),rw2(self);reward=&rw;otherReward=&rw2;CQuestRewards*savedReward=self->m_pQuestRewards;self->m_pQuestRewards=seed%3?reward:NULL;unsigned fp[]={0u,0x3fc00000u,0xbfc00000u,0x4effffffu,0x4f000000u,0x7f800000u,0xff800000u,0x7fc12345u};rw.m_fExperience=bits(fp[seed%8]);rw.m_fGold=bits(fp[(seed/8)%8]);rw.m_fFame=bits(fp[(seed/4)%8]);CCharacter actor(NULL);CDataGroup npcData(L"NPC",NULL,1,1,NULL);actor.m_pDataGroup=&npcData;npc=&actor;CDungeon d;dungeon=&d;unsigned clientIdentity=0;client=reinterpret_cast<CGameClient*>(&clientIdentity);if(seed&16)field<TArrayList<CGameClient*> >(resources,0x28).add(client);self->m_iUnknown1E8=seed&32?reinterpret_cast<long long>(&npcData):0;
 bool needsPlayer=mode>=9;player=needsPlayer?nativegame::createPlayer(resources):NULL;manager->m_pPlayer=otherManager->m_pPlayer=player;if(needsPlayer&&(seed%31==0))manager->m_pPlayer=NULL;if(mode==9){self->m_bUnknown20A=seed&8;if(seed&64)self->m_pQuestRewards=NULL;}if(mode==10){self->m_bUnknown20A=seed&8;if(seed&64){self->m_bUnknown20A=false;if(seed&128&&player)player->m_pResourceManager=NULL;else resources->m_pLevel=NULL;}}if(mode==11){self->m_Unknown1F0.add(L"next");self->m_Unknown1F0.add(L"MISSING");self->m_Unknown1F0.add(L"NeXt2");}
 detour::Set hooks;TL_REDIRECT(hooks,cqDeepest,&deepest);TL_REDIRECT(hooks,cqRandom,&randomUnit);TL_REDIRECT(hooks,cqCalculate,&calculate);TL_REDIRECT(hooks,cqEvent,&questEvent);TL_REDIRECT(hooks,cqCleanDialog,&cleanDialog);TL_REDIRECT(hooks,cqPopUnit,&populateUnit);TL_REDIRECT(hooks,cqPopDialog,&populateDialog);TL_REDIRECT(hooks,cqForNPC,&forNPC);TL_REDIRECT(hooks,cqComplete,&complete);TL_REDIRECT(hooks,cqRequirements,&requirements);if(mode==8)TL_REDIRECT(hooks,cqGetDialog,&selected);TL_REDIRECT(hooks,cqHasQuest,&hasQuest);TL_REDIRECT(hooks,cqDungeon,&findDungeon);TL_REDIRECT(hooks,cqClearHistory,&clearHistory);TL_REDIRECT(hooks,cqStored,&stored);TL_REDIRECT(hooks,cqRank,&rank);TL_REDIRECT(hooks,cqVolatile,&volatileRandom);TL_REDIRECT(hooks,cqReinit,&reinit);TL_REDIRECT(hooks,cqRewardReinit,&rewardReinit);TL_REDIRECT(hooks,cqRemove,&remove);TL_REDIRECT(hooks,cqUncool,&uncool);TL_REDIRECT(hooks,cqCleanUnit,&cleanUnit);TL_REDIRECT(hooks,cqJournal,&journal);TL_REDIRECT(hooks,cqRewardPlayer,&rewardPlayer);TL_REDIRECT(hooks,cqLookup,&lookup);TL_REDIRECT(hooks,cqGive,&give);if(mode==11){TL_REDIRECT(hooks,cqAccept,&accept);TL_REDIRECT(hooks,cqCleanup,&cleanup);}if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(mode==0){typedef int(*Fn)(CQuest*);Fn f=ours?cqNewFloor:cqOldFloor;if(!autotest::beginInvocation(out,f))return;number(f(self));}
 else if(mode==1){typedef long long(*Fn)(CQuest*);Fn f=ours?cqNewRandom:cqOldRandom;if(!autotest::beginInvocation(out,f))return;long long r=f(self);out.add(&r,8);}
 else if(mode==2||mode==3||mode==12){typedef int(*Fn)(CQuest*);Fn f=ours?(mode==2?cqNewXP:mode==3?cqNewGold:cqNewFame):(mode==2?cqOldXP:mode==3?cqOldGold:cqOldFame);if(!autotest::beginInvocation(out,f))return;number(f(self));}
 else if(mode==4){typedef void(*Fn)(CQuest*,bool);Fn f=ours?cqNewAccepted:cqOldAccepted;if(!autotest::beginInvocation(out,f))return;f(self,seed&1);number(self->m_questAccepted);for(unsigned i=0;i<dialogs.size();++i)number(dialogs[i]->m_bDialogInitialized);}
 else if(mode==5){typedef void(*Fn)(CQuest*,TArrayList<CQuestDialog*>&);Fn f=ours?cqNewDialogCleanup:cqOldDialogCleanup;if(!autotest::beginInvocation(out,f))return;f(self,self->m_acceptDialogs);}
 else if(mode==6){typedef void(*Fn)(CQuest*,CLevel*);Fn f=ours?cqNewPopulate:cqOldPopulate;if(!autotest::beginInvocation(out,f))return;f(self,seed&1?level:NULL);number(self->m_bUnknown2D);}
 else if(mode==7){typedef long long(*Fn)(CQuest*,CBaseUnit*);Fn f=ours?cqNewDialog:cqOldDialog;if(!autotest::beginInvocation(out,f))return;CQuestDialog*r=reinterpret_cast<CQuestDialog*>(f(self,seed%17?npc:NULL));number(r?dialogID(r):~0u);}
 else if(mode==8){self->m_bUnknown210=seed&16;self->m_bUnknown20B=seed&32;CQuestRequirements*saved=self->m_pQuestRequirements;if(seed&64)self->m_pQuestRequirements=NULL;typedef int(*Fn)(CQuest*,CBaseUnit*);Fn f=ours?cqNewValid:cqOldValid;if(!autotest::beginInvocation(out,f))return;number(f(self,seed&1?npc:NULL));self->m_pQuestRequirements=saved;}
 else if(mode==9){typedef void(*Fn)(CQuest*,CBaseUnit*);Fn f=ours?cqNewInitialize:cqOldInitialize;if(!autotest::beginInvocation(out,f))return;f(self,seed&1?npc:NULL);number(self->m_iUnknown1C);number(self->m_iUnknown1E8==reinterpret_cast<long long>(&npcData));number(self->m_iUnknown20C);number(self->m_bUnknown2D);}
 else if(mode==10){typedef void(*Fn)(CQuest*,bool);Fn f=ours?cqNewCleanup:cqOldCleanup;if(!autotest::beginInvocation(out,f))return;f(self,seed&1);}
 else {typedef void(*Fn)(CQuest*);Fn f=ours?cqNewReward:cqOldReward;if(!autotest::beginInvocation(out,f))return;f(self);number(self->m_bUnknown2D);}
 out.callCompleted=1;hooks.restore();if(player)player->m_pResourceManager=resources;resources->m_pLevel=level;self->m_pQuestRewards=savedReward;manager->m_pPlayer=otherManager->m_pPlayer=NULL;self->m_pQuestManager=manager;field<TArrayList<CGameClient*> >(resources,0x28).clear();if(player)nativegame::destroyPlayer(player);other.m_pLevel=NULL;
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned long address,unsigned count){nativegame::Services services;if(!services.ready())return 1;scene=services.scene;return smallmass::run(host,op,name,address,&side,count);}
}
TL_TEST(complete_quest_floor){return run(host,0,"complete_quest_floor",0xd0c780,128);}
TL_TEST(complete_quest_random){return run(host,1,"complete_quest_random",0xd0c910,128);}
TL_TEST(complete_quest_xp){return run(host,2,"complete_quest_xp",0xd0cae0,64);}
TL_TEST(complete_quest_gold){return run(host,3,"complete_quest_gold",0xd0cb10,64);}
TL_TEST(complete_quest_accept){return run(host,4,"complete_quest_accept",0xd0cb70,64);}
TL_TEST(complete_quest_dialog_cleanup){return run(host,5,"complete_quest_dialog_cleanup",0xd0d7b0,192);}
TL_TEST(complete_quest_populate){return run(host,6,"complete_quest_populate",0xd14510,192);}
TL_TEST(complete_quest_dialog_selection){return run(host,7,"complete_quest_dialog_selection",0xd14f60,4096);}
TL_TEST(complete_quest_valid){return run(host,8,"complete_quest_valid",0xd15180,256);}
TL_TEST(complete_quest_initialize){return run(host,9,"complete_quest_initialize",0xd197d0,1024);}
TL_TEST(complete_quest_cleanup){return run(host,10,"complete_quest_cleanup",0xd1cf40,512);}
TL_TEST(complete_quest_reward){return run(host,11,"complete_quest_reward",0xd1d270,512);}

TL_TEST(complete_quest_fame_restore){return run(host,12,"complete_quest_fame_restore",0xd0cab0,64);}
