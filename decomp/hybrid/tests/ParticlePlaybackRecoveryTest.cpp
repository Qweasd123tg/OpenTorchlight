#include <Ogre.h>
#include "AutoTest.h"
#include "tests/SystemsFixtureWorker.h"
#define private public
#define protected public
#include "Particle.h"
#include "ParticleCache.h"
#include "ParticlePreloader.h"
#include "Level.h"
#include "MasterResourceManager.h"
#include <ParticleUniverseSystemManager.h>
#include <ParticleUniverseSystem.h>
#include <ParticleUniverseEmitter.h>
#undef protected
#undef private
#include "ParticleNativeOwners.h"

TL_ORIGINAL(void, playbackCtor, (CParticle*,CParticlePreloader*,const std::wstring&,CResourceManager*), "_ZN9CParticleC1EP18CParticlePreloaderRKSbIwSt11char_traitsIwESaIwEEP16CResourceManager")
TL_ORIGINAL(void, playbackOldStart, (CParticle*), "_ZN9CParticle5StartEv")
TL_ORIGINAL(void, playbackOldStop, (CParticle*,bool), "_ZN9CParticle4StopEb")
TL_ORIGINAL(int, playbackOldCount, (CParticle*,bool), "_ZN9CParticle28getNumberOfParticlesUpdatingEb")
extern "C" void playbackNewStart(CParticle*) __asm__("_ZN9CParticle5StartEv");
extern "C" void playbackNewStop(CParticle*,bool) __asm__("_ZN9CParticle4StopEb");
extern "C" int playbackNewCount(CParticle*,bool) __asm__("_ZN9CParticle28getNumberOfParticlesUpdatingEb");

namespace {
struct Case { unsigned operation, seed, negative; };
ParticleNativeOwners owners;

void number(autotest::Capture& out, unsigned n) { out.add(&n,sizeof n); }
void scalar(autotest::Capture& out, float f) { out.add(&f,sizeof f); }

void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case c = *static_cast<Case*>(raw);
    unsigned mode = c.seed % 16;
    CResourceManager* resources = owners.resources;
    CLevel* level = new CLevel(L"particle playback",NULL,NULL,resources,owners.scene,NULL,17,3);
    resources->m_pLevel = level;
    CParticlePreloader* preloader = new CParticlePreloader(NULL);
    CParticle* particle = static_cast<CParticle*>(Ogre::NedAllocImpl::allocBytes(sizeof(CParticle),0,0,0));
    std::wstring name(L"playback fixture");
    playbackCtor(particle,preloader,name,resources);
    CParticleCache* cache = new CParticleCache(owners.scene,NULL);
    TArrayList<CParticleCache*>* available = new TArrayList<CParticleCache*>;
    cache->m_pRootSceneNode = available;
    preloader->m_particleCaches[name] = available;
    unsigned systems = 1 + c.seed / 16 % 3;
    if (mode == 8) systems = 0;
    std::vector<ParticleUniverse::ParticleSystem*> allSystems;
    std::vector<ParticleUniverse::ParticleEmitter*> allEmitters;
    for (unsigned i=0; i<systems; ++i) {
        std::string systemName("playback-system-"); systemName += char('0'+i);
        ParticleUniverse::ParticleSystem* system = CMasterResourceManager::getSingleton()->m_pParticleSystemManager->createParticleSystem(systemName,owners.scene);
        allSystems.push_back(system);
        cache->mActiveParticleSystems.add(system);
        Ogre::SceneNode* node = (c.seed+i)&1 ? owners.scene->createSceneNode() : NULL;
        cache->mParticleSceneNodes.add(node);
        unsigned techniques = 1 + (c.seed/4+i)%2;
        if (c.operation==2 && mode==9) {
            system->mTechniques.push_back(NULL);
            continue;
        }
        for (unsigned j=0; j<techniques; ++j) {
            ParticleUniverse::ParticleTechnique* technique = system->createTechnique();
            technique->setVisualParticleQuota(0);
            technique->mRunicFlag5b1 = bool((c.seed+j)&2);
            unsigned emitters = (c.seed/2+j)%4;
            for (unsigned k=0; k<emitters; ++k) {
                ParticleUniverse::ParticleEmitter* emitter = technique->createEmitter("Point");
                allEmitters.push_back(emitter);
                ParticleUniverse::DynamicAttributeFixed* duration = new ParticleUniverse::DynamicAttributeFixed;
                duration->setValue(.125f*(1+k));
                emitter->setDynDuration(duration);
                ParticleUniverse::DynamicAttributeFixed* ttl = new ParticleUniverse::DynamicAttributeFixed;
                ttl->setValue(.25f*(1+j));
                emitter->setDynTotalTimeToLive(ttl);
                emitter->setNumberOfLoops(int((c.seed+k)%4)-1);
                emitter->setNonExpiring(bool((c.seed+k)%5==0));
                emitter->mRunicFlag25b = bool(c.seed&4);
            }
            if (c.operation==2 && (c.seed+j)%3) {
                std::vector<ParticleUniverse::ParticleBehaviour*> behaviours;
                technique->mPool.increasePool(ParticleUniverse::Particle::PT_VISUAL,3,behaviours,technique);
                for (unsigned k=0; k<1+c.seed%3; ++k)
                    technique->mPool.releaseParticle(ParticleUniverse::Particle::PT_VISUAL,"");
            }
        }
        system->setFixedTimeout(c.seed&8 ? .75f : 0.0f);
    }
    particle->m_pParticleCache = cache;
    particle->m_bUnknown125 = bool(c.seed&1);
    particle->m_bUnknown126 = true;
    particle->m_bUnknown128 = bool(c.seed&2);
    particle->m_bUnknown127 = bool(c.seed&4);
    particle->m_fUnknown120 = 3.5f;
    particle->m_bVisible = c.operation==0 ? false : true;
    if (c.operation==0) {
        if (mode==0) particle->m_pUnknown110.clear();
        if (mode==1) particle->m_pResourceManager=NULL;
        if (mode==2) resources->m_pLevel=NULL;
        if (mode==3) particle->m_pParticlePreloader=NULL;
        if (mode==4) {particle->m_bUnknown126=false;particle->m_bVisible=true;}
        if (mode==5) {particle->m_pParticleCache=NULL;preloader->m_particleCaches.erase(name);}
        if (mode==6) {
            particle->m_pParticleCache=NULL;
            available->add(NULL);available->add(cache);available->add(cache);
        }
    } else if (c.operation==1) {
        if (mode==0) particle->m_bVisible=false;
        if (mode==1) particle->m_pParticleCache=NULL;
        if (mode==2) resources->m_pLevel=NULL;
        if (mode==3) particle->m_bUnknown125=true;
        else particle->m_bUnknown125=false;
        for (unsigned i=0; i<systems; ++i) {
            Ogre::SceneNode* node=cache->mParticleSceneNodes[i];
            if (node) {particle->getSceneNode()->addChild(node);node->attachObject(allSystems[i]);}
            else particle->getSceneNode()->attachObject(allSystems[i]);
        }
    } else if (mode==0) particle->m_pParticleCache=NULL;

