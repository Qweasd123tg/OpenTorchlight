#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "QuestDialogItem.h"
#include "QuestDialog.h"
#include "Quest.h"
#include "Equipment.h"
#undef protected
#undef private
TL_ORIGINAL(void,qiOld,(CQuestDialogItem*,CPlayer*),"_ZN16CQuestDialogItem14dialogCompleteEP7CPlayer")
extern "C" void qiNew(CQuestDialogItem*,CPlayer*) __asm__("_ZN16CQuestDialogItem14dialogCompleteEP7CPlayer");
TL_ORIGINAL(void,qiQuestCtor,(CQuest*,CResourceManager*,CQuestManager*),"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_ORIGINAL(void,qiQuestDtor,(CQuest*),"_ZN6CQuestD1Ev")
TL_FUNCTION(qiGold,"_ZN10CCharacter8giveGoldEi")
TL_FUNCTION(qiGuid,"_ZN16CResourceManager22getUnitGuidByDataGroupEP10CDataGroupRKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qiRemove,"_ZN7CPlayer44removeItemFromInventoryOrPetsInventoryByGuidExbbN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(qiRemovePet,"_ZN10CCharacter9removePetEPS_")
TL_FUNCTION(qiAddPet,"_ZN10CCharacter6addPetEPS_")
TL_FUNCTION(qiRemoveUnit,"_ZN6CLevel10removeUnitEP9CBaseUnitb")
TL_FUNCTION(qiCreate,"_ZN16CResourceManager10createUnitEP10CDataGroupibb")
TL_FUNCTION(qiPickup,"_ZN10CInventory15pickupEquipmentEP10CEquipmentb")
TL_FUNCTION(qiPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(qiRandom,"_ZN6CLevel22randomOpenItemPositionERKN4Ogre7Vector3Efb")
TL_FUNCTION(qiAddItem,"_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
namespace {
using namespace smallmass;
unsigned seed,removals;Ogre::SceneManager*scene;CPlayer*player;CQuestDialogItem*self;CQuest*quest;CQuestDialog*dialog;CResourceManager*resources,*alternate;CLevel*level;CDataGroup*groups[2];CInventory*inventory;CBaseUnit*created;CCharacter*pets[4];
int id(const void*p){if(!p)return -1;if(p==player)return 0;if(p==self)return 1;if(p==quest)return 2;if(p==dialog)return 3;if(p==resources)return 4;if(p==alternate)return 5;if(p==level)return 6;if(p==inventory)return 7;if(p==created)return 8;for(unsigned i=0;i<2;++i)if(p==groups[i])return 10+i;for(unsigned i=0;i<4;++i)if(p==pets[i])return 20+i;return -2;}
void event(unsigned tag,const void*p){number(tag);number(id(p));}
void gold(CCharacter*p,int amount){event(1,p);number(amount);}
long long guid(CResourceManager*p,CDataGroup*g,const std::wstring&key){event(2,p);number(id(g));text(key);return seed%7?0x123456789abcdefLL:-1;}
bool remove(CPlayer*p,long long value,bool a,bool b,UNITTYPES::EUNITTYPES type){event(3,p);output->add(&value,8);number(a);number(b);number(type);++removals;if(seed&256)self->m_iCount=1;return(seed+removals)%3==0;}
void removePet(CCharacter*p,CCharacter*pet){event(4,p);number(id(pet));for(std::vector<CCharacter*>::iterator i=p->m_Followers.begin();i!=p->m_Followers.end();++i)if(*i==pet){p->m_Followers.erase(i);break;}if(seed&128)player->m_pResourceManager=alternate;}
void addPet(CCharacter*p,CCharacter*pet){event(5,p);number(id(pet));p->m_Followers.push_back(pet);}
void removeUnit(CLevel*p,CBaseUnit*u,bool flag){event(6,p);number(id(u));number(flag);}
CBaseUnit*create(CResourceManager*p,CDataGroup*g,int lev,bool a,bool b){event(7,p);number(id(g));number(lev);number(a);number(b);if(seed&128)player->m_pResourceManager=alternate;return seed%11==0?NULL:created;}
CEquipment*pickup(CInventory*p,CEquipment*e,bool flag){event(8,p);number(id(e));number(flag);output->add(&e->m_iQuestGuid,8);return seed&32?e:NULL;}
Ogre::Vector3 position(CPositionableObject*p,bool flag){event(9,p);number(flag);return Ogre::Vector3(1.25f,-2.5f,3.75f);}
Ogre::Vector3 randomPosition(CLevel*p,const Ogre::Vector3&v,float radius,bool flag){event(10,p);vector(v);floating(radius);number(flag);return Ogre::Vector3(-3.5f,2.25f,-1.75f);}
CItem*addItem(CLevel*p,CItem*item,const Ogre::Vector3&v,bool flag){event(11,p);number(id(item));vector(v);number(flag);return item;}
void qiSide(Case&c,bool ours,autotest::Capture&out){output=&out;seed=c.index;removals=0;created=NULL;finishlevel::Fixture fixture;resources=&fixture.resources;level=&fixture.level;resources->m_pSceneManager=scene;CResourceManager other(NULL);alternate=&other;other.m_pLevel=seed&64?level:NULL;CDataGroup a(L"A",NULL,2,2,NULL),b(L"B",NULL,2,2,NULL);groups[0]=&a;groups[1]=&b;player=nativegame::createPlayer(resources);CInventory*originalInventory=player->m_pInventory;inventory=originalInventory?originalInventory:new CInventory(player,10);player->m_pInventory=seed&16?NULL:inventory;
 CQuest qStorage(resources,NULL);quest=&qStorage;quest->m_iUnknown1C8=0x123456789abcdefLL;CQuestDialog dialogStorage(quest);dialog=&dialogStorage;CQuestDialogItem item(dialog);self=&item;self->m_bGive=seed&1;self->m_bGold=seed&2;int counts[]={-2,-1,0,1,2,3,(-2147483647-1)};self->m_iCount=counts[(seed/4)%7];self->m_pDataGroup=seed&4?groups[0]:NULL;
 TSafePointer<CCharacter>petWeak[4];for(unsigned i=0;i<4;++i){pets[i]=new CCharacter(NULL);pets[i]->m_pDataGroup=(seed/7+i)%3?groups[0]:groups[1];petWeak[i].setObject(pets[i]);if(i<(seed/13)%5)player->m_Followers.push_back(pets[i]);}
 unsigned kind=(seed/8)%3;TSafePointer<CBaseUnit>createdWeak;if(kind==0)created=new CEquipment(NULL);else if(kind==1)created=new CCharacter(NULL);else created=new finishlevel::Item(NULL);createdWeak.setObject(created);
 detour::Set hooks;TL_REDIRECT(hooks,qiGold,&gold);TL_REDIRECT(hooks,qiGuid,&guid);TL_REDIRECT(hooks,qiRemove,&remove);TL_REDIRECT(hooks,qiRemovePet,&removePet);TL_REDIRECT(hooks,qiAddPet,&addPet);TL_REDIRECT(hooks,qiRemoveUnit,&removeUnit);TL_REDIRECT(hooks,qiCreate,&create);TL_REDIRECT(hooks,qiPickup,&pickup);TL_REDIRECT(hooks,qiPosition,&position);TL_REDIRECT(hooks,qiRandom,&randomPosition);TL_REDIRECT(hooks,qiAddItem,&addItem);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void(*Fn)(CQuestDialogItem*,CPlayer*);Fn fn=ours?qiNew:qiOld;if(!autotest::beginInvocation(out,fn))return;fn(self,seed%17==0?NULL:player);out.callCompleted=1;number(removals);number(self->m_iCount);number(id(player->m_pResourceManager));number(player->m_Followers.size());for(unsigned i=0;i<player->m_Followers.size();++i)number(id(player->m_Followers[i]));for(unsigned i=0;i<4;++i)number(petWeak[i].getObject()==NULL);number(createdWeak.getObject()==NULL);if(createdWeak.getObject())output->add(&created->m_iQuestGuid,8);
 hooks.restore();player->m_Followers.clear();player->m_pInventory=originalInventory;player->m_pResourceManager=resources;if(!originalInventory)delete inventory;for(unsigned i=0;i<4;++i)if(petWeak[i].getObject())delete pets[i];if(createdWeak.getObject())delete created;other.m_pLevel=NULL;nativegame::destroyPlayer(player);player=NULL;
}
}
TL_TEST(complete_quest_dialog_item){nativegame::Services services;if(!services.ready())return 1;scene=services.scene;return smallmass::run(host,0,"complete_quest_dialog_item",0xdf5fd0,&qiSide,512);}
