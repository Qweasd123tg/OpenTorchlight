#include "AutoTest.h"
#include "SystemsFixtureWorker.h"
#include "DataGroup.h"
#include "FileSystem.h"
#include "PairStyle.h"
#include "RandomNames.h"
#include "Randomizer.h"
#include "Utilities.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <new>
#include <string>
#include <unistd.h>

TL_ORIGINAL(void, namesOldLoad, (CRandomNames*, const wchar_t*), "_ZN12CRandomNames4loadEPKw")
TL_ORIGINAL(std::wstring, namesOldGenerate, (CRandomNames*, bool), "_ZN12CRandomNames12generateNameEb")
TL_ORIGINAL(void, namesOldDtor, (CRandomNames*), "_ZN12CRandomNamesD1Ev")
extern "C" void namesNewLoad(CRandomNames*, const wchar_t*) __asm__("_ZN12CRandomNames4loadEPKw");
extern "C" std::wstring namesNewGenerate(CRandomNames*, bool) __asm__("_ZN12CRandomNames12generateNameEb");
extern "C" void* namesSingleton __asm__("_ZL14g_pRandomNames");
namespace LinuxUtils {
extern std::wstring gameHomePath __asm__("_ZN10LinuxUtilsL12gameHomePathE");
}

namespace {
struct Case { unsigned index; bool generate; bool negative; };
char root[] = "/tmp/opencode/otl-random-names-XXXXXX";
std::wstring fixturePath;

// Native CRandomName record (0x48): two ints, prefix and suffix lists, center
// text and center chance; read through raw offsets checked by load at 0xe04e90.
void number(autotest::Capture& out, long long value) { out.add(&value, sizeof(value)); }
unsigned word(const void* base, unsigned offset) { unsigned v; std::memcpy(&v, static_cast<const char*>(base) + offset, 4); return v; }
int references(const std::wstring& value)
{
    int count;
    std::memcpy(&count, reinterpret_cast<const char*>(value.data()) - 8, sizeof(count));
    return count;
}
void text(autotest::Capture& out, const std::wstring& value)
{
    out.addText(value);
    number(out, value.data() == std::wstring().data() ? -1000 : references(value));
}
// TArrayList<std::wstring>: data +0, count +8, capacity +0xc, grow-by +0x10.
void strings(autotest::Capture& out, const void* list)
{
    unsigned count = word(list, 8);
    number(out, count); number(out, word(list, 0xc)); number(out, word(list, 0x10));
    std::wstring* data;
    std::memcpy(&data, list, sizeof(data));
    number(out, data != NULL);
    for (unsigned i = 0; i < count; ++i) text(out, data[i]);
}

void groupText(CDataGroup* group, const wchar_t* key, const std::wstring& value, bool translate)
{
    group->AddDataValue(std::wstring(key), value.c_str(), translate);
}
std::wstring piece(const wchar_t* stem, unsigned a, unsigned b)
{
    wchar_t buffer[64];
    std::swprintf(buffer, 64, L"%ls%u_%u", stem, a, b);
    std::wstring result(buffer);
    if (a % 7 == 4) result.append(96, L'x');
    if (a % 11 == 5) result += L"\x0416\x03b1";
    return result;
}

void removeCaches()
{
    unlink((std::string(root) + "/names.dat.adm").c_str());
    unlink((std::string(root) + "/names.dat.ADM").c_str());
}

// Writes one pair-style data file with the actual native CDataGroup/CPairStyle.
bool writeFixture(unsigned seed, bool generate)
{
    CDataGroup data(L"RANDOMNAMES", NULL, 20, 10, NULL);
    unsigned names = generate ? 1 + seed % 4 : seed % 5;
    if (!generate && seed % 11 == 3) names = 0;
    data.AddDataValue(std::wstring(L"WEIGHT"), int(seed));
    if (seed % 3 == 1) data.AddDataGroup(std::wstring(L"OTHER"))->AddDataValue(std::wstring(L"PREFIX"), L"decoy", false);
    for (unsigned n = 0; n < names; ++n) {
        CDataGroup* group = data.AddDataGroup(std::wstring(L"NAME"));
        unsigned k = seed * 7 + n * 13;
        if (k % 4) group->AddDataValue(std::wstring(L"WEIGHT"), int(k % 9) - (k % 5 == 0 ? 3 : 0));
        unsigned prefixes = generate ? 1 + k % 4 : k % 5;
        unsigned suffixes = generate ? 1 + (k / 3) % 4 : (k / 3) % 5;
        if (k % 6 != 2) {
            const int chances[] = {0, 100, 50, -5, 1, 99, 30};
            group->AddDataValue(std::wstring(L"CENTERCHANCE"), chances[(k / 2) % 7]);
        }
        if (k % 5 != 1) groupText(group, L"CENTER", piece(L"c", seed, n), (k & 8) != 0);
        for (unsigned i = 0; i < prefixes; ++i) groupText(group, L"PREFIX", piece(L"p", n, i), ((k + i) & 1) != 0);
        if (k % 7 == 4) groupText(group, L"prefix", L"lower", false);
        for (unsigned i = 0; i < suffixes; ++i) groupText(group, L"SUFFIX", piece(L"s", n, i), ((k + i) & 2) != 0);
        if (n == 1) group->AddDataGroup(std::wstring(L"NAME"))->AddDataValue(std::wstring(L"PREFIX"), L"nested", false);
    }
    if (seed % 4 != 3) {
        CDataGroup* title = data.AddDataGroup(std::wstring(L"TITLE"));
        if (seed % 5 != 2) {
            const int chances[] = {100, 0, 50, 75, -1};
            title->AddDataValue(std::wstring(L"CHANCE"), chances[seed % 5]);
        }
        unsigned prefixes = (seed / 2) % 4, suffixes = generate ? (seed / 3) % 4 : (seed / 4) % 5;
        for (unsigned i = 0; i < prefixes; ++i) groupText(title, L"PREFIX", piece(L"tp", seed, i), (i & 1) != 0);
        for (unsigned i = 0; i < suffixes; ++i) groupText(title, L"SUFFIX", piece(L"Title", seed, i), (i & 1) == 0);
    }
    CPairStyle style;
    std::string narrow = std::string(root) + "/names.dat";
    unlink(narrow.c_str());
    style.SaveDataGroupToFile(fixturePath, &data);
    removeCaches();
    return access(narrow.c_str(), R_OK) == 0;
}

union Storage { long double alignment; char bytes[sizeof(CRandomNames)]; };
CRandomNames* fresh(Storage& storage, unsigned seed)
{
    std::memset(storage.bytes, 0x5a, sizeof(storage.bytes));
    CRandomNames* names = reinterpret_cast<CRandomNames*>(storage.bytes);
    names->m_nWeight = seed;
    new (&names->m_prefixes) TArrayList<CRandomName*>(10);
    new (&names->m_suffixes) TArrayList<std::wstring>(10);
    new (&names->m_center) TArrayList<std::wstring>(10);
    names->m_pRandomizer = NULL;
    names->m_nCenterChance = 100;
    return names;
}

void state(autotest::Capture& out, CRandomNames* names)
{
    number(out, names->m_nWeight);
    number(out, names->m_nCenterChance);
    const void* list = &names->m_prefixes;
    unsigned count = word(list, 8);
    number(out, count); number(out, word(list, 0xc)); number(out, word(list, 0x10));
    for (unsigned i = 0; i < count; ++i) {
        const char* record = reinterpret_cast<const char*>(names->m_prefixes[i]);
        number(out, word(record, 0)); number(out, word(record, 4)); number(out, word(record, 0x40));
        strings(out, record + 8);
        strings(out, record + 0x20);
        text(out, *reinterpret_cast<const std::wstring*>(record + 0x38));
    }
    strings(out, &names->m_suffixes);
    strings(out, &names->m_center);
    CRandomizer* randomizer = names->m_pRandomizer;
    number(out, randomizer != NULL);
    if (randomizer) {
        unsigned choices = randomizer->getChoiceCount();
        number(out, choices);
        for (unsigned i = 0; i < choices; ++i) { number(out, randomizer->getChoice(i)); number(out, randomizer->getOdds(i)); }
        number(out, randomizer->hasValidChoices());
    }
}

void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw);
    Storage storage;
    CRandomNames* names = fresh(storage, c.index);
    namesSingleton = names;
    removeCaches();
    if (!c.generate) {
        typedef void (*Load)(CRandomNames*, const wchar_t*);
        Load call = ours ? namesNewLoad : namesOldLoad;
        if (!autotest::beginInvocation(out, call)) return;
        call(names, fixturePath.c_str());
        out.callCompleted = 1;
        unsigned expected = c.index % 11 == 3 ? 0 : c.index % 5;
        if (names->m_prefixes.size() != expected) out.issue = autotest::Capture::InvalidReport;
        if (ours && c.negative) names->m_nCenterChance ^= 1;
        state(out, names);
    } else {
        namesOldLoad(names, fixturePath.c_str());
        if (names->m_prefixes.size() != 1 + c.index % 4) {
            out.issue = autotest::Capture::InvalidReport;
            return;
        }
        // Exercise TArrayList's out-of-capacity fallback using a real weighted
        // randomizer whose returned choice is not a valid record index.
        if (c.index % 11 == 8) {
            names->m_pRandomizer->clear();
            names->m_pRandomizer->addChoice(-1, 1);
        }
        UTILITIES::setSeed(int((c.index + 1) * 2654435761u));
        typedef std::wstring (*Generate)(CRandomNames*, bool);
        Generate call = ours ? namesNewGenerate : namesOldGenerate;
        if (!autotest::beginInvocation(out, call)) return;
        for (unsigned i = 0; i < 48; ++i) {
            std::wstring result = call(names, i % 3 != 0);
            if (ours && c.negative && i == 5) result += L"!";
            text(out, result);
        }
        out.callCompleted = 1;
        number(out, UTILITIES::getRandState());
        state(out, names);
    }
    namesOldDtor(names);
    number(out, namesSingleton == NULL);
    out.addHeapInUse();
}
void before(void* c, autotest::Capture& out) { side(c, out, false); }
void after(void* c, autotest::Capture& out) { side(c, out, true); }

