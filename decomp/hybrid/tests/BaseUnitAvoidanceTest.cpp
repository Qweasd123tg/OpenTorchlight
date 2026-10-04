#include <cstring>
#include <map>
#include <new>
#include <vector>
#include <OgreSceneNode.h>
#include "AutoTest.h"
#include "BaseUnit.h"
#include "Level.h"
TL_ORIGINAL(void, originalAddAvoidance, (CBaseUnit*,CLevel&), "_ZN9CBaseUnit17addToAvoidanceMapER6CLevel")
TL_ORIGINAL(void, originalRemoveAvoidance, (CBaseUnit*,CLevel&), "_ZN9CBaseUnit22removeFromAvoidanceMapER6CLevel")
extern "C" void* avoidanceBaseTable[] __asm__("_ZTV9CBaseUnit");
namespace {
struct Case {unsigned int seed;};
unsigned int collisionQueries;
void* collisionModel(void*) {++collisionQueries;return NULL;}
void pointerAt(void* p,size_t offset,void* v) {std::memcpy(static_cast<char*>(p)+offset,&v,sizeof(v));}
void uintAt(void* p,size_t offset,unsigned int v) {std::memcpy(static_cast<char*>(p)+offset,&v,4);}
void floatAt(void* p,size_t offset,float v) {std::memcpy(static_cast<char*>(p)+offset,&v,4);}
void side(Case& c,bool ours,autotest::Capture& out) {
    long long base[0x1d8/8],level[0x2f0/8],guardLevel[0x2f0/8],resources[0x48/8],hierarchy[0x100/8],bounds[0xb8/8];
    std::memset(base,0,sizeof(base));std::memset(level,0,sizeof(level));std::memset(guardLevel,0,sizeof(guardLevel));std::memset(resources,0,sizeof(resources));std::memset(hierarchy,0,sizeof(hierarchy));std::memset(bounds,0,sizeof(bounds));
    void* table[80];std::memcpy(table,avoidanceBaseTable+2,sizeof(table));table[61]=reinterpret_cast<void*>(&collisionModel);pointerAt(base,0,table);
    short map[16][16],objects[16][16];short* mapRows[16];short* objectRows[16];
    for(unsigned int x=0;x<16;++x) {mapRows[x]=map[x];objectRows[x]=objects[x];for(unsigned int z=0;z<16;++z){map[x][z]=(x+z)%4;objects[x][z]=(x*3+z)%5;}}
    pointerAt(level,0x40,mapRows);pointerAt(level,0x48,objectRows);uintAt(level,0x50,16);uintAt(level,0x54,16);
    if(c.seed&1)pointerAt(level,0x68,level);floatAt(level,0x230,-0.8f);floatAt(level,0x234,-1.2f);
    typedef std::map<unsigned int,std::vector<unsigned int> > Relations;Relations* relations=new(reinterpret_cast<char*>(hierarchy)+0x10)Relations;(*relations)[777].push_back(29);(*relations)[778].push_back(31);(*relations)[779].push_back(32);
    pointerAt(resources,0x20,hierarchy);pointerAt(base,0x1c0,bounds);
    unsigned int mode=(c.seed/2)%8;char* self=reinterpret_cast<char*>(base);
    if(mode!=1)pointerAt(base,0x68,resources);if(mode!=2)pointerAt(resources,0x18,guardLevel);
    self[0x18f]=mode!=3;self[0x19b]=mode==4;self[0x18d]=mode!=5;self[0x19c]=mode!=6;
    const unsigned int types[]={0,29,31,32,777,778,779};uintAt(base,0x1ac,types[(c.seed/16)%7]);
    const float radii[]={-0.4f,0,0.3f,0.8f,2};floatAt(base,0x194,radii[(c.seed/112)%5]);
    Ogre::Vector3 position(2,1,3);if(c.seed%13==0)position=Ogre::Vector3(-2,1,-3);if(c.seed%17==0)position=Ogre::Vector3(10,1,11);
    std::memcpy(self+0x84,&position,sizeof(position));Ogre::SceneNode node(NULL);node.setPosition(position+Ogre::Vector3(0.8f,0,-0.4f));
    if(c.seed&8) {pointerAt(base,0x58,&node);pointerAt(base,0x50,base);}
    Ogre::Vector3 low=position-Ogre::Vector3(0.8f,1,0.8f),high=position+Ogre::Vector3(0.8f,1,0.8f);
    std::memcpy(reinterpret_cast<char*>(bounds)+0x40,&low,sizeof(low));std::memcpy(reinterpret_cast<char*>(bounds)+0x4c,&high,sizeof(high));
    CBaseUnit* object=reinterpret_cast<CBaseUnit*>(base);CLevel& target=*reinterpret_cast<CLevel*>(level);collisionQueries=0;
    for(unsigned int step=0;step<3;++step) {
        if(step==1) {if(ours)object->CBaseUnit::removeFromAvoidanceMap(target);else originalRemoveAvoidance(object,target);}
        else {if(ours)object->CBaseUnit::addToAvoidanceMap(target);else originalAddAvoidance(object,target);}
        out.add(map,sizeof(map));out.add(objects,sizeof(objects));out.add(self+0x19b,1);out.add(&collisionQueries,sizeof(collisionQueries));
    }
    relations->~Relations();
}
void original(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(base_unit_avoidance_grid_changes) {
    int failures=0;
    for(unsigned int seed=0;seed<560;++seed) {Case c={seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok)host->log("    avoidance seed %u status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);}
    return failures;
}
