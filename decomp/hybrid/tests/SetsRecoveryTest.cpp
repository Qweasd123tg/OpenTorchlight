#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <malloc.h>
#include <map>
#include <new>
#include <string>
#include <vector>
#include "tests/NativeGameServices.h"
#include "SystemsFixtureWorker.h"
#include "Affix.h"
#include "DataGroup.h"
#include "EffectGroupManager.h"
#include "FileSystem.h"
#include "SafePointer.h"
#include "Set.h"
#include "Sets.h"
#include "StringUtilities.h"

TL_ORIGINAL(void, oldSetLoad, (CSet*, CDataGroup*, CEffectGroupManager*),
    "_ZN4CSet4loadEP10CDataGroupP19CEffectGroupManager")
TL_ORIGINAL(void, oldSetsReload, (CSets*, CEffectGroupManager*), "_ZN5CSets6reloadEP19CEffectGroupManager")
TL_ORIGINAL(void, oldSetsDtor, (CSets*), "_ZN5CSetsD1Ev")
extern "C" void newSetLoad(CSet*, CDataGroup*, CEffectGroupManager*)
    __asm__("_ZN4CSet4loadEP10CDataGroupP19CEffectGroupManager");
extern "C" void newSetsReload(CSets*, CEffectGroupManager*) __asm__("_ZN5CSets6reloadEP19CEffectGroupManager");
extern "C" void newSetsDtor(CSets*) __asm__("_ZN5CSetsD1Ev");
extern "C" char setsVtable[] __asm__("_ZTV5CSets");
// TU-private singleton of the original Sets.cpp (0x1520ae0).
extern "C" void* nativeSetsSingleton __asm__("_ZL7g_pSets");

