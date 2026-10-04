#include <cstring>
#include <limits>
#include <OgreSceneNode.h>
#include "AutoTest.h"
#include "BaseUnit.h"
TL_ORIGINAL(void, originalBoundsUpdate, (CBaseUnit*), "_ZN9CBaseUnit19updateCullingBoundsEv")
extern "C" void* boundsBaseTable[] __asm__("_ZTV9CBaseUnit");
namespace {
struct Case {unsigned int seed;};
void* modelPointer;unsigned int lookups,modelMode;
void* modelForBounds(void*) {++lookups;return modelMode==0?NULL:modelMode==2&&lookups==2?NULL:modelPointer;}
void pointerAt(void* p,size_t offset,void* value) {std::memcpy(static_cast<char*>(p)+offset,&value,sizeof(value));}
void side(Case& c,bool ours,autotest::Capture& out) {
    long long base[0x1d8/8],model[0x250/8],bounds[0xb8/8];
    std::memset(base,0,sizeof(base));std::memset(model,0,sizeof(model));std::memset(bounds,0x42,sizeof(bounds));
    void* table[80];std::memcpy(table,boundsBaseTable+2,sizeof(table));table[60]=reinterpret_cast<void*>(&modelForBounds);pointerAt(base,0,table);
    char* self=reinterpret_cast<char*>(base);char* box=reinterpret_cast<char*>(bounds);
    if(c.seed%11)pointerAt(base,0x1c0,bounds);
    Ogre::Vector3 position(3,-2,7),offset(0.5f,1,-0.25f);
    std::memcpy(self+0x84,&position,sizeof(position));std::memcpy(reinterpret_cast<char*>(model)+0x84,&offset,sizeof(offset));
    Ogre::SceneNode node(NULL);node.setPosition(Ogre::Vector3(11,13,-17));
    if(c.seed&1) {pointerAt(base,0x58,&node);if(c.seed&2)pointerAt(base,0x50,base);}
    Ogre::Matrix4 matrix=Ogre::Matrix4::IDENTITY;
    switch((c.seed/4)%6) {
    case 1:matrix[0][0]=-2;matrix[1][1]=0.5f;matrix[2][2]=3;break;
    case 2:matrix[0][0]=0;matrix[0][2]=1;matrix[2][0]=-1;matrix[2][2]=0;break;
    case 3:matrix[0][0]=0.25f;matrix[0][1]=-0.5f;matrix[0][2]=0.75f;matrix[1][0]=1.5f;matrix[1][1]=-2;matrix[1][2]=3;matrix[2][0]=-0.75f;matrix[2][1]=0.5f;matrix[2][2]=2;break;
    case 4:matrix[3][0]=0.125f;matrix[3][1]=-0.25f;matrix[3][2]=0.5f;matrix[3][3]=2;break;
    case 5:matrix[3][3]=0;break;
    }
    matrix[0][3]=100;matrix[1][3]=-200;matrix[2][3]=300;
    std::memcpy(self+0xc0,&matrix,sizeof(matrix));
    Ogre::Vector3 low(-1,-2,-3),high(2,3,4);
    switch((c.seed/24)%5) {
    case 1:low=Ogre::Vector3(2,3,4);high=Ogre::Vector3(-1,-2,-3);break;
    case 2:low.x=std::numeric_limits<float>::quiet_NaN();break;
    case 3:high.z=std::numeric_limits<float>::infinity();break;
    case 4:low=Ogre::Vector3(-0.0f,0,-0.0f);high=Ogre::Vector3(0,-0.0f,0);break;
    }
    std::memcpy(box+0x10,&low,sizeof(low));std::memcpy(box+0x1c,&high,sizeof(high));
    modelPointer=model;modelMode=(c.seed/120)%3;lookups=0;
    CBaseUnit* object=reinterpret_cast<CBaseUnit*>(base);
    if(ours)object->updateCullingBounds();else originalBoundsUpdate(object);
    out.add(box+0x10,sizeof(bounds)-0x10);out.add(&lookups,sizeof(lookups));out.add(self+0xc0,sizeof(matrix));
}
void original(void* p,autotest::Capture& o) {side(*static_cast<Case*>(p),false,o);}
void recovered(void* p,autotest::Capture& o) {side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(base_unit_transformed_culling_bounds) {
    int failures=0;
    for(unsigned int seed=0;seed<360;++seed) {Case c={seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok)host->log("    bounds seed %u status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
        TL_CHECK(failures,ok);}
    return failures;
}
