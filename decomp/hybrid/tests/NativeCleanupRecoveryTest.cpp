#include "AutoTest.h"
#include "DescriptorController.h"
#include "DescriptorProp.h"
#include "DescriptorRegistry.h"
#include "EditorBaseObject.h"
#include "GameVariables.h"
#include "RandomNames.h"
#include "SafePointer.h"
#include "SystemsFixtureWorker.h"
#include <new>
#include <vector>

TL_ORIGINAL(void, controllerOriginalDtor, (CDescriptorController*), "_ZN21CDescriptorControllerD1Ev")
TL_ORIGINAL(void, namesOriginalDtor, (CRandomNames*), "_ZN12CRandomNamesD1Ev")
extern "C" void controllerRecoveredDtor(CDescriptorController*) __asm__("_ZN21CDescriptorControllerD1Ev");
extern "C" void namesRecoveredDtor(CRandomNames*) __asm__("_ZN12CRandomNamesD1Ev");
extern "C" void* nativeNamesSingleton __asm__("_ZL14g_pRandomNames");

namespace {
struct Case { unsigned index; bool names; bool negative; };
typedef std::map<std::wstring, TArrayList<CDescriptorProp*>*> Properties;
struct Caches { Properties properties, defaults; };
struct NameRecord : Ogre::GeneralAllocatedObject {
    int weight, index;
    TArrayList<std::wstring> prefixes, suffixes;
    std::wstring name;
    int chance;
    NameRecord() : prefixes(10), suffixes(10) {}
};
typedef char NameRecordSize[sizeof(NameRecord) == 0x48 ? 1 : -1];

void share(std::wstring& target, std::vector<std::wstring>& references, unsigned value)
{
    std::wstring text(48 + value % 17, wchar_t(L'A' + value % 23));
    references.push_back(text);
    target = references.back();
}

void stringState(autotest::Capture& out, const std::vector<std::wstring>& references)
{
    for (unsigned i = 0; i < references.size(); ++i) {
        // GCC 4.4's COW _Rep refcount is eight bytes before its character data.
        int count;
        std::memcpy(&count, reinterpret_cast<const char*>(references[i].data()) - 8, sizeof(count));
        out.add(&count, sizeof(count));
    }
}

void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw);
    std::vector<std::wstring> references;
    references.reserve(512);
    TSafePointer<CRunicCore> weak[256];
    unsigned weakCount = 0;
    unsigned groups = c.index % 5;
    unsigned elements = (c.index * 7) % 12;
    if (c.names) {
        union Storage { long double alignment; char bytes[sizeof(CRandomNames)]; } storage;
        std::memset(storage.bytes, 0x5a, sizeof(storage.bytes));
        CRandomNames* names = reinterpret_cast<CRandomNames*>(storage.bytes);
        names->m_nWeight = c.index;
        new (&names->m_prefixes) TArrayList<CRandomName*>(10);
        new (&names->m_suffixes) TArrayList<std::wstring>(10);
        new (&names->m_center) TArrayList<std::wstring>(10);
        names->m_pRandomizer = NULL;
        names->m_nCenterChance = 100;
        if (c.index & 1) {
            names->m_pRandomizer = new CRandomizer(RANDOMIZER_NORMAL);
            names->m_pRandomizer->addChoice(1, 10);
            weak[weakCount++].setObject(names->m_pRandomizer);
        }
        for (unsigned i = 0; i < groups; ++i) {
            if ((i + c.index) % 3 == 0) {
                names->m_prefixes.add(NULL);
                continue;
            }
            NameRecord* record = new NameRecord;
            record->weight = i;
            record->index = i + 5;
            record->chance = 21;
            share(record->name, references, i);
            for (unsigned j = 0; j < elements; ++j) {
                std::wstring text;
                share(text, references, i * 17 + j);
                record->prefixes.add(text);
                record->suffixes.add(text);
            }
            names->m_prefixes.add(reinterpret_cast<CRandomName*>(record));
        }
        for (unsigned i = 0; i < elements; ++i) {
            std::wstring text;
            share(text, references, i + 101);
            names->m_suffixes.add(text);
            names->m_center.add(text);
        }
        nativeNamesSingleton = names;
        typedef void (*Dtor)(CRandomNames*);
        Dtor call = ours ? namesRecoveredDtor : namesOriginalDtor;
        if (!autotest::beginInvocation(out, call)) return;
        call(names);
        out.callCompleted = 1;
        if (ours && c.negative) nativeNamesSingleton = names;
        bool cleared = nativeNamesSingleton == NULL;
        out.add(&cleared, sizeof(cleared));
    } else {
        union Storage { long double alignment; char bytes[sizeof(CDescriptorController)]; } storage;
        typedef char CachesSize[sizeof(Caches) == sizeof(storage.bytes) ? 1 : -1];
        Caches* caches = new (storage.bytes) Caches;
        for (unsigned which = 0; which < 2; ++which) {
            Properties& properties = which ? caches->defaults : caches->properties;
            unsigned count = which ? (c.index / 3) % 5 : groups;
            for (unsigned i = 0; i < count; ++i) {
                TArrayList<CDescriptorProp*>* list = new TArrayList<CDescriptorProp*>(3);
                for (unsigned j = 0; j < elements; ++j) {
                    if ((i + j + c.index) % 3 == 0) list->add(NULL);
                    else {
                        CDescriptorProp* prop = new CDescriptorProp(L"category", L"property", L"description", NULL, NULL, VARIABLE_TYPE_FLOAT, 0);
                        weak[weakCount++].setObject(prop);
                        list->add(prop);
                    }
                }
                properties[std::wstring(48 + i, wchar_t(L'k' + i))] = list;
            }
        }
        unsigned cached = (c.index / 2) % 5;
        for (unsigned i = 0; i < cached; ++i) {
            TArrayList<CEditorBaseObject*>* list = new TArrayList<CEditorBaseObject*>(3);
            for (unsigned j = 0; j < elements; ++j) {
                if ((i + j) % 3 == 0) list->add(NULL);
                else {
                    CEditorBaseObject* object = new CEditorBaseObject;
                    std::wstring text;
                    share(text, references, i * 17 + j);
                    object->SetName(text);
                    weak[weakCount++].setObject(object);
                    list->add(object);
                }
            }
            g_CachedObjects[std::wstring(48 + i, wchar_t(L'c' + i))] = list;
        }
        typedef void (*Dtor)(CDescriptorController*);
        Dtor call = ours ? controllerRecoveredDtor : controllerOriginalDtor;
        if (!autotest::beginInvocation(out, call)) return;
        call(reinterpret_cast<CDescriptorController*>(caches));
        out.callCompleted = 1;
        if (ours && c.negative) g_CachedObjects[L"negative"] = NULL;
        unsigned remaining = g_CachedObjects.size();
        out.add(&remaining, sizeof(remaining));
    }
    for (unsigned i = 0; i < weakCount; ++i) {
        bool invalidated = weak[i].getObject() == NULL;
        out.add(&invalidated, sizeof(invalidated));
    }
    stringState(out, references);
    out.addHeapInUse();
}

