#include <climits>
#include "ParentPairs.h"
#include "Detour.h"
#include "QuestDialogItem.h"
#include "DataGroup.h"
#include "UnitResourceList.h"

TL_ORIGINAL(void, questParseOld, (CQuestDialogItem*, CDataGroup*, bool),
    "_ZN16CQuestDialogItem20parseDialogItemGroupEP10CDataGroupb")
extern "C" void questParseNew(CQuestDialogItem*, CDataGroup*, bool)
    __asm__("_ZN16CQuestDialogItem20parseDialogItemGroupEP10CDataGroupb");
TL_FUNCTION(questResources, "_ZN17CUnitResourceList12getSingletonEv")
TL_FUNCTION(questResourceName, "_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEE")

namespace {
autotest::Capture* capture;
CUnitResourceList* resources;
CDataGroup* resolved;
unsigned currentSeed;
void number(unsigned value) { capture->add(&value, sizeof(value)); }
CUnitResourceList* singleton()
{
    number(10);
    return resources;
}
CDataGroup* byName(CUnitResourceList* self, const std::wstring& name)
{
    number(11);
    number(self == resources);
    capture->addText(name);
    return currentSeed % 3 ? resolved : NULL;
}
void side(void* raw, autotest::Capture& out, bool ours)
{
    currentSeed = static_cast<parentpairs::Case*>(raw)->seed;
    const unsigned seed = currentSeed;
    capture = &out;
    CDataGroup group(L"ITEM", NULL, 2, 2, NULL);
    CDataGroup result(L"RESOLVED", NULL, 2, 2, NULL);
    resolved = &result;
    // This collaborator receives identity only; its methods are redirected.
    unsigned long resourceToken = 0;
    resources = reinterpret_cast<CUnitResourceList*>(&resourceToken);
    const int counts[] = {INT_MIN, -7, 0, 1, 2, 47, INT_MAX};
    const wchar_t* names[] = {L"", L"GOLD", L"gold", L"gOlD",
                             L"Sword", L"missing", L"  gold", L"Жёлтый"};
    if (seed % 5)
        group.AddDataValue(L"COUNT", counts[seed % 7]);
    if (seed % 11)
        group.AddDataValue(L"NAME", names[seed % 8], false);
    group.AddDataValue(L"UNIT", names[(seed + 4) % 8], false);
    CQuestDialogItem item(NULL);
    item.m_bGold = (seed / 8) % 2;
    item.m_bGive = !bool(seed % 2);
    item.m_pDataGroup = &result;
    item.m_iCount = -999;
    detour::Set patches;
    TL_REDIRECT(patches, questResources, &singleton);
    TL_REDIRECT(patches, questResourceName, &byName);
    if (patches.failed()) { out.issue = autotest::Capture::InvalidReport; return; }
    typedef void (*Fn)(CQuestDialogItem*, CDataGroup*, bool);
    Fn fn = ours ? questParseNew : questParseOld;
    if (!autotest::beginInvocation(out, fn)) return;
    fn(&item, &group, bool(seed % 2));
    out.callCompleted = 1;
    number(item.m_bGold);
    number(item.m_bGive);
    number(item.m_iCount);
    number(item.m_pDataGroup == &result ? 1 : item.m_pDataGroup ? 2 : 0);
    number(item.m_pQuestDialog == NULL);
    out.addHeapInUse();
}
void original(void* p, autotest::Capture& c) { side(p, c, false); }
void candidate(void* p, autotest::Capture& c) { side(p, c, true); }
}
TL_TEST(deepen_quest_dialog_parse)
{
    autotest::Coverage coverage("deepen_quest_dialog_parse", (uintptr_t)&questParseOld);
    for (unsigned seed = 0; seed < 224; ++seed) {
        parentpairs::Case input = {seed};
        autotest::Outcome& a = autotest::g_outcomes[0];
        autotest::Outcome& b = autotest::g_outcomes[1];
        autotest::runChild(original, &input, a);
        autotest::runChild(candidate, &input, b);
        if (coverage.observe(host, a, b)) {
            host->log("    quest seed %u lengths %lu/%lu\n", seed,
                (unsigned long)a.capture.length, (unsigned long)b.capture.length);
            for (unsigned i = 0; i < a.capture.length && i < b.capture.length; ++i)
                if (a.capture.data[i] != b.capture.data[i])
                    host->log("    capture byte %u: %u/%u\n", i,
                        (unsigned char)a.capture.data[i], (unsigned char)b.capture.data[i]);
            coverage.report(host);
            return 1;
        }
    }
    coverage.report(host);
    return coverage.completed != 224 || coverage.different || coverage.missing;
}
