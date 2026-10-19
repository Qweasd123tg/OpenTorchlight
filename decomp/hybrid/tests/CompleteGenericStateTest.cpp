#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#define private public
#define protected public
#include "GenericModel.h"
#include "ResourceManager.h"
#include "GameClient.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"
#include "tests/NativeMenuClient.h"
#include "tests/SystemsFixtureWorker.h"
#include <OgreSubMesh.h>
TL_ORIGINAL(void,gsOldCasts,(CGenericModel*,bool),"_ZN13CGenericModel15setCastsShadowsEb")
TL_ORIGINAL(void,gsOldLight,(CGenericModel*,bool),"_ZN13CGenericModel19setRenderToLightMapEb")
TL_ORIGINAL(void,gsOldRelease,(CGenericModel*),"_ZN13CGenericModel22releaseUniqueMaterialsEv")
TL_ORIGINAL(void,gsResourceCtor,(CResourceManager*,Ogre::SceneManager*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,gsResourceDtor,(CResourceManager*),"_ZN16CResourceManagerD1Ev")
extern "C" void gsNewCasts(CGenericModel*,bool) __asm__("_ZN13CGenericModel15setCastsShadowsEb");
extern "C" void gsNewLight(CGenericModel*,bool) __asm__("_ZN13CGenericModel19setRenderToLightMapEb");
extern "C" void gsNewRelease(CGenericModel*) __asm__("_ZN13CGenericModel22releaseUniqueMaterialsEv");
namespace {
nativegame::Services*services;CGameClient*client;
struct Case{unsigned op,count,entity,value,mode,mask,removed;};
void integer(autotest::Capture&out,unsigned n){out.add(&n,4);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);
 CResourceManager*resources=static_cast<CResourceManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CResourceManager),0,0,0));gsResourceCtor(resources,services->scene);if(c.mode==2)resources->m_GameClients.add(client);client->m_pendingPassClear=false;
 CGenericModel*model=new CGenericModel(NULL,services->scene,static_cast<OGRE_UTILITIES::EPRIMITIVES>(0));model->setResourceManager(c.op==2&&c.mode==0?NULL:resources);
 std::vector<Ogre::MaterialPtr>materials;for(unsigned i=0;i<3;++i){Ogre::MaterialPtr m=Ogre::MaterialManager::getSingleton().create("generic-state-material-"+Ogre::StringConverter::toString(i),"General");m->removeAllTechniques();materials.push_back(m);}
 Ogre::Entity*entity=NULL;if(c.entity){Ogre::MeshPtr mesh=Ogre::MeshManager::getSingleton().createManual("generic-state-mesh","General");mesh->_setBounds(Ogre::AxisAlignedBox(-1,-1,-1,1,1,1),false);mesh->createSubMesh()->setMaterialName(materials[0]->getName());entity=services->scene->createEntity("generic-state-entity",mesh->getName());model->m_pEntity=entity;entity->setVisibilityFlags(0x35);entity->setRenderQueueGroup(17);}
 model->m_renderToLightMap=!c.value;model->m_uniqueMaterials=c.value;
 for(unsigned i=0;i<c.count;++i){CRenderableStates state=CRenderableStates();state.castsShadows=(i&1)!=0;state.material=(c.mask&1)?materials[0].getPointer():NULL;state.material18=(c.mask&2)?materials[1].getPointer():NULL;state.material20=(c.mask&4)?materials[2].getPointer():NULL;model->m_renderableStates.push_back(state);}
 if(c.removed)Ogre::MaterialManager::getSingleton().remove(materials[1]->getName());services->scene->getRenderQueue()->setDefaultQueueGroup(c.mode*31);
 if(c.op==0){void(*fn)(CGenericModel*,bool)=ours?gsNewCasts:gsOldCasts;if(autotest::beginInvocation(out,fn)){fn(model,c.value);out.callCompleted=1;}}
 else if(c.op==1){void(*fn)(CGenericModel*,bool)=ours?gsNewLight:gsOldLight;if(autotest::beginInvocation(out,fn)){fn(model,c.value);out.callCompleted=1;}}
 else{void(*fn)(CGenericModel*)=ours?gsNewRelease:gsOldRelease;if(autotest::beginInvocation(out,fn)){fn(model);out.callCompleted=1;}}
 integer(out,model->m_renderToLightMap);integer(out,model->m_uniqueMaterials);integer(out,client->m_pendingPassClear);integer(out,model->m_renderableStates.size());for(unsigned i=0;i<c.count;++i)integer(out,model->m_renderableStates[i].castsShadows);for(unsigned i=0;i<3;++i){integer(out,Ogre::MaterialManager::getSingleton().resourceExists(materials[i]->getName()));integer(out,materials[i]->isLoaded());}
 if(entity){integer(out,entity->getVisibilityFlags());integer(out,entity->getRenderQueueGroup());}
 delete model;resources->m_GameClients.clear();gsResourceDtor(resources);Ogre::NedAllocImpl::deallocBytes(resources);
}
void oldSide(void*p,autotest::Capture&o){side(p,o,false);}void newSide(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services native;services=&native;menugui::Audio audio(native.master);menugui::Client actualClient(*native.settings,native.master,*native.master->m_pSoundManager);client=actualClient.client;int failures=0;unsigned counts[]={0,1,4};
 const char*names[]={"generic_casts","generic_lightmap","generic_release"};uintptr_t addresses[]={reinterpret_cast<uintptr_t>(gsOldCasts),reinterpret_cast<uintptr_t>(gsOldLight),reinterpret_cast<uintptr_t>(gsOldRelease)};
 for(unsigned op=0;op<3;++op){autotest::Stats stats={0,0,0};autotest::Coverage coverage(names[op],addresses[op]);unsigned n=0;for(unsigned i=0;i<3;++i)for(unsigned value=0;value<2;++value)for(unsigned mode=0;mode<3;++mode)for(unsigned variant=0;variant<(op==2?16u:2u);++variant){Case c={op,counts[i],op==2?0u:variant,value,mode,op==2?(variant&7):0u,op==2?(variant>>3):0u};bool ok=autotest::compareCase(oldSide,newSide,&c,stats,host,names[op],n++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);failures+=stats.incomplete+(coverage.completed!=n);}
 return failures;
}
}
TL_TEST(complete_generic_state){return systems_fixture::isolated(&worker,host);}
