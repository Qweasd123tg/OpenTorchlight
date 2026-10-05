#include <cstring>
#include <new>
#include <stdexcept>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "Particle.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalDetach,(CEquipment*),"_ZN10CEquipment18detachFromLocationEv")
TL_FUNCTION(dtStop,"_ZN9CParticle4StopEb")
TL_FUNCTION(dtPaper,"_ZN10CCharacter16setPaperdollItemE16EEQUIP_LOCATIONSPN4Ogre6EntityE")
TL_FUNCTION(dtSecond,"_ZN10CCharacter25setPaperdollItemSecondaryE16EEQUIP_LOCATIONSPN4Ogre6EntityE")
extern "C" char dtBone[] __asm__("_ZN4Ogre6Entity20detachObjectFromBoneEPNS_13MovableObjectE");
namespace {
typedef char primary_offset[__builtin_offsetof(CCharacter,m_PaperdollItems)==0x560?1:-1];
typedef char secondary_offset[__builtin_offsetof(CCharacter,m_PaperdollItemsSecondary)==0x5c0?1:-1];
typedef char character_size[sizeof(CCharacter)==0x720?1:-1];
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T*get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned n,flags,mode,slot;};const Case*input;autotest::Capture*capture;
void number(int n){capture->add(&n,sizeof(n));}
struct World;World*world;
struct World{
 Raw<CEquipment>item;Raw<CCharacter>actors[2];Raw<CGenericModel>models[4];Raw<CParticle>particles[2];Raw<Ogre::Entity>entities[51];void*actorTable[96];Ogre::SceneNode*nodes[8];unsigned boneCalls;
 World():boneCalls(0){std::memset(actorTable,0,sizeof(actorTable));for(unsigned i=0;i<8;++i)nodes[i]=new Ogre::SceneNode(NULL);}
 ~World(){for(unsigned i=0;i<8;++i)delete nodes[i];}
 int actorID(CCharacter*p){return p==actors[0].get()?0:p==actors[1].get()?1:-1;}
 int entityID(const Ogre::MovableObject*p){for(unsigned i=0;i<51;++i)if(p==entities[i].get())return i;return -1;}
 int nodeID(const Ogre::Node*p){for(unsigned i=0;i<8;++i)if(p==nodes[i])return i;return -1;}
};
void*model(CCharacter*p){number(10);number(world->actorID(p));if(input->mode==1)world->item.get()->m_pEquippedTo=world->actors[1].get();return p->m_pUnitModel;}
void stop(CParticle*p,bool immediate){number(11);number(p==world->particles[0].get()?0:1);number(immediate);if(input->mode==2)world->item.get()->m_pParticle=world->particles[1].get();}
void bone(Ogre::Entity*p,Ogre::MovableObject*object){number(12);number(world->entityID(p));number(world->entityID(object));++world->boneCalls;if(input->mode==3||input->mode==5){world->item.get()->m_pEquippedTo=world->actors[1].get();world->item.get()->m_iUnknown298=(input->slot+1)%12;}if(input->mode==4||input->mode==5)throw std::runtime_error("bone");}
void paper(CCharacter*p,EEQUIP_LOCATIONS slot,Ogre::Entity*e){number(13);number(world->actorID(p));number(slot);number(world->entityID(e));p->m_PaperdollItems[slot]=e;if(input->mode==6){world->item.get()->m_pEquippedTo=world->actors[1].get();world->item.get()->m_iUnknown298=(input->slot+2)%12;}}
void second(CCharacter*p,EEQUIP_LOCATIONS slot,Ogre::Entity*e){number(14);number(world->actorID(p));number(slot);number(world->entityID(e));p->m_PaperdollItemsSecondary[slot]=e;}
void side(const Case&c,bool ours,autotest::Capture&out){input=&c;capture=&out;World w;world=&w;w.actorTable[0x1e0/8]=reinterpret_cast<void*>(&model);
 for(unsigned j=0;j<2;++j){*reinterpret_cast<void***>(w.actors[j].get())=w.actorTable;w.actors[j].get()->m_pUnitModel=w.models[2].get();w.actors[j].get()->m_pPaperdollModel=(c.flags&16)?w.models[3].get():NULL;for(unsigned k=0;k<12;++k){w.actors[j].get()->m_PaperdollItems[k]=(c.n+k+j)%3?w.entities[3+j*24+k].get():NULL;w.actors[j].get()->m_PaperdollItemsSecondary[k]=(c.n+k+j)%4?w.entities[15+j*24+k].get():NULL;}}
 CEquipment*p=w.item.get();p->m_pSceneNode=w.nodes[0];p->m_pEquippedTo=(c.flags&1)?NULL:w.actors[0].get();p->m_pUnitModel=(c.flags&2)?NULL:w.models[0].get();p->m_pUnitModelSecondary=(c.flags&64)?w.models[1].get():NULL;p->m_pParticle=(c.flags&128)?w.particles[0].get():NULL;p->m_iUnknown298=c.slot;
 w.models[0].get()->m_pEntity=(c.flags&4)?NULL:w.entities[0].get();w.models[2].get()->m_pEntity=(c.flags&8)?NULL:w.entities[1].get();w.models[3].get()->m_pEntity=(c.flags&32)?NULL:w.entities[2].get();
 w.models[0].get()->m_pSceneNode=w.nodes[1];w.models[1].get()->m_pSceneNode=w.nodes[2];w.particles[0].get()->m_pSceneNode=w.nodes[3];w.particles[1].get()->m_pSceneNode=w.nodes[4];
 if(c.n%2)w.nodes[5]->addChild(w.nodes[1]);w.nodes[6]->addChild(w.nodes[2]);if(c.n%3)w.nodes[5]->addChild(w.nodes[3]);if(c.n%4)w.nodes[6]->addChild(w.nodes[4]);
 detour::Set patches;TL_REDIRECT(patches,dtStop,&stop);TL_REDIRECT(patches,dtPaper,&paper);TL_REDIRECT(patches,dtSecond,&second);patches.redirect(dtBone,dtBone,&bone);if(patches.failed())_exit(42);
 for(unsigned repeat=0;repeat<2;++repeat){if(ours)p->detachFromLocation();else originalDetach(p);number(w.actorID(p->m_pEquippedTo));number(p->m_iUnknown298);number(w.boneCalls);for(unsigned j=0;j<8;++j)number(w.nodeID(w.nodes[j]->getParent()));for(unsigned j=0;j<2;++j)for(unsigned k=0;k<12;++k){number(w.entityID(w.actors[j].get()->m_PaperdollItems[k]));number(w.entityID(w.actors[j].get()->m_PaperdollItemsSecondary[k]));}}
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_detach_differential){int failures=0;for(unsigned n=0;n<3584;++n){Case c={n,n%256,0,(n/256)%12};if(n>=3072){unsigned q=n-3072;c.flags=16|64|128;c.mode=1+(q/72)%6;c.slot=q%12;}
 autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    detach case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok)return failures;}host->log("    detach: 3584 cases, two calls per side\n");return failures;}
