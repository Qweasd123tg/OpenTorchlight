#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#define private public
#define protected public
#include "TriggerUnit.h"
#include "Level.h"
#include "GenericModel.h"
#include "AnimationSet.h"
#include "ActiveAnimation.h"
#include "ItemSaveState.h"
#include "Effect.h"
#include "EffectManager.h"
#include "SoundBank.h"
#include "Layout.h"
#undef protected
#undef private
#include "NativeTriggerLevelFixture.h"
#include "tests/NativeMenuClient.h"
#include "tests/NativeEditorControls.h"
#include "tests/CharacterEmptyGlobals.h"
#include "tests/SmallMassCompare.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(void,tvFillOld,(CTriggerUnit*,CItemSaveState&,int,bool),"_ZN12CTriggerUnit13fillSaveStateER14CItemSaveStateib")
TL_ORIGINAL(void,tvApplyOld,(CTriggerUnit*,CItemSaveState&),"_ZN12CTriggerUnit14applySaveStateER14CItemSaveState")
extern "C" void tvFillNew(CTriggerUnit*,CItemSaveState&,int,bool) __asm__("_ZN12CTriggerUnit13fillSaveStateER14CItemSaveStateib");
extern "C" void tvApplyNew(CTriggerUnit*,CItemSaveState&) __asm__("_ZN12CTriggerUnit14applySaveStateER14CItemSaveState");
namespace {
nativegame::Services*services;autotest::Capture*output;Ogre::Camera*camera;bool recording;
void n(unsigned x){output->add(&x,4);}void f(float x){output->add(&x,4);}
struct Trigger:CTriggerUnit{
 explicit Trigger(CResourceManager*r):CTriggerUnit(r){}
 virtual void updateAnimation(float elapsed){if(recording){n(1);f(elapsed);}if(m_unitModel)m_unitModel->updateAnimation(elapsed,true);}
 virtual void update(Ogre::Camera*c,const Ogre::Vector3&position,float elapsed){if(recording){n(2);n(c==camera);output->add(&position,sizeof position);f(elapsed);}}
 virtual void addToAvoidanceMap(CLevel&){}
};
CEffect*effect(unsigned index,unsigned group){CEffect*p=new CEffect(static_cast<EEFFECT_TYPE>(index%5),false,static_cast<EEFFECT_ACTIVATION>(group),-900.f,.125f*(1+index),.5f*(1+index),false);p->m_fValueC0=.375f*(1+index);p->m_sName=L"retained-effect";p->m_flag31=index%2;return p;}
void eff(CEffect*p,CTriggerUnit*u){n(p->m_eType);n(p->m_activation);f(p->m_fRemainingDuration);f(p->m_fValue24);f(p->m_fValueC0);n(p->m_Owner.getObject()==NULL);n(p->m_Owner.getObject()==u);n(p->m_pSkillOwner.getObject()==NULL);output->addText(p->m_sName);}
void state(CTriggerUnit&u,CItemSaveState&s){
 n(u.m_state);n(u.m_pendingStateEvent);n(u.m_flag25C);n(u.m_bItemFlag1F0);n(u.m_bInActiveRange);n(u.m_bItemFlag218);n(u.m_bEnabled);n(u.m_bVisible);n(u.m_bBlocksPath);output->add(&u.m_vPosition,sizeof u.m_vPosition);
 n(s.m_iStackSize);output->add(&s.m_iOriginalGuid,8);output->add(&s.m_iStateValue38,8);output->add(&s.m_iParentHierarchyHash,8);n(s.m_iRoomIndex);n(s.m_iIndex);n(s.m_bSaveFlag5C);n(s.m_bEnabled);n(s.m_bBlocksPath);n(s.m_bItemFlag17C);output->addText(s.m_sItemName);output->add(&s.m_vLocalPosition,sizeof s.m_vLocalPosition);output->add(&s.m_vWorldPosition,sizeof s.m_vWorldPosition);output->add(&s.m_mOrientation,sizeof s.m_mOrientation);
 for(unsigned g=0;g<3;++g){n(s.m_Effects[g].size());for(unsigned i=0;i<s.m_Effects[g].size();++i)eff(s.m_Effects[g][i],&u);}
 n(u.m_pEffectManager!=NULL);if(u.m_pEffectManager)for(unsigned g=0;g<3;++g){TArrayList<CEffect*>&effects=u.m_pEffectManager->getActiveEffects(g);n(effects.size());for(unsigned i=0;i<effects.size();++i)eff(effects[i],&u);}if(u.m_pEffectManager)for(unsigned i=0;i<145;++i)f(u.m_pEffectManager->m_EffectValues[i]);
 if(u.m_unitModel){n(u.m_unitModel->m_animationPlaying);n(u.m_unitModel->m_activeAnimations.size());for(unsigned i=0;i<u.m_unitModel->m_animationStates.size();++i){Ogre::AnimationState*a=u.m_unitModel->m_animationStates[i];f(a->getTimePosition());f(a->getWeight());n(a->getEnabled());}}
}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;recording=false;unsigned seed=c.index;nativetrigger::LevelFixture fixture(*services);fixture.resources.m_pSceneManager=services->scene;fixture.resources.m_pLevel=&fixture.level;fixture.level.m_automapRoomPieces=false;
 Ogre::AnimationStateSet states;CAnimationSet animations;const char*names[]={"IDLE","OPEN","CLOSE","TRANSITION"};for(unsigned i=0;i<4;++i){animations.m_lUnknown28.push_back(names[i]);animations.m_lUnknown40.push_back(L"trigger-save-fixture");animations.m_lAnimationGroups.push_back(std::vector<CKeyframe*>());states.createAnimationState(names[i],0,1.f+i*.5f,1,false);}
 CLayout owner(&fixture.resources,static_cast<ELAYOUT_TYPES>(0));owner.setOriginalGuid(0x123456789LL+seed);
 Trigger u(&fixture.resources);u.sceneNodeSetParent(services->scene->getRootSceneNode(),false);u.m_pSoundBank=new CSoundBank(*services->master->m_pSoundManager,false);u.m_state=int(seed%6)-1;u.m_minState=seed/7%2;u.m_maxState=2+seed/11%2;u.m_cycleMode=seed/13%3;u.m_pendingStateEvent=seed/3%2;u.m_bItemFlag1F0=seed/5%2;u.m_bItemFlag218=seed/17%2;u.m_flag25C=seed/19%2;u.m_bVisible=seed/23%2;u.m_iRoomIndex=seed%4;u.m_iOriginalGuid=0x765432100LL+seed;u.m_iParentHierarchyHashCode=0x22334455+seed;u.m_pSceneOwner=seed%3?&owner:NULL;u.m_sItemName=L"saved trigger";u.setPosition(float(seed%5),-.25f,float(seed%7));u.m_eUnitType=static_cast<UNITTYPES::EUNITTYPES>(seed/29%2?0xad:32);
 for(unsigned i=0;i<4;++i){u.m_animations.add(i);u.m_altAnimations.add(~0u);u.m_looping.add((seed+i)%2);}
 if(seed/5%3){u.m_unitModel=new CGenericModel(&fixture.resources,services->scene,L"",L"",false);u.m_unitModel->m_animationSet=&animations;for(unsigned i=0;i<4;++i)u.m_unitModel->m_animationStates.add(states.getAnimationState(names[i]));u.m_unitModel->m_animationPlaying=seed%3?seed%4:~0u;}
 CItemSaveState save;save.m_iStackSize=int(seed/3%7)-2;save.m_iIndex=-3;save.m_iRoomIndex=seed%4;save.m_iSpawnerGuid=0xffffffffLL;save.m_iQuestGuid=0x99887766+seed;save.m_iQuestState=seed%3;save.m_bEnabled=seed%2;save.m_bBlocksPath=seed/2%2;save.m_bSaveFlag5C=seed/3%2;save.m_bItemFlag17C=seed/5%2;save.m_sItemName=L"apply state";save.m_vLocalPosition=Ogre::Vector3(-2.f,.125f*seed,3);save.m_vWorldPosition=Ogre::Vector3(.5f,1.25f,-3.75f);save.m_mOrientation=Ogre::Matrix4::IDENTITY;
 if(seed%3){u.m_pEffectManager=new CEffectManager(&u);for(unsigned g=0;g<3;++g)for(unsigned i=0;i<(seed/7+g)%3;++i){CEffect*p=effect(seed+i,g);p->m_Owner.setObject(&u);u.m_pEffectManager->getActiveEffects(g).add(p);}}
 for(unsigned g=0;g<3;++g)for(unsigned i=0;i<(seed/11+g)%3;++i)save.m_Effects[g].push_back(effect(seed+5+i,g));
 recording=true;if(c.op==0){void(*fn)(CTriggerUnit*,CItemSaveState&,int,bool)=ours?tvFillNew:tvFillOld;if(autotest::beginInvocation(out,fn)){fn(&u,save,int(seed%9)-4,bool(seed/13%2));out.callCompleted=1;}}else{void(*fn)(CTriggerUnit*,CItemSaveState&)=ours?tvApplyNew:tvApplyOld;if(autotest::beginInvocation(out,fn)){fn(&u,save);out.callCompleted=1;}}recording=false;state(u,save);if(u.m_unitModel)u.m_unitModel->m_animationSet=NULL;u.m_pSceneOwner=NULL;
}
int worker(const tlhybrid_host*host){
 initEmptyGlobals();void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x148c4e8),8);if(!p)new(reinterpret_cast<void*>(0x148c4e8))std::wstring;
 nativegame::Services native;services=&native;if(!native.ready())return 1;menugui::Audio audio(native.master);nativeeditor::Controls editor(native);
 {menugui::ProjectionDuringConstruction projection;camera=new Ogre::Camera("trigger-save-camera",native.scene);}CCameraControl cameras(camera,camera,camera,camera,camera);
 const char*names[]={"trigger_fill_save_native","trigger_apply_save_native"};const unsigned addresses[]={0x9073b0,0x8fc8e0};for(unsigned i=0;i<2;++i)if(smallmass::run(host,i,names[i],addresses[i],&side,192))return 1;delete camera;return 0;
}
}
TL_TEST(complete_trigger_save){return systems_fixture::isolated(&worker,host);}
