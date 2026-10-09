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
extern "C" std::wstring recoveredEquipmentFullName(CEquipment*,bool) __asm__("_ZN10CEquipment15getFullItemNameEb");
TL_FUNCTION(fnIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(fnSet,"_ZN10CEquipment6getSetEv")
namespace {
struct Case {unsigned seed,mode,warm,limited;};
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
struct Snapshot {
 std::vector<unsigned char> bytes;
 Snapshot(const void* p,size_t n):bytes(static_cast<const unsigned char*>(p),static_cast<const unsigned char*>(p)+n){}
 void pointer(size_t offset,uintptr_t value){if(offset+sizeof(value)>bytes.size())_exit(62);std::memcpy(&bytes[offset],&value,sizeof(value));}
 void string(const void* base,const std::wstring& s){pointer(reinterpret_cast<const char*>(&s)-static_cast<const char*>(base),s.empty()?0:1);text(s);}
 void emit(){capture->add(&bytes[0],bytes.size());}
};
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
        if(c.mode==6){static const int extremes[]={-2147483647-1,-1,0,2147483647,5};a->m_iRank=extremes[(c.seed+i)%5];}
        new(&a->m_sPrefix) Text(pattern(c.seed/32+i));new(&a->m_sSuffix) Text(pattern(c.seed/64+2*i+1));
        if(c.mode<7 && i<(c.seed/32)%6)list->add(a);
    }
    object->m_pEffectManager=c.mode>=7 || (c.seed&16)?manager:0;
    if(c.mode>=7){object->m_sItemName=name(c.seed/20);object->m_sUnidentifiedName=L"";object->m_sPrefix=c.mode==7?pattern(c.seed%20):L"";object->m_sSuffix=c.mode==8?pattern(c.seed%20):L"";}
    if(c.limited&&list->size()>1)list->m_nCapacity=1;
    detour::Set patches;TL_REDIRECT(patches,fnIsa,&isa);TL_REDIRECT(patches,fnSet,&set);if(patches.failed())_exit(42);
    for(unsigned repeat=0;repeat<=c.warm;++repeat){
        if(repeat==c.warm){if(ours)autotest::invoke(out,&recoveredEquipmentFullName,object,(c.seed&2)!=0);else autotest::invoke(out,&originalEquipmentFullName,object,(c.seed&2)!=0);}
        else text(ours?object->getFullItemName((c.seed&2)!=0):originalEquipmentFullName(object,(c.seed&2)!=0));
        number(100+repeat);text(object->m_sItemName);text(object->m_sUnidentifiedName);text(object->m_sPrefix);text(object->m_sSuffix);number(object->m_bUnknown348);number(object->m_pEffectManager==manager);
    }
    Snapshot eq(object,sizeof(*object));eq.string(object,object->m_sItemName);eq.string(object,object->m_sUnidentifiedName);eq.string(object,object->m_sPrefix);eq.string(object,object->m_sSuffix);eq.pointer(__builtin_offsetof(CEquipment,m_pEffectManager),object->m_pEffectManager==manager?1:object->m_pEffectManager?2:0);eq.emit();
    Snapshot ms(manager,sizeof(*manager));ms.pointer(0x10,list->m_pData?1:0);ms.emit();
    for(unsigned i=0;i<list->size();++i){unsigned id=0;while(id<5&&list->m_pData[i]!=reinterpret_cast<CAffix*>(affixes[id]))++id;number(id);}
    for(unsigned i=0;i<5;++i){CAffix* a=reinterpret_cast<CAffix*>(affixes[i]);Snapshot as(a,sizeof(*a));as.string(a,a->m_sPrefix);as.string(a,a->m_sSuffix);as.emit();}
    patches.restore();object->m_sItemName.~Text();object->m_sUnidentifiedName.~Text();object->m_sPrefix.~Text();object->m_sSuffix.~Text();
    for(unsigned i=0;i<5;++i){CAffix* a=reinterpret_cast<CAffix*>(affixes[i]);a->m_sPrefix.~Text();a->m_sSuffix.~Text();}list->~TArrayList<CAffix*>();
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}
void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_full_name_differential){
    autotest::Coverage coverage("equipment_full_name_differential",(uint64_t)(uintptr_t)&originalEquipmentFullName);unsigned count=0;
    for(unsigned n=0;n<3552;++n)for(unsigned warm=0;warm<2;++warm){Case c={n<1536?n:(n-1536)%768,n<1536?0u:1+(n-1536)/128,warm,0};if(n>=2304){c.seed=(n-2304)%560;c.mode=7+(n-2304)/560;}if(n>=3424){c.seed=64+n-3424;c.mode=0;c.limited=1;}
        autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);++count;
        int pair=coverage.observe(host,a,b);bool ok=!pair&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok){size_t i=0;while(i<a.capture.length&&i<b.capture.length&&a.capture.data[i]==b.capture.data[i])++i;host->log("    full name %u mode %u warm %u limited %u: status %d/%d bytes %lu/%lu first %lu\n",c.seed,c.mode,c.warm,c.limited,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)i);coverage.report(host);return 1;}
    }
    coverage.report(host);host->log("    equipment full name: %u completed cold/warm, rank boundary and capacity cases\n",count);return 0;
}
