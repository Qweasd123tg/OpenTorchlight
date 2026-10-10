#include <cstring>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "Particle.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalActive,(CEquipment*,bool),"_ZN10CEquipment16setActiveInLevelEb")
TL_FUNCTION(acDetach,"_ZN10CEquipment18detachFromLocationEv")
TL_FUNCTION(acBounds,"_ZN9CBaseUnit19updateCullingBoundsEv")
TL_FUNCTION(acParticles,"_ZN10CEquipment15createParticlesEv")
TL_FUNCTION(acSnap,"_ZN5CItem12snapToGroundEv")
TL_FUNCTION(acHide,"_ZN5CItem12hideItemTextEv")
TL_FUNCTION(acStop,"_ZN9CParticle4StopEb")
TL_FUNCTION(acStart,"_ZN9CParticle5StartEv")
TL_FUNCTION(acParent,"_ZN16CSceneNodeObject18sceneNodeSetParentEPN4Ogre9SceneNodeEb")
TL_FUNCTION(acPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
extern "C" void tracedoriginalActive(CEquipment*,bool) __asm__("_ZN10CEquipment16setActiveInLevelEb");
namespace {
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T*get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned n,flags,mode;};const Case*input;autotest::Capture*capture;
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}
struct World;World*world;
struct World{Raw<CEquipment>item;Raw<CGenericModel>models[2];Raw<CParticle>particles[3];Ogre::SceneNode*nodes[7];void*table[112];
 World(){std::memset(table,0,sizeof(table));*reinterpret_cast<void***>(item.get())=table;for(unsigned i=0;i<7;++i)nodes[i]=new Ogre::SceneNode(NULL);for(unsigned i=0;i<2;++i)models[i].get()->m_pSceneNode=nodes[i];for(unsigned i=0;i<3;++i){particles[i].get()->m_pSceneNode=nodes[i+2];nodes[i+2]->setPosition(Ogre::Vector3(3+i,5+i,7+i));if((input->n+i)%2)nodes[5]->addChild(nodes[i+2]);}}
 ~World(){for(unsigned i=0;i<7;++i)delete nodes[i];}
 int particle(const void*p){for(unsigned i=0;i<3;++i)if(p==particles[i].get())return i;return -1;}
 int node(const Ogre::Node*p){for(unsigned i=0;i<7;++i)if(p==nodes[i])return i;return -1;}
};
void detach(CEquipment*p){number(10);number(p==world->item.get());p->m_pEquippedTo=NULL;}
void visible(CEquipment*p,bool a,bool immediate){number(11);number(p==world->item.get());number(a);number(immediate);if(input->mode==1)p->m_pUnitModel=world->models[1].get();}
void bounds(CBaseUnit*p){number(12);number(p==world->item.get());if(input->mode==2)world->item.get()->m_pUnitModel=NULL;}
void particles(CEquipment*p){number(13);number(p==world->item.get());if(input->mode==3){p->m_pUnitModel=world->models[1].get();p->m_pParticle=world->particles[2].get();}if(input->mode==4)p->m_pParticle_3D0=world->particles[2].get();}
void snap(CItem*p){number(14);number(p==world->item.get());if(input->mode==5)world->item.get()->m_pUnitModel=world->models[1].get();}
void hide(CItem*p){number(15);number(p==world->item.get());}
void stop(CParticle*p,bool immediate){number(16);number(world->particle(p));number(immediate);number(world->node(p->getSceneNode()?p->getSceneNode()->getParent():NULL));if(input->mode==6)world->item.get()->m_pParticle_3D0=world->particles[2].get();}
void start(CParticle*p){number(17);number(world->particle(p));number(world->node(p->getSceneNode()?p->getSceneNode()->getParent():NULL));}
void parent(CSceneNodeObject*p,Ogre::SceneNode*n,bool keep){number(18);number(world->particle(p));number(world->node(n));number(keep);Ogre::SceneNode*node=p->getSceneNode();if(node->getParent())node->getParent()->removeChild(node);n->addChild(node);if(input->mode==7)world->item.get()->m_pParticle_3D0=world->particles[2].get();}
void position(CPositionableObject*p,const Ogre::Vector3&v){number(19);number(world->particle(p));real(v.x);real(v.y);real(v.z);if(p->getSceneNode())p->getSceneNode()->setPosition(v);if(input->mode==8)world->item.get()->m_pParticle_3D0=world->particles[2].get();}
void side(const Case&c,bool ours,autotest::Capture&out){input=&c;capture=&out;World w;world=&w;w.table[0x2c0/8]=reinterpret_cast<void*>(&visible);CEquipment*p=w.item.get();p->m_pUnitModel=c.flags&16?NULL:w.models[0].get();p->m_pParticle=c.flags&1?NULL:w.particles[0].get();p->m_pParticle_3D0=c.flags&2?NULL:w.particles[1].get();if(c.flags&4)w.particles[0].get()->m_pSceneNode=NULL;if(c.flags&8)w.particles[1].get()->m_pSceneNode=NULL;
 detour::Set patches;TL_REDIRECT(patches,acDetach,&detach);TL_REDIRECT(patches,acBounds,&bounds);TL_REDIRECT(patches,acParticles,&particles);TL_REDIRECT(patches,acSnap,&snap);TL_REDIRECT(patches,acHide,&hide);TL_REDIRECT(patches,acStop,&stop);TL_REDIRECT(patches,acStart,&start);TL_REDIRECT(patches,acParent,&parent);TL_REDIRECT(patches,acPosition,&position);if(patches.failed())_exit(42);
 for(unsigned repeat=0;repeat<2;++repeat){bool active=((c.n/32)+repeat)%2;if(repeat==0){autotest::invoke(out,ours?&tracedoriginalActive:&originalActive,p,active);}else{if(ours)p->CEquipment::setActiveInLevel(active);else originalActive(p,active);}for(unsigned i=0;i<7;++i){number(w.node(w.nodes[i]->getParent()));const Ogre::Vector3&v=w.nodes[i]->getPosition();real(v.x);real(v.y);real(v.z);}}
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_active_differential){
autotest::Coverage coverage0("equipment_active_differential",(uint64_t)(uintptr_t)&originalActive);
int failures=0;for(unsigned n=0;n<2304;++n){Case c={n,n%32,n/256};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage0.observe(host,a,b);bool ok=pair==0&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    active case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok){coverage0.report(host);return failures;}}host->log("    active: 2304 cases, activation and deactivation per side\n");{coverage0.report(host);return failures;}}
