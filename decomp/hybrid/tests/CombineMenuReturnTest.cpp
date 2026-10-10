#include <cstring>
#include <map>
#include <new>
#define private public
#define protected public
#include "CombineMenu.h"
#include "Character.h"
#include "Equipment.h"
#include "Inventory.h"
#include "Level.h"
#include "ResourceManager.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, originalReturn,(CCombineMenu*,CEquipment*),"_ZN12CCombineMenu28returnItemsToCorrectLocationEP10CEquipment")
TL_ORIGINAL(void, originalUsed,(CCombineMenu*,CEquipment*),"_ZN12CCombineMenu13equipmentUsedEP10CEquipment")
extern "C" void candidateReturn(CCombineMenu*,CEquipment*) __asm__("_ZN12CCombineMenu28returnItemsToCorrectLocationEP10CEquipment");
extern "C" void candidateUsed(CCombineMenu*,CEquipment*) __asm__("_ZN12CCombineMenu13equipmentUsedEP10CEquipment");
TL_FUNCTION(slotFn,"_ZN10CInventory22getEquipmentEquippedAtE16EEQUIP_LOCATIONS")
TL_FUNCTION(equipFn,"_ZN10CInventory34equipEquipmentIntoSpecificLocationEP10CEquipment16EEQUIP_LOCATIONS")
TL_FUNCTION(hasFn,"_ZN10CInventory22isEquipmentInInventoryEP10CEquipment")
TL_FUNCTION(pickFn,"_ZN10CInventory15pickupEquipmentEP10CEquipmentb")
TL_FUNCTION(posFn,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(addFn,"_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
namespace {
typedef std::map<CEquipment*,std::pair<CInventory*,EEQUIP_LOCATIONS> > Locations;
struct Case {unsigned mask,location,mutation,mode;};const Case* cs;autotest::Capture* cap;CCombineMenu* menu;CCharacter* actors[2];CInventory* inventories[2];CEquipment* items[2];CLevel* levels[2];
void n(int x){cap->add(&x,4);}int id(void* p,void* a,void* b){return !p?0:p==a?1:p==b?2:99;}
void change(unsigned point){if(cs->mutation==point){menu->m_pCharacter=actors[1];actors[0]->m_pInventory=inventories[1];}}
CEquipment* slot(CInventory* p,EEQUIP_LOCATIONS loc){n(1);n(id(p,inventories[0],inventories[1]));n(int(loc));change(1);return cs->mask&16?items[1]:0;}
bool equip(CInventory* p,CEquipment* q,EEQUIP_LOCATIONS loc){n(2);n(id(p,inventories[0],inventories[1]));n(id(q,items[0],items[1]));n(int(loc));change(2);return cs->mask&32;}
bool has(CInventory* p,CEquipment* q){n(3);n(id(p,inventories[0],inventories[1]));n(id(q,items[0],items[1]));change(3);return cs->mask&64;}
CEquipment* pickup(CInventory* p,CEquipment* q,bool flag){n(4);n(id(p,inventories[0],inventories[1]));n(id(q,items[0],items[1]));n(flag);change(4);return cs->mask&128?items[1]:0;}
Ogre::Vector3 position(CPositionableObject* p,bool flag){n(5);n(id(p,actors[0],actors[1]));n(flag);change(5);return Ogre::Vector3(-17.25f,0.5f,913.125f);}
void add(CLevel* p,CItem* q,const Ogre::Vector3& pos,bool flag){n(6);n(id(p,levels[0],levels[1]));n(id(q,items[0],items[1]));cap->add(&pos,sizeof(pos));n(flag);change(6);}
void drop(CEquipment* p){n(7);n(id(p,items[0],items[1]));change(7);}
void update(CCombineMenu* p){n(8);n(p==menu);n(menu->m_OriginalItemLocations.size());menu->m_ClickedSlot=91;}
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;cs=&c;cap=&out;unsigned long long mm[(sizeof(CCombineMenu)+23)/8],am[2][(sizeof(CCharacter)+7)/8]={0},im[2][(sizeof(CInventory)+7)/8]={0},em[2][(sizeof(CEquipment)+7)/8]={0},rm[2][(sizeof(CResourceManager)+7)/8]={0},lm[2][8]={0};std::memset(mm,0xa5,sizeof(mm));menu=(CCombineMenu*)mm;new(&menu->m_OriginalItemLocations) Locations;void* itemVT[120]={0};itemVT[0x360/8]=(void*)&drop;void* menuVT[24]={0};menuVT[9]=(void*)&update;*(void***)menu=menuVT;
 for(unsigned i=0;i<2;++i){actors[i]=(CCharacter*)am[i];inventories[i]=(CInventory*)im[i];items[i]=(CEquipment*)em[i];levels[i]=(CLevel*)lm[i];actors[i]->m_pInventory=c.mask&4?inventories[i]:0;actors[i]->m_pResourceManager=c.mask&256?(CResourceManager*)rm[i]:0;((CResourceManager*)rm[i])->m_pLevel=levels[i];*(void***)items[i]=itemVT;}
 menu->m_pCharacter=c.mask&2?actors[0]:0;const int locations[]={-1,0,18,19,2147483647,(-2147483647-1)};if(c.mask&8)menu->m_OriginalItemLocations[items[0]]=std::make_pair(c.mask&512?inventories[1]:(CInventory*)0,(EEQUIP_LOCATIONS)locations[c.location]);menu->m_OriginalItemLocations[items[1]]=std::make_pair(inventories[0],(EEQUIP_LOCATIONS)13);g_bDontTrackItemEquipAndUnEquip=c.mode==2;
 detour::Set d;TL_REDIRECT(d,slotFn,&slot);TL_REDIRECT(d,equipFn,&equip);TL_REDIRECT(d,hasFn,&has);TL_REDIRECT(d,pickFn,&pickup);TL_REDIRECT(d,posFn,&position);TL_REDIRECT(d,addFn,&add);if(d.failed())_exit(60);
 CEquipment* target=c.mask&1?items[0]:0;if(c.mode){if(ours)autotest::invoke(out,&candidateUsed,menu,target);else autotest::invoke(out,&originalUsed,menu,target);}else{if(ours)autotest::invoke(out,&candidateReturn,menu,target);else autotest::invoke(out,&originalReturn,menu,target);}
 n(menu->m_OriginalItemLocations.size());for(unsigned i=0;i<2;++i){Locations::iterator it=menu->m_OriginalItemLocations.find(items[i]);n(it!=menu->m_OriginalItemLocations.end());if(it!=menu->m_OriginalItemLocations.end()){n(id(it->second.first,inventories[0],inventories[1]));n(int(it->second.second));}}n(id(menu->m_pCharacter,actors[0],actors[1]));n(menu->m_ClickedSlot);menu->m_OriginalItemLocations.~Locations();
}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
int run(const tlhybrid_host* host,unsigned mode){autotest::Coverage coverage(mode?"combinemenu_equipment_used":"combinemenu_return_items",(uint64_t)(uintptr_t)(mode?&originalUsed:&originalReturn));for(unsigned mask=0;mask<1024;++mask)for(unsigned location=0;location<6;++location)for(unsigned mutation=0;mutation<8;++mutation){if(!(mask&2)&&(mask&1)&&(mask&8)&&(!(mask&512)||!(mask&128)))continue;Case c={mask,location,mutation,mode};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    return mismatch %u/%u/%u mode %u exits %d/%d\n",mask,location,mutation,mode,u.childStatus,v.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(combinemenu_return_items){return run(host,0);}
TL_TEST(combinemenu_equipment_used){return run(host,1);}
TL_TEST(combinemenu_equipment_used_suppressed){return run(host,2);}
