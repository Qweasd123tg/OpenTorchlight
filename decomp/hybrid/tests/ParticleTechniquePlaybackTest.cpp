#include <Ogre.h>
#include "AutoTest.h"
#include "tests/SystemsFixtureWorker.h"
#define private public
#define protected public
#include "ParticleTechWrapper.h"
#include "ParticleEmitterWrapper.h"
#include "Level.h"
#include "MasterResourceManager.h"
#include "ParticlePreloader.h"
#include <ParticleUniverseSystem.h>
#include <ParticleUniverseEmitter.h>
#include <ParticleRenderers/ParticleUniverseBillboardRenderer.h>
#undef protected
#undef private
#include "tests/ParticleNativeOwners.h"

TL_ORIGINAL(void, playbackTechCtor, (CParticleTechWrapper*,CResourceManager*), "_ZN20CParticleTechWrapperC1EP16CResourceManager")
TL_ORIGINAL(void, playbackTechDtor, (CParticleTechWrapper*), "_ZN20CParticleTechWrapperD1Ev")
TL_ORIGINAL(void, playbackEmitterCtor, (CParticleEmitterWrapper*,CResourceManager*), "_ZN23CParticleEmitterWrapperC1EP16CResourceManager")
TL_ORIGINAL(void, playbackEmitterDtor, (CParticleEmitterWrapper*), "_ZN23CParticleEmitterWrapperD1Ev")
TL_ORIGINAL(void, playbackEmitterParent, (CParticleEmitterWrapper*,CParticleTechWrapper*), "_ZN23CParticleEmitterWrapper25setParentTechniqueWrapperEP20CParticleTechWrapper")
TL_ORIGINAL(void, oldTechStart, (CParticleTechWrapper*), "_ZN20CParticleTechWrapper5startEv")
TL_ORIGINAL(void, oldTechStop, (CParticleTechWrapper*), "_ZN20CParticleTechWrapper4stopEv")
TL_ORIGINAL(bool, oldTechPlaying, (CParticleTechWrapper*), "_ZN20CParticleTechWrapper9isPlayingEv")
extern "C" void newTechStart(CParticleTechWrapper*) __asm__("_ZN20CParticleTechWrapper5startEv");
extern "C" void newTechStop(CParticleTechWrapper*) __asm__("_ZN20CParticleTechWrapper4stopEv");
extern "C" bool newTechPlaying(CParticleTechWrapper*) __asm__("_ZN20CParticleTechWrapper9isPlayingEv");

