#include <cstring>
#include <vector>
#include <new>
#include <Ogre.h>
#include <map>
#define protected public
#define private public
#include "Equipment.h"
#include "Inventory.h"
#include "DataGroup.h"
#include "GraphManager.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalEquipmentPrice,(CEquipment*),"_ZN10CEquipment16recalculatePriceEv")
TL_FUNCTION(epIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(epManager,"_ZN13CGraphManager12getSingletonEv")
TL_FUNCTION(epGraph,"_ZN13CGraphManager8getGraphERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(epValue,"_ZNK6CGraph8getValueEfj")
extern "C" void recoveredEquipmentPrice(CEquipment*) __asm__("_ZN10CEquipment16recalculatePriceEv");
extern "C" void* priceEquipmentTable[] __asm__("_ZTV10CEquipment");
namespace {
struct Case{unsigned seed,mode,warm;};
struct Snapshot{std::vector<unsigned char> bytes;Snapshot(const void* p,size_t n):bytes(static_cast<const unsigned char*>(p),static_cast<const unsigned char*>(p)+n){}void pointer(size_t at,uintptr_t id){if(at+sizeof(id)>bytes.size())_exit(71);std::memcpy(&bytes[at],&id,sizeof(id));}void emit(autotest::Capture& out){out.add(&bytes[0],bytes.size());}};
const Case* input;autotest::Capture* capture;CEquipment* equipment;CInventory* inventory;CBaseUnit* owner;int service[8];unsigned calls;
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){number(10);number(p==equipment?1:p==owner?2:0);number(type);return p==equipment?type==UNITTYPES::UNIQUE&&(input->seed&1):p==owner&&type==UNITTYPES::GAMBLER&&(input->seed/144)%4==3;}
bool magical(CEquipment* p){number(11);number(p==equipment);return (input->seed&2)!=0;}
CGraphManager* manager(){number(12);return reinterpret_cast<CGraphManager*>(&service[7]);}
CGraph* graph(CGraphManager* p,const std::wstring& name){number(13);number(p==reinterpret_cast<CGraphManager*>(&service[7]));text(name);static const wchar_t* keys[]={L"PRICE_PLAYERBUY_NORMAL",L"PRICE_PLAYERSELL_NORMAL",L"PRICE_PLAYERBUY_MAGIC",L"PRICE_PLAYERSELL_MAGIC",L"PRICE_PLAYERBUY_UNIQUE",L"PRICE_PLAYERSELL_UNIQUE",L"PRICE_PLAYERGAMBLE_MAGIC"};unsigned i=0;while(i<7&&name!=keys[i])++i;return reinterpret_cast<CGraph*>(&service[i]);}
float value(const CGraph* p,float x,unsigned line){unsigned id=0;while(id<8&&p!=reinterpret_cast<CGraph*>(&service[id]))++id;number(14);number(id);real(x);number(line);number(equipment->m_iUnknown264);number(equipment->m_iUnknown268);number(equipment->m_iUnknown26C);number(equipment->m_iUnknown270);
    static const float values[]={-0.25f,0.0f,0.001f,1.99999f,2.0f,50.25f,100.00000762939453f,999.999f};float result=values[(input->seed/576+id)%8];
    ++calls;if(input->mode==1){equipment->m_iUnknown274+=3;equipment->m_pDataGroup->AddDataValue(L"VALUE",static_cast<unsigned int>(900));}
    if(input->mode==2&&calls==2)equipment->m_pInventory=inventory;
    if(input->mode==3&&calls==2)equipment->m_pInventory=NULL;
    return result;
}
void side(const Case& c,bool ours,autotest::Capture& out){input=&c;capture=&out;calls=0;unsigned long long eqStorage[(sizeof(CEquipment)+7)/8],invStorage[(sizeof(CInventory)+7)/8],ownerStorage[(sizeof(CBaseUnit)+7)/8];std::memset(eqStorage,0,sizeof(eqStorage));std::memset(invStorage,0,sizeof(invStorage));std::memset(ownerStorage,0,sizeof(ownerStorage));equipment=reinterpret_cast<CEquipment*>(eqStorage);inventory=reinterpret_cast<CInventory*>(invStorage);owner=reinterpret_cast<CBaseUnit*>(ownerStorage);
    void* table[89];std::memcpy(table,priceEquipmentTable+2,sizeof(table));table[86]=reinterpret_cast<void*>(&magical);void** pointer=table;std::memcpy(equipment,&pointer,sizeof(pointer));
    static const int levels[]={-5,0,1,2,25,100};static const int values[]={0,1,-3,37,100,101};equipment->m_iUnknown274=levels[(c.seed/24)%6];equipment->m_iUnknown264=77;equipment->m_iUnknown268=88;equipment->m_iUnknown26C=99;equipment->m_iUnknown270=111;
    unsigned inv=(c.seed/144)%4;inventory->m_pPositionableObject=inv==1?NULL:reinterpret_cast<CCharacter*>(owner);equipment->m_pInventory=inv==0?NULL:inventory;if(c.mode==2)equipment->m_pInventory=NULL;
    CDataGroup data(L"ITEM",0,4,4,0);equipment->m_pDataGroup=&data;if((c.seed/4)%6!=4)data.AddDataValue(L"VALUE",static_cast<unsigned int>(values[(c.seed/4)%6]));
    detour::Set patches;TL_REDIRECT(patches,epIsa,&isa);TL_REDIRECT(patches,epManager,&manager);TL_REDIRECT(patches,epGraph,&graph);TL_REDIRECT(patches,epValue,&value);if(patches.failed())_exit(42);
    typedef void (*Fn)(CEquipment*);Fn fn=ours?&recoveredEquipmentPrice:&originalEquipmentPrice;
    for(unsigned repeat=0;repeat<=c.warm;++repeat){if(repeat==c.warm)autotest::invoke(out,fn,equipment);else fn(equipment);number(equipment->m_iUnknown264);number(equipment->m_iUnknown268);number(equipment->m_iUnknown26C);number(equipment->m_iUnknown270);number(equipment->m_iUnknown274);number(equipment->m_pInventory==inventory);}
    Snapshot eq(equipment,sizeof(CEquipment));eq.pointer(0,*reinterpret_cast<void***>(equipment)==table?1:255);eq.pointer(0x1b0,equipment->m_pDataGroup==&data?1:255);eq.pointer(0x240,equipment->m_pInventory==inventory?1:equipment->m_pInventory?255:0);eq.emit(out);
    Snapshot iv(inventory,sizeof(CInventory));iv.pointer(0x20,inventory->m_pPositionableObject==owner?1:inventory->m_pPositionableObject?255:0);iv.emit(out);out.add(owner,sizeof(CBaseUnit));number(data.GetDataValue(L"VALUE",100));number(calls);

}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_price_differential){int failures=0;autotest::Coverage coverage("equipment_price_differential",(uint64_t)(uintptr_t)&originalEquipmentPrice);
for(unsigned n=0;n<4896;++n)for(unsigned warm=0;warm<2;++warm){Case c={n<4608?n:n-4608+432,n<4608?0u:1+(n-4608)/96,warm};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int difference=coverage.observe(host,a,b);bool ok=!difference&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus;if(!ok)host->log("    price seed %u mode %u warm %u status %d/%d lengths %lu/%lu\n",c.seed,c.mode,c.warm,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok){coverage.report(host);return failures;}}
coverage.report(host);return failures;}
