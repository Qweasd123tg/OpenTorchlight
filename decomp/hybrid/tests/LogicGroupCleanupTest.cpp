#include "AutoTest.h"
#include "LogicGroup.h"
#include "LogicObject.h"
#include <cstring>
#include <stdint.h>

TL_ORIGINAL(void, originalLogicCleanup, (CLogicGroup*), "_ZN11CLogicGroupD1Ev")
extern "C" void candidateLogicCleanup(CLogicGroup*) __asm__("_ZN11CLogicGroupD1Ev");

namespace {
autotest::Capture* capture;
unsigned destroyed, expectedNext;
unsigned order[8];
class OwnedLogic : public CLogicObject
{
public:
    explicit OwnedLogic(unsigned id) : CLogicObject(NULL, -1, id), id_(id) {}
    virtual ~OwnedLogic()
    {
        capture->add(&id_, sizeof(id_));
        if (expectedNext >= 8 || order[expectedNext] != id_)
            capture->issue = autotest::Capture::InvalidReport;
        ++expectedNext;
        ++destroyed;
    }
private:
    unsigned id_;
};
struct Case { unsigned count, holes, growth; };
void execute(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw);
    CLogicGroup* object = new CLogicGroup(NULL);
    object->SetName(std::wstring(97, L'Ж'));
    object->m_logicObjects.setGrowBy(c.growth);
    unsigned expected = 0;
    for (unsigned i = 0; i < c.count; ++i) {
        bool live = c.holes == 0 || (c.holes == 1 ? i % 2 == 0 : i + 1 == c.count);
        object->m_logicObjects.add(live ? new OwnedLogic(i) : NULL);
        if (live) order[expected++] = i;
    }
    capture = &out;
    destroyed = expectedNext = 0;
    typedef void (*Function)(CLogicGroup*);
    Function function = ours ? candidateLogicCleanup : originalLogicCleanup;
    if (!autotest::beginInvocation(out, function)) return;
    function(object);
    out.callCompleted = 1;
    out.add(&destroyed, sizeof(destroyed));
    if (destroyed != expected || expectedNext != expected)
        out.issue = autotest::Capture::InvalidReport;
    // Inspect the ended object's storage, without calling methods on it.
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(object);
    void* data;
    unsigned count, capacity, growth;
    std::memcpy(&data, bytes + 0x60, sizeof(data));
    std::memcpy(&count, bytes + 0x68, sizeof(count));
    std::memcpy(&capacity, bytes + 0x6c, sizeof(capacity));
    std::memcpy(&growth, bytes + 0x70, sizeof(growth));
    unsigned empty = data == NULL;
    out.add(&empty, sizeof(empty));
    out.add(&count, sizeof(count));
    out.add(&capacity, sizeof(capacity));
    out.add(&growth, sizeof(growth));
    if (!empty || count || capacity || growth != c.growth)
        out.issue = autotest::Capture::InvalidReport;
    CLogicGroup::operator delete(object);
}
void before(void* c, autotest::Capture& out) { execute(c, out, false); }
void after(void* c, autotest::Capture& out) { execute(c, out, true); }
}
TL_TEST(mass_logic_group_owned_cleanup)
{
    autotest::Coverage coverage("mass_logic_group_owned_cleanup", (uintptr_t)&originalLogicCleanup);
    const unsigned counts[] = {0, 1, 2, 4, 7}, growths[] = {1, 2, 5, 10};
    for (unsigned n = 0; n < 60; ++n) {
        Case c = {counts[n % 5], n / 5 % 3, growths[n / 15]};
        autotest::Outcome a, b;
        autotest::runChild(before, &c, a);
        autotest::runChild(after, &c, b);
        if (coverage.observe(host, a, b)) {
            host->log("    cleanup case %u exits %d/%d\n", n, a.childStatus, b.childStatus);
            coverage.report(host);
            return 1;
        }
    }
    coverage.report(host);
    return 0;
}