bool generating;
int worker(const tlhybrid_host* host)
{
    if (!mkdtemp(root)) return 1;
    LinuxUtils::gameHomePath.assign(root, root + std::strlen(root));
    LinuxUtils::gameHomePath += L"/";
    fixturePath.assign(root, root + std::strlen(root));
    fixturePath += L"/names.dat";
    // Registered-owner pre-init branch of the native C1: members only, no
    // resource loading; uninitialized getFileInfo then checks the disk path.
    void* value = NULL;
    std::memcpy(&value, reinterpret_cast<void*>(0x1528e40), sizeof(value));
    if (!value) new (reinterpret_cast<void*>(0x1528e40)) std::string;
    std::memcpy(&value, reinterpret_cast<void*>(0x1528e48), sizeof(value));
    if (!value) new (reinterpret_cast<void*>(0x1528e48)) std::wstring;
    void* memory = CFileSystem::operator new(sizeof(CFileSystem));
    g_pFileSystem = static_cast<CFileSystem*>(memory);
    new (memory) CFileSystem(false);

    autotest::Coverage coverage(generating ? "random_names_generate" : "random_names_load",
                                generating ? 0xe062a0 : 0xe04e90);
    int failures = 0;
    const unsigned count = 44;
    for (unsigned i = 0; i < count && !failures; ++i) {
        if (!writeFixture(i, generating)) { host->log("    random names fixture %u not written\n", i); ++failures; break; }
        Case c = {i, generating, false};
        autotest::Outcome a, b;
        autotest::runChild(before, &c, a, 2000, 10000);
        autotest::runChild(after, &c, b, 2000, 10000);
        if (coverage.observe(host, a, b)) {
            host->log("    random names seed%u generate%d status%d/%d issue%u/%u bytes%lu/%lu\n", i, generating,
                      a.childStatus, b.childStatus, a.capture.issue, b.capture.issue,
                      (unsigned long)a.capture.length, (unsigned long)b.capture.length);
            for (size_t offset = 0; offset < a.capture.length && offset < b.capture.length; ++offset)
                if (a.capture.data[offset] != b.capture.data[offset]) {
                    host->log("    first mismatch at %lu\n", (unsigned long)offset); break;
                }
            ++failures;
        }
    }
    coverage.report(host);
    Case negative = {7, generating, true};
    writeFixture(negative.index, generating);
    autotest::Outcome a, b;
    autotest::runChild(before, &negative, a, 2000, 10000);
    autotest::runChild(after, &negative, b, 2000, 10000);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    TL_CHECK(failures, detected && !autotest::incomplete(a) && !autotest::incomplete(b) &&
        a.reportValid && b.reportValid && !a.childStatus && !b.childStatus);
    host->log("    random names negative control %s detected %d\n", generating ? "generate" : "load", detected);
    // Fixture sanity after all children: the loaded tables must be non-trivial.
    Storage probe;
    CRandomNames* loaded = fresh(probe, 9);
    bool probeWritten = writeFixture(9, generating);
    namesOldLoad(loaded, fixturePath.c_str());
    unsigned records = loaded->m_prefixes.size(), filled = 0;
    for (unsigned r = 0; r < records; ++r)
        filled += word(loaded->m_prefixes[r], 0x10) != 0 && word(loaded->m_prefixes[r], 0x28) != 0;
    host->log("    random names probe records %u filled %u titles %u/%u chance %d\n", records, filled,
              loaded->m_suffixes.size(), loaded->m_center.size(), loaded->m_nCenterChance);
    TL_CHECK(failures, probeWritten && records != 0 && filled != 0);
    namesOldDtor(loaded);
    unlink((std::string(root) + "/names.dat").c_str());
    removeCaches();
    rmdir(root);
    return failures + (coverage.completed != count);
}
}

TL_TEST(random_names_load) { generating = false; return systems_fixture::isolated(worker, host); }
TL_TEST(random_names_generate) { generating = true; return systems_fixture::isolated(worker, host); }
