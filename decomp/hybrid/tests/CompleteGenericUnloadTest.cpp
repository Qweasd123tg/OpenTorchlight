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
#include "Keyframe.h"
#include "DataGroup.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include <OgreSkeletonManager.h>
#include <OgreSkeletonInstance.h>
#include <OgreMeshManager.h>
#include <OgreSubMesh.h>
TL_ORIGINAL(void,guOld,(CGenericModel*),"_ZN13CGenericModel11unloadModelEv")
extern "C" void guNew(CGenericModel*) __asm__("_ZN13CGenericModel11unloadModelEv");
TL_ORIGINAL(void,guCtor,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_ORIGINAL(void,guDtor,(CGenericModel*),"_ZN13CGenericModelD1Ev")
TL_ORIGINAL(void,guResourceCtor,(CResourceManager*,Ogre::SceneManager*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,guResourceDtor,(CResourceManager*),"_ZN16CResourceManagerD1Ev")
namespace {
nativegame::Services*services;Ogre::MeshPtr meshes[2];
void number(autotest::Capture&o,unsigned n){o.add(&n,4);}void wide(autotest::Capture&o,const std::wstring&s){number(o,s.size());if(s.size())o.add(s.data(),s.size()*sizeof(wchar_t));}
void initialized(uintptr_t address,bool wide){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(address),8);if(!p){if(wide)new(reinterpret_cast<void*>(address))std::wstring;else new(reinterpret_cast<void*>(address))std::string;}}
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=*static_cast<unsigned*>(raw);CResourceManager*resources=static_cast<CResourceManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CResourceManager),0,0,0));guResourceCtor(resources,services->scene);CGenericModel*model=static_cast<CGenericModel*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGenericModel),0,0,0));guCtor(model,NULL,NULL,OGRE_UTILITIES::PRIMITIVE_SPHERE);model->setResourceManager(resources);
 CAnimationSet*set=new CAnimationSet;set->m_nAnimationCount=3+seed%4;if(seed/6%2)services->master->m_animationSets.push_back(set);model->m_animationSet=seed/12%3?set:NULL;
 std::vector<CKeyframe*>keys;set->m_lAnimationGroups.resize(1);CDataGroup data(L"key",NULL,10,10,NULL);for(unsigned i=0;i<seed/36%4;++i){CKeyframe*key=new CKeyframe(i,&data);keys.push_back(key);set->m_lAnimationGroups[0].push_back(key);model->m_AnimationEvents.push_back(key);}
 unsigned mode=seed%6;Ogre::Entity*main=NULL,*backup=NULL;if(mode==1||mode==3||mode==4||mode==5)main=services->scene->createEntity("generic-unload-main",meshes[seed/72%2]->getName());if(mode==2||mode==4)backup=services->scene->createEntity("generic-unload-backup",meshes[seed/72%2]->getName());if(mode==3)backup=main;if(main){model->sceneNodeAttachEntity(main);if(seed/3%2)model->setVisible(true);}model->m_entity230=backup;model->m_pSkeleton=main&&main->hasSkeleton()?main->getSkeleton():backup&&backup->hasSkeleton()?backup->getSkeleton():NULL;
 const wchar_t*paths[]={L"",L"media/model.mesh",L"\x041b\x0435\x0441.mesh",L"path with spaces"};model->m_sModelPath=paths[seed/18%4];model->m_modelGroup=paths[seed/54%4];void(*fn)(CGenericModel*)=ours?guNew:guOld;if(autotest::beginInvocation(out,fn)){fn(model);out.callCompleted=1;}
 number(out,model->m_animationSet==NULL);number(out,model->m_pSkeleton==NULL);number(out,model->m_pEntity==NULL);number(out,model->m_entity230==backup);number(out,model->m_AnimationEvents.size());number(out,set->m_nAnimationCount);number(out,set->m_lAnimationGroups[0].size());wide(out,model->m_sModelPath);wide(out,model->m_modelGroup);number(out,services->scene->hasEntity("generic-unload-main"));number(out,services->scene->hasEntity("generic-unload-backup"));for(unsigned i=0;i<keys.size();++i){number(out,keys[i]->getAnimationIndex());number(out,keys[i]->getEventCode());}
 // The native target intentionally leaves the backup slot unchanged after
 // destruction. Observe that exact value, then clear the stale fixture link
 // before the separate model D1 invocation.
 model->m_entity230=NULL;guDtor(model);Ogre::NedAllocImpl::deallocBytes(model);if(services->scene->hasEntity("generic-unload-main"))services->scene->destroyEntity("generic-unload-main");if(services->scene->hasEntity("generic-unload-backup"))services->scene->destroyEntity("generic-unload-backup");std::vector<CAnimationSet*>&sets=services->master->m_animationSets;sets.erase(std::remove(sets.begin(),sets.end(),set),sets.end());delete set;guResourceDtor(resources);Ogre::NedAllocImpl::deallocBytes(resources);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services native;services=&native;if(!native.ready())return 1;uintptr_t strings[]={0x1482e00,0x14884c0,0x14b37c0};for(unsigned i=0;i<3;++i){initialized(strings[i],false);initialized(strings[i]+8,true);}
 Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().create("generic-unload-material","General");material->removeAllTechniques();Ogre::SkeletonPtr skeleton=Ogre::SkeletonManager::getSingleton().create("generic-unload-skeleton","General",true);skeleton->createBone(0);skeleton->setBindingPose();skeleton->load();for(unsigned i=0;i<2;++i){meshes[i]=Ogre::MeshManager::getSingleton().createManual("generic-unload-mesh-"+Ogre::StringConverter::toString(i),"General");meshes[i]->_setBounds(Ogre::AxisAlignedBox(-1,-1,-1,1,1,1),false);meshes[i]->createSubMesh()->setMaterialName(material->getName());if(i)meshes[i]->setSkeletonName(skeleton->getName());}
 autotest::Coverage coverage("generic_unload_model",reinterpret_cast<uintptr_t>(guOld));for(unsigned seed=0;seed<432;++seed){autotest::Outcome a,b;autotest::runChild(original,&seed,a);autotest::runChild(candidate,&seed,b);if(coverage.observe(host,a,b)){host->log("    unload seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);for(unsigned i=0;i<2;++i)meshes[i].setNull();return coverage.completed!=432||coverage.missing||coverage.different;
}
}
TL_TEST(complete_generic_unload){return systems_fixture::isolated(&worker,host);}
