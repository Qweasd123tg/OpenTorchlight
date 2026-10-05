#include <cstring>
#include <new>
#include <Ogre.h>
#include <map>
#define protected public
#define private public
#include "Equipment.h"
#include "DataGroup.h"
#include "GenericModel.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalEquipmentReskin,(CEquipment*,std::wstring),"_ZN10CEquipment13reskinByClassESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(rsLoad,"_ZN10CEquipment9loadModelESbIwSt11char_traitsIwESaIwEES3_")
namespace {
typedef char model_size[sizeof(CGenericModel)==0x250?1:-1];
typedef char model_path_offset[__builtin_offsetof(CGenericModel,m_sModelPath)==0x110?1:-1];
struct Case{unsigned seed,mode;};
const Case* input;autotest::Capture* capture;CEquipment* equipment;CGenericModel* model;
void number(int n){capture->add(&n,sizeof(n));}void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
void load(CEquipment* p,std::wstring primary,std::wstring secondary){number(100);number(p==equipment);text(primary);text(secondary);if(input->mode==1)model->m_sModelPath=primary;}
void side(const Case& c,bool ours,autotest::Capture& out){input=&c;capture=&out;unsigned long long eqStorage[(sizeof(CEquipment)+7)/8],modelStorage[(sizeof(CGenericModel)+7)/8];std::memset(eqStorage,0,sizeof(eqStorage));std::memset(modelStorage,0,sizeof(modelStorage));equipment=reinterpret_cast<CEquipment*>(eqStorage);model=reinterpret_cast<CGenericModel*>(modelStorage);
    static const wchar_t* classes[]={L"",L"destroyer",L"DESTROYER",L"alchemist",L"vanquisher",L"\x416"};static const wchar_t* paths[]={L"",L"mesh/path.mesh",L"MESH/PATH.MESH",L"mesh\\path.mesh",L"other.mesh",L"\x416.mesh"};
    new(&model->m_sModelPath)std::wstring(paths[(c.seed/6)%6]);equipment->m_pUnitModel=(c.seed/36)%2?model:NULL;
    CDataGroup data(L"ITEM",0,4,4,0);equipment->m_pDataGroup=&data;unsigned count=(c.seed/72)%5;
    for(unsigned i=0;i<count;++i){CDataGroup* g=data.AddDataGroup(L"WARDROBE");unsigned cls=(c.seed/360+i)%6;if(cls)g->AddDataValue(L"CLASS",std::wstring(classes[cls]),false);unsigned primary=(c.seed/5+i)%7,secondary=(c.seed/11+i)%7;if(primary)g->AddDataValue(L"ITEM_MESH",std::wstring(paths[primary-1]),false);if(secondary)g->AddDataValue(L"ITEM_MESH_SECONDARY",std::wstring(paths[secondary-1]),false);g->AddDataValue(L"MESH",std::wstring(L"wrong-key.mesh"),false);}
    data.AddDataGroup(L"OTHER")->AddDataValue(L"ITEM_MESH",std::wstring(L"not-wardrobe.mesh"),false);
    std::wstring query=classes[c.seed%6];
    if(c.mode==1){equipment->m_pUnitModel=model;CDataGroup* g=data.AddDataGroup(L"WARDROBE");g->AddDataValue(L"CLASS",query,false);g->AddDataValue(L"ITEM_MESH",std::wstring(L"new.mesh"),false);}
    if(c.mode>=2){equipment->m_pUnitModel=model;CDataGroup* a=data.AddDataGroup(L"WARDROBE");a->AddDataValue(L"CLASS",query,false);a->AddDataValue(L"ITEM_MESH",std::wstring(L"new.mesh"),false);a->AddDataValue(L"ITEM_MESH_SECONDARY",std::wstring(L"old-secondary.mesh"),false);CDataGroup* b=data.AddDataGroup(L"WARDROBE");b->AddDataValue(L"CLASS",query,false);if(c.mode==2)b->AddDataValue(L"ITEM_MESH",std::wstring(L""),false);if(c.mode==3)b->AddDataValue(L"ITEM_MESH_SECONDARY",std::wstring(L""),false);if(c.mode==4){model->m_sModelPath=L"NEW.MESH";b->AddDataValue(L"ITEM_MESH_SECONDARY",std::wstring(L"changed-secondary.mesh"),false);}}
    detour::Set patches;TL_REDIRECT(patches,rsLoad,&load);if(patches.failed())_exit(42);
    for(unsigned repeat=0;repeat<2;++repeat){if(ours)equipment->reskinByClass(query);else originalEquipmentReskin(equipment,query);text(query);text(model->m_sModelPath);}
    patches.restore();typedef std::wstring Text;model->m_sModelPath.~Text();
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_reskin_differential){int failures=0;for(unsigned n=0;n<2520;++n){Case c={n<2160?n:n-2160,n<2160?0u:1+(n-2160)/90};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    reskin seed %u mode %u status %d/%d lengths %lu/%lu\n",c.seed,c.mode,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok)return failures;}host->log("    equipment reskin: 2520 cases, two calls per side\n");return failures;}
