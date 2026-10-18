#include "SmallMassCompare.h"
#include <vector>
#include <deque>
#include <OgreRoot.h>
#include <OgreLogManager.h>
#include <OgreMaterial.h>
#include <OgreTechnique.h>
#include <OgrePass.h>
#include <OgreTextureUnitState.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreAnimationState.h>
#define private public
#define protected public
#include "GenericModel.h"
#undef protected
#undef private
#include "AnimationSet.h"
#include "ResourceManager.h"
#include "MasterResourceManager.h"
TL_ORIGINAL(void,renderModelCtor,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_ORIGINAL(void,renderModelDtor,(CGenericModel*),"_ZN13CGenericModelD1Ev")
extern "C" void renderEntityCtor(Ogre::Entity*) __asm__("_ZN4Ogre6EntityC1Ev");
TL_FUNCTION(renderMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(renderRemove,"_ZN22CMasterResourceManager18removeAnimationSetEP13CAnimationSet")
#define SDK_FUNCTION(N,S) extern "C" char N##_original[] __asm__(S); extern "C" char N##_linked[] __asm__(S);
SDK_FUNCTION(renderBest,"_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE")
SDK_FUNCTION(renderSetTexture,"_ZN4Ogre16TextureUnitState14_setTexturePtrERKNS_10TexturePtrE")
#define RENDER_FN(N,R,A,S) TL_ORIGINAL(R,N##Old,A,S) extern "C" R N##New A __asm__(S);
RENDER_FN(renderQuery,void,(CGenericModel*,OGRE_UTILITIES::EQUERYMASK),"_ZN13CGenericModel12setQueryMaskEN14OGRE_UTILITIES10EQUERYMASKE")
RENDER_FN(renderShadows,void,(CGenericModel*,bool),"_ZN13CGenericModel15setCastsShadowsEb")
RENDER_FN(renderName,std::string,(CGenericModel*),"_ZN13CGenericModel13getTexureNameEv")
RENDER_FN(renderTexture,void,(CGenericModel*,Ogre::TexturePtr,std::string,std::string),"_ZN13CGenericModel18setTextureOverrideEN4Ogre10TexturePtrESsSs")
RENDER_FN(renderSingle,void,(CGenericModel*,std::string,Ogre::TexturePtr),"_ZN13CGenericModel24setTextureOverrideSingleESsN4Ogre10TexturePtrE")
RENDER_FN(renderUnload,void,(CGenericModel*),"_ZN13CGenericModel11unloadModelEv")
RENDER_FN(renderLight,void,(CGenericModel*,bool),"_ZN13CGenericModel19setRenderToLightMapEb")
namespace finish_render {
using namespace smallmass;
unsigned setCalls,removed;CAnimationSet* animation;Ogre::Material* materials[8];
CMasterResourceManager* master(){return 0;}
void remove(CMasterResourceManager*,CAnimationSet* p){number(901);number(p==animation);++removed;}
Ogre::Technique* best(Ogre::Material* p,unsigned short level,const Ogre::Renderable* r){number(902);number(level);number(r!=0);for(unsigned i=0;i<8;++i)if(materials[i]==p){number(i);if(input->op==2&&input->index%11==i)return 0;return p->getTechnique(0);} _exit(49);}
void setTexture(Ogre::TextureUnitState* p,const Ogre::TexturePtr& texture){number(903);number(texture.isNull());unsigned id=255;for(unsigned i=0;i<8;++i){Ogre::Pass* pass=materials[i]->getTechnique(0)->getPass(0);for(unsigned j=0;j<pass->getNumTextureUnitStates();++j)if(pass->getTextureUnitState(j)==p)id=i*10+j;}number(id);++setCalls;}
void ensure(){if(!Ogre::LogManager::getSingletonPtr()){Ogre::LogManager* logs=new Ogre::LogManager;logs->createLog("/tmp/otl-finish-model-render.log",true,false,true);}if(!Ogre::Root::getSingletonPtr()){void* storage=std::calloc(1,0x10000);if(!storage)std::abort();new(storage) Ogre::Root("","","");}}
void side(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;setCalls=removed=0;
 detour::Set patch;TL_REDIRECT(patch,renderMaster,&master);TL_REDIRECT(patch,renderRemove,&remove);TL_REDIRECT(patch,renderBest,&best);TL_REDIRECT(patch,renderSetTexture,&setTexture);if(patch.failed())_exit(42);

 CGenericModel* self=static_cast<CGenericModel*>(autotest::allocate(sizeof(CGenericModel)));renderModelCtor(self,0,0,OGRE_UTILITIES::PRIMITIVE_BOX);
 for(unsigned i=0;i<8;++i){std::string n="material";n+=char('0'+i);materials[i]=new Ogre::Material(0,n,i,"General");materials[i]->removeAllTechniques();Ogre::Technique* t=materials[i]->createTechnique();Ogre::Pass* pass=t->createPass();for(unsigned j=0;j<(c.op==4?1:(i+c.index)%4);++j){Ogre::TextureUnitState* unit=pass->createTextureUnitState();unit->setTextureName(n);}}
 for(unsigned i=0;i<c.index%5;++i){CRenderableStates state=CRenderableStates();state.name=i%2?"body_tail":"Body_head";state.material=c.op==2&&(c.index&16)&&(i&1)?0:materials[i];state.material18=c.index&8?materials[i+4]:0;state.castsShadows=!(c.index&1);self->m_renderableStates.push_back(state);}
 bool b=c.index&1;
 switch(c.op){
 case 2:{std::string(*fn)(CGenericModel*)=ours?renderNameNew:renderNameOld;autotest::beginInvocation(out,fn);text(fn(self));break;}
 case 3:{void(*fn)(CGenericModel*,Ogre::TexturePtr,std::string,std::string)=ours?renderTextureNew:renderTextureOld;autotest::beginInvocation(out,fn);fn(self,Ogre::TexturePtr(),c.index&16?"HEAD":"",c.index&32?"TAIL":"");break;}
 case 4:{void(*fn)(CGenericModel*,std::string,Ogre::TexturePtr)=ours?renderSingleNew:renderSingleOld;autotest::beginInvocation(out,fn);fn(self,c.index&16?"Head":c.index&32?"BODY":"",Ogre::TexturePtr());break;}
 }
 out.callCompleted=1;
 number(setCalls);
 for(unsigned i=0;i<self->m_renderableStates.size();++i)number(self->m_renderableStates[i].castsShadows);
 renderModelDtor(self);for(unsigned i=0;i<8;++i)delete materials[i];
}
}
#define RENDER_TEST(N,O,A) TL_TEST(finish_render_##N){finish_render::ensure();return smallmass::run(host,O,"finish_render_" #N,A,&finish_render::side,96);}
RENDER_TEST(name,2,0x89a0f0)
RENDER_TEST(texture,3,0x8a2fc0)
RENDER_TEST(single,4,0x8a3430)
