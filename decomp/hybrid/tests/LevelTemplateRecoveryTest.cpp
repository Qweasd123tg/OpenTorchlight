#include <map>
#include <string>
#include <vector>
#include <malloc.h>
#include "AutoTest.h"
#include "SystemsFixtureWorker.h"
#define private public
#include "LevelTemplateData.h"
#undef private
#include "SafePointer.h"

TL_ORIGINAL(void, templateOldDelete, (CLevelTemplateData*), "_ZN18CLevelTemplateData13deleteLayoutsEv")
extern "C" void templateNewDelete(CLevelTemplateData*) __asm__("_ZN18CLevelTemplateData13deleteLayoutsEv");

namespace {
struct Case { unsigned seed; bool negative; };
void number(autotest::Capture& out, long long value) { out.add(&value, sizeof(value)); }
template<class T> void listState(autotest::Capture& out, TArrayList<T>& list)
{
    unsigned values[3];
    std::memcpy(values, reinterpret_cast<char*>(&list) + 8, sizeof(values));
    out.add(values, sizeof(values));
}

void side(void* raw, bool ours, autotest::Capture& out)
{
    Case& c = *static_cast<Case*>(raw);
    CLevelTemplateData owner(NULL);
    std::vector<CLevelLayout*> all;
    TSafePointer<CRunicCore> layouts[64], instances[128], chunks[64], randomizer;
    unsigned instanceCount = 0;
    const unsigned sizes[] = {0, 1, 2, 7, 13, 23};
    unsigned count = sizes[c.seed % 6];
    std::vector<std::wstring> shared;
    shared.reserve(128);
    owner.m_layouts.setGrowBy(c.seed % 5 + 1);
    owner.m_randomLayoutGenerated = c.seed & 1;
    for (unsigned i = 0; i < count; ++i) {
        CLevelLayout* layout = new CLevelLayout;
        layout->m_seed = i + 100;
        layouts[i].setObject(layout);
        all.push_back(layout);
        CChunk* chunk = new CChunk;
        chunk->m_filename = L"borrowed chunk";
        chunks[i].setObject(chunk);
        owner.m_chunks.add(chunk);
        layout->m_chunks.add(chunk);
        for (unsigned j = 0; j < (c.seed + i) % 4; ++j) {
            if ((i + j) % 5 == 4) { layout->m_chunkInstances.add(NULL); continue; }
            CChunkInstance* instance = new CChunkInstance;
            instances[instanceCount++].setObject(instance);
            shared.push_back(std::wstring(64 + i, wchar_t(L'A' + i)));
            instance->m_name = shared.back();
            for (unsigned k = 0; k < j; ++k) instance->m_usedExits.push_back(k);
            layout->m_chunkInstances.add(instance);
        }
        if ((i + c.seed) % 3 == 0) owner.m_baseLayouts.add(layout);
        if ((i + c.seed) % 7 != 1) owner.m_layouts.add(layout);
        if ((i + c.seed) % 6 == 3) owner.m_layouts.add(NULL);
    }
    // Keep a borrowed base pointer twice, exercising restoration order/duplicates.
    if (owner.m_baseLayouts.size() && c.seed % 4 == 0)
        owner.m_baseLayouts.add(owner.m_baseLayouts[0]);
    if (c.seed % 3) {
        owner.m_layoutRandomizer = new CRandomizer(c.seed & 1 ? RANDOMIZER_DECAY : RANDOMIZER_NORMAL);
        randomizer.setObject(owner.m_layoutRandomizer);
        for (unsigned i = 0; i < c.seed % 11; ++i) owner.m_layoutRandomizer->addChoice(i + 40, i + 2);
    }
    int beforeCount = g_iTotalCountOfObjects;
    typedef void (*Function)(CLevelTemplateData*);
    Function function = ours ? templateNewDelete : templateOldDelete;
    if (!autotest::beginInvocation(out, function)) return;
    function(&owner);
    out.callCompleted = 1;
    if (ours && c.negative) owner.m_randomLayoutGenerated = true;
    number(out, g_iTotalCountOfObjects - beforeCount);
    number(out, owner.m_randomLayoutGenerated);
    number(out, randomizer.getObject() == owner.m_layoutRandomizer);
    listState(out, owner.m_layouts);
    listState(out, owner.m_baseLayouts);
    for (unsigned i = 0; i < owner.m_layouts.size(); ++i) {
        unsigned id = 999;
        for (unsigned j = 0; j < all.size(); ++j) if (all[j] == owner.m_layouts[i]) id = j;
        number(out, id);
    }
    number(out, owner.m_layoutRandomizer->getChoiceCount());
    for (unsigned i = 0; i < owner.m_layoutRandomizer->getChoiceCount(); ++i) {
        number(out, owner.m_layoutRandomizer->getChoice(i));
        number(out, owner.m_layoutRandomizer->getOdds(i));
    }
    for (unsigned i = 0; i < count; ++i) {
        number(out, layouts[i].getObject() != NULL);
        number(out, chunks[i].getObject() != NULL);
    }
    for (unsigned i = 0; i < instanceCount; ++i) number(out, instances[i].getObject() != NULL);
    for (unsigned i = 0; i < shared.size(); ++i) {
        int refs;
        std::memcpy(&refs, reinterpret_cast<const char*>(shared[i].data()) - 8, sizeof(refs));
        number(out, refs);
    }
    // Some base layouts were not in m_layouts initially; all live layouts are
    // now reclaimed exactly once, including duplicate borrowed base entries.
    owner.m_layouts.clear();
    owner.m_baseLayouts.clear();
    for (unsigned i = 0; i < count; ++i) if (layouts[i].getObject()) delete all[i];
    for (unsigned i = 0; i < instanceCount; ++i) number(out, instances[i].getObject() == NULL);
    malloc_trim(0);
    out.addHeapInUse();
}
void before(void* c, autotest::Capture& out) { side(c, false, out); }
void after(void* c, autotest::Capture& out) { side(c, true, out); }

int worker(const tlhybrid_host* host)
{
    autotest::Coverage coverage("level_template_recovery_delete", 0x972b80);
    int failures = 0;
    for (unsigned i = 0; i < 72; ++i) {
        Case c = {i, false};
        autotest::Outcome a, b;
        autotest::runChild(before, &c, a, 2000, 10000);
        autotest::runChild(after, &c, b, 2000, 10000);
        if (coverage.observe(host, a, b)) {
            host->log("    deleteLayouts seed%u status%d/%d bytes%lu/%lu issue%u/%u\n", i,
                a.childStatus, b.childStatus, (unsigned long)a.capture.length,
                (unsigned long)b.capture.length, a.capture.issue, b.capture.issue);
            ++failures;
            break;
        }
    }
    coverage.report(host);
    Case c = {7, true};
    autotest::Outcome a, b;
    autotest::runChild(before, &c, a, 2000, 10000);
    autotest::runChild(after, &c, b, 2000, 10000);
    bool detected = a.capture.length != b.capture.length ||
        std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    TL_CHECK(failures, detected && !autotest::incomplete(a) && !autotest::incomplete(b) &&
        a.reportValid && b.reportValid && !a.childStatus && !b.childStatus);
    host->log("    deleteLayouts negative control detected %u\n", detected ? 1u : 0u);
    return failures + (coverage.completed != 72);
}
}
TL_TEST(level_template_recovery_delete) { return systems_fixture::isolated(worker, host); }
