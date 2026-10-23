#ifndef MESH_NATIVE_RECOVERY_H
#define MESH_NATIVE_RECOVERY_H
#include <OgreMesh.h>
#include <Ogre.h>
typedef char NativeMeshSharedOffset[__builtin_offsetof(Ogre::Mesh,sharedVertexData)==0x1f0?1:-1];
#include <OgreMeshManager.h>
#include <OgreSubMesh.h>
#include <OgreSkeletonManager.h>
#include <OgreHardwareBufferManager.h>
#include "AutoTest.h"
namespace mesh_recovery {
inline void number(autotest::Capture& out,unsigned long n){out.add(&n,sizeof n);}
inline void vector(autotest::Capture& out,const Ogre::Vector3& v){out.add(&v,sizeof v);}
inline Ogre::Vector3 point(unsigned i,unsigned seed){return Ogre::Vector3(float(int(i%7)-3)*1.25f+seed*.0625f,float(int(i%5)-2)*.5f,float(int(i%11)-5)*-.125f);}
inline Ogre::VertexData* data(unsigned count,unsigned mode,unsigned seed)
{
    Ogre::VertexData* vd=OGRE_NEW Ogre::VertexData;
    vd->vertexCount=count;vd->vertexStart=seed%3;
    unsigned sourceNormal=mode%3==0?0:1,sourceUV=mode%3==2?2:sourceNormal;
    bool uv=mode<3;
    vd->vertexDeclaration->addElement(0,4,Ogre::VET_FLOAT3,Ogre::VES_POSITION);
    vd->vertexDeclaration->addElement(sourceNormal,sourceNormal==0?16:8,Ogre::VET_FLOAT3,Ogre::VES_NORMAL);
    if(uv)vd->vertexDeclaration->addElement(sourceUV,sourceUV==sourceNormal?(sourceNormal==0?28:20):4,Ogre::VET_FLOAT2,Ogre::VES_TEXTURE_COORDINATES);
    for(unsigned s=0;s<= (uv?sourceUV:sourceNormal);++s) {
        size_t stride=vd->vertexDeclaration->getVertexSize(s)+8;
        Ogre::HardwareVertexBufferSharedPtr buffer=Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(stride,count+4,Ogre::HardwareBuffer::HBU_STATIC,false);
        unsigned char* bytes=static_cast<unsigned char*>(buffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
        std::memset(bytes,0x6b,buffer->getSizeInBytes());
        const Ogre::VertexDeclaration::VertexElementList& elements=vd->vertexDeclaration->getElements();
        for(unsigned v=0;v<count+4;++v)for(Ogre::VertexDeclaration::VertexElementList::const_iterator e=elements.begin();e!=elements.end();++e)if(e->getSource()==s){
            float* p; e->baseVertexPointerToElement(bytes+v*stride,&p);
            Ogre::Vector3 q=point(v,seed+e->getSemantic());p[0]=q.x;p[1]=q.y;
            if(e->getSemantic()!=Ogre::VES_TEXTURE_COORDINATES)p[2]=q.z;
        }
        buffer->unlock();vd->vertexBufferBinding->setBinding(s,buffer);
    }
    return vd;
}
inline void indexData(Ogre::SubMesh* sub,unsigned count,bool wide,unsigned vertexCount,unsigned seed)
{
    Ogre::HardwareIndexBufferSharedPtr ib=Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(wide?Ogre::HardwareIndexBuffer::IT_32BIT:Ogre::HardwareIndexBuffer::IT_16BIT,(count+6)*(wide?2:1),Ogre::HardwareBuffer::HBU_STATIC,false);
    void* memory=ib->lock(Ogre::HardwareBuffer::HBL_DISCARD);
    for(unsigned i=0;i<count+6;++i){unsigned long value=vertexCount?(i*5+seed)%vertexCount:0;if(wide)static_cast<unsigned long*>(memory)[i]=value;else static_cast<unsigned short*>(memory)[i]=value;}
    ib->unlock();sub->indexData->indexBuffer=ib;sub->indexData->indexCount=count;sub->indexData->indexStart=seed%4;
}
inline void bone(Ogre::Mesh* mesh,Ogre::SubMesh* sub,unsigned vertex,unsigned which,float weight)
{
    Ogre::VertexBoneAssignment a;a.vertexIndex=vertex;a.boneIndex=which;a.weight=weight;
    if(sub)sub->addBoneAssignment(a);else mesh->addBoneAssignment(a);
}
inline Ogre::MeshPtr mesh(unsigned seed,unsigned subCount,bool mixed,bool skeleton)
{
    std::string name="SyntheticMesh";
    Ogre::MeshPtr mesh=Ogre::MeshManager::getSingleton().createManual(name,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    if(mixed)mesh->sharedVertexData=data(3+seed%7,seed%6,seed);
    const unsigned counts[]={0,1,2,3,7,12,25};
    for(unsigned s=0;s<subCount;++s){
        Ogre::SubMesh* sub=mesh->createSubMesh();sub->useSharedVertices=mixed&&((seed+s)%3!=0);
        unsigned count=counts[(seed/6+s)%7];
        if(!sub->useSharedVertices)sub->vertexData=data(count,(seed+s)%6,seed+s);
        else count=mesh->sharedVertexData->vertexCount;
        const unsigned indices[]={0,1,2,3,4,5,6,9,13,18};
        indexData(sub,indices[(seed/3+s)%10],(seed+s)%2,count,seed+s);
        sub->setMaterialName((seed+s)%4==0?"prefixnocollidesuffix":(seed+s)%4==1?"NOCOLLIDE":"material");
        if(count&&!sub->useSharedVertices)for(unsigned b=0;b<seed%5;++b)bone(mesh.getPointer(),sub,b%count,b%3,.25f*(b+1));
    }
    if(skeleton){
        Ogre::SkeletonPtr sk=Ogre::SkeletonManager::getSingleton().create("SyntheticSkeleton",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        mesh->_notifySkeleton(sk);
        for(unsigned b=0;b<seed%5;++b)bone(mesh.getPointer(),NULL,b%3,b%3,.25f*(b+1));
    }
    return mesh;
}
inline void transform(unsigned seed,Ogre::Vector3& p,Ogre::Quaternion& q,Ogre::Vector3& s)
{
    p=point(seed%9,seed);q=Ogre::Quaternion(1,0,0,0);s=Ogre::Vector3(1,1,1);
    if(seed%4==1){q=Ogre::Quaternion(.5f,-.5f,.5f,-.5f);s=Ogre::Vector3(-2,.25f,3);}
    if(seed%4==2){q=Ogre::Quaternion(.7f,.1f,-.3f,.2f);s=Ogre::Vector3(0,-1,2);}
    if(seed%4==3){q=Ogre::Quaternion(0,1,0,0);s=Ogre::Vector3(1e-12f,1e12f,-.0f);}
}
inline void captureBones(autotest::Capture& out,unsigned long count,const Ogre::VertexBoneAssignment* bones)
{
    number(out,count);number(out,bones!=NULL);if(count>200){out.issue=autotest::Capture::InvalidReport;return;}
    for(unsigned long b=0;b<count;++b){number(out,bones[b].vertexIndex);number(out,bones[b].boneIndex);out.add(&bones[b].weight,4);}
}
inline void captureBuffer(autotest::Capture& out,const Ogre::HardwareVertexBufferSharedPtr& buffer,size_t definedBytes)
{
    number(out,buffer->getVertexSize());number(out,buffer->getNumVertices());number(out,buffer->getUsage());number(out,buffer->hasShadowBuffer());number(out,buffer->isLocked());
    void* data=buffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY);out.add(data,definedBytes);buffer->unlock();
}
}
#endif
