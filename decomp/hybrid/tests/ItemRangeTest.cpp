#include <cstring>
#include <limits>
#include <map>
#include <new>
#include <vector>
#include <OgreSceneNode.h>
#include "AutoTest.h"
#include "Item.h"
#include "GameGlobals.h"

TL_ORIGINAL(void, originalItemRange, (CItem*,const Ogre::Vector3&), "_ZN5CItem20calculateActiveRangeERKN4Ogre7Vector3E")
extern "C" void* rangeItemTable[] __asm__("_ZTV5CItem");
extern CGameGlobals* rangeGameGlobals __asm__("_ZL14g_pGameGlobals");
namespace {
struct Case { unsigned int scenario,distance; };
void* modelPointer;unsigned int modelLookups;
void* modelForRange(void*) {++modelLookups;return modelPointer;}
void putPointer(void* p,size_t offset,void* value) {std::memcpy(static_cast<char*>(p)+offset,&value,sizeof(value));}
void putFloat(void* p,size_t offset,float value) {std::memcpy(static_cast<char*>(p)+offset,&value,sizeof(value));}
void side(Case& c,bool ours,autotest::Capture& out) {
    long long item[0x230/8],model[0x250/8],manager[0x48/8],level[0x2f0/8],data[0x778/8],globals[0x2d0/8],hierarchy[0x100/8];
    std::memset(item,0,sizeof(item));std::memset(model,0,sizeof(model));std::memset(manager,0,sizeof(manager));
    std::memset(level,0,sizeof(level));std::memset(data,0,sizeof(data));std::memset(globals,0,sizeof(globals));std::memset(hierarchy,0,sizeof(hierarchy));
    char* self=reinterpret_cast<char*>(item);
    void* table[89];std::memcpy(table,rangeItemTable+2,sizeof(table));table[60]=reinterpret_cast<void*>(&modelForRange);putPointer(item,0,table);
    self[0x198]=c.scenario%13!=0;self[0x199]=c.scenario&1;self[0x19a]=(c.scenario>>1)&1;self[0x1a9]=c.scenario%4!=0;
    putFloat(item,0x1e0,c.scenario%11==0?1.0f:c.scenario%5==0?-1.0f:0.0f);
    putFloat(globals,0xa8,10);putFloat(globals,0xac,24);putFloat(globals,0xb0,40);putFloat(globals,0xb4,16);putFloat(globals,0xb8,30);
    CGameGlobals* saved=rangeGameGlobals;rangeGameGlobals=reinterpret_cast<CGameGlobals*>(globals);
    typedef std::map<unsigned int,std::vector<unsigned int> > Relations;
    Relations* relations=new(reinterpret_cast<char*>(hierarchy)+0x10) Relations;(*relations)[777].push_back(32);
    putPointer(manager,0x20,hierarchy);unsigned int type=c.scenario%3==0?0:c.scenario%3==1?32:777;std::memcpy(self+0x1ac,&type,4);
    unsigned int context=c.scenario%6;
    if(context!=0)putPointer(item,0x68,manager);
    if(context>=2)putPointer(manager,0x18,level);
    if(context>=3)putPointer(level,0x1d8,data);
    reinterpret_cast<char*>(data)[0x763]=context==3;
    Ogre::Vector3 position(7,3,-2);std::memcpy(self+0x84,&position,sizeof(position));
    Ogre::SceneNode node(NULL);
    if(c.scenario&8) {node.setPosition(position+Ogre::Vector3(1,0,0));putPointer(item,0x58,&node);putPointer(item,0x50,item);}
    const float distances[]={0,9.99f,10,10.01f,15.99f,16,16.01f,23.99f,24,24.01f,29.99f,30,30.01f,40,40.01f,
        std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};
    const float heights[]={0,4,4.001f,-4,-4.001f,std::numeric_limits<float>::quiet_NaN()};
    Ogre::Vector3 viewer=position+Ogre::Vector3(distances[c.distance],heights[c.scenario%6],0);
    unsigned char materials[128];std::memset(materials,0,sizeof(materials));materials[1]=(c.scenario>>2)&1;materials[65]=!(c.scenario&1);
    putPointer(model,0x208,materials);putPointer(model,0x210,materials+sizeof(materials));putPointer(model,0x218,materials+sizeof(materials));
    modelPointer=c.scenario%7?model:NULL;modelLookups=0;
    CItem* object=reinterpret_cast<CItem*>(item);
    if(ours)object->calculateActiveRange(viewer);else originalItemRange(object,viewer);
    out.add(self+0x199,2);out.add(&modelLookups,sizeof(modelLookups));out.add(materials,sizeof(materials));
    relations->~Relations();rangeGameGlobals=saved;
}
void original(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(item_active_range_and_shadows) {
    int failures=0;
    for(unsigned int scenario=0;scenario<32;++scenario)for(unsigned int distance=0;distance<17;++distance) {
        Case c={scenario,distance};autotest::Outcome a,b;
        autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool same=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&
                  WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&
                  a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&
                  std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!same)host->log("    item range %u/%u status %d/%d bytes %lu/%lu\n",scenario,distance,a.status,b.status,
                          (unsigned long)a.capture.length,(unsigned long)b.capture.length);
        TL_CHECK(failures,same);
    }
    return failures;
}
