// Shadow test: CStringTranslate::reload against the original machine code.
// The translation file comes from a fake CFileSystem whose data group cache
// holds prepared groups, so CDataGroup::LoadFile takes its cached path and
// never touches the disk.
#include <cstring>
#include <map>
#include <new>
#include <string>

#include "DataGroup.h"
#include "HybridTest.h"
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

bool sameState(char* a, char* b)
{
    return translations(a) == translations(b) && fileName(a) == fileName(b) &&
           a[kLoadedOffset] == b[kLoadedOffset];
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

TL_TEST(StringTranslate_reload)
{
    int failures = 0;
    static char a[sizeof(CStringTranslate)];
    static char b[sizeof(CStringTranslate)];
    TL_CHECK(failures, sizeof(CStringTranslate) == 0x50);
    TL_CHECK(failures, sizeof(CDataGroup) == 0x60);

    CFileSystem* savedFileSystem = g_pFileSystem;
    CStringTranslate* savedSingleton = m_gStringTranslate;
    new (g_fakeFileSystem + kCacheOffset) GroupCache();
    g_pFileSystem = reinterpret_cast<CFileSystem*>(g_fakeFileSystem);

    addFile(L"media/menu.dat", kMenu, sizeof(kMenu) / sizeof(kMenu[0]), false);
    addFile(L"media/empty.dat", NULL, 0, false);
    addFile(L"media/chain.dat", kChain, sizeof(kChain) / sizeof(kChain[0]), true);
    // Found in the cache, but a name without a dot is never loaded.
    addFile(L"media/menu", kMenu, sizeof(kMenu) / sizeof(kMenu[0]), false);

    const wchar_t* sequence[] = {
        L"media/menu.dat", L"media/menu", L"media/menu.dat", L"media/empty.dat",
        L"media/menu.dat", L"media/chain.dat", L"media/chain.dat", L"media/menu.dat",
    };
    const int steps = sizeof(sequence) / sizeof(sequence[0]);

    m_gStringTranslate = NULL;
    originalConstruct(a, std::wstring(sequence[0]));
    m_gStringTranslate = NULL;
    CStringTranslate* ours = new (b) CStringTranslate(std::wstring(sequence[0]));
    TL_CHECK(failures, sameState(a, b));
    TL_CHECK(failures, translations(a).size() == 6);

    for (int step = 1; step < steps && failures == 0; step++)
    {
        fileName(a) = sequence[step];
        fileName(b) = sequence[step];
        // Each side is the active table while it reloads.
        m_gStringTranslate = reinterpret_cast<CStringTranslate*>(a);
        originalReload(a);
        m_gStringTranslate = ours;
        ours->reload();
        TL_CHECK(failures, sameState(a, b));
        if (failures)
            host->log("    step %d: %u vs %u entries, loaded %d vs %d\n", step,
                      unsigned(translations(a).size()), unsigned(translations(b).size()), a[kLoadedOffset],
                      b[kLoadedOffset]);
    }

    m_gStringTranslate = NULL;
    originalDestroy(a);
    ours->~CStringTranslate();
    for (int i = 0; i < g_groupCount; i++)
        dataGroupDestroy(g_groups[i]);
    cache().~GroupCache();
    g_pFileSystem = savedFileSystem;
    m_gStringTranslate = savedSingleton;
    return failures;
}
