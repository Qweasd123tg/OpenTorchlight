#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#define private public
#define protected public
#include "GenericModel.h"
#include "ResourceManager.h"
#include "MasterResourceManager.h"
#include "Keyframe.h"
#undef protected
#undef private
#include "AnimationSet.h"
#include "DataGroup.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include <OgreSkeletonManager.h>
#include <OgreSkeletonInstance.h>
#include <OgreSubMesh.h>
#include <OgreManualObject.h>
TL_ORIGINAL(void,guAnimOld,(CGenericModel*,float,bool),"_ZN13CGenericModel15updateAnimationEfb")
extern "C" void guAnimNew(CGenericModel*,float,bool) __asm__("_ZN13CGenericModel15updateAnimationEfb");
TL_ORIGINAL(void,guAnimCtor,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_ORIGINAL(void,guAnimDtor,(CGenericModel*),"_ZN13CGenericModelD1Ev")
TL_ORIGINAL(void,guAnimResourceCtor,(CResourceManager*,Ogre::SceneManager*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,guAnimResourceDtor,(CResourceManager*),"_ZN16CResourceManagerD1Ev")
namespace {
nativegame::Services*services;Ogre::MeshPtr mesh;Ogre::SkeletonPtr skeleton;
void number(autotest::Capture&o,unsigned n){o.add(&n,4);}void real(autotest::Capture&o,float f){o.add(&f,4);}
void initialized(uintptr_t address,bool wide){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(address),8);if(!p){if(wide)new(reinterpret_cast<void*>(address))std::wstring;else new(reinterpret_cast<void*>(address))std::string;}}
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=*static_cast<unsigned*>(raw);CResourceManager*resources=static_cast<CResourceManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CResourceManager),0,0,0));guAnimResourceCtor(resources,services->scene);resources->m_bFlag0=seed/96%2;CGenericModel*model=static_cast<CGenericModel*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGenericModel),0,0,0));guAnimCtor(model,NULL,services->scene,OGRE_UTILITIES::PRIMITIVE_SPHERE);model->setResourceManager(resources);model->setEnabled(seed/24%2);model->m_animationPaused=seed/48%2;Ogre::Entity*entity=services->scene->createEntity("generic-update-animation-entity",mesh->getName());model->sceneNodeAttachEntity(entity);model->m_pSkeleton=entity->getSkeleton();const char*names[]={"IDLE","RUN","WALK"};for(unsigned i=0;i<3;++i){Ogre::AnimationState*state=entity->getAnimationState(names[i]);state->setEnabled(seed/12%2);state->setTimePosition(.3f*i);state->setWeight(.25f*(1+i));model->m_animationStates.add(state);}
 CAnimationSet*set=new CAnimationSet;set->m_nAnimationCount=7;set->m_nUnknown=3;set->m_lAnimationGroups.resize(3);std::vector<CKeyframe*>keys;const int events[]={0,8,10,12,13,17,19,20,23,25,7};for(unsigned i=0;i<3;++i){set->m_lUnknown28.push_back(names[i]);set->m_lUnknown40.push_back(L"fixture.skeleton");for(unsigned k=0;k<11;++k){CDataGroup data(L"KEY",NULL,10,10,NULL);CKeyframe*key=new CKeyframe(i,&data);key->m_frame=float(k)*6.f;key->m_iEventCode=events[k];set->m_lAnimationGroups[i].push_back(key);keys.push_back(key);}}services->master->m_animationSets.push_back(set);model->m_animationSet=seed/192%2?NULL:set;model->m_AnimationEvents.push_back(keys[0]);
 unsigned counts[]={0,1,2,3,4,65,66};unsigned n=counts[seed/8%7];unsigned mode=seed/56%9;for(unsigned i=0;i<n;++i){CActiveAnimation*a=new CActiveAnimation;a->m_animation=mode==8?static_cast<unsigned int>(-1):i%3;a->m_length=seed/7%4==0?0.f:1.f+i%3;a->m_duration=a->m_length;a->m_time=.5f*(seed/5%4);a->m_loop=mode!=2;a->m_playing=mode!=3&&mode!=5;a->m_queued=mode==3&&i+1<n;if(mode==3&&i+1==n)a->m_playing=true;a->m_flag27=seed/11%2;a->m_flag28=mode==5;a->m_flag29=mode==6;a->m_flag2a=mode==7;a->m_blendRemaining=mode==4?.2f:0.f;a->m_blendDuration=.4f;a->m_weight=mode==4?.5f:0.f;a->m_speed=seed/3%3==0?0.f:seed/3%3==1?1.f:2.f;model->m_activeAnimations.push_back(a);}
 if(seed>=1152){model->setEnabled(true);model->m_animationPaused=false;resources->m_bFlag0=false;model->m_animationSet=set;}bool noEntity=seed<1152&&seed/384%3==2;if(noEntity)model->m_pEntity=NULL;float times[]={0.f,.01f,.1f,.2f,.5f,1.f,-.1f,1000.f};void(*fn)(CGenericModel*,float,bool)=ours?guAnimNew:guAnimOld;if(autotest::beginInvocation(out,fn)){fn(model,times[seed%8],seed/6%2);out.callCompleted=1;}number(out,model->m_activeAnimations.size());for(unsigned i=0;i<model->m_activeAnimations.size();++i){CActiveAnimation*a=model->m_activeAnimations[i];number(out,a->m_animation);real(out,a->m_time);number(out,a->m_loop);number(out,a->m_playing);number(out,a->m_queued);number(out,a->m_flag27);number(out,a->m_flag28);number(out,a->m_flag29);number(out,a->m_flag2a);real(out,a->m_blendRemaining);real(out,a->m_blendDuration);real(out,a->m_weight);real(out,a->m_speed);}number(out,model->m_AnimationEvents.size());for(unsigned i=0;i<model->m_AnimationEvents.size();++i){std::vector<CKeyframe*>::iterator it=std::find(keys.begin(),keys.end(),model->m_AnimationEvents[i]);if(it==keys.end())std::abort();number(out,it-keys.begin());}for(unsigned i=0;i<3;++i){Ogre::AnimationState*s=entity->getAnimationState(names[i]);number(out,s->getEnabled());real(out,s->getTimePosition());real(out,s->getWeight());}model->m_pEntity=entity;guAnimDtor(model);Ogre::NedAllocImpl::deallocBytes(model);std::vector<CAnimationSet*>&sets=services->master->m_animationSets;sets.erase(std::remove(sets.begin(),sets.end(),set),sets.end());delete set;guAnimResourceDtor(resources);Ogre::NedAllocImpl::deallocBytes(resources);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services native;services=&native;if(!native.ready())return 1;uintptr_t strings[]={0x1482e00,0x14884c0,0x14b37c0};for(unsigned i=0;i<3;++i){initialized(strings[i],false);initialized(strings[i]+8,true);}
 Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().create("generic-update-animation-material","General");material->removeAllTechniques();skeleton=Ogre::SkeletonManager::getSingleton().create("generic-update-animation-skeleton","General",true);skeleton->createBone(0);skeleton->setBindingPose();const char*names[]={"IDLE","RUN","WALK"};for(unsigned i=0;i<3;++i)skeleton->createAnimation(names[i],1.f+i);skeleton->load();Ogre::ManualObject*object=services->scene->createManualObject("generic-update-animation-geometry");object->begin(material->getName(),Ogre::RenderOperation::OT_TRIANGLE_LIST);object->position(-1,-1,0);object->normal(0,0,1);object->position(1,-1,0);object->normal(0,0,1);object->position(0,1,0);object->normal(0,0,1);object->triangle(0,1,2);object->end();mesh=object->convertToMesh("generic-update-animation-mesh","General");services->scene->destroyManualObject(object);mesh->setSkeletonName(skeleton->getName());for(unsigned i=0;i<3;++i){Ogre::VertexBoneAssignment assignment;assignment.vertexIndex=i;assignment.boneIndex=0;assignment.weight=1.f;mesh->getSubMesh(0)->addBoneAssignment(assignment);}mesh->getSubMesh(0)->_compileBoneAssignments();
 autotest::Coverage coverage("generic_update_animation",reinterpret_cast<uintptr_t>(guAnimOld));for(unsigned seed=0;seed<1728;++seed){autotest::Outcome a,b;autotest::runChild(original,&seed,a);autotest::runChild(candidate,&seed,b);if(coverage.observe(host,a,b)){host->log("    update-animation seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);if(a.capture.length==b.capture.length){const unsigned char*x=reinterpret_cast<const unsigned char*>(a.capture.data),*y=reinterpret_cast<const unsigned char*>(b.capture.data);for(unsigned j=0;j<a.capture.length;++j)if(x[j]!=y[j]){host->log("    first byte%u value%u/%u\n",j,x[j],y[j]);break;}}coverage.report(host);return 1;}}coverage.report(host);mesh.setNull();skeleton.setNull();return coverage.completed!=1728||coverage.missing||coverage.different;
}
}
TL_TEST(complete_generic_update_animation){return systems_fixture::isolated(&worker,host);}
