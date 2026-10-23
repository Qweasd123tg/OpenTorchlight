#include <execinfo.h>
#include "AutoTest.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsNativeGame.h"
#include "tests/NativeMenuClient.h"
#include "tests/SystemsFixtureWorker.h"
#include "RenderableStates.h"
#include <OgreSubEntity.h>
#include <OgreMeshManager.h>
#include <OgreSubMesh.h>
#include <OgreRenderQueueSortingGrouping.h>
TL_ORIGINAL(bool,rqOld,(CGame*,Ogre::Renderable*,unsigned char,unsigned short,Ogre::Technique**,Ogre::RenderQueue*),"_ZN5CGame16renderableQueuedEPN4Ogre10RenderableEhtPPNS0_9TechniqueEPNS0_11RenderQueueE")
extern "C" bool rqNew(CGame*,Ogre::Renderable*,unsigned char,unsigned short,Ogre::Technique**,Ogre::RenderQueue*) __asm__("_ZN5CGame16renderableQueuedEPN4Ogre10RenderableEhtPPNS0_9TechniqueEPNS0_11RenderQueueE");
TL_FUNCTION(rqAdd,"_ZN4Ogre16RenderQueueGroup13addRenderableEPNS_10RenderableEPNS_9TechniqueEt")
namespace {
const tlhybrid_host* diagnosticHost;
void diagnosticAbort(int line){diagnosticHost->log("    fixture abort at line%d\n",line);std::abort();}
void diagnosticFault(int signal){void* frames[32];int count=backtrace(frames,32);for(int i=0;i<count;++i)diagnosticHost->log("    fixture signal%d frame%d %p\n",signal,i,frames[i]);_exit(128+signal);}

nativegame::Services*services;CGameClient*client;autotest::Capture*cap;Ogre::RenderQueueGroup*group88,*group90;Ogre::Renderable*expectedRenderable;Ogre::Technique*techniques[4];
void num(unsigned n){cap->add(&n,4);}
unsigned techID(Ogre::Technique*t){if(!t)return 0;for(unsigned i=0;i<4;++i)if(t==techniques[i])return i+1;return 99;}
void add(Ogre::RenderQueueGroup*group,Ogre::Renderable*renderable,Ogre::Technique*tech,unsigned short priority){num(group==group88?88:group==group90?90:999);num(renderable==expectedRenderable);num(techID(tech));num(priority);if((group!=group88&&group!=group90)||renderable!=expectedRenderable)cap->issue=autotest::Capture::InvalidReport;}
struct Foreign:Ogre::Renderable{Ogre::MaterialPtr material;Ogre::LightList lights;const Ogre::MaterialPtr&getMaterial()const{return material;}void getRenderOperation(Ogre::RenderOperation&){}void getWorldTransforms(Ogre::Matrix4*)const{}Ogre::Real getSquaredViewDepth(const Ogre::Camera*)const{return 0;}const Ogre::LightList&getLights()const{return lights;}};
struct Case{unsigned queue,kind,flags,opacity,client,negative;};
void side(void*raw,autotest::Capture&out,bool ours){signal(SIGABRT,diagnosticFault);signal(SIGSEGV,diagnosticFault);Case c=*static_cast<Case*>(raw);cap=&out;SystemsNativeGame native(Ogre::Root::getSingletonPtr(),CMasterResourceManager::getSingleton()->m_pSettings);CGame*g=native.game;Ogre::SceneManager*scene=services->scene;
 Ogre::MaterialPtr noTech=Ogre::MaterialManager::getSingleton().create("render-no-tech","General");noTech->removeAllTechniques();Ogre::MeshPtr mesh=Ogre::MeshManager::getSingleton().createManual("render-state-mesh","General");mesh->_setBounds(Ogre::AxisAlignedBox(-1,-1,-1,1,1,1),false);mesh->createSubMesh()->setMaterialName(noTech->getName());Ogre::Entity*entity=scene->createEntity("render-state-entity",mesh->getName());Ogre::SubEntity*sub=entity->getSubEntity(0);
 Ogre::MaterialPtr materials[4];for(unsigned i=0;i<4;++i){materials[i]=Ogre::MaterialManager::getSingleton().create("render-state-material-"+Ogre::StringConverter::toString(i),"General");techniques[i]=materials[i]->getTechnique(0);techniques[i]->createPass();}
 if(c.kind==5)techniques[0]->removeAllPasses();CRenderableStates state=CRenderableStates();state.renderBehind=(c.flags&16)!=0;state.highlighted=(c.flags&32)!=0;state.m_state0=(c.flags&64)!=0;state.material18=materials[1].getPointer();state.material20=(c.flags&128)?materials[2].getPointer():NULL;const float opacities[]={-1,0,0.25f,__builtin_nanf("")};state.m_opacity=opacities[c.opacity];if(c.kind>=4||c.kind==6)sub->setUserAny(Ogre::Any(&state));else if(c.kind==3)sub->setUserAny(Ogre::Any(static_cast<CRenderableStates*>(NULL)));
 g->m_renderParticles=(c.flags&1)!=0;g->m_disableRenderBehind=(c.flags&2)!=0;g->m_disableRendering=(c.flags&4)!=0;g->m_renderBehind=(c.flags&8)!=0;g->m_particleMaterial=materials[3];g->m_behindMaterial=materials[3];g->m_gameClient=c.client?client:NULL;if(c.client)client->m_gameState=static_cast<EGameState>(c.client==1?0:1);
 Ogre::RenderQueue*queue=scene->getRenderQueue();group88=queue->getQueueGroup(88);group90=queue->getQueueGroup(90);Ogre::Technique*tech=c.kind==4?NULL:techniques[0];Foreign foreign;Ogre::Renderable*renderable=c.kind==0?NULL:c.kind==1?static_cast<Ogre::Renderable*>(&foreign):static_cast<Ogre::Renderable*>(sub);expectedRenderable=renderable;detour::Set dispatch;TL_REDIRECT(dispatch,rqAdd,&add);if(dispatch.failed())_exit(64);
 bool(*fn)(CGame*,Ogre::Renderable*,unsigned char,unsigned short,Ogre::Technique**,Ogre::RenderQueue*)=ours?rqNew:rqOld;if(autotest::beginInvocation(out,fn)){bool result=fn(g,renderable,c.queue,32769,&tech,queue);out.callCompleted=1;num(result);}num(techID(tech));if(ours&&c.negative)num(0xbadc0de);dispatch.restore();g->m_gameClient=NULL;g->m_particleMaterial.setNull();g->m_behindMaterial.setNull();scene->destroyEntity(entity);
}
void oldSide(void*p,autotest::Capture&o){side(p,o,false);}void newSide(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){diagnosticHost=host;nativegame::Services native;services=&native;CMasterResourceManager*master=CMasterResourceManager::getSingleton();if(!native.ready())return 1;menugui::Audio audio(master);menugui::Client actual(*master->m_pSettings,master,*master->m_pSoundManager);client=actual.client;autotest::Stats stats={0,0,0};autotest::Coverage cov("complete_game_renderable",reinterpret_cast<uintptr_t>(rqOld));unsigned n=0;int failures=0;unsigned queues[]={0,5,88,90,94,95,96,97,98,99,100,255};for(unsigned q=0;q<12;++q)for(unsigned kind=0;kind<7;++kind){Case c={queues[q],kind,0xff,2,2};bool ok=autotest::compareCase(oldSide,newSide,&c,stats,host,"complete_game_renderable",n++,&cov);TL_CHECK(failures,ok);}for(unsigned flags=0;flags<256;++flags)for(unsigned opacity=0;opacity<4;++opacity)for(unsigned client=0;client<3;++client){Case c={94,6,flags,opacity,client};bool ok=autotest::compareCase(oldSide,newSide,&c,stats,host,"complete_game_renderable",n++,&cov);TL_CHECK(failures,ok);}cov.report(host);Case control={94,6,0xff,2,2,1};autotest::Outcome a,b;autotest::runChild(oldSide,&control,a);autotest::runChild(newSide,&control,b);bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);bool completed=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!autotest::incomplete(a)&&!autotest::incomplete(b);host->log("    game renderable negative detected%u completed%u\n",unsigned(detected),unsigned(completed));return failures+stats.incomplete+(cov.completed!=n)+(!detected||!completed);}
}
TL_TEST(complete_game_renderable){return systems_fixture::isolated(&worker,host,180);}
