#include "AutoTest.h"
#include "SystemsFixtureWorker.h"
#include "Achievement.h"
#include "Achievements.h"
#include "DataGroup.h"
#include "Dungeon.h"
#include "FileSystem.h"
#include "LevelTemplateData.h"
#include "Mod.h"
#include "ModFileFilter.h"
#include "SafePointer.h"
#include "SteamStats.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iterator>
#include <malloc.h>
#include <new>
#include <string>
#include <unistd.h>

TL_ORIGINAL(void, oldAchievementsDtor, (CAchievements*), "_ZN13CAchievementsD1Ev")
TL_ORIGINAL(void, oldModFilterDtor, (CModFileFilter*), "_ZN14CModFileFilterD1Ev")
TL_ORIGINAL(bool, oldModSave, (CModFileFilter*, bool), "_ZN14CModFileFilter11saveModFileEb")
TL_ORIGINAL(void, oldDungeonDtor, (CDungeon*), "_ZN8CDungeonD1Ev")
extern "C" void newAchievementsDtor(CAchievements*) __asm__("_ZN13CAchievementsD1Ev");
extern "C" void newModFilterDtor(CModFileFilter*) __asm__("_ZN14CModFileFilterD1Ev");
extern "C" bool newModSave(CModFileFilter*, bool) __asm__("_ZN14CModFileFilter11saveModFileEb");
extern "C" void newDungeonDtor(CDungeon*) __asm__("_ZN8CDungeonD1Ev");
extern "C" char modVtable[] __asm__("_ZTV4CMod");
namespace LinuxUtils {
extern std::wstring gameHomePath __asm__("_ZN10LinuxUtilsL12gameHomePathE");
}

