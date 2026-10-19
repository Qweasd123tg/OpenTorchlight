#include <Ogre.h>
#include <execinfo.h>
#include <signal.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#include "ParticleWrapper.h"
#include "EditorScene.h"
#include "Layout.h"
#define private public
#define protected public
#include <ParticleUniverseSystem.h>
#undef protected
#undef private
#include <ParticleUniverseSystemManager.h>
#include "ParticleNativeOwners.h"
#include "OgreUtilities.h"
TL_ORIGINAL(void,pwOldCtor,(CParticleWrapper*,CResourceManager*),"_ZN16CParticleWrapperC1EP16CResourceManager")
extern "C" void pwNewCtor(CParticleWrapper*,CResourceManager*) __asm__("_ZN16CParticleWrapperC1EP16CResourceManager");
TL_ORIGINAL(void,pwOldCreate,(CParticleWrapper*),"_ZN16CParticleWrapper20createParticleSystemEv")
extern "C" void pwNewCreate(CParticleWrapper*) __asm__("_ZN16CParticleWrapper20createParticleSystemEv");
TL_ORIGINAL(void,pwOldShow,(CParticleWrapper*),"_ZN16CParticleWrapper20showVisualSphereMeshEv")
extern "C" void pwNewShow(CParticleWrapper*) __asm__("_ZN16CParticleWrapper20showVisualSphereMeshEv");
TL_FUNCTION(pwFixedTimeout,"_ZNK16ParticleUniverse14ParticleSystem15getFixedTimeoutEv")
TL_FUNCTION(pwCreateEntity,"_ZN14OGRE_UTILITIES12createEntityEPN4Ogre12SceneManagerENS_11EPRIMITIVESENS_10EQUERYMASKEPKc")
namespace {
struct Case{unsigned op,profile,negative;};
const Case* current;autotest::Capture* capture;const tlhybrid_host* logHost;bool oursSide;Ogre::Entity*visual;Ogre::SceneManager*scene;
float fixedTimeout(const ParticleUniverse::ParticleSystem*ps){
    const unsigned values[]={0xbf800000,0,0x3f000000,0x40000000,0x7fc00000,0x7f800000,0xff800000,0x80000000};
    unsigned bits=values[current->profile/4%8];float result;std::memcpy(&result,&bits,4);
    capture->add(&bits,4);unsigned valid=ps!=NULL;capture->add(&valid,4);return result;
}
void word(unsigned value){capture->add(&value,4);}void vec(const Ogre::Vector3&value){capture->add(&value,12);}
void fault(int signal){void*frames[24];int n=backtrace(frames,24);for(int i=0;i<n;++i)logHost->log("    Particle signal%d op%u profile%u side%u frame%d %p\n",signal,current->op,current->profile,unsigned(oursSide),i,frames[i]);_exit(128+signal);}
Ogre::Entity*asset(Ogre::SceneManager*manager,OGRE_UTILITIES::EPRIMITIVES primitive,OGRE_UTILITIES::EQUERYMASK mask,const char*name){
    word(101);word(manager==scene);word(primitive);word(mask);capture->addText(std::string(name));
    if(current->profile%8==5)throw Ogre::Exception(17,"controlled mesh failure","ParticleWrapper asset boundary");
    return visual;
}
void side(void* raw,autotest::Capture&out,bool ours){
    Case c=*static_cast<Case*>(raw);current=&c;capture=&out;oursSide=ours;signal(SIGSEGV,fault);signal(SIGABRT,fault);
    ParticleNativeOwners owners=particleNativeOwners(c.profile);scene=owners.scene;
    CParticleWrapper*wrapper=static_cast<CParticleWrapper*>(Ogre::NedAllocImpl::allocBytes(sizeof(CParticleWrapper),0,0,0));
    if(c.op!=0)pwOldCtor(wrapper,owners.resources);
    if(c.op==1){ParticleUniverse::ParticleSystemManager::getSingleton().destroyParticleSystem(wrapper->m_pParticleSystem,scene);wrapper->m_pParticleSystem=NULL;wrapper->m_bPlaying=c.profile&8;wrapper->m_iRandomWeight=13+c.profile;}
    if(c.op==2){
        if(c.profile%8==1||c.profile%8==2){wrapper->m_pVisualSphereNode=scene->createSceneNode();if(c.profile%8==2)scene->getRootSceneNode()->addChild(wrapper->m_pVisualSphereNode);}
        if(c.profile%8>=3)wrapper->SetSceneOwner(new CEditorScene(L"particle visual scene"));
        if(c.profile%8==3)wrapper->SetSceneOwner(new CLayout(owners.resources,static_cast<ELAYOUT_TYPES>(0)));
        Ogre::MeshPtr mesh=Ogre::MeshManager::getSingleton().createManual("particle-visual-mesh","General");mesh->_setBounds(Ogre::AxisAlignedBox(Ogre::Vector3(-1,-2,-3),Ogre::Vector3(1,2,3)),false);
        visual=scene->createEntity("particle-visual",mesh->getName());
    }
    out.length=0;detour::Set d;
    if(c.op==2)TL_REDIRECT(d,pwCreateEntity,asset);
    else TL_REDIRECT(d,pwFixedTimeout,fixedTimeout);
    if(d.failed())std::abort();
    if(c.op==0){typedef void(*F)(CParticleWrapper*,CResourceManager*);F f=ours?pwNewCtor:pwOldCtor;if(autotest::beginInvocation(out,f)){f(wrapper,owners.resources);out.callCompleted=1;}}
    else {typedef void(*F)(CParticleWrapper*);F f=c.op==1?(ours?pwNewCreate:pwOldCreate):(ours?pwNewShow:pwOldShow);if(autotest::beginInvocation(out,f)){f(wrapper);out.callCompleted=1;}}
    if(ours&&c.negative)wrapper->m_iRandomWeight^=1;
    word(wrapper->m_iRandomWeight);word(wrapper->m_bPlaying);word(wrapper->getVisible());word(wrapper->getEnabled());word(wrapper->getSceneNode()!=NULL);word(wrapper->getResourceManager()==owners.resources);vec(wrapper->getPosition(false));vec(wrapper->getScale());
    word(wrapper->m_pParticleSystem!=NULL);
    if(wrapper->m_pParticleSystem){ParticleUniverse::ParticleSystem*ps=wrapper->m_pParticleSystem;word(ps->getState());word(ps->getNumTechniques());word(ps->getQueryFlags());word(ps->getCastShadows());word(ps->getParentSceneNode()==wrapper->getSceneNode());word(ps->isEnabled());word(ps->isKeepLocal());word(ps->isAttached());word(ps->mBoundsAutoUpdate);word(ps->mRunicCurrentCamera==owners.camera);out.add(&ps->mRunicUpdateElapsed,4);word(ps->mManualUpdate);}
    word(wrapper->m_pVisualSphereNode!=NULL);word(wrapper->m_pVisualSphereEntity!=NULL);
    if(wrapper->m_pVisualSphereNode){Ogre::SceneNode*n=wrapper->m_pVisualSphereNode;vec(n->getScale());word(n->getParentSceneNode()==wrapper->getSceneNode());word(n->numAttachedObjects());}
    if(wrapper->m_pVisualSphereEntity){word(wrapper->m_pVisualSphereEntity==visual);word(wrapper->m_pVisualSphereEntity->getQueryFlags());word(wrapper->m_pVisualSphereEntity->getCastShadows());}
}
void before(void*p,autotest::Capture&c){side(p,c,false);}void after(void*p,autotest::Capture&c){side(p,c,true);}
int run(const tlhybrid_host*host,unsigned op,const char*name,uintptr_t address){
    const tlhybrid_host*h=host;logHost=h;int failures=0;autotest::Coverage coverage(name,address);
    for(unsigned i=0;i<32;++i){Case c={op,i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a,2000,10000);autotest::runChild(after,&c,b,2000,10000);int bad=coverage.observe(h,a,b);TL_CHECK(failures,!bad);if(bad){h->log("    Particle op%u profile%u status%d/%d bytes%lu/%lu\n",op,i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){h->log("    first difference%u %u/%u\n",j,unsigned(a.capture.data[j]),unsigned(b.capture.data[j]));break;}coverage.report(h);return failures;}}
    coverage.report(h);Case c={op,7,1};autotest::Outcome a,b;autotest::runChild(before,&c,a,2000,10000);autotest::runChild(after,&c,b,2000,10000);bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,detected&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);h->log("    Particle negative op%u detected%u\n",op,unsigned(detected));return failures;
}
int ctorWorker(const tlhybrid_host*h){return run(h,0,"particle_wrapper_ctor",0xa49cf0);}int createWorker(const tlhybrid_host*h){return run(h,1,"particle_wrapper_create",0xa499f0);}int showWorker(const tlhybrid_host*h){return run(h,2,"particle_wrapper_show",0xa497f0);}
}
TL_TEST(particle_wrapper_ctor){return systems_fixture::isolated(ctorWorker,host);}
TL_TEST(particle_wrapper_create){return systems_fixture::isolated(createWorker,host);}
TL_TEST(particle_wrapper_show){return systems_fixture::isolated(showWorker,host);}
