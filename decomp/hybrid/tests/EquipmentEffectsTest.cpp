#include <cstring>
#include <cstdlib>
#include <dlfcn.h>
#include "AutoTest.h"
#include "Detour.h"
#include "Equipment.h"
#include "StringUtilities.h"
TL_ORIGINAL(std::wstring, originalEquipmentEffects, (CEquipment*), "_ZN10CEquipment19getEquipmentEffectsEv")
extern "C" std::wstring recoveredEquipmentEffects(CEquipment*) __asm__("_ZN10CEquipment19getEquipmentEffectsEv");
TL_ORIGINAL(std::wstring, originalTrimEquipmentText, (const std::wstring&), "_Z16removeWhiteSpaceRKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(egLeaf,"_ZN10CEquipment18effectsDescriptionE18EEFFECT_ACTIVATIONbb")
TL_FUNCTION(egSkill,"_ZN10CEquipment16skillDescriptionEv")
namespace {
struct Case{unsigned seed,mode,warm;};
const Case* input;autotest::Capture* capture;CEquipment* object;unsigned leafCalls,skillCalls;
void number(int n){capture->add(&n,sizeof(n));}
void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
std::wstring value(unsigned index){
    if(input->mode==1)return L"";
    if(input->mode==2)return L"\n\n";
    switch((input->seed/2+index*3)%12){
    case 0:return L"";case 1:return L"\n";case 2:return L"\n\n";case 3:return L"x";
    case 4:return L"\nx\n";case 5:return L"x\n\n";case 6:return L" a \n";
    case 7:return L"\t\r\n";case 8:return L"\nA\nB\n";case 9:return L"\n\n\x416\U0001f525\n\n";
    case 10:return std::wstring(L"\nA\0B\n",5);default:return L"\r";
    }
}
std::wstring leaf(CEquipment* p,EEFFECT_ACTIVATION a,bool embedded,bool sockets){number(1);number(p==object);number(a);number(embedded);number(sockets);unsigned index=leafCalls++;if(input->mode==3&&index==0)object->m_bUnknown348=false;return value(index);}
std::wstring skill(CEquipment* p){number(2);number(p==object);++skillCalls;return value(6);}
void side(const Case& c,bool ours,autotest::Capture& out){
    input=&c;capture=&out;leafCalls=0;skillCalls=0;unsigned long long storage[(sizeof(CEquipment)+7)/8];std::memset(storage,0,sizeof(storage));object=reinterpret_cast<CEquipment*>(storage);object->m_bUnknown348=(c.seed&1)!=0;
    detour::Set patches;TL_REDIRECT(patches,egLeaf,&leaf);TL_REDIRECT(patches,egSkill,&skill);if(patches.failed())_exit(42);
    typedef void (*BeginCount)();typedef unsigned long long (*EndCount)();
    BeginCount begin=reinterpret_cast<BeginCount>(dlsym(RTLD_DEFAULT,"otl_begin_alloc_count"));
    EndCount end=reinterpret_cast<EndCount>(dlsym(RTLD_DEFAULT,"otl_end_alloc_count"));
    if((begin==0)!=(end==0) || (std::getenv("OTL_ALLOC_REQUIRED") && !begin))_exit(64);
    for(unsigned repeat=0;repeat<=c.warm;++repeat){
        bool wasIdentified=object->m_bUnknown348;
        if(begin)begin();
        if(repeat==c.warm){if(ours)autotest::invoke(out,&recoveredEquipmentEffects,object);else autotest::invoke(out,&originalEquipmentEffects,object);}
        else {std::wstring result=ours?object->getEquipmentEffects():originalEquipmentEffects(object);text(result);}
        unsigned long long allocations=end?end():0;
        if(begin && wasIdentified && allocations==0)_exit(65);
        number(100+repeat);number(object->m_bUnknown348);number(leafCalls);number(skillCalls);capture->add(&allocations,sizeof(allocations));capture->add(object,sizeof(*object));
    }
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}
void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_effects_differential){
    autotest::Coverage coverage("equipment_effects_differential",(uint64_t)(uintptr_t)&originalEquipmentEffects);unsigned count=0;
    for(unsigned n=0;n<384;++n)for(unsigned warm=0;warm<2;++warm){Case c={n<192?n:(n-192)%64,n<192?0u:1+(n-192)/64,warm};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);++count;
        int pair=coverage.observe(host,a,b);bool ok=!pair&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok){size_t i=0;while(i<a.capture.length&&i<b.capture.length&&a.capture.data[i]==b.capture.data[i])++i;host->log("    effects %u mode %u warm %u: status %d/%d bytes %lu/%lu first %lu\n",c.seed,c.mode,c.warm,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)i);coverage.report(host);return 1;}
    }
    coverage.report(host);host->log("    equipment effects: %u completed cold/warm cases; malloc counter %s\n",count,dlsym(RTLD_DEFAULT,"otl_begin_alloc_count")?"active":"not loaded");return 0;
}
TL_TEST(equipment_effects_trim_helper){
    int failures=0;std::wstring samples[]={L"",L"\n",L"\n\n",L"x",L"\nx\n",L"\n\nx\n\n",L" x ",L"\t\r\n",L"\n \n",L"\r\n",L"\n\r",L"\x416\U0001f525\n",std::wstring(L"\nA\0B\n",5),std::wstring(L"\0\n",2)};
    for(unsigned i=0;i<sizeof(samples)/sizeof(samples[0]);++i){
        std::wstring before=samples[i],shared=before;
        std::wstring expected=originalTrimEquipmentText(samples[i]);std::wstring actual=removeWhiteSpace(samples[i]);
        TL_CHECK(failures,expected==actual);TL_CHECK(failures,samples[i]==before&&shared==before);
    }
    const wchar_t alphabet[]={L'\n',L'x',L' ',L'\r',L'\0'};
    unsigned total=0,power=1;
    for(unsigned length=0;length<=6;++length){
        for(unsigned code=0;code<power;++code){
            std::wstring inputText(length,L'x');unsigned value=code;
            for(unsigned i=0;i<length;++i){inputText[i]=alphabet[value%5];value/=5;}
            std::wstring before=inputText,shared=inputText;
            TL_CHECK(failures,originalTrimEquipmentText(inputText)==removeWhiteSpace(inputText));
            TL_CHECK(failures,inputText==before&&shared==before);++total;
        }
        power*=5;
    }
    std::wstring longText=std::wstring(64,L'\n')+L"body"+std::wstring(64,L'\n');
    TL_CHECK(failures,originalTrimEquipmentText(longText)==removeWhiteSpace(longText));
    host->log("    trim helper: 14 edge cases, %u exhaustive small strings, one long boundary case\n",total);
    return failures;
}
