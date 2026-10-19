#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#define private public
#define protected public
#include "MasterResourceManager.h"
#include "TriggerUnit.h"
#include "Level.h"
#include "GenericModel.h"
#include "AnimationSet.h"
#include "Layout.h"
#include "CollisionModel.h"
#include "CollisionModelRef.h"
#include "CollisionList.h"
#include "CullingBounds.h"
#include "Timeline.h"
#include "StringUtilities.h"
#include "SoundBank.h"
#include "SoundBankDataInformation.h"
#include "UnitTriggerDescriptorNames.h"
#include "LevelTemplateData.h"
#undef protected
#undef private
#include "NativeTriggerLevelFixture.h"
#include "tests/NativeMenuClient.h"
#include "tests/NativeEditorControls.h"
#include "tests/MenuModelGpuBoundary.h"
#include "tests/CharacterEmptyGlobals.h"
#include "tests/SmallMassCompare.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(void,tjInitOld,(CTriggerUnit*,CDataGroup*,bool),"_ZN12CTriggerUnit8unitInitEP10CDataGroupb")
extern "C" void tjInitNew(CTriggerUnit*,CDataGroup*,bool) __asm__("_ZN12CTriggerUnit8unitInitEP10CDataGroupb");
TL_FUNCTION(tjItemInit,"_ZN5CItem8unitInitEP10CDataGroupb")
TL_FUNCTION(tjCreate,"_ZN16CResourceManager18createGenericModelEPN4Ogre12SceneManagerEPKwS4_bbb")
TL_FUNCTION(tjCollision,"_ZN22CMasterResourceManager17addCollisionModelESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(tjLoad,"_ZN7CLayout14loadLayoutFileERKSbIwSt11char_traitsIwESaIwEEbP13CTimerStaticsbbj")
TL_FUNCTION(tjQuery,"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(tjSounds,"_ZN12CTriggerUnit16addSoundsToStateE15ETRIGGER_STATESPKw")
TL_FUNCTION(tjRim,"_ZN13CGenericModel14setRimLightingESbIwSt11char_traitsIwESaIwEE")
namespace {
nativegame::Services*services;autotest::Capture*output;CTriggerUnit*unit;CDataGroup*data;unsigned seed;bool recording;Ogre::MeshPtr mesh;Ogre::AnimationStateSet*states;CAnimationSet*animations;TArrayList<CEditorBaseObject*>*timelines;
void n(unsigned x){output->add(&x,4);}void f(float x){output->add(&x,4);}void text(const std::wstring&s){output->addText(s);}
void item(CItem*p,CDataGroup*d,bool init){n(1);n(p==unit);n(d==data);n(init);p->m_pDataGroup=d;p->m_bBlocksPath=seed/3%2;p->m_bLevelLighting=seed/5%2;}
struct Model:CGenericModel{explicit Model(CResourceManager*r):CGenericModel(r,services->scene,L"",L"",false){}virtual ~Model(){m_animationSet=NULL;}};
CGenericModel*create(CResourceManager*r,Ogre::SceneManager*s,const wchar_t*file,const wchar_t*material,bool a,bool b,bool c){
 n(2);n(r==unit->m_pResourceManager);n(s==services->scene);text(file);text(material);n(a);n(b);n(c);if(seed/7%4==1)return NULL;
 Model*m=new Model(r);Ogre::Entity*entity=services->scene->createEntity("trigger-init-entity",mesh->getName());m->sceneNodeAttachEntity(entity);if(seed/11%3){m->m_animationSet=animations;for(unsigned i=0;i<3;++i)m->m_animationStates.add(states->getAnimationState(i==0?"IDLE":i==1?"OPEN":"CLOSE"));m->m_animationPlaying=seed/13%5;m->m_animationSpeed=.5f+seed%3*.25f;}return m;
}
CCollisionModel*collision(CMasterResourceManager*p,std::wstring file){n(3);n(p==services->master);text(file);CCollisionModel*model=new CCollisionModel(services->scene,L"");model->m_pCollisionList=new CCollisionList;model->m_pCollisionList->m_vBoundsMax=Ogre::Vector3(-1.f-seed%3,-.5f,-2.f);model->m_pCollisionList->m_vBoundsMin=Ogre::Vector3(1.5f,2.f,2.5f+seed%3);CollisionModelRef*ref=new CollisionModelRef;ref->m_pCollisionModel=model;ref->m_referenceCount=1;ref->m_sUnknown20=file;p->m_collisionModels.push_back(ref);return model;}
void load(CLayout*p,const std::wstring&file,bool a,CTimerStatics*t,bool b,bool c,unsigned value){n(4);n(p->m_Unknown1B8);text(file);n(a);n(t==NULL);n(b);n(c);n(value);}
TArrayList<CEditorBaseObject*>*query(CEditorScene*p,const std::wstring&name){n(5);text(name);CLayout*l=dynamic_cast<CLayout*>(p);n(l!=NULL);n(l?l->m_Unknown1B8:99);return seed/17%3==0?NULL:timelines;}
void sounds(CTriggerUnit*p,ETRIGGER_STATES state,const wchar_t*key){n(7);n(p==unit);n(state);text(key);n(p->m_pSoundBank!=NULL);}
void rim(CGenericModel*p,std::wstring file){n(6);n(p==unit->m_unitModel);text(file);}
void snapshot(CTriggerUnit&u){n(u.m_unitModel!=NULL);n(u.m_unitCollisionModel!=NULL);n(u.m_pSoundBank!=NULL);n(u.m_state);n(u.m_minState);n(u.m_maxState);n(u.m_cycleMode);n(u.m_flag25C);n(u.m_pendingStateEvent);n(u.m_bBlocksPath);n(u.m_bPathingFlag19C);n(u.m_bVisible);f(u.m_fBaseUnitValue194);text(u.m_modelName);text(u.m_requiredItem);n(u.m_value2F0);n(u.m_flag2F4);text(u.m_treasureClass);n(u.m_minTreasure);n(u.m_maxTreasure);output->add(&u.m_pCullingBounds->m_vMinimum,sizeof(Ogre::Vector3));output->add(&u.m_pCullingBounds->m_vMaximum,sizeof(Ogre::Vector3));output->add(&u.m_pCullingBounds->m_vLocalMinimum,sizeof(Ogre::Vector3));output->add(&u.m_pCullingBounds->m_vLocalMaximum,sizeof(Ogre::Vector3));for(unsigned g=0;g<3;++g){n(g==0?u.m_animations.size():g==1?u.m_altAnimations.size():u.m_looping.size());for(unsigned i=0;i<(g==0?u.m_animations.size():g==1?u.m_altAnimations.size():u.m_looping.size());++i)n(g==0?u.m_animations[i]:g==1?u.m_altAnimations[i]:u.m_looping[i]);}n(u.m_stateLayouts.size());for(unsigned i=0;i<u.m_stateLayouts.size();++i){CLayout*l=u.m_stateLayouts[i];n(l!=NULL);if(l){n(l->m_Unknown1B8);n(l->m_bVisible);n(l->m_bEnabled);n(l->m_bUnknown1C8);}}n(u.m_layout!=NULL);n(u.m_layout2C8!=NULL);if(u.m_unitModel){n(u.m_unitModel->m_animationPlaying);n(u.m_unitModel->m_activeAnimations.size());n(u.m_unitModel->getEntity()!=NULL);if(u.m_unitModel->getEntity()){const Ogre::AxisAlignedBox&box=u.m_unitModel->getEntity()->getMesh()->getBounds();output->add(&box.getMinimum(),sizeof(Ogre::Vector3));output->add(&box.getMaximum(),sizeof(Ogre::Vector3));n(u.m_unitModel->getEntity()->getQueryFlags());n(u.m_unitModel->getEntity()->getRenderQueueGroup());}}}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;recording=false;nativetrigger::LevelFixture fixture(*services);fixture.level.m_automapRoomPieces=seed/3%2;CTriggerUnit u(&fixture.resources);unit=&u;u.sceneNodeSetParent(services->scene->getRootSceneNode(),false);u.m_cycleMode=seed%3;if(seed/2%3==1)u.m_unitModel=new Model(&fixture.resources);u.m_modelName=L"previous";u.m_looping.add(seed%2);u.m_animations.add(2);u.m_altAnimations.add(1);u.m_stateLayouts.add(new CLayout(&fixture.resources,static_cast<ELAYOUT_TYPES>(1)));if(seed/2%2)u.m_layout=new CLayout(&fixture.resources,static_cast<ELAYOUT_TYPES>(0));if(seed/5%2)u.m_pSoundBank=new CSoundBank(*services->master->m_pSoundManager,false);
 Ogre::AnimationStateSet actualStates;CAnimationSet actualAnimations;states=&actualStates;animations=&actualAnimations;const char*names[]={"IDLE","OPEN","CLOSE"};for(unsigned i=0;i<3;++i){actualAnimations.m_lUnknown28.push_back(names[i]);actualAnimations.m_lUnknown40.push_back(L"fixture");actualAnimations.m_lAnimationGroups.push_back(std::vector<CKeyframe*>());actualStates.createAnimationState(names[i],0,1.f+i*.25f,1,false);}TArrayList<CEditorBaseObject*>timelineObjects;CTimeline timeline;if(seed/19%2)timelineObjects.add(&timeline);timelines=&timelineObjects;
 CDataGroup d(L"trigger",NULL,10,10,NULL);data=&d;d.SetDataValue(L"MAXSTATES",seed/37%4==0&&seed/3%3==0?0:int(1+seed%4));d.SetDataValue(L"RESOURCEDIRECTORY",seed/2%2?L"media\\props/":L"media/\x0434\x0432\x0435\x0440\x044c",false);d.SetDataValue(L"MESHFILE",seed/3%3?L"door":L"",false);d.SetDataValue(L"LAYOUTFILE",seed/5%3?L"layout":L"",false);d.SetDataValue(L"COLLISIONFILE",seed/7%3?L"collider":L"",false);const wchar_t*loops[]={L"No Loop",L"Cycle",L"bAcK aNd FoRtH",L"unknown",L""};d.SetDataValue(L"LOOPTYPE",loops[seed%5],false);d.SetDataValue(L"COLLISION_RADIUS",.125f*(1+seed%5));d.SetDataValue(L"ALLOW_HWSKINNING",bool(seed/11%2));d.SetDataValue(L"REQUIRED_UNIT",seed/13%2?L"KEY":L"",false);d.SetDataValue(L"REQUIRED_UNIT_COUNT",int(seed%7)-1);d.SetDataValue(L"TAKE_REQUIRED_UNIT",bool(seed/17%2));d.SetDataValue(L"NAME",L"fixture door",false);for(unsigned i=1;i<=4;++i){std::wstring suffix=STRINGS::GetValueAsWString(i);if((seed+i)%3==0)d.SetDataValue(L"LAYOUT_STATE_"+suffix,L"state"+suffix+L".layout",false);d.SetDataValue(L"ANIMATION_STATE_"+suffix,i%2?L"OPEN":L"CLOSE",false);}
 if(seed/19%2){CDataGroup*b=d.GetDataGroupByName(L"BOUNDS",true);b->SetDataValue(L"MINX",-2.f);b->SetDataValue(L"MAXX",1.25f);b->SetDataValue(L"MINY",-.5f);b->SetDataValue(L"MAXY",4.f);b->SetDataValue(L"MINZ",-1.5f);b->SetDataValue(L"MAXZ",3.f);}if(seed/23%2){CDataGroup*t=d.GetDataGroupByName(L"TREASURE",true);t->SetDataValue(L"SPAWNCLASS",L"GOLD",false);t->SetDataValue(L"MINCOUNT",int(seed%3));t->SetDataValue(L"MAXCOUNT",int(seed%5)+3);}d.SetDataValue(L"SPAWNLAYOUT",seed/29%2?L"spawn.layout":L"",false);
 CSoundBankDataInformation info(NULL);CSoundBankDataInformation*previous=services->master->m_pSoundBankDataInformation;services->master->m_pSoundBankDataInformation=&info;mesh->_setBounds(Ogre::AxisAlignedBox(-1,0,-2,1.5,2,2.5),false);detour::Set hooks;TL_REDIRECT(hooks,tjItemInit,&item);TL_REDIRECT(hooks,tjCreate,&create);TL_REDIRECT(hooks,tjCollision,&collision);TL_REDIRECT(hooks,tjLoad,&load);TL_REDIRECT(hooks,tjQuery,&query);TL_REDIRECT(hooks,tjRim,&rim);TL_REDIRECT(hooks,tjSounds,&sounds);if(hooks.failed())std::abort();autotest::invoke(out,ours?tjInitNew:tjInitOld,&u,seed%31==0?static_cast<CDataGroup*>(NULL):&d,bool(seed/7%2));hooks.restore();snapshot(u);services->master->m_pSoundBankDataInformation=previous;
}
int worker(const tlhybrid_host*host){
 initEmptyGlobals();void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x148c4e8),8);if(!p)new(reinterpret_cast<void*>(0x148c4e8))std::wstring;const wchar_t*loopNames[]={L"No Loop",L"Cycle",L"Back and Forth"};for(unsigned i=0;i<3;++i){void*at=reinterpret_cast<void*>(0x148d400+i*8);std::memcpy(&p,at,8);if(!p)new(at)std::wstring(loopNames[i]);}
 nativegame::Services native;services=&native;if(!native.ready())return 1;menugui::Audio audio(native.master);nativeeditor::Controls editor(native);menugui::ModelGpuBoundary gpu;
 Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().create("trigger-init-material","General");material->removeAllTechniques();Ogre::ManualObject*object=native.scene->createManualObject("trigger-init-manual");object->begin(material->getName(),Ogre::RenderOperation::OT_TRIANGLE_LIST);object->position(-1,0,-2);object->position(1.5,2,2.5);object->position(0,1,0);object->triangle(0,1,2);object->end();mesh=object->convertToMesh("trigger-init-mesh","General");native.scene->destroyManualObject(object);int failures=smallmass::run(host,0,"trigger_unit_init_native",0x90b0d0,&side,768);mesh.setNull();return failures;
}
}
TL_TEST(complete_trigger_init){return systems_fixture::isolated(&worker,host);}
