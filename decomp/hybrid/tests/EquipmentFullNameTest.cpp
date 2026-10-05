// Real string replacement/case conversion; controlled type and set services.
#include <cstring>
#include <new>
#include <Ogre.h>
#include <map>
#define protected public
#define private public
#include "Equipment.h"
#include "EffectManager.h"
#include "Affix.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(std::wstring, originalEquipmentFullName, (CEquipment*,bool), "_ZN10CEquipment15getFullItemNameEb")
TL_FUNCTION(fnIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(fnSet,"_ZN10CEquipment6getSetEv")
namespace {
struct Case {unsigned seed,mode;};
const Case* input;autotest::Capture* capture;CEquipment* object;CEffectManager* manager;
void number(int n){capture->add(&n,sizeof(n));}
void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES t){
    number(1);number(p==object);number(t);
    if(input->mode==1)object->m_bUnknown348=false;
    return input->mode>=7?false:(input->seed&4)!=0;
}
std::wstring set(CEquipment* p){
    number(2);number(p==object);
    if(input->mode==2)object->m_pEffectManager=0;
    if(input->mode==3)object->m_pEffectManager=manager;
    return input->mode<7 && (input->seed&8)?L"a set":L"";
}
std::wstring name(unsigned i){
    static const wchar_t* names[]={L"",L"Sword",L"{M}Sword",L"{f}Sword",L"{}",L"{",L"}",L"a{m}b{n}",L"{m}Sword{M}hot{/M}",L"{m}Sword{m}cold{/M}",L"{f}a{m}b{/m}{f}c{/f}",L"{m}a{m}b{/m",L"{m}a{n}b",L"{m}{x}",L"{m}{m}yes{/m}{n}no{/n}",L"{m}{m}yes{/m}{m}yes{/m}",L"{m}{m}{x}nested{/x}{/m}",L"{m}a{}b{/}",L"{m}{/m}",L"{{m}}Sword",L" {M}Sword ",L"{m}a{m}b{/mExtra}",L"\x416\U0001f525",L"{m}{m}body{/m}",L"{m}a{",L"{m}{x}}",L"{m}{m}x{/",L"{m}x{M}y{/M}"};
    return names[i%28];
}
std::wstring pattern(unsigned i){
    static const wchar_t* patterns[]={L"",L"[ITEM]",L"Fiery [ITEM]",L"[ITEM] of ice",L"[ITEM]/[ITEM]",L"fixed",L"{M}Red{/M}{F}Blue{/F}[ITEM]",L"{m}small{/m}[ITEM]",L"[ITEM]{m}a{/m}{f}b{/f}",L"[ITEM]{m}a{/M}",L"[ITEM]{x}no{/x}",L"[ITEM]{m}yes{/m",L"{}[ITEM]",L"[ITEM]{m}",L"\x416[ITEM]\U0001f525",L"[item]",L"[ITEM]{",L"[ITEM]{x}}"};
    if(i%20==18)return std::wstring(L"[ITEM]\0ignored",14);
    if(i%20==19)return std::wstring(L"\0ignored",8);
    return patterns[i%20];
}
void side(const Case& c,bool ours,autotest::Capture& out){
    input=&c;capture=&out;
    unsigned long long storage[(sizeof(CEquipment)+7)/8];std::memset(storage,0,sizeof(storage));object=reinterpret_cast<CEquipment*>(storage);
    typedef std::wstring Text;
    new(&object->m_sItemName) Text(name(c.seed/32));
    new(&object->m_sUnidentifiedName) Text((c.seed/768)%2?L"unknown {m}":L"");
    new(&object->m_sPrefix) Text(pattern(c.seed/64));
    new(&object->m_sSuffix) Text(pattern(c.seed/96+3));
    if(c.mode==4)object->m_sItemName=Text(L"{m}A\0B",7);
    object->m_bUnknown348=c.mode>=7?true:(c.seed&1)!=0;
    unsigned long long mgr[(sizeof(CEffectManager)+7)/8];std::memset(mgr,0,sizeof(mgr));manager=reinterpret_cast<CEffectManager*>(mgr);
    TArrayList<CAffix*>* list=new(reinterpret_cast<char*>(manager)+0x10) TArrayList<CAffix*>(2);
    unsigned long long affixes[5][(sizeof(CAffix)+7)/8];std::memset(affixes,0,sizeof(affixes));
    static const int ranks[]={10,0,5,-1,11};
    for(unsigned i=0;i<5;++i){
        CAffix* a=reinterpret_cast<CAffix*>(affixes[i]);a->m_iRank=c.mode==5?5:ranks[(c.seed/32+i)%5];
        new(&a->m_sPrefix) Text(pattern(c.seed/32+i));new(&a->m_sSuffix) Text(pattern(c.seed/64+2*i+1));
        if(c.mode<7 && i<(c.seed/32)%6)list->add(a);
    }
    object->m_pEffectManager=c.mode>=7 || (c.seed&16)?manager:0;
    if(c.mode>=7){object->m_sItemName=name(c.seed/20);object->m_sUnidentifiedName=L"";object->m_sPrefix=c.mode==7?pattern(c.seed%20):L"";object->m_sSuffix=c.mode==8?pattern(c.seed%20):L"";}
    detour::Set patches;TL_REDIRECT(patches,fnIsa,&isa);TL_REDIRECT(patches,fnSet,&set);if(patches.failed())_exit(42);
    for(unsigned repeat=0;repeat<2;++repeat){
        std::wstring result=ours?object->getFullItemName((c.seed&2)!=0):originalEquipmentFullName(object,(c.seed&2)!=0);
        number(100+repeat);text(result);text(object->m_sItemName);text(object->m_sUnidentifiedName);text(object->m_sPrefix);text(object->m_sSuffix);number(object->m_bUnknown348);number(object->m_pEffectManager==manager);
    }
    patches.restore();object->m_sItemName.~Text();object->m_sUnidentifiedName.~Text();object->m_sPrefix.~Text();object->m_sSuffix.~Text();
    for(unsigned i=0;i<5;++i){CAffix* a=reinterpret_cast<CAffix*>(affixes[i]);a->m_sPrefix.~Text();a->m_sSuffix.~Text();}list->~TArrayList<CAffix*>();
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}
void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_full_name_differential){
    int failures=0;
    for(unsigned n=0;n<3424;++n){Case c={n<1536?n:(n-1536)%768,n<1536?0u:1+(n-1536)/128};if(n>=2304){c.seed=(n-2304)%560;c.mode=7+(n-2304)/560;}autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok){size_t i=0;while(i<a.capture.length&&i<b.capture.length&&a.capture.data[i]==b.capture.data[i])++i;host->log("    full name %u mode %u: status %d/%d bytes %lu/%lu first %lu\n",c.seed,c.mode,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)i);}
        TL_CHECK(failures,ok);if(!ok)return failures;
    }
    host->log("    equipment full name: 3424 cases, two calls per side\n");return failures;
}
