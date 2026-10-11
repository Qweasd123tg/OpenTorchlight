// Shadow test: CSceneNodeObject methods that differ from the original only in
// block layout, run on identical objects whose Ogre collaborators are fakes.
#include <cstring>

#include "FakeVtable.h"
#include "AutoTest.h"
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

TL_ORIGINAL(void,originalResource,(void*,CResourceManager*),"_ZN16CSceneNodeObject18setResourceManagerEP16CResourceManager")
extern "C" void candidateResource(void*,CResourceManager*) __asm__("_ZN16CSceneNodeObject18setResourceManagerEP16CResourceManager");
TL_ORIGINAL(void,originalParent,(void*,CPositionableObject*),"_ZN16CSceneNodeObject27setParentPositionableObjectEP19CPositionableObject")
extern "C" void candidateParent(void*,CPositionableObject*) __asm__("_ZN16CSceneNodeObject27setParentPositionableObjectEP19CPositionableObject");

namespace {
struct Case{unsigned op,seed;};
void body(Case&c,bool ours,autotest::Capture&out){
 g_seed=c.seed*1777+41;g_world.reset();long long bytes[(kSize+7)/8];char*p=reinterpret_cast<char*>(bytes);randomObject(p);
 fake::Log log;log.clear();fake::currentLog()=&log;
 fake::setArguments(0x1a8,1);fake::setArguments(0x218,2);fake::setArguments(0x278,1);fake::setArguments(0x2a0,1);fake::setArguments(0x378,2);
 if(c.op==0){CResourceManager*m=reinterpret_cast<CResourceManager*>(const_cast<void*>(pick(0,g_world.resourceManager1,g_world.resourceManager2)));autotest::invoke(out,ours?candidateResource:originalResource,static_cast<void*>(p),m);}
 else{setPointer(g_world.positionable,kSceneNode,pick(0,&g_world.rootNode,&g_world.nodeB));CPositionableObject*parent=reinterpret_cast<CPositionableObject*>(const_cast<void*>(pick(0,g_world.positionable,g_world.positionable)));autotest::invoke(out,ours?candidateParent:originalParent,static_cast<void*>(p),parent);}
 fake::currentLog()=0;if(log.overflow){out.issue=autotest::Capture::Overflow;return;}out.add(&log.count,4);out.add(log.calls,log.count*sizeof(fake::Call));out.add(p,kSize);out.add(&g_world,sizeof(g_world));
}
void original(void*p,autotest::Capture&out){body(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){body(*static_cast<Case*>(p),true,out);}
}
namespace {
int observed(const tlhybrid_host*host,unsigned op,const char*name){
 const uint64_t addresses[]={(uint64_t)(uintptr_t)originalResource,(uint64_t)(uintptr_t)originalParent};
 autotest::Coverage coverage(name,addresses[op]);
 for(unsigned n=0;n<512;++n){Case c={op,n};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
  if(coverage.observe(host,a,b)){size_t k=0;while(k<a.capture.length&&k<b.capture.length&&a.capture.data[k]==b.capture.data[k])++k;
   host->log("    observed op %u case %u status %d/%d first %lu bytes %lu/%lu\n",op,n,a.status,b.status,(unsigned long)k,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}
 coverage.report(host);return 0;
}
}
TL_TEST(scenenode_resource_observed){return observed(host,0,"scenenode_resource_observed");}
TL_TEST(scenenode_parent_observed){return observed(host,1,"scenenode_parent_observed");}
