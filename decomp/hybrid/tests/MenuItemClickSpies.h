// Private fixture support only. No TL_TEST / original invocation until all
// direct and virtual collaborators have controlled implementations.
#ifndef MENU_ITEM_CLICK_SPIES_H
#define MENU_ITEM_CLICK_SPIES_H
#include <cstring>
#include <vector>
#include "MenuItemClickState.h"
#include "AutoTest.h"
namespace menu_click_fixture {
using namespace menu_item_click_detail;
struct Case {
    unsigned scenario, variant, failureMode, pickupFailures, equipResults;
    int slot, requiredPane, actualPane;
    unsigned openMask, shiftMask;
    bool returnValue, useAllowed, canEquip;
};
static unsigned long long storage[48][5120];
static CEquipment* inventorySlots[5][100];
static void* itemTable[128];
static void* menuTable[16];
static CCharacter* followerStorage[2];
static autotest::Capture* capture;
static const Case* current;
static unsigned keyCalls,pickupCalls,equipCalls;
static unsigned openMask;
static CCharacter* menuOwners[6];
static std::vector<TSafePointer<void*>*> registered[48];
static unsigned itemTags[4][8];
static unsigned itemTagCounts[4];
static UIState* ui;
static CGameUI* gameUI;
template<class T> T* object(unsigned index){return reinterpret_cast<T*>(storage[index]);}
template<class T> T& field(void* p,unsigned offset){return *reinterpret_cast<T*>(static_cast<char*>(p)+offset);}
static void number(int v){capture->add(&v,4);}
static void scalar(float v){capture->add(&v,4);}
static int objectIndex(const void* p) {
    if(!p)return -1;
    uintptr_t value=reinterpret_cast<uintptr_t>(p);
    uintptr_t begin=reinterpret_cast<uintptr_t>(storage);
    uintptr_t end=begin+sizeof(storage);
    if(value<begin || value>=end){capture->issue=autotest::Capture::UnsupportedPointer;return -2;}
    return (value-begin)/sizeof(storage[0]);
}
static void pointer(const void* p){int i=objectIndex(p);number(i);number(i<0?0:reinterpret_cast<const char*>(p)-reinterpret_cast<const char*>(storage[i]));}
static void event(int e,const void* p){number(e);pointer(p);}
static bool unitIs(CBaseUnit* unit,UNITTYPES::EUNITTYPES tag) {
    event(1,unit);number(tag);int i=objectIndex(unit);
    if(i==2)return tag==UNITTYPES::PLAYER;
    if(i==4)return tag==UNITTYPES::MERCHANT || ((current->variant&4) && tag==UNITTYPES::GAMBLER);
    if(i==5)return tag==UNITTYPES::STASH;
    if(i==6)return tag==UNITTYPES::SHAREDSTASH;
    if(i>=18 && i<22)for(unsigned k=0;k<itemTagCounts[i-18];++k)if(itemTags[i-18][k]==unsigned(tag))return true;
    return false;
}
static short key(unsigned k){number(2);number(k);return (current->shiftMask&(1U<<keyCalls++))?short(-32768):short(0);}
static bool menuOpen(CSubMenu* p){event(3,p);int i=objectIndex(p)-12;return i>=0 && i<6 && (openMask&(1U<<i));}
static CBaseUnit* menuOwner(CSubMenu* p){event(4,p);int i=objectIndex(p)-12;if(i<0 || i>=6)_exit(61);return menuOwners[i];}
static void menuSetOpen(CSubMenu* p,bool value){event(5,p);number(value);int i=objectIndex(p)-12;if(i<0 || i>=6)_exit(61);if(value)openMask|=1U<<i;else openMask&=~(1U<<i);}
static void menuLayout(CSubMenu* p){event(6,p);}
static void closeLeft(CGameUI* p){event(7,p);openMask&=~(1U<<1);}
static void closeRight(CGameUI* p){event(8,p);openMask&=~1U;}
static CEquipment* slotItem(CInventory* p,unsigned slot){event(9,p);number(slot);int i=objectIndex(p)-7;if(i<0 || i>=5)_exit(62);return slot<100?inventorySlots[i][slot]:NULL;}
static int findSlot(CInventory* p,CEquipment* item){event(10,p);pointer(item);int i=objectIndex(p)-7;if(i<0 || i>=5)_exit(62);for(int k=0;k<100;++k)if(inventorySlots[i][k]==item)return k;return -1;}
static long long removeEquipment(CInventory* p,CEquipment* item){event(11,p);pointer(item);int i=objectIndex(p)-7;if(i<0 || i>=5)_exit(62);for(int k=0;k<100;++k)if(inventorySlots[i][k]==item)inventorySlots[i][k]=NULL;return 0;}
static CEquipment* pickupAt(CInventory* p,CEquipment* item,int slot,bool allow) {
    event(12,p);pointer(item);number(slot);number(allow);int i=objectIndex(p)-7;if(i<0 || i>=5)_exit(62);
    bool fail=(current->pickupFailures&(1U<<(pickupCalls++%32)))!=0;if(fail)return NULL;
    if(slot>=0 && slot<100)inventorySlots[i][slot]=item;
    return item;
}
static CEquipment* pickupAny(CInventory* p,CEquipment* item,bool allow) {
    event(13,p);pointer(item);number(allow);int i=objectIndex(p)-7;if(i<0 || i>=5)_exit(62);
    bool fail=(current->pickupFailures&(1U<<(pickupCalls++%32)))!=0;if(fail)return NULL;
    for(int k=12;k<100;++k)if(!inventorySlots[i][k]){inventorySlots[i][k]=item;break;}
    return item;
}
static int requiredPane(CInventory* p,CEquipment* item){event(14,p);pointer(item);return current->requiredPane;}
static int itemPane(CInventory* p,unsigned slot){event(15,p);number(slot);return current->actualPane;}
static bool inventoryCanEquip(CInventory* p,CEquipment* item,bool flag){event(16,p);pointer(item);number(flag);return current->canEquip;}
static bool itemCanEquip(CEquipment* item,CCharacter* owner,bool flag){event(17,item);pointer(owner);number(flag);return current->canEquip;}
static bool firstFree(CInventory* p,CEquipment* item){event(18,p);pointer(item);bool okay=(current->equipResults&(1U<<(equipCalls++%32)))!=0;if(okay){int i=objectIndex(p)-7;if(i<0 || i>=5)_exit(62);inventorySlots[i][0]=item;}return okay;}
static void comparisonItems(CInventory* p,CEquipment* item,CEquipment** first,CEquipment** second){event(19,p);pointer(item);*first=(current->variant&1)?object<CEquipment>(20):NULL;*second=(current->variant&2)?object<CEquipment>(21):NULL;}
static void bonuses(CInventory* p){event(20,p);}
static void effectValues(CInventory* p){event(21,p);}
static void refreshEquipped(CInventory* p){event(22,p);}
static void setTab(CSubMenu* p,int tab){event(23,p);number(tab);}
static void setPetTab(CSubMenu* p,int tab){event(24,p);number(tab);}
static unsigned addSafe(CRunicCore* p,TSafePointer<void*>* ref){event(25,p);pointer(ref);int i=objectIndex(p);if(i<0)_exit(63);registered[i].push_back(ref);return registered[i].size()-1;}
static void removeSafe(CRunicCore* p,TSafePointer<void*>* ref,unsigned index){event(26,p);pointer(ref);number(index);int i=objectIndex(p);if(i<0)_exit(63);if(index<registered[i].size())registered[i][index]=NULL;}
static void deleteItem(CEquipment* p){event(27,p);int i=objectIndex(p);if(i<0)_exit(63);for(unsigned k=0;k<registered[i].size();++k)if(registered[i][k])registered[i][k]->invalidate();registered[i].clear();}
static void stack(CEquipment* p,int amount){event(28,p);number(amount);p->m_iUnknown238+=amount;}
static void drop(CEquipment* p){event(29,p);}
static void takeSound(CEquipment* p,Ogre::SceneNode* node){event(30,p);pointer(node);}
static void dropSound(CEquipment* p,Ogre::SceneNode* node){event(31,p);pointer(node);}
static int buyPrice(CEquipment* p){event(32,p);return 10+objectIndex(p)-18;}
static int sellPrice(CEquipment* p){event(33,p);return 3+objectIndex(p)-18;}
static void giveGold(CCharacter* p,int gold){event(34,p);number(gold);field<int>(p,0x444)+=gold;}
static void soldItem(CPlayer* p,CEquipment* item){event(35,p);pointer(item);}
static void journal(CPlayer* p,EJournalStatistic stat,int amount){event(36,p);number(stat);number(amount);}
static void playSample(CSoundBank* p,int sample,Ogre::SceneNode* node,float a,float b,bool flag){event(37,p);number(sample);pointer(node);scalar(a);scalar(b);number(flag);}
static void queueSample(CSoundBank* p,int sample,float a,float b){event(38,p);number(sample);scalar(a);scalar(b);}
static CSharedStash* shared(){number(39);return object<CSharedStash>(28);}
static CAchievements* achievements(){number(40);return object<CAchievements>(29);}
static CAchievement* achievement(CAchievements* p,EACHIEVEMENTS id){event(41,p);number(id);return (current->variant&2)?object<CAchievement>(30):NULL;}
static void forceComplete(CAchievement* p){event(42,p);}
static bool canUse(CEquipment* p,CCharacter* user,CBaseUnit* target){event(43,p);pointer(user);pointer(target);return current->useAllowed;}
static void use(CEquipment* p,CCharacter* user,CBaseUnit* target){event(44,p);pointer(user);pointer(target);}
static void targetItem(CCharacter* p,CItem* item){event(45,p);pointer(item);}
static bool castSkill(CCharacter* p,long long skill){event(46,p);capture->add(&skill,8);return true;}
static void renderBehind(CCharacter* p,bool value){event(47,p);number(value);}
static void mouseOver(CGameUI* p,CItem* item,bool value){event(48,p);pointer(item);number(value);}
static void cursorState(CGameUI* p,ECursorState state){event(49,p);number(state);}
static void hardwareCursor(CGameUI* p){event(50,p);}
static Ogre::Vector3 position(CPositionableObject* p,bool absolute){event(51,p);number(absolute);return Ogre::Vector3(float(objectIndex(p)),2.25f,-3.5f);}
static void addItem(CLevel* p,CItem* item,const Ogre::Vector3& where,bool flag){event(52,p);pointer(item);scalar(where.x);scalar(where.y);scalar(where.z);number(flag);}
static void addContainer(CEquipment* p,CEquipment* item){event(53,p);pointer(item);field<unsigned>(p,0x3f0)++;}
static void elemental(CEquipment* p){event(54,p);}
static CBaseUnit* create(CResourceManager* p,CDataGroup* data,int level,bool a,bool b){event(55,p);pointer(data);number(level);number(a);number(b);return object<CEquipment>(21);}
static void returnDragged(CGameUI* p){event(56,p);ui->draggedItem.setObject(NULL);ui->dragOwner.setObject(NULL);ui->dragSlot=-1;}
static CEGUI::UVector2 recordedPosition[48],recordedSize[48];
static void addWindow(CEGUI::Window* p,CEGUI::Window* child){event(57,p);pointer(child);field<CEGUI::Window*>(child,0xb0)=p;}
static void removeWindow(CEGUI::Window* p,CEGUI::Window* child){event(58,p);pointer(child);if(field<CEGUI::Window*>(child,0xb0)==p)field<CEGUI::Window*>(child,0xb0)=NULL;}
static void windowPosition(CEGUI::Window* p,const CEGUI::UVector2& v){event(59,p);scalar(v.d_x.d_scale);scalar(v.d_x.d_offset);scalar(v.d_y.d_scale);scalar(v.d_y.d_offset);recordedPosition[objectIndex(p)]=v;}
static void windowSize(CEGUI::Window* p,const CEGUI::UVector2& v){event(60,p);scalar(v.d_x.d_scale);scalar(v.d_x.d_offset);scalar(v.d_y.d_scale);scalar(v.d_y.d_offset);recordedSize[objectIndex(p)]=v;}
static unsigned scaledCalls;

static float scaledY(CGameUI* p,float v){event(61,p);scalar(v);if((current->variant&8) && ++scaledCalls==1)ui->mouseX+=37;return v*0.75f;}
static CEGUI::System* systemSingleton(){number(62);return object<CEGUI::System>(31);}
static bool mouseMove(CEGUI::System* p,float x,float y){event(63,p);scalar(x);scalar(y);return true;}
// Required before invocation: fixture setup, every redirect and full TL_TEST matrix.
}
#endif
