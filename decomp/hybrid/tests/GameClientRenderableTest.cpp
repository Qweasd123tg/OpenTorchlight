#include "AutoTest.h"
#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "tests/NativeMenuClient.h"
#include "tests/SystemsFixtureWorker.h"
#include "RenderableStates.h"
#include <OgreSubEntity.h>
#include <OgreMeshManager.h>
#include <OgreSubMesh.h>
#include <OgreStringConverter.h>
TL_ORIGINAL(bool,gcrOld,(CGameClient*,Ogre::Renderable*,unsigned char,unsigned short,Ogre::Technique**,Ogre::RenderQueue*),"_ZN11CGameClient16renderableQueuedEPN4Ogre10RenderableEhtPPNS0_9TechniqueEPNS0_11RenderQueueE")
extern "C" bool gcrNew(CGameClient*,Ogre::Renderable*,unsigned char,unsigned short,Ogre::Technique**,Ogre::RenderQueue*) __asm__("_ZN11CGameClient16renderableQueuedEPN4Ogre10RenderableEhtPPNS0_9TechniqueEPNS0_11RenderQueueE");
namespace {
CGameClient*client;Ogre::SubEntity*sub;Ogre::RenderQueue*queue;Ogre::Technique*techniques[5][64];
struct Foreign:Ogre::Renderable {Ogre::MaterialPtr material;Ogre::LightList lights;const Ogre::MaterialPtr&getMaterial()const{return material;}void getRenderOperation(Ogre::RenderOperation&){}void getWorldTransforms(Ogre::Matrix4*)const{}Ogre::Real getSquaredViewDepth(const Ogre::Camera*)const{return 0;}const Ogre::LightList&getLights()const{return lights;}};
struct Case {unsigned shadow,group,kind,casts,state,blend,opacity;};
unsigned identity(Ogre::Technique*p){if(!p)return 0;for(unsigned a=0;a<5;++a)for(unsigned i=0;i<64;++i)if(p==techniques[a][i])return 1+a*64+i;return 999;}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);client->m_shadowPass=c.shadow!=0;Foreign foreign;CRenderableStates state=CRenderableStates();state.castsShadows=c.casts!=0;state.m_state2=c.state;state.m_value2c=c.blend;
 if(c.opacity<64)state.m_opacity=float(c.opacity+1)/64.0f;else {const float edge[]={-1,0,__builtin_nanf(""),.0001f,.015624f,.015626f,.499999f,.500001f,.99999f};state.m_opacity=edge[c.opacity-64];}
 if(c.kind==2)sub->setUserAny(Ogre::Any());else if(c.kind==3)sub->setUserAny(Ogre::Any(static_cast<CRenderableStates*>(NULL)));else sub->setUserAny(Ogre::Any(&state));
 Ogre::Renderable*renderable=c.kind==0?NULL:c.kind==1?static_cast<Ogre::Renderable*>(&foreign):static_cast<Ogre::Renderable*>(sub);Ogre::Technique*technique=techniques[2][17];typedef bool(*Fn)(CGameClient*,Ogre::Renderable*,unsigned char,unsigned short,Ogre::Technique**,Ogre::RenderQueue*);Fn fn=ours?gcrNew:gcrOld;if(autotest::beginInvocation(out,fn)){bool result=fn(client,renderable,c.group,32769,&technique,queue);out.callCompleted=1;unsigned value=result;out.add(&value,4);value=identity(technique);out.add(&value,4);}
}
void oldSide(void*p,autotest::Capture&o){side(p,o,false);}void newSide(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services native;if(!native.ready())return 1;menugui::Audio audio(native.master);menugui::Client owner(*native.settings,native.master,*native.master->m_pSoundManager);client=owner.client;Ogre::SceneManager*scene=native.scene;
 Ogre::MaterialPtr noTech=Ogre::MaterialManager::getSingleton().create("client-render-no-tech","General");noTech->removeAllTechniques();Ogre::MeshPtr mesh=Ogre::MeshManager::getSingleton().createManual("client-render-mesh","General");mesh->_setBounds(Ogre::AxisAlignedBox(-1,-1,-1,1,1,1),false);mesh->createSubMesh()->setMaterialName(noTech->getName());Ogre::Entity*entity=scene->createEntity("client-render-entity",mesh->getName());sub=entity->getSubEntity(0);queue=scene->getRenderQueue();
 Ogre::MaterialPtr*arrays[]={client->m_shadowOpaque,client->m_shadowAlpha,client->m_shadowBlend3,client->m_shadowBlend2,client->m_shadowBlend1};for(unsigned a=0;a<5;++a)for(unsigned i=0;i<64;++i){Ogre::MaterialPtr m=Ogre::MaterialManager::getSingleton().create("client-shadow-"+Ogre::StringConverter::toString(a)+"-"+Ogre::StringConverter::toString(i),"General");arrays[a][i]=m;techniques[a][i]=m->getTechnique(0);}
 autotest::Stats stats={0,0,0};autotest::Coverage coverage("gameclient_renderable",(uintptr_t)gcrOld);unsigned index=0;int failures=0;unsigned groups[]={0,1,88,90,93,94,95,96,97,98,99,100,101,102,255};
 for(unsigned shadow=0;shadow<2;++shadow)for(unsigned group=0;group<15;++group)for(unsigned kind=0;kind<5;++kind){Case c={shadow,groups[group],kind,1,1,2,31};bool ok=autotest::compareCase(oldSide,newSide,&c,stats,host,"gameclient_renderable",index++,&coverage);TL_CHECK(failures,ok);if(!ok){coverage.report(host);return failures+stats.incomplete;}}
 for(unsigned casts=0;casts<2;++casts)for(unsigned state=0;state<2;++state)for(unsigned blend=0;blend<5;++blend)for(unsigned opacity=0;opacity<73;++opacity){if(!casts && opacity!=0 && opacity!=64 && opacity!=66)continue;if(casts && !state && blend!=0)continue;if(casts && state && blend==4 && opacity>=3)continue;Case c={1,90,4,casts,state,blend,opacity};bool ok=autotest::compareCase(oldSide,newSide,&c,stats,host,"gameclient_renderable",index++,&coverage);TL_CHECK(failures,ok);if(!ok){coverage.report(host);return failures+stats.incomplete;}}
 coverage.report(host);sub->setUserAny(Ogre::Any());scene->destroyEntity(entity);return failures+stats.incomplete+(coverage.completed!=index);
}
}
TL_TEST(gameclient_renderable){return systems_fixture::isolated(&worker,host);}
