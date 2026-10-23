#include <Ogre.h>
#include "AutoTest.h"
#define private public
#include "EditorBaseObject.h"
#undef private
#include "tests/NativeEditorControls.h"
#include "SystemsFixtureWorker.h"
#include "Descriptor.h"
#include "EditorScene.h"
#include "Undo.h"

TL_ORIGINAL(void, deletedOriginal, (CUndo*, CEditorBaseObject*), "_ZN5CUndo16AddObjectDeletedEP17CEditorBaseObject")
extern "C" void deletedRecovered(CUndo*, CEditorBaseObject*) __asm__("_ZN5CUndo16AddObjectDeletedEP17CEditorBaseObject");

TL_ORIGINAL(void, addedOriginal, (CUndo*, CEditorBaseObject*), "_ZN5CUndo12AddNewObjectEP17CEditorBaseObject")
TL_ORIGINAL(void, redoOriginal, (CUndo*), "_ZN5CUndo8DoAsRedoEv")
extern "C" void addedRecovered(CUndo*, CEditorBaseObject*) __asm__("_ZN5CUndo12AddNewObjectEP17CEditorBaseObject");
extern "C" void redoRecovered(CUndo*) __asm__("_ZN5CUndo8DoAsRedoEv");

namespace {
struct Descriptor : CDescriptor {
    Descriptor() : CDescriptor(0) {}
    virtual CEditorBaseObject* CreateObject(CEditorScene*) { std::abort(); }
};
struct Case { unsigned seed; bool negative; unsigned operation; };
nativeeditor::Controls* controls;
unsigned operation;
void number(autotest::Capture& out, long long value) { out.add(&value, sizeof(value)); }

void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw);
    CEditorScene scene(L"Undo deletion recovery");
    Descriptor descriptor;
    CEditorBaseObject plain;
    CSceneNodeObject node(controls->resources, NULL);
    CPositionableObject positionable(controls->resources, NULL);
    CEditorBaseObject* object = c.seed % 3 == 0 ? &plain : c.seed % 3 == 1
        ? static_cast<CEditorBaseObject*>(&node) : static_cast<CEditorBaseObject*>(&positionable);
    object->setGuid(100 + c.seed);
    object->SetSceneOwner(c.seed % 7 == 1 ? NULL : &scene);
    object->m_pDescriptor = c.seed % 7 == 2 ? NULL : &descriptor;
    if (c.seed % 2) {
        controls->manager->EditorObjectCreated(object);
        controls->manager->getSelectedObjects()->add(object);
    }
    CUndo undo;
    for (unsigned i = 0; i < c.seed % 4; ++i) {
        CUndo::CUndoData* previous = new CUndo::CUndoData;
        previous->m_data = NULL;
        previous->m_object = c.operation == 2 && c.seed % 7 != 0 ? object : NULL;
        previous->m_action = c.seed % 3;
        previous->m_property = ~0u;
        previous->m_count = 0;
        previous->m_objectGuid = object->getGuid();
        previous->m_sceneID = 0;
        previous->m_parentGuid = -1;
        undo.m_undoData.add(previous);
    }
    unsigned previousCount = c.operation == 2 ? 0 : undo.m_undoData.size();
    controls->editor->m_iMaxUndos = c.seed % 5;
    if (c.operation == 2 && c.seed & 4) controls->editor->addUndo(new CUndo, false);
    if (c.operation == 2) {
        typedef void (*Function)(CUndo*);
        Function function = ours ? redoRecovered : redoOriginal;
        if (!autotest::beginInvocation(out, function)) return;
        function(&undo);
    } else {
        typedef void (*Function)(CUndo*, CEditorBaseObject*);
        Function function = c.operation == 0 ? (ours ? deletedRecovered : deletedOriginal)
            : (ours ? addedRecovered : addedOriginal);
        if (!autotest::beginInvocation(out, function)) return;
        function(&undo, c.seed % 7 == 0 ? NULL : object);
    }
    out.callCompleted = 1;
    number(out, undo.m_undoData.size());
    number(out, controls->manager->getObjects()->count(object->getGuid()));
    number(out, controls->manager->getSelectedObjects()->size());
    number(out, node.getVisible());
    number(out, positionable.getVisible());
    for (unsigned i = previousCount; i < undo.m_undoData.size(); ++i) {
        CUndo::CUndoData* data = undo.m_undoData[i];
        if (ours && c.negative && c.operation != 2) data->m_action = data->m_action == 1 ? 2 : 1;
        number(out, data->m_object == object);
        number(out, data->m_action);
        number(out, data->m_property);
        number(out, data->m_objectGuid);
        number(out, data->m_data == NULL);
        number(out, data->m_count);
    }
    if (ours && c.negative && c.operation == 2) controls->editor->m_Undos.push_back(new CUndo);
    number(out, controls->editor->m_bUnknown164);
    number(out, controls->editor->m_Undos.size());
    number(out, controls->editor->m_Redos.size());
    for (std::list<CUndo*>::iterator i = controls->editor->m_Undos.begin(); i != controls->editor->m_Undos.end(); ++i) {
        number(out, (*i)->m_undoData.size());
        for (unsigned j = 0; j < (*i)->m_undoData.size(); ++j) {
            CUndo::CUndoData* data = (*i)->m_undoData[j];
            number(out, data->m_action);
            number(out, data->m_object == object);
            number(out, data->m_property);
            number(out, data->m_count);
        }
    }
    controls->editor->deleteAllUndos();
    controls->manager->getObjects()->clear();
    controls->manager->getSelectedObjects()->clear();
    controls->manager->getCreatedObjects().clear();
    object->m_pDescriptor = NULL;
    object->CEditorBaseObject::SetSceneOwner(NULL);
}
void before(void* c, autotest::Capture& out) { side(c, out, false); }
void after(void* c, autotest::Capture& out) { side(c, out, true); }
int worker(const tlhybrid_host* host)
{
    nativegame::Services services;
    if (!services.ready()) return 1;
    nativeeditor::Controls actual(services);
    controls = &actual;
    const char* labels[] = {"undo_deleted_recovery", "undo_added_regression", "undo_redo_regression"};
    const unsigned long addresses[] = {0x795600, 0x7953d0, 0x795970};
    autotest::Coverage coverage(labels[operation], addresses[operation]);
    for (unsigned i = 0; i < 84; ++i) {
        Case c = {i, false, operation};
        autotest::Outcome a, b;
        autotest::runChild(before, &c, a, 2000, 10000);
        autotest::runChild(after, &c, b, 2000, 10000);
        if (coverage.observe(host, a, b)) { coverage.report(host); return 1; }
    }
    coverage.report(host);
    Case c = {4, true, operation};
    autotest::Outcome a, b;
    autotest::runChild(before, &c, a, 2000, 10000);
    autotest::runChild(after, &c, b, 2000, 10000);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    host->log("    Undo deletion negative control detected %u\n", detected ? 1u : 0u);
    return !detected || autotest::incomplete(a) || autotest::incomplete(b) || !a.reportValid || !b.reportValid || a.childStatus || b.childStatus;
}
}
TL_TEST(undo_deleted_recovery) { operation = 0; return systems_fixture::isolated(worker, host); }
TL_TEST(undo_added_regression) { operation = 1; return systems_fixture::isolated(worker, host); }
TL_TEST(undo_redo_regression) { operation = 2; return systems_fixture::isolated(worker, host); }
