#include <string>
#include <vector>
#include <map>
#include <set>
#include <new>
#include <OgrePrerequisites.h>
#define private public
#define protected public
#include "Character.h"
#include "GenericModel.h"
#include "Particle.h"
#include "UnitTheme.h"
#include <OgreBone.h>
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldCharacterBones,(CCharacter*),"_ZN10CCharacter19updateBonePositionsEv")
extern "C" void newCharacterBones(CCharacter*) __asm__("_ZN10CCharacter19updateBonePositionsEv");
TL_ORIGINAL(void,oldCharacterThemeUpdate,(CCharacter*,CUnitTheme*,bool),"_ZN10CCharacter16unitThemeUpdatedEP10CUnitThemeb")
extern "C" void newCharacterThemeUpdate(CCharacter*,CUnitTheme*,bool) __asm__("_ZN10CCharacter16unitThemeUpdatedEP10CUnitThemeb");
TL_FUNCTION(cbones_create,"_ZN10CCharacter32createSpecificUnitThemeParticlesEP10CUnitTheme")
TL_FUNCTION(cbones_start,"_ZN9CParticle5StartEv")
TL_FUNCTION(cbones_stop,"_ZN9CParticle4StopEb")
TL_FUNCTION(cbones_position,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(cbones_setPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
namespace {
struct Case{unsigned mode,index;};struct State{Case c;autotest::Capture*out;CCharacter*self;CGenericModel*model;Ogre::Bone*bones[15];Ogre::SceneNode*nodes[15];CParticle*particles[8];CUnitTheme*theme,*otherTheme;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned v){active->out->add(&v,4);}void fp(float v){active->out->add(&v,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void quat(const Ogre::Quaternion&q){fp(q.w);fp(q.x);fp(q.y);fp(q.z);}unsigned id(const void*p){if(!p)return 0;if(p==active->self)return 1;if(p==active->model)return 2;if(p==active->theme)return 3;if(p==active->otherTheme)return 4;for(unsigned i=0;i<15;++i){if(p==active->bones[i])return 200+i;if(p==active->nodes[i])return 300+i;}for(unsigned i=0;i<8;++i)if(p==active->particles[i])return 100+i;return 999;}
Ogre::Vector3 position(CPositionableObject*p,bool absolute){num(1);num(id(p));num(absolute);return p->m_vPosition;}
void particlePosition(CPositionableObject*p,const Ogre::Vector3&v){num(2);num(id(p));vec(v);p->m_vPosition=v;}
void nodePosition(Ogre::Node*p,const Ogre::Vector3&v){num(3);num(id(p));vec(v);p->mPosition=v;}
void nodeOrientation(Ogre::Node*p,const Ogre::Quaternion&q){num(4);num(id(p));quat(q);p->mOrientation=q;}
const Ogre::Vector3&derivedPosition(const Ogre::Node*p){num(5);num(id(p));return p->mDerivedPosition;}
const Ogre::Quaternion&derivedOrientation(const Ogre::Node*p){num(6);num(id(p));return p->mDerivedOrientation;}
const Ogre::Matrix4&orientation(CCharacter*p){num(7);return p->m_mOrientation;}
void create(CCharacter*,CUnitTheme*t){num(8);num(id(t));}
void start(CParticle*p){num(9);num(id(p));p->m_bVisible=true;}
void stop(CParticle*p,bool flag){num(10);num(id(p));num(flag);p->m_bVisible=false;}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;active=&s;s.c=c;s.out=&out;
 s.self=static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));s.model=static_cast<CGenericModel*>(autotest::allocate(sizeof(CGenericModel)));s.self->m_pUnitModel=s.model;s.theme=static_cast<CUnitTheme*>(autotest::allocate(sizeof(CUnitTheme)));s.otherTheme=static_cast<CUnitTheme*>(autotest::allocate(sizeof(CUnitTheme)));s.model->m_vPosition=Ogre::Vector3(-2,3.5f,8);s.self->m_vPosition=Ogre::Vector3(4,10,-7);
 void**ct=static_cast<void**>(autotest::allocate(0x500));ct[0xe8/8]=reinterpret_cast<void*>(&orientation);*reinterpret_cast<void***>(s.self)=ct;
 s.self->m_mOrientation=Ogre::Matrix4(1.25f,.25f,-.5f,3, -.75f,2,.5f,-2, .125f,.75f,1.5f,1, 0,0,0,c.index%2?.5f:1.0f);
 void**nt=static_cast<void**>(autotest::allocate(0x220));nt[0xd0/8]=reinterpret_cast<void*>(&nodeOrientation);nt[0xe8/8]=reinterpret_cast<void*>(&nodePosition);nt[0x1f8/8]=reinterpret_cast<void*>(&derivedOrientation);nt[0x200/8]=reinterpret_cast<void*>(&derivedPosition);
 for(unsigned i=0;i<15;++i){s.bones[i]=static_cast<Ogre::Bone*>(autotest::allocate(sizeof(Ogre::Bone)));s.nodes[i]=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));*reinterpret_cast<void***>(s.bones[i])=nt;*reinterpret_cast<void***>(s.nodes[i])=nt;s.bones[i]->mDerivedPosition=Ogre::Vector3(float(i)*.5f,-float(i),float(i%3)*.25f);s.bones[i]->mDerivedOrientation=Ogre::Quaternion(.25f*float(i+1),.5f,-.75f,1);s.nodes[i]->mPosition=Ogre::Vector3(-99,-99,-99);s.nodes[i]->mOrientation=Ogre::Quaternion(1,0,0,0);}
 Ogre::SceneNode**nodes[]={&s.self->m_pRightHandNode,&s.self->m_fishingNode,&s.self->m_pLeftHandNode,&s.self->m_pShieldNode,&s.self->m_pRightShoulderNode,&s.self->m_pLeftShoulderNode,&s.self->m_pHeadNode};Ogre::Bone**bones[]={&s.self->m_rightHandBone,&s.self->m_fishingBone,&s.self->m_leftHandBone,&s.self->m_shieldBone,&s.self->m_leftShoulderBone,&s.self->m_rightShoulderBone,&s.self->m_headBone};
 for(unsigned i=0;i<7;++i){*nodes[i]=(hash(10+i)&1)?s.nodes[i]:NULL;*bones[i]=s.bones[i];}
 new(&s.self->m_particleTriggers)TArrayList<CCharacter::CParticleAnimationTrigger*>;
 for(unsigned i=0;i<8;++i){s.particles[i]=static_cast<CParticle*>(autotest::allocate(sizeof(CParticle)));s.particles[i]->m_vPosition=Ogre::Vector3(-88,-88,-88);s.particles[i]->m_bVisible=hash(90+i)&1;CCharacter::CParticleAnimationTrigger*t=new CCharacter::CParticleAnimationTrigger;t->m_theme=hash(80+i)%3==0?NULL:hash(80+i)%3==1?s.theme:s.otherTheme;t->m_node=hash(30+i)&1?s.nodes[7+i]:NULL;t->m_nodeOwner=hash(40+i)&1?s.bones[7+i]:NULL;t->m_stopWhenHidden=hash(50+i)&1;t->m_stopFlag59=hash(60+i)&1;t->m_particle=hash(70+i)&1?s.particles[i]:NULL;t->m_offset=Ogre::Vector3(float(i)*.25f,-.5f,.75f);s.self->m_particleTriggers.add(t);}
 if(c.mode==0)autotest::invoke(out,ours?newCharacterBones:oldCharacterBones,s.self);else autotest::invoke(out,ours?newCharacterThemeUpdate:oldCharacterThemeUpdate,s.self,hash(100)%7?s.theme:static_cast<CUnitTheme*>(NULL),bool(c.index&1));
 for(unsigned i=0;i<15;++i){vec(s.nodes[i]->mPosition);quat(s.nodes[i]->mOrientation);}for(unsigned i=0;i<8;++i){vec(s.particles[i]->m_vPosition);num(s.particles[i]->m_bVisible);}
 for(unsigned i=0;i<s.self->m_particleTriggers.size();++i){CCharacter::CParticleAnimationTrigger*t=s.self->m_particleTriggers[i];t->m_name.~basic_string();t->CRunicCore::~CRunicCore();Ogre::NedAllocImpl::deallocBytes(t);}s.self->m_particleTriggers.~TArrayList();
}
void before(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void after(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
}
namespace { int run(const tlhybrid_host*host,unsigned mode,const char*name,uintptr_t address){detour::Set hooks;TL_REDIRECT(hooks,cbones_create,&create);TL_REDIRECT(hooks,cbones_start,&start);TL_REDIRECT(hooks,cbones_stop,&stop);TL_REDIRECT(hooks,cbones_position,&position);TL_REDIRECT(hooks,cbones_setPosition,&particlePosition);if(hooks.failed())return 1;autotest::Coverage coverage(name,address);for(unsigned i=0;i<2048;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    character bones seed%u exits%d/%d bytes%lu/%lu\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);unsigned k=0;while(k*4<a.capture.length&&k*4<b.capture.length){unsigned x,y;std::memcpy(&x,a.capture.data+k*4,4);std::memcpy(&y,b.capture.data+k*4,4);if(x!=y){host->log("    first word%u %08x/%08x\n",k,x,y);break;}++k;}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=2048||coverage.different||coverage.missing;}

}
TL_TEST(all_character_bone_positions){return run(host,0,"all_character_bone_positions",0x822fb0);}
TL_TEST(all_character_unit_theme_update){return run(host,1,"all_character_unit_theme_update",0x830800);}
