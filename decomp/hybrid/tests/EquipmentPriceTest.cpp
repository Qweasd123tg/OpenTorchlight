#include <cstring>
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
extern "C" void* priceEquipmentTable[] __asm__("_ZTV10CEquipment");
namespace {
struct Case{unsigned seed,mode;};
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
    unsigned inv=(c.seed/144)%4;inventory->m_pPositionableObject=inv==1?NULL:owner;equipment->m_pInventory=inv==0?NULL:inventory;if(c.mode==2)equipment->m_pInventory=NULL;
    CDataGroup data(L"ITEM",0,4,4,0);equipment->m_pDataGroup=&data;if((c.seed/4)%6!=4)data.AddDataValue(L"VALUE",static_cast<unsigned int>(values[(c.seed/4)%6]));
    detour::Set patches;TL_REDIRECT(patches,epIsa,&isa);TL_REDIRECT(patches,epManager,&manager);TL_REDIRECT(patches,epGraph,&graph);TL_REDIRECT(patches,epValue,&value);if(patches.failed())_exit(42);
    for(unsigned repeat=0;repeat<2;++repeat){if(ours)equipment->recalculatePrice();else originalEquipmentPrice(equipment);number(equipment->m_iUnknown264);number(equipment->m_iUnknown268);number(equipment->m_iUnknown26C);number(equipment->m_iUnknown270);number(equipment->m_iUnknown274);number(equipment->m_pInventory==inventory);}
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_price_differential){int failures=0;for(unsigned n=0;n<4896;++n){Case c={n<4608?n:n-4608+432,n<4608?0u:1+(n-4608)/96};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    price seed %u mode %u status %d/%d lengths %lu/%lu\n",c.seed,c.mode,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok)return failures;}host->log("    equipment price: 4896 cases, two calls per side\n");return failures;}
