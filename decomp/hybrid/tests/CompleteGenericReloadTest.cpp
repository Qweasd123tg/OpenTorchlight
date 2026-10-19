#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#define private public
#define protected public
#include "GenericModel.h"
#include "ResourceManager.h"
#include "MasterResourceManager.h"
#undef protected
#undef private
#include "AnimationSet.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include <OgreSkeletonManager.h>
#include <OgreSkeletonInstance.h>
#include <OgreSubMesh.h>
TL_ORIGINAL(void,grOld,(CGenericModel*),"_ZN13CGenericModel16reloadAnimationsEv")
extern "C" void grNew(CGenericModel*) __asm__("_ZN13CGenericModel16reloadAnimationsEv");
TL_ORIGINAL(void,grCtor,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_ORIGINAL(void,grDtor,(CGenericModel*),"_ZN13CGenericModelD1Ev")
TL_ORIGINAL(void,grResourceCtor,(CResourceManager*,Ogre::SceneManager*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,grResourceDtor,(CResourceManager*),"_ZN16CResourceManagerD1Ev")
TL_FUNCTION(grLoad,"_ZN13CGenericModel9loadModelESbIwSt11char_traitsIwESaIwEES3_bbb")
namespace {
nativegame::Services*services;Ogre::MeshPtr meshes[2],replacement;Ogre::SkeletonPtr skeleton;CGenericModel*expected;autotest::Capture*output;
void number(unsigned n){output->add(&n,4);}void wide(const std::wstring&s){number(s.size());if(s.size())output->add(s.data(),s.size()*sizeof(wchar_t));}
void load(CGenericModel*p,std::wstring path,std::wstring group,bool a,bool b,bool c){if(p!=expected)std::abort();number(17);wide(path);wide(group);number(a);number(b);number(c);number(p->m_pEntity==NULL);number(p->m_entity230==NULL);number(p->m_pSkeleton==NULL);number(p->m_animationSet==NULL);number(p->m_activeAnimations.size());number(services->scene->hasEntity("generic-reload-entity"));number(Ogre::MeshManager::getSingleton().resourceExists(meshes[0]->getName()));number(Ogre::MeshManager::getSingleton().resourceExists(meshes[1]->getName()));number(skeleton->getNumAnimations());for(unsigned i=0;i<5;++i){const char*names[]={"BIND","bind","Walk","RUN","BiNd"};number(skeleton->hasAnimation(names[i]));}p->m_sModelPath=path;p->m_modelGroup=group;Ogre::Entity*entity=services->scene->createEntity("generic-reload-replacement",replacement->getName());p->sceneNodeAttachEntity(entity);}
void initialized(uintptr_t address,bool wide){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(address),8);if(!p){if(wide)new(reinterpret_cast<void*>(address))std::wstring;else new(reinterpret_cast<void*>(address))std::string;}}
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=*static_cast<unsigned*>(raw);output=&out;CResourceManager*resources=static_cast<CResourceManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CResourceManager),0,0,0));grResourceCtor(resources,services->scene);CGenericModel*model=static_cast<CGenericModel*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGenericModel),0,0,0));grCtor(model,NULL,services->scene,OGRE_UTILITIES::PRIMITIVE_SPHERE);model->setResourceManager(resources);model->setEnabled(seed/2%2);model->setVisible(seed/4%2);expected=model;
 Ogre::AnimationStateSet states;for(unsigned i=0;i<seed/8%4;++i){std::string name="active"+Ogre::StringConverter::toString(i);Ogre::AnimationState*state=states.createAnimationState(name,.5f,2.f);state->setEnabled(true);model->m_animationStates.add(state);CActiveAnimation*active=new CActiveAnimation;active->m_animation=i;model->m_activeAnimations.push_back(active);}
 CAnimationSet*set=new CAnimationSet;set->m_nAnimationCount=7;set->m_nUnknown=seed/32%6;const char*names[]={"BIND","bind","Walk","RUN","BiNd"};for(int i=0;i<set->m_nUnknown;++i)set->m_lUnknown28.push_back(names[i]);if(seed%2){services->master->m_animationSets.push_back(set);model->m_animationSet=set;}
 Ogre::Entity*entity=services->scene->createEntity("generic-reload-entity",meshes[seed/2%2]->getName());model->sceneNodeAttachEntity(entity);model->m_pSkeleton=entity->getSkeleton();model->m_entity230=entity;const wchar_t*paths[]={L"",L"media/hero.mesh",L"\x041b\x0435\x0441.mesh",L"path with spaces"};model->m_sModelPath=paths[seed/6%4];model->m_modelGroup=paths[seed/24%4];
 detour::Set hooks;TL_REDIRECT(hooks,grLoad,&load);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}void(*fn)(CGenericModel*)=ours?grNew:grOld;if(autotest::beginInvocation(out,fn)){fn(model);out.callCompleted=1;}number(model->getEnabled());number(model->m_activeAnimations.size());number(model->m_animationSet==NULL);number(set->m_nAnimationCount);number(services->scene->hasEntity("generic-reload-entity"));number(services->scene->hasEntity("generic-reload-replacement"));wide(model->m_sModelPath);wide(model->m_modelGroup);for(unsigned i=0;i<seed/8%4;++i)number(states.getAnimationState("active"+Ogre::StringConverter::toString(i))->getEnabled());hooks.restore();model->m_entity230=NULL;grDtor(model);Ogre::NedAllocImpl::deallocBytes(model);std::vector<CAnimationSet*>&sets=services->master->m_animationSets;sets.erase(std::remove(sets.begin(),sets.end(),set),sets.end());delete set;grResourceDtor(resources);Ogre::NedAllocImpl::deallocBytes(resources);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services native;services=&native;if(!native.ready())return 1;uintptr_t strings[]={0x1482e00,0x14b37c0};for(unsigned i=0;i<2;++i){initialized(strings[i],false);initialized(strings[i]+8,true);}
 Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().create("generic-reload-material","General");material->removeAllTechniques();skeleton=Ogre::SkeletonManager::getSingleton().create("generic-reload-skeleton","General",true);skeleton->createBone(0);skeleton->setBindingPose();const char*names[]={"BIND","bind","Walk","RUN","BiNd"};for(unsigned i=0;i<5;++i)skeleton->createAnimation(names[i],1.f+i);skeleton->load();for(unsigned i=0;i<3;++i){Ogre::MeshPtr mesh=Ogre::MeshManager::getSingleton().createManual("generic-reload-mesh-"+Ogre::StringConverter::toString(i),"General");mesh->_setBounds(Ogre::AxisAlignedBox(-1,-1,-1,1,1,1),false);mesh->createSubMesh()->setMaterialName(material->getName());if(i==1)mesh->setSkeletonName(skeleton->getName());if(i<2)meshes[i]=mesh;else replacement=mesh;}
 autotest::Coverage coverage("generic_reload_animations",reinterpret_cast<uintptr_t>(grOld));for(unsigned seed=0;seed<192;++seed){autotest::Outcome a,b;autotest::runChild(original,&seed,a);autotest::runChild(candidate,&seed,b);if(coverage.observe(host,a,b)){host->log("    reload seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);replacement.setNull();for(unsigned i=0;i<2;++i)meshes[i].setNull();skeleton.setNull();return coverage.completed!=192||coverage.missing||coverage.different;
}
}
TL_TEST(complete_generic_reload){return systems_fixture::isolated(&worker,host);}
