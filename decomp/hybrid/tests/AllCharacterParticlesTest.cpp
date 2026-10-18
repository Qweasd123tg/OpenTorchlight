#include <string>
#include <vector>
#include <map>
#include <set>
#include <new>
#define private public
#define protected public
#include "Character.h"
#include "GenericModel.h"
#include "Particle.h"
#include "UnitTheme.h"
#include "UnitThemes.h"
#include "UnitThemeParticle.h"
#include "MasterResourceManager.h"
#include "ParticlePreloader.h"
#include <OgreBone.h>
#include <OgreSkeletonInstance.h>
#include <OgreSceneManager.h>
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldCharacterConfigure,(CCharacter*,CCharacter::CParticleAnimationTrigger*,unsigned),"_ZN10CCharacter24configureParticleTriggerEPNS_25CParticleAnimationTriggerEj")
extern "C" void newCharacterConfigure(CCharacter*,CCharacter::CParticleAnimationTrigger*,unsigned) __asm__("_ZN10CCharacter24configureParticleTriggerEPNS_25CParticleAnimationTriggerEj");
TL_ORIGINAL(void,oldCharacterThemeParticles,(CCharacter*,CUnitTheme*),"_ZN10CCharacter32createSpecificUnitThemeParticlesEP10CUnitTheme")
extern "C" void newCharacterThemeParticles(CCharacter*,CUnitTheme*) __asm__("_ZN10CCharacter32createSpecificUnitThemeParticlesEP10CUnitTheme");
TL_ORIGINAL(void,oldCharacterAdditionalParticles,(CCharacter*),"_ZN10CCharacter34createAdditionalUnitThemeParticlesEv")
extern "C" void newCharacterAdditionalParticles(CCharacter*) __asm__("_ZN10CCharacter34createAdditionalUnitThemeParticlesEv");
TL_FUNCTION(cparticles_themes,"_ZN11CUnitThemes12getSingletonEv")
TL_FUNCTION(cparticles_configure,"_ZN10CCharacter24configureParticleTriggerEPNS_25CParticleAnimationTriggerEj")
TL_FUNCTION(cparticles_parent,"_ZN16CSceneNodeObject18sceneNodeSetParentEPN4Ogre9SceneNodeEb")
TL_FUNCTION(cparticles_rng,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(cparticles_singleton,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(cparticles_isa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(cparticles_name,"_ZN18CParticlePreloader25getParticleNameByFileNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cparticles_load,"_ZN18CParticlePreloader12LoadParticleESbIwSt11char_traitsIwESaIwEES3_")
TL_FUNCTION(cparticles_get,"_ZN18CParticlePreloader11GetParticleEP16CResourceManagerPKw")
TL_FUNCTION(cparticles_position,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
namespace {
struct Case{unsigned mode,index;};struct State{Case c;autotest::Capture*out;CCharacter*self;CGenericModel*model;Ogre::SkeletonInstance*skeleton;Ogre::Bone*bones[5];Ogre::SceneNode*parent,*child;CResourceManager*resources;Ogre::SceneManager*scene;CMasterResourceManager*manager;CParticlePreloader*preloader;CUnitThemes*themes;CUnitTheme*theme,*otherTheme;CParticle*particles[32];unsigned created;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned n){active->out->add(&n,4);}void fp(float n){active->out->add(&n,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void text(const std::string&v){num(v.size());active->out->add(v.data(),v.size());}void wide(const std::wstring&v){num(v.size());active->out->add(v.data(),v.size()*4);}unsigned id(const void*p){if(!p)return 0;if(p==active->self)return 1;if(p==active->model)return 2;if(p==active->parent)return 3;if(p==active->child)return 4;if(p==active->theme)return 5;if(p==active->otherTheme)return 6;for(unsigned i=0;i<5;++i)if(p==active->bones[i])return 20+i;for(unsigned i=0;i<32;++i)if(p==active->particles[i])return 100+i;return 999;}
void*model(CCharacter*){num(1);return active->c.mode==0&&hash(1)%9==0?NULL:active->model;}
unsigned short boneCount(const Ogre::Skeleton*){num(2);return hash(2)%5;}
Ogre::Bone*boneByIndex(const Ogre::Skeleton*,unsigned short i){num(3);num(i);return hash(3)%7==0?NULL:active->bones[i%5];}
Ogre::Bone*boneByName(const Ogre::Skeleton*,const std::string&name){num(4);text(name);return hash(4)%7==0?NULL:active->bones[0];}
bool hasBone(const Ogre::Skeleton*,const std::string&name){num(5);text(name);return hash(5)%3!=0;}
Ogre::SceneNode*sceneNode(Ogre::SceneManager*){num(6);return active->child;}
void addChild(Ogre::Node*,Ogre::Node*p){num(7);num(id(p));}
void parent(CSceneNodeObject*p,Ogre::SceneNode*n,bool flag){num(8);num(id(p));num(id(n));num(flag);}
float rng(float lo,float hi){num(9);fp(lo);fp(hi);return hi*float(hash(9)%3)*.5f;}
CUnitThemes*themesSingleton(){num(17);return active->themes;}
CMasterResourceManager*singleton(){num(10);return active->manager;}
bool isa(CBaseUnit*,UNITTYPES::EUNITTYPES t){num(11);num(t);return (hash(11+unsigned(t))&3)!=0;}
std::wstring particleName(CParticlePreloader*,const std::wstring&file){num(12);wide(file);return hash(12)%2?L"lookup-name":L"";}
void load(CParticlePreloader*,std::wstring file,std::wstring name){num(13);wide(file);wide(name);}
CParticle*get(CParticlePreloader*,CResourceManager*r,const wchar_t*file){num(14);num(r==active->resources);wide(file);unsigned i=active->created++;num(i);return hash(14+i)%3?active->particles[i%32]:NULL;}
void position(CPositionableObject*p,const Ogre::Vector3&v){num(15);num(id(p));vec(v);p->m_vPosition=v;}
void snapshot(CCharacter::CParticleAnimationTrigger*t){num(t->m_resources==active->resources);num(id(t->m_particle));num(t->m_stopOnDeath);num(t->m_animationIndex);vec(t->m_offset);num(id(t->m_node));text(t->m_name);num(id(t->m_nodeOwner));num(id(t->m_theme));num(t->m_stopWhenHidden);num(t->m_stopFlag59);num(t->m_stopFlag5A);}
void configure(CCharacter*p,CCharacter::CParticleAnimationTrigger*t,unsigned i){num(16);num(i);num(p->m_particleTriggers.size());snapshot(t);}
CCharacter::CParticleAnimationTrigger*trigger(){CCharacter::CParticleAnimationTrigger*t=new CCharacter::CParticleAnimationTrigger;t->m_resources=active->resources;t->m_particle=NULL;t->m_stopOnDeath=false;t->m_animationIndex=-1;t->m_offset=Ogre::Vector3::ZERO;t->m_node=NULL;t->m_nodeOwner=NULL;t->m_theme=NULL;t->m_stopWhenHidden=true;t->m_stopFlag59=false;t->m_stopFlag5A=false;return t;}
void dispose(CCharacter::CParticleAnimationTrigger*t){t->m_name.~basic_string();t->CRunicCore::~CRunicCore();Ogre::NedAllocImpl::deallocBytes(t);}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;active=&s;s.c=c;s.out=&out;s.created=0;
 s.self=static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));s.model=static_cast<CGenericModel*>(autotest::allocate(sizeof(CGenericModel)));s.skeleton=static_cast<Ogre::SkeletonInstance*>(autotest::allocate(sizeof(Ogre::SkeletonInstance)));s.resources=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));s.scene=static_cast<Ogre::SceneManager*>(autotest::allocate(sizeof(Ogre::SceneManager)));s.resources->m_pSceneManager=s.scene;s.self->m_pResourceManager=s.resources;s.model->m_pSkeleton=c.mode>0||hash(17)%7?s.skeleton:NULL;s.self->m_pUnitModel=hash(18)%11?s.model:NULL;
 s.parent=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.child=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.self->m_pSceneNode=s.parent;
 void**ct=static_cast<void**>(autotest::allocate(0x500));ct[0x1e0/8]=reinterpret_cast<void*>(&model);*reinterpret_cast<void***>(s.self)=ct;void**st=static_cast<void**>(autotest::allocate(0x200));st[0x188/8]=reinterpret_cast<void*>(&boneCount);st[0x1a8/8]=reinterpret_cast<void*>(&boneByIndex);st[0x1b0/8]=reinterpret_cast<void*>(&boneByName);st[0x1b8/8]=reinterpret_cast<void*>(&hasBone);*reinterpret_cast<void***>(s.skeleton)=st;
 void**nt=static_cast<void**>(autotest::allocate(0x220));nt[0x1a8/8]=reinterpret_cast<void*>(&addChild);*reinterpret_cast<void***>(s.parent)=nt;void**mt=static_cast<void**>(autotest::allocate(0x240));mt[0x230/8]=reinterpret_cast<void*>(&sceneNode);*reinterpret_cast<void***>(s.scene)=mt;
 for(unsigned i=0;i<5;++i){s.bones[i]=static_cast<Ogre::Bone*>(autotest::allocate(sizeof(Ogre::Bone)));new(&s.bones[i]->mName)std::string(i==0?"HAND":"BONE");}for(unsigned i=0;i<32;++i)s.particles[i]=static_cast<CParticle*>(autotest::allocate(sizeof(CParticle)));
 s.manager=static_cast<CMasterResourceManager*>(autotest::allocate(sizeof(CMasterResourceManager)));s.preloader=static_cast<CParticlePreloader*>(autotest::allocate(sizeof(CParticlePreloader)));s.manager->m_pParticlePreloader=s.preloader;
 s.theme=static_cast<CUnitTheme*>(autotest::allocate(sizeof(CUnitTheme)));s.otherTheme=static_cast<CUnitTheme*>(autotest::allocate(sizeof(CUnitTheme)));new(&s.theme->m_particles)TArrayList<CUnitThemeParticle*>;new(&s.otherTheme->m_particles)TArrayList<CUnitThemeParticle*>;s.themes=static_cast<CUnitThemes*>(autotest::allocate(sizeof(CUnitThemes)));new(&s.themes->m_Themes)TArrayList<CUnitTheme*>;s.themes->m_Themes.add(s.theme);s.themes->m_Themes.add(s.otherTheme);if(hash(74)%2)s.themes->m_Themes.add(s.theme);new(&s.self->m_particleTriggers)TArrayList<CCharacter::CParticleAnimationTrigger*>(10);
 if(c.mode==0){CCharacter::CParticleAnimationTrigger*t=trigger();const char*names[]={"","Random","Every Bone","HAND","NOPE"};t->m_name=names[c.index%5];t->m_particle=s.particles[0];t->m_stopWhenHidden=c.index&1;t->m_nodeOwner=s.bones[4];t->m_node=s.child;typedef void(*F)(CCharacter*,CCharacter::CParticleAnimationTrigger*,unsigned);F f=ours?newCharacterConfigure:oldCharacterConfigure;if(!autotest::beginInvocation(out,f))return;f(s.self,hash(19)%13==0?NULL:t,hash(20)%5);out.callCompleted=1;snapshot(t);dispose(t);}
 else {for(unsigned i=0;i<3;++i){CUnitThemeParticle*d=static_cast<CUnitThemeParticle*>(autotest::allocate(sizeof(CUnitThemeParticle)));new(&d->m_wstrFile)std::wstring(i==0?L"fx/fire":i==1?L"fx/smoke":L"FX/Spark");new(&d->m_wstrBone)std::wstring(hash(30+i)%4==0?L"Every Bone":hash(30+i)%4==1?L"Random":L"HAND");d->m_iCount=hash(40+i)%4;d->m_iUnitTypeID=i+20;d->m_bAttaches=hash(50+i)&1;d->m_bFollows=hash(60+i)&1;s.theme->m_particles.add(d);s.otherTheme->m_particles.add(d);}
 if(hash(70)%3==0){CCharacter::CParticleAnimationTrigger*t=trigger();t->m_theme=hash(71)%2?s.theme:s.otherTheme;t->m_particle=hash(72)%2?s.particles[31]:NULL;s.self->m_particleTriggers.add(t);}
 if(c.mode==1){typedef void(*F)(CCharacter*,CUnitTheme*);F f=ours?newCharacterThemeParticles:oldCharacterThemeParticles;if(!autotest::beginInvocation(out,f))return;f(s.self,hash(73)%17? s.theme:NULL);out.callCompleted=1;}else autotest::invoke(out,ours?newCharacterAdditionalParticles:oldCharacterAdditionalParticles,s.self);num(s.self->m_particleTriggers.size());num(s.self->m_particleTriggers.m_nCapacity);num(s.created);for(unsigned i=0;i<s.self->m_particleTriggers.size();++i){snapshot(s.self->m_particleTriggers[i]);dispose(s.self->m_particleTriggers[i]);}for(unsigned i=0;i<s.theme->m_particles.size();++i){s.theme->m_particles[i]->m_wstrFile.~basic_string();s.theme->m_particles[i]->m_wstrBone.~basic_string();}}
 s.themes->m_Themes.~TArrayList();s.otherTheme->m_particles.~TArrayList();s.theme->m_particles.~TArrayList();s.self->m_particleTriggers.~TArrayList();for(unsigned i=0;i<5;++i)s.bones[i]->mName.~basic_string();
}
void before(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void after(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host*host,unsigned mode,const char*name,unsigned long long address){detour::Set hooks;TL_REDIRECT(hooks,cparticles_themes,&themesSingleton);TL_REDIRECT(hooks,cparticles_parent,&parent);TL_REDIRECT(hooks,cparticles_rng,&rng);TL_REDIRECT(hooks,cparticles_singleton,&singleton);TL_REDIRECT(hooks,cparticles_isa,&isa);TL_REDIRECT(hooks,cparticles_name,&particleName);TL_REDIRECT(hooks,cparticles_load,&load);TL_REDIRECT(hooks,cparticles_get,&get);TL_REDIRECT(hooks,cparticles_position,&position);if(mode)TL_REDIRECT(hooks,cparticles_configure,&configure);if(hooks.failed())return 1;autotest::Coverage coverage(name,address);for(unsigned i=0;i<2048;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    particle mode%u seed%u exits%d/%d issue%u/%u bytes%lu/%lu\n",mode,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);unsigned k=0;while(k*4<a.capture.length&&k*4<b.capture.length){unsigned x,y;std::memcpy(&x,a.capture.data+k*4,4);std::memcpy(&y,b.capture.data+k*4,4);if(x!=y){host->log("    first word%u %08x/%08x\n",k,x,y);break;}++k;}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=2048||coverage.different||coverage.missing;}
}
TL_TEST(all_character_particle_configure){return run(host,0,"all_character_particle_configure",0x82e210);}
TL_TEST(all_character_theme_particles){return run(host,1,"all_character_theme_particles",0x8300f0);}

TL_TEST(all_character_additional_particles){return run(host,2,"all_character_additional_particles",0x834c40);}
