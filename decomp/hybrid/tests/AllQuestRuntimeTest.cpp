#include <string>
#include <map>
#include <vector>
#include <limits>
#include <climits>
#include <Ogre.h>
#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#define private public
#define protected public
#include "Quest.h"
#include "QuestDialog.h"
#include "QuestUnitData.h"
#include "QuestDialogItem.h"
#include "QuestManager.h"
#include "SoundBank.h"
#include "SoundManager.h"
#include "SoundData.h"
#include "SoundBankDataInformation.h"
#include "GameVariables.h"
#undef protected
#undef private
#define PAIR(R,N,A,S) TL_ORIGINAL(R,old##N,A,S) extern "C" R new##N A __asm__(S);
PAIR(int,Active,(CQuestUnitData*),"_ZN14CQuestUnitData23getDungeonFloorActiveOnEv")
PAIR(int,Deepest,(CQuestUnitData*),"_ZN14CQuestUnitData15getDeepestFloorEv")
PAIR(void,UnitDtor,(CQuestUnitData*),"_ZN14CQuestUnitDataD1Ev")
PAIR(void,RemoveAll,(CQuestUnitData*,bool),"_ZN14CQuestUnitData24cleanUpForQuestRemoveallEb")
PAIR(bool,Dropped,(CQuestUnitData*,CBaseUnit*),"_ZN14CQuestUnitData11unitDroppedEP9CBaseUnit")
PAIR(bool,NPC,(CQuestDialog*,CBaseUnit*),"_ZN12CQuestDialog14dialogIsForNPCEP9CBaseUnit")
PAIR(std::wstring,Dialog,(CQuestDialog*,bool),"_ZN12CQuestDialog9getDialogEb")
PAIR(void,Items,(CQuestDialog*,CBaseUnit*),"_ZN12CQuestDialog17giveOrRemoveItemsEP9CBaseUnit")
PAIR(void,Cleanup,(CQuestDialog*),"_ZN12CQuestDialog7cleanUpEv")
PAIR(void,Sound,(CQuestDialog*),"_ZN12CQuestDialog15playDialogSoundEv")
PAIR(void,DialogCtor,(CQuestDialog*,CQuest*),"_ZN12CQuestDialogC1EP6CQuest")
PAIR(void,DialogDtor,(CQuestDialog*),"_ZN12CQuestDialogD1Ev")
#undef PAIR
TL_ORIGINAL(void,questNativeCtor,(CQuest*,CResourceManager*,CQuestManager*),"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_ORIGINAL(void,questNativeDtor,(CQuest*),"_ZN6CQuestD1Ev")
TL_ORIGINAL(void,unitNativeCtor,(CQuestUnitData*,CQuest*),"_ZN14CQuestUnitDataC1EP6CQuest")
TL_FUNCTION(qPlayer,"_ZN6CQuest9getPlayerEv")
TL_FUNCTION(qGuid,"_ZN16CResourceManager22getUnitGuidByDataGroupEP10CDataGroupRKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qRemoveQuest,"_ZN7CPlayer49removeQuestItemFromInventoryOrPetsInventoryByGuidExxbbN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(qRemoveItem,"_ZN7CPlayer44removeItemFromInventoryOrPetsInventoryByGuidExbbN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(qResolve,"_ZN14CQuestUnitData20getBaseUnitDataGroupEv")
TL_FUNCTION(qSeed,"_ZN9UTILITIES7setSeedEi")
TL_FUNCTION(qRandom,"_ZN9UTILITIES20randomIntegerBetweenEii")
TL_FUNCTION(qReplace,"_ZN6CQuest17replaceStringTagsERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qItemComplete,"_ZN16CQuestDialogItem14dialogCompleteEP7CPlayer")
TL_FUNCTION(qPetRemove,"_ZN10CCharacter9removePetEPS_")
TL_FUNCTION(qPetAdd,"_ZN10CCharacter6addPetEPS_")
TL_FUNCTION(qIcon,"_ZN13CQuestManager16calculateNPCIconEP10CCharacter")
TL_FUNCTION(qVisible,"_ZN10CCharacter10setVisibleEbb")
TL_FUNCTION(qSoundFind,"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qSampleAdd,"_ZN10CSoundBank9addSampleEix")
TL_FUNCTION(qSamplePlay,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
namespace {
struct Case{unsigned mode,seed;};
Ogre::SceneManager* fixtureScene;
autotest::Capture* cap;const Case* input;CPlayer* currentPlayer;CQuest* currentQuest;CDataGroup* groups[2];CCharacter* actors[4];CSoundData* soundData;CQuestDialogItem* items[8];unsigned itemCount;
void word(unsigned n){cap->add(&n,4);}void wide(const std::wstring& s){word(s.size());cap->add(s.data(),4*s.size());}
unsigned actorId(CCharacter* p){for(unsigned i=0;i<4;++i)if(p==actors[i])return i+1;return p?99:0;}
CPlayer* getPlayer(CQuest* p){word(101);word(p==currentQuest);return input->seed%7?currentPlayer:NULL;}
long long guid(CResourceManager*,CDataGroup* group,const std::wstring& key){word(102);word(group==groups[0]?1:group==groups[1]?2:99);wide(key);return input->seed%5?0x123456789abcdefLL:-1;}
bool removeQuest(CPlayer* p,long long q,long long g,bool a,bool b,UNITTYPES::EUNITTYPES type){word(103);word(p==currentPlayer);cap->add(&q,8);cap->add(&g,8);word(a);word(b);word(type);return true;}
bool removeItem(CPlayer* p,long long g,bool a,bool b,UNITTYPES::EUNITTYPES type){word(104);word(p==currentPlayer);cap->add(&g,8);word(a);word(b);word(type);return false;}
CDataGroup* resolve(CQuestUnitData* p){word(105);word(p->m_questUnitDataId);return input->seed%3?groups[0]:NULL;}
void setSeed(int seed){word(106);word(seed);}
int random(int low,int high){word(107);word(low);word(high);return int(input->seed%6);}
std::wstring replace(CQuest* q,const std::wstring& text){word(108);word(q==currentQuest);wide(text);return L"<"+text+L">";}
void itemComplete(CQuestDialogItem* p,CPlayer* player){word(109);unsigned id=99;for(unsigned i=0;i<itemCount;++i)if(items[i]==p)id=i;word(id);word(player==currentPlayer);}
void removePet(CCharacter* who,CCharacter* pet){word(110);word(who==currentPlayer);word(actorId(pet));for(std::vector<CCharacter*>::iterator i=who->m_Followers.begin();i!=who->m_Followers.end();++i)if(*i==pet){who->m_Followers.erase(i);break;}}
void addPet(CCharacter* who,CCharacter* pet){word(111);word(who==currentPlayer);word(actorId(pet));who->m_Followers.push_back(pet);}
void icon(CQuestManager*,CCharacter* pet){word(112);word(actorId(pet));}
void visible(CCharacter* pet,bool a,bool b){word(113);word(actorId(pet));word(a);word(b);}
CSoundData* soundFind(CSoundBankDataInformation*,const std::wstring& name){word(114);wide(name);return input->seed%3?soundData:NULL;}
void sampleAdd(CSoundBank*,int index,long long guid){word(115);word(index);cap->add(&guid,8);}
int samplePlay(CSoundBank*,int index,Ogre::SceneNode* node,float a,float b,bool loop){word(116);word(index);word(node==NULL);cap->add(&a,4);cap->add(&b,4);word(loop);return 7;}
void statics(){const uintptr_t cells[]={0x14f9fe8,0x14fb488,0x14ff1a8,0x151d408};for(unsigned i=0;i<4;++i){void* p=NULL;std::memcpy(&p,(void*)cells[i],8);if(!p)new((void*)cells[i])std::wstring;}}
CQuestUnitData* unit(CQuest* quest,unsigned id){CQuestUnitData* p=static_cast<CQuestUnitData*>(Ogre::NedAllocImpl::allocBytes(sizeof(CQuestUnitData),0,0,0));unitNativeCtor(p,quest);p->m_questUnitDataId=id;return p;}
void observeTree(CQuestUnitData* p,TSafePointer<CQuestUnitData>* observers,unsigned& count){if(count>=8)std::abort();observers[count++].setObject(p);for(unsigned i=0;i<p->m_children.size();++i)observeTree(p->m_children[i],observers,count);}
void markFields(CQuestUnitData* p,unsigned seed){
 static const int relative[]={0,1,-1,7,-20,INT_MAX,INT_MIN};p->m_relativeFloor=relative[seed%7];p->m_specificFloor=int((seed/7)%9)-2;p->m_unitType=seed%3?8:22;p->m_currentUnitCount=seed%9?int(seed%5):-1;p->m_trackUnitEvents=seed%4!=0;p->m_completed=seed&1;p->m_pBaseUnitDataGroup=seed%3?groups[0]:NULL;p->m_unitSearchMode=(seed/4)%3;p->m_removeFromInventory=seed&2;p->m_removeOnlyQuestItems=seed&4;
}
void side(void* raw,autotest::Capture& out,bool ours){
 const Case& c=*static_cast<Case*>(raw);input=&c;cap=&out;statics();std::srand(c.seed+17);
 finishlevel::Fixture resources;CDataGroup a(L"first",NULL,2,2,NULL),b(L"second",NULL,2,2,NULL);groups[0]=&a;groups[1]=&b;
 union QuestStorage{long double alignment;unsigned char bytes[sizeof(CQuest)];} qs;CQuest* quest=reinterpret_cast<CQuest*>(qs.bytes);questNativeCtor(quest,&resources.resources,NULL);currentQuest=quest;
 quest->m_iUnknown20=int(c.seed%17)-7;quest->m_iUnknown1C=c.seed%3?int(c.seed):-1;quest->m_iUnknown1C8=0x3456789abcdefLL;
 CCharacter first(NULL),second(NULL),third(NULL),fourth(NULL);actors[0]=&first;actors[1]=&second;actors[2]=&third;actors[3]=&fourth;
 for(unsigned i=0;i<4;++i){actors[i]->m_pDataGroup=groups[(i+c.seed)%2];actors[i]->m_iQuestGuid=(c.seed+i)%3?quest->m_iUnknown1C8:0;actors[i]->m_iQuestState=(c.seed+i)%3;actors[i]->m_eUnitType=static_cast<UNITTYPES::EUNITTYPES>((c.seed+i)%2?8:22);actors[i]->m_bBaseUnitFlag190=false;}
 currentPlayer=NULL;
 if(c.mode==3||c.mode==7||c.mode==8){resources.resources.m_pSceneManager=fixtureScene;currentPlayer=nativegame::createPlayer(&resources.resources);}
 CSoundManager bankOwner(false);
 detour::Set hooks;TL_REDIRECT(hooks,qPlayer,&getPlayer);TL_REDIRECT(hooks,qGuid,&guid);TL_REDIRECT(hooks,qRemoveQuest,&removeQuest);TL_REDIRECT(hooks,qRemoveItem,&removeItem);TL_REDIRECT(hooks,qResolve,&resolve);TL_REDIRECT(hooks,qSeed,&setSeed);TL_REDIRECT(hooks,qRandom,&random);TL_REDIRECT(hooks,qReplace,&replace);TL_REDIRECT(hooks,qItemComplete,&itemComplete);TL_REDIRECT(hooks,qPetRemove,&removePet);TL_REDIRECT(hooks,qPetAdd,&addPet);TL_REDIRECT(hooks,qIcon,&icon);TL_REDIRECT(hooks,qVisible,&visible);TL_REDIRECT(hooks,qSoundFind,&soundFind);TL_REDIRECT(hooks,qSampleAdd,&sampleAdd);TL_REDIRECT(hooks,qSamplePlay,&samplePlay);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.mode<5){
  CQuestUnitData* self=unit(quest,1);markFields(self,c.seed);
  for(unsigned i=0;i<c.seed%4;++i){CQuestUnitData* child=unit(quest,2+i);markFields(child,c.seed+i+1);self->m_children.add(child);if(i%2){CQuestUnitData* leaf=unit(quest,7+i);markFields(leaf,c.seed+i+9);child->m_children.add(leaf);}}
  if(c.mode==0){typedef int(*F)(CQuestUnitData*);F fn=ours?newActive:oldActive;autotest::invoke(out,fn,self);}
  if(c.mode==1){typedef int(*F)(CQuestUnitData*);F fn=ours?newDeepest:oldDeepest;autotest::invoke(out,fn,self);}
  if(c.mode==2){TSafePointer<CQuestUnitData> observers[8];unsigned watched=0;observeTree(self,observers,watched);typedef void(*F)(CQuestUnitData*);F fn=ours?newUnitDtor:oldUnitDtor;autotest::invoke(out,fn,self);word(watched);for(unsigned i=0;i<watched;++i){word(observers[i].getObject()==NULL);word(observers[i].m_nIndex);}Ogre::NedAllocImpl::deallocBytes(self);self=NULL;}
  if(c.mode==3){if(c.seed%8==0)self->m_pQuest=NULL;typedef void(*F)(CQuestUnitData*,bool);F fn=ours?newRemoveAll:oldRemoveAll;autotest::invoke(out,fn,self,c.seed&8);}
  if(c.mode==4){typedef bool(*F)(CQuestUnitData*,CBaseUnit*);F fn=ours?newDropped:oldDropped;autotest::invoke(out,fn,self,c.seed%5?static_cast<CBaseUnit*>(&first):NULL);}
  if(self){word(self->m_currentUnitCount);word(self->m_completed);word(self->m_pBaseUnitDataGroup==groups[0]?1:self->m_pBaseUnitDataGroup?99:0);for(unsigned i=0;i<self->m_children.size();++i){word(self->m_children[i]->m_currentUnitCount);word(self->m_children[i]->m_completed);}oldUnitDtor(self);Ogre::NedAllocImpl::deallocBytes(self);}
 }else{
  union DialogStorage{long double alignment;unsigned char bytes[sizeof(CQuestDialog)];} ds;std::memset(ds.bytes,0xa5,sizeof ds.bytes);CQuestDialog* self=reinterpret_cast<CQuestDialog*>(ds.bytes);
  if(c.mode==10){typedef void(*F)(CQuestDialog*,CQuest*);F fn=ours?newDialogCtor:oldDialogCtor;autotest::invoke(out,fn,self,c.seed%2?quest:NULL);word(self->m_dialogText.size());word(self->m_dialogText.m_nGrowBy);word(self->m_dialogItemsToGive.m_nGrowBy);word(self->m_bIconAboveHead);word(self->m_bMakePetOnAccept);word(self->m_pSoundBank==NULL);wide(self->m_sThemeOverride);oldDialogDtor(self);}
  else{
   oldDialogCtor(self,quest);self->m_sSoundName=L"SAMPLE";self->m_pNPCDataGroup=c.seed%3?groups[0]:NULL;quest->m_iUnknown1E8=c.seed%4?reinterpret_cast<long long>(groups[1]):0;
   if(c.mode==5){if(c.seed%7==0)self->m_pQuest=NULL;typedef bool(*F)(CQuestDialog*,CBaseUnit*);F fn=ours?newNPC:oldNPC;CBaseUnit* actor=&first;if(c.seed%5==0&&(self->m_pNPCDataGroup||!self->m_pQuest||!quest->m_iUnknown1E8))actor=NULL;autotest::invoke(out,fn,self,actor);}
   if(c.mode==6){for(unsigned i=0;i<1+c.seed%4;++i)self->m_dialogText.add(i%2?L"B{tag}":L"A/строка");if(c.seed%5==0)self->m_pQuest=NULL;typedef std::wstring(*F)(CQuestDialog*,bool);F fn=ours?newDialog:oldDialog;if(!autotest::beginInvocation(out,fn))return;wide(fn(self,c.seed&4));out.callCompleted=1;}
   if(c.mode==7||c.mode==11){itemCount=0;for(unsigned i=0;i<c.seed%7;++i){CQuestDialogItem* item=new CQuestDialogItem(self);items[itemCount++]=item;if(i%2)self->m_dialogItemsToGive.add(item);else self->m_dialogItemsToRemove.add(item);}self->m_bItemsGiven=c.seed&8;self->m_bMakePetOnAccept=c.seed&4;
    if(c.mode==7){typedef void(*F)(CQuestDialog*,CBaseUnit*);F fn=ours?newItems:oldItems;autotest::invoke(out,fn,self,c.seed%3?static_cast<CBaseUnit*>(&first):NULL);word(self->m_bItemsGiven);word(currentPlayer->m_Followers.size());currentPlayer->m_Followers.clear();}
   }
   if(c.mode==8){for(unsigned i=0;i<c.seed%5;++i)currentPlayer->m_Followers.push_back(actors[i]);self->m_bDialogInitialized=c.seed&1;self->m_bRemoveAsPetOnComplete=c.seed&2;self->m_bDestroyPet=c.seed&4;typedef void(*F)(CQuestDialog*);F fn=ours?newCleanup:oldCleanup;autotest::invoke(out,fn,self);word(currentPlayer->m_Followers.size());for(unsigned i=0;i<currentPlayer->m_Followers.size();++i)word(actorId(currentPlayer->m_Followers[i]));for(unsigned i=0;i<4;++i)word(actors[i]->m_bBaseUnitFlag190);currentPlayer->m_Followers.clear();}
   if(c.mode==9){CSoundManager manager(false);CSoundData data;data.m_group=NULL;data.m_iGuid=0x123456789abcdefLL;soundData=&data;CMasterResourceManager* master=CMasterResourceManager::getSingleton();CSoundManager* previous=master->m_pSoundManager;master->m_pSoundManager=&manager;if(c.seed&1)self->m_pSoundBank=new CSoundBank(manager,false);typedef void(*F)(CQuestDialog*);F fn=ours?newSound:oldSound;autotest::invoke(out,fn,self);word(self->m_pSoundBank!=NULL);oldDialogDtor(self);self=NULL;master->m_pSoundManager=previous;}
   if(c.mode==11){TSafePointer<CQuestDialogItem> itemObservers[8];for(unsigned i=0;i<itemCount;++i)itemObservers[i].setObject(items[i]);TSafePointer<CSoundBank> bankObserver;if(c.seed&8){self->m_pSoundBank=new CSoundBank(bankOwner,false);bankObserver.setObject(self->m_pSoundBank);}TSafePointer<CQuestDialog> weak;weak.setObject(self);typedef void(*F)(CQuestDialog*);F fn=ours?newDialogDtor:oldDialogDtor;autotest::invoke(out,fn,self);word(weak.getObject()==NULL);word(weak.m_nIndex);for(unsigned i=0;i<itemCount;++i){word(itemObservers[i].getObject()==NULL);word(itemObservers[i].m_nIndex);}word(bankObserver.getObject()==NULL);self=NULL;}
   if(self)oldDialogDtor(self);
  }
 }
 hooks.restore();if(currentPlayer){nativegame::destroyPlayer(currentPlayer);currentPlayer=NULL;}questNativeDtor(quest);
}
void before(void* p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host* host,unsigned mode,const char* name,uintptr_t address,unsigned count){nativegame::Services services;if(!services.ready())return 1;fixtureScene=services.scene;autotest::Coverage coverage(name,address);for(unsigned seed=0;seed<count;++seed){Case c={mode,seed};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    quest mode%u seed%u issue%u/%u status%d/%d length%lu/%lu\n",mode,seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(all_quest_unit_floor){return run(host,0,"all_quest_unit_floor",0xd3dc60,512);}
TL_TEST(all_quest_unit_deepest){return run(host,1,"all_quest_unit_deepest",0xd3dca0,512);}
TL_TEST(all_quest_unit_destructor){return run(host,2,"all_quest_unit_destructor",0xd467d0,64);}
TL_TEST(all_quest_unit_remove){return run(host,3,"all_quest_unit_remove",0xd47530,256);}
TL_TEST(all_quest_unit_dropped){return run(host,4,"all_quest_unit_dropped",0xd48800,256);}
TL_TEST(all_quest_dialog_npc){return run(host,5,"all_quest_dialog_npc",0xd1de30,128);}
TL_TEST(all_quest_dialog_text){return run(host,6,"all_quest_dialog_text",0xd1df70,128);}
TL_TEST(all_quest_dialog_items){return run(host,7,"all_quest_dialog_items",0xd1e050,64);}
TL_TEST(all_quest_dialog_pet_cleanup){return run(host,8,"all_quest_dialog_pet_cleanup",0xd1e170,128);}
TL_TEST(all_quest_dialog_sound){return run(host,9,"all_quest_dialog_sound",0xd1e300,32);}
TL_TEST(all_quest_dialog_ctor){return run(host,10,"all_quest_dialog_ctor",0xd24940,16);}
TL_TEST(all_quest_dialog_dtor){return run(host,11,"all_quest_dialog_dtor",0xd26120,64);}
