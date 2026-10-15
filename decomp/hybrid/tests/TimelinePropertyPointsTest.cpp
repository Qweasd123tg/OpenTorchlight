// Typed linked-node states. Original and replacement entries are real;
// only property accessors and disposal collaborators are redirected.
#include <climits>
#include <cstddef>
#include <cstring>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "TimelineProperty.h"

TL_ORIGINAL(int, oldFreeID, (CTimelineProperty*), "_ZN17CTimelineProperty17GetFreeIDForPointEv")
TL_ORIGINAL(int, oldPointID, (CTimelineProperty*, int), "_ZN17CTimelineProperty25GetTimelinePointIDByIndexEi")
TL_ORIGINAL(CTimelineProperty::CTimelinePoint*, oldPoint, (CTimelineProperty*, int), "_ZN17CTimelineProperty16GetTimelinePointEi")
TL_ORIGINAL(float, oldTime, (CTimelineProperty*, int), "_ZN17CTimelineProperty21GetTimePercentAtPointEi")
TL_ORIGINAL(const std::wstring&, oldType, (CTimelineProperty*, int), "_ZN17CTimelineProperty24GetBaseTypeValueAsStringEi")
TL_ORIGINAL(void*, oldValue, (CTimelineProperty*, int, unsigned&), "_ZN17CTimelineProperty15GetValueAtPointEiRj")
TL_ORIGINAL(void, oldSet, (CTimelineProperty*, int, void*, unsigned), "_ZN17CTimelineProperty15SetValueAtPointEiPvj")
TL_ORIGINAL(bool, oldRemove, (CTimelineProperty*, int), "_ZN17CTimelineProperty11RemovePointEi")
extern "C" int newFreeID(CTimelineProperty*) __asm__("_ZN17CTimelineProperty17GetFreeIDForPointEv");
extern "C" int newPointID(CTimelineProperty*, int) __asm__("_ZN17CTimelineProperty25GetTimelinePointIDByIndexEi");
extern "C" CTimelineProperty::CTimelinePoint* newPoint(CTimelineProperty*, int) __asm__("_ZN17CTimelineProperty16GetTimelinePointEi");
extern "C" float newTime(CTimelineProperty*, int) __asm__("_ZN17CTimelineProperty21GetTimePercentAtPointEi");
extern "C" const std::wstring& newType(CTimelineProperty*, int) __asm__("_ZN17CTimelineProperty24GetBaseTypeValueAsStringEi");
extern "C" void* newValue(CTimelineProperty*, int, unsigned&) __asm__("_ZN17CTimelineProperty15GetValueAtPointEiRj");
extern "C" void newSet(CTimelineProperty*, int, void*, unsigned) __asm__("_ZN17CTimelineProperty15SetValueAtPointEiPvj");
extern "C" bool newRemove(CTimelineProperty*, int) __asm__("_ZN17CTimelineProperty11RemovePointEi");
TL_FUNCTION(pointGetData, "_ZN15CDescriptorProp7getDataERjP17CEditorBaseObject")
TL_FUNCTION(pointSetData, "_ZN15CDescriptorProp7setDataEPK14UNIONDATA32BITjP17CEditorBaseObject")
extern "C" char pointNodeFree[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
namespace {
typedef CTimelineProperty::CTimelinePoint Point;
typedef TLinkedListNode<Point*> Node;
typedef char HeadOffset[(offsetof(CTimelineProperty, m_timelinePoints) == 0x40) ? 1 : -1];
typedef char IDOffset[(offsetof(Point, m_pointID) == 0x98) ? 1 : -1];
typedef char TimeOffset[(offsetof(Point, m_timePercent) == 0x10) ? 1 : -1];
typedef char NodeSize[(sizeof(Node) == 24) ? 1 : -1];
struct Case { unsigned op, shape, variant; int query; };
const Case* input;
autotest::Capture* output;
Point* points[5]; Node* nodes[5];
unsigned count, calls, frees, destroys;
unsigned values[4];
void number(unsigned n) { output->add(&n, 4); }
void invalid() { output->issue = autotest::Capture::InvalidReport; }
unsigned pointIdentity(void* p) { if (!p) return 0; for (unsigned i = 0; i < count; ++i) if (p == points[i]) return i + 1; invalid(); return 999; }
unsigned nodeIdentity(void* p) { if (!p) return 0; for (unsigned i = 0; i < count; ++i) if (p == nodes[i]) return i + 1; invalid(); return 999; }
int found() { for (unsigned i = 0; i < count; ++i) if (points[i]->m_pointID == input->query) return i; return -1; }
unsigned propertyIdentity(CDescriptorProp* p) { for (unsigned i = 0; i < count; ++i) if (p == &points[i]->m_descriptorProperty) return i + 1; invalid(); return 999; }
UNIONDATA32BIT* getData(CDescriptorProp* p, unsigned& size, CEditorBaseObject* object) {
    ++calls; number(1); number(propertyIdentity(p)); number(size); number(object == NULL);
    if (object != NULL) invalid();
    size = input->variant + 17;
    return input->variant & 1 ? NULL : reinterpret_cast<UNIONDATA32BIT*>(values);
}
void setData(CDescriptorProp* p, const UNIONDATA32BIT* data, unsigned size, CEditorBaseObject* object) {
    ++calls; number(2); number(propertyIdentity(p)); number(size); number(object == NULL);
    number(data == reinterpret_cast<UNIONDATA32BIT*>(values)); output->add(data, sizeof(values));
    if (object != NULL || data != reinterpret_cast<UNIONDATA32BIT*>(values) || size != input->variant) invalid();
}
void releaseNode(void* p) {
    ++frees; number(3); unsigned id = nodeIdentity(p); number(id);
    if (id < 1 || id > count) return;
    if (nodes[id - 1]->m_pNext != NULL || nodes[id - 1]->m_pPrevious != NULL || destroys != 0) invalid();
}
void destroyPoint(Point* p) {
    ++destroys; number(4); number(pointIdentity(p));
    if (frees != 1) invalid();
}
void side(Case& c, bool ours, autotest::Capture& capture) {
    input = &c; output = &capture; calls = frees = destroys = 0;
    unsigned long long receiverStorage[(sizeof(CTimelineProperty) + 7) / 8];
    unsigned long long pointStorage[5][sizeof(Point) / 8]; Node nodeStorage[5];
    std::memset(receiverStorage, 0xa5, sizeof(receiverStorage));
    std::memset(pointStorage, 0x3c, sizeof(pointStorage)); std::memset(nodeStorage, 0, sizeof(nodeStorage));
    CTimelineProperty* self = reinterpret_cast<CTimelineProperty*>(receiverStorage);
    const unsigned lengths[] = {0, 1, 1, 3, 4, 5}; count = lengths[c.shape];
    const int ids[6][5] = {{0}, {0}, {INT_MAX}, {2, 0, 1}, {7, 7, 2, 0}, {INT_MIN, INT_MAX, -1, 1, 3}};
    const unsigned timeBits[] = {0, 0x80000000u, 0x3f000000u, 0xbf800000u, 0x7fc12345u, 0x7f800000u, 1, 0xff800000u};
    void* pointVtable[2] = {reinterpret_cast<void*>(&destroyPoint), reinterpret_cast<void*>(&destroyPoint)};
    for (unsigned i = 0; i < count; ++i) {
        points[i] = reinterpret_cast<Point*>(pointStorage[i]); nodes[i] = &nodeStorage[i];
        void* table = pointVtable; std::memcpy(points[i], &table, sizeof(table));
        points[i]->m_pointID = ids[c.shape][i];
        unsigned bits = timeBits[(c.variant + i) % 8]; std::memcpy(&points[i]->m_timePercent, &bits, 4);
        points[i]->m_descriptorProperty.m_eType = static_cast<EVARIABLE_TYPES>((c.variant + i + c.shape) % 10);
        points[i]->m_descriptorProperty.m_pInterpreter = c.variant == 5 ? reinterpret_cast<CDescriptorPropertyInterpreter*>(values) : NULL;
        nodes[i]->m_Data = points[i]; nodes[i]->m_pNext = i + 1 < count ? &nodeStorage[i + 1] : NULL;
        nodes[i]->m_pPrevious = i ? &nodeStorage[i - 1] : NULL;
    }
    self->m_timelinePoints = count ? nodes[0] : NULL;
    self->m_editorScene = (c.variant + c.shape) % 3 == 0 ? NULL : reinterpret_cast<CEditorScene*>(values);
    for (unsigned i = 0; i < 4; ++i) values[i] = 0x12340000u + c.variant * 17 + i;
    int match = found(); unsigned initialSize = 0x80000000u + c.variant;
    unsigned char beforeReceiver[sizeof(receiverStorage)], beforePoints[sizeof(pointStorage)];
    std::memcpy(beforeReceiver, receiverStorage, sizeof(receiverStorage)); std::memcpy(beforePoints, pointStorage, sizeof(pointStorage));
    detour::Set patches;
    if (c.op == 5) TL_REDIRECT(patches, pointGetData, &getData);
    if (c.op == 6) TL_REDIRECT(patches, pointSetData, &setData);
    if (c.op == 7) patches.redirect(pointNodeFree, pointNodeFree, &releaseNode);
    if (patches.failed()) { invalid(); return; }
    switch (c.op) {
    case 0: {
        int (*fn)(CTimelineProperty*) = ours ? newFreeID : oldFreeID;
        if (!autotest::beginInvocation(capture, fn)) return; int result = fn(self); capture.callCompleted = 1; number(result);
        int expected = 0; bool occupied = true;
        while (occupied) { occupied = false; for (unsigned i = 0; i < count; ++i) if (ids[c.shape][i] == expected) occupied = true; if (occupied) ++expected; }
        if (result != expected) invalid(); break;
    }
    case 1: {
        int (*fn)(CTimelineProperty*, int) = ours ? newPointID : oldPointID;
        if (!autotest::beginInvocation(capture, fn)) return; int result = fn(self, c.query); capture.callCompleted = 1; number(result);
        if (result != (c.query >= 0 && static_cast<unsigned>(c.query) < count ? ids[c.shape][c.query] : -1)) invalid(); break;
    }
    case 2: {
        Point* (*fn)(CTimelineProperty*, int) = ours ? newPoint : oldPoint;
        if (!autotest::beginInvocation(capture, fn)) return; Point* result = fn(self, c.query); capture.callCompleted = 1; number(pointIdentity(result));
        if (result != (match >= 0 ? points[match] : NULL)) invalid(); break;
    }
    case 3: {
        float (*fn)(CTimelineProperty*, int) = ours ? newTime : oldTime;
        if (!autotest::beginInvocation(capture, fn)) return; float result = fn(self, c.query); capture.callCompleted = 1; capture.add(&result, 4);
        unsigned expected = match >= 0 ? timeBits[(c.variant + match) % 8] : 0; if (std::memcmp(&result, &expected, 4)) invalid(); break;
    }
    case 4: {
        const std::wstring& (*fn)(CTimelineProperty*, int) = ours ? newType : oldType;
        if (!autotest::beginInvocation(capture, fn)) return; const std::wstring& result = fn(self, c.query); capture.callCompleted = 1;
        number(result.size()); capture.add(result.c_str(), result.size() * sizeof(wchar_t));
        unsigned type = c.variant == 5 ? 5 : (c.variant + match + c.shape) % 10;
        if (result != (match >= 0 ? KEditorObjectPropertyTypeNames[type] : std::wstring())) invalid(); break;
    }
    case 5: {
        void* (*fn)(CTimelineProperty*, int, unsigned&) = ours ? newValue : oldValue;
        if (!autotest::beginInvocation(capture, fn)) return; void* result = fn(self, c.query, initialSize); capture.callCompleted = 1;
        number(result == values); number(result == NULL); number(initialSize);
        bool action = match >= 0 && self->m_editorScene != NULL;
        if (calls != unsigned(action) || initialSize != (action ? c.variant + 17 : 0x80000000u + c.variant) ||
            result != (action && !(c.variant & 1) ? values : NULL)) invalid(); break;
    }
    case 6: {
        void (*fn)(CTimelineProperty*, int, void*, unsigned) = ours ? newSet : oldSet;
        void* data = c.variant % 3 ? values : NULL;
        if (!autotest::beginInvocation(capture, fn)) return; fn(self, c.query, data, c.variant); capture.callCompleted = 1;
        if (calls != unsigned(match >= 0 && self->m_editorScene != NULL && data != NULL)) invalid(); break;
    }
    case 7: {
        bool (*fn)(CTimelineProperty*, int) = ours ? newRemove : oldRemove;
        if (!autotest::beginInvocation(capture, fn)) return; bool result = fn(self, c.query); capture.callCompleted = 1; number(result);
        if (result != (match >= 0) || frees != unsigned(match >= 0) || destroys != unsigned(match >= 0)) invalid();
        number(nodeIdentity(self->m_timelinePoints));
        for (unsigned i = 0; i < count; ++i) { number(pointIdentity(nodes[i]->m_Data)); number(nodeIdentity(nodes[i]->m_pNext)); number(nodeIdentity(nodes[i]->m_pPrevious)); }
        // The only receiver change is its head when the first node is removed.
        self->m_timelinePoints = count ? nodes[0] : NULL; break;
    }
    }
    number(calls); number(frees); number(destroys);
    if (std::memcmp(beforeReceiver, receiverStorage, sizeof(receiverStorage)) || std::memcmp(beforePoints, pointStorage, sizeof(pointStorage))) invalid();
    if (c.op != 7) for (unsigned i = 0; i < count; ++i) {
        if (nodes[i]->m_Data != points[i] || nodes[i]->m_pNext != (i + 1 < count ? nodes[i + 1] : NULL) ||
            nodes[i]->m_pPrevious != (i ? nodes[i - 1] : NULL)) invalid();
    }
    patches.restore();
}
void original(void* c, autotest::Capture& capture) { side(*static_cast<Case*>(c), false, capture); }
void recovered(void* c, autotest::Capture& capture) { side(*static_cast<Case*>(c), true, capture); }
}
TL_TEST(timeline_property_points_differential) {
    const uint64_t addresses[] = {(uint64_t)(uintptr_t)&oldFreeID, (uint64_t)(uintptr_t)&oldPointID, (uint64_t)(uintptr_t)&oldPoint,
        (uint64_t)(uintptr_t)&oldTime, (uint64_t)(uintptr_t)&oldType, (uint64_t)(uintptr_t)&oldValue, (uint64_t)(uintptr_t)&oldSet,
        (uint64_t)(uintptr_t)&oldRemove};
    const int queries[] = {-1, 0, 1, 2, 3, 7, INT_MIN, INT_MAX};
    for (unsigned op = 0; op < 8; ++op) {
        autotest::Coverage coverage("timeline_property_points_differential", addresses[op]);
        for (unsigned shape = 0; shape < 6; ++shape) for (unsigned q = 0; q < 8; ++q) {
            Case c = {op, shape, q, queries[q]}; autotest::Outcome a, b;
            autotest::runChild(original, &c, a); autotest::runChild(recovered, &c, b);
            if (coverage.observe(host, a, b)) { host->log("    timeline property op %u shape %u query %u\n", op, shape, q); coverage.report(host); return 1; }
        }
        coverage.report(host);
    }
    return 0;
}
