// Independent state/order oracle derived from original d2f020 and d32600.
// No replacement source is consulted. Real GCC 4.4 COW strings and map nodes.
#include <map>
#include <string>
#include <cstring>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(long long, qrcOldRemove, (void*,void*,bool), "_ZN13CQuestManager11removeQuestEP6CQuestb")
extern "C" long long qrcNewRemove(void*,void*,bool) __asm__("_ZN13CQuestManager11removeQuestEP6CQuestb");
TL_ORIGINAL(long long, qrcOldComplete, (void*,void*), "_ZN13CQuestManager13completeQuestEP6CQuest")
extern "C" long long qrcNewComplete(void*,void*) __asm__("_ZN13CQuestManager13completeQuestEP6CQuest");
TL_FUNCTION(qrcInit,"_ZN6CQuest22initializeQuestWithNPCEP9CBaseUnit")
TL_FUNCTION(qrcAccepted,"_ZN6CQuest16setQuestAcceptedEb")
TL_FUNCTION(qrcSetComplete,"_ZN6CQuest13setIsCompleteEb")
TL_FUNCTION(qrcCleanup,"_ZN6CQuest7cleanUpEb")
TL_FUNCTION(qrcReinit,"_ZN6CQuest17reinitializeQuestEbb")
TL_FUNCTION(qrcReward,"_ZN13CQuestManager18giveRewardForQuestEP6CQuest")
TL_FUNCTION(qrcNotifyAccepted,"_ZN16CQuestController20questHasBeenAcceptedEb")
TL_FUNCTION(qrcNotifyAbandoned,"_ZN16CQuestController21questHasBeenAbandonedEv")
TL_FUNCTION(qrcNotifyComplete,"_ZN16CQuestController21questHasBeenCompletedEb")
TL_FUNCTION(qrcNPC,"_ZN6CLevel14updateNPCIconsEv")
TL_FUNCTION(qrcAutomap,"_ZN6CLevel18updateAutomapIconsEv")
TL_FUNCTION(qrcMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(qrcGetSetting,"_ZN20CDynamicPropertyFile9GetStringEj")
TL_FUNCTION(qrcSetSetting,"_ZN20CDynamicPropertyFile6SetIntEji")
TL_FUNCTION(qrcUpper,"_ZN7STRINGS11StringUpperERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qrcClass,"_ZN7CPlayer18getPlayerClassNameEv")
TL_FUNCTION(qrcStats,"_ZN11CSteamStats12getSingletonEv")
TL_FUNCTION(qrcStat,"_ZN11CSteamStats10getStatIntE6ESTATS")
TL_FUNCTION(qrcIncrement,"_ZN11CSteamStats13incrementStatE6ESTATSi")
TL_FUNCTION(qrcAchievements,"_ZN13CAchievements12getSingletonEv")
TL_FUNCTION(qrcAchievement,"_ZN13CAchievements14getAchievementE13EACHIEVEMENTS")
TL_FUNCTION(qrcForce,"_ZN12CAchievement13forceCompleteEv")
TL_FUNCTION(qrcIsComplete,"_ZN6CQuest10isCompleteEb")
TL_FUNCTION(qrcQuestEvent,"_ZN6CQuest16questEventUpdateE13EQUEST_EVENTSP9CBaseUnitS2_")
TL_FUNCTION(qrcUI,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(qrcRefresh,"_ZN7CGameUI16refreshQuestMenuEv")
extern unsigned int KSETTINGS_RETIREE_QUEST;
extern unsigned int KSETTINGS_GAME_COMPLETED_ONCE;
namespace qrc {
typedef std::map<std::wstring,bool> Map;
typedef Map::value_type Value;
typedef std::_Rb_tree_node_base Base;
typedef std::_Rb_tree_node<Value> Node;
struct List {void** data;unsigned count,capacity,grow,pad;};
typedef char ABI[sizeof(Map)==48&&sizeof(Node)==48&&sizeof(std::wstring)==8&&sizeof(List)==24?1:-1];
template<class T>T& at(void* p,unsigned o){return *reinterpret_cast<T*>((char*)p+o);}
enum Event {Reward=1,Accepted,Initialize,SetComplete,Cleanup,Reinitialize,NotifyAccepted,NotifyAbandoned,NotifyComplete,NPC,Automap,GetSetting,SetSetting,GetStat,Class,Increment,GetAchievement,Force,IsComplete,QuestEvent,Refresh};
enum Mutation {NoMutation,LiveShrink,LiveAppend,SwapTarget,SwapWrapper,ChangeCapacity,SwapList,ChangeName,AppendActive,InitAccepted,ReinitName,IconLevel,IconResource,InitResource,SetterActive,SetterRepeat,SetterName,RewardRepeat,InitRepeat,RewardPlayer,ControllerPlayer,SettingClients,IncrementStats,EventRepeatName};
struct Case {unsigned complete,mode,variant,fault;};
struct State {
 unsigned activeCount,activeCap,controllerCount,controllerCap,controllerList,mapCount,clientsCount,firstClient,resource;
 int active[8],slots[2][8],target[8],level[2],stats[3],gameState[2];
 bool accepted,done,repeat,npcClear,player,dialog[3];
 std::wstring name,controllerName[8],mapKey[16];bool mapValue[16];
 unsigned setting,achievements[2];
};
struct Expected {unsigned code,id;int argument;State state;};
struct Stop {};
const Case* cs;autotest::Capture* cap;State start,finish;Expected expected[256];unsigned expectedCount,used,errors,mutation,mutationEvent,mutationUsed,classCalls,currentPass;bool actualSetters,mutateInEvent;unsigned repeats;std::wstring retiree,classText[3];
void *owner,*quest[4],*controller[8],*wrapper[8],*resources[2],*levels[2],*clients[2],*managerPlayer,*master,*settings,*statsObject,*achievementsObject,*achievement[2],*ui,*dialogs[3],*npcMarker;
List *active,*controllers;void** controllerData[2];Map* completed;unsigned char ownerBefore[0xd0],questBefore[4][0x220],controllerBefore[8][0xc0],resourceBefore[2][0x80];
int observedStats[3];unsigned observedSetting,observedAchievements[2];
void need(bool ok){if(!ok)++errors;}
void n(unsigned v){cap->add(&v,4);}
void* raw(unsigned size){return autotest::allocate(size);}
unsigned id(void* p,void** objects,unsigned count){for(unsigned i=0;i<count;++i)if(objects[i]==p)return i;return 99;}
std::wstring upperValue(const std::wstring& s){std::wstring r=s;for(unsigned i=0;i<r.size();++i)if(r[i]>=L'a'&&r[i]<=L'z')r[i]-=L'a'-L'A';return r;}
// The oracle uses a sorted fixed array, not map insertion or the tested helper.
void put(State& s,const std::wstring& key,bool value){unsigned pos=0;while(pos<s.mapCount&&s.mapKey[pos]<key)++pos;if(pos<s.mapCount&&s.mapKey[pos]==key){s.mapValue[pos]=value;return;}for(unsigned i=s.mapCount;i>pos;--i){s.mapKey[i]=s.mapKey[i-1];s.mapValue[i]=s.mapValue[i-1];}s.mapKey[pos]=key;s.mapValue[pos]=value;++s.mapCount;}
void seed(const std::wstring& key,bool value){Base* h=(Base*)((char*)completed+8);Base* parent=h;Base* p=h->_M_parent;bool left=true;while(p){parent=p;left=key<static_cast<Node*>(p)->_M_value_field.first;p=left?p->_M_left:p->_M_right;}Node* node=static_cast<Node*>(::operator new(sizeof(Node)));new(&node->_M_value_field)Value(key,value);std::_Rb_tree_insert_and_rebalance(left,node,parent,*h);++at<size_t>(completed,40);}
void removeFirst(State& s){for(unsigned i=0;i<s.activeCount;++i)if(s.active[i]==0){--s.activeCount;s.active[i]=s.active[s.activeCount];break;}}
void want(State& s,unsigned code,unsigned who=0,int arg=0){need(expectedCount<256);if(expectedCount>=256)return;Expected& e=expected[expectedCount++];e.code=code;e.id=who;e.argument=arg;e.state=s;}
void mutateModel(State& s,unsigned code,unsigned& once){if(once||code!=mutationEvent)return;++once;switch(mutation){
 case LiveShrink:s.controllerCount=1;break;case LiveAppend:s.controllerCount=3;break;
 case SwapTarget:s.target[0]=4;break;case SwapWrapper:s.slots[0][0]=4;break;
 case ChangeCapacity:s.controllerCap=1;break;case SwapList:s.controllerList=1;break;
 case ChangeName:s.name=L"Changed";break;case AppendActive:s.active[s.activeCount++]=0;break;
 case InitAccepted:s.accepted=true;break;case ReinitName:s.name=L"Changed";break;
 case IconLevel:s.level[s.resource]=1;break;case IconResource:s.resource=1;break;
 case InitResource:s.resource=1;break;case SetterActive:s.active[0]=2;s.active[1]=0;s.active[2]=3;s.activeCount=3;break;
 case SetterRepeat:case RewardRepeat:case InitRepeat:s.repeat=!s.repeat;break;
 case SetterName:s.name=L"Changed";break;case RewardPlayer:s.player=false;break;
 case ControllerPlayer:s.player=true;break;case SettingClients:s.clientsCount=1;s.firstClient=1;s.gameState[1]=1;break;
 case IncrementStats:s.stats[0]=0;s.stats[1]=0;s.stats[2]=0;break;
 case EventRepeatName:s.repeat=true;s.name=L"Changed";break;default:break;}}
void modelCallback(State& s,unsigned code,unsigned& once,unsigned who=0,int arg=0){want(s,code,who,arg);mutateModel(s,code,once);}
void modelAccepted(State& s,unsigned& once){if(actualSetters){if(s.accepted){s.accepted=false;for(unsigned i=0;i<3;++i)s.dialog[i]=false;}}else{modelCallback(s,Accepted,once,0,0);s.accepted=false;}}
void modelInit(State& s,unsigned& once){modelCallback(s,Initialize,once);s.npcClear=true;}
void modelCompleteSetter(State& s,unsigned& once){bool value=!s.repeat;if(!actualSetters){modelCallback(s,SetComplete,once,0,value);s.done=value;return;}bool changed=s.done!=value;s.done=value;if(!changed||!value||!s.player)return;
 // Boundary cases intentionally use two active entries, and no event5/UI.
 for(unsigned i=0;i<s.activeCount;++i){unsigned q=s.active[i<s.activeCap?i:0];if(q==99)continue;bool done=q==0?s.done:!mutateInEvent;want(s,IsComplete,q,0);if(done)continue;modelCallback(s,QuestEvent,once,q,4);want(s,IsComplete,q,0);want(s,IsComplete,q,0);}if(mutateInEvent)want(s,Refresh);
}
void modelControllers(State& s,unsigned& once){for(unsigned i=0;i<s.controllerCount;++i){unsigned slot=i<s.controllerCap?i:0;int target=s.target[s.slots[s.controllerList][slot]];if(target<0||s.controllerName[target]!=s.name)continue;modelCallback(s,cs->complete?NotifyComplete:NotifyAccepted,once,target,cs->complete?1:0);if(!cs->complete&&cs->variant){slot=i<s.controllerCap?i:0;target=s.target[s.slots[s.controllerList][slot]];modelCallback(s,NotifyAbandoned,once,target);}}}
void modelIcons(State& s,unsigned& once){if(!cs->complete||s.level[s.resource]>=0){modelCallback(s,NPC,once,s.level[s.resource]<0?99:s.level[s.resource]);modelCallback(s,Automap,once,s.level[s.resource]<0?99:s.level[s.resource]);}}
void modelAchievements(State& s,unsigned& once){std::wstring up=upperValue(s.name);if(up==L"PALACEALRICDEAD"||up==L"PALACEPT2"){want(s,GetAchievement,13);want(s,Force,13);++s.achievements[0];}if(!s.player)return;modelCallback(s,GetSetting,once);if(up!=upperValue(retiree))return;modelCallback(s,SetSetting,once,0,1);s.setting=1;if(!s.clientsCount||s.firstClient>1||s.gameState[s.firstClient]!=1)return;
 int local[3];for(unsigned i=0;i<3;++i){want(s,GetStat,23-i);local[i]=s.stats[i];}
 int chosen=-1;for(unsigned i=0;i<3;++i){want(s,Class,i);const wchar_t* names[]={L"DESTROYER",L"ALCHEMIST",L"VANQUISHER"};if(classText[i]==names[i]&&!local[i]){chosen=i;break;}}
 if(chosen>=0){modelCallback(s,Increment,once,23-chosen,1);++s.stats[chosen];++local[chosen];}
 if(local[0]&&local[1]&&local[2]){want(s,GetAchievement,23);want(s,Force,23);++s.achievements[1];}
}
void buildModel(){State s=start;expectedCount=0;unsigned once=0;for(unsigned pass=0;pass<repeats;++pass){if(cs->mode==0)continue;if(!cs->complete){removeFirst(s);modelInit(s,once);modelAccepted(s,once);if(cs->variant){modelCallback(s,Cleanup,once,0,0);modelCallback(s,Reinitialize,once,0,1);}modelControllers(s,once);modelIcons(s,once);}else{if(s.player)modelCallback(s,Reward,once);modelAccepted(s,once);modelInit(s,once);modelCompleteSetter(s,once);removeFirst(s);put(s,s.name,!s.repeat);modelControllers(s,once);modelIcons(s,once);modelAchievements(s,once);}}finish=s;if(cs->fault){unsigned cut=0;while(cut<expectedCount&&expected[cut].code!=cs->fault)++cut;need(cut<expectedCount);if(cut<expectedCount){finish=expected[cut].state;expectedCount=cut+1;}}}
void configure(){start=State();mutation=NoMutation;mutationEvent=0;repeats=1;actualSetters=false;mutateInEvent=false;retiree=L"Different retiree quest";for(unsigned i=0;i<3;++i)classText[i]=L"DESTROYER";
 start.activeCount=3;start.activeCap=8;start.controllerCount=2;start.controllerCap=8;start.controllerList=0;start.clientsCount=1;start.firstClient=0;start.resource=0;start.player=true;start.accepted=true;start.done=false;start.repeat=cs->complete&&cs->variant;start.npcClear=false;start.name=L"Quest";start.level[0]=0;start.level[1]=1;start.gameState[0]=start.gameState[1]=1;
 for(unsigned i=0;i<8;++i){start.active[i]=i<4?int(i):99;start.slots[0][i]=i;start.slots[1][i]=(i+4)%8;start.target[i]=i;start.controllerName[i]=L"Quest";}for(unsigned i=0;i<3;++i)start.dialog[i]=true;
 put(start,L"A unrelated",false);put(start,L"z unrelated",true);
 unsigned m=cs->mode;
 if(!cs->complete){switch(m){
  case 1:start.activeCount=0;start.controllerCount=0;break;
  case 2:start.active[0]=1;start.active[1]=2;start.controllerCount=0;break;
  case 3:start.controllerCount=0;break;
  case 4:start.active[0]=1;start.active[1]=0;start.active[2]=2;break;
  case 5:start.active[0]=1;start.active[1]=2;start.active[2]=0;break;
  case 6:start.active[0]=0;start.active[1]=0;start.active[2]=2;start.active[3]=0;start.activeCount=4;break;
  case 7:start.active[0]=1;start.active[1]=2;start.active[2]=0;start.activeCap=1;break;
  case 8:start.controllerName[0]=L"quest";start.controllerName[1]=L"QUEST";break;
  case 9:start.target[0]=-1;break;
  case 10:start.controllerCount=4;start.target[0]=-1;start.controllerName[1]=L"Quests";start.controllerName[2]=L"quest";break;
  case 11:start.controllerCount=3;start.controllerCap=1;break;
  case 12:mutation=LiveShrink;mutationEvent=NotifyAccepted;start.controllerCount=3;break;
  case 13:mutation=LiveAppend;mutationEvent=NotifyAccepted;start.controllerCount=1;break;
  case 14:mutation=SwapTarget;mutationEvent=NotifyAccepted;break;
  case 15:mutation=SwapWrapper;mutationEvent=NotifyAccepted;break;
  case 16:mutation=ChangeCapacity;mutationEvent=NotifyAccepted;start.controllerCount=3;break;
  case 17:mutation=SwapList;mutationEvent=NotifyAccepted;start.controllerCount=3;break;
  case 18:mutation=ChangeName;mutationEvent=NotifyAccepted;start.controllerCount=3;start.controllerName[2]=L"Changed";break;
  case 19:mutation=AppendActive;mutationEvent=Accepted;break;
  case 20:mutation=InitAccepted;mutationEvent=Initialize;start.accepted=false;break;
  case 21:mutation=LiveAppend;mutationEvent=Cleanup;start.controllerCount=1;break;
  case 22:mutation=ReinitName;mutationEvent=Reinitialize;start.controllerName[1]=L"Changed";break;
  case 23:mutation=IconLevel;mutationEvent=NPC;break;
  case 24:mutation=IconResource;mutationEvent=NPC;break;
  case 25:start.level[0]=-1;break;
  case 26:mutation=InitResource;mutationEvent=Initialize;break;
  case 27:mutation=SetterActive;mutationEvent=Accepted;break;
  case 28:repeats=2;break;
  case 29:start.accepted=false;break;
  case 30:start.name=L"";start.controllerName[0]=L"";start.controllerName[1]=L"Quest";break;
  case 31:{const wchar_t name[]={L'Q',0,L'\u03a9'};start.name.assign(name,3);start.controllerName[0]=start.name;start.controllerName[1]=L"Q";break;}
  case 32:actualSetters=true;break;
  case 33:actualSetters=true;start.accepted=false;break;
  case 34:actualSetters=true;repeats=2;break;
  case 35:start.target[1]=0;break;
 }}else{switch(m){
  case 1:start.player=false;start.activeCount=0;start.controllerCount=0;start.mapCount=0;break;
  case 2:start.controllerCount=0;break;
  case 3:start.active[0]=1;start.active[1]=0;start.active[2]=2;break;
  case 4:start.active[0]=1;start.active[1]=2;start.active[2]=0;break;
  case 5:start.active[0]=0;start.active[1]=0;start.active[2]=2;start.active[3]=0;start.activeCount=4;break;
  case 6:start.active[0]=1;start.active[1]=2;start.active[2]=3;break;
  case 7:start.active[0]=1;start.active[1]=2;start.active[2]=0;start.activeCap=1;break;
  case 8:start.repeat=true;break;
  case 9:repeats=2;break;
  case 10:put(start,L"Quest",true);break;
  case 11:put(start,L"Quest",false);break;
  case 12:put(start,L"QUEST",true);put(start,L"quest",false);put(start,std::wstring(150,L'z'),false);break;
  case 13:mutation=SetterRepeat;mutationEvent=SetComplete;break;
  case 14:mutation=SetterName;mutationEvent=SetComplete;start.controllerName[1]=L"Changed";break;
  case 15:mutation=RewardRepeat;mutationEvent=Reward;break;
  case 16:mutation=InitRepeat;mutationEvent=Initialize;break;
  case 17:mutation=SetterActive;mutationEvent=SetComplete;break;
  case 18:mutation=LiveShrink;mutationEvent=NotifyComplete;start.controllerCount=3;break;
  case 19:mutation=LiveAppend;mutationEvent=NotifyComplete;start.controllerCount=1;break;
  case 20:start.controllerCount=3;start.controllerCap=1;break;
  case 21:start.target[0]=-1;break;
  case 22:start.controllerName[0]=L"quest";start.controllerName[1]=L"QUEST";break;
  case 23:mutation=ChangeName;mutationEvent=NotifyComplete;start.controllerCount=3;start.controllerName[2]=L"Changed";break;
  case 24:mutation=SwapList;mutationEvent=NotifyComplete;start.controllerCount=3;break;
  case 25:mutation=IconLevel;mutationEvent=NPC;break;
  case 26:mutation=IconResource;mutationEvent=NPC;break;
  case 27:start.level[0]=-1;break;
  case 28:start.name=L"pAlAcEaLrIcDeAd";start.player=false;break;
  case 29:start.name=L"pAlAcEpT2";break;
  case 30:start.name=L"PalacePT2x";break;
  case 31:retiree=L"qUeSt";start.player=false;break;
  case 32:retiree=L"qUeSt";start.clientsCount=0;break;
  case 33:retiree=L"qUeSt";start.firstClient=99;break;
  case 34:case 35:case 36:retiree=L"qUeSt";start.gameState[0]=m==34?0:m==35?2:-1;break;
  case 37:retiree=L"qUeSt";break;
  case 38:retiree=L"qUeSt";for(unsigned i=0;i<3;++i)classText[i]=L"ALCHEMIST";break;
  case 39:retiree=L"qUeSt";for(unsigned i=0;i<3;++i)classText[i]=L"VANQUISHER";break;
  case 40:retiree=L"qUeSt";for(unsigned i=0;i<3;++i)classText[i]=L"UNKNOWN";break;
  case 41:retiree=L"qUeSt";for(unsigned i=0;i<3;++i)classText[i]=L"destroyer";break;
  case 42:retiree=L"qUeSt";start.stats[0]=1;break;
  case 43:retiree=L"qUeSt";start.stats[0]=-1;start.stats[1]=-4;start.stats[2]=0;break;
  case 44:retiree=L"qUeSt";start.stats[1]=2;start.stats[2]=-3;break;
  case 45:retiree=L"qUeSt";for(unsigned i=0;i<3;++i){start.stats[i]=-1;classText[i]=L"UNKNOWN";}break;
  case 46:retiree=L"qUeSt";classText[0]=L"UNKNOWN";classText[1]=L"ALCHEMIST";break;
  case 47:retiree=L"qUeSt";classText[0]=classText[1]=L"UNKNOWN";classText[2]=L"VANQUISHER";break;
  case 48:retiree=L"qUeSt";start.stats[0]=4;classText[1]=L"ALCHEMIST";break;
  case 49:retiree=L"qUeSt";start.stats[1]=2;start.stats[2]=3;mutation=IncrementStats;mutationEvent=Increment;break;
  case 50:retiree=L"qUeSt";start.clientsCount=0;start.gameState[0]=0;mutation=SettingClients;mutationEvent=SetSetting;break;
  case 51:mutation=RewardPlayer;mutationEvent=Reward;break;
  case 52:start.player=false;mutation=ControllerPlayer;mutationEvent=NotifyComplete;retiree=L"qUeSt";break;
  case 53:{const wchar_t name[]={L'Q',0,L'\u03a9'};start.name.assign(name,3);put(start,L"Q",true);put(start,std::wstring(name,3),cs->variant==0);break;}
  case 60:retiree=L"qUeSt";start.stats[0]=1;start.stats[2]=-1;for(unsigned i=0;i<3;++i)classText[i]=L"ALCHEMIST";break;
  case 61:retiree=L"qUeSt";start.stats[0]=-2;start.stats[1]=1;for(unsigned i=0;i<3;++i)classText[i]=L"VANQUISHER";break;
  case 62:start.name=L"PaLaCeAlRiCdEaD";retiree=L"palacealricdead";start.stats[1]=start.stats[2]=1;repeats=2;break;
  case 63:start.name=L"";start.mapCount=0;start.controllerName[0]=L"";break;
  case 64:start.name=std::wstring(150,L"z"[0]);start.controllerName[0]=start.name;break;
  case 65:mutation=ChangeCapacity;mutationEvent=NotifyComplete;start.controllerCount=3;break;
  case 66:mutation=SwapTarget;mutationEvent=NotifyComplete;start.controllerCount=3;start.controllerCap=1;break;
  case 54:case 55:case 56:case 57:case 58:case 59:
   actualSetters=true;start.activeCount=2;start.repeat=m==57;start.done=m==56;start.accepted=m!=55;
   if(m==58||m==59){mutateInEvent=true;mutation=EventRepeatName;mutationEvent=QuestEvent;start.controllerName[1]=L"Changed";if(m==59)put(start,L"Changed",true);}break;
 }}
}
void actualMutation(unsigned code){if(mutationUsed||code!=mutationEvent)return;++mutationUsed;switch(mutation){
 case LiveShrink:controllers->count=1;break;case LiveAppend:controllers->count=3;break;
 case SwapTarget:at<void*>(wrapper[0],0)=controller[4];break;case SwapWrapper:controllerData[0][0]=wrapper[4];break;
 case ChangeCapacity:controllers->capacity=1;break;case SwapList:controllers->data=controllerData[1];break;
 case ChangeName:case ReinitName:case SetterName:at<std::wstring>(quest[0],0x50)=L"Changed";break;
 case AppendActive:active->data[active->count++]=quest[0];break;case InitAccepted:at<bool>(quest[0],0x26)=true;break;
 case IconLevel:at<void*>(at<void*>(owner,0x38),0x18)=levels[1];break;
 case IconResource:case InitResource:at<void*>(owner,0x38)=resources[1];break;
 case SetterActive:active->data[0]=quest[2];active->data[1]=quest[0];active->data[2]=quest[3];active->count=3;break;
 case SetterRepeat:case RewardRepeat:case InitRepeat:at<bool>(quest[0],0x20b)=!at<bool>(quest[0],0x20b);break;
 case RewardPlayer:at<void*>(owner,0x10)=0;break;case ControllerPlayer:at<void*>(owner,0x10)=managerPlayer;break;
 case SettingClients:for(unsigned i=0;i<2;++i){at<unsigned>(resources[i],0x30)=1;at<void**>(resources[i],0x28)[0]=clients[1];}at<int>(clients[1],0x38d0)=1;break;
 case IncrementStats:observedStats[0]=observedStats[1]=observedStats[2]=0;break;
 case EventRepeatName:at<bool>(quest[0],0x20b)=true;at<std::wstring>(quest[0],0x50)=L"Changed";break;default:break;}}
void checkState(const State& s){need(active->count==s.activeCount&&active->capacity==s.activeCap);for(unsigned i=0;i<8;++i)need(id(active->data[i],quest,4)==unsigned(s.active[i]));
 need(at<bool>(quest[0],0x26)==s.accepted&&at<bool>(quest[0],0x24)==s.done&&at<bool>(quest[0],0x20b)==s.repeat);need(at<void*>(quest[0],0x1e8)==(s.npcClear?0:npcMarker));need(at<std::wstring>(quest[0],0x50)==s.name);
 need(at<void*>(owner,0x10)==(s.player?managerPlayer:0));need(at<void*>(owner,0x38)==resources[s.resource]);for(unsigned i=0;i<2;++i){need(at<void*>(resources[i],0x18)==(s.level[i]<0?0:levels[s.level[i]]));need(at<unsigned>(resources[i],0x30)==s.clientsCount);need(at<void**>(resources[i],0x28)[0]==(s.firstClient>1?0:clients[s.firstClient]));need(at<int>(clients[i],0x38d0)==s.gameState[i]);}
 need(controllers->count==s.controllerCount&&controllers->capacity==s.controllerCap&&controllers->data==controllerData[s.controllerList]);for(unsigned i=0;i<8;++i){need(at<void*>(wrapper[i],0)==(s.target[i]<0?0:controller[s.target[i]]));need(at<std::wstring>(controller[i],0xa8)==s.controllerName[i]);for(unsigned j=0;j<2;++j)need(controllerData[j][i]==wrapper[s.slots[j][i]]);}
 need(completed->size()==s.mapCount);unsigned j=0;for(Map::iterator i=completed->begin();i!=completed->end()&&j<16;++i,++j){need(j<s.mapCount&&i->first==s.mapKey[j]&&i->second==s.mapValue[j]);}need(j==s.mapCount);
 for(unsigned i=0;i<3;++i){need(observedStats[i]==s.stats[i]);need(at<bool>(dialogs[i],0x76)==s.dialog[i]);}need(observedSetting==s.setting);for(unsigned i=0;i<2;++i)need(observedAchievements[i]==s.achievements[i]);
}
void event(unsigned code,unsigned who=0,int arg=0){n(code);n(who);n(arg);need(used<expectedCount);if(used<expectedCount){const Expected& e=expected[used];need(code==e.code&&who==e.id&&arg==e.argument);checkState(e.state);}++used;if(cs->fault==code)throw Stop();actualMutation(code);}
void reward(void* self,void* q){need(self==owner&&q==quest[0]);event(Reward);}
void accepted(void* self,bool value){need(self==quest[0]&&!value);event(Accepted,0,value);at<bool>(self,0x26)=value;}
void initialize(void* self,void* npc){need(self==quest[0]&&!npc);event(Initialize);at<void*>(self,0x1e8)=npc;}
void setComplete(void* self,bool value){need(self==quest[0]);event(SetComplete,0,value);at<bool>(self,0x24)=value;}
void cleanup(void* self,bool value){need(self==quest[0]&&!value);event(Cleanup,0,value);}
void reinit(void* self,bool first,bool second){need(self==quest[0]&&first&&!second);event(Reinitialize,0,first);}
void notifyAccepted(void* self,bool value){event(NotifyAccepted,id(self,controller,8),value);}
void notifyAbandoned(void* self){event(NotifyAbandoned,id(self,controller,8));}
void notifyComplete(void* self,bool value){event(NotifyComplete,id(self,controller,8),value);}
void npc(void* self){event(NPC,id(self,levels,2));}
void automap(void* self){event(Automap,id(self,levels,2));}
void* getMaster(){return master;}
const std::wstring& getSetting(void* self,unsigned property){need(self==settings&&property==KSETTINGS_RETIREE_QUEST);event(GetSetting);return retiree;}
void setSetting(void* self,unsigned property,int value){need(self==settings&&property==KSETTINGS_GAME_COMPLETED_ONCE);event(SetSetting,0,value);observedSetting=value;}
std::wstring upper(const std::wstring& text){return upperValue(text);}
void* getStats(){return statsObject;}
int getStat(void* self,int which){need(self==statsObject&&which>=21&&which<=23);if(which==23)classCalls=0;event(GetStat,which);return which>=21&&which<=23?observedStats[23-which]:0;}
std::wstring getClass(void* self){need(self==managerPlayer);unsigned i=classCalls++;event(Class,i);return classText[i<3?i:2];}
void increment(void* self,int which,int value){need(self==statsObject&&which>=21&&which<=23);event(Increment,which,value);if(which>=21&&which<=23)observedStats[23-which]+=value;}
void* getAchievements(){return achievementsObject;}
void* getAchievement(void* self,int which){need(self==achievementsObject&&(which==13||which==23));event(GetAchievement,which);return achievement[which==23?1:0];}
void force(void* self){unsigned i=id(self,achievement,2);need(i<2);event(Force,i==0?13:23);if(i<2)++observedAchievements[i];}
long long isComplete(void* self,bool include){unsigned i=id(self,quest,4);need(i<4&&!include);event(IsComplete,i,include);return (i==0?at<bool>(quest[0],0x24):!mutateInEvent)?0x101:0x100;}
void questEvent(void* self,int which,void* character,void* unit){need(!character&&!unit&&which==4);event(QuestEvent,id(self,quest,4),which);}
void* getUI(){return ui;}
void refresh(void* self){need(self==ui);event(Refresh);}
void setup(){autotest::g_arenaUsed=0;errors=used=mutationUsed=classCalls=0;observedSetting=observedAchievements[0]=observedAchievements[1]=0;configure();
 owner=raw(0xf0);std::memset(owner,0xa5,0xf0);owner=(char*)owner+16;
 for(unsigned i=0;i<4;++i){quest[i]=raw(0x240);std::memset(quest[i],0x8a,0x240);quest[i]=(char*)quest[i]+16;new((char*)quest[i]+0x50)std::wstring(i==0?start.name:L"Other quest");}
 for(unsigned i=0;i<8;++i){controller[i]=raw(0xe0);std::memset(controller[i],0x9b,0xe0);controller[i]=(char*)controller[i]+16;new((char*)controller[i]+0xa8)std::wstring(start.controllerName[i]);wrapper[i]=raw(16);at<void*>(wrapper[i],0)=start.target[i]<0?0:controller[start.target[i]];at<unsigned long long>(wrapper[i],8)=0x8badf00d98765432ULL;}
 for(unsigned i=0;i<2;++i){resources[i]=raw(0xa0);std::memset(resources[i],0x6c,0xa0);resources[i]=(char*)resources[i]+16;levels[i]=raw(32);clients[i]=raw(0x38e0);at<int>(clients[i],0x38d0)=start.gameState[i];controllerData[i]=(void**)raw(8*sizeof(void*));for(unsigned j=0;j<8;++j)controllerData[i][j]=wrapper[start.slots[i][j]];}
 for(unsigned i=0;i<2;++i){at<void*>(resources[i],0x18)=start.level[i]<0?0:levels[start.level[i]];at<void**>(resources[i],0x28)=(void**)raw(2*sizeof(void*));at<void**>(resources[i],0x28)[0]=start.firstClient>1?0:clients[start.firstClient];at<void**>(resources[i],0x28)[1]=clients[1];at<unsigned>(resources[i],0x30)=start.clientsCount;at<unsigned>(resources[i],0x34)=2;}
 managerPlayer=raw(0x38e0);master=raw(0xa0);settings=raw(32);at<void*>(master,0x90)=settings;statsObject=raw(32);achievementsObject=raw(32);achievement[0]=raw(32);achievement[1]=raw(32);ui=raw(32);npcMarker=raw(32);
 at<void*>(owner,0x10)=start.player?managerPlayer:0;at<void*>(owner,0x38)=resources[start.resource];active=(List*)((char*)owner+0x18);active->data=(void**)raw(8*sizeof(void*));active->count=start.activeCount;active->capacity=start.activeCap;active->grow=11;active->pad=0x7351aabc;for(unsigned i=0;i<8;++i)active->data[i]=start.active[i]==99?0:quest[start.active[i]];
 completed=new((char*)owner+0x70)Map;for(unsigned i=0;i<start.mapCount;++i)seed(start.mapKey[i],start.mapValue[i]);
 controllers=(List*)((char*)quest[0]+0x1b0);controllers->data=controllerData[start.controllerList];controllers->count=start.controllerCount;controllers->capacity=start.controllerCap;controllers->grow=9;controllers->pad=0x2541beef;
 at<bool>(quest[0],0x24)=start.done;at<bool>(quest[0],0x26)=start.accepted;at<bool>(quest[0],0x20b)=start.repeat;at<void*>(quest[0],0x1e8)=start.npcClear?0:npcMarker;at<void*>(quest[0],0x1d0)=owner;
 List* acceptDialogs=(List*)((char*)quest[0]+0x60);acceptDialogs->data=(void**)raw(3*sizeof(void*));acceptDialogs->count=acceptDialogs->capacity=3;acceptDialogs->grow=7;acceptDialogs->pad=0x4271cafe;for(unsigned i=0;i<3;++i){dialogs[i]=raw(0x90);at<bool>(dialogs[i],0x76)=start.dialog[i];acceptDialogs->data[i]=dialogs[i];observedStats[i]=start.stats[i];}
 std::memcpy(ownerBefore,owner,0xd0);for(unsigned i=0;i<4;++i)std::memcpy(questBefore[i],quest[i],0x220);for(unsigned i=0;i<8;++i)std::memcpy(controllerBefore[i],controller[i],0xc0);for(unsigned i=0;i<2;++i)std::memcpy(resourceBefore[i],resources[i],0x80);buildModel();
}
void preserved(){unsigned char a[0x220],b[0x220];std::memcpy(a,owner,0xd0);std::memcpy(b,ownerBefore,0xd0);std::memset(a+0x70,0,48);std::memset(b+0x70,0,48);std::memset(a+0x10,0,8);std::memset(b+0x10,0,8);std::memset(a+0x38,0,8);std::memset(b+0x38,0,8);std::memset(a+0x20,0,4);std::memset(b+0x20,0,4);need(!std::memcmp(a,b,0xd0));
 for(unsigned q=0;q<4;++q){std::memcpy(a,quest[q],0x220);std::memcpy(b,questBefore[q],0x220);if(!q){const unsigned offsets[]={0x24,0x26,0x20b};for(unsigned j=0;j<3;++j)a[offsets[j]]=b[offsets[j]]=0;std::memset(a+0x50,0,8);std::memset(b+0x50,0,8);std::memset(a+0x1b0,0,16);std::memset(b+0x1b0,0,16);std::memset(a+0x1e8,0,8);std::memset(b+0x1e8,0,8);}need(!std::memcmp(a,b,0x220));for(unsigned k=0;k<16;++k)need(at<unsigned char>(quest[q],0x220+k)==0x8a&&((unsigned char*)quest[q])[-16+(int)k]==0x8a);}
 for(unsigned i=0;i<8;++i){need(!std::memcmp(controller[i],controllerBefore[i],0xc0));need(at<unsigned long long>(wrapper[i],8)==0x8badf00d98765432ULL);for(unsigned k=0;k<16;++k)need(at<unsigned char>(controller[i],0xc0+k)==0x9b&&((unsigned char*)controller[i])[-16+(int)k]==0x9b);}
 for(unsigned i=0;i<2;++i){std::memcpy(a,resources[i],0x80);std::memcpy(b,resourceBefore[i],0x80);std::memset(a+0x18,0,8);std::memset(b+0x18,0,8);std::memset(a+0x30,0,4);std::memset(b+0x30,0,4);need(!std::memcmp(a,b,0x80));for(unsigned k=0;k<16;++k)need(at<unsigned char>(resources[i],0x80+k)==0x6c&&((unsigned char*)resources[i])[-16+(int)k]==0x6c);}
 for(unsigned k=0;k<16;++k)need(at<unsigned char>(owner,0xd0+k)==0xa5&&((unsigned char*)owner)[-16+(int)k]==0xa5);
}
void serialize(){n(active->count);n(active->capacity);for(unsigned i=0;i<8;++i)n(id(active->data[i],quest,4));n(at<bool>(quest[0],0x24));n(at<bool>(quest[0],0x26));n(at<bool>(quest[0],0x20b));cap->addText(at<std::wstring>(quest[0],0x50));n(controllers->count);n(controllers->capacity);n(controllers->data==controllerData[1]);for(unsigned i=0;i<8;++i)n(id(at<void*>(wrapper[i],0),controller,8));n(completed->size());for(Map::iterator i=completed->begin();i!=completed->end();++i){cap->addText(i->first);n(i->second);}for(unsigned i=0;i<3;++i){n(observedStats[i]);n(at<bool>(dialogs[i],0x76));}n(observedSetting);n(observedAchievements[0]);n(observedAchievements[1]);}
void side(void* context,autotest::Capture& out,bool replacement){cs=(Case*)context;cap=&out;setup();long long result=-17;bool caught=false;
 {detour::Set d;
 TL_REDIRECT(d,qrcInit,&initialize);TL_REDIRECT(d,qrcCleanup,&cleanup);TL_REDIRECT(d,qrcReinit,&reinit);TL_REDIRECT(d,qrcReward,&reward);
 if(!actualSetters){TL_REDIRECT(d,qrcAccepted,&accepted);TL_REDIRECT(d,qrcSetComplete,&setComplete);}
 TL_REDIRECT(d,qrcNotifyAccepted,&notifyAccepted);TL_REDIRECT(d,qrcNotifyAbandoned,&notifyAbandoned);TL_REDIRECT(d,qrcNotifyComplete,&notifyComplete);TL_REDIRECT(d,qrcNPC,&npc);TL_REDIRECT(d,qrcAutomap,&automap);
 TL_REDIRECT(d,qrcMaster,&getMaster);TL_REDIRECT(d,qrcGetSetting,&getSetting);TL_REDIRECT(d,qrcSetSetting,&setSetting);TL_REDIRECT(d,qrcUpper,&upper);TL_REDIRECT(d,qrcClass,&getClass);TL_REDIRECT(d,qrcStats,&getStats);TL_REDIRECT(d,qrcStat,&getStat);TL_REDIRECT(d,qrcIncrement,&increment);TL_REDIRECT(d,qrcAchievements,&getAchievements);TL_REDIRECT(d,qrcAchievement,&getAchievement);TL_REDIRECT(d,qrcForce,&force);
 TL_REDIRECT(d,qrcIsComplete,&isComplete);TL_REDIRECT(d,qrcQuestEvent,&questEvent);TL_REDIRECT(d,qrcUI,&getUI);TL_REDIRECT(d,qrcRefresh,&refresh);
 if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(cs->complete){typedef long long(*Fn)(void*,void*);Fn fn=replacement?&qrcNewComplete:&qrcOldComplete;if(!autotest::beginInvocation(out,fn))return;try{for(currentPass=0;currentPass<repeats;++currentPass){result=fn(owner,cs->mode?quest[0]:0);need(result==(cs->mode?1:0));}out.callCompleted=1;}catch(const Stop&){caught=true;}}
 else{typedef long long(*Fn)(void*,void*,bool);Fn fn=replacement?&qrcNewRemove:&qrcOldRemove;if(!autotest::beginInvocation(out,fn))return;try{for(currentPass=0;currentPass<repeats;++currentPass){result=fn(owner,cs->mode?quest[0]:0,cs->variant!=0);need(result==(cs->mode?1:0));}out.callCompleted=1;}catch(const Stop&){caught=true;}}
 }
 need(caught==(cs->fault!=0));need(used==expectedCount);checkState(finish);preserved();serialize();n(caught);n(used);n(0xd2f32600u);n(errors);
 for(unsigned i=0;i<4;++i)at<std::wstring>(quest[i],0x50).~basic_string();for(unsigned i=0;i<8;++i)at<std::wstring>(controller[i],0xa8).~basic_string();completed->~Map();
}
void original(void* context,autotest::Capture& out){side(context,out,false);}void recovered(void* context,autotest::Capture& out){side(context,out,true);}
bool good(const autotest::Outcome& o){unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&tail[0]==0xd2f32600u&&!tail[1];}
bool pair(const tlhybrid_host* host,autotest::Coverage& cv,Case& c){autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=good(a)&&good(b)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);if(!c.fault){if(cv.observe(host,a,b))ok=false;}else ok=ok&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==cv.original&&host&&host->abi_version==TLHYBRID_ABI_VERSION&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget);
 if(!ok){unsigned ta[2]={0,~0u},tb[2]={0,~0u};if(a.capture.length>=8)std::memcpy(ta,a.capture.data+a.capture.length-8,8);if(b.capture.length>=8)std::memcpy(tb,b.capture.data+b.capture.length-8,8);host->log(" remove/complete op=%u mode=%u variant=%u fault=%u status=%d/%d errors=%u/%u issue=%u/%u\n",c.complete,c.mode,c.variant,c.fault,a.childStatus,b.childStatus,ta[1],tb[1],a.capture.issue,b.capture.issue);}return ok;}
}
TL_TEST(questmanager_remove_quest){using namespace qrc;autotest::Coverage cv("questmanager_remove_quest",0xd2f020);unsigned count=0;for(unsigned mode=0;mode<36;++mode)for(unsigned variant=0;variant<2;++variant){Case c={0,mode,variant,0};if(!pair(host,cv,c)){cv.report(host);return 1;}++count;}cv.report(host);return count<20||cv.completed!=count||cv.different||cv.missing;}
TL_TEST(questmanager_complete_quest){using namespace qrc;autotest::Coverage cv("questmanager_complete_quest",0xd32600);unsigned count=0;for(unsigned mode=0;mode<67;++mode)for(unsigned variant=0;variant<2;++variant){Case c={1,mode,variant,0};if(!pair(host,cv,c)){cv.report(host);return 1;}++count;}cv.report(host);return count<20||cv.completed!=count||cv.different||cv.missing;}
TL_TEST(questmanager_removal_completion_exceptions){using namespace qrc;autotest::Coverage remove("remove unwind excluded",0xd2f020),complete("complete unwind excluded",0xd32600);const Case cases[]={
 {0,3,1,Initialize},{0,3,1,Accepted},{0,3,1,Cleanup},{0,3,1,Reinitialize},{0,14,1,NotifyAccepted},{0,14,1,NotifyAbandoned},{0,3,1,NPC},{0,3,1,Automap},
 {1,10,0,Reward},{1,10,0,Accepted},{1,10,0,Initialize},{1,10,0,SetComplete},{1,10,0,NotifyComplete},{1,10,0,NPC},{1,10,0,Automap},{1,10,0,GetSetting},{1,44,0,SetSetting},{1,44,0,GetStat},{1,44,0,Class},{1,44,0,Increment},{1,28,0,GetAchievement},{1,28,0,Force},{1,58,0,QuestEvent},{1,58,0,Refresh}};
 for(unsigned i=0;i<sizeof(cases)/sizeof(cases[0]);++i){Case c=cases[i];if(!pair(host,c.complete?complete:remove,c))return 1;}host->log(" remove/complete: 24 expected collaborator unwinds, excluded from completed coverage\n");return 0;}
