#include "SmallMassCompare.h"
#include <deque>
#include <vector>
#define private public
#define protected public
#include "GenericModel.h"
#undef protected
#undef private
#include "ResourceManager.h"
#include "MasterResourceManager.h"
#include "AnimationSet.h"
#include "DataGroup.h"
#include "Keyframe.h"
TL_ORIGINAL(void,lifeCtorOld,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE")
extern "C" void lifeCtorNew(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES) __asm__("_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE");
TL_ORIGINAL(void,lifeDtorOld,(CGenericModel*),"_ZN13CGenericModelD1Ev")
extern "C" void lifeDtorNew(CGenericModel*) __asm__("_ZN13CGenericModelD1Ev");
TL_ORIGINAL(void,lifeKeyOld,(CGenericModel*,unsigned,CDataGroup*),"_ZN13CGenericModel6AddKeyEjP10CDataGroup")
extern "C" void lifeKeyNew(CGenericModel*,unsigned,CDataGroup*) __asm__("_ZN13CGenericModel6AddKeyEjP10CDataGroup");
TL_FUNCTION(lifeMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(lifePrefab,"_ZN13CGenericModel14loadPrefabTypeEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_FUNCTION(lifeUnload,"_ZN13CGenericModel11unloadModelEv")
TL_FUNCTION(lifeUnique,"_ZN13CGenericModel22releaseUniqueMaterialsEv")
namespace finish_life {
using namespace smallmass;
unsigned calls;CGenericModel* object;
CMasterResourceManager* master(){return 0;}
void prefab(CGenericModel* self,OGRE_UTILITIES::EPRIMITIVES primitive){number(1001);number(self==object);number(primitive);number(self->m_animationStates.size());number(self->m_activeAnimations.size());number(self->m_queryMask);number(self->m_bEnabled);++calls;}
void unload(CGenericModel* self){number(1002);number(self==object);number(self->m_animationStates.size());number(self->m_activeAnimations.size());self->m_animationSet=0;self->m_pEntity=0;self->m_entity230=0;++calls;}
void unique(CGenericModel* self){number(1003);number(self==object);number(self->m_activeAnimations.size());number(self->m_renderableStates.size());++calls;}
void snapshot(CGenericModel* self){text(self->m_sModelPath);text(self->m_modelGroup);text(self->m_name);text(self->m_string128);number(self->m_pSkeleton!=0);number(self->m_animationStates.size());number(self->m_activeAnimations.size());number(self->m_AnimationEvents.size());number(self->m_valueIndexes.size());number(self->m_animationSet!=0);number(self->m_animationPaused);number(self->m_flag1e9);number(self->m_queryMask);number(self->m_renderableStates.size());number(self->m_randomWeight);number(self->m_uniqueMaterials);floating(self->m_opacity);number(self->m_entity230!=0);number(self->m_flag238);number(self->m_renderToLightMap);number(self->m_renderFlag23A);number(self->m_gap23B);number(self->m_animationLoop);floating(self->m_animationSpeed);number(self->m_animationPlaying);floating(self->m_animationStep);number(self->m_bEnabled);}
void side(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;calls=0;
 detour::Set patch;TL_REDIRECT(patch,lifeMaster,&master);TL_REDIRECT(patch,lifePrefab,&prefab);TL_REDIRECT(patch,lifeUnload,&unload);TL_REDIRECT(patch,lifeUnique,&unique);if(patch.failed())_exit(42);
 CResourceManager resources(0);
 CGenericModel* self=static_cast<CGenericModel*>(autotest::allocate(sizeof(CGenericModel)));object=self;
 int before=g_iTotalCountOfObjects;

 lifeCtorOld(self,0,0,OGRE_UTILITIES::PRIMITIVE_SPHERE);
 CAnimationSet* set=new CAnimationSet;self->m_animationSet=set;
 CDataGroup group(L"KEYFRAME",0,2,2,0);group.SetDataValue(L"FRAME",int(c.index));group.SetDataValue(L"TYPE",L"SOUND",false);
 if(c.op==2){unsigned count=c.index%7;set->m_lAnimationGroups.resize(count);for(unsigned i=0;i<count;++i)for(unsigned j=0;j<i%3;++j)set->m_lAnimationGroups[i].push_back(new CKeyframe(i,&group));if(c.index%9==0)self->m_animationSet=0;void(*fn)(CGenericModel*,unsigned,CDataGroup*)=ours?lifeKeyNew:lifeKeyOld;autotest::beginInvocation(out,fn);fn(self,c.index%8,&group);out.callCompleted=1;number(set->m_lAnimationGroups.size());for(unsigned i=0;i<set->m_lAnimationGroups.size();++i){number(set->m_lAnimationGroups[i].size());for(unsigned j=0;j<set->m_lAnimationGroups[i].size();++j){number(set->m_lAnimationGroups[i][j]->getAnimationIndex());number(set->m_lAnimationGroups[i][j]->getEventCode());}}self->m_animationSet=0;lifeDtorOld(self);delete set;return;}
 TSafePointer<CGenericModel> watched;watched.setObject(self);TSafePointer<CActiveAnimation> active[140];
 for(unsigned i=0;i<c.index%137;++i){CActiveAnimation* a=new CActiveAnimation;a->m_animation=i%6;a->m_queued=i&1;a->m_playing=!(i&1);a->m_time=i;self->m_activeAnimations.push_back(a);active[i].setObject(a);}
 self->m_renderableStates.resize(c.index%5);self->m_valueIndexes.resize(c.index%4);for(unsigned i=0;i<self->m_valueIndexes.size();++i){self->m_valueIndexes[i].resize(i+1);for(unsigned j=0;j<i+1;++j)for(unsigned k=0;k<c.index%4;++k)self->m_valueIndexes[i][j].add(k);}
 self->m_animationStates.add(0);self->m_animationStates.add(0);
 void(*fn)(CGenericModel*)=ours?lifeDtorNew:lifeDtorOld;autotest::beginInvocation(out,fn);fn(self);out.callCompleted=1;number(calls);number(watched.getObject()==0);for(unsigned i=0;i<c.index%137;++i)number(active[i].getObject()==0);delete set;
}
}
TL_TEST(finish_model_destructor_lifetime){return smallmass::run(host,1,"finish_model_destructor_lifetime",0x8a5e00,&finish_life::side,144);}
TL_TEST(finish_model_add_key){return smallmass::run(host,2,"finish_model_add_key",0x8a1600,&finish_life::side,144);}
