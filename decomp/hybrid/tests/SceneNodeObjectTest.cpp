// Shadow test: CSceneNodeObject methods that differ from the original only in
// block layout, run on identical objects whose Ogre collaborators are fakes.
#include <cstring>

#include "FakeVtable.h"
#include "HybridTest.h"
#include "SceneNodeObject.h"

TL_ORIGINAL(void, originalSetResourceManager, (void*, CResourceManager*),
            "_ZN16CSceneNodeObject18setResourceManagerEP16CResourceManager")
TL_ORIGINAL(void, originalSetParentPositionableObject, (void*, CPositionableObject*),
            "_ZN16CSceneNodeObject27setParentPositionableObjectEP19CPositionableObject")

namespace
{

// CSceneNodeObject layout (offsets checked against the original constructor).
const int kSize = 0x88;
const int kParentPositionable = 0x50;
const int kSceneNode = 0x58;
const int kEntity = 0x60;
const int kResourceManager = 0x68;
const int kParentSceneNode = 0x70;
const int kSceneManager = 0x78;
const int kKeepParent = 0x80;
const int kVisible = 0x81;
const int kEnabled = 0x82;

unsigned int g_seed = 4242;

unsigned int nextRandom()
{
    g_seed = g_seed * 1103515245u + 12345u;
    return g_seed >> 8;
}

void setPointer(char* object, int offset, const void* value)
{
    std::memcpy(object + offset, &value, sizeof(value));
}

const void* pick(const void* a, const void* b, const void* c)
{
    switch (nextRandom() % 3)
    {
    case 0:
        return a;
    case 1:
        return b;
    default:
        return c;
    }
}

struct World
{
    fake::Object sceneManagerA;
    fake::Object sceneManagerB;
    fake::Object createdNode;
    fake::Object rootNode;
    fake::Object nodeA;
    fake::Object nodeB;
    fake::Object entity;
    char resourceManager1[0x40];
    char resourceManager2[0x40];
    char positionable[0x100];

    void reset()
    {
        fake::Object* all[] = {&sceneManagerA, &sceneManagerB, &createdNode, &rootNode, &nodeA, &nodeB, &entity};
        for (unsigned int i = 0; i < sizeof(all) / sizeof(all[0]); i++)
            fake::init(*all[i]);
        // SceneManager::createSceneNode() and getRootSceneNode().
        fake::setResult(sceneManagerA, 0x230, &createdNode);
        fake::setResult(sceneManagerA, 0x250, &rootNode);
        fake::setResult(sceneManagerB, 0x230, &createdNode);
        fake::setResult(sceneManagerB, 0x250, &nodeB);
        // MovableObject::getParentSceneNode().
        fake::setResult(entity, 0xa0, pick(0, &createdNode, &nodeA));
        std::memset(resourceManager1, 0, sizeof(resourceManager1));
        std::memset(resourceManager2, 0, sizeof(resourceManager2));
        setPointer(resourceManager1, 0x10, &sceneManagerA);
        setPointer(resourceManager2, 0x10, &sceneManagerB);
        std::memset(positionable, 0, sizeof(positionable));
    }
};

World g_world;

void randomObject(char* object)
{
    World& w = g_world;
    std::memset(object, 0, kSize);
    setPointer(object, kParentPositionable, pick(0, 0, w.positionable));
    setPointer(object, kSceneNode, pick(0, 0, &w.nodeA));
    setPointer(object, kEntity, pick(0, &w.entity, 0));
    setPointer(object, kResourceManager, pick(0, w.resourceManager1, w.resourceManager2));
    setPointer(object, kParentSceneNode, pick(0, &w.rootNode, &w.nodeB));
    setPointer(object, kSceneManager, pick(0, &w.sceneManagerA, &w.sceneManagerB));
    object[kKeepParent] = char(nextRandom() % 2);
    object[kVisible] = char(nextRandom() % 2);
    object[kEnabled] = char(nextRandom() % 2);
}

} // namespace

TL_TEST(SceneNodeObject_shadow)
{
    int failures = 0;
    fake::setArguments(0x1a8, 1); // Node::addChild(Node*)
    fake::setArguments(0x218, 2); // SceneNode::_update(bool, bool)
    fake::setArguments(0x278, 1); // SceneNode::attachObject(MovableObject*)
    fake::setArguments(0x2a0, 1); // SceneNode::detachObject(MovableObject*)
    fake::setArguments(0x378, 2); // SceneNode::setVisible(bool, bool)
    static char a[kSize];
    static char b[kSize];
    static fake::Log logA;
    static fake::Log logB;
    TL_CHECK(failures, sizeof(CSceneNodeObject) == kSize);

    for (int step = 0; step < 20000 && failures == 0; step++)
    {
        g_world.reset();
        randomObject(a);
        std::memcpy(b, a, kSize);
        bool resourceStep = nextRandom() % 2;
        logA.clear();
        logB.clear();
        if (resourceStep)
        {
            CResourceManager* manager = reinterpret_cast<CResourceManager*>(
                const_cast<void*>(pick(0, g_world.resourceManager1, g_world.resourceManager2)));
            fake::currentLog() = &logA;
            originalSetResourceManager(a, manager);
            fake::currentLog() = &logB;
            reinterpret_cast<CSceneNodeObject*>(b)->setResourceManager(manager);
        }
        else
        {
            setPointer(g_world.positionable, kSceneNode, pick(0, &g_world.rootNode, &g_world.nodeB));
            CPositionableObject* parent = reinterpret_cast<CPositionableObject*>(
                const_cast<void*>(pick(0, g_world.positionable, g_world.positionable)));
            fake::currentLog() = &logA;
            originalSetParentPositionableObject(a, parent);
            fake::currentLog() = &logB;
            reinterpret_cast<CSceneNodeObject*>(b)->CSceneNodeObject::setParentPositionableObject(parent);
        }
        fake::currentLog() = 0;
        TL_CHECK(failures, logA == logB);
        TL_CHECK(failures, std::memcmp(a, b, kSize) == 0);
        if (failures)
            host->log("    step %d (%s), %d vs %d calls\n", step, resourceStep ? "setResourceManager" : "setParent",
                      logA.count, logB.count);
    }
    return failures;
}
