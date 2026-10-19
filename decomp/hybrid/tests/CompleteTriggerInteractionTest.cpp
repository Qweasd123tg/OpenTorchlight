#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#define private public
#define protected public
#include "TriggerUnit.h"
#include "Level.h"
#include "Player.h"
#include "GenericModel.h"
#include "AnimationSet.h"
#include "Inventory.h"
#include "Equipment.h"
#include "EquipmentRef.h"
#include "QuestManager.h"
#include "Quest.h"
#include "SteamStats.h"
#include "UnitResourceList.h"
#include "SoundBankDataInformation.h"
#include "SoundBank.h"
#undef protected
#undef private
#include "NativeTriggerLevelFixture.h"
#include "tests/NativeMenuClient.h"
#include "tests/NativeEditorControls.h"
#include "tests/CharacterEmptyGlobals.h"
#include "tests/SmallMassCompare.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(bool,txInteractOld,(CTriggerUnit*,CCharacter*),"_ZN12CTriggerUnit8interactEP10CCharacter")
extern "C" bool txInteractNew(CTriggerUnit*,CCharacter*) __asm__("_ZN12CTriggerUnit8interactEP10CCharacter");
TL_FUNCTION(txTrigger,"_ZN12CTriggerUnit7triggerEP10CCharacter")
TL_FUNCTION(txRemove,"_ZN10CInventory15removeEquipmentEP10CEquipment")
TL_FUNCTION(txStat,"_ZN11CSteamStats13incrementStatE6ESTATSi")
TL_FUNCTION(txQuests,"_ZN13CQuestManager10loadQuestsEv")
namespace {
nativegame::Services*services;autotest::Capture*output;CTriggerUnit*unit;CCharacter*actor;CInventory*ownInventory;CInventory*petInventory;unsigned seed;std::vector<CEquipment*>items;
void n(unsigned x){output->add(&x,4);}void noQuestFile(CQuestManager*){}
bool trigger(CTriggerUnit*p,CCharacter*a){n(1);n(p==unit);n(a==actor);return seed%3!=0;}
long long remove(CInventory*p,CEquipment*e){n(2);n(p==ownInventory?1:p==petInventory?2:0);unsigned id=~0u;for(unsigned i=0;i<items.size();++i)if(items[i]==e)id=i;n(id);n(e->m_iUnknown238);return 1;}
void stat(CSteamStats*p,ESTATS which,int amount){n(3);n(p==CSteamStats::getSingleton());n(which);n(amount);}
struct Trigger:CTriggerUnit{
 explicit Trigger(CResourceManager*r):CTriggerUnit(r){}
 virtual void BroadcastEvent(unsigned e){n(4);n(e);CEditorBaseObject::BroadcastEvent(e);}
};
void equipment(CInventory*inventory,CResourceManager*r,unsigned count,unsigned base){
 for(unsigned i=0;i<count;++i){CEquipment*e=new CEquipment(r);e->m_iUnitValue1A0=(seed+i)%5?1234567:7654321;e->m_iUnknown238=int((seed/7+i)%5)-1;CEquipmentRef*ref=new CEquipmentRef;ref->m_pEquipment=e;ref->m_iSlot=12+i;ref->m_originalSlot=ref->m_iSlot;ref->m_flag20=false;ref->m_effectsEnabled=false;inventory->m_equipmentRefs.add(ref);items.push_back(e);}
}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;items.clear();nativetrigger::LevelFixture fixture(*services);
 Trigger u(&fixture.resources);unit=&u;u.sceneNodeSetParent(services->scene->getRootSceneNode(),false);u.m_pSoundBank=new CSoundBank(*services->master->m_pSoundManager,false);u.m_bEnabled=true;u.m_bItemFlag1F0=true;u.m_maxState=seed/5%2?1:3;u.m_treasureClass=seed/7%2?L"":L"treasure";
 CPlayer*player=nativegame::createPlayer(&fixture.resources);CPlayer*pet=nativegame::createPlayer(&fixture.resources);CCharacter other(&fixture.resources);actor=player;if(!player->getInventory())player->m_pInventory=new CInventory(player,40);if(!pet->getInventory())pet->m_pInventory=new CInventory(pet,40);ownInventory=player->getInventory();petInventory=pet->getInventory();
 CSoundBankDataInformation soundInfo(NULL);CSoundBankDataInformation*previousInfo=services->master->m_pSoundBankDataInformation;services->master->m_pSoundBankDataInformation=&soundInfo;
 CQuestManager*quests=CQuestManager::getSingleton();bool ownQuests=!quests;if(!quests){detour::Set loading;TL_REDIRECT(loading,txQuests,&noQuestFile);if(loading.failed())std::abort();quests=new CQuestManager(&fixture.resources);}unsigned questIndex=quests->m_Unknown18.size();player->m_questManager=quests;CQuest*quest=new CQuest(&fixture.resources,quests);quest->m_sUnknown50=seed/11%2?L"ACTIVE":L"other";quests->m_Unknown18.add(quest);u.m_requiredQuest=seed/13%3==0?L"":seed/13%3==1?L"ACTIVE":L"missing";
 CUnitResourceList resources;CUnitResourceList*previousList=m_pGlobalUnitResourceList;m_pGlobalUnitResourceList=&resources;CDataGroup data(L"key",NULL,10,10,NULL);data.SetDataValue(L"UNIT_GUID",L"1234567",false);resources.m_dataGroupsByResourceGroupAndName[L"ITEMS"][L"KEY"]=&data;
 u.m_requiredItem=seed%7==0?L"":seed%7==1?L"MISSING":L"KEY";u.m_value2F0=int(seed/3%9)-2;u.m_flag2F4=seed/5%2;
 equipment(ownInventory,&fixture.resources,seed/2%4,0);equipment(petInventory,&fixture.resources,seed/7%4,4);pet->m_eAIState=static_cast<EAIState>(seed/17%2?42:0);if(seed/19%3)player->m_Followers.push_back(seed/19%3==1?pet:NULL);
 Ogre::AnimationStateSet states;CAnimationSet animations;animations.m_lUnknown28.push_back("IDLE");animations.m_lUnknown40.push_back(L"fixture");animations.m_lAnimationGroups.push_back(std::vector<CKeyframe*>());states.createAnimationState("IDLE",0,3,1,false);
 if(c.op==0){unsigned gate=seed%8;if(gate==0)u.m_bEnabled=false;else if(gate==1)u.m_bItemFlag1F0=false;else if(gate==2)actor=NULL;else if(gate==3)actor=&other;else if(gate==4||gate==5){u.m_unitModel=new CGenericModel(&fixture.resources,services->scene,L"",L"",false);u.m_unitModel->m_animationSet=&animations;u.m_unitModel->m_animationStates.add(states.getAnimationState("IDLE"));if(gate==4)u.m_unitModel->playAnimation(0,true,1,-1);}}
 CResourceManager*saved=u.m_pResourceManager;if(c.op==1&&seed/23%3==1)u.m_pResourceManager=NULL;
 CSteamStats stats;detour::Set hooks;TL_REDIRECT(hooks,txTrigger,&trigger);TL_REDIRECT(hooks,txRemove,&remove);TL_REDIRECT(hooks,txStat,&stat);if(hooks.failed())std::abort();autotest::invoke(out,ours?txInteractNew:txInteractOld,&u,actor);hooks.restore();u.m_pResourceManager=saved;n(u.m_bEnabled);n(u.m_bItemFlag1F0);n(ownInventory->m_equipmentRefs.size());n(petInventory->m_equipmentRefs.size());
 if(u.m_unitModel)u.m_unitModel->m_animationSet=NULL;player->m_Followers.clear();player->m_questManager=NULL;quests->m_Unknown18.removeAt(questIndex);delete quest;if(ownQuests)delete quests;services->master->m_pSoundBankDataInformation=previousInfo;m_pGlobalUnitResourceList=previousList;fixture.resources.m_pLevel=NULL;nativegame::destroyPlayer(pet);nativegame::destroyPlayer(player);fixture.resources.m_pLevel=&fixture.level;
}
int worker(const tlhybrid_host*host){
 initEmptyGlobals();void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x148c4e8),8);if(!p)new(reinterpret_cast<void*>(0x148c4e8))std::wstring;
 nativegame::Services native;services=&native;if(!native.ready())return 1;menugui::Audio audio(native.master);nativeeditor::Controls editor(native);
 if(smallmass::run(host,0,"trigger_interact_gates_native",0x9095c0,&side,192))return 1;return smallmass::run(host,1,"trigger_interact_inventory_native",0x9095c0,&side,768);
}
}
TL_TEST(complete_trigger_interaction){return systems_fixture::isolated(&worker,host);}
