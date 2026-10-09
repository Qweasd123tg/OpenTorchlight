#include <cstring>
#include <vector>
#include <OgreSceneNode.h>
#include "AutoTest.h"
#include "BaseUnit.h"
#define private public
#include "CollisionList.h"
#undef private
TL_ORIGINAL(bool, originalUnitRay, (CBaseUnit*,const Ogre::Vector3&,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,bool), "_ZN9CBaseUnit12rayCollisionERKN4Ogre7Vector3ES3_RS1_S4_b")
TL_ORIGINAL(bool, originalUnitSphere, (CBaseUnit*,const Ogre::Vector3&,const Ogre::Vector3&,float,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&), "_ZN9CBaseUnit15sphereCollisionERKN4Ogre7Vector3ES3_fRS1_S4_S4_")
extern "C" bool recoveredUnitRay(CBaseUnit*,const Ogre::Vector3&,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,bool) __asm__("_ZN9CBaseUnit12rayCollisionERKN4Ogre7Vector3ES3_RS1_S4_b");
extern "C" bool recoveredUnitSphere(CBaseUnit*,const Ogre::Vector3&,const Ogre::Vector3&,float,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&) __asm__("_ZN9CBaseUnit15sphereCollisionERKN4Ogre7Vector3ES3_fRS1_S4_S4_");
extern "C" void* meshBaseTable[] __asm__("_ZTV9CBaseUnit");
namespace {
struct Case {unsigned int seed,operation,warm;};
struct Snapshot {std::vector<unsigned char> bytes;Snapshot(const void* p,size_t n):bytes(static_cast<const unsigned char*>(p),static_cast<const unsigned char*>(p)+n){}void pointer(size_t o,uintptr_t v){if(o+sizeof(v)>bytes.size())_exit(71);std::memcpy(&bytes[o],&v,sizeof(v));}void emit(autotest::Capture& c){c.add(&bytes[0],bytes.size());}};
template<class T> void vectorState(autotest::Capture& o,const std::vector<T>& v){size_t n=v.size();o.add(&n,sizeof(n));if(n)o.add(&v[0],n*sizeof(T));}

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
    if(c.seed>=768){self[0x18d]=self[0x19c]=1;collisionPointer=collider;localStart=Ogre::Vector3(-1,0.5f,0);localEnd=Ogre::Vector3(1,0.5f,0);minimum=offset+Ogre::Vector3(-4,3,-4);maximum=offset+Ogre::Vector3(4,3.1f,4);std::memcpy(reinterpret_cast<char*>(bounds)+0x40,&minimum,sizeof(minimum));std::memcpy(reinterpret_cast<char*>(bounds)+0x4c,&maximum,sizeof(maximum));}
    Ogre::Vector3 start=offset+orientation*localStart,end=offset+orientation*localEnd;
    CBaseUnit* object=reinterpret_cast<CBaseUnit*>(base);
    for(unsigned int repeat=0;repeat<=c.warm;++repeat) {
        Ogre::Vector3 position(101,102,103),hit(201,202,203),normal(301,302,303);
        modelCalls=collisionCalls=0;
        if(c.operation==0) {
            Ogre::Vector3& normalOut=c.seed%23==0?hit:normal;
            typedef bool (*Fn)(CBaseUnit*,const Ogre::Vector3&,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,bool);
            Fn fn=ours?&recoveredUnitRay:&originalUnitRay;
            if(repeat==c.warm)autotest::invoke<Fn,CBaseUnit*,const Ogre::Vector3&,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,bool>(out,fn,object,start,end,hit,normalOut,(c.seed&4)!=0);
            else fn(object,start,end,hit,normalOut,(c.seed&4)!=0);
        } else {
            const float radii[]={0,0.25f,1,2};float radius=radii[(c.seed/16)%4];
            Ogre::Vector3& positionOut=c.seed%23==0?hit:position;
            typedef bool (*Fn)(CBaseUnit*,const Ogre::Vector3&,const Ogre::Vector3&,float,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&);
            Fn fn=ours?&recoveredUnitSphere:&originalUnitSphere;
            if(repeat==c.warm)autotest::invoke<Fn,CBaseUnit*,const Ogre::Vector3&,const Ogre::Vector3&,float,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&>(out,fn,object,start,end,radius,positionOut,hit,normal);
            else fn(object,start,end,radius,positionOut,hit,normal);
        }
        if(repeat==c.warm){out.add(&position,sizeof(position));out.add(&hit,sizeof(hit));out.add(&normal,sizeof(normal));out.add(&modelCalls,sizeof(modelCalls));out.add(&collisionCalls,sizeof(collisionCalls));}
    }
    Snapshot state(base,sizeof(base));state.pointer(0,*reinterpret_cast<void***>(base)==table+2?1:255);void* p;std::memcpy(&p,self+0x50,sizeof(p));state.pointer(0x50,p==base?1:p?255:0);std::memcpy(&p,self+0x58,sizeof(p));state.pointer(0x58,p==&node?1:255);std::memcpy(&p,self+0x1c0,sizeof(p));state.pointer(0x1c0,p==bounds?1:255);state.emit(out);
    out.add(visual,sizeof(visual));out.add(bounds,sizeof(bounds));Snapshot col(collider,sizeof(collider));std::memcpy(&p,reinterpret_cast<char*>(collider)+0x38,sizeof(p));col.pointer(0x38,p==&mesh?1:255);col.emit(out);
    out.add(&start,sizeof(start));out.add(&end,sizeof(end));const Ogre::Vector3& np=node.getPosition();const Ogre::Vector3& ns=node.getScale();const Ogre::Quaternion& nq=node.getOrientation();out.add(&np,sizeof(np));out.add(&ns,sizeof(ns));out.add(&nq,sizeof(nq));
    out.add(&mesh.m_vBoundsMin,sizeof(mesh.m_vBoundsMin));out.add(&mesh.m_vBoundsMax,sizeof(mesh.m_vBoundsMax));out.add(&mesh.m_iIgnoredMaterial,sizeof(mesh.m_iIgnoredMaterial));
    vectorState(out,mesh.m_FaceMaxBounds);vectorState(out,mesh.m_FaceMinBounds);vectorState(out,mesh.m_Vertices);vectorState(out,mesh.m_Colors);vectorState(out,mesh.m_Normals);vectorState(out,mesh.m_IndicesA);vectorState(out,mesh.m_IndicesB);vectorState(out,mesh.m_IndicesC);vectorState(out,mesh.m_Materials);

}
void original(void* p,autotest::Capture& o) {side(*static_cast<Case*>(p),false,o);}
void recovered(void* p,autotest::Capture& o) {side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(base_unit_real_mesh_collisions) {
    int failures=0;unsigned int rayHits=0,sphereHits=0;
    autotest::Coverage ray("base_unit_real_mesh_collisions",(uint64_t)(uintptr_t)&originalUnitRay),sphere("base_unit_real_mesh_collisions",(uint64_t)(uintptr_t)&originalUnitSphere);
    for(unsigned int seed=0;seed<960;++seed)for(unsigned int operation=0;operation<2;++operation)for(unsigned int warm=0;warm<2;++warm) {
        Case c={seed,operation,warm};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        int pair=(operation?sphere:ray).observe(host,a,b);
        bool ok=!pair&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus;
        if(ok&&a.capture.length>0){if(operation)sphereHits+=a.capture.data[0]!=0;else rayHits+=a.capture.data[0]!=0;}
        if(!ok)host->log("    collision seed %u operation %u warm %u status %d/%d bytes %lu/%lu\n",seed,operation,warm,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
        TL_CHECK(failures,ok);if(!ok){ray.report(host);sphere.report(host);return failures;}
    }
    ray.report(host);sphere.report(host);host->log("    mesh cases: ray hits %u, sphere hits %u\n",rayHits,sphereHits);
    TL_CHECK(failures,rayHits>0 && sphereHits>0);return failures;
}
