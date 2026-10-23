#include "tests/NativeGameServices.h"
#include "SystemsFixtureWorker.h"
#include "SpawnClassParser.h"
#include "SpawnClass.h"
#include "SpawnClassData.h"
#include "Utilities.h"

TL_ORIGINAL(void, parserOldCtor, (CSpawnClassParser*), "_ZN17CSpawnClassParserC1Ev")
TL_ORIGINAL(void, parserOldDtor, (CSpawnClassParser*), "_ZN17CSpawnClassParserD1Ev")
extern "C" void parserNewCtor(CSpawnClassParser*) __asm__("_ZN17CSpawnClassParserC1Ev");
extern "C" CSpawnClassParser* parserSingleton __asm__("_ZL19m_gSpawnClassParser");

namespace {
struct Case { unsigned seed; bool negative; };
union Storage { long double alignment; char bytes[sizeof(CSpawnClassParser)]; };
void number(autotest::Capture& out, long long value) { out.add(&value, sizeof(value)); }
void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw);
    Storage storage;
    std::memset(storage.bytes, c.seed & 1 ? 0x5a : 0, sizeof(storage.bytes));
    CSpawnClassParser* parser = reinterpret_cast<CSpawnClassParser*>(storage.bytes);
    CSpawnClassParser* previous = parserSingleton;
    if (c.seed & 2) parserSingleton = NULL;
    UTILITIES::setSeed(0x5300 + c.seed);
    int previousObjects = g_iTotalCountOfObjects;
    typedef void (*Function)(CSpawnClassParser*);
    Function function = ours ? parserNewCtor : parserOldCtor;
    if (!autotest::beginInvocation(out, function)) return;
    function(parser);
    out.callCompleted = 1;
    if (ours && c.negative) parserSingleton = previous;
    number(out, parserSingleton == parser);
    number(out, g_iTotalCountOfObjects - previousObjects);
    number(out, UTILITIES::getRandState());
    number(out, parser->m_spawnClasses.size());
    number(out, parser->m_spawnClassData.size());
    if (parser->m_spawnClasses.empty() || parser->m_spawnClassData.empty()) {
        out.issue = autotest::Capture::InvalidReport;
        return;
    }
    for (std::map<std::wstring, CSpawnClass*>::iterator i = parser->m_spawnClasses.begin();
         i != parser->m_spawnClasses.end(); ++i) {
        out.addText(i->first);
        number(out, i->second != NULL);
        if (i->second) {
            out.addText(i->second->m_name);
            number(out, i->second->m_entries.size());
            number(out, i->second->m_iUnknown30);
        }
    }
    for (std::map<std::wstring, CSpawnClassData*>::iterator i = parser->m_spawnClassData.begin();
         i != parser->m_spawnClassData.end(); ++i) {
        out.addText(i->first);
        number(out, i->second != NULL);
        if (i->second) {
            out.addText(i->second->m_sName);
            number(out, i->second->m_lUnitDataObjects.size());
            number(out, i->second->m_iMinimumLevel);
            number(out, i->second->m_iLevelOffset);
            number(out, i->second->m_iRarityOverride);
            number(out, i->second->m_iFlags);
        }
    }
    parserOldDtor(parser);
    number(out, g_iTotalCountOfObjects - previousObjects);
    number(out, parserSingleton == NULL);
    parserSingleton = previous;
}
void before(void* c, autotest::Capture& out) { side(c, out, false); }
void after(void* c, autotest::Capture& out) { side(c, out, true); }
int worker(const tlhybrid_host* host)
{
    nativegame::Services services;
    if (!services.ready()) return 1;
    autotest::Coverage coverage("spawn_parser_constructor_recovery", 0xa81b90);
    for (unsigned i = 0; i < 32; ++i) {
        Case c = {i, false};
        autotest::Outcome a, b;
        autotest::runChild(before, &c, a, 10000, 20000);
        autotest::runChild(after, &c, b, 10000, 20000);
        if (coverage.observe(host, a, b)) { coverage.report(host); return 1; }
    }
    coverage.report(host);
    Case c = {3, true};
    autotest::Outcome a, b;
    autotest::runChild(before, &c, a, 10000, 20000);
    autotest::runChild(after, &c, b, 10000, 20000);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    host->log("    Spawn parser negative control detected %u\n", detected ? 1u : 0u);
    return !detected || autotest::incomplete(a) || autotest::incomplete(b) || !a.reportValid || !b.reportValid || a.childStatus || b.childStatus;
}
}
TL_TEST(spawn_parser_constructor_recovery) { return systems_fixture::isolated(worker, host, 120); }
