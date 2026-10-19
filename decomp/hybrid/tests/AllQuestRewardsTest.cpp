#include <string>
#include <map>
#include <vector>
#include <limits>
#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#define private public
#define protected public
#include "Quest.h"
#include "QuestRewards.h"
#include "Equipment.h"
#include "Monster.h"
#include "GameUI.h"
#include "SpawnClass.h"
#include "SoundBank.h"
#include "SoundManager.h"
#include "Graph.h"
#undef protected
#undef private
#define PAIR(N,S,A) TL_ORIGINAL(void,old##N,A,S) extern "C" void new##N A __asm__(S);
PAIR(Calculate,"_ZN13CQuestRewards16calculateRewardsEv",(CQuestRewards*))
PAIR(Reward,"_ZN13CQuestRewards12rewardPlayerEv",(CQuestRewards*))
PAIR(Reset,"_ZN13CQuestRewards19reInitializeRewardsEv",(CQuestRewards*))
#undef PAIR
TL_ORIGINAL(void,rewardCtor,(CQuestRewards*,CQuest*),"_ZN13CQuestRewardsC1EP6CQuest")
TL_ORIGINAL(void,rewardDtor,(CQuestRewards*),"_ZN13CQuestRewardsD1Ev")
TL_ORIGINAL(void,rewardQuestCtor,(CQuest*,CResourceManager*,CQuestManager*),"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_ORIGINAL(void,rewardQuestDtor,(CQuest*),"_ZN6CQuestD1Ev")
#define DEP(N,S) TL_FUNCTION(rw##N,S)
DEP(Player,"_ZN6CQuest9getPlayerEv")
DEP(Graph,"_ZN16CResourceManager8getGraphERKSbIwSt11char_traitsIwESaIwEE")
DEP(Value,"_ZNK6CGraph8getValueEfj")
DEP(Seed,"_ZN9UTILITIES7setSeedEi")
DEP(Random,"_ZN9UTILITIES13randomBetweenEff")
DEP(Integer,"_ZN9UTILITIES20randomIntegerBetweenEii")
DEP(Create,"_ZN16CResourceManager10createUnitEP10CDataGroupibb")
DEP(Roll,"_ZN11CSpawnClass14rollSpawnClassER10TArrayListIP10CDataGroupEPS0_IbEP10CCharacterS8_ijiiii")
DEP(Remove,"_ZN6CLevel10removeUnitEP9CBaseUnitb")
DEP(Add,"_ZN6CLevel7addUnitEP9CBaseUnitRKN4Ogre7Vector3E")
DEP(Text,"_ZN5CItem15destroyItemTextEv")
DEP(Enchant,"_ZN10CEquipment7enchantEb")
DEP(EquipmentActive,"_ZN5CItem10setVisibleEb")
DEP(MonsterActive,"_ZN10CCharacter10setVisibleEb")
DEP(UI,"_ZN7CGameUI12getSingletonEv")
DEP(Sound,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
DEP(Gold,"_ZN10CCharacter8giveGoldEi")
DEP(XP,"_ZN10CCharacter15awardExperienceER6CLevelPS_ib")
DEP(Fame,"_ZN10CCharacter9awardFameER6CLevelPS_ib")
DEP(Can,"_ZN10CInventory9canPickupEP10CEquipmentb")
DEP(Pickup,"_ZN10CInventory15pickupEquipmentEP10CEquipmentb")
DEP(Pet,"_ZN10CCharacter6addPetEPS_")
DEP(Calculate,"_ZN13CQuestRewards16calculateRewardsEv")
#undef DEP
namespace {
struct Case{unsigned mode,seed;};
autotest::Capture* output;const Case* input;CQuest* quest;CQuestRewards* owner;CPlayer* player;CGameUI* ui;CBaseUnit* units[7];CDataGroup* groups[7];CGraph* graph;unsigned createCalls,randomCalls;Ogre::SceneManager* scene;
void n(unsigned v){output->add(&v,4);}void f(float v){output->add(&v,4);}void text(const std::wstring&v){n(v.size());output->add(v.data(),v.size()*4);}
unsigned id(CBaseUnit*p){for(unsigned i=0;i<7;++i)if(units[i]==p)return i+1;return p?99:0;}
unsigned groupId(CDataGroup*p){for(unsigned i=0;i<7;++i)if(groups[i]==p)return i+1;return p?99:0;}
CPlayer* getPlayer(CQuest*){n(10);return input->seed%17?player:NULL;}
bool editor(CResourceManager*){return input->seed%53==0;}
void seed(int v){n(11);n(v);randomCalls=0;}
float random(float lo,float hi){n(12);f(lo);f(hi);++randomCalls;return lo+(hi-lo)*(float((input->seed+randomCalls)%5)/4.0f);}
int integer(int lo,int hi){n(13);n(lo);n(hi);return int(input->seed%4)-1;}
CGraph* getGraph(CResourceManager*,const std::wstring&name){n(14);text(name);return graph;}
float graphValue(const CGraph*,float x,unsigned line){n(15);f(x);n(line);return (float(input->seed%31)-7.25f)*x;}
CBaseUnit* create(CResourceManager*,CDataGroup* data,int level,bool a,bool b){n(16);n(groupId(data));n(level);n(a);n(b);unsigned index=createCalls++%7;if((input->seed/19+index)%5==0)return NULL;return units[index];}
int roll(CSpawnClass*,TArrayList<CDataGroup*>& data,TArrayList<bool>* flags,CCharacter* a,CCharacter*b,int level,unsigned s,int c,int d,int e,int g){n(17);n(a==player);n(b==player);n(level);n(s);n(c);n(d);n(e);n(g);n(data.m_nGrowBy);n(flags->m_nGrowBy);unsigned count=(input->seed/5)%4;for(unsigned i=0;i<count;++i){data.add(groups[3+i]);flags->add((input->seed+i)%2==0);}return count;}
void remove(CLevel*,CBaseUnit*p,bool b){n(18);n(id(p));n(b);}
CBaseUnit* add(CLevel*,CBaseUnit*p,const Ogre::Vector3&v){n(19);n(id(p));f(v.x);f(v.y);f(v.z);return p;}
void itemText(CItem*p){n(20);n(id(p));}
void enchant(CEquipment*p,bool b){n(21);n(id(p));n(b);}
void active(CBaseUnit*p,bool b){n(22);n(id(p));n(b);p->m_bVisible=b;}
CGameUI* getUI(){n(23);return ui;}
int sound(CSoundBank*,int sample,Ogre::SceneNode*node,float a,float b,bool loop){n(24);n(sample);n(node==NULL);f(a);f(b);n(loop);if(input->seed%13==0){owner->m_fGold=0;owner->m_fExperience=3.25f;}return 3;}
void gold(CCharacter*p,int v){n(25);n(p==player);n(v);if(input->seed%11==0)owner->m_fGold=0;}
void xp(CCharacter*p,CLevel&,CCharacter*source,int value,bool b){n(26);n(p==player);n(source==NULL);n(value);n(b);}
void fame(CCharacter*p,CLevel&,CCharacter*source,int value,bool b){n(27);n(p==player);n(source==NULL);n(value);n(b);if(input->seed%23==0)quest->m_pResourceManager=NULL;}
bool can(CInventory*,CEquipment*p,bool b){n(28);n(id(p));n(b);return (input->seed+id(p))%3!=0;}
bool pickup(CInventory*,CEquipment*p,bool b){n(29);n(id(p));n(b);return true;}
void pet(CCharacter*p,CCharacter*child){n(30);n(p==player);n(id(child));}
void calculated(CQuestRewards*p){n(31);n(p->m_rewardItems.size());n(p->m_rewardItems.m_nCapacity);n(p->m_rewardItems.m_pData==NULL);p->m_fGold=17.5f;}
struct Other:finishlevel::Item{Other(CResourceManager*r):finishlevel::Item(r){}virtual void setVisible(bool b){active(this,b);}};
void side(void*raw,autotest::Capture&out,bool ours){
 const Case&c=*static_cast<Case*>(raw);input=&c;output=&out;createCalls=randomCalls=0;finishlevel::Fixture resources;resources.resources.m_pSceneManager=scene;
 player=nativegame::createPlayer(&resources.resources);player->setPosition(Ogre::Vector3(7.25f,-3.0f,11.5f));
 union QuestStorage{long double a;unsigned char bytes[sizeof(CQuest)];} qs;quest=reinterpret_cast<CQuest*>(qs.bytes);rewardQuestCtor(quest,&resources.resources,NULL);quest->m_iUnknown1C=int(c.seed)-17;quest->m_iUnknown20C=int(c.seed%31)-2;
 union OwnerStorage{long double a;unsigned char bytes[sizeof(CQuestRewards)];} os;owner=reinterpret_cast<CQuestRewards*>(os.bytes);rewardCtor(owner,quest);
 // Controlled scalar/game-service boundaries; no GameClient or UI constructor coverage is claimed.
 union ClientStorage{long double a;unsigned char bytes[sizeof(CGameClient)];} cs;std::memset(cs.bytes,0,sizeof(cs.bytes));CGameClient*client=reinterpret_cast<CGameClient*>(cs.bytes);client->m_startDifficulty=int((c.seed/7)%6)-1;if(c.seed%29)resources.resources.m_GameClients.add(c.seed%31?client:NULL);
 union UIStorage{long double a;unsigned char bytes[sizeof(CGameUI)];} us;ui=reinterpret_cast<CGameUI*>(us.bytes);CSoundManager soundManager(false);CSoundBank bank(soundManager,false);ui->m_soundBank=&bank;
 CGraph realGraph(GRAPH_LINEAR,L"test",1);graph=&realGraph;CSpawnClass spawn(L"test");
 TSafePointer<CBaseUnit> observers[7];
 for(unsigned i=0;i<7;++i){groups[i]=new CDataGroup(L"unit",NULL,2,2,NULL);units[i]=i%3==0?static_cast<CBaseUnit*>(new CEquipment(&resources.resources)):i%3==1?static_cast<CBaseUnit*>(new CMonster(&resources.resources,1)):static_cast<CBaseUnit*>(new Other(&resources.resources));observers[i].setObject(units[i]);}
 owner->m_fGold=1.25f;owner->m_fExperience=2.75f;owner->m_fFame=-0.25f;
 float*percent=&owner->m_fExperienceMinPercent;for(unsigned i=0;i<6;++i)percent[i]=float(int((c.seed/(i+1))%7)-2)*25.25f;
 if(c.seed%11==0)for(unsigned i=0;i<6;++i)percent[i]=0;
 owner->m_pSpawnClass=c.seed%3==0?&spawn:NULL;
 unsigned refs=(c.seed/3)%4;for(unsigned i=0;i<refs;++i){CQuestRewards::CUnitCreateRef*p=new CQuestRewards::CUnitCreateRef;p->m_pDataGroup=groups[i];p->m_bIdentify=(c.seed/5+i)%2;owner->m_unitRewardReferences.add(p);}
 if(c.mode==1||c.mode==2||(c.seed%37==0)){unsigned count=c.mode==0?1:(c.seed/2)%7;for(unsigned i=0;i<count;++i)owner->m_rewardItems.add(i%5?units[i]:NULL);}
 if(c.mode==0&&c.seed%41==1){owner->m_fGoldMinPercent=owner->m_fGoldMaxPercent=owner->m_fFameMinPercent=owner->m_fFameMaxPercent=0;owner->m_fExperienceMinPercent=300;owner->m_fExperienceMaxPercent=400;owner->m_pSpawnClass=NULL;owner->m_unitRewardReferences.deleteAll();}
 if(c.mode==1){static const unsigned values[]={0,0x80000000,0x3e800000,0xbf800000,0x7fc01234,0x7f800000,0x4f000000};unsigned a=values[c.seed%7],b=values[(c.seed/7)%7],d=values[(c.seed/49)%7];std::memcpy(&owner->m_fGold,&a,4);std::memcpy(&owner->m_fExperience,&b,4);std::memcpy(&owner->m_fFame,&d,4);if(c.seed%41==0)owner->m_pQuest=NULL;if(c.seed%43==0)quest->m_pResourceManager=NULL;if(c.seed%47==0)resources.resources.m_pLevel=NULL;}
 detour::Set h;TL_REDIRECT(h,levelFixtureEditorRunning,&editor);TL_REDIRECT(h,rwPlayer,&getPlayer);TL_REDIRECT(h,rwGraph,&getGraph);TL_REDIRECT(h,rwValue,&graphValue);TL_REDIRECT(h,rwSeed,&seed);TL_REDIRECT(h,rwRandom,&random);TL_REDIRECT(h,rwInteger,&integer);TL_REDIRECT(h,rwCreate,&create);TL_REDIRECT(h,rwRoll,&roll);TL_REDIRECT(h,rwRemove,&remove);TL_REDIRECT(h,rwAdd,&add);TL_REDIRECT(h,rwText,&itemText);TL_REDIRECT(h,rwEnchant,&enchant);TL_REDIRECT(h,rwEquipmentActive,&active);TL_REDIRECT(h,rwMonsterActive,&active);TL_REDIRECT(h,rwUI,&getUI);TL_REDIRECT(h,rwSound,&sound);TL_REDIRECT(h,rwGold,&gold);TL_REDIRECT(h,rwXP,&xp);TL_REDIRECT(h,rwFame,&fame);TL_REDIRECT(h,rwCan,&can);TL_REDIRECT(h,rwPickup,&pickup);TL_REDIRECT(h,rwPet,&pet);if(c.mode==2)TL_REDIRECT(h,rwCalculate,&calculated);if(h.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void(*F)(CQuestRewards*);F fn=c.mode==0?(ours?newCalculate:oldCalculate):c.mode==1?(ours?newReward:oldReward):(ours?newReset:oldReset);autotest::invoke(out,fn,owner);
 f(owner->m_fExperience);f(owner->m_fGold);f(owner->m_fFame);n(owner->m_rewardItems.size());n(owner->m_rewardItems.m_nCapacity);n(owner->m_rewardItems.m_nGrowBy);for(unsigned i=0;i<owner->m_rewardItems.size();++i)n(id(owner->m_rewardItems[i]));for(unsigned i=0;i<7;++i){n(observers[i].getObject()!=NULL);if(observers[i].getObject()){n(units[i]->getVisible());CEquipment*e=dynamic_cast<CEquipment*>(units[i]);if(e)n(e->m_bUnknown348);}}
 h.restore();resources.resources.m_GameClients.clear();resources.resources.m_pLevel=&resources.level;rewardDtor(owner);for(unsigned i=0;i<7;++i)if(observers[i].getObject())delete units[i];quest->m_pResourceManager=&resources.resources;rewardQuestDtor(quest);resources.resources.m_GameClients.clear();nativegame::destroyPlayer(player);for(unsigned i=0;i<7;++i)delete groups[i];
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned mode,const char*name,unsigned long long address,unsigned count){nativegame::Services services;if(!services.ready())return 1;scene=services.scene;autotest::Coverage coverage(name,address);for(unsigned i=0;i<count;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    rewards mode%u seed%u status%d/%d bytes%lu/%lu\n",mode,i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);unsigned at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    first diff byte%u\n",at);for(unsigned z=(at/4>8?at/4-8:0);z<at/4+24&&z*4<a.capture.length&&z*4<b.capture.length;++z){unsigned x,y;std::memcpy(&x,a.capture.data+z*4,4);std::memcpy(&y,b.capture.data+z*4,4);host->log("    word%u %08x/%08x\n",z,x,y);}coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(all_quest_rewards_calculate){return run(host,0,"all_quest_rewards_calculate",0xd3caf0,1024);}
TL_TEST(all_quest_rewards_reward){return run(host,1,"all_quest_rewards_reward",0xd34b30,1024);}
TL_TEST(all_quest_rewards_reset){return run(host,2,"all_quest_rewards_reset",0xd3db90,72);}
