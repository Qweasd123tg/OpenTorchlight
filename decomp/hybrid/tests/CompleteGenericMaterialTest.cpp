#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#define private public
#define protected public
#include "GenericModel.h"
#undef protected
#undef private
#include "SettingsVariables.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include <OgrePass.h>
#include <OgreTextureUnitState.h>
TL_ORIGINAL(void,gmOldLight,(CGenericModel*,float),"_ZN13CGenericModel16setLightOverrideEf")
TL_ORIGINAL(void,gmOldOpacity,(CGenericModel*,float),"_ZN13CGenericModel10setOpacityEf")
TL_ORIGINAL(void,gmCtor,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_ORIGINAL(void,gmDtor,(CGenericModel*),"_ZN13CGenericModelD1Ev")
extern "C" void gmNewLight(CGenericModel*,float) __asm__("_ZN13CGenericModel16setLightOverrideEf");
extern "C" void gmNewOpacity(CGenericModel*,float) __asm__("_ZN13CGenericModel10setOpacityEf");
extern "C" char gmBest[] __asm__("_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE");
namespace {
nativegame::Services*services;std::vector<Ogre::MaterialPtr>*known;
struct Case {unsigned op,seed;};
void integer(autotest::Capture&o,unsigned n){o.add(&n,4);}void scalar(autotest::Capture&o,float n){o.add(&n,4);}void colour(autotest::Capture&o,const Ogre::ColourValue&c){scalar(o,c.r);scalar(o,c.g);scalar(o,c.b);scalar(o,c.a);}
Ogre::Technique*best(Ogre::Material*p,unsigned short lod,const Ogre::Renderable*r){if(lod||r)std::abort();for(unsigned i=0;i<known->size();++i)if((*known)[i].getPointer()==p)return p->getTechnique(0);std::abort();return NULL;}
void blend(autotest::Capture&o,const Ogre::LayerBlendModeEx&b){integer(o,b.blendType);integer(o,b.operation);integer(o,b.source1);integer(o,b.source2);if(b.blendType==Ogre::LBT_COLOUR){colour(o,b.colourArg1);colour(o,b.colourArg2);}else{scalar(o,b.alphaArg1);scalar(o,b.alphaArg2);}scalar(o,b.factor);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);unsigned seed=c.seed;
 services->settings->SetInt(KSETTINGS_NETBOOK_MODE,seed%3);
 CGenericModel*model=static_cast<CGenericModel*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGenericModel),0,0,0));gmCtor(model,NULL,services->scene,OGRE_UTILITIES::PRIMITIVE_SPHERE);
 std::vector<Ogre::MaterialPtr>materials;known=&materials;unsigned count=(seed/3)%5;
 for(unsigned i=0;i<count;++i){CRenderableStates state=CRenderableStates();state.m_state0=17+i;state.m_opacity=-7.f;state.spectral=((seed/15+i)&1)!=0;state.m_gap2e=((seed/30+i)&1)!=0;
  for(unsigned k=0;k<3;++k){std::string name="generic-material-"+Ogre::StringConverter::toString(i*3+k);Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().create(name,"General");materials.push_back(material);Ogre::Technique*tech=material->getTechnique(0);
   unsigned passes=c.op==0?1:((seed/60+i)%4);if(!passes)tech->removeAllPasses();else for(unsigned j=1;j<passes;++j)tech->createPass();
   for(unsigned j=0;j<passes;++j){Ogre::Pass*pass=tech->getPass(j);pass->setAmbient(.11f+i,.22f+k,.33f+j);pass->setDiffuse(Ogre::ColourValue(.27f+i,.37f+k,.47f+j,.57f));pass->setSelfIllumination(Ogre::ColourValue(.13f+i,.23f+k,.43f+j,.63f));unsigned units=c.op==0?0:((seed/240+i+j)%3);for(unsigned u=0;u<units;++u)pass->createTextureUnitState();}
   if(k==0)state.originalMaterial=material.getPointer();else if(k==1)state.material=material.getPointer();else state.material20=(seed/15+i)%3?material.getPointer():NULL;
  }model->m_renderableStates.push_back(state);
 }
 model->m_gap23B=(seed/120)%2;float values[]={-2.f,0.f,.1f,.25f,.5f,1.f,1.5f,2.f};float value=values[(seed/5)%8];if((seed/40)%5==4){unsigned bits=0x7fc00001;std::memcpy(&value,&bits,4);}model->m_opacity=(seed/2)%7==0?value:.625f;
 detour::Set hooks;hooks.redirect(gmBest,gmBest,&best);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 void(*fn)(CGenericModel*,float)=c.op?(ours?gmNewOpacity:gmOldOpacity):(ours?gmNewLight:gmOldLight);if(autotest::beginInvocation(out,fn)){fn(model,value);out.callCompleted=1;}
 scalar(out,model->m_opacity);integer(out,model->m_renderableStates.size());for(unsigned i=0;i<count;++i){CRenderableStates&s=model->m_renderableStates[i];integer(out,s.m_state0);scalar(out,s.m_opacity);}
 for(unsigned i=0;i<materials.size();++i){Ogre::Technique*tech=materials[i]->getTechnique(0);integer(out,tech->getNumPasses());for(unsigned j=0;j<tech->getNumPasses();++j){Ogre::Pass*p=tech->getPass(j);colour(out,p->getAmbient());colour(out,p->getDiffuse());colour(out,p->getSelfIllumination());integer(out,p->hasSeparateSceneBlending());integer(out,p->getSourceBlendFactor());integer(out,p->getDestBlendFactor());integer(out,p->getSourceBlendFactorAlpha());integer(out,p->getDestBlendFactorAlpha());integer(out,p->getAlphaRejectFunction());integer(out,p->getAlphaRejectValue());integer(out,p->getNumTextureUnitStates());for(unsigned u=0;u<p->getNumTextureUnitStates();++u){blend(out,p->getTextureUnitState(u)->getColourBlendMode());blend(out,p->getTextureUnitState(u)->getAlphaBlendMode());}}}
 hooks.restore();gmDtor(model);Ogre::NedAllocImpl::deallocBytes(model);for(unsigned i=0;i<materials.size();++i)Ogre::MaterialManager::getSingleton().remove(materials[i]->getHandle());
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services native;services=&native;if(!native.ready())return 1;const char*names[]={"generic_light_override","generic_opacity"};int failures=0;for(unsigned op=0;op<2;++op){autotest::Coverage coverage(names[op],reinterpret_cast<uintptr_t>(op?gmOldOpacity:gmOldLight));for(unsigned i=0;i<960;++i){Case c={op,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)&&i<12)host->log("    material op%u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",op,i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);}coverage.report(host);failures+=coverage.completed!=960||coverage.missing;
#ifdef GM_EXPECT_DIFFERENCES
 failures+=coverage.different==0;
#else
 failures+=coverage.different!=0;
#endif
 }return failures;}
}
TL_TEST(complete_generic_material){return systems_fixture::isolated(&worker,host);}
