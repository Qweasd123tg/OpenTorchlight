#include "AutoTest.h"
#include "tests/SystemsFixtureWorker.h"
#include "Timeline.h"
#include "TimelineProperty.h"
#include "SafePointer.h"
#include <cstring>

TL_ORIGINAL(void, oldPropertyConstructor,
    (CTimelineProperty*, CTimeline*, CEditorScene*, CDescriptor*, CDescriptorProp*, long long),
    "_ZN17CTimelinePropertyC1EP9CTimelineP12CEditorSceneP11CDescriptorP15CDescriptorPropx")
extern "C" void newPropertyConstructor(CTimelineProperty*, CTimeline*, CEditorScene*,
    CDescriptor*, CDescriptorProp*, long long)
    __asm__("_ZN17CTimelinePropertyC1EP9CTimelineP12CEditorSceneP11CDescriptorP15CDescriptorPropx");
TL_ORIGINAL(void, oldPropertyDestructor, (CTimelineProperty*), "_ZN17CTimelinePropertyD1Ev")
extern "C" void newPropertyDestructor(CTimelineProperty*) __asm__("_ZN17CTimelinePropertyD1Ev");

namespace {
struct Case { unsigned operation, index; bool negative; };
struct Descriptor : CDescriptor {
    Descriptor() : CDescriptor(0) {}
    CEditorBaseObject* CreateObject(CEditorScene*) { return NULL; }
    void add(CDescriptorProp* property, unsigned id)
    {
        m_PropertyIDs[property->m_sName] = id;
        m_Properties.add(property);
    }
};
typedef CTimelineProperty::CTimelinePoint Point;
typedef TLinkedListNode<Point*> Node;
autotest::Capture* currentCapture;
unsigned deletionCalls;
template<class T> void captureValue(autotest::Capture& out, T value)
{
    out.add(&value, sizeof(value));
}

// A real timeline point with an observing destructor; the native point and
// descriptor-property destructors still own all their normal member cleanup.
struct ObservedPoint : Point {
    ObservedPoint(CDescriptorProp* property, int id) : Point(property, NULL, id), node(NULL) {}
    ~ObservedPoint()
    {
        ++deletionCalls;
        captureValue(*currentCapture, m_pointID);
        captureValue(*currentCapture, node->m_pNext == NULL && node->m_pPrevious == NULL);
    }
    Node* node;
};

void side(void* raw, autotest::Capture& out, bool ours)
{
    Case c = *static_cast<Case*>(raw);
    currentCapture = &out;
    deletionCalls = 0;
    CTimeline timeline;
    CEditorScene scene(L"timeline-owner-recovery");
    Descriptor descriptor;
    const wchar_t* names[] = {L"", L"FLOAT", L"POSITION", L"mixed Case", L"Имя свойства", L"missing"};
    CDescriptorProp source(L"category", names[c.index % 6], L"description", NULL, NULL,
                           static_cast<EVARIABLE_TYPES>(2 + c.index % 8), 0);
    unsigned count = (c.index / 6) % 5;
    for (unsigned i = 0; i < count; ++i)
    {
        std::wstring name = names[i];
        if (i == 3)
            name.append(96, L'x');
        CDescriptorProp* property = new CDescriptorProp(L"category", name, L"description",
            NULL, NULL, VARIABLE_TYPE_FLOAT, 0);
        descriptor.add(property, 7 + i * 11);
    }
    UNIONDATA32BIT value;
    for (unsigned i = 0; i < c.index % 7; ++i)
    {
        value.m_iValue = int(i * 19) - 7;
        source.m_DefaultValue.add(value);
    }
    union Storage { long double alignment; unsigned char bytes[sizeof(CTimelineProperty)]; } storage;
    std::memset(&storage, 0x5a, sizeof(storage));
    CTimelineProperty* property = reinterpret_cast<CTimelineProperty*>(storage.bytes);
    CTimeline* timelineArgument = c.index & 1 ? &timeline : NULL;
    CEditorScene* sceneArgument = c.index & 2 ? &scene : NULL;
    const long long identifiers[] = {-1, 0, 17, 0x123456789abcdefLL};
    long long identifier = identifiers[c.index % 4];
    if (c.operation == 0)
    {
        typedef void (*Fn)(CTimelineProperty*, CTimeline*, CEditorScene*, CDescriptor*, CDescriptorProp*, long long);
        Fn function = ours ? newPropertyConstructor : oldPropertyConstructor;
        if (!autotest::beginInvocation(out, function)) return;
        function(property, timelineArgument, sceneArgument, &descriptor, &source, identifier);
        out.callCompleted = 1;
        if (ours && c.negative) ++property->m_propertyID;
        captureValue(out, property->m_objectID);
        captureValue(out, property->m_propertyID);
        captureValue(out, property->m_eventID);
        captureValue(out, property->m_inputEvent);
        captureValue(out, property->m_lastTimePercent);
        captureValue(out, property->m_editorScene == sceneArgument);
        captureValue(out, property->m_descriptor == &descriptor);
        captureValue(out, property->m_descriptorProperty == &source);
        captureValue(out, static_cast<Node*>(property->m_timelinePoints) == NULL);
        captureValue(out, property->m_interpolationType);
        captureValue(out, property->m_spline == NULL);
        captureValue(out, property->m_timeline == timelineArgument);
        captureValue(out, property->m_updating);
        TSafePointer<CTimelineProperty> weak;
        weak.setObject(property);
        oldPropertyDestructor(property);
        captureValue(out, weak.getObject() == NULL);
        return;
    }
    oldPropertyConstructor(property, timelineArgument, sceneArgument, &descriptor, &source, identifier);
    const unsigned counts[] = {0, 1, 2, 7, 19};
    unsigned points = counts[c.index % 5];
    TSafePointer<Point> weakPoints[20];
    Node* tail = NULL;
    for (unsigned i = 0; i < points; ++i)
    {
        Node* node = new Node;
        node->m_pPrevious = tail;
        node->m_pNext = NULL;
        if (tail) tail->m_pNext = node;
        else property->m_timelinePoints = node;
        tail = node;
        node->m_Data = NULL;
        if ((i + c.index / 5) % 4 != 1)
        {
            ObservedPoint* point = new ObservedPoint(&source, int(i));
            point->node = node;
            node->m_Data = point;
            weakPoints[i].setObject(point);
        }
    }
    if (c.index & 1)
    {
        property->m_spline = new Ogre::SimpleSpline;
        property->m_spline->setAutoCalculate(false);
        for (unsigned i = 0; i < c.index % 6; ++i)
            property->m_spline->addPoint(Ogre::Vector3(float(i), float(i * i), -float(i)));
        property->m_spline->recalcTangents();
    }
    TSafePointer<CTimelineProperty> weakOwner;
    weakOwner.setObject(property);
    typedef void (*Fn)(CTimelineProperty*);
    Fn function = ours ? newPropertyDestructor : oldPropertyDestructor;
    if (!autotest::beginInvocation(out, function)) return;
    function(property);
    out.callCompleted = 1;
    if (ours && c.negative) ++deletionCalls;
    captureValue(out, deletionCalls);
    captureValue(out, weakOwner.getObject() == NULL);
    for (unsigned i = 0; i < points; ++i)
        captureValue(out, weakPoints[i].getObject() == NULL);
    captureValue(out, property->m_spline == NULL);
    captureValue(out, static_cast<Node*>(property->m_timelinePoints) == NULL);
}
void original(void* raw, autotest::Capture& out) { side(raw, out, false); }
void replacement(void* raw, autotest::Capture& out) { side(raw, out, true); }

int run(const tlhybrid_host* host, unsigned operation)
{
    const char* name = operation ? "timeline_owner_destructor" : "timeline_owner_constructor";
    uint64_t address = operation ? 0x7ccae0 : 0x7c9960;
    autotest::Coverage coverage(name, address);
    for (unsigned i = 0; i < 64; ++i)
    {
        Case c = {operation, i, false};
        autotest::Outcome a, b;
        autotest::runChild(original, &c, a, 2000, 10000);
        autotest::runChild(replacement, &c, b, 2000, 10000);
        if (coverage.observe(host, a, b))
        {
            host->log("    case %u original status %d issue %u completed %u; candidate status %d issue %u completed %u\n",
                i, a.childStatus, a.capture.issue, a.capture.callCompleted,
                b.childStatus, b.capture.issue, b.capture.callCompleted);
            coverage.report(host);
            return 1;
        }
    }
    coverage.report(host);
    Case negative = {operation, 19, true};
    autotest::Outcome a, b;
    autotest::runChild(original, &negative, a, 2000, 10000);
    autotest::runChild(replacement, &negative, b, 2000, 10000);
    bool detected = a.capture.callCompleted && b.capture.callCompleted &&
        !a.capture.issue && !b.capture.issue && !a.childStatus && !b.childStatus &&
        (a.capture.length != b.capture.length ||
         std::memcmp(a.capture.data, b.capture.data, a.capture.length));
    host->log("    negative control detected=%u\n", unsigned(detected));
    return coverage.completed != 64 || coverage.different || coverage.missing || !detected;
}
int constructorWorker(const tlhybrid_host* host) { return run(host, 0); }
int destructorWorker(const tlhybrid_host* host) { return run(host, 1); }
}
TL_TEST(timeline_owner_constructor) { return systems_fixture::isolated(constructorWorker, host); }
TL_TEST(timeline_owner_destructor) { return systems_fixture::isolated(destructorWorker, host); }