namespace {
struct Case { unsigned index, operation; bool negative; };
char root[] = "/tmp/opencode/otl-owner-cleanup-XXXXXX";
const unsigned counts[] = {0, 1, 2, 7, 19};
void number(autotest::Capture& out, long long value) { out.add(&value, sizeof(value)); }

template<class T> union Storage {
    long double alignment;
    unsigned char bytes[sizeof(T)];
};

void achievements(Case& c, bool ours, autotest::Capture& out)
{
    Storage<CAchievements> storage;
    CAchievements* owner = reinterpret_cast<CAchievements*>(storage.bytes);
    std::memset(owner, 0, sizeof(*owner));
    new (static_cast<CRunicCore*>(owner)) CRunicCore;
    new (&owner->m_completedAchievements) TArrayList<CAchievement*>(2);
    new (&owner->m_achievements) TArrayList<CAchievement*>(3);
    new (&owner->m_achievementsById) std::map<EACHIEVEMENTS, CAchievement*>;
    TSafePointer<CRunicCore> weak[24];
    TSafePointer<CRunicCore> self;
    self.setObject(owner);
    unsigned count = counts[c.index % 5];
    for (unsigned i = 0; i < count; ++i) {
        CAchievement* item = NULL;
        if ((i + c.index) % 4) {
            item = new CAchievement(std::string(80, char('a' + i)),
                static_cast<ESTATS>(i % 31), int(i), int(i + 10));
            weak[i].setObject(item);
        }
        owner->m_achievements.add(item);
        owner->m_achievementsById[static_cast<EACHIEVEMENTS>(i)] = item;
        if (i % 2) owner->m_completedAchievements.add(item);
    }
    CAchievement* borrowed = new CAchievement("borrowed achievement",
        static_cast<ESTATS>(0), 0, 1);
    TSafePointer<CRunicCore> borrowedWeak;
    borrowedWeak.setObject(borrowed);
    owner->m_completedAchievements.add(borrowed);
    owner->m_achievementsById[static_cast<EACHIEVEMENTS>(1000)] = borrowed;
    m_gAchievementsObject = owner;
    typedef void (*Function)(CAchievements*);
    Function function = ours ? newAchievementsDtor : oldAchievementsDtor;
    if (!autotest::beginInvocation(out, function)) return;
    function(owner);
    out.callCompleted = 1;
    if (c.negative && ours) m_gAchievementsObject = owner;
    number(out, m_gAchievementsObject == NULL);
    number(out, self.getObject() == NULL);
    for (unsigned i = 0; i < count; ++i) number(out, weak[i].getObject() == NULL);
    number(out, borrowedWeak.getObject() == borrowed);
    delete borrowed;
    out.addHeapInUse();
}

CMod* mod(unsigned i, const std::wstring& shared)
{
    CMod* item = static_cast<CMod*>(CMod::operator new(sizeof(CMod)));
    new (static_cast<CRunicCore*>(item)) CRunicCore;
    new (&item->m_sUnknown10) std::string(60, char('A' + i));
    new (&item->m_mapModFiles) std::map<std::wstring, std::wstring>;
    new (&item->m_sUnknown48) std::string("fixture group");
    new (&item->m_wUnknown50) std::wstring(shared);
    new (&item->m_wUnknown58) std::wstring(shared);
    new (&item->m_wUnknown60) std::wstring(shared);
    new (&item->m_wUnknown68) std::wstring(shared);
    item->m_mapModFiles[L"one.mesh"] = shared;
    item->m_mapModFiles[L"two.mesh"] = shared;
    item->m_bUnknown70 = (i % 3 != 0);
    item->m_bUnknown71 = (i % 2 != 0);
    item->m_iUnknown74 = (i % 3 == 0) ? -1 : int(i);
    const void* vtable = modVtable + 16;
    std::memcpy(item, &vtable, sizeof(vtable));
    return item;
}

void mods(Case& c, bool ours, autotest::Capture& out)
{
    Storage<CModFileFilter> storage;
    CModFileFilter* owner = reinterpret_cast<CModFileFilter*>(storage.bytes);
    std::memset(owner, 0, sizeof(*owner));
    new (static_cast<CRunicCore*>(owner)) CRunicCore;
    std::wstring path(root, root + std::strlen(root));
    path += L"/";
    new (storage.bytes + 0x10) std::wstring(path);
    TArrayList<CMod*>* items = new (storage.bytes + 0x18) TArrayList<CMod*>(3);
    storage.bytes[0x30] = (c.index / 5) % 2;
    const std::string saved = std::string(root) + "/mods.dat";
    unlink(saved.c_str());
    std::wstring shared(128, L'X');
    TSafePointer<CRunicCore> weak[24];
    TSafePointer<CRunicCore> self;
    self.setObject(owner);
    unsigned count = counts[c.index % 5];
    for (unsigned i = 0; i < count; ++i) {
        CMod* item = mod(i, shared);
        weak[i].setObject(item);
        items->add(item);
    }
    g_pModFileFilter = owner;
    const int objectsBefore = g_iTotalCountOfObjects;
    if (c.operation == 3) {
        typedef bool (*Function)(CModFileFilter*, bool);
        Function function = ours ? newModSave : oldModSave;
        if (!autotest::beginInvocation(out, function)) return;
        number(out, function(owner, (c.index / 10) % 2));
        number(out, items->size());
        number(out, storage.bytes[0x30]);
    } else {
        typedef void (*Function)(CModFileFilter*);
        Function function = ours ? newModFilterDtor : oldModFilterDtor;
        if (!autotest::beginInvocation(out, function)) return;
        function(owner);
    }
    out.callCompleted = 1;
    number(out, g_iTotalCountOfObjects - objectsBefore);
    if (c.negative && ours) g_pModFileFilter = c.operation == 3 ? NULL : owner;
    number(out, g_pModFileFilter == NULL);
    number(out, self.getObject() == NULL);
    for (unsigned i = 0; i < count; ++i) number(out, weak[i].getObject() == NULL);
    std::ifstream file(saved.c_str(), std::ios::binary);
    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    number(out, text.size());
    out.add(text.data(), text.size());
    file.close();
    if (c.operation == 3) oldModFilterDtor(owner);
    // Coalesce freed string temporaries before comparing live allocations.
    malloc_trim(0);
    out.addHeapInUse();
    unlink(saved.c_str());
}

void dungeon(Case& c, bool ours, autotest::Capture& out)
{
    Storage<CDungeon> storage;
    CDungeon* owner = new (storage.bytes) CDungeon;
    std::wstring shared(128, L'Y');
    owner->m_sName = owner->m_sDisplayName = owner->m_sParentDungeon = shared;
    unsigned count = counts[c.index % 5];
    TSafePointer<CRunicCore> weak[24];
    TSafePointer<CRunicCore> self;
    self.setObject(owner);
    for (unsigned i = 0; i < count; ++i) {
        CLevelTemplateData* item = NULL;
        if ((i + c.index) % 3) {
            item = new CLevelTemplateData(NULL);
            weak[i].setObject(item);
        }
        owner->m_levelTemplateData.add(item);
        owner->m_randomizer.addChoice(i, i + 1);
        TArrayList<std::wstring>* names = NULL;
        if ((i + c.index) % 4) {
            names = new TArrayList<std::wstring>(2);
            for (unsigned j = 0; j < (i % 7); ++j) names->add(shared);
        }
        owner->m_mustBeCompleted.add(names);
        names = new TArrayList<std::wstring>(3);
        for (unsigned j = 0; j < (i % 5); ++j) names->add(shared);
        owner->m_mustBeCompletedOrActive.add(names);
    }
    CDataGroup* borrowed = new CDataGroup(L"borrowed", NULL, 3, 2, NULL);
    TSafePointer<CRunicCore> borrowedWeak, dataWeak;
    borrowedWeak.setObject(borrowed);
    owner->m_strataData.add(borrowed);
    if (c.index % 2) {
        owner->m_pDungeonData = new CDataGroup(L"dungeon", NULL, 3, 2, NULL);
        owner->m_pDungeonData->AddDataGroup(L"strata");
        owner->m_strataData.add(owner->m_pDungeonData);
        dataWeak.setObject(owner->m_pDungeonData);
    }
    typedef void (*Function)(CDungeon*);
    Function function = ours ? newDungeonDtor : oldDungeonDtor;
    if (!autotest::beginInvocation(out, function)) return;
    function(owner);
    out.callCompleted = 1;
    number(out, c.negative && ours ? false : self.getObject() == NULL);
    for (unsigned i = 0; i < count; ++i) number(out, weak[i].getObject() == NULL);
    number(out, dataWeak.getObject() == NULL);
    number(out, borrowedWeak.getObject() == borrowed);
    delete borrowed;
    out.addHeapInUse();
}

void side(void* context, bool ours, autotest::Capture& out)
{
    Case& c = *static_cast<Case*>(context);
    if (c.operation == 0) achievements(c, ours, out);
    if (c.operation == 1 || c.operation == 3) mods(c, ours, out);
    if (c.operation == 2) dungeon(c, ours, out);
}
void before(void* c, autotest::Capture& out) { side(c, false, out); }
void after(void* c, autotest::Capture& out) { side(c, true, out); }
unsigned operation;
int worker(const tlhybrid_host* host)
{
    if (!mkdtemp(root)) return 1;
    LinuxUtils::gameHomePath.assign(root, root + std::strlen(root));
    LinuxUtils::gameHomePath += L"/";
    new CSteamStats;
    if (operation == 1 || operation == 3) {
        // The native C1's registered-owner branch constructs all members but
        // deliberately skips application/resource loading (FileSystem.cpp).
        void* value = NULL;
        std::memcpy(&value, reinterpret_cast<void*>(0x1528e40), sizeof(value));
        if (!value) new (reinterpret_cast<void*>(0x1528e40)) std::string;
        std::memcpy(&value, reinterpret_cast<void*>(0x1528e48), sizeof(value));
        if (!value) new (reinterpret_cast<void*>(0x1528e48)) std::wstring;
        void* memory = CFileSystem::operator new(sizeof(CFileSystem));
        g_pFileSystem = static_cast<CFileSystem*>(memory);
        new (memory) CFileSystem(false);
        // Populate first-use serialization/repository caches before forking.
        Storage<CModFileFilter> storage;
        CModFileFilter* owner = reinterpret_cast<CModFileFilter*>(storage.bytes);
        new (static_cast<CRunicCore*>(owner)) CRunicCore;
        std::wstring directory(root, root + std::strlen(root));
        directory += L"/";
        new (storage.bytes + 0x10) std::wstring(directory);
        TArrayList<CMod*>* items = new (storage.bytes + 0x18) TArrayList<CMod*>(3);
        std::wstring shared(128, L'X');
        for (unsigned i = 0; i < 19; ++i) items->add(mod(i, shared));
        storage.bytes[0x30] = true;
        g_pModFileFilter = owner;
        oldModSave(owner, true);
        newModSave(owner, true);
        storage.bytes[0x30] = false;
        oldModFilterDtor(owner);
        unlink((std::string(root) + "/mods.dat").c_str());
    }
    const char* names[] = {"owner_cleanup_achievements", "owner_cleanup_mods", "owner_cleanup_dungeon", "owner_mod_save"};
    const uintptr_t targets[] = {0xec65a0, 0xc844a0, 0x934190, 0xc83c80};
    autotest::Coverage coverage(names[operation], targets[operation]);
    int failures = 0;
    for (unsigned i = 0; i < 40; ++i) {
        Case c = {i, operation, false};
        autotest::Outcome a, b;
        autotest::runChild(before, &c, a, 2000, 10000);
        autotest::runChild(after, &c, b, 2000, 10000);
        if (coverage.observe(host, a, b)) {
            host->log("    owner cleanup seed%u op%u status%d/%d issue%u/%u bytes%lu/%lu\n",
                i, operation, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue,
                (unsigned long)a.capture.length, (unsigned long)b.capture.length);
            for (size_t offset = 0; offset < a.capture.length && offset < b.capture.length; ++offset) {
                if (a.capture.data[offset] != b.capture.data[offset]) {
                    host->log("    first mismatch at %lu: %u/%u\n", (unsigned long)offset,
                        unsigned(static_cast<unsigned char>(a.capture.data[offset])),
                        unsigned(static_cast<unsigned char>(b.capture.data[offset])));
                    break;
                }
            }
            ++failures;
            break;
        }
    }
    coverage.report(host);
    Case negative = {7, operation, true};
    autotest::Outcome a, b;
    autotest::runChild(before, &negative, a, 2000, 10000);
    autotest::runChild(after, &negative, b, 2000, 10000);
    bool detected = a.capture.length != b.capture.length ||
        std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    TL_CHECK(failures, detected && !autotest::incomplete(a) && !autotest::incomplete(b) &&
        a.reportValid && b.reportValid && !a.childStatus && !b.childStatus);
    const std::string saved = std::string(root) + "/mods.dat";
    unlink(saved.c_str());
    rmdir(root);
    return failures + (coverage.completed != 40);
}
}

TL_TEST(owner_cleanup_achievements) { operation = 0; return systems_fixture::isolated(worker, host); }
TL_TEST(owner_cleanup_mods) { operation = 1; return systems_fixture::isolated(worker, host); }
TL_TEST(owner_cleanup_dungeon) { operation = 2; return systems_fixture::isolated(worker, host); }
TL_TEST(owner_mod_save) { operation = 3; return systems_fixture::isolated(worker, host); }
