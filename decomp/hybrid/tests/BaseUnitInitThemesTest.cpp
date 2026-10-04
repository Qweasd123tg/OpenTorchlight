#include <cstring>
#include <new>
#include <map>
#include <string>
#include "AutoTest.h"
#include "BaseUnit.h"
#include "DataGroup.h"
#include "UnitThemes.h"
#include "StringTranslate.h"
TL_ORIGINAL(void, originalInitThemes, (CBaseUnit*), "_ZN9CBaseUnit14unitInitThemesEv")
extern CUnitThemes* initThemeCatalog __asm__("_ZL13g_pUnitThemes");
namespace {
struct Case {unsigned int seed;};
void pointerAt(void* p,size_t offset,void* v) {std::memcpy(static_cast<char*>(p)+offset,&v,sizeof(v));}
void side(Case& c,bool ours,autotest::Capture& out) {
    CDataGroup data(L"UNIT",NULL,4,4,NULL);
    CDataGroup* group=data.AddDataGroup(c.seed%9==0?L"OTHER":L"THEMES");
    if(c.seed%9==0)group=group->AddDataGroup(L"THEMES");
    long long translator[0x50/8];std::memset(translator,0,sizeof(translator));
    typedef std::map<std::wstring,std::wstring> Translations;
    Translations* translations=new(reinterpret_cast<char*>(translator)+0x10)Translations;
    (*translations)[L"missing"]=L"ALPHA";(*translations)[L"alpha"]=L"BETA";(*translations)[L"BETA"]=L"ALPHA";
    new(reinterpret_cast<char*>(translator)+0x40)std::wstring;
    reinterpret_cast<char*>(translator)[0x48]=1;
    CStringTranslate* savedTranslator=m_gStringTranslate;m_gStringTranslate=reinterpret_cast<CStringTranslate*>(translator);
    const wchar_t* words[]={L"alpha",L"BETA",L"missing",L"",L"AlPhA",L"beta"};
    if(c.seed%7) {
        group->AddDataValue(L"A",std::wstring(words[c.seed%6]),false);
        group->AddDataValue(L"B",std::wstring(words[(c.seed+1)%6]),true);
        group->AddDataValue(L"C",std::wstring(words[(c.seed+2)%6]),false);
        group->AddDataValue(L"NUMBER",17u);group->AddDataValue(L"BOOL",true);
    }
    long long base[0x1d8/8],catalog[0x30/8],themes[3][0x38/8];
    std::memset(base,0,sizeof(base));std::memset(catalog,0,sizeof(catalog));std::memset(themes,0,sizeof(themes));
    const wchar_t* names[]={L"ALPHA",L"BETA",L""};CUnitTheme* tokens[4];tokens[0]=NULL;
    for(unsigned int i=0;i<3;++i) {new(reinterpret_cast<char*>(themes[i])+0x28)std::wstring(names[i]);tokens[i+1]=reinterpret_cast<CUnitTheme*>(themes[i]);}
    TArrayList<CUnitTheme*>* available=new(reinterpret_cast<char*>(catalog)+0x18)TArrayList<CUnitTheme*>(1);
    for(unsigned int i=0;i<3;++i)available->add(tokens[i+1]);
    CUnitThemes* saved=initThemeCatalog;initThemeCatalog=c.seed%11?reinterpret_cast<CUnitThemes*>(catalog):NULL;
    TArrayList<CUnitTheme*>* lists[4];char* self=reinterpret_cast<char*>(base);
    for(unsigned int i=0;i<4;++i) {lists[i]=new(self+0x108+i*0x18)TArrayList<CUnitTheme*>(1);if(c.seed&(1u<<i))lists[i]->add(tokens[(c.seed+i)%4]);}
    if(c.seed%13)pointerAt(base,0x1b0,&data);
    CBaseUnit* object=reinterpret_cast<CBaseUnit*>(base);
    if(ours)object->unitInitThemes();else originalInitThemes(object);
    unsigned int groupCount=data.GetNumberOfDataGroups();out.add(&groupCount,sizeof(groupCount));
    for(unsigned int i=0;i<4;++i) {
        out.add(reinterpret_cast<char*>(lists[i])+8,12);
        for(unsigned int j=0;j<lists[i]->size();++j) {int id=-1;for(int k=0;k<4;++k)if((*lists[i])[j]==tokens[k])id=k;out.add(&id,sizeof(id));}
        lists[i]->~TArrayList<CUnitTheme*>();
    }
    initThemeCatalog=saved;available->~TArrayList<CUnitTheme*>();
    m_gStringTranslate=savedTranslator;translations->~Translations();
    reinterpret_cast<std::wstring*>(reinterpret_cast<char*>(translator)+0x40)->~basic_string();
    for(unsigned int i=0;i<3;++i)reinterpret_cast<std::wstring*>(reinterpret_cast<char*>(themes[i])+0x28)->~basic_string();
}
void original(void* p,autotest::Capture& o) {side(*static_cast<Case*>(p),false,o);}
void recovered(void* p,autotest::Capture& o) {side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(base_unit_init_theme_data) {
    int failures=0;
    for(unsigned int seed=0;seed<192;++seed) {Case c={seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok)host->log("    init themes seed %u status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);}
    return failures;
}
