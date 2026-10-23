#include <Ogre.h>
#include "AutoTest.h"
#define private public
#include "ResourceManager.h"
#undef private
#include "tests/NativeEditorControls.h"
#include "tests/SystemsFixtureWorker.h"
#include "EditorScene.h"
#include "Layout.h"
#include "RandomGroup.h"
#include "Utilities.h"
#include <vector>

TL_ORIGINAL(void, randomGroupOldCalculate, (CRandomGroup*), "_ZN12CRandomGroup17calculateChildrenEv")
TL_ORIGINAL(void, randomGroupOldChoose, (CRandomGroup*, TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&), "_ZN12CRandomGroup28chooseChildrenByRandomChoiceER10TArrayListIPS_ERS0_IP17CEditorBaseObjectE")
extern "C" void randomGroupNewCalculate(CRandomGroup*) __asm__("_ZN12CRandomGroup17calculateChildrenEv");
extern "C" void randomGroupNewChoose(CRandomGroup*, TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&) __asm__("_ZN12CRandomGroup28chooseChildrenByRandomChoiceER10TArrayListIPS_ERS0_IP17CEditorBaseObjectE");

namespace {
struct Case { unsigned seed; bool choose; bool negative; };
nativegame::Services* services;
nativeeditor::Controls* controls;
void number(autotest::Capture& out, long long value) { out.add(&value, sizeof(value)); }
void vector(autotest::Capture& out, const Ogre::Vector3& v) { out.add(v.ptr(), 12); }
void identity(autotest::Capture& out, CEditorBaseObject* p) { number(out, p ? p->getGuid() : -1); }
void listState(autotest::Capture& out, TArrayList<CEditorBaseObject*>& list)
{
    number(out, list.size());
    for (unsigned i = 0; i < list.size(); ++i) identity(out, list[i]);
    // Capacity and grow-by are observable output-container state.
    const char* raw = reinterpret_cast<const char*>(&list);
    unsigned capacity, grow;
    std::memcpy(&capacity, raw + 12, 4);
    std::memcpy(&grow, raw + 16, 4);
    number(out, capacity); number(out, grow);
}

void add(CEditorScene& scene, CEditorBaseObject* object, long long guid, long long parent)
{
    object->setGuid(guid);
    object->setParentGuid(parent);
    object->SetSceneOwner(&scene);
    scene.getObjects()[guid] = object;
}

void calculate(const Case& c, autotest::Capture& out, bool ours)
{
    CResourceManager* resources = controls->resources;
    controls->editor->m_iFlags = 2;
    CEditorScene scene(L"random group native scene");
    scene.setResourceManager(resources);
    scene.setVisible(true);
    CRandomGroup root(resources);
    add(scene, &root, 100, -1);
    root.setPosition(Ogre::Vector3(3.25f, -5.5f, 11.75f));
    std::vector<CEditorBaseObject*> objects;
    std::vector<CLayout*> layouts;
    const unsigned sizes[] = {0, 1, 3, 12, 27};
    unsigned count = sizes[c.seed % 5];
    unsigned layoutCount = c.seed % 7 == 6 ? 13 : c.seed % 4;
    for (unsigned i = 0; i < layoutCount; ++i) {
        CLayout* layout = new CLayout(resources, static_cast<ELAYOUT_TYPES>(0));
        long long parent = i && c.seed % 3 == 0 ? layouts[i - 1]->getGuid() : root.getGuid();
        add(scene, layout, 1000 + i, parent);
        layout->setPosition(Ogre::Vector3(float(i) + 2, -3, float(i) * 1.5f));
        objects.push_back(layout); layouts.push_back(layout);
    }
    for (unsigned i = 0; i < count; ++i) {
        CEditorBaseObject* object = i % 7 == 3 ? static_cast<CEditorBaseObject*>(new CEditorBaseObject)
            : i % 6 == 4 ? static_cast<CEditorBaseObject*>(new CRandomGroup(resources))
            : static_cast<CEditorBaseObject*>(new CPositionableObject(resources, services->scene));
        long long parent = i % 5 == 2 ? -1 : i % 5 == 4 ? 999999 : root.getGuid();
        if (i % 5 == 1 && !layouts.empty()) parent = layouts[i % layouts.size()]->getGuid();
        if (i % 5 == 3 && i != 0) parent = objects.back()->getGuid();
        add(scene, object, 2000 + i, parent);
        CPositionableObject* positionable = dynamic_cast<CPositionableObject*>(object);
        if (positionable) positionable->setPosition(Ogre::Vector3(float(i) * 2 - 10, float(i) * .25f, 7 - float(i)));
        objects.push_back(object);
    }
    // Existing entries are not cleared at entry. Repeated editor calls append;
    // runtime calls reparent relative to the root and finally clear the array.
    for (unsigned i = 0; i < c.seed % 4 && i < objects.size(); ++i) {
        CPositionableObject* object = dynamic_cast<CPositionableObject*>(objects[i]);
        if (object) root.m_children.add(object);
    }
    controls->editor->m_iFlags = c.seed / 5 % 2 ? 0 : 2;
    if (c.seed % 17 == 11) root.CEditorBaseObject::SetSceneOwner(NULL);
    if (c.seed % 17 == 12) root.setResourceManager(NULL);
    if (c.seed % 17 == 13) root.m_bIsDynamicGroup = false;
    typedef void (*Call)(CRandomGroup*);
    Call call = ours ? randomGroupNewCalculate : randomGroupOldCalculate;
    if (!autotest::beginInvocation(out, call)) return;
    call(&root);
    if (c.seed % 3 == 1) call(&root);
    out.callCompleted = 1;
    if (ours && c.negative) root.m_children.add(&root);
    number(out, root.m_children.size());
    for (unsigned i = 0; i < root.m_children.size(); ++i) identity(out, root.m_children[i]);
    identity(out, root.getSceneOwner());
    number(out, root.getResourceManager() == resources);
    vector(out, root.getPosition(false));
    for (unsigned i = 0; i < objects.size(); ++i) {
        CEditorBaseObject* object = objects[i];
        identity(out, object); number(out, object->getParentGuid());
        identity(out, object->getParentPositionableObject());
        CPositionableObject* positionable = dynamic_cast<CPositionableObject*>(object);
        number(out, positionable != NULL);
        if (positionable) {
            vector(out, positionable->getPosition(false));
            number(out, positionable->getSceneNode() != NULL);
            if (positionable->getSceneNode()) {
                vector(out, positionable->getSceneNode()->getPosition());
                number(out, positionable->getSceneNode()->getParentSceneNode() == root.getSceneNode());
            }
        }
    }
    root.CEditorBaseObject::SetSceneOwner(NULL);
    root.setResourceManager(resources);
    root.m_children.clear();
    scene.getObjects().clear();
    controls->editor->m_iFlags = 2;
    for (unsigned i = objects.size(); i != 0; --i) {
        objects[i - 1]->CEditorBaseObject::SetSceneOwner(NULL);
        delete objects[i - 1];
    }
}

void choose(const Case& c, autotest::Capture& out, bool ours)
{
    CResourceManager* resources = controls->resources;
    controls->editor->m_iFlags = 2;
    resources->m_bFlag3 = c.seed / 9 % 5 == 4;
    CRandomGroup root(resources);
    root.setGuid(100);
    root.m_iRandomType = c.seed % 4;
    const int picks[] = {-3, 0, 1, 2, 5, 30};
    root.m_iNumberOfPicks = picks[c.seed / 4 % 6];
    if (c.seed / 13 % 5 == 4) root.m_sPlayerClassName = L"No native client of this class";
    const unsigned counts[] = {0, 1, 3, 7, 18};
    unsigned count = counts[c.seed / 3 % 5];
    TArrayList<CRandomGroup*> input(3);
    TArrayList<CEditorBaseObject*> output(c.seed % 5 + 1);
    CEditorBaseObject sentinel;
    sentinel.setGuid(77);
    for (unsigned i = 0; i < c.seed % 3; ++i) output.add(&sentinel);
    std::vector<CRandomGroup*> allocated;
    const unsigned weights[] = {0, 1, 30, 99, 100, 101, 0xffffffffu, 0x80000000u};
    for (unsigned i = 0; i < count; ++i) {
        if ((i + c.seed) % 9 == 3) { input.add(NULL); continue; }
        CRandomGroup* group = new CRandomGroup(resources);
        group->setGuid(2000 + i);
        group->SetRandomWeight(weights[(i + c.seed / 5) % 8]);
        input.add(group); allocated.push_back(group);
    }
    UTILITIES::setSeed(int((c.seed + 1) * 2654435761u));
    typedef void (*Call)(CRandomGroup*, TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&);
    Call call = ours ? randomGroupNewChoose : randomGroupOldChoose;
    if (!autotest::beginInvocation(out, call)) return;
    call(&root, input, output);
    out.callCompleted = 1;
    if (ours && c.negative) output.add(&sentinel);
    listState(out, output);
    number(out, UTILITIES::getRandState());
    number(out, input.size());
    for (unsigned i = 0; i < input.size(); ++i) {
        identity(out, input[i]);
        if (input[i]) number(out, input[i]->GetRandomWeight());
    }
    for (unsigned i = 0; i < allocated.size(); ++i) delete allocated[i];
    resources->m_bFlag3 = false;
}

void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw);
    if (c.choose) choose(c, out, ours);
    else calculate(c, out, ours);
}
void before(void* c, autotest::Capture& out) { side(c, out, false); }
void after(void* c, autotest::Capture& out) { side(c, out, true); }
bool choosing;
int worker(const tlhybrid_host* host)
{
    nativegame::Services actualServices;
    services = &actualServices;
    if (!services->ready()) return 1;
    nativeeditor::Controls actualControls(*services);
    controls = &actualControls;
    controls->game.game->m_sceneManager = services->scene;
    autotest::Coverage coverage(choosing ? "random_group_choose" : "random_group_calculate",
                               choosing ? 0x9f9c00 : 0x9f1e40);
    unsigned count = choosing ? 240 : 144;
    int failures = 0;
    for (unsigned i = 0; i < count; ++i) {
        Case c = {i, choosing, false};
        autotest::Outcome a, b;
        autotest::runChild(before, &c, a, 2000, 10000);
        autotest::runChild(after, &c, b, 2000, 10000);
        if (coverage.observe(host, a, b)) {
            host->log("    random group case%u choose%d status%d/%d issue%u/%u bytes%lu/%lu\n", i, choosing,
                      a.childStatus, b.childStatus, a.capture.issue, b.capture.issue,
                      (unsigned long)a.capture.length, (unsigned long)b.capture.length);
            for (size_t j = 0; j < a.capture.length && j < b.capture.length; ++j)
                if (a.capture.data[j] != b.capture.data[j]) { host->log("    mismatch byte %lu\n", (unsigned long)j); break; }
            ++failures; break;
        }
    }
    coverage.report(host);
    Case negative = {24, choosing, true};
    autotest::Outcome a, b;
    autotest::runChild(before, &negative, a, 2000, 10000);
    autotest::runChild(after, &negative, b, 2000, 10000);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    TL_CHECK(failures, detected && !autotest::incomplete(a) && !autotest::incomplete(b) &&
        a.reportValid && b.reportValid && !a.childStatus && !b.childStatus);
    host->log("    random group negative control detected %d\n", detected);
    return failures + (coverage.completed != count);
}
}

TL_TEST(random_group_calculate) { choosing = false; return systems_fixture::isolated(worker, host); }
TL_TEST(random_group_choose) { choosing = true; return systems_fixture::isolated(worker, host); }
