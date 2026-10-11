// Shadow test: CStringTranslate::reload against the original machine code.
// The translation file comes from a fake CFileSystem whose data group cache
// holds prepared groups, so CDataGroup::LoadFile takes its cached path and
// never touches the disk.
#include <cstring>
#include <map>
#include <new>
#include <string>

#include "DataGroup.h"
#include "AutoTest.h"
#include "StringTranslate.h"

TL_ORIGINAL(void, originalConstruct, (void*, const std::wstring&),
            "_ZN16CStringTranslateC1ERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void, originalDestroy, (void*), "_ZN16CStringTranslateD1Ev")
TL_ORIGINAL(void, originalReload, (void*), "_ZN16CStringTranslate6reloadEv")

// DataGroup.cpp, StringUtilities.cpp and FileSystem code are not recovered:
// the tests use their original machine code to build the input.
TL_ORIGINAL(void, dataGroupConstruct,
            (void*, const std::wstring&, CDataGroup*, unsigned int, unsigned int, TRepository<std::wstring>*),
            "_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void, dataGroupDestroy, (void*), "_ZN10CDataGroupD1Ev")
TL_ORIGINAL(CDataGroup*, addDataGroup, (void*, const std::wstring&),
            "_ZN10CDataGroup12AddDataGroupERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void*, addDataValue, (void*, const std::wstring&, const std::wstring&, bool),
            "_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEES5_b")
TL_ORIGINAL(void, stringUpper, (std::wstring*, const std::wstring&),
            "_ZN7STRINGS11StringUpperERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void, cleanPath, (std::wstring*, const std::wstring&),
            "_ZN10FILESYSTEM9CleanPathERKSbIwSt11char_traitsIwESaIwEE")

class CFileSystem;
extern CFileSystem* g_pFileSystem;

extern "C" void candidateReload(void*) __asm__("_ZN16CStringTranslate6reloadEv");
namespace
{

typedef std::map<std::wstring, std::wstring> TranslationMap;
typedef std::map<std::wstring, CDataGroup*> GroupCache;

// CFileSystem::getDataGroup looks the cleaned upper-case path up in the map
// at +0x68.
const int kCacheOffset = 0x68;
const int kTranslationsOffset = 0x10;
const int kFileNameOffset = 0x40;
const int kLoadedOffset = 0x48;

char g_fakeFileSystem[0x200];

GroupCache& cache()
{
    return *reinterpret_cast<GroupCache*>(g_fakeFileSystem + kCacheOffset);
}

std::wstring cacheKey(const std::wstring& path)
{
    std::wstring upper;
    stringUpper(&upper, path);
    std::wstring clean;
    cleanPath(&clean, upper);
    return clean;
}

struct Entry
{
    const wchar_t* original;
    const wchar_t* translation;
};

const int kMaxGroups = 8;
char g_groups[kMaxGroups][sizeof(CDataGroup)];
int g_groupCount = 0;

// A cached file: one child group per entry; a null field leaves its value out.
void addFile(const wchar_t* path, const Entry* entries, int count, bool translatable)
{
    void* root = g_groups[g_groupCount++];
    dataGroupConstruct(root, std::wstring(), NULL, 20, 10, NULL);
    for (int i = 0; i < count; i++)
    {
        CDataGroup* child = addDataGroup(root, std::wstring(L"TEXT"));
        if (entries[i].original)
            addDataValue(child, std::wstring(L"ORIGINAL"), std::wstring(entries[i].original), translatable);
        if (entries[i].translation)
            addDataValue(child, std::wstring(L"TRANSLATION"), std::wstring(entries[i].translation), translatable);
    }
    cache()[cacheKey(path)] = static_cast<CDataGroup*>(root);
}

TranslationMap& translations(char* object)
{
    return *reinterpret_cast<TranslationMap*>(object + kTranslationsOffset);
}

std::wstring& fileName(char* object)
{
    return *reinterpret_cast<std::wstring*>(object + kFileNameOffset);
}

const Entry kMenu[] = {
    {L"New Game", L"Nouvelle partie"},
    {L"Options", L"Options"},
    {L"Quit", L"Quitter"},
    // A repeated ORIGINAL keeps the last TRANSLATION.
    {L"Options", L"Reglages"},
    {NULL, L"Sans original"},
    {L"Sans traduction", NULL},
    {L"Empty", L""},
};

// Read while the table is reloaded: every value asks the active table for its
// translation, which must stay off until the reload is finished.
const Entry kChain[] = {
    {L"One", L"Two"},
    {L"Two", L"Three"},
    {L"Three", L"One"},
    {L"Four", L"Two"},
};

} // namespace


namespace {
struct Case{unsigned seed;};
void side(Case&c,bool ours,autotest::Capture&out){
 char object[sizeof(CStringTranslate)];std::memset(object,(c.seed*31+3)&255,sizeof(object));
 g_groupCount=0;new(g_fakeFileSystem+kCacheOffset)GroupCache();g_pFileSystem=reinterpret_cast<CFileSystem*>(g_fakeFileSystem);
 addFile(L"media/menu.dat",kMenu,sizeof(kMenu)/sizeof(kMenu[0]),false);
 addFile(L"media/empty.dat",NULL,0,false);
 addFile(L"media/chain.dat",kChain,sizeof(kChain)/sizeof(kChain[0]),true);
 addFile(L"media/menu",kMenu,sizeof(kMenu)/sizeof(kMenu[0]),false);
 const wchar_t* sequence[]={L"media/menu.dat",L"media/menu",L"media/menu.dat",L"media/empty.dat",L"media/menu.dat",L"media/chain.dat",L"media/chain.dat",L"media/menu.dat"};
 m_gStringTranslate=NULL;originalConstruct(object,std::wstring(sequence[0]));
 for(unsigned step=0;step<(c.seed/8)%5;++step){fileName(object)=sequence[(step+c.seed)%8];originalReload(object);}
 translations(object)[L"Old key"]=(c.seed&1)?L"old value":L"";object[kLoadedOffset]=(c.seed/8)&1;fileName(object)=sequence[c.seed%8];m_gStringTranslate=reinterpret_cast<CStringTranslate*>(object);
 void(*fn)(void*)=ours?reinterpret_cast<void(*)(void*)>(&candidateReload):originalReload;
 if(!autotest::beginInvocation(out,fn))return;fn(object);out.callCompleted=1;
 unsigned count=translations(object).size();out.add(&count,4);for(TranslationMap::iterator i=translations(object).begin();i!=translations(object).end();++i){out.addText(i->first);out.addText(i->second);}out.addText(fileName(object));out.add(object+kLoadedOffset,sizeof(object)-kLoadedOffset);bool singleton=m_gStringTranslate==reinterpret_cast<CStringTranslate*>(object);out.add(&singleton,1);
 m_gStringTranslate=NULL;originalDestroy(object);for(int i=0;i<g_groupCount;++i)dataGroupDestroy(g_groups[i]);cache().~GroupCache();
}
void original(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(string_translate_reload_observed){autotest::Coverage coverage("string_translate_reload_observed",(uint64_t)(uintptr_t)originalReload);for(unsigned n=0;n<160;++n){Case c={n};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){host->log("    translation %u status %d/%d bytes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return 0;}
