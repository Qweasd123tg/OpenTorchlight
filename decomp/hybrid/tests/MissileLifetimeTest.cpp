#include "AutoTest.h"
#include <Ogre.h>
#include <stdexcept>
#define private public
#define protected public
#include "Missile.h"
#include "Path.h"
#include "ParticlePreloader.h"
#include "iMissile.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"
#include "tests/SmallMassCompare.h"
#include "tests/SystemsFixtureWorker.h"
#define DECL(N,A,S) TL_ORIGINAL(void,mlOld##N,A,S) extern "C" void mlNew##N A __asm__(S);
DECL(Ctor,(CMissile*,CResourceManager*),"_ZN8CMissileC1EP16CResourceManager")
DECL(Copy,(CMissile*,CResourceManager*,const CMissile*),"_ZN8CMissileC1EP16CResourceManagerPKS_")
DECL(Dtor,(CMissile*),"_ZN8CMissileD1Ev")
#undef DECL
TL_FUNCTION(mlLoad,"_ZN18CParticlePreloader12LoadParticleESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(mlGet,"_ZN18CParticlePreloader11GetParticleEP16CResourceManagerPKw")
TL_FUNCTION(mlStop,"_ZN9CParticle4StopEb")
namespace {
#include "tests/CharacterEmptyGlobals.h"
nativegame::Services*services;autotest::Capture*output;bool armed;unsigned seed,operation,loads;bool unwindMode;CCharacter*owner;CParticlePreloader*preloader;CResourceManager*resources;CMissile*constructing;
void number(unsigned n){if(armed)output->add(&n,4);}
void scalar(float f){if(armed)output->add(&f,4);}
void vector(const Ogre::Vector3&v){scalar(v.x);scalar(v.y);scalar(v.z);}
void text(const std::wstring&s){number(s.size());if(armed)output->add(s.data(),s.size()*sizeof(wchar_t));}
struct Particle:CParticle{unsigned id;Particle(CResourceManager*r,unsigned n):CParticle(NULL,L"fixture",r),id(n){}virtual ~Particle(){number(11);number(id);}};
void load(CParticlePreloader*p,std::wstring file){number(1);number(p==preloader);text(file);number(constructing->m_owner.getObject()==owner);++loads;if(seed&64)throw std::runtime_error("missile copy load failure");}
CParticle*get(CParticlePreloader*p,CResourceManager*r,const wchar_t*file){number(2);number(p==preloader);number(r==resources);text(file);return seed&128?NULL:new Particle(r,21+loads);}
void stop(CParticle*p,bool immediate){number(3);number(static_cast<Particle*>(p)->id);number(immediate);}
unsigned references(CRunicCore*p){return p->m_pSafePointers?p->m_pSafePointers->size():0;}
void state(CMissile*m,bool copy){
 number(m->m_pResourceManager==resources);number(m->m_pSceneNode!=NULL);vector(m->m_vPosition);number(m->m_bVisible);number(m->m_bEnabled);
 for(unsigned i=0;i<4;++i){text(m->m_particleFiles[i]);number(m->m_particles[i]?static_cast<Particle*>(m->m_particles[i])->id:0);}
 number(m->m_bStartAtFullVelocity);number(m->m_bUnknown141);number(m->m_bPiercing);number(m->m_bCanVerticalAim);if(!copy)number(m->m_bUnknown144);
 vector(m->m_resetVector148);scalar(m->m_fForceAppliedPerSecond);scalar(m->m_fMaxVelocity);scalar(m->m_fFriction);scalar(m->m_fAOERadius);number(m->m_iUnknown164);number(m->m_iUnknown168);scalar(m->m_fUnknown16C);scalar(m->m_fUnknown170);scalar(m->m_fUnknown174);scalar(m->m_fRadiusOfMissile);number(m->m_iUnknown17C);number(m->m_iNumberOfRicochets);number(m->m_bUnknown184);number(m->m_bUnknown185);number(m->m_bTargetsPosition);number(m->m_bCollidesWithObjects);number(m->m_bTrackGround);vector(m->m_targetPosition);scalar(m->m_fUnknown198);scalar(m->m_fMissileArchHeight);vector(m->m_resetVector1A0);scalar(m->m_fLifetime);scalar(m->m_fLifetimeRemaining);scalar(m->m_fUnknown1B4);scalar(m->m_fDistanceAllowedToTraveled);scalar(m->m_fUnknown1BC);scalar(m->m_fUnknown1C0);scalar(m->m_iUnknown1C4);
 number(m->m_Listeners.size());number(m->m_Listeners.m_nGrowBy);number(m->m_sceneNodes.size());number(m->m_sceneNodes.m_nGrowBy);number(m->m_iUnknown208);number(m->m_pPath!=NULL);scalar(m->m_fUnknown218);number(m->m_owner.getObject()==owner);number(m->m_owner.m_nIndex);number(m->m_target.getObject()!=NULL);number(m->m_target.m_nIndex);number(m->m_targetCharacter.getObject()!=NULL);number(m->m_targetCharacter.m_nIndex);scalar(m->m_fTargetHomingValue);scalar(m->m_fHomeAfterXSeconds);scalar(m->m_fUnknown258);scalar(m->m_fUnknown25C);scalar(m->m_fTargetingAngle);scalar(m->m_fMaxTurnRate);scalar(m->m_fTurnAcceleration);scalar(m->m_fRandomizedTurnAcceleration);scalar(m->m_fRandomizedTurnUpdate);scalar(m->m_fUnknown274);if(!copy)scalar(m->m_fUnknown278);scalar(m->m_fAOEDamageScale);scalar(m->m_fSoakScale);scalar(m->m_fInherentMinDMGPercent);scalar(m->m_fInherentMaxDMGPercent);scalar(m->m_fInherentKnockback);scalar(m->m_fUnknown290);number(m->m_bUnknown294);number(m->m_collisionUnits.size());number(m->m_collisionUnits.m_nGrowBy);number(m->m_collisionStates.size());number(m->m_collisionStates.m_nGrowBy);text(m->m_sMissileName);number(m->m_iDamageType);
}
CMissile*allocate(){CMissile*m=static_cast<CMissile*>(Ogre::NedAllocImpl::allocBytes(sizeof(CMissile),0,0,0));std::memset(m,0x5a,sizeof(CMissile));return m;}
void release(CMissile*m){mlOldDtor(m);Ogre::NedAllocImpl::deallocBytes(m);}
void lifetimeSide(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;armed=false;seed=c.index;if(operation==1&&!unwindMode)seed=seed%64+128*(seed/64);loads=0;owner=NULL;CResourceManager actualResources(services->scene);resources=operation==0&&seed&1?NULL:&actualResources;CParticlePreloader actualPreloader(NULL);preloader=&actualPreloader;CParticlePreloader*saved=services->master->m_pParticlePreloader;services->master->m_pParticlePreloader=preloader;
 CMissile*source=NULL;
 if(operation){source=allocate();mlOldCtor(source,resources);owner=new CCharacter(NULL);if(seed&1)source->m_owner.setObject(owner);source->setPosition(Ogre::Vector3(seed%7+.25f,-float(seed%5),float(seed%11)));source->m_iDamageType=seed%9;source->m_fMissileArchHeight=seed*.03f;source->m_bTargetsPosition=seed&2;source->m_bCollidesWithObjects=seed&4;source->m_bTrackGround=seed&8;source->m_fTargetingAngle=seed*.07f;source->m_fUnknown16C=seed*.1f;source->m_fForceAppliedPerSecond=seed*.2f;source->m_fMaxVelocity=seed*.3f;source->m_fAOEDamageScale=seed*.4f;source->m_fSoakScale=seed*.5f;source->m_bStartAtFullVelocity=seed&16;source->m_iNumberOfRicochets=seed%8;source->m_fRadiusOfMissile=seed*.04f;source->m_fFriction=seed*.06f;source->m_fLifetime=seed*.08f;source->m_fDistanceAllowedToTraveled=seed*.09f;source->m_fAOERadius=seed*.11f;source->m_bPiercing=seed&32;source->m_bCanVerticalAim=seed&16;source->m_fMaxTurnRate=seed*.12f;source->m_fTurnAcceleration=seed*.13f;source->m_fRandomizedTurnAcceleration=seed*.14f;source->m_fRandomizedTurnUpdate=seed*.15f;source->m_fInherentMinDMGPercent=seed*.16f;source->m_fInherentMaxDMGPercent=seed*.17f;source->m_fInherentKnockback=seed*.18f;source->m_fTargetHomingValue=seed*.19f;source->m_sMissileName=L"copy_\x416";source->m_fHomeAfterXSeconds=seed*.21f;for(unsigned i=0;i<4;++i)if(seed&(1u<<(i+1))){source->m_particles[i]=new Particle(resources,i+1);source->m_particleFiles[i]=i%2?L"SECOND.PARTICLE":L"FIRST.PARTICLE";}}
 CMissile*m=operation==2?source:allocate();constructing=m;unsigned beforeCount=g_iTotalCountOfObjects;unsigned beforeNodes=services->scene->getRootSceneNode()->numChildren();
 detour::Set hooks;TL_REDIRECT(hooks,mlLoad,&load);TL_REDIRECT(hooks,mlGet,&get);TL_REDIRECT(hooks,mlStop,&stop);if(hooks.failed())std::abort();
 if(operation<2){armed=true;bool thrown=false;try{if(operation==0){typedef void(*Fn)(CMissile*,CResourceManager*);Fn fn=ours?mlNewCtor:mlOldCtor;if(!autotest::beginInvocation(out,fn))return;fn(m,resources);}else{typedef void(*Fn)(CMissile*,CResourceManager*,const CMissile*);Fn fn=ours?mlNewCopy:mlOldCopy;if(!autotest::beginInvocation(out,fn))return;fn(m,resources,source);}}catch(const std::runtime_error&e){thrown=true;text(std::wstring(e.what(),e.what()+std::strlen(e.what())));}out.callCompleted=thrown?0:1;number(thrown);number(g_iTotalCountOfObjects-beforeCount);number(services->scene->getRootSceneNode()->numChildren()-beforeNodes);if(owner)number(references(owner));if(!thrown)state(m,operation==1);armed=false;hooks.restore();if(!thrown)release(m);else Ogre::NedAllocImpl::deallocBytes(m);}
 else {
  unsigned count=seed%5;std::vector<std::string>nodeNames,entityNames;
  for(unsigned i=0;i<count;++i){Ogre::SceneNode*node=services->scene->createSceneNode();std::string name="missile-life-"+Ogre::StringConverter::toString(i);Ogre::Entity*entity=services->scene->createEntity(name,"missile-lifetime-mesh");node->attachObject(entity);if((seed+i)&1)services->scene->getRootSceneNode()->addChild(node);m->m_sceneNodes.add(node);nodeNames.push_back(node->getName());entityNames.push_back(name);m->m_collisionUnits.add(owner);m->m_collisionStates.add(i&1);}
  if(seed&4)m->m_pPath=new CPath("lifetime",false,Ogre::Vector3::ZERO);m->m_target.setObject(owner);m->m_targetCharacter.setObject(owner);if(seed&8)m->m_Listeners.add(static_cast<iMissile*>(owner));TSafePointer<CPath>weakPath;weakPath.setObject(m->m_pPath);TSafePointer<CMissile>weak;weak.setObject(m);beforeCount=g_iTotalCountOfObjects;armed=true;typedef void(*Fn)(CMissile*);Fn fn=ours?mlNewDtor:mlOldDtor;if(!autotest::beginInvocation(out,fn))return;fn(m);out.callCompleted=1;number(g_iTotalCountOfObjects-beforeCount);number(weak.getObject()==NULL);number(weak.m_nIndex);number(weakPath.getObject()==NULL);number(weakPath.m_nIndex);number(references(owner));for(unsigned i=0;i<count;++i){number(services->scene->hasEntity(entityNames[i]));number(services->scene->hasSceneNode(nodeNames[i]));}armed=false;hooks.restore();if(weakPath.getObject())delete weakPath.getObject();Ogre::NedAllocImpl::deallocBytes(m);source=NULL;
 }
 if(source)release(source);delete owner;services->master->m_pParticlePreloader=saved;
}
void unwindBefore(void*p,autotest::Capture&o){lifetimeSide(*static_cast<smallmass::Case*>(p),false,o);}
void unwindAfter(void*p,autotest::Capture&o){lifetimeSide(*static_cast<smallmass::Case*>(p),true,o);}
int unwindRegression(const tlhybrid_host*host){int failures=0;for(unsigned i=0;i<32;++i){smallmass::Case c={1,64u|2u|(i&1u)|((i/2%8)<<2)|((i/16)<<7)};autotest::Outcome a,b;autotest::runChild(unwindBefore,&c,a);autotest::runChild(unwindAfter,&c,b);bool ok=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.issue==autotest::Capture::Complete&&b.capture.issue==autotest::Capture::Complete&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,ok);if(!ok){host->log("    supplemental unwind%u reports%u/%u status%d/%d started%u/%u returned%u/%u bytes%lu/%lu\n",i,a.reportValid,b.reportValid,a.status,b.status,a.capture.callStarted,b.capture.callStarted,a.capture.callCompleted,b.capture.callCompleted,(unsigned long)a.capture.length,(unsigned long)b.capture.length);return failures;}}host->log("    32 expected constructor unwinds: cleanup regression only; no acceptance coverage\n");return failures;}
int worker(const tlhybrid_host*host){initEmptyGlobals();nativegame::Services native;if(!native.ready())return 1;services=&native;Ogre::SceneManager*old=native.master->m_pSceneManager;native.master->m_pSceneManager=native.scene;for(unsigned i=0;i<2;++i){void*p=NULL;void*a=reinterpret_cast<void*>(0x14a4320+8*i);std::memcpy(&p,a,8);if(!p){if(i)new(a)std::wstring;else new(a)std::string;}}
 Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().create("missile-lifetime-material","General");material->removeAllTechniques();Ogre::MeshPtr mesh=Ogre::MeshManager::getSingleton().createManual("missile-lifetime-mesh","General");mesh->_setBounds(Ogre::AxisAlignedBox(-1,-1,-1,1,1,1),false);mesh->createSubMesh()->setMaterialName(material->getName());if(unwindMode){int result=unwindRegression(host);native.master->m_pSceneManager=old;return result;}const char*names[]={"missile_constructor_native","missile_copy_native","missile_destructor_native"};unsigned addresses[]={0xd05fb0,0xd06250,0xd05ad0};int result=smallmass::run(host,operation,names[operation],addresses[operation],&lifetimeSide,operation==0?64:256);native.master->m_pSceneManager=old;return result;}
}
TL_TEST(missile_constructor_native){operation=0;unwindMode=false;return systems_fixture::isolated(&worker,host);}
TL_TEST(missile_copy_native){operation=1;unwindMode=false;return systems_fixture::isolated(&worker,host);}
TL_TEST(missile_destructor_native){operation=2;unwindMode=false;return systems_fixture::isolated(&worker,host);}

TL_TEST(missile_copy_unwind_regression){operation=1;unwindMode=true;return systems_fixture::isolated(&worker,host);}
