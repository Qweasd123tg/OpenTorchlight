#include <cstring>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
#include "Equipment.h"
#include "StringTranslate.h"
TL_ORIGINAL(std::wstring, originalEquipmentType, (CEquipment*,bool), "_ZN10CEquipment16getEquipmentTypeEb")
TL_FUNCTION(etIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(etTranslation,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(etTranslate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(etQuest,"_ZN9CBaseUnit14getIsQuestUnitEv")
namespace {
struct Case {unsigned seed,mode;};
const Case* input;autotest::Capture* capture;CEquipment* object;unsigned long long service;
// Each leaf plus category fallbacks; IDs are from the original unittypes.hie.
static const int types[]={11,36,44,89,105,61,90,116,110,98,8,12,23,16,18,15,20,21,13,120,39,33,42,0};
void number(int n){capture->add(&n,sizeof(n));}
void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES t){
    number(1);number(p==object);number(t);unsigned leaf=input->seed%24,quality=(input->seed/24)%4;
    if(input->mode==8)object->m_bUnknown348=!object->m_bUnknown348;
    if(t==UNITTYPES::UNIQUE)return quality==1;
    if(t==UNITTYPES::MAGIC)return quality==2;
    return static_cast<int>(t)==types[leaf] || (t==UNITTYPES::WEAPON&&leaf<11) || (t==UNITTYPES::ARMOR&&leaf>=11&&leaf<19);
}
CStringTranslate* translator(){number(2);return reinterpret_cast<CStringTranslate*>(&service);}
std::wstring translate(CStringTranslate*,const wchar_t* s){
    number(3);text(s);std::wstring value=s;
    switch(input->mode){
    case 1:return L"";
    case 2:return L"{remove}"+value+L"{keep}";
    case 3:return L"{}"+value;
    case 4:return L"{"+value;
    case 5:return L"}"+value+L"{x}";
    case 6:return L"{{nested}}"+value;
    case 7:return L"\x416\U0001f525"+value+L"{\x416}";
    default:return L"T:"+value;
    }
}
bool quest(CBaseUnit* p){number(4);number(p==object);return (input->seed/192)%2!=0;}
bool magical(CEquipment* p){number(5);number(p==object);return (input->seed/24)%4==3;}
void side(const Case& c,bool ours,autotest::Capture& out){
    input=&c;capture=&out;unsigned long long storage[(sizeof(CEquipment)+7)/8];std::memset(storage,0,sizeof(storage));object=reinterpret_cast<CEquipment*>(storage);
    void* vtable[128];std::memset(vtable,0,sizeof(vtable));vtable[86]=reinterpret_cast<void*>(&magical);*reinterpret_cast<void***>(object)=vtable;
    object->m_bUnknown348=(c.seed/96)%2!=0;
    detour::Set patches;TL_REDIRECT(patches,etIsa,&isa);TL_REDIRECT(patches,etTranslation,&translator);TL_REDIRECT(patches,etTranslate,&translate);TL_REDIRECT(patches,etQuest,&quest);
    if(patches.failed())_exit(42);
    for(int i=0;i<2;++i){bool show=(c.seed/384)%2!=0;std::wstring result=ours?object->getEquipmentType(show):originalEquipmentType(object,show);number(100+i);text(result);number(object->m_bUnknown348);}
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}
void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_type_differential){
    int failures=0;
    for(unsigned n=0;n<1536;++n){
        Case c={n<768?n:((n-768)%96)+480,n<768?0u:1+(n-768)/96};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok){size_t i=0;while(i<a.capture.length&&i<b.capture.length&&a.capture.data[i]==b.capture.data[i])++i;host->log("    type %u mode %u: status %d/%d bytes %lu/%lu first %lu\n",c.seed,c.mode,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)i);}
        TL_CHECK(failures,ok);
    }
    host->log("    equipment type: 1536 cases, two calls per side\n");return failures;
}
