#include "MeshNativeRecovery.h"
#include "tests/CharacterEmptyGlobals.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include "UtilitiesMath.h"
#include <fenv.h>
#include <ucontext.h>
#include <execinfo.h>
TL_ORIGINAL(void,meshGetOld,(const Ogre::Mesh*,unsigned long&,Ogre::Vector3*&,Ogre::Vector3*&,Ogre::Vector3*&,unsigned long&,unsigned long*&,unsigned long&,unsigned long&,unsigned int*&,std::vector<std::string>&,unsigned long&,Ogre::VertexBoneAssignment*&,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&),"_ZN4MATH18getMeshInformationEPKN4Ogre4MeshERmRPNS0_7Vector3ES7_S7_S4_RPmS4_S4_RPjRSt6vectorISsSaISsEES4_RPNS0_22VertexBoneAssignment_sERKS5_RKNS0_10QuaternionESK_")
extern "C" void meshGetNew(const Ogre::Mesh*,unsigned long&,Ogre::Vector3*&,Ogre::Vector3*&,Ogre::Vector3*&,unsigned long&,unsigned long*&,unsigned long&,unsigned long&,unsigned int*&,std::vector<std::string>&,unsigned long&,Ogre::VertexBoneAssignment*&,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&) __asm__("_ZN4MATH18getMeshInformationEPKN4Ogre4MeshERmRPNS0_7Vector3ES7_S7_S4_RPmS4_S4_RPjRSt6vectorISsSaISsEES4_RPNS0_22VertexBoneAssignment_sERKS5_RKNS0_10QuaternionESK_");
TL_ORIGINAL(void,meshSetOld,(Ogre::Mesh*,unsigned long,Ogre::Vector3*&,Ogre::Vector3*&,Ogre::Vector3*&,unsigned long,unsigned long*&,unsigned long,unsigned long,unsigned int*&,std::vector<std::string>&,unsigned long,Ogre::VertexBoneAssignment*&),"_ZN4MATH18setMeshInformationEPN4Ogre4MeshEmRPNS0_7Vector3ES5_S5_mRPmmmRPjRSt6vectorISsSaISsEEmRPNS0_22VertexBoneAssignment_sE")
extern "C" void meshSetNew(Ogre::Mesh*,unsigned long,Ogre::Vector3*&,Ogre::Vector3*&,Ogre::Vector3*&,unsigned long,unsigned long*&,unsigned long,unsigned long,unsigned int*&,std::vector<std::string>&,unsigned long,Ogre::VertexBoneAssignment*&) __asm__("_ZN4MATH18setMeshInformationEPN4Ogre4MeshEmRPNS0_7Vector3ES5_S5_mRPmmmRPjRSt6vectorISsSaISsEEmRPNS0_22VertexBoneAssignment_sE");
TL_ORIGINAL(void,meshSubOld,(const Ogre::SubMesh*,bool,unsigned long&,Ogre::Vector3*&,Ogre::Vector3*&,Ogre::Vector3*&,unsigned long&,unsigned long*&,unsigned long&,unsigned long&,Ogre::VertexBoneAssignment*&,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&),"_ZN4MATH21getSubMeshInformationEPKN4Ogre7SubMeshEbRmRPNS0_7Vector3ES7_S7_S4_RPmS4_S4_RPNS0_22VertexBoneAssignment_sERKS5_RKNS0_10QuaternionESE_")
extern "C" void meshSubNew(const Ogre::SubMesh*,bool,unsigned long&,Ogre::Vector3*&,Ogre::Vector3*&,Ogre::Vector3*&,unsigned long&,unsigned long*&,unsigned long&,unsigned long&,Ogre::VertexBoneAssignment*&,const Ogre::Vector3&,const Ogre::Quaternion&,const Ogre::Vector3&) __asm__("_ZN4MATH21getSubMeshInformationEPKN4Ogre7SubMeshEbRmRPNS0_7Vector3ES7_S7_S4_RPmS4_S4_RPNS0_22VertexBoneAssignment_sERKS5_RKNS0_10QuaternionESE_");
namespace {
using mesh_recovery::number;
struct Case{unsigned seed,kind;bool negative;};
const tlhybrid_host* diagnosticsHost;
unsigned stage,activeSeed,activeKind;bool activeOurs;
void fault(int sig,siginfo_t* info,void* raw){ucontext_t* u=static_cast<ucontext_t*>(raw);diagnosticsHost->log("    mesh fault%d stage%u kind%u seed%u ours%u rip%p address%p\n",sig,stage,activeKind,activeSeed,unsigned(activeOurs),reinterpret_cast<void*>(u->uc_mcontext.gregs[REG_RIP]),info->si_addr);void* frames[18];int n=backtrace(frames,18);for(int i=0;i<n;++i)diagnosticsHost->log("    mesh frame%d %p\n",i,frames[i]);_exit(128+sig);}
void diagnostics(){struct sigaction a;std::memset(&a,0,sizeof a);a.sa_sigaction=fault;a.sa_flags=SA_SIGINFO;sigemptyset(&a.sa_mask);sigaction(SIGABRT,&a,NULL);sigaction(SIGSEGV,&a,NULL);sigaction(SIGBUS,&a,NULL);}
void side(void* raw,autotest::Capture& out,bool ours)
{
    const Case& c=*static_cast<Case*>(raw);unsigned seed=c.seed;activeSeed=seed;activeKind=c.kind;activeOurs=ours;stage=1;diagnostics();
    Ogre::MeshPtr mesh;
    Ogre::Vector3 position,scale;Ogre::Quaternion orientation;mesh_recovery::transform(seed,position,orientation,scale);
    unsigned long nv=seed%4,ni=seed%5,nt=seed%3,nm=17,nb=seed%3;
    Ogre::Vector3* vertices=NULL;Ogre::Vector3* normals=NULL;Ogre::Vector3* uvs=NULL;unsigned long* indices=NULL;
    Ogre::VertexBoneAssignment* bones=NULL;unsigned int* materials=NULL;
    std::vector<std::string> names;names.push_back("existing material");names.push_back("nocollide old prefix");
    if(c.kind==0){
        mesh=mesh_recovery::mesh(seed,seed%5,seed/5%2,seed/10%2);
        Ogre::VertexBoneAssignment prior[3];for(unsigned i=0;i<3;++i){prior[i].vertexIndex=900+i;prior[i].boneIndex=30+i;prior[i].weight=-i*.5f;}
        bones=prior;
        stage=2;feclearexcept(FE_ALL_EXCEPT);
        if(autotest::beginInvocation(out,ours?meshGetNew:meshGetOld)){
            (ours?meshGetNew:meshGetOld)(mesh.getPointer(),nv,vertices,normals,uvs,ni,indices,nt,nm,materials,names,nb,bones,position,orientation,scale);out.callCompleted=1;
        }
        stage=3;number(out,fetestexcept(FE_ALL_EXCEPT));
        if(ours&&c.negative)++nm;
        number(out,nv);number(out,ni);number(out,nt);number(out,nm);mesh_recovery::captureBones(out,nb,bones);
        out.add(vertices,nv*12);out.add(normals,nv*12);
        unsigned long offset=0;bool shared=false;
        for(unsigned s=0;s<mesh->getNumSubMeshes();++s){
            Ogre::SubMesh* sub=mesh->getSubMesh(s);if(sub->useSharedVertices&&shared)continue;
            Ogre::VertexData* data=sub->useSharedVertices?mesh->sharedVertexData:sub->vertexData;
            if(data->vertexDeclaration->findElementBySemantic(Ogre::VES_TEXTURE_COORDINATES))out.add(uvs+offset,data->vertexCount*12);
            offset+=data->vertexCount;if(sub->useSharedVertices)shared=true;
        }
        unsigned long written=0;for(unsigned s=0;s<mesh->getNumSubMeshes();++s)written+=mesh->getSubMesh(s)->indexData->indexCount/3;
        out.add(indices,written*3*8);out.add(materials,written*4);
        number(out,names.size());for(unsigned i=0;i<names.size();++i)out.addText(names[i]);
        delete[] vertices;delete[] normals;delete[] uvs;delete[] indices;delete[] materials;if(bones!=prior)delete[] bones;
    }else if(c.kind==1){
        mesh=mesh_recovery::mesh(seed,1,false,false);Ogre::SubMesh* sub=mesh->getSubMesh(0);
        bool existing=seed/6%2;bool collect=seed/12%2;
        unsigned long oldV=existing?nv:0,oldI=existing?ni:0,oldB=existing?nb:0;
        nv=oldV;ni=oldI;nb=oldB;
        const unsigned long capV=oldV+sub->vertexData->vertexCount,capI=oldI+sub->indexData->indexCount;
        if(existing){
            vertices=static_cast<Ogre::Vector3*>(std::malloc((capV+1)*12));normals=static_cast<Ogre::Vector3*>(std::malloc((capV+1)*12));uvs=static_cast<Ogre::Vector3*>(std::malloc((capV+1)*12));indices=static_cast<unsigned long*>(std::malloc((capI+1)*8));
            for(unsigned i=0;i<capV+1;++i){vertices[i]=mesh_recovery::point(i,1);normals[i]=mesh_recovery::point(i,2);uvs[i]=mesh_recovery::point(i,3);}for(unsigned i=0;i<capI+1;++i)indices[i]=0xabcdef1234567890ul+i;
            bones=static_cast<Ogre::VertexBoneAssignment*>(std::malloc((oldB+sub->getBoneAssignments().size()+1)*12));
            for(unsigned i=0;i<oldB;++i){bones[i].vertexIndex=80+i;bones[i].boneIndex=11+i;bones[i].weight=-.25f*i;}
        }
        stage=2;feclearexcept(FE_ALL_EXCEPT);
        if(autotest::beginInvocation(out,ours?meshSubNew:meshSubOld)){
            (ours?meshSubNew:meshSubOld)(sub,collect,nv,vertices,normals,uvs,ni,indices,nt,nb,bones,position,orientation,scale);out.callCompleted=1;
        }
        stage=3;number(out,fetestexcept(FE_ALL_EXCEPT));if(ours&&c.negative)++nt;
        number(out,nv);number(out,ni);number(out,nt);mesh_recovery::captureBones(out,nb,bones);
        out.add(vertices,nv*12);out.add(normals,nv*12);
        if(existing||sub->vertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_TEXTURE_COORDINATES))out.add(uvs,nv*12);
        unsigned long written=sub->indexData->indexCount/3*3;
        out.add(indices,(existing?ni:written)*8);
        std::free(vertices);std::free(normals);std::free(uvs);std::free(indices);if(existing)std::free(bones);else delete[] bones;
    }else{
        mesh=Ogre::MeshManager::getSingleton().createManual("SetSyntheticMesh",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        const unsigned counts[]={0,1,2,3,7,12,25,257};nv=counts[seed%8];nt=seed/8%7;nm=seed%2?0:999;ni=seed%2?0:1;
        mesh->sharedVertexData=OGRE_NEW Ogre::VertexData;Ogre::VertexData* data=mesh->sharedVertexData;data->vertexCount=3+seed%4;
        data->vertexStart=seed%3;
        data->vertexDeclaration->addElement(0,0,Ogre::VET_FLOAT3,Ogre::VES_POSITION);data->vertexDeclaration->addElement(0,12,Ogre::VET_FLOAT3,Ogre::VES_NORMAL);
        data->vertexDeclaration->addElement(1,0,Ogre::VET_FLOAT2,Ogre::VES_TEXTURE_COORDINATES);
        unsigned subCount=seed/8%4;for(unsigned s=0;s<subCount;++s)mesh->createSubMesh();
        vertices=new Ogre::Vector3[nv];normals=new Ogre::Vector3[nv];uvs=new Ogre::Vector3[nv];indices=new unsigned long[nt*3];materials=new unsigned int[nt];
        for(unsigned v=0;v<nv;++v){vertices[v]=mesh_recovery::point(v,seed);normals[v]=mesh_recovery::point(v,seed+1);uvs[v]=mesh_recovery::point(v,seed+2);}
        for(unsigned t=0;t<nt;++t){materials[t]=(t+seed)%5;for(unsigned k=0;k<3;++k)indices[t*3+k]=nv?(t*3+k+seed)%nv:0;}
        while(names.size()<subCount)names.push_back("set material");
        nb=nv?seed/16%4:0;bones=new Ogre::VertexBoneAssignment[nb];
        for(unsigned b=0;b<nb;++b){bones[b].vertexIndex=b%nv;bones[b].boneIndex=b%2;bones[b].weight=.25f*(b+1);}
        if(nv&&seed/32%2)mesh_recovery::bone(mesh.getPointer(),NULL,0,3,.2f);
        stage=2;feclearexcept(FE_ALL_EXCEPT);
        if(autotest::beginInvocation(out,ours?meshSetNew:meshSetOld)){
            (ours?meshSetNew:meshSetOld)(mesh.getPointer(),nv,vertices,normals,uvs,ni,indices,nt,nm,materials,names,nb,bones);out.callCompleted=1;
        }
        stage=3;number(out,fetestexcept(FE_ALL_EXCEPT));
        if(ours&&c.negative)data->vertexStart++;
        number(out,data->vertexCount);number(out,data->vertexStart);number(out,data->vertexDeclaration->getElementCount());
        mesh_recovery::captureBuffer(out,data->vertexBufferBinding->getBuffer(0),nv*24);
        mesh_recovery::captureBuffer(out,data->vertexBufferBinding->getBuffer(1),nv*8);
        for(unsigned s=0;s<subCount;++s){Ogre::SubMesh* sub=mesh->getSubMesh(s);out.addText(sub->getMaterialName());number(out,sub->indexData->indexCount);Ogre::HardwareIndexBufferSharedPtr ib=sub->indexData->indexBuffer;number(out,ib->getType());number(out,ib->getUsage());number(out,ib->isLocked());void* p=ib->lock(Ogre::HardwareBuffer::HBL_READ_ONLY);out.add(p,sub->indexData->indexCount*2);ib->unlock();}
        const Ogre::Mesh::VertexBoneAssignmentList& assignments=mesh->getBoneAssignments();number(out,assignments.size());
        for(Ogre::Mesh::VertexBoneAssignmentList::const_iterator i=assignments.begin();i!=assignments.end();++i){number(out,i->first);mesh_recovery::captureBones(out,1,&i->second);}
        out.add(vertices,nv*12);out.add(normals,nv*12);out.add(uvs,nv*12);out.add(indices,nt*3*8);out.add(materials,nt*4);
        delete[] vertices;delete[] normals;delete[] uvs;delete[] indices;delete[] materials;delete[] bones;
    }
    stage=4;mesh.setNull();Ogre::MeshManager::getSingleton().removeAll();Ogre::SkeletonManager::getSingleton().removeAll();
}
void original(void* p,autotest::Capture& out){side(p,out,false);}void candidate(void* p,autotest::Capture& out){side(p,out,true);}
int worker(const tlhybrid_host* host,unsigned kind)
{
    diagnosticsHost=host;initEmptyGlobals();nativegame::Services services;if(!services.ready())return 1;
    const char* labels[]={"mesh_extract_native","submesh_extract_native","mesh_upload_native"};
    uintptr_t address=kind==0?reinterpret_cast<uintptr_t>(&meshGetOld):kind==1?reinterpret_cast<uintptr_t>(&meshSubOld):reinterpret_cast<uintptr_t>(&meshSetOld);
    autotest::Coverage coverage(labels[kind],address);int failed=0;unsigned total=kind==2?224:420;
    for(unsigned seed=0;seed<total;++seed){Case c={seed,kind,false};autotest::Outcome a,b;autotest::runChild(original,&c,a,6000,16000);autotest::runChild(candidate,&c,b,6000,16000);if(coverage.observe(host,a,b)){host->log("    mesh kind%u seed%u valid%u/%u issue%u/%u status%d/%d bytes%lu/%lu\n",kind,seed,a.reportValid,b.reportValid,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);failed=1;break;}}
    coverage.report(host);
    if(!failed){Case c={67,kind,true};autotest::Outcome a,b;autotest::runChild(original,&c,a,6000,16000);autotest::runChild(candidate,&c,b,6000,16000);autotest::Coverage negative(labels[kind],address);int delta=negative.observe(host,a,b);host->log("    mesh negative kind%u detected%u completed%u incomplete%u\n",kind,unsigned(delta==1),negative.completed,negative.missing);if(delta!=1||negative.completed!=1||negative.missing)failed=1;}
    return failed;
}
int getWorker(const tlhybrid_host* h){return worker(h,0);}int subWorker(const tlhybrid_host* h){return worker(h,1);}int setWorker(const tlhybrid_host* h){return worker(h,2);}
}
TL_TEST(mesh_extract_native){return systems_fixture::isolated(getWorker,host,240);}
TL_TEST(submesh_extract_native){return systems_fixture::isolated(subWorker,host,240);}
TL_TEST(mesh_upload_native){return systems_fixture::isolated(setWorker,host,240);}
