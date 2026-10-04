#include <cstring>
#include <OgreSceneNode.h>
#include "AutoTest.h"
#include "BaseUnit.h"
#include "CollisionList.h"
TL_ORIGINAL(bool, originalUnitRay, (CBaseUnit*,const Ogre::Vector3&,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,bool), "_ZN9CBaseUnit12rayCollisionERKN4Ogre7Vector3ES3_RS1_S4_b")
TL_ORIGINAL(bool, originalUnitSphere, (CBaseUnit*,const Ogre::Vector3&,const Ogre::Vector3&,float,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&), "_ZN9CBaseUnit15sphereCollisionERKN4Ogre7Vector3ES3_fRS1_S4_S4_")
extern "C" void* meshBaseTable[] __asm__("_ZTV9CBaseUnit");
namespace {
struct Case {unsigned int seed;};
void* modelPointer;void* collisionPointer;unsigned int modelCalls,collisionCalls;
void* model(void*) {++modelCalls;return modelPointer;}
void* collision(void*) {++collisionCalls;return collisionPointer;}
void pointerAt(void* p,size_t offset,void* v) {std::memcpy(static_cast<char*>(p)+offset,&v,sizeof(v));}
void side(Case& c,bool ours,autotest::Capture& out) {
    CCollisionList mesh;
    if(c.seed%17) {
        const Ogre::Vector3 vertices[]={Ogre::Vector3(-2,0,-2),Ogre::Vector3(2,0,-2),Ogre::Vector3(2,0,2),Ogre::Vector3(-2,0,2)};
        for(unsigned int i=0;i<4;++i)mesh.addVertex(vertices[i],-1);
        mesh.addFace(0,2,1,1,-1);mesh.addFace(0,3,2,1,-1);mesh.calculateNormals();mesh.calculateFaceBounds();
    }
    long long base[0x1d8/8],visual[0x250/8],collider[0x48/8],bounds[0xb8/8];std::memset(base,0,sizeof(base));std::memset(visual,0,sizeof(visual));std::memset(collider,0,sizeof(collider));std::memset(bounds,0,sizeof(bounds));
    void* table[82];std::memcpy(table,meshBaseTable,sizeof(table));table[62]=reinterpret_cast<void*>(&model);table[63]=reinterpret_cast<void*>(&collision);pointerAt(base,0,table+2);
    char* self=reinterpret_cast<char*>(base);self[0x18d]=c.seed&1;self[0x19c]=(c.seed>>1)&1;
    pointerAt(collider,0x38,&mesh);pointerAt(base,0x1c0,bounds);
    Ogre::SceneNode node(NULL);Ogre::Quaternion orientation=Ogre::Quaternion::IDENTITY;
    switch((c.seed/32)%4) {
    case 1:orientation=Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Y);break;
    case 2:orientation=Ogre::Quaternion(Ogre::Degree(45),Ogre::Vector3::UNIT_Z);break;
    case 3:orientation=Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_X);break;
    }
    Ogre::Vector3 basePosition(3,5,-7),visualPosition(0.5f,1,-0.25f);node.setPosition(basePosition+Ogre::Vector3(1,2,3));node.setOrientation(orientation);node.setScale(2,0.5f,3);
    pointerAt(base,0x58,&node);if(c.seed&8)pointerAt(base,0x50,base);
    std::memcpy(self+0x84,&basePosition,sizeof(basePosition));std::memcpy(reinterpret_cast<char*>(visual)+0x84,&visualPosition,sizeof(visualPosition));
    Ogre::Vector3 offset=c.seed&8?node._getDerivedPosition():basePosition;
    modelPointer=c.seed&16?visual:NULL;if(modelPointer)offset+=visualPosition;
    collisionPointer=c.seed%11?collider:NULL;
    Ogre::Vector3 minimum=offset-Ogre::Vector3(4),maximum=offset+Ogre::Vector3(4);
    if(c.seed%19==0) {minimum+=Ogre::Vector3(100);maximum+=Ogre::Vector3(100);}
    std::memcpy(reinterpret_cast<char*>(bounds)+0x40,&minimum,sizeof(minimum));std::memcpy(reinterpret_cast<char*>(bounds)+0x4c,&maximum,sizeof(maximum));
    Ogre::Vector3 localStart(0,4,0),localEnd(0,-4,0);
    switch((c.seed/128)%6) {
    case 1:localStart.x=localEnd.x=3;break;
    case 2:localStart=Ogre::Vector3(1.9f,4,1.9f);localEnd=Ogre::Vector3(1.9f,-4,1.9f);break;
    case 3:localStart=Ogre::Vector3(0,-4,0);localEnd=Ogre::Vector3(0,4,0);break;
    case 4:localStart=Ogre::Vector3(-1,0.5f,0);localEnd=Ogre::Vector3(1,0.5f,0);break;
    case 5:localStart=Ogre::Vector3(-1,6,0);localEnd=Ogre::Vector3(1,6,0);break;
    }
    Ogre::Vector3 start=offset+orientation*localStart,end=offset+orientation*localEnd;
    CBaseUnit* object=reinterpret_cast<CBaseUnit*>(base);
    for(unsigned int operation=0;operation<2;++operation) {
        Ogre::Vector3 position(101,102,103),hit(201,202,203),normal(301,302,303);
        modelCalls=collisionCalls=0;bool found;
        if(operation==0) {
            Ogre::Vector3& normalOut=c.seed%23==0?hit:normal;
            if(ours)found=object->rayCollision(start,end,hit,normalOut,(c.seed&4)!=0);else found=originalUnitRay(object,start,end,hit,normalOut,(c.seed&4)!=0);
        } else {
            const float radii[]={0,0.25f,1,2};float radius=radii[(c.seed/16)%4];
            Ogre::Vector3& positionOut=c.seed%23==0?hit:position;
            if(ours)found=object->sphereCollision(start,end,radius,positionOut,hit,normal);else found=originalUnitSphere(object,start,end,radius,positionOut,hit,normal);
        }
        out.add(&found,sizeof(found));out.add(&position,sizeof(position));out.add(&hit,sizeof(hit));out.add(&normal,sizeof(normal));out.add(&modelCalls,sizeof(modelCalls));out.add(&collisionCalls,sizeof(collisionCalls));
    }
}
void original(void* p,autotest::Capture& o) {side(*static_cast<Case*>(p),false,o);}
void recovered(void* p,autotest::Capture& o) {side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(base_unit_real_mesh_collisions) {
    int failures=0;unsigned int rayHits=0,sphereHits=0;
    for(unsigned int seed=0;seed<768;++seed) {Case c={seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        if(a.capture.length==90) {rayHits+=a.capture.data[0]!=0;sphereHits+=a.capture.data[45]!=0;}
        bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok)host->log("    collision seed %u status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);}
    host->log("    mesh cases: ray hits %u, sphere hits %u\n",rayHits,sphereHits);
    TL_CHECK(failures,rayHits>0 && sphereHits>0);
    return failures;
}
