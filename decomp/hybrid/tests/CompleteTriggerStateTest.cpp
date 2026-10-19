#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#include <vector>
#include <limits>
#define private public
#define protected public
#include "TriggerUnit.h"
#include "Level.h"
#include "CollisionList.h"
#include "GenericModel.h"
#include "AnimationSet.h"
#include "Layout.h"
#include "SoundBank.h"
#include "ActiveAnimation.h"
#include "CullingBounds.h"
#include "DataGroup.h"
#include "StringUtilities.h"
#undef protected
#undef private
#include "NativeTriggerLevelFixture.h"
#include "tests/NativeMenuClient.h"
#include "tests/NativeEditorControls.h"
#include "tests/CharacterEmptyGlobals.h"
#include "tests/SmallMassCompare.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(void,tsStateOld,(CTriggerUnit*,ETRIGGER_STATES,bool,bool,bool),"_ZN12CTriggerUnit15setTriggerStateE15ETRIGGER_STATESbbb")
TL_ORIGINAL(void,tsResetOld,(CTriggerUnit*),"_ZN12CTriggerUnit12resetTriggerEv")
TL_ORIGINAL(void,tsActiveOld,(CTriggerUnit*,bool),"_ZN12CTriggerUnit16setActiveInLevelEb")
TL_ORIGINAL(void,tsUpdateOld,(CTriggerUnit*,Ogre::Camera*,const Ogre::Vector3&,float),"_ZN12CTriggerUnit6updateEPN4Ogre6CameraERKNS0_7Vector3Ef")
TL_ORIGINAL(void,tsAnimationsOld,(CTriggerUnit*),"_ZN12CTriggerUnit13addAnimationsEv")
extern "C" void tsStateNew(CTriggerUnit*,ETRIGGER_STATES,bool,bool,bool) __asm__("_ZN12CTriggerUnit15setTriggerStateE15ETRIGGER_STATESbbb");
extern "C" void tsResetNew(CTriggerUnit*) __asm__("_ZN12CTriggerUnit12resetTriggerEv");
extern "C" void tsActiveNew(CTriggerUnit*,bool) __asm__("_ZN12CTriggerUnit16setActiveInLevelEb");
extern "C" void tsUpdateNew(CTriggerUnit*,Ogre::Camera*,const Ogre::Vector3&,float) __asm__("_ZN12CTriggerUnit6updateEPN4Ogre6CameraERKNS0_7Vector3Ef");
extern "C" void tsAnimationsNew(CTriggerUnit*) __asm__("_ZN12CTriggerUnit13addAnimationsEv");
TL_FUNCTION(tsSnap,"_ZN5CItem12snapToGroundEv")
TL_FUNCTION(tsItemUpdate,"_ZN5CItem6updateEPN4Ogre6CameraERKNS0_7Vector3Ef")
namespace {
nativegame::Services*services;autotest::Capture*output;CTriggerUnit*unit;CLevel*level;bool recording;Ogre::Camera*camera;
void n(unsigned x){output->add(&x,4);}void f(float x){output->add(&x,4);}
void snap(CItem*p){n(90);n(p==unit);p->setY(2.75f);}
void itemUpdate(CItem*p,Ogre::Camera*c,const Ogre::Vector3&v,float elapsed){n(91);n(p==unit);n(c!=NULL);output->add(&v,sizeof v);f(elapsed);p->m_bInActiveRange=!p->m_bInActiveRange;}
struct Trigger:CTriggerUnit{
 explicit Trigger(CResourceManager*r):CTriggerUnit(r){}
 virtual void BroadcastEvent(unsigned event){if(recording){n(1);n(event);}CEditorBaseObject::BroadcastEvent(event);}
 virtual void addToAvoidanceMap(CLevel&l){if(recording){n(2);n(&l==level);}}
 virtual void removeFromAvoidanceMap(CLevel&l){if(recording){n(3);n(&l==level);}}
 virtual void setVisible(bool visible,bool immediate){if(recording){n(4);n(visible);n(immediate);}CTriggerUnit::setVisible(visible,immediate);}
};
struct Layout:CLayout{
 explicit Layout(CResourceManager*r):CLayout(r,static_cast<ELAYOUT_TYPES>(1)){}
 virtual void update(float elapsed){if(recording){n(6);f(elapsed);}CLayout::update(elapsed);}
};
void snapshot(CTriggerUnit&u){
 n(u.m_state);n(u.m_minState);n(u.m_maxState);n(u.m_flag25C);n(u.m_pendingStateEvent);n(u.m_bVisible);n(u.m_bRequestedVisible);n(u.m_bInActiveRange);n(u.m_bPathingFlag19C);n(u.m_bItemFlag1F0);f(u.m_fForcedActiveTime);output->add(&u.m_vPosition,sizeof u.m_vPosition);
 n(u.m_animations.size());for(unsigned i=0;i<u.m_animations.size();++i)n(u.m_animations[i]);
 n(u.m_altAnimations.size());for(unsigned i=0;i<u.m_altAnimations.size();++i)n(u.m_altAnimations[i]);
 n(u.m_looping.size());for(unsigned i=0;i<u.m_looping.size();++i)n(u.m_looping[i]);
 for(unsigned i=0;i<u.m_stateLayouts.size();++i){CLayout*l=u.m_stateLayouts[i];n(l!=NULL);if(l){n(l->m_bVisible);n(l->m_bEnabled);n(l->m_bStartOnLoad);n(l->m_bUnknown1C8);n(l->m_bUnknown1C9);}}
 if(u.m_unitModel){CGenericModel*m=u.m_unitModel;n(m->m_animationPlaying);n(m->m_activeAnimations.size());for(unsigned i=0;i<m->m_activeAnimations.size();++i){CActiveAnimation*a=m->m_activeAnimations[i];n(a->m_animation);f(a->m_time);f(a->m_length);f(a->m_duration);n(a->m_loop);n(a->m_playing);n(a->m_queued);f(a->m_blendDuration);f(a->m_speed);}for(unsigned i=0;i<m->m_animationStates.size();++i){Ogre::AnimationState*a=m->m_animationStates[i];f(a->getTimePosition());f(a->getWeight());n(a->getEnabled());}}
}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;recording=false;unsigned seed=c.index;nativetrigger::LevelFixture fixture(*services);fixture.resources.m_pSceneManager=services->scene;fixture.resources.m_pLevel=&fixture.level;level=&fixture.level;fixture.level.m_automapRoomPieces=seed/3%2;
 Ogre::AnimationStateSet states;CAnimationSet set;const char*names[]={"IDLE","OPEN","CLOSE","TRANSITION","loop",""};for(unsigned i=0;i<6;++i){set.m_lUnknown28.push_back(names[i]);set.m_lUnknown40.push_back(L"trigger-fixture");set.m_lAnimationGroups.push_back(std::vector<CKeyframe*>());states.createAnimationState(names[i],0,1.f+i*.5f,1,false);}
 Trigger u(&fixture.resources);unit=&u;u.sceneNodeSetParent(services->scene->getRootSceneNode(),false);u.m_pSoundBank=new CSoundBank(*services->master->m_pSoundManager,false);u.m_bVisible=seed%2;u.m_bRequestedVisible=seed/2%2;u.m_state=int(seed%5)-1;u.m_minState=seed/7%2;u.m_maxState=2+seed/11%3;u.m_flag25C=seed/5%2;u.m_pendingStateEvent=seed/13%2;u.m_bInActiveRange=seed/17%2;u.m_bBlocksPath=seed/19%2;u.m_bItemFlag218=seed/23%2;u.m_bPathingFlag19C=seed/29%2;u.m_fForcedActiveTime=.625f;
 if(seed%4){u.m_unitModel=new CGenericModel(&fixture.resources,services->scene,L"",L"",false);u.m_unitModel->m_animationSet=&set;for(unsigned i=0;i<6;++i)u.m_unitModel->m_animationStates.add(states.getAnimationState(names[i]));u.m_unitModel->m_animationPlaying=seed%3?seed%6:~0u;if(c.op==3&&seed%3==1)u.m_unitModel->playAnimation(seed%6,seed/3%2,1,-1);}
 for(unsigned i=0;i<6;++i){u.m_animations.add((i+seed)%6);u.m_altAnimations.add((seed+i)%3?~0u:(i+seed+1)%6);u.m_looping.add((seed+i)%2);}
 for(unsigned i=0;i<seed%5;++i)u.m_stateLayouts.add((seed+i)%3?new Layout(&fixture.resources):NULL);
 if(seed/31%2)u.m_layout=new Layout(&fixture.resources);if(seed/37%2)u.m_layout2C8=new Layout(&fixture.resources);
 CDataGroup data(L"unit",NULL,10,10,NULL);u.m_pDataGroup=&data;
 for(unsigned i=1;i<=5;++i){std::wstring suffix=STRINGS::GetValueAsWString(i);unsigned k=(seed+i)%7;if(k<3)data.SetDataValue(L"ANIMATION_STATE_LOOP_"+suffix,std::wstring(k==0?L"OPEN":k==1?L"loop":L"unknown"),false);if(k<5)data.SetDataValue(L"ANIMATION_STATE_"+suffix,std::wstring(k==3?L"CLOSE":L"IDLE"),false);if(k%2)data.SetDataValue(L"ANIMATION_TRANSITION_STATE_"+suffix,std::wstring(k==1?L"TRANSITION":k==3?L"":L"missing"),false);}
 CResourceManager* saved=u.m_pResourceManager;CLevel*savedLevel=saved->m_pLevel;if(c.op==2&&seed/9%3==1)u.m_pResourceManager=NULL;else if(c.op==2&&seed/9%3==2)saved->m_pLevel=NULL;
 CCollisionList collision;fixture.level.m_collisionList=seed/41%2?&collision:NULL;
 detour::Set hooks;TL_REDIRECT(hooks,tsSnap,&snap);TL_REDIRECT(hooks,tsItemUpdate,&itemUpdate);if(hooks.failed())std::abort();recording=true;
 if(c.op==0){void(*fn)(CTriggerUnit*,ETRIGGER_STATES,bool,bool,bool)=ours?tsStateNew:tsStateOld;autotest::invoke(out,fn,&u,static_cast<ETRIGGER_STATES>(int(seed/2%9)-3),bool(seed/5%2),bool(seed/7%2),bool(seed/11%2));}
 else if(c.op==1)autotest::invoke(out,ours?tsResetNew:tsResetOld,&u);
 else if(c.op==2)autotest::invoke(out,ours?tsActiveNew:tsActiveOld,&u,bool(seed%2));
 else if(c.op==3){Ogre::Vector3 position(1.25f,-2,3.5f);autotest::invoke(out,ours?tsUpdateNew:tsUpdateOld,&u,seed%2?camera:static_cast<Ogre::Camera*>(NULL),position,float(int(seed%9)-3)*.125f);}
 else{if(seed/5%3==1&&u.m_unitModel)u.m_unitModel->m_animationSet=NULL;else if(seed/5%3==2)set.m_lUnknown28.clear();autotest::invoke(out,ours?tsAnimationsNew:tsAnimationsOld,&u);}
 recording=false;hooks.restore();snapshot(u);fixture.level.m_collisionList=NULL;u.m_pResourceManager=saved;saved->m_pLevel=savedLevel;if(u.m_unitModel)u.m_unitModel->m_animationSet=NULL;
}
int worker(const tlhybrid_host*host){
 initEmptyGlobals();void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x148c4e8),8);if(!p)new(reinterpret_cast<void*>(0x148c4e8))std::wstring;
 nativegame::Services native;services=&native;if(!native.ready())return 1;menugui::Audio audio(native.master);nativeeditor::Controls editor(native);
{menugui::ProjectionDuringConstruction projection;camera=new Ogre::Camera("trigger-state-camera",native.scene);}
 const char*names[]={"trigger_state_native","trigger_reset_native","trigger_active_native","trigger_update_native","trigger_animations_native"};const unsigned addresses[]={0x8fc4e0,0x8fcc70,0x8fc3f0,0x8fcdf0,0x909ee0};for(unsigned i=0;i<5;++i)if(smallmass::run(host,i,names[i],addresses[i],&side,256))return 1;delete camera;return 0;
}
}
TL_TEST(complete_trigger_state){return systems_fixture::isolated(&worker,host);}
