#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#define private public
#define protected public
#include "GenericModel.h"
#include "ResourceManager.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include <OgreManualObject.h>
#include <OgreSubMesh.h>
#include <OgreSubEntity.h>
TL_ORIGINAL(void,geOld,(CGenericModel*,unsigned long,bool),"_ZN13CGenericModel16generateExtremesEmb")
extern "C" void geNew(CGenericModel*,unsigned long,bool) __asm__("_ZN13CGenericModel16generateExtremesEmb");
TL_ORIGINAL(void,geCtor,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_ORIGINAL(void,geDtor,(CGenericModel*),"_ZN13CGenericModelD1Ev")
TL_ORIGINAL(void,geResourceCtor,(CResourceManager*,Ogre::SceneManager*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,geResourceDtor,(CResourceManager*),"_ZN16CResourceManagerD1Ev")
namespace {
nativegame::Services*services;Ogre::MeshPtr meshes[5];
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=*static_cast<unsigned*>(raw);CResourceManager*resources=static_cast<CResourceManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CResourceManager),0,0,0));geResourceCtor(resources,services->scene);CGenericModel*model=static_cast<CGenericModel*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGenericModel),0,0,0));geCtor(model,NULL,services->scene,OGRE_UTILITIES::PRIMITIVE_SPHERE);model->setResourceManager(resources);Ogre::Entity*entity=services->scene->createEntity("generic-extremes-entity",meshes[seed/2%5]->getName());model->sceneNodeAttachEntity(entity);unsigned long counts[]={0,1,2,3,4,5,6,7,8,9,10,12,16,24,32,64};unsigned long count=counts[seed/10%16];void(*fn)(CGenericModel*,unsigned long,bool)=ours?geNew:geOld;if(autotest::beginInvocation(out,fn)){fn(model,count,seed%2);out.callCompleted=1;}unsigned n=entity->getNumSubEntities();out.add(&n,4);for(unsigned i=0;i<n;++i){Ogre::SubMesh*sub=entity->getSubEntity(i)->getSubMesh();unsigned size=sub->extremityPoints.size();out.add(&size,4);for(unsigned j=0;j<size;++j)out.add(&sub->extremityPoints[j],sizeof(Ogre::Vector3));}geDtor(model);Ogre::NedAllocImpl::deallocBytes(model);geResourceDtor(resources);Ogre::NedAllocImpl::deallocBytes(resources);}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services native;services=&native;if(!native.ready())return 1;for(unsigned i=0;i<2;++i){uintptr_t address=0x1482e00+i*8;void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(address),8);if(!p){if(i)new(reinterpret_cast<void*>(address))std::wstring;else new(reinterpret_cast<void*>(address))std::string;}}
 Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().create("generic-extremes-material","General");material->removeAllTechniques();meshes[0]=Ogre::MeshManager::getSingleton().createManual("generic-extremes-mesh0","General");meshes[0]->_setBounds(Ogre::AxisAlignedBox(-1,-1,-1,1,1,1),false);
 for(unsigned n=1;n<5;++n){Ogre::ManualObject*object=services->scene->createManualObject("generic-extremes-manual-"+Ogre::StringConverter::toString(n));for(unsigned section=0;section<n;++section){object->begin(material->getName(),Ogre::RenderOperation::OT_TRIANGLE_LIST);for(unsigned triangle=0;triangle<1+(n+section)%3;++triangle){float x=3.f*section,y=float(triangle)*1.5f,z=float(section)-float(triangle);object->position(x-2,y-1,z);object->position(x+2,y-1,z+1.f);object->position(x,y+3,z-1.f);if((n+section)%2)object->triangle(triangle*3,triangle*3+1,triangle*3+2);}object->end();}meshes[n]=object->convertToMesh("generic-extremes-mesh"+Ogre::StringConverter::toString(n),"General");services->scene->destroyManualObject(object);}
 autotest::Coverage coverage("generic_generate_extremes",reinterpret_cast<uintptr_t>(geOld));for(unsigned seed=0;seed<160;++seed){autotest::Outcome a,b;autotest::runChild(original,&seed,a);autotest::runChild(candidate,&seed,b);if(coverage.observe(host,a,b)){host->log("    extremes seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);for(unsigned i=0;i<5;++i)meshes[i].setNull();return coverage.completed!=160||coverage.missing||coverage.different;
}
}
TL_TEST(complete_generic_extremes){return systems_fixture::isolated(&worker,host);}
