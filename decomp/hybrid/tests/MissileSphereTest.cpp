#include "AutoTest.h"
#include <Ogre.h>
#define private public
#define protected public
#include "Missile.h"
#include "OgreUtilities.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/SmallMassCompare.h"
TL_ORIGINAL(void,msOld,(CMissile*),"_ZN8CMissile11placeSphereEv")
extern "C" void msNew(CMissile*) __asm__("_ZN8CMissile11placeSphereEv");
TL_FUNCTION(msCreate,"_ZN14OGRE_UTILITIES12createEntityEPN4Ogre12SceneManagerENS_11EPRIMITIVESENS_10EQUERYMASKEPKc")
namespace {
nativegame::Services*services;autotest::Capture*output;unsigned created;bool armed;
void number(unsigned n){if(armed)output->add(&n,4);}
void vector(const Ogre::Vector3&v){if(armed)output->add(&v,sizeof v);}
Ogre::Entity*create(Ogre::SceneManager*scene,OGRE_UTILITIES::EPRIMITIVES primitive,OGRE_UTILITIES::EQUERYMASK mask,const char*name){number(1);number(scene==services->scene);number(primitive);number(mask);unsigned length=std::strlen(name);number(length);if(armed)output->add(name,length);return scene->createEntity("missile-sphere-"+Ogre::StringConverter::toString(created++),"missile-sphere-mesh");}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;armed=false;created=0;CResourceManager resources(services->scene);CMissile*missile=new CMissile(&resources);
 const unsigned sizes[]={0,1,9,10,11,19,20,21};unsigned size=sizes[c.index%8];
 for(unsigned i=0;i<size;++i){Ogre::SceneNode*node=services->scene->createSceneNode();node->attachObject(create(services->scene,OGRE_UTILITIES::PRIMITIVE_SPHERE,OGRE_UTILITIES::QUERY_MASK_DEFAULT,"setup"));node->setScale(.2f,.3f,.4f);node->setPosition(Ogre::Vector3(float(i),float(i+1),float(i+2)));missile->m_sceneNodes.add(node);}
 missile->m_iUnknown208=(c.index/8%3==0)?0:(c.index/8%3==1&&size?size-1:size);
 detour::Set hooks;TL_REDIRECT(hooks,msCreate,&create);if(hooks.failed())std::abort();
 typedef void(*Fn)(CMissile*);Fn fn=ours?msNew:msOld;armed=true;if(!autotest::beginInvocation(out,fn))return;
 unsigned repeat=1+c.index/24%12;
 for(unsigned j=0;j<repeat;++j){missile->setPosition(Ogre::Vector3(float(int(c.index%9)-4)+.25f*j,-float(j),float(c.index%7)*-.5f));fn(missile);number(missile->m_iUnknown208);number(missile->m_sceneNodes.size());number(missile->m_sceneNodes.m_nCapacity);}
 out.callCompleted=1;number(created);number(missile->m_sceneNodes.m_nGrowBy);
 for(unsigned i=0;i<missile->m_sceneNodes.size();++i){Ogre::SceneNode*node=missile->m_sceneNodes[i];vector(node->getPosition());vector(node->getScale());number(node->getParentSceneNode()==services->scene->getRootSceneNode());number(node->numAttachedObjects());number(dynamic_cast<Ogre::Entity*>(node->getAttachedObject(0))!=NULL);}
 armed=false;hooks.restore();delete missile;
}
int worker(const tlhybrid_host*host){nativegame::Services native;if(!native.ready())return 1;services=&native;Ogre::SceneManager*old=native.master->m_pSceneManager;native.master->m_pSceneManager=native.scene;
 Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().create("missile-sphere-material","General");material->removeAllTechniques();Ogre::MeshPtr mesh=Ogre::MeshManager::getSingleton().createManual("missile-sphere-mesh","General");mesh->_setBounds(Ogre::AxisAlignedBox(-1,-1,-1,1,1,1),false);mesh->createSubMesh()->setMaterialName(material->getName());
 int result=smallmass::run(host,0,"missile_sphere_native",0xcf8f90,&side,192);native.master->m_pSceneManager=old;return result;}
}
TL_TEST(missile_sphere_native){return systems_fixture::isolated(&worker,host);}
