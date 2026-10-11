#include <cstring>
#include <vector>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,original0,(void*,void*),"_ZN10CInventory11addListenerEP18iInventoryListener")
extern "C" void candidate0(void*,void*) __asm__("_ZN10CInventory11addListenerEP18iInventoryListener");
TL_ORIGINAL(void,original1,(void*),"_ZN10CInventory15verifyEquipmentEv")
extern "C" void candidate1(void*) __asm__("_ZN10CInventory15verifyEquipmentEv");
TL_ORIGINAL(bool,original2,(void*,long long,unsigned,bool),"_ZN10CInventory21removeEquipmentByGuidExjb")
extern "C" bool candidate2(void*,long long,unsigned,bool) __asm__("_ZN10CInventory21removeEquipmentByGuidExjb");
TL_ORIGINAL(long long,original3,(void*,void*),"_ZN10CInventory15removeEquipmentEP10CEquipment")
extern "C" long long candidate3(void*,void*) __asm__("_ZN10CInventory15removeEquipmentEP10CEquipment");
TL_ORIGINAL(void,original4,(void*),"_ZN10CInventory13freeInventoryEv")
extern "C" void candidate4(void*) __asm__("_ZN10CInventory13freeInventoryEv");
TL_ORIGINAL(int,original5,(void*,void*),"_ZN10CInventory12findFreeSlotEP10CEquipment")
extern "C" int candidate5(void*,void*) __asm__("_ZN10CInventory12findFreeSlotEP10CEquipment");
TL_FUNCTION(target_effects,"_ZN10CInventory21calculateEffectValuesEv")
TL_FUNCTION(target_bonuses,"_ZN10CInventory13updateBonusesEv")
TL_FUNCTION(target_canEquip,"_ZN10CInventory8canEquipEP10CEquipmentb")
TL_FUNCTION(target_unequip,"_ZN10CInventory16unequipEquipmentEP10CEquipment")
TL_FUNCTION(target_remove,"_ZN10CInventory15removeEquipmentEP10CEquipment")
TL_FUNCTION(target_verify,"_ZN10CInventory15verifyEquipmentEv")
TL_FUNCTION(target_notify,"_ZN6CLevel16notifyOfDeletionEP5CItem")
TL_FUNCTION(target_requiredPane,"_ZN10CInventory15getRequiredPaneEP10CEquipment")
TL_FUNCTION(target_paneIndex,"_ZN10CInventory12getPaneIndexE16EINVENTORY_PANES")