namespace {
struct Case {
    unsigned seed, operation;
    bool negative;
    unsigned topology, ownParticles, firstParticles;
    bool nonExpiring;
};
template<class T> union Storage { long double alignment; char bytes[sizeof(T)]; };
ParticleNativeOwners owners;
unsigned operation;
void number(autotest::Capture& out,long long value){out.add(&value,sizeof(value));}
void particles(ParticleUniverse::ParticleTechnique* technique,unsigned count)
{
    technique->setVisualParticleQuota(0);
    if(!count)return;
    std::vector<ParticleUniverse::ParticleBehaviour*> behaviours;
    technique->mPool.increasePool(ParticleUniverse::Particle::PT_VISUAL,4,behaviours,technique);
    for(unsigned i=0;i<count;++i)technique->mPool.releaseParticle(ParticleUniverse::Particle::PT_VISUAL,"");
}
void systemState(autotest::Capture& out,ParticleUniverse::ParticleSystem* system,
                 ParticleUniverse::ParticleTechnique* own,ParticleUniverse::ParticleTechnique* other)
{
    number(out,system->getNumTechniques());
    for(unsigned i=0;i<system->getNumTechniques();++i){
        ParticleUniverse::ParticleTechnique* technique=system->getTechnique(i);
        number(out,technique==own);number(out,technique==other);
        number(out,technique->getNumberOfEmittedParticles());
        number(out,technique->getParentSystem()==system);
    }
}
void side(void* raw,autotest::Capture& out,bool ours)
{
    const Case& c=*static_cast<Case*>(raw);
    CResourceManager* resources=owners.resources;
    CMasterResourceManager* master=CMasterResourceManager::getSingleton();
    if(!master->m_pParticlePreloader)master->m_pParticlePreloader=new CParticlePreloader(NULL);
    CLevel* level=new CLevel(L"technique playback",NULL,NULL,resources,owners.scene,NULL,17,3);
    resources->m_pLevel=level;
    particleNativeSetEditorMode(owners,true);
    Storage<CParticleTechWrapper> storage;
    CParticleTechWrapper* wrapper=reinterpret_cast<CParticleTechWrapper*>(storage.bytes);
    playbackTechCtor(wrapper,resources);
    Storage<CParticleEmitterWrapper> emitterStorage[5];
    CParticleEmitterWrapper* emitters[5];
    unsigned count=c.topology?3:c.seed/16%6;
    for(unsigned i=0;i<count;++i){
        emitters[i]=reinterpret_cast<CParticleEmitterWrapper*>(emitterStorage[i].bytes);
        playbackEmitterCtor(emitters[i],resources);
        playbackEmitterParent(emitters[i],wrapper);
        emitters[i]->m_pEmitter->setNonExpiring(c.nonExpiring && i==count/2);
        emitters[i]->m_pEmitter->mRemainingLoops=int((c.seed+i)%4)-1;
        emitters[i]->m_pEmitter->setEnabled(bool((c.seed+i)&1));
        emitters[i]->m_bEnabled=bool((c.seed+i)&2);
    }
    ParticleUniverse::ParticleTechnique* technique=wrapper->m_technique;
    ParticleUniverse::ParticleSystem* system=wrapper->m_pParticleSystem;
    Storage<CParticleTechWrapper> otherStorage;
    CParticleTechWrapper* other=NULL;
    ParticleUniverse::ParticleTechnique* otherTechnique=NULL;
    ParticleUniverse::ParticleSystem* otherSystem=NULL;
    std::vector<ParticleUniverse::ParticleTechnique*> originalTechniques=system->mTechniques;
    std::vector<ParticleUniverse::ParticleTechnique*> otherOriginalTechniques;
    if(c.topology==2){
        other=reinterpret_cast<CParticleTechWrapper*>(otherStorage.bytes);
        playbackTechCtor(other,resources);
        otherTechnique=other->m_technique;otherSystem=other->m_pParticleSystem;
        otherOriginalTechniques=otherSystem->mTechniques;
        otherSystem->mTechniques.clear();
        system->addTechnique(otherTechnique);
        std::swap(system->mTechniques[0],system->mTechniques[1]);
    }else if(c.topology==1){
        system->mTechniques.clear();technique->setParentSystem(NULL);
    }
    if(c.seed&4)system->start();else system->stop();
    // Populate after start/stop: those SDK lifecycle calls can reset a pool.
    particles(technique,c.ownParticles);
    if(otherTechnique)particles(otherTechnique,c.firstParticles);
    wrapper->m_bPlaying=bool(c.seed&1);
    wrapper->m_bEnabled=bool(c.seed&2);
    if(c.seed%7==4){wrapper->m_bUnknown208=true;level->addUpdateObject(wrapper);}
    if(c.seed%7==5)resources->m_pLevel=NULL;
    if(c.operation==2 && !c.topology && c.seed%16==15)wrapper->m_pParticleSystem=NULL;
    particleNativeSetEditorMode(owners,(c.seed/8)%2==0);
    number(out,c.topology);number(out,c.nonExpiring);
    systemState(out,system,technique,otherTechnique);
    number(out,technique->getNumberOfEmittedParticles());
    if(technique->getNumberOfEmittedParticles()!=c.ownParticles ||
       (otherTechnique&&otherTechnique->getNumberOfEmittedParticles()!=c.firstParticles) ||
       (c.topology==1&&system->getNumTechniques()!=0) ||
       (c.topology==2&&(system->getNumTechniques()!=2||system->getTechnique(0)!=otherTechnique))){
        out.issue=autotest::Capture::InvalidReport;return;
    }
    bool result=false;
    if(c.operation==2){
        typedef bool(*Function)(CParticleTechWrapper*);
        Function function=ours?newTechPlaying:oldTechPlaying;
        if(!autotest::beginInvocation(out,function))return;
        result=function(wrapper);
    }else{
        typedef void(*Function)(CParticleTechWrapper*);
        Function function=c.operation==0?(ours?newTechStart:oldTechStart):(ours?newTechStop:oldTechStop);
        if(!autotest::beginInvocation(out,function))return;
        function(wrapper);
    }
    out.callCompleted=1;
    if(ours&&c.negative)wrapper->m_bPlaying=!wrapper->m_bPlaying;
    number(out,result);number(out,wrapper->m_bPlaying);number(out,wrapper->m_bUnknown208);
    number(out,wrapper->getVisible());number(out,wrapper->m_bEnabled);
    number(out,system->getState());number(out,technique->getNumberOfEmittedParticles());
    systemState(out,system,technique,otherTechnique);
    number(out,level->m_updateObjects.size());
    for(unsigned i=0;i<level->m_updateObjects.size();++i)number(out,level->m_updateObjects[i]==wrapper);
    for(unsigned i=0;i<count;++i){
        number(out,emitters[i]->m_pEmitter->isEnabled());
        number(out,emitters[i]->m_bEnabled);number(out,emitters[i]->m_pEmitter->mRemainingLoops);
        number(out,emitters[i]->m_pEmitter->isNonExpiring());
    }
    ParticleUniverse::BillboardRenderer* renderer=dynamic_cast<ParticleUniverse::BillboardRenderer*>(technique->getRenderer());
    number(out,renderer!=NULL);
    if(renderer){number(out,renderer->mBillboardSet!=NULL);if(renderer->mBillboardSet)number(out,renderer->mBillboardSet->isVisible());}
    wrapper->m_pParticleSystem=system;resources->m_pLevel=level;
    particleNativeSetEditorMode(owners,true);
    // Restore the native owners before either wrapper's original destructor.
    system->mTechniques=originalTechniques;technique->setParentSystem(system);
    if(other){
        otherSystem->mTechniques=otherOriginalTechniques;
        otherTechnique->setParentSystem(otherSystem);
    }
    for(unsigned i=0;i<count;++i)playbackEmitterDtor(emitters[i]);
    if(other)playbackTechDtor(other);
    playbackTechDtor(wrapper);
    delete level;resources->m_pLevel=NULL;
}
void before(void*p,autotest::Capture&out){side(p,out,false);}
void after(void*p,autotest::Capture&out){side(p,out,true);}
int worker(const tlhybrid_host*host)
{
    owners=particleNativeOwners(2);
    const char* labels[]={"technique_start_recovery","technique_stop_recovery","technique_playing_recovery"};
    const unsigned long addresses[]={0xa3d110,0xa3d240,0xa3c650};
    autotest::Coverage coverage(labels[operation],addresses[operation]);
    unsigned cases=operation==2?192:96;
    for(unsigned i=0;i<cases;++i){
        Case c={i,operation,false,0,i%4,0,bool(i/4%2)};
        if(i>=96){
            unsigned sample=i-96;
            c.topology=sample<32?1:2;
            unsigned variant=sample<32?sample:sample-32;
            unsigned state=variant%16;
            c.seed=96+(state&1)+((state&2)<<1)+((state&4)<<1)+(variant/16)*32;
            c.nonExpiring=bool(state&8);
            c.ownParticles=variant/16%2?2:0;
            c.firstParticles=variant/32%2?3:0;
        }
        autotest::Outcome a,b;
        autotest::runChild(before,&c,a,2000,10000);autotest::runChild(after,&c,b,2000,10000);
        if(coverage.observe(host,a,b)){
            host->log("    technique case%u op%u status%d/%d issue%u/%u bytes%lu/%lu\n",i,operation,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
            coverage.report(host);return 1;
        }
    }
    coverage.report(host);
    Case c={19,operation,true,0,3,0,false};autotest::Outcome a,b;
    autotest::runChild(before,&c,a,2000,10000);autotest::runChild(after,&c,b,2000,10000);
    bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);
    host->log("    technique negative control detected%u\n",detected?1u:0u);
    return !detected||autotest::incomplete(a)||autotest::incomplete(b)||!a.reportValid||!b.reportValid||a.childStatus||b.childStatus;
}
}
TL_TEST(technique_start_recovery){operation=0;return systems_fixture::isolated(worker,host);}
TL_TEST(technique_stop_recovery){operation=1;return systems_fixture::isolated(worker,host);}
TL_TEST(technique_playing_recovery){operation=2;return systems_fixture::isolated(worker,host);}