namespace {
struct Case { unsigned index, operation; bool negative; };
CEffectGroupManager* manager;
TArrayList<std::wstring>* gameSetFiles;
std::vector<std::wstring>* affixNames;
const wchar_t* const kPaths[] = {L"media/sets/", L"", L"media/nosuchsets/", L"MEDIA/SETS"};

template<class T> union Storage {
    long double alignment;
    unsigned char bytes[sizeof(T)];
};

void number(autotest::Capture& out, long long value) { out.add(&value, sizeof(value)); }

std::wstring decimal(unsigned value) { return STRINGS::GetValueAsWString(int(value)); }

std::wstring affixName(unsigned i) { return (*affixNames)[i % affixNames->size()]; }

// One synthetic set; k selects every optional key and AFFIX block shape.
void buildSet(CDataGroup& group, unsigned k)
{
    if (k % 5 != 0) group.AddDataValue(L"NAME", (L"Set" + decimal(k % 11)).c_str(), false);
    if (k % 3 != 0) group.AddDataValue(L"DISPLAYNAME", (L"Display \x0416 " + decimal(k)).c_str(), false);
    if (k % 2) group.AddDataGroup(L"OTHER")->AddDataValue(L"AFFIX", affixName(k).c_str(), false);
    unsigned blocks = k % 13;
    for (unsigned j = 0; j < blocks; ++j) {
        CDataGroup* affix = group.AddDataGroup(L"AFFIX");
        unsigned shape = (k + j) % 7;
        if (shape == 1) affix->AddDataValue(L"AFFIX", L"MISSING_SET_AFFIX", false);
        else if (shape == 2) affix->AddDataValue(L"AFFIX", STRINGS::StringLower(affixName(k * 3 + j)).c_str(), false);
        else if (shape != 3) affix->AddDataValue(L"AFFIX", affixName(k * 3 + j).c_str(), false);
        if ((k + j) % 2) affix->AddDataValue(L"COUNT", int((k + j) % 6));
        if ((k + j) % 3 != 1) affix->AddDataValue(L"AFFIXLEVEL", int((k * 7 + j) % 23));
    }
}

void fillGroup(CDataGroup& group, unsigned k)
{
    if (k % 2 == 0 && gameSetFiles->size()) group.LoadFile((*gameSetFiles)[(k / 2) % gameSetFiles->size()], NULL);
    else buildSet(group, k);
}

int affixIndex(const CAffix* affix)
{
    int index = 0;
    for (std::map<std::wstring, CAffix*>::iterator i = manager->m_mapAffixes.begin();
         i != manager->m_mapAffixes.end(); ++i, ++index)
        if (i->second == affix) return index;
    return affix ? -2 : -1;
}

void captureSet(autotest::Capture& out, CSet* set)
{
    number(out, set != NULL);
    if (!set) return;
    out.addText(set->m_sName);
    out.addText(set->m_sDisplayName);
    unsigned header[4];
    std::memcpy(header, reinterpret_cast<char*>(&set->m_Affixes) + 8, 12);
    number(out, header[0]);
    number(out, header[1]);
    number(out, header[2]);
    for (unsigned i = 0; i < set->m_Affixes.size(); ++i) {
        CSetAffix* record = set->m_Affixes[i];
        number(out, record != NULL);
        if (!record) continue;
        out.addText(record->m_sAffixName);
        number(out, record->m_iLevel);
        number(out, record->m_iRequiredCount);
        CAffix* affix = record->m_pAffix;
        number(out, affix != NULL);
        if (!affix) continue;
        number(out, affixIndex(affix->m_pOriginalAffix));
        number(out, affix->m_uiLevel);
        number(out, affix->m_iRank);
        number(out, affix->m_iMinSpawnRange);
        number(out, affix->m_iMaxSpawnRange);
        number(out, affix->m_Effects.size());
        out.addText(affix->m_sAffixFileName);
        out.addText(affix->m_sDisplayName);
    }
}

CSetAffix* priorRecord(unsigned i)
{
    CSetAffix* record = new CSetAffix;
    std::map<std::wstring, CAffix*>::iterator source = manager->m_mapAffixes.begin();
    for (unsigned n = 0; n < i % 3 && source != manager->m_mapAffixes.end(); ++n) ++source;
    record->m_pAffix = source == manager->m_mapAffixes.end() ? NULL : new CAffix(source->second, i);
    record->m_sAffixName = L"prior";
    record->m_iLevel = i;
    record->m_iRequiredCount = int(i) - 1;
    return record;
}

void load(Case& c, bool ours, autotest::Capture& out)
{
    CDataGroup group(L"SET", NULL, 20, 10, NULL);
    fillGroup(group, c.index);
    CSet* set = new CSet;
    if (c.index % 3 == 1) {
        set->m_sName = L"previous";
        set->m_sDisplayName = L"previous display";
        set->m_Affixes.add(priorRecord(c.index));
        set->m_Affixes.add(NULL);
    }
    const int objects = g_iTotalCountOfObjects;
    typedef void (*Function)(CSet*, CDataGroup*, CEffectGroupManager*);
    Function function = ours ? newSetLoad : oldSetLoad;
    if (!autotest::beginInvocation(out, function)) return;
    function(set, &group, manager);
    out.callCompleted = 1;
    if (c.negative && ours) set->m_sName += L"!";
    number(out, g_iTotalCountOfObjects - objects);
    captureSet(out, set);
    delete set;
    number(out, g_iTotalCountOfObjects - objects);
    malloc_trim(0);
    out.addHeapInUse();
}

CSets* makeOwner(Storage<CSets>& storage, unsigned directory)
{
    CSets* owner = reinterpret_cast<CSets*>(storage.bytes);
    std::memset(owner, 0, sizeof(*owner));
    new (static_cast<CRunicCore*>(owner)) CRunicCore;
    new (&owner->m_path) std::wstring(kPaths[directory % 4]);
    new (&owner->m_sets) TArrayList<CSet*>(10);
    new (&owner->m_setIndices) std::map<std::wstring, unsigned int, std::less<std::wstring> >;
    const void* vtable = setsVtable + 16;
    std::memcpy(owner, &vtable, sizeof(vtable));
    return owner;
}

void prefill(CSets* owner, unsigned index)
{
    unsigned count = index % 4;
    for (unsigned i = 0; i < count; ++i) {
        if ((i + index) % 5 == 4) { owner->m_sets.add(NULL); continue; }
        CDataGroup group(L"SET", NULL, 20, 10, NULL);
        fillGroup(group, index + i * 7);
        CSet* set = new CSet;
        oldSetLoad(set, &group, manager);
        if (i == 1) set->m_Affixes.add(NULL);
        owner->m_sets.add(set);
    }
    if (index % 2) owner->m_setIndices[L"Stale"] = 99;
    if (index % 3 == 2) owner->m_setIndices[L"Set1"] = 77;
}

void captureOwner(autotest::Capture& out, CSets* owner)
{
    out.addText(owner->m_path);
    unsigned header[4];
    std::memcpy(header, reinterpret_cast<char*>(&owner->m_sets) + 8, 12);
    number(out, header[0]);
    number(out, header[1]);
    number(out, header[2]);
    for (unsigned i = 0; i < owner->m_sets.size(); ++i) captureSet(out, owner->m_sets[i]);
    number(out, owner->m_setIndices.size());
    for (std::map<std::wstring, unsigned int>::iterator i = owner->m_setIndices.begin();
         i != owner->m_setIndices.end(); ++i) {
        out.addText(i->first);
        number(out, i->second);
    }
}

void reload(Case& c, bool ours, autotest::Capture& out)
{
    Storage<CSets> storage;
    CSets* owner = makeOwner(storage, c.index);
    prefill(owner, c.index);
    TSafePointer<CRunicCore> weak[64];
    unsigned weakCount = 0;
    for (unsigned i = 0; i < owner->m_sets.size(); ++i) {
        CSet* set = owner->m_sets[i];
        for (unsigned j = 0; set && j < set->m_Affixes.size() && weakCount < 64; ++j)
            if (set->m_Affixes[j] && set->m_Affixes[j]->m_pAffix)
                weak[weakCount++].setObject(set->m_Affixes[j]->m_pAffix);
    }
    nativeSetsSingleton = c.index % 2 ? owner : NULL;
    const int objects = g_iTotalCountOfObjects;
    typedef void (*Function)(CSets*, CEffectGroupManager*);
    Function function = ours ? newSetsReload : oldSetsReload;
    if (!autotest::beginInvocation(out, function)) return;
    function(owner, manager);
    out.callCompleted = 1;
    if (c.negative && ours) owner->m_setIndices[L"negative"] = 1;
    number(out, g_iTotalCountOfObjects - objects);
    number(out, nativeSetsSingleton == owner);
    for (unsigned i = 0; i < weakCount; ++i) number(out, weak[i].getObject() == NULL);
    captureOwner(out, owner);
    oldSetsDtor(owner);
    number(out, g_iTotalCountOfObjects - objects);
    malloc_trim(0);
    out.addHeapInUse();
}

void destroy(Case& c, bool ours, autotest::Capture& out)
{
    Storage<CSets> storage;
    CSets* owner = makeOwner(storage, c.index);
    if (c.index % 4) oldSetsReload(owner, manager);
    prefill(owner, c.index / 4);
    TSafePointer<CRunicCore> weak[96];
    unsigned weakCount = 0;
    for (unsigned i = 0; i < owner->m_sets.size(); ++i) {
        CSet* set = owner->m_sets[i];
        for (unsigned j = 0; set && j < set->m_Affixes.size() && weakCount < 95; ++j)
            if (set->m_Affixes[j] && set->m_Affixes[j]->m_pAffix)
                weak[weakCount++].setObject(set->m_Affixes[j]->m_pAffix);
    }
    TSafePointer<CRunicCore> self;
    self.setObject(owner);
    int other = 0;
    nativeSetsSingleton = c.index % 3 == 0 ? NULL : c.index % 3 == 1 ? static_cast<void*>(owner) : &other;
    const int objects = g_iTotalCountOfObjects;
    typedef void (*Function)(CSets*);
    Function function = ours ? newSetsDtor : oldSetsDtor;
    if (!autotest::beginInvocation(out, function)) return;
    function(owner);
    out.callCompleted = 1;
    if (c.negative && ours) nativeSetsSingleton = owner;
    number(out, g_iTotalCountOfObjects - objects);
    number(out, nativeSetsSingleton == NULL);
    number(out, self.getObject() == NULL);
    number(out, weakCount);
    for (unsigned i = 0; i < weakCount; ++i) number(out, weak[i].getObject() == NULL);
    malloc_trim(0);
    out.addHeapInUse();
}

void side(void* context, bool ours, autotest::Capture& out)
{
    Case& c = *static_cast<Case*>(context);
    if (c.operation == 0) load(c, ours, out);
    if (c.operation == 1) reload(c, ours, out);
    if (c.operation == 2) destroy(c, ours, out);
}
void before(void* c, autotest::Capture& out) { side(c, false, out); }
void after(void* c, autotest::Capture& out) { side(c, true, out); }

unsigned operation;
int worker(const tlhybrid_host* host)
{
    nativegame::Services services;
    if (!services.ready()) return 1;
    manager = CMasterResourceManager::getSingleton()->m_effectGroups;
    CSets* gameSets = static_cast<CSets*>(nativeSetsSingleton);
    gameSetFiles = new TArrayList<std::wstring>(10);
    CFileSystem::getSingleton()->getFileList(L"media/sets/", *gameSetFiles, L"*.dat", true, true, false, false);
    affixNames = new std::vector<std::wstring>;
    for (std::map<std::wstring, CAffix*>::iterator i = manager->m_mapAffixes.begin();
         i != manager->m_mapAffixes.end(); ++i)
        affixNames->push_back(i->first);
    host->log("    sets fixture affixes %u set files %u game sets %u\n", unsigned(affixNames->size()),
        gameSetFiles->size(), gameSets ? gameSets->m_sets.size() : 0u);
    int failures = affixNames->empty() || !gameSetFiles->size() || !gameSets;
    {
        // Populate first-use caches before forking.
        Storage<CSets> storage;
        CSets* owner = makeOwner(storage, 0);
        oldSetsReload(owner, manager);
        failures += owner->m_sets.size() != gameSetFiles->size();
        oldSetsDtor(owner);
    }
    nativeSetsSingleton = gameSets;

    const char* names[] = {"sets_recovery_load", "sets_recovery_reload", "sets_recovery_dtor"};
    const uintptr_t targets[] = {0xe0e7a0, 0xe0f320, 0xe0ef30};
    autotest::Coverage coverage(names[operation], targets[operation]);
    for (unsigned i = 0; i < 40 && !failures; ++i) {
        Case c = {i, operation, false};
        autotest::Outcome a, b;
        autotest::runChild(before, &c, a, 2000, 10000);
        autotest::runChild(after, &c, b, 2000, 10000);
        if (coverage.observe(host, a, b)) {
            host->log("    sets seed%u op%u status%d/%d issue%u/%u bytes%lu/%lu\n",
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
    return failures + (coverage.completed != 40);
}
}

TL_TEST(sets_recovery_load) { operation = 0; return systems_fixture::isolated(worker, host); }
TL_TEST(sets_recovery_reload) { operation = 1; return systems_fixture::isolated(worker, host); }
TL_TEST(sets_recovery_dtor) { operation = 2; return systems_fixture::isolated(worker, host); }
