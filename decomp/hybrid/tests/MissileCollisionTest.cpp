#include "AutoTest.h"
#include <Ogre.h>
#include <limits>
#define private public
#define protected public
#include "Missile.h"
#include "iMissile.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"
#include "tests/FinishLevelFixture.h"
#include "tests/SmallMassCompare.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(int,mcOld,(CMissile*,Ogre::Vector3,Ogre::Vector3,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,CBaseUnit**),"_ZN8CMissile14checkCollisionEN4Ogre7Vector3ES1_RS1_S2_S2_PP9CBaseUnit")
extern "C" int mcNew(CMissile*,Ogre::Vector3,Ogre::Vector3,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,CBaseUnit**) __asm__("_ZN8CMissile14checkCollisionEN4Ogre7Vector3ES1_RS1_S2_S2_PP9CBaseUnit");
TL_FUNCTION(mcSort,"_ZN6CLevel24sortForCollisionByPointsERKN4Ogre7Vector3ES3_f")
TL_FUNCTION(mcSphere,"_ZN6CLevel24preSortedSphereCollisionERKN4Ogre7Vector3ES3_fRS1_S4_S4_RjS4_PP9CBaseUnitb")
TL_FUNCTION(mcISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(mcHit,"_ZN8CMissile20handleMissileHitUnitEP9CBaseUnitN4Ogre7Vector3E")
TL_FUNCTION(mcRicochet,"_ZN8CMissile15ricochetMissileERKN4Ogre7Vector3ES3_S3_S3_")
TL_FUNCTION(mcKill,"_ZN8CMissile11killMissileEv")
TL_FUNCTION(mcAOE,"_ZN8CMissile11doAOEDamageEP9CBaseUnit")
namespace {
nativegame::Services*services;autotest::Capture*output;bool armed;unsigned seed;CMissile*missile;CLevel*level;CBaseUnit*units[4];
void number(unsigned n){if(armed)output->add(&n,4);}void scalar(float n){if(armed)output->add(&n,4);}void vector(const Ogre::Vector3&v){scalar(v.x);scalar(v.y);scalar(v.z);}
unsigned id(CBaseUnit*p){if(!p)return 0;for(unsigned i=0;i<4;++i)if(p==units[i])return i+1;return 99;}
void flags(){for(unsigned i=0;i<4;++i){number(units[i]!=NULL);if(units[i])number(units[i]->m_bBlocksPath);}number(id(missile->m_owner.getObject()));}
void sort(CLevel*p,const Ogre::Vector3&a,const Ogre::Vector3&b,float radius){number(1);number(p==level);vector(a);vector(b);scalar(radius);flags();}
bool sphere(CLevel*p,const Ogre::Vector3&a,const Ogre::Vector3&b,float radius,Ogre::Vector3&point,Ogre::Vector3&impact,Ogre::Vector3&normal,unsigned&type,Ogre::Vector3&extra,CBaseUnit**unit,bool collides){number(2);number(p==level);vector(a);vector(b);scalar(radius);number(collides);flags();point=Ogre::Vector3(3.25f,-1.5f,4.75f);impact=Ogre::Vector3(-2.5f,7.125f,-3.5f);const float heights[]={0,.2f,.20001f,1,-1,std::numeric_limits<float>::quiet_NaN()};normal=Ogre::Vector3(seed%3*.5f,heights[seed/8%6],-float(seed%5));type=seed&32?100:7;extra=Ogre::Vector3(9,8,7);*unit=seed/4%5==4?NULL:units[seed/4%5];return seed&1;}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){number(3);number(id(p));number(type);return type==25?(seed&64)!=0:type==UNITTYPES::BREAKABLE?(seed&128)!=0:false;}
bool hit(CMissile*m,CBaseUnit*p,Ogre::Vector3 direction){number(4);number(m==missile);number(id(p));vector(direction);flags();if(seed&512)m->m_owner.setObject(units[3]);return seed&16;}
Ogre::Vector3 ricochet(CMissile*m,const Ogre::Vector3&a,const Ogre::Vector3&b,const Ogre::Vector3&c,const Ogre::Vector3&d){number(5);number(m==missile);vector(a);vector(b);vector(c);vector(d);flags();++m->m_iUnknown17C;return c+d*.125f;}
void kill(CMissile*m){number(6);number(m==missile);flags();m->m_bUnknown184=true;}
void aoe(CMissile*m,CBaseUnit*p){number(7);number(m==missile);number(id(p));flags();}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){output=&out;armed=false;seed=c.index;finishlevel::Fixture f;level=&f.level;f.resources.m_pSceneManager=services->scene;CMissile actual(&f.resources);missile=&actual;for(unsigned i=0;i<4;++i){units[i]=new CCharacter(NULL);units[i]->setPosition(Ogre::Vector3(i+.25f,-float(i),i+.75f));units[i]->m_bBlocksPath=(seed+i)&1;}
 if(seed&2)actual.m_owner.setObject(units[0]);actual.m_bPiercing=seed&4;actual.m_bUnknown144=seed&8;actual.m_bTrackGround=seed&256;actual.m_bCollidesWithObjects=seed&64;actual.m_bUnknown184=seed&128;actual.m_fUnknown170=seed%5*.375f;actual.m_fRadiusOfMissile=seed%7*.125f;actual.m_iNumberOfRicochets=seed/16%4;actual.m_iUnknown17C=seed/32%4;actual.m_fUnknown1C0=seed%7*.5f;
 for(unsigned i=0;i<seed/64%4;++i){actual.m_collisionUnits.add(units[(i+seed/256)%4]);actual.m_collisionStates.add((seed+i)&1);}
 Ogre::Vector3 a(.125f,-.25f,1),b(7,-2,5),position(-4,-5,-6),impact(8,9,10),normal(11,12,13);Ogre::Vector3*impactArg=seed/256%4==1||seed/256%4==3?&position:&impact;Ogre::Vector3*normalArg=seed/256%4>=2?&position:&normal;CBaseUnit*collided=units[3];CBaseUnit**unitArg=seed&1024?NULL:&collided;
 detour::Set hooks;TL_REDIRECT(hooks,mcSort,&sort);TL_REDIRECT(hooks,mcSphere,&sphere);TL_REDIRECT(hooks,mcISA,&isa);TL_REDIRECT(hooks,mcHit,&hit);TL_REDIRECT(hooks,mcRicochet,&ricochet);TL_REDIRECT(hooks,mcKill,&kill);TL_REDIRECT(hooks,mcAOE,&aoe);if(hooks.failed())std::abort();typedef int(*Fn)(CMissile*,Ogre::Vector3,Ogre::Vector3,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,CBaseUnit**);Fn fn=ours?mcNew:mcOld;armed=true;if(!autotest::beginInvocation(out,fn))return;int result=fn(missile,a,b,position,*impactArg,*normalArg,unitArg);out.callCompleted=1;number(result);vector(position);vector(impact);vector(normal);number(id(collided));number(actual.m_collisionUnits.size());number(actual.m_collisionUnits.m_nCapacity);for(unsigned i=0;i<actual.m_collisionUnits.size();++i)number(id(actual.m_collisionUnits[i]));number(actual.m_collisionStates.size());number(actual.m_collisionStates.m_nCapacity);for(unsigned i=0;i<actual.m_collisionStates.size();++i)number(actual.m_collisionStates[i]);number(actual.m_iUnknown17C);number(actual.m_bUnknown184);scalar(actual.m_fUnknown1C0);flags();armed=false;hooks.restore();actual.m_collisionUnits.clear();actual.m_collisionStates.clear();actual.m_owner.setObject(NULL);for(unsigned i=0;i<4;++i)delete units[i];
}
int worker(const tlhybrid_host*host){finishlevel::initializeCharacterText();nativegame::Services native;if(!native.ready())return 1;services=&native;Ogre::SceneManager*old=native.master->m_pSceneManager;native.master->m_pSceneManager=native.scene;for(unsigned i=0;i<2;++i){void*p=NULL;void*a=reinterpret_cast<void*>(0x14a4320+8*i);std::memcpy(&p,a,8);if(!p){if(i)new(a)std::wstring;else new(a)std::string;}}int result=smallmass::run(host,0,"missile_collision_native",0xd038a0,&side,2048);native.master->m_pSceneManager=old;return result;}
}
TL_TEST(missile_collision_native){return systems_fixture::isolated(&worker,host);}