void before(void* p, autotest::Capture& out) { side(p, out, false); }
void after(void* p, autotest::Capture& out) { side(p, out, true); }
int worker(const tlhybrid_host* host, bool names)
{
    autotest::Coverage coverage(names ? "native_cleanup_random_names" : "native_cleanup_descriptors", names ? 0xe066e0 : 0x5c8ad0);
    for (unsigned i = 0; i < 40; ++i) {
        Case c = {i, names, false};
        autotest::Outcome a, b;
        autotest::runChild(before, &c, a, 2000, 10000);
        autotest::runChild(after, &c, b, 2000, 10000);
        if (coverage.observe(host, a, b)) {
            host->log("    cleanup seed%u names%d status%d/%d issue%u/%u bytes%lu/%lu\n", i, names, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue, (unsigned long)a.capture.length, (unsigned long)b.capture.length);
            coverage.report(host); return 1;
        }
    }
    coverage.report(host);
    Case c = {7, names, true};
    autotest::Outcome a, b;
    autotest::runChild(before, &c, a, 2000, 10000);
    autotest::runChild(after, &c, b, 2000, 10000);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    return !detected || autotest::incomplete(a) || autotest::incomplete(b) || !a.reportValid || !b.reportValid || a.childStatus || b.childStatus;
}
int controllerWorker(const tlhybrid_host* host) { return worker(host, false); }
int namesWorker(const tlhybrid_host* host) { return worker(host, true); }
}

TL_TEST(native_cleanup_descriptors) { return systems_fixture::isolated(controllerWorker, host); }
TL_TEST(native_cleanup_random_names) { return systems_fixture::isolated(namesWorker, host); }
