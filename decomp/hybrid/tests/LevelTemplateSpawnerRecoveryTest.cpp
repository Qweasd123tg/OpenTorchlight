#include <cstring>
#include <string>
#include <vector>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#include "LevelTemplateData.h"
#undef private
#include "ResourceManager.h"
#include "SpawnClass.h"
#include "SpawnClassData.h"
#include "Utilities.h"

TL_ORIGINAL(void, spawnerOwnerCtor, (CLevelTemplateData*, const wchar_t*), "_ZN18CLevelTemplateDataC1EPKw")
TL_ORIGINAL(void, spawnerOwnerDtor, (CLevelTemplateData*), "_ZN18CLevelTemplateDataD1Ev")
TL_ORIGINAL(void, chooseSpawnersOriginal, (CLevelTemplateData*, CResourceManager*), "_ZN18CLevelTemplateData18chooseUnitSpawnersEP16CResourceManager")
extern "C" void chooseSpawnersCandidate(CLevelTemplateData*, CResourceManager*) __asm__("_ZN18CLevelTemplateData18chooseUnitSpawnersEP16CResourceManager");
TL_FUNCTION(spawnerResourceLookup, "_ZN16CResourceManager19getSpawnClassByNameERKSbIwSt11char_traitsIwESaIwEE")

namespace {
struct Case { unsigned seed; bool negative; };
autotest::Capture* capture;
CResourceManager* resources;
CSpawnClass* classes[4];
unsigned lookups;
void number(unsigned value) { capture->add(&value, sizeof(value)); }
CSpawnClass* lookup(CResourceManager* owner, const std::wstring& name)
{
    if (owner != resources) capture->issue = autotest::Capture::InvalidReport;
    number(11); capture->addText(name); ++lookups;
    for (unsigned i = 0; i < 4; ++i) if (classes[i]->m_name == name) return classes[i];
    return NULL;
}
void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw); capture = &out; lookups = 0;
    union OwnerStorage { long double align; char bytes[sizeof(CLevelTemplateData)]; } ownerStorage;
    std::memset(ownerStorage.bytes, 0xa5, sizeof(ownerStorage.bytes));
    CLevelTemplateData* owner = reinterpret_cast<CLevelTemplateData*>(ownerStorage.bytes);
    spawnerOwnerCtor(owner, NULL);
    uint64_t resourceWitness[8] = {0}; resources = reinterpret_cast<CResourceManager*>(resourceWitness);
    const wchar_t* classNames[] = {L"class-a", L"class-Ж", L"class-c", L"class-d"};
    const wchar_t* resultNames[] = {L"", L"chosen-one", L"Ж中", L"a-long-selected-spawn-class-name", L"other", L"last"};
    CSpawnClass* nested[6];
    for (unsigned i = 0; i < 6; ++i) nested[i] = new CSpawnClass(resultNames[(i + c.seed) % 6]);
    union DataStorage { long double align; char bytes[sizeof(CSpawnClassData)]; } dataStorage[4][9];
    const unsigned counts[] = {1, 2, 6, 9};
    const int weights[] = {-2147483647 - 1, -99, -1, 0, 1, 7, 100, 1000000, 2147483647};
    for (unsigned k = 0; k < 4; ++k) {
        classes[k] = new CSpawnClass(classNames[k]);
        for (unsigned i = 0; i < counts[k]; ++i) {
            SpawnClassEntry* entry = new SpawnClassEntry;
            entry->data = new CSpawningData;
            int odds = weights[(i + k * 3 + c.seed) % 9];
            std::memcpy(reinterpret_cast<char*>(entry->data) + 0x10, &odds, 4);
            std::memset(dataStorage[k][i].bytes, 0, sizeof(CSpawnClassData));
            entry->spawnClassData = reinterpret_cast<CSpawnClassData*>(dataStorage[k][i].bytes);
            entry->spawnClassData->m_pSpawnClass = i == 0 || (i + c.seed + k) % 3 ? nested[(i + k) % 6] : NULL;
            classes[k]->m_entries.add(entry);
        }
    }
    for (unsigned i = 0; i < 11; ++i) {
        owner->m_useSpawnClass[i] = ((c.seed + i * 5) % 4) != 0;
        owner->m_unitSpawnerNames[i] = (i + c.seed) % 5 == 0 ? L"missing-class" : classNames[(i + c.seed) % 4];
        owner->m_selectedUnitSpawners[i] = (i + c.seed) % 2 ? L"old-selection" : L"";
    }
    detour::Set redirects; TL_REDIRECT(redirects, spawnerResourceLookup, &lookup);
    if (redirects.failed()) { out.issue = autotest::Capture::InvalidReport; return; }
    UTILITIES::setSeed(c.seed * 313 + 7);
    int countBefore = g_iTotalCountOfObjects;
    autotest::invoke(out, ours ? chooseSpawnersCandidate : chooseSpawnersOriginal, owner, resources);
    if (ours && c.negative) owner->m_selectedUnitSpawners[0] += L"!";
    number(lookups); number(g_iTotalCountOfObjects - countBefore);
    for (unsigned i = 0; i < 11; ++i) {
        number(owner->m_useSpawnClass[i]); out.addText(owner->m_unitSpawnerNames[i]); out.addText(owner->m_selectedUnitSpawners[i]);
    }
    for (unsigned k = 0; k < 4; ++k) {
        number(classes[k]->m_entries.size());
        for (unsigned i = 0; i < classes[k]->m_entries.size(); ++i) {
            int odds; std::memcpy(&odds, reinterpret_cast<char*>(classes[k]->m_entries[i]->data) + 0x10, 4);
            out.add(&odds, 4);
            CSpawnClass* chosen = classes[k]->m_entries[i]->spawnClassData->m_pSpawnClass;
            number(chosen != NULL); if (chosen) out.addText(chosen->m_name);
        }
    }
    for (unsigned i = 0; i < 4; ++i) { float next = UTILITIES::randomBetween(-1.0f, 1.0f); out.add(&next, 4); }
    for (unsigned k = 0; k < 4; ++k) delete classes[k];
    for (unsigned i = 0; i < 6; ++i) delete nested[i];
    spawnerOwnerDtor(owner);
}
void original(void* p, autotest::Capture& out) { side(p, out, false); }
void candidate(void* p, autotest::Capture& out) { side(p, out, true); }
}

TL_TEST(level_template_spawner_recovery)
{
    autotest::Coverage coverage("level_template_spawner_recovery", 0x974f80);
    for (unsigned seed = 0; seed < 144; ++seed) {
        Case c = {seed, false}; autotest::Outcome a, b;
        autotest::runChild(original, &c, a); autotest::runChild(candidate, &c, b);
        if (coverage.observe(host, a, b)) {
            host->log("    choose spawners seed %u status %d/%d issue %u/%u bytes %lu/%lu\n", seed, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue, (unsigned long)a.capture.length, (unsigned long)b.capture.length);
            coverage.report(host); return 1;
        }
    }
    coverage.report(host);
    Case negative = {7, true}; autotest::Outcome a, b;
    autotest::runChild(original, &negative, a); autotest::runChild(candidate, &negative, b);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    host->log("    choose spawners negative control detected %u\n", detected ? 1 : 0);
    return !detected || !a.reportValid || !b.reportValid || a.childStatus || b.childStatus || autotest::incomplete(a) || autotest::incomplete(b);
}
