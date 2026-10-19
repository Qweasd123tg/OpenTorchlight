#include <Ogre.h>
#include "AutoTest.h"
#include "tests/SystemsFixtureWorker.h"
#define private public
#define protected public
#include "ParticleUniverseTechnique.h"
#include "ParticleRenderers/ParticleUniverseBillboardRenderer.h"
#include "ParticleRenderers/ParticleUniverseRibbonTrailRenderer.h"
#undef protected
#undef private
#include <ParticleUniverseSystemManager.h>
#include "ParticleNativeOwners.h"
namespace {
int worker(const tlhybrid_host*host){
    int failures=0;ParticleNativeOwners owners=particleNativeOwners(0);
    using namespace ParticleUniverse;
    ParticleSystemManager&manager=ParticleSystemManager::getSingleton();
    for(unsigned i=0;i<64;++i){
        int loops[]={-1,0,1,3};int count=loops[i%4];
        ParticleEmitter*emitter=manager.createEmitter("Point");
        TL_CHECK(failures,emitter->mRemainingLoops==-1&&emitter->mParentTechnique==NULL);
        emitter->setNumberOfLoops(count);
        TL_CHECK(failures,emitter->mNumberOfLoops==count&&emitter->mRemainingLoops==count);
        emitter->setNonExpiring(i&1);TL_CHECK(failures,emitter->isNonExpiring()==bool(i&1));
        TL_CHECK(failures,emitter->mKeepLocal==emitter->isKeepLocal());
        manager.destroyEmitter(emitter);
        BillboardRenderer*billboard=static_cast<BillboardRenderer*>(manager.createRenderer("Billboard"));
        TL_CHECK(failures,billboard->getBillboardSet()!=NULL);
        billboard->setBillboardOrigin(static_cast<Ogre::BillboardOrigin>(i%9));
        TL_CHECK(failures,billboard->getBillboardOrigin()==static_cast<Ogre::BillboardOrigin>(i%9));
        billboard->setFlipbookWidthHeight(1+i%4,1+i/4%4);
        TL_CHECK(failures,billboard->mRunicFlipbookWidth==int(1+i%4)&&billboard->mRunicFlipbookHeight==int(1+i/4%4));
        TL_CHECK(failures,billboard->mRunicFlipbookCount==billboard->mRunicFlipbookWidth*billboard->mRunicFlipbookHeight);
        ParticleRenderer*renderer=billboard;renderer->setRenderQueueGroup(i%101);TL_CHECK(failures,renderer->getRenderQueueGroup()==i%101);
        renderer->notifyCurrentCamera(owners.camera);
        manager.destroyRenderer(billboard);
        RibbonTrailRenderer*ribbon=static_cast<RibbonTrailRenderer*>(manager.createRenderer("RibbonTrail"));
        TL_CHECK(failures,ribbon->mRunicNodeC0==NULL&&ribbon->mTrail==NULL);
        ribbon->setTrailLocal(i&1);TL_CHECK(failures,ribbon->mTrailLocal==bool(i&1));
        Ogre::ColourValue a((i%8)*.125f,.25f,.5f,.75f),b(.75f,.5f,.25f,(i%8)*.125f);
        ribbon->setStartColour(a);ribbon->setEndColour(b);
        TL_CHECK(failures,ribbon->mStartColour==a&&ribbon->mEndColour==b);
        manager.destroyRenderer(ribbon);
        ParticleAffector*affector=manager.createAffector("LinearForce");
        ParticleTechnique*technique=manager.createTechnique();
        TL_CHECK(failures,affector->getParentTechnique()==NULL);
        technique->addAffector(affector);TL_CHECK(failures,affector->getParentTechnique()==technique);
        technique->removeAffector(affector);TL_CHECK(failures,affector->getParentTechnique()==NULL);
        manager.destroyAffector(affector);manager.destroyTechnique(technique);
    }
    host->log("    native SDK Emitter/Billboard/Ribbon/Affector C1/D1:64 profiles, exact typed fields and virtual APIs\n");return failures;
}
}
TL_TEST(particle_renderer_emitter_sdk_owners){return systems_fixture::isolated(worker,host);}