    int result=0;
    if (c.operation==0) {
        typedef void (*F)(CParticle*); F f=ours?playbackNewStart:playbackOldStart;
        if (autotest::beginInvocation(out,f)) {f(particle);out.callCompleted=1;}
    } else if (c.operation==1) {
        typedef void (*F)(CParticle*,bool); F f=ours?playbackNewStop:playbackOldStop;
        if (autotest::beginInvocation(out,f)) {f(particle,bool(c.seed&4));out.callCompleted=1;}
    } else {
        typedef int (*F)(CParticle*,bool); F f=ours?playbackNewCount:playbackOldCount;
        if (autotest::beginInvocation(out,f)) {result=f(particle,bool(c.seed&1));out.callCompleted=1;}
    }
    if (ours && c.negative) {
        if (c.operation==2) result^=1;
        else particle->m_bUnknown125=!particle->m_bUnknown125;
    }
    number(out,result);number(out,particle->m_pParticleCache==cache);number(out,particle->m_pParticleCache!=NULL);
    number(out,particle->m_bVisible);number(out,particle->m_bUnknown125);number(out,particle->m_bUnknown126);
    number(out,particle->m_bUnknown127);number(out,particle->m_bUnknown128);scalar(out,particle->m_fUnknown120);
    number(out,level->m_updateObjects.size());number(out,available->size());
    number(out,particle->getSceneNode()->numAttachedObjects());number(out,particle->getSceneNode()->numChildren());
    for (unsigned i=0;i<allSystems.size();++i) {
        ParticleUniverse::ParticleSystem* system=allSystems[i];
        number(out,system->getState());number(out,system->getParentSceneNode()==particle->getSceneNode());
        number(out,system->mRunicCurrentCamera==NULL);scalar(out,system->getFixedTimeout());
        for (unsigned j=0;j<system->getNumTechniques();++j) {
            ParticleUniverse::ParticleTechnique* technique=system->getTechnique(j);
            number(out,technique!=NULL);
            if (technique) number(out,technique->getNumberOfEmittedParticles());
        }
    }
    for (unsigned i=0;i<allEmitters.size();++i) {
        ParticleUniverse::ParticleEmitter* emitter=allEmitters[i];
        number(out,emitter->mRunicFlag25b);number(out,emitter->mRemainingLoops);number(out,emitter->isNonExpiring());
    }
}
void before(void* p,autotest::Capture& c) {side(p,c,false);}
void after(void* p,autotest::Capture& c) {side(p,c,true);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address)
{
    owners=particleNativeOwners(0);
    int failures=0;
    autotest::Coverage coverage(name,address);
    for (unsigned i=0;i<48;++i) {
        Case c={operation,i,0};autotest::Outcome a,b;
        autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);
        int bad=coverage.observe(host,a,b);TL_CHECK(failures,!bad);
        if (bad) {host->log("    playback op%u seed%u status%d/%d bytes%lu/%lu\n",operation,i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return failures;}
    }
    coverage.report(host);
    Case c={operation,7,1};autotest::Outcome a,b;
    autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);
    bool detected=a.capture.length!=b.capture.length || std::memcmp(a.capture.data,b.capture.data,a.capture.length);
    TL_CHECK(failures,detected&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);
    return failures;
}
int startWorker(const tlhybrid_host* h) {return run(h,0,"particle_playback_start",0xa2a620);}
int stopWorker(const tlhybrid_host* h) {return run(h,1,"particle_playback_stop",0xa2a290);}
int countWorker(const tlhybrid_host* h) {return run(h,2,"particle_playback_count",0xa2ab30);}
}
TL_TEST(particle_playback_start) {return systems_fixture::isolated(startWorker,host);}
TL_TEST(particle_playback_stop) {return systems_fixture::isolated(stopWorker,host);}
TL_TEST(particle_playback_count) {return systems_fixture::isolated(countWorker,host);}
