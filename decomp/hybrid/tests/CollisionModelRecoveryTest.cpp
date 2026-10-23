#include "MeshNativeRecovery.h"
#include <OgreMeshSerializer.h>
#include "tests/CharacterEmptyGlobals.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/Detour.h"
#define private public
#include "CollisionModel.h"
#undef private
#include "CollisionList.h"
#include "FileSystem.h"
#include "FileUtilities.h"
#include <fenv.h>
#include <ucontext.h>
#include <execinfo.h>
TL_ORIGINAL(void,collisionLoadOld,(CCollisionModel*,std::wstring),"_ZN15CCollisionModel9loadModelESbIwSt11char_traitsIwESaIwEE")
extern "C" void collisionLoadNew(CCollisionModel*,std::wstring) __asm__("_ZN15CCollisionModel9loadModelESbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void,collisionCtor,(CCollisionModel*,Ogre::SceneManager*,std::wstring),"_ZN15CCollisionModelC1EPN4Ogre12SceneManagerESbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,collisionDtor,(CCollisionModel*),"_ZN15CCollisionModelD1Ev")
TL_ORIGINAL(void,collisionFsCtor,(CFileSystem*,bool),"_ZN11CFileSystemC1Eb")
TL_ORIGINAL(void,collisionFsDtor,(CFileSystem*),"_ZN11CFileSystemD1Ev")
TL_ORIGINAL(void,collisionInfoOld,(CFileSystem*,const std::wstring&,CFileInfo&,bool,bool,bool),"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(collisionInfoEntry,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
namespace {
struct Case{unsigned seed;bool negative;};
const tlhybrid_host* diagnosticsHost;const Case* active;autotest::Capture* output;nativegame::Services* services;
unsigned stage,infoCalls;bool activeOurs;detour::Set infoHook;CFileSystem* fs;std::string directory;
void number(unsigned long n){mesh_recovery::number(*output,n);}
void fault(int sig,siginfo_t* info,void* raw){ucontext_t* u=static_cast<ucontext_t*>(raw);diagnosticsHost->log("    collision fault%d stage%u seed%u ours%u rip%p address%p\n",sig,stage,active->seed,unsigned(activeOurs),reinterpret_cast<void*>(u->uc_mcontext.gregs[REG_RIP]),info->si_addr);void* frames[18];int n=backtrace(frames,18);for(int i=0;i<n;++i)diagnosticsHost->log("    collision frame%d %p\n",i,frames[i]);_exit(128+sig);}
void diagnostics(){struct sigaction a;std::memset(&a,0,sizeof a);a.sa_sigaction=fault;a.sa_flags=SA_SIGINFO;sigemptyset(&a.sa_mask);sigaction(SIGABRT,&a,NULL);sigaction(SIGSEGV,&a,NULL);sigaction(SIGBUS,&a,NULL);}
void info(CFileSystem* self,const std::wstring& name,CFileInfo& file,bool a,bool b,bool c)
{
    number(++infoCalls);number(self==fs);output->addText(name);number(a);number(b);number(c);
    if(infoCalls==1&&(self!=fs||a||!b||c))output->issue=autotest::Capture::InvalidReport;
    infoHook.restore();collisionInfoOld(self,name,file,a,b,c);TL_REDIRECT(infoHook,collisionInfoEntry,&info);
    if(infoHook.failed())output->issue=autotest::Capture::InvalidReport;
    number(file.m_bExists);output->addText(file.m_sPath);output->addText(file.m_sResourceName);
    if(active->seed==8)diagnosticsHost->log("    collision info ours%u exists%u path[%ls] resource[%s]\n",unsigned(activeOurs),unsigned(file.m_bExists),file.m_sPath.c_str(),file.m_sResourceName.c_str());
}
void snapshot(CCollisionModel* model)
{
    output->addText(model->m_sFilename);output->addText(model->m_sMeshName);mesh_recovery::vector(*output,model->m_vUnknown20);mesh_recovery::vector(*output,model->m_vUnknown2C);number(model->m_pSceneManager==services->scene);
    CCollisionList* list=model->getCollisionList();number(list!=NULL);if(!list)return;
    number(list->getVertexCount());number(list->getFaceCount());
    for(int v=0;v<list->getVertexCount();++v)mesh_recovery::vector(*output,list->getVertex(v));
    for(int f=0;f<list->getFaceCount();++f){number(list->getVertexIndexA(f));number(list->getVertexIndexB(f));number(list->getVertexIndexC(f));number(list->getMaterial(f));mesh_recovery::vector(*output,list->getNormal(f));mesh_recovery::vector(*output,list->getMinFaceBounds(f));mesh_recovery::vector(*output,list->getMaxFaceBounds(f));}
}
void side(void* raw,autotest::Capture& out,bool ours)
{
    active=static_cast<Case*>(raw);output=&out;activeOurs=ours;stage=1;infoCalls=0;diagnostics();unsigned seed=active->seed;
    char previous[4096];if(!getcwd(previous,sizeof previous)||chdir(directory.c_str()))std::abort();
    CFileSystem* previousFs=g_pFileSystem;fs=static_cast<CFileSystem*>(Ogre::NedAllocImpl::allocBytes(sizeof(CFileSystem),0,0,0));g_pFileSystem=fs;collisionFsCtor(fs,false);
    unsigned condition=seed%6;
    Ogre::MeshPtr mesh=mesh_recovery::mesh(seed,seed/6%5,seed/30%2,false);
    bool usesShared=false;for(unsigned s=0;s<mesh->getNumSubMeshes();++s)if(mesh->getSubMesh(s)->useSharedVertices)usesShared=true;
    if(!usesShared&&mesh->sharedVertexData){OGRE_DELETE mesh->sharedVertexData;mesh->sharedVertexData=NULL;}
    bool sharedPacked=false;
    for(unsigned s=0;s<mesh->getNumSubMeshes();++s){
        Ogre::SubMesh* sub=mesh->getSubMesh(s);
        if(!sub->useSharedVertices||!sharedPacked){
            Ogre::VertexData* old=sub->useSharedVertices?mesh->sharedVertexData:sub->vertexData;
            unsigned count=3+(seed+s)%9;bool hasUV=(seed+s)%2!=0;
            Ogre::VertexData* packed=OGRE_NEW Ogre::VertexData;packed->vertexCount=count;
            packed->vertexDeclaration->addElement(0,0,Ogre::VET_FLOAT3,Ogre::VES_POSITION);
            packed->vertexDeclaration->addElement(0,12,Ogre::VET_FLOAT3,Ogre::VES_NORMAL);
            if(hasUV)packed->vertexDeclaration->addElement(0,24,Ogre::VET_FLOAT2,Ogre::VES_TEXTURE_COORDINATES);
            unsigned stride=hasUV?32:24;
            Ogre::HardwareVertexBufferSharedPtr vb=Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(stride,count,Ogre::HardwareBuffer::HBU_STATIC,false);
            float* values=static_cast<float*>(vb->lock(Ogre::HardwareBuffer::HBL_DISCARD));
            for(unsigned v=0;v<count;++v){Ogre::Vector3 point=mesh_recovery::point(v,seed+s);*values++=point.x;*values++=point.y;*values++=point.z;*values++=0;*values++=1;*values++=0;if(hasUV){*values++=v*.125f;*values++=-v*.25f;}}
            vb->unlock();packed->vertexBufferBinding->setBinding(0,vb);OGRE_DELETE old;
            if(sub->useSharedVertices){mesh->sharedVertexData=packed;sharedPacked=true;}else sub->vertexData=packed;
        }
        unsigned count=sub->useSharedVertices?mesh->sharedVertexData->vertexCount:sub->vertexData->vertexCount;
        sub->clearBoneAssignments();mesh_recovery::indexData(sub,3*(1+(seed+s)%4),false,count,seed+s);sub->indexData->indexStart=0;
    }
    mesh->_setBounds(Ogre::AxisAlignedBox(-20,-20,-20,20,20,20),false);mesh->_setBoundingSphereRadius(40);
    std::string file="MEDIA/SyntheticMesh.mesh";
    Ogre::MeshSerializer serializer;serializer.exportMesh(mesh.getPointer(),file);
    mesh.setNull();Ogre::MeshManager::getSingleton().removeAll();
    std::wstring path=condition==0?L"missing.mesh":condition==1?L"":condition==2?L"./MEDIA/SyntheticMesh.mesh":L"MEDIA/SyntheticMesh.mesh";
    CCollisionModel* model=static_cast<CCollisionModel*>(Ogre::NedAllocImpl::allocBytes(sizeof(CCollisionModel),0,0,0));collisionCtor(model,services->scene,L"");
    model->m_sMeshName="previous mesh label";model->m_vUnknown20=mesh_recovery::point(seed,1);model->m_vUnknown2C=mesh_recovery::point(seed,2);
    CCollisionList* prior=NULL;
    if(condition==3||condition==4||condition==5){prior=new CCollisionList;prior->addVertex(Ogre::Vector3(4,5,6),-1);model->m_pCollisionList=prior;model->m_sFilename=condition==3?L"MEDIA/SyntheticMesh.mesh":condition==4?L"prior.mesh":L"MEDIA/SYNTHETICMESH.MESH";}
    stage=2;TL_REDIRECT(infoHook,collisionInfoEntry,&info);if(infoHook.failed())std::abort();feclearexcept(FE_ALL_EXCEPT);
    if(autotest::beginInvocation(out,ours?collisionLoadNew:collisionLoadOld)){
        (ours?collisionLoadNew:collisionLoadOld)(model,path);out.callCompleted=1;
    }
    stage=3;number(fetestexcept(FE_ALL_EXCEPT));infoHook.restore();number(infoCalls);
    if(ours&&active->negative)model->m_sMeshName="negative model state";
    snapshot(model);number(model->getCollisionList()==prior);number(Ogre::MeshManager::getSingleton().resourceExists(file));
    CCollisionList* current=model->getCollisionList();collisionDtor(model);Ogre::NedAllocImpl::deallocBytes(model);if(prior&&prior!=current)delete prior;
    stage=4;collisionFsDtor(fs);Ogre::NedAllocImpl::deallocBytes(fs);g_pFileSystem=previousFs;Ogre::MeshManager::getSingleton().removeAll();unlink(file.c_str());
    if(chdir(previous))std::abort();stage=5;
}
void original(void* p,autotest::Capture& out){side(p,out,false);}void candidate(void* p,autotest::Capture& out){side(p,out,true);}
int worker(const tlhybrid_host* host)
{
    diagnosticsHost=host;initEmptyGlobals();nativegame::Services native;if(!native.ready())return 1;services=&native;
    char temp[]="/tmp/otl-collision-model-XXXXXX";char* made=mkdtemp(temp);if(!made)return 1;directory=made;if(mkdir((directory+"/MEDIA").c_str(),0700))return 1;
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation(directory,"FileSystem",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    autotest::Coverage coverage("collision_model_native_files",reinterpret_cast<uintptr_t>(&collisionLoadOld));int failed=0;
    for(unsigned seed=0;seed<180;++seed){Case c={seed,false};autotest::Outcome a,b;autotest::runChild(original,&c,a,10000,18000);autotest::runChild(candidate,&c,b,10000,18000);if(coverage.observe(host,a,b)){host->log("    collision seed%u valid%u/%u issue%u/%u status%d/%d bytes%lu/%lu\n",seed,a.reportValid,b.reportValid,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);failed=1;break;}}
    coverage.report(host);
    if(!failed){Case c={34,true};autotest::Outcome a,b;autotest::runChild(original,&c,a,10000,18000);autotest::runChild(candidate,&c,b,10000,18000);autotest::Coverage negative("collision_model_native_files",reinterpret_cast<uintptr_t>(&collisionLoadOld));int delta=negative.observe(host,a,b);host->log("    collision negative detected%u completed%u incomplete%u\n",unsigned(delta==1),negative.completed,negative.missing);if(delta!=1||negative.completed!=1||negative.missing)failed=1;}
    Ogre::ResourceGroupManager::getSingleton().removeResourceLocation(directory,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);rmdir((directory+"/MEDIA").c_str());rmdir(directory.c_str());return failed;
}
}
TL_TEST(collision_model_native_files){return systems_fixture::isolated(worker,host,360);}
