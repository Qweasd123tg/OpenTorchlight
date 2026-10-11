// Differential inventory fixtures use actual lists, vectors and maps with the
// pinned ABI. Search results, append behavior, mutations and collaborator traces
// are compared with the untouched original. Null cases only enter paths that
// the original supports; effects cover rounding and floating-point edge values.
#include <cstring>
#include <new>
#include <map>
#include <vector>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "TArrayList.h"
TL_ORIGINAL(int,original0,(void*,int),"_ZN10CInventory12getPaneIndexE16EINVENTORY_PANES")
extern "C" int candidate0(void*,int) __asm__("_ZN10CInventory12getPaneIndexE16EINVENTORY_PANES");
TL_ORIGINAL(bool,original1,(void*,unsigned),"_ZN10CInventory16EquipmentsInSlotEj")
extern "C" bool candidate1(void*,unsigned) __asm__("_ZN10CInventory16EquipmentsInSlotEj");
TL_ORIGINAL(int,original2,(void*,void*),"_ZN10CInventory17findEquipmentSlotEP10CEquipment")
extern "C" int candidate2(void*,void*) __asm__("_ZN10CInventory17findEquipmentSlotEP10CEquipment");
TL_ORIGINAL(int,original3,(void*,void*),"_ZN10CInventory29getEquipmentsEquippedLocationEP10CEquipment")
extern "C" int candidate3(void*,void*) __asm__("_ZN10CInventory29getEquipmentsEquippedLocationEP10CEquipment");
TL_ORIGINAL(int,original4,(void*,long long),"_ZN10CInventory23getEquipmentCountOfGuidEx")
extern "C" int candidate4(void*,long long) __asm__("_ZN10CInventory23getEquipmentCountOfGuidEx");
TL_ORIGINAL(void*,original5,(void*,long long),"_ZN10CInventory18getEquipmentOfGuidEx")
extern "C" void* candidate5(void*,long long) __asm__("_ZN10CInventory18getEquipmentOfGuidEx");
TL_ORIGINAL(void,original6,(void*),"_ZN10CInventory34forceRecalculationOfEquipmentStatsEv")
extern "C" void candidate6(void*) __asm__("_ZN10CInventory34forceRecalculationOfEquipmentStatsEv");
TL_ORIGINAL(bool,original7,(void*,void*,bool),"_ZN10CInventory9canPickupEP10CEquipmentb")
extern "C" bool candidate7(void*,void*,bool) __asm__("_ZN10CInventory9canPickupEP10CEquipmentb");
TL_ORIGINAL(float,original8,(void*,int,int),"_ZN10CInventory14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
extern "C" float candidate8(void*,int,int) __asm__("_ZN10CInventory14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES");
TL_ORIGINAL(float,original9,(void*,int,float,const std::wstring*),"_ZN10CInventory14getEffectValueE12EEFFECT_TYPEfRKSbIwSt11char_traitsIwESaIwEE")
extern "C" float candidate9(void*,int,float,const std::wstring*) __asm__("_ZN10CInventory14getEffectValueE12EEFFECT_TYPEfRKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(float,original10,(void*,int,int,int),"_ZN10CInventory31getEffectValueFromEquipmentSlotE12EEFFECT_TYPE16EEQUIP_LOCATIONS13EDAMAGE_TYPES")
extern "C" float candidate10(void*,int,int,int) __asm__("_ZN10CInventory31getEffectValueFromEquipmentSlotE12EEFFECT_TYPE16EEQUIP_LOCATIONS13EDAMAGE_TYPES");
TL_ORIGINAL(float,original11,(void*,int,int,int),"_ZN10CInventory32getEffectValueMinusEquipmentSlotE12EEFFECT_TYPE16EEQUIP_LOCATIONS13EDAMAGE_TYPES")
extern "C" float candidate11(void*,int,int,int) __asm__("_ZN10CInventory32getEffectValueMinusEquipmentSlotE12EEFFECT_TYPE16EEQUIP_LOCATIONS13EDAMAGE_TYPES");
TL_ORIGINAL(float,original12,(void*,int,int),"_ZN10CInventory20calculateEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
extern "C" float candidate12(void*,int,int) __asm__("_ZN10CInventory20calculateEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES");
TL_ORIGINAL(void,original13,(void*),"_ZN10CInventory11identifyAllEv")
extern "C" void candidate13(void*) __asm__("_ZN10CInventory11identifyAllEv");
TL_ORIGINAL(void,original14,(void*),"_ZN10CInventory12destroyIconsEv")
extern "C" void candidate14(void*) __asm__("_ZN10CInventory12destroyIconsEv");
TL_ORIGINAL(unsigned,original15,(void*,long long,void*),"_ZN10CInventory22getEquipmentsOfQuestIDExR10TArrayListIP13CEquipmentRefE")
extern "C" unsigned candidate15(void*,long long,void*) __asm__("_ZN10CInventory22getEquipmentsOfQuestIDExR10TArrayListIP13CEquipmentRefE");
TL_ORIGINAL(unsigned,original16,(void*,long long,void*),"_ZN10CInventory23getEquipmentsOfUnitGuidExR10TArrayListIP13CEquipmentRefE")
extern "C" unsigned candidate16(void*,long long,void*) __asm__("_ZN10CInventory23getEquipmentsOfUnitGuidExR10TArrayListIP13CEquipmentRefE");
TL_ORIGINAL(unsigned,original17,(void*,int,void*),"_ZN10CInventory23getEquipmentsOfUnitTypeEN9UNITTYPES10EUNITTYPESER10TArrayListIP13CEquipmentRefE")
extern "C" unsigned candidate17(void*,int,void*) __asm__("_ZN10CInventory23getEquipmentsOfUnitTypeEN9UNITTYPES10EUNITTYPESER10TArrayListIP13CEquipmentRefE");
TL_ORIGINAL(bool,original18,(void*,void*,void*),"_ZN10CInventory12useEquipmentEP10CEquipmentP10CCharacter")
extern "C" bool candidate18(void*,void*,void*) __asm__("_ZN10CInventory12useEquipmentEP10CEquipmentP10CCharacter");
TL_FUNCTION(target_isa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(target_recalculate,"_ZN14CEffectManager18recalculateEffectsEv")
TL_FUNCTION(target_destroyText,"_ZN5CItem15destroyItemTextEv")
TL_FUNCTION(target_destroyIcon,"_ZN10CEquipment11destroyIconEv")
TL_FUNCTION(target_managerEffect,"_ZN14CEffectManager14getEffectValueE18EEFFECT_ACTIVATION12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(target_managerNamedEffect,"_ZN14CEffectManager14getEffectValueE12EEFFECT_TYPERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_canUse,"_ZN10CInventory15canUseEquipmentEP10CEquipmentP10CCharacter")
TL_FUNCTION(target_removeEquipment,"_ZN10CInventory15removeEquipmentEP10CEquipment")

namespace {
struct Case{unsigned operation,mode,count,slot,seed;int key,damage,slots,stack,maximum;long long guid;float amount;bool flag;};
struct List{void** data;unsigned count,capacity,grow;};
const Case* input;autotest::Capture* capture;
void* inventory;void* equipment[16];void* references[12];void* managers[17];void* owner;void* owner2;
unsigned effectCalls,notifications,removed,deleted;List* equipmentList;
unsigned mutationCalls,effectReceivers[8],listenerReceivers[8];
void* listenerObjects[3];void** changedSockets;void** changedListeners;
List* firstSockets;List* liveListeners;
void number(unsigned n){capture->add(&n,4);}
unsigned identity(void*p){if(!p)return 0;for(unsigned i=0;i<3;++i)if(p==listenerObjects[i])return 70+i;if(p==inventory)return 1;if(p==owner)return 2;if(p==owner2)return 3;
 for(unsigned i=0;i<16;++i)if(p==equipment[i])return 10+i;
 for(unsigned i=0;i<12;++i)if(p==references[i])return 30+i;
 for(unsigned i=0;i<17;++i)if(p==managers[i])return 50+i;return 99;}
void event(unsigned code,void*p){number(code);number(identity(p));}
void pointerAt(void*p,unsigned at,void*v){std::memcpy(static_cast<char*>(p)+at,&v,8);}
void integerAt(void*p,unsigned at,int v){std::memcpy(static_cast<char*>(p)+at,&v,4);}
void wideAt(void*p,unsigned at,long long v){std::memcpy(static_cast<char*>(p)+at,&v,8);}
float value(unsigned index){
 if(input->mode==17){if(index==10||index==22||index==1||index==2)return 0.25f;if(index==23||index==24)return -0.25f;return 0.0f;}
 if(input->mode==18){if(index==10)return -1.25f;if(index==22||index==1||index==2)return -0.25f;if(index==23)return 0.25f;if(index==24)return 1.25f;return 0.0f;}
 const unsigned bits[]={0,0x80000000u,0x3eaaaaabu,0xbeaaaaabu,0x3f800000u,0xbfa00000u,0x7f800000u,0xff800000u,0x7fc00011u,0x7fc00022u};float f;unsigned x=bits[(input->seed+index)%10];std::memcpy(&f,&x,4);return f;}
bool isa(void*p,int type){event(1,p);capture->add(&type,4);return input->mode!=3&&((identity(p)+static_cast<unsigned>(type)+input->seed)%3!=0);}
void recalculate(void*p){event(2,p);integerAt(p,0x18,71);if(input->mode==7)equipmentList->count=0;}
void destroyText(void*p){event(3,p);integerAt(p,0x6f0,81);if(input->mode==7)integerAt(inventory,0x28,0);}
void destroyIcon(void*p){event(4,p);integerAt(p,0x6f0,91);if(input->mode==7)equipmentList->count=0;}
// Modes 9-12 alter the socket list from the equipment or first socket call.
void mutateSockets(void*p){
 if((input->mode<9||input->mode>12)&&input->mode!=17&&input->mode!=18)return;
 if(effectCalls<=8)effectReceivers[effectCalls-1]=identity(p);
 if(input->mode==17||input->mode==18)return;
 if(input->mode==9&&effectCalls==1){firstSockets->count=0;++mutationCalls;}
 if(effectCalls==2){
  if(input->mode==10){firstSockets->count=1;++mutationCalls;}
  if(input->mode==11){firstSockets->capacity=1;++mutationCalls;}
  if(input->mode==12){firstSockets->data=changedSockets;++mutationCalls;}
 }
}
float effect(void*p,int activation,int type,float amount,int damage){event(5,p);capture->add(&activation,4);capture->add(&type,4);capture->add(&amount,4);capture->add(&damage,4);++effectCalls;mutateSockets(p);return value(identity(p));}
float namedEffect(void*p,int type,float amount,const std::wstring&name){event(6,p);capture->add(&type,4);capture->add(&amount,4);capture->addText(name);++effectCalls;mutateSockets(p);return value(identity(p));}
float managerEffect(void*p,int activation,int type,int damage){event(7,p);capture->add(&activation,4);capture->add(&type,4);capture->add(&damage,4);return value(1);}
float managerNamedEffect(void*p,int type,const std::wstring&name){event(8,p);capture->add(&type,4);capture->addText(name);return value(2);}
bool canPickup(void*p,void*character){event(9,p);number(identity(character));return input->mode!=2;}
bool canUse(void*p,void*item,void*target){event(10,p);number(identity(item));number(identity(target));return input->mode!=3;}
void use(void*p,void*character,void*target){event(11,p);number(identity(character));number(identity(target));integerAt(p,0x238,input->stack);}
void used(void*p,void*item){event(12,p);number(identity(item));++notifications;
 if(input->mode>=13&&input->mode<=16){
  if(notifications<=8)listenerReceivers[notifications-1]=identity(p);
  if(notifications==1){++mutationCalls;
   if(input->mode==13){liveListeners->count=1;integerAt(item,0x238,0);}
   if(input->mode==14){liveListeners->count=3;integerAt(item,0x238,5);}
   if(input->mode==15)liveListeners->capacity=1;
   if(input->mode==16)liveListeners->data=changedListeners;
  }
 }
}
long long removeEquipment(void*p,void*item){event(13,p);number(identity(item));++removed;return 0x123456789LL;}
void destroy(void*p){event(14,p);++deleted;integerAt(p,0x6f0,101);}
void side(Case&c,bool ours,autotest::Capture&out){
 input=&c;capture=&out;effectCalls=notifications=removed=deleted=mutationCalls=0;
 std::memset(effectReceivers,0,sizeof(effectReceivers));std::memset(listenerReceivers,0,sizeof(listenerReceivers));
 unsigned long long inventoryBytes[0x218/8]={0},equipmentBytes[16][0x700/8]={{0}},referenceBytes[12][5]={{0}},managerBytes[17][8]={{0}},ownerBytes[2][8]={{0}};
 void* refPointers[12];void* sockets[3];void* listeners[3];void* replacementSockets[3];void* replacementListeners[3];unsigned long long listenerBytes[3][4]={{0}};
 void* vtable[112]={0};void* listenerTable[8]={0};
 vtable[0x248/8]=reinterpret_cast<void*>(&effect);vtable[0x258/8]=reinterpret_cast<void*>(&namedEffect);
 vtable[0x300/8]=reinterpret_cast<void*>(&canPickup);vtable[0x330/8]=reinterpret_cast<void*>(&use);vtable[1]=reinterpret_cast<void*>(&destroy);
 listenerTable[6]=reinterpret_cast<void*>(&used);
 inventory=inventoryBytes;owner=ownerBytes[0];owner2=ownerBytes[1];
 for(unsigned i=0;i<17;++i)managers[i]=managerBytes[i];
 for(unsigned i=0;i<16;++i){equipment[i]=equipmentBytes[i];pointerAt(equipment[i],0,vtable);pointerAt(equipment[i],0x1b8,c.mode==4&&i%2?NULL:managers[i]);
  wideAt(equipment[i],0x1a0,(i+c.seed)%3?c.guid:c.guid+1);wideAt(equipment[i],0x170,(i+c.seed)%2?c.guid:c.guid-1);
  wideAt(equipment[i],0x18,c.mode==5?c.guid:c.mode==6?c.guid+1:-1LL);
  integerAt(equipment[i],0x238,c.stack+static_cast<int>(i%3));integerAt(equipment[i],0x23c,c.maximum-(i%3==0?1:0));
 }
 wideAt(owner,0x10,c.guid);pointerAt(inventory,0x20,owner);pointerAt(inventory,0x18,managers[16]);integerAt(inventory,0x28,c.slots);
 for(unsigned i=0;i<12;++i){references[i]=referenceBytes[i];refPointers[i]=references[i];pointerAt(references[i],0x10,equipment[i]);
  integerAt(references[i],0x18,static_cast<int>((i*3+c.seed)%20));
  const bool requireEquipment=c.operation==4||c.operation==5||(c.operation>=15&&c.operation<=17);
  const bool requireReference=requireEquipment||c.operation==6||(c.operation==1&&c.slot>=12);
  if(c.mode==1&&!requireEquipment&&i%3==0)pointerAt(references[i],0x10,NULL);
  if(c.mode==2&&!requireReference&&i%3==1)refPointers[i]=NULL;
 }
 if(c.count>2&&c.mode==8){integerAt(references[0],0x18,0);integerAt(references[1],0x18,0);pointerAt(references[0],0x10,NULL);
  if(c.operation==4||c.operation==5||c.operation>=15)pointerAt(references[0],0x10,equipment[0]);}
 List list={refPointers,c.count,c.mode==6?2u:12u,2};std::memcpy(static_cast<char*>(inventory)+0x30,&list,sizeof(list));equipmentList=reinterpret_cast<List*>(static_cast<char*>(inventory)+0x30);
 for(unsigned i=0;i<3;++i){sockets[i]=equipment[12+i];listeners[i]=listenerBytes[i];listenerObjects[i]=listeners[i];pointerAt(listeners[i],0,listenerTable);}
 List socketList={sockets,c.mode==0?0u:3u,c.mode==6?1u:3u,2};
 for(unsigned i=0;i<12;++i)std::memcpy(static_cast<char*>(equipment[i])+0x3e8,&socketList,sizeof(socketList));
 firstSockets=reinterpret_cast<List*>(static_cast<char*>(equipment[0])+0x3e8);
 replacementSockets[0]=equipment[14];replacementSockets[1]=equipment[14];replacementSockets[2]=equipment[13];changedSockets=replacementSockets;
 replacementListeners[0]=listeners[2];replacementListeners[1]=listeners[2];replacementListeners[2]=listeners[1];changedListeners=replacementListeners;
 List listenerList={listeners,c.mode==0?0u:c.mode==14?1u:3u,c.mode==6?1u:3u,2};std::memcpy(static_cast<char*>(inventory)+0x48,&listenerList,sizeof(listenerList));
 liveListeners=reinterpret_cast<List*>(static_cast<char*>(inventory)+0x48);
 typedef std::vector<int> Vector;Vector* panes=::new(static_cast<char*>(inventory)+0x60)Vector;Vector* starts=::new(static_cast<char*>(inventory)+0x78)Vector;
 unsigned paneCount=c.operation==7?1+c.seed%5:c.seed%6;
 for(unsigned i=0;i<paneCount;++i){panes->push_back((i+c.seed)%5);starts->push_back(i*3);}
 typedef std::map<int,float> Map;Map* maps=reinterpret_cast<Map*>(static_cast<char*>(inventory)+0x90);
 for(unsigned i=0;i<8;++i){::new(&maps[i])Map;for(int j=-3;j<4;++j)if(c.mode!=0)(maps[i])[j*3]=value(i+j+4);}
 TArrayList<void*> output(1+c.seed%3);for(unsigned i=0;i<c.seed%4;++i)output.add(references[11-i]);
 std::wstring name=c.mode==8?std::wstring(L"a\0b",3):c.mode==7?L"":L"stat Ω";
 void* target=c.mode==0?NULL:equipment[c.seed%12];
 detour::Set patches;
 TL_REDIRECT(patches,target_isa,&isa);
 TL_REDIRECT(patches,target_recalculate,&recalculate);
 TL_REDIRECT(patches,target_destroyText,&destroyText);
 TL_REDIRECT(patches,target_destroyIcon,&destroyIcon);
 TL_REDIRECT(patches,target_managerEffect,&managerEffect);
 TL_REDIRECT(patches,target_managerNamedEffect,&managerNamedEffect);
 TL_REDIRECT(patches,target_canUse,&canUse);
 TL_REDIRECT(patches,target_removeEquipment,&removeEquipment);
 if(patches.failed())_exit(41);
 switch(c.operation){
 case 0:autotest::invoke(out,ours?&candidate0:&original0,inventory,c.key);break;
 case 1:autotest::invoke(out,ours?&candidate1:&original1,inventory,c.slot);break;
 case 2:autotest::invoke(out,ours?&candidate2:&original2,inventory,target);break;
 case 3:autotest::invoke(out,ours?&candidate3:&original3,inventory,target);break;
 case 4:autotest::invoke(out,ours?&candidate4:&original4,inventory,c.guid);break;
 case 5:{void*(*fn)(void*,long long)=ours?&candidate5:&original5;if(!autotest::beginInvocation(out,fn))return;void* result=fn(inventory,c.guid);out.callCompleted=1;number(identity(result));break;}
 case 6:autotest::invoke(out,ours?&candidate6:&original6,inventory);break;
 case 7:autotest::invoke(out,ours?&candidate7:&original7,inventory,target,c.flag);break;
 case 8:autotest::invoke(out,ours?&candidate8:&original8,inventory,c.key,c.damage);break;
 case 9:{
  if(c.mode==17||c.mode==18){float(*fn)(void*,int,float,const std::wstring*)=ours?&candidate9:&original9;if(!autotest::beginInvocation(out,fn))return;
   float result=fn(inventory,c.key,c.amount,&name);out.callCompleted=1;out.add(&result,4);
   if(result!=(c.operation==10||c.mode==18?2.0f:3.0f))out.issue=autotest::Capture::InvalidReport;
  }else autotest::invoke(out,ours?&candidate9:&original9,inventory,c.key,c.amount,&name);break;}
 case 10:{
  if(c.mode==17||c.mode==18){float(*fn)(void*,int,int,int)=ours?&candidate10:&original10;if(!autotest::beginInvocation(out,fn))return;
   float result=fn(inventory,c.key,static_cast<int>(c.slot),c.damage);out.callCompleted=1;out.add(&result,4);
   if(result!=(c.operation==10||c.mode==18?2.0f:3.0f))out.issue=autotest::Capture::InvalidReport;
  }else autotest::invoke(out,ours?&candidate10:&original10,inventory,c.key,static_cast<int>(c.slot),c.damage);break;}
 case 11:autotest::invoke(out,ours?&candidate11:&original11,inventory,c.key,static_cast<int>(c.slot),c.damage);break;
 case 12:{
  if(c.mode==17||c.mode==18){float(*fn)(void*,int,int)=ours?&candidate12:&original12;if(!autotest::beginInvocation(out,fn))return;
   float result=fn(inventory,c.key,c.damage);out.callCompleted=1;out.add(&result,4);
   if(result!=(c.operation==10||c.mode==18?2.0f:3.0f))out.issue=autotest::Capture::InvalidReport;
  }else autotest::invoke(out,ours?&candidate12:&original12,inventory,c.key,c.damage);break;}
 case 13:autotest::invoke(out,ours?&candidate13:&original13,inventory);break;
 case 14:autotest::invoke(out,ours?&candidate14:&original14,inventory);break;
 case 15:autotest::invoke(out,ours?&candidate15:&original15,inventory,c.guid,static_cast<void*>(&output));break;
 case 16:autotest::invoke(out,ours?&candidate16:&original16,inventory,c.guid,static_cast<void*>(&output));break;
 case 17:autotest::invoke(out,ours?&candidate17:&original17,inventory,c.key,static_cast<void*>(&output));break;
 case 18:autotest::invoke(out,ours?&candidate18:&original18,inventory,target,c.flag?NULL:owner2);break;

 }
 // Require positive mutation witnesses separately on each side. Coverage::observe
 // rejects a nonzero child exit, even if both sides violate the same assertion.
 if(c.mode>=9&&c.mode<=12){
  const unsigned expected=c.mode==9?1u:c.mode==10?2u:4u;
  if(mutationCalls!=1||effectCalls!=expected||effectReceivers[0]!=10)_exit(42);
  if(expected>1&&effectReceivers[1]!=22)_exit(42);
  if(c.mode==11&&(effectReceivers[2]!=22||effectReceivers[3]!=22||firstSockets->capacity!=1))_exit(42);
  if(c.mode==12&&(effectReceivers[2]!=24||effectReceivers[3]!=23||firstSockets->data!=changedSockets))_exit(42);
  if(c.mode==9&&firstSockets->count!=0)_exit(42);
  if(c.mode==10&&firstSockets->count!=1)_exit(42);
 }
 if(c.mode>=13&&c.mode<=16){
  const unsigned expected=c.mode==13?1u:3u;
  const unsigned destruction=(c.mode==13||c.mode==15)?1u:0u;
  if(mutationCalls!=1||notifications!=expected||removed!=destruction||deleted!=destruction||listenerReceivers[0]!=70)_exit(42);
  if(c.mode==14&&(listenerReceivers[1]!=71||listenerReceivers[2]!=72||liveListeners->count!=3))_exit(42);
  if(c.mode==15&&(listenerReceivers[1]!=70||listenerReceivers[2]!=70||liveListeners->capacity!=1))_exit(42);
  if(c.mode==16&&(listenerReceivers[1]!=72||listenerReceivers[2]!=71||liveListeners->data!=changedListeners))_exit(42);
  if(c.mode==13&&liveListeners->count!=1)_exit(42);
 }
 number(mutationCalls);out.add(effectReceivers,sizeof(effectReceivers));out.add(listenerReceivers,sizeof(listenerReceivers));
 if(c.mode==17||c.mode==18){
  if(effectCalls!=4||mutationCalls!=0||effectReceivers[0]!=10||effectReceivers[1]!=22||
     effectReceivers[2]!=23||effectReceivers[3]!=24||firstSockets->count!=3||firstSockets->capacity!=3)_exit(42);
 }
 number(effectCalls);number(notifications);number(removed);number(deleted);
 out.add(equipmentBytes,sizeof(equipmentBytes));out.add(referenceBytes,sizeof(referenceBytes));out.add(managerBytes,sizeof(managerBytes));
 out.add(static_cast<char*>(inventory)+0x10,0x50);number(output.size());
 for(unsigned i=0;i<output.size();++i)number(identity(output[i]));
 for(unsigned i=0;i<8;++i){number(maps[i].size());for(Map::iterator j=maps[i].begin();j!=maps[i].end();++j){out.add(&j->first,4);out.add(&j->second,4);}maps[i].~Map();}
 starts->~Vector();panes->~Vector();patches.restore();
}
void original(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(inventory_mass_differential){
 const uint64_t addresses[]={
(uint64_t)(uintptr_t)&original0,(uint64_t)(uintptr_t)&original1,(uint64_t)(uintptr_t)&original2,(uint64_t)(uintptr_t)&original3,(uint64_t)(uintptr_t)&original4,(uint64_t)(uintptr_t)&original5,(uint64_t)(uintptr_t)&original6,(uint64_t)(uintptr_t)&original7,(uint64_t)(uintptr_t)&original8,(uint64_t)(uintptr_t)&original9,(uint64_t)(uintptr_t)&original10,(uint64_t)(uintptr_t)&original11,(uint64_t)(uintptr_t)&original12,(uint64_t)(uintptr_t)&original13,(uint64_t)(uintptr_t)&original14,(uint64_t)(uintptr_t)&original15,(uint64_t)(uintptr_t)&original16,(uint64_t)(uintptr_t)&original17,(uint64_t)(uintptr_t)&original18};

 const unsigned slots[]={0,1,7,11,12,13,18,19,0xffffffffu};
 const int limits[]={-1,0,1,11,12,19,24};const int stacks[]={-3,0,1,2,17};
 const long long ids[]={0,-1,1,0x123456789abcdefLL};
 for(unsigned operation=0;operation<19;++operation){autotest::Coverage coverage("inventory_mass_differential",addresses[operation]);
  for(unsigned n=0;n<504;++n){Case c={operation,n%9,(n/9)%13,slots[(n/9)%9],n/9,static_cast<int>((n/27)%23)-10,static_cast<int>((n/63)%8),limits[(n/18)%7],stacks[(n/18)%5],stacks[(n/63)%5],ids[(n/18)%4],(n%2?0.125f:-7.75f),((n/9)%2)!=0};
   autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int result=coverage.observe(host,a,b);
   if(result){host->log("    inventory operation %u case %u pair %d status %d/%d bytes %lu/%lu\n",operation,n,result,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}
  }
  // Single live item in slot zero makes callback sequences unambiguous.
  const unsigned firstMode=operation==18?13u:9u;
  const unsigned lastMode=operation==18?16u:12u;
  if(operation==9||operation==10||operation==12||operation==18){
   for(unsigned mode=firstMode;mode<=lastMode;++mode){
    Case c={operation,mode,1,0,0,0,0,12,mode==13?2:mode==16?1:0,2,1,0.125f,false};
    autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
    int result=coverage.observe(host,a,b);
    if(result){host->log("    inventory mutation operation %u mode %u pair %d status %d/%d\n",operation,mode,result,a.status,b.status);coverage.report(host);return 1;}
   }
  }
  if(operation==9||operation==10||operation==12){
   for(unsigned mode=17;mode<=18;++mode){
    Case c={operation,mode,1,0,0,0,0,12,1,2,1,0.125f,false};
    autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
    int result=coverage.observe(host,a,b);
    if(result){host->log("    inventory finite rounding operation %u mode %u pair %d status %d/%d\n",operation,mode,result,a.status,b.status);coverage.report(host);return 1;}
   }
  }
  coverage.report(host);
  const unsigned expected=operation==18?508u:(operation==9||operation==10||operation==12)?510u:504u;
  if(coverage.completed!=expected||coverage.different||coverage.missing)return 1;
 }return 0;
}
