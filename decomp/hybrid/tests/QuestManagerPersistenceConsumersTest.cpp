// Genuine original Quest serialization integration, NOT GameClient/world coverage.
// All objects below run original constructors. The isolated resource has no game
// clients: resetGameSeed is an explicit boundary double, never a fake client.
// Dungeon loading uses the original constructor/reload/lookup with a controlled
// empty file-list result. Quest save/load/reinitialize and dialog save/load are
// actual original bodies. Only manager load receives comparison credit.
#include <cstdio>
#include <cstring>
#include <map>
#include <new>
#include <string>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"

TL_ORIGINAL(void, qpcOldLoad, (void*, FILE*, unsigned, void*), "_ZN13CQuestManager4loadEP8_IO_FILEjP16CResourceManager")
extern "C" void qpcNewLoad(void*, FILE*, unsigned, void*) __asm__("_ZN13CQuestManager4loadEP8_IO_FILEjP16CResourceManager");
TL_ORIGINAL(void, qpcManagerCtor, (void*, void*), "_ZN13CQuestManagerC1EP16CResourceManager")
TL_ORIGINAL(void, qpcManagerDtor, (void*), "_ZN13CQuestManagerD1Ev")
TL_ORIGINAL(void, qpcResourceCtor, (void*, void*), "_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void, qpcResourceDtor, (void*), "_ZN16CResourceManagerD1Ev")
TL_ORIGINAL(void, qpcQuestCtor, (void*, void*, void*), "_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_ORIGINAL(void, qpcQuestDtor, (void*), "_ZN6CQuestD1Ev")
TL_ORIGINAL(void, qpcQuestSave, (void*, FILE*), "_ZN6CQuest4saveEP8_IO_FILE")
TL_ORIGINAL(void, qpcQuestLoad, (void*, FILE*, void*, unsigned), "_ZN6CQuest4loadEP8_IO_FILEP16CResourceManagerj")
TL_ORIGINAL(void, qpcDialogCtor, (void*, void*), "_ZN12CQuestDialogC1EP6CQuest")
TL_ORIGINAL(void, qpcDialogDtor, (void*), "_ZN12CQuestDialogD1Ev")
TL_ORIGINAL(void, qpcDungeonCtor, (void*, std::wstring), "_ZN15CDungeonManagerC1ESbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void, qpcDungeonDtor, (void*), "_ZN15CDungeonManagerD1Ev")
TL_ORIGINAL(void*, qpcMaster, (), "_ZN22CMasterResourceManager12getSingletonEv")
TL_ORIGINAL(void*, qpcLookup, (void*, const std::wstring&), "_ZN13CQuestManager14getQuestByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(bool, qpcActive, (void*, const std::wstring&), "_ZN13CQuestManager16getQuestIsActiveERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(char, qpcComplete, (void*, const std::wstring&), "_ZN13CQuestManager16getQuestCompleteERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qpcLoadBoundary, "_ZN6CQuest4loadEP8_IO_FILEP16CResourceManagerj")
TL_FUNCTION(qpcSeedBoundary, "_ZN11CGameClient13resetGameSeedEi")
TL_FUNCTION(qpcFilesBoundary, "_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")

namespace quest_persistence_consumers {
typedef std::wstring Wide;
typedef std::map<Wide, void*> QuestMap;
typedef std::map<Wide, bool> CompleteMap;
typedef char WideAbi[sizeof(Wide) == 8 ? 1 : -1];
typedef char MapAbi[sizeof(QuestMap) == 48 ? 1 : -1];
template<class T> T& at(void* p, unsigned offset) {
    return *reinterpret_cast<T*>(static_cast<char*>(p) + offset);
}
struct Case { unsigned version, name, duplicate; };
static const Case* current;
static autotest::Capture* capture;
static void *manager, *resource, *quest, *dungeon, *dialogs[4];
static unsigned errors, loadCalls, seedCalls, fileCalls;
static long payloadStart[2], payloadEnd[2];
static detour::Set* loadPatch;
static void number(unsigned n) { capture->add(&n, sizeof(n)); }
static void need(bool condition, unsigned site) {
    if (!condition) { ++errors; number(0xf1000000u + site); }
}
static void* storage(unsigned n) {
    void* p = autotest::allocate(n);
    if (!p) _exit(71);
    // Poison verifies that constructors, not a zeroed buffer, establish state.
    std::memset(p, 0xa5, n);
    return p;
}
static void put(std::vector<unsigned char>& bytes, unsigned value, unsigned width) {
    for (unsigned i = 0; i < width; ++i) {
        bytes.push_back(static_cast<unsigned char>(value)); value >>= 8;
    }
}
static void putName(std::vector<unsigned char>& bytes, const Wide& name) {
    put(bytes, name.size(), 2);
    for (unsigned i = 0; i < name.size(); ++i) put(bytes, name[i], 2);
}
static Wide name() {
    if (current->name == 0) return Wide(L"original quest");
    if (current->name == 1) return Wide();
    const wchar_t text[] = {L'Q', 0, L'\u0416', L'\u732b'};
    return Wide(text, 4);
}
static unsigned emptyFiles(void*, const Wide& path, void* list, Wide,
                       bool recursive, bool flag, bool third, bool fourth) {
    ++fileCalls;
    need(path == L"QUEST_PERSISTENCE_ISOLATED/", 1);
    need(at<unsigned>(list, 8) == 0 && !at<void*>(list, 0), 2);
    need(recursive && flag && !third && !fourth, 3);
    // Keep the actual caller-created, empty TArrayList untouched.
    return 0;
}
static void noGameClientSeed(void* client, int depth) {
    // Original CResourceManager has a genuinely empty client collection.
    need(!client && at<unsigned>(resource, 0x30) == 0, 4);
    need(depth == 7 + static_cast<int>(loadCalls), 5);
    ++seedCalls;
}
static void observedQuestLoad(void* self, FILE* file, void* forwarded, unsigned version) {
    unsigned index = loadCalls++;
    need(index < 2 && self == quest && forwarded == resource, 6);
    need(version == current->version, 7);
    need(at<unsigned>(manager, 0x20) == index, 8);
    if (index < 2) need(std::ftell(file) == payloadStart[index], 9);
    loadPatch->restore();
    qpcQuestLoad(self, file, forwarded, version); // Entire ORIGINAL entry/body.
    TL_REDIRECT(*loadPatch, qpcLoadBoundary, &observedQuestLoad);
    need(!loadPatch->failed(), 10);
    if (index < 2) need(std::ftell(file) == payloadEnd[index], 11);
    need(at<bool>(quest, 0x26), 12);
}
static void configurePayload(unsigned index) {
    at<int>(quest, 0x1c) = 1337 + index;
    at<int>(quest, 0x20) = 8 + index;
    at<int>(quest, 0x20c) = 5 + index;
    for (unsigned i = 0; i < 4; ++i) {
        at<bool>(dialogs[i], 0x76) = ((i + index) & 1) != 0;
        at<bool>(dialogs[i], 0x77) = ((i + index) & 2) != 0;
    }
}
static std::vector<unsigned char> originalPayload(unsigned index) {
    configurePayload(index);
    FILE* file = std::tmpfile();
    if (!file) _exit(71);
    qpcQuestSave(quest, file);
    need(std::ftell(file) == 56 && !std::ferror(file), 13);
    std::rewind(file);
    std::vector<unsigned char> bytes(56);
    need(std::fread(&bytes[0], 1, bytes.size(), file) == bytes.size(), 14);
    need(std::fclose(file) == 0, 15);
    // Independent layout oracle from d16bb0 and d1df00, not manager save.
    std::vector<unsigned char> expected;
    put(expected, ~0u, 4); put(expected, ~0u, 4); // absent data-group GUID
    put(expected, 1337 + index, 4); put(expected, 8 + index, 4);
    put(expected, 5 + index, 4);
    for (unsigned i = 0; i < 4; ++i) {
        put(expected, 1, 4);
        put(expected, ((i + index) & 1) != 0, 1);
        put(expected, ((i + index) & 2) != 0, 1);
    }
    for (unsigned i = 0; i < 3; ++i) put(expected, 0, 4);
    need(bytes == expected, 16);
    // Legacy Quest payload has no +20c word. All other bytes are original output.
    if (current->version <= 19) bytes.erase(bytes.begin() + 16, bytes.begin() + 20);
    return bytes;
}
static bool good(const autotest::Capture& out) {
    unsigned footer[2];
    if (out.length < sizeof(footer)) return false;
    std::memcpy(footer, out.data + out.length - sizeof(footer), sizeof(footer));
    return footer[0] == 0x51504349u && footer[1] == 0;
}
static void side(void* context, autotest::Capture& out, bool candidate) {
    current = static_cast<Case*>(context); capture = &out;
    errors = loadCalls = seedCalls = fileCalls = 0;
    autotest::g_arenaUsed = 0;
    // The harness runs before game static constructors. Initialize only the two
    // original TU empty-string cells used by the original object constructors.
    new(reinterpret_cast<void*>(0x14f9fe8)) Wide();
    new(reinterpret_cast<void*>(0x14fb488)) Wide();
    if (qpcMaster()) { out.issue = autotest::Capture::InvalidReport; return; }
    resource = storage(0x48); qpcResourceCtor(resource, 0);
    need(!at<void*>(resource, 0x28) && at<unsigned>(resource, 0x30) == 0, 17);

    // Reserve this isolated singleton slot before C1. Its original secondary-
    // manager branch constructs every map/list without loading quests or sound.
    // It only checks the slot for nonnull, never dereferences an unbuilt object.
    void*& singleton = *reinterpret_cast<void**>(0x14fc6e0);
    void* savedManager = singleton;
    manager = storage(0xd0); singleton = manager;
    qpcManagerCtor(manager, resource); at<void*>(manager, 0x30) = 0;
    quest = storage(0x218); qpcQuestCtor(quest, resource, manager);
    at<Wide>(quest, 0x50) = name();
    // A loaded empty quest definition requests zero random groups. The ctor's
    // default min=1 cannot be used with an empty definition during reinitialize.
    at<int>(quest, 0x1a8) = 0;
    static const unsigned dialogOffsets[] = {0x60, 0x78, 0x90, 0xa8};
    for (unsigned i = 0; i < 4; ++i) {
        dialogs[i] = storage(0xa8); qpcDialogCtor(dialogs[i], quest);
        void** entries = new void*[1]; entries[0] = dialogs[i];
        at<void*>(quest, dialogOffsets[i]) = entries;
        at<unsigned>(quest, dialogOffsets[i] + 8) = 1;
        at<unsigned>(quest, dialogOffsets[i] + 12) = 1;
    }
    at<QuestMap>(manager, 0x40).insert(QuestMap::value_type(name(), quest));
    at<CompleteMap>(manager, 0x70).insert(CompleteMap::value_type(name(), true));

    detour::Set environment;
    TL_REDIRECT(environment, qpcFilesBoundary, &emptyFiles);
    TL_REDIRECT(environment, qpcSeedBoundary, &noGameClientSeed);
    if (environment.failed()) { out.issue = autotest::Capture::InvalidReport; return; }
    void* savedDungeon = *reinterpret_cast<void**>(0x151f650);
    dungeon = storage(0x30);
    qpcDungeonCtor(dungeon, Wide(L"quest_persistence_isolated/"));
    need(fileCalls == 1 && at<unsigned>(dungeon, 0x20) == 0, 18);

    const unsigned records = current->duplicate ? 2 : 1;
    std::vector<unsigned char> input(5, 0x5a);
    put(input, 1, 4); putName(input, name()); put(input, records, 4);
    for (unsigned i = 0; i < records; ++i) {
        std::vector<unsigned char> bytes = originalPayload(i);
        // Deliberately inconsistent known-record end: actual Quest consumption
        // determines the next record, never this missing-record skip target.
        put(input, 0x12345678u, 4); putName(input, name());
        payloadStart[i] = input.size();
        input.insert(input.end(), bytes.begin(), bytes.end());
        payloadEnd[i] = input.size();
    }
    unsigned finalPosition = input.size();
    put(input, 0xc0decafeu, 4);
    FILE* file = std::tmpfile(); if (!file) _exit(71);
    need(std::fwrite(&input[0], 1, input.size(), file) == input.size(), 19);
    need(std::fseek(file, 5, SEEK_SET) == 0, 20);
    at<int>(quest, 0x1c) = -1; at<int>(quest, 0x20) = -1;
    at<int>(quest, 0x20c) = 999;
    at<bool>(quest, 0x24) = true; at<bool>(quest, 0x26) = false;
    for (unsigned i = 0; i < 4; ++i) {
        at<bool>(dialogs[i], 0x76) = true; at<bool>(dialogs[i], 0x77) = true;
    }
    // Reach/reset real pre-existing storage, then allow the manager's real
    // append to allocate its own list. No prefilled capacity survives reset.
    void** oldActive = new void*[2]; oldActive[0] = quest; oldActive[1] = quest;
    at<void*>(manager, 0x18) = oldActive;
    at<unsigned>(manager, 0x20) = at<unsigned>(manager, 0x24) = 2;
    detour::Set observation; loadPatch = &observation;
    TL_REDIRECT(observation, qpcLoadBoundary, &observedQuestLoad);
    if (observation.failed()) { out.issue = autotest::Capture::InvalidReport; return; }
    typedef void (*Load)(void*, FILE*, unsigned, void*);
    Load invoked = candidate ? &qpcNewLoad : &qpcOldLoad;
    if (!autotest::beginInvocation(out, invoked)) return;
    invoked(manager, file, current->version, resource);
    out.callCompleted = 1;
    observation.restore();
    need(loadCalls == records && seedCalls == records, 21);
    need(std::ftell(file) == static_cast<long>(finalPosition) && !std::ferror(file), 22);
    unsigned sentinel = 0;
    need(std::fread(&sentinel, 4, 1, file) == 1 && sentinel == 0xc0decafeu, 23);
    need(std::fclose(file) == 0, 24);
    need(at<unsigned>(manager, 0x20) == records && at<unsigned>(manager, 0x24) == 10, 25);
    for (unsigned i = 0; i < records; ++i) need(at<void**>(manager, 0x18)[i] == quest, 26);
    need(at<int>(quest, 0x1c) == static_cast<int>(1336 + records), 27);
    need(at<int>(quest, 0x20) == static_cast<int>(7 + records), 28);
    need(at<int>(quest, 0x20c) == (current->version <= 19 ? 999 : static_cast<int>(4 + records)), 29);
    need(at<bool>(quest, 0x26) && !at<bool>(quest, 0x24), 30);
    need(at<void*>(quest, 0x1d8) == resource && !at<void*>(quest, 0x1e8), 31);
    need(qpcLookup(manager, name()) == quest && qpcActive(manager, name()) && qpcComplete(manager, name()), 32);
    for (unsigned i = 0; i < 4; ++i) {
        bool first = ((i + records - 1) & 1) != 0;
        bool second = ((i + records - 1) & 2) != 0;
        need(at<bool>(dialogs[i], 0x76) == first && at<bool>(dialogs[i], 0x77) == second, 33);
        number(at<bool>(dialogs[i], 0x76)); number(at<bool>(dialogs[i], 0x77));
    }
    number(finalPosition); number(records); number(loadCalls); number(seedCalls);
    number(at<unsigned>(manager, 0x24)); number(at<int>(quest, 0x1c));
    number(at<int>(quest, 0x20)); number(at<int>(quest, 0x20c));
    // Detach arena-backed dialogs before original deleting ownership paths.
    for (unsigned i = 0; i < 4; ++i) {
        delete[] at<void**>(quest, dialogOffsets[i]);
        at<void*>(quest, dialogOffsets[i]) = 0;
        at<unsigned>(quest, dialogOffsets[i] + 8) = 0;
        at<unsigned>(quest, dialogOffsets[i] + 12) = 0;
        qpcDialogDtor(dialogs[i]);
    }
    at<QuestMap>(manager, 0x40).clear();
    qpcQuestDtor(quest); qpcManagerDtor(manager); singleton = savedManager;
    qpcDungeonDtor(dungeon); *reinterpret_cast<void**>(0x151f650) = savedDungeon;
    qpcResourceDtor(resource);
    number(0x51504349u); number(errors);
}
static void original(void* c, autotest::Capture& out) { side(c, out, false); }
static void candidate(void* c, autotest::Capture& out) { side(c, out, true); }
}

TL_TEST(questmanager_persistence_original_quest_integration) {
    using namespace quest_persistence_consumers;
    autotest::Coverage coverage("questmanager_persistence_original_quest_integration", 0xd2f8a0);
    const unsigned versions[] = {19, 20, 21, ~0u};
    unsigned completed = 0;
    for (unsigned v = 0; v < 4; ++v) for (unsigned n = 0; n < 3; ++n)
    for (unsigned d = 0; d < 2; ++d) {
        Case c = {versions[v], n, d};
        autotest::Outcome a, b;
        autotest::runChild(original, &c, a); autotest::runChild(candidate, &c, b);
        ++completed;
        if (coverage.observe(host, a, b) || !good(a.capture) || !good(b.capture)) {
            host->log(" original Quest integration version=%u name=%u duplicate=%u oracle=%u/%u status=%d/%d\n",
                      c.version, n, d, good(a.capture), good(b.capture), a.childStatus, b.childStatus);
            coverage.report(host); return 1;
        }
    }
    coverage.report(host);
    host->log(" actual original Quest save/load/dialogs; seed and empty filesystem boundaries controlled; GameClient/world callers NOT executed\n");
    return coverage.completed != completed || coverage.different || coverage.missing;
}
