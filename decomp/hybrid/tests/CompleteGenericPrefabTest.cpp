#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#define private public
#define protected public
#include "GenericModel.h"
#include "ResourceManager.h"
#undef protected
#undef private
#include "FileSystem.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include <OgreSubMesh.h>
TL_ORIGINAL(void,gpOld,(CGenericModel*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModel14loadPrefabTypeEN14OGRE_UTILITIES11EPRIMITIVESE")
extern "C" void gpNew(CGenericModel*,OGRE_UTILITIES::EPRIMITIVES) __asm__("_ZN13CGenericModel14loadPrefabTypeEN14OGRE_UTILITIES11EPRIMITIVESE");
TL_ORIGINAL(void,gpCtor,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_ORIGINAL(void,gpDtor,(CGenericModel*),"_ZN13CGenericModelD1Ev")
TL_ORIGINAL(void,gpResourceCtor,(CResourceManager*,Ogre::SceneManager*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,gpResourceDtor,(CResourceManager*),"_ZN16CResourceManagerD1Ev")
TL_FUNCTION(gpFiles,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(gpName,"_ZNK4Ogre13MovableObject7getNameEv")
extern "C" char gpLog[] __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
namespace {
CGenericModel*expected;bool nameFailure;
nativegame::Services*services;Ogre::MeshPtr mesh;autotest::Capture*output;
void number(unsigned n){output->add(&n,4);}void wide(const std::wstring&s){number(s.size());if(s.size())output->add(s.data(),s.size()*sizeof(wchar_t));}void narrow(const std::string&s){number(s.size());if(s.size())output->add(s.data(),s.size());}
const std::string& observedName(const Ogre::MovableObject*p){if(nameFailure&&p==expected->getEntity()){nameFailure=false;number(2);services->scene->getEntity("missing-for-prefab-name-error");std::abort();}return p->Ogre::MovableObject::getName();}

void log(Ogre::LogManager*p,const std::string&message,Ogre::LogMessageLevel level,bool mask){if(p!=Ogre::LogManager::getSingletonPtr())std::abort();number(3);narrow(message);number(level);number(mask);}
void files(CFileSystem*p,const std::wstring&path,CFileInfo&info,bool a,bool b,bool c){if(p!=g_pFileSystem)std::abort();number(1);wide(path);number(a);number(b);number(c);info.m_bExists=true;info.m_sResourceName=mesh->getName();}
void initialized(uintptr_t address,bool wide,const wchar_t*value=L""){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(address),8);if(!p){if(wide)new(reinterpret_cast<void*>(address))std::wstring(value);else new(reinterpret_cast<void*>(address))std::string;}}
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=*static_cast<unsigned*>(raw);output=&out;CResourceManager*resources=static_cast<CResourceManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CResourceManager),0,0,0));gpResourceCtor(resources,services->scene);CGenericModel*model=static_cast<CGenericModel*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGenericModel),0,0,0));gpCtor(model,NULL,services->scene,OGRE_UTILITIES::PRIMITIVE_SPHERE);model->setResourceManager(resources);model->setScale(.25f*(1+seed/24%3),2.f,.5f);model->setPosition(Ogre::Vector3(float(int(seed%5)-2),1.f,-3.f));model->setVisible(seed/6%2);model->m_renderToLightMap=seed/12%2;model->m_queryMask=static_cast<OGRE_UTILITIES::EQUERYMASK>(17+seed%3);model->m_sModelPath=L"previous/path";model->m_modelGroup=L"previous/group";if(seed/24%2||seed>=288){Ogre::Entity*previous=services->scene->createEntity("previous-prefab",mesh->getName());model->sceneNodeAttachEntity(previous);}services->scene->getRenderQueue()->setDefaultQueueGroup(17+seed/48%5);
 expected=model;detour::Set hooks;TL_REDIRECT(hooks,gpFiles,&files);hooks.redirect(gpLog,gpLog,&log);nameFailure=seed>=288;if(nameFailure){TL_REDIRECT(hooks,gpName,&observedName);}if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}void(*fn)(CGenericModel*,OGRE_UTILITIES::EPRIMITIVES)=ours?gpNew:gpOld;if(autotest::beginInvocation(out,fn)){fn(model,static_cast<OGRE_UTILITIES::EPRIMITIVES>(seed%6));out.callCompleted=1;}Ogre::Entity*entity=model->m_pEntity;wide(model->m_sModelPath);wide(model->m_modelGroup);narrow(model->m_name);number(model->m_queryMask);number(model->m_renderToLightMap);number(entity!=NULL);if(entity){narrow(entity->getName());number(entity->getCastShadows());number(entity->getQueryFlags());number(entity->getVisibilityFlags());number(entity->getRenderQueueGroup());number(entity->getParentSceneNode()==model->getSceneNode());}number(services->scene->hasEntity("previous-prefab"));out.add(&model->m_vPosition,sizeof(Ogre::Vector3));out.add(&model->m_vScale,sizeof(Ogre::Vector3));hooks.restore();gpDtor(model);Ogre::NedAllocImpl::deallocBytes(model);gpResourceDtor(resources);Ogre::NedAllocImpl::deallocBytes(resources);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services native;services=&native;if(!native.ready())return 1;uintptr_t strings[]={0x1482e00,0x1528e40,0x14e6860,0x14e6900};for(unsigned i=0;i<4;++i){initialized(strings[i],false);initialized(strings[i]+8,true);}const wchar_t*names[]={L"SPHERE",L"BOX",L"PLANE",L"CYLINDER",L"CONE",L"ARROW"};for(unsigned i=0;i<6;++i)initialized(0x1482e20+i*8,true,names[i]);CFileSystem*previous=g_pFileSystem;void*memory=Ogre::NedAllocImpl::allocBytes(sizeof(CFileSystem),0,0,0);g_pFileSystem=static_cast<CFileSystem*>(memory);CFileSystem*fs=new(memory)CFileSystem(false);Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().create("generic-prefab-material","General");material->removeAllTechniques();mesh=Ogre::MeshManager::getSingleton().createManual("generic-prefab-mesh","General");mesh->_setBounds(Ogre::AxisAlignedBox(-1,-1,-1,1,1,1),false);mesh->createSubMesh()->setMaterialName(material->getName());
 autotest::Coverage coverage("generic_load_prefab",reinterpret_cast<uintptr_t>(gpOld));for(unsigned seed=0;seed<384;++seed){autotest::Outcome a,b;autotest::runChild(original,&seed,a);autotest::runChild(candidate,&seed,b);if(coverage.observe(host,a,b)){host->log("    prefab seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);mesh.setNull();fs->~CFileSystem();Ogre::NedAllocImpl::deallocBytes(fs);g_pFileSystem=previous;return coverage.completed!=384||coverage.missing||coverage.different;
}
}
TL_TEST(complete_generic_prefab){return systems_fixture::isolated(&worker,host);}
