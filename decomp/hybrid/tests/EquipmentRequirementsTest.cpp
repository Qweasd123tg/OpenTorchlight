#include <cstring>
#include <new>
#include <Ogre.h>
#include <map>
#define protected public
#define private public
#include "Equipment.h"
#include "DataGroup.h"
#include "GraphManager.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalEquipmentRequirements,(CEquipment*),"_ZN10CEquipment15setRequirementsEv")
TL_FUNCTION(erIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(erManager,"_ZN13CGraphManager12getSingletonEv")
TL_FUNCTION(erGraph,"_ZN13CGraphManager8getGraphERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(erValue,"_ZNK6CGraph8getValueEfj")
namespace {
struct Case{unsigned seed,mode;};
const Case* input;autotest::Capture* capture;CEquipment* equipment;CDataGroup* alternate;unsigned graphId;int service[6];
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}
void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){number(10);number(p==equipment);number(type);unsigned bits=input->seed%8;return type==UNITTYPES::WEAPON?(bits&1)!=0:type==UNITTYPES::ARMOR?(bits&2)!=0:type==UNITTYPES::TRINKET?(bits&4)!=0:false;}
CGraphManager* manager(){number(11);return reinterpret_cast<CGraphManager*>(&service[0]);}
CGraph* graph(CGraphManager* p,const std::wstring& name){number(12);number(p==reinterpret_cast<CGraphManager*>(&service[0]));text(name);static const wchar_t* keys[]={L"ITEM_LEVEL_REQUIREMENTS",L"ITEM_STRENGTH_REQUIREMENTS",L"ITEM_DEXTERITY_REQUIREMENTS",L"ITEM_MAGIC_REQUIREMENTS",L"ITEM_DEFENSE_REQUIREMENTS"};graphId=0;while(graphId<5&&name!=keys[graphId])++graphId;return reinterpret_cast<CGraph*>(&service[graphId]);}
float value(const CGraph* p,float x,unsigned line){number(13);number(p==reinterpret_cast<CGraph*>(&service[graphId]));real(x);number(line);static const float values[]={-0.25f,0.0f,1.99999f,2.0f,10.99999f,50.25f,100.5f,999.999f};float result=values[((input->seed/384)+graphId)%8];
    if(input->mode==1){equipment->m_iUnknown28C+=2;equipment->m_iUnknown274+=1;}
    if(input->mode==2){equipment->m_iUnknown27C+=7;equipment->m_iUnknown280+=9;equipment->m_iUnknown284+=11;equipment->m_iUnknown288+=13;}
    if(input->mode==3)equipment->m_pDataGroup=alternate;
    return result;
}
void side(const Case& c,bool ours,autotest::Capture& out){input=&c;capture=&out;unsigned long long storage[(sizeof(CEquipment)+7)/8];std::memset(storage,0,sizeof(storage));equipment=reinterpret_cast<CEquipment*>(storage);
    static const int reductions[]={-3,0,1,4,5,6,10,11};equipment->m_iUnknown28C=reductions[(c.seed/8)%8];equipment->m_iUnknown274=static_cast<int>(c.seed%51)-5;
    CDataGroup data(L"ITEM",0,8,8,0),other(L"ITEM",0,8,8,0);alternate=&other;equipment->m_pDataGroup=&data;
    static const wchar_t* keys[]={L"LEVEL_REQUIRED",L"STRENGTH_REQUIRED",L"DEXTERITY_REQUIRED",L"MAGIC_REQUIRED",L"DEFENSE_REQUIRED"};static const int requirements[]={0,1,2,-2,37,100};
    for(unsigned i=0;i<5;++i){unsigned mode=(c.seed/64+i)%6;if(mode)data.AddDataValue(keys[i],static_cast<unsigned int>(requirements[mode]));other.AddDataValue(keys[i],static_cast<unsigned int>(17+i));}
    detour::Set patches;TL_REDIRECT(patches,erIsa,&isa);TL_REDIRECT(patches,erManager,&manager);TL_REDIRECT(patches,erGraph,&graph);TL_REDIRECT(patches,erValue,&value);if(patches.failed())_exit(42);
    for(unsigned repeat=0;repeat<2;++repeat){if(ours)equipment->setRequirements();else originalEquipmentRequirements(equipment);number(equipment->m_iUnknown274);number(equipment->m_iUnknown278);number(equipment->m_iUnknown27C);number(equipment->m_iUnknown280);number(equipment->m_iUnknown284);number(equipment->m_iUnknown288);number(equipment->m_iUnknown28C);number(equipment->m_pDataGroup==alternate);}
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_requirements_differential){int failures=0;for(unsigned n=0;n<3360;++n){Case c={n<3072?n:n-3072,n<3072?0u:1+(n-3072)/96};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    requirements seed %u mode %u status %d/%d lengths %lu/%lu\n",c.seed,c.mode,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok)return failures;}host->log("    equipment requirements: 3360 cases, two calls per side\n");return failures;}
