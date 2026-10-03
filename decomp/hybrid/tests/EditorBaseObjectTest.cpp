// Shadow test: editor API functions of EditorBaseObject.cpp that differ from the
// original only in register allocation or block layout. gEditor points at a
// fake editor whose object manager holds a real std::map of fake objects.
#include <cstring>
#include <map>

#include "Editor.h"
#include "EditorBaseObject.h"
#include "EditorDLL.h"
#include "HybridTest.h"
#include "TArrayList.h"

TL_ORIGINAL(int, originalGetObjectDescriptorID, (long long), "_Z27EditorGetObjectDescriptorIDx")
TL_ORIGINAL(void, originalParticleMovementConfig, (float&, float&, bool), "_Z28EditorParticleMovementConfigRfS_b")

namespace
{

// CEditor offsets (from CEditor::CEditor).
const int kEditorSize = 0x1f8;
const int kDisabled = 0x49;
const int kEditorResourceManager = 0x58;
const int kObjectManager = 0x120;
const int kParticleMovementA = 0x1c0;
const int kParticleMovementB = 0x1c4;

// CEditorBaseObject offsets.
const int kObjectSize = 0x58;
const int kGuid = 0x10;
const int kDescriptor = 0x38;
const int kSceneOwner = 0x48;
// CEditorScene::m_pDescriptorManager.
const int kDescriptorManager = 0x100;

struct FakeObjectManager
{
    void* vptr;
    void* safePointers;
    std::map<long long, CEditorBaseObject*> objects;
    TArrayList<CEditorBaseObject*> selected;
    TArrayList<CEditorBaseObject*> created;
    void* control;
    bool flags[2];
};

const int kObjects = 6;

char g_editor[kEditorSize];
char g_objects[kObjects][kObjectSize];
char g_scenes[2][0x190];
char g_dummy[16];
FakeObjectManager* g_manager;

unsigned int g_seed = 9001;

unsigned int nextRandom()
{
    g_seed = g_seed * 1103515245u + 12345u;
    return g_seed >> 8;
}

void setPointer(char* object, int offset, const void* value)
{
    std::memcpy(object + offset, &value, sizeof(value));
}

void randomEditor()
{
    g_editor[kDisabled] = char(nextRandom() % 5 == 0);
    setPointer(g_editor, kEditorResourceManager, (nextRandom() % 5 == 0) ? 0 : g_dummy);
    setPointer(g_editor, kObjectManager, g_manager);
}

void randomWorld()
{
    g_manager->objects.clear();
    setPointer(g_scenes[0], kDescriptorManager, 0);
    setPointer(g_scenes[1], kDescriptorManager, g_dummy);
    for (int i = 0; i < kObjects; i++)
    {
        std::memset(g_objects[i], 0, kObjectSize);
        long long guid = 100 + i;
        std::memcpy(g_objects[i] + kGuid, &guid, sizeof(guid));
        unsigned int scene = nextRandom() % 3;
        setPointer(g_objects[i], kSceneOwner, scene == 2 ? 0 : g_scenes[scene]);
        setPointer(g_objects[i], kDescriptor, (nextRandom() % 3) ? g_dummy : 0);
        if (nextRandom() % 4)
            g_manager->objects[guid] = reinterpret_cast<CEditorBaseObject*>(g_objects[i]);
    }
}

} // namespace

TL_TEST(EditorBaseObject_shadow)
{
    int failures = 0;
    CEditor* savedEditor = gEditor;
    gEditor = reinterpret_cast<CEditor*>(g_editor);
    // Constructed here: the blob does not run static constructors.
    g_manager = new FakeObjectManager();
    TL_CHECK(failures, sizeof(CEditor) == kEditorSize);

    for (int step = 0; step < 20000 && failures == 0; step++)
    {
        randomEditor();
        if (nextRandom() % 2)
        {
            randomWorld();
            long long guid = (nextRandom() % 8 == 0) ? -1 : 98 + int(nextRandom() % (kObjects + 4));
            int expected = originalGetObjectDescriptorID(guid);
            int actual = EditorGetObjectDescriptorID(guid);
            TL_CHECK(failures, expected == actual);
        }
        else
        {
            bool set = nextRandom() % 2;
            float a0 = float(nextRandom() % 1000) / 7.0f;
            float b0 = float(nextRandom() % 1000) / 9.0f;
            float fieldA = float(nextRandom() % 1000) / 3.0f;
            float fieldB = float(nextRandom() % 1000) / 5.0f;
            char before[kEditorSize];
            std::memcpy(g_editor + kParticleMovementA, &fieldA, 4);
            std::memcpy(g_editor + kParticleMovementB, &fieldB, 4);
            std::memcpy(before, g_editor, kEditorSize);

            float a1 = a0, b1 = b0;
            originalParticleMovementConfig(a1, b1, set);
            char afterOriginal[kEditorSize];
            std::memcpy(afterOriginal, g_editor, kEditorSize);

            std::memcpy(g_editor, before, kEditorSize);
            float a2 = a0, b2 = b0;
            EditorParticleMovementConfig(a2, b2, set);
            TL_CHECK(failures, std::memcmp(&a1, &a2, 4) == 0 && std::memcmp(&b1, &b2, 4) == 0);
            TL_CHECK(failures, std::memcmp(afterOriginal, g_editor, kEditorSize) == 0);
        }
        if (failures)
            host->log("    step %d\n", step);
    }

    delete g_manager;
    g_manager = 0;
    gEditor = savedEditor;
    return failures;
}
