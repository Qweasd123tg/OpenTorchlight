#include "AutoTest.h"
#include "tests/NativeEditorControls.h"
#include "tests/NativeMenuClient.h"
#include "tests/SystemsFixtureWorker.h"
#include "GenericModel.h"
#include "UtilitiesMath.h"
#include <OgreSubMesh.h>
TL_ORIGINAL(void,drOld,(CObjectControl3D*),"_ZN16CObjectControl3D19UpdateChunkTemplateEv")
extern "C" void drNew(CObjectControl3D*) __asm__("_ZN16CObjectControl3D19UpdateChunkTemplateEv");
TL_ORIGINAL(void,drModelCtor,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_FUNCTION(drMouse,"_ZN13CMouseHandler13MousePositionEv")
TL_FUNCTION(drRay,"_ZN4MATH16screenToWorldRayEPN4Ogre6CameraEffff")
namespace {
nativeeditor::Controls*owners;nativegame::Services*services;Ogre::Camera*camera;Ogre::MeshPtr mesh;autotest::Capture*output;unsigned seed;Ogre::Vector3 direction;
void n(unsigned v){output->add(&v,4);}void vec(const Ogre::Vector3&v){output->add(v.ptr(),12);}
POINT mouse(CMouseHandler*p){if(p!=owners->control->m_mouseHandler)std::abort();n(11);POINT q={17+int(seed%5),23-int(seed%7)};return q;}
Ogre::Vector3 ray(Ogre::Camera*p,float x,float y,float width,float height){if(p!=camera)std::abort();n(12);output->add(&x,4);output->add(&y,4);output->add(&width,4);output->add(&height,4);return direction;}
void side(void*raw,autotest::Capture&out,bool ours){seed=*static_cast<unsigned*>(raw);output=&out;CObjectControl3D*c=owners->control;const unsigned counts[]={0,1,9,19,20,21,24};unsigned count=counts[seed%7];
 for(unsigned i=0;i<count;++i){CGenericModel*p=static_cast<CGenericModel*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGenericModel),0,0,0));drModelCtor(p,NULL,services->scene,OGRE_UTILITIES::PRIMITIVE_BOX);p->setResourceManager(owners->resources);char name[50];std::sprintf(name,"chunk-entity-%u",i);Ogre::Entity*e=services->scene->createEntity(name,mesh->getName());p->sceneNodeAttachEntity(e);p->sceneNodeSetParent(services->scene->getRootSceneNode(),false);p->setPosition(Ogre::Vector3(float(i)-3,4,5));p->setScale(2.f,3.f,4.f);p->setVisible((seed+i)%2);c->m_models.push_back(p);}
 const float depths[]={0.f,8.f,-3.f,.125f};c->m_chunkDepth=depths[seed/77%4];c->m_chunkCount=seed/7%11;c->m_chunkWidth=float(seed/4%9)-2.5f;c->m_chunkSize=float(seed/9%5)-1.25f;for(unsigned i=0;i<20;++i)c->m_chunkPositions[i]=Ogre::Vector3(float(i)-2.25f,float(seed%3)-1.5f,float(i)*.75f);
 void(*fn)(CObjectControl3D*)=ours?drNew:drOld;if(autotest::beginInvocation(out,fn)){fn(c);out.callCompleted=1;}for(unsigned i=0;i<count;++i){CGenericModel*p=c->m_models[i];n(p->getVisible());vec(p->getPosition(false));vec(p->getScale());vec(p->getSceneNode()->getPosition());vec(p->getSceneNode()->getScale());n(p->getEntity()->getVisible());delete p;}c->m_models.clear();
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
void initialized(uintptr_t address,bool wide,const wchar_t*value=L""){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(address),8);if(!p){if(wide)new(reinterpret_cast<void*>(address))std::wstring(value);else new(reinterpret_cast<void*>(address))std::string;}}
int worker(const tlhybrid_host*host){nativegame::Services native;services=&native;if(!native.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());menugui::Client client(*CMasterResourceManager::getSingleton()->m_pSettings,CMasterResourceManager::getSingleton(),*CMasterResourceManager::getSingleton()->m_pSoundManager);camera=client.camera->m_cameras[0];nativeeditor::Controls actual(native);owners=&actual;initialized(0x1482e00,false);initialized(0x1482e08,true);const wchar_t*names[]={L"SPHERE",L"BOX",L"PLANE",L"CYLINDER",L"CONE",L"ARROW"};for(unsigned i=0;i<6;++i)initialized(0x1482e20+i*8,true,names[i]);Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().create("object-drag-material","General");material->removeAllTechniques();mesh=Ogre::MeshManager::getSingleton().createManual("object-drag-mesh","General");mesh->_setBounds(Ogre::AxisAlignedBox(-.2f,-.2f,-.2f,.2f,.2f,.2f),false);mesh->createSubMesh()->setMaterialName(material->getName());autotest::Coverage coverage("object_chunk",reinterpret_cast<uintptr_t>(drOld));for(unsigned seed=0;seed<616;++seed){autotest::Outcome a,b;autotest::runChild(original,&seed,a);autotest::runChild(candidate,&seed,b);if(coverage.observe(host,a,b)){host->log("    chunk seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);mesh.setNull();return coverage.completed!=616||coverage.missing||coverage.different;}
}
TL_TEST(complete_object_chunk){return systems_fixture::isolated(&worker,host);}
