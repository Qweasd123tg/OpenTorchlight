#include <Ogre.h>
#include "AutoTest.h"
#include "ParticleMaterialBoundary.h"
#include "tests/SystemsFixtureWorker.h"
#define private public
#define protected public
#include "ParticleTechWrapper.h"
#include "Level.h"
#include "MasterResourceManager.h"
#include "ParticlePreloader.h"
#include <ParticleUniverseTechnique.h>
#include <ParticleUniverseSystem.h>
#undef protected
#undef private
#include "tests/ParticleNativeOwners.h"

TL_ORIGINAL(void, techniqueCtorOriginal,(CParticleTechWrapper*,CResourceManager*),"_ZN20CParticleTechWrapperC1EP16CResourceManager")
TL_ORIGINAL(void, techniqueCtorDtor,(CParticleTechWrapper*),"_ZN20CParticleTechWrapperD1Ev")
extern "C" void techniqueCtorRecovered(CParticleTechWrapper*,CResourceManager*) __asm__("_ZN20CParticleTechWrapperC1EP16CResourceManager");
namespace {
using namespace particlegraphics;
union Storage{long double alignment;char bytes[sizeof(CParticleTechWrapper)];};
struct Case{unsigned seed;bool negative;};
ParticleNativeOwners owners;
void number(autotest::Capture&out,long long value){out.add(&value,sizeof(value));}
void real(autotest::Capture&out,float value){out.add(&value,sizeof(value));}
void side(void*raw,autotest::Capture&out,bool ours){
 const Case&c=*static_cast<Case*>(raw);Storage storage;

 std::memset(storage.bytes,c.seed&1?0x5a:0,sizeof(storage.bytes));
 CParticleTechWrapper*w=reinterpret_cast<CParticleTechWrapper*>(storage.bytes);
 particleNativeSetEditorMode(owners,true);
 CMasterResourceManager* master=CMasterResourceManager::getSingleton();
 if(!master->m_pParticlePreloader)master->m_pParticlePreloader=new CParticlePreloader(NULL);
 CLevel*level=new CLevel(L"technique ctor",master->m_pSettings,NULL,owners.resources,owners.scene,NULL,17,3);
 owners.resources->m_pLevel=level;
 particleNativeSetEditorMode(owners,(c.seed&2)==0);
 owners.camera->setPosition(float(c.seed)-4,2,-3);
 int before=g_iTotalCountOfObjects;
 typedef void(*Function)(CParticleTechWrapper*,CResourceManager*);
 Function function=ours?techniqueCtorRecovered:techniqueCtorOriginal;
 MaterialCompileBoundary graphics;
 if(!autotest::beginInvocation(out,function))return;

 function(w,owners.resources);out.callCompleted=1;

 if(ours&&c.negative)++w->m_iFlipbookWidth;
 number(out,compileCalls());
 number(out,g_iTotalCountOfObjects-before);number(out,w->m_pResourceManager==owners.resources);
 number(out,w->m_technique!=NULL);number(out,w->m_pParticleSystem!=NULL);
 number(out,w->m_renderType);number(out,w->m_renderQueue);number(out,w->m_billboardRotation);number(out,w->m_billboardOrigin);
 real(out,w->m_fRibbonLength);real(out,w->m_fRibbonWidth);number(out,w->m_iRibbonMaxChains);
 number(out,w->m_bRibbonEndFade);number(out,w->m_bRibbonLocalTrail);number(out,w->m_iFlipbookWidth);number(out,w->m_iFlipbookHeight);
 real(out,w->m_fUScroll);real(out,w->m_fVScroll);number(out,w->m_bSorts);
 number(out,w->m_pUnknown180==NULL);
 number(out,w->m_iUnknown188==0);number(out,w->m_iUnknown190==0);number(out,w->m_iUnknown198==0);
 number(out,w->m_ribbonRenderer==NULL);number(out,w->m_pUnknown1A8==NULL);
 out.addText(w->m_pTexturePath);out.addText(w->m_pModelPath);out.addText(w->m_pUnknown1C0);
 number(out,w->m_iParticleRenderStyle);number(out,w->m_bDepthCheck);number(out,w->m_bIsLight);number(out,w->m_bUnknown1CE);
 number(out,w->m_iSortIndex);real(out,w->m_fDepthBias);number(out,w->m_bUnknown208);
 out.add(reinterpret_cast<char*>(&w->m_Unknown1D8)+8,12);out.add(reinterpret_cast<char*>(&w->m_Unknown1F0)+8,12);
 number(out,w->m_bEnabled);number(out,w->m_bPlaying);number(out,w->getVisible());
 number(out,w->m_technique->getParentSystem()==w->m_pParticleSystem);
 out.add(&w->m_technique->position,sizeof(Ogre::Vector3));
 real(out,w->m_technique->getDefaultDepth());real(out,w->m_technique->getDefaultHeight());real(out,w->m_technique->getDefaultWidth());
 real(out,w->m_technique->getMaxVelocity());number(out,w->m_technique->getVisualParticleQuota());
 number(out,w->m_technique->isEnabled());number(out,w->m_technique->getNumEmitters());number(out,w->m_technique->getNumAffectors());
 number(out,w->m_pParticleSystem->getNumTechniques());number(out,w->m_pParticleSystem->getState());

 techniqueCtorDtor(w);number(out,g_iTotalCountOfObjects-before);

 delete level;owners.resources->m_pLevel=NULL;
}
void a(void*p,autotest::Capture&out){side(p,out,false);}void b(void*p,autotest::Capture&out){side(p,out,true);}
int worker(const tlhybrid_host*host){
 owners=particleNativeOwners(2);autotest::Coverage coverage("technique_constructor_recovery",0xa46260);
 for(unsigned i=0;i<32;++i){Case c={i,false};autotest::Outcome before,after;
  autotest::runChild(a,&c,before,2000,10000);autotest::runChild(b,&c,after,2000,10000);
  if(coverage.observe(host,before,after)){host->log("    technique ctor case%u status%d/%d issue%u/%u bytes%lu/%lu\n",i,before.childStatus,after.childStatus,before.capture.issue,after.capture.issue,(unsigned long)before.capture.length,(unsigned long)after.capture.length);coverage.report(host);return 1;}
 }
 coverage.report(host);Case c={7,true};autotest::Outcome before,after;
 autotest::runChild(a,&c,before,2000,10000);autotest::runChild(b,&c,after,2000,10000);
 bool detected=before.capture.length!=after.capture.length||std::memcmp(before.capture.data,after.capture.data,before.capture.length);
 host->log("    technique ctor negative control detected%u\n",detected?1u:0u);
 return !detected||autotest::incomplete(before)||autotest::incomplete(after)||!before.reportValid||!after.reportValid||before.childStatus||after.childStatus;
}
}
TL_TEST(technique_constructor_recovery){return systems_fixture::isolated(worker,host);}
