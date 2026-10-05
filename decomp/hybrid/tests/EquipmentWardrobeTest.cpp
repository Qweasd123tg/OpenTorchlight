#include <cstring>
#include "AutoTest.h"
#define protected public
#include "Equipment.h"
#include "DataGroup.h"
#undef protected
TL_ORIGINAL(bool, originalEquipmentWardrobe, (CEquipment*,std::wstring), "_ZN10CEquipment11isWardrobedESbIwSt11char_traitsIwESaIwEE")
namespace {
struct Case{unsigned seed,mode;};
void text(autotest::Capture& c,const std::wstring& s){unsigned n=s.size();c.add(&n,sizeof(n));c.add(s.data(),n*sizeof(wchar_t));}
void side(const Case& c,bool ours,autotest::Capture& out){
    unsigned long long storage[(sizeof(CEquipment)+7)/8];std::memset(storage,0,sizeof(storage));CEquipment* object=reinterpret_cast<CEquipment*>(storage);
    CDataGroup data(L"ITEM",0,4,4,0);object->m_pDataGroup=&data;
    static const wchar_t* classes[]={L"",L"destroyer",L"ALCHEMIST",L"Destroyer",L"vanquisher",L"unknown",L"\x416"};
    unsigned count=c.mode==0?(c.seed/7)%6:c.mode==1?1:4;
    for(unsigned i=0;i<count;++i){
        CDataGroup* g=data.AddDataGroup(c.mode==3&&i%2?L"UNRELATED":L"WARDROBE");
        if((c.seed+i)%5)g->AddDataValue(L"CLASS",std::wstring(classes[(c.seed/11+i)%7]),false);
        unsigned a=(c.seed/3+i)%5,b=(c.seed/13+2*i)%5;
        if(c.mode==1){a=(c.seed/7)%5;b=(c.seed/35)%5;g->AddDataValue(L"CLASS",std::wstring(classes[c.seed%7]),false);}
        if(c.mode==2){a=i==3?2:0;b=0;g->AddDataValue(L"CLASS",std::wstring(classes[c.seed%7]),false);}
        if(a)g->AddDataValue(L"MESH",a==1?L"":a==2?L"part":a==3?std::wstring(1,L'\0'):L" ",false);
        if(b)g->AddDataValue(L"TEXTURE",b==1?L"":b==2?L"texture":b==3?std::wstring(1,L'\0'):L" ",false);
        // ICON/ITEM_MESH alone must not satisfy this predicate.
        g->AddDataValue(L"ICON",std::wstring(L"icon"),false);g->AddDataValue(L"ITEM_MESH",std::wstring(L"item.mesh"),false);
    }
    std::wstring query=classes[c.seed%7];if(c.mode==4)query=std::wstring(L"\0ignored",8);
    for(unsigned repeat=0;repeat<2;++repeat){bool result=ours?object->isWardrobed(query):originalEquipmentWardrobe(object,query);out.add(&result,sizeof(result));text(out,query);}
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_wardrobe_differential){
    int failures=0;
    for(unsigned n=0;n<1540;++n){Case c={n<840?n:(n-840)%175,n<840?0u:1+(n-840)/175};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok)host->log("    wardrobe seed %u mode %u status %d/%d lengths %lu/%lu\n",c.seed,c.mode,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
        TL_CHECK(failures,ok);if(!ok)return failures;
    }
    host->log("    equipment wardrobe: 1540 cases, two calls per side\n");return failures;
}