namespace {
struct List{void**data;unsigned count,capacity,grow,padding;};struct Case{unsigned op,seed,mode;};Case*input;autotest::Capture*output;void*active;void*refs[8];void*items[9];void*listeners[9];List*equipment;List*listenerList;unsigned calls;
void num(unsigned v){output->add(&v,4);}void ptr(void*p){output->add(&p,8);}void event(unsigned id,void*p){num(id);ptr(p);}void put(void*p,unsigned o,void*v){std::memcpy(static_cast<char*>(p)+o,&v,8);}void integer(void*p,unsigned o,unsigned v){std::memcpy(static_cast<char*>(p)+o,&v,4);}void*get(void*p,unsigned o){void*v;std::memcpy(&v,static_cast<char*>(p)+o,8);return v;}unsigned value(void*p,unsigned o){unsigned v;std::memcpy(&v,static_cast<char*>(p)+o,4);return v;}
void observedState(){num(equipment->count);num(equipment->capacity);if(equipment->data)for(unsigned i=0;i<8;++i)ptr(equipment->data[i]);for(unsigned i=0;i<8;++i)output->add(refs[i],40);}
void effects(void*p){event(1,p);observedState();++calls;}
void bonuses(void*p){event(2,p);integer(p,0x10,0x12340000+calls);}
bool canEquip(void*p,void*item,bool force){event(3,p);ptr(item);num(force);return input->mode==8?false:((calls+input->seed)%3)!=0;}
bool unequip(void*p,void*item){event(4,p);ptr(item);if(input->mode!=8){for(unsigned i=0;i<8;++i)if(get(refs[i],0x10)==item)integer(refs[i],0x18,19);}return input->seed&1;}
long long remove(void*p,void*item){event(5,p);ptr(item);observedState();for(unsigned i=0;i<equipment->count;++i){void*ref=equipment->data[i];if(get(ref,0x10)==item){--equipment->count;equipment->data[i]=equipment->data[equipment->count];break;}}return 1;}
void verify(void*p){event(6,p);observedState();}
void notify(void*p,void*item){event(7,p);ptr(item);observedState();if(input->mode==7)for(unsigned i=0;i<equipment->count;++i)if(equipment->data[i]&&get(equipment->data[i],0x10)==item)equipment->data[i]=NULL;}
int requiredPane(void*p,void*item){event(8,p);ptr(item);return input->seed%3;}
int paneIndex(void*p,int pane){event(9,p);num(pane);return input->seed%3;}
void deleteRef(void*p){event(10,p);output->add(p,40);observedState();if(input->mode==5&&equipment->count>1)--equipment->count;}
void deleteItem(void*p){event(11,p);output->add(static_cast<char*>(p)+0x238,8);observedState();}
void decrement(void*p,int n){event(12,p);num(n);integer(p,0x238,value(p,0x238)+unsigned(n));}
void removedFromInventory(void*p,void*inventory,void*owner){event(13,p);ptr(inventory);ptr(owner);observedState();}
void unequipped(void*p,void*inventory,void*owner,int slot){event(14,p);ptr(inventory);ptr(owner);num(slot);observedState();if(input->mode==6&&listenerList->count>1)--listenerList->count;}
void dropped(void*p,void*item){event(15,p);ptr(item);observedState();if(input->mode==7&&listenerList->count>1)--listenerList->count;}
void listenerUnequipped(void*p,void*item){event(16,p);ptr(item);observedState();}
void destroyed(void*p){event(17,p);observedState();if(input->mode==6&&listenerList->count>1)--listenerList->count;}
void side(Case&c,bool ours,autotest::Capture&out){input=&c;output=&out;calls=0;unsigned long long self[0x210/8]={0},ref[8][5]={{0}},item[9][128]={{0}},listener[9][4]={{0}},resource[8][8]={{0}},level[8]={0},owner[8]={0};active=self;
 void*refTable[2]={NULL,reinterpret_cast<void*>(&deleteRef)};void*itemTable[120]={0};itemTable[1]=reinterpret_cast<void*>(&deleteItem);itemTable[0x318/8]=reinterpret_cast<void*>(&removedFromInventory);itemTable[0x328/8]=reinterpret_cast<void*>(&unequipped);itemTable[0x338/8]=reinterpret_cast<void*>(&decrement);
 void*listenerTable[8]={0};listenerTable[3]=reinterpret_cast<void*>(&dropped);listenerTable[5]=reinterpret_cast<void*>(&listenerUnequipped);listenerTable[7]=reinterpret_cast<void*>(&destroyed);
 for(unsigned i=0;i<9;++i){items[i]=item[i];listeners[i]=listener[i];put(items[i],0,itemTable);put(listeners[i],0,listenerTable);long long id=static_cast<long long>((c.seed/10+i)%3)*0x123456789LL;std::memcpy(static_cast<char*>(items[i])+0x1a0,&id,8);integer(items[i],0x238,(c.seed/30+i)%9);const int maximum[]={-1,0,1,2,8,20};integer(items[i],0x23c,maximum[(c.seed/10+i)%6]);if(i<8){refs[i]=ref[i];put(refs[i],0,refTable);put(refs[i],0x10,items[i]);integer(refs[i],0x18,(c.seed/10+i*3)%25);static_cast<char*>(refs[i])[0x21]=(c.seed+i)&1;put(items[i],0x68,c.mode==2?NULL:resource[i]);put(resource[i],0x18,c.mode==3?NULL:level);}}
 equipment=reinterpret_cast<List*>(reinterpret_cast<char*>(self)+0x30);listenerList=reinterpret_cast<List*>(reinterpret_cast<char*>(self)+0x48);
 equipment->count=(c.seed/10)%8;equipment->capacity=c.mode==9?2:8;equipment->grow=2;equipment->data=new void*[8];listenerList->count=(c.seed/20)%5;listenerList->capacity=8;listenerList->grow=1;listenerList->data=new void*[8];
 for(unsigned i=0;i<8;++i){equipment->data[i]=refs[i];listenerList->data[i]=listeners[i];if((c.op==1||c.op==4||c.op==5)&&c.mode==4){if(i%3==0)equipment->data[i]=NULL;else if(i%3==1)put(refs[i],0x10,NULL);}}
 if(c.op==0){listenerList->capacity=(c.seed/10)%3==0?listenerList->count:8;if(c.seed%10==9){delete[]listenerList->data;listenerList->data=NULL;listenerList->count=listenerList->capacity=0;}}
 if(c.op==2)equipment->capacity=8;
 put(self,0x20,c.mode==0?NULL:owner);reinterpret_cast<char*>(self)[0x15]=c.mode==1;reinterpret_cast<char*>(self)[0x14]=(c.seed/10)&1;integer(self,0x28,33);
 std::vector<unsigned>*panes=new(reinterpret_cast<char*>(self)+0x60)std::vector<unsigned>;std::vector<unsigned>*starts=new(reinterpret_cast<char*>(self)+0x78)std::vector<unsigned>;panes->push_back(0);panes->push_back(1);panes->push_back(2);starts->push_back(19);starts->push_back(25);starts->push_back(29);
 if(c.mode==8)(*starts)[c.seed%3]=40;
 detour::Set patches;
 TL_REDIRECT(patches,target_effects,&effects);
 TL_REDIRECT(patches,target_bonuses,&bonuses);
 TL_REDIRECT(patches,target_canEquip,&canEquip);
 TL_REDIRECT(patches,target_unequip,&unequip);
 if(c.op==2) TL_REDIRECT(patches,target_remove,&remove);
 if(c.op!=1) TL_REDIRECT(patches,target_verify,&verify);
 TL_REDIRECT(patches,target_notify,&notify);
 TL_REDIRECT(patches,target_requiredPane,&requiredPane);
 TL_REDIRECT(patches,target_paneIndex,&paneIndex);

 if(patches.failed())_exit(41);const unsigned counts[]={0,1,3,20,0xffffffffu};
 switch(c.op){case 0:autotest::invoke(out,ours?candidate0:original0,active,c.mode==0?NULL:listeners[(c.seed/10)%9]);break;case 1:autotest::invoke(out,ours?candidate1:original1,active);break;
 case 2:autotest::invoke(out,ours?candidate2:original2,active,static_cast<long long>((c.seed/10)%4)*0x123456789LL,counts[(c.seed/20)%5],(c.seed/10&1)!=0);break;
 case 3:autotest::invoke(out,ours?candidate3:original3,active,items[(c.seed/10)%9]);break;case 4:autotest::invoke(out,ours?candidate4:original4,active);break;case 5:autotest::invoke(out,ours?candidate5:original5,active,items[8]);break;}
 num(calls);num(equipment->count);num(equipment->capacity);num(equipment->grow);num(equipment->data!=NULL);if(equipment->data)out.add(equipment->data,64);
 num(listenerList->count);num(listenerList->capacity);num(listenerList->grow);num(listenerList->data!=NULL);if(listenerList->data){unsigned initialized=c.op==0?listenerList->count:8;out.add(listenerList->data,8*initialized);}
 out.add(ref,sizeof(ref));out.add(item,sizeof(item));out.add(listener,sizeof(listener));out.add(resource,sizeof(resource));out.add(level,sizeof(level));out.add(owner,sizeof(owner));put(self,0x30,NULL);put(self,0x48,NULL);out.add(self,sizeof(self));patches.restore();
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
int run(const tlhybrid_host*host,unsigned op,const char*name){const uint64_t addresses[]={(uint64_t)(uintptr_t)original0,(uint64_t)(uintptr_t)original1,(uint64_t)(uintptr_t)original2,(uint64_t)(uintptr_t)original3,(uint64_t)(uintptr_t)original4,(uint64_t)(uintptr_t)original5};autotest::Coverage coverage(name,addresses[op]);for(unsigned n=0;n<360;++n){Case c={op,n,n%10};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){host->log("    inventory operation %u/%u status %d/%d bytes %lu/%lu\n",op,n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);unsigned end=a.capture.length<b.capture.length?a.capture.length:b.capture.length;for(unsigned i=0;i<end;++i)if(a.capture.data[i]!=b.capture.data[i]){host->log("    first byte %u %u/%u\n",i,a.capture.data[i],b.capture.data[i]);break;}coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(inventory_next_listener){return run(host,0,"inventory_next_listener");}
TL_TEST(inventory_next_verify){return run(host,1,"inventory_next_verify");}
TL_TEST(inventory_next_remove_guid){return run(host,2,"inventory_next_remove_guid");}
TL_TEST(inventory_next_remove){return run(host,3,"inventory_next_remove");}
TL_TEST(inventory_next_free){return run(host,4,"inventory_next_free");}
TL_TEST(inventory_next_free_slot){return run(host,5,"inventory_next_free_slot");}
