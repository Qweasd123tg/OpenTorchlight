#include "SmallMassCompare.h"
TL_ORIGINAL(bool, original0, (void*,long long,bool,bool,int), "_ZN7CPlayer44removeItemFromInventoryOrPetsInventoryByGuidExbbN9UNITTYPES10EUNITTYPESE")
extern "C" bool candidate0(void*,long long,bool,bool,int) __asm__("_ZN7CPlayer44removeItemFromInventoryOrPetsInventoryByGuidExbbN9UNITTYPES10EUNITTYPESE");
TL_ORIGINAL(bool, original1, (void*,long long,long long,bool,bool,int), "_ZN7CPlayer49removeQuestItemFromInventoryOrPetsInventoryByGuidExxbbN9UNITTYPES10EUNITTYPESE")
extern "C" bool candidate1(void*,long long,long long,bool,bool,int) __asm__("_ZN7CPlayer49removeQuestItemFromInventoryOrPetsInventoryByGuidExxbbN9UNITTYPES10EUNITTYPESE");
TL_ORIGINAL(void, original2, (void*,bool), "_ZL14SetPetsEnabledP10CCharacterb")
extern "C" void candidate2(void*,bool) __asm__("__tlhybrid_local_186__ZL14SetPetsEnabledP10CCharacterb");
#include "TArrayList.h"
TL_FUNCTION(dep_questItems, "_ZN10CInventory22getEquipmentsOfQuestIDExR10TArrayListIP13CEquipmentRefE")
TL_FUNCTION(dep_unitItems, "_ZN10CInventory23getEquipmentsOfUnitGuidExR10TArrayListIP13CEquipmentRefE")
TL_FUNCTION(dep_isa, "_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(dep_remove, "_ZN10CInventory15removeEquipmentEP10CEquipment")

namespace {
using namespace smallmass;
void* self;void* inventories[2];void* refs[2][6];void* items[2][6];
unsigned collect(void* p,long long guid,TArrayList<void*>& out,unsigned kind){event(kind,p);output->add(&guid,8);unsigned which=p==inventories[0]?0:1;unsigned count=(input->index+which)%7;for(unsigned i=0;i<count;++i)out.add(refs[which][i]);return count;}
unsigned questItems(void* p,long long guid,TArrayList<void*>& out){return collect(p,guid,out,1);}
unsigned unitItems(void* p,long long guid,TArrayList<void*>& out){return collect(p,guid,out,2);}
bool isa(void* p,int type){event(3,p);number(type);return (field<unsigned>(p,0x170)+input->index)%4!=0;}
long long remove(void* p,void* item){event(4,p);pointer(item);field<bool>(item,0x240)=true;return 123;}
void increment(void* p,int count){event(5,p);number(count);field<int>(p,0x238)+=count;}
void destroy(void* p){event(6,p);field<bool>(p,0x241)=true;}
void enabled(void* p,bool value){event(7,p);number(value);field<bool>(p,0x82)=value;}
void execute(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;self=object(0xa70);inventories[0]=object(0x200);inventories[1]=object(0x200);
 void** table=static_cast<void**>(object(0x360));table[0x338/8]=reinterpret_cast<void*>(&increment);table[1]=reinterpret_cast<void*>(&destroy);table[0x40/8]=reinterpret_cast<void*>(&enabled);
 void* characters[8];characters[0]=self;
 for(unsigned j=0;j<8;++j){if(j)characters[j]=object(0x778);field<void*>(characters[j],0)=table;}
 for(unsigned j=0;j<8;++j){
  void** pets=static_cast<void**>(object(4*8));unsigned count=0;
  if(j==0){for(unsigned i=0;i<c.index%4;++i)pets[count++]=characters[1+i];}
  if(j>0&&j<4&&c.index%3!=0)pets[count++]=characters[4+j];
  field<void*>(characters[j],0x648)=pets;field<void*>(characters[j],0x650)=pets+count;field<void*>(characters[j],0x658)=pets+4;
 }
 field<void*>(self,0x490)=c.index%11?inventories[0]:0;field<void*>(characters[1],0x490)=c.index%13?inventories[1]:0;
 for(unsigned j=0;j<2;++j)for(unsigned i=0;i<6;++i){
  items[j][i]=object(0x480);refs[j][i]=object(0x28);field<void*>(items[j][i],0)=table;field<void*>(refs[j][i],0x10)=items[j][i];field<unsigned>(items[j][i],0x170)=i+3*j;
  field<long long>(items[j][i],0x1a0)=(c.index+i)%3?0x12345678901LL:0x22345678902LL;field<int>(items[j][i],0x238)=int((c.index+i)%4);
 }
 detour::Set patches;
 TL_REDIRECT(patches,dep_questItems,&questItems);
 TL_REDIRECT(patches,dep_unitItems,&unitItems);
 TL_REDIRECT(patches,dep_isa,&isa);
 TL_REDIRECT(patches,dep_remove,&remove);

 if(patches.failed())_exit(41);
 long long guid=c.index%3==0?-1LL:c.index%3==1?0x12345678901LL:0x22345678902LL;
 long long quest=c.index%5==0?-1LL:0x34567890123LL;
 switch(c.op){
 case 0:autotest::invoke(out,ours?candidate0:original0,self,guid,bool(c.index&4),bool(c.index&8),int(c.index%9));break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self,quest,guid,bool(c.index&4),bool(c.index&8),int(c.index%9));break;
 case 2:autotest::invoke(out,ours?candidate2:original2,c.index%13?self:0,bool(c.index&1));break;
 }
 for(unsigned j=0;j<2;++j)for(unsigned i=0;i<6;++i){number(field<int>(items[j][i],0x238));number(field<bool>(items[j][i],0x240));number(field<bool>(items[j][i],0x241));}
 for(unsigned j=0;j<8;++j)number(field<bool>(characters[j],0x82));
}
}
TL_TEST(mass3_8f1380) { return smallmass::run(host,0,"mass3_8f1380",(uint64_t)(uintptr_t)original0,execute,256); }
TL_TEST(mass3_8f16e0) { return smallmass::run(host,1,"mass3_8f16e0",(uint64_t)(uintptr_t)original1,execute,256); }
TL_TEST(mass3_aec900) { return smallmass::run(host,2,"mass3_aec900",(uint64_t)(uintptr_t)original2,execute,128); }
