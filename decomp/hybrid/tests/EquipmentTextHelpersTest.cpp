#include <string>
#include <cstring>
#define private public
#define protected public
#include "Equipment.h"
#include "DataGroup.h"
#include "StringTranslate.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(std::wstring,oldTrim,(const std::wstring&),"_Z16removeWhiteSpaceRKSbIwSt11char_traitsIwESaIwEE")
extern "C" std::wstring newTrim(const std::wstring&) __asm__("_Z16removeWhiteSpaceRKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(std::wstring,oldSpeed,(CEquipment*,EWeaponSpeed),"_ZN10CEquipment20getAttackSpeedStringE12EWeaponSpeed")
extern "C" std::wstring newSpeed(CEquipment*,EWeaponSpeed) __asm__("_ZN10CEquipment20getAttackSpeedStringE12EWeaponSpeed");
TL_ORIGINAL(std::wstring,oldFlavor,(CEquipment*),"_ZN10CEquipment20getFlavorDescriptionEv")
extern "C" std::wstring newFlavor(CEquipment*) __asm__("_ZN10CEquipment20getFlavorDescriptionEv");
TL_ORIGINAL(std::wstring,oldSet,(CEquipment*),"_ZN10CEquipment6getSetEv")
extern "C" std::wstring newSet(CEquipment*) __asm__("_ZN10CEquipment6getSetEv");
TL_FUNCTION(translateSingleton,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(translateText,"_ZN16CStringTranslate18getTranslateStringEPKw")
namespace {
struct Case{unsigned n,warm,kind;};const Case* cs;autotest::Capture* cap;unsigned calls;unsigned long long token;
void n(int x){cap->add(&x,4);}std::wstring sample(unsigned k){switch(k%8){case 0:return L"";case 1:return L"\n";case 2:return L"\n\nx\n\n";case 3:return L" \t\r\n";case 4:return std::wstring(L"\nA\0B\n",5);case 5:return L"\x416\x20ac";case 6:return std::wstring(80,L'\n')+L"middle"+std::wstring(81,L'\n');default:return L"a\nb";}}
CStringTranslate* singleton(){n(1);return reinterpret_cast<CStringTranslate*>(&token);}
std::wstring translated(CStringTranslate* p,const wchar_t* key){n(2);n(p==reinterpret_cast<CStringTranslate*>(&token));cap->addText(std::wstring(key));++calls;static std::wstring value;value=sample(cs->n/11);return value;}
void trim(void* raw,autotest::Capture& out,bool ours){Case c=*(Case*)raw;std::wstring text=sample(c.n);if(c.n>=8){const wchar_t alphabet[]={L'\n',L' ',L'\r',L'\0',L'x'};unsigned q=c.n-8;text.clear();for(unsigned i=0;i<4;++i){text.push_back(alphabet[q%5]);q/=5;}}if(c.warm)text.reserve(1024);std::wstring shared=text;typedef std::wstring(*Fn)(const std::wstring&);autotest::invoke<Fn,const std::wstring&>(out,ours?&newTrim:&oldTrim,text);out.addText(text);out.addText(shared);}
void trA(void*p,autotest::Capture&o){trim(p,o,false);}void trB(void*p,autotest::Capture&o){trim(p,o,true);}
void speed(void*raw,autotest::Capture&out,bool ours){Case c=*(Case*)raw;cs=&c;cap=&out;calls=0;unsigned long long memory[(sizeof(CEquipment)+7)/8];std::memset(memory,0xa5,sizeof(memory));CEquipment* item=(CEquipment*)memory;EWeaponSpeed v=static_cast<EWeaponSpeed>(int(c.n%11)-3);detour::Set d;TL_REDIRECT(d,translateSingleton,&singleton);TL_REDIRECT(d,translateText,&translated);if(d.failed())_exit(60);for(unsigned i=0;i<c.warm;++i)out.addText(ours?newSpeed(item,v):oldSpeed(item,v));autotest::invoke(out,ours?&newSpeed:&oldSpeed,item,v);n(calls);out.add(memory,sizeof(memory));}
void spA(void*p,autotest::Capture&o){speed(p,o,false);}void spB(void*p,autotest::Capture&o){speed(p,o,true);}
void text(void*raw,autotest::Capture&out,bool ours){Case c=*(Case*)raw;unsigned long long memory[(sizeof(CEquipment)+7)/8];std::memset(memory,0xa5,sizeof(memory));CEquipment*item=(CEquipment*)memory;CDataGroup group(L"ITEM",0,4,4,0);item->m_pDataGroup=&group;std::wstring value=sample(c.n/4);if(c.n&1)group.AddDataValue(L"DESCRIPTION",value,false);if(c.n&2)group.AddDataValue(L"SET",value,false);group.AddDataValue(L"UNRELATED",std::wstring(L"wrong"),false);if(c.kind)autotest::invoke(out,ours?&newSet:&oldSet,item);else autotest::invoke(out,ours?&newFlavor:&oldFlavor,item);out.addText(value);item->m_pDataGroup=0;out.add(memory,sizeof(memory));}
void txA(void*p,autotest::Capture&o){text(p,o,false);}void txB(void*p,autotest::Capture&o){text(p,o,true);}
}
TL_TEST(equipment_trim_production){autotest::Coverage cv("equipment_trim_production",(uint64_t)(uintptr_t)&oldTrim);for(unsigned i=0;i<633;++i)for(unsigned warm=0;warm<2;++warm){Case c={i,warm,0};autotest::Outcome a,b;autotest::runChild(trA,&c,a);autotest::runChild(trB,&c,b);if(cv.observe(host,a,b)){cv.report(host);return 1;}}cv.report(host);return 0;}
TL_TEST(equipment_speed_text_production){autotest::Coverage cv("equipment_speed_text_production",(uint64_t)(uintptr_t)&oldSpeed);for(unsigned i=0;i<88;++i)for(unsigned warm=0;warm<3;++warm){Case c={i,warm,0};autotest::Outcome a,b;autotest::runChild(spA,&c,a);autotest::runChild(spB,&c,b);if(cv.observe(host,a,b)){host->log("    speed text %u/%u\n",i,warm);cv.report(host);return 1;}}cv.report(host);return 0;}
TL_TEST(equipment_data_text_production){autotest::Coverage flavor("equipment_data_text_production",(uint64_t)(uintptr_t)&oldFlavor),set("equipment_data_text_production",(uint64_t)(uintptr_t)&oldSet);for(unsigned kind=0;kind<2;++kind)for(unsigned i=0;i<32;++i){Case c={i,0,kind};autotest::Outcome a,b;autotest::runChild(txA,&c,a);autotest::runChild(txB,&c,b);if((kind?set:flavor).observe(host,a,b)){flavor.report(host);set.report(host);return 1;}}flavor.report(host);set.report(host);return 0;}
